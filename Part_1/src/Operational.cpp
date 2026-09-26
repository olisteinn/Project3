#include <uart.h>
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>
#include <digital_out.h>
#include <drive.h>

extern Digital_out led;
extern Drive bridge;

void Operational::on_do()
{
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
