/**
  ******************************************************************************
  * @file    time_switch.h
  * @author  SKrull
  * @version V0.0.0
  * @date    02.03.2017

  * @brief   This file includes time switch functions for Temperatur Control
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APPLICATION_USER_MAIN_TIME_SWITCH_H_
#define APPLICATION_USER_MAIN_TIME_SWITCH_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "RTC_Internal.h"
#include "RTC3click.h"

#define EVENTLIST_ENTRIES_MAX	10

/* Exported types ------------------------------------------------------------*/
typedef struct{
	uint8_t 		ID;				// entry ID
	RTC_Time 		startTime;		// Triggertime
	RTC_DayOfWeek 	startDay;		// Triggerweekday
	float 			Temperature;	// Temperture Setting
	uint8_t 		Repeat;			// Repeating event: 0 = one time execution, 1 = repeated execution (Weekly)
	//void 			(*cb_fp)(void);	// Callback function pointer
}TimeSwitch_Event;

/* Exported constants --------------------------------------------------------*/
extern TimeSwitch_Event TimeSwitch_EventList[EVENTLIST_ENTRIES_MAX];
extern uint8_t EventListEntryCount;
extern uint8_t timeSwitch_SetTemperature;
extern struct Parameter *ParameterEventList[];

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void timeSwitch_setNewEntry(TimeSwitch_Event *event);
void timeSwitch_checkEvents(void);

void timeSwitch_initTestTable(void);
void timeSwitch_delete_Event(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_MAIN_TIME_SWITCH_H_ */
