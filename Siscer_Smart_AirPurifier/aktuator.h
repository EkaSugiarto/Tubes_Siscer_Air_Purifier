#include "esp32-hal-ledc.h"
#include "esp32-hal-gpio.h"
#include <Servo.h>

#define pinKipas 12
#define pinHeater 4

Servo asli1;

int mid_x;

int iii;

int PWMf = 5000, PWMr = 8;

float fanSpeedValue, heaterValue;

void AktuatorS() {
  pinMode(pinKipas, OUTPUT);
  pinMode(pinHeater, OUTPUT);

  digitalWrite(pinKipas, LOW);
  digitalWrite(pinHeater, LOW);

  asli1.attach(14, 4);

  ledcSetup(3, PWMf, PWMr);
  ledcSetup(2, PWMf, PWMr);

  ledcAttachPin(pinKipas, 3);
  ledcAttachPin(pinHeater, 2);

  Serial.println("Setup aktuator selesai!");
  delay(1000);
}

void PenggerakL() {
  asli1.write(map(mid_x, 50, 350, 20, 80));
}

void PemanasL() {
  ledcWrite(2, map(heaterValue, 0, 100, 0, 255));
}

void KipasL() {
  ledcWrite(3, fanSpeedValue);
}