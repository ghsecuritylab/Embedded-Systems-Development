/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

/** \addtogroup DAC2click
 *  @{
 *  The DAC2-clickboard can be programmed by SPI and the 12-bit output Voltage can be set from 0 V to VCC / 4.096V (selected by SMD-Jumper on the clickboard).
 */

#include "DAC2click.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void DAC2click_SPI_Init() {
    //Call SPI_Init
    SPI_Init(SPI_BAUDRATEPRESCALER_64, SPI_DIRECTION_1LINE,SPI_PHASE_1EDGE, SPI_POLARITY_LOW,SPI_DATASIZE_8BIT,SPI_FIRSTBIT_MSB);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void DAC2click_Select(struct clickBoard * Board) {
    DAC2_Current = Board;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void DAC2click_set(unsigned short channel, uint16_t Value) {    // Set 0..4095
    uint8_t Val1 = Value >> 8;
    uint8_t Val2 = Value;

    //SPI Init
    DAC2click_SPI_Init();

    //ChipSelect
    SetCS(DAC2_Current->MB,0);

    //Daten auf Chip schreiben --> Send ACK --> Send Value-Teil 1 --> Send Value-Teil 2
    WriteSPI(DAC2_ACK);

    WriteSPI(Val1);
    WriteSPI(Val2);

    //ChipDeSelect
    SetCS(DAC2_Current->MB,1);

    //SPI DeInit
    SPI_DeInit();
}
