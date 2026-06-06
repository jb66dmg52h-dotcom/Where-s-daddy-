#include "screens/ui_components.h"

#include "screens/screen_manager.h"

namespace {

const lv_color_t Background = lv_color_hex(0x101418);
const lv_color_t Text = lv_color_hex(0xF5F7FA);
const lv_color_t MutedText = lv_color_hex(0x9EA7B3);
const lv_color_t ButtonFill = lv_color_hex(0x202832);
const lv_color_t ButtonPress = lv_color_hex(0x33404F);
const lv_color_t LiveGreen = lv_color_hex(0x62D45A);
const lv_color_t HeartRed = lv_color_hex(0xD9345C);
const lv_color_t StatusPurple = lv_color_hex(0xA855F7);

void onGesture(lv_event_t *event) {
  const lv_dir_t direction = lv_indev_get_gesture_dir(lv_indev_get_act());

  if (direction == LV_DIR_LEFT) {
    ScreenManager::showNext();
  } else if (direction == LV_DIR_RIGHT) {
    ScreenManager::showPrevious();
  }
}

void onPreviousClicked(lv_event_t *event) {
  ScreenManager::showPrevious();
}

void onNextClicked(lv_event_t *event) {
  ScreenManager::showNext();
}

lv_obj_t *createNavButton(lv_obj_t *screen, const char *label, lv_align_t align, lv_event_cb_t callback) {
  lv_obj_t *button = lv_btn_create(screen);
  lv_obj_set_size(button, 20, 34);
  lv_obj_align(button, align, 2, 0);
  lv_obj_add_event_cb(button, callback, LV_EVENT_CLICKED, nullptr);
  lv_obj_set_style_radius(button, 6, LV_PART_MAIN);
  lv_obj_set_style_bg_color(button, ButtonFill, LV_PART_MAIN);
  lv_obj_set_style_bg_color(button, ButtonPress, LV_STATE_PRESSED);
  lv_obj_set_style_shadow_width(button, 0, LV_PART_MAIN);

  lv_obj_t *buttonLabel = lv_label_create(button);
  lv_label_set_text(buttonLabel, label);
  lv_obj_set_style_text_color(buttonLabel, Text, LV_PART_MAIN);
  lv_obj_center(buttonLabel);

  return button;
}

void stylePanel(lv_obj_t *obj, lv_color_t color, uint8_t radius) {
  lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(obj, radius, LV_PART_MAIN);
  lv_obj_set_style_border_color(obj, lv_color_hex(0x263142), LV_PART_MAIN);
  lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
  lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
}

lv_obj_t *createHeart(lv_obj_t *parent) {
  lv_obj_t *root = lv_obj_create(parent);
  lv_obj_remove_style_all(root);
  lv_obj_set_size(root, 22, 20);

  lv_obj_t *left = lv_obj_create(root);
  lv_obj_set_size(left, 12, 12);
  lv_obj_align(left, LV_ALIGN_TOP_LEFT, 1, 0);
  lv_obj_set_style_radius(left, 6, LV_PART_MAIN);
  lv_obj_set_style_bg_color(left, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(left, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(left, 0, LV_PART_MAIN);

  lv_obj_t *right = lv_obj_create(root);
  lv_obj_set_size(right, 12, 12);
  lv_obj_align(right, LV_ALIGN_TOP_RIGHT, -1, 0);
  lv_obj_set_style_radius(right, 6, LV_PART_MAIN);
  lv_obj_set_style_bg_color(right, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(right, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(right, 0, LV_PART_MAIN);

  lv_obj_t *point = lv_obj_create(root);
  lv_obj_set_size(point, 16, 16);
  lv_obj_align(point, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_transform_angle(point, 450, LV_PART_MAIN);
  lv_obj_set_style_bg_color(point, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(point, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(point, 0, LV_PART_MAIN);
  lv_obj_set_style_radius(point, 2, LV_PART_MAIN);

  return root;
}

void createSignalBars(lv_obj_t *parent) {
  for (int i = 0; i < 4; ++i) {
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, 4, 5 + i * 4);
    lv_obj_align(bar, LV_ALIGN_TOP_RIGHT, -27 + i * 6, 10 - i * 4);
    lv_obj_set_style_bg_color(bar, LiveGreen, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 1, LV_PART_MAIN);
    lv_obj_set_style_border_width(bar, 0, LV_PART_MAIN);
  }
}

void createMiniCar(lv_obj_t *parent, lv_color_t color) {
  lv_obj_t *body = lv_obj_create(parent);
  lv_obj_set_size(body, 34, 16);
  lv_obj_align(body, LV_ALIGN_LEFT_MID, 10, 4);
  lv_obj_set_style_bg_color(body, color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(body, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(body, 4, LV_PART_MAIN);
  lv_obj_set_style_border_width(body, 0, LV_PART_MAIN);

  lv_obj_t *cabin = lv_obj_create(parent);
  lv_obj_set_size(cabin, 22, 12);
  lv_obj_align(cabin, LV_ALIGN_LEFT_MID, 16, -7);
  lv_obj_set_style_bg_color(cabin, color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(cabin, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(cabin, 4, LV_PART_MAIN);
  lv_obj_set_style_border_width(cabin, 0, LV_PART_MAIN);
}

lv_obj_t *createMetricColumn(lv_obj_t *parent,
                             int x,
                             const char *top,
                             const char *bottom,
                             lv_color_t bottomColor) {
  lv_obj_t *column = lv_obj_create(parent);
  lv_obj_remove_style_all(column);
  lv_obj_set_size(column, 82, 36);
  lv_obj_align(column, LV_ALIGN_LEFT_MID, x, 0);

  lv_obj_t *topLabel = lv_label_create(column);
  lv_label_set_text(topLabel, top);
  lv_obj_set_style_text_font(topLabel, &lv_font_montserrat_14, LV_PART_MAIN);
  lv_obj_set_style_text_color(topLabel, Text, LV_PART_MAIN);
  lv_obj_align(topLabel, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *bottomLabel = lv_label_create(column);
  lv_label_set_text(bottomLabel, bottom);
  lv_obj_set_style_text_font(bottomLabel, &lv_font_montserrat_14, LV_PART_MAIN);
  lv_obj_set_style_text_color(bottomLabel, bottomColor, LV_PART_MAIN);
  lv_obj_align(bottomLabel, LV_ALIGN_BOTTOM_LEFT, 0, 0);

  return column;
}

}  // namespace

namespace Ui {

lv_obj_t *createBaseScreen() {
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(screen, Background, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
  attachNavigation(screen);
  return screen;
}

void createHeader(lv_obj_t *screen) {
  lv_obj_t *heart = createHeart(screen);
  lv_obj_align(heart, LV_ALIGN_TOP_LEFT, 9, 4);

  lv_obj_t *title = lv_label_create(screen);
  lv_label_set_text(title, "WHERE'S DADDY?");
  lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN);
  lv_obj_set_style_text_color(title, Text, LV_PART_MAIN);
  lv_obj_align(title, LV_ALIGN_TOP_LEFT, 38, 2);

  lv_obj_t *liveDot = lv_obj_create(screen);
  lv_obj_set_size(liveDot, 11, 11);
  lv_obj_align(liveDot, LV_ALIGN_TOP_RIGHT, -77, 10);
  lv_obj_set_style_radius(liveDot, 6, LV_PART_MAIN);
  lv_obj_set_style_bg_color(liveDot, LiveGreen, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(liveDot, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(liveDot, 0, LV_PART_MAIN);

  lv_obj_t *live = lv_label_create(screen);
  lv_label_set_text(live, "LIVE");
  lv_obj_set_style_text_font(live, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_text_color(live, LiveGreen, LV_PART_MAIN);
  lv_obj_align(live, LV_ALIGN_TOP_RIGHT, -34, 6);

  createSignalBars(screen);

  lv_obj_t *rule = lv_obj_create(screen);
  lv_obj_set_size(rule, 302, 2);
  lv_obj_align(rule, LV_ALIGN_TOP_MID, 0, 33);
  lv_obj_set_style_bg_color(rule, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(rule, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(rule, 0, LV_PART_MAIN);
}

lv_obj_t *createHeroPanel(lv_obj_t *screen,
                          const char *status,
                          const char *city,
                          lv_color_t accent,
                          lv_color_t panelColor,
                          lv_color_t cityColor) {
  lv_obj_t *panel = lv_obj_create(screen);
  lv_obj_set_size(panel, 302, 78);
  lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 41);
  stylePanel(panel, panelColor, 6);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *statusBox = lv_obj_create(panel);
  lv_obj_set_size(statusBox, 118, 38);
  lv_obj_align(statusBox, LV_ALIGN_TOP_LEFT, 95, 10);
  stylePanel(statusBox, accent, 6);
  lv_obj_set_style_border_width(statusBox, 0, LV_PART_MAIN);

  lv_obj_t *statusLabel = lv_label_create(statusBox);
  lv_label_set_text(statusLabel, status);
  lv_obj_set_style_text_font(statusLabel, &lv_font_montserrat_24, LV_PART_MAIN);
  lv_obj_set_style_text_color(statusLabel, Text, LV_PART_MAIN);
  lv_obj_center(statusLabel);

  lv_obj_t *cityBox = lv_obj_create(panel);
  lv_obj_set_size(cityBox, 124, 24);
  lv_obj_align(cityBox, LV_ALIGN_BOTTOM_LEFT, 95, -8);
  stylePanel(cityBox, cityColor, 5);
  lv_obj_set_style_border_width(cityBox, 0, LV_PART_MAIN);

  lv_obj_t *pin = lv_label_create(panel);
  lv_label_set_text(pin, "O");
  lv_obj_set_style_text_font(pin, &lv_font_montserrat_20, LV_PART_MAIN);
  lv_obj_set_style_text_color(pin, Text, LV_PART_MAIN);
  lv_obj_align(pin, LV_ALIGN_BOTTOM_LEFT, 76, -9);

  lv_obj_t *cityLabel = lv_label_create(cityBox);
  lv_label_set_text(cityLabel, city);
  lv_obj_set_style_text_font(cityLabel, &lv_font_montserrat_16, LV_PART_MAIN);
  lv_obj_set_style_text_color(cityLabel, Text, LV_PART_MAIN);
  lv_obj_center(cityLabel);

  return panel;
}

void createIconBadge(lv_obj_t *panel, lv_obj_t *icon, lv_color_t accent) {
  lv_obj_t *badge = lv_obj_create(panel);
  lv_obj_set_size(badge, 74, 74);
  lv_obj_align(badge, LV_ALIGN_LEFT_MID, 8, 0);
  stylePanel(badge, lv_color_hex(0x0E1117), 37);
  lv_obj_set_style_border_color(badge, accent, LV_PART_MAIN);
  lv_obj_set_style_border_width(badge, 4, LV_PART_MAIN);

  lv_obj_set_parent(icon, badge);
  lv_obj_center(icon);
}

void createInfoStrip(lv_obj_t *screen,
                     const char *movement,
                     const char *speed,
                     const char *status,
                     const char *updated,
                     lv_color_t accent) {
  lv_obj_t *strip = lv_obj_create(screen);
  lv_obj_set_size(strip, 302, 42);
  lv_obj_align(strip, LV_ALIGN_BOTTOM_MID, 0, -8);
  stylePanel(strip, lv_color_hex(0x0D1118), 6);
  lv_obj_clear_flag(strip, LV_OBJ_FLAG_SCROLLABLE);

  createMiniCar(strip, lv_color_hex(0x3B82F6));
  createMetricColumn(strip, 52, movement, speed, MutedText);
  createMetricColumn(strip, 136, "STATUS", status, StatusPurple);
  createMetricColumn(strip, 220, "UPDATED", updated, LiveGreen);

  lv_obj_t *leftRule = lv_obj_create(screen);
  lv_obj_set_size(leftRule, 78, 2);
  lv_obj_align(leftRule, LV_ALIGN_BOTTOM_MID, -54, -1);
  lv_obj_set_style_bg_color(leftRule, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(leftRule, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(leftRule, 0, LV_PART_MAIN);

  lv_obj_t *rightRule = lv_obj_create(screen);
  lv_obj_set_size(rightRule, 78, 2);
  lv_obj_align(rightRule, LV_ALIGN_BOTTOM_MID, 54, -1);
  lv_obj_set_style_bg_color(rightRule, HeartRed, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(rightRule, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_width(rightRule, 0, LV_PART_MAIN);
}

void attachNavigation(lv_obj_t *screen) {
  lv_obj_add_event_cb(screen, onGesture, LV_EVENT_GESTURE, nullptr);
}

void createNavigationButtons(lv_obj_t *screen) {
  createNavButton(screen, "<", LV_ALIGN_LEFT_MID, onPreviousClicked);
  createNavButton(screen, ">", LV_ALIGN_RIGHT_MID, onNextClicked);
}

}  // namespace Ui
