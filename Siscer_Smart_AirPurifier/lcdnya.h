#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C elsidi(0x27, 20, 4);

void LCDS() {
  Wire.begin(13, 15);
  elsidi.begin(20, 4);
  elsidi.init();
  elsidi.backlight();
  Serial.println("LCD setup selesai!");
  delay(1000);
  elsidi.clear();
  elsidi.setCursor(0, 0);
  elsidi.print("Menghubungkan");
  elsidi.setCursor(0, 1);
  elsidi.print("ke WiFi");
  elsidi.setCursor(0, 2);
  elsidi.print(WIFI_SSID);
}

void LCDSS() {
  elsidi.clear();
  elsidi.setCursor(0, 0);
  elsidi.print("Terhubung");
  elsidi.setCursor(0, 1);
  elsidi.print("ke WiFi");
  elsidi.setCursor(0, 2);
  elsidi.print(WIFI_SSID);
  delay(1000);
}

void LCDLL() {
  elsidi.clear();
  elsidi.setCursor(0, 0);
  elsidi.print("Terputus");
  elsidi.setCursor(0, 1);
  elsidi.print("ke WiFi");
  elsidi.setCursor(0, 2);
  elsidi.print(WIFI_SSID);
  delay(1000);
}

void LCDL() {
  elsidi.clear();
  elsidi.setCursor(0, 0);
  elsidi.print("Suhu   = " + String(DHTT) + " C");
  elsidi.setCursor(0, 1);
  elsidi.print("Kelemb = " + String(DHTH) + "%");
  elsidi.setCursor(0, 2);
  elsidi.print("PM2.5  = " + String(PM25v) + " ug/m^3");
  elsidi.setCursor(0, 3);
  elsidi.print(String(fanSpeedValue) + " | " + String(heaterValue));
}