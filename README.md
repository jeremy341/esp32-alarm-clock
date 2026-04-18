# ⏰ ESP32 Alarm Clock / Funkuhr

A modular ESP32-based smart alarm clock with TFT display, real-time clock (RTC), button navigation, and expandable firmware architecture.  
Designed for learning embedded systems, UI development, and future hardware enclosure integration.

---

## 📌 Overview

This project turns an ESP32 into a fully functional digital alarm clock with:

- Precise timekeeping using DS3231 RTC
- Graphical UI on ILI9341 TFT display
- Button-based navigation system
- Alarm scheduler with persistent settings
- Modular and expandable firmware design
- CAD-ready enclosure planning

---

## 🧠 Core Components

| Component | Model |
|---|---|
| MCU | ESP32-WROOM-32 |
| Display | ILI9341 2.8" SPI TFT (320×240) |
| RTC | DS3231 (I2C) |
| Buzzer | Not currently implemented in firmware |
| Buttons | 3 tactile switches |
| Power | 5V USB input (optional Li-ion system) |

---

## 🔌 Pin Configuration (ESP32)

### 📺 ILI9341 (SPI)
| Signal | GPIO |
|---|---|
| SCK | 18 |
| MOSI | 23 |
| MISO | 19 |
| CS | 15 |
| DC | 2 |
| RESET | 4 |

---

### ⏰ DS3231 (I2C)
| Signal | GPIO |
|---|---|
| SDA | 21 |
| SCL | 22 |

> The RTC is initialized with `Wire.begin()` and uses the ESP32 default I2C pins.

---

### 🔘 Buttons
| Function | GPIO |
|---|---|
| MODE | 32 |
| UP | 33 |
| DOWN | 27 |

> Buttons are read with `INPUT_PULLUP` and should be wired to GND.

---

## 🧱 Project Structure (PlatformIO)


All buttons are wired to GND with INPUT_PULLUP — no external resistors needed.

---

## Firmware

### Build

```bash
cd firmware
pio run
pio run --target upload
pio run --target uploadfs   # uploads LittleFS partition (empty on first flash)
```

Requires PlatformIO. All libraries are declared in `platformio.ini` and fetched automatically.

### Module overview

```
firmware/src/
├── main.cpp                    App controller and main Arduino loop
├── core/app.cpp                App state, event processing, alarm flow
├── core/input.cpp              Debounced 3-button driver
├── display/display.cpp         ILI9341 renderer and layout drawing
├── serial/receiver.cpp         Binary packet parser and serial transport
├── time/clock.cpp              DS3231 RTC wrapper and clock snapshot
├── storage/config_store.cpp    LittleFS preset/alarm persistence
├── storage/littlefs_manager.cpp LittleFS initialization
├── ui/ui_engine.cpp            Layout/theme/clock-style resolution
```

### Button behaviour

| Button | Short press |
|---|---|
| MODE | Enter/advance alarm menu |
| UP | Increase value / move up |
| DOWN | Decrease value / move down |

### Layouts

| ID | Name | Description |
|---|---|---|
| `minimal` | Minimal | Large clean digits on black, date below |
| `digital` | Digital | Terminal-style with horizontal rules and status line |
| `retro_pixel` | Retro Pixel | CRT scanlines, pixel shadow, purple/pink palette |

---

## Web App

### Serve locally

```bash
cd web
python -m http.server 8000
# then open http://localhost:8000 in Chrome or Edge
```

WebSerial requires **Chrome or Edge** and a **localhost or HTTPS** origin.

### Features

- **Live clock preview** on each layout card — shows real current time
- **Push to device** — sends layout/theme/clock-style JSON over USB serial
- **Set alarm** — sends alarm hour, minute, and enabled state
- **Sync time** — sends current PC time to the ESP32 RTC

### File structure

```
web/
├── index.html        Single-file app (no bundler needed)
└── js/
    ├── serial.js     WebSerial transport — connect, send, ACK/NACK
    └── protocol.js   Protocol constants mirrored from firmware
```

---

## Wire Protocol

```
[0xAA][0x55][CMD][SEQ][LEN_HI][LEN_LO][PAYLOAD...][CRC_HI][CRC_LO]
```

Payload is always a JSON string. CRC16/CCITT over payload bytes only.

| CMD | Direction | Payload |
|---|---|---|
| `0x00` PING | PC→ESP | `{}` |
| `0x01` PRESET | PC→ESP | `{"layout":"minimal","theme":"oled_black","clockStyle":"clean_24h"}` |
| `0x02` SET_TIME | PC→ESP | `{"year":2025,"month":4,"day":17,"hour":10,"minute":30,"second":0}` |
| `0x03` SET_ALARM | PC→ESP | `{"hour":7,"minute":0,"enabled":true}` |
| `0x80` ACK | ESP→PC | echoed SEQ byte |
| `0x81` NACK | ESP→PC | `[seq, err_code]` |

---

## Storage

Preset and alarm are persisted to LittleFS:

```
/preset.json   {"layout":"minimal","theme":"oled_black","clockStyle":"clean_24h"}
/alarm.json    {"hour":7,"minute":0,"enabled":false}
```

Both are loaded at boot. Missing files fall back to defaults.

---

## Testing without hardware

Open `web/index.html` via `python -m http.server` in Chrome.

The UI is fully testable without an ESP32 — live clock previews, theme/style pickers, and alarm inputs all work. The "Push", "Set alarm", and "Sync time" buttons are disabled until a serial port is connected.

To mock the serial connection and inspect packets in DevTools:

```js
// Paste in DevTools console before clicking Connect
navigator.serial.requestPort = async () => ({
  open: async () => {},
  writable: { getWriter: () => ({ write: async d => console.log('TX:', d), releaseLock: ()=>{} }) },
  readable: { getReader: () => ({ read: async () => ({ done: true }), releaseLock: ()=>{} }) },
  close: async () => {}
});
```

---

## License

MIT
