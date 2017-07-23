#pragma once

//MCU-Treiber
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_can.h"

//Board-Treiber
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_qspi.h"
#include "stm32746g_discovery_sdram.h"

//Bibliotheken
#include "stm32_ub_fatfs.h"
/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

//
#include "MemoryStructures.h"

#include "GUI.h"
#include "WM.h"

//GUI-Interface
#include "LoadingScreen.h"
#include "GUIControl.h"

//ProcessControl
#include "Firmware_ProcessControl.h"

uint8_t Gui_Update_Counter;

#define CANx_RX_IRQHandler             CAN1_RX0_IRQHandler
