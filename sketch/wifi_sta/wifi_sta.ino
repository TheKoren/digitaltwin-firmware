#include "WiFi.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFiClient.h>

const char* ssid = "ESP32";
const char* password = "asdasd1234";

WebServer server(80);

typedef struct Control {
    int TVOC;
    long int ECO2;
    double UV;
    double LIGHT;
    double TEMP;
    double HUM;
    int PRESSURE;
    double SOUND;
    int EXEC;
}Control;

Control control;

void handleRoot() {
  server.send(200, "application/json", readFromStation());
}

void setup() {
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

  Serial2.begin(115200);
  delay(100);
}

void loop() {
  while(WiFi.status() == WL_CONNECTED)
  {
    server.handleClient();
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
  measurements["temp"] = control.TEMP;
  measurements["hum"] = control.HUM;
  measurements["press"] = control.PRESSURE;
  measurements["eco2"] = control.ECO2;
  measurements["tvoc"] = control.TVOC;
  measurements["light"] = control.LIGHT;
  measurements["uv"] = control.UV;
  measurements["sound"] = control.SOUND;
  
   // Operational
  JsonObject operational = doc.createNestedObject("operational");
  operational["rssi"] = WiFi.RSSI();
  operational["channel"] = WiFi.channel();
  operational["TxPower"] = WiFi.getTxPower();
  operational["mode"] = "WIFI_AP_STA";
  operational["sensorRead"] = endTime - startTime;
  operational["sensorExec"] = control.EXEC;

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
  Serial2.flush();
  while (true) {
    while (!(Serial2.available() > 0)) {
      delay(30);
      Serial.print(".");
    }
    char firstChar = Serial2.read();
    if (firstChar == '[') {
      break; // Exit the loop when '[' is received
    }
  }
  bool ending = false;
  char element;
  char buffer[10];
  while (ending == false) {
    for (int i = 0; i<9; i++) {
      int numBytes = Serial2.readBytesUntil(',', buffer, 10);
      buffer[numBytes] = '\0';
      switch(i) {
        case 0:
            control.HUM = atoi(buffer); break;
        case 1:
            control.TEMP = atoi(buffer); break;
        case 2:
            control.LIGHT = atoi(buffer); break;
        case 3:
            control.UV = atoi(buffer); break;
        case 4:
            control.PRESSURE = atoi(buffer); break;
        case 5:
            control.ECO2 = atoi(buffer); break;
        case 6:
            control.TVOC = atoi(buffer); break;
        case 7:
            control.SOUND = atoi(buffer); break;
        case 8:
            control.EXEC = atoi(buffer); break;
        default: break;
      }
    }
    ending = true;
  }
  Serial.println("Sensor read complete.");
}