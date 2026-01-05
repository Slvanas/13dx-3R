#include "Veiw.h" 
#include "stc15f2k60s2.h"
#include "init.h" 
unsigned char veiwon=0;
unsigned int xdata showalltime=0;
unsigned char xdata ppvv=0;

unsigned char showjj=1;
unsigned char xdata showerrtime;

extern unsigned char leds_buffer[6]; 
extern int xdata wddata;
extern int xdata pldata;
extern int xdata wddata2;
extern int xdata pldata2;
extern unsigned char duth;
extern unsigned char th[21]	;
extern unsigned char xdata therr1;
extern unsigned char xdata therr2;
extern unsigned int xdata muentimeout;
extern unsigned char showcccc;

//extern unsigned char btl;

void showwsd(void)
{	
//------------------------------------------------------------
//			if(th[0]==00)
//			{
//				showalltime=50;
//			}
		
//		
		#if((xxh==1)||(xxh==2))
				if(therr1==1)
				{
						if(wddata>=500)
						{
						
							if(wddata>=1500)
							{
								if(wddata>=1700)
								{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=21;
								}  
								else
								{
								
								leds_buffer[0]=(wddata-500)/1000;
								leds_buffer[1]=((wddata-500)/100)%10;
								leds_buffer[2]=((wddata-500)/10)%10;
								}
							
							}
							else
							{
								if(wddata>=600)
								{
									 leds_buffer[0]=((wddata-500)/100)%10;
								}
								else
								{
									 leds_buffer[0]=28;
								}
							
								leds_buffer[1]=((wddata-500)/10)%10+10;
								leds_buffer[2]=((wddata-500))%10;
							}				
						}
						else
						{
					
								if(wddata>400)
								{
									   leds_buffer[0]=27;
									   leds_buffer[1]=(((500-wddata)/10)%10)+10;
									   leds_buffer[2]=((500-wddata))%10;
								}
								else
								{
									if(wddata>=100)
									{
									  leds_buffer[0]=27;
									   leds_buffer[1]=((500-wddata)/100)%10;
									   leds_buffer[2]=((500-wddata)/10)%10;
									}
									else
									{
									
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=29;
									}
								}
						}
						if(pldata>0)
						{
							if(pldata<1000)
							{
								leds_buffer[3]=(pldata/100)%10;
								leds_buffer[4]=((pldata/10)%10)+10;
								leds_buffer[5]=pldata%10;
							}
							else
							{
									leds_buffer[3]=1;
						 			leds_buffer[4]=0;
									leds_buffer[5]=0;
							}
						}
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			#endif
			#if((xxh==3))
			   if(therr1==1)
				{
					
						if(pldata>0)
						{
							if(pldata<1000)
							{
								leds_buffer[0]=(pldata/100)%10;
								leds_buffer[1]=((pldata/10)%10)+10;
								leds_buffer[2]=pldata%10;
							}
							else
							{
									leds_buffer[0]=1;
						 			leds_buffer[1]=0;
									leds_buffer[2]=0;
							}
						}
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			#endif
		
			#if(xxh==4)

			if(showalltime<500)
			{
				if(therr1==1)
				{
						if(wddata>=500)
						{
						
							if(wddata>=1500)
							{

								if(wddata>=1700)
								{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=21;
								}  
								else
								{
								leds_buffer[0]=(wddata-500)/1000;
								leds_buffer[1]=((wddata-500)/100)%10;
								leds_buffer[2]=((wddata-500)/10)%10;
								}
							
							}
							else
							{
								if(wddata>=600)
								{
									 leds_buffer[0]=((wddata-500)/100)%10;
								}
								else
								{
									 leds_buffer[0]=28;
								}
							
								leds_buffer[1]=((wddata-500)/10)%10+10;
								leds_buffer[2]=((wddata-500))%10;
							}				
						}
						else
						{
								if(wddata>400)
								{
									   leds_buffer[0]=27;
									   leds_buffer[1]=(((500-wddata)/10)%10)+10;
									   leds_buffer[2]=((500-wddata))%10;
								}
								else
								{
									if(wddata>=100)
									{
									  leds_buffer[0]=27;
									   leds_buffer[1]=((500-wddata)/100)%10;
									   leds_buffer[2]=((500-wddata)/10)%10;
									}
									else
									{
										leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=29;
									}
								}
						}
						if(pldata>0)
						{
							if(pldata<1000)
							{
								leds_buffer[3]=(pldata/100)%10;
								leds_buffer[4]=((pldata/10)%10)+10;
								leds_buffer[5]=pldata%10;
							}
//							else
//							{
//									leds_buffer[3]=1;
//						 			leds_buffer[4]=0;
//									leds_buffer[5]=0;
//							}
						}
					
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
		
			}
			else
			{
				if(therr2==1)
				{
						if(wddata2>=500)
						{
						
							if(wddata2>=1500)
							{
								if(wddata2>=1700)
								{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=21;
								}  
								else
								{
								leds_buffer[0]=(wddata2-500)/1000;
								leds_buffer[1]=((wddata2-500)/100)%10;
								leds_buffer[2]=((wddata2-500)/10)%10;
								}
							
							}
							else
							{
								if(wddata2>=600)
								{
									 leds_buffer[0]=((wddata2-500)/100)%10;
								}
								else
								{
									 leds_buffer[0]=28;
								}
							
								leds_buffer[1]=((wddata2-500)/10)%10+10;
								leds_buffer[2]=((wddata2-500))%10;
							}				
						}
						else
						{
								if(wddata2>400)
								{
									   leds_buffer[0]=27;
									   leds_buffer[1]=(((500-wddata2)/10)%10)+10;
									   leds_buffer[2]=((500-wddata2))%10;
								}
								else
								{
									if(wddata2>=100)
									{
									  leds_buffer[0]=27;
									   leds_buffer[1]=((500-wddata2)/100)%10;
									   leds_buffer[2]=((500-wddata2)/10)%10;
									}
								
									else
									{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=29;
									
									}
								}
						}
						if(pldata2>0)
						{
							if(pldata2<1000)
							{
								leds_buffer[3]=(pldata2/100)%10;
								leds_buffer[4]=((pldata2/10)%10)+10;
								leds_buffer[5]=pldata2%10;
							}
							else
							{
									leds_buffer[3]=1;
						 			leds_buffer[4]=0;
									leds_buffer[5]=0;
							}
						}
					
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			}
		
				#endif
				
					#if(xxh==5)

			if(showalltime<500)
			{
				if(therr1==1)
				{
						if(wddata>=500)
						{
						
							if(wddata>=1500)
							{
								if(wddata>=1700)
								{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=21;
								}  
								else
								{
								leds_buffer[0]=(wddata-500)/1000;
								leds_buffer[1]=((wddata-500)/100)%10;
								leds_buffer[2]=((wddata-500)/10)%10;
								}
							
							}
							else
							{
								if(wddata>=600)
								{
									 leds_buffer[0]=((wddata-500)/100)%10;
								}
								else
								{
									 leds_buffer[0]=28;
								}
							
								leds_buffer[1]=((wddata-500)/10)%10+10;
								leds_buffer[2]=((wddata-500))%10;
							}				
						}
						else
						{
								if(wddata>400)
								{
									   leds_buffer[0]=27;
									   leds_buffer[1]=(((500-wddata)/10)%10)+10;
									   leds_buffer[2]=((500-wddata))%10;
								}
								else
								{
									if(wddata>=100)
									{
									  leds_buffer[0]=27;
									   leds_buffer[1]=((500-wddata)/100)%10;
									   leds_buffer[2]=((500-wddata)/10)%10;
									}
									else
									{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=29;
									}
								}
						}
					
					
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
		
			}
			else
			{
				if(therr2==1)
				{
						if(wddata2>=500)
						{
						
							if(wddata2>=1500)
							{
								if(wddata2>=1700)
								{
									leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=21;
								}  
								else
								{
								leds_buffer[0]=(wddata2-500)/1000;
								leds_buffer[1]=((wddata2-500)/100)%10;
								leds_buffer[2]=((wddata2-500)/10)%10;
								}
							
							}
							else
							{
								if(wddata2>=600)
								{
									 leds_buffer[0]=((wddata2-500)/100)%10;
								}
								else
								{
									 leds_buffer[0]=28;
								}
							
								leds_buffer[1]=((wddata2-500)/10)%10+10;
								leds_buffer[2]=((wddata2-500))%10;
							}				
						}
						else
						{
								if(wddata2>400)
								{
									   leds_buffer[0]=27;
									   leds_buffer[1]=(((500-wddata2)/10)%10)+10;
									   leds_buffer[2]=((500-wddata2))%10;
								}
								else
								{
									if(wddata2>=100)
									{
									  leds_buffer[0]=27;
									   leds_buffer[1]=((500-wddata2)/100)%10;
									   leds_buffer[2]=((500-wddata2)/10)%10;
									}
									else
									{
    								leds_buffer[0]=28;
									leds_buffer[1]=34;
									leds_buffer[2]=29;
									}
								}
						}		
					
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			}
		
				#endif	


				#if((xxh==6))
	   if(showalltime<500)
			{
				 if(therr1==1)
				{
					
						if(pldata>0)
						{
							if(pldata<1000)
							{
								leds_buffer[0]=(pldata/100)%10;
								leds_buffer[1]=((pldata/10)%10)+10;
								leds_buffer[2]=pldata%10;
							}
							else
							{
									leds_buffer[0]=1;
						 			leds_buffer[1]=0;
									leds_buffer[2]=0;
							}
						}
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			}
			else
			{
			   if(therr2==1)
				{
					
						if(pldata2>0)
						{
							if(pldata2<1000)
							{
								leds_buffer[0]=(pldata2/100)%10;
								leds_buffer[1]=((pldata2/10)%10)+10;
								leds_buffer[2]=pldata2%10;
							}
							else
							{
									leds_buffer[0]=1;
						 			leds_buffer[1]=0;
									leds_buffer[2]=0;
							}
						}
					
				}
				else
				{
					if((showerrtime%20)>10)
					{
							leds_buffer[0]=25;
				 			leds_buffer[1]=26;
							leds_buffer[2]=26;
							leds_buffer[3]=25;
				 			leds_buffer[4]=26;
							leds_buffer[5]=26;
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
			}
			#endif
	
}


void meumtnt(unsigned char tempjj,unsigned char tempmax,unsigned char tempmin)
{
#if((xxh==1)||(xxh==4))
{
		if(th[tempjj]>=50)
			{
				leds_buffer[3]=(th[tempjj]-50)/100;
				leds_buffer[4]=(th[tempjj]-50)%100/10;
				leds_buffer[5]=(th[tempjj]-50)%10;

			}
			else
			{
			
				leds_buffer[3]=27;
				leds_buffer[4]=(50-th[tempjj])%100/10;
				leds_buffer[5]=(50-th[tempjj])%10;
			}
			if((th[tempjj])>tempmax)th[tempjj]=tempmax;	
			if((th[tempjj])<tempmin)th[tempjj]=tempmin;	
}
#endif
#if((xxh==2)||(xxh==3)||(xxh==5)||(xxh==6))
{
		if(th[tempjj]>=50)
			{
				leds_buffer[0]=(th[tempjj]-50)/100;
				leds_buffer[1]=(th[tempjj]-50)%100/10;
				leds_buffer[2]=(th[tempjj]-50)%10;

			}
			else
			{
			
				leds_buffer[0]=27;
				leds_buffer[1]=(50-th[tempjj])%100/10;
				leds_buffer[2]=(50-th[tempjj])%10;
			}
			if((th[tempjj])>tempmax)th[tempjj]=tempmax;	
			if((th[tempjj])<tempmin)th[tempjj]=tempmin;	
}
#endif
			
						
}

 void showkeyview(unsigned char  tempshows)
{

	switch(tempshows)
	{
	#if((xxh==1)||(xxh==4))
		case 1:
		{		
			leds_buffer[0]=20;					  //加热1上
			leds_buffer[1]=1;
			leds_buffer[2]=23;		 
			meumtnt(1,180,10);
			 if((th[1])<=th[2]) th[showjj]++;
		}
		break;
		case 2:								//加热1下
		{
		 	leds_buffer[0]=20;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
			meumtnt(2,180,10);	
			if((th[1])<=th[2]) th[showjj]--;
		}
		break;
	#endif
		#if((xxh==2)||(xxh==5))
		case 1:
		{
			if(showcccc==0)	
			{	
			leds_buffer[0]=20;					  //加热1上
			leds_buffer[1]=1;
			leds_buffer[2]=23;	
			}
			else
			{	 
			meumtnt(1,180,10);
			 if((th[1])<=th[2]) th[showjj]++;
			 }
		}
		break;
		case 2:								//加热1下
		{
			if(showcccc==0)	
			{
		 	leds_buffer[0]=20;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
			}
			else
			{
				meumtnt(2,180,10);	
			if((th[1])<=th[2]) th[showjj]--;
			}

		}
		break;
	#endif
		#if((xxh==1)||(xxh==4))
		case 3:									 //湿度加热1
		{
			leds_buffer[0]=21;					  
			leds_buffer[1]=1;
			leds_buffer[2]=23;
			leds_buffer[3]=th[showjj]/100;
			leds_buffer[4]=th[showjj]%100/10;
			leds_buffer[5]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[3])<=th[4]) th[showjj]++;
		}
		break;
		case 4:
		{
			leds_buffer[0]=21;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
			leds_buffer[3]=th[showjj]/100;
			leds_buffer[4]=th[showjj]%100/10;
			leds_buffer[5]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=0;	
				if((th[3])<=th[4]) th[showjj]--;
		}
		break;
		#endif
		#if((xxh==3)||(xxh==6) )
		case 3:									 //湿度加热1
		{
		if(showcccc==0)	
			{
			leds_buffer[0]=21;					  
			leds_buffer[1]=1;
			leds_buffer[2]=23;
			}
			else
			{
			leds_buffer[0]=th[showjj]/100;
			leds_buffer[1]=th[showjj]%100/10;
			leds_buffer[2]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[3])<=th[4]) th[showjj]++;
				}
		}
		break;
		case 4:
		{
			if(showcccc==0)	
			{
			leds_buffer[0]=21;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
			}
			else
			{
			leds_buffer[0]=th[showjj]/100;
			leds_buffer[1]=th[showjj]%100/10;
			leds_buffer[2]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=0;	
				if((th[3])<=th[4]) th[showjj]--;
				}
		}
		break;
		#endif
		#if((xxh==1)||(xxh==4) )
		case 5:									  //排1
		{
			leds_buffer[0]=22;					  
			leds_buffer[1]=1;
			leds_buffer[2]=23;		 

				meumtnt(5,180,10);
			if((th[5])<=th[6]) th[showjj]++;
		}
		break;
		case 6:
		{
			leds_buffer[0]=22;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
				meumtnt(6,180,10);	
			if((th[5])<=th[6]) th[showjj]--;
		}
		break;
		#endif
		#if(xxh==2)
		case 5:									  //排1
		{
			if(showcccc==0)	
			{
			leds_buffer[0]=22;					  
			leds_buffer[1]=1;
			leds_buffer[2]=23;
			}		 
			 else
			 {
				meumtnt(5,180,10);
			if((th[5])<=th[6]) th[showjj]++;
			}
		}
		break;
		case 6:
		{
			if(showcccc==0)	
			{
			leds_buffer[0]=22;					  
			leds_buffer[1]=1;
			leds_buffer[2]=24;
			}
			else
			{
				meumtnt(6,180,10);	
				if((th[5])<=th[6]) th[showjj]--;
			}
		}
		break;
		#endif
		#if(xxh==4)
		case 7:
		{		
			leds_buffer[0]=20;					  //加热2上
			leds_buffer[1]=2;
			leds_buffer[2]=23;		 

				meumtnt(7,180,10);	
			if((th[7])<=th[8]) th[showjj]++;
		}
		break;
		case 8:
		{
		 	leds_buffer[0]=20;					  
			leds_buffer[1]=2;
			leds_buffer[2]=24;
				meumtnt(8,180,10);	
			if((th[7])<=th[8]) th[showjj]--;

		
		}
		break;
		case 9:
		{
			leds_buffer[0]=21;					  
			leds_buffer[1]=2;
			leds_buffer[2]=23;
			leds_buffer[3]=th[showjj]/100;
			leds_buffer[4]=th[showjj]%100/10;
			leds_buffer[5]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[9])<=th[10]) th[showjj]++;
		}
		break;
		case 10:
		{
		  leds_buffer[0]=21;					  
			leds_buffer[1]=2;
			leds_buffer[2]=24;
			leds_buffer[3]=th[showjj]/100;
			leds_buffer[4]=th[showjj]%100/10;
			leds_buffer[5]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[9])<=th[10]) th[showjj]--;
		}
		break;
		#endif
		#if(xxh==5)
		case 7:
		{
		
			if(showcccc==0)	
			{		
			leds_buffer[0]=20;					  //加热2上
			leds_buffer[1]=2;
			leds_buffer[2]=23;		 
			}
			else
			{
				meumtnt(7,180,10);	
				if((th[7])<=th[8]) th[showjj]++;
			}
		}
		break;
		case 8:
		{
			if(showcccc==0)	
			{
		 	leds_buffer[0]=20;					  
			leds_buffer[1]=2;
			leds_buffer[2]=24;
			}
			else
			{
				meumtnt(8,180,10);	
				if((th[7])<=th[8]) th[showjj]--;
			}
		
		}
		break;
		#endif
			#if(xxh==6)
		case 9:
		{
		if(showcccc==0)	
			{
			leds_buffer[0]=21;					  
			leds_buffer[1]=2;
			leds_buffer[2]=23;
			}
			else
			{
			leds_buffer[0]=th[showjj]/100;
			leds_buffer[1]=th[showjj]%100/10;
			leds_buffer[2]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[9])<=th[10]) th[showjj]++;
				}
		}
		break;
		case 10:
		{
		if(showcccc==0)	
			{
		  leds_buffer[0]=21;					  
			leds_buffer[1]=2;
			leds_buffer[2]=24;
			}
			else
			{
			leds_buffer[0]=th[showjj]/100;
			leds_buffer[1]=th[showjj]%100/10;
			leds_buffer[2]=th[showjj]%10;

			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<1)th[showjj]=1;	
				if((th[9])<=th[10]) th[showjj]--;
				}
		}
		break;
		 #endif
		case 11:
		{
			
			leds_buffer[0]=22;					  
			leds_buffer[1]=2;
			leds_buffer[2]=23;		 

				meumtnt(11,180,10);
		
			if((th[11])<=th[12]) th[showjj]++;
		}
		break;
		case 12:
		{
			
			leds_buffer[0]=22;					  
			leds_buffer[1]=2;
			leds_buffer[2]=24;		

				meumtnt(12,180,10);	
			if((th[11])<=th[12]) th[showjj]--;
		}
		break;
	#if((xxh==1)||(xxh==4))
		case 13:
		{
			leds_buffer[0]=30;					  
			leds_buffer[1]=31;
			leds_buffer[2]=31;
			leds_buffer[3]=th[13]/100;
			leds_buffer[4]=th[13]%100/10;
			leds_buffer[5]=th[13]%10;
		
			if((th[13])>247)th[13]=1;	
			if((th[13])==0)th[13]=247;	
	
		}
		break;
		case 14:
		{

			leds_buffer[0]=32;					  
			leds_buffer[1]=33;
			leds_buffer[2]=31;
		
			if(th[14]==0)
			{
				leds_buffer[3]=4;
				leds_buffer[4]=8;
				leds_buffer[5]=0;
			}
			else
			{
				leds_buffer[3]=9;
				leds_buffer[4]=6;
				leds_buffer[5]=0;
			}
	
		}
		break; 
		#endif
			#if((xxh==2)||(xxh==3)||(xxh==5))
		case 13:
		{
		if(showcccc==0)
		{
			leds_buffer[0]=30;					  
			leds_buffer[1]=31;
			leds_buffer[2]=31;
			}
			else
			{
			leds_buffer[0]=th[13]/100;
			leds_buffer[1]=th[13]%100/10;
			leds_buffer[2]=th[13]%10;
		
			if((th[13])>247)th[13]=1;	
			if((th[13])==0)th[13]=247;	
			}
	
		}
		break;
		case 14:
		{
		   if(showcccc==0)
		   {
			leds_buffer[0]=32;					  
			leds_buffer[1]=33;
			leds_buffer[2]=31;
		   }
		   else
		   {
				if(th[14]==0)
				{
					leds_buffer[0]=4;
					leds_buffer[1]=8;
					leds_buffer[2]=0;
				}
				else
				{
					leds_buffer[0]=9;
					leds_buffer[1]=6;
					leds_buffer[2]=0;
				}
			}
	
		}
		break;
		#endif
		#if (xxh==1)
		
		case 15:
		{

			leds_buffer[0]=20;					  
			leds_buffer[1]=30;
			leds_buffer[2]=29;		

				meumtnt(15,130,10);
	
	
		}
		break;
	case 16:
		{

			leds_buffer[0]=21;					  
			leds_buffer[1]=30;
			leds_buffer[2]=29;		

			
				leds_buffer[3]=(th[showjj])/100;
				leds_buffer[4]=(th[showjj])%100/10;
				leds_buffer[5]=(th[showjj])%10;

			
			if((th[showjj])>100)th[showjj]=100;	
		//	if((th[showjj])<5)th[showjj]=5;	
	
		}		
		break;
		#endif
	}
}