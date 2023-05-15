/*
 * loop.cpp
 *
 *  Created on: May 15, 2023
 *      Author: nir
 */


#include "Controller/Controller.h"
#include "Configuration.h"

MotorController control1;

extern "C" void loop_init() {
	if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
	{
	  // Starting Error
	  Error_Handler();
	}
}

extern "C" void loop() {

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) // Check if the interrupt comes from TIM2
  {
	  control1.update();
  }
}
