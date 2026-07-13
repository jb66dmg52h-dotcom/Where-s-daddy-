#include "screens/driving_screen.h"

#include <cstdio>

#include "icons/vehicle_icon.h"
#include "location/location_state.h"
#include "screens/ui_components.h"

namespace Screens {

lv_obj_t *createDrivingScreen() {
  lv_obj_t *screen = Ui::createBaseScreen();
  Ui::createHeader(screen);

  const LocationState state = Location::currentPlaceholderState();
  char speedText[24];
  std::snprintf(speedText, sizeof(speedText), "%d km/h", state.speedKph);

  const lv_color_t accent = lv_color_hex(0x1DA1FF);
  lv_obj_t *panel =
      Ui::createHeroPanel(screen, "DRIVING", state.city, accent, lv_color_hex(0x063E69), lv_color_hex(0x0A5D91));
  lv_obj_t *icon = Icons::createVehicleIcon(panel, accent);
  Ui::createIconBadge(panel, icon, accent);

  Ui::createInfoStrip(screen, "MOVING", speedText, "DRIVE", state.updatedTime, accent);
  Ui::createNavigationButtons(screen);
  return screen;
}

}  // namespace Screens
