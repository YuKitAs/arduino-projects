#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int dustPin = 0; // Arduino A0 pin
int ledPower = 2; // LED driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setupLcd() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Dust den:");
}

void setup()
{
  setupLcd();
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
}

void loop()
{ 
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(dustPin); // read raw voltage

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  calcVoltage = voMeasured * (5.0 / 1024.0);
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  dustDensity = 0.17 * calcVoltage - 0.1;
  
  lcd.setCursor(10,0);
  lcd.print(dustDensity); // mg*m^(-3)
  Serial.println(dustDensity, 3);

  lcd.setCursor(0,1);
  if (dustDensity <= 0.035) {
    lcd.print("   EXCELLENT    ");
  } else if (dustDensity > 0.035 && dustDensity <= 0.075) {
    lcd.print("      GOOD      ");
  } else if (dustDensity > 0.075 && dustDensity <= 0.115) {
    lcd.print("    MODERATE    ");
  } else if (dustDensity > 0.115 && dustDensity <= 0.15) {
    lcd.print("      POOR      ");
  } else if (dustDensity > 0.15 && dustDensity <= 0.25) {
    lcd.print("   VERY POOR    ");
  } else if (dustDensity > 0.25) {
    lcd.print("    SERIOUS     "); 
  }

  delay(1000);
}
