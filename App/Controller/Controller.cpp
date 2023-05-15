/*
 * Controller.cpp
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */

#include "Controller.h"
MotorController::MotorController() {
	  max_.MAX22200_init(&statusReg);
    for (uint8_t i = 1; i <= 4; i++) {
        motors.push_back(Motor(i,max_));
    }

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

void MotorController::update(void) {
  // Update the status register
  uint32_t statusRegData = max_.buildStatusRegister(&statusReg);
  max_.MAX22200_write_register(MAX22200_STATUS, statusRegData);

  // Update the configuration registers for each motor
  for (auto& motor : motors) {
    // Update configuration register for channel 1
    uint32_t cfg1Data = motor.buildCfgRegister(motor.cfg1_);
    max_.MAX22200_write_register(motor.channel1_, cfg1Data);

    // Update configuration register for channel 2
    uint32_t cfg2Data = motor.buildCfgRegister(motor.cfg2_);
    max_.MAX22200_write_register(motor.channel2_, cfg2Data);
  }
}

