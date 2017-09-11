#include "Firmware_Page_RTC.h"

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

extern uint8_t RTC3click_Available;

// USER START (Optionally insert additional static code)
static char * apDayOfWeek[] = { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };

static char * apDay[] = { "01", "02", "03", "04", "05", "06", "07", "08", "09",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21",
		"22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };

static char * apMonth[] = { "01", "02", "03", "04", "05", "06", "07", "08",
		"09", "10", "11", "12" };

static char * apYear[] = { "2017", "2018", "2019", "2020", "2021", "2022",
		"2023", "2024", "2025", "2026", "2027", "2028", "2029", "2030", "2031",
		"2032", "2033", "2034", "2035", "2036", "2037", "2038", "2039", "2040",
		"2041", "2042", "2043", "2044", "2045", "2046" };

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
static void _cbRTC_Page(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int NCode;
	int Id;

	int LineHeight = 32;
	int ListWheelHeight = 120;
	unsigned int InitItemSel = 0;

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXTBOX_0);
		TEXT_SetFont(hItem, GUI_FONT_24_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXTBOX_1);
		TEXT_SetFont(hItem, GUI_FONT_24_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_ACCEPT);
		BUTTON_SetFont(hItem, GUI_FONT_24_1);

		//
		// Initialization of 'Day of Week'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DOW);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apDayOfWeek); i++) {
			LISTWHEEL_AddString(hItem, apDayOfWeek[i]);
		}


		//
		// Initialization of 'Days'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DAYS);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apDay); i++) {
			LISTWHEEL_AddString(hItem, apDay[i]);
		}

		//
		// Initialization of 'Months'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MONTHS);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apMonth); i++) {
			LISTWHEEL_AddString(hItem, apMonth[i]);
		}

		//
		// Initialization of 'Years'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_YEARS);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apYear); i++) {
			LISTWHEEL_AddString(hItem, apYear[i]);
		}

		//
		// Initialization of 'Hours'-ListWheel
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOURS);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_GRAY_60);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_GRAY_E7);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
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
		LISTWHEEL_SetFont(hItem, GUI_FONT_32_1);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTWHEEL_SetSnapPosition(hItem, (ListWheelHeight - LineHeight) / 2);
		LISTWHEEL_SetLineHeight(hItem, LineHeight);

		for (int i = 0; i < GUI_COUNTOF(apMinSec); i++) {
			LISTWHEEL_AddString(hItem, apMinSec[i]);
		}

		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_LISTWHEEL_DOW: // Notifications sent by 'Months'-ListWheel
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
		case ID_LISTWHEEL_DAYS: // Notifications sent by 'Days'-ListWheel
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DAYS);
				int lw_item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, lw_item);
				break;
			}
			break;
		case ID_LISTWHEEL_MONTHS: // Notifications sent by 'Months'-ListWheel
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MONTHS);
				int lw_item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, lw_item);
				break;
			}
			break;
		case ID_LISTWHEEL_YEARS: // Notifications sent by 'Years'-ListWheel
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_YEARS);
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
				System_Date.DayofWeek = LISTWHEEL_GetSel(hItem) + 1;

				/* Days */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DAYS);
				System_Date.Date = LISTWHEEL_GetSel(hItem) + 1;

				/* Months */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MONTHS);
				System_Date.Month = LISTWHEEL_GetSel(hItem) + 1;

				/* Years */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_YEARS);
				System_Date.Year = LISTWHEEL_GetSel(hItem) + 17;

				/* Hours */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOURS);
				System_Time.Hours = LISTWHEEL_GetSel(hItem);

				/* Minutes */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MINUTES);
				System_Time.Minutes = LISTWHEEL_GetSel(hItem);

				/* Seconds */
				System_Time.Seconds = 0;

				/* External RTC */
				LOCK_RTC = 1;
				if(RTC3click_Available){
					RTC3click_setTime(&System_Time);
					RTC3click_setDate(&System_Date);
				}
				/* Internal RTC */
				RTC_setTime(&System_Time);
				RTC_setDate(&System_Date);
                LOCK_RTC = 0;
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
void Update_RTC_Page(WM_HWIN * MainWindow) {
	static char cTime[16];
	static char cDate[16];
	static char Text[32];
	WM_HWIN hItem;

	RTC3click_ConvTimeToString(&System_Time,cTime);
	RTC3click_ConvDateToString(&System_Date,cDate);

	sprintf(Text, "Uhrzeit: %s", cTime);
	hItem = WM_GetDialogItem(*MainWindow, ID_TEXTBOX_1);
	TEXT_SetText(hItem, Text);

	sprintf(Text, "Datum: %s", cDate);
	hItem = WM_GetDialogItem(*MainWindow, ID_TEXTBOX_0);
	TEXT_SetText(hItem, Text);
}

/*********************************************************************
 *
 *       CreateWindow
 */
WM_HWIN Create_RTC_Page(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aRTCPageCreate, GUI_COUNTOF(_aRTCPageCreate),
			_cbRTC_Page, WM_HBKWIN, 0, 0);

	WindowChange_Handled = 1;

	return hWin;
}

/*************************** End of file ****************************/
