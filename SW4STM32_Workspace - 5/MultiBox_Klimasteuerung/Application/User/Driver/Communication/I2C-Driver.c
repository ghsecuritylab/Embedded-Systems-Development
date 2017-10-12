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

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_Init(uint32_t Timing, uint32_t Address, uint32_t AddressingMode)
{
    I2cHandle.Instance             = I2Cx;
    I2cHandle.Init.Timing          = 0x00A0A5F9; //I2C_TIMING;
    I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
    I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.OwnAddress2     = 0xFF;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2CEx_ConfigAnalogFilter(&I2cHandle,I2C_ANALOGFILTER_ENABLE);

    while(HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {

    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void WriteI2C(uint16_t Address, unsigned char * Message)
{
    uint8_t size_Message = (sizeof(Message)-1) / sizeof(char) -1;
    //I2C_Tx = 1;

    if (HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)Address, Message,size_Message) != HAL_OK) {
    }

    while(!I2C_Tx);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void WriteI2C_1B(uint16_t Address, uint8_t Message)
{
    uint32_t t = DWT->CYCCNT;

    I2C_Tx = 0;

    if (HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)Address, &Message,1) != HAL_OK) {
    }

    //Timeout nach 500µs
    while(!I2C_Tx & ((DWT->CYCCNT - t) < (200*500)));
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static uint8_t Answer;
uint8_t * ReceiveI2C(uint16_t Address, int Count)
{
    Answer = 0;

    uint32_t t = DWT->CYCCNT;

    I2C_Rx = 0;

    if(HAL_I2C_Master_Receive_IT(&I2cHandle, (uint16_t)Address, &Answer,Count) != HAL_OK)
    {
        //Answer = Answer;
    }

    while(!I2C_Rx & ((DWT->CYCCNT - t) < (200*400)));

    return &Answer;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void WriteI2C_Reg(uint16_t Address, uint16_t Register,uint8_t Message)
{
    //static
    uint8_t Bytes[3];
    Bytes[0] = Register;
    Bytes[1] = Message;

    HAL_I2C_Master_Transmit(&I2cHandle, Address, &(Bytes[0]), 2, 1);
    /*
    if (HAL_I2C_Mem_Write(&I2cHandle, (uint16_t)Address, Register, 1, &Message,1 , 1) != HAL_OK) {
    }*/
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t CheckI2C_Device(uint16_t Address)
{
    uint8_t I2CSendCount = 0;

    while((HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)Address,0,0) != HAL_OK) & (I2CSendCount < 10))  {
        I2CSendCount++;
    }

    return (I2CSendCount > 10) ? 0 : 1;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
static uint8_t Answer;
uint16_t ReceiveI2C_Reg(uint16_t Address,uint16_t Register, uint8_t Count)
{

    if(HAL_I2C_Mem_Read(&I2cHandle, (uint16_t)Address, Register, 1, &Answer,1 , 1) != HAL_OK)
    {
    }

    return Answer;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_DeInit()
{
    HAL_I2C_DeInit(&I2cHandle);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  /*GPIO_InitTypeDef  GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef  RCC_PeriphCLKInitStruct;

  /*##-1- Configure the I2C clock source. The clock is derived from the SYSCLK #
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2Cx;
  RCC_PeriphCLKInitStruct.I2c1ClockSelection = RCC_I2CxCLKSOURCE_SYSCLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

  /*##-2- Enable peripherals and GPIO Clocks #################################
  /* Enable GPIO TX/RX clock
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  /* Enable I2Cx clock
  I2Cx_CLK_ENABLE();

  /*##-3- Configure peripheral GPIO ##########################################
  /* I2C TX GPIO pin configuration
  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

  /* I2C RX GPIO pin configuration
  GPIO_InitStruct.Pin       = I2Cx_SDA_PIN;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);*/






  {

    GPIO_InitTypeDef GPIO_InitStruct;
    if(hi2c->Instance==I2C1)
    {
    /* USER CODE BEGIN I2C1_MspInit 0 */

    /* USER CODE END I2C1_MspInit 0 */

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = I2Cx_SCL_PIN |I2Cx_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
    /* USER CODE BEGIN I2C1_MspInit 1 */

    /* USER CODE END I2C1_MspInit 1 */
    }
  }

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

  /*##-1- Reset peripherals ##################################################
  I2Cx_FORCE_RESET();
  I2Cx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################
  /* Configure I2C Tx as alternate function
  HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
  /* Configure I2C Rx as alternate function
  HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);*/



  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */
      I2Cx_FORCE_RESET();
  I2Cx_RELEASE_RESET();
  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, I2Cx_SDA_PIN|I2Cx_SCL_PIN);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);

    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);

  }
}



/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  i2c_handler : I2C handler
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(I2C_HandleTypeDef *i2c_handler, uint8_t Addr)
{
  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(i2c_handler);

  /* Re-Initialize the I2C communication bus */
  I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);
}


/**
  * @brief  Reads multiple data.
  * @param  i2c_handler : I2C handler
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: Memory address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler,
                                           uint8_t Addr,
                                           uint16_t Reg,
                                           uint16_t MemAddress,
                                           uint8_t *Buffer,
                                           uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}



/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  i2c_handler : I2C handler
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  MemAddress: Memory address
  * @param  Buffer: The target register value to be written
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler,
                                            uint8_t Addr,
                                            uint16_t Reg,
                                            uint16_t MemAddress,
                                            uint8_t *Buffer,
                                            uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}


/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  * @retval None
  */
void I2C1_WriteByte(uint8_t Addr, uint8_t Reg, uint8_t Value){
  I2Cx_WriteMultiple(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,(uint8_t*)&Value, 1);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Received Data
  */
HAL_StatusTypeDef I2C1_ReadByte(uint8_t Addr, uint8_t Reg, uint8_t *Data){
  HAL_StatusTypeDef ret = HAL_ERROR;

  ret = I2Cx_ReadMultiple(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)Data, 1);

  return ret;
}
