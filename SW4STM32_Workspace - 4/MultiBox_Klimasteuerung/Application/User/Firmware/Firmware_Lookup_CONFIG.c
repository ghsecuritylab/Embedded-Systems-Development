/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Memory
 *  @{
 */

/** \addtogroup Data
 *  @{
 */

#include "Firmware_Lookup_CONFIG.h"
/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_Init_LookUps() {
    Lookup_Init(&Lookup_Toggle,2,&DATATYPE_BOOL);
    Lookup_Write((&Lookup_Toggle),0,"AUS", 0);
    Lookup_Write((&Lookup_Toggle),1,"AN", 1);
}
