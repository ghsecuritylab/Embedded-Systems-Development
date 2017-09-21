/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

 /** \addtogroup PWMclick
 *  \brief PWMclick Driver
 *
 *  @{
 *  The PWMclick board can be programmed using I2C and has 16 12-bit-PWM-Out Pins which can be controlled independently.
 *  The PWM-Frequency can be set from 24Hz to 1526Hz or
 *  an External-Clock signal can be used. The chosen Frequency is used for ALL Pins.
 *  Each Pin can be \n
 *  - ON all the time \n
 *  - OFF all the time \n
 *  - ON for XX Steps/Percent and then OFF \n
 *  - ON for XX Steps/Percent and then OFF with a defined Offset to Start \n
 */

#include "PWMclick.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_I2C_Init() {
    //Call I2C_Init
    I2C_Init(I2C_TIMING,I2C_ADDRESS,I2C_ADDRESSINGMODE_7BIT);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_Select(struct clickBoard * Board) {
    PWM_Current = Board;
    if (Board->Address == 0) {
        Board->Address = PWM_I2C_ADDRESS_DEF;
    }

    uint8_t i;
    PWMclick_I2C_Init();
    i = CheckI2C_Device(Board->Address);
    I2C_DeInit();

    if (i != 1) {
        //Board Nicht Gefunden
        Board->MB->Error = 1;
    }

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_WriteConfig(uint8_t CLK, uint8_t SLEEP, uint8_t INVRT, uint8_t OUTCH, uint8_t OUTDRV) {
    uint8_t temp;

    if (!PWM_Current->MB->Error) {
        //Init I2C
        PWMclick_I2C_Init();

        temp = Config1_Default | CLK | SLEEP;
        WriteI2C_Reg(PWM_Current->Address,PWM_REG_MODE1,temp);

        temp = Config2_Default | INVRT | OUTCH | OUTDRV;
        WriteI2C_Reg(PWM_Current->Address,PWM_REG_MODE2,temp);

        //DeInit
        I2C_DeInit();
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_SetChON(uint8_t channel) {
    if (!PWM_Current->MB->Error) {

    PWMclick_I2C_Init();

    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_H,PWM_SET_ON);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_L,0x00);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_H,0x00);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_L,0x00);

    I2C_DeInit();

    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_SetChOFF(uint8_t channel) {
    if (!PWM_Current->MB->Error) {

    PWMclick_I2C_Init();

    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_H,0x00);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_L,0x00);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_H,PWM_SET_OFF);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_L,0x00);

    I2C_DeInit();

    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_SetChDuty(uint8_t channel, uint16_t Duty, uint16_t Offset) {
if (!PWM_Current->MB->Error) {
    PWMclick_I2C_Init();

    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_L,Duty);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_OFF_H,Duty >> 8);

    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_L,Offset);
    WriteI2C_Reg(PWM_Current->Address,channel + PWM_REG_CH_ON_H,Offset >> 8);


    I2C_DeInit();
}
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_SetChDuty_Per(uint8_t channel, double Duty_Per,  uint8_t Offset_Per) {

    if (Duty_Per >= 100) {

        PWMclick_SetChON(channel);
    } else if (Duty_Per == 0) {
        PWMclick_SetChOFF(channel);
    } else if ((Duty_Per < 100) & (Offset_Per <= 100)) {
        uint16_t Duty;
        uint16_t Offset;

        Duty = (uint16_t) (4096 * Duty_Per / 100);
        Offset = (uint16_t) (4096 * Offset_Per / 100);
        PWMclick_SetChDuty(channel,Duty, Offset);
    }

}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void PWMclick_Start(uint8_t Reg_Mode1) {
if (!PWM_Current->MB->Error) {
    //Init I2C
    PWMclick_I2C_Init();

    //Set Osci ON, Wait for Oscillator, Set Restart Bit
    WriteI2C_Reg(PWM_Current->Address,PWM_REG_MODE1,Reg_Mode1 & !PWM_CONFIG1_SLEEP_OSCIOFF);
    HAL_Delay(1);
    WriteI2C_Reg(PWM_Current->Address,PWM_REG_MODE1,(Reg_Mode1 & !PWM_CONFIG1_SLEEP_OSCIOFF) | PWM_CONFIG1_RESTART);

    //DeInit I2C
    I2C_DeInit();
}
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t PWMclick_Shutdown_HoldValues() {
    uint8_t Reg_Mode1;

if (!PWM_Current->MB->Error) {
    //Init I2C
    PWMclick_I2C_Init();

    //Read Config1
    Reg_Mode1 = ReceiveI2C_Reg(PWM_Current->Address, PWM_REG_MODE1, 1);

    //Set the SleepBit
    WriteI2C_Reg(PWM_Current->Address,PWM_REG_MODE1,Reg_Mode1 | 0b00010000);

    //Wait for Restart-Bit to be Set
    do
    {
        Reg_Mode1 = ReceiveI2C_Reg(PWM_Current->Address, PWM_REG_MODE1, 1);
    } while (!(Reg_Mode1 & PWM_CONFIG1_RESTART));

    //DeInit I2C
    I2C_DeInit();
}
    return Reg_Mode1;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
double PWMclick_SetFrequency(double Frequency) {
    //Check if Frequency is in Range
    if ((Frequency >= 24) & (Frequency <= 1526)) {
        uint8_t prescale_value;
        uint8_t Reg_Mode1;

        //Calculation of PreScaleValue
        prescale_value = (uint8_t) (25000000 / (4096 * Frequency)) - 1 + 0.5;

        //Shutdown the PWMclick
        Reg_Mode1 = PWMclick_Shutdown_HoldValues();

if (!PWM_Current->MB->Error) {
        //Init I2C
        PWMclick_I2C_Init();

        //Write New Frequency
        WriteI2C_Reg(PWM_Current->Address,PWM_REG_PRESCALE,prescale_value);

        //DeInit I2C
        I2C_DeInit();
}
        //Shutdown the PWMclick
        PWMclick_Start(Reg_Mode1);

        //Return of Real Frequence
        return (25000000 / (( prescale_value + 1) * 4096));
    }

    return 0;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint16_t PWMclick_GetConfig() {
    uint16_t Receive;

if (!PWM_Current->MB->Error) {
    //Init I2C
    PWMclick_I2C_Init();

    Receive = ReceiveI2C_Reg(PWM_Current->Address,PWM_REG_MODE1,1) << 8;
    Receive = Receive | ReceiveI2C_Reg(PWM_Current->Address,PWM_REG_MODE2,1);

    //DeInit I2C
    I2C_DeInit();
}
    return Receive;
}
