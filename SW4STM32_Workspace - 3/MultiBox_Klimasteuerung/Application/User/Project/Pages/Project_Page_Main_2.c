#include "Project_Page_Main_2.h"
#include "RTC3click.h"
#include "RTC_Internal.h"
#include "graphSettings.h"


extern WM_HWIN CreateAnzeige(void);


#define MAX_VALUE 180

static GRAPH_DATA_Handle _ahData[9]; // Array of handles for the GRAPH_DATA objects
static GRAPH_SCALE_Handle _hScaleV;   // Handle of vertical scale
static GRAPH_SCALE_Handle _hScaleH;   // Handle of horizontal scale
static GRAPH_Handle _hGraph;
static WM_HWIN hCheckDialog;

int16_t graphValues[9];

static uint8_t graph_initialized = 0;

static I16 _aValue[9];
static int32_t T_offset = GRAPH_SIZE_T;
static uint8_t firstInitDone = 0;

extern uint8_t newGraphValuesAvailable;

/*	Temperatur Reihenfolge
 * 	0  SollTemperatur
 * 	1  Raumtemperatur
 * 	2  Aussentemepratur
 * 	3  Luftstrom 1
 * 	4  Ausseneinheit 1
 * 	5  Luftstrom 2
 * 	6  Ausseneinheit 2
 * 	7  Motortemperatur
 *
 * */

uint8_t enableLine[9] = {1,1,0,0,0,0,0,0,0};

GUI_COLOR _aColor[] = {
GUI_RED,
GUI_DARKGREEN,
GUI_BLUE,
GUI_BLACK,
GUI_DARKGRAY,
GUI_ORANGE,
GUI_BROWN,
GUI_MAGENTA,
GUI_LIGHTBLUE
}; // Array of colors for the GRAPH_DATA objects

void Graph_AddValues(int16_t *val) {
	unsigned i;

	for (i = 0; i < GUI_COUNTOF(_aColor); i++) {
		if(enableLine[i]){
			GRAPH_DATA_YT_AddValue(_ahData[i], val[i]);
		}
	}

	GRAPH_SCALE_SetOff(_hScaleH, (T_offset--)); //+ T_scrollVal);
}

/*********************************************************************
*       _UserDraw
*
* Function description
*   This routine is called by the GRAPH object before anything is drawn
*   and after the last drawing operation.
*/
static void _UserDraw(WM_HWIN hWin, int Stage) {
  if (Stage == GRAPH_DRAW_LAST) {
    char acText[] = "  [°C]";
    GUI_RECT Rect;
    GUI_RECT RectInvalid;
    int FontSizeY;

    GUI_SetFont(&GUI_Font13_1);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.y1 = Rect.y0 + FontSizeY *5;
    GUI_SetColor(GUI_DARKBLUE);
    GUI_DispStringInRectEx(acText, &Rect, 0/*GUI_TA_HCENTER*/, strlen(acText), GUI_ROTATE_0);
  }
}

void _cbDialog_Main2(WM_MESSAGE * pMsg) {
	unsigned i;
	int NCode;
	int Id;
	WM_HWIN hDlg;
	WM_HWIN hItem;
	static WM_HMEM hTimer;

	hDlg = pMsg->hWin;
	_hGraph = hDlg;
	switch (pMsg->MsgId) {
	case WM_TIMER:
		WM_RestartTimer(hTimer, 100);

		if(newGraphValuesAvailable){
			newGraphValuesAvailable = 0;
			Graph_AddValues(graphValues);
		}
		break;

	case WM_INIT_DIALOG:

		hTimer = WM_CreateTimer(hDlg, 0, 1, 0);

		hItem = WM_GetDialogItem(hDlg, ID_BUTTON_0);
		BUTTON_SetFont(hItem, GUI_FONT_32_1);

		//
		// Initialization of 'Graph'
		//
		hItem = WM_GetDialogItem(hDlg, ID_GRAPH_0);
		GRAPH_SetBorder(hItem, 25, 15, 15, 10);
		GRAPH_SetColor(hItem, GUI_WHITE, GRAPH_CI_BK);
		//GRAPH_SetColor(hItem, IAV_BLAU_5, GRAPH_CI_BORDER);
		GRAPH_SetColor(hItem, IAV_BLAU_5, GRAPH_CI_FRAME);
		GRAPH_SetColor(hItem, IAV_BLAU_2, GRAPH_CI_GRID);

		//
		// Add graphs
		//
		for (i = 0; i < GUI_COUNTOF(_aColor); i++) {
			//_aValue[i] = rand() % 180;
			_ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], GRAPH_SIZE_T, 0, 0);
			GRAPH_AttachData(hItem, _ahData[i]);
		}

		//
		// Set graph attributes
		//
		GRAPH_SetGridDistY(hItem, 25);
		GRAPH_SetGridDistX(hItem, 30);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetGridFixedX(hItem, 1);
		GRAPH_SetUserDraw(hItem, _UserDraw);

		//
		// Create and add vertical scale
		//
		_hScaleV = GRAPH_SCALE_Create(20, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 50);
		GRAPH_SCALE_SetTextColor(_hScaleV, GUI_DARKBLUE);
		GRAPH_SCALE_SetFactor(_hScaleV, SCALE_FACTOR_T);
		GRAPH_AttachScale(hItem, _hScaleV);

		//
		// Create and add horizontal scale
		//
		_hScaleH = GRAPH_SCALE_Create(211, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 60);
		GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKBLUE);
		GRAPH_SCALE_SetFactor(_hScaleH, SCALE_FACTOR_Y);
		RTC_Time now;
		RTC_getTime(&now);
		if(!firstInitDone){
			T_offset -= (now.Hours * 30 + now.Minutes/2);
		}
		GRAPH_SCALE_SetOff(_hScaleH, T_offset);
		GRAPH_AttachScale(hItem, _hScaleV);
		GRAPH_AttachScale(hItem, _hScaleH);

		//
		// Create and add scrollbars
		//
		GRAPH_SetVSizeX(hItem, GRAPH_SIZE_T);
		GRAPH_SetVSizeY(hItem, GRAPH_SIZE_Y);

		/* Add Values from RingMemory to Graph */
		uint16_t ValCnt = TemperaturRaum.StoredItems;
		int16_t aVal[8];
		if(ValCnt > 0){
			uint16_t idx = ValCnt - 1;
			while(idx != 0){
			//for(uint16_t i = ValIdx; i < ValCnt; i--){
				union Data data;
				data = *RingMemory_getValasData(&Sollwert, idx);
				aVal[0] = data.un;
				data = *RingMemory_getValasData(&TemperaturRaum, idx);
				aVal[1] = data.un;
				data = *RingMemory_getValasData(&TemperaturOutside, idx);
				aVal[2] = data.un;
				data = *RingMemory_getValasData(&TemperaturAir1, idx);
				aVal[3] = data.un;
				data = *RingMemory_getValasData(&TemperaturUnit1, idx);
				aVal[4] = data.un;
				data = *RingMemory_getValasData(&TemperaturAir2, idx);
				aVal[5] = data.un;
				data = *RingMemory_getValasData(&TemperaturUnit2, idx);
				aVal[6] = data.un;
				data = *RingMemory_getValasData(&TemperaturMotor, idx);
				aVal[7] = data.un;
				data = *RingMemory_getValasData(&TemperaturCAN, idx);
				aVal[8] = data.un;
				Graph_AddValues(aVal);
				idx--;
				T_offset--;
			}
//			T_offset += TemperaturRaum.Count;
		}

		/* Restore Settings for displayed Graph Lines */
		uint16_t enabledLines = GraphDispLines.Value.un;
		for(int i = 0; i < 9; i++){
			enableLine[i] = (enabledLines >> i) & 1;
		}

		graph_initialized = 1;
		firstInitDone = 1;

		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_BUTTON_0: // Notifications sent by 'Raumtemperatur'
			switch (NCode) {
			case WM_NOTIFICATION_RELEASED:
				hCheckDialog = CreateAnzeige();
				break;
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

void UpdateMain2(WM_HWIN * MainWindow) {
//    WM_HWIN hItem;
//    hItem = WM_GetDialogItem(*MainWindow, ID_TEXT_0);
	for(int i = 0; i < 9; i++){
		if(!enableLine[i]){
			GRAPH_DATA_YT_Clear(_ahData[i]);
		}
	}
}

WM_HWIN CreateMain2(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate_Main2,
			GUI_COUNTOF(_aDialogCreate_Main2), _cbDialog_Main2, WM_HBKWIN, 0,
			0);
	WindowChange_Handled = 1;
	return hWin;
}
