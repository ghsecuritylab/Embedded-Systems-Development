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

#include "Firmware_Pages_CONFIG.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_Init_Pages() {
    HardwarePage.Create = &CreateHardwarePage;
    HardwarePage.Update = &UpdateHardwarePage;
    strcpy(HardwarePage.Name, "Hardware");

    RTC_Page.Create = &Create_RTC_Page;
    RTC_Page.Update = &Update_RTC_Page;
    strcpy(RTC_Page.Name, "RTC");
}
