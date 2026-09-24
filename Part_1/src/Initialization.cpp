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
  serial_print("Initialization -> ");
}



