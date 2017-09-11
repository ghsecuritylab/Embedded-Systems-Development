#pragma once

#include "Clickboards_Conf.h"

struct clickBoard * ADC_Current;

void initChipSelect_ADC();
void ADCclick_SPI_Init();
void ADCclick_Select(struct clickBoard * Board);
uint16_t * ADCclick_get(unsigned short channel);
