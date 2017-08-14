#pragma once

#include "Clickboards_Conf.h"

#define PWM_I2C_ADDRESS_DEF             (0b10000000)
#define PWM_I2C_ADDRESS_1               (0b10000001)
#define PWM_I2C_ADDRESS_2               (0b10000010)
#define PWM_I2C_ADDRESS_3               (0b10000011)
#define PWM_I2C_ADDRESS_4               (0b10000100)
#define PWM_I2C_ADDRESS_5               (0b10000101)
#define PWM_I2C_ADDRESS_6               (0b10000110)
#define PWM_I2C_ADDRESS_7               (0b10000111)

#define PWM_READ                        (0b00000001)
#define PWM_WRITE                       (0b00000000)

#define PWM_REG_MODE1                   (0x00)
#define PWM_REG_MODE2                   (0x01)

#define PWM_REG_CH00                    (0x06)
#define PWM_REG_CH01                    (0x0A)
#define PWM_REG_CH02                    (0x0E)
#define PWM_REG_CH03                    (0x12)
#define PWM_REG_CH04                    (0x16)
#define PWM_REG_CH05                    (0x1A)
#define PWM_REG_CH06                    (0x1E)
#define PWM_REG_CH07                    (0x22)
#define PWM_REG_CH08                    (0x26)
#define PWM_REG_CH09                    (0x2A)
#define PWM_REG_CH10                    (0x2E)
#define PWM_REG_CH11                    (0x32)
#define PWM_REG_CH12                    (0x36)
#define PWM_REG_CH13                    (0x3A)
#define PWM_REG_CH14                    (0x3E)
#define PWM_REG_CH15                    (0x42)

#define PWM_REG_CH_ON_L                 (0)
#define PWM_REG_CH_ON_H                 (1)
#define PWM_REG_CH_OFF_L                (2)
#define PWM_REG_CH_OFF_H                (3)

#define PWM_REG_CHALL                   (0xFA)

#define PWM_REG_PRESCALE                (0xFE)

#define PWM_SET_ON                      (0x10)
#define PWM_CLR_ON                      (0x00)
#define PWM_SET_OFF                     (0x10)
#define PWM_CLR_OFF                     (0x00)

#define PWM_CONFIG1_CLK_EXTCLK          (0x40)
#define PWM_CONFIG1_RESTART             (0x80)
#define PWM_CONFIG1_SLEEP_OSCIOFF       (0x10)
#define PWM_CONFIG2_OUTCH_ONACK         (0x08)
#define PWM_CONFIG2_INVRT_ON            (0x10)
#define PWM_CONFIG2_OUTDRV_OD           (0x00)
#define PWM_CONFIG2_OUTDRV_TP           (0x04)

#define Config1_Default                 (0b00000001)
#define Config2_Default                 (0b00000000)

struct clickBoard * PWM_Current;

void initEnable_PWM();
void PWMclick_I2C_Init();
void PWMclick_Select(struct clickBoard * Board);
void PWMclick_WriteConfig(uint8_t CLK, uint8_t SLEEP, uint8_t INVRT, uint8_t OUTCH, uint8_t OUTDRV);
void PWMclick_SetChON(uint8_t channel);
void PWMclick_SetChOFF(uint8_t channel);
void PWMclick_SetChDuty(uint8_t channel, uint16_t Duty, uint16_t Offset);
void PWMclick_SetChDuty_Per(uint8_t channel, double Duty_Per, uint8_t Offset_Per);
double PWMclick_SetFrequency(double Frequency);
uint16_t PWMclick_GetConfig();
unsigned int PWMclick_set(unsigned short channel);
