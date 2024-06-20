#include "aktuator.h"
#include "sensor_pm25.h"
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "camera_config.h"
#include "web_visualisasi.h"
#include "NTPnya.h"
#include "dhtnya.h"
#include "fuzzynya.h"
#include "lcdnya.h"
#include "kirim_data.h"

// Set the interval2 for 5 seconds (5000 milliseconds)
const unsigned long interval2 = 10000;

// Variable to store the last time the message was printed
unsigned long previousMillis2 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Mulai setup");
  
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  CameraS();
  AktuatorS();
  LCDSS();
  DHTS();
  PMS();
  FuzzyS();
  ServerS();
  RTCS();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    LCDLL();
    ServerS();
  }

  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2) {
    Serve();
    previousMillis2 = currentMillis2;
    PML();
    DHTL();
    FuzzyL();
    LCDL();
    PemanasL();
    KipasL();
    Serve();
    BLL();
    Serve();
  }

  RTCR();
  Serve();
}
