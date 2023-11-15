#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFi.h>

#define DHT_PIN 26
#define DHT_TYPE DHT11

const char *SSID = "";     // Your WiFi SSID
const char *PASSWORD = ""; // Your WiFi Password

char buffer[512];

WebServer server(3490); // Creates a server in port 3490
DHT dht(DHT_PIN, DHT_TYPE);

// Function prototypes

void handleDataReading(void);
void addCustomHeaders(void);

void setup(void) {

  Serial.begin(9600);

  dht.begin();

  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/data",            // URL:
                                // http://YOUR_ESP-32_IP_ADDRESS/data
            handleDataReading); // When the user requests this URL, the
                                // function handleDataReading is called

  server.begin();
}

void loop(void) { server.handleClient(); }

void handleDataReading(void) {

  float temperature = dht.readTemperature();
  int humidity = dht.readHumidity();

  sprintf(buffer, "{ \"mcu_data\": {\"temperature\": %.2f, \"humidity\": %d}}",
          temperature, humidity);

  addCustomHeaders();

  server.send(200, "application/json; charset=utf-8", buffer);
}

void addCustomHeaders(void) {

  server.sendHeader("Access-Control-Allow-Methods", "GET");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Connection", "close");
}
