/*
 * Controller.h
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */

#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "Configuration.h"
#include "../Motor/Motor.h"

class MotorController
{
public:
    MotorController();
    void setMotorPWM(uint8_t motorNumber, uint8_t pwm);
    void stopMotor(uint8_t motorNumber);
    void setMotorDirection(uint8_t motorNumber, uint8_t mode);
    void update(void);
	MAX22200 max_;

private:
    std::vector<Motor> motors;
    MAX22200_StatusReg statusReg = {
        .ONCH = {0, 0, 0, 0, 0, 0, 0, 0},     // Set all elements of the array to 0
        .M_OVT = 0,                          // Set to 0
        .M_OCP = 0,                          // Set to 0
        .M_OLF = 0,                          // Set to 0
        .M_HHF = 0,                          // Set to 0
        .M_DPM = 0,                          // Set to 0
        .M_COMF = 1,                         // Set to 0
        .M_UVM = 0,                          // Set to 0
        .FREQM = 0,                          // Set to 0
        .CM76 = {1, 0},                 // Set all elements of the array to 0
        .CM54 = {1, 0},                 // Set all elements of the array to 0
        .CM32 = {1, 0},                 // Set all elements of the array to 0
        .CM10 = {1, 0},                 // Set all elements of the array to 0
        .OVT = 0,                            // Set to 0
        .OCP = 0,                            // Set to 0
        .OLF = 0,                            // Set to 0
        .HHF = 0,                            // Set to 0
        .DPM = 0,                            // Set to 0
        .COMER = 0,                          // Set to 0
        .UVM = 0,                            // Set to 0
        .ACTIVE = 1                          // Set to 0
    };
};


#endif /* CONTROLLER_CONTROLLER_H_ */
