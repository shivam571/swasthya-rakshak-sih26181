/*
  gesture-band.ino
  -----------------
  Main firmware for the Swastya Rakshak wearable (SIH 2026, PS 26181).

  STATUS: SKELETON / WORK IN PROGRESS.
  This file wires up includes, pin definitions we've confirmed so far (LoRa),
  and a rough setup()/loop() shape. It is NOT a finished, tested firmware —
  the sensor bring-up, gesture classification, and alert logic below are
  marked TODO and still need to be written and tested on hardware.

  Confirmed wiring: LoRa (Ra-02/SX1278) — see docs/hardware-wiring.md.
  Sensor pins (MPU6050, MAX30100, DHT22, MQ-2, OLED, buzzer, pulse sensor)
  are NOT yet finalized — fill in as bring-up proceeds and update
  docs/hardware-wiring.md to match.
*/

#include <SPI.h>
#include <LoRa.h>
// TODO: add sensor library includes once pins/bring-up are confirmed, e.g.
// #include <Wire.h>
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <Adafruit_SSD1306.h>
// #include "MAX30100_PulseOximeter.h"

// ---- LoRa (confirmed wiring) ----
#define LORA_NSS   5
#define LORA_RST   14
#define LORA_DIO0  26
#define LORA_FREQ  433E6

// ---- Sensor pins (TODO: fill in once wired) ----
// #define MQ2_PIN        <analog pin>
// #define PULSE_PIN      <analog pin>
// #define BUZZER_PIN     <digital pin>
// #define DHT_PIN        <digital pin>

enum AlertLevel { NORMAL, CAUTION, EMERGENCY };

void setup() {
  Serial.begin(115200);
  while (!Serial) { }

  // ---- LoRa init ----
  LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed. Check wiring.");
    // Not halting here — local sensing/alerting should still work without LoRa.
  } else {
    Serial.println("LoRa ready.");
  }

  // TODO: init I2C bus, MPU6050, MAX30100, DHT22, SSD1306 OLED
  // TODO: init buzzer pin as OUTPUT
  // TODO: init MQ-2 / analog pulse sensor pins as INPUT

  Serial.println("Gesture band firmware skeleton booted. Sensor logic not yet implemented.");
}

void loop() {
  // TODO: read MPU6050 -> feed into gesture classifier
  // TODO: read MAX30100 + analog pulse sensor -> cross-check heart rate/SpO2
  // TODO: read DHT22 -> ambient temp/humidity
  // TODO: read MQ-2 -> hazard/gas threshold check
  // TODO: fuse readings into an AlertLevel (NORMAL / CAUTION / EMERGENCY)
  // TODO: drive OLED display with live vitals
  // TODO: drive buzzer on CAUTION/EMERGENCY
  // TODO: on confirmed SOS gesture or EMERGENCY, send an alert packet over LoRa

  delay(100);
}

// TODO: gesture classification function — deliberate SOS pattern detection
// with a debounce/confirmation step to avoid false positives from everyday
// hand movement.
// AlertLevel classifyGesture(...) { ... }

// TODO: sensor fusion function — combine vitals + ambient + motion into a
// single AlertLevel.
// AlertLevel fuseSensors(...) { ... }
