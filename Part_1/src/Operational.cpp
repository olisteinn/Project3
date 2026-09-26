#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"
#include "Initialization.h"
#include "Operational.h"
#include "Context.h"
#include "digital_out.h"
#include "drive.h"
#include "encoder.h"
#include "controller.h"
#include "timer.h"
#include "StopState.h"
#include "PreOperational.h"

extern Digital_out led;
extern Drive bridge;
extern Encoder motor;
extern controller* ctrl;
extern int16_t target_speed;
char speed_str[10];
char print_str[80];
int16_t currspeed;
int16_t ctrlOP;

void Operational::on_do()
{
  if (loop1 == true){
    loop1 = false;
    currspeed = motor.speed();
    ctrlOP = ctrl->update(target_speed,currspeed); // ctrlOP = controller output, int16_t 
    bridge.run(ctrlOP); // .run(int16_t) les signed 16 bit on þýðir:
    //[-1,-32768] í .rev([0,255]) og [1,32767] í .fwd([0,255])
  }
  if (loop2 == true) {
    loop2 = false;
    sprintf(speed_str,"%4d.%2d",currspeed/100,abs(currspeed)%100);
    sprintf(print_str,"\rTarget speed: %4d.%1d rpm    True speed: %s rpm    PWM: %3d    ",
      target_speed/100,abs(target_speed)%100,speed_str, ctrlOP>>7);
    serial_print(print_str);
  }
}

void Operational::on_entry()
{
  serial_println("Operational");
  led.set_hi();
  bridge.wake();
}

void Operational::on_exit()
{
  led.set_lo();
  bridge.stop();
  serial_print("Operational -> ");
}

void Operational::reset()
{
  this->context_->transition_to(&init_state);
}

void Operational::on_operate()
{

}

void Operational::on_pre_operate()
{
  this->context_->transition_to(&pre_op_state);
}

void Operational::on_fault()
{
    this->context_->transition_to(&stop_state);
}