#pragma once


#include <stdio.h>

//GUI & WindowManager
#include "GUI.h"
#include "WM.h"
#include "DIALOG.h"

//Global Variables
#include "Layout_CONFIG.h"

//Memory
#include "MemoryStructures.h"

//Windows
#include "MenuView.h"
#include "Navigationpanel.h"
#include "Parameters_Edit.h"

//SD-Card
#include "stm32_ub_fatfs.h"

//OneWire
extern struct Parameter ** OneWire_Devices_Parameter;

//Pointer Update --> Move to GuiControl
void BSP_Pointer_Update(void);

void InitMainTask();
void MainTask(void);
void GUI_Error_Handler(char *title, char *text);
void SaveScreenshot();



/****************************************

DEFINITION Structs & Variables

****************************************/

int state;                       //state = 0 --> MainWindow, = 1, MenuWindow
int ReDrawStopped;               //Flag for stopping Redrawing (1 => Stopped)
int WindowChange_Handled;        //Handle Variable, has to be set to 1 for changing Window according to state
int BlockChange;                 //Handle Variable, has to be set to 1 for changing Menu according to Menu_Active
int DialogOpen_Handled;          //Handle Variable, has to be set to 1 for changing Menu according to Menu_Active
int ParameterChange_Handled;      //Handle Variable, hast to be set to 1 for redrawing updated Parameters
int OneWire_Devices_ERROR;
int Menu_isDynamic;

//SD-Screenshot Save
extern uint8_t SD_LOCK;
uint32_t LastScreenshot;
uint32_t FileCounter;
extern FIL FileObj;
char TempScreenshot[200];
uint16_t TempScreenshotByteCounter;


struct MenuPage *Menu_Active;        //Pointer to Active MenuPage
struct Parameter *Parameter_Active;  //Pointer to Active MainPage
struct Page *Page_Active;        //Pointer to Active MainPage
struct MenuPage *Menu_Home;          //Pointer to Home Menu / First Menustage
struct MenuPage *Menu_Dynamic;          //Pointer to Home Menu / First Menustage
