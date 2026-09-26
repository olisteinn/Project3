#include <uart.h>
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>


void Initialization::on_do()
{
}

void Initialization::on_entry()
{
  serial_println("Initialization");
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


