#include "Project_Page_Main_3.h"
#include "Dialog_NewTimerEvent.h"
#include "GUIControl.h"
#include "time_switch.h"

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

extern void Update_EventList(void);

// USER START (Optionally insert additional static code)
static char * apDayOfWeek[] = { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };

static char * apMinSec[] = { "00", "01", "02", "03", "04", "05", "06", "07",
		"08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31",
		"32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43",
		"44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55",
		"56", "57", "58", "59" };

static char * apHour[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08",
		"09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23" };

/*********************************************************************
 *
 *       _cbDialog
 */
static void _cbTimerEvent_Page(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int NCode;
	int Id;
	WM_HWIN hWin = pMsg->hWin;

	int LineHeight = ListWheel_LineHeight;
	int ListWheelHeight = ListWheel_Height;
	unsigned int InitItemSel = 0;

	TimeSwitch_Event event;

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

	    //
	    // Initialization of 'Text'
	    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXTBOX_0);
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXTBOX_1);
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXTBOX_3);
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_ACCEPT);
		BUTTON_SetFont(hItem, GUI_FONT_20_1);

	    //
	    // Initialization of 'Spinbox'
	    //
	    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
	    SPINBOX_SetFont(hItem, GUI_FONT_20_1);
	    SPINBOX_SetRange(hItem, 16, 30);
	    SPINBOX_SetValue(hItem, 20);

	    //
	    // Initialization of 'Checkbox'
	    //
	    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
	    CHECKBOX_SetText(hItem, "Wöchentliche Wiederholung");
	    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);

		//
		// Initialization of 'Day of Week'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DOW);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_20_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apDayOfWeek); i++) {
			LISTWHEEL_AddString(hItem, apDayOfWeek[i]);
		}

		//
		// Initialization of 'Hours'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOURS);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_20_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apHour); i++) {
			LISTWHEEL_AddString(hItem, apHour[i]);
		}

		//
		// Initialization of 'Minutes'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MINUTES);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_20_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apMinSec); i++) {
			LISTWHEEL_AddString(hItem, apMinSec[i]);
		}

		break;
	case WM_SET_FOCUS:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case WM_NOTIFICATION_LOST_FOCUS:
			WM_DeleteWindow(hWin);
			break;
		default:
			break;
		}
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_LISTWHEEL_DOW: // Notifications sent by 'Day of Week'-ListWheel
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DOW);
				int lw_item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, lw_item);
				break;
			}
			break;
		case ID_LISTWHEEL_HOURS: // Notifications sent by 'Hours'-ListWheel
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOURS);
				int lw_item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, lw_item);
				break;
			}
			break;
		case ID_LISTWHEEL_MINUTES: // Notifications sent by 'Minutes'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MINUTES);
				int lw_item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, lw_item);
				break;
			}
			break;
		case ID_BUTTON_ACCEPT: // Notifications sent by 'Einstellungen übernehmen'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:

				/* Day of Week */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DOW);
				event.startDay = LISTWHEEL_GetSel(hItem) + 1;

				/* Hours */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOURS);
				event.startTime.Hours = LISTWHEEL_GetSel(hItem);

				/* Minutes */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MINUTES);
				event.startTime.Minutes = LISTWHEEL_GetSel(hItem);

				/* Repeat */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
				event.Repeat = CHECKBOX_IsChecked(hItem);

				/* Temperature */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
				event.Temperature = (float)SPINBOX_GetValue(hItem);

				event.ID = EventListEntryCount;

				timeSwitch_setNewEntry(&event);

				Update_EventList();

				WM_DeleteWindow(hWin);
				//BlockChange = 0;

				break;
			}
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */
void Update_TimerEvent_Page(WM_HWIN * MainWindow) {
//	static char cTime[16];
//	static char cDate[16];
//	static char Text[32];
//	WM_HWIN hItem;
//
//	if(RTC3click_Available){
//		RTC3click_getTimeAsString(cTime);
//		RTC3click_getDateAsString(cDate);
//	}else{
//		RTC_getTimeAsString(cTime);
//		RTC_getDateAsString(cDate);
//	}
//
//
//	sprintf(Text, "Uhrzeit: %s", cTime);
//	hItem = WM_GetDialogItem(*MainWindow, ID_TEXTBOX_1);
//	TEXT_SetText(hItem, Text);
//
//	sprintf(Text, "Datum: %s", cDate);
//	hItem = WM_GetDialogItem(*MainWindow, ID_TEXTBOX_0);
//	TEXT_SetText(hItem, Text);
}

/*********************************************************************
 *
 *       CreateWindow
 */
WM_HWIN Create_TimerEvent_Page(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aTimerEventPageCreate, GUI_COUNTOF(_aTimerEventPageCreate),
			_cbTimerEvent_Page, WM_HBKWIN, 0, 0);

	WindowChange_Handled = 1;

	return hWin;
}

/*************************** End of file ****************************/
