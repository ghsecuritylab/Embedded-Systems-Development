/** \file
 *  \brief
 *
 *
 */


/** \addtogroup AdapterBoard
 *  @{
 */

#include "AdapterBoard_OneWire.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_OneWire() {
    LOCK_OneWire = 0;

    //Init OneWire Pin
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /* XXX OneWire Pin */
    TM_OneWire_Init(&OW, GPIOA, GPIO_PIN_8);	// D10
    //TM_OneWire_Init(&OW, GPIOB, GPIO_PIN_15);	// D11

    checkOneWireDevice_SearchonBus();

    //Send Reset-Signal
    TM_OneWire_Reset(&OW);
}


void checkOneWireDevice_SearchonBus() {
    uint8_t Temp, count_, i;

    // suche nach 1Wire-Geräten
    Temp = TM_OneWire_First(&OW);
    count_ = 0;

    device = malloc(sizeof(uint8_t));

    while (Temp)
    {
        count_++;
        device = realloc(device, sizeof(uint8_t) * (8*count_ +1));
        //Get byte per byte
        for (i = 0; i < 8; i++)
        {
            device[(count_ - 1)*8+i] = TM_OneWire_GetROM(&OW, i);
        }

        Temp = TM_OneWire_Next(&OW);
    }

    deviceCount = count_;
    OneWire_Devices_ERROR = 0;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void checkOneWireDevice_Parameter(struct Parameter * Para) {
    int i,j;
    int Found=1;

    for (i=0; i<deviceCount; i++) {
        j=0;
        while((Para->Value.ROM[j] == device[i*8+j]) & (j<8)) {
            j++;
        }
        if (j == 8) {
            //Rom-ID wurde gefunden, 8 bytes stimmen überein
            Found = 0;
            break;
        }
    }

    OneWire_Devices_ERROR += Found;
}
