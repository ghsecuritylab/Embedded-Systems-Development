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
#include "temperature_control.h"
#include "math.h"
#include "stdlib.h"
#include "PanasonicAC_IR.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static volatile enum fsm_states currentState = Start;
float TC_SollTemperature = 20.0;
float *pTC_IstTemperature1;
float *pTC_IstTemperature2;
uint8_t activeMode1 = 0;
uint8_t activeMode2 = 0;

/* Private function prototypes -----------------------------------------------*/
static void temperatureControl_setHeatingMode(void);
static void temperatureControl_setCoolingMode(void);
static void temperatureControl_setHoldMode(void);
static void temperatureControl_setRapidHeatingMode(void);


/* Private functions ---------------------------------------------------------*/


/**
 * @brief  evaluate events of the state machine
 * @param  None
 * @retval None
 */
void temperatureControl_evalEvents(void){
	switch(currentState){
		case Start:
			currentState = Standby;
			break;
		case Standby:
				currentState = Ready;
			break;
		case Ready:
			if( (TC_SollTemperature - *pTC_IstTemperature1) > 0.2 &&
					(TC_SollTemperature - *pTC_IstTemperature1) < 3.0){
				currentState = Heating;
				temperatureControl_setHeatingMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) < -0.2){
				currentState = Cooling;
				temperatureControl_setCoolingMode();
			}else
			if( fabs(TC_SollTemperature - *pTC_IstTemperature1) <= 0.2){
				currentState = Hold;
				temperatureControl_setHoldMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) >= 3.0){
				currentState = RapidHeating;
				temperatureControl_setRapidHeatingMode();
			}
			break;
		case Heating:
			if( (TC_SollTemperature - *pTC_IstTemperature1) < -0.2){
				currentState = Cooling;
				temperatureControl_setCoolingMode();
			}else
			if( fabs(TC_SollTemperature - *pTC_IstTemperature1) <= 0.2){
				currentState = Hold;
				temperatureControl_setHoldMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) >= 3.0){
				currentState = RapidHeating;
				temperatureControl_setRapidHeatingMode();
			}
			break;
		case RapidHeating:
			if( (TC_SollTemperature - *pTC_IstTemperature1) > 0.2 &&
					(TC_SollTemperature - *pTC_IstTemperature1) < 3.0){
				currentState = Heating;
				temperatureControl_setHeatingMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) < -0.2){
				currentState = Cooling;
				temperatureControl_setCoolingMode();
			}else
			if( fabs(TC_SollTemperature - *pTC_IstTemperature1) <= 0.2){
				currentState = Hold;
				temperatureControl_setHoldMode();
			}
			break;
		case Cooling:
			if( (TC_SollTemperature - *pTC_IstTemperature1) > 0.2 &&
					(TC_SollTemperature - *pTC_IstTemperature1) < 3.0){
				currentState = Heating;
				temperatureControl_setHeatingMode();
			}else
			if( fabs(TC_SollTemperature - *pTC_IstTemperature1) <= 0.2){
				currentState = Hold;
				temperatureControl_setHoldMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) >= 3.0){
				currentState = RapidHeating;
				temperatureControl_setRapidHeatingMode();
			}
			break;
		case Hold:
			if( (TC_SollTemperature - *pTC_IstTemperature1) > 0.2 &&
					(TC_SollTemperature - *pTC_IstTemperature1) < 3.0){
				currentState = Heating;
				temperatureControl_setHeatingMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) < -0.2){
				currentState = Cooling;
				temperatureControl_setCoolingMode();
			}else
			if( (TC_SollTemperature - *pTC_IstTemperature1) >= 3.0){
				currentState = RapidHeating;
				temperatureControl_setRapidHeatingMode();
			}
			break;
		case Error:
//			if(){
//				currentState = Standby;
//			}
			break;
		default:
			currentState = Start;

	}
}

/**
 * @brief  evaluate states of the state machine
 * @param  None
 * @retval None
 */
void temperatureControl_evalState(void){
	switch(currentState){
		case Start:
		case Standby:
			break;
		case Ready:
			break;
		case Heating:
			break;
		case RapidHeating:
			break;
		case Cooling:
			break;
		case Hold:
			break;
		case Error:
			break;
	}
}

void temperatureControl_setSoll(float sollT){
	TC_SollTemperature = sollT;
}

void temperatureControl_setIst(float *pIstT){
	pTC_IstTemperature1 = pIstT;
}

static void temperatureControl_setHeatingMode(void){

	activeMode1 = 0;

	/* configure IR message */
	PanasonicAC_SetMode(Mode_Heat);
	PanasonicAC_SetAirDir(AirDir_Swing);
	PanasonicAC_SetFanSpeed(Fan_Auto);
	if(TC_SollTemperature < 16.0){
		PanasonicAC_SetTemp(Temp_16C);
	}else if(TC_SollTemperature > 30.0){
		PanasonicAC_SetTemp(Temp_30C);
	}else{
		PanasonicAC_SetTemp( (PanasonicAC_Temperature)((uint8_t)TC_SollTemperature - 4) );
	}

	/* send IR message */
	PanasonicAC_SendIRMessage();

	/* TODO send command over "wired-remote" */
	wired_control_SendIRMessage();

	/* TODO switch off electrical heater */
	DMX_setSlot(1, 0);
	DMX_setSlot(2, 0);
}

static void temperatureControl_setCoolingMode(void){

	activeMode1 = 2;

	/* configure IR message */
	PanasonicAC_SetMode(Mode_Cool);
	PanasonicAC_SetAirDir(AirDir_Swing);
	PanasonicAC_SetFanSpeed(Fan_Auto);
	if(TC_SollTemperature < 16.0){
		PanasonicAC_SetTemp(Temp_16C);
	}else if(TC_SollTemperature > 30.0){
		PanasonicAC_SetTemp(Temp_30C);
	}else{
		PanasonicAC_SetTemp( (PanasonicAC_Temperature)((uint8_t)TC_SollTemperature - 4) );
	}

	/* send IR message */
	PanasonicAC_SendIRMessage();

	/* send command over "wired-remote" */
	wired_control_SendIRMessage();

	/* switch off electrical heater */
	DMX_setSlot(1, 0);
	DMX_setSlot(2, 0);
}

static void temperatureControl_setHoldMode(void){

	activeMode1 = 3;

	/* configure IR message */
	PanasonicAC_SetMode(Mode_Auto);
	PanasonicAC_SetAirDir(AirDir_Swing);
	PanasonicAC_SetFanSpeed(Fan_Auto);
	if(TC_SollTemperature < 16.0){
		PanasonicAC_SetTemp(Temp_16C);
	}else if(TC_SollTemperature > 30.0){
		PanasonicAC_SetTemp(Temp_30C);
	}else{
		PanasonicAC_SetTemp( (PanasonicAC_Temperature)((uint8_t)TC_SollTemperature - 4) );
	}

	/* send IR message */
	PanasonicAC_SendIRMessage();

	/* send command over "wired-remote" */
	wired_control_SendIRMessage();

	/* switch off electrical heater */
	DMX_setSlot(1, 0);
	DMX_setSlot(2, 0);
}

static void temperatureControl_setRapidHeatingMode(void){

	activeMode1 = 1;

	/* configure IR message */
	PanasonicAC_SetMode(Mode_Heat);
	PanasonicAC_SetAirDir(AirDir_Swing);
	PanasonicAC_SetFanSpeed(Fan_Auto);
	if(TC_SollTemperature < 16.0){
		PanasonicAC_SetTemp(Temp_16C);
	}else if(TC_SollTemperature > 30.0){
		PanasonicAC_SetTemp(Temp_30C);
	}else{
		PanasonicAC_SetTemp( (PanasonicAC_Temperature)((uint8_t)TC_SollTemperature - 4) );
	}

	/* send IR message */
	PanasonicAC_SendIRMessage();

	/* send command over "wired-remote" */
	wired_control_SendIRMessage();

	/* switch on electrical heater */

	DMX_setSlot(1, 255);
	DMX_setSlot(2, 255);
}

uint8_t temperatureControl_getMode(void){
	return activeMode1;
}


