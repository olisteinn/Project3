#include "P_controller.h"
#include <stdint.h>

P_controller::P_controller(double Kp) : Kp(Kp) {}

uint8_t P_controller::update(int16_t ref,int16_t actual) {
    return (uint8_t)Kp*(ref-actual);
}