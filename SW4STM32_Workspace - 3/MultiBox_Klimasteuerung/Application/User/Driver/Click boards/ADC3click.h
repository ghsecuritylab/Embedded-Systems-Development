#pragma once

#include "Clickboards_Conf.h"

#define ADC3_ACK                 (0b11010000)
#define ADC3_READ                (0b00000001)
#define ADC3_WRITE               (0b00000000)


#define ADC3_CH0                 (0b00000000)
#define ADC3_CH1                 (0b00100000)
#define ADC3_CH2                 (0b01000000)
#define ADC3_CH3                 (0b01100000)

#define ADC3_CONVERSION_CONTINOUS   (0b00010000)
#define ADC3_SAMPLE_240SPS_12BIT    (0b00000000)
#define ADC3_SAMPLE_60SPS_14BIT     (0b00000100)
#define ADC3_SAMPLE_15SPS_16BIT     (0b00001000)
#define ADC3_PGAGAIN_X1             (0b00000000)
#define ADC3_PGAGAIN_X2             (0b00000001)
#define ADC3_PGAGAIN_X4             (0b00000010)
#define ADC3_PGAGAIN_X8             (0b00000011)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

struct clickBoard * ADC3_Current;

void ADC3click_I2C_Init();
void ADC3click_WriteConfig(uint8_t Channel, uint8_t ConversionMode, uint8_t SampleRate, uint8_t PGAGain);
void ADC3click_Select(struct clickBoard * Board, uint8_t Addr);
uint8_t * ADC3click_get(unsigned short channel);
