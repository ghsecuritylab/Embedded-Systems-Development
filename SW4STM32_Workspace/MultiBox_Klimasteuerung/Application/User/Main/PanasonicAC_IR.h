/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PANASONICAC_IR__H
#define PANASONICAC_IR__H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
    Power_On  = 0b10,
    Power_Off = 0b01
}PanasonicAC_Power;

typedef enum {
    Mode_Heat = 0b001,
    Mode_Dry  = 0b011,
    Mode_Cool = 0b010,
    Mode_Fan  = 0b000,
    Mode_Auto = 0b100
}PanasonicAC_Mode;

typedef enum {
    Temp_16C = 0b01100,
    Temp_17C = 0b01101,
    Temp_18C = 0b01110,
    Temp_19C = 0b01111,
    Temp_20C = 0b10000,
    Temp_21C = 0b10001,
    Temp_22C = 0b10010,
    Temp_23C = 0b10011,
    Temp_24C = 0b10100,
    Temp_25C = 0b10101,
    Temp_26C = 0b10110,
    Temp_27C = 0b10111,
    Temp_28C = 0b11000,
    Temp_29C = 0b11001,
    Temp_30C = 0b11010
}PanasonicAC_Temperature;

typedef enum {
    Fan_Auto = 0b00,
    Fan_Hi   = 0b01,
    Fan_Med  = 0b11,
    Fan_Lo   = 0b10
}PanasonicAC_FanSpeed;


/** Air direction:
 *  0 - 0° (Horizontal)
 *  1 - 22.5°
 *  2 - 45°
 *  3 - 67.5°
 *  4 - 90° (Vertical)
 */
typedef enum {
    AirDir_0     = 0b001,
    AirDir_1     = 0b010,
    AirDir_2     = 0b011,
    AirDir_3     = 0b100,
    AirDir_4     = 0b101,
    AirDir_Swing = 0b000,
    AirDir_Stop  = 0b111
}PanasonicAC_AirDir;

typedef struct{
    PanasonicAC_Mode Mode;
    PanasonicAC_Temperature Temperatur;
    PanasonicAC_FanSpeed FanSpeed;
    PanasonicAC_AirDir AirDirection;
}Panasonic_AC_Config_t;

typedef struct{
    char *Mode;
    char *Temperatur;
    char *FanSpeed;
    char *AirDirection;
}Panasonic_AC_ConfigStrings_t;


extern Panasonic_AC_Config_t Panasonic_AC_Config;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PanasonicAC_IR_Init(void);

void PanasonicAC_SetMode(PanasonicAC_Mode mode);
void PanasonicAC_SetTemp(PanasonicAC_Temperature temp);
void PanasonicAC_SetFanSpeed(PanasonicAC_FanSpeed fanspeed);
void PanasonicAC_SetAirDir(PanasonicAC_AirDir airdir);
void PanasonicAC_PowerOn(void);
void PanasonicAC_PowerOff(void);
void PanasonicAC_SendIRMessage(void);

uint8_t PanasonicAC_NewRXMessageAvailable(void);
uint8_t * PanasonicAC_GetRXMessage(void);
void PanasonicAC_GetRXMessageAsString(char * message);

#endif // PANASONICAC_IR__H
