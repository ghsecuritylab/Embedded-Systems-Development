#include "Project_Page_Main_3.h"
#include "DIALOG.h"
#include "MESSAGEBOX.h"
#include "Dialog_NewTimerEvent.h"
#include "GUIControl.h"
#include "time_switch.h"

char *neinJa[] = { "Nein", "Ja" };

uint8_t updateEventList_flag = 0;
uint8_t MsgBoxOpen = 0;
static uint8_t ParaLoad_flag = 0;

WM_HWIN hWinPage3;
WM_HMEM hTimer;

void PeriodicUpdate(WM_HWIN * MainWindow);

/*********************************************************************
 *       _cbDialog
 */
void _cbTimeSWDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int NCode;
	int Id;

	switch (pMsg->MsgId) {
	case WM_TIMER:
		PeriodicUpdate(&pMsg->hWin);
		WM_RestartTimer(pMsg->Data.v, 1000);
		break;
	case WM_INIT_DIALOG:

		/* Init Timer for Window-Update */
		hTimer = WM_CreateTimer(pMsg->hWin, 0, 1, 0);

		//
		// Initialization of 'Listview'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_TS);
		LISTVIEW_AddColumn(hItem, 20, "ID", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 80, "Wochentag",
		GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 60, "Zeit", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 80, "Temperatur",
		GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_AddColumn(hItem, 80, "Wiederholung",
		GUI_TA_HCENTER | GUI_TA_VCENTER);

		if (!ParaLoad_flag) {
			EventListEntryCount = ListEntryCount.Value.un;
			for (int i = 0; i < EventListEntryCount; i++) {
				TimeSwitch_EventList[i].ID = i;
				TimeSwitch_EventList[i].startDay =
						ParameterEventList[i*5]->Value.un;
				TimeSwitch_EventList[i].startTime.Hours =
						ParameterEventList[i*5+1]->Value.un;
				TimeSwitch_EventList[i].startTime.Minutes =
						ParameterEventList[i*5+2]->Value.un;
				TimeSwitch_EventList[i].Temperature =
						ParameterEventList[i*5+3]->Value.f;
				TimeSwitch_EventList[i].Repeat =
						ParameterEventList[i*5+4]->Value.b;
			}
			ParaLoad_flag = 1;
		}

		for (uint8_t i = 0; i < EventListEntryCount; i++) {
			char cDay[16];
			char cTime[6];
			char cTemp[6];
			char cID[3];

			sprintf(cID, "%d", TimeSwitch_EventList[i].ID);
			sprintf(cDay,
					RTC_DayOfWeekStings[TimeSwitch_EventList[i].startDay]);
			sprintf(cTime, "%02d:%02d", TimeSwitch_EventList[i].startTime.Hours,
					TimeSwitch_EventList[i].startTime.Minutes);
			sprintf(cTemp, "%2.1f", TimeSwitch_EventList[i].Temperature);

			LISTVIEW_AddRow(hItem, NULL);
			LISTVIEW_SetItemText(hItem, 0U, i, cID);
			LISTVIEW_SetItemText(hItem, 1U, i,
					RTC_DayOfWeekStings[TimeSwitch_EventList[i].startDay - 1]);
			LISTVIEW_SetItemText(hItem, 2U, i, cTime);
			LISTVIEW_SetItemText(hItem, 3U, i, cTemp);
			LISTVIEW_SetItemText(hItem, 4U, i,
					neinJa[TimeSwitch_EventList[i].Repeat]);
		}

		//
		// Initialization of 'Temperatur Zeitschaltung'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TITLE);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_LISTVIEW_TS: // Notifications sent by 'Listview'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:

				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				break;
			}
			break;
		case ID_BUTTON_NE: // Notifications sent by 'Neuer Eintrag'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				//BlockChange = 1;
				if (EventListEntryCount < EVENTLIST_ENTRIES_MAX) {
					Create_TimerEvent_Page();
				} else {
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_NE);
					WM_DisableWindow(hItem);
					GUI_MessageBox("Maximale Anzahl an Einträgen erreicht!",
							"Meldung", 0);
					WM_EnableWindow(hItem);
				}
				break;
			}
			break;
		case ID_BUTTON_EL: // Notifications sent by 'Eintrag löschen'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_TS);
				uint8_t selItem = LISTVIEW_GetSel(hItem);
				/* if list is not empty delete one entry */
				if (EventListEntryCount > 0) {
					timeSwitch_delete_Event(selItem);
					Update_EventList();
				}
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

void PeriodicUpdate(WM_HWIN * MainWindow) {

}

void Update_TimerEventsPage(WM_HWIN * MainWindow) {
	static uint8_t last_EventListEntryCount = 0;
	WM_HWIN hItem;
	char cSetT[60];
	char cTime[12];

	//RTC3click_getTimeAsString(cTime);
//	RTC_Time System_Time;
//	RTC_Date System_Date;
	sprintf(cTime, "%02d:%02d:%02d", System_Time.Hours, System_Time.Minutes,
			System_Time.Seconds);
	sprintf(cSetT, "Zeitschaltliste                       %s", cTime);

	hItem = WM_GetDialogItem(*MainWindow, ID_TEXT_TITLE);
	TEXT_SetText(hItem, cSetT);

	hItem = WM_GetDialogItem(*MainWindow, ID_LISTVIEW_TS);

	/* Entry list has changed, update displayed List*/
	if ((last_EventListEntryCount != EventListEntryCount)
			|| updateEventList_flag) {

		LISTVIEW_DeleteAllRows(hItem);

		if (EventListEntryCount > 0) {

			for (uint8_t i = 0; i < EventListEntryCount; i++) {
				char cDay[16];
				char cTime[6];
				char cTemp[6];
				char cID[3];

				sprintf(cID, "%d", TimeSwitch_EventList[i].ID);
				sprintf(cDay,
						RTC_DayOfWeekStings[TimeSwitch_EventList[i].startDay]);
				sprintf(cTime, "%02d:%02d",
						TimeSwitch_EventList[i].startTime.Hours,
						TimeSwitch_EventList[i].startTime.Minutes);
				sprintf(cTemp, "%2.1f", TimeSwitch_EventList[i].Temperature);

				LISTVIEW_AddRow(hItem, NULL);
				LISTVIEW_SetItemText(hItem, 0U, i, cID);
				LISTVIEW_SetItemText(hItem, 1U, i,
						RTC_DayOfWeekStings[TimeSwitch_EventList[i].startDay - 1]);
				LISTVIEW_SetItemText(hItem, 2U, i, cTime);
				LISTVIEW_SetItemText(hItem, 3U, i, cTemp);
				LISTVIEW_SetItemText(hItem, 4U, i,
						neinJa[TimeSwitch_EventList[i].Repeat]);
			}

			last_EventListEntryCount = EventListEntryCount;
		}
		updateEventList_flag = 0;
	}
	updateEventList_flag = 0;
}

void Update_EventList(void) {
	updateEventList_flag = 1;
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */
/*********************************************************************
 *
 *       CreateWindow
 */
WM_HWIN Create_TimerEventsPage(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogTimeSWCreate,
			GUI_COUNTOF(_aDialogTimeSWCreate), _cbTimeSWDialog, WM_HBKWIN, 0,
			0);

	hWinPage3 = hWin;
	WindowChange_Handled = 1;
	return hWin;
}

/*************************** End of file ****************************/
