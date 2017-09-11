#include "GUIControl.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void InitMainTask() {
    //Initialize Variables for Window / Menu changing / Variable changing / Redraw-Stopping
    state = 0;
    WindowChange_Handled = 0;
    DialogOpen_Handled = 1;
    ParameterChange_Handled = 1;
    BlockChange = 0;
    ReDrawStopped = 0;
    Menu_isDynamic = 0;

    LastScreenshot = 0;
    FileCounter = 0;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void MainTask(void) {
    //Create Header
    CreateHeader();

    //Define Menu and Main-Window Handle
    WM_HWIN AktWindow;

    /* OneWire Error Handling */
    if (OneWire_Devices_ERROR) {
        uint8_t OneWire_Devices_ErrorCount, i;
        OneWire_Devices_ErrorCount = OneWire_Devices_ERROR;
        i = 0;

        //Schleife die solange läuft, bis alle Fehler abgearbeitet sind
        while(OneWire_Devices_ErrorCount > 0) {
            OneWire_Devices_ERROR = 1;
            checkOneWireDevice_Parameter(ParameterGroup_OneWire.Para[i]); //OneWire_Devices_ParameterArray.Para[i]);

            if (OneWire_Devices_ERROR > 1) {
                //Ordne dem Parameter ein Gerät zu, Error Count -1 da ein Gerät zugeordnet wurde
                Parameter_Active = ParameterGroup_OneWire.Para[i];//OneWire_Devices_ParameterArray.Para[i];
                BlockChange = 1;
                Edit_OneWireROM();
                OneWire_Devices_ErrorCount--;
            }

            i++;

            //warten bis Edit-Dialog geschlossen wird
            while (BlockChange) {
                BSP_Pointer_Update();
                GUI_Delay(50);
            };

        }
    }


    /************************************************************************************************************************

        Endless loop - Program

    ************************************************************************************************************************/
    while (1) {
        if (!BlockChange) {

            if ((!WindowChange_Handled)) {
                WM_DeleteWindow(AktWindow);

                switch (state) {
                    case 1: AktWindow = CreateMenu(); break;

                    case 2:
                    case 0: AktWindow = Page_Active->Create(); break;
                }

                ChangeHeader();
            }

            if (!ParameterChange_Handled)
            {
                if (state == 1)
                {
                    UpdateParameters();
                }

                Parameter_SaveALLInFlash();
                Parameter_Active->Changed = 1;
                ParameterChange_Handled = 1;
            }

            if (!DialogOpen_Handled)
            {
                BlockChange = 1;
                switch (Parameter_Active->EditType)
                {
                    case EDITTYPE_NOEDIT:       BlockChange = 0;        break;
                    case EDITTYPE_TOGGLE:       Edit_Toggle();          break;
                    case EDITTYPE_KEYPAD:       Edit_Keypad_Hex(0);     break;
                    case EDITTYPE_KEYPAD_HEX:   Edit_Keypad_Hex(1);     break;
                    case EDITTYPE_UPDOWN:       Edit_UpDown();          break;
                    case EDITTYPE_ONEWIREROM:   Edit_OneWireROM();      break;
                }

                DialogOpen_Handled = 1;
            }
        }

        if (SD_Mounted == 1) {
            if (!(BSP_SD_IsDetected())) {
                SD_UnMount();
                SD_Mounted = 0;

            }
        } else {
            if ((BSP_SD_IsDetected())) {
                SD_Test();
                SD_Mounted = 1;
            }
        }

        if (BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_SET) {
            //Save Screenshot
            SaveScreenshot();
        }


        if (!ReDrawStopped)
        {
            if ((state==0) | (state == 2)) {
                Page_Active->Update(&AktWindow);
            }

            BSP_Pointer_Update();
            GUI_Delay(50);
        }
    }
}

static void _WriteByte2Array(U8 DatPixel, void * p) {
    //Write Bytes to Array
    //TempScreenshot = realloc(TempScreenshot, sizeof(uint8_t) * (TempScreenshotByteCounter+1));
    TempScreenshot[TempScreenshotByteCounter] = DatPixel;
    TempScreenshotByteCounter++;

    if (TempScreenshotByteCounter >= 200) {
        UB_Fatfs_WriteBlock(&FileObj,TempScreenshot,TempScreenshotByteCounter,NULL);
        TempScreenshotByteCounter = 0;
    }
}

void SaveScreenshot() {
    if ((BSP_SD_IsDetected()) & (SD_Mounted == 1)) {
        //Speichere Screenshot auf SD
        FATFS_t result;
        //UB_Fatfs_Init();

        char Filename[21] = "";

        sprintf(Filename, "0:/TEST%u.bmp",FileCounter);

        SD_LOCK = 1;
        result = UB_Fatfs_OpenFile(&FileObj, Filename, F_WR_CLEAR); //"0:/Test.bmp"
        if (result != FATFS_OK) {
            GUI_Error_Handler("SD-Card Error", "Öffnen der Datei fehlgeschlagen!");
        }
        SD_LOCK = 0;

        TempScreenshotByteCounter = 0;

        __disable_irq();
        SD_LOCK = 1;
        ReDrawStopped = 1;
        GUI_BMP_SerializeEx(_WriteByte2Array,0,0,480,272,NULL);
        ReDrawStopped = 0;


        UB_Fatfs_WriteBlock(&FileObj,TempScreenshot,TempScreenshotByteCounter,NULL);
        SD_LOCK = 0;
        __enable_irq();

        SD_LOCK = 1;
        result = UB_Fatfs_CloseFile(&FileObj);// mit IRclick_Init() -> FATFS_CLOSE_ERR (FR_DISK_ERR)
        if (result != FATFS_OK) {
            GUI_Error_Handler("SD-Card Error",
                    "Schließen der Datei fehlgeschlagen!");
        }
        SD_LOCK = 0;

        //GUI_MessageBox("Fertig", "Screenshot", 20);

        FileCounter++;
    }

}

void BSP_Pointer_Update(void)
{
    static GUI_PID_STATE TS_State = {0, 0, 0, 0};
    __IO TS_StateTypeDef  ts;
    uint16_t xDiff, yDiff;

    BSP_TS_GetState((TS_StateTypeDef *)&ts);

    if((ts.touchX[0] >= LCD_GetXSize()) ||(ts.touchY[0] >= LCD_GetYSize()) )
    {
        ts.touchX[0] = 0;
        ts.touchY[0] = 0;
    }

    xDiff = (TS_State.x > ts.touchX[0]) ? (TS_State.x - ts.touchX[0]) : (ts.touchX[0] - TS_State.x);
    yDiff = (TS_State.y > ts.touchY[0]) ? (TS_State.y - ts.touchY[0]) : (ts.touchY[0] - TS_State.y);

    if((TS_State.Pressed != ts.touchDetected ) ||
            (xDiff > 20 )||
            (yDiff > 20))
    {
        TS_State.Pressed = ts.touchDetected;
        TS_State.Layer = 0;
        if(ts.touchDetected)
        {
            TS_State.x = LCD_GetXSize() - ts.touchX[0];
            if(ts.touchY[0] < 240)
            {
                TS_State.y = LCD_GetYSize() - ts.touchY[0] ;
            }
            else
            {
                TS_State.y = LCD_GetYSize() - ((ts.touchY[0] * 480) / 450);
            }
            GUI_TOUCH_StoreStateEx(&TS_State);
        }
        else
        {
            GUI_TOUCH_StoreStateEx(&TS_State);
            TS_State.x = 0;
            TS_State.y = 0;
        }
    }
}

void GUI_Error_Handler(char *title, char *text) {
	GUI_SetColor(GUI_WHITE);
	GUI_Clear();
	GUI_MessageBox(text, title, 0);
}

/*************************** End of file ****************************/
