#include "screens/home_screen.h"

#include "icons/home_icon.h"
#include "screens/ui_components.h"

namespace Screens {

lv_obj_t *createHomeScreen() {
  lv_obj_t *screen = Ui::createBaseScreen();
  Ui::createHeader(screen);

  const lv_color_t accent = lv_color_hex(0x65D83D);
  lv_obj_t *panel =
      Ui::createHeroPanel(screen, "AT HOME", "GUELPH, ON", accent, lv_color_hex(0x173F17), lv_color_hex(0x2E5F22));
  lv_obj_t *icon = Icons::createHomeIcon(panel, accent);
  Ui::createIconBadge(panel, icon, accent);

  Ui::createInfoStrip(screen, "NOT MOVING", "0 km/h", "AT HOME", "11:23 AM", accent);
  Ui::createNavigationButtons(screen);
  return screen;
}

}  // namespace Screens
