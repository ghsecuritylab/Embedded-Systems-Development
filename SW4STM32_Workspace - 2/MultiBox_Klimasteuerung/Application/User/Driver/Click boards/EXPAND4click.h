#pragma once

#include "Clickboards_Conf.h"

struct clickBoard * EXPAND4_Current;

extern void EXPAND4click_SPI_Init();
extern void EXPAND4click_Select(struct clickBoard * Board);
extern void EXPAND4click_set(uint8_t Ports);
