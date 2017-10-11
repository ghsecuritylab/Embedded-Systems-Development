#ifndef __IRCLICK_H__
#define __IRCLICK_H__

#include "Clickboards_Conf.h"

struct clickBoard * IRclick_Current;

void 		IRclick_Select(struct clickBoard * Board, uint8_t Addr);
void 		IRclick_set(unsigned short channel, uint8_t Val);
uint8_t * 	IRclick_get(unsigned short channel);

void 		IRclick_Init(void);
void 		IRclick_DeInit(void);

void 		IRclick_Send(uint16_t *pulseTimeBuffer, uint16_t length);

uint8_t 	IRclick_IsMessageReady(void);
uint16_t * 	IRclick_GetRXMessagePulseBuffer(void);

#endif // __IRCLICK_H__
