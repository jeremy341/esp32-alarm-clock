# ESP32 Bitmap System

## Flow
Web App → WebSerial → ESP32 → TFT Display

## Format
- 16-bit RGB565
- raw pixel stream
- header: 0xAA 0x55 + width + height

## MVP Goal
Send 32x32 bitmap to ESP32 and display it