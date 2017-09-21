#pragma once

#include "stm32f7xx_hal.h"

#include "stdint.h"

#include "I2C-Driver.h"
#include "SPI-Driver.h"

#include "AdapterBoard_MikrobusSocket.h"
#include "AdapterBoard_MCUExt.h"

#include "Project_MemoryStructures_CONFIG.h"

struct clickBoard {
    struct MikrobusSocket * MB;

    uint8_t Address;

    char Name[20];

    struct ParameterGroup * Group;
};

struct clickBoard * ClickBoardArray[8];
uint8_t ClickBoardArrayCount;

uint8_t RTC3click_Available;

extern void Firmware_ProcessLogic_ErrorHandler(uint8_t ErrorType);


struct clickBoard * Create_clickBoard(uint8_t MB, uint8_t Address, char * Name, char * Description);
void Update_Clickboard(struct clickBoard * clickBoard);
