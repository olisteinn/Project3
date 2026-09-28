#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include "timer.h"
#include "digital_in.h"
#include "digital_out.h"
#include "encoder.h"
#include "drive.h"
#include "P_controller.h"
#include "PI_controller.h"
#include "Context.h"
#include "uart.h"
#include "Initialization.h"
#include "Operational.h"
#include "State.h"
#include "Fault_handling.h"
#include "StopState.h"
#include "PreOperational.h"

Initialization init_state;
Operational operational_state;
StopState stop_state;
PreOperational pre_op_state;
Context *motor_state;



Encoder motor(D2,D4,D7); // encoder driver, (encoder in 1, encoder in 2, signal read out)
Drive bridge(0,D8); // motor driver, (timer circuit no., slp pin)

Digital_out led(D13);

double Kp_inp = 1;
double Ti_inp = 1;
int16_t target_speed = -5000;  // Target speed = rpm*100
P_controller Pctrl(Kp_inp);
PI_controller PIctrl(Kp_inp,Ti_inp);
controller* ctrl = &Pctrl;

ISR(INT0_vect) {  // D2 interrupt, INT0 activated by digital_in through encoder class
  motor.update(); // reads position and timestamps on encoder in pin interrupt
}

int main() {
  serial_init();
  Context ctx(&init_state);
  motor_state = &ctx;
  char c[10];

  while (1) {
    if (loop1 == true) {}
    if (loop2 == true) {}
    
    if (serial_available()) {
        bool set_param = false;
        serial_read_string(c,10);
        serial_print("\r\n");
        serial_print("I received: ");
        serial_print(c);
        serial_print("\r\n");
        if (c[0] == 'r' && c[1] == '\0') {
          motor_state->reset();
        } else if (c[0] == 'o' && c[1] == '\0') {
          motor_state->on_operate();
        } else if (c[0] == 'p' && c[1] == '\0') {
          motor_state->on_pre_operate();
        } else if (c[0] == 'P' && (c[1] == '\0'|| c[2] == '\0'||)) {
          motor_state->controller_selector(c);
        } else if (c[0] == 'K' && c[1] == 'p' && c[2] == '\0') {
          char Kp_str[7];
          serial_read_string(Kp_str,7);
          Kp_inp = atof(Kp_str);
          set_param = true;
        } else if (c[0] == 'T' && c[1] == 'i' && c[2] == '\0') {
          char Ti_str[7];
          serial_read_string(Ti_str,7);
          Ti_inp = atof(Ti_str);
          set_param = true;
        }
        if (set_param == true)
          motor_state->set_parameters(Kp_inp,Ti_inp);
    }
    motor_state->do_work();
    
  }
  

  bridge.sleep(); // sets pwm to 0 and slp pin low
  return 0;
}