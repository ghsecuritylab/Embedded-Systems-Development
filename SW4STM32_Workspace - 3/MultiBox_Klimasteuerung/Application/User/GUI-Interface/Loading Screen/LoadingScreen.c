/** \file
 *  \brief
 *
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup LoadingScreen
 *  @{
 */

#include "LoadingScreen.h"

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void _cbDialogLoadingScreen(WM_MESSAGE * pMsg)
{
    WM_HWIN      hItem;

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:

        hItem = WM_GetDialogItem(pMsg->hWin, ID_LOADINGSCREEN_PROGBAR_0);
        PROGBAR_SetFont(hItem, GUI_FONT_D32);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_LOADINGSCREEN_IMAGE_0);
        IMAGE_SetBitmap(hItem, &bmIAV);

        break;
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
uint8_t UpdateLoadingScreen(WM_HWIN Scrollbar, WM_HWIN Text, char * UpdateText, uint8_t UpdateValue)
{
    TEXT_SetText(Text, UpdateText);
    PROGBAR_SetValue(Scrollbar,UpdateValue + 25);
    GUI_Delay(150);

    return UpdateValue + 16;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
void Init_GUI(WM_HWIN hWin)
{
    WM_HWIN hItem_Scrollbar, hItem_Text;

    hItem_Scrollbar = WM_GetDialogItem(hWin, ID_LOADINGSCREEN_PROGBAR_0);
    hItem_Text = WM_GetDialogItem(hWin, ID_LOADINGSCREEN_TEXT_0);

    {
        uint8_t LoadingProgress = 0;

        //Initialize Menu
        LoadingProgress = UpdateLoadingScreen(hItem_Scrollbar,hItem_Text, "Initialisiere Menustrukturen",LoadingProgress);
        Firmware_Init_Menus();
        Project_Init_Menus();

        //Init Main Windows
        LoadingProgress = UpdateLoadingScreen(hItem_Scrollbar,hItem_Text, "Initialisiere Main-Windows",LoadingProgress);
        Firmware_Init_Pages();
        Project_Init_Pages();

        //Initialize MainTask
        LoadingProgress = UpdateLoadingScreen(hItem_Scrollbar,hItem_Text, "Initialisiere Gui-Control",LoadingProgress);
        InitMainTask();

        //Initialize TouchScreen
        LoadingProgress = UpdateLoadingScreen(hItem_Scrollbar,hItem_Text, "Initialisiere Touchscreen",LoadingProgress);
        BSP_TS_Init(480,272);

        Dialog_ChangeSkin_Button();
        Dialog_ChangeSkin_Scrollbar();

        /* Activate the use of memory device feature */
        WM_SetCreateFlags(WM_CF_MEMDEV);
    }


}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
WM_HWIN CreateLoadingScreen(void)
{
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialogLoadingScreen, WM_HBKWIN, 0, 0);

    Init_GUI(hWin);

    return hWin;
}
