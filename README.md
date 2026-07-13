# Where's Daddy

ESP32-C6 graphical prototype for a 1.47 inch LCD display, styled from the
`Ui/mockup` dashboard mockups.

## Current Prototype

- PlatformIO project for ESP32-C6 using the ESP-IDF framework.
- LVGL dashboard UI with three landscape screens: Home, Driving, and Work.
- Native ESP-IDF `esp_lcd` display driver configured for a 172 x 320 ST7789
  LCD, rotated to 320 x 172 landscape.
- Swipe left/right and on-screen arrow navigation.
- Optional physical button navigation, defaulting to GPIO 0 for next-screen.
- Modular folders for screens, icons, location state, and future MQTT work.

## Build

```sh
pio run
```

## Flash

```sh
pio run --target upload
```

## Display Pins

The default display pin configuration lives in `include/app_config.h`. Update
these values if your ESP32-C6 1.47 inch LCD board uses different wiring:

- `TftMosiPin`
- `TftSclkPin`
- `TftCsPin`
- `TftDcPin`
- `TftRstPin`
- `TftBacklightPin`

## Navigation

- Swipe left/right on touch-capable displays.
- Tap the on-screen arrow buttons on touch-capable displays.
- Press GPIO 0, commonly the BOOT button, to advance screens.

To set a previous-screen physical button, update `NavPreviousButtonPin` in
`include/app_config.h`.
