#include "icons/home_icon.h"

#include "icons/icon_style.h"

namespace Icons {

lv_obj_t *createHomeIcon(lv_obj_t *parent, lv_color_t color) {
  lv_obj_t *root = createIconRoot(parent);

  static lv_point_t roofPoints[] = {{12, 36}, {39, 12}, {66, 36}};
  lv_obj_t *roof = lv_line_create(root);
  lv_line_set_points(roof, roofPoints, 3);
  styleLine(roof, color, 8);

  lv_obj_t *body = lv_obj_create(root);
  lv_obj_set_size(body, 46, 36);
  lv_obj_align(body, LV_ALIGN_BOTTOM_MID, 0, -10);
  styleSolid(body, color, 6);

  lv_obj_t *door = lv_obj_create(root);
  lv_obj_set_size(door, 14, 20);
  lv_obj_align(door, LV_ALIGN_BOTTOM_MID, 0, -10);
  styleSolid(door, lv_color_hex(0x101418), 3);

  return root;
}

}  // namespace Icons
