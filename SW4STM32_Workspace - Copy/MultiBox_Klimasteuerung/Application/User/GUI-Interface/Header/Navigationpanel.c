/** \file HeaderDLG.c
 *  \brief Quellcode mit Funktionen die das Navigationspanel für die Menü-Struktur und die Hauptansicht realisiert.
 *
 *  Sowohl die Erstellung des Navigationspanels wird hier realisiert, als auch die Verarbeitung der Ereignisse wenn ein Knopf betätigt wird.
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Navigationpanel
 *  @{
 */

#include "Navigationpanel.h"

/** \brief Wird vor Erstellen des Navigationspanels aufgerufen und erstellt die benoetigten Buttons des Panels.
 *
 *  \retval keins
 */
void aDialogHeaderInit() {
    int i,j;
    for(i=0;i<HEADER_MAX_ELEMENTS;i++) {
        GUI_WIDGET_CREATE_INFO TempElements[] = {
        { BUTTON_CreateIndirect, "Button", ID_HEADER_BUTTON_0+i, HEADER_BUTTON_WIDTH*i, 0,HEADER_BUTTON_WIDTH, HEADER_HEIGHT, 0, 0x0, 0 }};
        for(j = 0; j<1;j++) {
            aDialogCreate_Header[i+j*MENU_MAX_Elements+2] = TempElements[j];
        }
    }
}

/** \brief Wird bei jeder Nutzerinteraktion (Touchscreen) mit dem Navigationspanel aufgerufen.
 *
 *  Diese Funktion wird sowohl bei Nutzerinteraktion mit dem Navigationspanel aufgerufen, als auch
 *  Je nachdem wo sich der Nutzer momentan befindet (Hauptansicht oder im Menu) verhaelt sich diese Funktion unterschiedlich. \n
 *  Innerhalb der Hauptansicht kann nur ins Menue gewechselt werden und die entsprechenden Variablen werden hier gesetzt, der eigentliche
 *  Wechsel der Fenster erfolgt im \ref Programm.c .
 *  \n
 *  Befindet sich der Nutzer momentan in der MenuStruktur bedeutet ein Ereignis hier entweder \n
 *  - der Wechsel in ein anderes Menu \n
 *  - Wechsel zurueck in die Hauptansicht \n
 *  \retval keins
 */
void cbDialog_Header(WM_MESSAGE * pMsg)
{
    WM_HWIN      hItem;
    int          NCode;
    int          Id;
    int          i;
    int           Hierarchical_ID;
    struct MenuPage * Menu_Temp;

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, HEADER_BACKGROUND_COLOR);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_IMAGE_0);

        for (i=0; i<HEADER_MAX_ELEMENTS; i++)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_BUTTON_0+i);
            BUTTON_SetFont(hItem, HEADER_FONT_NORMAL);
            BUTTON_SetSkin(hItem, Header_DrawSkinFlex_BUTTON);
        }

        break;


    case WM_NOTIFY_PARENT:
        {
            if ((!BlockChange) & (WindowChange_Handled== 1)) {
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            Hierarchical_ID = 0;

            switch(Id)
            {
            case ID_HEADER_BUTTON_0: // Notifications sent by 'Header'
                switch(NCode)
                {
                case WM_NOTIFICATION_RELEASED:
                    //Es wurde auf den ersten Knopf gedrückt
                    switch (state) {
                        case 0: state = 1; Menu_Active = Menu_Home; break;
                        case 1: state = 0; break;
                        case 2: state = 1; Page_Active = MainPageArray[0]; break;
                    }

                    WindowChange_Handled = 0;

                    I2C_IO_USER_SetBuzzer(5,150);

                    break;
                case WM_NOTIFICATION_CLICKED:
                    break;
                case WM_NOTIFICATION_MOVED_OUT:
                    break;
                }
                break;

            default:
                switch (state) {
                    case 1:
                    //im Menue
                    if (NCode == WM_NOTIFICATION_RELEASED)
                    {
                        //Herausfinden der Tiefe des Menus
                        Menu_Temp = Menu_Active;
                        int Menu_Depth;
                        Menu_Depth = 0;

                        while (Menu_Temp != Menu_Home)
                        {
                            Menu_Depth++;
                            Menu_Temp = Menu_Temp->Parent;
                        }

                        Hierarchical_ID = Menu_Depth + 1 - (Id - ID_HEADER_BUTTON_0);

                        for(; Hierarchical_ID>0; Hierarchical_ID--)
                        {
                            Menu_Active = Menu_Active->Parent;
                        }

                        I2C_IO_USER_SetBuzzer(5,150);

                        WindowChange_Handled = 0;
                    }
                    break;

                case 0:

                    //im Main
                    if (NCode == WM_NOTIFICATION_RELEASED)
                    {
                        Hierarchical_ID = (Id - ID_HEADER_BUTTON_0 - 1);

                        Page_Active = MainPageArray[Hierarchical_ID];

                        I2C_IO_USER_SetBuzzer(5,150);

                        WindowChange_Handled = 0;
                    }
                    break;
                }
                break;
            }
            break;
        }

    default:
        WM_DefaultProc(pMsg);
        break;
    }
    }

}

/** \brief Erstellt das Navigationspanel
 *
 *  Wird von \ref Program.c aufgerufen und erstellt das Navigationspanel.
 *  \retval Window-Handle Navigationspanel
 */
WM_HWIN CreateHeader(void) {
  WM_HWIN hWin;

  aDialogHeaderInit();

  hWin = GUI_CreateDialogBox(aDialogCreate_Header, GUI_COUNTOF(aDialogCreate_Header), cbDialog_Header, WM_HBKWIN, 0, 0);
  return hWin;
}

/** \brief Aktualisiert das Navigationspanel anhand des aktiven Menues.
 *
 *  Wird nach dem Wechsel auf eine neue MenuPage von \ref Program.c aufgerufen. \n
 *  Befinden wir uns
 *  - im Menu \n
 *      - werden gemaess der MenuPages Buttons ein- und ausgeblendet (durch Verschiebungen). \n
 *      - werden die Buttons entsprechend beschriftet. \n
 *  - ausserhalb des Menues/in der Hauptansicht, wird nur der erste Button als Menuebutton gezeigt.  \n
 *  \param inMenu: Gibt Menuestatus an(=1 -> im Menue; =0 -> in der Hauptansicht)
 *  \retval keins
 */
int ChangeHeader() {
    WM_HWIN hItem;

    int i;
    int Menu_Depth;
    char * Menu_Items[HEADER_MAX_ELEMENTS];
    GUI_BITMAP ** Menu_Icons[HEADER_MAX_ELEMENTS];

    for (i=0;i<HEADER_MAX_ELEMENTS; i++) {
        Menu_Icons[i] = NULL;
    }


    i=1;

    switch (state) {
        case 2:
            hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0);
            BUTTON_SetText(hItem,"Zurück");
            BUTTON_SetBitmapEx(hItem, BUTTON_BI_UNPRESSED, &bmMenu, 0, 0);

            break;

        case 0:     //Main
            hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0);
            BUTTON_SetText(hItem,"Menu");
            BUTTON_SetBitmapEx(hItem, BUTTON_BI_UNPRESSED, &bmMenu, 0,0);

            for (;i<=MAINPAGE_COUNT;i++) {
                hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0+i);
                WM_MoveTo(hItem, i*HEADER_BUTTON_WIDTH,0);
                BUTTON_SetText(hItem,MainPageArray[i-1]->Name);

                if (strcmp(MainPageArray[i-1]->Name, Page_Active->Name)) {
                    BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, HEADER_BUTTON_COLOR_NORMAL);
                } else {
                    BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, HEADER_BUTTON_COLOR_PRESSED);
                }

                BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,NULL,0,0);
                BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
            }



            break;

        case 1:     //Menu
            Menu_Depth = 0;

            struct MenuPage * Menu_Temp;
            Menu_Temp = Menu_Active;

            while (Menu_Temp != Menu_Home) {
                Menu_Depth++;
                Menu_Temp = Menu_Temp->Parent;
            }

            Menu_Temp = Menu_Active;
            for(;i<Menu_Depth+1;i++) {
                if (Menu_Temp->Parent->Icon[Menu_Temp->ParentID]) {
                    Menu_Icons[Menu_Depth-i] = (GUI_BITMAP **) (Menu_Temp->Parent->Icon[Menu_Temp->ParentID]);
                }

                Menu_Items[Menu_Depth-i] = (Menu_Temp->Parent->ParameterGroup[Menu_Temp->ParentID] != NULL) ? Menu_Temp->Parent->ParameterGroup[Menu_Temp->ParentID]->Name : Menu_Temp->Parent->_labels[Menu_Temp->ParentID];
                Menu_Temp = Menu_Temp->Parent;
            }


            hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0);
            BUTTON_SetText(hItem,"");
            BUTTON_SetBitmapEx(hItem, BUTTON_BI_UNPRESSED, &bmMain, 0,0);

            for (i=1;i<=Menu_Depth;i++) {
                hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0+i);
                BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, HEADER_BUTTON_COLOR_NORMAL);
                if (Menu_Icons[i-1]!=NULL) {
                    BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,(GUI_BITMAP *) Menu_Icons[i-1],(HEADER_BUTTON_WIDTH-MENU_IMAGE_WIDTH) / 2,(HEADER_HEIGHT-MENU_IMAGE_HEIGHT) / 2);
                    BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_BOTTOM);
                } else {
                    BUTTON_SetBitmapEx(hItem,BUTTON_BI_UNPRESSED,NULL,0,0);
                    BUTTON_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

                }
                BUTTON_SetText(hItem,Menu_Items[i-1]);
                WM_MoveTo(hItem, i*HEADER_BUTTON_WIDTH,0);
            }

        break;
    }

    for (;i<8;i++) {
        hItem = WM_GetDialogItem(WM_HBKWIN, ID_HEADER_BUTTON_0+i);
        WM_MoveTo(hItem, i*HEADER_BUTTON_WIDTH,-HEADER_HEIGHT);
    }

    return 1;
}
