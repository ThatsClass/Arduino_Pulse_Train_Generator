#include <TonePlayer.h>

TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);  // pin D9 (Uno).

const byte char_length = 32;
char received_chars[char_length];
char * command = NULL;
volatile uint32_t pulse_counter = 0;
volatile uint32_t trigger_time_ms = 0;
volatile uint32_t trigger_check_ms = 0;
const uint8_t interrupt_pin = 2;
const uint8_t trigger_pin = 3;
const uint16_t trigger_period_ms = 400;
const uint8_t debounce_time_ms = 100;
uint16_t pulses = 0;
uint16_t frequency_Hz = 0;
uint8_t mode = 0; // 0 = idle, 1 = busrt, 2 = continuous, 3 = stop.

boolean new_command = false;
volatile boolean burst_mode = false;
volatile boolean trigger_ready = true;
volatile boolean trigger_check = false;

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), pulse_count, FALLING);
  pinMode(trigger_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(trigger_pin), trigger_pulse, FALLING);
  pinMode (9, OUTPUT);  // output pin is fixed (OC1A)
  Serial.print("Open\n");
}

void loop() {
  check_serial_port();
  run_new_command();

  if (trigger_check == true) {
    if (millis() - trigger_check_ms >= debounce_time_ms) {
      if (digitalRead(trigger_pin) == LOW) {
        trigger_ready = false;
        trigger_time_ms = millis();
        pulses = 1;
        pulse_counter = 0;
        burst_mode = true;
        trigger_check = false;
        tone1.tone (1000);
      }
      else
      {
        trigger_check = false;
      }
    }
  }

  if (trigger_ready == false) {
    if (millis() - trigger_time_ms >= trigger_period_ms) {
      trigger_ready =  true;
    }
  }
}
