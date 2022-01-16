void run_new_command() {
  if (new_command == true) {
    new_command = false;
    if (mode == 1) { //1 = busrt.
      pulse_counter = 0;
      burst_mode = true;
      tone1.tone (frequency_Hz);
    }
    if (mode == 2) { // 2 = continuous.
      tone1.tone (frequency_Hz);
    }
    if (mode == 3) { // 3 = stop.
      tone1.noTone ();
      burst_mode = false;
    }
  }
}
