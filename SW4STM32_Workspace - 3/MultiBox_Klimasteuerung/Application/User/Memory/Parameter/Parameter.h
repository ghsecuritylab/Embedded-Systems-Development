#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32746g_discovery_qspi.h"
#include "Data.h"
#include "Parameters_Edit.h"
#include "Lookup.h"

/****************************************

DEFINITION ParameterFlash

****************************************/

#define PARAMETER_MAX_GROUP_ELEMENTS    (32)
#define PARAMETER_FLASH_STARTADDRESS    (0x00)
#define PARAMETER_FLASH_SIZE            (sizeof(uint8_t)*5*DATASIZE + sizeof(uint8_t))



#define ParameterRead(Para, Data)               DataRead(Para->DataType->ID, Para->Data)
#define ParameterWrite(Para, Data, Val)         DataWrite(Para->DataType->ID, Para->Data, Val)


#define ParameterWriteALL(Para, MinVal, DefVal, MaxVal, StepVal, ValVal) { \
                                                    DataWrite(Para->DataType->ID, Para->Min, MinVal); \
                                                    DataWrite(Para->DataType->ID, Para->Max, MaxVal); \
                                                    DataWrite(Para->DataType->ID, Para->Default, DefVal); \
                                                    DataWrite(Para->DataType->ID, Para->Step, StepVal); \
                                                    DataWrite(Para->DataType->ID, Para->Value, ValVal); \
                                                }


#define ParameterActiveRead(Data)               DataRead(Parameter_Active->DataType->ID, Parameter_Active->Data)
#define ParameterActiveWrite(Data, Val)         { \
                                                    DataWrite(Parameter_Active->DataType->ID, Parameter_Active->Data, Val); \
                                                }

#define DataActiveRead(Data)                    DataRead(Parameter_Active->DataType->ID, Data)
#define DataActiveNegate(Data)                  DataNegate(Parameter_Active->DataType->ID, Data)
#define DataActiveWrite(Data, Val)              DataWrite(Parameter_Active->DataType->ID, Data, Val)

#define NOTUSED         ( 0xFFFFFFFFFFFFFFFFFF)
/*
extern union Data;
extern struct DataType;
*/
struct Parameter {
    uint8_t ID;

    union Data Min;
    union Data Max;
    union Data Step;
    union Data Default;
    union Data Value;

    struct DataType * DataType;
    struct Lookup * Lookup;
    uint8_t EditType;

    int Changed;

    char Name[20];
    char Description[32];
    char dimension[4];

    uint8_t isUsed;

    struct ParameterGroup * Group;
};

struct ParameterGroup{
    uint8_t Count;
    char Name[20];
    char Description[20];

    struct Parameter * Para[PARAMETER_MAX_GROUP_ELEMENTS];

    struct ParameterGroup * ParentGroup;
    struct ParameterGroup * ChildGroups[PARAMETER_MAX_GROUP_ELEMENTS];

};

enum {
  PARA_DATA_BIT_MIN = 0,
  PARA_DATA_BIT_MAX,
  PARA_DATA_BIT_DEF,
  PARA_DATA_BIT_STEP,
  PARA_DATA_BIT_VAL,
} PARA_DATA_BIT;

struct ParameterList {
    uint8_t Count;
    struct Parameter * Para[256];
} ParameterArray, OneWire_Devices_ParameterArray;

/****************************************

DEFINITION Skinning-Routines

****************************************/

extern int Dialog_DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

/****************************************

DEFINITION Icons

****************************************/

extern GUI_CONST_STORAGE GUI_BITMAP bmUp;
extern GUI_CONST_STORAGE GUI_BITMAP bmDown;
extern GUI_CONST_STORAGE GUI_BITMAP bmStop;
extern GUI_CONST_STORAGE GUI_BITMAP bmBack;

extern GUI_CONST_STORAGE GUI_BITMAP bmOk;

extern GUI_CONST_STORAGE GUI_BITMAP bmCancel;

/****************************************

DEFINITION Parameter

****************************************
Parameter PARA_LOAD_FLASH;
Parameter KONFIGMODE_OUTPUT;
ParameterGroup ParameterGroup_ClickBoards;

ParameterGroup ParameterGroup_CAN;
struct Lookup AnAus;
Parameter CAN_ACTIVE;
Parameter CAN_SPEED;
Parameter CAN_ID;
Parameter CAN_ZYKLUSZEIT;

ParameterGroup ParameterGroup_CAN_Msg1;
Parameter CAN_Msg1_ACTIVE;
Parameter CAN_Msg1_ID;
Parameter CAN_Msg1_ZYKLUSZEIT;


ParameterGroup ParameterGroup_Prozessparameter;
ParameterGroup ParameterGroup_Sollwerte;
ParameterGroup ParameterGroup_Zustandsgroessen;

Parameter SOLL_DRUCK;
Parameter PWM_DROSSEL;

ParameterGroup ParameterGroup_SensorDrossel;
Parameter SENSOR_DROSSEL_R1D;
Parameter SENSOR_DROSSEL_R1U;
Parameter SENSOR_DROSSEL_R2D;
Parameter SENSOR_DROSSEL_R2U;

ParameterGroup ParameterGroup_ReglerDrossel;
Parameter PWM_DROSSEL_T;
Parameter PWM_DROSSEL_KI;
Parameter PWM_DROSSEL_KP;
Parameter PWM_DROSSEL_KD;*/

extern uint8_t QSPI_status;

char * ValConvStr[5];
char ValueString[25];
struct Parameter * AktParameter;

uint8_t ID_Counter;

void Init_Params();
void ParameterGroup_Init(struct ParameterGroup * Group, char * Name, char * Description, struct ParameterGroup * ParentGroup);
void Parameter_InitOneWire(struct Parameter * Para);
char * Parameter_getValAsStr(struct Parameter * Para);
char * Parameter_getDefValAsStr(struct Parameter * Para);
void Parameter_Init(struct Parameter * Para, struct ParameterGroup * Group);

void Init_ParamFlash();

void Parameter_SaveALLInFlash();
void Parameter_ReadALLFromFlash();
void Parameter_SaveInFlash(struct Parameter * Para);
void Parameter_ReadFromFlash(struct Parameter * Para);

void Create_CAN_Message(struct ParameterGroup * CanMessageGroup, uint8_t Active, uint8_t ID, uint8_t CycleTime, char * Name, char * Description);
