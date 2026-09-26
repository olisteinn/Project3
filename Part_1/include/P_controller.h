#ifndef P_CONTROLLER_H
#define P_CONTROLLER_H
#include "controller.h"
#include <stdint.h>

class P_controller {
    private:
        uint8_t Kp;
    public:
        P_controller(uint8_t Kp);
        uint8_t update(uint16_t ref,uint16_t actual);
};

#endif