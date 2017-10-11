#include "Firmware_Memory_EasyParameterGroups.h"

void Firmware_EasyCAN_CreateMessageParaGroup(struct ParameterGroup * CanMessageGroup, uint8_t Active, uint8_t ID, uint8_t CycleTime, char * Name, char * Description) {
    struct ParameterGroup * CAN_MsgGroup = malloc(sizeof(struct ParameterGroup));

    struct Parameter * Msg_Active = malloc(sizeof(struct Parameter));
    struct Parameter * Msg_ID = malloc(sizeof(struct Parameter));
    struct Parameter * Msg_CycleTime = malloc(sizeof(struct Parameter));

    ParameterGroup_Init(CAN_MsgGroup, Name, Description, CanMessageGroup);

    //CAN_Msg1-Active
    Parameter_Init(Msg_Active, CAN_MsgGroup);
    Msg_Active->DataType = &DATATYPE_BOOL;
    Msg_Active->EditType = EDITTYPE_TOGGLE;
    ParameterWriteALL(Msg_Active, 0,1,1,1,Active);
    strcpy(Msg_Active->Name, "Active");

    //CAN-ID
    Parameter_Init(Msg_ID, CAN_MsgGroup);
    Msg_ID->DataType = &DATATYPE_UNINT;
    Msg_ID->EditType = EDITTYPE_UPDOWN;
    ParameterWriteALL(Msg_ID, 0,0,0,1,ID);
    strcpy(Msg_ID->Name, "ID");

    //CAN-Zykluszeit
    Parameter_Init(Msg_CycleTime, CAN_MsgGroup);
    Msg_CycleTime->DataType = &DATATYPE_PROZENT;
    Msg_CycleTime->EditType = EDITTYPE_UPDOWN;
    ParameterWriteALL(Msg_CycleTime, 0,0,0,1,CycleTime);
    strcpy(Msg_CycleTime->Name, "Zykluszeit");
}

void Firmware_EasyClickboard_CreateDriverParaGroup(struct ParameterGroup * ClickboardGroup, uint8_t MB, uint8_t Address, char * Name, char * Description) {
    struct ParameterGroup * Clickboard = malloc(sizeof(struct ParameterGroup));

    struct Parameter * Click_MB = malloc(sizeof(struct Parameter));
    struct Parameter * Click_Address = malloc(sizeof(struct Parameter));

    ParameterGroup_Init(Clickboard, Name, Description, ClickboardGroup);

    //CAN_Msg1-Active
    Parameter_Init(Click_MB, Clickboard);
    Click_MB->DataType = &DATATYPE_UNINT;
    Click_MB->EditType = EDITTYPE_UPDOWN;
    ParameterWriteALL(Click_MB, 1,MB,8,1,MB);
    strcpy(Click_MB->Name, "MikrobusSocket");

    //CAN-ID
    Parameter_Init(Click_Address, Clickboard);
    Click_Address->DataType = &DATATYPE_UNINT;
    Click_Address->EditType = EDITTYPE_KEYPAD;
    ParameterWriteALL(Click_Address, 0,Address,255,1,Address);
    strcpy(Click_Address->Name, "Addressbyte");
}

