#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H
#include "controller.h"
#include <stdint.h>

class PI_controller {
    private:
        uint8_t Kp;
        uint8_t Ki;
        uint8_t Ti;
        uint8_t e;
        uint32_t
    public:
        PI_controller(uint8_t Kp, uint8_t Ki, uint8_t Ti, int16_t e);
        uint8_t update(int16_t ref, int16_t actual);
};

#endif