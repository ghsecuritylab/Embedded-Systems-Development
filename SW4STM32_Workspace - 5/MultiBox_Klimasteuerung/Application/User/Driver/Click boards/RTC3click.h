/** \file	RTC3click Driver Header File
 *  \brief
 *
 *
 */

#ifndef __RTC3CLICK_H__
#define __RTC3CLICK_H__

/******************************************************************************
* Includes
*******************************************************************************/
#include "Clickboards_Conf.h"
#include "I2C-Driver.h"
#include "stdint.h"
#include "RTC_Internal.h"


struct clickBoard * RTC3_Current;

HAL_StatusTypeDef RTC3click_Init();
void RTC3click_Select(struct clickBoard * Board, uint8_t Addr);
void RTC3click_set(uint8_t channel, uint8_t Val);
uint8_t * RTC3click_get(uint8_t channel);

uint8_t 	RTC3click_setTime(RTC_Time *time);
uint8_t 	RTC3click_setDate(RTC_Date *date);
void 		RTC3click_getTime(RTC_Time *time);
void 		RTC3click_getDate(RTC_Date *date);
void 		RTC3click_getTimeAsString(char *buffer);
void 		RTC3click_getDateAsString(char *buffer);
uint8_t 	RTC3click_TimeCompare(RTC_Time *time1, RTC_Time *time2);
void 		RTC3click_getTimeDate(RTC_TimeDate *timeDate);
uint8_t 	RTC3click_TimeDateCompare(RTC_TimeDate *timeDate1, RTC_TimeDate *timeDate2);
void 		RTC3click_getWeekdayAsString(char *buf);

void 		RTC3click_SyncIntRTC(void);

uint32_t RTC3click_getUnixTime(void);
void RTC3click_getUnixTimeBytes(uint8_t *bytes);
uint32_t RTC3click_convTimeDateto_UnixTime(RTC_Time * time, RTC_Date * date);

#endif // __RTC3CLICK_H__
