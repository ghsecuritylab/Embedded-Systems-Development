/** \file Parameters_Edit_Keypad_Hex
 *  \brief Erzeugt eine Tastatur-Ansicht auf dem Display, wahlweise auch mit Hex-Tasten.
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Dialogs
 *  @{
 */

/** \addtogroup Keypad_Hex
 *  @{
 */

#include "Parameters_Edit.h"


//Labels der Buttons
const char * KEYPAD_HEX_Labels[] = {
    "", "", "",".","+/-","F","E","D","C","B","A","9","8","7","6","5","4","3","2","1","0",
};

/** \brief Widget-Array, wird in /ref Edit_KeyPad_Hex um weitere Buttons erg‰nzt
 */
GUI_WIDGET_CREATE_INFO _aDialogCreate_KeyPad_Hex[7+16] = {
    { FRAMEWIN_CreateIndirect, "", ID_KEYPAD_HEX_WINDOW_0,        KEYPAD_HEX_POSX,                                                        KEYPAD_HEX_POSY,                                                            KEYPAD_HEX_WIDTH,                                                       KEYPAD_HEX_HEIGHT, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "0", ID_KEYPAD_HEX_TEXT_0,             KEYPAD_HEX_TEXT_POSX,                                                   KEYPAD_HEX_TEXT_POSY,                                                       KEYPAD_HEX_TEXT_WIDTH,                                                  KEYPAD_HEX_TEXT_HEIGHT, TEXT_CF_VCENTER, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_CANCEL,     KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX+KEYPAD_HEX_BUTTON_WIDTH)*5, KEYPAD_HEX_BUTTON_POSY, KEYPAD_HEX_BUTTON_WIDTH,                                KEYPAD_HEX_BUTTON_HEIGHT*2+KEYPAD_HEX_BUTTON_OFFSETY,                       0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_OK,         KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX+KEYPAD_HEX_BUTTON_WIDTH)*5, KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_HEIGHT+KEYPAD_HEX_BUTTON_OFFSETY)*2,    KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT*2+KEYPAD_HEX_BUTTON_OFFSETY,  0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_BACKSPACE,  KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX+KEYPAD_HEX_BUTTON_WIDTH)*5, KEYPAD_HEX_TEXT_POSY,                                                       KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_TEXT_HEIGHT,                            0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_PLUSMINUS,  KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*0, KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_OFFSETY + KEYPAD_HEX_BUTTON_HEIGHT)*3,KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_0+15,       KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*1, KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_OFFSETY + KEYPAD_HEX_BUTTON_HEIGHT)*3,KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_SEPERATOR,  KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*2, KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_OFFSETY + KEYPAD_HEX_BUTTON_HEIGHT)*3,KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT, 0, 0x0, 0 },
};

/** \brief Callback-Funktion die bei jedem Ereignis des Dialogs aufgerufen wird
 *
 */
void _cbDialog_KeyPad_Hex(WM_MESSAGE * pMsg) {
    WM_HWIN      hItem;
    int          NCode;
    int          Id;
    int          i;

    switch (pMsg->MsgId) {
        //Initialisierung
        case WM_INIT_DIALOG:
            //Format Framewin
            hItem = pMsg->hWin;
            WINDOW_SetBkColor(hItem, GUI_WHITE);
            FRAMEWIN_SetSkinClassic(hItem);
            FRAMEWIN_SetTitleVis(hItem,0);

            //Format Buttons
            for (i=-5;i<16;i++) {
                hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_BUTTON_0+i);
                BUTTON_SetText(hItem, KEYPAD_HEX_Labels[i+5]);
                BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);
            }

            //Format Button Backspace
            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_BUTTON_BACKSPACE);
            BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmBack,0,0);
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            //Format Button OK
            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_BUTTON_OK);
            BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmOk,0,0);
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            //Format Button Cancel
            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_BUTTON_CANCEL);
            BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmCancel,0,0);
            BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

            //Value in String ¸bertragen und in das TextFeld
            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);
            TEXT_SetFont(hItem, KEYPAD_HEX_TEXT_FONT);
            strcpy(ValueString, Parameter_getValAsStr(Parameter_Active));//)) sprintf(ValueString, Parameter_Active->DataType->OutStr, Parameter_Active->Value);
            TEXT_SetText(hItem,ValueString);

            break;

        case WM_NOTIFY_PARENT:
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;

            //Event Number-Key
            if ((Id >= ID_KEYPAD_HEX_BUTTON_0) & (Id <= ID_KEYPAD_HEX_BUTTON_0+15)) {
                switch(NCode) {
                    case WM_NOTIFICATION_RELEASED:
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);
                        TEXT_GetText(hItem,ValueString,16);

                        char lbl[2] ="";
                        if ((Id - ID_KEYPAD_HEX_BUTTON_0) <= 5) {
                            //Letters
                            lbl[0] = 'A'    +   (5 - (Id - ID_KEYPAD_HEX_BUTTON_0));
                        } else {
                            //Numbers
                            lbl[0] = '0'    +   (15 - (Id - ID_KEYPAD_HEX_BUTTON_0));
                        }

                        strcpy(ValueString,strcat(ValueString,lbl));

                        TEXT_SetText(hItem, ValueString);

                        break;
                }
                break;
            }

            //Other Events
            switch (Id) {
                //Event Seperator
                case ID_KEYPAD_HEX_BUTTON_SEPERATOR:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);
                            TEXT_GetText(hItem,ValueString,16);

                            char lbl[2] ="";
                            lbl[0] = '.';
                            strcpy(ValueString,strcat(ValueString,lbl));

                            TEXT_SetText(hItem, ValueString);
                            break;
                    }
                    break;

                //Event PLUS MINUS
                case ID_KEYPAD_HEX_BUTTON_PLUSMINUS:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);
                            union Data temp;

                            sscanf(ValueString, Parameter_Active->DataType->InStr, &temp);
                            DataActiveNegate(temp);
                            sprintf(ValueString, Parameter_Active->DataType->InStr, temp);

                            TEXT_SetText(hItem,ValueString);
                            break;
                    }
                    break;

                //Event Cancel
                case ID_KEYPAD_HEX_BUTTON_CANCEL:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            BlockChange = 0;
                            ParameterChange_Handled = 1;
                            GUI_EndDialog(pMsg->hWin,0);
                            break;
                    }
                    break;

                //Event OK
                case ID_KEYPAD_HEX_BUTTON_OK:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:

                            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);
                            TEXT_GetText(hItem,ValueString,16);
                            sscanf(ValueString, Parameter_Active->DataType->InStr,&(Parameter_Active->Value));

                            BlockChange = 0;
                            ParameterChange_Handled = 0;

                            GUI_EndDialog(pMsg->hWin,1);

                            break;
                    }
                    break;

                //Event Backspace
                case ID_KEYPAD_HEX_BUTTON_BACKSPACE:
                    switch(NCode) {
                        case WM_NOTIFICATION_RELEASED:
                            hItem = WM_GetDialogItem(pMsg->hWin, ID_KEYPAD_HEX_TEXT_0);

                            TEXT_GetText(hItem,ValueString,16);

                            char cset[] = "+-01234567890.ABCDEF";

                            int Count = strspn(ValueString, cset);
                            if ( Count > 0) {
                                ValueString[Count-1] = '\0';
                            }

                            TEXT_SetText(hItem,ValueString);
                            break;
                    }
                    break;
            }
        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

/** \brief Erstell-Funktion des Dialogs
 *
 *  Es werden hier anhand des ‹bergabeparameters zus‰tzliche Buttons erstellt, ggf. das Fenster
 *  angepasst und ggf. Buttons verschoben. Auﬂerdem wird durch Aufruf dieser Funktion der eigentliche Dialog erstellt
 *  \param  Hex: =1 mit HexKeypad, =0 ohne
 */
void Edit_Keypad_Hex(int Hex) {
    //if Not Hex - Change Window-Size
    if (!Hex) {
        GUI_WIDGET_CREATE_INFO TempElements[] = {
            { FRAMEWIN_CreateIndirect, "", ID_KEYPAD_HEX_WINDOW_0,        KEYPAD_HEX_POSX,   KEYPAD_HEX_POSY,    KEYPAD_HEX_WIDTH - (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*2, KEYPAD_HEX_HEIGHT, 0, 0x0, 0 },
        };
        _aDialogCreate_KeyPad_Hex[0] = TempElements[0];
    } else {
        GUI_WIDGET_CREATE_INFO TempElements[] = {
            { FRAMEWIN_CreateIndirect, "", ID_KEYPAD_HEX_WINDOW_0,        KEYPAD_HEX_POSX,   KEYPAD_HEX_POSY,    KEYPAD_HEX_WIDTH, KEYPAD_HEX_HEIGHT, 0, 0x0, 0 },
        };
        _aDialogCreate_KeyPad_Hex[0] = TempElements[0];
    }


    //Create Buttons - Hex
    int i,j;
    for(i=3;i<5;i++) {
        for(j=0;j<3;j++) {
            GUI_WIDGET_CREATE_INFO TempElements[] = {
            { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_0+i-3+j*2, KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*(7-i), KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_OFFSETY + KEYPAD_HEX_BUTTON_HEIGHT)*j,KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT, 0, 0x0, 0 }};
            _aDialogCreate_KeyPad_Hex[i-3+j*2+8] = TempElements[0];
        }
    }

    //Create Buttons - Normal
    for(i=0;i<3;i++) {
        for(j=0;j<3;j++) {
            GUI_WIDGET_CREATE_INFO TempElements[] = {
            { BUTTON_CreateIndirect, "", ID_KEYPAD_HEX_BUTTON_0+6+i+j*3, KEYPAD_HEX_BUTTON_POSX + (KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*(2-i), KEYPAD_HEX_BUTTON_POSY + (KEYPAD_HEX_BUTTON_OFFSETY + KEYPAD_HEX_BUTTON_HEIGHT)*j,KEYPAD_HEX_BUTTON_WIDTH, KEYPAD_HEX_BUTTON_HEIGHT, 0, 0x0, 0 }};
            _aDialogCreate_KeyPad_Hex[i+j*3+14] = TempElements[0];
        }
    }

    //WIDGET_SetDefaultEffect(&WIDGET_Effect_None);

    //Erstelle Fenster
    WM_HWIN hWin;
    hWin = GUI_CreateDialogBox(_aDialogCreate_KeyPad_Hex, GUI_COUNTOF(_aDialogCreate_KeyPad_Hex), _cbDialog_KeyPad_Hex, WM_HBKWIN, 0, 0);

    //Lˆsche ggf. HexButtons und verschiebe OK Cancel Backspace
    if (!Hex) {
        WM_HWIN hItem;
        //Lˆschen HexButtons
        for(i=0;i<6;i++) {
            hItem = WM_GetDialogItem(hWin, ID_KEYPAD_HEX_BUTTON_0+i);
            WM_DeleteWindow(hItem);
        }

        //Verschieben OK, Cancel, Backspace
        for(i=-5;i<-2;i++) {
            hItem = WM_GetDialogItem(hWin, ID_KEYPAD_HEX_BUTTON_0+i);
            WM_MoveWindow(hItem,-(KEYPAD_HEX_BUTTON_OFFSETX + KEYPAD_HEX_BUTTON_WIDTH)*2,0);
        }
    }
}



