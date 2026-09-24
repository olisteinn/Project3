#include <Arduino.h>
#include <Initialization.h>
#include <Context.h>


void Idle::on_do()
{
}

void Idle::on_entry()
{
  Serial.println("Initialization");
}

void Idle::on_exit()
{
  Serial.print("Initialization -> ");
}



