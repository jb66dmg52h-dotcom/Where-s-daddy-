#include "screens/ui_components.h"

#include "screens/screen_manager.h"

namespace {

const lv_color_t Background = lv_color_hex(0x020509);
const lv_color_t Surface = lv_color_hex(0x07101A);
const lv_color_t SurfaceLine = lv_color_hex(0x1D2B3A);
const lv_color_t Text = lv_color_hex(0xFFFFFF);
const lv_color_t MutedText = lv_color_hex(0x8FA1B8);
const lv_color_t LiveGreen = lv_color_hex(0x4ADE3F);
const lv_color_t AlertRed = lv_color_hex(0xFF2E67);

void onGesture(lv_event_t *event) {
  const lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());

  if (direction == LV_DIR_LEFT) {
    ScreenManager::showNext();
  } else if (direction == LV_DIR_RIGHT) {
    ScreenManager::showPrevious();
  }
}

void styleBox(lv_obj_t *obj, lv_color_t color, uint8_t radius) {
  lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(obj, radius, LV_PART_MAIN);
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
}

void stylePanel(lv_obj_t *obj, lv_color_t color, uint8_t radius) {
  styleBox(obj, color, radius);
  lv_obj_set_style_border_color(obj, SurfaceLine, LV_PART_MAIN);
  lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
}

lv_obj_t *createLabel(lv_obj_t *parent,
                      const char *text,
                      const lv_font_t *font,
                      lv_color_t color,
                      lv_align_t align,
                      int x,
                      int y) {
  lv_obj_t *label = lv_label_create(parent);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
  lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
  lv_obj_align(label, align, x, y);
  return label;
}

void createBattery(lv_obj_t *parent) {
  lv_obj_t *shell = lv_obj_create(parent);
  lv_obj_set_size(shell, 18, 10);
  lv_obj_align(shell, LV_ALIGN_TOP_LEFT, 8, 8);
  stylePanel(shell, lv_color_hex(0x061015), 2);
  lv_obj_set_style_border_color(shell, LiveGreen, LV_PART_MAIN);

  lv_obj_t *level = lv_obj_create(shell);
  lv_obj_set_size(level, 12, 6);
  lv_obj_align(level, LV_ALIGN_LEFT_MID, 2, 0);
  styleBox(level, LiveGreen, 1);

  lv_obj_t *nub = lv_obj_create(parent);
  lv_obj_set_size(nub, 2, 6);
  lv_obj_align(nub, LV_ALIGN_TOP_LEFT, 27, 10);
  styleBox(nub, LiveGreen, 1);
}

void createSignal(lv_obj_t *parent) {
  for (int i = 0; i < 4; ++i) {
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, 4, 5 + i * 4);
    lv_obj_align(bar, LV_ALIGN_TOP_RIGHT, -34 + i * 6, 16 - i * 4);
    styleBox(bar, LiveGreen, 1);
  }

  lv_obj_t *live = createLabel(parent, "LIVE", &lv_font_montserrat_12, LiveGreen, LV_ALIGN_TOP_RIGHT, -8, 18);
  lv_obj_set_width(live, 32);
  lv_label_set_long_mode(live, LV_LABEL_LONG_CLIP);
}

void createSmallVehicle(lv_obj_t *parent) {
  lv_obj_t *body = lv_obj_create(parent);
  lv_obj_set_size(body, 24, 13);
  lv_obj_align(body, LV_ALIGN_LEFT_MID, 8, 5);
  styleBox(body, lv_color_hex(0x238AFF), 4);

  lv_obj_t *roof = lv_obj_create(parent);
  lv_obj_set_size(roof, 16, 9);
  lv_obj_align(roof, LV_ALIGN_LEFT_MID, 12, -3);
  styleBox(roof, lv_color_hex(0x2D9CFF), 4);
}

void createDivider(lv_obj_t *parent, int x) {
  lv_obj_t *divider = lv_obj_create(parent);
  lv_obj_set_size(divider, 1, 34);
  lv_obj_align(divider, LV_ALIGN_TOP_LEFT, x, 6);
  styleBox(divider, SurfaceLine, 0);
}

void createMetricColumn(lv_obj_t *parent, int x, const char *label, const char *value, lv_color_t valueColor) {
  lv_obj_t *column = lv_obj_create(parent);
  lv_obj_remove_style_all(column);
  lv_obj_set_size(column, 96, 36);
  lv_obj_align(column, LV_ALIGN_TOP_LEFT, x, 5);

  lv_obj_t *top = createLabel(column, label, &lv_font_montserrat_12, MutedText, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_width(top, 92);
  lv_obj_set_style_text_align(top, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_label_set_long_mode(top, LV_LABEL_LONG_CLIP);

  lv_obj_t *bottom = createLabel(column, value, &lv_font_montserrat_16, valueColor, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_width(bottom, 92);
  lv_obj_set_style_text_align(bottom, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_label_set_long_mode(bottom, LV_LABEL_LONG_CLIP);
}

}  // namespace

namespace Ui {

lv_obj_t *createBaseScreen() {
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(screen, Background, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
  attachNavigation(screen);
  return screen;
}

void createHeader(lv_obj_t *screen) {
  createBattery(screen);

  lv_obj_t *title = createLabel(screen, "WHERE'S DADDY?", &lv_font_montserrat_20, Text, LV_ALIGN_TOP_LEFT, 38, 3);
  lv_obj_set_width(title, 174);
  lv_label_set_long_mode(title, LV_LABEL_LONG_CLIP);

  createSignal(screen);

  lv_obj_t *rule = lv_obj_create(screen);
  lv_obj_set_size(rule, 304, 2);
  lv_obj_align(rule, LV_ALIGN_TOP_MID, 0, 31);
  styleBox(rule, AlertRed, 1);
}

lv_obj_t *createHeroPanel(lv_obj_t *screen,
                          const char *status,
                          const char *city,
                          lv_color_t accent,
                          lv_color_t panelColor,
                          lv_color_t cityColor) {
  lv_obj_t *panel = lv_obj_create(screen);
  lv_obj_set_size(panel, 304, 78);
  lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 39);
  stylePanel(panel, panelColor, 7);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *statusBox = lv_obj_create(panel);
  lv_obj_set_size(statusBox, 118, 34);
  lv_obj_align(statusBox, LV_ALIGN_TOP_LEFT, 102, 11);
  styleBox(statusBox, accent, 6);

  lv_obj_t *statusLabel = createLabel(statusBox, status, &lv_font_montserrat_24, Text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_width(statusLabel, 112);
  lv_obj_set_style_text_align(statusLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_label_set_long_mode(statusLabel, LV_LABEL_LONG_CLIP);

  lv_obj_t *cityBox = lv_obj_create(panel);
  lv_obj_set_size(cityBox, 132, 24);
  lv_obj_align(cityBox, LV_ALIGN_BOTTOM_LEFT, 102, -8);
  styleBox(cityBox, cityColor, 5);

  createLabel(panel, "O", &lv_font_montserrat_20, Text, LV_ALIGN_BOTTOM_LEFT, 78, -8);

  lv_obj_t *cityLabel = createLabel(cityBox, city, &lv_font_montserrat_16, Text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_width(cityLabel, 126);
  lv_obj_set_style_text_align(cityLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_label_set_long_mode(cityLabel, LV_LABEL_LONG_CLIP);

  return panel;
}

void createIconBadge(lv_obj_t *panel, lv_obj_t *icon, lv_color_t accent) {
  lv_obj_t *badge = lv_obj_create(panel);
  lv_obj_set_size(badge, 58, 58);
  lv_obj_align(badge, LV_ALIGN_LEFT_MID, 18, 0);
  stylePanel(badge, lv_color_hex(0x04100A), 29);
  lv_obj_set_style_border_color(badge, accent, LV_PART_MAIN);
  lv_obj_set_style_border_width(badge, 3, LV_PART_MAIN);

  lv_obj_set_parent(icon, badge);
  lv_obj_set_style_transform_zoom(icon, 205, LV_PART_MAIN);
  lv_obj_center(icon);
}

void createInfoStrip(lv_obj_t *screen,
                     const char *movement,
                     const char *speed,
                     const char *status,
                     const char *updated,
                     lv_color_t accent) {
  lv_obj_t *strip = lv_obj_create(screen);
  lv_obj_set_size(strip, 304, 46);
  lv_obj_align(strip, LV_ALIGN_BOTTOM_MID, 0, -6);
  stylePanel(strip, Surface, 7);
  lv_obj_clear_flag(strip, LV_OBJ_FLAG_SCROLLABLE);

  createSmallVehicle(strip);
  lv_obj_t *speedLabel = createLabel(strip, speed, &lv_font_montserrat_16, Text, LV_ALIGN_LEFT_MID, 38, 6);
  lv_obj_set_width(speedLabel, 54);
  lv_label_set_long_mode(speedLabel, LV_LABEL_LONG_CLIP);

  createDivider(strip, 101);
  createMetricColumn(strip, 104, "STATUS", status, accent);
  createDivider(strip, 202);
  createMetricColumn(strip, 205, "UPDATED", updated, LiveGreen);

  (void)movement;
}

void attachNavigation(lv_obj_t *screen) {
  lv_obj_add_event_cb(screen, onGesture, LV_EVENT_GESTURE, nullptr);
}

void createNavigationButtons(lv_obj_t *screen) {
  (void)screen;
}

}  // namespace Ui
