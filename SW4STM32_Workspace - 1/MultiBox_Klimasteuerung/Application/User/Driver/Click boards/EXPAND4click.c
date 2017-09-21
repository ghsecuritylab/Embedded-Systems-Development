/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

/** \addtogroup EXPAND4click
 *  \brief PWMclick Driver
 *
 *  @{
 *  The Expand4clickboard has 8 individual channels. The Chip is programmed by SPI using an internal Shift-Register.
 */

#include "EXPAND4click.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPAND4click_SPI_Init() {
    //Call SPI_Init
    SPI_Init(SPI_BAUDRATEPRESCALER_64, SPI_DIRECTION_1LINE,SPI_PHASE_1EDGE, SPI_POLARITY_LOW,SPI_DATASIZE_8BIT,SPI_FIRSTBIT_MSB);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPAND4click_Select(struct clickBoard * Board) {
    EXPAND4_Current = Board;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPAND4click_set(uint8_t Ports) {    // Returns 0..4095
    //SPI Init
    EXPAND4click_SPI_Init();

    //Alles Aus
    SetPWM(EXPAND4_Current->MB,1);
    SetPWM(EXPAND4_Current->MB,0);

    //CLR Input Shift
    SetRST(EXPAND4_Current->MB,0);
    SetRST(EXPAND4_Current->MB,1);

    //Daten vom CHIP holen --> Send ACK --> Send Channel -> Receive Data1 --> Receive Data2
    WriteSPI(Ports);

    //Übernehmen
    SetCS(EXPAND4_Current->MB,0);
    SetCS(EXPAND4_Current->MB,1);

    //SPI DeInit
    SPI_DeInit();
}
