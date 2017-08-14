/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

 /** \addtogroup Templateclick
 *  @{
 *
 */

#include "IRclick.h"
#include "PanasonicAC_IR.h"
#include "stm32746g_discovery.h"

/* PWM Timer Configuration
 *
 * MB8
 * ClickBoard IN -> EXT_MCU_2 -> PF_6 (TIM10_CH1)
 * ClickBoard OUT -> MB_AN7 -> IC3_P5 (PortExpander)
 * */
#define PWM_TIMER_INSTANCE			TIM10
#define PWM_TIMER_CHANNEL			TIM_CHANNEL_1
#define PWM_TIMER_CLK_ENABLE()		__HAL_RCC_TIM10_CLK_ENABLE()
#define PWM_TIMER_CLK_DISABLE()		__HAL_RCC_TIM10_CLK_DISABLE()
#define PWM_PORT					GPIOF
#define PWM_PIN						GPIO_PIN_6
#define PWM_ALTERNATE_FUNCTION		GPIO_AF3_TIM10

/* Pulse Timer Configuration */
/* additional: Rename the IRQ Handler in "stm32f7xx_it.c/.h */
#define PULSE_TIMER_INSTANCE		TIM4
#define PULSE_TIMER_CHANNEL			TIM_CHANNEL_1
#define PULSE_TIMER_IRQ				TIM4_IRQn
#define PULSE_TIMER_CLK_ENABLE()	__HAL_RCC_TIM4_CLK_ENABLE()
#define PULSE_TIMER_CLK_DISABLE()	__HAL_RCC_TIM4_CLK_DISABLE()

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef hPWMTimer;                    // PWM Timer TIM5/CH4
TIM_HandleTypeDef hPulseTimer;                  // Pulse Timer TIM5/CH1
TIM_HandleTypeDef hRXTimer;						// RX Capture Timer
static TIM_OC_InitTypeDef sConfigOC_PWM;        // Config-struct PWM Timer
static TIM_OC_InitTypeDef sConfigOC_Pulse;      // Config-struct Pulse Timer

static uint16_t *pPulseTimeBuffer;
static uint16_t nPulses = 0;
static volatile uint16_t pulseIndex = 0;
static volatile uint8_t pulseToggle = 0;

static volatile uint8_t RX_Message_Complete = 0;
static uint16_t RX_Pulse_Buffer[200] = {0};

/* Private function prototypes -----------------------------------------------*/
static void IR_PWMTimer_GPIO_Init(void);
static void IR_PWMTimer_Init(void);
static void IR_StartPWM(uint8_t percentDutyCycle);
//void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm);

static void IR_PulseTimer_Init(void);
static void IR_SetPulseLength(uint16_t pulseLength);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef* htim_oc);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef* htim_oc);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* htim);

static void IR_RX_Pin_Init(void);
static void IR_RX_Timer_Init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

//extern void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/
/** \brief
 *
 *  \param
 *  \retval
 */
void IRclick_Select(struct clickBoard * Board, uint8_t Addr) {
	IRclick_Current = Board;


}

/** \brief
 *
 *  \param
 *  \retval
 */
uint8_t * IRclick_get(unsigned short channel) {
    static uint8_t Receive;

    //Kommunikations-Init


    //Write Read Funktionen



    return &Receive;
}

/** \brief
 *
 *  \param
 *  \retval
 */
void IRclick_set(unsigned short channel, uint8_t Val) {

}


/** \brief  Initialize the the IRclick-Board
 *
 *  \param  None
 *  \retval None
 */
 void IRclick_Init(void){
     /* Init PWM Timer */
	 PWM_TIMER_CLK_ENABLE();
	 IR_PWMTimer_GPIO_Init();
     IR_PWMTimer_Init();
     /* Init Pulse Timer */
     IR_PulseTimer_Init();

     /* Init Receive Timer and Pin */
     //IR_RX_Pin_Init();
     //IR_RX_Timer_Init();
 }

 /** \brief De-Initialize the the IRclick-Board
 *
 *  \param  None
 *  \retval None
 */
 void IRclick_DeInit(void){
     HAL_TIM_PWM_MspDeInit(&hPWMTimer);
     HAL_TIM_OC_MspDeInit(&hPulseTimer);
 }

/** \brief  Starts the Transmission of the IR-Message
 *
 *  \param  uint16_t *pulseTimeBuffer: Buffer with the Pulse-Lengths in MicroSeconds
            uint16_t length: Length of the Buffer
 *  \retval None
 */
 void IRclick_Send(uint16_t *pulseTimeBuffer, uint16_t length){
       /* Init Pulse Timer */
       IR_PulseTimer_Init();
       IR_StartPWM(50);
       pulseToggle = 1;
       pPulseTimeBuffer = pulseTimeBuffer;
       nPulses = length;
       /* Start Pulse Timer */
       IR_SetPulseLength(pPulseTimeBuffer[pulseIndex++]);
       //HAL_NVIC_EnableIRQ(PULSE_TIMER_IRQ);
       HAL_TIM_OC_Start_IT(&hPulseTimer, PULSE_TIMER_CHANNEL);
}


/**********************************************************************/
/**                 PWM Timer (Transmit)                              */
/**********************************************************************/

/** \brief  Set the Duty Cycle for PWM and Start
 *
 *  \param  uin8_t percentDutyCycle: 0-100
 *  \retval None
 */
static void IR_StartPWM(uint8_t percentDutyCycle){
    uint16_t dutyCycle = (2632*percentDutyCycle) / 100;
    __HAL_TIM_SET_COMPARE(&hPWMTimer, PWM_TIMER_CHANNEL, dutyCycle);
    HAL_TIM_PWM_Start(&hPWMTimer, PWM_TIMER_CHANNEL);
}


/** \brief  Initialize Port for PWM Output
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==PWM_TIMER_INSTANCE){

    /**TIM5 GPIO Configuration
    PI0     ------> TIM5_CH4
    */
    GPIO_InitStruct.Pin = PWM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = PWM_ALTERNATE_FUNCTION;
    HAL_GPIO_Init(PWM_PORT, &GPIO_InitStruct);
  }

}


/** \brief  Activate Clock for PWM Timer Output Port
 *
 *  \param  None
 *  \retval None
 */
static void IR_PWMTimer_GPIO_Init(void){
	__HAL_RCC_GPIOI_CLK_ENABLE();
}


/** \brief  PWM Timer Init Function (TIM5)
 *
 *  \param  None
 *  \retval None
 */
static void IR_PWMTimer_Init(void){
  TIM_MasterConfigTypeDef sMasterConfig;
  //TIM_OC_InitTypeDef sConfigOC;

  /* CLK_IN = 100MHz
   * f_OUT = 38kHz
   *
   *    N = CLK_IN / f_OUT = 2632
   *    N = Prescaler * Period = 2632
   *
   */
   uint16_t prescalerValue = 1;
   uint32_t periodValue = 2632;

  hPWMTimer.Instance = PWM_TIMER_INSTANCE;
  hPWMTimer.Init.Prescaler = prescalerValue-1;
  hPWMTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
  hPWMTimer.Init.Period = periodValue-1;
  hPWMTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  //htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&hPWMTimer) != HAL_OK){
    //Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&hPWMTimer, &sMasterConfig) != HAL_OK){
    //Error_Handler();
  }

  sConfigOC_PWM.OCMode = TIM_OCMODE_PWM1;
  //sConfigOC.Pulse = 658-1;
  sConfigOC_PWM.Pulse = 0;
  sConfigOC_PWM.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC_PWM.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&hPWMTimer, &sConfigOC_PWM, PWM_TIMER_CHANNEL) != HAL_OK){
    //Error_Handler();
  }

  HAL_TIM_MspPostInit(&hPWMTimer);

}


/**********************************************************************/
/**                 Pulse Timer (Transmit)                            */
/**********************************************************************/

/** \brief  Set the Pulse
 *
 *  \param  uin8_t percentDutyCycle: 0-100
 *  \retval None
 */
static void IR_SetPulseLength(uint16_t pulseLength){
    //htim2.Init.Period = pulseLength;
    //HAL_TIM_OC_Init(&htim2);
    sConfigOC_Pulse.Pulse = pulseLength;
    HAL_TIM_OC_ConfigChannel(&hPulseTimer, &sConfigOC_Pulse, PULSE_TIMER_CHANNEL);
}

/** \brief  Initialize Pulse Timer (TIM2)
 *
 *  \param  None
 *  \retval None
 */
/* TIM2 init function */
static void IR_PulseTimer_Init(void){
  TIM_MasterConfigTypeDef sMasterConfig;

  hPulseTimer.Instance = PULSE_TIMER_INSTANCE;
  hPulseTimer.Init.Prescaler = 100;
  hPulseTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
  hPulseTimer.Init.Period = 3401;
  hPulseTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  //htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&hPulseTimer) != HAL_OK){
    //Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&hPulseTimer, &sMasterConfig) != HAL_OK){
    //Error_Handler();
  }

  sConfigOC_Pulse.OCMode = TIM_OCMODE_TIMING;
  sConfigOC_Pulse.Pulse = 3400;
  sConfigOC_Pulse.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC_Pulse.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&hPulseTimer, &sConfigOC_Pulse, PULSE_TIMER_CHANNEL) != HAL_OK){
    //Error_Handler();
  }

}

/** \brief  Initialize Pulse Timer Clock and Interrupt
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef* htim_oc){

  if(htim_oc->Instance==PULSE_TIMER_INSTANCE){
    /* Peripheral clock enable */
    PULSE_TIMER_CLK_ENABLE();
    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(PULSE_TIMER_IRQ, 15, 0);
    HAL_NVIC_EnableIRQ(PULSE_TIMER_IRQ);
  }

}

/** \brief  De-Initialize Pulse Timer Clock and Interrupt
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef* htim_oc){

  if(htim_oc->Instance==PULSE_TIMER_INSTANCE){
    /* Peripheral clock disable */
	  PULSE_TIMER_CLK_DISABLE();

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(PULSE_TIMER_IRQ);
  }
}


/** \brief  Interrupt Callback for Pulse Timer
 *
 *  \param  Timer Handle
 *  \retval None
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef* htim){
    uint16_t pulseTime = pPulseTimeBuffer[pulseIndex++];
    hPulseTimer.Init.Period = pulseTime;
    HAL_TIM_OC_Init(&hPulseTimer);

    if(pulseToggle){
    	// Set new PWM value: 0%
        __HAL_TIM_SET_COMPARE(&hPWMTimer, PWM_TIMER_CHANNEL, 0);
        pulseToggle = 0;
    }else{
    	// Set new PWM value: 50%
        __HAL_TIM_SET_COMPARE(&hPWMTimer, PWM_TIMER_CHANNEL, 1316);
        pulseToggle = 1;
    }

    if(pulseIndex >= nPulses){
        /* IR Message Complete -> Stop Interrupt */
        HAL_TIM_OC_Stop_IT(&hPulseTimer, PULSE_TIMER_CHANNEL);
        //HAL_NVIC_DisableIRQ(PULSE_TIMER_IRQ);
        pulseIndex = 0;
    }
}

/**********************************************************************/
/**                 PF10 EXTI (Receive)                               */
/**********************************************************************/

/** \brief  Configure pin PF10 as EXTI (PF10 -> EXTI Line 10)
 *
 * 	\param  None
 * 	\retval None
*/
static void IR_RX_Pin_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin : PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* Enable and set Button EXTI Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x00, 0x00);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/** \brief  Initialize the timer for receive
 *
 *  \param  None
 *  \retval None
 */
static void IR_RX_Timer_Init(void){

	__HAL_RCC_TIM14_CLK_ENABLE();

	uint32_t uwPrescalerValue = 0;
	/* Compute the prescaler value to have TIM14 counter clock equal to 10 KHz */
	uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / 100000) - 1;

	/* Set TIMx instance */
	hRXTimer.Instance = TIM14;

	/* Initialize TIM3 peripheral as follows:
	 + Period = 500 - 1
	 + Prescaler = ((SystemCoreClock/2)/10000) - 1
	 + ClockDivision = 0
	 + Counter direction = Up
	 */
	hRXTimer.Init.Period = 0xFFFF;
	hRXTimer.Init.Prescaler = uwPrescalerValue;
	hRXTimer.Init.ClockDivision = 0;
	hRXTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	if (HAL_TIM_Base_Init(&hRXTimer) != HAL_OK) {
		//Error_Handler();
	}
}

/** \brief  Function to check if a new message is available
 *
 *  \param  None
 *  \retval 1 if new message is available otherwise 0
 */
uint8_t IRclick_IsMessageReady(void){
	uint8_t ret = 0;
	if(RX_Message_Complete){
		ret = 1;
		RX_Message_Complete = 0;
	}else{
		ret = 0;
	}
	return ret;
}

/** \brief  Request pointer to the received message pulse buffer
 *
 *  \param  None
 *  \retval Pointer to the buffer
 */
uint16_t * IRclick_GetRXMessagePulseBuffer(void){
	//RX_Message_Complete = 0;
	return RX_Pulse_Buffer;
}


/** \brief  Interrupt Callback for receive process
 *
 *  \param  uint16_t GPIO_Pin
 *  \retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	//__disable_irq();
	static uint32_t ticks_last_edge = 0;
	static uint8_t start_flag = 0, start_pulse_flag = 0;
	static uint16_t buffer_index = 0;
	uint32_t ticks, deltaTicks;
	if(GPIO_Pin == GPIO_PIN_10){

		// Erste Flanke -> Timer starten
		if(start_flag == 0){
			HAL_TIM_Base_Start(&hRXTimer);
			start_flag = 1;
		}else{
			// Zeit zwischen Flanken messen
			ticks = TIM14->CNT;
			deltaTicks = ticks - ticks_last_edge;

			// Start Puls Erkennung
			if( (deltaTicks > 320) && (deltaTicks < 380) && !start_pulse_flag){
				start_pulse_flag = 1;
			}else if(!start_pulse_flag){		// if(deltaTicks > 500)
				// Fehler
				HAL_TIM_Base_Stop(&hRXTimer);
				TIM14->CNT = 0;
				buffer_index = 0;
				ticks_last_edge = 0;
				start_flag = 0;
				RX_Message_Complete = 0;
				start_pulse_flag = 0;
			}

			// Start Puls erkannt, Pulse einlesen
			if(start_pulse_flag){
				RX_Pulse_Buffer[buffer_index++] = deltaTicks;
				ticks_last_edge = ticks;
				if(buffer_index > 194){
					// IR Message Ende
					HAL_TIM_Base_Stop(&hRXTimer);
					TIM14->CNT = 0;
					buffer_index = 0;
					ticks_last_edge = 0;
					start_flag = 0;
					RX_Message_Complete = 1;
					start_pulse_flag = 0;
				}
			}
		}
	}
	//__enable_irq();
}
