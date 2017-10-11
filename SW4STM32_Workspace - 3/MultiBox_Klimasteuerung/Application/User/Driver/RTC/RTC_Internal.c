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
#include "RTC_Internal.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define BCD2BIN(val) ( ( ( val ) & 15 ) + ( ( val ) >> 4 ) * 10 )
#define BIN2BCD(val) ( ( ( ( val ) / 10 ) << 4 ) + ( val ) % 10 )

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

char * RTC_DayOfWeekStings[] = {
		"Sonntag",
		"Montag",
		"Dienstag",
		"Mittwoch",
		"Donnerstag",
		"Freitag",
		"Samstag"
};

/* Anzahl der Tage seit Jahresanfang ohne Tage des aktuellen Monats und ohne Schalttag */
const short tage_seit_jahresanfang[12] =
    {0,31,59,90,120,151,181,212,243,273,304,334};

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  RTC init function
 * @param
 * @retval
 */
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc) {
	if (hrtc->Instance == RTC) {
		/* Peripheral clock enable */
		__HAL_RCC_RTC_ENABLE();
	}
}

/**
 * @brief  	RTC init function
 * @param	Pointer to RTC Handle
 * @retval	None
 */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc) {
	if (hrtc->Instance == RTC) {
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();
	}
}

/**
 * @brief  RTC init function
 * @param  None
 * @retval None
 */
void RTC_Init(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	/* Configue LSE as RTC clock soucre */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK) {
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) == HAL_OK) {
			/* Enable RTC Clock */
			__HAL_RCC_RTC_ENABLE();

			/**Initialize RTC Only
			 */
			hrtc.Instance = RTC;
			hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
			hrtc.Init.AsynchPrediv = 127;
			hrtc.Init.SynchPrediv = 255;
			hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
			hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
			hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
			if (HAL_RTC_Init(&hrtc) != HAL_OK) {
				Firmware_ProcessLogic_ErrorHandler(0);
			}
		}
	}

//	RTC_AlarmTypeDef sAlarm;
//	/**Enable the Alarm A
//	 */
//	sAlarm.AlarmTime.Hours = 0x0;
//	sAlarm.AlarmTime.Minutes = 0x0;
//	sAlarm.AlarmTime.Seconds = 0x0;
//	sAlarm.AlarmTime.SubSeconds = 0x0;
//	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
//	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
//	sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
//	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
//	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
//	sAlarm.AlarmDateWeekDay = 0x1;
//	sAlarm.Alarm = RTC_ALARM_A;
//	if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK) {
//		Firmware_ProcessLogic_ErrorHandler(0);
//	}
//
//	/**Enable the Alarm B
//	 */
//	sAlarm.AlarmDateWeekDay = 0x1;
//	sAlarm.Alarm = RTC_ALARM_B;
//	if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK) {
//		Firmware_ProcessLogic_ErrorHandler(0);
//	}

}

/**
 * @brief  	Sets the time
 * @param	Pointer to RTC_TimeTypeDef struct
 * @retval	None
 */
void RTC_setTime(RTC_Time *time) {

	RTC_TimeTypeDef sTime;
	/* Initialize RTC and set the Time and Date */
	sTime.Hours = time->Hours;
	sTime.Minutes = time->Minutes;
	sTime.Seconds = time->Seconds;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}
}

/**
 * @brief  	Sets the date
 * @param	Pointer to RTC_DateTypeDef struct
 * @retval	None
 */
void RTC_setDate(RTC_Date *date) {

	RTC_DateTypeDef sDate;

	if(date->DayofWeek == Sonntag){
		sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
	}else{
		sDate.WeekDay = date->DayofWeek - 1;
	}

	sDate.Month = date->Month;
	sDate.Date = date->Date;
	sDate.Year = date->Year;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}
}

/**
 * @brief  	Get the time
 * @param	Pointer to RTC_TimeTypeDef struct
 * @retval	None
 */
void RTC_getTime(RTC_Time *time) {
	RTC_TimeTypeDef sTime;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}
	time->Hours = sTime.Hours;
	time->Minutes = sTime.Minutes;
	time->Seconds = sTime.Seconds;
}

/**
 * @brief  	Get the date
 * @param	Pointer to RTC_DateTypeDef struct
 * @retval	None
 */
void RTC_getDate(RTC_Date *date) {
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}

	if(sDate.WeekDay == RTC_WEEKDAY_SUNDAY){
		date->DayofWeek = Sonntag;
	}else{
		date->DayofWeek = sDate.WeekDay + 1;
	}
	date->Date = sDate.Date;
	date->Month = sDate.Month;
	date->Year = sDate.Year;
}

/**
 * @brief	Get the time as string
 * @param	char array
 * @retval	None
 */
void RTC_getTimeAsString(char *cTime) {
	RTC_TimeTypeDef sTime;

	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}

	sprintf(cTime, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
}

/**
 * @brief	Get the date as string
 * @param	char array
 * @retval	None
 */
void RTC_getDateAsString(char *cDate) {
	RTC_DateTypeDef sDate;

	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}

	sprintf(cDate, "%02d.%02d.%02d", sDate.Date, sDate.Month,
			2000 + sDate.Year);
}

/**
 * @brief	Get the weekday as string
 * @param	char array
 * @retval	None
 */
void RTC_getWeekdayAsString(char *buf){
	RTC_Date date;
	RTC_getDate(&date);
	switch(date.DayofWeek){
	case Sonntag:
		sprintf(buf, "Sonntag");
		break;
	case Montag:
		sprintf(buf, "Montag");
		break;
	case Dienstag:
		sprintf(buf, "Dienstag");
		break;
	case Mittwoch:
		sprintf(buf, "Mittwoch");
		break;
	case Donnerstag:
		sprintf(buf, "Donnerstag");
		break;
	case Freitag:
		sprintf(buf, "Freitag");
		break;
	case Samstag:
		sprintf(buf, "Samstag");
		break;
	default:
		break;
	}
}


/**
 * @brief	Get UnixTime
 * @param	None
 * @retval	uint32_t UnixTime
 */
uint32_t RTC_getUnixTime(void){
	uint32_t unixTime = 0;
	RTC_Time time;
	RTC_Date date;

	RTC_getTime(&time);
	RTC_getDate(&date);

	uint32_t stunde = time.Hours - 1;
	uint32_t minute = time.Minutes;
	uint32_t sekunde = time.Seconds;

	uint32_t jahr = 2000 + date.Year;
	uint32_t monat = date.Month;
	uint32_t tag = date.Date;

	uint32_t schaltjahre = ((jahr-1)-1968)/4 /* Anzahl der Schaltjahre seit 1970 (ohne das evtl. laufende Schaltjahr) */
	                  - ((jahr-1)-1900)/100
	                  + ((jahr-1)-1600)/400;

	uint32_t tage_seit_1970 = (jahr-1970)*365 + schaltjahre
	                      + tage_seit_jahresanfang[monat-1] + tag-1;

	/* +Schalttag, wenn jahr Schaltjahr ist */
	if ( (monat>2) && (jahr%4==0 && (jahr%100!=0 || jahr%400==0)) )
	    tage_seit_1970 += 1;

	return sekunde + 60 * ( minute + 60 * (stunde + 24*tage_seit_1970) );
}

/**
 * @brief	Get UnixTime in Bytes
 * @param	uint8_t array for bytes
 * @retval	None
 */
void RTC_getUnixTimeBytes(uint8_t *bytes){
	uint32_t unixTime = 0;

	unixTime = RTC_getUnixTime();

	bytes[0] = unixTime & 0xFF;
	bytes[1] = (unixTime >> 8) & 0xFF;
	bytes[2] = (unixTime >> 16) & 0xFF;
	bytes[3] = (unixTime >> 24) & 0xFF;
}

/**
 * @brief	Sets the RTC alarm
 * @param	sTime: Pointer to RTC_TimeTypeDef struct
 * 			weekday: Weekday i.e. RTC_WEEKDAY_FRIDAY
 * @retval	None
 */
void RTC_setAlarm(RTC_Time *time, RTC_DayOfWeek dow){

	RTC_AlarmTypeDef sAlarm;
	uint8_t weekday;
	/**Enable the Alarm A
	 */
	sAlarm.AlarmTime.Hours = time->Hours;
	sAlarm.AlarmTime.Minutes = time->Minutes;
	sAlarm.AlarmTime.Seconds = time->Seconds;
	sAlarm.AlarmTime.SubSeconds = 0x0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;

	if(dow == Sonntag){
		weekday = RTC_WEEKDAY_SUNDAY;
	}else{
		weekday = dow - 1;
	}
	sAlarm.AlarmDateWeekDay = weekday;
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK) {
		Firmware_ProcessLogic_ErrorHandler(0);
	}

	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0xF, 0x0);
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}


/**
  * @brief  ALARM A Event Callback in non blocking mode
  * @note   This function is called  when RTC_ALARM interrupt took place, inside
  * 		RTC_ALARM_IRQHandler().
  * @param  hrtc : RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	BSP_LED_Toggle(LED1);
}



