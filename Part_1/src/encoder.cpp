#include "encoder.h"
#include "timer.h"
#include <avr/interrupt.h>
#include <cstdint>
#include <stdint.h>

Encoder::Encoder(int pin1, int pin2, int pin_out) 
  : P1(pin1), P2(pin2), Pout(pin_out) 
{
    counter = 0;
    ext_counter = 0;
    dir = true;
}

void Encoder::init() {
    P1.init();
    P2.init();
    Pout.init();
    P1prevstate = P1.is_hi();
}

void Encoder::update() {
    bool P1currstate = P1.is_hi();
    if (P1currstate == true) {
        if (P1currstate != P1prevstate) {
            bool P2currstate = P2.is_hi();
            if (P1currstate != P2currstate) {
                counter++;
                ext_counter++;
                dir = true;
            } else {
                counter--;
                ext_counter--;
                dir = false;
            }
            P1prevstate = P1currstate;

            history_head++;
            if (history_head >= history_length) {
                history_head=0;
            }
            enc_memory[history_head].timestamps = time_mus();
            enc_memory[history_head].counter_mem = (int8_t)counter;

        if (ext_counter >= rev_res || -rev_res >= ext_counter) {
            ext_counter = 0;
        }
        }
    } else {
        P1prevstate = P1currstate;
    }
}

bool Encoder::direction() {
    return dir;
}

int16_t Encoder::position() {
    cli();
    int16_t val = ext_counter;
    sei();
    return val;
}

int16_t Encoder::speed() {
    uint8_t head = history_head;
    uint8_t tail = head + 1;
    if (tail >= history_length) {
        tail = 0;
    }
    cli(); //stoppa interrupts til að copya >8 bit vals
        int32_t new_time = enc_memory[head].timestamps;
        int32_t old_time = enc_memory[tail].timestamps;
        int8_t delta_pos = enc_memory[head].counter_mem - enc_memory[tail].counter_mem;
    sei();
    if ((time_mus() - new_time) > timeout) {
        rpm = 0;
        return rpm;
    }
    int32_t delta_time = new_time - old_time;
    if (delta_time == 0) {
        return rpm; 
    }
    rpm = 100L * (60000000L/rev_res) * delta_pos / delta_time;
    return rpm;
}