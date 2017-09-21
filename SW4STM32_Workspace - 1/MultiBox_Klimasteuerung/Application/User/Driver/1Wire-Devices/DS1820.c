/** \file
 *  \brief
 *
 *
 */

/** \addtogroup Sensors
 *  @{
 */

#include "DS1820.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void DS1820_askTemp(uint8_t * ROM)
{
    if(TM_OneWire_Reset(&OW)==0)
    {
        // befehl senden (auslesen einer Rom-ID)
        TM_OneWire_Select(&OW, ROM);

        TM_OneWire_WriteByte(&OW,DS1820_CONVERT);
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t DS1820_isTemp()
{
    return TM_OneWire_ReadBit(&OW);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
union Data * DS18x20_readTemp(uint8_t * ROM) {
    switch (ROM[0]) {
        case 0x10:  return DS18S20_readTemp(ROM);
        case 0x28:  return DS18B20_readTemp(ROM);
        default:    return NULL;
    }
}


/** \brief
 *
 *
 *  \param
 *  \retval
 */
static union Data Temp;
union Data * DS18S20_readTemp(uint8_t * ROM) {
    Temp.f = -150;

    uint8_t n;

    // reset seq
    if(TM_OneWire_Reset(&OW)==0)
    {
        TM_OneWire_Select(&OW, ROM);

        TM_OneWire_WriteByte(&OW,DS1820_READ_SCRATCH);

        char Receive[9];
        for(n=0; n<8; n++)
        {
            Receive[n] = TM_OneWire_ReadByte(&OW);
        }
        //TM_OneWire_Reset(&OW);
        Temp.f = (float) (Receive[0]) / 2;
        Temp.f += - 0.25 + (float) (Receive[7] - Receive[6]) / Receive[7];
        Temp.f *= ((Receive[1] == 0) ? 1 : -1);
    }

    return &Temp;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
union Data  * DS18B20_readTemp(uint8_t * ROM) {
    Temp.f = -150;
    uint8_t n;

    // reset seq
    if(TM_OneWire_Reset(&OW)==0)
    {
        TM_OneWire_Select(&OW, ROM);

        TM_OneWire_WriteByte(&OW,DS1820_READ_SCRATCH);

        char Receive[9];
        for(n=0; n<8; n++)
        {
            Receive[n] = TM_OneWire_ReadByte(&OW);
        }
        //TM_OneWire_Reset(&OW);
        Temp.f = (float) (Receive[0]) / 16;
        Temp.f += (float) (Receive[1] & 0b111) * 16;
        Temp.f *= ((Receive[1] & 0b1000) == 0) ? 1 : -1;
    }

    return &Temp;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
float DS18x20_getTemp(uint8_t * ROM) {
    switch (ROM[0]) {
        case 0x10:  return DS18S20_getTemp(ROM);
        case 0x28:  return DS18B20_getTemp(ROM);
        default:    return 0.0;
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
float DS18S20_getTemp(uint8_t * ROM) {
    float temp = -150;

    uint8_t n;

    // reset seq
    if(TM_OneWire_Reset(&OW)==0)
    {
        TM_OneWire_Select(&OW, ROM);

        TM_OneWire_WriteByte(&OW,DS1820_READ_SCRATCH);

        char Receive[9];
        for(n=0; n<8; n++)
        {
            Receive[n] = TM_OneWire_ReadByte(&OW);
        }
        //TM_OneWire_Reset(&OW);
        temp = (float) (Receive[0]) / 2;
        temp += - 0.25 + (float) (Receive[7] - Receive[6]) / Receive[7];
        temp *= ((Receive[1] == 0) ? 1 : -1);
    }

    return temp;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
float DS18B20_getTemp(uint8_t * ROM) {
    float temp = -150;
    uint8_t n;

    // reset seq
    if(TM_OneWire_Reset(&OW)==0)
    {
        TM_OneWire_Select(&OW, ROM);

        TM_OneWire_WriteByte(&OW,DS1820_READ_SCRATCH);

        char Receive[9];
        for(n=0; n<8; n++)
        {
            Receive[n] = TM_OneWire_ReadByte(&OW);
        }
        //TM_OneWire_Reset(&OW);
        temp = (float) (Receive[0]) / 16;
        temp += (float) (Receive[1] & 0b111) * 16;
        temp *= ((Receive[1] & 0b1000) == 0) ? 1 : -1;
    }

    return temp;
}
