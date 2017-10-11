#pragma once

//Include Standard Libs
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Include STemWin and GUIControl
#include "GUIControl.h"
#include "GUI.h"
#include "DIALOG.h"
#include "WM.h"

//Include Layout
#include "Layout_CONFIG.h"

//Include Memory Structures
#include "MemoryStructures.h"

//Include Driver
#include "DriverConf.h"

/****************************************

DEFINITION EditTypes

****************************************/

enum EDITTYPE{
    EDITTYPE_NOEDIT = 1,
    EDITTYPE_TOGGLE,
    EDITTYPE_KEYPAD,
    EDITTYPE_KEYPAD_HEX,
    EDITTYPE_UPDOWN,
    EDITTYPE_ONEWIREROM,
};


/****************************************

DEFINITION EditTypes - KEYPAD

****************************************/

#define ID_KEYPAD_WINDOW_0          (GUI_ID_USER + 0xE9)
#define ID_KEYPAD_TEXT_0            (GUI_ID_USER + 0xEA)
#define ID_KEYPAD_BUTTON_OK         (GUI_ID_USER + 0xEB)
#define ID_KEYPAD_BUTTON_CANCEL     (GUI_ID_USER + 0xEC)
#define ID_KEYPAD_BUTTON_BACKSPACE  (GUI_ID_USER + 0xED)
#define ID_KEYPAD_BUTTON_SEPERATOR  (GUI_ID_USER + 0xEE)
#define ID_KEYPAD_BUTTON_PLUSMINUS  (GUI_ID_USER + 0xEF)
#define ID_KEYPAD_BUTTON_0          (GUI_ID_USER + 0xF0)

/****************************************

DEFINITION EditTypes - KEYPAD_HEX

****************************************/

#define ID_KEYPAD_HEX_WINDOW_0          (GUI_ID_USER + 0xE9)
#define ID_KEYPAD_HEX_TEXT_0            (GUI_ID_USER + 0xEA)
#define ID_KEYPAD_HEX_BUTTON_OK         (GUI_ID_USER + 0xEB)
#define ID_KEYPAD_HEX_BUTTON_CANCEL     (GUI_ID_USER + 0xEC)
#define ID_KEYPAD_HEX_BUTTON_BACKSPACE  (GUI_ID_USER + 0xED)
#define ID_KEYPAD_HEX_BUTTON_SEPERATOR  (GUI_ID_USER + 0xEE)
#define ID_KEYPAD_HEX_BUTTON_PLUSMINUS  (GUI_ID_USER + 0xEF)
#define ID_KEYPAD_HEX_BUTTON_0          (GUI_ID_USER + 0xF0)

/****************************************

DEFINITION EditTypes - UPDOWN

****************************************/

#define ID_UPDOWN_WINDOW_0              (GUI_ID_USER + 0xF0)
#define ID_UPDOWN_SPINBOX_TEXT          (GUI_ID_USER + 0xF1)
#define ID_UPDOWN_SPINBOX_BUTTON_UP     (GUI_ID_USER + 0xF2)
#define ID_UPDOWN_SPINBOX_BUTTON_DOWN   (GUI_ID_USER + 0xF3)
#define ID_UPDOWN_BUTTON_CANCEL         (GUI_ID_USER + 0xF4)
#define ID_UPDOWN_BUTTON_OK             (GUI_ID_USER + 0xF5)

/****************************************

DEFINITION EditTypes - ONEWIREROM

****************************************/

#define ID_ONEWIREROM_WINDOW_0              (GUI_ID_USER + 0xF0)
#define ID_ONEWIREROM_SPINBOX_TEXT          (GUI_ID_USER + 0xF1)
#define ID_ONEWIREROM_SPINBOX_TEMPTEXT      (GUI_ID_USER + 0xF2)
#define ID_ONEWIREROM_SPINBOX_BUTTON_UP     (GUI_ID_USER + 0xF3)
#define ID_ONEWIREROM_SPINBOX_BUTTON_DOWN   (GUI_ID_USER + 0xF4)
#define ID_ONEWIREROM_BUTTON_CANCEL         (GUI_ID_USER + 0xF5)
#define ID_ONEWIREROM_BUTTON_OK             (GUI_ID_USER + 0xF6)

/****************************************

DEFINITION EditTypes - TOGGLE

****************************************/

#define ID_TOGGLE_WINDOW_0              (GUI_ID_USER + 0xF0)
#define ID_TOGGLE_TEXT                  (GUI_ID_USER + 0xF1)
#define ID_TOGGLE_BUTTON_ON             (GUI_ID_USER + 0xF2)
#define ID_TOGGLE_BUTTON_OFF            (GUI_ID_USER + 0xF3)
#define ID_TOGGLE_BUTTON_CANCEL         (GUI_ID_USER + 0xF4)
#define ID_TOGGLE_BUTTON_OK             (GUI_ID_USER + 0xF5)

extern int Dialog_DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

/****************************************

DEFINITION Icons

****************************************/

extern GUI_CONST_STORAGE GUI_BITMAP bmUp;
extern GUI_CONST_STORAGE GUI_BITMAP bmDown;
extern GUI_CONST_STORAGE GUI_BITMAP bmStop;
extern GUI_CONST_STORAGE GUI_BITMAP bmBack;

extern GUI_CONST_STORAGE GUI_BITMAP bmOk;

extern GUI_CONST_STORAGE GUI_BITMAP bmCancel;

char * ValConvStr[5];
char ValueString[25];
struct Parameter * AktParameter;

void Edit_UpDown();
void Edit_Keypad_Hex(int Hex);
void Edit_Toggle();
void Edit_OneWireROM();

void Increment();
void Decrement();

void checkRange_OneWire(WM_HWIN * hWin);

void getTemp();
