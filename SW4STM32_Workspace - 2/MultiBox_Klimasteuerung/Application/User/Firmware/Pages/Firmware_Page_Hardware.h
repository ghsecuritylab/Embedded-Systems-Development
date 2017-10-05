#pragma once

#include "DIALOG.h"
#include "Layout_CONFIG.h"
#include "GUIControl.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define PAGE_HARDWARE_WINDOW_0 (GUI_ID_USER + 0x00)
#define PAGE_HARDWARE_BUTTON_0 (GUI_ID_USER + 0x01)
#define PAGE_HARDWARE_BUTTON_1 (GUI_ID_USER + 0x02)
#define PAGE_HARDWARE_BUTTON_2 (GUI_ID_USER + 0x03)
#define PAGE_HARDWARE_BUTTON_3 (GUI_ID_USER + 0x04)
#define PAGE_HARDWARE_BUTTON_4 (GUI_ID_USER + 0x05)
#define PAGE_HARDWARE_BUTTON_5 (GUI_ID_USER + 0x06)
#define PAGE_HARDWARE_BUTTON_6 (GUI_ID_USER + 0x07)
#define PAGE_HARDWARE_BUTTON_7 (GUI_ID_USER + 0x08)
#define PAGE_HARDWARE_LISTVIEW_0 (GUI_ID_USER + 0x0A)
#define PAGE_HARDWARE_TEXT_0 (GUI_ID_USER + 0x0B)
#define PAGE_HARDWARE_BUTTON_8 (GUI_ID_USER + 0x0C)
#define PAGE_HARDWARE_BUTTON_9 (GUI_ID_USER + 0x0D)

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_HardwarePage[] = {
  { WINDOW_CreateIndirect, "Window", PAGE_HARDWARE_WINDOW_0, 0, 52, 480, 220, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB8", PAGE_HARDWARE_BUTTON_0, 10, 130, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB1", PAGE_HARDWARE_BUTTON_1, 90, 85, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB2", PAGE_HARDWARE_BUTTON_2, 170, 85, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB3", PAGE_HARDWARE_BUTTON_3, 250, 85, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB4", PAGE_HARDWARE_BUTTON_4, 330, 85, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB5", PAGE_HARDWARE_BUTTON_5, 410, 40, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB6", PAGE_HARDWARE_BUTTON_6, 410, 130, 60, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MB7", PAGE_HARDWARE_BUTTON_7, 9, 39, 60, 80, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", PAGE_HARDWARE_LISTVIEW_0, 90, 11, 300, 60, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", PAGE_HARDWARE_TEXT_0, 90, 175, 300, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "CAN", PAGE_HARDWARE_BUTTON_8, 10, 10, 60, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "AdapBoard", PAGE_HARDWARE_BUTTON_9, 410, 10, 60, 20, 0, 0x0, 0 },
};

WM_HWIN CreateHardwarePage(void);
void UpdateHardwarePage(WM_HWIN * MainWindow);

