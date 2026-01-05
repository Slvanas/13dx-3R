#include "stc15f2k60s2.h"

#define     PWM_DUTY        4096            //定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define     PWM_HIGH_MAX    PWM_DUTY-32     //限制PWM输出的最大占空比。
#define     PWM_HIGH_MIN        32          //限制PWM输出的最小占空比。

#define CCP_S0 0x10                         //P_SW1.4
#define CCP_S1 0x20                         //P_SW1.5
sbit  CCP0      =   P1^1;
sbit  CCP1      =   P1^0;

unsigned int    PWM_high;                   //定义PWM占空比寄存器，即PWM输出高电平的PCA时钟脉冲个数（占空比写入变量）。
unsigned int    PWM_low;                    //定义PWM输出低电平的PCA时钟脉冲个数。
unsigned int    CCAP0_tmp;                  //定义CCAP0重装载影射寄存器。

//========================================================================
// 函数: void PWMn_SetHighReg(unsigned int high)
// 描述: 写入占空比数据。
// 参数: high:  占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
// 返回: 无
// 版本: VER1.0
// 日期: 2009-12-30
// 备注:
//========================================================================
//void PWMn_SetHighReg(unsigned int high)
//{
//    if(high > PWM_HIGH_MAX)     high = PWM_HIGH_MAX;    //如果写入大于最大占空比数据，强制为最大占空比。
//    if(high < PWM_HIGH_MIN)     high = PWM_HIGH_MIN;    //如果写入小于最小占空比数据，则返回错误代码2。
//    CR = 0;                     //停止PCA。
//    PWM_high = high;                        //数据在正确范围，则装入占空比寄存器。
//    PWM_low = PWM_DUTY - high;              //计算并保存PWM输出低电平的PCA时钟脉冲个数。
//    CR = 1;                     //启动PCA。
//}

//========================================================================
// 函数: void PWMn_init(unsigned int high)
// 描述: 初始化程序。
// 参数: high:  初始化占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
// 返回: 无
// 版本: VER1.0
// 日期: 2009-12-30
// 备注:
//========================================================================
void PWMn_init(unsigned int high)
{
  ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=0
    P_SW1 = ACC;                    //(P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2)
    
//  ACC = P_SW1;
//  ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=1 CCP_S1=0
//  ACC |= CCP_S0;                  //(P3.4/ECI_2, P3.5/CCP0_2, P3.6/CCP1_2, P3.7/CCP2_2)
//  P_SW1 = ACC;  
//  
//  ACC = P_SW1;
//  ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=1
//  ACC |= CCP_S1;                  //(P2.4/ECI_3, P2.5/CCP0_3, P2.6/CCP1_3, P2.7/CCP2_3)
//  P_SW1 = ACC;  

    CCON = 0;                       //初始化PCA控制寄存器
                                    //PCA定时器停止
                                    //清除CF标志
                                    //清除模块中断标志
    CL = 0;                         //复位PCA寄存器
    CH = 0;
    CMOD = 0x02;                    //设置PCA时钟源
                                    //禁止PCA定时器溢出中断
    PCA_PWM0 = 0x00;                //PCA模块0工作于8位PWM
    CCAP0H = CCAP0L = high;         //PWM0的占空比为87.5% ((100H-20H)/100H)
    CCAPM0 = 0x42;                  //PCA模块0为8位PWM模式

    PCA_PWM1 = 0x00;                //PCA模块1工作于7位PWM
    CCAP1H = CCAP1L = high;         //PWM1的占空比为75% ((80H-20H)/80H)
    CCAPM1 = 0x42;                  //PCA模块1为7位PWM模式

//    PCA_PWM2 = 0x80;                //PCA模块2工作于6位PWM
//    CCAP2H = CCAP2L = 0x20;         //PWM2的占空比为50% ((40H-20H)/40H)
//    CCAPM2 = 0x42;                  //PCA模块2为6位PWM模式

    CR = 1;                         //PCA定时器开始工作                 //允许总中断
}

//========================================================================
// 函数: void PCA_interrupt (void) interrupt 7
// 描述: PCA中断服务程序。
// 参数: 无。
// 返回: 无。
// 版本: VER1.0
// 日期: 2009-12-30
// 备注:
//========================================================================
void PCA_interrupt (void) interrupt 7
{
    if(CCF0 == 1)       //PCA模块0中断
    {
        CCF0 = 0;       //清PCA模块0中断标志

        if(CCP0 == 1)   CCAP0_tmp += PWM_high;      //输出为高电平，则给影射寄存器装载高电平时间长度
        else            CCAP0_tmp += PWM_low;       //输出为低电平，则给影射寄存器装载低电平时间长度
        CCAP0L = (unsigned char)CCAP0_tmp;          //将影射寄存器写入捕获寄存器，先写CCAP0L
        CCAP0H = (unsigned char)(CCAP0_tmp >> 8);   //后写CCAP0H
    }
/*  
    else if(CCF1 == 1)                         //PCA模块1中断
    {
        CCF1 = 0;                              //清PCA模块1中断标志
    }
    else if(CF == 1)                           //PCA溢出中断
    {
        CF = 0;                                //清PCA溢出中断标志
    }
*/
}

