#include "DIALOG.h"
#include "Page_Main_3.h"
/*********************************************************************
*
*       _cbDialog
*/
void _cbTimeSWDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_TS);
    LISTVIEW_AddColumn(hItem, 80, "Wochentag", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 60, "Zeit", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 80, "Temperatur", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
    LISTVIEW_AddColumn(hItem, 80, "Wiederholend", GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Temperatur Zeitschaltung'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTVIEW_TS: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        break;
      }
      break;
    case ID_BUTTON_NE: // Notifications sent by 'Neuer Eintrag'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
        break;
      }
      break;
    case ID_BUTTON_EL: // Notifications sent by 'Eintrag löschen'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
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

void UpdateMain3(WM_HWIN * MainWindow) {

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
WM_HWIN CreateTimeSWWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogTimeSWCreate, GUI_COUNTOF(_aDialogTimeSWCreate), _cbTimeSWDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

/*************************** End of file ****************************/
