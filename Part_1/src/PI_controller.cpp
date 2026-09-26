#include "PI_controller.h"
#include <cstdint>
#include <stdint.h>
#include "timer.h"

PI_controller::PI_controller(int16_t Kp, int16_t Ki, int16_t Ti) : Kp(Kp), Ki(Ki), Ti(Ti){}

uint8_t PI_controller::update(int16_t ref, int16_t actual) {
    uint16_t = 
    return (uint8_t)
}