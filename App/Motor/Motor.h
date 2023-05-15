/*
 * Motor.h
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#include "MAX22200_driver.h"

class Motor
{
public:
  Motor(uint8_t motorNumber);
  void setPWM(uint8_t pwm);
  void stop();
  void setDirection(uint8_t mode);
  uint8_t ONCH_bits[2];
private:
  uint8_t channel1_;
  uint8_t channel2_;
  uint8_t m;
};



#endif /* MOTOR_MOTOR_H_ */
