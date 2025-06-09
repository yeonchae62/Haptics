#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> // For setting MAC address

// Receiver MAC address
uint8_t receiverMac[] = { 0x24, 0x6F, 0x28, 0x11, 0x22, 0x33 };

// Sender MAC address
uint8_t senderMac[] = { 0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC };

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, senderMac);  

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Sender Ready");
}

void loop() {
  const char* msg = "Hello from Sender";
  esp_err_t result = esp_now_send(receiverMac, (uint8_t*)msg, strlen(msg));

  if (result == ESP_OK) {
    Serial.println("Sent successfully");
  } else {
    Serial.printf("Send error: %d\n", result);
  }

  delay(1000);
}
