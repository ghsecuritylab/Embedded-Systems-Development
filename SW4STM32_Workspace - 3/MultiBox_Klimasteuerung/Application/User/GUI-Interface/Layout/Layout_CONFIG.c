/** \file
 *  \brief
 *
 *
 */

/** \addtogroup GUI-Interface
 *  @{
 */

/** \addtogroup Layout
 *  @{
 */


#include "Layout_CONFIG.h"

GUI_CONST_STORAGE GUI_COLOR _ColorsHeader_Normal[] =
{
    0xFFFFFF, IAV_BLAU_3
};
GUI_CONST_STORAGE GUI_COLOR _ColorsHeader_Pressed[] =
{
    0xFFFFFF, GUI_BLACK
};
GUI_CONST_STORAGE GUI_COLOR _ColorsDataType[] =
{
    0xFFFFFF, GUI_BLACK
};
GUI_CONST_STORAGE GUI_COLOR _ColorsIcon[] =
{
    0xFFFFFF, GUI_BLACK
};

GUI_CONST_STORAGE GUI_LOGPALETTE _PalHeader_Normal =
{
    2,  // Number of entries
    1,  // Has transparency
    &_ColorsHeader_Normal[0]
};
GUI_CONST_STORAGE GUI_LOGPALETTE _PalHeader_Pressed =
{
    2,  // Number of entries
    1,  // Has transparency
    &_ColorsHeader_Pressed[0]
};
GUI_CONST_STORAGE GUI_LOGPALETTE _PalDataType =
{
    2,  // Number of entries
    1,  // Has transparency
    &_ColorsDataType[0]
};
GUI_CONST_STORAGE GUI_LOGPALETTE _PalIcon =
{
    2,  // Number of entries
    1,  // Has transparency
    &_ColorsIcon[0]
};

int Dialog_DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    GUI_CONST_STORAGE GUI_BITMAP * Bmp;
    int xPos, yPos;

    switch (pDrawItemInfo->Cmd)
    {
    case WIDGET_ITEM_DRAW_TEXT:
        //Formatiere Text und führe anschließend die normale Draw-Routine aus
        BUTTON_SetTextColor(pDrawItemInfo->hWin, BUTTON_CI_UNPRESSED, IAV_BLAU_3);
        BUTTON_SetFont(pDrawItemInfo->hWin, TOGGLE_BUTTON_FONT);
        break;

    case WIDGET_ITEM_DRAW_BITMAP:
        //Zeichne Bitmap zentriert, anschließend KEIN Aufruf der normalen Draw-Routine
        Bmp = BUTTON_GetBitmap(pDrawItemInfo->hWin, BUTTON_BI_UNPRESSED);

        if(Bmp != NULL)
        {
            xPos =  ((pDrawItemInfo->x1 - pDrawItemInfo->x0) - Bmp->XSize) / 2 + pDrawItemInfo->x0;
            yPos =  ((pDrawItemInfo->y1 - pDrawItemInfo->y0) - Bmp->YSize) / 2 + pDrawItemInfo->y0;

            GUI_DrawBitmap(Bmp, xPos, yPos);
        }

        return 0;
        break;

    }
    return BUTTON_DrawSkinFlex(pDrawItemInfo);
}

int Header_DrawSkinFlex_BUTTON(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    GUI_CONST_STORAGE GUI_BITMAP * Bmp;
    char buffer[20];
    int xPos, yPos;
    GUI_RECT Rect;

    switch (pDrawItemInfo->Cmd)
    {


    case WIDGET_ITEM_DRAW_TEXT:

        Bmp = BUTTON_GetBitmap(pDrawItemInfo->hWin, BUTTON_BI_UNPRESSED);

        if(Bmp != NULL)
        {
            //Bitmap vorhanden
            GUI_SetFont(HEADER_FONT_BITMAP);
            Rect.y0 = pDrawItemInfo->y0 + 16;
            Rect.y1 = pDrawItemInfo->y1 + 16;

        }
        else
        {
            //Kein Bitmap vorhanden
            GUI_SetFont(HEADER_FONT_NORMAL);
            Rect.y0 = pDrawItemInfo->y0;
            Rect.y1 = pDrawItemInfo->y1;
        }

        Rect.x0 = pDrawItemInfo->x0;
        Rect.x1 = pDrawItemInfo->x1;

        GUI_SetTextMode(GUI_TM_TRANS);

        BUTTON_GetText(pDrawItemInfo->hWin, buffer, sizeof(buffer));

        if (BUTTON_IsPressed(pDrawItemInfo->hWin))
        {
            //Pressed
            GUI_SetColor(GUI_BLACK);
        }
        else
        {
            //Normal
            GUI_SetColor(IAV_BLAU_3);
        }

        GUI_DispStringInRectWrap(buffer, &Rect, GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_CHAR);

        return 0;
        break;

    case WIDGET_ITEM_DRAW_BITMAP:


        Bmp = BUTTON_GetBitmap(pDrawItemInfo->hWin, BUTTON_BI_UNPRESSED);
        BUTTON_GetText(pDrawItemInfo->hWin, &(buffer[0]), 20);

        if(Bmp != NULL)
        {
            xPos =  ((pDrawItemInfo->x1 - pDrawItemInfo->x0) - Bmp->XSize) / 2 + pDrawItemInfo->x0;
            yPos =  ((pDrawItemInfo->y1 - pDrawItemInfo->y0) - Bmp->YSize) / 2 + pDrawItemInfo->y0;

            if (buffer[0] != 0x0)
            {
                //Wenn Bmp und Text vorhanden ist, Bild nach oben verschieben
                yPos -= 8;
            }

            if (BUTTON_IsPressed(pDrawItemInfo->hWin))
            {
                //Pressed
                DrawBitmapPalette(Bmp, &_PalHeader_Pressed,xPos,yPos);
            }
            else
            {
                //Normal
                DrawBitmapPalette(Bmp, &_PalHeader_Normal,xPos,yPos);
            }

        }

        return 0;
        break;


    }
    return BUTTON_DrawSkinFlex(pDrawItemInfo);
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
int Dialog_ChangeSkin_Button()
{
    BUTTON_SKINFLEX_PROPS Props;


    BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);
    Props.aColorFrame[0] = IAV_BLAU_3;
    Props.aColorFrame[1] = IAV_BLAU_3;
    Props.aColorFrame[2] = IAV_BLAU_3;
    Props.aColorUpper[0] = GUI_WHITE;
    Props.aColorUpper[1] = GUI_WHITE;
    Props.aColorLower[0] = GUI_WHITE;
    Props.aColorLower[1] = GUI_WHITE;
    Props.Radius = 2;
    BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);
    BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);

    Props.aColorUpper[0] = IAV_BLAU_1_60;
    Props.aColorUpper[1] = IAV_BLAU_1_60;
    Props.aColorLower[0] = IAV_BLAU_1_60;
    Props.aColorLower[1] = IAV_BLAU_1_60;
    BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);

    Props.aColorUpper[0] = GUI_DARKGRAY;
    Props.aColorUpper[1] = GUI_DARKGRAY;
    Props.aColorLower[0] = GUI_DARKGRAY;
    Props.aColorLower[1] = GUI_DARKGRAY;
    Props.aColorUpper[0] = GUI_GRAY;
    Props.aColorUpper[1] = GUI_GRAY;
    Props.aColorLower[0] = GUI_GRAY;
    Props.aColorLower[1] = GUI_GRAY;
    BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_DISABLED);

return 1;
}

/** \brief
 *
 *
 *  \param
 *  \retval
 */
int Dialog_ChangeSkin_Scrollbar()
{
    SCROLLBAR_SKINFLEX_PROPS Props;

    SCROLLBAR_GetSkinFlexProps(&Props, SCROLLBAR_SKINFLEX_PI_UNPRESSED);
    Props.aColorFrame[0] = GUI_WHITE;
    Props.aColorFrame[1] = IAV_BLAU_1_60;
    Props.aColorFrame[2] = GUI_WHITE;
    Props.aColorUpper[0] = IAV_BLAU_1_60;
    Props.aColorUpper[1] = IAV_BLAU_1_60;
    Props.aColorLower[0] = IAV_BLAU_1_60;
    Props.aColorLower[1] = IAV_BLAU_1_60;
    Props.aColorShaft[0] = GUI_WHITE;
    Props.aColorShaft[1] = GUI_WHITE;
    Props.ColorArrow = GUI_BLACK;
    Props.ColorGrasp = GUI_WHITE;
    SCROLLBAR_SetSkinFlexProps(&Props, SCROLLBAR_SKINFLEX_PI_UNPRESSED);
    SCROLLBAR_SetSkinFlexProps(&Props, SCROLLBAR_SKINFLEX_PI_PRESSED);

    Props.aColorUpper[0] = IAV_BLAU_1;
    Props.aColorUpper[1] = IAV_BLAU_1;
    Props.aColorLower[0] = IAV_BLAU_1;
    Props.aColorLower[1] = IAV_BLAU_1;
    SCROLLBAR_SetSkinFlexProps(&Props, SCROLLBAR_SKINFLEX_PI_PRESSED);

return 1;
}

void DrawBitmapPalette(GUI_CONST_STORAGE GUI_BITMAP * Bmp, GUI_CONST_STORAGE GUI_LOGPALETTE * Pal, int x, int y) {

    GUI_BITMAP BmpTemp =
            {
                Bmp->XSize, // xSize
                Bmp->YSize, // ySize
                Bmp->BytesPerLine, // BytesPerLine
                Bmp->BitsPerPixel, // BitsPerPixel
                Bmp->pData,  // Pointer to picture data (indices)
                Pal
            };

    GUI_DrawBitmap(&BmpTemp, x, y);
}
