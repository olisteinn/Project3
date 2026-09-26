#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "digital_in.h"
#include "digital_out.h"
#include "encoder.h"
#include "drive.h"
#include "P_controller.h"
#include <Context.h>
#include <uart.h>
#include <Initialization.h>
#include <Operational.h>
#include <State.h>
#include "Fault_handling.h"
#include "StopState.h"

Initialization init_state;
Operational operational_state;
Context *motor_state;

Encoder motor(D2,D4,D7); // encoder driver, (encoder in 1, encoder in 2, signal read out)
Drive bridge(0,D8); // motor driver, (timer circuit no., slp pin)

Digital_out led(D13);

bool put_reset, put_operate;

ISR(INT0_vect) {  // D2 interrupt, INT0 activated by digital_in through encoder class
  motor.update(); // reads position and timestamps on encoder in pin interrupt
}

int main() {
  Context ctx(&init_state);
  motor_state = &ctx;
  sei();

  while (1) {
    if (loop1 == true) {}
    if (loop2 == true) {}
    if (check_fault()) {
      motor_state->transition_to(&stop_state);
    }

  char c=0;

  if (serial_available()) {
      c = serial_read();
      serial_print("I received: ");
      serial_print_char(c);
      serial_print("\r\n");
}
  put_reset = put_operate = false;

  if (c=='r'){
    put_reset = true;
  }
  if (c=='o'){
    put_operate = true;
  }


  motor_state->do_work();
  
  if (put_reset)
    motor_state->reset();
  if (put_operate)
    motor_state->on_operate();
  }
  

  bridge.sleep(); // sets pwm to 0 and slp pin low
  return 0;
}