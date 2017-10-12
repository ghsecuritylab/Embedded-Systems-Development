/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

/** \addtogroup ADC3click
 *  @{
 */

#include "ADC3click.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADC3click_I2C_Init() {
    //Call I2C_Init
    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);


}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADC3click_WriteConfig(uint8_t Channel, uint8_t ConversionMode, uint8_t SampleRate, uint8_t PGAGain) {
    uint8_t temp;

    ADC3click_I2C_Init();

    //Daten vom CHIP holen --> Send ACK --> Send Channel -> Receive Data1 --> Receive Data2
    temp = Channel | ConversionMode | SampleRate | PGAGain;
    WriteI2C_1B(ADC3_ACK | ADC3_WRITE,temp);

    //SPI DeInit
    I2C_DeInit();
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADC3click_ChangeChannel(short Channel) {
    uint8_t Config_Mode;

    ADC3click_I2C_Init();

    //Daten vom CHIP holen --> Send ACK --> Send Channel -> Receive Data1 --> Receive Data2
    Config_Mode = ReceiveI2C(ADC3_ACK | ADC3_WRITE,3)[2];
    Config_Mode= (Config_Mode & 0b10011111) | (Channel << 5) ;
    WriteI2C_1B(ADC3_ACK | ADC3_WRITE,Config_Mode);

    //SPI DeInit
    I2C_DeInit();
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void ADC3click_Select(struct clickBoard * Board, uint8_t Addr) {
    ADC3_Current = Board;

    ADC3_Current->Address = Addr;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t * ADC3click_get(unsigned short channel) {    // Returns 0..4095
    //ADC3click_WriteConfig(0b10000000 | (channel <<5));

    uint8_t * Receive;

    ADC3click_ChangeChannel(channel);

    //I2C Init
    ADC3click_I2C_Init();

    //Daten vom CHIP holen --> Send ACK --> Send Channel -> Receive Data1 --> Receive Data2
    Receive = ReceiveI2C(ADC3_ACK| ADC3_READ,2);


    //SPI DeInit
    I2C_DeInit();

    return Receive;
}
