#pragma once

#include "stm32f7xx_hal.h"
#include "I2C-Driver.h"
#include "AdapterBoard_MikrobusSocket.h"

#include "GUI.h"


#define I2C_IO_ACK_W            (0b00000001)
#define I2C_IO_ACK_R            (0b00000000)
#define I2C_IO_ADDR0            (0b00000000)
#define I2C_IO_ADDR1            (0b00000010)
#define I2C_IO_ADDR2            (0b00000100)
#define I2C_IO_ADDR3            (0b00000110)
#define I2C_IO_ADDR4            (0b00001000)
#define I2C_IO_ADDR5            (0b00001010)
#define I2C_IO_ADDR6            (0b00001100)
#define I2C_IO_ADDR7            (0b00001110)

#define PIN_0_In                (0b00000001)
#define PIN_1_In                (0b00000010)
#define PIN_2_In                (0b00000100)
#define PIN_3_In                (0b00001000)
#define PIN_4_In                (0b00010000)
#define PIN_5_In                (0b00100000)
#define PIN_6_In                (0b01000000)
#define PIN_7_In                (0b10000000)



struct I2C_IO {
    uint8_t I2CAddress;
    uint8_t Config;
    uint8_t OutputState;
    uint8_t Error;
};

struct I2C_IO * I2C_IO_Current;


void I2C_IO_SetOut_and_Config();
void I2C_IO_I2C_Init();
uint8_t * I2C_IO_GetPin(struct I2C_IO * IC, uint8_t Pin);
void I2C_IO_SetPin(struct I2C_IO * IC, uint8_t Pin, uint8_t state);
void I2C_IO_Select(struct I2C_IO * IC);
void I2C_IO_USER_SetLED(uint8_t R, uint8_t G, uint8_t B);
void I2C_IO_USER_SetEXT(uint8_t EXT1, uint8_t EXT2, uint8_t EXT3);
void I2C_IO_USER_SetBuzzer(uint32_t time, uint16_t Frequency);
uint8_t * I2C_IO_USER_GetKonfig();
void I2C_IO_USER_SetALARM();
void delayUS(uint32_t us);
