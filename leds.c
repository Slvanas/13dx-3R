#include "leds.h"
#include "key.h"
#include "Qudong.h"

code unsigned char leds_tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90, //无小数点
							   0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,	//有小数点
							   0xC6,0x89,0x8C,0xDC,0xE3,0x86,0xAF,0xBF,0xff,0xc7,0x88,0xa1,0x83,0xe3,0XA3};
							  //20   21	  22   23	 24  25  26   27	 28   29   30    31   32   33  34
							  //C,   H,   P,  上限, 下限,  E   R  －    空    L     A    d     b    u	o
unsigned char  xdata led_status = 0x00;
unsigned char  xdata led_status2 = 0x00;
unsigned char  leds_buffer[6] = {0, 0, 0, 0, 0, 0};
unsigned char xdata leds_flash_flag = 0x00;
unsigned char key[4];
unsigned int xdata keynum[4];

unsigned char c1H,c1L,h1H,h1L,p1H,p1L;
extern unsigned int xdata	muentimeout;

 unsigned char j = 0;
 unsigned int cot = 0;

unsigned char ti=0;

//code unsigned char code leds_tab2[] = {};	 //C,   H,   P,  1,  上限,下限



void LEDS_Init()
{
	P1M0 = 0x1f;
	P1M1 = 0;
	P0M0 = 0xff;
	P0M1 = 0x00;
	P1 = 0xff;
	P0 = 0x00;
	P2 = 0x00;
	P4=0;
	P2M0=0x00;//00000000
	P2M1=0x00;//00000000
	P4M0=0xff;
	P4M1=0x00;
}

void showpp(unsigned char tempbu)
{
	LEDS_DX_PORT=0x00;  
	LEDS_WX_PORT=~(1<<tempbu); 
	LEDS_DX_PORT=~leds_tab[leds_buffer[tempbu]]; 
}
void showkey(unsigned char tempbu)
{
	if(KEYIN==0)
	{
		if(keynum[tempbu]<3000)keynum[tempbu]++;
		if(keynum[tempbu]==30)
		{
			muentimeout=1200;
		}
		if(keynum[tempbu]>=30)
		{
		
			
			if(keynum[tempbu]>=2000&&keynum[tempbu]<2500)
			{
			//	keynum[tempbu]=2000;
				key[tempbu]=2;	
			}
		
		}
	}
	else
	{
		if((keynum[tempbu]>=30)&&(keynum[tempbu]<2000))
		{
			key[tempbu]=1;
			muentimeout=1200;
		}
	   	 keynum[tempbu]=0;
		 if(key[tempbu]==2)
	   	 key[tempbu]=0;
	   
	} 
}


void LEDS_Refresh()
{

  switch(j)
  {
    case 0:
	
	 showpp(0);
	 showkey(0);
		j++	; 	
		   

	break;
    case 1:
	 showpp(1); 
	 j++; 
	 
	 break;
    case 2: 
	 showpp(2);
	 showkey(1);
		j++	; 	
		   
	 
	 break;  
    case 3:
 		showpp(3);
	 	if(ti==0)
		{
			ti=1;
		}
		else
		{
			ti=0;
		j++	; 	
		 }  
	   break;
    case 4:
	 showpp(4);
	 showkey(2);
	if(ti==0)
		{
			ti=1;
		}
		else
		{
			ti=0;
		j++	; 	
		 }  

	 
	 break;
    case 5: 
	 showpp(5);
	
	if(ti==0)
		{
			ti=1;
		}
		else
		{
			ti=0;
		j++	; 	
		 }  	
		   
	break;
    case 6: 
// showpp(6);
LEDS_DX_PORT=0;
LEDS_WX_PORT=~LEDS_BIT6; 
	
	j++;
	LEDS_DX_PORT=led_status;   
	 showkey(3);
		
		   
	break;
	 case 7: 
	 LEDS_DX_PORT=0;
	LEDS_WX_PORT=~LEDS_BIT7;

	j++;
	LEDS_DX_PORT=led_status2;   
		
		   
	break;
    default: j=0; break; 
	}
}