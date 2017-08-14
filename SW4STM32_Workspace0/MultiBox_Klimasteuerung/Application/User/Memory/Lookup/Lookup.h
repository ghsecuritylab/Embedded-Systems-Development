#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parameter.h"

/****************************************

DEFINITION ParameterFlash

****************************************/

struct Lookup {
    uint8_t Count;

    struct DataType * DataType;

    struct LookupElement * Elements[255];
};

struct LookupElement {
    union Data Value;
    char Name[255];
};
//(DataRead(Lookup->DataType->ID,Val)));

#define Lookup_Write(Lookup, Val, Nam, Index) {\
   DataWrite(Lookup->DataType->ID,Lookup->Elements[Index]->Value,Val);\
   sprintf(Lookup->Elements[Index]->Name, "%s", Nam);\
}


#define Lookup_ReadVal(Lookup, Index) (DataRead(Lookup->DataType->ID,Lookup->Elements[Index]->Value))

void Lookup_Init(struct Lookup * Lookup, uint8_t Count, struct DataType * DataType);

uint8_t Lookup_getValueID(struct Lookup * Lookup, union Data * Value);

//void Lookup_Write(struct Lookup * Lookup, union Data Value, char * Name, uint8_t Index);
