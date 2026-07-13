#pragma once

#include <lvgl.h>

enum class AppScreen {
  Home,
  Driving,
  Work,
};

namespace ScreenManager {

void begin();
void show(AppScreen screen, lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_MOVE_LEFT);
void showNext();
void showPrevious();
AppScreen current();

}  // namespace ScreenManager

