#include "HX711_ADC.h"

HX711_ADC LoadCell(5, 6); // DT - D5, SCK - D6

void setup() {
  LoadCell.begin();
  LoadCell.start(2000); // wait for stabilization
  LoadCell.setCalFactor(376.0); // TODO: adjust the calibration factor with a known weight

  Serial.begin(9600);
}

void loop() {
  LoadCell.update();
  float i = LoadCell.getData(); // weight in gram
  Serial.println(i);

  delay(2000);
}
