/** \file
 *  \brief
 *
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Pages
 *  @{
 */

#include "Project_Pages_CONFIG.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Project_Init_Pages() {
    Page_Active = &MainPage_1;

    MainPage_1.Create = &CreateMain1;
    MainPage_1.Update = &UpdateMain1;
    strcpy(MainPage_1.Name, "Klima-\nregelung");
    MainPageArray[0] = &MainPage_1;

    MainPage_2.Create = &CreateMain2;
    MainPage_2.Update = &UpdateMain2;
    strcpy(MainPage_2.Name, "Temperatur-\nverlauf");
    MainPageArray[1] = &MainPage_2;

    MainPage_3.Create = &Create_TimerEventsPage;
	MainPage_3.Update = &Update_TimerEventsPage;
	strcpy(MainPage_3.Name, "Zeit-\nschaltung");
	MainPageArray[2] = &MainPage_3;

    HardwarePage.Create = &CreateHardwarePage;
    HardwarePage.Update = &UpdateHardwarePage;
    strcpy(HardwarePage.Name, "Hardware");

    RTC_Page.Create = &Create_RTC_Page;
    RTC_Page.Update = &Update_RTC_Page;
    strcpy(RTC_Page.Name, "RTC");

//    Page_Active = &MainPage_1;
//
//    MainPage_1.Create = &CreateMain;
//    MainPage_1.Update = &UpdateMain;
//    strcpy(MainPage_1.Name, "Main1");
//    MainPageArray[0] = &MainPage_1;
//
//    MainPage_2.Create = &CreateMain2;
//    MainPage_2.Update = &UpdateMain2;
//    strcpy(MainPage_2.Name, "Main2");
//    MainPageArray[1] = &MainPage_2;
}
