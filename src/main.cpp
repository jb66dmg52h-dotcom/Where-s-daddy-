#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#include "app_config.h"
#include "screens/screen_manager.h"

namespace {

TFT_eSPI tft;
lv_disp_draw_buf_t drawBuffer;
lv_color_t drawBufferPixels[AppConfig::ScreenWidth * 40];
uint32_t lastNextPressMs = 0;
uint32_t lastPreviousPressMs = 0;

void flushDisplay(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *colorP) {
  const uint32_t width = area->x2 - area->x1 + 1;
  const uint32_t height = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, width, height);
  tft.pushColors(reinterpret_cast<uint16_t *>(&colorP->full), width * height, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void initDisplay() {
  tft.begin();
  tft.setRotation(AppConfig::DisplayRotation);
  tft.fillScreen(TFT_BLACK);

#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
#endif
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
}

void initNavigationButtons() {
  pinMode(AppConfig::NavNextButtonPin, INPUT_PULLUP);

  if (AppConfig::NavPreviousButtonPin >= 0) {
    pinMode(AppConfig::NavPreviousButtonPin, INPUT_PULLUP);
  }
}

void pollNavigationButtons() {
  const uint32_t now = millis();

  if (digitalRead(AppConfig::NavNextButtonPin) == LOW &&
      now - lastNextPressMs > AppConfig::ButtonDebounceMs) {
    lastNextPressMs = now;
    ScreenManager::showNext();
  }

  if (AppConfig::NavPreviousButtonPin >= 0) {
    if (digitalRead(AppConfig::NavPreviousButtonPin) == LOW &&
        now - lastPreviousPressMs > AppConfig::ButtonDebounceMs) {
      lastPreviousPressMs = now;
      ScreenManager::showPrevious();
    }
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(100);

  initDisplay();
  initLvgl();
  initNavigationButtons();
  ScreenManager::begin();
}

void loop() {
  pollNavigationButtons();
  lv_timer_handler();
  delay(AppConfig::LvglTickMs);
  lv_tick_inc(AppConfig::LvglTickMs);
}
