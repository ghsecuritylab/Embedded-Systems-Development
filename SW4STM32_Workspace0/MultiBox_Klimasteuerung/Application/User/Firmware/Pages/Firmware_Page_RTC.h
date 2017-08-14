#ifndef __RTC_PAGE_H__
#define __RTC_PAGE_H__

#include "DIALOG.h"
#include "GUIControl.h"
#include "RTC3click.h"
#include "Firmware_ProcessControl.h"

extern uint8_t LOCK_RTC;
RTC_Time System_Time;
RTC_Date System_Date;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 			(GUI_ID_USER + 0x00)
#define ID_LISTWHEEL_DAYS 		(GUI_ID_USER + 0x01)
#define ID_LISTWHEEL_MONTHS 	(GUI_ID_USER + 0x02)
#define ID_LISTWHEEL_YEARS 		(GUI_ID_USER + 0x03)
#define ID_LISTWHEEL_HOURS 		(GUI_ID_USER + 0x04)
#define ID_LISTWHEEL_MINUTES 	(GUI_ID_USER + 0x05)
#define ID_LISTWHEEL_DOW 		(GUI_ID_USER + 0x07)
#define ID_TEXTBOX_0 			(GUI_ID_USER + 0x08)
#define ID_TEXTBOX_1 			(GUI_ID_USER + 0x09)
#define ID_BUTTON_ACCEPT 		(GUI_ID_USER + 0x0A)



/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aRTCPageCreate[] = {
  { WINDOW_CreateIndirect, 		"Window", 			ID_WINDOW_0, 		 	 0,  52, 480, 220, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Days", 			ID_LISTWHEEL_DAYS, 	 	200,  40,  40,  120, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Months", 			ID_LISTWHEEL_MONTHS, 	240,  40,  40,  120, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Years", 			ID_LISTWHEEL_YEARS, 	280,  40,  60,  120, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Hours", 			ID_LISTWHEEL_HOURS, 	370,  40,  40,  120, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"Minutes", 			ID_LISTWHEEL_MINUTES, 	410,  40,  40,  120, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, 	"DayOfWeek", 		ID_LISTWHEEL_DOW, 		 30,  40,  140,  120, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"Datum:", 			ID_TEXTBOX_0, 			 20,  5,  200,  20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"Uhrzeit:", 		ID_TEXTBOX_1, 			260,  5,  160,  20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"Einstellungen übernehmen", ID_BUTTON_ACCEPT, 	110, 170, 260,  40, 0, 0x0, 0 },
};

WM_HWIN Create_RTC_Page(void);
void Update_RTC_Page(WM_HWIN * MainWindow);

#endif // __RTC_PAGE_H__
