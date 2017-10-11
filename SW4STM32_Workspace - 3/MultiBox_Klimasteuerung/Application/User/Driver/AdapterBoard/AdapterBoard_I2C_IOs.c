/** \file AdapterBoard_I2C_IOs.c
 *  \brief Source File providing functions for controlling the 4x I2C-PortExpander on the AdapterBoard.
 *
 *  3 of the Port-Expander are used for controlling IO-Pins of the Mikrobussockets which are rarely used by the clickboards. \n
 *  The last I2C is used for the USER-IO.
 */


/** \addtogroup AdapterBoard
 *  @{
 */

 /** \addtogroup Port-Expander
 *  \brief I2C-Port Expander Driver
 *
 *  @{
 *
 *  Those Port Expanders are providing the option to control at each of the 8 Mikrobussockets the following Pins:
 *  - RST
 *  - PWM
 *  - AN
 *  The last of the Port Expanders is used for the USER-IO.
 *  - 3 Channels are used for a RGB-LED,
 *  - 1 Channel for a Buzzer,
 *  - 1 Channel for a Config-Button
 *  - 3 Channel are free and can be used for additional, projectspecific USER-IO
 */

#include "AdapterBoard_I2C_IOs.h"

/** \brief Setzt die Ports des momentan ausgewaehlten Port-Expanders
 *
 * \retval keins
 */
void I2C_IO_SetOut_and_Config()
{
    //Nur senden wenn kein Error vorliegt
    if (!I2C_IO_Current->Error) {
        I2C_IO_I2C_Init();

        WriteI2C_1B(I2C_IO_ACK_W | I2C_IO_Current->I2CAddress, I2C_IO_Current->OutputState | I2C_IO_Current->Config);

        I2C_DeInit();
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_I2C_Init() {
    //Call I2C_Init
    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);
}

/** \brief Liest die Ports des momentan ausgewaehlten Port-Expanders
 *
 * \retval 8-bit Portstatus
 */
static uint8_t state;
uint8_t * I2C_IO_GetPin(struct I2C_IO * IC, uint8_t Pin)
{
    state = 0;
    uint8_t Mask,i;

    //Nur Expander auslesen, wenn kein Error vorliegt
    if (!I2C_IO_Current->Error) {
        Mask = 1;
        for (i=0;i<Pin; i++) {
            Mask = (Mask << 1);
        }

        uint8_t Data;
        Data=1;

        I2C_IO_I2C_Init();

        Data = *ReceiveI2C(I2C_IO_ACK_R | I2C_IO_Current->I2CAddress,1);

        I2C_DeInit();

        state = (Data & Mask) >> Pin;

        if (state == 1) {
            state = 1;
        }
    }

    return &state;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_SetPin(struct I2C_IO * IC, uint8_t Pin, uint8_t state) {
    I2C_IO_Select(IC);

    uint8_t Mask,i;
    Mask = 1;
    for (i=0;i<Pin; i++) {
        Mask = (Mask << 1);
    }

    Mask = ~Mask;

    IC->OutputState = (IC->OutputState & Mask) | (state << Pin);
    I2C_IO_SetOut_and_Config();
}

/** \brief Waehlt den angegebenen Port-Expander als momentaten Port-Expander aus
 *
 * \param Addr: Adresse des auszuwaehlenden Port-Expanders
 *      \arg RST
 *      \arg PWM
 *      \arg AN
 *      \arg UserIO
 * \retval keins
 */
void I2C_IO_Select(struct I2C_IO * IC)
{
    I2C_IO_Current = IC;

    I2C_IO_I2C_Init();
    I2C_IO_Current->Error = !CheckI2C_Device(I2C_IO_Current->I2CAddress);
    I2C_DeInit();
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_USER_SetLED(uint8_t R, uint8_t G, uint8_t B)
{
    I2C_IO_Select(&IC_USER);

    I2C_IO_SetPin(&IC_USER,0,R);
    I2C_IO_SetPin(&IC_USER,1,B);
    I2C_IO_SetPin(&IC_USER,2,G);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_USER_SetEXT(uint8_t EXT1, uint8_t EXT2, uint8_t EXT3)
{
    I2C_IO_Select(&IC_USER);

    I2C_IO_SetPin(&IC_USER,5,EXT1);
    I2C_IO_SetPin(&IC_USER,6,EXT2);
    I2C_IO_SetPin(&IC_USER,7,EXT3);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_USER_SetBuzzer(uint32_t time, uint16_t Frequency)
{
    uint8_t state;
    uint32_t tickstart = 0;
    uint32_t Delta;

    Delta = 100000 / Frequency;

    I2C_IO_Select(&IC_USER);

    tickstart = HAL_GetTick();
    while((HAL_GetTick() - tickstart) < 2*time)
    {
        state = (state == 0) ? 1 : 0;
        //I2C_IO_SetPin(&IC_USER,4,state);
        delayUS(Delta);
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t * I2C_IO_USER_GetKonfig()
{
    /*I2C_IO_Select(&IC_USER);
    //I2C_IO_SetPin(&IC_USER,3,1);

    return I2C_IO_GetPin(&IC_USER,3);*/
	return 0;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void I2C_IO_USER_SetALARM()
{
    while(1) {
        I2C_IO_USER_SetBuzzer(10,1000);
        I2C_IO_USER_SetLED(0,0,0);
        HAL_Delay(20);
        I2C_IO_USER_SetBuzzer(20,2000);
        I2C_IO_USER_SetLED(1,1,1);
        HAL_Delay(20);
        I2C_IO_USER_SetBuzzer(40,1500);
        I2C_IO_USER_SetLED(0,0,1);
        HAL_Delay(20);
        I2C_IO_USER_SetBuzzer(80,1800);
        I2C_IO_USER_SetLED(0,1,0);
        HAL_Delay(20);
        I2C_IO_USER_SetBuzzer(100,2200);
        I2C_IO_USER_SetLED(1,0,0);
        HAL_Delay(2000);
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void delayUS(uint32_t us)
{
    uint32_t t;

    t = DWT->CYCCNT;

    while((DWT->CYCCNT - t) < (us * 200));


    //us = us * 200 / 3 - 66;
    //while(us--);
}

//void AdapterBoard_Read() {
//    #if USE_RTOS_SYSTEM
//    osSignalSet(ThreadID_ADAPTER,0x1);
//    #else
//    Firmware_ProcessLogic_ReadInputs(8);
//    Project_ProcessLogic_ReadInputs(8);
//    #endif
//}
//
//void AdapterBoard_Write() {
//    #if USE_RTOS_SYSTEM
//    osSignalSet(ThreadID_ADAPTER,0x2);
//    #else
//    Firmware_ProcessLogic_WriteOutputs(8);
//    Project_ProcessLogic_WriteOutputs(8);
//    #endif
//}
