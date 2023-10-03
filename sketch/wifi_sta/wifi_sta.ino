#include "WiFi.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFiClient.h>
const char* ssid = "ESP32";
const char* password = "123456789";

WebServer server(80);

void handleRoot() {
  server.send(200, "application/json", readFromStation());
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("\n[*] Creating ESP32 STA");
  WiFi.begin(ssid, password);
  Serial.println("\n[*] Connecting to WiFi Network");
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
  Serial.print("\n[+] Connected to WiFi network with local IP : ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp32_sta")) {
        Serial.println("Error setting up MDNS responder!");
        delay(1000);
  }
  Serial.println("mDNS responder started");
  server.begin();
  server.on("/", handleRoot);
  MDNS.addService("http", "tcp", 80);
  Serial.println("TCP server with service started");
}

void loop()
{
  while(WiFi.status() == WL_CONNECTED)
  {
    server.handleClient();
    delay(2);
  }
  reconnect();
}

String readFromStation() {
  // Creating JSON Data
  StaticJsonDocument<512> doc;
  char output[512];

  // Header
  JsonObject header = doc.createNestedObject("header");
  header["device"] = "ESP32";
  header["mac"] = WiFi.macAddress();

  // Measurements
  unsigned long startTime = millis();
  updateMeasurementValues();
  unsigned long endTime = millis();
  JsonObject measurements = doc.createNestedObject("measurements");
  measurements["temp"] = random(0, 40);
  measurements["hum"] = random(30, 70);
  measurements["press"] = random(38, 42);
  measurements["gas"] = random(100, 500);
  
   // Operational
  JsonObject operational = doc.createNestedObject("operational");
  operational["rssi"] = WiFi.RSSI();
  operational["channel"] = WiFi.channel();
  operational["TxPower"] = WiFi.getTxPower();
  operational["mode"] = "WIFI_STA";
  operational["sensorRead"] = endTime - startTime;

  serializeJson(doc, output);
  Serial.println(output);
  return output;
}

void reconnect() {
  WiFi.disconnect();
  WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
  Serial.print("\n[+] Reconnected to WiFi network with local IP : ");
  Serial.println(WiFi.localIP());
}

void updateMeasurementValues() {
  Serial.println("Reading sensorvalues");
  delay(10);
}