/**
 ******************************************************************************
 * @file    time_switch.c
 * @author  SKrull
 * @version V0.0.0
 * @date    02.03.2017

 * @brief   This file contains ...
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "time_switch.h"
#include "temperature_control.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TimeSwitch_Event TimeSwitch_EventList[EVENTLIST_ENTRIES_MAX];
uint8_t EventListEntryCount = 0;
uint8_t timeSwitch_SetTemperature = 20;

/* Private function prototypes -----------------------------------------------*/
//void sort_EventList(void);
static void timeSwitch_saveListInFlash(void);
static void swap_Events(TimeSwitch_Event *entry1, TimeSwitch_Event *entry2);
static void sort_EventList(void);
static void move_ToEndOfList(uint8_t index);

extern void Update_EventList(void);

/* defined in "Project_Page_1.c" file */
extern uint8_t SollVorgabe;

/* Parameter Pointer Array saving the TimeSwitchList */
struct Parameter *ParameterEventList[] = {
		&ListEntry0_Day,
		&ListEntry0_Hour,
		&ListEntry0_Minutes,
		&ListEntry0_Temperature,
		&ListEntry0_Repeat,
		&ListEntry1_Day,
		&ListEntry1_Hour,
		&ListEntry1_Minutes,
		&ListEntry1_Temperature,
		&ListEntry1_Repeat,
		&ListEntry2_Day,
		&ListEntry2_Hour,
		&ListEntry2_Minutes,
		&ListEntry2_Temperature,
		&ListEntry2_Repeat,
		&ListEntry3_Day,
		&ListEntry3_Hour,
		&ListEntry3_Minutes,
		&ListEntry3_Temperature,
		&ListEntry3_Repeat,
		&ListEntry4_Day,
		&ListEntry4_Hour,
		&ListEntry4_Minutes,
		&ListEntry4_Temperature,
		&ListEntry4_Repeat,
		&ListEntry5_Day,
		&ListEntry5_Hour,
		&ListEntry5_Minutes,
		&ListEntry5_Temperature,
		&ListEntry5_Repeat,
		&ListEntry6_Day,
		&ListEntry6_Hour,
		&ListEntry6_Minutes,
		&ListEntry6_Temperature,
		&ListEntry6_Repeat,
		&ListEntry7_Day,
		&ListEntry7_Hour,
		&ListEntry7_Minutes,
		&ListEntry7_Temperature,
		&ListEntry7_Repeat,
		&ListEntry8_Day,
		&ListEntry8_Hour,
		&ListEntry8_Minutes,
		&ListEntry8_Temperature,
		&ListEntry8_Repeat,
		&ListEntry9_Day,
		&ListEntry9_Hour,
		&ListEntry9_Minutes,
		&ListEntry9_Temperature,
		&ListEntry9_Repeat,
};

/* Private functions ---------------------------------------------------------*/

static void timeSwitch_saveListInFlash(void) {
	ParameterWrite((&ListEntryCount),Value, EventListEntryCount);

	for(int i = 0; i < EventListEntryCount; i++){
		ParameterWrite((ParameterEventList[i*5]),Value, TimeSwitch_EventList[i].startDay);
		ParameterWrite((ParameterEventList[i*5+1]),Value, TimeSwitch_EventList[i].startTime.Hours);
		ParameterWrite((ParameterEventList[i*5+2]),Value, TimeSwitch_EventList[i].startTime.Minutes);
		ParameterWrite((ParameterEventList[i*5+3]),Value, TimeSwitch_EventList[i].Temperature);
		ParameterWrite((ParameterEventList[i*5+4]),Value, TimeSwitch_EventList[i].Repeat);
	}

	ParameterChange_Handled = 0;
}

/**
 * @brief
 * @param
 * @retval
 */
void timeSwitch_setNewEntry(TimeSwitch_Event *event) {
	TimeSwitch_EventList[EventListEntryCount].ID = event->ID;
	TimeSwitch_EventList[EventListEntryCount].startTime.Hours =
			event->startTime.Hours;
	TimeSwitch_EventList[EventListEntryCount].startTime.Minutes =
			event->startTime.Minutes;
	TimeSwitch_EventList[EventListEntryCount].startDay = event->startDay;
	TimeSwitch_EventList[EventListEntryCount].Repeat = event->Repeat;
	TimeSwitch_EventList[EventListEntryCount].Temperature = event->Temperature;
	//TimeSwitch_EventList[EventListEntryCount].cb_fp = event->cb_fp;
	EventListEntryCount++;
	sort_EventList();
	timeSwitch_saveListInFlash();
}

/**
 * @brief
 * @param
 * @retval
 */
void timeSwitch_checkEvents(void) {
	RTC_Date actualDate;
	RTC_Time actualTime;

	RTC_getTime(&actualTime);
	RTC_getDate(&actualDate);

	if (EventListEntryCount > 0) {

		/* Check for Weekday match */
		if (TimeSwitch_EventList[0].startDay == actualDate.DayofWeek) {
			/* Check for Hour match*/
			if (TimeSwitch_EventList[0].startTime.Hours == actualTime.Hours) {
				/* Check for Minutes match*/
				if (TimeSwitch_EventList[0].startTime.Minutes
						== actualTime.Minutes) {
					/* Only if Seconds are 0 */
					if (actualTime.Seconds == 0) {
						/* Check if the event is repeating */
						if (TimeSwitch_EventList[0].Repeat) {
							timeSwitch_SetTemperature =
									TimeSwitch_EventList[0].Temperature;
							temperatureControl_setSoll(
									(float) timeSwitch_SetTemperature);
							//SollVorgabe = timeSwitch_SetTemperature;
							//timeSwitch_SetTemperature += 1;
							move_ToEndOfList(0);
							timeSwitch_saveListInFlash();
						} else {
							timeSwitch_SetTemperature =
									TimeSwitch_EventList[0].Temperature;
							temperatureControl_setSoll(
									(float) timeSwitch_SetTemperature);
							//SollVorgabe = timeSwitch_SetTemperature;
							//timeSwitch_SetTemperature += 1;
							if(EventListEntryCount > 0){
								timeSwitch_delete_Event(0);
							}
							//sort_EventList();
							Update_EventList();
							timeSwitch_saveListInFlash();
						}
					}
				}
			}

		}
	}
}

/**
 * @brief
 * @param
 * @retval
 */
static void sort_EventList(void) {
	int8_t sortingList[EventListEntryCount];

	RTC_Date actualDate;
	RTC_Time actualTime;

	RTC_getTime(&actualTime);
	RTC_getDate(&actualDate);

	/* create sorting list by days */
	for (uint8_t idx = 0; idx < EventListEntryCount; idx++) {
		sortingList[idx] = TimeSwitch_EventList[idx].startDay
				- actualDate.DayofWeek;
		/* day is in the past */
		if (sortingList[idx] < 0) {
			sortingList[idx] += 7;
		}

		/* if days are equal and time is in the past, move entry to the end of list */
		if (TimeSwitch_EventList[idx].startDay == actualDate.DayofWeek) {
			if (TimeSwitch_EventList[idx].startTime.Hours == actualTime.Hours) {
				if (TimeSwitch_EventList[idx].startTime.Minutes
						< actualTime.Minutes) {
					sortingList[idx] = 6;
				}
			} else if (TimeSwitch_EventList[idx].startTime.Hours
					< actualTime.Hours) {
				sortingList[idx] = 6;
			}
		}
	}

	/* sort by days with sorting list */
	uint8_t index = 0;
	for (uint8_t k = 0; k < 7; k++) {
		for (uint8_t idx = 0; idx < EventListEntryCount; idx++) {
			if (sortingList[idx] == k) {
				swap_Events(&TimeSwitch_EventList[idx],
						&TimeSwitch_EventList[index]);
				uint8_t temp = sortingList[idx];
				sortingList[idx] = sortingList[index];
				sortingList[index] = temp;
				index += 1;
			}
		}
	}

	uint8_t sorted = 1;
	uint8_t idx = 0;
	/* if days are equal sort by Hours and Minutes (Bubble Sort) */
	do {
		sorted = 1;
		idx = 0;
		do {
			/* if days are equal check time and sort by time */
			if (TimeSwitch_EventList[idx].startDay
					== TimeSwitch_EventList[idx + 1].startDay) {
				/* if hours are equal check Minutes and sort by Minutes */
				if (TimeSwitch_EventList[idx].startTime.Hours
						== TimeSwitch_EventList[idx + 1].startTime.Hours) {
					if (TimeSwitch_EventList[idx].startTime.Minutes
							> TimeSwitch_EventList[idx + 1].startTime.Minutes) {
						swap_Events(&TimeSwitch_EventList[idx],
								&TimeSwitch_EventList[idx + 1]);
						sorted = 0;
					}
				} else if (TimeSwitch_EventList[idx].startTime.Hours
						> TimeSwitch_EventList[idx + 1].startTime.Hours) {
					swap_Events(&TimeSwitch_EventList[idx],
							&TimeSwitch_EventList[idx + 1]);
					sorted = 0;
				}
			}
			idx++;
		} while (idx < (EventListEntryCount - 1));
	} while (!sorted);

	move_ToEndOfList(0);

	Update_EventList();
}

/**
 * @brief
 * @param
 * @retval
 */
static void move_ToEndOfList(uint8_t index) {
	RTC_Date actualDate;
	RTC_Time actualTime;

	RTC_getTime(&actualTime);
	RTC_getDate(&actualDate);

	/* Move entry to the end of the list */
	if (EventListEntryCount > 1) {
		if (TimeSwitch_EventList[index].Repeat) {
			if (TimeSwitch_EventList[index].startDay == actualDate.DayofWeek) {
				if (TimeSwitch_EventList[index].startTime.Hours
						== actualTime.Hours) {
					if (TimeSwitch_EventList[index].startTime.Minutes
							<= actualTime.Minutes) {
						for (int i = 0; i < ((EventListEntryCount - index) - 1);
								i++) {
							swap_Events(&TimeSwitch_EventList[i],
									&TimeSwitch_EventList[i + 1]);
						}
					}
				}
			}
		}
	}
	Update_EventList();
}

/**
 * @brief
 * @param
 * @retval
 */
static void swap_Events(TimeSwitch_Event *entry1, TimeSwitch_Event *entry2) {
	TimeSwitch_Event temp;

	temp.startDay = entry1->startDay;
	temp.startTime.Hours = entry1->startTime.Hours;
	temp.startTime.Minutes = entry1->startTime.Minutes;
	temp.Temperature = entry1->Temperature;
	temp.Repeat = entry1->Repeat;

	entry1->startDay = entry2->startDay;
	entry1->startTime.Hours = entry2->startTime.Hours;
	entry1->startTime.Minutes = entry2->startTime.Minutes;
	entry1->Temperature = entry2->Temperature;
	entry1->Repeat = entry2->Repeat;

	entry2->startDay = temp.startDay;
	entry2->startTime.Hours = temp.startTime.Hours;
	entry2->startTime.Minutes = temp.startTime.Minutes;
	entry2->Temperature = temp.Temperature;
	entry2->Repeat = temp.Repeat;
}

/**
 * @brief
 * @param
 * @retval
 */
void timeSwitch_delete_Event(uint8_t index) {
	for (uint8_t idx = index; idx < (EventListEntryCount - 1); idx++) {
		TimeSwitch_EventList[idx].startDay =
				TimeSwitch_EventList[idx + 1].startDay;
		TimeSwitch_EventList[idx].startTime.Hours =
				TimeSwitch_EventList[idx + 1].startTime.Hours;
		TimeSwitch_EventList[idx].startTime.Minutes = TimeSwitch_EventList[idx
				+ 1].startTime.Minutes;
		TimeSwitch_EventList[idx].Temperature =
				TimeSwitch_EventList[idx + 1].Temperature;
		TimeSwitch_EventList[idx].Repeat = TimeSwitch_EventList[idx + 1].Repeat;
	}
	EventListEntryCount -= 1;
	timeSwitch_saveListInFlash();
}

/**
 * @brief
 * @param
 * @retval
 */
void timeSwitch_initTestTable(void) {

	RTC_Date actualDate;
	RTC_Time actualTime;

	RTC_getTime(&actualTime);
	RTC_getDate(&actualDate);

	TimeSwitch_EventList[0].startDay = actualDate.DayofWeek;
	TimeSwitch_EventList[0].startTime.Hours = actualTime.Hours;
	TimeSwitch_EventList[0].startTime.Minutes = (actualTime.Minutes + 1) % 60;
	TimeSwitch_EventList[0].Temperature = 26.0;
	TimeSwitch_EventList[0].Repeat = 0;
	TimeSwitch_EventList[0].ID = 0;

//	TimeSwitch_EventList[1].startDay = actualDate.DayofWeek;
//	TimeSwitch_EventList[1].startTime.Hours = actualTime.Hours;
//	TimeSwitch_EventList[1].startTime.Minutes = actualTime.Minutes + 4;
//	TimeSwitch_EventList[1].Temperature = 24.0;
//	TimeSwitch_EventList[1].Repeat = 0;
//	TimeSwitch_EventList[1].ID = 1;
//
//	TimeSwitch_EventList[2].startDay = actualDate.DayofWeek;
//	TimeSwitch_EventList[2].startTime.Hours = actualTime.Hours;
//	TimeSwitch_EventList[2].startTime.Minutes = actualTime.Minutes + 5;
//	TimeSwitch_EventList[2].Temperature = 25.0;
//	TimeSwitch_EventList[2].Repeat = 1;
//	TimeSwitch_EventList[2].ID = 2;
//
//	TimeSwitch_EventList[3].startDay = actualDate.DayofWeek;
//	TimeSwitch_EventList[3].startTime.Hours = actualTime.Hours;
//	TimeSwitch_EventList[3].startTime.Minutes = actualTime.Minutes + 3;
//	TimeSwitch_EventList[3].Temperature = 23.0;
//	TimeSwitch_EventList[3].Repeat = 0;
//	TimeSwitch_EventList[3].ID = 3;
//
//	TimeSwitch_EventList[4].startDay = actualDate.DayofWeek;
//	TimeSwitch_EventList[4].startTime.Hours = actualTime.Hours;
//	TimeSwitch_EventList[4].startTime.Minutes = actualTime.Minutes + 1;
//	TimeSwitch_EventList[4].Temperature = 21.0;
//	TimeSwitch_EventList[4].Repeat = 0;
//	TimeSwitch_EventList[4].ID = 4;
//
//	TimeSwitch_EventList[5].startDay = actualDate.DayofWeek;
//	TimeSwitch_EventList[5].startTime.Hours = actualTime.Hours;
//	TimeSwitch_EventList[5].startTime.Minutes = actualTime.Minutes + 2;
//	TimeSwitch_EventList[5].Temperature = 22.0;
//	TimeSwitch_EventList[5].Repeat = 1;
//	TimeSwitch_EventList[5].ID = 5;

	EventListEntryCount = 1;

	sort_EventList();
	Update_EventList();
}
