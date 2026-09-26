#include "uart.h"
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
  cli();
  time_init(); // initalize timer 1 for time tracking use
  motor.init();  // initalize encoder
  bridge.init();  // initalize motor driver
  set_loop_ms(5,250); // sets loop durations in ms, one for controller loop other for serial print
  led.init();
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

void Initialization::on_pre_operate()
{

}

void Initialization::on_fault()
{
}


