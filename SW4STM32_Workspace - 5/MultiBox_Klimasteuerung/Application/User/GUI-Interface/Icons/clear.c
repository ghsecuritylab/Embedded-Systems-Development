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
* Source file: clear                                                 *
* Dimensions:  32 * 32                                               *
* NumColors:   256                                                   *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmclear;

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
static GUI_CONST_STORAGE GUI_COLOR _Colorsclear[] = {
  0xFFFFFF, 0x000000, 0x000000, 0x6AB9E2,
  0x4383B4, 0x4385BA, 0x5395C4, 0xFEFDFD,
  0x498BBC, 0x72B5DA, 0x6AADD4, 0x69B6E0,
  0x72BCE3, 0x7BC2E5, 0x79BCE0, 0xECEAE9,
  0x1A3B52, 0x356A93, 0x5A9CCA, 0x66B5E0,
  0x0B2D4A, 0x2D638A, 0x3372A9, 0x3C7EB4,
  0x4D90C2, 0x62A3CD, 0x6CB3DC, 0xCAC3BD,
  0x81C5E5, 0xF5F4F3, 0x153A5C, 0x1E415A,
  0x234B69, 0x3C667C, 0x1D5182, 0x20588B,
  0x3C7AAD, 0x407CA9, 0x5BA0CE, 0x61AEDD,
  0x76B9DC, 0x7EC6E8, 0x83C8E9, 0xD3CBC5,
  0xD9D5D2, 0x33312B, 0x113652, 0x193B5A,
  0x111969, 0x14406A, 0x1B4972, 0x224665,
  0x224967, 0x2A5678, 0x345D75, 0x3C687C,
  0x6E6966, 0x7C7A76, 0x225C90, 0x30648B,
  0x377099, 0x38729D, 0x3B76A3, 0x566D81,
  0x457693, 0x3E82BA, 0x4380AD, 0x518CB3,
  0x498CC1, 0x5A99C3, 0x5196C8, 0x619CC2,
  0x5AA5D3, 0x6AA7CB, 0x6BA8C9, 0x62A6D1,
  0x66AAD4, 0x65B8E3, 0x70B7E0, 0x76C2E8,
  0x7DC8EB, 0xB4ABA4, 0x82C7E8, 0xD2CEC9,
  0xDAD4CE, 0xDEDAD6, 0xE3E1DE, 0xE6E5E2,
  0x00002D, 0x003827, 0x003F29, 0x292421,
  0x312C2A, 0x323636, 0x373B3D, 0x3E3E3E,
  0x443C2F, 0x493F33, 0x484137, 0x4B433A,
  0x00154A, 0x032744, 0x092745, 0x18354E,
  0x133E4E, 0x18394F, 0x002157, 0x0F375A,
  0x103351, 0x143550, 0x143B57, 0x1A3C59,
  0x1C3F5C, 0x0D1B65, 0x0D1A6D, 0x161E6E,
  0x111973, 0x0F3B67, 0x103C64, 0x1D2474,
  0x393977, 0x174B5C, 0x20415B, 0x1A4062,
  0x1C486F, 0x124472, 0x174977, 0x174778,
  0x1A4B7A, 0x374A60, 0x32446A, 0x394C7A,
  0x2D5271, 0x2D5D7F, 0x3D5F7B, 0x2F607D,
  0x366075, 0x3A6477, 0x464440, 0x4B4746,
  0x444357, 0x555555, 0x5B5955, 0x65615B,
  0x7B6E5E, 0x455869, 0x476073, 0x556D7F,
  0x596A7A, 0x5D6B79, 0x5D737E, 0x756F6E,
  0x786D6D, 0x606076, 0x777571, 0x787370,
  0x7A7772, 0x74777A, 0x7F7F7F, 0x837059,
  0x817D7A, 0x1D268F, 0x2F3480, 0x323781,
  0x313985, 0x333989, 0x383E8B, 0x2A36B7,
  0x333EBC, 0x1B4F80, 0x294988, 0x3D4082,
  0x3A4384, 0x215481, 0x3B6881, 0x266399,
  0x3944B8, 0x306FA6, 0x3E79A6, 0x434982,
  0x444C89, 0x426C86, 0x4C6E8A, 0x546E86,
  0x527089, 0x48739F, 0x4B7E9D, 0x627483,
  0x61768B, 0x6F7F8B, 0x6E7F8C, 0x5860AF,
  0x4A7EA0, 0x5A62B1, 0x407FB3, 0x6169AF,
  0x6A72BB, 0x3942C9, 0x515CCD, 0x757DCF,
  0x737EE5, 0x3F81B7, 0x74828E, 0x78818A,
  0x4D82A9, 0x5185A3, 0x4D8AB6, 0x5894B6,
  0x5794BC, 0x5995B9, 0x5E9BBB, 0x668DAA,
  0x7D96AD, 0x509ACF, 0x5BABDC, 0x64B4DF,
  0x74B3D6, 0x7DBDDE, 0x7780E2, 0x7781E5,
  0x7E89E8, 0x77C0E5, 0x8A8785, 0x918880,
  0x9C948C, 0x80819A, 0x818F9D, 0x999491,
  0xADA59B, 0xB4A89F, 0x849AAE, 0x879CAE,
  0x87A1B0, 0x9BADBE, 0xBDB6AF, 0xC3BDB7,
  0xC9BEB5, 0xC3BFBB, 0xC2BFBC, 0xCBC0B6,
  0xACBAC1, 0x939BE5, 0x969FF3, 0x99C7E1,
  0x8AD0ED, 0xCCC6C0, 0xC9C6C4, 0xD5D1CD,
  0xCFD4D7, 0xDEDBDA, 0xE8E0DA, 0xCCD0F9,
  0xEAE7E5, 0xEAE8E6, 0xEEECEB, 0xF3EBE6
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palclear = {
  256,  // Number of entries
  1,    // Has transparency
  &_Colorsclear[0]
};

static GUI_CONST_STORAGE unsigned char _acclear[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xA6, 0x83, 0x2E, 0x6F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2, 0xF1, 0xDA, 0xAA, 0x84, 0x59, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xC1, 0xDB, 0xC5, 0xB9, 0x86, 0x81, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xB4, 0xDC, 0xA8, 0xA5, 0xB6, 0xB8, 0x3F, 0x94, 0x95, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xB3, 0xC7, 0xB0, 0x77, 0x82, 0xB7, 0x91, 0xBC, 0xE6, 0xBE, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xC4, 0xC6, 0x30, 0x72, 0x92, 0x3F, 0xD4, 0xE7, 0xE9, 0xE2, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9E, 0x39, 0x9C, 0x97, 0x38, 0x8D, 0x00, 0xA3, 0xC3, 0xC8, 0x74, 0x71, 0x00, 0x00, 0x93, 0xBB, 0xBD, 0xCA, 0xCB, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9D, 0x9A, 0xF6, 0x0F, 0xEE, 0xE3, 0xA0, 0x99, 0xBF, 0xF2, 0xA1, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x9B, 0xF9, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0xFB, 0xA7, 0x73, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x96, 0xFF, 0xFD, 0x2C, 0x0F, 0xFC, 0xFE, 0x1D, 0x07, 0x07, 0xE1, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x21, 0xCD, 0xD6, 0xF3, 0xFA, 0xF5, 0x53, 0x1D, 0x07, 0x07, 0x1D, 0x1D, 0x57, 0x8E, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x37, 0xD2, 0x27, 0x4D, 0x4D, 0xD9, 0x0F, 0x55, 0x55, 0x0F, 0x0F, 0x57, 0x56, 0x56, 0xDE, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x89, 0xB5, 0x0A, 0x27, 0x4D, 0x03, 0x0B, 0x0C, 0x1C, 0xF8, 0x54, 0x54, 0x2C, 0x2C, 0xF7, 0x53, 0xED, 0x8A, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x88, 0x40, 0x09, 0x27, 0x13, 0x03, 0x03, 0x0C, 0x2A, 0x29, 0x1A, 0xF0, 0x2B, 0x2B, 0x2B, 0x1B, 0xEB, 0x1B, 0x38, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x36, 0xBA, 0x4E, 0x03, 0xD7, 0x03, 0x03, 0x03, 0x29, 0x29, 0x52, 0x1A, 0x48, 0xE8, 0xEF, 0x1B, 0x1B, 0x51, 0xEA, 0x8F, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x88, 0xC0, 0x4E, 0x0C, 0x13, 0x03, 0x03, 0x0B, 0xDD, 0x52, 0x52, 0x0D, 0x4C, 0x26, 0xD5, 0xD3, 0xE5, 0xEC, 0xE5, 0xE0, 0x63, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x89, 0x40, 0x1A, 0x0C, 0x0C, 0x03, 0x03, 0x0B, 0x0C, 0x2A, 0x1C, 0x0E, 0x0E, 0x48, 0x12, 0x46, 0x18, 0xCC, 0xDF, 0xE4, 0x90, 0x62, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x21, 0x4E, 0x4E, 0x0D, 0x0C, 0x03, 0x0B, 0x13, 0x29, 0x1C, 0x0E, 0x0E, 0x09, 0x26, 0x46, 0x18, 0x44, 0x05, 0x25, 0x39, 0x9F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x28, 0x50, 0x50, 0x03, 0x0B, 0x13, 0xDD, 0x1C, 0x0E, 0x0E, 0x09, 0x0A, 0x12, 0x18, 0x44, 0x05, 0xC9, 0x41, 0x7D, 0x5E, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1F, 0x15, 0xCF, 0xF4, 0x4F, 0x0B, 0x03, 0x0D, 0x0E, 0x28, 0x09, 0x0A, 0x0A, 0x46, 0x44, 0x05, 0x04, 0xC2, 0xB1, 0x75, 0x14, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x3B, 0x15, 0x15, 0x4A, 0x4F, 0x0C, 0x0D, 0x09, 0x09, 0x0A, 0x4C, 0x19, 0x06, 0x05, 0x05, 0x17, 0xC9, 0x80, 0x76, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x67, 0x1F, 0x3B, 0x11, 0x3B, 0xD1, 0x2A, 0x1A, 0x09, 0x0A, 0x4B, 0x19, 0x12, 0x06, 0x05, 0x17, 0x24, 0x16, 0x31, 0x6B, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x6D, 0x10, 0x35, 0x3C, 0x11, 0x4A, 0x28, 0x0A, 0x4B, 0x19, 0x12, 0x45, 0x06, 0xC9, 0x17, 0x17, 0x22, 0x7E, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x6A, 0x69, 0x85, 0x3D, 0x3C, 0x4A, 0x28, 0x19, 0x12, 0x06, 0x06, 0x06, 0x05, 0x24, 0x16, 0x7F, 0x31, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x79, 0x7A, 0x11, 0x3E, 0x3D, 0x43, 0xD8, 0x06, 0x06, 0x18, 0x08, 0x08, 0x05, 0x22, 0x22, 0x2E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x1F, 0x11, 0xB2, 0x3E, 0x43, 0x19, 0x44, 0x44, 0x05, 0x04, 0x24, 0xA9, 0x32, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x10, 0x35, 0x25, 0x25, 0x47, 0x49, 0x08, 0x04, 0x05, 0x23, 0x23, 0x1E, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x20, 0x25, 0x42, 0xCE, 0x47, 0xD0, 0x16, 0x23, 0x32, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x20, 0x42, 0x04, 0x04, 0x45, 0x3A, 0x3A, 0x1E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x20, 0x42, 0x08, 0x04, 0xAF, 0x7C, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x33, 0x11, 0x08, 0xAD, 0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x33, 0x34, 0x2F, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmclear = {
  32, // xSize
  32, // ySize
  32, // BytesPerLine
  8, // BitsPerPixel
  _acclear,  // Pointer to picture data (indices)
  &_Palclear   // Pointer to palette
};

/*************************** End of file ****************************/
