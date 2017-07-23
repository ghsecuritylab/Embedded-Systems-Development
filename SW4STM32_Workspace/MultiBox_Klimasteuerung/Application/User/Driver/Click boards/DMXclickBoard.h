/**
  ******************************************************************************
  * @file    .h
  * @author  
  * @version V0.0.0
  * @date    

  * @brief   This file contains ...
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMXCLICKBOARD_H
#define __DMXCLICKBOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Defines -------------------------------------------------------------------*/
#define DMX_FRAME_LENGTH	513		// max. 513 slots, start slot + 512
#define DMX_LOOP_TIME_MS	50		// DMX frame rate in milliseconds
#define DMX_BAUDRATE	250000	// 250 kbps

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t DMX_Frame[DMX_FRAME_LENGTH];

/* Exported functions ------------------------------------------------------- */
void DMX_init(void);							// Initialize the UART module to 250 Kbaud 8N2
void DMX_loop(void);							// insert in main-loop, sends periodically the dmx frame
void DMX_setSlot(uint16_t addr, uint8_t value);	// change DMX frame


#ifdef __cplusplus
}
#endif

#endif /* __DMXCLICKBOARD_H */
