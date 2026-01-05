#include "Exint.h"

void delay_ms(unsigned int ms)		//@24.000MHz
{
	unsigned char i, j;
	while(ms--)
	{
		i = 24; j = 85;
		do
		{
			while (--j);
		} while (--i);
	}
}



