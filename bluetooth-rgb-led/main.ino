const int redPin = 10; // D10
const int greenPin = 9; // D9
const int bluePin = 8; // D8

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char color = Serial.read();

    switch(color) {
      case 'r':
        analogWrite(redPin, 255);
        Serial.println("RED");
        break;
      case 'g':
        analogWrite(greenPin, 255);
        Serial.println("GREEN");
        break;
      case 'b':
        analogWrite(bluePin, 255);
        Serial.println("BLUE");
        break;
      default:
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
        break;
    }
  }
}
