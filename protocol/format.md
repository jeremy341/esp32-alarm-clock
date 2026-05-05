# ESP32 Alarm Clock Protocol

The alarm clock uses a simple binary packet envelope with a UTF-8 JSON payload.

## Packet layout

| Offset | Size | Meaning |
| --- | --- | --- |
| `0` | 1 | Magic byte `0xAC` |
| `1` | 1 | Magic byte `0xDC` |
| `2` | 1 | Protocol version |
| `3` | 1 | Packet type |
| `4` | 2 | Payload length, little-endian |
| `6` | N | UTF-8 JSON payload |
| `6 + N` | 2 | CRC16-CCITT of bytes `2..(5 + N)` |

## Packet types

- `0x01`: preset configuration JSON
- `0x02`: time synchronization JSON

## Preset JSON payload

```json
{
  "version": 1,
  "layout": "digital",
  "theme": "neon_blue",
  "clockStyle": "split_seconds"
}
```

## Time Sync JSON payload

```json
{
  "year": 2026,
  "month": 5,
  "day": 5,
  "hour": 14,
  "minute": 30,
  "second": 0
}
```

## Notes

- The ESP32 persists the selected preset JSON to LittleFS.
- The current firmware keeps time in software and can be updated over WebSerial.
- Unknown layout, theme, or clock style identifiers fall back to defaults.
- CRC uses polynomial `0x1021` and initial value `0xFFFF`.
