#include <Wire.h>
#include "DFRobot_AirQualitySensor.h"

DFRobot_AirQualitySensor particle(&Wire, 0x19);

int PM25v;

void PMS() {
  Wire.begin(13, 15);
  particle.begin();
}

void PML() {
  PM25v = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  // Serial.println("PM2.5 = " + String(PM25v));
}
