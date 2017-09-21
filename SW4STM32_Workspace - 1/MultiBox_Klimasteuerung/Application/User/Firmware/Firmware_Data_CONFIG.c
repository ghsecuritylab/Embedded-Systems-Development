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

#include "Firmware_Data_CONFIG.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_Init_DataTypes() {
    DATATYPE_BOOL.Count = DATATYPE_ID_BOOL;
    DATATYPE_BOOL.ID = 0;
    strcpy(DATATYPE_BOOL.InStr,"%u");
    strcpy(DATATYPE_BOOL.OutStr , "%u");
    DATATYPE_BOOL.ICON = &bmDataType_IO;

    DATATYPE_FLOAT.Count = 10;
    DATATYPE_FLOAT.ID = DATATYPE_ID_FLOAT;
    strcpy(DATATYPE_FLOAT.InStr, "%f");
    strcpy(DATATYPE_FLOAT.OutStr, "%f");
    DATATYPE_FLOAT.ICON = &bmFliekomma;

    DATATYPE_PROZENT.Count = 3;
    DATATYPE_PROZENT.ID = DATATYPE_ID_PROZENT;
    strcpy(DATATYPE_PROZENT.InStr , "%u");
    strcpy(DATATYPE_PROZENT.OutStr , "%u");
    DATATYPE_PROZENT.ICON = &bmDataType_P;

    DATATYPE_HEX.Count = 2;
    DATATYPE_HEX.ID = DATATYPE_ID_HEX;
    strcpy(DATATYPE_HEX.InStr , "%X");
    strcpy(DATATYPE_HEX.OutStr , "%X");
    DATATYPE_HEX.ICON = &bmDataType_P;

    DATATYPE_UNINT.Count = 2;
    DATATYPE_UNINT.ID = DATATYPE_ID_UNINT;
    strcpy(DATATYPE_UNINT.InStr , "%" PRIu16);
    strcpy(DATATYPE_UNINT.OutStr , "%" PRIu16);
    DATATYPE_UNINT.ICON = &bmDataType_P;

    DATATYPE_ROM.Count = 8;
    DATATYPE_ROM.ID = DATATYPE_ID_ROM;
    strcpy(DATATYPE_ROM.InStr , "%2X%2X:%2X%2X:%2X%2X:%2X%2X");
    strcpy(DATATYPE_ROM.OutStr , "%2X%2X:%2X%2X:%2X%2X:%2X%2X");
    DATATYPE_ROM.ICON = &bmDataType_Int;
}

uint8_t Firmware_DataError(uint8_t ID) {
    char str[20];
    sprintf(str, "%u", ID);

}
