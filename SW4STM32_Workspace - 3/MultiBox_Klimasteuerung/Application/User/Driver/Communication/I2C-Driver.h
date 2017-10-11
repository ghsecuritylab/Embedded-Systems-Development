#pragma once

#include "stm32746g_discovery.h"

#include <stdlib.h>

#define I2Cx                            I2C1
#define RCC_PERIPHCLK_I2Cx              RCC_PERIPHCLK_I2C1
#define RCC_I2CxCLKSOURCE_SYSCLK        RCC_I2C1CLKSOURCE_PCLK1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

#define I2C_ADDRESS        0xF

/* I2C TIMING Register define when I2C clock source is APB1 (SYSCLK/4) */
/* I2C TIMING is calculated in case of the I2C Clock source is the APB1CLK = 50 MHz */
/* This example use TIMING to 0x40912732 to reach 100 kHz speed (Rise time = 700 ns, Fall time = 100 ns) */
#define I2C_TIMING      0x40912732

I2C_HandleTypeDef I2cHandle;
uint8_t I2C_Tx, I2C_Rx;



/** \file I2Cclick_conf.c
 *  \brief Source File providing functions for using the I2C interface of the Microcontroller.
 *
 *  Each Mikrobussocket is connected to the I2C-Pins of the ARDUINO UNO Connector. The Clickboard drivers are using the functions for the Initialization
 *  of the I2C-Interface, and the command sending/receiving. Normally the WriteI2C_Reg/ReceiveI2C_Reg functions are used because most of the clickboards having
 *  a register-based IC on them.
 *
 *  Besides the clickboards these functions are used by the I2C-Portexpanders Those are providing additional Pins needed by the Mikrobussockets.
 */


/** \addtogroup Communication
 *  @{
 */

 /** \addtogroup I2C
 *  \brief Provides I2C_Communication Functions.
 *  @{
 *
 *  This library is used for all I2C-Communication between the Microcontrollerboards, the Mikrobussockets, the Arduino Nanos and the I2C-Port Expanders.
 */

#include "I2C-Driver.h"

void I2C_Init(uint32_t Timing, uint32_t Address, uint32_t AddressingMode);
void WriteI2C(uint16_t Address, unsigned char * Message);
void WriteI2C_1B(uint16_t Address, uint8_t Message);
uint8_t * ReceiveI2C(uint16_t Address, int Count);
void WriteI2C_Reg(uint16_t Address, uint16_t Register,uint8_t Message);
uint8_t CheckI2C_Device(uint16_t Address);
uint16_t ReceiveI2C_Reg(uint16_t Address,uint16_t Register, uint8_t Count);
void I2C_DeInit();
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

void I2C1_WriteByte(uint8_t Addr, uint8_t Reg, uint8_t Value);
HAL_StatusTypeDef I2C1_ReadByte(uint8_t Addr, uint8_t Reg, uint8_t *Data);

