/** \file Parameters_Edit_OneWireROM
 *  \brief Erzeugt eine Ansicht auf dem Display wo dem momentan aktiven Parameter ein erkannter Sensor zugeordnet wird.
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Dialogs
 *  @{
 */

 /** \addtogroup OneWireROM
 *  @{
 */

#include "Parameters_Edit.h"

extern uint8_t deviceCount;
extern uint8_t * device;

/** \brief Liste mit den Widgets dieses Fensters
 */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_OneWireROM[] =
{
    { FRAMEWIN_CreateIndirect, "",          ID_ONEWIREROM_WINDOW_0,                 0,                                                                                      0,                          ONEWIREROM_WIDTH,                   ONEWIREROM_HEIGHT,                  0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_ONEWIREROM_SPINBOX_BUTTON_DOWN,      ONEWIREROM_SPINBOX_POSX,                                                                ONEWIREROM_SPINBOX_POSY,    ONEWIREROM_SPINBOX_BUTTON_WIDTH,    ONEWIREROM_SPINBOX_BUTTON_HEIGHT,   0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_ONEWIREROM_SPINBOX_BUTTON_UP,        ONEWIREROM_SPINBOX_POSX+ONEWIREROM_SPINBOX_BUTTON_WIDTH+ONEWIREROM_SPINBOX_TEXT_WIDTH,  ONEWIREROM_SPINBOX_POSY,    ONEWIREROM_SPINBOX_BUTTON_WIDTH,    ONEWIREROM_SPINBOX_BUTTON_HEIGHT,   0, 0x0, 0 },
    { TEXT_CreateIndirect, "",              ID_ONEWIREROM_SPINBOX_TEXT,             ONEWIREROM_SPINBOX_POSX+ONEWIREROM_SPINBOX_BUTTON_WIDTH,                                ONEWIREROM_SPINBOX_POSY,    ONEWIREROM_SPINBOX_TEXT_WIDTH,      ONEWIREROM_SPINBOX_TEXT_HEIGHT,     TEXT_CF_VCENTER | TEXT_CF_HCENTER, 0x0, 0 },
    { TEXT_CreateIndirect, "",              ID_ONEWIREROM_SPINBOX_TEMPTEXT,         ONEWIREROM_TEMPTEXT_POSX,                                                               ONEWIREROM_TEMPTEXT_POSY,   ONEWIREROM_TEMPTEXT_WIDTH,          ONEWIREROM_TEMPTEXT_HEIGHT,         TEXT_CF_VCENTER | TEXT_CF_HCENTER, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_ONEWIREROM_BUTTON_CANCEL,            ONEWIREROM_BUTTON_CANCEL_POSX,                                                          ONEWIREROM_BUTTON_POSY,     ONEWIREROM_BUTTON_WIDTH,            ONEWIREROM_BUTTON_HEIGHT,           0, 0x0, 0 },
    { BUTTON_CreateIndirect, "",            ID_ONEWIREROM_BUTTON_OK,                ONEWIREROM_BUTTON_OK_POSX,                                                              ONEWIREROM_BUTTON_POSY,     ONEWIREROM_BUTTON_WIDTH,            ONEWIREROM_BUTTON_HEIGHT,           0, 0x0, 0 },
};

int Index;
char DeviceName[15] = "";

/** \brief Funktion die nach jedem Klicken auf Up oder Down überprüft, ob der Anfang oder das Ende der Liste erreicht wurde. Ggf. wird der jeweilige Button gesperrt.
 *
 *  \param hWin = momentane Fenster
 */
void checkRange_OneWire(WM_HWIN * hWin)
{
    WM_HWIN hItem;

    if (Index + 1 >= deviceCount)
    {
        hItem = WM_GetDialogItem(*hWin, ID_ONEWIREROM_SPINBOX_BUTTON_UP);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmStop,0,0);
    } else {
        hItem = WM_GetDialogItem(*hWin, ID_ONEWIREROM_SPINBOX_BUTTON_UP);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmUp,0,0);
    }

    if (Index <= 0)
    {
        hItem = WM_GetDialogItem(*hWin, ID_ONEWIREROM_SPINBOX_BUTTON_DOWN);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmStop,0,0);
    }    else   {
        hItem = WM_GetDialogItem(*hWin, ID_ONEWIREROM_SPINBOX_BUTTON_DOWN);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmDown,0,0);
    }
}

/** \brief Callback-Funktion des Dialoges, wird bei Ereignissen automatisch aufgerufen
 *
 */
static void _cbDialog_OneWireROM(WM_MESSAGE * pMsg)
{
    int NCode;
    int Id;
    WM_HWIN hItem;

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, GUI_WHITE);
        FRAMEWIN_SetSkinClassic(hItem);
        FRAMEWIN_SetTitleVis(hItem,1);
        FRAMEWIN_SetText(hItem, Parameter_Active->Name);
        FRAMEWIN_SetFont(hItem, MENU_ELEMENTS_FONT_DESCRIPTION);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_BUTTON_OK);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmOk,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_BUTTON_CANCEL);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmCancel,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_BUTTON_DOWN);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmDown,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_BUTTON_UP);
        BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,&bmUp,0,0);
        BUTTON_SetSkin(hItem, Dialog_DrawSkinFlex_BUTTON);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_TEMPTEXT);
        TEXT_SetFont(hItem, ONEWIREROM_SPINBOX_FONT);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_TEXT);
        TEXT_SetFont(hItem, ONEWIREROM_SPINBOX_FONT);
        sprintf(ValueString,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",device[0],device[1],device[2],device[3],device[4],device[5],device[6],device[7]);
        TEXT_SetText(hItem, ValueString);

        checkRange_OneWire(&(pMsg->hWin));
        break;

    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id)
        {
        case ID_ONEWIREROM_SPINBOX_TEMPTEXT:
            switch(NCode) {
                case WM_NOTIFICATION_RELEASED:
                    getTemp();
                    break;
            }
            break;

        case ID_ONEWIREROM_BUTTON_CANCEL:
            switch(NCode) {
                case WM_NOTIFICATION_RELEASED:
                    ParameterChange_Handled = 1;
                    BlockChange = 0;
                    GUI_EndDialog(pMsg->hWin,0);
                    break;
            }
            break;
        case ID_ONEWIREROM_BUTTON_OK:
            switch(NCode)            {

            case WM_NOTIFICATION_RELEASED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_TEXT);

                sscanf(ValueString,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",(Parameter_Active->Value.ROM + 0),(Parameter_Active->Value.ROM + 1),(Parameter_Active->Value.ROM + 2),(Parameter_Active->Value.ROM + 3),(Parameter_Active->Value.ROM + 4),(Parameter_Active->Value.ROM + 5),(Parameter_Active->Value.ROM + 6),(Parameter_Active->Value.ROM + 7));

                ParameterChange_Handled = 0;
                BlockChange = 0;

                GUI_EndDialog(pMsg->hWin,1);
                break;
            case WM_NOTIFICATION_MOVED_OUT:
                break;
            }
            break;
        case ID_ONEWIREROM_SPINBOX_BUTTON_UP: // Notifications sent by 'Spinbox'
            switch(NCode)
            {

            case WM_NOTIFICATION_RELEASED:
                if (Index + 1 <= deviceCount-1)
                {
                    Index++;
                    checkRange_OneWire(&(pMsg->hWin));

                    hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_TEXT);
                    sprintf(ValueString,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",device[0+8*Index],device[1+8*Index],device[2+8*Index],device[3+8*Index],device[4+8*Index],device[5+8*Index],device[6+8*Index],device[7+8*Index]);
                    TEXT_SetText(hItem, ValueString);
                }
                break;

            }
            break;
        case ID_ONEWIREROM_SPINBOX_BUTTON_DOWN: // Notifications sent by 'Spinbox'
            switch(NCode)
            {

            case WM_NOTIFICATION_RELEASED:
                if (Index - 1 >= 0)
                {
                    Index--;
                    checkRange_OneWire(&(pMsg->hWin));

                    hItem = WM_GetDialogItem(pMsg->hWin, ID_ONEWIREROM_SPINBOX_TEXT);
                    sprintf(ValueString,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",device[0+8*Index],device[1+8*Index],device[2+8*Index],device[3+8*Index],device[4+8*Index],device[5+8*Index],device[6+8*Index],device[7+8*Index]);
                    TEXT_SetText(hItem, ValueString);
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

/** \brief Liest aus momentan ausgewähltem Sensor die Temperatur aus.
 *
 *  Wird beim Öffnen des Fenster, beim Klicken auf das Temperatur Textfeld oder bei Up oder Down aufgerufen.
*   Der Temperaturwert wird direkt in das Textfeld geschrieben.
 */
void getTemp() {
    WM_HWIN hItem;
    union Data ROM;
    double Temp1, Temp2;
    char Temperatur[255];

    hItem = WM_GetDialogItem(WM_HBKWIN, ID_ONEWIREROM_SPINBOX_TEMPTEXT);
    sprintf(Temperatur, "Lese Temperatur aus ...",Temp1, Temp2);
    TEXT_SetText(hItem, Temperatur);

    LOCK_OneWire = 1;



    sscanf(ValueString,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",ROM.ROM+0,ROM.ROM+1,ROM.ROM+2,ROM.ROM+3,ROM.ROM+4,ROM.ROM+5,ROM.ROM+6,ROM.ROM+7);


    DS1820_askTemp(ROM.ROM);
    HAL_Delay(800);
    //Temp1 = *DS18S20_readTemp(ROM.ROM);
    HAL_Delay(200);

    DS1820_askTemp(ROM.ROM);
    HAL_Delay(800);
    //Temp2 = *DS18B20_readTemp(ROM.ROM);

    LOCK_OneWire = 0;

    sprintf(Temperatur, "DS1820: %.2f\nDS18B20 %.2f",Temp1, Temp2);

    TEXT_SetText(hItem, Temperatur);
}

/** \brief Funktion die den Dialog öffnet
 */
void Edit_OneWireROM()
{
    Index = 0;
    GUI_CreateDialogBox(_aDialogCreate_OneWireROM, GUI_COUNTOF(_aDialogCreate_OneWireROM), _cbDialog_OneWireROM, WM_HBKWIN, 0, 0);
}
