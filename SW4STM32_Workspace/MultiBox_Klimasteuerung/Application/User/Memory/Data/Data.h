#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GUI.h"

union Data {
    float f;
    uint8_t b;      //Bit
    uint8_t p;      //Prozent
    uint16_t un;    //Unsigned Number 16bit
    uint16_t x;      //2-bit Hexadecimal
    uint8_t ROM[9]; //8x8-bit
};

struct DataType {
    int ID;
    int Count;
    char InStr[10];
    char OutStr[10];

    void * Var;

    const GUI_BITMAP * ICON;

};
