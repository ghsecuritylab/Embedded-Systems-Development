/** \file SPIclick_conf.c
 *  \brief Source File providing functions for using the SPI-Interface.
 *  Each Mikrobussocket is connected to the SPI-Pins of the ARDUINO UNO Connector. The Clickboard drivers are using the functions for the Initialization
 *  of the SPI-Interface, and the SPI writing and receiving.
 */

/** \addtogroup Communication-Driver
 *  @{
 */

/** \addtogroup SPI
 *  @{
 */


#pragma once

#include "stm32746g_discovery.h"
#include "stm32f7xx_hal_spi.h"
#include "stm32f7xx_hal.h"

#define SPIx                             SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOI_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_1
#define SPIx_SCK_GPIO_PORT               GPIOI
#define SPIx_SCK_AF                      GPIO_AF5_SPI2
#define SPIx_MISO_PIN                    GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                    GPIO_PIN_15
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_AF                     GPIO_AF5_SPI2

/* Definition for SPIx's DMA */
#define SPIx_TX_DMA_STREAM               DMA1_Stream4
#define SPIx_RX_DMA_STREAM               DMA1_Stream3
#define SPIx_TX_DMA_CHANNEL              DMA_CHANNEL_0
#define SPIx_RX_DMA_CHANNEL              DMA_CHANNEL_0


/* Definition for SPIx's NVIC */
#define SPIx_IRQn                        SPI2_IRQn
#define SPIx_IRQHandler                  SPI2_IRQHandler

#define SPIx_DMA_TX_IRQn                 DMA1_Stream4_IRQn
#define SPIx_DMA_RX_IRQn                 DMA1_Stream3_IRQn

#define SPIx_DMA_TX_IRQHandler           DMA1_Stream4_IRQHandler
#define SPIx_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler

/* Size of buffer */
#define BUFFERSIZE                       (COUNTOF(Send) - 1)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

SPI_HandleTypeDef SpiHandle;

void SPI_Init(uint32_t BaudRatePrescaler, uint32_t Direction, uint32_t CLKPhase, uint32_t CLKPolarity, uint32_t DataSize, uint32_t FirstBit);
void SPI_DeInit();
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);
void WriteSPI(uint8_t Message);
uint8_t WriteReceiveSPI(uint8_t Message);
