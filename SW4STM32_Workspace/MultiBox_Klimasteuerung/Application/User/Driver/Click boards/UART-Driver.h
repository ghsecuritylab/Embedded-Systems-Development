/**
  ******************************************************************************
  * @file    UART_ST-Link.h
  * @author  
  * @version V0.0.0
  * @date    

  * @brief   This file contains ...
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/

typedef enum{
	UART_8N1,
	UART_8N2
}UART_Mode_t;

// Endekennung beim Senden
typedef enum {
  NONE = 0,  // keine Endekennung
  LFCR,      // LineFeed + CarriageReturn (0x0A,0x0D)
  CRLF,      // CarriageReturn + LineFeed (0x0D,0x0A)
  LF,        // nur LineFeed (0x0A)
  CR         // nur CarriageReturn (0x0D)
}UART_LASTBYTE_t;

// Status beim Empfangen
typedef enum {
  RX_EMPTY = 0,  // nichts empfangen
  RX_READY,      // es steht was im Empfangspuffer
  RX_FULL        // RX-Puffer ist voll
}UART_RXSTATUS_t;

/* Exported constants --------------------------------------------------------*/

#define RXBUFFERSIZE            32
#define TXBUFFERSIZE            80

/* UART1 connected to ST-Link Virtual COM Port */
#define UART1_RX_PIN_Pin 		GPIO_PIN_7
#define UART1_RX_PIN_GPIO_Port 	GPIOB
#define UART1_TX_PIN_Pin 		GPIO_PIN_9
#define UART1_TX_PIN_GPIO_Port 	GPIOA

/* UART6 on D0/D1 at Arduino UNO Connector */
#define UART6_RX_PIN_Pin 		GPIO_PIN_7
#define UART6_RX_PIN_GPIO_Port 	GPIOC
#define UART6_TX_PIN_Pin 		GPIO_PIN_6
#define UART6_TX_PIN_GPIO_Port 	GPIOC

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void 	Dbg_Init(uint32_t baudrate, UART_Mode_t mode);	// Dbg_Init(115200, UART_8N1);
uint8_t Dbg_print(char *format, ...);
uint8_t Dbg_println(char *format, ...);
void _Error_Handler(char * file, int line);	 // _Error_Handler(__FILE__, __LINE__);

void 	UART_Init(uint32_t baudrate, UART_Mode_t mode);
void 	UART_send(uint8_t *buffer, uint16_t size);
void 	UART_DMA_send(uint8_t *buffer, uint16_t size);
HAL_StatusTypeDef UART_startReceive(uint8_t *data, uint8_t size);
uint8_t UART_RxCplt(void);

#ifdef __cplusplus
}
#endif

#endif /* __UART_DRIVER_H__ */
