#include "timer.h"

static uint32_t time = 0;

uint32_t time_mus() {
    return time;
}

void time_set(uint32_t t) {
    time = t;
}