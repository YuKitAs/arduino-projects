# arduino-projects

## Notes

* For Arduino sketches compiled by the Arduino IDE, the sketch folder name and the main `.ino` filename must match.

* I2C scanner:

  ```cpp
  void setup() {
    Serial.begin(115200);
    Wire.begin();

    for (byte addr = 1; addr < 127; addr++) {
      Wire.beginTransmission(addr);

      if (Wire.endTransmission() == 0) {
        Serial.print("Found device at 0x");
        Serial.println(addr, HEX);
      }
    }
  }
  ```

## Troubleshooting
### Avrdude stk500 not in sync

  **Board**: Arduino UNO (ATMEGA328P)

  **Issue**:

  Error message on upload after selecting correct board and port:
  ```
  serial port avrdude: stk500 disable: unknown response= 0x04 does not exist or your board is not connected
  ```

  **Possible cause**: digital pins 0 or 1 (used for uploading) or RESET are in use

  **Solution**: Disconnect the pins before upload
