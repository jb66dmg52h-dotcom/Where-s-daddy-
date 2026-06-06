#include <cstdio>

#include <lvgl.h>

#include "app_config.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_idf_version.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "screens/screen_manager.h"

namespace {

constexpr const char *Tag = "wheres-daddy";
constexpr spi_host_device_t LcdHost = SPI2_HOST;

lv_disp_draw_buf_t drawBuffer;
lv_color_t drawBufferPixels[AppConfig::ScreenWidth * 40];
esp_lcd_panel_handle_t panelHandle = nullptr;
uint32_t lastNextPressMs = 0;
uint32_t lastPreviousPressMs = 0;

uint32_t millis() {
  return static_cast<uint32_t>(esp_timer_get_time() / 1000ULL);
}

uint64_t pinMaskFor(int pin) {
  if (pin < 0) {
    return 0;
  }

  return 1ULL << static_cast<unsigned>(pin);
}

void lvglTick(void *arg) {
  lv_tick_inc(AppConfig::LvglTickMs);
}

void flushDisplay(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *colorP) {
  esp_lcd_panel_draw_bitmap(panelHandle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, colorP);
  lv_disp_flush_ready(disp);
}

void initBacklight() {
  gpio_config_t config = {};
  config.pin_bit_mask = 1ULL << AppConfig::TftBacklightPin;
  config.mode = GPIO_MODE_OUTPUT;
  config.pull_up_en = GPIO_PULLUP_DISABLE;
  config.pull_down_en = GPIO_PULLDOWN_DISABLE;
  config.intr_type = GPIO_INTR_DISABLE;
  ESP_ERROR_CHECK(gpio_config(&config));
  ESP_ERROR_CHECK(gpio_set_level(static_cast<gpio_num_t>(AppConfig::TftBacklightPin), 1));
}

void initDisplay() {
  spi_bus_config_t busConfig = {};
  busConfig.mosi_io_num = AppConfig::TftMosiPin;
  busConfig.miso_io_num = -1;
  busConfig.sclk_io_num = AppConfig::TftSclkPin;
  busConfig.quadwp_io_num = -1;
  busConfig.quadhd_io_num = -1;
  busConfig.max_transfer_sz = AppConfig::ScreenWidth * 40 * sizeof(lv_color_t);
  ESP_ERROR_CHECK(spi_bus_initialize(LcdHost, &busConfig, SPI_DMA_CH_AUTO));

  esp_lcd_panel_io_handle_t ioHandle = nullptr;
  esp_lcd_panel_io_spi_config_t ioConfig = {};
  ioConfig.dc_gpio_num = static_cast<gpio_num_t>(AppConfig::TftDcPin);
  ioConfig.cs_gpio_num = static_cast<gpio_num_t>(AppConfig::TftCsPin);
  ioConfig.pclk_hz = AppConfig::SpiClockHz;
  ioConfig.lcd_cmd_bits = 8;
  ioConfig.lcd_param_bits = 8;
  ioConfig.spi_mode = 0;
  ioConfig.trans_queue_depth = 10;
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LcdHost, &ioConfig, &ioHandle));

  esp_lcd_panel_dev_config_t panelConfig = {};
  panelConfig.reset_gpio_num = static_cast<gpio_num_t>(AppConfig::TftRstPin);
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
  panelConfig.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
#else
  panelConfig.color_space = ESP_LCD_COLOR_SPACE_RGB;
#endif
  panelConfig.bits_per_pixel = 16;
  ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(ioHandle, &panelConfig, &panelHandle));

  ESP_ERROR_CHECK(esp_lcd_panel_reset(panelHandle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(panelHandle));
  ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panelHandle, true));
  ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panelHandle, true));
  ESP_ERROR_CHECK(esp_lcd_panel_mirror(panelHandle, false, true));
  ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panelHandle, AppConfig::St7789XGap, AppConfig::St7789YGap));
  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panelHandle, true));
  initBacklight();
}

void initLvgl() {
  lv_init();
  lv_disp_draw_buf_init(&drawBuffer, drawBufferPixels, nullptr, AppConfig::ScreenWidth * 40);

  static lv_disp_drv_t displayDriver;
  lv_disp_drv_init(&displayDriver);
  displayDriver.hor_res = AppConfig::ScreenWidth;
  displayDriver.ver_res = AppConfig::ScreenHeight;
  displayDriver.flush_cb = flushDisplay;
  displayDriver.draw_buf = &drawBuffer;
  lv_disp_drv_register(&displayDriver);

  esp_timer_create_args_t tickTimerArgs = {};
  tickTimerArgs.callback = &lvglTick;
  tickTimerArgs.arg = nullptr;
  tickTimerArgs.dispatch_method = ESP_TIMER_TASK;
  tickTimerArgs.name = "lvgl_tick";
  tickTimerArgs.skip_unhandled_events = true;

  esp_timer_handle_t tickTimer = nullptr;
  ESP_ERROR_CHECK(esp_timer_create(&tickTimerArgs, &tickTimer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(tickTimer, AppConfig::LvglTickMs * 1000));
}

void initNavigationButtons() {
  const uint64_t pinMask = pinMaskFor(AppConfig::NavNextButtonPin) | pinMaskFor(AppConfig::NavPreviousButtonPin);

  gpio_config_t config = {};
  config.pin_bit_mask = pinMask;
  config.mode = GPIO_MODE_INPUT;
  config.pull_up_en = GPIO_PULLUP_ENABLE;
  config.pull_down_en = GPIO_PULLDOWN_DISABLE;
  config.intr_type = GPIO_INTR_DISABLE;
  ESP_ERROR_CHECK(gpio_config(&config));
}

void pollNavigationButtons() {
  const uint32_t now = millis();

  if (gpio_get_level(static_cast<gpio_num_t>(AppConfig::NavNextButtonPin)) == 0 &&
      now - lastNextPressMs > AppConfig::ButtonDebounceMs) {
    lastNextPressMs = now;
    ScreenManager::showNext();
  }

  if (AppConfig::NavPreviousButtonPin >= 0 &&
      gpio_get_level(static_cast<gpio_num_t>(AppConfig::NavPreviousButtonPin)) == 0 &&
      now - lastPreviousPressMs > AppConfig::ButtonDebounceMs) {
    lastPreviousPressMs = now;
    ScreenManager::showPrevious();
  }
}

}  // namespace

extern "C" void app_main() {
  ESP_LOGI(Tag, "Starting Where's Daddy display");

  initDisplay();
  initLvgl();
  initNavigationButtons();
  ScreenManager::begin();

  while (true) {
    pollNavigationButtons();
    lv_timer_handler();
    vTaskDelay(pdMS_TO_TICKS(AppConfig::LvglTickMs));
  }
}
