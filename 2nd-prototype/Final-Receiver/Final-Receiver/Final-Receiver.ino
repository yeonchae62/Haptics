#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

uint8_t myMac[] = { 0x24, 0x6F, 0x28, 0x11, 0x22, 0x33 };

typedef struct _message {
  int tMode;
  int tIntensity;
} _message;

_message inData;

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len == sizeof(_message)) {
    memcpy(&inData, data, sizeof(inData));
    Serial.print("Received mode: ");
    Serial.print(inData.tMode);
    Serial.print(", intensity: ");
    Serial.println(inData.tIntensity);
  } else {
    Serial.println("Received data length mismatch");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, myMac);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  Serial.println("Receiver Ready");
}

void loop() {
  // Passive wait
}
