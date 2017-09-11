#pragma once

#include "GUI.h"
#include "WM.h"

#include "Layout_Config.h"

#include "Firmware_Pages_CONFIG.h"

#include "Project_Page_Main_1.h"
#include "Project_Page_Main_2.h"
#include "Project_Page_Main_3.h"


/**START USER CONFIG**/
/**
    Über MAINPAGE_COUNT wird die Anzahl der verfügbaren MainPages festgelegt

    Anschließend werden alle benötigten Pages definiert.
    Sowohl MainPages als auch normale Pages.

    Nomenklatur:
    Der jeweilige Art soll zwecks Übersichtlichkeit im Strukturnamen enthalten sein:

    z.B.
    MainPage_ABC
    bzw.
    PAge_XYZ
**/

#define MAINPAGE_COUNT      (3)

struct Page MainPage_1;
struct Page MainPage_2;
struct Page MainPage_3;

/**END USER CONFIG**/

void Project_Init_Pages();


struct Page * MainPageArray[MAINPAGE_COUNT +1];
