#pragma once

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_tim.h"
#include "MemoryStructures.h"






/** \file
 *  \brief
 *
 *
 */


/** \addtogroup AdapterBoard
 *  @{
 */

void SetMCUExt(uint8_t ID, uint8_t state);
void SetMCUExt_PWM(uint8_t ID, float Frequency, float Cycle);
void Init_MCUExt(uint8_t Mode_Ext0, uint8_t Mode_Ext1);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef * htim_pwm);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm);
void PWMTimer_Init(TIM_HandleTypeDef * htim, float Frequency, float DutyCycle);



