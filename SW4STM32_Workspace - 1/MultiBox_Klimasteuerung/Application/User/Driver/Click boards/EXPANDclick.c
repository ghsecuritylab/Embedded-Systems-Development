/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

/** \addtogroup EXPANDclick
 *  @{
 */

#include "EXPANDclick.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_ConfigureChip() {
    //Chip zurücksetzen
    EXPANDclick_Reset();

    //Port A Eingänge
    EXPANDclick_Send(EXPAND_REG_IODIRA, 0xFF);

    //Port B Ausgänge
    EXPANDclick_Send(EXPAND_REG_IODIRB, 0x00);

    //Port B Ausgänge setzen
    EXPANDclick_Send(EXPAND_REG_GPIOB, 0xFF);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_Reset() {
    //Reset Chip
    SetRST(EXPAND_Current->MB,1);
    //HAL_Delay(10);
    SetRST(EXPAND_Current->MB,0);
    //HAL_Delay(10);
    SetRST(EXPAND_Current->MB,1);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_Send(uint8_t Register, uint8_t Data) {

    EXPANDclick_SPI_Init();

    EXPANDclick_ChipSelect();

    WriteSPI(EXPAND_ACK_W | EXPAND_Current->Address);
    WriteSPI(Register);
    WriteSPI(Data);

    EXPANDclick_ChipDeSelect();

    SPI_DeInit();

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t EXPANDclick_Receive(uint8_t Register) {
    uint8_t Receive;

    EXPANDclick_SPI_Init();

    EXPANDclick_ChipSelect();

    WriteSPI(EXPAND_ACK_R | EXPAND_Current->Address);
    WriteSPI(Register);
    Receive = WriteReceiveSPI(0x00);

    SPI_DeInit();

    EXPANDclick_ChipDeSelect();

    return Receive;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_ChipSelect() {
    SetCS(EXPAND_Current->MB,0);
    SetCS(EXPAND_Current->MB,1);
    SetCS(EXPAND_Current->MB,0);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_ChipDeSelect() {
    SetCS(EXPAND_Current->MB,1);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_Select(struct clickBoard * Board) {
    EXPAND_Current = Board;
    if (Board->Address == 0) {
        Board->Address = EXPAND_ADDR_DEF;
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void EXPANDclick_SPI_Init() {
    //Call SPI_Init
    SPI_Init(SPI_BAUDRATEPRESCALER_4, SPI_DIRECTION_2LINES,SPI_PHASE_1EDGE, SPI_POLARITY_LOW,SPI_DATASIZE_8BIT,SPI_FIRSTBIT_MSB);
}

 /** @} */
