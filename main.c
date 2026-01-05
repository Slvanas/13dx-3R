#include "stc15f2k60s2.h"
#include "init.h"
#include "leds.h"
#include "timer.h"
#include "key.h"
#include "Exint.h"
#include "eep.h"
#include "Uart.h"
#include "Qudong.h"
#include "Veiw.h"
#include "Ws.h"
#if(tde==5)
#include "adc.h"
#include "pwm.h"
#endif


//#define 0    0 
extern unsigned char  leds_buffer[6] ;
extern unsigned char xdata ppvv;
extern unsigned char xdata th[21];
extern unsigned char key[4];

 extern unsigned char xdata flagg;




void main()
{

	LEDS_Init();	//设置推挽
	TIM0_Init();	//定时器


	ExintInit();
	#if(tde==5)
	InitADC();
	PWMn_init(40);
	#endif
	EA=1;
	eepread(th,21);
	UartInit(); 
	 if(TorNULL==0)
		{
	 leds_buffer[0]=18;
	 leds_buffer[1]=18;
	 leds_buffer[2]=18;
	 leds_buffer[3]=18;
	 leds_buffer[4]=18;
	 leds_buffer[5]=18;
	 }
	 else
	 {
	  leds_buffer[0]=28;
	 leds_buffer[1]=28;
	 leds_buffer[2]=28;
	 leds_buffer[3]=28;
	 leds_buffer[4]=28;
	 leds_buffer[5]=28;	
	 }
	 	if((th[17]<70)||(th[17]>90))
	{
		th[17]=80;
	}
	if((th[18]<140)||(th[18]>180))
	{
		th[18]=160;
	}
	if((th[19]<70)||(th[19]>90))
	{
		th[19]=80;
	}
	if((th[20]<120)||(th[20]>160))
	{
		th[20]=134;
	}
	 delay_ms(2000);
	key[0]=0;
	key[1]=0;
	key[2]=0;
	key[3]=0;
	while(1)
	{
		if(ppvv==0)
		{  
			wsdup();
		}
		 keyonview();
		 wsdcl();
	}
}

