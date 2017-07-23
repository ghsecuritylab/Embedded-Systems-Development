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
#include "UART-Driver.h"
#include "stdarg.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define ASCII_BS	0x7F	// back space
#define ASCII_TAB	0x09
#define ASCII_LF	0x0A	// line feed, new line (\n)
#define ASCII_CR	0x0D	// carriage return (\r)
#define ASCII_ESC	0x1B

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1, huart6;
DMA_HandleTypeDef hdma_usart1_tx, hdma_usart6_tx;

__IO uint8_t UART1_busy = 0, UART6_busy = 0;
__IO ITStatus Uart1RxReady = RESET, Uart6RxReady = RESET;
uint8_t aTxBuffer[TXBUFFERSIZE];
__IO uint8_t buf1Index = 0, buf6Index = 0;
__IO uint8_t cChar1, cChar6;

/* Private function prototypes -----------------------------------------------*/

static void USART1_GPIO_Init(void);
static void USART1_DMA_Init(void);
static void USART6_GPIO_Init(void);
static void USART6_DMA_Init(void);
static void UART_Config(UART_HandleTypeDef *huart, uint8_t uart_num, uint32_t baudrate, UART_Mode_t mode);
static void UART_putc(char ch);

void DMA2_Stream7_IRQHandler(void);
void USART1_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void USART6_IRQHandler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Initialize the UART
 * @param	uint32_t baudrate: UART Baudrate
 * @retval
 */
void Dbg_Init(uint32_t baudrate, UART_Mode_t mode) {
	USART1_GPIO_Init();
	UART_Config(&huart1, 1, baudrate, mode);
	USART1_DMA_Init();

	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	//HAL_UART_Receive_IT(&huart1, (uint8_t *) &cChar1, 1);
}

/**
 * @brief	Sends data over UART in non-blocking mode
 * @param	uint8_t *buffer: uint8_t array with data
 * 		    uint16_t size: size of data array
 * @retval	None
 */
uint8_t Dbg_print(char *format, ...) {

	va_list arg;

	while (UART1_busy) {
	}

	va_start(arg, format);
	vsprintf((char *) aTxBuffer, format, arg);
	va_end(arg);

	uint16_t size = strlen((char *) aTxBuffer);

	HAL_UART_Transmit_DMA(&huart1, aTxBuffer, size);
	UART1_busy = 1;

	return 0;

}

/**
 * @brief	Sends data over UART in non-blocking mode
 * @param	uint8_t *buffer: uint8_t array with data
 * 		    uint16_t size: size of data array
 * @retval	None
 */
uint8_t Dbg_println(char *format, ...) {

	va_list arg;

	while (UART1_busy) {
	}

	va_start(arg, format);
	vsprintf((char *) aTxBuffer, format, arg);
	va_end(arg);

	uint16_t size = strlen((char *) aTxBuffer);
	aTxBuffer[size++] = '\r';
	aTxBuffer[size++] = '\n';
	aTxBuffer[size] = '\0';

	HAL_UART_Transmit_DMA(&huart1, aTxBuffer, size);
	UART1_busy = 1;

	return 0;

}

/**
 * @brief	Initialize the UART
 * @param	uint32_t baudrate: UART Baudrate i.e. 9600
 * 			UART_Mode_t mode: UART Mode i.e. UART_8N1
 * @retval
 */
void UART_Init(uint32_t baudrate, UART_Mode_t mode) {
	USART6_GPIO_Init();
	UART_Config(&huart6, 6, baudrate, mode);
	USART6_DMA_Init();

	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(USART6_IRQn);

	//HAL_UART_Receive_IT(&huart6, (uint8_t *) &cChar6, 1);
}

/**
 * @brief	Sends data over UART in blocking mode
 * @param	uint8_t *buffer: uint8_t array with data
 * 		    uint16_t size: size of data array
 * @retval	None
 */
void UART_send(uint8_t *buffer, uint16_t size) {
	//uint16_t size = strlen((char *)buffer);
	HAL_UART_Transmit(&huart6, buffer, size, 1000);
}

/**
 * @brief	Sends data over UART in non-blocking mode
 * @param	uint8_t *buffer: uint8_t array with data
 * 		    uint16_t size: size of data array
 * @retval	None
 */
void UART_DMA_send(uint8_t *buffer, uint16_t size) {

	while(UART6_busy){

	}

	//uint16_t size = strlen((char *)buffer);
	HAL_UART_Transmit_DMA(&huart6, buffer, size);
	UART6_busy = 1;

}


uint8_t UART_RxCplt(void){
	return Uart6RxReady;
}

/**
 * @brief	Receive in blocking-mode
 * @param
 * @retval
 */
HAL_StatusTypeDef UART_startReceive(uint8_t *data, uint8_t size){
	Uart6RxReady = RESET;
	return HAL_UART_Receive_IT(&huart6, data, size);
	//return HAL_UART_Receive(&huart6, data, size, 1000);
}

/**
 * @brief	Transmit Complete Callback
 * @param	UART_HandleTypeDef *huart: UART Handle
 * @retval	None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART1){
		UART1_busy = 0;
	}
	else if(huart->Instance == USART6){
		UART6_busy = 0;
	}
}

/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if(huart->Instance == USART1){
		Uart1RxReady = SET;
	}
	else if(huart->Instance == USART6){
		Uart6RxReady = SET;
	}

//	/* Set transmission flag: trasfer complete*/
//	UART_putc(cChar);
//	if(cChar == ASCII_CR || cChar == ASCII_LF){
//		UartRxReady = SET;
//		bufIndex = 0;
//	}else if(cChar == ASCII_BS){
//		if(bufIndex >= 1){
//			bufIndex--;
//		}
//	}else{
//		aRxBuffer[bufIndex++] = cChar;
//	}
//
//	if(HAL_UART_Receive_IT(&huart1, (uint8_t *)&cChar, 1) != HAL_OK){
//		//Error_Handler();
//	}
}

/**
 * @brief	USART6 init function
 * @param	uint32_t baudrate
 * 		    UART_Mode_t mode
 * @retval	None
 */
static void UART_Config(UART_HandleTypeDef *huart, uint8_t uart_num, uint32_t baudrate, UART_Mode_t mode) {

	if(uart_num == 1){
		huart->Instance = USART1;
	}else if(uart_num == 6){
		huart->Instance = USART6;
	}

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	huart->Init.BaudRate = baudrate;

	switch (mode) {
	case UART_8N1:
		huart->Init.WordLength = UART_WORDLENGTH_8B;
		huart->Init.StopBits = UART_STOPBITS_1;
		huart->Init.Parity = UART_PARITY_NONE;
		break;
	case UART_8N2:
		huart->Init.WordLength = UART_WORDLENGTH_8B;
		huart->Init.StopBits = UART_STOPBITS_2;
		huart->Init.Parity = UART_PARITY_NONE;
		break;
	default:
		huart->Init.WordLength = UART_WORDLENGTH_8B;
		huart->Init.StopBits = UART_STOPBITS_1;
		huart->Init.Parity = UART_PARITY_NONE;
		break;
	}

	huart->Init.Mode = UART_MODE_TX_RX;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.OverSampling = UART_OVERSAMPLING_16;
	huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(huart) != HAL_OK) {
		while (1) {

		}
	}

}

/**
 * Enable DMA controller clock
 */
static void USART1_DMA_Init(void) {
	/* DMA2_Stream7_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}

/**
 * Enable DMA controller clock
 */
static void USART6_DMA_Init(void) {
	/* TX DMA2_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

/** Pinout Configuration
 */
static void USART1_GPIO_Init(void) {
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

/** Pinout Configuration
 */
static void USART6_GPIO_Init(void) {
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
}

/**
 * @brief
 * @param
 * @retval
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart) {

	if (huart->Instance == USART1) {

		GPIO_InitTypeDef GPIO_InitStruct;
		/* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE()
		;

		/**USART6 GPIO Configuration
		 PB7     ------> USART1_RX
		 PA9     ------> USART1_TX
		 */
		GPIO_InitStruct.Pin = UART1_TX_PIN_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;	// GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = UART1_RX_PIN_Pin;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART1 DMA Init */
		/* USART1_TX Init */
		hdma_usart1_tx.Instance = DMA2_Stream7;
		hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_tx.Init.Mode = DMA_NORMAL;
		hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK) {
			//_Error_Handler(__FILE__, __LINE__);
		}
		__HAL_LINKDMA(huart, hdmatx, hdma_usart1_tx);
	}

	if (huart->Instance == USART6) {
		GPIO_InitTypeDef GPIO_InitStruct;
		/* Peripheral clock enable */
		__HAL_RCC_USART6_CLK_ENABLE()
		;

		/**USART6 GPIO Configuration
		 PC7     ------> USART6_RX
		 PC6     ------> USART6_TX
		 */
		GPIO_InitStruct.Pin = UART6_RX_PIN_Pin | UART6_TX_PIN_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;	// GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* Peripheral DMA init for TX */
		hdma_usart6_tx.Instance = DMA2_Stream6;
		hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
		hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart6_tx.Init.Mode = DMA_NORMAL;
		hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_usart6_tx);
		__HAL_LINKDMA(&huart6, hdmatx, hdma_usart6_tx);
	}
}

/**
 * @brief
 * @param
 * @retval
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {

	if (huart->Instance == USART1) {

		__USART1_FORCE_RESET();
		__USART1_RELEASE_RESET();

		/**USART6 GPIO Configuration
		 PB7     ------> USART6_RX
		 PA9     ------> USART6_TX
		 */
		HAL_GPIO_DeInit(GPIOA, UART1_TX_PIN_Pin);
		HAL_GPIO_DeInit(GPIOB, UART1_RX_PIN_Pin);

		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/* Peripheral DMA DeInit*/
		HAL_DMA_DeInit(huart->hdmatx);

		/* Peripheral interrupt DeInit*/
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		HAL_NVIC_DisableIRQ(DMA2_Stream7_IRQn);
	}
	if (huart->Instance == USART6) {

		__USART6_FORCE_RESET();
		__USART6_RELEASE_RESET();

		/**USART6 GPIO Configuration
		 PC7     ------> USART6_RX
		 PC6     ------> USART6_TX
		 */
		HAL_GPIO_DeInit(GPIOC, UART6_RX_PIN_Pin | UART6_TX_PIN_Pin);

		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/* Peripheral DMA DeInit*/
		HAL_DMA_DeInit(huart->hdmatx);

		/* Peripheral interrupt DeInit*/
		HAL_NVIC_DisableIRQ(USART6_IRQn);

		HAL_NVIC_DisableIRQ(DMA2_Stream6_IRQn);
	}
}


/**
 * @brief This function handles DMA2 stream7 global interrupt.
 */
void DMA2_Stream7_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_usart1_tx);
}

/**
 * @brief This function handles DMA2 stream6 global interrupt.
 */
void DMA2_Stream6_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_usart6_tx); // &hdma_usart6_tx);
}

/**
 * @brief This function handles USART6 global interrupt.
 */
void USART1_IRQHandler(void) {
	HAL_UART_IRQHandler(&huart1);
}

/**
 * @brief This function handles USART6 global interrupt.
 */
void USART6_IRQHandler(void) {
	HAL_UART_IRQHandler(&huart6);
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
int __io_putchar(int ch) {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	while (HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xFFFF) != HAL_OK) {
	}
	return ch;
}

/**
 * @brief
 * @param
 * @retval
 */
static void UART_putc(char ch) {
	while (HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xFFFF) != HAL_OK) {
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char * file, int line) {
	/* User can add his own implementation to report the HAL error return state */
#ifdef DEBUG
	Dbg_println("Error in file \"%s\" in line %d.", file, line);
#endif
	while (1) {
	}
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  assert_failed
 *         Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  File: pointer to the source file name
 * @param  Line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line
	 number,ex: printf("Wrong parameters value: file %s on line %d\r\n",
	 file, line) */
	Dbg_println("Assert failed in file \"%s\" in line %d.", file, line);

	/* Infinite loop */
	while (1)
	{}
}

#endif
