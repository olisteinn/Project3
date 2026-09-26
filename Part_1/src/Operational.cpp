#include <stdint.h>
#include "uart.h"
#include "Initialization.h"
#include "Operational.h"
#include "Context.h"
#include "digital_out.h"
#include "drive.h"
#include "encoder.h"
#include "controller.h"
#include "timer.h"

extern Digital_out led;
extern Drive bridge;
extern Encoder motor;
extern controller* ctrl;
extern int16_t target_speed;


void Operational::on_do()
{
  if (loop1 == true){
    loop1 = false;
    int16_t ctrlOP = ctrl->update(target_speed,motor.speed()); // ctrlOP = controller output, int16_t 
    bridge.run(ctrlOP); // .run(int16_t) les signed 16 bit on þýðir:
    //[-1,-32768] í .rev([0,255]) og [1,32767] í .fwd([0,255])
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

}
