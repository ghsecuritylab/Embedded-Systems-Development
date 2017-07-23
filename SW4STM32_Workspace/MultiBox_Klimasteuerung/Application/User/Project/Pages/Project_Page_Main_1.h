#pragma once

#include <stdio.h>

#include "DIALOG.h"
#include "Layout_Config.h"
#include "GUIControl.h"

#define ID_WINDOW_TC 		(GUI_ID_USER + 0x00)
#define ID_DROPDOWN_TC 		(GUI_ID_USER + 0x01)
#define ID_TEXT_TITLE1 		(GUI_ID_USER + 0x02)
#define ID_TEXT_TC1 		(GUI_ID_USER + 0x03)
#define ID_TEXT_TC2 		(GUI_ID_USER + 0x04)
#define ID_SPINBOX_TCSEL 	(GUI_ID_USER + 0x05)
#define ID_TEXT_TITLE2 		(GUI_ID_USER + 0x06)
#define ID_LISTVIEW_TC 		(GUI_ID_USER + 0x07)
#define ID_TEXT_TC9 		(GUI_ID_USER + 0x0E)
#define ID_TEXT_TEMPIST 	(GUI_ID_USER + 0x0F)
#define ID_TEXT_TC10 		(GUI_ID_USER + 0x10)
#define ID_TEXT_MODE 		(GUI_ID_USER + 0x11)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Main1[] = {
		  { WINDOW_CreateIndirect, "Window", ID_WINDOW_TC, 0, 52, 480, 220, 0, 0x0, 0 },
		  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_TC, 95, 50, 155, 80, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "Temperaturregelung", ID_TEXT_TITLE1, 25, 5, 186, 20, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "Regelgr��e:", ID_TEXT_TC1, 20, 52, 80, 20, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "F�hrungsgr��e [�C]:", ID_TEXT_TC2, 20, 93, 120, 20, 0, 0x0, 0 },
		  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_TCSEL, 160, 82, 84, 40, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "Messwerte", ID_TEXT_TITLE2, 269, 5, 200, 20, 0, 0x0, 0 },
		  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_TC, 272, 34, 180, 115, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "Messwert Regelgr��e:", ID_TEXT_TC9, 100, 170, 180, 20, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "20.0 �C", ID_TEXT_TEMPIST, 290, 170, 74, 20, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "          Aktueller Modus:", ID_TEXT_TC10, 100, 190, 185, 20, 0, 0x0, 0 },
		  { TEXT_CreateIndirect, "", ID_TEXT_MODE, 290, 190, 160, 20, 0, 0x0, 0 },
};

void _cbDialog_Main1(WM_MESSAGE * pMsg);
void UpdateMain1(WM_HWIN * MainWindow);
WM_HWIN CreateMain1(void);
