void WIFI_Init() {
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    Serial.println("STA Failed to configure.");
  else Serial.println("STA Succeeded to config.");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type)
  {
    case WStype_DISCONNECTED: Serial.printf("[%u] Disconnected!\n", num); break;
    case WStype_CONNECTED: {
        IPAddress ip = websocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        if (LED_Status)websocket.sendTXT(num, "LED ON");
        else websocket.sendTXT(num, "LED OFF");
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[%u] get Text: %s\n", num, payload);
        String message = String((char*)( payload));
        if (message == "LED ON") {
          digitalWrite(LED_Pin, HIGH);
          LED_Status = true;
        }
        else {
          digitalWrite(LED_Pin, LOW);
          LED_Status = false;
        }
        websocket.broadcastTXT(message);
      }
      break;
  }
}

void Server_Init() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon.png", "image/png");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/index.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.js", "text/js");
  });

  server.onNotFound(notFound);
  server.begin();
  websocket.begin();
  websocket.onEvent(webSocketEvent);
}
