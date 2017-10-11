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

 #include "Firmware_MenuView_CONFIG.h"

/** \brief Initialisiert fuer die Menues benoetigte Parameter und enthaelt die Nutzer-Konfiguration der Menue-Struktur.
 *
 *  Hier wird die vom Nutzer benoetigte Menu-Konfiguration in Form von einzelnen \ref MenuPage Strukturen erstellt und konfiguriert.
 *  Am Anfang der Funktion werden einige fuer das Funktionieren wichtige Variablen intialisiert und am Ende wird die rekursive Funktion \ref GetParents aufgerufen. \n
 *  \n
 *  Zur Erstellung einer neuen \ref MenuPage muessen folgende Dinge beachtet werden: \n
 *      - MenuPage muss zuerst mit \ref Firmware_InitStructMenu initialisiert werden \n
 *      - MenuPage muss von einer anderen MenuPage als Child eines MenuElementes verlinkt sein \n
 *      - Mindestens MenuPage._labels sollte mit den Namen der MenuElemente gefüllt sein \n
 *      - Je nach Art des Menues sollten (auch ein Mix daraus ist denkbar) \n
 *          -# Child-Menues definiert sein \n
 *          -# Parameter den Elementen zugeordnet sein \n
 *          -# Callback Funktionen MenuClick bzw. MenuRelease zugeordnet sein \n
 *  \retval keins
 */
void Firmware_Init_Menus() {
    //General Initialization
    Menu_Active = NULL;         //Currently no Active Menu
    Menu_Home = &Ebene1;        //Pointer to Home Menu / First stage

    //MENU-Configuring

    //Hauptebene
    {
        Firmware_InitStructMenu(&Ebene1,2);
        Ebene1._labels[0] = "System";
        Ebene1._labels[1] = "Projekt";
        Ebene1.Child[0] = &Ebene11;
        Ebene1.Child[1] = &Ebene12;
        Ebene1.Icon[0] = &bmSystem;
    }

    //Systemebene
    {
        Firmware_InitStructMenu(&Ebene11,6);
        Ebene11._labels[0] = "Kommunikation";
        Ebene11.Icon[0] = &bmBild3;
        Ebene11._descriptions[0] = "Change Connectivity settings";
        Ebene11._labels[1] = "Systeminfo";
        Ebene11.Icon[2] = &bmwindow_information;
        Ebene11._labels[2] = "GeräteInfo";
        Ebene11._labels[3] = "System zurücksetzen";
        Ebene11._labels[4] = "Hardware";

        Ebene11.Icon[2] = &bmHardware;

        /* Real Time Clock - RTC */
		Ebene11._labels[5] = "Datum und Uhrzeit einstellen";
		Ebene11.Page[5] = &RTC_Page;

        Ebene11.Child[0] = &Ebene111;
        Ebene11.Child[2] = &Ebene113;
        Ebene11.Child[3] = &Ebene114;

        Ebene11.Page[4] = &HardwarePage;

        //System --> Kommunikationsebene
        {
            Firmware_InitStructMenu(&Ebene111,3);
            Ebene111._labels[0] = "CAN";
            Ebene111._labels[1] = "Ethernet";
            Ebene111._labels[2] = "RS232";

            Ebene111.ParameterGroup[0] = &ParameterGroup_CAN;//Ebene1111;
            Ebene111.Child[1] = &Ebene1112;

            //System --> Kommunikationsebene --> Ethernet
            {
                Firmware_InitStructMenu(&Ebene1112,3);
                Ebene1112._labels[0] = "MAC";
                Ebene1112._labels[1] = "IP";
                Ebene1112._labels[2] = "Active";
            }
        }

        //System --> GeräteInfo
        {
            Firmware_InitStructMenu(&Ebene113,1);
            Ebene113._labels[0] = "ID";
        }

        //System --> System zurücksetzen
        {
            Firmware_InitStructMenu(&Ebene114,2);
            Ebene114._labels[0] = "Parametervergleich";
            Ebene114._labels[1] = "Zurücksetzen";
        }
    }

    //Projektebene
    {
        Firmware_InitStructMenu(&Ebene12,4);
        Ebene12._labels[4] = "Projekt zurücksetzen";

        Ebene12.ParameterGroup[0] = &ParameterGroup_ClickBoards;
        Ebene12.ParameterGroup[1] = &ParameterGroup_Prozessparameter;
        Ebene12.ParameterGroup[2] = &ParameterGroup_Zustandsgroessen;
        Ebene12.Child[3] = &Ebene122;

        //Projekt --> Projekt zurücksetzen
        {
            Firmware_InitStructMenu(&Ebene122,2);
            Ebene122._labels[0] = "Vergleich Standard - Ist";
            Ebene122.Parameter[1] = &PARA_LOAD_FLASH;
        }
    }

    //Project_Init_Menus();

    Firmware_MenuGetParents(Menu_Home);
}

/** \brief Initialisiert neue \ref MenuPage Strukturen
 *
 *  Initialisierung der jeweiligen MenuPage, beschreiben der verwendeten Felder mit leeren Zeichenketten bzw. mit NULL-Zeigern
 *  \param Menu: Zeiger auf Struktur
 *  \param Count: Anzahl der verwendeten MenuElemente
 *  \retval keins
 */
void Firmware_InitStructMenu(struct MenuPage * Menu, int Count){
    Menu->Count = Count;
    int i;
    for(i=0;i<Menu->Count;i++) {
        Menu->_labels[i] = "";
        Menu->_descriptions[i] = "";
        Menu->Icon[i] = NULL;
        Menu->Page[i] = NULL;
        Menu->Child[i] = NULL;
        Menu->Parameter[i] = NULL;
        Menu->ParameterGroup[i] = NULL;
    }

    Menu->MenuClick = NULL;
    Menu->MenuRelease = NULL;
}

/** \brief Speichert MenuPage bei den Children als Parent-MenuPage ein.
 *
 *
 *  \param Menu: Erste MenuPage (oberste MenuPage)
 *  \retval keins
 */
void Firmware_MenuGetParents(struct MenuPage * Menu) {
    int i;
    for (i=0;i<Menu->Count;i++) {
        if(Menu->Child[i]) {
            Menu->Child[i]->Parent = Menu;
            Menu->Child[i]->ParentID = i;
            Firmware_MenuGetParents(Menu->Child[i]);
        } else if (Menu->ParameterGroup[i]){
            //Kein Child definiert, aber eine ParameterGruppe
            //Menu erstellen
            struct MenuPage * Temp;
            Temp = CreateMenufromParameterGroup(Menu->ParameterGroup[i],i, Menu);
            Firmware_MenuGetParents(Temp);
        }
    }
}
