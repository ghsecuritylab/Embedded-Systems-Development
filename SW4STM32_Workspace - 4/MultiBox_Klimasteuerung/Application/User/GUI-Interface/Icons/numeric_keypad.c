/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.32.                      *
*        Compiled Oct  8 2015, 11:58:22                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: numeric_keypad                                        *
* Dimensions:  64 * 64                                               *
* NumColors:   3                                                     *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmnumeric_keypad;

#if 0


/*********************************************************************
*
*  This palette is included for reference only
*  As it is saved as device dependent bitmap without color info.
*  Please note that this bitmap requires the physical palette to be
*  identical to the palette of the display.
*  If this does not work out, please convert your bitmap into a DIB 
*/
/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
static GUI_CONST_STORAGE GUI_COLOR _Colorsnumeric_keypad[] = {
  0xFFFFFF, 0x000000, 0x69380C
};

#endif

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palnumeric_keypad = {
  3,  // Number of entries
  1,  // Has transparency
  NULL
};

static GUI_CONST_STORAGE unsigned char _acnumeric_keypad[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x2A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA0, 0x00, 0x0A, 0x00, 0x00, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xA8, 0x00, 0x2A, 0x80, 0x02, 0xA8, 0x00, 0x2A, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0xAA, 0xA0, 0x0A, 0xAA, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x80, 0x02, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0x80, 0x02, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x2A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmnumeric_keypad = {
  64, // xSize
  64, // ySize
  16, // BytesPerLine
  2, // BitsPerPixel
  _acnumeric_keypad,  // Pointer to picture data (indices)
  &_Palnumeric_keypad   // Pointer to palette
};

/*************************** End of file ****************************/
