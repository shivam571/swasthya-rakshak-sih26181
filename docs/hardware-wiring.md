# Hardware Wiring Reference

Board: **DOIT ESP32 DEVKIT V1**

## Ra-02 / SX1278 LoRa module

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

Frequency: `433E6`. Validated point-to-point between two ESP32 boards using the
sketches in `firmware/lora-test/`.

## Other sensors (pins TBD as bring-up proceeds)

| Component | Interface | Notes |
|---|---|---|
| MPU6050 | I2C (SDA/SCL) | Gesture + fall sensing |
| MAX30100 | I2C (SDA/SCL) | Heart rate & SpO2, shares the bus with MPU6050 — confirm addresses don't clash |
| DHT22 | 1-wire digital | Ambient temp/humidity |
| MQ-2 | Analog | Gas/hazard threshold sensing |
| SSD1306 OLED | I2C (SDA/SCL) | On-wrist display — receiver board does **not** use one |
| Buzzer | Digital output | Local audible alert |
| Analog pulse sensor | Analog | Second heart-rate source, cross-checked against MAX30100 |
| TP4056 | Charges the Li-ion/LiPo cell | Not connected to ESP32 GPIO |

Fill in exact GPIO pin numbers for each sensor here as you wire them up, so the
main `gesture-band.ino` skeleton can be completed against real pin assignments.

## Notes

- The **receiver** ESP32 in the LoRa test does not have an OLED attached; it instead
  runs a small web server to show received data (see `firmware/lora-test/lora_receiver`).
- I2C address conflicts between MPU6050 and MAX30100 are a common gotcha — check
  datasheets before wiring both onto the same bus.
