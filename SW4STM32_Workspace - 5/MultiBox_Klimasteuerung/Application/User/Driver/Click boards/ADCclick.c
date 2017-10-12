/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

 /** \addtogroup ADCclick
 *  @{
 *  The ADC3click can be programmed by SPI and has 4 ADC-Channels. Depending on the Configuration the ADC is working in 12-/14-/16-bit mode and
 *  has a dependent Sample Rate (High Resolution = Slow-Sample-Rate).
 */

#include "ADCclick.h"

#define ADC_ACK                 (0b01100000)
#define ADC_CH0                 (0b00000000)
#define ADC_CH1                 (0b00000100)
#define ADC_CH2                 (0b00001000)
#define ADC_CH3                 (0b00001100)
#define ADC_CH(__channel__)     (__channel__ << 2)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADCclick_SPI_Init() {
    //Call SPI_Init
    SPI_Init(SPI_BAUDRATEPRESCALER_128, SPI_DIRECTION_2LINES,SPI_PHASE_1EDGE, SPI_POLARITY_LOW,SPI_DATASIZE_8BIT,SPI_FIRSTBIT_MSB);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADCclick_Select(struct clickBoard * Board) {
    ADC_Current = Board;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static uint16_t Receive;
uint16_t * ADCclick_get(unsigned short channel) {    // Returns 0..4095
    //SPI Init
    ADCclick_SPI_Init();

    //ChipSelect
    SetCS(ADC_Current->MB,0);

    //Daten vom CHIP holen --> Send ACK --> Send Channel -> Receive Data1 --> Receive Data2
    WriteSPI(ADC_ACK | ADC_CH(channel));

    Receive = WriteReceiveSPI(0x00);//);
    Receive = (Receive << 4) | ((WriteReceiveSPI(0x00) & 0xF0) >> 4);

    //ChipDeSelect
    SetCS(ADC_Current->MB,1);

    //SPI DeInit
    SPI_DeInit();

    return &Receive;
}
