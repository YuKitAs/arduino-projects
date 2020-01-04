int liquid_level = 0;

void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT);
}

void loop() {
  liquid_level = digitalRead(5);
  if (liquid_level <= 0) {
    Serial.println(liquid_level);
  }
  
  delay(5000);
}
