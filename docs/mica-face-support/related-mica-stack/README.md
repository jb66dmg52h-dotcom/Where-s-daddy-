# Mica Stack

Mica is a lightweight replacement runtime for the old OpenClaw setup.

The base stack includes:
- Python 3 Discord bot.
- Generic lightweight HTTP model API client.
- Mica personality prompt in `config/mica_personality.md`.
- SQLite recent-memory store in `data/memory.sqlite`.
- Tool router for system status, MQTT status, MeshCore placeholders, RemoteTerm placeholders, and disabled-by-default dev/Codex commands.

## Install On The Pi

Boot the SSD on the Raspberry Pi, then run:

```bash
cd /boot/firmware/mica_stack
bash scripts/backup_old_openclaw.sh
bash scripts/install_on_pi.sh
sudo nano /opt/mica_stack/.env
sudo systemctl start mica-bot.service
sudo journalctl -u mica-bot.service -f
```

After Mica starts successfully:

```bash
bash /opt/mica_stack/scripts/disable_openclaw.sh
```

Do not delete OpenClaw folders until Mica has booted and Discord behavior has been verified.

## Discord Use

Mention Mica or use the configured prefix:

```text
!mica status
!mica mqtt
!mica mesh
!mica hello
```

Normal chat uses `MODEL_API_URL`; it does not use Codex.

## Dev Tools

Dev/Codex routing is disabled by default:

```env
ENABLE_CODEX_DEV_TOOLS=false
```

Leave it that way unless you are deliberately wiring a future debug executor.
