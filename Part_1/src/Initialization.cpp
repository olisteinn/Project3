#include "uart.h"
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>
#include "encoder.h"
#include "drive.h"
#include "digital_out.h"
#include "timer.h"
#include <avr/interrupt.h>
#include "Fault_handling.h"
#include "PreOperational.h"
#include "P_controller.h"
#include "PI_controller.h"


extern Encoder motor;
extern Drive bridge;

extern Digital_out led;

extern double Kp_init;
extern double Ti_init;
extern P_controller Pctrl;
extern PI_controller PIctrl;

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
  set_loop_ms(5,250); // sets loop durations in ms, one for controller loop other for serial print
  led.init();
  initFaultPin();
  
  P_controller Pctrl(Kp_init);
  PI_controller PIctrl(Kp_init,Ti_init);

  sei();
  serial_println("Initialization complete");
  this->context_->transition_to(&pre_op_state);
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
  
}

void Initialization::on_pre_operate()
{

}

void Initialization::on_fault()
{
}


