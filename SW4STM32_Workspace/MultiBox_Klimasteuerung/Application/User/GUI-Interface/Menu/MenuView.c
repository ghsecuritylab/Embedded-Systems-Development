/** \file MenuDLG.c
 *  \brief Quellcode mit Funktionen die das Menue der aktuellen Menue-Struktur anzeigt und deren Ereignisse behandelt.
 *
 *  Sowohl die Erstellung des Menues wird hier realisiert, als auch die Verarbeitung der Ereignisse wenn ein Knopf betätigt wird.
 */

/** \addtogroup GUI
 *  @{
 */

/** \addtogroup Menue
 *  @{
 */

#include "MenuView.h"

 /**<\brief Array mit Widget Elementen des Menus wird in \ref _aDialogInit ergaenzt und in \ref CreateMenu benutzt */
static GUI_WIDGET_CREATE_INFO _aDialogCreateMenu[2+7*MENU_MAX_Elements] = {
  { WINDOW_CreateIndirect, "Window", MENUVIEW_WINDOW_0, MENU_WINDOW_POSX, MENU_WINDOW_POSY, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT, 0, 0x0, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", MENUVIEW_SCROLLBAR_0, MENU_WINDOW_WIDTH - MENU_SCROLLBAR_WIDTH, 0, MENU_SCROLLBAR_WIDTH, MENU_WINDOW_HEIGHT,8, 0x0, 0 },
};

/** \brief Wird aufgerufen bevor das Menue gezeichnet wird und schreibt in \ref _aDialogCreateMenu die benoetigten WIDGET-Elemente.
 *
 *  Entsprechend der Anzahl der Maximalen Anzahl von Menueelementen werden die fuer jeden Menueeintrag in \ref _aDialogCreateMenu geschrieben.
 * \retval keins
 */
void _aDialogInit() {
    int i,j;
    for(i=0;i<MENU_MAX_Elements;i++) {
        GUI_WIDGET_CREATE_INFO TempElements[] = {
            { TEXT_CreateIndirect, "",  MENUVIEW_TEXT_0+i,                ItemPos(MENUVIEW_TEXT_0,0,i,0),               ItemPos(MENUVIEW_TEXT_0,1,i,0)-HEADER_HEIGHT,                     MENU_BUTTON_WIDTH,          MENU_BUTTON_HEIGHT,                             TEXT_CF_VCENTER,    0x0, 0 },
            { TEXT_CreateIndirect, "",  MENUVIEW_TEXT1_0+i,               ItemPos(MENUVIEW_TEXT1_0,0,i,0),              ItemPos(MENUVIEW_TEXT1_0,1,i,0)-HEADER_HEIGHT,                    MENU_BUTTON_WIDTH,          MENU_TEXT_HEADER_HEIGHT,                        TEXT_CF_VCENTER ,   0x0, 0 },
            { TEXT_CreateIndirect, "",  MENUVIEW_TEXT2_0+i,               ItemPos(MENUVIEW_TEXT2_0,0,i,0),              ItemPos(MENUVIEW_TEXT2_0,1,i,0)-HEADER_HEIGHT,                    MENU_BUTTON_WIDTH,          MENU_BUTTON_HEIGHT-MENU_TEXT_HEADER_HEIGHT,     TEXT_CF_VCENTER ,   0x0, 0 },
            { IMAGE_CreateIndirect, "", MENUVIEW_IMAGE_0+i,               ItemPos(MENUVIEW_IMAGE_0,0,i,0),              ItemPos(MENUVIEW_IMAGE_0,1,i,0)-HEADER_HEIGHT,                    MENU_IMAGE_WIDTH,           MENU_IMAGE_HEIGHT,                              0,                  0x0, 0 },
            { IMAGE_CreateIndirect, "", MENUVIEW_IMAGE_EDIT_0+i,          ItemPos(MENUVIEW_IMAGE_EDIT_0,0,i,0),         ItemPos(MENUVIEW_IMAGE_EDIT_0,1,i,0)-HEADER_HEIGHT,               MENU_IMAGE_VAR_WIDTH,      MENU_IMAGE_VAR_HEIGHT,                         0,                  0x0, 0 },
            { TEXT_CreateIndirect, "",  MENUVIEW_TEXT_VALUE_0+i,          ItemPos(MENUVIEW_TEXT_VALUE_0,0,i,0),         ItemPos(MENUVIEW_TEXT_VALUE_0,1,i,0)-HEADER_HEIGHT,               MENU_TEXT_VALUE_WIDTH,      MENU_TEXT_VALUE_HEIGHT,                         TEXT_CF_VCENTER | TEXT_CF_HCENTER,    0x0, 0 },
            { TEXT_CreateIndirect, "",  MENUVIEW_TEXT_DEFAULTVALUE_0+i,   ItemPos(MENUVIEW_TEXT_DEFAULTVALUE_0,0,i,0),  ItemPos(MENUVIEW_TEXT_DEFAULTVALUE_0,1,i,0)-HEADER_HEIGHT,        MENU_TEXT_DEFAULTVALUE_WIDTH,      MENU_TEXT_DEFAULTVALUE_HEIGHT,           TEXT_CF_VCENTER | TEXT_CF_HCENTER,    0x0, 0 },
        };

        for(j = 0; j<7;j++) {
            _aDialogCreateMenu[i+j*MENU_MAX_Elements+2] = TempElements[j];
        }
    }
  }

/** \brief Callback-Funktion die von STemWin aufgerufen wird, sobald eine Ereignis ausgeloest wurde.
 *
 *  Wird das Menue erstellt wird direkt danach die Message WM_INIT_Dialog an diese Funktion gesendet.
 *  In dieser Funktion werden die Elemente des Menues formatiert. Außerdem werden nicht benoetigte Elemente wieder geloescht. \n\n
 *
 *  Desweiteren wird jede Interaktion des Benutzers mit dem Menu (ueber den Touchscreen) in dieser Funktion behandelt und entsprechend richtig weiterverarbeitet.
 *  Die hier verarbeitetenden Benutzeraktionen sind: \n
 *  - Scrollbar wird benutzt (Verschiebung von den Menueelementen) \n
 *  - Click/Release/Moveout Ereignis eines Menuelementes \n
 *      -# evtl. Aufrufen eines Untermenues \n
 *      -# evtl. Aufrufen einer Menu-Callbackfunktion aus \ref MenuCallbackFunction.c \n
 *      -# evtl. Aufrufen eines Parameter-Dialogs \n
 *  \param pMsg: EreignisMessage des STemWin WindowManagers
 *  \retval keins
 */
void _cbDialogMenu(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
    int     NCode;
    int     Id;
    int i, temp;

    switch (pMsg->MsgId)
    {
    //INIT-Routine for formatting widgets and window and deleting unused Elements
    case WM_INIT_DIALOG:
        //Windowformat
        hItem = pMsg->hWin;
        WINDOW_SetBkColor(hItem, MENU_BACKGROUND_COLOR);

        //Formatting Used Elements
        for (i=0; i<Menu_Active->Count; i++)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_0+i);
            TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_NORMAL);

            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT1_0+i);
            TEXT_SetFont(hItem, MENU_ELEMENTS_FONT_LABEL);
            TEXT_SetText(hItem, Menu_Active->_labels[i]);
            TEXT_SetTextColor(hItem, MENU_ELEMENTS_FONT_COLOR);
            TEXT_SetBkColor(hItem, GUI_INVALID_COLOR);

            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT2_0+i);
            if(Menu_Active->_descriptions[i])
            {
                TEXT_SetFont(hItem, MENU_ELEMENTS_FONT_DESCRIPTION);
                TEXT_SetText(hItem, Menu_Active->_descriptions[i]);
                TEXT_SetTextColor(hItem, MENU_ELEMENTS_FONT_COLOR);
                TEXT_SetBkColor(hItem, GUI_INVALID_COLOR);
            } else {
                //WM_DeleteWindow(hItem);
            }

            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_0+i);
            if(Menu_Active->Icon[i])
            {
                Menu_Active->Icon[i]->pPal = &_PalIcon;
                IMAGE_SetBitmap(hItem, Menu_Active->Icon[i]);
            } else {
                WM_DeleteWindow(hItem);
            }

            if(Menu_Active->Parameter[i] != NULL)
            {
                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_EDIT_0+i);
                IMAGE_SetBitmap(hItem, Menu_Active->Parameter[i]->DataType->ICON);

                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT1_0+i);
                TEXT_SetText(hItem, Menu_Active->Parameter[i]->Name);

                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT2_0+i);
                TEXT_SetText(hItem, Menu_Active->Parameter[i]->Description);

                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_VALUE_0+i);
                TEXT_SetFont(hItem, MENU_ELEMENTS_FONT_VALUE);
                TEXT_SetTextColor(hItem, MENU_ELEMENTS_FONT_COLOR);
                TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_VALUE);

                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_DEFAULTVALUE_0+i);
                TEXT_SetFont(hItem, MENU_ELEMENTS_FONT_DEFAULTVALUE);
                TEXT_SetTextColor(hItem, MENU_ELEMENTS_FONT_COLOR);
                TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_DEFAULTVALUE);
            } else {
                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_EDIT_0+i);
                WM_DeleteWindow(hItem);
                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_VALUE_0+i);
                WM_DeleteWindow(hItem);
                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_DEFAULTVALUE_0+i);
                WM_DeleteWindow(hItem);
            }

            if(Menu_Active->ParameterGroup[i] != NULL)
            {
                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT1_0+i);
                TEXT_SetText(hItem, Menu_Active->ParameterGroup[i]->Name);

                hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT2_0+i);
                TEXT_SetText(hItem, Menu_Active->ParameterGroup[i]->Description);
            }


        }

        UpdateParameters();

        //Delete Unused Elements
        for (; i<MENU_MAX_Elements; i++)
        {
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT1_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT2_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_EDIT_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_VALUE_0+i);
            WM_DeleteWindow(hItem);
            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_DEFAULTVALUE_0+i);
            WM_DeleteWindow(hItem);
        }


        //Adding Scrollbar if Count of Elements is too high, delete it if not
        hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_SCROLLBAR_0);
        //Calculating how much Elements can be showed in window
        int ElementsPerShowedArea;
        ElementsPerShowedArea =  floor((MENU_WINDOW_HEIGHT - MENU_BUTTON_OFFSETBORDERY) / (MENU_BUTTON_HEIGHT + MENU_BUTTON_OFFSETY));
        if (Menu_Active->Count > ElementsPerShowedArea)
        {
            //Setting Value of the Scrollbar
            SCROLLBAR_SetNumItems(hItem, (Menu_Active->Count - ElementsPerShowedArea + 1) * MENU_SCROLLBAR_PARTS);
            SCROLLBAR_SetColor(hItem, SCROLLBAR_CI_THUMB, MENU_SCROLLBAR_COLOR_THUMB);
            SCROLLBAR_SetColor(hItem, SCROLLBAR_CI_SHAFT, MENU_SCROLLBAR_COLOR_SHAFT);
            SCROLLBAR_SetColor(hItem, SCROLLBAR_CI_ARROW, MENU_SCROLLBAR_COLOR_ARROWS);

            //SCROLLBAR_SetSkinFlex(hItem);

        }
        else
        {
            //Scrollbar not used --> delete
            WM_DeleteWindow(hItem);
        }

        //Initializing Clicked - Variable (see Touchevents)
        Clicked = 0;

        WindowChange_Handled = 1;

        break;

    case WM_NOTIFY_PARENT:
        if (!BlockChange) {
            //Touchevent
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;

            if (Id == MENUVIEW_SCROLLBAR_0)
            {
                //Scrollbar Move Items
                switch(NCode)
                {
                    case WM_NOTIFICATION_CLICKED:
                        break;
                    case WM_NOTIFICATION_RELEASED:
                        break;
                    case WM_NOTIFICATION_VALUE_CHANGED:
                        //Value - Change --> Move Items

                        //Get Value
                        hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_SCROLLBAR_0);
                        temp = SCROLLBAR_GetValue(hItem);

                        //Moving Elements >> Stop Redrawing before moving all Elements, enable it after everything has been moved.
                        for (i=0; i<Menu_Active->Count; i++)
                        {
                            ReDrawStopped = 1;

                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_TEXT_0,0,i,temp), ItemPos(MENUVIEW_TEXT_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT1_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_TEXT1_0,0,i,temp), ItemPos(MENUVIEW_TEXT1_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT2_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_TEXT2_0,0,i,temp), ItemPos(MENUVIEW_TEXT2_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_IMAGE_0,0,i,temp), ItemPos(MENUVIEW_IMAGE_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_IMAGE_EDIT_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_IMAGE_EDIT_0,0,i,temp), ItemPos(MENUVIEW_IMAGE_EDIT_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_VALUE_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_TEXT_VALUE_0,0,i,temp), ItemPos(MENUVIEW_TEXT_VALUE_0,1,i,temp));
                            hItem = WM_GetDialogItem(pMsg->hWin, MENUVIEW_TEXT_DEFAULTVALUE_0+i);
                            WM_MoveTo(hItem,    ItemPos(MENUVIEW_TEXT_DEFAULTVALUE_0,0,i,temp), ItemPos(MENUVIEW_TEXT_DEFAULTVALUE_0,1,i,temp));

                            ReDrawStopped = 0;
                        }

                        break;
                }
            } else if  (Id >= MENUVIEW_TEXT_0)  {
                //Touch Event on Textboxes / Menu Elements

                //Changing EventID --> Same Eventhandling for Touch on both Textboxes (one for Title, one for description)
                if(Id >= MENUVIEW_TEXT_DEFAULTVALUE_0)
                {
                    Id = Id - MENUVIEW_TEXT_DEFAULTVALUE_0 + MENUVIEW_TEXT_0;
                } else if(Id >= MENUVIEW_TEXT_VALUE_0)
                {
                    Id = Id - MENUVIEW_TEXT_VALUE_0 + MENUVIEW_TEXT_0;
                } else if(Id >= MENUVIEW_IMAGE_EDIT_0)
                {
                    Id = Id - MENUVIEW_IMAGE_EDIT_0 + MENUVIEW_TEXT_0;
                } else if(Id >= MENUVIEW_IMAGE_0)
                {
                    Id = Id - MENUVIEW_IMAGE_0 + MENUVIEW_TEXT_0;
                } else if(Id >= MENUVIEW_TEXT2_0)
                {
                    Id = Id - MENUVIEW_TEXT2_0 + MENUVIEW_TEXT_0;
                } else if(Id >= MENUVIEW_TEXT1_0)
                {
                    Id = Id - MENUVIEW_TEXT1_0 + MENUVIEW_TEXT_0;
                }

                switch(NCode)
                {
                    /*Click-Event
                    --> Changing Color of Elements to MENU_ELEMENTS_COLOR_PRESSED
                    --> Setting Clicked to 1 for remembering Click
                    --> Calling MenuClick function if defined*/
                    case WM_NOTIFICATION_CLICKED:
                        if(Clicked == 0)
                        {
                            hItem = WM_GetDialogItem(pMsg->hWin, Id);
                            TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_PRESSED);

                            I2C_IO_USER_SetBuzzer(5,200);

                            Clicked = 1;
                        }

                        if (Menu_Active->MenuClick != NULL) {
                            Menu_Active->MenuClick(Id - MENUVIEW_TEXT_0);
                        }
                        break;

                    /*Release-Event -
                    EVENT PERFORMING ONLY IF CLICKED == 1, BECAUSE USER HAS THE OPTION TO CLICK ON ELEMENT AND THEN MOVE OUT FOR ABORTING
                    --> Changing Color of Elements to NORMAL
                    --> Setting Clicked to 0
                    --> Setting given ChildMenu of Element to ActiveMenu, if none is given, nothing happens
                    --> Calling MenuRelease function if defined*/
                    case WM_NOTIFICATION_RELEASED:
                        if(Clicked == 1)
                        {
                            hItem = WM_GetDialogItem(pMsg->hWin, Id);
                            TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_NORMAL);

                            Menu_isDynamic = 0;

                            /*if (Menu_Active->ParameterGroup[Id - MENUVIEW_TEXT_0] != NULL) {
                                Menu_Active = CreateMenufromParameterGroup(Menu_Active->ParameterGroup[Id - MENUVIEW_TEXT_0], Id - MENUVIEW_TEXT_0);
                                WindowChange_Handled = 0;
                            } else */if (Menu_Active->Parameter[Id - MENUVIEW_TEXT_0] != NULL ) {
                                Parameter_Active = Menu_Active->Parameter[Id - MENUVIEW_TEXT_0];
                                DialogOpen_Handled = 0;

                                /*int temp2;

                                temp2 = Menu_Active->Parameter[Id - MENUVIEW_TEXT_0]->EditType;

                                switch (temp2) {
                                    case 0: Edit_Toggle(Menu_Active->Parameter[Id - MENUVIEW_TEXT_0]); break;
                                    case 2: Edit_Keypad_Hex(Menu_Active->Parameter[Id - MENUVIEW_TEXT_0], 1); break;
                                    case 3: Edit_UpDown(Menu_Active->Parameter[Id - MENUVIEW_TEXT_0]); break;
                                    case 1: Edit_Keypad_Hex(Menu_Active->Parameter[Id - MENUVIEW_TEXT_0],0); break;
                                }*/
                            } else if (Menu_Active->Page[Id - MENUVIEW_TEXT_0]) {
                                Page_Active = Menu_Active->Page[Id - MENUVIEW_TEXT_0];
                                state = 2;
                                WindowChange_Handled = 0;

                            } else if (Menu_Active->Child[Id - MENUVIEW_TEXT_0])
                            {
                                Menu_Active = Menu_Active->Child[Id - MENUVIEW_TEXT_0];
                                WindowChange_Handled = 0;
                            } else if (Menu_Active->MenuRelease != NULL) {
                                Menu_Active->MenuRelease(Id - MENUVIEW_TEXT_0);
                            }

                        }

                        Clicked = 0;
                        break;

                    /*Release-Event -
                    EVENT PERFORMING ONLY IF CLICKED == 1, BECAUSE USER HAS THE OPTION TO CLICK ON ELEMENT AND THEN MOVE OUT FOR ABORTING
                    --> Changing Color of Elements to NORMAL
                    --> Setting Clicked to 2, so the CLICK EVENT can be handled again if RELEASE is called before*/
                    case WM_NOTIFICATION_MOVED_OUT:

                        hItem = WM_GetDialogItem(pMsg->hWin, Id);
                        TEXT_SetBkColor(hItem, MENU_ELEMENTS_COLOR_NORMAL);

                        Clicked = 2;
                        break;
                }
                break;
            }
            break;



    //Additional EventHandling
    default:
        WM_DefaultProc(pMsg);
        break;
    }
    }
}

/** \brief Wird beim ersten Zeichnen des Menues und beim Benutzen der Scrollbar aufgerufen zur Berechnung der einzelnen WidgetPositionen der Menuelemente
 *
 *  Die Darstellung von Parameterwerten wird durch den Aufruf dieser Funktion mit den Werten der Parametern aktualisiert.
 *  \param Item: MENUVIEW_0 des entsprechenden Objektes dessen Position berechnet werden soll
 *  \param xory: Gibt an ob die x- oder y-Position berechnet werden soll
 *      \arg 0: x-Koordinate
 *      \arg 1: y-Koordinate
 *  \param ScrollbarValue: Wert der Scrollbar
 *  \retval Berechnete Position des Window-Elements
 */
int ItemPos(int Item, int xory, int ItemIndex, int ScrollbarValue) {
    //Calculates the Position of the Items in the Window

    switch(xory) {
    case 0: // x
        switch (Item) {
            case MENUVIEW_TEXT_0:
                return MENU_BUTTON_OFFSETBORDERX;
            case MENUVIEW_TEXT1_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_TEXT_OFFSETX;
            case MENUVIEW_TEXT2_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_TEXT_OFFSETX;
            case MENUVIEW_IMAGE_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_IMAGE_OFFSETX;
            case MENUVIEW_IMAGE_EDIT_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_IMAGE_VAR_OFFSETX;
            case MENUVIEW_TEXT_VALUE_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_TEXT_VALUE_OFFSETX;
            case MENUVIEW_TEXT_DEFAULTVALUE_0:
                return MENU_BUTTON_OFFSETBORDERX + MENU_TEXT_DEFAULTVALUE_OFFSETX;
        }
        break;
    case 1: //y
        switch (Item) {
            case MENUVIEW_TEXT_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)                             -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_TEXT1_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)                             -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_TEXT2_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)+MENU_TEXT_HEADER_HEIGHT     -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_IMAGE_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)+MENU_IMAGE_OFFSETY          -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_IMAGE_EDIT_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)+MENU_IMAGE_VAR_OFFSETY     -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_TEXT_VALUE_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)+MENU_TEXT_VALUE_OFFSETY     -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
            case MENUVIEW_TEXT_DEFAULTVALUE_0:
                return HEADER_HEIGHT + MENU_BUTTON_OFFSETBORDERY+ItemIndex*(MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)+MENU_TEXT_DEFAULTVALUE_OFFSETY     -ScrollbarValue*((MENU_BUTTON_HEIGHT+MENU_BUTTON_OFFSETY)/MENU_SCROLLBAR_PARTS);
        }
    }

    return 0;
}

/** \brief Wird waehrend jeder Ereignisbehandlung von \ref _cbDialogMenu aufgerufen. Aktualisiert Darstellung der Werte von Parametern.
 *
 *  Die Darstellung von Parameterwerten wird durch den Aufruf dieser Funktion mit den Werten der Parametern aktualisiert.
 * \retval keins
 */
void UpdateParameters() {
    WM_HWIN hItem;
    int i;

    for (i=0; i<Menu_Active->Count; i++) {
        hItem = WM_GetDialogItem(WM_HBKWIN, MENUVIEW_TEXT_VALUE_0+i);

        if (Menu_Active->Parameter[i] != NULL) {
            char * temp3;
            //sscanf(temp3, Menu_Active->Parameter[i]->DataType->OutStr, Menu_Active->Parameter[i]->Value);
            temp3 = Parameter_getValAsStr(Menu_Active->Parameter[i]);
            TEXT_SetText(hItem,temp3);

            hItem = WM_GetDialogItem(WM_HBKWIN, MENUVIEW_TEXT_DEFAULTVALUE_0+i);
            strcpy(temp3,Parameter_getDefValAsStr(Menu_Active->Parameter[i]));
            TEXT_SetText(hItem,temp3);
        }
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 *//*
struct MenuPage * CreateMenufromParameterGroup(struct ParameterGroup * Group, uint8_t ParentID) {
    struct MenuPage * Menu = malloc(sizeof(struct MenuPage));

    uint8_t i;

    InitStruct(Menu,Group->Count);

    Menu->Parent = Menu_Active;
    Menu->ParentID = ParentID;

    for(i=0;i<Group->Count;i++) {
         Menu->ParameterGroup[i] = Group->ChildGroups[i];
         Menu->Parameter[i] = Group->Para[i];
    }

    Menu_Dynamic = Menu;
    Menu_isDynamic = 1;

    return Menu;
};*/

struct MenuPage * CreateMenufromParameterGroup(struct ParameterGroup * Group, uint8_t ParentID, struct MenuPage * Parent) {
    struct MenuPage * Menu = malloc(sizeof(struct MenuPage));

    uint8_t i;

    Firmware_InitStructMenu(Menu,Group->Count);

    Menu->Parent = Parent;
    Menu->ParentID = ParentID;

    Menu->Parent->Child[ParentID] = Menu;

    for(i=0;i<Group->Count;i++) {
         Menu->ParameterGroup[i] = Group->ChildGroups[i];
         Menu->Parameter[i] = Group->Para[i];
    }

    return Menu;
};

/** \brief Wird aufgerufen wenn aus Hauptansicht ins Menue gewechselt werden soll bzw. aus einem Menue in ein Untermenue.
 *
 * Entsprechend der Anzahl der Maximalen Anzahl von Menueelementen werden die fuer jeden Menueeintrag in \ref _aDialogCreateMenu geschrieben.
 * \retval Window-Handle Objekt
 */
WM_HWIN CreateMenu(void) {
    //Creating and Displaying Menu after Clearing the screen
    WM_HWIN hWin;

    _aDialogInit();

    hWin = GUI_CreateDialogBox(_aDialogCreateMenu, GUI_COUNTOF(_aDialogCreateMenu), _cbDialogMenu, WM_HBKWIN, 0, 0);

    //SCROLLBAR_CreateAttached(hWin, SCROLLBAR_CF_VERTICAL);

    return hWin;
}

