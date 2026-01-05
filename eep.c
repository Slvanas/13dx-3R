#include "stc15f2k60s2.h"
#include "eep.h"
#include "intrins.h"

#define ENABLE_IAP  0x82

#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3               //IAP扇区擦除命令							
///*----------------------------
//软件延时
//----------------------------*/
//void Delay(unsigned char n)
//{
//    unsigned int x;
//
//    while (n--)
//    {
//        x = 0;
//        while (++x);
//    }
//}

/*----------------------------
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
unsigned char IapReadByte(unsigned int addr)
{
    unsigned char  dat;                       //数据缓冲区

    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

/*----------------------------
扇区擦除
----------------------------*/
void IapEraseSector(unsigned int addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}


void eepwrite(unsigned char tempdata[],unsigned char templong)
{
	unsigned char i;
	
	IapEraseSector(0x00);
	IapProgramByte(0x00,0xaa);
	IapProgramByte(0x01,0x55);	
	IapProgramByte(0x02,0x00);
	IapProgramByte(0x03,0x00);
	IapProgramByte(0x04,0x00);
	for(i=0;i<templong;i++)
	{
		IapProgramByte(0x05+i,tempdata[i]);
	}
}


void eepread(unsigned char tempdata[],unsigned char templong)
{
	unsigned char i;
	if(IapReadByte(0x00)==0xaa&&IapReadByte(0x01)==0x55)
	{	
		for(i=0;i<templong;i++)
		{
			tempdata[i]=IapReadByte(0x05+i);
		}
	}
	else
	{  
		tempdata[0]=0;
		tempdata[1]=63;
		tempdata[2]=55;
		tempdata[3]=85;
		tempdata[4]=75;
		tempdata[5]=90;
		tempdata[6]=75;

		tempdata[7]=63;
		tempdata[8]=55;
		tempdata[9]=85;
		tempdata[10]=75;
		tempdata[11]=90;
		tempdata[12]=75;
		
		tempdata[13]=1;
		tempdata[14]=0;
		tempdata[15]=105;
		tempdata[16]=90;
		
		tempdata[17]=20;
		tempdata[18]=80;
		tempdata[19]=20;
		tempdata[20]=67;
	}
}
