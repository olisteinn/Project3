#include "PI_controller.h"
#include <stdint.h>
#include "timer.h"
// þetta er sleggjan

PI_controller::PI_controller(double Kp_arg, double Ti_arg) {
    Kp = 256*Kp_arg;
    Ki = 256*Kp_arg/Ti_arg;
    KiE = 0;
    last_time = time_mus();
}

int16_t PI_controller::update(int16_t ref, int16_t actual) {
    int16_t e = ref-actual; // speed error
    int32_t Kpe = ((int32_t)Kp*e)>>8;
    uint32_t curr_time = time_mus();
    uint16_t dt = curr_time-last_time;
    int32_t edt = (int32_t)e*dt;
    last_time = curr_time;
    KiE += (Ki*(edt>>12))>>16;
    int32_t total = (int32_t)Kpe+KiE;
    if (total > (255*128)) { // Kemur þessu í rétt snið fyrir 8 bit pwm
        return (255*128);
    } else if (total < -(255*128)) {
        return -(255*128); // compiler reiknar öll "(255*128)" og setur bara töluna inn
    } else {
        return total;
    }
}