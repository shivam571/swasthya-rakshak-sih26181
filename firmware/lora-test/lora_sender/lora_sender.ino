/*
  lora_sender.ino
  ----------------
  Standalone LoRa TX test sketch for the Ra-02 (SX1278) module on ESP32.
  Sends an incrementing counter packet once a second. Used to validate the
  point-to-point link before wiring LoRa into the main gesture-band firmware.

  Library: "LoRa" by sandeepmistry (install via Arduino Library Manager).

  Wiring (Ra-02 -> ESP32):
    VCC  -> 3V3
    GND  -> GND
    MOSI -> GPIO23
    MISO -> GPIO19
    SCK  -> GPIO18
    NSS  -> GPIO5
    RST  -> GPIO14
    DIO0 -> GPIO26
*/

#include <SPI.h>
#include <LoRa.h>

#define LORA_NSS   5
#define LORA_RST   14
#define LORA_DIO0  26
#define LORA_FREQ  433E6

uint32_t counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { }

  LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed. Check wiring.");
    while (true) { delay(1000); }
  }

  Serial.println("LoRa sender ready.");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("PING #");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(1000);
}
