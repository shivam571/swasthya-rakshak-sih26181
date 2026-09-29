/*
  lora_receiver.ino
  ------------------
  Standalone LoRa RX test sketch for the Ra-02 (SX1278) module on ESP32.
  This board has no OLED attached — instead it joins WiFi and serves a small
  web page showing the last packet received over LoRa, plus RSSI/SNR.

  Libraries: "LoRa" by sandeepmistry, built-in WiFi + WebServer (ESP32 core).

  Wiring (Ra-02 -> ESP32): same as lora_sender — see docs/hardware-wiring.md.

  Setup:
    1. Copy wifi_credentials.example.h -> wifi_credentials.h and fill in your SSID/password.
    2. Flash this sketch, open Serial Monitor to see the assigned IP address.
    3. Visit that IP in a browser on the same network to see live packets.
*/

#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
#include "wifi_credentials.h"

#define LORA_NSS   5
#define LORA_RST   14
#define LORA_DIO0  26
#define LORA_FREQ  433E6

WebServer server(80);

String lastPacket = "(none yet)";
int lastRssi = 0;
float lastSnr = 0;
uint32_t packetsReceived = 0;

void handleRoot() {
  String html = "<html><head><meta http-equiv='refresh' content='2'>"
                 "<title>LoRa Receiver</title></head><body>"
                 "<h2>Swastya Rakshak - LoRa Test Receiver</h2>"
                 "<p><b>Packets received:</b> " + String(packetsReceived) + "</p>"
                 "<p><b>Last packet:</b> " + lastPacket + "</p>"
                 "<p><b>RSSI:</b> " + String(lastRssi) + " dBm</p>"
                 "<p><b>SNR:</b> " + String(lastSnr) + " dB</p>"
                 "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed. Check wiring.");
    while (true) { delay(1000); }
  }
  Serial.println("LoRa receiver ready.");

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }
    lastPacket = received;
    lastRssi = LoRa.packetRssi();
    lastSnr = LoRa.packetSnr();
    packetsReceived++;

    Serial.print("Received: ");
    Serial.print(received);
    Serial.print(" | RSSI: ");
    Serial.print(lastRssi);
    Serial.print(" | SNR: ");
    Serial.println(lastSnr);
  }

  server.handleClient();
}
