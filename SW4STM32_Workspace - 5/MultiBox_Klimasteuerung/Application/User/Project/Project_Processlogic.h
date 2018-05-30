#pragma once

#include "DriverConf.h"
#include "Project_MemoryStructures_CONFIG.h"

struct clickBoard * Board_ADC_1;
struct clickBoard * Board_EXPAND_4;

uint8_t MikrobusFehler = 0;
uint8_t AdapterBoardFehler = 0;
uint8_t CANFehler = 0;

uint8_t ReglerFreigabe = 1;
uint8_t Notbelueftung = 0;

float Drossel_eSum_d;
float Druck_eSum_d;

extern uint32_t Counter;



/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Project
 *  @{
 */

 #include "Project_Processlogic.h"

void Project_ProcessLogic_Init_Clickboards();
void Project_ProcessLogic_Init_Variables();
void Project_ProcessLogic_Configure_Clickboards();
uint8_t * Project_ProcessLogic_getError();
void Project_ProcessLogic_SafeStartUp();
void Project_ProcessLogic_ReadInputs();
void Project_ProcessLogic_WriteOutputs();
void Project_ProcessLogic_Mode_Auto();
void Project_ProcessLogic_Mode_Konfig();
void Project_ProcessLogic_Mode_Error();
void Project_ProcessLogic_CAN_Receive(CAN_HandleTypeDef *CanHandle);