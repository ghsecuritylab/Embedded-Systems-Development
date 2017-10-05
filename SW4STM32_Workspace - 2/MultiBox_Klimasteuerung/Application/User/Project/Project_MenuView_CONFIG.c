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
#include "MenuView.h"

/** \brief Enthaelt die Nutzer-Konfiguration der Menue-Struktur.
 *
 *  Hier wird die vom Nutzer benoetigte Menu-Konfiguration in Form von einzelnen \ref MenuPage Strukturen erstellt und konfiguriert.
 *  Am Anfang der Funktion werden einige fuer das Funktionieren wichtige Variablen intialisiert und am Ende wird die rekursive Funktion \ref GetParents aufgerufen. \n
 *  \n
 *  Zur Erstellung einer neuen \ref MenuPage muessen folgende Dinge beachtet werden: \n
 *      - MenuPage muss zuerst mit \ref InitStruct initialisiert werden \n
 *      - MenuPage muss von einer anderen MenuPage als Child eines MenuElementes verlinkt sein \n
 *      - Mindestens MenuPage._labels sollte mit den Namen der MenuElemente gefüllt sein \n
 *      - Je nach Art des Menues sollten (auch ein Mix daraus ist denkbar) \n
 *          -# Child-Menues definiert sein \n
 *          -# Parameter den Elementen zugeordnet sein \n
 *          -# Callback Funktionen MenuClick bzw. MenuRelease zugeordnet sein \n
 *  \retval keins
 */
void Project_Init_Menus() {

    Firmware_MenuGetParents(Menu_Home);
}
