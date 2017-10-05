/** \file MenuDLG.h
 *  \brief Header mit Funktionen die das Menue der aktuellen Menue-Struktur anzeigt und deren Ereignisse behandelt.
 *
 *  Sowohl die Erstellung des Menues wird hier realisiert, als auch die Verarbeitung der Ereignisse wenn ein Knopf betätigt wird.
 */

/** \addtogroup GUI
 *  @{
 */

/** \addtogroup MenuView
 *  @{
 */

#pragma once

//Include of Items
#include "Dialog.h"

//Include of DEFINES, Variables and Structs, math
#include "Layout_CONFIG.h"
#include "GUIControl.h"
#include <math.h>

//Include of Header
#include "Navigationpanel.h"


#include "Project_Pages_CONFIG.h"
#include "Firmware_Pages_CONFIG.h"


#include "Parameter.h"

/** \addtogroup WidgetIDs_Menu
 *  @{
 */
#define MENUVIEW_WINDOW_0             (GUI_ID_USER + 0x20)
#define MENUVIEW_SCROLLBAR_0          (GUI_ID_USER + 0x21)
#define MENUVIEW_TEXT_0               (GUI_ID_USER + 0x22)
#define MENUVIEW_TEXT1_0              (GUI_ID_USER + 0x32)
#define MENUVIEW_TEXT2_0              (GUI_ID_USER + 0x42)
#define MENUVIEW_IMAGE_0              (GUI_ID_USER + 0x52)
#define MENUVIEW_IMAGE_EDIT_0         (GUI_ID_USER + 0x62)
#define MENUVIEW_TEXT_VALUE_0         (GUI_ID_USER + 0x72)
#define MENUVIEW_TEXT_DEFAULTVALUE_0  (GUI_ID_USER + 0x82)
/**
  * @}
  */

struct MenuPage {
    uint8_t Count;                                      /**<\brief Number of Items in the Menu */
    char * _labels[MENU_MAX_Elements+1];                /**<\brief Array with Menu Item Title */
    char * _descriptions[MENU_MAX_Elements+1];          /**<\brief Array with Menu Item Description*/
    GUI_BITMAP * Icon[MENU_MAX_Elements+1];             /**<\brief Array with Icon - BMP Pointers*/
    struct MenuPage *Parent;                            /**<\brief Pointer to ParentMenu / One stage higher*/
    int ParentID;                                       /**<\brief Number of Item in ParentMenu which opens this Menu (starting at 0)*/

    struct MenuPage *Child[MENU_MAX_Elements+1];        /**<\brief Pointer to ChildMenu which will be opened if the MenuItem is hitted (starting at 0)*/

    struct Parameter *Parameter[MENU_MAX_Elements+1];   /**<\brief Pointer to Parameterstruct*/
    struct Page *Page[MENU_MAX_Elements+1];
    struct ParameterGroup *ParameterGroup[MENU_MAX_Elements+1];

    int (* MenuClick)(int ElementNumber);               /**<\brief Pointer to Click Callback Function*/
    int (* MenuRelease)(int ElementNumber);             /**<\brief Pointer to Release Callback Function*/
};


int Clicked;                /**<\brief Used for Click - Release - MovedOut Handling */

void _aDialogInit();
void _cbDialog(WM_MESSAGE * pMsg);
void Firmware_InitStructMenu(struct MenuPage * Menu, int Count);
void Firmware_MenuGetParents(struct MenuPage * Menu);
int ItemPos(int Item, int xory, int ItemIndex, int ScrollbarValue);
struct MenuPage * CreateMenufromParameterGroup(struct ParameterGroup * Group, uint8_t ParentID, struct MenuPage * Parent);
void UpdateParameters();
WM_HWIN CreateMenu(void);
