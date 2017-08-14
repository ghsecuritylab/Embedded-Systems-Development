/** \file Menu_CONFIG.c
 *  \brief Definition der Menuestruktur.
 *
 *  Die hier enthaltene Funktione \ref Init_Menus() wird beim Start des Microcontrollers aufgerufen und enthält die Definition der gesamten Menuestruktur.
 *  Die beiden anderen Funktionen dienen der Initialisierung der MenuStrukturen und werden innerhalb der \ref Init_Menus - Funktion aufgerufen.
 */

/** \addtogroup GUI
 *  @{
 */

/** \addtogroup Menue
 *  @{
 */

/** \addtogroup Menue-Konfiguration
 *  @{
 */
 #pragma once

#include "MenuView.h"
//#include "Project_MenuView_CONFIG.h"

//Include bitmaps
extern GUI_BITMAP bmSystem;
extern GUI_BITMAP bmwindow_information;
extern GUI_BITMAP bmBild3;
extern GUI_BITMAP bmHardware;

//MenuPages
struct MenuPage Ebene1;
struct MenuPage Ebene11;
struct MenuPage Ebene111;
struct MenuPage Ebene1111;
struct MenuPage Ebene1112;
struct MenuPage Ebene113;
struct MenuPage Ebene114;
struct MenuPage Ebene12;
struct MenuPage Ebene121;
struct MenuPage Ebene122;


void Firmware_Init_Menus();
void Firmware_InitStructMenuMenu(struct MenuPage * Menu, int Count);
void Firmware_MenuGetParents(struct MenuPage * Menu);

