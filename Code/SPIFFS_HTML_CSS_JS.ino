#include <WiFi.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "HIPAA";
const char* password = "123456789";

const uint8_t LED_Pin = 2;
boolean LED_Status;

AsyncWebServer server(80);
WebSocketsServer websocket(81);

IPAddress local_IP(192, 168, 137, 77);
IPAddress gateway(10, 32, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

#include "Web_Function.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_Pin, OUTPUT);
  digitalWrite(LED_Pin, LOW);
  
  WIFI_Init();
  Server_Init();
}

void loop() {
  websocket.loop();
}
