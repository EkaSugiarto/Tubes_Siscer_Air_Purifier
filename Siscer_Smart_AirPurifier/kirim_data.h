#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Cert.h"

void BLL() {
  WiFiClientSecure* client2 = new WiFiClientSecure;
  if (client2) {
    client2->setCACert(ca_cert);
    HTTPClient https;
    StaticJsonDocument<300> doc;
    String url, ESPData;

    Serial.println("[HTTPS] Mulai...");
    if (https.begin(*client2, "https://biru-langit.com/api/radons/data/create")) {

      doc["co2"] = String(map(mid_x, 50, 350, 20, 80));
      doc["pm25"] = String(PM25v);
      doc["sht31_temp"] = String(DHTT);
      doc["sht31_humid"] = String(DHTH);
      doc["geiger"] = String(fanSpeedValue);
      doc["phtd"] = String(heaterValue);
      doc["created_at"] = GetDateTime();
      doc["rssi"] = String(WiFi.RSSI());

      https.addHeader("Content-Type", "application/json");
      serializeJson(doc, ESPData);

      int httpCode = https.POST(ESPData);

      if (httpCode > 0)
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) Serial.println("[HTTPS] Data terkirim! Kode: " + String(httpCode) + "\n");
        else {
          Serial.println("[HTTPS] POST... gagal, error: " + String(httpCode) + "\n");
        }
      https.end();
    }
  }

  else {
    Serial.println("[HTTPS] Gagal menghubungkan\n");
  }
}