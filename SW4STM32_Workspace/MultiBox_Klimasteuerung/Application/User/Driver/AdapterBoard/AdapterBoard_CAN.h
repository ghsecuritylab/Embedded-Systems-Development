#pragma once

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "MemoryStructures.h"
#include "stm32746g_discovery.h"
#include "main.h"

#define CANx                             CAN1
#define CANx_CLK_ENABLE()               __HAL_RCC_CAN1_CLK_ENABLE()
#define CANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#define CANx_FORCE_RESET()              __HAL_RCC_CAN1_FORCE_RESET()
#define CANx_RELEASE_RESET()            __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CANx_TX_PIN                    GPIO_PIN_12
#define CANx_TX_GPIO_PORT              GPIOA
#define CANx_TX_AF                     GPIO_AF9_CAN1
#define CANx_RX_PIN                    GPIO_PIN_11
#define CANx_RX_GPIO_PORT              GPIOA
#define CANx_RX_AF                     GPIO_AF9_CAN1

/* Definition for USARTx's NVIC */
#define CANx_RX_IRQn                   CAN1_RX0_IRQn
#define CANx_RX_IRQHandler             CAN1_RX0_IRQHandler

#define CANx_TX_IRQn                   CAN1_TX_IRQn
#define CANx_TX_IRQHandler             CAN1_TX_IRQHandler


CAN_HandleTypeDef      CanHandle;
CanTxMsgTypeDef        TxMessage;
CanRxMsgTypeDef        RxMessage;

void CAN_Config(uint16_t SPEED);
void LED_Display(uint8_t LedStatus);
void CAN_recieve();

void CAN_send(uint16_t ID, uint8_t STATUS, uint16_t SPEED , uint8_t Count, uint8_t * Data);
void CAN_TRANSMIT(uint8_t ACTIVE_FLAG, uint8_t Clock_Speed, uint8_t Msg);

extern void ProjectCanMessage(CAN_HandleTypeDef *CanHandle);
extern void ProjectCanMessage_System(CAN_HandleTypeDef *CanHandle);
