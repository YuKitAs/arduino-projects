#include "HX711.h"

HX711 scale(5, 6); // DT - D5, SCK - D6

float calibration_factor = 50; // TODO: Modify the calibration factor
float units;

void setup() {
  Serial.begin(9600);

  scale.set_scale();
  scale.tare();  // Reset the scale to 0
}

void loop() {
  scale.set_scale(calibration_factor);

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0) {
    units = 0.00;
  }
  Serial.print(units);
  Serial.print(" grams");
  Serial.print(" | Calibration factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  // Press '+'/'-' to increase/descrease the calibration factor until the reading value matches a known weight
  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == '+') {
      calibration_factor += 1;
    } else if (temp == '-') {
      calibration_factor -= 1;
    }
  }

  scale.power_down();
  delay(1000);
  scale.power_up();
}
