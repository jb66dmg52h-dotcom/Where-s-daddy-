#pragma once

#include <lvgl.h>

namespace Ui {

lv_obj_t *createBaseScreen();
void createHeader(lv_obj_t *screen);
lv_obj_t *createHeroPanel(lv_obj_t *screen,
                          const char *status,
                          const char *city,
                          lv_color_t accent,
                          lv_color_t panelColor,
                          lv_color_t cityColor);
void createIconBadge(lv_obj_t *panel, lv_obj_t *icon, lv_color_t accent);
void createInfoStrip(lv_obj_t *screen,
                     const char *movement,
                     const char *speed,
                     const char *status,
                     const char *updated,
                     lv_color_t accent);
void attachNavigation(lv_obj_t *screen);
void createNavigationButtons(lv_obj_t *screen);

}  // namespace Ui
