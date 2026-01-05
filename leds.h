#ifndef __LEDS_H
#define __LEDS_H

#include "stc15f2k60s2.h"

#define LEDS_DX_PORT P0
#define LEDS_WX_PORT P2

#define LED0			0x01
#define LED1			0x02
#define LED2			0x04
#define LED3			0x08

#define LEDS_BIT0 0x01
#define LEDS_BIT1 0x02
#define LEDS_BIT2 0x04
#define LEDS_BIT3 0x08
#define LEDS_BIT4 0x10
#define LEDS_BIT5 0x20
#define LEDS_BIT6 0x40
#define LEDS_BIT7 0x80

#define LEDS_FLASH_ON		0
#define LEDS_FLASH_OFF	1

extern unsigned char leds_buffer[6];

void LEDS_Init();
void LEDS_Refresh();
void LEDS_SetFlash(unsigned char bits, unsigned char fun);

void LED_ON(unsigned char led);
void LED_OFF(unsigned char led);

#endif
