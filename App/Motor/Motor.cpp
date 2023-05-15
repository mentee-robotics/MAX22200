/*
 * Motor.cpp
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */
#include "Motor.h"

Motor::Motor(uint8_t motorNumber,MAX22200 max)
{
  max_=max;
  m=motorNumber;
  channel1_ = (motorNumber - 1) * 2 + 1;
  channel2_ = (motorNumber - 1) * 2 + 2;
  CFG_CH_Register cfg1_ = {
      .HFS = 1,                              // Set to 0
      .HOLD = {0, 0, 0, 0, 0, 0, 0},          // Set all elements of the array to 0
      .TRGnSPI = 0,                          // Set to 0
      .HIT = {0, 0, 0, 0, 0, 0, 0},           // Set all elements of the array to 0
      .HIT_T = {0, 0, 0, 0, 0, 0, 0, 0},       // Set all elements of the array to 0
      .VDRnCDR = 0,                          // Set to 0
      .HSnLS = 0,                            // Set to 0
      .FREQ_CFG = {0, 0},                     // Set all elements of the array to 0
      .SRC = 0,                              // Set to 0
      .OL_EN = 0,                            // Set to 0
      .DPM_EN = 0,                           // Set to 0
      .HHF_EN = 0                            // Set to 0
  };
  CFG_CH_Register cfg2_ = {
      .HFS = 1,                              // Set to 0
      .HOLD = {0, 0, 0, 0, 0, 0, 0},          // Set all elements of the array to 0
      .TRGnSPI = 0,                          // Set to 0
      .HIT = {0, 0, 0, 0, 0, 0, 0},           // Set all elements of the array to 0
      .HIT_T = {0, 0, 0, 0, 0, 0, 0, 0},       // Set all elements of the array to 0
      .VDRnCDR = 0,                          // Set to 0
      .HSnLS = 0,                            // Set to 0
      .FREQ_CFG = {0, 0},                     // Set all elements of the array to 0
      .SRC = 0,                              // Set to 0
      .OL_EN = 0,                            // Set to 0
      .DPM_EN = 0,                           // Set to 0
      .HHF_EN = 0                            // Set to 0
  };
  // Build and send configuration registers for channel 1
  uint32_t cfg1Data = buildCfgRegister(cfg1_);
  max_.MAX22200_write_register(channel1_, cfg1Data);

  // Build and send configuration registers for channel 2
  uint32_t cfg2Data = buildCfgRegister(cfg2_);
  max_.MAX22200_write_register(channel2_, cfg2Data);
}

void Motor::setPWM(uint8_t pwm) {
  uint32_t data1=max_.MAX22200_Set_CH(channel1_, 0, pwm, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  uint32_t data2=max_.MAX22200_Set_CH(channel2_, 0, pwm, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  //update cfg1_ cfg2_

}

void Motor::stop() {
	setDirection(3);
}
void Motor::forward() {
	setDirection(1);
}
void Motor::reverse() {
	setDirection(2);
}
void Motor::sleep() {
	setDirection(0);
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

 // Helper function to build configuration register data
 uint32_t Motor::buildCfgRegister(const CFG_CH_Register& config) {
   uint32_t result = 0;

   result |= (config.HFS << 31);
   for (int i = 0; i < 7; i++) {
     result |= (config.HOLD[i] << (24 - i));
   }
   result |= (config.TRGnSPI << 23);
   for (int i = 0; i < 7; i++) {
     result |= (config.HIT[i] << (16 - i));
   }
   for (int i = 0; i < 8; i++) {
     result |= (config.HIT_T[i] << (8 - i));
   }
   result |= (config.VDRnCDR << 7);
   result |= (config.HSnLS << 6);
   result |= ((config.FREQ_CFG[0] & 0x3) << 4);
   result |= (config.SRC << 3);
   result |= (config.OL_EN << 2);
   result |= (config.DPM_EN << 1);
   result |= config.HHF_EN;

   return result;
 }

