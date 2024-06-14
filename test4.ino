#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

const char* ssid = "WISMA BERIMAN 3";
const char* password = "ALVIN0713";
const char* serverName = "http://192.168.1.220:2209";

#define DHTTYPE DHT11
#define DHT_PIN 27

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  delay(2000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  String jsonPayload = "{\"temperature\":";
  jsonPayload += temperature;
  jsonPayload += ",\"humidity\":";
  jsonPayload += humidity;
  jsonPayload += "}";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
   
