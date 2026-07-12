# Mica Migration Report

Generated: 2026-06-27

## Disk Audit

Visible macOS disk layout:
- External SSD: `/dev/disk4`
- Boot partition: `/dev/disk4s1`, mounted at `/Volumes/bootfs`
- Linux root partition: `/dev/disk4s2`, ext4, not mounted by macOS
- Rootfs from `cmdline.txt`: `root=PARTUUID=d299bceb-02 rootfstype=ext4`

macOS could not mount or read the ext4 Linux root filesystem in this environment:
- No ext4 readers/writers were present (`ext4fuse`, `fuse-ext2`, `e2ls`, and `debugfs` were not installed).
- Raw `/dev/rdisk4s2` read access was blocked by macOS permissions.

Because of that, this migration pass backed up and inspected the mounted boot partition and staged Pi-side scripts to finish rootfs salvage after booting Linux.

## Backup Created

Visible boot/OpenClaw files were copied to:

`/Volumes/bootfs/mica_salvage_backup_2026-06-27_1110`

Copied files:
- `/Volumes/bootfs/openclaw-offline-repair.sh`
- `/Volumes/bootfs/user-data`
- `/Volumes/bootfs/meta-data`
- `/Volumes/bootfs/network-config`
- `/Volumes/bootfs/cmdline.txt`
- `/Volumes/bootfs/config.txt`

Secrets were preserved in copied files but were not printed during the audit.

## OpenClaw Parts Found From Bootfs

Cloud-init `user-data` invokes:
- `bash /boot/firmware/openclaw-offline-repair.sh >> /var/log/openclaw-offline-repair.log 2>&1 || true`

`openclaw-offline-repair.sh` references:
- SSH and NetworkManager boot enablement.
- Home Assistant MeshCore config at `/home/jordan/homeassistant/config/.storage/core.config_entries`.
- Stable Heltec MeshCore serial path:
  - `/dev/serial/by-id/usb-Espressif_Systems_heltec_wifi_lora_32_v4__16_MB_FLASH__2_MB_PSRAM__441BF669CE78-if00`
- Watchdog path:
  - `/home/jordan/.local/bin/openclaw-gateway-watchdog`
- Logs:
  - `/home/jordan/.openclaw/logs/gateway-watchdog.log`
  - `/var/log/openclaw-offline-repair.log`
- OpenClaw user services/timers:
  - `openclaw-gateway.service`
  - `openclaw-mesh-live-watcher.service`
  - `openclaw-gateway-watchdog.timer`
  - `openclaw-mesh-status.timer`
  - `openclaw-postboot-health.timer`

## Mica Identity Recovered

Recovered directly:
- Mica is replacing OpenClaw as the primary Discord assistant runtime.
- Mica should retain personality, memory, Discord behavior, MeshCore/MQTT/telemetry ideas, and remote terminal concepts.
- Normal Discord chat must not use Codex.
- Codex/dev tools must remain disabled by default.
- The Pi environment appears centered around user `jordan`, hostname `Mesh-pi`, Discord health, MeshCore serial integration, and Home Assistant MeshCore config.

Not yet recoverable from macOS:
- Rootfs-resident prompt files.
- Rootfs-resident memory files.
- Discord bot source and `.env` files.
- OpenClaw rootfs service units and logs beyond names referenced from bootfs.

Run `scripts/backup_old_openclaw.sh` on the Pi to complete rootfs extraction before disabling OpenClaw.

## New Stack Created

Created under `mica_stack/`:
- `bot.py`
- `requirements.txt`
- `.env.example`
- `README.md`
- `config/mica_personality.md`
- `config/settings.example.json`
- `data/memory.sqlite`
- `data/memory_seed.md`
- `tools/router.py`
- `tools/system_status.py`
- `tools/mqtt_client.py`
- `tools/meshcore.py`
- `tools/remoteterm.py`
- `services/mica-bot.service`
- `scripts/install_on_pi.sh`
- `scripts/run_dev.sh`
- `scripts/backup_old_openclaw.sh`
- `scripts/disable_openclaw.sh`

## Safe Boot Plan

1. Eject the SSD from macOS.
2. Boot it on the Raspberry Pi.
3. Log in as `jordan`.
4. Run:

```bash
cd /boot/firmware/mica_stack
bash scripts/backup_old_openclaw.sh
bash scripts/install_on_pi.sh
sudo nano /opt/mica_stack/.env
sudo systemctl start mica-bot.service
sudo journalctl -u mica-bot.service -f
```

5. After Mica connects to Discord and responds:

```bash
bash /opt/mica_stack/scripts/disable_openclaw.sh
```

## Rollback

To stop Mica:

```bash
sudo systemctl disable --now mica-bot.service
```

To re-enable OpenClaw user services, boot the Pi and run the relevant `systemctl --user` enables for the units listed above. If `disable_openclaw.sh` renamed `/boot/firmware/openclaw-offline-repair.sh`, rename the `.disabled.TIMESTAMP` file back to `openclaw-offline-repair.sh` and restore the backed-up `user-data.before-openclaw-disable.TIMESTAMP` if needed.

Do not delete the `mica_salvage_backup_*` folders until the new Mica stack has been verified over multiple boots.
