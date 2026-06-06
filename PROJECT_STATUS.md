# Project Status

## 1. What Was Created

- Complete PlatformIO project for an ESP32-S3 with a 1.47 inch 172 x 320 ST7789 LCD, rotated to a 320 x 172 landscape UI.
- Fetched and reviewed the GitHub README and all mockup images on branch `Ui/mockup`: `IMG_1457.jpeg`, `IMG_1458.jpeg`, and `IMG_1459.jpeg`.
- LVGL-based graphical prototype with three screens:
  - Home: large house icon and `AT HOME` dashboard status.
  - Driving: large vehicle icon, placeholder speed, and placeholder city.
  - Work: large hard hat icon, `AT WORK` status, and `GUELPH, ON` placeholder location.
- Mockup-inspired dashboard layout with title header, heart/live indicators, per-screen color themes, hero card, and bottom metric strip.
- Modular source layout:
  - `src/screens` for screen creation, reusable UI components, and screen manager.
  - `src/icons` for LVGL-drawn icon components.
  - `src/location` for placeholder location state.
  - `src/mqtt` for a deliberately empty future MQTT boundary.
  - `include` for app and LVGL configuration.
  - `lib` reserved for project-local PlatformIO libraries.
- Swipe, on-screen arrow, and optional physical button navigation between screens.
- Clear separation between UI code and future data-source code.

## 2. Remaining Work

- Confirm the LCD controller and exact ESP32-S3 pinout for the target hardware.
- Add touch input if the selected 1.47 inch LCD module includes a touch controller.
- Configure a second physical navigation button if previous-screen hardware navigation is needed.
- Replace placeholder driving speed and city values with live location data.
- Add Wi-Fi provisioning or static Wi-Fi configuration.
- Add persistent configuration for MQTT broker settings.
- Add status/error screens for disconnected Wi-Fi, MQTT failures, and stale location updates.

## 3. Recommended Next Steps for MQTT and OwnTracks Integration

- Add Wi-Fi connection management first, keeping connection state outside the screen files.
- Add an MQTT client module under `src/mqtt` using a library such as PubSubClient or AsyncMqttClient.
- Subscribe to the OwnTracks topic for the tracked device, typically `owntracks/user/device`.
- Parse OwnTracks JSON payloads in a dedicated parser module instead of inside UI code.
- Convert parsed OwnTracks data into a small app-level location model in `src/location`.
- Notify the screen manager or active screen when location state changes.
- Add stale-data handling so the UI can show when the last OwnTracks update is too old.
