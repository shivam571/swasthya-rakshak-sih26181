# Architecture (planned)

```
Sensors (MPU6050, DHT22, MAX30100 + pulse sensor, MQ-2)
        │
        ▼
ESP32 sensor fusion & gesture classification
        │
        ├──► OLED display (live vitals)
        ├──► Buzzer (local alert)
        └──► LoRa TX ──► Base-station ESP32 ──► Web dashboard
```

- **On-device fusion**: filtering + cross-checking happens on the wearable's ESP32,
  so local alerts (OLED/buzzer) still work if the LoRa link is down.
- **LoRa relay**: carries vitals + alert state to a base station running a simple
  web server, for monitoring beyond WiFi/mobile range.
- **Gesture SOS**: a specific, deliberate MPU6050 motion pattern (with a debounce/
  confirmation step to cut down false positives) raises a silent alert without
  touching a phone or app.

This mirrors the pipeline described in the team's SIH deck — update it here as the
actual classification logic and thresholds are implemented and tuned.
