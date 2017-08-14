#pragma once

#include "stm32f7xx_hal.h"
#include "AdapterBoard_I2C_IOs.h"

#include "I2C-Driver.h"
#include "SPI-Driver.h"

struct MikrobusSocket {
    GPIO_TypeDef * CS_Port;
    uint16_t CS_Pin;

    GPIO_TypeDef * INT_Port;
    uint16_t INT_Pin;

    struct I2C_IO * PWM_I2C_IO;
    uint8_t PWM_I2C_Pin;

    struct I2C_IO * AN_I2C_IO;
    uint8_t AN_I2C_Pin;

    struct I2C_IO * RST_I2C_IO;
    uint8_t RST_I2C_Pin;



    uint8_t Error;

    //InterruptRoutine
};

struct MikrobusSocket MB1;
struct MikrobusSocket MB2;
struct MikrobusSocket MB3;
struct MikrobusSocket MB4;
struct MikrobusSocket MB5;
struct MikrobusSocket MB6;
struct MikrobusSocket MB7;
struct MikrobusSocket MB8;

static struct MikrobusSocket * MB_Array[8] = {&MB1,&MB2,&MB3,&MB4,&MB5,&MB6,&MB7,&MB8};



struct I2C_IO IC1;
struct I2C_IO IC2;
struct I2C_IO IC3;
struct I2C_IO IC_USER;

/****************
    FUNKTIONEN
****************/

void CheckMikrobus(struct MikrobusSocket * MB, uint8_t state);

void Init_Mikrobus(void);
void Init_Error(struct MikrobusSocket * MB, uint8_t Error);
void Init_CS(struct MikrobusSocket * MB, GPIO_TypeDef * Port, uint16_t Pin);
void Init_INT(struct MikrobusSocket * MB, GPIO_TypeDef * Port, uint16_t Pin);
void Init_PWM(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin);
void Init_RST(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin);
void Init_AN(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin);
void SetPWM(struct MikrobusSocket * MB, uint8_t state);

void SetAN(struct MikrobusSocket * MB, uint8_t state);
void SetRST(struct MikrobusSocket * MB, uint8_t state);
void SetCS(struct MikrobusSocket * MB, uint8_t state);
void RST_ALL(struct MikrobusSocket * MB, uint8_t state);
