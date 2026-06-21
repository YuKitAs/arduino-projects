# arduino-projects

For Arduino sketches compiled by the Arduino IDE, the sketch folder name and the main `.ino` filename must match.

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
