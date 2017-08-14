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

#include "Project_RingMemory_CONFIG.h"
#include "graphSettings.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */



void Project_Init_RingMemories() {
    //Ringspeicher
	RingMemory_Init(&Sollwert, "Sollwert", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturRaum, "Raumtemperatur", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL); // &ParameterGroup_RingMemory
    RingMemory_Init(&TemperaturOutside, "Aussentemepratur", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturAir1, "Temp. Luftstrom 1", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturUnit1, "Temp. Unit 1", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturAir2, "Temp. Luftstrom 2", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturUnit2, "Temp. Unit 2", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturMotor, "Motortemperatur", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
    RingMemory_Init(&TemperaturCAN, "Temperatur CAN", GRAPH_SIZE_T, (&DATATYPE_UNINT), 10.0, 0, NULL);
}
