#include "icons/hard_hat_icon.h"

#include "icons/icon_style.h"

namespace Icons {

lv_obj_t *createHardHatIcon(lv_obj_t *parent, lv_color_t color) {
  lv_obj_t *root = createIconRoot(parent);

  lv_obj_t *dome = lv_arc_create(root);
  lv_obj_set_size(dome, 62, 62);
  lv_obj_align(dome, LV_ALIGN_TOP_MID, 0, 12);
  lv_arc_set_bg_angles(dome, 200, 340);
  lv_arc_set_angles(dome, 200, 340);
  lv_obj_remove_style(dome, nullptr, LV_PART_KNOB);
  lv_obj_set_style_arc_color(dome, color, LV_PART_MAIN);
  lv_obj_set_style_arc_color(dome, color, LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(dome, 24, LV_PART_MAIN);
  lv_obj_set_style_arc_width(dome, 24, LV_PART_INDICATOR);

  lv_obj_t *centerRidge = lv_obj_create(root);
  lv_obj_set_size(centerRidge, 10, 32);
  lv_obj_align(centerRidge, LV_ALIGN_TOP_MID, 0, 24);
  styleSolid(centerRidge, lv_color_hex(0xFDBA74), 5);

  lv_obj_t *brim = lv_obj_create(root);
  lv_obj_set_size(brim, 70, 12);
  lv_obj_align(brim, LV_ALIGN_CENTER, 0, 24);
  styleSolid(brim, color, 8);

  return root;
}

}  // namespace Icons
