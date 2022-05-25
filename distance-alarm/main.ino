const int echoPin = 5; // D5
const int trigPin = 6; // D6
const int buzzPin = 7; // D7

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // clear trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // trigger and wait for 10 µs
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // distance in cm
  distance = (duration * 0.034) / 2;
  if (distance < 5) {
    // generates a square wave of frequency 1000Hz, duration 200ms
    tone(buzzPin, 1000, 200);
  }

  delay(1000);
}
