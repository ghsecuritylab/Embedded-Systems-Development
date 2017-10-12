/** \file HeaderDLG.h
 *  \brief Header mit Funktionen die das Navigationspanel für die Menü-Struktur und die Hauptansicht realisiert.
 *
 *  Sowohl die Erstellung des Navigationspanels wird hier realisiert, als auch die Verarbeitung der Ereignisse wenn ein Knopf betätigt wird.
 */

/** \addtogroup GUI
 *  @{
 */

/** \addtogroup Navigationpanel
 *  @{
 */

#pragma once

#include "Layout_CONFIG.h"
#include "MenuView.h"
#include "Project_Pages_CONFIG.h"
#include "Firmware_Pages_CONFIG.h"
#include "DIALOG.h"

/** \addtogroup WidgetIDs_Header
 *  @{
 */
#define ID_HEADER_WINDOW_1 (GUI_ID_USER + 0xE0)
#define ID_HEADER_IMAGE_0 (GUI_ID_USER + 0xE1)
#define ID_HEADER_BUTTON_0 (GUI_ID_USER + 0xE2)
#define ID_HEADER_BUTTON_1 (GUI_ID_USER + 0xE3)
#define ID_HEADER_BUTTON_2 (GUI_ID_USER + 0xE4)
#define ID_HEADER_BUTTON_3 (GUI_ID_USER + 0xE5)
#define ID_HEADER_BUTTON_4 (GUI_ID_USER + 0xE6)
#define ID_HEADER_BUTTON_5 (GUI_ID_USER + 0xE7)
#define ID_HEADER_BUTTON_6 (GUI_ID_USER + 0xE8)
#define ID_HEADER_BUTTON_7 (GUI_ID_USER + 0xE9)
/**
  * @}
  */


/**<\brief Array mit Widget Elementen des Headers wird in \ref _aDialogInit ergaenzt und in \ref CreateHeader benutzt */
static GUI_WIDGET_CREATE_INFO aDialogCreate_Header[2+HEADER_MAX_ELEMENTS] = {
  { WINDOW_CreateIndirect, "Header", ID_HEADER_WINDOW_1, 0, 0, MENU_WINDOW_WIDTH, HEADER_HEIGHT, 0, 0x0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_HEADER_IMAGE_0, MENU_WINDOW_WIDTH - HEADER_IMAGE_WIDTH, HEADER_IMAGE_WIDTH, HEADER_HEIGHT, 0, 0, 0 },
};

/****************************************

DEFINITION Skinning-Routines

****************************************/

extern int Header_DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

extern GUI_CONST_STORAGE GUI_BITMAP bmMenu;
extern GUI_CONST_STORAGE GUI_BITMAP bmMain;

void aDialogHeaderInit();
void cbDialog_Header(WM_MESSAGE * pMsg);
WM_HWIN CreateHeader(void);
int ChangeHeader();


