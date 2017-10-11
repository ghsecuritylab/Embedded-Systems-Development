/** \file AdapterBoard_MikrobusSocket.c
 *  \brief Source File providing functions for controlling the MikrobusSockets on the AdapterBoard.
 *
 */


/** \addtogroup AdapterBoard
 *  @{
 */

 /** \addtogroup MikrobusSockets
 *  \brief Driver for MikrobusSockets
 *
 *  @{
 *
 */

#include "AdapterBoard_MikrobusSocket.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_Mikrobus(void) {
    /* Enable the GPIO clock */
        // CS
        __HAL_RCC_GPIOG_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        // 1-Wire
        __HAL_RCC_GPIOA_CLK_ENABLE();

        //SPI
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();

        //I2C
        __HAL_RCC_GPIOB_CLK_ENABLE();

        //UART
        __HAL_RCC_GPIOC_CLK_ENABLE();

        //INTs
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();

    //Init ErrorStati
    Init_Error(&MB1,0);
    Init_Error(&MB2,0);
    Init_Error(&MB3,0);
    Init_Error(&MB4,0);
    Init_Error(&MB5,0);
    Init_Error(&MB6,0);
    Init_Error(&MB7,0);
    Init_Error(&MB8,0);

    //INIT 8xCS
    Init_CS(&MB1, GPIOG, GPIO_PIN_6);
    Init_CS(&MB2, GPIOB, GPIO_PIN_4);
    Init_CS(&MB3, GPIOG, GPIO_PIN_7);
    Init_CS(&MB4, GPIOI, GPIO_PIN_0);
    Init_CS(&MB5, GPIOH, GPIO_PIN_6);
    Init_CS(&MB6, GPIOI, GPIO_PIN_3);
    Init_CS(&MB7, GPIOI, GPIO_PIN_2);
    Init_CS(&MB8, GPIOA, GPIO_PIN_15);

    //INIT 4xINT
    Init_INT(&MB1, GPIOA, GPIO_PIN_0);
    Init_INT(&MB2, GPIOF, GPIO_PIN_10);
    Init_INT(&MB3, GPIOF, GPIO_PIN_9);
    Init_INT(&MB4, GPIOF, GPIO_PIN_8);

    //INIT 8xRST
    Init_RST(&MB1, &IC1, 7);
    Init_RST(&MB2, &IC2, 2);
    Init_RST(&MB3, &IC2, 7);
    Init_RST(&MB4, &IC3, 0);
    Init_RST(&MB5, &IC1, 5);
    Init_RST(&MB6, &IC1, 1);
    Init_RST(&MB7, &IC3, 4);
    Init_RST(&MB8, &IC3, 6);

    //INIT 8xPWM
    Init_PWM(&MB1, &IC1, 0);
    Init_PWM(&MB2, &IC2, 3);
    Init_PWM(&MB3, &IC2, 0);
    Init_PWM(&MB4, &IC2, 5);
    Init_PWM(&MB5, &IC1, 4);
    Init_PWM(&MB6, &IC1, 3);
    Init_PWM(&MB7, &IC3, 3);
    Init_PWM(&MB8, &IC3, 7);

    //INIT 8xAN
    Init_AN(&MB1, &IC2, 4);
    Init_AN(&MB2, &IC2, 1);
    Init_AN(&MB3, &IC2, 6);
    Init_AN(&MB4, &IC3, 1);
    Init_AN(&MB5, &IC1, 6);
    Init_AN(&MB6, &IC1, 2);
    Init_AN(&MB7, &IC3, 2);
    Init_AN(&MB8, &IC3, 5);

    //I2C_Config
    IC1.I2CAddress = 0b01110000;
    IC1.Config = 0b00000000;
    I2C_IO_Select(&IC1);
    I2C_IO_SetOut_and_Config();

    IC2.I2CAddress = 0b01110010;
    IC2.Config = 0b00000000;
    I2C_IO_Select(&IC2);
    I2C_IO_SetOut_and_Config();

    IC3.I2CAddress = 0b01111000;
    IC3.Config = 0b00000000;
    I2C_IO_Select(&IC3);
    I2C_IO_SetOut_and_Config();

    IC_USER.I2CAddress = 0b01110100;
    IC_USER.Config = 0b00001000;
    I2C_IO_Select(&IC_USER);
    I2C_IO_SetOut_and_Config();
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_Error(struct MikrobusSocket * MB, uint8_t Error) {
    MB->Error = Error;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_CS(struct MikrobusSocket * MB, GPIO_TypeDef * Port, uint16_t Pin) {
    MB->CS_Port = Port;
    MB->CS_Pin = Pin;

    GPIO_InitTypeDef  gpio_init_structure;

    /* Configure the GPIO_LED pin */
    gpio_init_structure.Pin = MB->CS_Pin;
    gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;

    HAL_GPIO_Init(MB->CS_Port, &gpio_init_structure);

    SetCS(MB, 1);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_INT(struct MikrobusSocket * MB, GPIO_TypeDef * Port, uint16_t Pin) {
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_PWM(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin) {
    MB->PWM_I2C_IO = IC;
    MB->PWM_I2C_Pin = Pin;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_RST(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin) {
    MB->RST_I2C_IO = IC;
    MB->RST_I2C_Pin = Pin;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_AN(struct MikrobusSocket * MB, struct I2C_IO * IC, uint8_t Pin) {
    MB->AN_I2C_IO = IC;
    MB->AN_I2C_Pin = Pin;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SetPWM(struct MikrobusSocket * MB, uint8_t state) {
    I2C_IO_SetPin(MB->PWM_I2C_IO, MB->PWM_I2C_Pin, state);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SetAN(struct MikrobusSocket * MB, uint8_t state) {
    I2C_IO_SetPin(MB->AN_I2C_IO, MB->AN_I2C_Pin, state);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SetRST(struct MikrobusSocket * MB, uint8_t state) {
    I2C_IO_SetPin(MB->RST_I2C_IO, MB->RST_I2C_Pin, state);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void SetCS(struct MikrobusSocket * MB, uint8_t state) {
    if (state == 0) {
        HAL_GPIO_WritePin(MB->CS_Port,MB->CS_Pin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(MB->CS_Port,MB->CS_Pin, GPIO_PIN_SET);
    }

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void CheckMikrobus(struct MikrobusSocket * MB, uint8_t state) {
    SetAN(MB, state);
    SetRST(MB, state);
    SetPWM(MB, state);
    SetCS(MB, state);

    //I2C
    HAL_GPIO_WritePin(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN, state);
    HAL_GPIO_WritePin(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN, state);

    //SPI
    HAL_GPIO_WritePin(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN , state);
    HAL_GPIO_WritePin(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN, state);
    HAL_GPIO_WritePin(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN, state);

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void RST_ALL(struct MikrobusSocket * MB, uint8_t state) {

}
