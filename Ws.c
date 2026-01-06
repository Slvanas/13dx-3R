#include "init.h"
#include "Ws.h"
#include "adc.h"
#include "pwm.h"
#include "stc15f2k60s2.h"
#include "Uart.h"
#include "qudong.h"

#include "math.h"

sbit hot1=P4^0;
sbit fan1=P4^1;
sbit hot2=P4^2;
sbit fan2=P4^3;
sbit BAout=P4^5;
sbit CDout=P4^7;
sbit HHAout=P4^6;
sbit loadhot1=P3^4;
sbit loadfan1=P3^5;
sbit loadhot2=P3^6;
sbit loadfan2=P3^7;
//
extern unsigned int xdata wddatanow;
extern unsigned int xdata pldatanow;
extern unsigned char xdata  Terrnum;
extern unsigned char xdata  Herrnum;
extern unsigned char xdata THrecok;
//
//
extern unsigned int xdata wddata2now;
extern unsigned int xdata pldata2now;
extern unsigned char xdata  Terrnum2;
extern unsigned char xdata  Herrnum2;
extern unsigned char xdata THrecok2;

extern unsigned int xdata thouttime1;
extern unsigned int xdata thouttime2;

extern unsigned int xdata wddata;
extern unsigned int xdata pldata;
extern unsigned int xdata wddata2;
extern unsigned int xdata pldata2;

extern unsigned char xdata therr1;
extern unsigned char xdata therr2;
extern unsigned int xdata handctrltime;
extern unsigned char led_status;
extern unsigned char led_status2;
extern unsigned int xdata showalltime;

unsigned char xdata led_Senbreak;
unsigned char xdata led_Senbreak2;
unsigned char xdata thhotctrl1=0;  
unsigned char xdata thsdctrl1=0;
unsigned char xdata thhotctrl2=0;
unsigned char xdata thsdctrl2=0;
unsigned char xdata thfatctrl1=0;
unsigned char xdata thfatctrl2=0;
unsigned char xdata thfathandctrl1=0;
unsigned char xdata thfathandctrl2=0;
unsigned char xdata thhothandctrl1=0;
unsigned char xdata thsdhandctrl1=0;
unsigned char xdata thhothandctrl2=0;
unsigned char xdata thsdhandctrl2=0;
unsigned char xdata th[21];

unsigned char xdata ctrl_Hot1;     

unsigned char xdata ctrl_Fan1;
unsigned char xdata ctrl_Hot2;     

unsigned char xdata ctrl_Fan2;

unsigned char xdata ctrl_break1;
unsigned char xdata ctrl_break2;
unsigned char xdata ctrl_break3;
unsigned char xdata ctrl_break4;
unsigned char xdata led_Hot1;       // connections to LCD module
unsigned char xdata led_Fan2;
unsigned char xdata led_Fan1;
unsigned char xdata led_Hot2;
unsigned char xdata led_Handhot;
unsigned char xdata led_Handfan;
unsigned char xdata led_Light;
unsigned char xdata led_Senbreak;
unsigned char xdata led_Senbreak2;
//unsigned char xdata led_Loadbreak;	
//unsigned char xdata led_Loadbreak2;	
//unsigned char xdata led_Light;
//unsigned char xdata led_Hot3;
//unsigned char xdata led_Fan3;
//unsigned char xdata led_Hotout;
//unsigned char xdata led_Sdout;
//unsigned char xdata led_Uart;
unsigned char xdata outloadnum1=0;
unsigned char xdata outloadnum2=0;
unsigned char xdata outloadnum3=0;
unsigned char xdata outloadnum4=0;

unsigned long xdata wddataall;
extern unsigned char xdata ppvv;
extern unsigned char xdata showtime;


unsigned int xdata old_wddata=0;
unsigned char xdata overflow_count1=0;

unsigned int xdata old_pldata=0;
unsigned char xdata overflow_count11=0;

unsigned int xdata old_wddata2=0;
unsigned char xdata overflow_count2=0;
unsigned int xdata old_pldata2=0;
unsigned char xdata overflow_count22=0;


// ... 原有变量定义 ...
unsigned long xdata wddataall;

// [新增] 定义远程控制模式，默认为0（自动）
unsigned char remote_ctrl_mode = 0; 

extern unsigned char xdata ppvv;
// ...



void wsdup(void)
{		   
	if(thouttime1>0)therr1=1;
	else therr1=0;
	if(thouttime2>0)therr2=1;
	else therr2=0;
	
	if(THrecok==1)
	{
		if(old_wddata == 0)
		{
			wddata=wddatanow;
			old_wddata=wddata;
		}
		else
		{
			if(abs(old_wddata-wddatanow)>=50)	//大于10摄氏度的差值，需要连续三次才能输出
			{
				overflow_count1++;
				if(overflow_count1>=5)
				{
					overflow_count1=0;
					wddata=wddatanow;
					old_wddata=wddata;
				}
			}
			else
			{
				overflow_count1=0;
				wddata=wddatanow;
				old_wddata=wddata;
			}
		}
		if(old_pldata==0)
		{
			pldata=pldatanow;
			old_pldata=pldata;
		}
		else
		{
			if(abs(old_pldata-pldatanow)>=50)	//大于10摄氏度的差值，需要连续三次才能输出
			{
				overflow_count11++;
				if(overflow_count11>=5)
				{
					overflow_count11=0;
					pldata=pldatanow;
					old_pldata=pldata;					
				}				
			}
			else
			{
				overflow_count11=0;
				pldata=pldatanow;
				old_pldata=pldata;
			}
		}
		if(pldata>1000)pldata=1000;
		THrecok=0;
	}
	//---------------------------------------------------------------------------
	if(THrecok2==1)
	{		
		if(old_wddata2==0)
		{
			wddata2=wddata2now;
			old_wddata2=wddata2;
		}
		else
		{
			if(abs(old_wddata2-wddata2now)>=50)
			{
				overflow_count2++;
				if(overflow_count2>=5)
				{
					overflow_count2=0;
					wddata2=wddata2now;
					old_wddata2=wddata2;
				}				
			}
			else
			{
				overflow_count2=0;
				wddata2=wddata2now;
				old_wddata2=wddata2;
			}
		}
		if(old_pldata2==0)
		{
			pldata2=pldata2now;
			old_pldata2=pldata2;
		}
		else
		{
			if(abs(old_pldata2-pldata2now)>=50)	//大于10摄氏度的差值，需要连续三次才能输出
			{
				overflow_count22++;
				if(overflow_count22>=5)
				{
					overflow_count22=0;
					pldata2=pldata2now;
					old_pldata2=pldata2;
				}				
			}
			else
			{
				overflow_count22=0;
				pldata2=pldata2now;
				old_pldata2=pldata2;
			}
		}		
		THrecok2=0;
		if(pldata2>1000)pldata2=1000;
	}

	if(handctrltime==0)	
	{
		if(therr1==1)
		{
			led_Senbreak=1;
			if(wddata>1700||wddata<100)
				{
					thhotctrl1=0;
				}
				if(wddata>100)
				{
					if(((wddata/10)<th[2]))
					{
						thhotctrl1=1;				
					}
				}	
				if(((wddata/10)>=th[1]))
				{
					thhotctrl1=0;
				}
				if(pldata>10)
				{
					if(((pldata/10)>=th[3]))
					{
						thsdctrl1=1;	
					}
				}
				if(((pldata/10)<th[4]))
				{
					thsdctrl1=0;		
				}													
		}
		
	else
		{
			led_Senbreak=0;
			thhotctrl1=0;
			thsdctrl1=0;
		}
		  
		
	   }
}
  

void wsdcl(void)
{
	
	
	#if(xxh==2)
	 thsdctrl1=0;
#endif
	#if(xxh==3)
	 thhotctrl1=0;
	 thfatctrl1=0;
#endif
	#if(xxh==4)	
	#if(tde==1)
	{
		
	}
	#else
	{
		#if(tda==1)
		{
	   		
		}
		#else
		{
			thfatctrl1=0;
	  	 	thfatctrl1=0;
		}
		#endif
	}
	#endif	
#endif
	#if((xxh==5))	
thfatctrl1=0;
thfatctrl2=0;
thsdctrl1=0;
thsdctrl2=0;	
#endif
#if(xxh==8)
thsdctrl1=0;
thsdctrl2=0;
#endif
	#if(xxh==6)||(xxh==9)	
thhotctrl1=0;
thhotctrl2=0;
thfatctrl1=0;
thfatctrl2=0;	
#endif

	

	
		#if(tde==0)
        
        // [新增/修改] 远程控制逻辑介入
        if(remote_ctrl_mode == 1) // 远程强制开启
        {
            ctrl_Hot1 = 1;
            led_Hot1 = 1;
        }
        else if(remote_ctrl_mode == 2) // 远程强制关闭
        {
            ctrl_Hot1 = 0;
            led_Hot1 = 0;
        }
        else // remote_ctrl_mode == 0 (自动模式，执行原有逻辑)
        {
            if((thhotctrl1==1)||(thsdctrl1==1))
            {
                    ctrl_Hot1=1;	
                    led_Hot1=1;
            }
            else
            {	
                    ctrl_Hot1=0;
                    led_Hot1=0;							
            }
        }

			if((thhotctrl2==1)||(thsdctrl2==1))
			{				
						ctrl_Hot2=1;	
						led_Hot2=1;
									
			}
			else
			{
						ctrl_Hot2=0;	
						led_Hot2=0;										
			}

	
		if(thfatctrl1==1)
		{	
				ctrl_Fan1=1;
				led_Fan1=1;
		}
		else
		{	
		
				ctrl_Fan1=0;
				led_Fan1=0;
					
		}

		if((thfatctrl2==1))
		{	
				ctrl_Fan2=1;
				led_Fan2=1;
		}
		else
		{	
		
				ctrl_Fan2=0;
				led_Fan2=0;
					
		}
		#endif
		#if(tde==3)	
		thhotctrl1=0;
		if(thfatctrl1==1||thsdctrl1==1)
		{	
				ctrl_Fan1=1;
				led_Fan1=1;
				led_Hot1=1;
		}
		else
		{	
				ctrl_Fan1=0;
				led_Fan1=0;	
				led_Hot1=0;	
		}
		#endif
			#if(tde==0)
				
			#endif

//----------------------------------------------		
//	if(handctrltime==0)	
	if(ppvv==0)
	{		
		if(ctrl_Hot1==1&&loadhot1==1)
		{
			
			outloadnum1++;
			if(outloadnum1>100)
			{
				ctrl_break1=1;
				outloadnum1=100;	
			}
			
		}
		else
		{
			if(outloadnum1>0)outloadnum1--;
			else ctrl_break1=0;
			
		}

		if(fan1==1&&loadfan1==1)
		{	
			outloadnum3++;
			if(outloadnum3>100)
			{
				ctrl_break3=1;
				outloadnum3=100;		
			}
		}
		else
		{
			
			if(outloadnum3>0)outloadnum3--;
			else ctrl_break3=0;
			
		}

		if(ctrl_Hot2==1&&loadhot2==1)
		{
			outloadnum2++;
			if(outloadnum2>100)
			{
				outloadnum2=100;		
				ctrl_break2=1;
			}
		}
		else
		{
			if(outloadnum2>0)outloadnum2--;
			else ctrl_break2=0;
		}

	}			  

					
				  #if((xxh==1)||(xxh==2)||(xxh==3))
				  {
				  	  therr2=1;
					  ctrl_break2=0;
			  	  	if(hot1==1) led_status|=0x01;
					else  led_status&=0xFE;
					if(fan1==1) led_status|=0x02;
					else  led_status&=0xFD;	
					if(ctrl_Hot1==1)hot1=1;
					else hot1=0;
					if(ctrl_Fan1==1)fan1=1;
					else fan1=0;
						#if(tde==3)	
					  if(ctrl_Fan1==1)
					  {
					  fan1=1;
					  led_status|=0x01;
					  }

					else 
					{	
						fan1=0;
						led_status&=0xFE;
					}

					#endif
					if(TorNULL==1)
					{
					  if(therr1==0)
					  {
					  	led_status|=0x80;
					  }
					  else
					  {
					  	led_status&=0x7F;
					  }
					}
					#if(tde==5)
					if(therr1!=0)
					{
						if((wddata/10)>=th[15])
						{
							led_status|=0x08;
						}
						else
						{
							if((wddata/10)<th[15]-1)
							led_status&=0xF7;
						}
						if((pldata/10)>=th[16])
						{
							led_status|=0x10;
						}
						else  
						{
							if((pldata/10)<th[16]-1)
							led_status&=0xEF;
						}
					}		

				  
				  #endif
				  }
				  #endif
				  #if((xxh==4)||(xxh==5)||(xxh==6))
				  ctrl_break3=0;
				  if(TorNULL==1)
				  {
				   if((therr1==0)||(therr2==0))
				   {
				  	  led_status|=0x80;
				   }
				   else
				   {
				  	  led_status&=0x7F;
				   }
				 	if(hot1==1) led_status|=0x01;
					else  led_status&=0xFE;
					if(fan1==1) led_status|=0x02;
					else  led_status&=0xFD;
					}
					else
					{	
					  if(showalltime<500) 
					  {
					  	  if(ctrl_Hot1==1) led_status|=0x01;
						  else  led_status&=0xFE;
						  	if(ctrl_Fan1==1) led_status|=0x02;
							  else  led_status&=0xFD;
					  }
					  else
					  {	 
					      if(ctrl_Hot2==1) led_status|=0x01;
						else  led_status&=0xFE;
							if(ctrl_Fan2==1) led_status|=0x02;
							  else  led_status&=0xFD;
					  }	
					}
					  if(ctrl_Hot1==1)hot1=1;
					else hot1=0;
					if(tda==1)
					{
							if(ctrl_Fan1==1)fan1=1;
						else fan1=0;
					  	if(ctrl_Hot2==1)hot2=1;
						else hot2=0;
					}
					else
					{
					if(ctrl_Hot2==1)fan1=1;
					else fan1=0;
				   	}
				  #endif

//------------------------------------------------------------------------------------------
				  #if((xxh==7)||(xxh==8)||(xxh==9))
				  ctrl_break3=0;
				  if((therr1==0)||(therr2==0)||ctrl_break1==1||ctrl_break2==1)
				  {
				  	led_status|=0x80;
				  }
				  else
				  {
				  	led_status&=0x7F;
				  }
				  if(ctrl_Hot1==1) led_status|=0x01;
					else  led_status&=0xFE;
				if(ctrl_Fan1==1) led_status|=0x02;
							  else  led_status&=0xFD;


				  if(ctrl_Hot2==1) led_status2|=0x01;
					else  led_status2&=0xFE;
				if(ctrl_Fan2==1) led_status2|=0x02;
							  else  led_status2&=0xFD;
				 	if(ctrl_Hot1==1)hot1=1;
						else hot1=0;
						if(ctrl_Hot2==1)hot2=1;
						else hot2=0;
				   	if(ctrl_Fan1==1)fan1=1;
						else fan1=0;
						if(ctrl_Fan2==1)fan2=1;
						else fan2=0;
					//	SBUF=ctrl_Fan2;

					 if(handctrltime>0) led_status|=0x04;
				else  led_status&=0xFB;
//				if(showalltime>500)  led_status|=0x80;
//				else  led_status&=0x7F;

				  #endif

				 	if(ctrl_Fan2==1)fan2=1;
						else fan2=0;
		if(ctrl_break1==1||ctrl_break3==1||ctrl_break2==1)
		{
			BAout=1;
			led_status|=0x40;						 
		}
		else
		{
			BAout=0;
			led_status&=0xBF;
		}
		
		if((therr1==0)||(therr2==0))
		{
			CDout=1;
		}
		else
		{
			CDout=0;
		}
		
		if(wddata/10>=th[15]||pldata/10>=th[16])
		{
			HHAout=1;	
		}
		else
		{
			if((wddata/10<th[15]-1)&&(pldata/10<th[16]-1))
			{
				HHAout=0;	
			}
		}
		
		
		#if(tde==5)
		if(therr1==1)
		{
			PWMOUT2(pldata*(0.002*th[18])+th[17]);
			PWMOUT((wddata-100)*(0.002*th[20])+th[19]);
		}
		else
		{
			PWMOUT2(th[17]-4);
			PWMOUT(th[19]-4);
		}
		#endif     
}

