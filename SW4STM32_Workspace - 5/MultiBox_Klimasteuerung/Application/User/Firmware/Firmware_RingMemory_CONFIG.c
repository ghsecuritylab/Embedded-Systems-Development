/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Memory
 *  @{
 */

/** \addtogroup RingMemory
 *  @{
 */

#include "Firmware_RingMemory_CONFIG.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_Init_RingMemories() {
    ParameterGroup_Init(&ParameterGroup_RingMemory, "RingSpeicher", "", NULL);

    //Ringspeicher
    RingMemory_Init(&TemperaturGehaeuse, "TempGehaeuse", 100, (&DATATYPE_FLOAT),10.0, 0, &ParameterGroup_RingMemory);
}
