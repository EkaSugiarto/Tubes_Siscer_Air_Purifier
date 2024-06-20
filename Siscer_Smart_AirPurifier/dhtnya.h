#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

float DHTT;
int DHTH;

void DHTS() {
  dht.begin();
}

void DHTL() {
  DHTT = dht.readTemperature();
  DHTH = dht.readHumidity();
}