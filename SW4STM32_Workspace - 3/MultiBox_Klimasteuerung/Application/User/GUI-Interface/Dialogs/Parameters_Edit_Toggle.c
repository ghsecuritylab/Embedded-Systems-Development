/** \file
 *  \brief
 *
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Dialogs
 *  @{
 */

 /** \addtogroup Toggle
 *  @{
 */

#include "Parameters_Edit.h"

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_TOGGLE[] = {
    { FRAMEWIN_CreateIndirect, "",          ID_TOGGLE_WINDOW_0,         0,                                                                          0,                      TOGGLE_WIDTH,                   TOGGLE_HEIGHT,                  0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_TOGGLE_BUTTON_ON,        TOGGLE_POSX,                                                        TOGGLE_POSY,                    TOGGLE_BUTTON_ON_WIDTH,            TOGGLE_BUTTON_ON_HEIGHT,   0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_TOGGLE_BUTTON_OFF,       TOGGLE_POSX+TOGGLE_BUTTON_ON_WIDTH+TOGGLE_TEXT_WIDTH,                  TOGGLE_POSY,                    TOGGLE_BUTTON_OFF_WIDTH,            TOGGLE_BUTTON_OFF_HEIGHT,   0, 0x0, 0 },
    { TEXT_CreateIndirect, "",              ID_TOGGLE_TEXT,             TOGGLE_POSX+TOGGLE_BUTTON_OFF_WIDTH,                                    TOGGLE_POSY,                    TOGGLE_TEXT_WIDTH,              TOGGLE_TEXT_HEIGHT,     TEXT_CF_VCENTER | TEXT_CF_HCENTER, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_TOGGLE_BUTTON_CANCEL,    TOGGLE_BUTTON_CANCEL_POSX,                                          TOGGLE_BUTTON_POSY,             TOGGLE_BUTTON_WIDTH,            TOGGLE_BUTTON_HEIGHT,           0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_TOGGLE_BUTTON_OK,        TOGGLE_BUTTON_OK_POSX,                                              TOGGLE_BUTTON_POSY,             TOGGLE_BUTTON_WIDTH,            TOGGLE_BUTTON_HEIGHT,           0, 0x0, 0 },
};

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static void _cbDialog_TOGGLE(WM_MESSAGE * pMsg) {
    int NCode;
    int Id;
    WM_HWIN hItem;

    switch (pMsg->MsgId) {
        case WM_INIT_DIALOG:
            hItem = pMsg->hWin;
            WINDOW_SetBkColor(hItem, GUI_WHITE);
            FRAMEWIN_SetSkinClassic(hItem);
            FRAMEWIN_SetTitleVis(hItem,0);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_BUTTON_OK);
            BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmOk,0,0);
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_BUTTON_CANCEL);
            BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmCancel,0,0);
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_BUTTON_ON);
            BUTTON_SetText(hItem,"1");
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_BUTTON_OFF);
            BUTTON_SetText(hItem,"0");
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_TEXT);
            TEXT_SetFont(hItem, TOGGLE_FONT);

            //Wert in ValueString Text übertragen
            sprintf(ValueString, Parameter_Active->DataType->InStr, Parameter_Active->Value);
            TEXT_SetText(hItem, ValueString);

            break;

        case WM_NOTIFY_PARENT:
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
                case ID_TOGGLE_BUTTON_CANCEL:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            ParameterChange_Handled = 1;
                            BlockChange = 0;
                            GUI_EndDialog(pMsg->hWin,0);
                            break;
                    }
                    break;
                case ID_TOGGLE_BUTTON_OK:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_TEXT);
                            sscanf(ValueString, Parameter_Active->DataType->InStr, &Parameter_Active->Value);

                            ParameterChange_Handled = 0;
                            BlockChange = 0;

                            GUI_EndDialog(pMsg->hWin,1);
                            break;
                    }
                    break;
                case ID_TOGGLE_BUTTON_ON:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            strcpy(ValueString, "1");
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_TEXT);
                            TEXT_SetText(hItem, ValueString);
                            break;
                    }
                    break;
                case ID_TOGGLE_BUTTON_OFF:
                    switch(NCode) {

                        case WM_NOTIFICATION_RELEASED:
                            strcpy(ValueString, "0");
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_TOGGLE_TEXT);
                            TEXT_SetText(hItem, ValueString);
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

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Edit_Toggle() {
    GUI_CreateDialogBox(_aDialogCreate_TOGGLE, GUI_COUNTOF(_aDialogCreate_TOGGLE), _cbDialog_TOGGLE, WM_HBKWIN, 0, 0);
}
