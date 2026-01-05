#include "Exint.h"
 #include "stc15f2k60s2.h"

unsigned long xdata oldlineall=0;
unsigned char xdata onelinetime=0;
unsigned char xdata onelinedata=0;
unsigned long xdata onelineall=0;
unsigned char xdata onelinebu=0;

unsigned long xdata ctsendchar=0;
unsigned char xdata tempsum=0;
unsigned int xdata wddatanow=0;
unsigned int xdata pldatanow=0;
unsigned char xdata  Terrnum=0;
unsigned char xdata  Herrnum=0;
unsigned char xdata THrecok=0;

unsigned char xdata onelinetime2=0;
unsigned char xdata onelinedata2=0;
unsigned long xdata onelineall2=0;
unsigned char xdata onelinebu2=0;
//unsigned int xdata wddata2=0;
//unsigned int xdata pldata2=0;
unsigned int xdata wddata2now=0;
unsigned int xdata pldata2now=0;
unsigned char xdata  Terrnum2=0;
unsigned char xdata  Herrnum2=0;
unsigned char xdata THrecok2=0;

unsigned int xdata thhandctrltime=0;
unsigned char xdata thhandctrl=0;
unsigned char xdata therr1=0;
unsigned char xdata therr2=0;
unsigned int xdata thouttime1=0;
unsigned int xdata thouttime2=0;

unsigned int xdata wddata=0;
unsigned int xdata pldata=0;
unsigned int xdata wddata2=0;
unsigned int xdata pldata2=0;

void ExintInit(void)
{
	IT0=1;
	EX0=1;	
	IT1=1;
	EX1=1;	
}


unsigned char CRC8(long buffer)
{
		unsigned char crc = 0;
		unsigned char i,j;
		unsigned char tempbuffer;
		for (j = 0; j < 3; j++)
		{
			 tempbuffer=(buffer>>(8*j));
				crc ^= tempbuffer;
				for (i = 0; i < 8; i++)
				{
						if ((crc & 0x01) != 0)
						{
								crc >>= 1;
								crc ^= 0x8c;
						}
						else
						{
								crc >>= 1;
						}
				}
		}
		return crc;
}
unsigned char CRC28(long buffer)
{
		unsigned char crc = 0;
		unsigned char i,j;
		unsigned char tempbuffer;
		for (j = 0; j < 3; j++)
		{
			 tempbuffer=(buffer>>(8*j));
				crc ^= tempbuffer;
				for (i = 0; i < 8; i++)
				{
						if ((crc & 0x01) != 0)
						{
								crc >>= 1;
								crc ^= 0x8c;
						}
						else
						{
								crc >>= 1;
						}
				}
		}
		return crc;
}
void Int0() interrupt 0
{
	unsigned char i=0;
	if(	 onelinetime>35&&onelinetime<45)
	{
		onelinedata=1;
	}
	if(	 onelinetime>73&&onelinetime<87)
	{
		onelinedata=2;
	}
	if( onelinetime>110&&onelinetime<130)
	{
	    onelinedata=3;
	}
	if(onelinetime>150)
	{
		onelinedata=5;	
	}
	onelinetime=0;
	if(onelinedata==2)
	{
		onelineall|=((unsigned long)(0x0001)<<onelinebu);
		onelinebu++;
	
	}
	else
	{
		if(onelinedata==1)
		{
			onelinebu++;
			thouttime1=50;
		}
		else
		{
			if(onelinedata==3)
			{
				onelinebu=0;
				onelineall=0;
			}
		}
	}
	if(onelinedata>4)
	{
	   	
		if(CRC8(onelineall>>8)==(onelineall&0xff))
		{
	
			onelineall=onelineall>>8;	
			tempsum=0;
			ctsendchar=((onelineall>>3)&0xaaaaaa);
			for(i=0;i<21;i++)
	     	{
		       if((ctsendchar&0x01)==0x01)
		       {
		         tempsum++;
		       }
	       		ctsendchar=ctsendchar>>1;
	     	}
     		tempsum=tempsum&0x7;
			 if(tempsum==(onelineall&0x07))
			 {
				 if(onelineall!=0)
				 {
					wddatanow=onelineall>>13;
					
					pldatanow=(onelineall&0x1ff8)>>3;
				
					THrecok=1;
				 }
			 }	 
	 	}
		onelinebu=0;
		onelineall=0;	 
	}		
}

void Int1() interrupt 2
{
	unsigned char i=0;
	//SBUF=onelinetime>>4;
	if(onelinetime2>35&&onelinetime2<45)
	{
		onelinedata2=1;
	}
	if(	 onelinetime2>73&&onelinetime2<87)
	{
		onelinedata2=2;
	}
	if( onelinetime2>110&&onelinetime2<130)
	{
	    onelinedata2=3;
	}
	if(onelinetime2>150)
	{
		onelinedata2=5;	
	}
//	onelinedata2=onelinetime2>>4;
	onelinetime2=0;
	if(onelinedata2==2)
	{
		onelineall2|=((unsigned long)(0x0001)<<onelinebu2);
		onelinebu2++;
	}
	else
	{
		if(onelinedata2==1)
		{
			onelinebu2++;
			thouttime2=50;
		}
		else
		{
			if(onelinedata2==3)
			{
				onelinebu2=0;
				onelineall2=0;
			}
		}
	}
	if(onelinedata2>4)
	{
		//SBUF=onelineall2>>16;
		if(CRC28(onelineall2>>8)==(onelineall2&0xff))
		{
			onelineall2=onelineall2>>8;	
			tempsum=0;
			ctsendchar=((onelineall2>>3)&0xaaaaaa);
			 for(i=0;i<21;i++)
			 {
				 if((ctsendchar&0x01)==0x01)
				 {
					 tempsum++;
				 }
				 ctsendchar=ctsendchar>>1;
			 }
			 tempsum=tempsum&0x7;
			 if(tempsum==(onelineall2&0x07))
			 {
				 if(onelineall2!=0)
				 {
					wddata2now=onelineall2>>13;
					pldata2now=(onelineall2&0x1ff8)>>3;
				  //SBUF=wddata2>>3;
					 THrecok2=1;
				 }	
			 }
		 }
		onelinebu2=0;
		onelineall2=0;
		
	}
		
}