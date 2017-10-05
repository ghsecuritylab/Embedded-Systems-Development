#pragma once

#include "GUI.h"
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_TS 	(GUI_ID_USER + 0x00)
#define ID_LISTVIEW_TS 	(GUI_ID_USER + 0x01)
#define ID_BUTTON_NE 	(GUI_ID_USER + 0x02)
#define ID_BUTTON_EL 	(GUI_ID_USER + 0x03)
#define ID_TEXT_TITLE 	(GUI_ID_USER + 0x04)
#define ID_TEXT_SEL 	(GUI_ID_USER + 0x05)


/*********************************************************************
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogTimeSWCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_TS, 0, 52, 480, 220, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_TS, 20, 30, 320, 170, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Neuer Eintrag", ID_BUTTON_NE, 360, 60, 100, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Eintrag löschen", ID_BUTTON_EL, 360, 127, 100, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "", ID_TEXT_TITLE, 30, 4, 440, 21, 0, 0x0, 0 },
  { TEXT_CreateIndirect, ">", ID_TEXT_SEL, 8, 44, 10, 20, 0, 0x0, 0 },
};

void Update_TimerEventsPage(WM_HWIN * MainWindow);
WM_HWIN Create_TimerEventsPage(void);

void Update_EventList(void);
