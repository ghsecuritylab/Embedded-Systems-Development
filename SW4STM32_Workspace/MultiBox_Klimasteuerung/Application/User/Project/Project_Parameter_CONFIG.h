#pragma once

#include "Parameter.h"
#include "Firmware_Parameter_CONFIG.h"

/**/
//struct Parameter SOLL_DRUCK;
//struct Parameter SOLL_DROSSEL;
//struct Parameter PWM_DROSSEL;
//struct Parameter IO_VENTIL;
//struct Parameter ONEWIRE_ROM_MOSFET;
struct Parameter ONEWIRE_ROM_ROOM;
struct Parameter ONEWIRE_ROM_OUTSIDE;
struct Parameter ONEWIRE_ROM_AIR1;
struct Parameter ONEWIRE_ROM_UNIT1_OUTSIDE;
struct Parameter ONEWIRE_ROM_AIR2;
struct Parameter ONEWIRE_ROM_UNIT2_OUTSIDE;
struct Parameter ONEWIRE_ROM_MOTOR;

struct ParameterGroup ParameterGroup_TemperatureControl;
struct Parameter TC_IstWert_Sel;
struct Parameter TC_Sollwert;

struct ParameterGroup ParameterGroup_CAN;
struct Parameter CAN_TEMP_ID;
struct Parameter CAN_TEMP_STARTBIT;
struct Parameter CAN_TEMP_BITCOUNT;
struct Parameter CAN_TEMP_TYPE;
struct Parameter CAN_TEMP_FORMAT;
struct Parameter CAN_TEMP_FACTOR;
struct Parameter CAN_TEMP_OFFSET;

struct Parameter GraphDispLines;

struct ParameterGroup ParameterGroup_TimeSwitchList;
struct Parameter ListEntryCount;
struct Parameter ListEntry0_Day;
struct Parameter ListEntry0_Hour;
struct Parameter ListEntry0_Minutes;
struct Parameter ListEntry0_Temperature;
struct Parameter ListEntry0_Repeat;
struct Parameter ListEntry1_Day;
struct Parameter ListEntry1_Hour;
struct Parameter ListEntry1_Minutes;
struct Parameter ListEntry1_Temperature;
struct Parameter ListEntry1_Repeat;
struct Parameter ListEntry2_Day;
struct Parameter ListEntry2_Hour;
struct Parameter ListEntry2_Minutes;
struct Parameter ListEntry2_Temperature;
struct Parameter ListEntry2_Repeat;
struct Parameter ListEntry3_Day;
struct Parameter ListEntry3_Hour;
struct Parameter ListEntry3_Minutes;
struct Parameter ListEntry3_Temperature;
struct Parameter ListEntry3_Repeat;
struct Parameter ListEntry4_Day;
struct Parameter ListEntry4_Hour;
struct Parameter ListEntry4_Minutes;
struct Parameter ListEntry4_Temperature;
struct Parameter ListEntry4_Repeat;
struct Parameter ListEntry5_Day;
struct Parameter ListEntry5_Hour;
struct Parameter ListEntry5_Minutes;
struct Parameter ListEntry5_Temperature;
struct Parameter ListEntry5_Repeat;
struct Parameter ListEntry6_Day;
struct Parameter ListEntry6_Hour;
struct Parameter ListEntry6_Minutes;
struct Parameter ListEntry6_Temperature;
struct Parameter ListEntry6_Repeat;
struct Parameter ListEntry7_Day;
struct Parameter ListEntry7_Hour;
struct Parameter ListEntry7_Minutes;
struct Parameter ListEntry7_Temperature;
struct Parameter ListEntry7_Repeat;
struct Parameter ListEntry8_Day;
struct Parameter ListEntry8_Hour;
struct Parameter ListEntry8_Minutes;
struct Parameter ListEntry8_Temperature;
struct Parameter ListEntry8_Repeat;
struct Parameter ListEntry9_Day;
struct Parameter ListEntry9_Hour;
struct Parameter ListEntry9_Minutes;
struct Parameter ListEntry9_Temperature;
struct Parameter ListEntry9_Repeat;

struct Parameter *ZUSTAND_Power1;
struct Parameter *ZUSTAND_Power2;
struct Parameter *ZUSTAND_Power3;
struct Parameter *ZUSTAND_Power4;
struct Parameter *ZUSTAND_Abgasabsaugung;
struct Parameter *ZUSTAND_Schnellstopp;



//struct ParameterGroup ParameterGroup_SensorDrossel;
//struct Parameter SENSOR_DROSSEL_R1D;
//struct Parameter SENSOR_DROSSEL_R1U;
//struct Parameter SENSOR_DROSSEL_R2D;
//struct Parameter SENSOR_DROSSEL_R2U;
//
//struct ParameterGroup ParameterGroup_ReglerDrossel;
//struct Parameter PWM_DROSSEL_T;
//struct Parameter PWM_DROSSEL_KI;
//struct Parameter PWM_DROSSEL_KP;
//struct Parameter PWM_DROSSEL_KD;
//struct Parameter PWM_DROSSEL_Inv;
//
//struct ParameterGroup ParameterGroup_ReglerDruck;
//struct Parameter PWM_DRUCK_T;
//struct Parameter PWM_DRUCK_KI;
//struct Parameter PWM_DRUCK_KP;
//struct Parameter PWM_DRUCK_KD;
//struct Parameter PWM_DRUCK_Inv;


void Project_Init_Parameters();
