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

/** \addtogroup UpDown
 *  @{
 */

#include "Parameters_Edit.h"

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_UpDown[] =
{
    { FRAMEWIN_CreateIndirect, "",          ID_UPDOWN_WINDOW_0,         0,                                                                          0,                      UPDOWN_WIDTH,                   UPDOWN_HEIGHT,                  0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_UPDOWN_SPINBOX_BUTTON_DOWN,      UPDOWN_SPINBOX_POSX,                                                        UPDOWN_SPINBOX_POSY,    UPDOWN_SPINBOX_BUTTON_WIDTH,    UPDOWN_SPINBOX_BUTTON_HEIGHT,   0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_UPDOWN_SPINBOX_BUTTON_UP,        UPDOWN_SPINBOX_POSX+UPDOWN_SPINBOX_BUTTON_WIDTH+UPDOWN_SPINBOX_TEXT_WIDTH,  UPDOWN_SPINBOX_POSY,    UPDOWN_SPINBOX_BUTTON_WIDTH,    UPDOWN_SPINBOX_BUTTON_HEIGHT,   0, 0x0, 0 },
    { TEXT_CreateIndirect, "",              ID_UPDOWN_SPINBOX_TEXT,             UPDOWN_SPINBOX_POSX+UPDOWN_SPINBOX_BUTTON_WIDTH,                            UPDOWN_SPINBOX_POSY,    UPDOWN_SPINBOX_TEXT_WIDTH,      UPDOWN_SPINBOX_TEXT_HEIGHT,     TEXT_CF_VCENTER | TEXT_CF_HCENTER, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_UPDOWN_BUTTON_CANCEL,            UPDOWN_BUTTON_CANCEL_POSX,                                                  UPDOWN_BUTTON_POSY,     UPDOWN_BUTTON_WIDTH,            UPDOWN_BUTTON_HEIGHT,           0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_UPDOWN_BUTTON_OK,                UPDOWN_BUTTON_OK_POSX,                                                      UPDOWN_BUTTON_POSY,     UPDOWN_BUTTON_WIDTH,            UPDOWN_BUTTON_HEIGHT,           0, 0x0, 0 },
};

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void checkRange(WM_HWIN hWin, union Data * temp)
{
    WM_HWIN hItem;
    if (ParameterActiveRead(Step))
    {
        if (ParameterActiveRead(Max))
        {

            if (DataActiveRead((*temp)) + ParameterActiveRead(Step) > ParameterActiveRead(Max))
            {
                hItem = WM_GetDialogItem(hWin, ID_UPDOWN_SPINBOX_BUTTON_UP);
                BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmStop,0,0);
            }
            else
            {
                hItem = WM_GetDialogItem(hWin, ID_UPDOWN_SPINBOX_BUTTON_UP);
                BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmUp,0,0);
            }
        }

        if (ParameterActiveRead(Min))
        {
            if  (DataActiveRead((*temp)) - ParameterActiveRead(Step) < ParameterActiveRead(Min))
            {
                hItem = WM_GetDialogItem(hWin, ID_UPDOWN_SPINBOX_BUTTON_DOWN);
                BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmStop,0,0);
            }
            else
            {
                hItem = WM_GetDialogItem(hWin, ID_UPDOWN_SPINBOX_BUTTON_DOWN);
                BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmDown,0,0);
            }
        }
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static void _cbDialog_UpDown(WM_MESSAGE * pMsg)
{
    int NCode;
    int Id;
    WM_HWIN hItem;
    union Data temp;

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //Formatierung der Elemente
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_WHITE);
        FRAMEWIN_SetSkinClassic(hItem);
        FRAMEWIN_SetTitleVis(hItem,0);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_BUTTON_OK);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmOk,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_BUTTON_CANCEL);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmCancel,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_BUTTON_DOWN);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmDown,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_BUTTON_UP);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmUp,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_TEXT);
        TEXT_SetFont(hItem, UPDOWN_SPINBOX_FONT);

        //Wert in ValueString Text übertragen
        strcpy(ValueString,Parameter_getValAsStr(Parameter_Active)); //sprintf(ValueString, Parameter_Active->DataType->InStr, Parameter_Active->Value);
        TEXT_SetText(hItem, ValueString);

        //Überprüfung Werte
        checkRange(pMsg->hWin, &Parameter_Active->Value);

        break;

    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id)
        {
        case ID_UPDOWN_BUTTON_CANCEL:
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                break;
            case WM_NOTIFICATION_RELEASED:
                ParameterChange_Handled = 1;
                BlockChange = 0;
                GUI_EndDialog(pMsg->hWin,0);
                break;
            case WM_NOTIFICATION_MOVED_OUT:
                break;
            }
            break;
        case ID_UPDOWN_BUTTON_OK:
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                break;
            case WM_NOTIFICATION_RELEASED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_TEXT);

                sscanf(ValueString, Parameter_Active->DataType->InStr, &Parameter_Active->Value);

                ParameterChange_Handled = 0;
                BlockChange = 0;

                GUI_EndDialog(pMsg->hWin,1);
                break;
            case WM_NOTIFICATION_MOVED_OUT:
                break;
            }
            break;
        case ID_UPDOWN_SPINBOX_BUTTON_UP:
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                break;
            case WM_NOTIFICATION_RELEASED:
                Increment();
                break;
            case WM_NOTIFICATION_MOVED_OUT:
                break;
            }
            break;
        case ID_UPDOWN_SPINBOX_BUTTON_DOWN:
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                break;
            case WM_NOTIFICATION_RELEASED:
                //Übertragen Wert aus String in temp
                sscanf(ValueString, Parameter_Active->DataType->InStr, &temp);

                //Step von temp subtrahieren
                DataActiveWrite(temp,DataActiveRead(temp) - ParameterRead(Parameter_Active, Step));

                //Wenn untere Grenze definiert
                if (ParameterRead(Parameter_Active,Min))
                {
                    //Prüfe neuer Wert größer als Grenze

                    if (DataActiveRead(temp) >= ParameterActiveRead(Min))
                    {
                        //neuer Wert ok, übertragen in String
                        if (Parameter_Active->DataType == &DATATYPE_FLOAT) {
                            sprintf(ValueString, Parameter_Active->DataType->InStr, temp.f);
                        } else {
                            sprintf(ValueString, Parameter_Active->DataType->InStr, temp);
                        }

                        //sprintf(ValueString, Parameter_Active->DataType->InStr, temp);
                        hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_TEXT);
                        TEXT_SetText(hItem, ValueString);

                        //Überprüfung Sperrung eines Buttons
                        checkRange(pMsg->hWin, &temp);
                    }
                }
                else
                {
                    //keine Grenzwerte vorgegeben, übertrage neuen Wert in String
                    sprintf(ValueString, Parameter_Active->DataType->InStr, temp);
                    hItem = WM_GetDialogItem(pMsg->hWin, ID_UPDOWN_SPINBOX_TEXT);
                    TEXT_SetText(hItem, ValueString);
                }
                break;
            case WM_NOTIFICATION_MOVED_OUT:
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
void Increment()
{

    WM_HWIN hItem;
    union Data temp;
//Übertragen Wert aus String in temp
    sscanf(ValueString, Parameter_Active->DataType->InStr, &temp);

//Step auf temp aufaddieren
    union Data K23;
    DataActiveWrite(K23,ParameterActiveRead(Step));

    DataActiveWrite(temp,(DataActiveRead(temp) + DataActiveRead(K23)));

//Wenn obere Grenze definiert ist
    if (ParameterActiveRead(Max))
    {
        //Prüfe neuer Wert kleiner als Grenze
        if (DataActiveRead(temp) <= ParameterActiveRead(Max))
        {
            //neuer Wert ok, übertragen in String
            if (Parameter_Active->DataType == &DATATYPE_FLOAT) {
                sprintf(ValueString, Parameter_Active->DataType->InStr, temp.f);
            } else {
                sprintf(ValueString, Parameter_Active->DataType->InStr, temp);
            }

            hItem = WM_GetDialogItem(WM_HBKWIN, ID_UPDOWN_SPINBOX_TEXT);
            TEXT_SetText(hItem, ValueString);

            //Überprüfung Sperrung eines Buttons
            checkRange(WM_HBKWIN, &temp);
        }
    }
    else
    {
        //keine Grenzwerte vorgegeben, übertrage neuen Wert in String
        sprintf(ValueString, Parameter_Active->DataType->InStr, temp);
        hItem = WM_GetDialogItem(WM_HBKWIN, ID_UPDOWN_SPINBOX_TEXT);
        TEXT_SetText(hItem, ValueString);
    }


}



/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Decrement()
{

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Edit_UpDown()
{
    GUI_CreateDialogBox(_aDialogCreate_UpDown, GUI_COUNTOF(_aDialogCreate_UpDown), _cbDialog_UpDown, WM_HBKWIN, 0, 0);
}
