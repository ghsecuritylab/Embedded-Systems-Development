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
#ifndef __RTC_INTERNAL_H__
#define __RTC_INTERNAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"

extern void Firmware_ProcessLogic_ErrorHandler(uint8_t ErrorType);

/* Exported types ------------------------------------------------------------*/

// RTC Time structure definition
typedef struct{
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
}RTC_Time;

typedef enum{
	Sonntag = 1,
	Montag,
	Dienstag,
	Mittwoch,
	Donnerstag,
	Freitag,
	Samstag
}RTC_DayOfWeek;

char * RTC_DayOfWeekStings[7];

// RTC Date structure definition
typedef struct{
	RTC_DayOfWeek DayofWeek;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}RTC_Date;

// RTC Time & Date structure definition
typedef struct{
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
	RTC_DayOfWeek DayofWeek;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}RTC_TimeDate;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void RTC_Init(void);
void RTC_setTime(RTC_Time *sTime);
void RTC_setDate(RTC_Date *sDate);
void RTC_getTime(RTC_Time *sTime);
void RTC_getDate(RTC_Date *sDate);
void RTC_getTimeAsString(char *cTime);
void RTC_getDateAsString(char *cDate);
void RTC_setAlarm(RTC_Time *time, RTC_DayOfWeek dow);
void RTC_getWeekdayAsString(char *buf);
uint32_t RTC_getUnixTime(void);
void RTC_getUnixTimeBytes(uint8_t *bytes);


#ifdef __cplusplus
}
#endif

#endif /* __RTC_INTERNAL_H__ */
