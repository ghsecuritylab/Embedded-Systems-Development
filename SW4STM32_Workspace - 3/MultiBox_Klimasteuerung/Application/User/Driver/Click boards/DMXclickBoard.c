/**
  ******************************************************************************
  * @file    .c
  * @author  
  * @version V0.0.0
  * @date    

  * @brief   This file includes ... 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "DMXclickBoard.h"
#include "UART-Driver.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t DMX_Frame[DMX_FRAME_LENGTH] = {0};

/* Private function prototypes -----------------------------------------------*/

static void DMX_BreakPulse(void);
static void DMX_config_TX_Output(void);
static void DMX_config_TX_UART(void);

/* defined in "AdapterBoard_I2C_IOs.c" file */
extern void delayUS(uint32_t us);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Initialize the UART with 250kBaud
 * @param	None
 * @retval	None
 */
void DMX_init(void){
	UART_Init(DMX_BAUDRATE, UART_8N2);
}

/** uint32_t UART_Mode_t
 * @brief	Loop function which periodically sends the DMX frame
 * @param	None
 * @retval	None
 */
void DMX_loop(void){
	static uint32_t previousTicks = 0;
	uint32_t currentTicks = HAL_GetTick();
	if( (currentTicks - previousTicks) >= DMX_LOOP_TIME_MS){
		previousTicks = currentTicks;
		DMX_BreakPulse();
		UART_DMA_send(DMX_Frame, sizeof(DMX_Frame));
	}
}

/**
 * @brief  Sets a slot in the DMX-Frame to a specific value (without sending)
 * @param  uint16_t addr: DMX slot address
 * 		   uint8_t value: DMX slot value
 * @retval None
 */
void DMX_setSlot(uint16_t addr, uint8_t value){
	if(addr >= DMX_FRAME_LENGTH){
		return;
	}
	DMX_Frame[addr] = value;
}

/**
 * @brief  Configure the DMX pin as output
 * @param  None
 * @retval None
 */
static void DMX_config_TX_Output(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	/* Peripheral clock enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/**USART6 GPIO Configuration
	 PC7     ------> USART6_RX
	 PC6     ------> USART6_TX
	 */
	GPIO_InitStruct.Pin = UART6_TX_PIN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;	// GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(UART6_TX_PIN_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief  Configure the DMX pin with alternate function for UART
 * @param  None
 * @retval None
 */
static void DMX_config_TX_UART(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	/* Peripheral clock enable */
	__HAL_RCC_USART6_CLK_ENABLE();

	/**USART6 GPIO Configuration
	 PC7     ------> USART6_RX
	 PC6     ------> USART6_TX
	 */
	GPIO_InitStruct.Pin = UART6_TX_PIN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;	// GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(UART6_TX_PIN_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief  Pulls the DMX-Pin low for 176us (break pulse)
 * @param  None
 * @retval None
 */
static void DMX_BreakPulse(void){
	DMX_config_TX_Output();
	HAL_GPIO_WritePin(UART6_TX_PIN_GPIO_Port, UART6_TX_PIN_Pin, GPIO_PIN_RESET);
	/* 88us break pulse: logical 0 */
	delayUS(176);
	HAL_GPIO_WritePin(UART6_TX_PIN_GPIO_Port, UART6_TX_PIN_Pin, GPIO_PIN_SET);
	DMX_config_TX_UART();
	/* 8us mark pulse: logical 1 */
	delayUS(20);
}
