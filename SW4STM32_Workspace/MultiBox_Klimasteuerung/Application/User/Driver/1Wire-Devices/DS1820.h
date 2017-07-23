#pragma once

#include "AdapterBoard_OneWire.h"

void DS1820_askTemp(uint8_t * ROM);
uint8_t DS1820_isTemp();

union Data * DS18x20_readTemp(uint8_t * ROM);
union Data * DS18S20_readTemp(uint8_t * ROM);
union Data * DS18B20_readTemp(uint8_t * ROM);

float DS18x20_getTemp(uint8_t * ROM);
float DS18S20_getTemp(uint8_t * ROM);
float DS18B20_getTemp(uint8_t * ROM);
