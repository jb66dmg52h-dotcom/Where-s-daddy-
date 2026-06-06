#pragma once

#include <Arduino.h>

namespace AppConfig {

constexpr uint16_t ScreenWidth = 320;
constexpr uint16_t ScreenHeight = 172;
constexpr uint8_t DisplayRotation = 1;
constexpr uint32_t LvglTickMs = 5;
constexpr uint8_t NavNextButtonPin = 0;
constexpr int8_t NavPreviousButtonPin = -1;
constexpr uint16_t ButtonDebounceMs = 180;

// These values are placeholders for the graphical prototype. The location
// layer owns them so future MQTT/OwnTracks updates do not bleed into UI code.
constexpr int PlaceholderSpeedKph = 72;
constexpr const char *PlaceholderCity = "HIGHWAY 401";
constexpr const char *PlaceholderUpdatedTime = "11:23 AM";

}  // namespace AppConfig
