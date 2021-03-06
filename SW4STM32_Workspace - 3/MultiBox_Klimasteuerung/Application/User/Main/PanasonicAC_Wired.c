/*
 * PanasonicAC_Wired.c
 *
 *
 */


#include "PanasonicAC_Wired.h"
#include "temperature_control.h"


void PanasonicAC_Wired_Init(void){

	//	Set MODE from FAN to AUTO
	uint8_t click_count = 3;
	while (click_count > 0){
		EXPAND4click_set(4);
		delayUS(500000);
		EXPAND4click_set(0);
		delayUS(500000);
		click_count--;
	}

	//	Set TEMP from 25�C to 20�C
	click_count = 5;
	while (click_count > 0){
	   EXPAND4click_set(2); //DOWN
	   delayUS(500000);
	   EXPAND4click_set(0);
	   delayUS(500000);
	   click_count--;
	}
}


void PanasonicAC_Wired_PowerOn(void){
	EXPAND4click_set(8); //ON OFF
	delayUS(500000);
}

void PanasonicAC_Wired_SetMode(uint8_t mode_click_count){
	while (mode_click_count > 0){
		EXPAND4click_set(4); //MODE
		delayUS(500000);
		EXPAND4click_set(0);
		delayUS(500000);
		mode_click_count--;
	}
}

void PanasonicAC_Wired_SetTempDown(uint8_t TempD_click_count){

//	if (*pTC_IstTemperature > TC_SollTemperature){
//		click_count = *pTC_IstTemperature - TC_SollTemperature;
		while (TempD_click_count > 0){
			EXPAND4click_set(2); //DOWN
			delayUS(500000);
			EXPAND4click_set(0);
			delayUS(500000);
			TempD_click_count--;
		}
//	}
}

void PanasonicAC_Wired_SetTempUp(uint8_t TempU_click_count){

//	if (*pTC_IstTemperature < TC_SollTemperature){
//		click_count = TC_SollTemperature - *pTC_IstTemperature;
		while (TempU_click_count > 0){
			EXPAND4click_set(1); //UP
			delayUS(500000);
			EXPAND4click_set(0);
			delayUS(500000);
			TempU_click_count--;
		}
//	}
}

void PanasonicAC_Wired_SetFanSpeed(uint8_t FanSpeed_click_count){
	// Set FAN speed from AUTO to LO
//	if (currentState == Standby){
	while (FanSpeed_click_count > 0){
		EXPAND4click_set(32);
		delayUS(500000);
		EXPAND4click_set(0);
		delayUS(500000);
		FanSpeed_click_count--;
	}
//	}
}

// Set AIR SWING to AUTO
void PanasonicAC_SetAirAuto(void){
		EXPAND4click_set(64);
		delayUS(500000);
		EXPAND4click_set(0);
		delayUS(500000);
}

// Set AIR SWING to MANUAL
void PanasonicAC_SetAirManual(void){
		EXPAND4click_set(128);
		delayUS(500000);
		EXPAND4click_set(0);
		delayUS(500000);
}
