#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "digital_in.h"
#include "digital_out.h"
#include "encoder.h"
#include "drive.h"
#include "P_controller.h"

Encoder motor(D2,D4,D7); // encoder driver, (encoder in 1, encoder in 2, signal read out)
Drive bridge(0,D8); // motor driver, (timer circuit no., slp pin)

ISR(INT0_vect) {  // D2 interrupt, INT0 activated by digital_in through encoder class
  motor.update(); // reads position and timestamps on encoder in pin interrupt
}

int main() {
  time_init(); // initalize timer 1 for time tracking use
  motor.init();  // initalize encoder
  bridge.init();  // initalize motor driver
  set_loop_ms(5,20); // sets loop durations in ms, one for controller loop other for serial print

  sei();

  while (1) {
    if (loop1 == true) {}
    if (loop2 == true) {}
  }

  bridge.sleep(); // sets pwm to 0 and slp pin low
  return 0;
}