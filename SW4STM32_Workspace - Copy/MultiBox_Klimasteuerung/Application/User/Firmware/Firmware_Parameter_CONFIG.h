#pragma once

#include "MemoryStructures.h"

struct Parameter PARA_LOAD_FLASH;
struct Parameter KONFIGMODE_OUTPUT;

struct ParameterGroup ParameterGroup_ClickBoards;

struct ParameterGroup ParameterGroup_CAN;
struct Parameter CAN_ACTIVE;
struct Parameter CAN_SPEED;

struct ParameterGroup ParameterGroup_OneWire;
struct Parameter ONEWIRE_ROM_GEHAEUSE;
struct Parameter * ONEWIRE_ROM_TEMP1;
struct Parameter * ONEWIRE_ROM_TEMP2;
struct Parameter * ONEWIRE_ROM_TEMP3;
struct Parameter * ONEWIRE_ROM_TEMP4;
struct Parameter * ONEWIRE_ROM_TEMP5;

struct ParameterGroup ParameterGroup_Prozessparameter;

struct ParameterGroup ParameterGroup_Sollwerte;

struct ParameterGroup ParameterGroup_Zustandsgroessen;

void Firmware_Init_Parameters();
