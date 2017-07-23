#pragma once

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
#define ID_TEXT_TITLE 		(GUI_ID_USER + 0x04)


/*********************************************************************
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_TS, 0, 52, 480, 220, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_TS, 16, 30, 300, 185, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Neuer Eintrag", ID_BUTTON_NE, 360, 60, 100, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Eintrag löschen", ID_BUTTON_EL, 360, 127, 100, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Temperatur Zeitschaltung", ID_TEXT_TITLE, 8, 4, 217, 21, 0, 0x0, 0 },
};

void _cbTimeSWDialog(WM_MESSAGE * pMsg);
void UpdateMain3(WM_HWIN * MainWindow);
WM_HWIN CreateTimeSWWindow(void);