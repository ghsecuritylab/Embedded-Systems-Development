

/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

 /** \addtogroup Templateclick
 *  @{
 *
 */

#include "Template_click.h"

/** \brief Bei SPI Kommunikation nutzen dieser Init - Funktion mit entsprechender Parameteranpassung, löschen der I2C-Funktion
 *
 *
 *  \param
 *  \retval
 */
void Templateclick_SPI_Init() {
    //Call SPI_Init
    SPI_Init(SPI_BAUDRATEPRESCALER_128, SPI_DIRECTION_2LINES,SPI_PHASE_1EDGE, SPI_POLARITY_LOW,SPI_DATASIZE_8BIT,SPI_FIRSTBIT_MSB);
}

/** \brief Bei I2C Kommunikation nutzen dieser Init - Funktion mit entsprechender Parameteranpassung, löschen der SPI-Funktion
 *
 *
 *  \param
 *  \retval
 */
void Templateclick_I2C_Init() {
    //Call I2C_Init
    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Templateclick_Select(struct clickBoard * Board, uint8_t Addr) {
    Template_Current = Board;

    //Je nach Kommunikationsart entsprechendes löschen der anderen Zeile
    Template_Current->Address = Addr;
    Template_Current->Address = Addr;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static uint8_t Receive;
uint8_t * Templateclick_get(unsigned short channel) {


    //Kommunikations-Init
    Templateclick_SPI_Init();
    Templateclick_I2C_Init();

    //ChipSelect
    SetCS(Template_Current->MB,0);

    //Write Read Funktionen

    //ChipDeSelect
    SetCS(Template_Current->MB,1);

    //SPI DeInit
    SPI_DeInit();
    I2C_DeInit();

    return &Receive;
}

void Templateclick_set(unsigned short channel, uint8_t Val) {
    //Kommunikations-Init
    Templateclick_SPI_Init();
    Templateclick_I2C_Init();

    //ChipSelect
    SetCS(Template_Current->MB,0);

    //Write Funktionen


    //ChipDeSelect
    SetCS(Template_Current->MB,1);

    //SPI DeInit
    SPI_DeInit();
    I2C_DeInit();
}
