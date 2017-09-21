#pragma once

#include "Clickboards_Conf.h"

#define DAC2_ACK                 (0b01100000)
#define DAC2_CH0                 (0b00000000)
#define DAC2_CH1                 (0b01000000)
#define DAC2_CH2                 (0b10000000)
#define DAC2_CH3                 (0b11000000)
#define DAC2_CH(__channel__)     (__channel__ << 6)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

struct clickBoard * DAC2_Current;

void initChipSelect_DAC2();
void DAC2click_SPI_Init();
void DAC2click_Select(struct clickBoard * Board);
void DAC2click_set(unsigned short channel, uint16_t Value);
