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

#include "Firmware_Parameter_CONFIG.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_Init_Parameters() {
    ID_Counter = 0;
    ParameterArray.Count = 0;
    //ParameterArray.Para = malloc(sizeof(struct Parameter *));

    /***********************************/
    /*  Erster Parameter wird als Speicher genutzt
        und bestimmt, ob in Parameter-Init die PArameter
        aus dem Flash gelesen werden sollen.
        Seine Definition darf NICHT verändert werden
    */

    Parameter_Init(&PARA_LOAD_FLASH, NULL);
    PARA_LOAD_FLASH.DataType = &DATATYPE_BOOL;
    PARA_LOAD_FLASH.EditType = EDITTYPE_TOGGLE;
    ParameterWriteALL((&PARA_LOAD_FLASH), 0,1,1,1,1);
    strcpy(PARA_LOAD_FLASH.Name, "Parameter aus Speicher laden");

    Parameter_Init(&KONFIGMODE_OUTPUT, NULL);
    KONFIGMODE_OUTPUT.DataType = &DATATYPE_BOOL;
    KONFIGMODE_OUTPUT.EditType = EDITTYPE_TOGGLE;
    ParameterWriteALL((&KONFIGMODE_OUTPUT), 0,1,1,1,0);
    strcpy(KONFIGMODE_OUTPUT.Name, "Ausgänge schreiben im KonfigMode");

    /***********************************/

    //Lookup Tables

    union Data Test2;

    ParameterGroup_Init(&ParameterGroup_CAN, "CAN", "", NULL);
    {
        //CAN-Active
        Parameter_Init(&CAN_ACTIVE, &ParameterGroup_CAN);
        CAN_ACTIVE.DataType = &DATATYPE_BOOL;
        CAN_ACTIVE.EditType = EDITTYPE_TOGGLE;
        ParameterWriteALL((&CAN_ACTIVE), 0,1,1,1,1);
        CAN_ACTIVE.Value.b = 1;
        strcpy(CAN_ACTIVE.Name, "Active");

        //CAN-Speed
        Parameter_Init(&CAN_SPEED, &ParameterGroup_CAN);
        CAN_SPEED.DataType = &DATATYPE_FLOAT;
        CAN_SPEED.EditType = EDITTYPE_KEYPAD_HEX;
        ParameterWriteALL((&CAN_SPEED), -4,14,44.5,0.5,17);
        strcpy(CAN_SPEED.dimension, " m/s");
        strcpy(CAN_SPEED.Name, "Speed");
    }

    ParameterGroup_Init(&ParameterGroup_OneWire, "1Wire Sensoren", "", NULL);
    {
        Parameter_Init(&ONEWIRE_ROM_GEHAEUSE, &ParameterGroup_OneWire);
        ONEWIRE_ROM_GEHAEUSE.EditType = EDITTYPE_ONEWIREROM;
        ONEWIRE_ROM_GEHAEUSE.DataType = &DATATYPE_ROM;
        strcpy(ONEWIRE_ROM_GEHAEUSE.Name, "Temperatur Gehäuse");
    }

    ParameterGroup_Init(&ParameterGroup_ClickBoards, "ClickBoards", "", NULL);

    ParameterGroup_Init(&ParameterGroup_Prozessparameter, "Prozessparameter", "", NULL);

    ParameterGroup_Init(&ParameterGroup_Zustandsgroessen, "Zustandsgrößen", "", NULL);
}
