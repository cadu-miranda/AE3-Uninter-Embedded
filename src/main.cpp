#include <Arduino.h>

#define LED_PIN 2

void setup(void) { pinMode(LED_PIN, OUTPUT); }

void loop(void) {

  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
