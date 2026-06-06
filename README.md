# Where-s-daddy-
Where’s Daddy Display

A family-friendly ESP32 location display that shows a simple status of Dad’s location on a dedicated 1.47” LCD screen.

The goal is to provide an easy-to-read display for family members without requiring them to constantly check a phone. The display receives location updates from OwnTracks via MQTT and presents them through a clean, icon-driven interface.

Features

Home Screen 🏠

Displays when Dad is at home.

* Large house icon
* Home status indicator
* Clean, glanceable layout

Driving Screen 🚗

Displays while in motion.

* Vehicle icon
* Live speed display
* Current city/location
* Motion status

Work Screen 👷

Displays when Dad is at work.

* Hard hat icon
* Work status indicator
* Simple industrial-themed layout

Hardware

Planned Hardware

* ESP32-S3
* 1.47” LCD display
* WiFi connection
* USB-C power


Software Stack

Development

* VS Code
* PlatformIO
* Git
* GitHub

Libraries

* LVGL
* TFT_eSPI (or display-specific driver)
* PubSubClient
* ArduinoJson
* WiFi

Data Sources

* OwnTracks
* MQTT Broker
* Home Assistant (optional)

Architecture

Phone
↓
OwnTracks
↓
MQTT Broker
↓
ESP32 Display
↓
LVGL Interface

Project Goals

Phase 1

Static User Interface

* Home screen
* Driving screen
* Work screen
* Touch/button navigation

Phase 2

Live Location Integration

* MQTT connectivity
* OwnTracks integration
* Automatic status switching

Phase 3

Enhanced Information

* Live speed
* City name
* Connection status
* Last update timestamp

Phase 4

Polish

* Animated transitions
* Improved icons
* Deep sleep support
* OTA firmware updates

Design Philosophy

The display should:

* Be readable from across a room
* Require no interaction
* Update automatically
* Be family-friendly
* Avoid information overload

A single glance should answer the question:

“Where’s Daddy?”

Repository Structure

wheres-daddy-display/
├── docs/
├── images/
├── include/
├── src/
│   ├── screens/
│   ├── mqtt/
│   ├── location/
│   └── icons/
├── lib/
├── test/
├── platformio.ini
└── README.md

Future Ideas

* ETA to home
* Weather information
* School pickup mode
* Custom status messages
* Multiple family member tracking
* Home Assistant dashboard integration
* MeshCore location relay support

License

Personal project developed for learning, family automation, and ESP32 experimentation.
