#include "P_controller.h"
#include <stdint.h>

P_controller::P_controller(double Kp_arg) {
    Kp = Kp_arg * 256; // Kp_arg getur verið max 128
}

int16_t P_controller::update(int16_t ref, int16_t actual) {
    int16_t e = ref - actual; //gerir ráð fyrir að max hraði sé +/- ~100rpm
    int32_t Kpe = (int32_t)Kp*e; // Þetta er víst eitthvað trix fyrir 16b*16b = 32b aðgerðir
    return (int16_t)(Kpe >> 8);
}