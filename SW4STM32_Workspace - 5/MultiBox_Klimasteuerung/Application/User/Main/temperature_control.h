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
#ifndef __TEMPERATURE_CONTROL_H__
#define __TEMPERATURE_CONTROL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
enum fsm_states {Start, Standby, Ready, Heating, RapidHeating, Cooling, Hold, Error};

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void temperatureControl_evalEvents(void);
void temperatureControl_evalState(void);

extern void temperatureControl_setSoll(float sollT);
void temperatureControl_setIst(float *pIstT);

uint8_t temperatureControl_getMode(void);

extern float *pTC_IstTemperature;
extern float TC_SollTemperature;

#ifdef __cplusplus
}
#endif

#endif /* __TEMPERATURE_CONTROL_H__ */
