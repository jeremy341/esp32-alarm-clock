# ESP32-S3 Alarm Clock

Custom-PCB alarm clock built around the `ESP32-S3-WROOM-1`, with an `ILI9341` SPI display, WebSerial control app, persistent settings, and modular firmware.

## What Matters

- `ESP32-S3-WROOM-1` target with USB-C power and data
- `ILI9341` TFT UI rendered on-device
- `LittleFS` storage for preset and alarm settings
- Browser control app over `WebSerial` in Chrome/Edge
- Three `INPUT_PULLUP` user buttons plus `EN` and `GPIO0`
- `IP5306` battery/boost stage and `AMS1117-3.3` logic rail

## Hardware

| Block | Part |
|---|---|
| MCU | `ESP32-S3-WROOM-1` |
| Display | `ILI9341` SPI TFT |
| Power path | `USB-C -> IP5306 -> AMS1117-3.3` |
| Storage | `LittleFS` |
| Audio | GPIO buzzer output |
| Control app | WebSerial browser UI |

## Power

```text
USB-C VBUS (5V)
  -> IP5306
     -> LiPo charging
     -> 5V boost output
        -> AMS1117-3.3
           -> ESP32-S3 + display + logic
```

Keep `100nF` decoupling close to active devices, use `10uF` bulk caps on local rails, and keep the `AMS1117` input/output capacitor loops compact. A continuous ground reference and careful power routing matter more here than any firmware optimization.

## Pin Map

### Display (`ILI9341`)

| Signal | GPIO | Note |
|---|---|---|
| `SCK` | `GPIO12` | SPI clock, avoid external pull-downs |
| `MOSI` | `GPIO11` | SPI data out |
| `MISO` | `GPIO6` | Optional, can be left unused |
| `CS` | `GPIO10` | Chip select |
| `DC` | `GPIO9` | Data / command |
| `RST` | `GPIO14` | Display reset |

### Buttons

| Function | GPIO | Note |
|---|---|---|
| `EN` | `EN` | Reset button, active low |
| `BOOT` | `GPIO0` | Low during reset enters flash mode |
| `BUTTON 1` | `GPIO1` | `INPUT_PULLUP`, switch to GND |
| `BUTTON 2` | `GPIO2` | `INPUT_PULLUP`, switch to GND |
| `BUTTON 3` | `GPIO3` | `INPUT_PULLUP`, switch to GND |

### Other Signals

| Signal | GPIO | Note |
|---|---|---|
| `BUZZER` | `GPIO4` | PWM-capable |
| `USB D-` | `GPIO19` | Reserve for USB only |
| `USB D+` | `GPIO20` | Reserve for USB only |

## Firmware Layout

```text
firmware/src/
├── main.cpp
├── core/
│   ├── app.cpp
│   └── input.cpp
├── display/
│   └── display.cpp
├── serial/
│   └── receiver.cpp
├── time/
│   └── clock.cpp
├── storage/
│   ├── config_store.cpp
│   └── littlefs_manager.cpp
├── ui/
│   └── ui_engine.cpp
```

- `core/`: app flow, button events, alarm/menu state
- `display/`: TFT init and region-based drawing
- `serial/`: framed packet receive/transmit path
- `time/`: clock source and sync logic
- `storage/`: persistent preset/alarm files in LittleFS
- `ui/`: layout, theme, and clock-style composition

## Web App

```text
web/
├── index.html
└── js/
    ├── serial.js
    └── protocol.js
```

The web app is a local control surface for:

- live preview
- pushing layout/theme changes
- setting the alarm
- syncing time over USB

Serve it locally and open it in Chrome or Edge to use WebSerial.

## Protocol

```text
[0xAA][0x55][CMD][SEQ][LEN][PAYLOAD][CRC]
```

- payloads are JSON
- framing is binary
- CRC16 protects the packet

Core commands:

- `PING`
- `PRESET`
- `SET_TIME`
- `SET_ALARM`
- `ACK / NACK`

## Storage

LittleFS persists the active device configuration:

```text
/preset.json
/alarm.json
```

## Getting Started

Firmware:

```bash
cd firmware
pio run
pio run -t upload
pio run -t uploadfs
```

Web:

```bash
cd web
python -m http.server 8000
```

Then open `http://localhost:8000` in Chrome or Edge.

## Notes

- This PCB has **no dedicated RTC module**.
- Time is intended to come from `WiFi/NTP` or `WebSerial` sync.
- If any firmware paths still reference the older RTC-based design, they should be treated as migration work rather than the final hardware model.

## License

MIT
