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


#include "Parameter.h"
/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_ParamFlash() {

  //QSPI_status = BSP_QSPI_Init(); //moved into main
  if (QSPI_status == QSPI_OK) {
        //Lese ersten Parameter aus Flash
        Parameter_ReadFromFlash(&PARA_LOAD_FLASH);

        //Prüfe Wert des ersten Parameters und ob UserButton nicht gedrückt ist
        if((ParameterRead((&PARA_LOAD_FLASH), Value) == 1) & (BSP_PB_GetState(BUTTON_KEY) != GPIO_PIN_SET)) {
            //Lese aus Flash
            Parameter_ReadALLFromFlash();
        } else {
            //System solltezurückgesetzt werden, lese nicht aus Flash
            //Setze PARA_LOAD_FLASH auf 1
            ParameterWrite((&PARA_LOAD_FLASH), Value, 1);

            ParameterChange_Handled = 0;
        }
  }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_SaveALLInFlash() {
    uint32_t i;

    uint32_t Counter = 0;
    while (Counter *  N25Q128A_SUBSECTOR_SIZE < ParameterArray.Count * PARAMETER_FLASH_SIZE) {
        BSP_QSPI_Erase_Block(PARAMETER_FLASH_STARTADDRESS + Counter * N25Q128A_SUBSECTOR_SIZE);
        Counter++;
    }

    for(i=0;i<ParameterArray.Count;i++) {
        Parameter_SaveInFlash(ParameterArray.Para[i]);
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_ReadALLFromFlash() {
    uint8_t i;

    for(i=0;i<ParameterArray.Count;i++) {
        Parameter_ReadFromFlash(ParameterArray.Para[i]);
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_SaveInFlash(struct Parameter * Para) {
    uint32_t Address;
    Address = PARAMETER_FLASH_STARTADDRESS + Para->ID * PARAMETER_FLASH_SIZE;

    //Erase Block
    //if (BSP_QSPI_Erase_Block(Address) == QSPI_OK) {};

    uint8_t temp[PARAMETER_FLASH_SIZE+1];
    memcpy(temp,&Para->ID,          1);
    memcpy(temp+1+0*DATASIZE,&Para->Min,       DATASIZE);
    memcpy(temp+1+1*DATASIZE,&Para->Max,      DATASIZE);
    memcpy(temp+1+2*DATASIZE,&Para->Step,     DATASIZE);
    memcpy(temp+1+3*DATASIZE,&Para->Default,  DATASIZE);
    memcpy(temp+1+4*DATASIZE,&Para->Value,    DATASIZE);

    BSP_QSPI_Write(temp,Address,PARAMETER_FLASH_SIZE);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_ReadFromFlash(struct Parameter * Para) {
    uint32_t Address;
    Address = PARAMETER_FLASH_STARTADDRESS + Para->ID * PARAMETER_FLASH_SIZE;

    uint8_t temp5 = DATASIZE;

    uint8_t temp[PARAMETER_FLASH_SIZE+1];

    BSP_QSPI_Read(temp,Address,PARAMETER_FLASH_SIZE);

    //The Variable was saved before, detected by FirstByte = ID
    if(Para->ID == temp[0]) {
        memcpy(&Para->ID,       temp,       1);
        memcpy(&Para->Min,      temp+1+0*DATASIZE,    DATASIZE);
        memcpy(&Para->Max,      temp+1+1*DATASIZE,    DATASIZE);
        memcpy(&Para->Step,     temp+1+2*DATASIZE,    DATASIZE);
        memcpy(&Para->Default,  temp+1+3*DATASIZE,    DATASIZE);
        memcpy(&Para->Value,    temp+1+4*DATASIZE,    DATASIZE);

        if (Para->DataType->ID == DATATYPE_ROM.ID) {
            memcpy(Para->Value.ROM,    temp+1+4*DATASIZE,    DATASIZE);
        }
    }
};

/** \brief
 *
 *
 *  \param
 *  \retval
 */
char * Parameter_getValAsStr(struct Parameter * Para) {
    static char str[20] = "";

    if (Para->DataType->ID == DATATYPE_ROM.ID) {
        DataWritetoString(Para->DataType->ID,Para->Value,str);
        //sprintf(str,"%02X%02X:%02X%02X:%02X%02X:%02X%02X",Para->Value.ROM[0],Para->Value.ROM[1],Para->Value.ROM[2],Para->Value.ROM[3],Para->Value.ROM[4],Para->Value.ROM[5],Para->Value.ROM[6],Para->Value.ROM[7]);
    } else {
        if (Para->Lookup == NULL) {
            //Keine Lookup zugeordnet, Wert zurückgeben
            /*if (Para->DataType->ID == DATATYPE_FLOAT.ID) {
                sprintf(str, Para->DataType->OutStr, ParameterRead(Para,Value));
            } else {
                sprintf(str, Para->DataType->OutStr, Para->Value);
            }*/
            DataWritetoString(Para->DataType->ID,Para->Value,str);
        } else {
            //Lookup zugeordnet, Spezifischen Text zurückgeben
            uint8_t i = Lookup_getValueID(Para->Lookup, &Para->Value);
            sprintf(str, "%s", Para->Lookup->Elements[i-1]->Name);
        }
    }

    return str;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
char * Parameter_getDefValAsStr(struct Parameter * Para) {
    static char str[100];
    char str2[100];

    strcpy(str,"");
    strcpy(str2,"");

    if (Para->DataType->ID != DATATYPE_ROM.ID) {
        strcat(str,"Min = ");
        DataWritetoString(Para->DataType->ID,Para->Min,str2);
        strcat(str,str2);

        strcat(str,"\nDef = ");
        DataWritetoString(Para->DataType->ID,Para->Default,str2);
        strcat(str,str2);

        strcat(str,"\nMax = ");
        DataWritetoString(Para->DataType->ID,Para->Max,str2);
        strcat(str,str2);

    //if (Para->Min.b != NULL) {
        /*
        sprintf(str2, "Min = %s\n", Para->DataType->OutStr);
        if (Para->DataType->ID == DATATYPE_FLOAT.ID) {
            DataWritetoString(Para->DataType->ID,Para->Value,str);
            sprintf(str, str2, ParameterRead(Para,Min));
        } else {
            sprintf(str,str2, Para->Min);
        }
    //}

    //if (Para->Default.b != NULL) {
        sprintf(str2, "%sDef = %s\n", str, Para->DataType->OutStr);
        if (Para->DataType->ID == DATATYPE_FLOAT.ID) {
            sprintf(str, str2, ParameterRead(Para,Default));
        } else {
            sprintf(str, str2, Para->Default);
        }
    //}

    //if (Para->Max.b != NULL) {
        sprintf(str2, "%sMax = %s", str, Para->DataType->OutStr);
        if (Para->DataType->ID == DATATYPE_FLOAT.ID) {
            sprintf(str, str2, ParameterRead(Para,Max));
        } else {
            sprintf(str, str2, Para->Max);;
        }
    //}*/
    }

    return str;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_Init(struct Parameter * Para, struct ParameterGroup * Group) {
    Para->DataType = &DATATYPE_BOOL;
    Para->ID = ID_Counter;
    ID_Counter++;

    ParameterWrite(Para, Default, 0);
    ParameterWrite(Para, Max, 0);
    ParameterWrite(Para, Min, 0);
    ParameterWrite(Para, Step, 1);
    ParameterWrite(Para, Value, 0);

    strcpy(Para->dimension, "");
    strcpy(Para->Name, "");
    strcpy(Para->Description, "");

    Para->EditType = EDITTYPE_NOEDIT;
    Para->Changed = 0;
    Para->Lookup = NULL;

    //Add Parameter to Group, if defined
    if (Group != NULL) {
            Para->Group = Group;

            Para->Group->Para[Para->Group->Count] = Para;
            Para->Group->ChildGroups[Para->Group->Count] = NULL;

            Para->Group->Count++;
    } else {
        Para->Group = NULL;
    }


    //Add Parameter to ParameterArray;
    ParameterArray.Count = ParameterArray.Count + 1;
    //ParameterArray.Para = realloc((ParameterArray.Para),sizeof(Para)*(ParameterArray.Count + 1));
    ParameterArray.Para[ParameterArray.Count-1] = Para;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ParameterGroup_Init(struct ParameterGroup * Group, char * Name, char * Description, struct ParameterGroup * ParentGroup) {
    Group->Count = 0;
    strcpy(Group->Name, Name);
    strcpy(Group->Description, Description);

    if (ParentGroup != NULL) {
            Group->ParentGroup = ParentGroup;

            ParentGroup->Para[ParentGroup->Count] = NULL;
            ParentGroup->ChildGroups[ParentGroup->Count] = Group;
            ParentGroup->Count++;
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Parameter_InitOneWire(struct Parameter * Para) {
    Parameter_Init(Para, NULL);

    //Add Parameter to OneWireParameterArray;
    OneWire_Devices_ParameterArray.Count++;
    OneWire_Devices_ParameterArray.Para[OneWire_Devices_ParameterArray.Count-1] = Para;
}

/*void Parameter_WriteALL(struct Parameter * Para, union Data MinVal, union Data DefVal, union Data MaxVal, union Data StepVal, union Data ValVal) {
    Para->isUsed = 0;

    /*if (DataRead(Para->DataType->ID, MinVal) != NOTUSED) {
        Para->isUsed |= 1 << PARA_DATA_BIT_MIN;
    }
    //ParameterWrite(Para, Min, MinVal);

    DataWrite(Para->DataType->ID, Para->Min, MinVal);
    DataWrite(Para->DataType->ID, Para->Max, MaxVal);
    DataWrite(Para->DataType->ID, Para->Default, DefVal);
    DataWrite(Para->DataType->ID, Para->Step, StepVal);
    DataWrite(Para->DataType->ID, Para->Value, ValVal);



    /*if (DataRead(Para->DataType->ID,MaxVal) != NOTUSED) {
        Para->isUsed |= 1 << PARA_DATA_BIT_MAX;
    }
    DataWrite(Para->DataType->ID, Para->Max, MaxVal);


    /*if (DataRead(Para->DataType->ID,DefVal) != NOTUSED) {
        Para->isUsed |= 1 << PARA_DATA_BIT_DEF;
    }
    DataWrite(Para->DataType->ID, Para->Default, DefVal);


    /*if (DataRead(Para->DataType->ID,StepVal) != NOTUSED) {
        Para->isUsed |= 1 << PARA_DATA_BIT_STEP;
    }
    DataWrite(Para->DataType->ID, Para->Step, StepVal);


    /*if (DataRead(Para->DataType->ID,ValVal) != NOTUSED) {
        Para->isUsed |= 1 << PARA_DATA_BIT_VAL;
    }
    DataWrite(Para->DataType->ID, Para->Value, ValVal);
}*/
