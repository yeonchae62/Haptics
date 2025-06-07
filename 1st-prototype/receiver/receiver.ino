#include <esp_now.h>
#include <WiFi.h>

#define intDown 19
#define intUp 21
#define modeUp 23
#define modeDown 22
#define pulseLen 80

int currentMode = 1;
int currentInt = 0;

typedef struct struct_message {
  int mode;
  int intensity;
} struct_message;

void shortPulse(int pin) {
  digitalWrite(pin, HIGH);
  delay(pulseLen);
  digitalWrite(pin, LOW);
  delay(pulseLen);
}

void setMode(int hmode) {
  while (currentMode < hmode) {
    shortPulse(modeUp);
    currentMode++;
  }
  while (currentMode > hmode) {
    shortPulse(modeDown);
    currentMode--;
  }
  delay(pulseLen);
}

void setInt(int intensity) {
  while (currentInt < intensity) {
    shortPulse(intUp);
    currentInt++;
  }
  while (currentInt > intensity) {
    shortPulse(intDown);
    currentInt--;
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  struct_message msg;
  memcpy(&msg, incomingData, sizeof(msg));

  setMode(msg.mode);
  setInt(msg.intensity);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(modeUp, OUTPUT);
  pinMode(modeDown, OUTPUT);
  pinMode(intUp, OUTPUT);
  pinMode(intDown, OUTPUT);

  digitalWrite(modeUp, LOW);
  digitalWrite(modeDown, LOW);
  digitalWrite(intUp, LOW);
  digitalWrite(intDown, LOW);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed here
}
