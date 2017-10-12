#pragma once

#include <stdio.h>

#include "DIALOG.h"
#include "GUI.h"

#include "Layout_CONFIG.h"
#include "Firmware_MenuView_CONFIG.h"
#include "Project_MenuView_CONFIG.h"

#include "Parameters_Edit.h"
#include "Project_MemoryStructures_CONFIG.h"
#include "Firmware_MemoryStructures_CONFIG.h"

//Include Bitmaps
extern GUI_CONST_STORAGE GUI_BITMAP bmIAV;

#define ID_LOADINGSCREEN_WINDOW_0       (GUI_ID_USER + 0x00)
#define ID_LOADINGSCREEN_PROGBAR_0      (GUI_ID_USER + 0x01)
#define ID_LOADINGSCREEN_IMAGE_0        (GUI_ID_USER + 0x02)
#define ID_LOADINGSCREEN_TEXT_0         (GUI_ID_USER + 0x03)

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "LoadingScreen", ID_LOADINGSCREEN_WINDOW_0, 0, 0, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT + HEADER_HEIGHT, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_LOADINGSCREEN_PROGBAR_0, MENU_WINDOW_WIDTH / 6, 180, MENU_WINDOW_WIDTH / 6 * 4, HEADER_HEIGHT, 0, 0x0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_LOADINGSCREEN_IMAGE_0, 40, -30, 400, 210, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "", ID_LOADINGSCREEN_TEXT_0, MENU_WINDOW_WIDTH / 6, 180 + HEADER_HEIGHT, MENU_WINDOW_WIDTH / 6 * 4, 40, TEXT_CF_VCENTER | TEXT_CF_HCENTER, 0x0, 0 },
};


void _cbDialog(WM_MESSAGE * pMsg);
WM_HWIN CreateLoadingScreen(void);
