# Swastya Rakshak — Personal Health Companion (SIH 2026, PS 26181)

**Smart India Hackathon 2026**
**Problem Statement ID:** 26181
**Problem Statement Title:** AI-powered health companion providing real-time monitoring and early warnings during disasters
**Theme:** HealthTech
**PS Category:** Hardware
**Team:** Swastya Rakshak

## What this is

A wrist-worn "gesture band" that extends our earlier Smart Safety Helmet hardware into
a personal wearable. It continuously tracks the wearer's vitals and nearby hazard
conditions, and can raise a silent, gesture-triggered alert that reaches a base station
over LoRa — even with no WiFi or mobile signal.

## Hardware (ESP32-based)

| Component | Role |
|---|---|
| ESP32 (DOIT ESP32 DEVKIT V1) | Main controller, sensor fusion, gesture classification |
| MPU6050 | Motion / gesture sensing |
| MAX30100 + dedicated analog pulse sensor | Heart rate & SpO2 (dual-source cross-check) |
| DHT22 | Ambient temperature & humidity |
| MQ-2 | Gas / hazard / air-quality sensing |
| SSD1306 OLED | On-wrist live display |
| Buzzer | Local audible alert |
| Ra-02 (SX1278) LoRa module | Long-range link to base station, 433 MHz |
| Li-ion/LiPo cell + TP4056 | Power + charging |

See [`hardware/bom.md`](hardware/bom.md) and [`docs/hardware-wiring.md`](docs/hardware-wiring.md)
for the full parts list and pinout.

## Repo layout

```
firmware/
  gesture-band/     Main wearable firmware (work in progress — sensor fusion + gesture SOS)
  lora-test/        Standalone sender/receiver sketches used to validate the LoRa link
                     before wiring it into the main firmware
docs/                Problem statement, architecture notes, wiring reference
hardware/            Bill of materials
```

## Status

- [x] LoRa point-to-point link validated between two ESP32 boards (`firmware/lora-test/`)
- [ ] Individual sensors (MPU6050, MAX30100, DHT22, MQ-2) bring-up on the gesture band
- [ ] Gesture classification (SOS pattern recognition)
- [ ] Sensor fusion + local alert logic (OLED + buzzer)
- [ ] LoRa integration into main firmware
- [ ] Base-station web dashboard

`firmware/gesture-band/gesture-band.ino` is currently a **skeleton** — includes and pin
definitions are filled in from our wiring notes, but the sensing/fusion/gesture logic
still needs to be written and tested. Update this README's status list as pieces land.

## Building / flashing

Uses the Arduino IDE (or [PlatformIO](https://platformio.org/)) with the ESP32 board package.

**Arduino IDE:**
1. Install the ESP32 board package (Boards Manager → search "esp32").
2. Install libraries via Library Manager: `LoRa` (sandeepmistry), `Adafruit MPU6050`,
   `Adafruit Unified Sensor`, `DHT sensor library`, `Adafruit SSD1306`, `Adafruit GFX Library`,
   `MAX30100lib` (or your preferred MAX30100 driver).
3. Open the relevant `.ino` file, select board **ESP32 Dev Module**, select the correct COM port.
4. Upload.

## LoRa test wiring (Ra-02 / SX1278 ↔ ESP32)

| Ra-02 pin | ESP32 pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| MOSI | GPIO23 |
| MISO | GPIO19 |
| SCK | GPIO18 |
| NSS | GPIO5 |
| RST | GPIO14 |
| DIO0 | GPIO26 |

Frequency: **433E6** (Asia/India band).

## License

MIT — see [`LICENSE`](LICENSE). Swap this out if your team wants something else.
