# Mica Face Fresh Install Support Packet

Collected on 2026-07-10 from local Codex workspaces.

## What This Packet Is

This folder gathers the local supporting material I found for rebuilding the Mica Face / `mica-face-display` setup.

The old Raspberry Pi audit shows a project path of `/home/jordan/mica-face-display` and an OpenClaw plugin named `mica-face-display`. I did not find a full local copy of that exact Pi project directory. The closest complete firmware source found locally is the ESP32-C6 1.47 inch LCD project named `Where-s-daddy-`, which matches the face/display prototype work.

## Folder Map

- `firmware/`: docs and build/config files from the ESP32-C6 LCD firmware project.
- `source-archives/where-s-daddy-clean-source.tar.gz`: clean source snapshot for the display firmware, excluding `.git`, `.pio`, `.platformio`, `.venv`, and build artifacts.
- `pi-openclaw/`: OpenClaw configuration, plugin registration evidence, install script, and audit notes showing how `mica-face-display` was loaded.
- `pi-systemd/`: systemd user service files related to Mica Face, OpenClaw gateway, and RemoteTerm MeshCore.
- `vendor-waveshare/`: Waveshare ESP32-C6 LCD demo docs and original demo ZIP.
- `related-mica-stack/`: separate Mica assistant runtime migration docs, included because it may matter if you are rebuilding the broader Mica setup too.

## Known Fresh Install Shape

Hardware/firmware:

- Target board in the PlatformIO config: `esp32-c6-devkitc-1`.
- Display target: ESP32-C6 with 1.47 inch 172 x 320 ST7789 LCD, rotated to 320 x 172 landscape.
- Framework: ESP-IDF via PlatformIO.
- LVGL dependency: `lvgl/lvgl@^8.3.11`.
- Conservative flash config: 2 MB, even though the status doc says esptool identified an ESP32-C6FH8 with 8 MB embedded flash during upload.

Pi/OpenClaw integration:

- OpenClaw gateway service expected at `/home/jordan/.npm-global/lib/node_modules/openclaw/dist/index.js`.
- Gateway port recorded as `18789`.
- Mica Face plugin load path recorded as `/home/jordan/mica-face-display/tools/openclaw-plugin`.
- Serial bridge service executes `/home/jordan/mica-face-display/tools/mica_serial_bridge.py` using PlatformIO's bundled Python.

## Fresh Install Checklist

1. Restore or clone the display firmware source.

   Use `source-archives/where-s-daddy-clean-source.tar.gz` if you want the local source snapshot:

   ```sh
   tar -xzf source-archives/where-s-daddy-clean-source.tar.gz
   cd Where-s-daddy-
   ```

2. Install PlatformIO.

   The original project was built with PlatformIO Core and ESP-IDF:

   ```sh
   python3 -m pip install platformio
   pio run
   ```

3. Review display pins before flashing.

   The pin defaults are in `firmware/app_config.h` and inside the source archive at `Where-s-daddy-/include/app_config.h`. The old placeholder values were:

   ```text
   MOSI=6, SCLK=7, CS=14, DC=15, RST=21, BL=22
   ```

   The old status doc says earlier GPIO 12/13 use interfered with native USB enumeration, so keep those avoided unless you confirm the board wiring.

4. Flash firmware.

   ```sh
   pio run --target upload
   ```

5. Recreate Pi-side project path if using OpenClaw integration.

   The old config expects:

   ```text
   /home/jordan/mica-face-display/tools/openclaw-plugin
   /home/jordan/mica-face-display/tools/mica_serial_bridge.py
   ```

   The exact plugin source was not found locally, so this packet preserves the configuration evidence rather than pretending the plugin code is present.

6. Restore OpenClaw config carefully.

   Use `pi-openclaw/openclaw.json` as a reference, not as a blind overwrite. The important part is:

   ```json
   {
     "plugins": {
       "allow": ["codex", "discord", "mica-face-display", "openai", "memory-core"],
       "load": {
         "paths": ["/home/jordan/mica-face-display/tools/openclaw-plugin"]
       }
     }
   }
   ```

7. Reinstall user services.

   Review and adapt the files in `pi-systemd/`, especially:

   - `mica-serial-bridge.service`
   - `openclaw-gateway.service`
   - `remoteterm-meshcore.service`

   Install them under the target user's systemd user directory, then reload and enable as needed:

   ```sh
   mkdir -p ~/.config/systemd/user
   cp pi-systemd/*.service ~/.config/systemd/user/
   systemctl --user daemon-reload
   systemctl --user enable --now mica-serial-bridge.service
   ```

## Gaps To Resolve

- Full `/home/jordan/mica-face-display` source tree was not present in the local Codex workspace.
- `tools/openclaw-plugin/index.js`, its `openclaw.plugin.json`, and `tools/mica_serial_bridge.py` are referenced by config/service files but were not found as source files.
- Exact final LCD board pinout still needs confirmation.
- Live MQTT/OwnTracks work was planned but not implemented in the firmware snapshot I found.

## Best Starting Points

- Firmware state: `firmware/PROJECT_STATUS.md`
- Build steps: `firmware/README.md`
- Clean source: `source-archives/where-s-daddy-clean-source.tar.gz`
- OpenClaw plugin registration: `pi-openclaw/installs.json`
- Pi service path for serial bridge: `pi-systemd/mica-serial-bridge.service`
