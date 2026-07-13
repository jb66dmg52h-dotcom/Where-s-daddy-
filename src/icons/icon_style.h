#pragma once

#include <lvgl.h>

namespace Icons {

lv_obj_t *createIconRoot(lv_obj_t *parent);
void styleSolid(lv_obj_t *obj, lv_color_t color, uint8_t radius = 6);
void styleLine(lv_obj_t *line, lv_color_t color, uint8_t width = 5);

}  // namespace Icons

