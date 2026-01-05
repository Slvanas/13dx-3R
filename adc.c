#include "stc15f2k60s2.h"
#include  "adc.h"

/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks

unsigned char xdata VV=0;
unsigned char xdata VV2=0;





void Delay(unsigned int n)
{
    unsigned int x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
void InitADC()
{
    P1ASF = 0x1c;                   //Open 8 channels ADC function
    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2); 	//ADC power-on and delay
	VV=220;
}

unsigned int GetADCResult(unsigned char  ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
 //   Delay(1);   
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return (ADC_RES*4+ADC_RESL);                 //Return ADC result
}


   void PWMOUT(unsigned int inbz)
{
	unsigned int adnum;
	
	 	adnum=GetADCResult(2);
		if(adnum<inbz-1)
		{
			
			if(VV>30)VV--;
		}
		else
		{
			if(adnum>inbz+1)
			{
				if(VV<217) VV++;
			}
			else
			{
				
			}
		}
	//	SBUF=adnum;
	 	 CCAP1H = CCAP1L=VV;
	 
}

void PWMOUT2(unsigned int inbz)
{
	unsigned int adnum;
	 	adnum=GetADCResult(3);
		if(adnum<inbz-1)
		{
			
			if(VV2>3)VV2--;
		}
		else
		{
			if(adnum>inbz+1)
			{
				if(VV2<250) VV2++;
			}
			else
			{
				
			}
		}
	//	SBUF=adnum;
	 	 CCAP0H = CCAP0L=VV2;
	 
}