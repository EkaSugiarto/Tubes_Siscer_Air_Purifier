#include <WiFiUdp.h>
#include <NTPClient.h>
#include <time.h>
#include <ESP32Time.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset = 25200;
const int daylightOffset = 3600;

WiFiUDP ntpUDP;
NTPClient waktu(ntpUDP, ntpServer, gmtOffset, daylightOffset);

ESP32Time rtc_esp(1);

void RTCS() {
  waktu.begin();
  waktu.update();

  while (waktu.getEpochTime() < 1710103401) RTCS();

  rtc_esp.setTime(waktu.getEpochTime());

  Serial.println("Setup RTC selesai!");
}

String GetDateTime() {
  String SM, SD;

  if (rtc_esp.getMonth() + 1 < 10) SM = "0" + String(rtc_esp.getMonth() + 1);
  else SM = String(rtc_esp.getMonth() + 1);

  if (rtc_esp.getDay() < 10) SD = "0" + String(rtc_esp.getDay());
  else SD = String(rtc_esp.getDay());

  return String(rtc_esp.getYear()) + "-" + SM + "-" + SD + " " + rtc_esp.getTime();
}

void RTCR() {
  if (rtc_esp.getHour() == 0 && rtc_esp.getSecond() < 5) ESP.restart();
}