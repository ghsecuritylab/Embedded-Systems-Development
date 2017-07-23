#include "AdapterBoard_CAN.h"

uint8_t Count = 1;
uint8_t interval;
uint8_t temp = 0;

void HAL_CAN_MspInit(CAN_HandleTypeDef *CanHandle) {

  GPIO_InitTypeDef   GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* CAN1 Periph clock enable */
    CANx_CLK_ENABLE();              // HAL_RCC_CAN1_CLOCK_ENABLE
    CANx_GPIO_CLK_ENABLE();         // HAL_RCC_GPIOx_CLK_ENABLE

  /*##-2- Configure peripheral GPIO ##########################################*/

  /* CAN1 TX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Alternate =  CANx_TX_AF;

  HAL_GPIO_Init(CANx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* CAN1 RX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_RX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Alternate =  CANx_RX_AF;

  HAL_GPIO_Init(CANx_RX_GPIO_PORT, &GPIO_InitStruct);

}

void CAN_PinChecker() {

  GPIO_InitTypeDef   GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* CAN1 Periph clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE(); // RCC: Reset and Clock Controller

  /*##-2- Configure peripheral GPIO ##########################################*/

  /* CAN1 TX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(CANx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* CAN1 RX GPIO pin configuration */
  GPIO_InitStruct.Pin = CANx_RX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  HAL_GPIO_Init(CANx_RX_GPIO_PORT, &GPIO_InitStruct);

  HAL_GPIO_WritePin(CANx_TX_GPIO_PORT,CANx_TX_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(CANx_RX_GPIO_PORT,CANx_RX_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(CANx_TX_GPIO_PORT,CANx_TX_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CANx_RX_GPIO_PORT,CANx_RX_PIN,GPIO_PIN_RESET);
}


/**
  * @brief CAN MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *CanHandle) {

  /*##-1- Reset peripherals ##################################################*/
  CANx_FORCE_RESET();
  CANx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* De-initialize the CAN1 TX GPIO pin */
  HAL_GPIO_DeInit(CANx_TX_GPIO_PORT, CANx_TX_PIN);
  /* De-initialize the CAN1 RX GPIO pin */
  HAL_GPIO_DeInit(CANx_RX_GPIO_PORT, CANx_RX_PIN);

  /*##-4- Disable the NVIC for CAN reception #################################*/
  HAL_NVIC_DisableIRQ(CANx_RX_IRQn); // NVIC: Nested Vectored Interrupt Controller

}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */

 void CAN_Config(uint16_t SPEED) {

/* This Initialization is used only for CAN receive */
/* For SEND Operation, configuration is done separately in CAN_send function */

  CAN_FilterConfTypeDef  sFilterConfig;

/*##-1- Configure the CAN peripheral #######################################*/
  CanHandle.Instance = CANx;
  CanHandle.pTxMsg = &TxMessage;
  CanHandle.pRxMsg = &RxMessage;
  CanHandle.State = HAL_CAN_STATE_RESET;
  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_NORMAL;
  CanHandle.Init.SJW  = CAN_SJW_1TQ;
  CanHandle.Init.BS1  = CAN_BS1_5TQ;
  CanHandle.Init.BS2  = CAN_BS2_4TQ;

  switch(SPEED){
            case (64):
                  CanHandle.Init.Prescaler = 10;
                  break;
            case (100):
                  CanHandle.Init.Prescaler = 50;
                  break;
            case (125):
                  CanHandle.Init.Prescaler = 40;
                  break;
            case (500):
                  CanHandle.Init.Prescaler = 10;
                  break;
            case (1000):
                  CanHandle.Init.Prescaler = 5;
                  break;
            default:
                  CanHandle.Init.Prescaler = 10;   // Default Clock_speed 500 kbps
        }

  if (HAL_CAN_Init(&CanHandle) != HAL_OK)   // HAL_CAN_Init
  {
    /* Initialization Error */
    Firmware_ProcessLogic_ErrorHandler(0);
  }

 /*##-2- Configure the CAN Filter ###########################################*/
  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  sFilterConfig.FilterIdHigh = 0b01000000 << 5; // (msg ID) 11 bits -> (filter length) 16 bits
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0b0000000000 << 5;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if (HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)   // Configure filter
  {
    /* Filter configuration Error */
    Firmware_ProcessLogic_ErrorHandler(0);
  }

 /*##-3- Configure the NVIC #################################################*/

/* NVIC configuration for CAN1 Reception complete interrupt */
  HAL_NVIC_SetPriority(CANx_RX_IRQn, 1, 0); // only CAN1 is used
  HAL_NVIC_EnableIRQ(CANx_RX_IRQn);

}

void CAN_send(uint16_t ID, uint8_t STATUS, uint16_t SPEED , uint8_t Count, uint8_t * Data) {

   /*##-1- Configure the CAN peripheral #######################################*/
  CanHandle.Instance = CANx;
  CanHandle.pTxMsg = &TxMessage;
  CanHandle.pRxMsg = &RxMessage;
  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_NORMAL;
  CanHandle.Init.SJW  = CAN_SJW_1TQ;
  CanHandle.Init.BS1  = CAN_BS1_5TQ;
  CanHandle.Init.BS2  = CAN_BS2_4TQ;

  switch(SPEED){
            case (64):
                  CanHandle.Init.Prescaler = 10;
                  break;
            case (100):
                  CanHandle.Init.Prescaler = 50;
                  break;
            case (125):
                  CanHandle.Init.Prescaler = 40;
                  break;
            case (500):
                  CanHandle.Init.Prescaler = 10;
                  break;
            case (1000):
                  CanHandle.Init.Prescaler = 5;
                  break;
            default:
                  CanHandle.Init.Prescaler = 10;   // Default Clock_speed 500 kbps
        }

/*polling method. Tx process is not configured with interrupt handling unlike CAN_Receive function*/

  if (HAL_CAN_Init(&CanHandle) != HAL_OK) // Transmit Message
  {
    /* Initialization Error */
    Firmware_ProcessLogic_ErrorHandler(0);
  }
    /*##-3- Configure Transmission process #####################################*/

        CanHandle.pTxMsg->StdId = ID;           //Can be anything. Should be verified at receiving end
        CanHandle.pTxMsg->ExtId = 0x01;         //Can be anything. Should be verified at receiving end
        CanHandle.pTxMsg->RTR = CAN_RTR_DATA;
        CanHandle.pTxMsg->IDE = CAN_ID_STD;
        CanHandle.pTxMsg->DLC = Count;          // DLC can be decided based on data which we receive from process logic

        uint8_t i;
        for(i=0; i<Count; i++) {
            CanHandle.pTxMsg->Data[i] = Data[i];
        }
        //CanHandle.pTxMsg->Data[1] = 0x02;

     /* Transmit Message #####################################*/

    if (HAL_CAN_Transmit(&CanHandle, 10) != HAL_OK) {
          /* Tx Error */
        //Firmware_ProcessLogic_ErrorHandler();
    }
}

void CAN_recieve() {

    /* Enable CAN reception */
  if (HAL_CAN_Receive_IT(&CanHandle,CAN_FIFO0) != HAL_OK)
    {
        /* Rx Error */
        Firmware_ProcessLogic_ErrorHandler(0);
    }
}

void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef *CanHandle){
    /* User Code when interrupt is triggered */
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *CanHandle){

    /* User Code when interrupt is triggered */

    Firmware_ProcessLogic_CAN_Receive(CanHandle);
    Project_ProcessLogic_CAN_Receive(CanHandle);

    /* Receive */
    CAN_recieve();

}

/*CAN_TRANSMIT(uint8_t ACTIVE_FLAG, uint8_t ID, uint8_t Cycle_Time){

ACTIVE_FLAG == ParameterRead(CAN_Msg1_ACTIVE.Group.Para.ID

/*if ( (ParameterRead((&CAN_ACTIVE),Value) == 1) && (ParameterRead((&CAN_ZYKLUSZEIT),Value) == Cnt) ){

            CAN_send(ParameterRead((&CAN_ID), Value),ParameterRead((&CAN_SPEED),Value),0,0);
            Cnt = 1;

}*/

/* For Test Purpose */

void LED_Display(uint8_t LedStatus) {

    switch(LedStatus){
    case(1):
        BSP_LED_On(LED1);
    break;

    case(2):
        BSP_LED_On(LED1);
        HAL_Delay(1000);
        BSP_LED_Off(LED1);
    break;
    }
}
