#include "esp32-hal.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "esp_timer.h"
#include "Arduino.h"
#include "face_detection.h"

#define WIFI_SSID "AE_IoT2"
#define WIFI_PASSWORD "BuatAlatAja"

// Server settings
WiFiServer server(80);

void LCDS();

bool pernah = false;

void ServerS() {
  LCDS();
  Serial.print("Connecting to WiFi SSID ");
  WiFi.hostname("Eka-Laila-Sefani");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Setup server selesai!");
  delay(1000);
}

void AksaraJawa1() {
  client1.println("HTTP/1.1 200 OK");
  client1.println("Content-type:text/html");
  client1.println();
  client1.print(
    "<style>"
    "body {"
    "  margin: 0;"
    "  display: flex;"
    "  justify-content: center;"
    "  align-items: center;"
    "  height: 100vh;"
    "  background-color: #000;"
    "}"
    "img {"
    "  height: 100%;"
    "  max-width: 100%;"
    "  max-height: 100%;"
    "}"
    "</style>"
    "<img id='cameraImage' src='/stream'>"
    "<script>"
    "function updateImage() {"
    "  var img = document.getElementById('cameraImage');"
    "  img.src = '/stream?' + new Date().getTime();"
    "}"
    "setInterval(updateImage, 1000);"  // Update every second
    "</script>");
  client1.println();
}

void AksaraJawa2() {
  client1.println("HTTP/1.1 200 OK");
  client1.println("Content-type:text/html");
  client1.println();
  client1.print(
    "<style>"
    "body {"
    "  margin: 0;"
    "  display: flex;"
    "  justify-content: center;"
    "  align-items: center;"
    "  height: 100vh;"
    "  background-color: #000;"
    "}"
    "img {"
    "  height: 100%;"
    "  max-width: 100%;"
    "  max-height: 100%;"
    "}"
    "</style>"
    "<img id='cameraImage' src='/stream'>"
    "<script>"
    "function updateImage() {"
    "  var img = document.getElementById('cameraImage');"
    "  img.src = '/capture?' + new Date().getTime();"
    "}"
    "</script>");
  client1.println();
}

void Serve() {
  WiFiClient client = server.available();
  client1 = client;
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            AksaraJawa1();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /stream")) {
          Serial.println("Client connected");
          TrackMukaWeb();
        }

        if (currentLine.endsWith("GET /capture")) {
          Serial.println("Client connected");
          AksaraJawa2();
          pernah = true;
          break;
        }
      }
    }
  }
  client.stop();
  // Serial.println("Client disconnected");

  // if (pernah == false) TrackMuka();
  pernah = false;
}
