/**
 ******************************************************************************
 * @file    STemWin/STemWin_HelloWorld/Src/stm32f7xx_it.c
 * @author  MCD Application Team
 * @version V1.0.3
 * @date    22-April-2016
 * @brief   Main Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"
#include "stm32f7xx_it.h"
#include "GUI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile GUI_TIMER_TIME OS_TimeMS;
extern LTDC_HandleTypeDef hltdc;
extern TIM_HandleTypeDef TimHandle;
extern I2C_HandleTypeDef I2cHandle;
extern CAN_HandleTypeDef CanHandle;
/* Timer Handle declared in "IRclick.c" file */
extern TIM_HandleTypeDef hPulseTimer;
/* RTC Hanlde declared in "RTC_Internal.c" file */
extern RTC_HandleTypeDef hrtc;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1) {
	}
}


/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
	/* Update the LocalTime by adding 1 ms each SysTick interrupt */
	HAL_IncTick();
	//HAL_SYSTICK_IRQHandler();

	OS_TimeMS++;
}

/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
 * @brief This function handles I2C1 event interrupt.
 */
void I2C1_EV_IRQHandler(void) {
	/* USER CODE BEGIN I2C1_EV_IRQn 0 */

	/* USER CODE END I2C1_EV_IRQn 0 */
	HAL_I2C_EV_IRQHandler(&I2cHandle);
	/* USER CODE BEGIN I2C1_EV_IRQn 1 */

	/* USER CODE END I2C1_EV_IRQn 1 */
}

/**
 * @brief This function handles I2C1 error interrupt.
 */
void I2C1_ER_IRQHandler(void) {
	/* USER CODE BEGIN I2C1_ER_IRQn 0 */

	/* USER CODE END I2C1_ER_IRQn 0 */
	HAL_I2C_ER_IRQHandler(&I2cHandle);
	/* USER CODE BEGIN I2C1_ER_IRQn 1 */

	/* USER CODE END I2C1_ER_IRQn 1 */
}

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

void CAN1_RX0_IRQHandler(void) {
	HAL_CAN_IRQHandler(&CanHandle);
	//__HAL_CAN_CLEAR_FLAG(&CanHandle,CAN_IT_FMP0);
}

/**
 * @brief  This function handles CAN1 TX interrupt request.
 * @param  None
 * @retval None
 */
void CAN1_TX_IRQHandler(void) {
	HAL_CAN_IRQHandler(&CanHandle);
}

/**
 * @brief  This function handles TIM interrupt request.
 * @param  None
 * @retval None
 */
void TIM3_IRQHandler(void) {
	HAL_TIM_IRQHandler(&TimHandle);
}

/**
 * @brief  This function handles LTDC global interrupt request.
 * @param  None
 * @retval None
 */
void LTDC_IRQHandler(void) {
	HAL_LTDC_IRQHandler(&hltdc);
}

/**
 * @brief This function handles TIM4 global interrupt.
 * @param  None
 * @retval None
 */
void TIM4_IRQHandler(void) {
	HAL_TIM_IRQHandler(&hPulseTimer);
}

/**
 * @brief  This function handles EXTI interrupt request.
 * @param  None
 * @retval None
 */
void EXTI15_10_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}

/**
 * @brief  This function handles RTC ALARM interrupt request.
 * @param  None
 * @retval None
 */
void RTC_Alarm_IRQHandler(void) {
	HAL_RTC_AlarmIRQHandler(&hrtc);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
