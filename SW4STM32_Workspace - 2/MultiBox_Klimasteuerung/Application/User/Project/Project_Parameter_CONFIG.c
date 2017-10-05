/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Memory
 *  @{
 */

/** \addtogroup Parameter
 *  @{
 */
#include "Project_Parameter_CONFIG.h"
#include "Parameter.h"

/** \brief
 *	XXX Project Parameter Init
 *
 *  \param
 *  \retval
 */
void Project_Init_Parameters() {

	// ParameterWriteALL(Para, MinVal, DefVal, MaxVal, StepVal, ValVal)

	ParameterGroup_Init(&ParameterGroup_TemperatureControl, "Temperaturregelung", "", &ParameterGroup_Prozessparameter);
	{
		Parameter_Init(&TC_IstWert_Sel, &ParameterGroup_TemperatureControl);
		TC_IstWert_Sel.DataType = &DATATYPE_UNINT;
		TC_IstWert_Sel.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&TC_IstWert_Sel), 0,0,2,1,0);
		strcpy(TC_IstWert_Sel.Name, "Auswahl Regelgröße");
		strcpy(TC_IstWert_Sel.Description, "siehe Hauptfenster");

		Parameter_Init(&TC_Sollwert, &ParameterGroup_TemperatureControl);
		TC_Sollwert.DataType = &DATATYPE_UNINT;
		TC_Sollwert.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&TC_Sollwert), 16,20,30,1,20);
		strcpy(TC_Sollwert.Name, "Stellwert");
	}

	Parameter_Init(&ONEWIRE_ROM_ROOM, &ParameterGroup_OneWire);
	ONEWIRE_ROM_ROOM.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_ROOM.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_ROOM.Name, "Raumtemperatur");

	Parameter_Init(&ONEWIRE_ROM_OUTSIDE, &ParameterGroup_OneWire);
	ONEWIRE_ROM_OUTSIDE.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_OUTSIDE.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_OUTSIDE.Name, "Aussentemperatur");

	Parameter_Init(&ONEWIRE_ROM_AIR1, &ParameterGroup_OneWire);
	ONEWIRE_ROM_AIR1.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_AIR1.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_AIR1.Name, "Luftstrom Klimagerät 1");

	Parameter_Init(&ONEWIRE_ROM_UNIT1_OUTSIDE, &ParameterGroup_OneWire);
	ONEWIRE_ROM_UNIT1_OUTSIDE.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_UNIT1_OUTSIDE.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_UNIT1_OUTSIDE.Name, "Ausseneinheit 1");

	Parameter_Init(&ONEWIRE_ROM_AIR2, &ParameterGroup_OneWire);
	ONEWIRE_ROM_AIR2.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_AIR2.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_AIR2.Name, "Luftstrom Klimagerät 2");

	Parameter_Init(&ONEWIRE_ROM_UNIT2_OUTSIDE, &ParameterGroup_OneWire);
	ONEWIRE_ROM_UNIT2_OUTSIDE.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_UNIT2_OUTSIDE.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_UNIT2_OUTSIDE.Name, "Ausseneinheit 2");

	Parameter_Init(&ONEWIRE_ROM_MOTOR, &ParameterGroup_OneWire);
	ONEWIRE_ROM_MOTOR.EditType = EDITTYPE_ONEWIREROM;
	ONEWIRE_ROM_MOTOR.DataType = &DATATYPE_ROM;
	strcpy(ONEWIRE_ROM_MOTOR.Name, "Motortemperatur");

	Parameter_Init(&GraphDispLines, NULL);
	GraphDispLines.EditType = EDITTYPE_NOEDIT;
	GraphDispLines.DataType = &DATATYPE_UNINT;
	strcpy(GraphDispLines.Name, "GraphDispLines");

	// ParameterWriteALL(Para, MinVal, DefVal, MaxVal, StepVal, ValVal)

	ParameterGroup_Init(&ParameterGroup_CAN, "Einstellung CAN", "für Regelgröße", &ParameterGroup_Prozessparameter);
	{
		Parameter_Init(&CAN_TEMP_ID, &ParameterGroup_CAN);
		CAN_TEMP_ID.EditType = EDITTYPE_KEYPAD_HEX;
		CAN_TEMP_ID.DataType = &DATATYPE_HEX;
		ParameterWriteALL((&CAN_TEMP_ID), 0x000,0xFFF,0xFFF,1,0xFFF);
		strcpy(CAN_TEMP_ID.Name, "CAN ID");
		strcpy(CAN_TEMP_ID.Description, "Nachricht mit Temperaturwert");

		Parameter_Init(&CAN_TEMP_STARTBIT, &ParameterGroup_CAN);
		CAN_TEMP_STARTBIT.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_STARTBIT.DataType = &DATATYPE_UNINT;
		ParameterWriteALL((&CAN_TEMP_STARTBIT), 0,0,64,1,0);
		strcpy(CAN_TEMP_STARTBIT.Name, "Startbit");
		//strcpy(CAN_TEMP_STARTBIT.Description, "Temperatur Allgemein");

		Parameter_Init(&CAN_TEMP_BITCOUNT, &ParameterGroup_CAN);
		CAN_TEMP_BITCOUNT.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_BITCOUNT.DataType = &DATATYPE_UNINT;
		ParameterWriteALL((&CAN_TEMP_BITCOUNT), 1,16,32,1,16);
		strcpy(CAN_TEMP_BITCOUNT.Name, "Anzahl Bits");
		//strcpy(CAN_TEMP_BITCOUNT.Description, "Temperatur Allgemein");

		Parameter_Init(&CAN_TEMP_TYPE, &ParameterGroup_CAN);
		CAN_TEMP_TYPE.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_TYPE.DataType = &DATATYPE_UNINT;
		ParameterWriteALL((&CAN_TEMP_TYPE), 0,0,2,1,0);
		strcpy(CAN_TEMP_TYPE.Name, "Wertetyp");
		strcpy(CAN_TEMP_TYPE.Description, "0: unsigned, 1: signed, 2: float");

		Parameter_Init(&CAN_TEMP_FORMAT, &ParameterGroup_CAN);
		CAN_TEMP_FORMAT.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_FORMAT.DataType = &DATATYPE_UNINT;
		ParameterWriteALL((&CAN_TEMP_FORMAT), 0,0,1,1,0);
		strcpy(CAN_TEMP_FORMAT.Name, "Format");
		strcpy(CAN_TEMP_FORMAT.Description, "0: Intel, 1: Motorola");

		Parameter_Init(&CAN_TEMP_FACTOR, &ParameterGroup_CAN);
		CAN_TEMP_FACTOR.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_FACTOR.DataType = &DATATYPE_FLOAT;
		ParameterWriteALL((&CAN_TEMP_FACTOR), 0.0,1.0,1000.0,1,1.0);
		strcpy(CAN_TEMP_FACTOR.Name, "Faktor");
		//strcpy(CAN_TEMP_FACTOR.Description, "Temperatur Allgemein");

		Parameter_Init(&CAN_TEMP_OFFSET, &ParameterGroup_CAN);
		CAN_TEMP_OFFSET.EditType = EDITTYPE_KEYPAD;
		CAN_TEMP_OFFSET.DataType = &DATATYPE_FLOAT;
		ParameterWriteALL((&CAN_TEMP_OFFSET), 0.0,0.0,1000.0,1,0.0);
		strcpy(CAN_TEMP_OFFSET.Name, "Offset");
		//strcpy(CAN_TEMP_OFFSET.Description, "Temperatur Allgemein");
	}

	ParameterGroup_Init(&ParameterGroup_TimeSwitchList, "Zeitschaltliste", "", &ParameterGroup_TimeSwitchList);
	{

		Parameter_Init(&ListEntryCount, &ParameterGroup_TimeSwitchList);
		ListEntryCount.DataType = &DATATYPE_UNINT;
		ListEntryCount.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntryCount), 0,0,9,1,0);
		strcpy(ListEntryCount.Name, "ListEntryCount");

		/* Time Switch List Entry 0 */
		Parameter_Init(&ListEntry0_Day, &ParameterGroup_TimeSwitchList);
		ListEntry0_Day.DataType = &DATATYPE_UNINT;
		ListEntry0_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry0_Day), 1,1,7,1,1);
		strcpy(ListEntry0_Day.Name, "ListEntry0_Day");

		Parameter_Init(&ListEntry0_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry0_Hour.DataType = &DATATYPE_UNINT;
		ListEntry0_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry0_Hour), 0,0,23,1,0);
		strcpy(ListEntry0_Hour.Name, "ListEntry0_Hour");

		Parameter_Init(&ListEntry0_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry0_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry0_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry0_Minutes), 0,0,59,1,0);
		strcpy(ListEntry0_Minutes.Name, "ListEntry0_Minutes");

		Parameter_Init(&ListEntry0_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry0_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry0_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry0_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry0_Temperature.Name, "ListEntry0_Temperature");

		Parameter_Init(&ListEntry0_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry0_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry0_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry0_Repeat), 0,0,1,1,0);
		strcpy(ListEntry0_Repeat.Name, "ListEntry0_Temperature");

		/* Time Switch List Entry 1 */
		Parameter_Init(&ListEntry1_Day, &ParameterGroup_TimeSwitchList);
		ListEntry1_Day.DataType = &DATATYPE_UNINT;
		ListEntry1_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry1_Day), 1,1,7,1,1);
		strcpy(ListEntry1_Day.Name, "ListEntry1_Day");

		Parameter_Init(&ListEntry1_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry1_Hour.DataType = &DATATYPE_UNINT;
		ListEntry1_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry1_Hour), 0,0,23,1,0);
		strcpy(ListEntry1_Hour.Name, "ListEntry1_Hour");

		Parameter_Init(&ListEntry1_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry1_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry1_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry1_Minutes), 0,0,59,1,0);
		strcpy(ListEntry1_Minutes.Name, "ListEntry1_Minutes");

		Parameter_Init(&ListEntry1_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry1_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry1_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry1_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry1_Temperature.Name, "ListEntry1_Temperature");

		Parameter_Init(&ListEntry1_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry1_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry1_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry1_Repeat), 0,0,1,1,0);
		strcpy(ListEntry1_Repeat.Name, "ListEntry1_Temperature");

		/* Time Switch List Entry 2 */
		Parameter_Init(&ListEntry2_Day, &ParameterGroup_TimeSwitchList);
		ListEntry2_Day.DataType = &DATATYPE_UNINT;
		ListEntry2_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry2_Day), 1,1,7,1,1);
		strcpy(ListEntry2_Day.Name, "ListEntry2_Day");

		Parameter_Init(&ListEntry2_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry2_Hour.DataType = &DATATYPE_UNINT;
		ListEntry2_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry2_Hour), 0,0,23,1,0);
		strcpy(ListEntry2_Hour.Name, "ListEntry2_Hour");

		Parameter_Init(&ListEntry2_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry2_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry2_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry2_Minutes), 0,0,59,1,0);
		strcpy(ListEntry2_Minutes.Name, "ListEntry2_Minutes");

		Parameter_Init(&ListEntry2_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry2_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry2_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry2_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry2_Temperature.Name, "ListEntry2_Temperature");

		Parameter_Init(&ListEntry2_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry2_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry2_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry2_Repeat), 0,0,1,1,0);
		strcpy(ListEntry2_Repeat.Name, "ListEntry2_Temperature");

		/* Time Switch List Entry 3 */
		Parameter_Init(&ListEntry3_Day, &ParameterGroup_TimeSwitchList);
		ListEntry3_Day.DataType = &DATATYPE_UNINT;
		ListEntry3_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry3_Day), 1,1,7,1,1);
		strcpy(ListEntry3_Day.Name, "ListEntry3_Day");

		Parameter_Init(&ListEntry3_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry3_Hour.DataType = &DATATYPE_UNINT;
		ListEntry3_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry3_Hour), 0,0,23,1,0);
		strcpy(ListEntry3_Hour.Name, "ListEntry3_Hour");

		Parameter_Init(&ListEntry3_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry3_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry3_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry3_Minutes), 0,0,59,1,0);
		strcpy(ListEntry3_Minutes.Name, "ListEntry3_Minutes");

		Parameter_Init(&ListEntry3_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry3_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry3_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry3_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry3_Temperature.Name, "ListEntry3_Temperature");

		Parameter_Init(&ListEntry3_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry3_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry3_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry3_Repeat), 0,0,1,1,0);
		strcpy(ListEntry3_Repeat.Name, "ListEntry3_Repeat");

		/* Time Switch List Entry 4 */
		Parameter_Init(&ListEntry4_Day, &ParameterGroup_TimeSwitchList);
		ListEntry4_Day.DataType = &DATATYPE_UNINT;
		ListEntry4_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry4_Day), 1,1,7,1,1);
		strcpy(ListEntry4_Day.Name, "ListEntry4_Day");

		Parameter_Init(&ListEntry4_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry4_Hour.DataType = &DATATYPE_UNINT;
		ListEntry4_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry4_Hour), 0,0,23,1,0);
		strcpy(ListEntry4_Hour.Name, "ListEntry4_Hour");

		Parameter_Init(&ListEntry4_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry4_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry4_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry4_Minutes), 0,0,59,1,0);
		strcpy(ListEntry4_Minutes.Name, "ListEntry4_Minutes");

		Parameter_Init(&ListEntry4_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry4_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry4_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry4_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry4_Temperature.Name, "ListEntry4_Temperature");

		Parameter_Init(&ListEntry4_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry4_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry4_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry4_Repeat), 0,0,1,1,0);
		strcpy(ListEntry4_Repeat.Name, "ListEntry4_Repeat");

		/* Time Switch List Entry 5 */
		Parameter_Init(&ListEntry5_Day, &ParameterGroup_TimeSwitchList);
		ListEntry5_Day.DataType = &DATATYPE_UNINT;
		ListEntry5_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry5_Day), 1,1,7,1,1);
		strcpy(ListEntry5_Day.Name, "ListEntry5_Day");

		Parameter_Init(&ListEntry5_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry5_Hour.DataType = &DATATYPE_UNINT;
		ListEntry5_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry5_Hour), 0,0,23,1,0);
		strcpy(ListEntry5_Hour.Name, "ListEntry5_Hour");

		Parameter_Init(&ListEntry5_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry5_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry5_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry5_Minutes), 0,0,59,1,0);
		strcpy(ListEntry5_Minutes.Name, "ListEntry5_Minutes");

		Parameter_Init(&ListEntry5_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry5_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry5_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry5_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry5_Temperature.Name, "ListEntry5_Temperature");

		Parameter_Init(&ListEntry5_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry5_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry5_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry5_Repeat), 0,0,1,1,0);
		strcpy(ListEntry5_Repeat.Name, "ListEntry5_Repeat");

		/* Time Switch List Entry 6 */
		Parameter_Init(&ListEntry6_Day, &ParameterGroup_TimeSwitchList);
		ListEntry6_Day.DataType = &DATATYPE_UNINT;
		ListEntry6_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry6_Day), 1,1,7,1,1);
		strcpy(ListEntry6_Day.Name, "ListEntry6_Day");

		Parameter_Init(&ListEntry6_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry6_Hour.DataType = &DATATYPE_UNINT;
		ListEntry6_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry6_Hour), 0,0,23,1,0);
		strcpy(ListEntry6_Hour.Name, "ListEntry6_Hour");

		Parameter_Init(&ListEntry6_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry6_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry6_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry6_Minutes), 0,0,59,1,0);
		strcpy(ListEntry6_Minutes.Name, "ListEntry6_Minutes");

		Parameter_Init(&ListEntry6_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry6_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry6_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry6_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry6_Temperature.Name, "ListEntry6_Temperature");

		Parameter_Init(&ListEntry6_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry6_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry6_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry6_Repeat), 0,0,1,1,0);
		strcpy(ListEntry6_Repeat.Name, "ListEntry6_Repeat");

		/* Time Switch List Entry 7 */
		Parameter_Init(&ListEntry7_Day, &ParameterGroup_TimeSwitchList);
		ListEntry7_Day.DataType = &DATATYPE_UNINT;
		ListEntry7_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry7_Day), 1,1,7,1,1);
		strcpy(ListEntry7_Day.Name, "ListEntry7_Day");

		Parameter_Init(&ListEntry7_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry7_Hour.DataType = &DATATYPE_UNINT;
		ListEntry7_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry7_Hour), 0,0,23,1,0);
		strcpy(ListEntry7_Hour.Name, "ListEntry7_Hour");

		Parameter_Init(&ListEntry7_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry7_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry7_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry7_Minutes), 0,0,59,1,0);
		strcpy(ListEntry7_Minutes.Name, "ListEntry7_Minutes");

		Parameter_Init(&ListEntry7_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry7_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry7_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry7_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry7_Temperature.Name, "ListEntry7_Temperature");

		Parameter_Init(&ListEntry7_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry7_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry7_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry7_Repeat), 0,0,1,1,0);
		strcpy(ListEntry7_Repeat.Name, "ListEntry7_Repeat");

		/* Time Switch List Entry 8 */
		Parameter_Init(&ListEntry8_Day, &ParameterGroup_TimeSwitchList);
		ListEntry8_Day.DataType = &DATATYPE_UNINT;
		ListEntry8_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry8_Day), 1,1,7,1,1);
		strcpy(ListEntry8_Day.Name, "ListEntry8_Day");

		Parameter_Init(&ListEntry8_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry8_Hour.DataType = &DATATYPE_UNINT;
		ListEntry8_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry8_Hour), 0,0,23,1,0);
		strcpy(ListEntry8_Hour.Name, "ListEntry8_Hour");

		Parameter_Init(&ListEntry8_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry8_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry8_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry8_Minutes), 0,0,59,1,0);
		strcpy(ListEntry8_Minutes.Name, "ListEntry8_Minutes");

		Parameter_Init(&ListEntry8_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry8_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry8_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry8_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry8_Temperature.Name, "ListEntry8_Temperature");

		Parameter_Init(&ListEntry8_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry8_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry8_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry8_Repeat), 0,0,1,1,0);
		strcpy(ListEntry8_Repeat.Name, "ListEntry8_Repeat");

		/* Time Switch List Entry 9 */
		Parameter_Init(&ListEntry9_Day, &ParameterGroup_TimeSwitchList);
		ListEntry9_Day.DataType = &DATATYPE_UNINT;
		ListEntry9_Day.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry9_Day), 1,1,7,1,1);
		strcpy(ListEntry9_Day.Name, "ListEntry9_Day");

		Parameter_Init(&ListEntry9_Hour, &ParameterGroup_TimeSwitchList);
		ListEntry9_Hour.DataType = &DATATYPE_UNINT;
		ListEntry9_Hour.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry9_Hour), 0,0,23,1,0);
		strcpy(ListEntry9_Hour.Name, "ListEntry9_Hour");

		Parameter_Init(&ListEntry9_Minutes, &ParameterGroup_TimeSwitchList);
		ListEntry9_Minutes.DataType = &DATATYPE_UNINT;
		ListEntry9_Minutes.EditType = EDITTYPE_UPDOWN;
		ParameterWriteALL((&ListEntry9_Minutes), 0,0,59,1,0);
		strcpy(ListEntry9_Minutes.Name, "ListEntry9_Minutes");

		Parameter_Init(&ListEntry9_Temperature, &ParameterGroup_TimeSwitchList);
		ListEntry9_Temperature.DataType = &DATATYPE_FLOAT;
		ListEntry9_Temperature.EditType = EDITTYPE_KEYPAD;
		ParameterWriteALL((&ListEntry9_Temperature), 0.0,0.0,30.0,1.0,0);
		strcpy(ListEntry9_Temperature.Name, "ListEntry9_Temperature");

		Parameter_Init(&ListEntry9_Repeat, &ParameterGroup_TimeSwitchList);
		ListEntry9_Repeat.DataType = &DATATYPE_BOOL;
		ListEntry9_Repeat.EditType = EDITTYPE_TOGGLE;
		ParameterWriteALL((&ListEntry9_Repeat), 0,0,1,1,0);
		strcpy(ListEntry9_Repeat.Name, "ListEntry9_Repeat");
	}

}
