#include "StopState.h"
#include "Context.h"          
#include "Initialization.h"   
#include "Operational.h"      
#include "drive.h"
#include "digital_out.h"      
#include "uart.h"


extern Drive bridge;
extern Digital_out led;

void StopState::on_do()
{
    //led toggle
}

void StopState::on_entry()
{
    bridge.stop();
    serial_println("Stopped");
}

void StopState::on_exit()
{
    serial_print("Stopped -> ");
}

void StopState::reset()
{
    this->context_->transition_to(&init_state);
}

void StopState::on_operate()
{
    this->context_->transition_to(&operational_state);
}

void StopState::on_pre_operate()
{
}

void StopState::on_fault()
{
}