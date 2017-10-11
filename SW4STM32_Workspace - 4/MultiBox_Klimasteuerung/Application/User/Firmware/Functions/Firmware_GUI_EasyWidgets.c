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

#include "Firmware_GUI_EasyWidgets.h"


/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_EasyText_SetParameter(WM_HWIN * hWin, uint32_t ID_TEXT, struct Parameter * Para, uint8_t Append, uint8_t IncludeName, uint8_t IncludeDimension) {
    char buffer[255] = "";
    WM_HWIN hText;

    hText = WM_GetDialogItem(*hWin, ID_TEXT);

    //Write Text of Textfield in buffer
    if (Append) {
        TEXT_GetText(hText, buffer, 255);
        strcat(buffer, "\n");
    }

    //Write ParameterName in buffer
    if (IncludeName) {
        strcat(buffer, Para->Name);
        strcat(buffer, " = ");
    }

    //Write Value in buffer
    strcat(buffer,Parameter_getValAsStr(Para));

    //Write Dimension in buffer
    if (IncludeDimension) {
        strcat(buffer, " ");
        strcat(buffer, Para->dimension);
    }

    //Write buffer to Textfield
    TEXT_SetText(hText, buffer);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Firmware_EasyText_SetRingMemory(WM_HWIN * hWin, uint32_t ID_TEXT, struct RingMemory * Ring, uint8_t PastCount, uint8_t Append, uint8_t IncludeName, uint8_t IncludeDimension) {
    char buffer[255] = "";
    WM_HWIN hText;

    hText = WM_GetDialogItem(*hWin, ID_TEXT);

    //Write Text of Textfield in buffer
    if (Append) {
        TEXT_GetText(hText, buffer, 255);
        strcat(buffer, "\n");
    }

    //Write ParameterName in buffer
    if (IncludeName) {
        strcat(buffer, Ring->Name);
        strcat(buffer, " = ");
    }

    //Write Value in buffer
    strcat(buffer,RingMemory_getValAsStr(Ring,PastCount));

    //Write Dimension in buffer
    if (IncludeDimension) {
        strcat(buffer, " ");
        //strcat(buffer, Ring->dimension);
    }

    //Write buffer to Textfield
    TEXT_SetText(hText, buffer);
}
