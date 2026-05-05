# ESP32-S3 Alarm Clock

Custom alarm clock built around an `ESP32-S3-WROOM-1` on a dedicated PCB, with an `ILI9341` display, battery power path, WebSerial preset control, and persistent on-device configuration.

## Overview

- `ESP32-S3-WROOM-1`
- `ILI9341` SPI display
- `IP5306` power-path, Li-ion charge, and boost stage
- `LV75533PDBVR` 3.3 V regulator
- `USBLC6-2SC6` USB ESD protection
- `2N3904` transistor-driven buzzer stage with `1N4148`
- `LittleFS` storage for presets and alarms
- WebSerial browser app for preset upload

## Hardware

| Block | Part | Role |
|---|---|---|
| MCU | `ESP32-S3-WROOM-1` | Main control, USB serial, UI logic |
| Display | `ILI9341` | TFT clock UI |
| USB | USB-C receptacle | Power + USB data |
| ESD | `USBLC6-2SC6` | Protection for `D+` / `D-` |
| Power manager | `IP5306` | Li-ion charging and 5 V boost |
| 3.3 V rail | `LV75533PDBVR` | Logic supply for ESP32-S3 and display |
| Audio driver | `2N3904` + `1N4148` | GPIO-switched buzzer stage |
| Storage | `LittleFS` | Preset and alarm persistence |

## Power Path

```text
USB-C VBUS
  -> IP5306
     -> Li-ion charging
     -> 5V_SYS
        -> LV75533PDBVR
           -> 3.3V rail
              -> ESP32-S3 + ILI9341 + logic
```

The board uses local `100 nF` and `10 uF` decoupling around the ESP32-S3, regulator, and display rail. Keep those loops tight and maintain a clean shared ground reference across the USB, power, MCU, and display sections.

## Pin Map

### ILI9341

| Signal | GPIO |
|---|---|
| `SCK` | `GPIO12` |
| `MOSI` | `GPIO11` |
| `MISO` | `GPIO13` |
| `CS` | `GPIO10` |
| `DC` | `GPIO9` |
| `RST` | `GPIO14` |

### Buttons

| Function | GPIO | Notes |
|---|---|---|
| `RESET` | `EN` | Active low |
| `BOOT` | `GPIO0` | Hold low during reset for flash mode |
| `MENU` | `GPIO1` | `INPUT_PULLUP`, switch to GND |
| `UP` | `GPIO2` | `INPUT_PULLUP`, switch to GND |
| `DOWN` | `GPIO5` | `INPUT_PULLUP`, switch to GND |

### Other Signals

| Signal | GPIO | Notes |
|---|---|---|
| `BUZZER` | `GPIO4` | Drives transistor stage |
| `USB D-` | `GPIO19` | USB only |
| `USB D+` | `GPIO20` | USB only |

## Firmware Notes

```text
firmware/src/
├── main.cpp
├── core/
├── display/
├── protocol/
├── serial/
├── storage/
├── time/
└── ui/
```

The firmware is preset-driven: the ESP32 renders the full UI locally, stores the selected preset in `LittleFS`, and only redraws clock-dependent regions during updates.

Recent cleanup in this repo:

- removed the old hard dependency on a DS3231/RTClib clock path
- switched timekeeping to a lightweight software clock with serial time sync support
- fixed a stale-snapshot bug in the main loop so alarm/display updates use the current time
- avoided unnecessary preset re-renders and writes when the selection has not changed

## Protocol

The WebSerial link uses a compact framed packet with JSON payloads:

```text
[MAGIC0][MAGIC1][VERSION][TYPE][LEN_LO][LEN_HI][PAYLOAD][CRC16]
```

Currently used packet types:

- `0x01`: preset selection
- `0x02`: set time

## Storage

```text
/preset.json
/alarm.json
```

## Web App

The browser app is served from `web/` and is intended for Chromium-based browsers with WebSerial support. Its current main path is preset selection and upload; the firmware also supports serial time sync at the protocol level.

## Getting Started

```bash
cd firmware
pio run
pio run -t upload
pio run -t uploadfs
```

```bash
cd web
python -m http.server 8000
```

Then open [http://localhost:8000](http://localhost:8000) in Chrome or Edge.

## License

MIT
