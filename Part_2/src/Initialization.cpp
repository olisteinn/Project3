#include "uart.h"
#include <Initialization.h>
#include <Operational.h>
#include "StopState.h"
#include <Context.h>
#include "encoder.h"
#include "drive.h"
#include "digital_out.h"
#include "timer.h"
#include <avr/interrupt.h>
#include "Fault_handling.h"
#include "P_controller.h"


extern Encoder motor;
extern Drive bridge;

extern Digital_out led;

extern double Kp_init;
extern double Ti_init;
extern P_controller Pctrl;
extern double Kp_inp;
extern double Ti_inp;
extern controller* ctrl;

void Initialization::on_do()
{

}

void Initialization::on_entry()
{
  serial_println("Initialization");
  cli();
  time_init(); // initalize timer 1 for time tracking use
  motor.init();  // initalize encoder
  bridge.init();  // initalize motor driver
  set_loop_ms(5,20); // sets loop durations in ms, one for controller loop other for serial print
  led.init();
  initFaultPin();

  Pctrl  = P_controller(Kp_init);
  Kp_inp = Kp_init;          
  Ti_inp = Ti_init;
  ctrl   = &Pctrl;           

  sei();
  serial_println("Initialization complete");
}

void Initialization::on_exit()
{
  serial_println("Boot up complete");
  serial_print("Initialization -> ");
}

void Initialization::reset()
{

}

void Initialization::on_operate()
{
  this->context_->transition_to(&operational_state);
}

void Initialization::on_fault()
{
  this->context_->transition_to(&stop_state);
}


