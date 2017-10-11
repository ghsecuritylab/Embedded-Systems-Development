/*
 * Project name:
     Can_Spi_1st (CAN Network demonstration with mikroE's CAN-SPI module)
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20111224:
       - initial release;
 * Description:
     This is code that shows simple connection of two CAN SPI modules. This is for 1st node.
     Press buttons on PortD/L to send message and receive message on TFT.
 * Test configuration:
     MCU:             STM32F107VC
                      http://www.st.com/internet/com/technical_resources/technical_literature/datasheet/cd00220364.pdf
     Dev.Board:       EasyMx PRO v7 for STM32
                      http://www.mikroe.com/eng/products/view/852/easymx-pro-v7-for-stm32/
     Oscillator:      HSE-PLL, 72.000MHz
     ext. modules:    mikroe  ac:CAN_SPI_click  module
                      http://www.mikroe.com/eng/products/view/813/can-spi-click-3-3v/
                      with  SN65HVD230 on board:
                      http://www.ti.com/product/sn65hvd230
     SW:              mikroC PRO for ARM
                      http://www.mikroe.com/eng/products/view/752/mikroc-pro-for-arm/
 * NOTES:
     - Consult the CAN standard about CAN bus termination resistance.
     - Turn ON TFT backlight (SW11.3)
     - PULL Down PORTD/L (portD three state switch)
     - Set Button Press Switch in upper position.
**************************************************************************************************/
#include "CANclick.h"
/**************************************************************************************************
* Global variables
**************************************************************************************************/
unsigned char Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags; // can flags
unsigned char Rx_Data_Len;                                   // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const long ID_1st = 12111, ID_2nd = 3;                       // node IDs
long Rx_ID;

/**************************************************************************************************
* CAN SPI connections
**************************************************************************************************/
sbit CanSpi_CS            at  GPIOD_ODR.B13;
sbit CanSpi_Rst           at  GPIOC_ODR.B2;

/**************************************************************************************************
* Draw Screen
**************************************************************************************************/
void DrawScr(){
  TFT_Fill_Screen(CL_WHITE);
  TFT_Set_Pen(CL_Black, 1);
  TFT_Line(20, 220, 300, 220);
  TFT_LIne(20,  46, 300,  46);
  TFT_Set_Font(&HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL);
  TFT_Write_Text("CAN spi click  TEST", 75, 14);
  TFT_Set_Font(&Verdana12x13_Regular, CL_BLACK, FO_HORIZONTAL);
  TFT_Write_Text("EasyMX PRO for ST", 19, 223);
  TFT_Set_Font(&Verdana12x13_Regular, CL_RED, FO_HORIZONTAL);
  TFT_Write_Text("www.mikroe.com", 200, 223);
  TFT_Set_Font(&TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
}

/**************************************************************************************************
* Draw LED on screen
**************************************************************************************************/
void DrawLed(short No, char fill){
char xcoo, ycoo;

  if (fill)
    TFT_Set_Brush(1, CL_RED, 1, LEFT_TO_RIGHT, CL_PURPLE, CL_RED);
  else
    TFT_Set_Brush(1, CL_WHITE, 0, LEFT_TO_RIGHT, CL_BLACK, CL_WHITE);

  xcoo = 180 - (No / 4) * 40;
  ycoo = 190 - (No % 4) * 30;
  TFT_Circle(xcoo, ycoo, 10);
}

/**************************************************************************************************
* Port read variables
**************************************************************************************************/
char port_rd;
char port_rd_temp;
char i;
char old_message = 0xFF;

/**************************************************************************************************
* MAIN PROGRAM
**************************************************************************************************/
void main() {

  // PORT set up
  GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_LOW);
  GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_13);
  GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_2);

  TFT_Init(320, 240);
  DrawScr();
  for(i = 0; i < 8; i++)
    DrawLed(i, 0);
  TFT_Write_Text("PORT D/L buttons from 2nd node", 70, 60);

  Can_Init_Flags = 0;                                         //
  Can_Send_Flags = 0;                                         // clear flags
  Can_Rcv_Flags  = 0;                                         //

  Can_Send_Flags = _CANSPI_TX_PRIORITY_0 &                    // form value to be used
                   _CANSPI_TX_XTD_FRAME &                     // with CANSPIWrite
                   _CANSPI_TX_NO_RTR_FRAME;

  Can_Init_Flags = _CANSPI_CONFIG_SAMPLE_THRICE &             // form value to be used
                   _CANSPI_CONFIG_PHSEG2_PRG_ON &             // with CANSPIInit
                   _CANSPI_CONFIG_XTD_MSG &
                   _CANSPI_CONFIG_DBL_BUFFER_ON &
                   _CANSPI_CONFIG_VALID_XTD_MSG;

  // Initialize SPI1 module
   SPI3_Init_Advanced(_SPI_FPCLK_DIV8, _SPI_MASTER  | _SPI_8_BIT |
                     _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                     _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE | _SPI_SSI_1,
                     &_GPIO_MODULE_SPI3_PC10_11_12);

  GPIO_Alternate_Function_Enable(&_GPIO_MODULE_SWJ_JTAGDISABLE);

  // Focs = 10MHz, SJW = 1, PHSEG1 = 3, PHSEG2 = 3, PROPSEG = 1, -> N = 1+3+3+1, N = 8
  // Desired Baud rate Fbaud = 125kb/s
  // BRP = Fosc/(2*N*Fbaud) = 5
  CANSPIInitialize(1,5,3,3,1,Can_Init_Flags);                            // initialize external CANSPI module
  CANSPISetOperationMode(_CANSPI_MODE_CONFIG,0xFF);                      // set CONFIGURATION mode
  CANSPISetMask(_CANSPI_MASK_B1,-1,_CANSPI_CONFIG_XTD_MSG);              // set all mask1 bits to ones
  CANSPISetMask(_CANSPI_MASK_B2,-1,_CANSPI_CONFIG_XTD_MSG);              // set all mask2 bits to ones
  CANSPISetFilter(_CANSPI_FILTER_B2_F4,ID_2nd,_CANSPI_CONFIG_XTD_MSG);   // set id of filter B2_F4 to 2nd node ID

  CANSPISetOperationMode(_CANSPI_MODE_NORMAL,0xFF);                      // set NORMAL mode

  // Set initial data to be sent
  RxTx_Data[0] = 9;

  CANSPIWrite(ID_1st, RxTx_Data, 1, Can_Send_Flags);                          // send initial message

  while(1)
  {                                                                           // endless loop
    Msg_Rcvd = CANSPIRead(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags); // receive message

    if ((Rx_ID == ID_2nd) && Msg_Rcvd) {                                      // if message received check id

      if (RxTx_Data[0] != old_message){                                       // id correct, output data at PORTD
        old_message = RxTx_Data[0];
        for (i = 0; i < 8; i ++){
          DrawLed(i, RxTx_Data[0] % 2);
          RxTx_Data[0] = RxTx_Data[0] / 2;
        }
      }
//      Delay_ms(10);
    }

    port_rd = GPIOD_IDR;                                                      // Read value from PORTB
    if (port_rd != port_rd_temp)                                              // Check for change on PORTB
    {
       port_rd_temp = port_rd;                                                // Save current port value

       CANSPIWrite(ID_1st, &port_rd, 1, Can_Send_Flags);                      // send incremented data back
    }
  }
}
