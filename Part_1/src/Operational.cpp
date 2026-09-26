#include <uart.h>
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>


void Operational::on_do()
{
}

void Operational::on_entry()
{
  serial_println("Operational");
}

void Operational::on_exit()
{
  serial_print("Operational -> ");
}

void Operational::on_init()
{
  this->context_->transition_to(&init_state);
}

void Operational::on_operate()
{

}

