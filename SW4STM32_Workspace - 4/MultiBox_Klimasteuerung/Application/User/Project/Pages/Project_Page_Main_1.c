#include "Project_Page_Main_1.h"
#include "temperature_control.h"
#include "time_switch.h"


static const char *acMode[4] = { "Heizen\0", "Schnellaufheizen\0", "Kühlen\0",
		"Halten\0" };

typedef struct {
	const uint8_t ID;
	const char *name;
} TC_Input_Sel_t;

TC_Input_Sel_t TC_Input_Sel[3] = {
		{ 0U, "(0) Raumtemperatur" },
		{ 1U, "(1) Motortemperatur" },
		{ 2U, "(2) CAN-Nachricht" } };

static uint8_t MessStelle = 0xFF;

uint8_t CAN_Motoroel_Enable = 0;
uint8_t CAN_Temperatur_Enable = 0;

float *ptIstTemperatur;
extern uint8_t timeSwitch_SetTemperature;

uint8_t SollVorgabe = 20;
static uint8_t lastTimeSwitch_SetTemperature = 20;
static uint8_t initDone = 0;

float tRaumtemperatur = 0.0;
float tAussentemperatur = 0.0;
float tLuftstrom1 = 0.0;
float tLuftstrom2 = 0.0;
float tAusseneinheit1 = 0.0;
float tAusseneinheit2 = 0.0;
float tMotor = 0.0;
float tMotor_CAN = 0.0;

void _cbDialog_Main1(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int NCode;
	int Id;
	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_DELETE:
		initDone = 0;
		break;
	case WM_INIT_DIALOG:
		//
		// Initialization of 'Spinbox'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_TCSEL);
		SPINBOX_SetFont(hItem, GUI_FONT_20_1);
		SPINBOX_SetRange(hItem, 16, 30);
		SPINBOX_SetValue(hItem, 20);
		//
		// Initialization of 'Dropdown'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TC);
		DROPDOWN_AddString(hItem, TC_Input_Sel[0].name);
		DROPDOWN_AddString(hItem, TC_Input_Sel[1].name);
		DROPDOWN_AddString(hItem, TC_Input_Sel[2].name);
		DROPDOWN_SetFont(hItem, GUI_FONT_16_1);

		MessStelle = TC_IstWert_Sel.Value.un;
		DROPDOWN_SetSel(hItem, MessStelle);

		switch (MessStelle) {
		case (0):		// Raumtemperatur
			ptIstTemperatur = &tRaumtemperatur;
			temperatureControl_setIst(&tRaumtemperatur);
			break;
		case (1):		// Motortemperatur
			ptIstTemperatur = &tMotor;
			temperatureControl_setIst(&tMotor);
			break;
		case (2):		// Temperatur (CAN)
			ptIstTemperatur = &tMotor_CAN;
			temperatureControl_setIst(&tMotor_CAN);
			break;
		}

		//
		// Initialization of 'Temperatursteuerung'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TITLE1);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		//
		// Initialization of 'Messstelle:'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TC1);
		TEXT_SetFont(hItem, GUI_FONT_16_1);
		//
		// Initialization of 'Sollvorgabe [°C]:'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TC2);
		TEXT_SetFont(hItem, GUI_FONT_16_1);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_TCSEL);
		SollVorgabe = TC_Sollwert.Value.un;
		temperatureControl_setSoll(SollVorgabe);
		SPINBOX_SetValue(hItem, SollVorgabe);

		//
		// Initialization of 'Temperaturwerte'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TITLE2);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		//
		// Initialization of 'Listview'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_TC);
		LISTVIEW_AddColumn(hItem, 115, "Messstelle", GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 65, "Temperatur",
		GUI_TA_VCENTER | GUI_TA_HCENTER);
		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 0, "Raumtemperatur");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 1, "Aussentemperatur");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 2, "Luftstrom Klimagerät 1");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 3, "Ausseneinheit 1");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 4, "Luftstrom Klimagerät 2");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 5, "Ausseneinheit 2");
		LISTVIEW_AddRow(hItem, NULL);
		LISTVIEW_SetItemText(hItem, 0, 6, "Motortemperatur");
		//
		// Initialization of 'Aktuelle Temperatur:'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TC9);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		//
		// Initialization of '20.0 °C'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TEMPIST);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		//
		// Initialization of 'Aktuelle Modus:'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TC10);
		TEXT_SetFont(hItem, GUI_FONT_20_1);
		//
		// Initialization of 'Mode'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MODE);
		TEXT_SetFont(hItem, GUI_FONT_20_1);

		initDone = 1;

		break;
	case WM_NOTIFY_PARENT:
		if (initDone) {
			Id = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch (Id) {
			case ID_DROPDOWN_TC: // Notifications sent by 'Dropdown'
				switch (NCode) {
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					break;
				case WM_NOTIFICATION_SEL_CHANGED:
//				hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_TCSEL);
//				MessStelle = DROPDOWN_GetSel(hItem);

					hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_TC);
					MessStelle = DROPDOWN_GetSel(hItem);
					//if (lastMessstelle != MessStelle) {
					//	lastMessstelle = MessStelle;
					switch (MessStelle) {
					case (0):		// Raumtemperatur
						ptIstTemperatur = &tRaumtemperatur;
						temperatureControl_setIst(&tRaumtemperatur);
						ParameterWrite((&TC_IstWert_Sel), Value, MessStelle);
						ParameterChange_Handled = 0;
						break;
					case (1):		// Motortemperatur
						ptIstTemperatur = &tMotor;
						temperatureControl_setIst(&tMotor);
						ParameterWrite((&TC_IstWert_Sel), Value, MessStelle);
						ParameterChange_Handled = 0;
						break;
					case (2):		// Temperatur Allg. (CAN)
						ptIstTemperatur = &tMotor_CAN;
						temperatureControl_setIst(&tMotor_CAN);
						ParameterWrite((&TC_IstWert_Sel), Value, MessStelle);
						ParameterChange_Handled = 0;
						break;
					}
					//}

					break;
				}
				break;
			case ID_SPINBOX_TCSEL: // Notifications sent by 'Spinbox'
				switch (NCode) {
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					break;
				case WM_NOTIFICATION_MOVED_OUT:
					break;
				case WM_NOTIFICATION_VALUE_CHANGED:
					/* Wenn Wert in SpinBox sich geändert hat, übernehmen*/
					hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_TCSEL);
					SollVorgabe = SPINBOX_GetValue(hItem);
					ParameterWrite((&TC_Sollwert), Value, SollVorgabe)
					;
					ParameterChange_Handled = 0;
					break;
				}
				break;
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

void UpdateMain1(WM_HWIN * MainWindow) {
	WM_HWIN hItem;
	char cTemp[16];

	// Update of 'Temperaturwerte' Listview
	hItem = WM_GetDialogItem(*MainWindow, ID_LISTVIEW_TC);
	sprintf(cTemp, "%2.1f°C", tRaumtemperatur);
	LISTVIEW_SetItemText(hItem, 1, 0, cTemp);
	sprintf(cTemp, "%2.1f°C", tAussentemperatur);
	LISTVIEW_SetItemText(hItem, 1, 1, cTemp);
	sprintf(cTemp, "%2.1f°C", tLuftstrom1);
	LISTVIEW_SetItemText(hItem, 1, 2, cTemp);
	sprintf(cTemp, "%2.1f°C", tLuftstrom2);
	LISTVIEW_SetItemText(hItem, 1, 3, cTemp);
	sprintf(cTemp, "%2.1f°C", tAusseneinheit1);
	LISTVIEW_SetItemText(hItem, 1, 4, cTemp);
	sprintf(cTemp, "%2.1f°C", tAusseneinheit2);
	LISTVIEW_SetItemText(hItem, 1, 5, cTemp);
	sprintf(cTemp, "%2.1f°C", tMotor);
	LISTVIEW_SetItemText(hItem, 1, 6, cTemp);

// Update of 'Ist-Temperatur' Text
	hItem = WM_GetDialogItem(*MainWindow, ID_TEXT_TEMPIST);
	char cIstTemp[10];
	sprintf(cIstTemp, "%2.1f °C", *ptIstTemperatur);
	TEXT_SetText(hItem, cIstTemp);

// Update of 'Soll-Vorgabe' SpinBox

	hItem = WM_GetDialogItem(*MainWindow, ID_SPINBOX_TCSEL);
	/* Wenn sich timeSwitch_SetTemperature verändert hat, übernehmen*/
	if (lastTimeSwitch_SetTemperature != timeSwitch_SetTemperature) {
		lastTimeSwitch_SetTemperature = timeSwitch_SetTemperature;
		SollVorgabe = timeSwitch_SetTemperature;
		SPINBOX_SetValue(hItem, SollVorgabe);
		ParameterWrite((&TC_Sollwert), Value, SollVorgabe);
		ParameterChange_Handled = 0;
	}

	/* send SetPoint to TempControl */
	temperatureControl_setSoll((float) SollVorgabe);
	SPINBOX_SetValue(hItem, SollVorgabe);

	// Update of 'Mode' Text
	hItem = WM_GetDialogItem(*MainWindow, ID_TEXT_MODE);
	TEXT_SetText(hItem, acMode[temperatureControl_getMode()]);
}

WM_HWIN CreateMain1(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate_Main1,
			GUI_COUNTOF(_aDialogCreate_Main1), _cbDialog_Main1, WM_HBKWIN, 0,
			0);
	WindowChange_Handled = 1;

	return hWin;
}

