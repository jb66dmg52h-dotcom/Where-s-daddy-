#pragma once

#include <cstdint>

namespace AppConfig {

constexpr uint16_t ScreenWidth = 320;
constexpr uint16_t ScreenHeight = 172;
constexpr uint8_t DisplayRotation = 1;
constexpr uint32_t LvglTickMs = 5;
constexpr int TftMosiPin = 11;
constexpr int TftSclkPin = 12;
constexpr int TftCsPin = 10;
constexpr int TftDcPin = 13;
constexpr int TftRstPin = 14;
constexpr int TftBacklightPin = 15;
constexpr int St7789XGap = 34;
constexpr int St7789YGap = 0;
constexpr uint32_t SpiClockHz = 40000000;
constexpr int NavNextButtonPin = 0;
constexpr int8_t NavPreviousButtonPin = -1;
constexpr uint16_t ButtonDebounceMs = 180;

// These values are placeholders for the graphical prototype. The location
// layer owns them so future MQTT/OwnTracks updates do not bleed into UI code.
constexpr int PlaceholderSpeedKph = 72;
constexpr const char *PlaceholderCity = "HIGHWAY 401";
constexpr const char *PlaceholderUpdatedTime = "11:23 AM";

}  // namespace AppConfig
