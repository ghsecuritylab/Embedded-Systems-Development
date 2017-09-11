/** \file
 *  \brief
 *
 *
 */

/** \addtogroup ClickBoard-Driver
 *  @{
 */

 /** \addtogroup DCMotor3click
 *  @{
 *
 */

#include "DCMotor3click.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void DCMotor3click_Select(struct clickBoard * Board) {
    DCMotor3_Current = Board;
}

void DCMotor3click_setFrequency(double Frequency) {
    DCMotor3_Frequency = Frequency;
}

void DCMotor3click_setCycle(double DutyCycle) {
    SetMCUExt_PWM(DCMotor3_Current->Address,DCMotor3_Frequency,DutyCycle);
}


void DCMotor3click_Mode_ShortBrake() {
    SetAN(DCMotor3_Current->MB,1);
    SetRST(DCMotor3_Current->MB,1);
    SetCS(DCMotor3_Current->MB,1);
}

void DCMotor3click_Mode_CW() {
    SetAN(DCMotor3_Current->MB,0);
    SetRST(DCMotor3_Current->MB,1);
    SetCS(DCMotor3_Current->MB,1);
}

void DCMotor3click_Mode_CCW() {
    SetAN(DCMotor3_Current->MB,1);
    SetRST(DCMotor3_Current->MB,0);
    SetCS(DCMotor3_Current->MB,1);
}

void DCMotor3click_Mode_STOP() {
    SetAN(DCMotor3_Current->MB,0);
    SetRST(DCMotor3_Current->MB,0);
    SetCS(DCMotor3_Current->MB,1);
}

void DCMotor3click_Mode_Standby() {
    SetAN(DCMotor3_Current->MB,1);
    SetRST(DCMotor3_Current->MB,1);
    SetCS(DCMotor3_Current->MB,0);
}
