#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>

#define DHT_PIN 26
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup(void) {
  Serial.begin(9600);

  Serial.println(F("Teste - DHT11"));

  dht.begin();
}

void loop(void) {

  delay(2000);

  float temperature = dht.readTemperature(), humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Falha ao ler dados do sensor."));
    return;
  }

  Serial.print(F("Temperatura: "));
  Serial.print(temperature);
  Serial.print(F("°C"));

  Serial.print(F(" | "));
  Serial.print(F("Umidade: "));
  Serial.print(humidity);
  Serial.print(F("%"));
}
