/*
 * Motor.h
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_
#include "../Configuration.h"
#include "../MAX22200/MAX22200_driver.h"
 // Define the struct that represents the CFG_CH register
  typedef struct {
      uint8_t HFS;
      uint8_t HOLD[7];
      uint8_t TRGnSPI;
      uint8_t HIT[7];
      uint8_t HIT_T[8];
      uint8_t VDRnCDR;
      uint8_t HSnLS;
      uint8_t FREQ_CFG[2];
      uint8_t SRC;
      uint8_t OL_EN;
      uint8_t DPM_EN;
      uint8_t HHF_EN;
  } CFG_CH_Register;

class Motor
{
public:
  Motor(uint8_t motorNumber,MAX22200 max);
  void setPWM(uint8_t pwm);
  void stop();
  void forward();
  void reverse();
  void sleep();
  void setDirection(uint8_t mode);
  uint32_t buildCfgRegister(const CFG_CH_Register& config);
  uint8_t ONCH_bits[2];
  uint8_t channel1_;
  uint8_t channel2_;
  uint8_t m;
  CFG_CH_Register cfg1_;
  CFG_CH_Register cfg2_;
  MAX22200 max_;
private:




};



#endif /* MOTOR_MOTOR_H_ */
