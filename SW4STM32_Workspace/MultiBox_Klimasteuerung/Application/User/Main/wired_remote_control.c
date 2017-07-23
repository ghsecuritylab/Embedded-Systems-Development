#include "wired_remote_control.h"
#include "stdint.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
// wired control Header: 0x2706FC
#define WIRED_CONTROL_ID1    0x27U
#define WIRED_CONTROL_ID2    0x06U
#define WIRED_CONTROL_ID3    0xFCU

/* Wired control Pulse Time in us */
#define WIRED_CONTROL_START_PULSE    2000U

#define WIRED_CONTROL_START_PAUSE    1700U
#define WIRED_CONTROL_BIT_PULSE       455U

#define WIRED_CONTROL_LOW_PULSE       380U
#define WIRED_CONTROL_HIGH_PULSE     1200U

#define PULSE_LENGTH_MAX    196

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
wired_control_Config_t wired_control_Config;

wired_control_ConfigStrings_t wired_control_ConfigStrings;

static uint16_t W_Message_Pulses[PULSE_LENGTH_MAX] = {0};
uint8_t W_RX_Message[7] = {0};
uint8_t W_TX_Message[7] = {WIRED_CONTROL_ID1,
                           WIRED_CONTROL_ID2,
                           WIRED_CONTROL_ID3,
                           0,                         // Byte 1: On/Off, FanSpeed, [7:8] - Mode[1:0]
                           0,                         // Byte 2: [7] - Mode[2], [5:1] - Temperature
                           0,                         // Byte 3: Measured Temperature
                           0                          // Byte 4: Checksum
                           };

/* Private function prototypes -----------------------------------------------*/
static void wired_control_ConvertToPulses(uint8_t *Message);
static uint8_t wired_control_CalcChecksum(uint8_t *Message);
static void wired_control_ConvertPulsesToBits(void);

/* Private functions ---------------------------------------------------------*/

/** \brief	Initialize the local AC configuration
 *
 *  \param	None
 *  \retval	None
 */
void wired_control_Init(void){

	//IRclick_Init();
    wired_control_SetMode(W_Mode_Auto);
    wired_control_SetTemp(W_Temp_20C);
    wired_control_SetFanSpeed(W_Fan_Auto);
    wired_control_SetAirDir(AirDir_Swing_W);
    wired_control_ConvertToPulses(W_TX_Message);
}

/** \brief	Sets the AC mode in the local configuration
 *
 *  \param	wired_control_Mode mode
 *  \retval	None
 */
void wired_control_SetMode(wired_control_Mode mode){
    /* Bits l�schen */
    W_TX_Message[5] &= ~0xC0; // 1100 0000
    W_TX_Message[6] &= ~0x80; // 1000 0000
    /* Neue Konfiguration setzen */
    W_TX_Message[5] |= (0xC0 & (mode<<6));
    W_TX_Message[6] |= (0x80 & (mode<<5));
    wired_control_Config.W_Mode = mode;
    switch(mode){
        case W_Mode_Heat:
        	wired_control_ConfigStrings.W_Mode = "Heat";
            break;
        case W_Mode_Dry:
        	wired_control_ConfigStrings.W_Mode = "Dry";
            break;
        case W_Mode_Cool:
        	wired_control_ConfigStrings.W_Mode = "Cool";
            break;
        case W_Mode_Fan:
        	wired_control_ConfigStrings.W_Mode = "Fan";
            break;
        case W_Mode_Auto:
        	wired_control_ConfigStrings.W_Mode = "Auto";
            break;
        default:
            break;
    }
}

/** \brief	Sets the AC temperature in the local configuration
 *
 *  \param	wired_control_Temperature temp
 *  \retval	None
 */
void wired_control_SetTemp(wired_control_Temperature temp){
    /* Bits l�schen */
    W_TX_Message[6] &= ~0x3E;
    /* Neue Konfiguration setzen */
    W_TX_Message[6] |= (0x3E & (temp<<1));
    wired_control_Config.W_Temperatur = temp;
    switch(temp){
        case W_Temp_16C:
        	wired_control_ConfigStrings.W_Temperatur = "16�C";
            break;
        case W_Temp_17C:
        	wired_control_ConfigStrings.W_Temperatur = "17�C";
            break;
        case W_Temp_18C:
        	wired_control_ConfigStrings.W_Temperatur = "18�C";
            break;
        case W_Temp_19C:
        	wired_control_ConfigStrings.W_Temperatur = "19�C";
            break;
        case W_Temp_20C:
        	wired_control_ConfigStrings.W_Temperatur = "20�C";
            break;
        case W_Temp_21C:
        	wired_control_ConfigStrings.W_Temperatur = "21�C";
            break;
        case W_Temp_22C:
        	wired_control_ConfigStrings.W_Temperatur = "22�C";
            break;
        case W_Temp_23C:
        	wired_control_ConfigStrings.W_Temperatur = "23�C";
            break;
        case W_Temp_24C:
        	wired_control_ConfigStrings.W_Temperatur = "24�C";
            break;
        case W_Temp_25C:
        	wired_control_ConfigStrings.W_Temperatur = "25�C";
            break;
        case W_Temp_26C:
        	wired_control_ConfigStrings.W_Temperatur = "26�C";
            break;
        case W_Temp_27C:
        	wired_control_ConfigStrings.W_Temperatur = "27�C";
            break;
        case W_Temp_28C:
        	wired_control_ConfigStrings.W_Temperatur = "28�C";
            break;
        case W_Temp_29C:
        	wired_control_ConfigStrings.W_Temperatur = "29�C";
            break;
        case W_Temp_30C:
        	wired_control_ConfigStrings.W_Temperatur = "30�C";
            break;
        case W_Temp_31C:
            wired_control_ConfigStrings.W_Temperatur = "31�C";
            break;
        default:
            break;
    }
}

/** \brief	Sets the fan speed in the local configuration
 *
 *  \param	wired_control_FanSpeed fanspeed
 *  \retval	None
 */
void wired_control_SetFanSpeed(wired_control_FanSpeed fanspeed){
    /* Bits l�schen */
    W_TX_Message[5] &= ~0x0C;
    /* Neue Konfiguration setzen */
    W_TX_Message[5] |= (0x0C & (fanspeed<<2));
    wired_control_Config.W_FanSpeed = fanspeed;
    switch(fanspeed){
        case W_Fan_Auto:
        	wired_control_ConfigStrings.W_FanSpeed = "Auto";
            break;
        case W_Fan_Hi:
            wired_control_ConfigStrings.W_FanSpeed = "High";
            break;
        case W_Fan_Med:
            wired_control_ConfigStrings.W_FanSpeed = "Med";
            break;
        case W_Fan_Lo:
            wired_control_ConfigStrings.W_FanSpeed = "Low";
            break;
        default:
            break;
    }
}

/** \brief	Sets the air direction in the local configuration
 *
 *  \param	wired_control_AirDir airdir
 *  \retval	None
 */
void wired_control_SetAirDir(wired_control_AirDir airdir){
    /* Bits l�schen */
    W_TX_Message[10] &= ~0x07;
    /* Neue Konfiguration setzen */
    W_TX_Message[10] |= (0x07 & airdir);
    wired_control_Config.W_AirDirection = airdir;
    switch(airdir){
        case AirDir_0d:
            wired_control_ConfigStrings.W_AirDirection = "0� (Horizontal)";
            break;
        case AirDir_30d:
            wired_control_ConfigStrings.W_AirDirection = "30�";
            break;
        case AirDir_60d:
            wired_control_ConfigStrings.W_AirDirection = "60�";
            break;
        case AirDir_90d:
            wired_control_ConfigStrings.W_AirDirection = "90� (Vertical)";
            break;
        case AirDir_Swing_W:
            wired_control_ConfigStrings.W_AirDirection = "Swing";
            break;
        default:
            break;
    }
}

/** \brief	Sends the local configuration to the AC unit
 *
 *  \param	None
 *  \retval	None
 */
void wired_control_SendIRMessage(void){
    W_TX_Message[11] = wired_control_CalcChecksum(W_TX_Message);
    wired_control_ConvertToPulses(W_TX_Message);
    IRclick_Send(W_Message_Pulses, PULSE_LENGTH_MAX);
}

/** \brief	Sends the local configuration with Power-On-bit to the AC unit
 *
 *  \param	None
 *  \retval	None
 */
void wired_control_PowerOn(void){
    /* Bits l�schen */
    W_TX_Message[5] &= ~0x03; //0000 0011
    /* Neue Konfiguration setzen */
    W_TX_Message[5] |= (0x03 & W_Power_On); // 0111, after &: 0000 0011. After |:
    /* Send Message */
    wired_control_SendIRMessage();
    //wired_control_ConvertToPulses(W_Message_ON);
    //IRclick_Send(W_Message_Pulses, PULSE_LENGTH_MAX);
    /* Bits wieder l�schen */
    W_TX_Message[5] &= ~0x03;
}

/** \brief	Sends the local configuration with Power-Off-bit to the AC unit
 *
 *  \param	None
 *  \retval	None
 */
void wired_control_PowerOff(void){
    /* Bits l�schen */
    W_TX_Message[5] &= ~0x03;
    /* Neue Konfiguration setzen */
    W_TX_Message[5] |= (0x03 & W_Power_Off);
    /* Send Message */
    wired_control_SendIRMessage();
    //wired_control_ConvertToPulses(W_Message_OFF);
    //IRclick_Send(W_Message_Pulses, PULSE_LENGTH_MAX);
    /* Bits wieder l�schen */
    W_TX_Message[5] &= ~0x03;
}





/** \brief	Converts the Hex-Message into pulses
 *
 *  \param	uint8_t *Message: Pointer to Hex-Message which will be converted
 *  \retval	None
 */
static void wired_control_ConvertToPulses(uint8_t *Message){
    W_Message_Pulses[0] = WIRED_CONTROL_START_PULSE;
    W_Message_Pulses[1] = WIRED_CONTROL_START_PAUSE;
    uint8_t nByte;
    int8_t nBit;
    uint16_t nPulse = 2;
    for(nByte = 0; nByte < 7; nByte++){
        for(nBit = 0; nBit < 8; nBit++){
            if(Message[nByte] & (0x1 << nBit)){
                W_Message_Pulses[nPulse++] = WIRED_CONTROL_BIT_PULSE;
                W_Message_Pulses[nPulse++] = WIRED_CONTROL_HIGH_PAUSE;
            }else{
                W_Message_Pulses[nPulse++] = WIRED_CONTROL_BIT_PULSE;
                W_Message_Pulses[nPulse++] = WIRED_CONTROL_LOW_PAUSE;
            }
        }
    }
    W_Message_Pulses[nPulse++] = WIRED_CONTROL_BIT_PULSE;
}






/** \brief	Calculates the Checksum (Byte 7) from Byte 1 to 6
 *
 *  \param	Pointer to the Message which will be calculated
 *  \retval	uint8_t Checksum
 */
static uint8_t wired_control_CalcChecksum(uint8_t *Message){
    uint8_t checksum = 0;
    for(size_t index = 0; index < 6; ++index){
        checksum += (Message[index] >> 4) + (Message[index] & 0x0F);
    }
    return checksum - 8;
}

/** \brief	Converts the received Pulselength into Bytes
 *
 *  \param	None
 *  \retval	None
 */
static void wired_control_ConvertPulsesToBits(void){
	uint16_t *pRX_Pulse_Buffer = IRclick_GetRXMessagePulseBuffer();
	uint8_t index = 3;
	uint8_t byte = 0;
	for(int i = 0; i<12; i++){
		for(int j = 0; j<8; j++){
			if(pRX_Pulse_Buffer[index] > 40){
				byte |= 1<<j;
			}
			index += 2;
		}
		W_RX_Message[i] = byte;
		byte = 0;
	}
}

/** \brief	Function to check if a new message has arrived
 *
 *  \param	None
 *  \retval	1 (yes) / 0 (no)
 */
uint8_t wired_control_NewRXMessageAvailable(void){
	return IRclick_IsMessageReady();
}

/** \brief	This function returns a pointer to the received IR-Message
 *
 *  \param	None
 *  \retval	Pointer to the IR-Message
 */
uint8_t * wired_control_GetRXMessage(void){
	wired_control_ConvertPulsesToBits();
	return W_RX_Message;
}

/** \brief	This function fills an char-array with the IR-Message
 *
 *  \param	char array in which the message is stored as ASCII
 *  \retval	None
 */
void wired_control_GetRXMessageAsString(char * message){
	wired_control_ConvertPulsesToBits();
	sprintf(message, "%02X %02X %02X %02X %02X %02X %02X",
			W_RX_Message[0],
			W_RX_Message[1],
			W_RX_Message[2],
			W_RX_Message[3],
			W_RX_Message[4],
			W_RX_Message[5],
			W_RX_Message[6]);
}

