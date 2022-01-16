// Pulse trigger routine.
void trigger_pulse() {
  if (trigger_ready ==  true)
  {
    trigger_check = true;
    trigger_check_ms = millis();
  }
}
