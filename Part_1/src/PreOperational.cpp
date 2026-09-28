#include "uart.h"
#include <Initialization.h>
#include <Operational.h>
#include <Context.h>
#include "encoder.h"
#include "drive.h"
#include "digital_out.h"
#include "timer.h"
#include <avr/interrupt.h>
#include "Fault_handling.h"
#include "PreOperational.h"
#include "StopState.h"
#include "controller.h"
#include "P_controller.h"
#include "PI_controller.h"


extern Drive bridge;
extern Digital_out led;
static uint32_t led_ms;

extern controller* ctrl;
extern P_controller Pctrl;
extern PI_controller PIctrl;

void PreOperational::on_do()
{
    if ((time_ms()-led_ms) >= 500) {
        led_ms = time_ms();
        led.toggle();
    }
}

void PreOperational::on_entry()
{
  serial_println("Pre Operational");
  bridge.stop();
  led_ms = time_ms();
}

void PreOperational::on_exit()
{
  led.set_lo();
  serial_print("Pre Operational -> ");
}

void PreOperational::reset()
{
  this->context_->transition_to(&init_state);
}

void PreOperational::on_operate()
{
  this->context_->transition_to(&operational_state);
}

void PreOperational::on_pre_operate()
{

}

void PreOperational::on_fault()
{
    this->context_->transition_to(&stop_state);

}

void PreOperational::controller_selector(uint8_t type)
{
  if (type == 1) {
    ctrl = &Pctrl;
    serial_println("P controller selected");
  } else if (type == 2) {
    ctrl = &PIctrl;
    serial_println("PI controller selected");
  }
}

void PreOperational::set_parameters(double Kp, double Ti)
{
  if (Kp <= 0 || Kp >= 127 || Ti <= 0) {
    serial_println("Invalid: need 0 < Kp < 127 and Ti > 0"); // Kp overflowar fyrir ofan 127
    return;
  }
  ctrl->set_params(Kp, Ti);
  serial_println("Parameters set");
}


