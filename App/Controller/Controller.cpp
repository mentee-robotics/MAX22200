/*
 * Controller.cpp
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */

#include "Controller.h"

MotorController::MotorController() {
	  MAX22200_init();
    for (uint8_t i = 1; i <= 4; i++) {
        motors.push_back(Motor(i));
    }
    MAX22200_build_and_send_status_register(&statusReg);

}

void MotorController::setMotorPWM(uint8_t motorNumber, uint8_t pwm) {
    if (motorNumber > 0 && motorNumber <= motors.size()) {
        motors[motorNumber - 1].setPWM(pwm);
    }
}

void MotorController::stopMotor(uint8_t motorNumber) {
    if (motorNumber > 0 && motorNumber <= motors.size()) {
        motors[motorNumber - 1].stop();
    }
}

void MotorController::setMotorDirection(uint8_t motorNumber, uint8_t mode) {
    if (motorNumber > 0 && motorNumber <= motors.size()) {
        motors[motorNumber - 1].setDirection(mode);
    }
}


