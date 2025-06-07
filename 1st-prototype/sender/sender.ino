#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int mode;
  int intensity;
} struct_message;

struct_message msg;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Receiver's MAC 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  if (Serial.available()) {
    String buff = Serial.readStringUntil('\n');
    int comma = buff.indexOf(',');
    if (comma != -1) {
      msg.mode = buff.substring(0, comma).toInt();
      msg.intensity = buff.substring(comma + 1).toInt();

      esp_now_send(broadcastAddress, (uint8_t*)&msg, sizeof(msg));
    }
  }
}
