/*
 * PanasonicAC_Wired.h
 *
 *
 */

#ifndef APPLICATION_USER_MAIN_PANASONICAC_WIRED_H_
#define APPLICATION_USER_MAIN_PANASONICAC_WIRED_H_

#include "EXPAND4click.h"

//typedef enum {
//	Cool = 1,
//	Dry  = 2,
//	Auto = 3,
//	Heat = 4
//}Wired_Control_Mode_ClickCount;

void PanasonicAC_Wired_Init(void);
void PanasonicAC_Wired_PowerOn(void);
void PanasonicAC_Wired_SetMode(uint8_t mode_click_count);
void PanasonicAC_Wired_SetTempDown(uint8_t TempD_click_count);
void PanasonicAC_Wired_SetTempUp(uint8_t TempU_click_count);
void PanasonicAC_Wired_SetFanSpeed(uint8_t FanSpeed_click_count);
void PanasonicAC_SetAirAuto(void);
void PanasonicAC_SetAirManual(void);

#endif /* APPLICATION_USER_MAIN_PANASONICAC_WIRED_H_ */

