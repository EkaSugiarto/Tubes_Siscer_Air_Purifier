#include <Fuzzy.h>

// Create an instance of Fuzzy
Fuzzy *fuzzy = new Fuzzy();

// Create fuzzy sets and rules
void FuzzyS() {
  // Fuzzy Input for Temperature
  FuzzySet *cold = new FuzzySet(0, 0, 20, 25);
  FuzzySet *normal = new FuzzySet(20, 25, 25, 30);
  FuzzySet *hot = new FuzzySet(25, 30, 40, 40);
  FuzzyInput *temperature = new FuzzyInput(1);

  temperature->addFuzzySet(cold);
  temperature->addFuzzySet(normal);
  temperature->addFuzzySet(hot);
  fuzzy->addFuzzyInput(temperature);

  // Fuzzy Input for Humidity
  FuzzySet *dry = new FuzzySet(0, 0, 40, 50);
  FuzzySet *normalHumidity = new FuzzySet(40, 50, 50, 60);
  FuzzySet *humid = new FuzzySet(50, 60, 100, 100);
  FuzzyInput *humidity = new FuzzyInput(2);

  humidity->addFuzzySet(dry);
  humidity->addFuzzySet(normalHumidity);
  humidity->addFuzzySet(humid);
  fuzzy->addFuzzyInput(humidity);

  // Fuzzy Input for PM2.5
  FuzzySet *good = new FuzzySet(0, 0, 50, 100);
  FuzzySet *moderate = new FuzzySet(50, 100, 100, 150);
  FuzzySet *bad = new FuzzySet(100, 150, 200, 200);
  FuzzyInput *pm25 = new FuzzyInput(3);

  pm25->addFuzzySet(good);
  pm25->addFuzzySet(moderate);
  pm25->addFuzzySet(bad);
  fuzzy->addFuzzyInput(pm25);

  // Fuzzy Output for Fan Speed
  FuzzySet *low = new FuzzySet(0, 0, 50, 100);
  FuzzySet *medium = new FuzzySet(50, 100, 100, 150);
  FuzzySet *high = new FuzzySet(100, 150, 255, 255);
  FuzzyOutput *fanSpeed = new FuzzyOutput(1);

  fanSpeed->addFuzzySet(low);
  fanSpeed->addFuzzySet(medium);
  fanSpeed->addFuzzySet(high);
  fuzzy->addFuzzyOutput(fanSpeed);

  // Fuzzy Output for Heater
  FuzzySet *off = new FuzzySet(0, 0, 40, 50);
  FuzzySet *lowHeat = new FuzzySet(40, 50, 50, 60);
  FuzzySet *highHeat = new FuzzySet(50, 60, 100, 100);
  FuzzyOutput *heater = new FuzzyOutput(2);

  heater->addFuzzySet(off);
  heater->addFuzzySet(lowHeat);
  heater->addFuzzySet(highHeat);
  fuzzy->addFuzzyOutput(heater);

  // Initialize Fuzzy Rule Antecedents (Input Fuzzy)
  FuzzyRuleAntecedent *coldDry = new FuzzyRuleAntecedent();
  coldDry->joinWithAND(cold, dry);
  FuzzyRuleAntecedent *coldDryGood = new FuzzyRuleAntecedent();
  coldDryGood->joinWithAND(coldDry, good);
  FuzzyRuleAntecedent *coldDryModerate = new FuzzyRuleAntecedent();
  coldDryModerate->joinWithAND(coldDry, moderate);
  FuzzyRuleAntecedent *coldDryBad = new FuzzyRuleAntecedent();
  coldDryBad->joinWithAND(coldDry, bad);

  FuzzyRuleAntecedent *coldNormal = new FuzzyRuleAntecedent();
  coldNormal->joinWithAND(cold, normalHumidity);
  FuzzyRuleAntecedent *coldNormalGood = new FuzzyRuleAntecedent();
  coldNormalGood->joinWithAND(coldNormal, good);
  FuzzyRuleAntecedent *coldNormalModerate = new FuzzyRuleAntecedent();
  coldNormalModerate->joinWithAND(coldNormal, moderate);
  FuzzyRuleAntecedent *coldNormalBad = new FuzzyRuleAntecedent();
  coldNormalBad->joinWithAND(coldNormal, bad);

  FuzzyRuleAntecedent *coldHumid = new FuzzyRuleAntecedent();
  coldHumid->joinWithAND(cold, humid);
  FuzzyRuleAntecedent *coldHumidGood = new FuzzyRuleAntecedent();
  coldHumidGood->joinWithAND(coldHumid, good);
  FuzzyRuleAntecedent *coldHumidModerate = new FuzzyRuleAntecedent();
  coldHumidModerate->joinWithAND(coldHumid, moderate);
  FuzzyRuleAntecedent *coldHumidBad = new FuzzyRuleAntecedent();
  coldHumidBad->joinWithAND(coldHumid, bad);

  FuzzyRuleAntecedent *normalDry = new FuzzyRuleAntecedent();
  normalDry->joinWithAND(normal, dry);
  FuzzyRuleAntecedent *normalDryGood = new FuzzyRuleAntecedent();
  normalDryGood->joinWithAND(normalDry, good);
  FuzzyRuleAntecedent *normalDryModerate = new FuzzyRuleAntecedent();
  normalDryModerate->joinWithAND(normalDry, moderate);
  FuzzyRuleAntecedent *normalDryBad = new FuzzyRuleAntecedent();
  normalDryBad->joinWithAND(normalDry, bad);

  FuzzyRuleAntecedent *normalNormal = new FuzzyRuleAntecedent();
  normalNormal->joinWithAND(normal, normalHumidity);
  FuzzyRuleAntecedent *normalNormalGood = new FuzzyRuleAntecedent();
  normalNormalGood->joinWithAND(normalNormal, good);
  FuzzyRuleAntecedent *normalNormalModerate = new FuzzyRuleAntecedent();
  normalNormalModerate->joinWithAND(normalNormal, moderate);
  FuzzyRuleAntecedent *normalNormalBad = new FuzzyRuleAntecedent();
  normalNormalBad->joinWithAND(normalNormal, bad);

  FuzzyRuleAntecedent *normalHumid = new FuzzyRuleAntecedent();
  normalHumid->joinWithAND(normal, humid);
  FuzzyRuleAntecedent *normalHumidGood = new FuzzyRuleAntecedent();
  normalHumidGood->joinWithAND(normalHumid, good);
  FuzzyRuleAntecedent *normalHumidModerate = new FuzzyRuleAntecedent();
  normalHumidModerate->joinWithAND(normalHumid, moderate);
  FuzzyRuleAntecedent *normalHumidBad = new FuzzyRuleAntecedent();
  normalHumidBad->joinWithAND(normalHumid, bad);

  FuzzyRuleAntecedent *hotDry = new FuzzyRuleAntecedent();
  hotDry->joinWithAND(hot, dry);
  FuzzyRuleAntecedent *hotDryGood = new FuzzyRuleAntecedent();
  hotDryGood->joinWithAND(hotDry, good);
  FuzzyRuleAntecedent *hotDryModerate = new FuzzyRuleAntecedent();
  hotDryModerate->joinWithAND(hotDry, moderate);
  FuzzyRuleAntecedent *hotDryBad = new FuzzyRuleAntecedent();
  hotDryBad->joinWithAND(hotDry, bad);

  FuzzyRuleAntecedent *hotNormal = new FuzzyRuleAntecedent();
  hotNormal->joinWithAND(hot, normalHumidity);
  FuzzyRuleAntecedent *hotNormalGood = new FuzzyRuleAntecedent();
  hotNormalGood->joinWithAND(hotNormal, good);
  FuzzyRuleAntecedent *hotNormalModerate = new FuzzyRuleAntecedent();
  hotNormalModerate->joinWithAND(hotNormal, moderate);
  FuzzyRuleAntecedent *hotNormalBad = new FuzzyRuleAntecedent();
  hotNormalBad->joinWithAND(hotNormal, bad);

  FuzzyRuleAntecedent *hotHumid = new FuzzyRuleAntecedent();
  hotHumid->joinWithAND(hot, humid);
  FuzzyRuleAntecedent *hotHumidGood = new FuzzyRuleAntecedent();
  hotHumidGood->joinWithAND(hotHumid, good);
  FuzzyRuleAntecedent *hotHumidModerate = new FuzzyRuleAntecedent();
  hotHumidModerate->joinWithAND(hotHumid, moderate);
  FuzzyRuleAntecedent *hotHumidBad = new FuzzyRuleAntecedent();
  hotHumidBad->joinWithAND(hotHumid, bad);

  // Initialize Fuzzy Rule Consequents (Output Fuzzy)
  FuzzyRuleConsequent *thenLowOff = new FuzzyRuleConsequent();
  thenLowOff->addOutput(low);
  thenLowOff->addOutput(off);

  FuzzyRuleConsequent *thenLowLowHeat = new FuzzyRuleConsequent();
  thenLowLowHeat->addOutput(low);
  thenLowLowHeat->addOutput(lowHeat);

  FuzzyRuleConsequent *thenLowHighHeat = new FuzzyRuleConsequent();
  thenLowHighHeat->addOutput(low);
  thenLowHighHeat->addOutput(highHeat);

  FuzzyRuleConsequent *thenMediumOff = new FuzzyRuleConsequent();
  thenMediumOff->addOutput(medium);
  thenMediumOff->addOutput(off);

  FuzzyRuleConsequent *thenMediumLowHeat = new FuzzyRuleConsequent();
  thenMediumLowHeat->addOutput(medium);
  thenMediumLowHeat->addOutput(lowHeat);

  FuzzyRuleConsequent *thenMediumHighHeat = new FuzzyRuleConsequent();
  thenMediumHighHeat->addOutput(medium);
  thenMediumHighHeat->addOutput(highHeat);

  FuzzyRuleConsequent *thenHighOff = new FuzzyRuleConsequent();
  thenHighOff->addOutput(high);
  thenHighOff->addOutput(off);

  FuzzyRuleConsequent *thenHighLowHeat = new FuzzyRuleConsequent();
  thenHighLowHeat->addOutput(high);
  thenHighLowHeat->addOutput(lowHeat);

  FuzzyRuleConsequent *thenHighHighHeat = new FuzzyRuleConsequent();
  thenHighHighHeat->addOutput(high);
  thenHighHighHeat->addOutput(highHeat);

  // Add Fuzzy Rules
  fuzzy->addFuzzyRule(new FuzzyRule(1, coldDryGood, thenLowOff));
  fuzzy->addFuzzyRule(new FuzzyRule(2, coldDryModerate, thenLowLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(3, coldDryBad, thenMediumLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(4, coldNormalGood, thenLowOff));
  fuzzy->addFuzzyRule(new FuzzyRule(5, coldNormalModerate, thenMediumLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(6, coldNormalBad, thenMediumHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(7, coldHumidGood, thenMediumOff));
  fuzzy->addFuzzyRule(new FuzzyRule(8, coldHumidModerate, thenMediumHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(9, coldHumidBad, thenHighHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(10, normalDryGood, thenLowOff));
  fuzzy->addFuzzyRule(new FuzzyRule(11, normalDryModerate, thenLowLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(12, normalDryBad, thenMediumLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(13, normalNormalGood, thenLowOff));
  fuzzy->addFuzzyRule(new FuzzyRule(14, normalNormalModerate, thenMediumLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(15, normalNormalBad, thenMediumHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(16, normalHumidGood, thenMediumOff));
  fuzzy->addFuzzyRule(new FuzzyRule(17, normalHumidModerate, thenMediumHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(18, normalHumidBad, thenHighHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(19, hotDryGood, thenMediumOff));
  fuzzy->addFuzzyRule(new FuzzyRule(20, hotDryModerate, thenMediumLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(21, hotDryBad, thenHighLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(22, hotNormalGood, thenMediumOff));
  fuzzy->addFuzzyRule(new FuzzyRule(23, hotNormalModerate, thenHighLowHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(24, hotNormalBad, thenHighHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(25, hotHumidGood, thenHighOff));
  fuzzy->addFuzzyRule(new FuzzyRule(26, hotHumidModerate, thenHighHighHeat));
  fuzzy->addFuzzyRule(new FuzzyRule(27, hotHumidBad, thenHighHighHeat));
}

// Main loop
void FuzzyL() {
  // Example input values
  fuzzy->setInput(1, DHTT);   // Temperature input
  fuzzy->setInput(2, DHTH);   // Humidity input
  fuzzy->setInput(3, PM25v);  // PM2.5 input

  // Fuzzify inputs
  fuzzy->fuzzify();

  // Get and print output values
  fanSpeedValue = fuzzy->defuzzify(1);
  heaterValue = fuzzy->defuzzify(2);

  Serial.println("Suhu       = " + String(DHTT));
  Serial.println("Kelembapan = " + String(DHTH));
  Serial.println("PM2.5      = " + String(PM25v));
  Serial.println("Servo      = " + String(map(mid_x, 50, 350, 20, 80)));
  Serial.println("Fan Speed  = " + String(fanSpeedValue));
  Serial.println("Heater     = " + String(heaterValue));

  delay(1000);
}
