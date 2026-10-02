#include <uart.h>
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>
#include "encoder.h"
#include "drive.h"
#include "digital_out.h"
#include "timer.h"
#include <avr/interrupt.h>


extern Encoder motor;
extern Drive bridge;

extern Digital_out led;

void Initialization::on_do()
{

}

void Initialization::on_entry()
{
  serial_println("Initialization");
  cli(); // disable interrupts
  time_init(); // initalize timer 1 for time tracking use
  motor.init();  // initalize encoder
  bridge.init();  // initalize motor driver
  set_loop_ms(5,250); // sets loop durations in ms, one for controller loop other for serial print
  led.init(); // initalize led
  sei(); // enable interrupts
  serial_println("Boot up complete");
}

void Initialization::on_exit()
{
  serial_print("Initialization -> ");
}

void Initialization::reset()
{

}

void Initialization::on_operate()
{
  this->context_->transition_to(&operational_state);
}




