#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Data.h"
#include "Parameter.h"

#define RingMemory_getVal(Ring,PastCount)               (DataRead(Ring->DataType->ID, (*RingMemory_getValasData(Ring, PastCount))))

struct RingElement {
    struct RingElement *Previous;
    struct RingElement *Next;

    //char ValueString[10];
    union Data Value;
};

struct RingMemory {
    struct DataType * DataType;
    uint16_t Count;
    uint16_t StoredItems;

    uint32_t FlashAddress[20];
    uint32_t FlashCounter[20];
    uint16_t AktFlashIndex;

    struct Parameter * CycleTime;
    struct Parameter * SaveToSD;

    char Name[20];

    uint16_t AktValueIndex;
    union Data ** AktValue; //struct RingElement * AktValue;
};

extern uint8_t SD_Mounted;
extern uint8_t QSPI_status;

uint32_t AktFlashAddress;
uint32_t LastFlashSize;

struct ParameterGroup ParameterGroup_RingMemory;

void RingMemory_Init(struct RingMemory * Ring, char * Name, uint16_t ElementCount, struct DataType * DataType_, double CycleTime, uint8_t SaveToSD, struct ParameterGroup * Group);
void RingMemory_Save(struct RingMemory * Ring, union Data * Data);

union Data * RingMemory_getValasData(struct RingMemory * Ring, uint16_t PastCount);

void RingMemory_SavetoSD(struct RingMemory * Ring, uint8_t Start, uint8_t End);
uint32_t * RingMemory_getNewFlashAddres();
