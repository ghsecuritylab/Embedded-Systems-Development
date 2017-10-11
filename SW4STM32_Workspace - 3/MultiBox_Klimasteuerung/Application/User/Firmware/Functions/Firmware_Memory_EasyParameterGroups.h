#pragma once

#include "MemoryStructures.h"

void Firmware_EasyCAN_CreateMessageParaGroup(struct ParameterGroup * CanMessageGroup, uint8_t Active, uint8_t ID, uint8_t CycleTime, char * Name, char * Description);
void Firmware_EasyClickboard_CreateDriverParaGroup(struct ParameterGroup * ClickboardGroup, uint8_t MB, uint8_t Address, char * Name, char * Description);
