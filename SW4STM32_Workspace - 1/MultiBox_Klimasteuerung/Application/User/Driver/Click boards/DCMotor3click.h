#pragma once

#include "Clickboards_Conf.h"

struct clickBoard * DCMotor3_Current;
double DCMotor3_Frequency;

void DCMotor3click_Select(struct clickBoard * Board);
void DCMotor3click_set(uint8_t Mode, double DutyCycle);
void DCMotor3click_setFrequency(double Frequency);
void DCMotor3click_setCycle(double DutyCycle);
void DCMotor3click_Mode_ShortBrake();
void DCMotor3click_Mode_CW();
void DCMotor3click_Mode_CCW();
void DCMotor3click_Mode_STOP();
void DCMotor3click_Mode_Standby();
