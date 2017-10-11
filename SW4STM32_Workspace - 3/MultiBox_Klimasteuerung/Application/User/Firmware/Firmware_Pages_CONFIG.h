#pragma once

#include "GUI.h"
#include "WM.h"

#include "Layout_Config.h"

#include "Firmware_Page_Hardware.h"
#include "Firmware_Page_RTC.h"


struct Page {
    WM_HWIN (* Create)(void);                           /**<\brief Pointer to CreateMain Function*/
    void ( *Update)(WM_HWIN * MainWindow);             /**<\brief Pointer to UpdateMain Function*/

    char Name[20];
};

struct Page HardwarePage;
struct Page RTC_Page;



void Firmware_Init_Pages();
