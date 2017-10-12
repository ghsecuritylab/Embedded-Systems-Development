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

 #include "GUI.h"
 #include "WM.h"
 #include "MemoryStructures.h"

#pragma once

void Firmware_EasyText_SetParameter(WM_HWIN * hWin, uint32_t ID_TEXT, struct Parameter * Para, uint8_t Append, uint8_t IncludeName, uint8_t IncludeDimension);
void Firmware_EasyText_SetRingMemory(WM_HWIN * hWin, uint32_t ID_TEXT, struct RingMemory * Ring, uint8_t PastCount, uint8_t Append, uint8_t IncludeName, uint8_t IncludeDimension);
