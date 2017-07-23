/** \file
 *  \brief
 *
 *
 */


/** \addtogroup AdapterBoard
 *  @{
 */


#include "AdapterBoard_MCUExt.h"


TIM_HandleTypeDef htim10;                        // PWM Timer
TIM_HandleTypeDef htim11;                        // Pulse Timer
TIM_OC_InitTypeDef sConfigOC_PWM;

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SetMCUExt(uint8_t ID, uint8_t state) {
    if (ID == 1) {
        if (state == 0) {
            HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7, GPIO_PIN_SET);
        }
    } else {
        if (state == 0) {
            HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6, GPIO_PIN_SET);
        }
    }
}

void SetMCUExt_PWM(uint8_t ID, float Frequency, float Cycle) {
    if (Cycle <= 0) {
        HAL_TIM_PWM_DeInit(((ID==0) ? &htim10 : &htim11));
        Init_MCUExt(0,0);
        SetMCUExt(ID,0);


    } else if (Cycle >= 100) {
        HAL_TIM_PWM_DeInit(((ID==0) ? &htim10 : &htim11));
        Init_MCUExt(0,0);
        SetMCUExt(ID,1);

    } else {
        __HAL_RCC_GPIOF_CLK_ENABLE();
        Init_MCUExt(1,1);

        //Start Timer
        if (ID == 1) {
                htim11.Instance = TIM11;
                PWMTimer_Init(&htim11,Frequency, Cycle);
        } else {
                htim10.Instance = TIM10;
                PWMTimer_Init(&htim10,Frequency, Cycle);
        }
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_MCUExt(uint8_t Mode_Ext0, uint8_t Mode_Ext1) {
    //CLK
    __HAL_RCC_GPIOF_CLK_ENABLE();


    GPIO_InitTypeDef  gpio_init_structure;


    //MCUExt0
    gpio_init_structure.Pin = GPIO_PIN_7;
    if (Mode_Ext0 == 0) {
        //IO
        gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
        gpio_init_structure.Pull = GPIO_PULLUP;
        gpio_init_structure.Speed = GPIO_SPEED_HIGH;
    } else {
        //Timer
        gpio_init_structure.Mode = GPIO_MODE_AF_PP;
        gpio_init_structure.Pull = GPIO_NOPULL;
        gpio_init_structure.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init_structure.Alternate = GPIO_AF3_TIM11;
    }

    HAL_GPIO_Init(GPIOF, &gpio_init_structure);


    //MCUExt1
    gpio_init_structure.Pin = GPIO_PIN_6;
    if (Mode_Ext1 == 0) {
        //IO

        gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
        gpio_init_structure.Pull = GPIO_PULLUP;
        gpio_init_structure.Speed = GPIO_SPEED_HIGH;


    } else {
        //Timer
        gpio_init_structure.Mode = GPIO_MODE_AF_PP;
        gpio_init_structure.Pull = GPIO_NOPULL;
        gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_structure.Alternate = GPIO_AF3_TIM10;
    }

    HAL_GPIO_Init(GPIOF, &gpio_init_structure);

    //Ausgänge auf 0 setzen
    SetMCUExt(0, 0);
    SetMCUExt(1, 0);
}

/** \brief  Enable Clock and Port for PWM Timer
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef * htim_pwm){
  if(htim_pwm->Instance==TIM10){
    __HAL_RCC_TIM10_CLK_ENABLE();
  } else if (htim_pwm->Instance==TIM11) {
    __HAL_RCC_TIM11_CLK_ENABLE();
  }
}

/** \brief  Disable Clock for PWM Timer
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm){
  if(htim_pwm->Instance==TIM10){
    /* Peripheral clock disable */
    __HAL_RCC_TIM10_CLK_DISABLE();
  } else if(htim_pwm->Instance==TIM11){
    /* Peripheral clock disable */
    __HAL_RCC_TIM10_CLK_DISABLE();
  }
}

/** \brief  PWM Timer Init Function
 *
 *  \param  None
 *  \retval None
 */
void PWMTimer_Init(TIM_HandleTypeDef * htim, float Frequency, float DutyCycle){
  TIM_MasterConfigTypeDef sMasterConfig;

  uint32_t periodValue = 200000000 / Frequency;
  uint16_t prescalerValue = periodValue / 65536 + 1;
  periodValue /= prescalerValue;

  uint16_t dutyCycle_Ticks = (periodValue*DutyCycle) / 100;


  htim->Init.Prescaler = prescalerValue-1;
  htim->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim->Init.Period = periodValue-1;
  htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  if (HAL_TIM_PWM_Init(htim) != HAL_OK){
    while(1);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK){
    while(1);
  }

  sConfigOC_PWM.OCMode = TIM_OCMODE_PWM1;
  //sConfigOC.Pulse = 658-1;
  sConfigOC_PWM.Pulse = (periodValue-1) / 10;
  sConfigOC_PWM.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC_PWM.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC_PWM, TIM_CHANNEL_1) != HAL_OK){
    while(1);
  }






  __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, dutyCycle_Ticks);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
}


