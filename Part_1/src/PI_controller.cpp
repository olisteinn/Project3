#include "PI_controller.h"
#include <stdint.h>
#include "timer.h"

PI_controller::PI_controller(double Kp_arg, double Ti_arg) {
    Kp = 256*Kp_arg; // int16_t*double -> double*double = double -> int16_t (Kp max 128)
    Ki = 256*Kp_arg/Ti_arg;// int16_t*double/double -> double*double/double = double -> int16_t
    KiE = 0;
    last_time = time_mus();
}

int16_t PI_controller::update(int16_t ref, int16_t actual) {
    int16_t e = ref-actual;
    int16_t Kpe = (int16_t)(((int32_t)Kp*e)>>8);
    uint32_t curr_time = time_mus();
    uint16_t dt = curr_time-last_time;// max 65,535 mícrósek á milli, overflowar annas, samt ekki hættulegt
    int32_t edt = (int32_t)e*dt; // (int32_t)int16_t*uint16_t er sama trix (notar mulsu instruction)
    last_time = curr_time;
    KiE += (int16_t)((Ki*(edt>>8))>>16); // staggeruð bit shift passa að ekkert overflowi en missi samt ekki nákvæmni
    int32_t total = (int32_t)Kpe+KiE;
    if (total > (255*128)) {
        return (255*128);
    } else if (total < -(255*128)) {
        return -(255*128);
    } else {
        return total;
    }
}