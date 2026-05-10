# ESP32-S3 Alarm Clock

Custom alarm clock built around an `ESP32-S3-WROOM-1` on a dedicated PCB, with an `ILI9341` display, battery powerer , Website , and USB C for both flashing and charging. The website allows the user to choose from existing presets and change the color of them, to change the UI.
I created this Project as a birthday gift for my little sister as in the morning i always wake her up and she doesnt have a alarm, I also wanted to gain new skills as i want to become an enginier and build up my CV.


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
![Fusion 360](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/Case%20Front.png)

![Fusion 360](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/Case%20side.png)

![Fusion 360](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/Case%20Back.png)


![PCB RENDER](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/PCB%20renderd.png)

![PCB Routed](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/PCB%20routed.png)

![PCB Schematic](https://github.com/jeremy341/esp32-alarm-clock/blob/main/images/pcb%20schematic.jpg)



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





## Bill of Materials (BOM)

| Part Name | Distributor | Qty | LCSC Part # / Spec | Link | Price |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **ESP32-S3-WROOM-1** | LCSC | 1 | C2913202 | [Link](https://www.lcsc.com/product-detail/C2913202.html) | $4.95 |
| **IP5306** | LCSC | 1 | C181552 | [Link](https://www.lcsc.com/product-detail/C181552.html) | $3.95 |
| **ILI9341 Display** | Aliexpress | 1 | 2.8" SPI TFT | [Link](https://de.aliexpress.com/item/1005009761383945.html) | $5.79 |
| **3000 mAh LiPo Battery** | Aliexpress | 1 | 3.7V Cell | [Link](https://de.aliexpress.com/item/1005009240348340.html) | $14.99 |
| **Custom PCB** | JLCPCB | 1 | 2-Layer FR4 | [Link](https://jlcpcb.com/) | $6.40 |
| **Mechanical Switch (UP)** | Aliexpress | 1 | Gateron/Akko Style | [Link](https://de.aliexpress.com/item/1005011838889689.html) | $0.00* |
| **Mechanical Switch (DOWN)** | Aliexpress | 1 | Gateron/Akko Style | [Link](https://de.aliexpress.com/item/1005011838889689.html) | $2.73 |
| **Mechanical Switch (Menu)** | Aliexpress | 1 | Gateron/Akko Style | [Link](https://de.aliexpress.com/item/1005011838889689.html) | $0.00* |
| **TLV75533PDBV** | LCSC | 1 | C404027 | [Link](https://www.lcsc.com/product-detail/C404027.html) | $0.62 |
| **USBLC6-2SC6** | LCSC | 1 | C7519 | [Link](https://www.lcsc.com/product-detail/C7519.html) | $0.76 |
| **USB-C Port (16P)** | LCSC | 1 | C165948 | [Link](https://www.lcsc.com/product-detail/C165948.html) | $0.85 |
| **Passive Buzzer** | LCSC | 1 | C409842 | [Link](https://www.lcsc.com/product-detail/C409842.html) | $0.71 |
| **Battery Connector** | LCSC | 1 | C22360303 | [Link](https://www.lcsc.com/product-detail/C22360303.html) | $0.35 |
| **2N3904 Transistor** | LCSC | 1 | C2874602 | [Link](https://www.lcsc.com/product-detail/C2874602.html) | $0.54 |
| **1N4148 Diode** | LCSC | 1 | C85057 | [Link](https://www.lcsc.com/product-detail/C85057.html) | $0.62 |
| **2.2 µH Inductor** | LCSC | 1 | C7427099 | [Link](https://www.lcsc.com/product-detail/C7427099.html) | $0.40 |
| **100nF Capacitor** | LCSC | 1 | C49678 | [Link](https://www.lcsc.com/product-detail/C49678.html) | $0.53 |
| **10uF Capacitor** | LCSC | 5 | C15850 | [Link](https://www.lcsc.com/product-detail/C15850.html) | $0.41 |
| **1uF Capacitor** | LCSC | 1 | C28323 | [Link](https://www.lcsc.com/product-detail/C28323.html) | $0.28 |
| **5.1K Resistor** | LCSC | 2 | C714010 | [Link](https://www.lcsc.com/product-detail/C714010.html) | $0.74 |
| **22Ω Resistor** | LCSC | 2 | C3009224 | [Link](https://www.lcsc.com/product-detail/C3009224.html) | $0.41 |
| **1k Resistor** | LCSC | 1 | C713997 | [Link](https://www.lcsc.com/product-detail/C713997.html) | $0.77 |
| **10K Resistor** | LCSC | 2 | C119347 | [Link](https://www.lcsc.com/product-detail/C119347.html) | $0.56 |
| **System Button (BOOT)** | LCSC | 1 | C42416254 | [Link](https://www.lcsc.com/product-detail/C42416254.html) | $1.46 |
| **System Button (RESET)** | LCSC | 1 | C42416254 | [Link](https://www.lcsc.com/product-detail/C42416254.html) | $0.00* |
| **System Button (KEY)** | LCSC | 1 | C42416254 | [Link](https://www.lcsc.com/product-detail/C42416254.html) | $0.00* |

*\*Note: 1 often just shows the minimum quantity availaiable so its just the minimum included in a single pack price, also the $0.00 are duplicates so they are alredy included in the pack of similar items such as the buttons.*


## License

This project is licensed under the **MIT License**. This means you are free to use, modify, and distribute the software and hardware designs, as long as you include the original copyright notice. 

See the [LICENSE](LICENSE) file for the full text.
