#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <esp_wifi.h>
#include <lwip\opt.h>
#include <ESPmDNS.h>

const char* wifi_network_ssid = "Koren";
const char* wifi_network_password = "hotqm1asd";

const char* soft_ap_ssid = "ESP32";
const char* soft_ap_password = "123456789";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  Serial.println("\n[*] Creating ESP32 APSTA");
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  Serial.println("\n[*] Connecting to WiFi Network");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print("\n[+] Connected to WiFi network with local IP : ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp32_AP")) {
    Serial.println("Error setting up MDNS responder!");
    delay(100);
  }

  Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (WiFi.status() == WL_CONNECTED) {
    pollNodes("http", "tcp");
    delay(5000);
    bool ending = false;
    if (Serial2.available()) {
      if ((char)Serial2.read() == '[') {
        while (ending == false) {
          char element = (char)Serial2.read();
          if (element == ']') {
            ending = true;
          } else {
            Serial.print(element);
          }
        }
        Serial.println();
      }
    }
  }
  reconnect();
}

void pollNodes(const char* service, const char* proto) {
  Serial.printf("Browsing for service _%s._%s.local. ... ", service, proto);
  int n = MDNS.queryService(service, proto);
  if (n == 0) {
    //Serial.println("no services found");
  } else {
    Serial.print(n);
    //Serial.println(" service(s) found");
    for (int i = 0; i < n; ++i) {
      // Print details for each service found
      //Serial.print("  ");
      //Serial.print(i + 1);
      //Serial.print(": ");
      //Serial.print(MDNS.hostname(i));
      //Serial.print(" (");
      //Serial.print(MDNS.IP(i));
      // Serial.print(":");
      //Serial.print(MDNS.port(i));
      //Serial.println(")");
    }
    String ip = String(MDNS.IP(0)[0]) + String(".") + String(MDNS.IP(0)[1]) + String(".") + String(MDNS.IP(0)[2]) + String(".") + String(MDNS.IP(0)[3]) + String(":") + String(MDNS.port(0));
    String data = requestData(ip);
    if (data != "") {
      sendData(data);
    }
  }
  String dataAP = readFromAP();
  sendData(dataAP);
}

String getMacAddress(uint8_t macAddr[6]) {
  String macAddress;
  for (int i = 0; i < 6; i++) {
    if (macAddr[i] < 0x10) {
      macAddress += "0";
    }
    macAddress += String(macAddr[i], HEX);
    if (i < 5) {
      macAddress += ":";
    }
  }
  return macAddress;
}

String requestData(String ip) {
  WiFiClient client;
  HTTPClient http;

  String url = "http://";
  url += ip;
  url += "/";

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    String response = http.getString();
    http.end();
    //Serial.println(response);
    return response;
  } else {
    //Serial.print("Error on HTTP request: ");
    //Serial.println(httpResponseCode);
    http.end();
    return "";
  }
}

String readFromAP() {
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
  JsonArray addressList = operational.createNestedArray("addressList");
  operational["rssi"] = WiFi.RSSI();
  operational["channel"] = WiFi.channel();
  operational["TxPower"] = WiFi.getTxPower();
  operational["mode"] = "WIFI_AP_STA";
  operational["sensorRead"] = endTime - startTime;

  /*
  Not used: 
  //wifiValues["snr"] = WiFi.RSSI()-WiFi.noise();
  //wifiValues["speed"] = WiFi.getSpeedMbps();
  //wifiValues["packetloss"] = WiFi.packetLoss();
  */

  wifi_sta_list_t stationList;
  memset(&stationList, 0, sizeof(stationList));
  esp_wifi_ap_get_sta_list(&stationList);

  for (int i = 0; i < WiFi.softAPgetStationNum(); i++) {
    addressList.add(getMacAddress(stationList.sta[i].mac));
  }

  serializeJson(doc, output);
  //Serial.println(output);
  return output;
}

void sendData(String data) {
  WiFiClient client;
  HTTPClient http;
  String url = "http://192.168.0.100:8080/data";

  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    String response = http.getString();
    //Serial.println(response);
  } else {
    //Serial.print("Error on HTTP request: ");
    //Serial.println(httpResponseCode);
  }
  http.end();
}

void reconnect() {
  WiFi.disconnect();
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  while (WiFi.status() != WL_CONNECTED) {
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