#pragma once

#include "MemoryStructures.h"
#include <inttypes.h>



#define DATASIZE            (sizeof(union Data))

#define DataRead(ID, Var)   (                                                           \
                            ((ID == DATATYPE_ID_FLOAT ) ? (float) Var.f :               \
                            ((ID == DATATYPE_ID_PROZENT ) ? (uint8_t) Var.p :           \
                            ((ID == DATATYPE_ID_HEX ) ? (uint16_t) Var.x :               \
                            ((ID == DATATYPE_ID_UNINT ) ? (uint16_t) Var.un :           \
                            ((ID == DATATYPE_ID_ROM ) ? (uint8_t) Var.ROM[0] :          \
                            ((ID == DATATYPE_ID_BOOL ) ? (uint8_t) Var.b    :           \
                            Firmware_DataError(ID)                                      \
                            )))))))

#define DataWrite(ID, Var, Val) switch(ID)                                                      \
                   { case DATATYPE_ID_BOOL:     Var.b = (uint8_t) Val; break;                   \
                     case DATATYPE_ID_FLOAT:    Var.f = (float) Val; break;                     \
                     case DATATYPE_ID_PROZENT:  Var.p = (uint8_t) Val; break;                   \
                     case DATATYPE_ID_HEX:      Var.x = (uint16_t) Val; break;                   \
                     case DATATYPE_ID_UNINT:    Var.un = (uint16_t) Val; break;                 \
                   }

#define DataNegate(ID, Var) switch(ID)                                                          \
                   { case DATATYPE_ID_BOOL:     Var.b = Var.b; break;                           \
                     case DATATYPE_ID_FLOAT:    Var.f = -Var.f; break;                          \
                     case DATATYPE_ID_PROZENT:  Var.p = Var.p; break;                           \
                     case DATATYPE_ID_HEX:      Var.x = Var.x; break;                           \
                     case DATATYPE_ID_UNINT:    Var.un = Var.un; break;                         \
                   }

#define DataWritetoString(ID, Var, buffer) switch(ID)                                             \
                   { case DATATYPE_ID_BOOL:     sprintf(buffer, "%u",Var.b); break;               \
                     case DATATYPE_ID_FLOAT:    sprintf(buffer, "%f",Var.f); break;               \
                     case DATATYPE_ID_PROZENT:  sprintf(buffer, "%u",Var.p); break;               \
                     case DATATYPE_ID_HEX:      sprintf(buffer, "%X",Var.x); break;               \
                     case DATATYPE_ID_UNINT:    sprintf(buffer, "%"PRIu16,Var.un); break;          \
                     case DATATYPE_ID_ROM:      sprintf(buffer, "%2X%2X:%2X%2X:%2X%2X:%2X%2X",Var.ROM[0],Var.ROM[1],Var.ROM[2],Var.ROM[3],Var.ROM[4],Var.ROM[5],Var.ROM[6],Var.ROM[7]); break;          \
                   }

/****************************************

DEFINITION Datatypes

****************************************/

enum DATATYPE{
    DATATYPE_ID_BOOL,
    DATATYPE_ID_FLOAT,
    DATATYPE_ID_PROZENT,
    DATATYPE_ID_HEX,
    DATATYPE_ID_UNINT,
    DATATYPE_ID_ROM
};

struct DataType DATATYPE_BOOL;
struct DataType DATATYPE_FLOAT;
struct DataType DATATYPE_PROZENT;
struct DataType DATATYPE_HEX;
struct DataType DATATYPE_UNINT;
struct DataType DATATYPE_ROM;

extern GUI_CONST_STORAGE GUI_BITMAP bmFliekomma;
extern GUI_CONST_STORAGE GUI_BITMAP bmDataType_D;
extern GUI_CONST_STORAGE GUI_BITMAP bmDataType_Int;
extern GUI_CONST_STORAGE GUI_BITMAP bmDataType_IO;
extern GUI_CONST_STORAGE GUI_BITMAP bmDataType_P;

void Firmware_Init_DataTypes();
uint8_t Firmware_DataError(uint8_t ID);
