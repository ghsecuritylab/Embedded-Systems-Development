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

#include "RingMemory.h"

extern FIL FileObj;
/** \brief
 *
 *
 *  \param
 *  \retval
 */
void RingMemory_Init(struct RingMemory * Ring, char * Name, uint16_t ElementCount, struct DataType * DataType_, double CycleTime, uint8_t SaveToSD, struct ParameterGroup * Group) {
    struct RingElement * Temp;
    struct RingElement * First;

    Ring->DataType = DataType_;
    Ring->Count = ElementCount;
    strcpy(Ring->Name, Name);

    //Erstellt Erstes Element und reserviert Speicher
    Temp = malloc(sizeof(struct RingElement)); //calloc!

    //Erste Element wird gemerkt und als Element des Ringspeichers verlinkt
    First = Temp;
    Ring->AktValue = First;

    uint16_t i;
    //Schleife die alle weiteren Elemente erzeugt und Previous und Next-Zeiger setz
    for(i=0;i<ElementCount;i++) {
        //Temp                    =   calloc(1,sizeof(struct RingElement));
        //Temp->Previous          =   Ring->AktValue;
        //Ring->AktValue->Next    =   Temp;

        //Ring->AktValue = Temp;

        Ring->AktValue[i] = calloc(1,sizeof(union Data));

        //DataWrite(Ring->DataType->ID, Temp->Value, 0);
    }

    Ring->AktValueIndex = 0;

    //Zeiger setzen f¸r letzte Erstellte Element welches mit First verbunden werden muss
    //Ring->AktValue->Next       =    First;
    //First->Previous            =    Ring->AktValue;


    //Erstellen Parameter f¸r Cycle Time
    struct Parameter * Para_CycleTime = malloc(sizeof(struct Parameter));
    char str[40];
    sprintf(str,"%s - Zykluszeit", Ring->Name);

    Parameter_Init(Para_CycleTime, Group);
    Para_CycleTime->DataType = &DATATYPE_UNINT;
    Para_CycleTime->EditType = EDITTYPE_KEYPAD;
    ParameterWriteALL(Para_CycleTime, 0,0,0,1,CycleTime);
    strcpy(Para_CycleTime->Name, str);

    Ring->CycleTime = Para_CycleTime;

    struct Parameter * Para_SaveToSD = malloc(sizeof(struct Parameter));
    sprintf(str,"%s - SD Speichern", Ring->Name);

    Parameter_Init(Para_SaveToSD, Group);
    Para_SaveToSD->DataType = &DATATYPE_UNINT;
    Para_SaveToSD->EditType = EDITTYPE_TOGGLE;
    ParameterWriteALL(Para_SaveToSD, 0,0,0,1,SaveToSD);
    strcpy(Para_SaveToSD->Name, str);

    Ring->SaveToSD = Para_SaveToSD;

    //Z‰hler wie viele Elemente im Ring schon abgelegt wurden
    Ring->StoredItems = 0;
    Ring->AktFlashIndex = 0;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void RingMemory_Save(struct RingMemory * Ring, union Data * Data) {
    //AktValue ein Element weiterschieben
    Ring->AktValueIndex = (Ring->AktValueIndex >= Ring->Count) ? 0 : Ring->AktValueIndex + 1 ;
    //vorher Next zeug

    //Wert ¸bertragen
    memcpy(&Ring->AktValue[Ring->AktValueIndex], Data, DATASIZE);
    //memcpy(&Ring->AktValue->Value, Data, DATASIZE);

   //Einspeichern des Wert-Strings wenn Export des Wertes auf SD-vorgesehen ist
    if(ParameterRead(Ring->SaveToSD,Value)) {
        char WriteString[10];
        strcpy(WriteString,Ring->DataType->OutStr);
        strncat(WriteString,"\n\0",2);

        //sprintf(Ring->AktValue->ValueString, WriteString, Ring->AktValue->Value);
    }

    //RingElementZ‰hler inkrementieren
    Ring->StoredItems++;

    if(Ring->StoredItems >= Ring->Count) {
        Ring->StoredItems = Ring->Count;

        if(ParameterRead(Ring->SaveToSD,Value)) {
            //Speichere Ring auf SD-Karte
            RingMemory_SavetoSD(Ring,Ring->Count,0);
        }
    }
}

union Data * RingMemory_getValasData(struct RingMemory * Ring, uint16_t PastCount) {
    uint16_t i;
    uint16_t AktIndex = Ring->AktValueIndex;
    //static struct RingElement * TempElement;
    //TempElement = Ring->AktValue;

    for(i=0;i<PastCount; i++) {
        //TempElement = TempElement->Previous;
        AktIndex = (AktIndex == 0) ? Ring->Count - 1 : AktIndex - 1;
    }

    return &Ring->AktValue[AktIndex];
};

/** \brief
 *
 *
 *  \param
 *  \retval
 */
char * RingMemory_getValAsStr(struct RingMemory * Ring, uint8_t PastCount) {
    static char str[20] = "";

    DataWritetoString(Ring->DataType->ID,(*RingMemory_getValasData(Ring,PastCount)),str);

    return str;
}

void RingMemory_SavetoFLASH(struct RingMemory * Ring) {
    if (QSPI_status == QSPI_OK) {
        uint32_t Time = DWT->CYCCNT;

        //RingElement Iterieren
        uint16_t i = 0;
        struct RingElement * TempElement = Ring->AktValue;

        for(i=0;i<Ring->Count;i++) {
            TempElement = TempElement->Previous;
        }

        //FlashAddresse einspeichern
        Ring->FlashAddress[Ring->AktFlashIndex] = *RingMemory_getNewFlashAddres();

        //Erasen vom Flash
        uint8_t Counter;
        while (Counter *  N25Q128A_SUBSECTOR_SIZE < ParameterArray.Count * PARAMETER_FLASH_SIZE) {
            BSP_QSPI_Erase_Block(Ring->FlashAddress[Ring->AktFlashIndex] + Counter * N25Q128A_SUBSECTOR_SIZE);
            Counter++;
        }

        //Strings in Flash schreiben
        uint32_t CurrentAddress = Ring->FlashAddress[Ring->AktFlashIndex];
        do
        {
            //BSP_QSPI_Write(TempElement->ValueString,CurrentAddress,strlen(TempElement->ValueString));
            //CurrentAddress+=strlen(TempElement->ValueString);

            TempElement = TempElement->Next;
            i++;
        } while(i < Ring->Count);

        Ring->FlashCounter[Ring->AktFlashIndex] = LastFlashSize;
        LastFlashSize = CurrentAddress - Ring->FlashAddress[Ring->AktFlashIndex];
        Ring->AktFlashIndex++;

        //Alles in Flash geschrieben
    }
}

static uint32_t Address;
uint32_t * RingMemory_getNewFlashAddres() {

    Address = AktFlashAddress + (uint32_t) (ceil(LastFlashSize / N25Q128A_SUBSECTOR_SIZE));


    return &Address;
}

void RingMemory_SavetoSD(struct RingMemory * Ring, uint8_t Start, uint8_t End) {
    if ((BSP_SD_IsDetected()) & (SD_Mounted == 1)) {
        char * String;
        String = malloc(sizeof(char));

        char WriteString[40] = "";
        char FileName[40] = "";

        strcat(WriteString,Ring->DataType->OutStr);

        strcat(FileName,"0:/");
        strcat(FileName, Ring->Name);
        strcat(FileName,".csv");

        FATFS_t result;

        SD_LOCK = 1;

        result = UB_Fatfs_OpenFile(&FileObj, FileName, F_WR_NEW);
        if (result != FATFS_OK) {
            GUI_Error_Handler("SD-Card Error", "÷ffnen der Datei fehlgeschlagen!");
        }

        SD_LOCK = 0;

        uint16_t i = 0;
        struct RingElement * TempElement = Ring->AktValue;

        for(i=0;i<Start;i++) {
            TempElement = TempElement->Previous;
        }

        i=0;
        char temp[20];

        char WriteString1[42];
        strcpy(WriteString1, WriteString);
        strncat(WriteString1,"\0",2);
        char WriteString2[42];
        strcpy(WriteString2, WriteString);
        strncat(WriteString2,"\0",1);


        do
        {
            //Daten in String schreiben
            sprintf(temp, WriteString1, DataRead(Ring->DataType->ID, (TempElement->Value)));

            UB_Fatfs_WriteString(&FileObj,temp);
            //SD_LOCK = 1;
            //UB_Fatfs_WriteBlock(&FileObj,(char *) &TempElement->Value,sizeof(TempElement->Value),NULL);
            //SD_LOCK = 0;

            /*String = (char *) realloc(String, sizeof(String) + strlen(temp) * sizeof(char));
            strncat(String, temp, strlen(temp));*/

            TempElement = TempElement->Next;
            i++;

        }
        while(i<(Start-End));

        /*sprintf(temp, WriteString2, DataRead(Ring->DataType->ID, (TempElement->Value)));
        UB_Fatfs_WriteBlock(&FileObj,temp,strlen(temp),NULL);*/

        //UB_Fatfs_WriteBlock(&FileObj,String,sizeof(String),NULL);

        SD_LOCK = 1;
        result = UB_Fatfs_CloseFile(&FileObj);// mit IRclick_Init() -> FATFS_CLOSE_ERR (FR_DISK_ERR)
        SD_LOCK = 0;

        if (result != FATFS_OK) {
            GUI_Error_Handler("SD-Card Error",
                    "Schlieﬂen der Datei fehlgeschlagen!");
        }


    }
}
