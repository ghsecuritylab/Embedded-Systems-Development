#pragma once

//#include "MemoryStructures.h"

#include "stm32746g_discovery.h"

#include "DriverConf.h"
#include "Firmware_MemoryStructures_CONFIG.h"

#include "Layout_CONFIG.h"



enum {
    STATE_SETSAVE,
    STATE_AUTO,
    STATE_MANU,
    STATE_KONFIG,
    STATE_ERROR,
};


uint8_t Machinestate;

//Extern functions of Project-Processlogic
extern void Project_ProcessLogic_Init_Clickboards();
extern void Project_ProcessLogic_Init_Variables();
extern void Project_ProcessLogic_Configure_Clickboards();
extern uint8_t * Project_ProcessLogic_getError();
extern void Project_ProcessLogic_SafeStartUp();
extern void Project_ProcessLogic_ReadInputs() ;
extern void Project_ProcessLogic_WriteOutputs();
extern void Project_ProcessLogic_Mode_Auto();
extern void Project_ProcessLogic_Mode_Konfig();
extern void Project_ProcessLogic_Mode_Error();
extern void Project_ProcessLogic_CAN_Receive(CAN_HandleTypeDef *CanHandle);

//Functions
void Firmware_ProcessLogic_Init();
void Firmware_ProcessLogic_ReadInputs();
void Firmware_ProcessLogic_WriteOutputs();
void Firmware_ProcessLogic_CAN_Receive(CAN_HandleTypeDef *CanHandle);
void Firmware_ProcessLogic_MainTask();
void Firmware_ProcessLogic_LED();
void Firmware_ProcessLogic_WriteClickBoardConfig();
void Firmware_ProcessLogic_ErrorHandler(uint8_t ErrorType);

float * ProjectPIController(uint16_t CycleTime, float KI, float KP, float SOLL, float IST, float * eSum);
float * ProjectPIDController(uint16_t CycleTime, float KI, float KP, float KD, float SOLL, float IST, float IST_1, float * eSum, uint8_t Invers) ;


