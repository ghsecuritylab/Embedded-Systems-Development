#pragma once

#include "Clickboards_Conf.h"

struct clickBoard * Template_Current;

void Templateclick_SPI_Init();
void Templateclick_I2C_Init();
void Templateclick_Select(struct clickBoard * Board, uint8_t Addr);
void Templateclick_set(unsigned short channel, uint8_t Val);
uint8_t * Templateclick_get(unsigned short channel);
