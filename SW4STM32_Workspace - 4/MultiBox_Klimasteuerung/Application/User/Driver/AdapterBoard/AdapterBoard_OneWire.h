#pragma once

#include "MemoryStructures.h"

#include "stm32f7xx_hal.h"
#include "1WIRE-Driver.h"
#include "DS1820.h"

//Forward Declaration
struct Parameter;


uint8_t deviceCount;
uint8_t * device;

TM_OneWire_t OW;
uint8_t LOCK_OneWire;

void Init_OneWire();
void checkOneWireDevice_SearchonBus();
void checkOneWireDevice_Parameter(struct Parameter * Para);

