#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h> // For set_mac

uint8_t myMac[] = { 0x24, 0x6F, 0x28, 0x11, 0x22, 0x33 };

void onDataRecv(const esp_now_recv_info_t *recvInfo, const uint8_t *incomingData, int len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           recvInfo->src_addr[0], recvInfo->src_addr[1], recvInfo->src_addr[2],
           recvInfo->src_addr[3], recvInfo->src_addr[4], recvInfo->src_addr[5]);

  Serial.print("Received from ");
  Serial.print(macStr);
  Serial.print(": ");
  Serial.write(incomingData, len);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, myMac);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);

  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("Receiver Ready");
}

void loop() {
  // passive wait
}

