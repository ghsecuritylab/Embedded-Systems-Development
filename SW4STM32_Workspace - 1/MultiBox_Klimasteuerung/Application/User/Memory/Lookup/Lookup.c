/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Memory
 *  @{
 */

/** \addtogroup Parameter
 *  @{
 */

#include "Lookup.h"
/** \brief
 *
 *
 *  \param
 *  \retval
 */
 void Lookup_Init(struct Lookup * Lookup, uint8_t Count, struct DataType * DataType) {
    Lookup->Count = Count;
    Lookup->DataType = DataType;

    uint8_t i;
    struct LookupElement * Temp;
    for(i=0;i<Count; i++) {
        Temp = malloc(sizeof(struct LookupElement));
        Lookup->Elements[i] = Temp;
    }
 }

 uint8_t Lookup_getValueID(struct Lookup * Lookup, union Data * Value) {
    uint8_t i;

    union Data Data1;
    DataWrite(Lookup->DataType->ID, Data1, DataRead(Lookup->DataType->ID,(*Value)));
    union Data Data2;
    DataWrite(Lookup->DataType->ID, Data2, Lookup_ReadVal(Lookup, 0));

    i=1;
    while((DataRead(Lookup->DataType->ID, Data1) != DataRead(Lookup->DataType->ID, Data2))  & (i <= (Lookup->Count))) {
        DataWrite(Lookup->DataType->ID,Data2, Lookup_ReadVal(Lookup, i));
        i++;
    }

    //gibt ArrayIndex +1 zurück bei Fund des Values, ansonsten 0 bei keinem Fund
    return (i <= (Lookup->Count)) ? i : 0;
 }



