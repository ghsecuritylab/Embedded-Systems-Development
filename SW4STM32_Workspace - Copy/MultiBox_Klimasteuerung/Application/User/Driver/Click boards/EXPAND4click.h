#pragma once

#include "Clickboards_Conf.h"

struct clickBoard * EXPAND4_Current;

void EXPAND4click_SPI_Init();
void EXPAND4click_Select(struct clickBoard * Board);
void EXPAND4click_set(uint8_t Ports);
