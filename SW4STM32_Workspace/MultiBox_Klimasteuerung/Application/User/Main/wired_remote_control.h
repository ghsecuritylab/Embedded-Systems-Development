/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WIRED_REMOTE_CONTROL__H
#define WIRED_REMOTE_CONTROL__H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
	W_Power_On  = 0b0111, // 7
	W_Power_Off = 0b1111
}wired_control_Power;

typedef enum {
    W_Mode_Heat = 0b0111,
    W_Mode_Dry  = 0b1101,
    W_Mode_Cool = 0b1011,
    W_Mode_Fan  = 0b0011,
    W_Mode_Auto = 0b1110
}wired_control_Mode;

typedef enum {
    W_Temp_16C = 0b1111,
    W_Temp_17C = 0b0111,
    W_Temp_18C = 0b1011,
    W_Temp_19C = 0b0011,
    W_Temp_20C = 0b1101,
    W_Temp_21C = 0b0101,
    W_Temp_22C = 0b1001,
    W_Temp_23C = 0b0001,
    W_Temp_24C = 0b1110,
    W_Temp_25C = 0b0110,
    W_Temp_26C = 0b1010,
    W_Temp_27C = 0b0010,
    W_Temp_28C = 0b1100,
    W_Temp_29C = 0b0100,
    W_Temp_30C = 0b1000,
	W_Temp_31C = 0b0000
}wired_control_Temperature;

typedef enum {
    W_Fan_Auto = 0b1110,
    W_Fan_Hi   = 0b0111,
    W_Fan_Med  = 0b1011,
    W_Fan_Lo   = 0b0011
}wired_control_FanSpeed;


/** Air direction:
 *  AirDir_0d  - 0°  (Horizontal)
 *  AirDir_30d - 30°
 *  AirDir_60d - 60°
 *  AirDir_90d - 90° (Vertical)
 */
typedef enum {
    AirDir_0d     = 0b1111,
    AirDir_30d    = 0b0111,
    AirDir_60d    = 0b1011,
    AirDir_90d    = 0b0011,
    AirDir_Swing_W  = 0b1110
}wired_control_AirDir;

typedef struct{
	wired_control_Mode W_Mode;
	wired_control_Temperature W_Temperatur;
	wired_control_FanSpeed W_FanSpeed;
	wired_control_AirDir W_AirDirection;
}wired_control_Config_t;

typedef struct{
    char *W_Mode;
    char *W_Temperatur;
    char *W_FanSpeed;
    char *W_AirDirection;
}wired_control_ConfigStrings_t;


extern wired_control_Config_t wired_control_Config;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void wired_control_Init(void);

void wired_control_SetMode(wired_control_Mode mode);
void wired_control_SetTemp(wired_control_Temperature temp);
void wired_control_SetFanSpeed(wired_control_FanSpeed fanspeed);
void wired_control_SetAirDir(wired_control_AirDir airdir);
void wired_control_PowerOn(void);
void wired_control_PowerOff(void);
void wired_control_SendIRMessage(void);

uint8_t wired_control_NewRXMessageAvailable(void);
uint8_t * wired_control_GetRXMessage(void);
void wired_control_GetRXMessageAsString(char * message);

#endif // WIRED_REMOTE_CONTROL__H
