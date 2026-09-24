#pragma once
#include <stdint.h>

class controller {
    private: 
        virtual ~controller();
    public:
        virtual uint8_t update(int16_t ref, int16_t actual) = 0;
};