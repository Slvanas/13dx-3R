

#include "stc15f2k60s2.h"

#define KEY0_CLICK 	0x00
#define KEY1_CLICK 	0x01
#define KEY2_CLICK 	0x02
#define KEY3_CLICK 	0x03

#define KEY0_HOLD		0x04
#define KEY1_HOLD		0x05
#define KEY2_HOLD		0x06
#define KEY3_HOLD		0x07

#define KEYS_IDLE		0xFF

sbit KEYIN = P1^7;


 void keyonview(void);
void SW(void);
