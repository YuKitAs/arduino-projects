#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_PIN = 18;             // GPIO 18, active LOW (INPUT_PULLUP)
const unsigned long DEBOUNCE_MS = 20;  // ignore raw state change (contact bounces) until stable for at least 20ms

static unsigned long lastTick = 0;  // last counter tick
unsigned long debounceStart;        // last raw state change, initialize in setup()

unsigned long count = 0;

bool backlightOn = true;

int lastRawBtnState = HIGH;  // raw GPIO read (HIGH = unpressed)
int stableBtnState = HIGH;   // debounced state (HIGH = unpressed)

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(count);

  debounceStart = millis();
}

void loop() {
  unsigned long now = millis();

  // button debounce
  int raw = digitalRead(BUTTON_PIN);
  if (raw != lastRawBtnState) {
    debounceStart = now;
    lastRawBtnState = raw;
  }

  if (now - debounceStart >= DEBOUNCE_MS && raw != stableBtnState) {
    stableBtnState = raw;

    // on button press
    if (stableBtnState == LOW) {
      backlightOn = !backlightOn;

      if (backlightOn) {
        lcd.backlight();
      } else {
        lcd.noBacklight();
      }
    }
  }

  if (now - lastTick >= 1000) {
    lastTick = now;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(++count);
  }
}
