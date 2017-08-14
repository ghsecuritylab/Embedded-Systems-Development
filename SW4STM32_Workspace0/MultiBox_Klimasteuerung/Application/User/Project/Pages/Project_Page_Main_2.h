#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Parameter.h"
#include "DIALOG.h"
#include "LISTBOX.h"
#include "Layout_Config.h"
#include "GUIControl.h"

#define ID_WINDOW_0 	(GUI_ID_USER + 0x00)
#define ID_GRAPH_0 		(GUI_ID_USER + 0x01)
#define ID_BUTTON_0		(GUI_ID_USER + 0x02)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Main2[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 52, 480, 220, 0, 0x0, 0 },
	{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 0, 0, 480, 220, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "i", ID_BUTTON_0, 452, 3, 25, 30, 0, 0x0, 0 },
};

void _cbDialog_Main2(WM_MESSAGE * pMsg);
void UpdateMain2(WM_HWIN * MainWindow);
WM_HWIN CreateMain2(void);
void Graph_AddValues(int16_t *val);


