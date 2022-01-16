// Pulse counting routine.
void pulse_count() {
  if (burst_mode == true) {
    pulse_counter++;
    if (pulse_counter >= pulses) {
      tone1.noTone ();
      burst_mode = false;
    }
  }
}
