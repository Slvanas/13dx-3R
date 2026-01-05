#include "Uart.h"
 #include "stc15f2k60s2.h"
 #include "init.h"
 #include "eep.h"

unsigned char xdata rec[20];		//接收缓存
unsigned char xdata recs=0;			//接收字数
 unsigned char xdata send[20];		 //发送缓存
unsigned char xdata sends=0;		  //发送字数
unsigned char xdata sendnum=0;	
unsigned char xdata timeout;
extern unsigned int  xdata   wddata,pldata;
extern unsigned char xdata thhotctrl1,thsdctrl1;
extern unsigned char xdata th[21];
extern unsigned char thfatctrl1;
extern unsigned char therr1,therr2;
extern unsigned int wddata2,pldata2;
extern unsigned char xdata ctrl_break1;
extern unsigned char xdata ctrl_break2;
extern unsigned char xdata ctrl_break3;
extern unsigned char xdata ctrl_break4;

sbit RS485=P5^4;
sbit hot1=P4^0;
sbit fan1=P4^1;
sbit hot2=P4^2;
sbit fan2=P4^3;

void UartInit(void)		//4800bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	  if(th[14]==1)
	{
 	
		TL1 = 0xE0;		//设定定时初值	  9600
		TH1 = 0xFE;		//设定定时初值
	 }
	 else
	 {
			
			TL1 = 0xC0;		//设定定时初值	 4800
			TH1 = 0xFD;		//设定定时初值
	 }

	//TL1 = 0xE0;		//设定定时初值	  9600
	//TH1 = 0xFE;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;	
	ES=1;
}
unsigned char CRC16(unsigned char *tempsend, unsigned char Data_Len)
	{
			unsigned char  crc1, crc2;

			unsigned char CRC16Lo = 0xff, CRC16Hi = 0xff, CH = 0xA0, CL = 0x01;

			unsigned char  SaveHi, SaveLo;

			unsigned char i, Flag;

			crc1 = tempsend[Data_Len];
			crc2 = tempsend[Data_Len + 1];

			for (i = 0; i < Data_Len; i++)  //0 to Data_Len-1
			{

					CRC16Lo = (unsigned char)(CRC16Lo ^ tempsend[i]);

					for (Flag = 0; Flag < 8; Flag++) //0 to 7
					{

							SaveHi = CRC16Hi;

							SaveLo = CRC16Lo;

							CRC16Hi = (unsigned char)(CRC16Hi >> 1);

							CRC16Lo = (unsigned char)(CRC16Lo >> 1);

							if ((SaveHi & 0x01) == 0x01)
							{
									CRC16Lo = (unsigned char)(CRC16Lo | 0x80);
							}

							if ((SaveLo & 0x01) == 0x01)
							{

									CRC16Hi = (unsigned char)(CRC16Hi ^ CH);

									CRC16Lo = (unsigned char)(CRC16Lo ^ CL);

							}

					}

			}

			tempsend[Data_Len + 1] = CRC16Hi;

			tempsend[Data_Len] = CRC16Lo;

			if (tempsend[Data_Len] == crc1 && tempsend[Data_Len+1] == crc2)
			{
					return 1;
			}
			else
			{
					return 0;
			}

	}

void sendpccmd27(void)
{
RS485=0;
	send[0]= th[13];
	send[1]=0x03;
	send[2]=0x08;
	if(therr1==1)
	{
		if(wddata>=500)
		{
			send[3]=(wddata-500)>>8;
			send[4]=(wddata-500);
		}
		else
		{
			send[3]=(((500-wddata)>>8)|0x80);
			send[4]=(500-wddata);
		}
		send[5]=pldata>>8;
		send[6]=pldata;
		
		if(wddata<200)
		{
			send[3]=0x00;
			send[4]=0xcc;
		}
		if(pldata==0)
		{
			send[5]=0x00;
			send[6]=0xcc;
		}
	}
	else
	{
		send[3]=0x00;
		send[4]=0xcc;
		send[5]=0x00;
		send[6]=0xcc;
	}
	#if((xxh==4)||(xxh==5)||(xxh==6)||(xxh==7)||(xxh==8)||(xxh==9))
	{
		if(therr2==1)
		{
				if(wddata2>=500)
				{
					send[7]=(wddata2-500)>>8;
					send[8]=(wddata2-500);
				}
				else
				{
					send[7]=(((500-wddata2)>>8)|0x80);
					send[8]=(500-wddata2);
				}
				send[9]=pldata2>>8;
				send[10]=pldata2;
				
				if(wddata2<200)
				{
					send[7]=0x00;
					send[8]=0xcc;
				}
				if(pldata2==0)
				{
					send[9]=0x00;
					send[10]=0xcc;
				}
			}
			else
			{
				send[7]=0x00;
				send[8]=0xcc;
				send[9]=0x00;
				send[10]=0xcc;
			}
	}
	#else
	  send[7]=0x00;
				send[8]=0x00;
				send[9]=0x00;
				send[10]=0x00;
	#endif
	
	
	CRC16(send,11);
	SBUF=send[0];
	sendnum=1;
	sends=13;
} 

void sendpccmd34(void)
{
RS485=0;
	send[0]=th[13];
	send[1]=0x03;
	send[2]=0x02;	
	send[3]=0x00;
	send[4]=0x00;
	if(hot1!=0)send[4]|=0x01;
	if(fan1!=0)send[4]|=0x02;


	if(ctrl_break1==1)send[4]|=0x10;	
	if(ctrl_break3==1)send[4]|=0x20;	
	if(therr1==0)send[3]|=0x03;
	#if(xxh==4||xxh==5||xxh==6||xxh==7||xxh==8||xxh==9)
		if(hot2!=0)send[4]|=0x04;
	if(fan2!=0)send[4]|=0x08;
	if(ctrl_break2==1)send[4]|=0x40;
	if(ctrl_break4==1)send[4]|=0x80;
	if(therr2==0)send[3]|=0x0c;	
	#endif

	#if(tde==5)
	if(therr1!=0)
	{
	if((wddata/10)>=th[15])send[3]|=0x10;
	if((pldata/10)>=th[16])send[3]|=0x20;
	}
	#endif

//	if((wddata/10)>=th[15])send[3]|=0x10;
//	if((pldata/10)>=th[16])send[3]|=0x20;
		
	CRC16(send,5);
	SBUF=send[0];
	sendnum=1;
	sends=7;
}

void Uart_Isr() interrupt 4 using 1
{
	unsigned char tempi;
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
			rec[recs++]=SBUF;	
		timeout=40;
		if(recs>20)recs=0;
		
			if(rec[0]==th[13])
			{				
				if(recs>2)
				{
					if(rec[1]==0x03)
					{
						if(recs>=8)
						{
							recs=0;
							//if(sendctrlrealok==1)
							{
								if(rec[3]==0x27)
								{
									if(rec[5]==0x04)sendpccmd27();
									
								}
								if(rec[3]==0x34)
								{
									if(rec[5]==0x01)sendpccmd34();
								}
							}
						}
					}				
                    else
                        recs = 0;
                }
                
			}
			else
			{
				recs=0;
			}
	 	}
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
			if(sendnum<sends)					//发送未完毕
			{
				SBUF=send[sendnum];
				sendnum++;
			}
			else
			{
	//			_nop_();
				RS485=1;
//			 led_status&=0x7F;
			}
		}
}
