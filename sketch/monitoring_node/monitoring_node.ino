#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* serverAddress = "http://192.168.0.100:8080/data";
WiFiClient wifiClient;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin("Koren", "hotqm1asd");  // Replace with your WiFi credentials
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
}

void loop() {
  createJson();
  delay(30000);
}

void createJson() {
  DynamicJsonDocument doc(1800);
  char output[1800];

  JsonObject header = doc.createNestedObject("header");

  // Create the "header" part
  header["device"] = "ESP8266";
  header["mode"] = "monitor";
  header["mac"] = WiFi.macAddress();

  // Create the "networks" array
  JsonArray networks = doc.createNestedArray("networks");

  int scanResult = WiFi.scanNetworks(false, true);

  if (scanResult > 0) {
    for (int i = 0; i < scanResult; i++) {
      String ssid;
      int32_t rssi;
      uint8_t encryptionType;
      uint8_t *bssid;
      int32_t channel;
      bool hidden;
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);

      // Check if SSID is not empty before adding it to the "networks" array
      if (!ssid.isEmpty()) {
        JsonObject network = networks.createNestedObject();
        network["SSID"] = ssid;
        network["RSSI"] = rssi;
        network["Channel"] = channel;
      }
    }
  }

  serializeJson(doc, output);
  Serial.println(output);
  sendPostRequest(output);
}


void sendPostRequest(const String& data) {
  http.begin(wifiClient, serverAddress);
  http.addHeader("Content-Type", "application/json");
  http.POST(data);
  http.end();
  return;
}
