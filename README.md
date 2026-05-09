# ESP32-S3 Alarm Clock

Custom alarm clock built around an `ESP32-S3-WROOM-1` on a dedicated PCB, with an `ILI9341` display, battery powerer , Website , and USB C for both flashing and charging. The website allows the user to choose from existing presets and change the color of them, to change the UI.
I created this Project as a birthday gift for my little sister as in the morning i always wake her up and she doesnt have a alarm, I also wanted to gain new skills as i want to become an enginier and builduing up my CV.


## Overview

- `ESP32-S3-WROOM-1`
- `ILI9341` SPI display
- `IP5306` power-path, Li-ion charge, and boost stage
- `LV75533PDBVR` 3.3 V regulator
- `USBLC6-2SC6` USB ESD protection
- `2N3904` transistor-driven buzzer stage with `1N4148`
- `LittleFS` storage for presets and alarms
- WebSerial browser app for preset upload

## IMAGES

<img width="1171" height="762" alt="image" src="https://github.com/user-attachments/assets/4c89c337-9c52-4df0-a836-1c3ce4735979" />  

<img width="1014" height="848" alt="image" src="https://github.com/user-attachments/assets/3b6c2eb8-3e09-4b4c-b349-f91c0d51f3b8" />

<img width="1025" height="588" alt="image" src="https://github.com/user-attachments/assets/c4a9b6df-e291-4fa9-b111-0b83a14a283a" />

<img width="1602" height="882" alt="image" src="https://github.com/user-attachments/assets/e7613f12-3904-498b-8f1a-24e8ad1e0358" />

<img width="1557" height="950" alt="image" src="https://github.com/user-attachments/assets/c613a602-3d31-49a3-b2f5-1046ed718bbd" />

<img width="2559" height="1395" alt="image" src="https://github.com/user-attachments/assets/08f149ca-8b9a-4568-9a29-83624bdc535c" />





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
| `GND` | `GND` |
| `VCC` | `3.3V` |

### Buttons

| Function | GPIO | Notes |
|---|---|---|
| `RESET` | `EN` | Active low |
| `BOOT` | `GPIO0` | Hold low during reset for flash mode |
| `MENU` | `GPIO1` | `INPUT_PULLUP`, switch to GND |
| `UP` | `GPIO2` | `INPUT_PULLUP`, switch to GND |
| `DOWN` | `GPIO5` | `INPUT_PULLUP`, switch to GND |

### Other PINS

| Signal | GPIO | Notes |
|---|---|---|
| `BUZZER` | `GPIO4` | Drives transistor stage |
| `USB D-` | `GPIO19` | USB only |
| `USB D+` | `GPIO20` | USB only |



## Web App

The browser app is served from `web/` and is intended for Chrome or firefox, browsers with WebSerial support. Its function is choosing of custom ui and flashing `ESP32`.

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

This project is open-source under the **MIT License**. Feel free to fork, modify, and build your own!
