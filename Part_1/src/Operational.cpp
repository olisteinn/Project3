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



