#include <Arduino.h>

const int pwmPin = 3;        // Output pin for PWM
const int pwmFreq = 22222;   // Approx 45 µs period = 22.2 kHz
const int pwmResolution = 8; // 8-bit resolution (0–255)

const int maxIntensity = 30;

// Lookup table: PWM values for intensities 1–15 and 30
uint8_t pwmTable[31] = {
  0,    // index 0 unused
  2, 3, 5, 8, 11, 16, 20, 27, 33, 40, 47, 54, 59, 65, 73, // 1-15
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               // 16-29
  187 // 30
};

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  delay(5000);

  // Setup PWM on pwmPin
  if (!ledcAttach(pwmPin, pwmFreq, pwmResolution)) {
    Serial.println("Failed to configure PWM");
    while (1); // Halt execution
  }

}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int intensity = input.toInt();

    if (intensity >= 0 && intensity <= maxIntensity) {
      uint8_t pwmValue = pwmTable[intensity];
      if (!ledcWrite(pwmPin, pwmValue)) {
        Serial.println("Failed to set PWM duty cycle");
      } 
      else {
        Serial.print("Intensity: ");
        Serial.print(intensity);
        Serial.print(" => PWM: ");
        Serial.println(pwmValue);
      }
    } else {
      Serial.println("Invalid intensity! Enter value between 1 and 30.");
    }
  }
}
