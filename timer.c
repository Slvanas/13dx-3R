#include "stc15f2k60s2.h"
#include "init.h"
#include "timer.h"
#include "leds.h"
#include "key.h"


unsigned char eetime=0; 
unsigned int xdata handctrltime=0;
unsigned char xdata handctrlcnt=0;
extern unsigned int muentimeout;
extern unsigned char timeout;
 extern unsigned char xdata 	 onelinetime;
  extern unsigned char xdata 	 onelinetime2;
    extern unsigned int xdata thouttime1;
extern unsigned int xdata thouttime2;
extern unsigned int xdata showalltime;
extern unsigned char xdata showerrtime;

extern unsigned char xdata showtime=0;
 unsigned char xdata flagg=0;
void TIM0_Init()
{
   AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xAE;		//设置定时初值
	TH0 = 0xFB;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;
    EA = 1;

}

void TIM0_Isr() interrupt 1
{	



   	if(onelinetime<250)onelinetime++;
	if(onelinetime2<250)onelinetime2++;
	if(timeout>0)
    {timeout--;
    }
 	eetime++;

 	if(eetime>250)
	{
		eetime=0;
	   if(muentimeout>0)muentimeout--;
	   if(thouttime1>0) thouttime1--;
		if(thouttime2>0) thouttime2--;
        
        handctrlcnt++;  //手动30min返回
        if(handctrlcnt>=60)
        {
            handctrlcnt = 0;
            if(handctrltime>0)handctrltime--;        
        }

			showalltime++;
		if(showalltime>1000)showalltime=0;
		 showerrtime++;
		if(showtime>0)showtime--;
		
	}


	 	
		LEDS_Refresh();
	//KEY_Scanf();
}