/** \file SPIclick_conf.c
 *  \brief Source File providing functions for using the SPI-Interface.
 *  Each Mikrobussocket is connected to the SPI-Pins of the ARDUINO UNO Connector. The Clickboard drivers are using the functions for the Initialization
 *  of the SPI-Interface, and the SPI writing and receiving.
 */

/** \addtogroup Communication
 *  @{
 */

/** \addtogroup SPI
 *  \brief Provides SPI_Communication Functions.
 *
 *  @{
 *  This library is used for all SPI-Communication between the Microcontrollerboards and the Mikrobussockets.
 */

#include "SPI-Driver.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SPI_Init(uint32_t BaudRatePrescaler, uint32_t Direction, uint32_t CLKPhase, uint32_t CLKPolarity, uint32_t DataSize, uint32_t FirstBit) {
  SpiHandle.Instance               = SPIx;
  SpiHandle.Init.BaudRatePrescaler = BaudRatePrescaler;//SPI_BAUDRATEPRESCALER_128;
  SpiHandle.Init.Direction         = Direction;//SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = CLKPhase;//SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = CLKPolarity;//SPI_POLARITY_LOW;
  SpiHandle.Init.DataSize          = DataSize;//SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = FirstBit;//SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
  SpiHandle.Init.Mode              = SPI_MODE_MASTER;

  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    while(1)
    {
    }
  }

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SPI_DeInit()
{
    HAL_SPI_DeInit(&SpiHandle);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
GPIO_InitTypeDef  GPIO_InitStruct;

  if (hspi->Instance == SPIx)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    SPIx_SCK_GPIO_CLK_ENABLE();
    SPIx_MISO_GPIO_CLK_ENABLE();
    SPIx_MOSI_GPIO_CLK_ENABLE();
    /* Enable SPI2 clock */
    SPIx_CLK_ENABLE();
    /* Enable DMA clock */
    //DMAx_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = SPIx_SCK_AF;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MISO GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MISO_PIN;
    GPIO_InitStruct.Alternate = SPIx_MISO_AF;
    HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPIx_MOSI_AF;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

    /*##-5- Configure the NVIC for SPI #########################################*/
    /* NVIC for SPI */
    HAL_NVIC_SetPriority(SPIx_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(SPIx_IRQn);
  }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  if(hspi->Instance == SPIx)
  {
    /*##-1- Reset peripherals ##################################################*/
    SPIx_FORCE_RESET();
    SPIx_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Deconfigure SPI SCK */
    HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    /* Deconfigure SPI MISO */
    HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
    /* Deconfigure SPI MOSI */
    HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);

    /*##-4- Disable the NVIC for DMA ###########################################*/
    HAL_NVIC_DisableIRQ(SPIx_DMA_TX_IRQn);
    HAL_NVIC_DisableIRQ(SPIx_DMA_RX_IRQn);
  }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void WriteSPI(uint8_t Message)
{
    HAL_SPI_Transmit(&SpiHandle,&Message, 1,10);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t WriteReceiveSPI(uint8_t Message)
{
    uint8_t Answer;

    HAL_SPI_TransmitReceive(&SpiHandle,&Message,&Answer,1,10);

    return Answer;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t ReceiveSPI(uint8_t Message)
{
    uint8_t Answer;

    HAL_SPI_Receive(&SpiHandle,&Answer,1,10);

    return Answer;
}
