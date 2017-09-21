#pragma once

#include "Clickboards_Conf.h"

#define EXPAND_ACK_W            (0b01000000)
#define EXPAND_ACK_R            (0b01000001)
#define EXPAND_ADDR_DEF         (0b00000000)
#define EXPAND_ADDR1            (0b00000010)
#define EXPAND_ADDR2            (0b00000100)
#define EXPAND_ADDR3            (0b00000110)
#define EXPAND_ADDR4            (0b00001000)
#define EXPAND_ADDR5            (0b00001010)
#define EXPAND_ADDR6            (0b00001100)
#define EXPAND_ADDR7            (0b00001110)

#define EXPAND_REG_IODIRA       (0x00)
#define EXPAND_REG_IODIRB       (0x01)
#define EXPAND_REG_IPOLA        (0x02)
#define EXPAND_REG_IPOLB        (0x03)
#define EXPAND_REG_GPINTENA     (0x04)
#define EXPAND_REG_GPINTENB     (0x05)
#define EXPAND_REG_DEFVALA      (0x06)
#define EXPAND_REG_DEFVALB      (0x07)
#define EXPAND_REG_INTCONA      (0x08)
#define EXPAND_REG_INTCONB      (0x09)
#define EXPAND_REG_IOCONA       (0x0A)
#define EXPAND_REG_IOCONB       (0x0B)
#define EXPAND_REG_GPPUA        (0x0C)
#define EXPAND_REG_GPPUB        (0x0D)
#define EXPAND_REG_INTFA        (0x0E)
#define EXPAND_REG_INTFB        (0x0F)
#define EXPAND_REG_INTCAPA      (0x10)
#define EXPAND_REG_INTCAPB      (0x11)
#define EXPAND_REG_GPIOA        (0x12)
#define EXPAND_REG_GPIOB        (0x13)
#define EXPAND_REG_OLATA        (0x14)
#define EXPAND_REG_OLATB        (0x15)

struct clickBoard * EXPAND_Current;

void EXPANDclick_ConfigureChip();
void EXPANDclick_Init_Interrupt();
void EXTI9_5_IRQHandler();
void EXPANDclick_Reset();
void EXPANDclick_Send(uint8_t Register, uint8_t Data) ;
uint8_t EXPANDclick_Receive(uint8_t Register);
void EXPANDclick_ChipSelect();
void EXPANDclick_ChipDeSelect();
void EXPANDclick_Select(struct clickBoard * Board);
void EXPANDclick_SPI_Init();
