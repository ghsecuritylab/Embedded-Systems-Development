#pragma once

#include "stm32f7xx_hal.h"

//Communication Driver
#include "1WIRE-Driver.h"
#include "I2C-Driver.h"
#include "SPI-Driver.h"

//AdapterBoard Driver
#include "AdapterBoard_CAN.h"
#include "AdapterBoard_I2C_IOs.h"
#include "AdapterBoard_MCUExt.h"
#include "AdapterBoard_MikrobusSocket.h"
#include "AdapterBoard_OneWire.h"

//Clickboard Driver
#include "ADC3click.h"
#include "ADCclick.h"
#include "DAC2click.h"
#include "DCMotor3click.h"
#include "EXPAND4click.h"
#include "EXPANDclick.h"
#include "PWMclick.h"
#include "RTC3click.h"

//SD-Card
#include "stm32_ub_fatfs.h"

//Sensors
#include "DS1820.h"

//Other
#include "RTC_Internal.h"


