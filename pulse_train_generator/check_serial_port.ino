void check_serial_port() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && new_command == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        received_chars[ndx] = rc;
        ndx++;
        if (ndx >= char_length) {
          ndx = char_length - 1;
        }
      }
      else {
        received_chars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        new_command = true;

        command = strtok(received_chars, ",");
        pulses = String(command).toInt();
        command = strtok(NULL, ",");
        frequency_Hz = String(command).toInt();
        command = strtok(NULL, ",");
        mode = String(command).toInt();
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}
