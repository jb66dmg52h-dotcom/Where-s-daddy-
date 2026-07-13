#include "screens/work_screen.h"

#include "icons/hard_hat_icon.h"
#include "screens/ui_components.h"

namespace Screens {

lv_obj_t *createWorkScreen() {
  lv_obj_t *screen = Ui::createBaseScreen();
  Ui::createHeader(screen);

  const lv_color_t accent = lv_color_hex(0xF37B23);
  lv_obj_t *panel =
      Ui::createHeroPanel(screen, "AT WORK", "GUELPH, ON", accent, lv_color_hex(0x67300D), lv_color_hex(0x934616));
  lv_obj_t *icon = Icons::createHardHatIcon(panel, accent);
  Ui::createIconBadge(panel, icon, accent);

  Ui::createInfoStrip(screen, "NOT MOVING", "0 km/h", "WORK", "11:23 AM", accent);
  Ui::createNavigationButtons(screen);
  return screen;
}

}  // namespace Screens
