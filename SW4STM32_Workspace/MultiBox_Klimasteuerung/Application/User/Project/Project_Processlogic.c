/** \file
 *  \brief
 *
 *	XXX Project Processlogic
 *
 */

/** \addtogroup Project
 *  @{
 */

#include "Project_Processlogic.h"
#include "time_switch.h"
#include "temperature_control.h"
#include "graphSettings.h"

#include "Parameter.h"
#include "Data.h"

//struct clickBoard * Board_DMX_Steckdosen;

/* Temperature Values defined in "Project_Page_Main_1.c"*/
extern float tRaumtemperatur;
extern float tAussentemperatur;
extern float tLuftstrom1;
extern float tLuftstrom2;
extern float tAusseneinheit1;
extern float tAusseneinheit2;
extern float tMotor;
extern float tMotor_CAN;

extern int16_t graphValues[8];
extern uint8_t SollVorgabe1;
extern uint8_t SollVorgabe2;
extern float *pTC_IstTemperature1;
extern float *pTC_IstTemperature2;
extern uint8_t activeMode1;
extern uint8_t activeMode2;


/* CAN Variables */
extern float tMotor_CAN;

uint32_t CycleCounter = 0;

uint8_t newGraphValuesAvailable = 0;

void Project_ProcessLogic_Init_Clickboards() {

	/***********************
	 Zuordnung Clickboards
	 ************************/
//    Board_ADC_1 = Create_clickBoard(4, 0,"ADC", "");
//    Board_EXPAND_4 = Create_clickBoard(6,0,"EXP4","");
//	  Board_PWM_1 = Create_clickBoard(8,0,"PWM","");

	//Board_DMX_Steckdosen = Create_clickBoard(8, 0, "DMX - Steckdosen", "");
	//DMXclick_Select(Board_DMX_Steckdosen);
	DMX_init();
}

void Project_ProcessLogic_Init_Variables() {
}

void Project_ProcessLogic_Configure_Clickboards() {
	/***********************
	 Kopieren der Daten aus ParameterStruktur in Clickboard-Struktur
	 ************************/

	//Update_Clickboard(Board_ADC_1);
	//Update_Clickboard(Board_EXPAND_4);
	//Update_Clickboard(Board_PWM_1);
	/***********************
	 Initialisierung Clickboards
	 ************************/
	//ADCclick_Select(Board_ADC_1);
	//EXPAND4click_Select(Board_EXPAND_4);
	//PWMclick_Select(Board_PWM_1);
	//PWMclick_WriteConfig(0,0,0,PWM_CONFIG2_OUTCH_ONACK,PWM_CONFIG2_OUTDRV_TP);

	//Update_Clickboard(Board_DMX_Steckdosen);

}

static uint8_t ErrorFlag;
uint8_t * Project_ProcessLogic_getError() {
	ErrorFlag = 0;

	//Überprüfung Adapterboard /check
	AdapterBoardFehler = IC1.Error;
	AdapterBoardFehler += IC2.Error;
	AdapterBoardFehler += IC3.Error;
	AdapterBoardFehler += IC_USER.Error;

	//Überprüfung Hardware angeschlossen /connected
	/*MikrobusFehler = Board_EXPAND4_1->MB->Error;
	 MikrobusFehler += Board_EXPAND_1->MB->Error;
	 MikrobusFehler += Board_PWM_1->MB->Error;*/

	//Überprüfung OneWire
	//OneWire_Devices_ERROR = 0;
	//Überprüfung CAN
	CANFehler = 0;

	ErrorFlag = AdapterBoardFehler + MikrobusFehler + OneWire_Devices_ERROR
			+ CANFehler;

	return &ErrorFlag;
}

void Project_ProcessLogic_SafeStartUp() {
	/*PWM_DROSSEL.Value = PWM_DROSSEL.Default; //throttle
	 PWM_DROSSEL.Changed = 1;*/

	Project_ProcessLogic_WriteOutputs();
}

void Project_ProcessLogic_ReadInputs() {

	/* XXX OneWire Project Read */
	if (!LOCK_OneWire) {
		//Anfrage Temperatursensor
		if ((Counter + 2) % 1000 == 0) {
			DS1820_askTemp(ONEWIRE_ROM_ROOM.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_OUTSIDE.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_AIR1.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_UNIT1_OUTSIDE.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_AIR2.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_UNIT2_OUTSIDE.Value.ROM);
			DS1820_askTemp(ONEWIRE_ROM_MOTOR.Value.ROM);
		}

		//Einlesen Temperatursensoren
		if ((Counter + 202) % 1000 == 0) {

			CycleCounter++;

			// OneWire einlesen
			tRaumtemperatur = DS18x20_getTemp(ONEWIRE_ROM_ROOM.Value.ROM);
			tAussentemperatur = DS18x20_getTemp(ONEWIRE_ROM_OUTSIDE.Value.ROM);
			tLuftstrom1 = DS18x20_getTemp(ONEWIRE_ROM_AIR1.Value.ROM);
			tAusseneinheit1 = DS18x20_getTemp(ONEWIRE_ROM_UNIT1_OUTSIDE.Value.ROM);
			tLuftstrom2 = DS18x20_getTemp(ONEWIRE_ROM_AIR2.Value.ROM);
			tAusseneinheit2 = DS18x20_getTemp(ONEWIRE_ROM_UNIT2_OUTSIDE.Value.ROM);
			tMotor = DS18x20_getTemp(ONEWIRE_ROM_MOTOR.Value.ROM);

			/* Add Values to Graph-Buffer and save them in Ringmemory */
			if ((CycleCounter % 1) == 0) {
				/* Add new Values to Graph-Buffer */
				graphValues[0] = SollVorgabe1 * GRAPH_SCALE_Y;
				graphValues[1] = tRaumtemperatur * GRAPH_SCALE_Y;
				graphValues[2] = tAussentemperatur * GRAPH_SCALE_Y;
				graphValues[3] = tLuftstrom1 * GRAPH_SCALE_Y;
				graphValues[4] = tAusseneinheit1 * GRAPH_SCALE_Y;
				graphValues[5] = tLuftstrom2 * GRAPH_SCALE_Y;
				graphValues[6] = tAusseneinheit2 * GRAPH_SCALE_Y;
				graphValues[7] = tMotor * GRAPH_SCALE_Y;
				graphValues[8] = tMotor_CAN * GRAPH_SCALE_Y;

				/* save current values in RingMomory */
				union Data data;
				data.un = graphValues[0];
				RingMemory_Save(&Sollwert, &data);
				data.un = graphValues[1];
				RingMemory_Save(&TemperaturRaum, &data);
				data.un = graphValues[2];
				RingMemory_Save(&TemperaturOutside, &data);
				data.un = graphValues[3];
				RingMemory_Save(&TemperaturAir1, &data);
				data.un = graphValues[4];
				RingMemory_Save(&TemperaturUnit1, &data);
				data.un = graphValues[5];
				RingMemory_Save(&TemperaturAir2, &data);
				data.un = graphValues[6];
				RingMemory_Save(&TemperaturUnit2, &data);
				data.un = graphValues[7];
				RingMemory_Save(&TemperaturMotor, &data);
				data.un = graphValues[8];
				RingMemory_Save(&TemperaturCAN, &data);

				newGraphValuesAvailable = 1;
			}

			/* XXX CAN Message */

			uint8_t *pTemp1 = (uint8_t*) pTC_IstTemperature1;
			uint8_t *pTemp2 = (uint8_t*) pTC_IstTemperature2;
			uint8_t CANData[8];

			// T(soll)1, T(soll)2
			CANData[0] = SollVorgabe1; // Soll Temperature specification
			CANData[1] = SollVorgabe2;

			// T(ist)1, T(ist)2
			CANData[2] = pTemp1[0];
			CANData[3] = pTemp1[1];
			CANData[4] = pTemp2[0];
			CANData[5] = pTemp2[1];

			// 6.0-6.2: Mode1, 6.3-6.5: Mode2, 6.6: 230v-1, 6.7: 230v-2
			CANData[6] = 0x00;
			CANData[6]|= (activeMode1  & 0x1)  << 7;
			CANData[6]|= (activeMode1  & 0x1)  << 6;
			CANData[6]|= (activeMode1  & 0x1)  << 5;
			CANData[6]|= (activeMode2  & 0x1)  << 4;
			CANData[6]|= (activeMode2  & 0x1)  << 3;
			CANData[6]|= (activeMode2  & 0x1)  << 2;
			CANData[6]|= (((uint8_t)ParameterRead(ZUSTAND_Power1,Value))         & 0x1) << 1;
			CANData[6]|= (((uint8_t)ParameterRead(ZUSTAND_Power2,Value))  		 & 0x1) << 0;

			// 7.0: 230v-3, 7.1: 230v-4, 7.2-7.4: Box status, 7.5: B_error, 7.6: B_schnellstopp, 7.7: Status_exhaustGasVentilator
			CANData[7] = 0x00;
			CANData[7]|= (((uint8_t)ParameterRead(ZUSTAND_Power3,Value))         & 0x1) << 7;
			CANData[7]|= (((uint8_t)ParameterRead(ZUSTAND_Power4,Value))         & 0x1) << 6;
			CANData[7]|= (Machinestate & 0x1)  << 5;
			CANData[7]|= (Machinestate & 0x1)  << 4;
			CANData[7]|= (Machinestate & 0x1)  << 3;
			CANData[7]|= (((uint8_t)RingMemory_getVal(IST_Nothalt,0))          	 & 0x1) << 2;
			CANData[7]|= (((uint8_t)ParameterRead(ZUSTAND_Schnellstopp,Value))   & 0x1) << 1;
			CANData[7]|= (((uint8_t)ParameterRead(ZUSTAND_Abgasabsaugung,Value)) & 0x1) << 0;

			CAN_send(0x6AF, 1, 500, sizeof(CANData), CANData);
		}
	}
}

void Project_ProcessLogic_WriteOutputs() {
	/***********************
	 Projekt AusgabeRoutinen /output routine
	 ************************/
	DMX_loop();

}

void Project_ProcessLogic_Mode_Auto() {
	/***********************
	 Projekt AutoRoutinen
	 ************************/
	timeSwitch_checkEvents();
	temperatureControl_evalEvents();

//    if (Counter%50 == 0) {
//        uint8_t SendData[2];
//
//        SendData[0] = ReglerFreigabe << 2 | Notbelueftung << 1 | ((ParameterRead((&PWM_DROSSEL), Value) > 0.0) ? 1 : 0);
//        SendData[1] = (uint8_t) ParameterRead((&IO_VENTIL),Value);
//        CAN_send(0x724,1,500,2,SendData);
//    }

}

void Project_ProcessLogic_Mode_Konfig() {

}

void Project_ProcessLogic_Mode_Error() {

}

void Project_ProcessLogic_CAN_Receive(CAN_HandleTypeDef *CanHandle) {
	CAN_Rx_flag = 1;
	union Data Receive;
	uint32_t uRAW_L = 0;
	uint32_t uRAW_H = 0;
	uint32_t RAW;
	int32_t sRAW;
	float *fPointer;

	if(CanHandle->pRxMsg->StdId == CAN_TEMP_ID.Value.x){
		/* XXX CAN Temperature Receive */

		/* handle format: Intel / Motorola */
		if(CAN_TEMP_FORMAT.Value.un == 0){
			/* Intel Format (Little Endian) */
			for(int i = 0; i < CanHandle->pRxMsg->DLC; i++){
				if(i < 4){
					uRAW_L |= CanHandle->pRxMsg->Data[i] << (i*8);
				}else{
					uRAW_H |= CanHandle->pRxMsg->Data[i] << ((i - 4)*8);
				}
			}
		}else
		if(CAN_TEMP_FORMAT.Value.un == 1){
			/* Motorola Format (Big Endian) */
			for(int i = 0; i < CanHandle->pRxMsg->DLC; i++){
				if(i < 4){
					uRAW_H |= CanHandle->pRxMsg->Data[(CanHandle->pRxMsg->DLC - 1) - i] << (i*8);
				}else{
					uRAW_L |= CanHandle->pRxMsg->Data[(CanHandle->pRxMsg->DLC - 1) - i] << ((i - 4)*8);
				}
			}
		}

		/* handle Startbit and bit count */
		if(CAN_TEMP_STARTBIT.Value.x > 31){
			RAW = uRAW_H >> (CAN_TEMP_STARTBIT.Value.x - 32);
			RAW = RAW & ~(0xFFFFFFFF << CAN_TEMP_BITCOUNT.Value.x);
		}else{
			if( (CAN_TEMP_STARTBIT.Value.x + CAN_TEMP_BITCOUNT.Value.x) > 31){
				RAW = uRAW_L >> CAN_TEMP_STARTBIT.Value.x;
				RAW |= uRAW_H << (32 - CAN_TEMP_STARTBIT.Value.x);
				RAW = RAW & ~(0xFFFFFFFF << CAN_TEMP_BITCOUNT.Value.x);
			}else{
				RAW = uRAW_L >> (CAN_TEMP_STARTBIT.Value.x);
				RAW = RAW & ~(0xFFFFFFFF << CAN_TEMP_BITCOUNT.Value.x);
			}
		}

		/* handle type */
		if(CAN_TEMP_TYPE.Value.un == 0){
			/* value type is unsigned */
			tMotor_CAN = (float)RAW * CAN_TEMP_FACTOR.Value.f + CAN_TEMP_OFFSET.Value.f;

		}else if(CAN_TEMP_TYPE.Value.un == 1){
			/* value type is signed */
			sRAW = (int32_t) RAW;
			tMotor_CAN = (float)sRAW * CAN_TEMP_FACTOR.Value.f + CAN_TEMP_OFFSET.Value.f;

		}else if(CAN_TEMP_TYPE.Value.un == 2){
			/* value type is IEEE float */
			fPointer = (float*)&RAW;
			tMotor_CAN = *fPointer;
		}

	}

	switch (CanHandle->pRxMsg->StdId) {
	case 0x722:
		break;
	case 0x720:
		break;
	}
}
