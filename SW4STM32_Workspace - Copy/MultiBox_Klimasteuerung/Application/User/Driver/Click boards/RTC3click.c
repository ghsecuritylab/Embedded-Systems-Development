/** \file	RTC3click Driver Source File
 *  \brief
 *
 *
 */
#include "RTC3click.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define RTC3_BQ32000_SLAVE		0xD0	// BQ32000 I2C Slave Address

/* BQ32000 Normal Register Addresses */
#define RTC3_REG_SECONDS		0x00	// Clock seconds and STOP bit
#define RTC3_REG_MINUTES		0x01	// Clock minutes
#define RTC3_REG_CENT_HOURS		0x02	// Clock hours, century, and CENT_EN bit
#define RTC3_REG_DAY			0x03	// Clock day
#define RTC3_REG_DATE			0x04	// Clock date
#define RTC3_REG_MONTH			0x05	// Clock month
#define RTC3_REG_YEARS			0x06	// Clock years
#define RTC3_REG_CAL_CFG1		0x07	// Calibration and configuration
#define RTC3_REG_TCH2			0x08	// Trickle charge enable
#define RTC3_REG_CFG2			0x09	// Configuration 2

/* BQ32000 Special Function Register Addresses */
#define RTC3_REG_SF_KEY1		0x20	// Special function key 1
#define RTC3_REG_SF_KEY2		0x21	// Special function key 2
#define RTC3_REG_SFR			0x22	// Special function register



/* Bit Masks */
#define RTC3_OSC_STOP			0x80	// in SECONDS register
#define RTC3_OSC_FAIL			0x80	// in MINUTES register
#define RTC3_CENT_EN			0x80	// in CENT_HOURS register

/* CAL_CFG1 register */
#define RTC3_OUT				0x80	// if FT = 0
#define RTC3_FT					0x40	// frequency test depends on FTF in SFR register
#define RTC3_CAL_SIGN			0x20	// 0 - slowing, 1 - speeding
#define RTC3_CAL				0x1F	// CAL bits along with S determine calibration amount

/* TCH2 Register */
#define RTC3_TCH2				0x20	// Trickle charge switch two

/* CFG3 Register */
#define RTC3_TCFE				0x40	// Trickle charge FET bypass: 0 - open, 1 - close
#define RTC3_TCHE				0x05	// Trickle charge enable: 0x5 - active otherwise inactive



#define JULIAN_DAY_1970 2440588 // julian day calculation for jan 1 1970
#define TIME_SEC_IN_MIN             60                     // seconds per minute
#define TIME_SEC_IN_HOUR            (TIME_SEC_IN_MIN * 60) // seconds per hour
#define TIME_SEC_IN_24_HOURS        (TIME_SEC_IN_HOUR * 24)// seconds per day


#define RTC_SECONDS_ADDR   0x00
#define RTC_SECONDS_MASK( value ) ( value & 0x7f )
#define RTC_SECONDS_CLEAR( value ) ( value & 0x80 )

#define RTC_MINUTES_ADDR   0x01
#define RTC_MINUTES_MASK( value ) ( value & 0x7f )
#define RTC_MINUTES_CLEAR( value ) ( value & 0x80 )

#define RTC_HOURS_ADDR     0x02
#define RTC_HOURS_MASK( value ) ( value & 0x3f )
#define RTC_HOURS_CLEAR( value ) ( value & 0xc0 )

#define RTC_DAY_ADDR       0x03
#define RTC_DAY_MASK( value ) ( value & 0x07 )
#define RTC_DAY_CLEAR( value ) ( value & 0xf8 )

#define RTC_DATE_ADDR      0x04
#define RTC_DATE_MASK( value ) ( value & 0x3f )
#define RTC_DATE_CLEAR( value ) ( value & 0xc0 )

#define RTC_MONTH_ADDR     0x05
#define RTC_MONTH_MASK( value ) ( value & 0x1f )
#define RTC_MONTH_CLEAR( value ) ( value & 0xe0 )

#define RTC_YEAR_ADDR      0x06
#define RTC_YEAR_MASK( value ) ( value & 0xff )
#define RTC_YEAR_CLEAR( value ) ( value & 0x00 )

#define RTC_CONFIG_ADDR    0x07

#define RTC_START_OSC_BIT  7
#define RTC_START_OSC_MASK ( 1 << RTC_START_OSC_BIT )

#define RTC_TIMEDATE_BYTES 7
#define RTC_SECONDS_BYTE   0
#define RTC_MINUTES_BYTE   1
#define RTC_HOUR_BYTE      2
#define RTC_DAY_BYTE       3
#define RTC_DATE_BYTE      4
#define RTC_MONTH_BYTE     5
#define RTC_YEAR_BYTE      6

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define BCD2BIN(val) ( ( ( val ) & 15 ) + ( ( val ) >> 4 ) * 10 )
#define BIN2BCD(val) ( ( ( ( val ) / 10 ) << 4 ) + ( val ) % 10 )


/* Anzahl der Tage seit Jahresanfang ohne Tage des aktuellen Monats und ohne Schalttag */
const short tageSeitJahresanfang[12] =
    {0,31,59,90,120,151,181,212,243,273,304,334};

/******************************************************************************
* Function Definitions
*******************************************************************************/

/** \brief 	Initialize I2C Bus and RTC Clock
 *
 *  \param	None
 *  \retval	None
 */
HAL_StatusTypeDef RTC3click_Init() {
    //Call I2C_Init
	uint8_t reg = 0;
	HAL_StatusTypeDef ret = HAL_ERROR;
    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);



    /* clear OSC Stop Bit */
    ret = I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_SECONDS, &reg);
    if(ret != HAL_OK){
    	return ret;
    }
    reg &= ~RTC3_OSC_STOP;
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_SECONDS, reg);

    /* Close Charge Switches to charge the super cap */
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_CFG2, RTC3_TCHE);	// Switch 1 close
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_TCH2, RTC3_TCH2);	// Switch 2 close

    I2C_DeInit();
    return ret;
}

/** \brief
 *
 *  \param
 *  \retval
 */
void RTC3click_Select(struct clickBoard * Board, uint8_t Addr) {
	RTC3_Current = Board;
    RTC3_Current->Address = Addr;
}

/** \brief	Get Time from RTC
 *
 *  \param	Pointer to RTC_Time-Struct
 *  \retval	None
 */
void RTC3click_getTime(RTC_Time *time){
	uint8_t buffer[RTC_TIMEDATE_BYTES] = {0};

	I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);

	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_SECONDS, &buffer[RTC_SECONDS_BYTE]);
	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_MINUTES, &buffer[RTC_MINUTES_BYTE]);
	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_CENT_HOURS, &buffer[RTC_HOUR_BYTE]);

	I2C_DeInit();

	time->Seconds = BCD2BIN( RTC_SECONDS_MASK( buffer[RTC_SECONDS_BYTE] ) );
	time->Minutes = BCD2BIN( RTC_MINUTES_MASK( buffer[RTC_MINUTES_BYTE] ) );
	time->Hours = 	BCD2BIN( RTC_HOURS_MASK( buffer[RTC_HOUR_BYTE] ) );
}

/** \brief	Sets the RTC Time
 *
 *  \param	Pointer to RTC_Time-Struct
 *  \retval	if success: 0 otherwise -1
 */
uint8_t RTC3click_setTime(RTC_Time *time){

    if( time->Seconds > 59 ||
		time->Minutes > 59 ||
		time->Hours > 24){
        return -1;
    }

    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);

    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_SECONDS, 0x80);
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_MINUTES, BIN2BCD(time->Minutes));
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_CENT_HOURS, BIN2BCD(time->Hours));
    I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_SECONDS, BIN2BCD(time->Seconds));

    I2C_DeInit();
	return 0;
}

/** \brief	Get Date from RTC
 *
 *  \param	Pointer to RTC_Date-Struct
 *  \retval	None
 */
void RTC3click_getDate(RTC_Date *date){
	uint8_t buffer[RTC_TIMEDATE_BYTES] = {0};

	I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);

	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_DAY, &buffer[RTC_DAY_BYTE]);
	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_DATE, &buffer[RTC_DATE_BYTE]);
	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_MONTH, &buffer[RTC_MONTH_BYTE]);
	I2C1_ReadByte(RTC3_BQ32000_SLAVE, RTC3_REG_YEARS, &buffer[RTC_YEAR_BYTE]);

	date->DayofWeek = RTC_DAY_MASK( buffer[RTC_DAY_BYTE] );
	date->Date = BCD2BIN( RTC_DATE_MASK(buffer[RTC_DATE_BYTE]) );
	date->Month = BCD2BIN( RTC_MONTH_MASK(buffer[RTC_MONTH_BYTE]) );
	date->Year = BCD2BIN( RTC_YEAR_MASK(buffer[RTC_YEAR_BYTE]) );

	I2C_DeInit();
}

/** \brief	Sets the RTC Date
 *
 *  \param	Pointer to RTC_Date-Struct
 *  \retval	if success: 0 otherwise -1
 */
uint8_t RTC3click_setDate(RTC_Date *date){
	if( date->DayofWeek > 7 ||
		date->Date > 31 ||
		date->Month > 12 ||
		date->Year > 99 ){
		return -1;
	}

    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);

	I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_DAY, BIN2BCD(date->DayofWeek));
	I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_DATE, BIN2BCD(date->Date));
	I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_MONTH, BIN2BCD(date->Month));
	I2C1_WriteByte(RTC3_BQ32000_SLAVE, RTC3_REG_YEARS, BIN2BCD(date->Year));

	I2C_DeInit();
	return 0;
}

/** \brief	Get the Time as a String
 *
 *  \param	Pointer to a char buffer
 *  \retval	None
 */
void RTC3click_getTimeAsString(char *buffer){
	RTC_Time time;
	RTC3click_getTime(&time);
	sprintf(buffer, "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
}

/** \brief	Get the Date as a String
 *
 *  \param	Pointer to a char buffer
 *  \retval	None
 */
void RTC3click_getDateAsString(char *buffer){
	RTC_Date date;
	RTC3click_getDate(&date);
	sprintf(buffer, "%02d.%02d.2%03d", date.Date, date.Month, date.Year);
}

/** \brief	Compares two Time structs
 *
 *  \param	Pointers to the Time structs
 *  \retval	1 if time1 is bigger or equal than time2, otherwise 0
 */
uint8_t RTC3click_TimeCompare(RTC_Time *time1, RTC_Time *time2){
	if(time1->Hours >= time2->Hours){
		if(time1->Minutes >= time2->Minutes){
			if(time1->Minutes >= time2->Minutes){
				return 1;
			}
		}
	}
	return 0;
}

/** \brief	Get the Time and Date from RTC
 *
 *  \param	Pointer to RTC_TimeDate-Struct
 *  \retval	None
 */
void RTC3click_getTimeDate(RTC_TimeDate *timeDate){
	RTC_Time time;
	RTC_Date date;
	RTC3click_getTime(&time);
	RTC3click_getDate(&date);
	timeDate->Seconds = time.Seconds;
	timeDate->Minutes = time.Minutes;
	timeDate->Hours = time.Hours;
	timeDate->DayofWeek = date.DayofWeek;
	timeDate->Date = date.Date;
	timeDate->Month = date.Month;
	timeDate->Year = date.Year;
}

/** \brief	Compares two TimeDate structs
 *
 *  \param	Pointers to the Time structs
 *  \retval	1 if time1 is bigger or equal than time2, otherwise 0
 */
uint8_t RTC3click_TimeDateCompare(RTC_TimeDate *timeDate1, RTC_TimeDate *timeDate2){
	if(timeDate1->Year >= timeDate2->Year){
		if(timeDate1->Month >= timeDate2->Month){
			if(timeDate1->Date >= timeDate2->Date){
				if(timeDate1->Hours >= timeDate2->Hours){
					if(timeDate1->Minutes >= timeDate2->Minutes){
						if(timeDate1->Minutes >= timeDate2->Minutes){
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
 * @brief	Get the weekday as string
 * @param	char array
 * @retval	None
 */
void RTC3click_getWeekdayAsString(char *buf){
	RTC_Date date;
	RTC3click_getDate(&date);
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

/** \brief	Sync the internal RTC with the RTC3click-Board
 *
 *  \param	None
 *  \retval	None
 */
void RTC3click_SyncIntRTC(void){
	RTC_Time time;
	RTC_Date date;
	RTC3click_getTime(&time);
	RTC_setTime(&time);
	RTC3click_getDate(&date);
	RTC_setDate(&date);
}

/**
 * @brief	Get UnixTime
 * @param	None
 * @retval	uint32_t UnixTime
 */
uint32_t RTC3click_getUnixTime(void){
	uint32_t unixTime = 0;
	RTC_Time time;
	RTC_Date date;

	RTC3click_getTime(&time);
	RTC3click_getDate(&date);

	return RTC3click_convTimeDateto_UnixTime(&time,&date);
}


/**
 * @brief	Get UnixTime
 * @param	None
 * @retval	uint32_t UnixTime
 */
uint32_t RTC3click_convTimeDateto_UnixTime(RTC_Time * time, RTC_Date * date){
	uint32_t unixTime = 0;

	uint32_t stunde = time->Hours - 1;
	uint32_t minute = time->Minutes;
	uint32_t sekunde = time->Seconds;

	uint32_t jahr = 2000 + date->Year;
	uint32_t monat = date->Month;
	uint32_t tag = date->Date;

	uint32_t schaltjahre = ((jahr-1)-1968)/4 /* Anzahl der Schaltjahre seit 1970 (ohne das evtl. laufende Schaltjahr) */
	                  - ((jahr-1)-1900)/100
	                  + ((jahr-1)-1600)/400;

	uint32_t tage_seit_1970 = (jahr-1970)*365 + schaltjahre
	                      + tageSeitJahresanfang[monat-1] + tag-1;

	/* +Schalttag, wenn jahr Schaltjahr ist */
	if ( (monat>2) && (jahr%4==0 && (jahr%100!=0 || jahr%400==0)) )
	    tage_seit_1970 += 1;

	return sekunde + 60 * ( minute + 60 * (stunde + 24*tage_seit_1970) );
}


/** \brief	Converts Time to String
 *
 *  \param	Pointer to a char buffer
 *  \retval	None
 */
void RTC3click_ConvTimeToString(RTC_Time * time, char *buffer){
	sprintf(buffer, "%02d:%02d:%02d", time->Hours, time->Minutes, time->Seconds);
}

/** \brief	Converts Date to String
 *
 *  \param	Pointer to a char buffer
 *  \retval	None
 */
void RTC3click_ConvDateToString(RTC_Date * date, char *buffer){
	sprintf(buffer, "%02d.%02d.2%03d", date->Date, date->Month, date->Year);
}
