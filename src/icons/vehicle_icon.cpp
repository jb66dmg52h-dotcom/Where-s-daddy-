#include "icons/vehicle_icon.h"

#include "icons/icon_style.h"

namespace Icons {

lv_obj_t *createVehicleIcon(lv_obj_t *parent, lv_color_t color) {
  lv_obj_t *root = createIconRoot(parent);

  lv_obj_t *cabin = lv_obj_create(root);
  lv_obj_set_size(cabin, 38, 22);
  lv_obj_align(cabin, LV_ALIGN_TOP_MID, 0, 18);
  styleSolid(cabin, color, 8);

  lv_obj_t *body = lv_obj_create(root);
  lv_obj_set_size(body, 64, 26);
  lv_obj_align(body, LV_ALIGN_CENTER, 0, 8);
  styleSolid(body, color, 8);

  lv_obj_t *window = lv_obj_create(root);
  lv_obj_set_size(window, 26, 12);
  lv_obj_align(window, LV_ALIGN_TOP_MID, 0, 24);
  styleSolid(window, lv_color_hex(0x101418), 4);

  const int wheelOffsets[] = {-22, 22};
  for (int i = 0; i < 2; ++i) {
    const int x = wheelOffsets[i];
    lv_obj_t *wheel = lv_obj_create(root);
    lv_obj_set_size(wheel, 17, 17);
    lv_obj_align(wheel, LV_ALIGN_CENTER, x, 24);
    styleSolid(wheel, lv_color_hex(0xF5F7FA), 9);

    lv_obj_t *hub = lv_obj_create(wheel);
    lv_obj_set_size(hub, 7, 7);
    lv_obj_center(hub);
    styleSolid(hub, lv_color_hex(0x101418), 5);
  }

  return root;
}

}  // namespace Icons
