#ifndef __DIALOG_NEWTIMEREVENT_H__
#define __DIALOG_NEWTIMEREVENT_H__

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 			(GUI_ID_USER + 0x00)
#define ID_LISTWHEEL_HOURS 		(GUI_ID_USER + 0x04)
#define ID_LISTWHEEL_MINUTES 	(GUI_ID_USER + 0x05)
#define ID_LISTWHEEL_DOW 		(GUI_ID_USER + 0x07)
#define ID_TEXTBOX_0 			(GUI_ID_USER + 0x08)
#define ID_TEXTBOX_1 			(GUI_ID_USER + 0x09)
#define ID_BUTTON_ACCEPT 		(GUI_ID_USER + 0x0A)
#define ID_TEXTBOX_3 			(GUI_ID_USER + 0x0C)
#define ID_SPINBOX_0 			(GUI_ID_USER + 0x0D)
#define ID_CHECKBOX_0 			(GUI_ID_USER + 0x0E)



/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#define ListWheel_Height		80
#define ListWheel_LineHeight	20

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aTimerEventPageCreate[] = {
  { WINDOW_CreateIndirect, 		"Window", 			ID_WINDOW_0, 		 	 0,  52, 480, 220, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Hours", 			ID_LISTWHEEL_HOURS, 	190,  40,  40,  ListWheel_Height, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Minutes", 			ID_LISTWHEEL_MINUTES, 	230,  40,  40,  ListWheel_Height, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"DayOfWeek", 		ID_LISTWHEEL_DOW, 		40,  40,  100,  ListWheel_Height, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"Eintrag speichern", ID_BUTTON_ACCEPT, 		110, 170, 260,  40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"Wochentag:", 		ID_TEXTBOX_0, 			40, 18, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"Uhrzeit:", 		ID_TEXTBOX_1, 			190, 18, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"Temperatur [°C]", 		ID_TEXTBOX_3, 		300, 18, 140, 20, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, 	"Temperatur", 		ID_SPINBOX_0, 			305, 60, 120, 60, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, 	"Wöchentliche Wiederholung", ID_CHECKBOX_0, 110, 130, 300, 30, 0, 0x0, 0 },
};

WM_HWIN Create_TimerEvent_Page(void);
void Update_TimerEvent_Page(WM_HWIN * MainWindow);

#endif // __DIALOG_NEWTIMEREVENT_H__
