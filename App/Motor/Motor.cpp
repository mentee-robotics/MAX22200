/*
 * Motor.cpp
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */
#include "Motor.h"

Motor::Motor(uint8_t motorNumber) {
  m=motorNumber;
  channel1_ = (motorNumber - 1) * 2 + 1;
  channel2_ = (motorNumber - 1) * 2 + 2;

}

void Motor::setPWM(uint8_t pwm) {
  MAX22200_Set_CH(channel1_, 0, pwm, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  MAX22200_Set_CH(channel2_, 0, pwm, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
}

void Motor::stop() {

}

void Motor::setDirection(uint8_t mode){
    switch (mode) {
    case 0:  //mode 0 -Hi Z
        ONCH_bits[0] = 0;
        ONCH_bits[1] = 0;
        break;
    case 1:  //mode 1 - forward
        ONCH_bits[0] = 0;
        ONCH_bits[1] = 1;
        break;
    case 2:  //mode 2 - reverse
        ONCH_bits[0] = 1;
        ONCH_bits[1] = 0;
        break;
    case 3:  //mode 3 break
        ONCH_bits[0] = 1;
        ONCH_bits[1] = 1;
        break;
    }
}


