# Problem Statement

- **Problem Statement ID:** 26181
- **Problem Statement Title:** AI-powered health companion providing real-time
  monitoring and early warnings during disasters
- **Theme:** HealthTech
- **PS Category:** Hardware
- **Team:** Swastya Rakshak

## Our approach

Extend the team's existing Smart Safety Helmet hardware (built for an earlier
CPS-based safety-helmet project) into a wrist-worn gesture band:

- Continuous vitals monitoring (heart rate, SpO2) with a dual-source cross-check
  (MAX30100 + a separate analog pulse sensor) to reduce motion-artifact false readings.
- Ambient hazard sensing (MQ-2 gas/air-quality, DHT22 temperature/humidity).
- Motion sensing (MPU6050) used both for a deliberate gesture-triggered silent SOS
  and for fall detection.
- On-device (ESP32) sensor fusion, so alerts work even without connectivity.
- Local feedback via OLED display + buzzer.
- Long-range relay via a Ra-02 (SX1278) LoRa link to a base-station dashboard, for
  areas without WiFi/mobile coverage — the disaster-response scenario the PS asks for.

This is a living document — expand it as the design firms up.
