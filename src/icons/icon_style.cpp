#include "icons/icon_style.h"

namespace Icons {

lv_obj_t *createIconRoot(lv_obj_t *parent) {
  lv_obj_t *root = lv_obj_create(parent);
  lv_obj_remove_style_all(root);
  lv_obj_set_size(root, 78, 78);
  lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);
  return root;
}

void styleSolid(lv_obj_t *obj, lv_color_t color, uint8_t radius) {
  lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_radius(obj, radius, LV_PART_MAIN);
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
}

void styleLine(lv_obj_t *line, lv_color_t color, uint8_t width) {
  lv_obj_set_style_line_color(line, color, LV_PART_MAIN);
  lv_obj_set_style_line_width(line, width, LV_PART_MAIN);
  lv_obj_set_style_line_rounded(line, true, LV_PART_MAIN);
}

}  // namespace Icons
