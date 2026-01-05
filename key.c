#include "key.h"
#include "Veiw.h"
#include "eep.h"
#include "stc15f2k60s2.h"
#include "adc.h"
#include "qudong.h"
#include "init.h"
#include  "Uart.h"


//code unsigned char meum0[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,0};
#if (xxh==1)
#if(tde==5)
code unsigned char meum0[]={1,2,3,4,5,6,0,0,0,0,0,0,13,14,15,16,0};
#else
code unsigned char meum0[]={1,2,3,4,5,6,0,0,0,0,0,0,13,14,0,0,0};
#endif
#endif		
#if(xxh==2)
code unsigned char meum0[]={1,2,0,0,5,6,0,0,0,0,0,0,13,14,0,0,0};
#endif 
#if(xxh==3)
code unsigned char meum0[]={0,0,3,4,0,0,0,0,0,0, 0, 0,13,14,0,0,0};
#endif 	
#if(xxh==4)
#if(tde==1)
code unsigned char meum0[]={1,2,3,4,5,6,7,8,9,10, 0, 0,0,0,0,0,0};
#else
 #if(tda==1)
code unsigned char meum0[]={1,2,3,4,5,6,7,8,9,10, 11, 12,0,0,0,0,0};
#else
code unsigned char meum0[]={1,2,3,4,0,0,7,8,9,10, 0, 0,0,0,0,0,0};
#endif
#endif
#endif	
#if(xxh==5)
code unsigned char meum0[]={1,2,0,0,0,0,7,8,0,0, 0, 0,0,0,0,0,0};
#endif
#if(xxh==6)
code unsigned char meum0[]={0,0,3,4,0,0,0,0,9,10, 0, 0,0,0,0,0,0};
#endif
#if(xxh==7)||(xxh==8)||(xxh==9)
code unsigned char meum0[]={0,0,3,4,0,0,0,0,9,10, 0, 0,0,0,0,0,0};
#endif

extern unsigned char xdata thhotctrl1;  
extern unsigned char xdata thsdctrl1;
extern unsigned char xdata thhotctrl2;
extern unsigned char xdata thsdctrl2;
extern unsigned char xdata thfatctrl1;
extern unsigned char xdata thfatctrl2;
extern unsigned char xdata key[4];
extern unsigned int xdata handctrltime;
extern unsigned int xdata showalltime;
extern unsigned char showjj;

extern unsigned char th[21];
extern unsigned char xdata ppvv;
extern unsigned char leds_buffer[6];
extern unsigned char xdata thfathandctrl1;
extern unsigned char xdata thfathandctrl2;
extern unsigned char led_status;
 unsigned int xdata muentimeout=0;
 unsigned int xdata shownum=0;
 unsigned char xdata meums=0;
unsigned char ppvvshow1=0;
unsigned char eepctrl=0;
unsigned char keyon1,keyon2,keyon3,keyon4;
unsigned char showcccc=0;
extern unsigned char  keynum[4];

extern unsigned int xdata wddata;
extern unsigned int xdata pldata;

void SW(void)
{	
		
		  if(key[1]==1)
		  {
		  		handctrltime=1200;
		   	 	thhotctrl1=1;
				thsdctrl1=1;	
				thhotctrl2=1;
				thsdctrl2=1;	
				
		 }
		  if(key[1]==2)
		  {
		  		handctrltime=0;
		   	 	thhotctrl1=0;
				thsdctrl1=0;	
				thhotctrl2=0;
				thsdctrl2=0;	
		 }
		
		
}


void keyonview(void)
{
	 if(muentimeout==0)
	 {
		 if(eepctrl==1)
		 {
			 eepctrl=0;
			 eepread(th,21);
			 UartInit();
		 }
		 ppvv=0;
	 }
  	
	if(ppvv==0)
	{
	  // shownum++;
	  // if(shownum>30)
	   
	  
	   	shownum=0;
		if(TorNULL==0)
		{
	   		showwsd();
		}
		#if((xxh==4)||(xxh==5)||(xxh==6))
				
		if(TorNULL==0)
		{
			 	if(showalltime<500) led_status|=0x04;
				else  led_status&=0xFB;
				if(showalltime>500)  led_status|=0x80;
				else  led_status&=0x7F;
			  #if (tda==1)
				if(showalltime<500) led_status|=0x08;
				else  led_status&=0xF7;
				if(showalltime>500)  led_status|=0x10;
				else  led_status&=0xEF;
			  #endif			
		}
		#endif
	   
		if(key[0]==1)
		{
			if(keyon1!=1)
			{
				keyon1=1;
			
			
					
			}
			key[0]=0;	
		}
		if(key[0]==2)
		{
			if(keyon1!=2)
			{
				keyon1=2;
				ppvv=1;
				eepctrl=1;
				//if(showjj==0||showjj>14)
				showjj=1;
				
				meums=0;
				showcccc=0;
				#if((xxh==3)||(xxh==6))
				showjj=3;
			   meums=2;
			   #endif
//				setok=0;
					
			}
				   
		}
		if(key[0]==0)
		{
			keyon1=0;
		}
		#if(tde==5)
		if(key[2]==2&&key[3]==2)
		{
			ppvv=2;
		}
		#endif
  	if(key[1]==1)
	 {
			if(keyon4!=1)
			{
				keyon4=1;
				SW();	
			}
			key[1]=0;	
		}
		if(key[1]==2)
		{
			if(keyon4!=2)
			{
				keyon4=2;
			 SW();
			 }
		}
		if(key[1]==0)
		{
			keyon4=0;
		}
	key[1]=0;
	
		if(key[2]==1)
		{
			key[2]=0;
			if(showalltime>500)showalltime=0;
			else
			{
				showalltime=500;
			}
		}
		if(key[3]==1)
		{
			key[3]=0;
			if(showalltime>500)showalltime=0;
					else
					{
						showalltime=500;
					}
			
		}	
	}
	else
	{
		if(ppvv==2)
		{
			if(key[0]==2)
			{
				ppvv=0;
				key[0]=0;
				keynum[0]=0;
				eepwrite(th,21)	 ;
			}
		}
	}
	if(ppvv==1)
	{
//		led_status&=0xF7;
//		led_status&=0xEF;
		if(key[0]==1)
		{
			if(keyon1==0)
			{
			showcccc=0;
				keyon1=1;
				//--------------------------------
			TTT1:	meums++;
				if(meums>=16)
					{
						meums=0;
						ppvv=0;	
						eepwrite(th,21)	 ;
					}
				showjj=meum0[meums];
				if(showjj==0||showjj>16)goto TTT1;
				//----------------------------------
			}
			key[0]=0;		   
		}
		else
		{
			if(key[0]==0)
			{
				keyon1=0;
			}
		}
		
		if(key[1]==1)
		{
			if(keyon4==0)
			 {	
				keyon4=1;
			//-----------------------------------------			
			  showcccc=0;

			TTT2:	if(meums==0)
			{
				meums=0;
						ppvv=0;	
						eepwrite(th,21)	 ;

			}
				#if((xxh==3)||(xxh==5))
			   if(meums<2)
					{
						meums=0;
								ppvv=0;	
								eepwrite(th,21)	 ;
		
					}
			   #endif
				if(meums>16)meums=16;
				meums--;
				showjj=meum0[meums];
				if(showjj>16||showjj==0)goto TTT2;
			//-----------------------------------------
			}
			key[1]=0;
		}
		else
		{
			if(key[1]==0)
			{
				keyon4=0;
			}
		}		

		if(muentimeout>1080)
		{
			showkeyview(showjj);
		}
		else
		{
			if((muentimeout%20)>10)
			{
					showkeyview(showjj);
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
		}
			
		
			if(key[3]==1)
			{		
			  if(keyon2==0)
			   {
			   	 #if((xxh==1)||(xxh==4))			
				 showcccc=1;
				 #endif
			   	   if( showcccc==1)
				   {
				   		keyon2=1;
						if(showjj==13)
						{
							 th[13]-- ; 
						}
						else
						{
							if(showjj==14)
							{
	
							   	 if(th[14]==0)
								 {
							 		th[14]=1;
									TL1 = 0xE0;		//设定定时初值	  9600
									TH1 = 0xFE;		//设定定时初值
								 }
								 else
								 {
									th[14]=0;
									TL1 = 0xC0;		//设定定时初值	 4800
									TH1 = 0xFD;		//设定定时初值
								 }
							}
							else
							{
								if(th[showjj]>0)
								{
								th[showjj]--	;
								}
							}
						}
					}
					
				 showcccc=1;
				 
				}
				key[3]=0;
			}
			else
			{
				keyon2=0;
			}
		
			if(key[2]==1)
			{
			  
			  if(keyon3==0)
			   {
			   
					#if((xxh==1)||(xxh==4))			
				 showcccc=1;
				 #endif
			   if( showcccc==1)	
			  {
			   	keyon3=1;	
				if(showjj==13)
					{
						 th[13]++ ; 
					}
					else
					{
						if(showjj==14)
						{
						    if(th[14]==0)
							 {
							 		th[14]=1;
								TL1 = 0xE0;		//设定定时初值	  9600
								TH1 = 0xFE;		//设定定时初值
							 }
							 else
							 {
							 	    th[14]=0;
									TL1 = 0xC0;		//设定定时初值	 4800
									TH1 = 0xFD;		//设定定时初值
							 }
						}
						else
						{

							th[showjj]++	;
						}
					}
					}
			
					
				 showcccc=1;
				 
				}
				key[2]=0;
			}
			else
			{
				keyon3=0;
			}
			
			shownum++;
	   if(shownum>30)
	   {
	   	shownum=0;
			if(key[3]==2)
			{
		
			if( showcccc==1)
			{
				delay_ms(60);
				if(showjj==13)
					{
						if(th[13]>0)
							{
						 th[13]-- ;
							}
						if(th[13]>0)
							{
					//	 th[13]-- ;
							}
					}
					else
					{
						if(showjj==14)
						{

						    if(th[14]==0)
							 {
							 		th[14]=1;
									TL1 = 0xE0;		//设定定时初值	  9600
									TH1 = 0xFE;		//设定定时初值
							 }
							 else
							 {
							 	    th[14]=0;
									TL1 = 0xC0;		//设定定时初值	 4800
									TH1 = 0xFD;		//设定定时初值
							 }
						}
						else
						{
							if(th[showjj]>0)
							{
							th[showjj]--	;
							}
							if(th[showjj]>0)
							{
						//	th[showjj]--	;
							}
						}
					}
					}
					 showcccc=1;
			}
			if(key[2]==2)
			{
			delay_ms(60);
			if( showcccc==1)
			{
				if(showjj==13)
					{
						 th[13]++ ; 
					//	th[13]++ ;
					}
					else
					{
						if(showjj==14)
						{

						     if(th[14]==0)
							 {
							 		th[14]=1;
									TL1 = 0xE0;		//设定定时初值	  9600
									TH1 = 0xFE;		//设定定时初值
							 }
							 else
							 {
							 	    th[14]=0;
									TL1 = 0xC0;		//设定定时初值	 4800
									TH1 = 0xFD;		//设定定时初值
							 }
						}
						else
						{

							th[showjj]++	;
						//	th[showjj]++	;
						}
					}
				}
				 showcccc=1;
			}
		}
		//	showkeyview(showjj);
					
	}
	#if(tde==5)
	
	if(ppvv==2)
	{
		 //PWMOUT(bzvv);
		if(key[0]==1)
		{
			
			if(keyon1==0)
			{
				keyon1=1;
				ppvvshow1++;
				if(ppvvshow1>=4)ppvvshow1=0;
			}
			key[0]=0;	   
		}
		else
		{
		
				keyon1=0;		
		}
			
		if( ppvvshow1==0)
		{
			pldata=0;
			//wddata=100;
		
			leds_buffer[0]=0;
			leds_buffer[1]=0;
			leds_buffer[2]=1;
			leds_buffer[3]=th[17]%1000/100;
			leds_buffer[4]=th[17]%100/10;
			leds_buffer[5]=th[17]%10;
			
			if(key[2]==1)
				{		
					if(keyon2==0)
					 {
							keyon2=1;
							th[17]++;

					}
					key[2]=0;
				}
				else
				{
					keyon2=0;
				}
			
				if(key[3]==1)
				{
					if(keyon3==0)
					 {	
						 keyon3=1;
						if(th[17]>0)
						 th[17]--;
					}
					key[3]=0;
				}
				else
				{
					keyon3=0;
				}

			}
		if( ppvvshow1==1)
		 {
			pldata=900;
			//wddata=100;
		
			leds_buffer[0]=0;
			leds_buffer[1]=0;
			leds_buffer[2]=2;
			leds_buffer[3]=th[18]%1000/100;
			leds_buffer[4]=th[18]%100/10;
			leds_buffer[5]=th[18]%10;
			
			if(key[2]==1)
				{		
					if(keyon2==0)
					 {
							keyon2=1;
							th[18]++;

					}
					key[2]=0;
				}
				else
				{
					keyon2=0;
				}
			
				if(key[3]==1)
				{
					if(keyon3==0)
					 {	
						 keyon3=1;
							if(th[18]>0)
						 th[18]--;
					}
					key[3]=0;
				}
				else
				{
					keyon3=0;
				}

		}
		if( ppvvshow1==2)
		{
		//	pldata=0;
			wddata=100;
		
			leds_buffer[0]=0;
			leds_buffer[1]=0;
			leds_buffer[2]=3;
			leds_buffer[3]=th[19]%1000/100;
			leds_buffer[4]=th[19]%100/10;
			leds_buffer[5]=th[19]%10;
			
			if(key[2]==1)
				{		
					if(keyon2==0)
					 {
							keyon2=1;
							th[19]++;

					}
					key[2]=0;
				}
				else
				{
					keyon2=0;
				}
			
				if(key[3]==1)
				{
					if(keyon3==0)
					 {	
						 keyon3=1;	
						 th[19]--;
					}
					key[3]=0;
				}
				else
				{
					keyon3=0;
				}

			}
		if( ppvvshow1==3)
		 {
			//pldata=1000;
			wddata=1200;
		
			leds_buffer[0]=0;
			leds_buffer[1]=0;
			leds_buffer[2]=4;
			leds_buffer[3]=th[20]%1000/100;
			leds_buffer[4]=th[20]%100/10;
			leds_buffer[5]=th[20]%10;
			
			if(key[2]==1)
				{		
					if(keyon2==0)
					 {
							keyon2=1;
							th[20]++;

					}
					key[2]=0;
				}
				else
				{
					keyon2=0;
				}
			
				if(key[3]==1)
				{
					if(keyon3==0)
					 {	
						 keyon3=1;	
						 th[20]--;
					}
					key[3]=0;
				}
				else
				{
					keyon3=0;
				}

			}
		
		
	}
//	if(pldata<950) pldataaa=pldata*0.97;
//	else pldataaa=pldata;
//	if(wddata<1250)wddataaa=wddata*0.97;
//	else wddataaa=wddata;
	#endif
		
}