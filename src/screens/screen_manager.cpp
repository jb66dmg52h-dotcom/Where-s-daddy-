#include "screens/screen_manager.h"

#include "screens/driving_screen.h"
#include "screens/home_screen.h"
#include "screens/work_screen.h"

namespace {

AppScreen activeScreen = AppScreen::Home;

lv_obj_t *createScreen(AppScreen screen) {
  switch (screen) {
    case AppScreen::Home:
      return Screens::createHomeScreen();
    case AppScreen::Driving:
      return Screens::createDrivingScreen();
    case AppScreen::Work:
      return Screens::createWorkScreen();
  }

  return Screens::createHomeScreen();
}

AppScreen nextScreen(AppScreen screen) {
  switch (screen) {
    case AppScreen::Home:
      return AppScreen::Driving;
    case AppScreen::Driving:
      return AppScreen::Work;
    case AppScreen::Work:
      return AppScreen::Home;
  }

  return AppScreen::Home;
}

AppScreen previousScreen(AppScreen screen) {
  switch (screen) {
    case AppScreen::Home:
      return AppScreen::Work;
    case AppScreen::Driving:
      return AppScreen::Home;
    case AppScreen::Work:
      return AppScreen::Driving;
  }

  return AppScreen::Home;
}

}  // namespace

namespace ScreenManager {

void begin() {
  show(AppScreen::Home, LV_SCR_LOAD_ANIM_NONE);
}

void show(AppScreen screen, lv_scr_load_anim_t animation) {
  activeScreen = screen;
  lv_obj_t *newScreen = createScreen(screen);
  lv_scr_load_anim(newScreen, animation, 220, 0, true);
}

void showNext() {
  show(nextScreen(activeScreen), LV_SCR_LOAD_ANIM_MOVE_LEFT);
}

void showPrevious() {
  show(previousScreen(activeScreen), LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}

AppScreen current() {
  return activeScreen;
}

}  // namespace ScreenManager

