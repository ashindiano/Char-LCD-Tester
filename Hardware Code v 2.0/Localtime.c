#include<pic.h>
#include "Localtime.h"
#include<stdlib.h>
#include<string.h>
void CREATE_DATE_STRING(void)
{
	itoa(MONTH,month,10);
	itoa(TODAY,today,10);
	itoa(YEAR,year,10);
	if(strlen(TODAY)== 1)
	{
		time_temp = TODAY[0];
		TODAY[0] = '0';
		TODAY[1] = time_temp;
		TODAY[2] = '\0';
	}
	if(strlen(MONTH)== 1)
	{
		time_temp = MONTH[0];
		MONTH[0] = '0';
		MONTH[1] = time_temp;
		MONTH[2] = '\0';
	}
	strcpy(DATE,"  :  :   ");
	DATE[0] = TODAY[0];
	DATE[1] = TODAY[1]; 
	DATE[3] = MONTH[0];
	DATE[4] = MONTH[1]; 
	DATE[6] = YEAR[0];
	DATE[7] = YEAR[1]; 
	DATE[8] = YEAR[2];
	DATE[9] = YEAR[3]; 
	DATE[10] = '\0';
}
void CREATE_TIME_STRING(void)
{
	itoa(SEC,sec,10);
	itoa(MIN,min,10);
	itoa(HOUR,hour,10);
	if(strlen(SEC)== 1)
	{
		time_temp = SEC[0];
		SEC[0] = '0';
		SEC[1] = time_temp;
		SEC[2] = '\0';
	}
	if(strlen(MIN)== 1)
	{
		time_temp = MIN[0];
		MIN[0] = '0';
		MIN[1] = time_temp;
		MIN[2] = '\0';
	}
	if(strlen(HOUR)== 1)
	{
		time_temp = HOUR[0];
		HOUR[0] = '0';
		HOUR[1] = time_temp;
		HOUR[2] = '\0';
	}
	strcpy(TIME,"  :  :");
	TIME[0] = HOUR[0];
	TIME[1] = HOUR[1]; 
	TIME[3] = MIN[0];
	TIME[4] = MIN[1]; 
	TIME[6] = SEC[0];
	TIME[7] = SEC[1]; 
	TIME[8] = '\0';
}

void time_polling(void)
{
	if(TMR1IF)
	{
		TMR1IF = 0;
		TMR1H = 0x3C;     // preset for timer1 MSB register
		TMR1L = 0xB0;
		_5ms_sec++;
		if(_5ms_sec == 20)
		{
			_5ms_sec = 0;
			sec++;
			if(sec == 60)
			{
				sec = 0;
				min++;
				if(min == 60)
				{
					min =0;
					hour++;
					if(hour == 24)
					{
						hour = 0;
						today++;
						if(today > 27)
						{
							if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && today == 31)
							{
								today = 0;
							}
							else if((month == 4 || month == 6 || month == 9 || month == 12 )&& today == 30)
							{
								today = 0;
								month++;
							}
							else if(month ==2 && year%4==0 && today == 29)
							{
								today = 0;
								month++;
							}
							else if(month ==2 && year%4!=0 && today == 28)
							{
								today = 0;
								month++;
							}
							if(month == 12)
							{
								year++;
								if(year == 9999)
								year = 0;
							}
						}
					}
				}
			}
		}
	}
} 
void local_clock_init(void)
{
	sec = hour = min = 0;
	year = 2013;
	today = 7;
	month = 3;
	T1CKPS1 = 0;// bits 5-4  Prescaler Rate Select bits
	T1CKPS0 = 1;
	T1OSCEN = 0;// bit 3 Timer1 Oscillator Enable Control: bit 1=on
//	T1SYNC  = 1;// bit 2 Timer1 External Clock Input Synchronization Control bit: 1=Do not synchronize external clock input
	TMR1CS  = 0;// bit 1 Timer1 Clock Source Select bit: 0=Internal clock (FOSC/4) / 1 = External clock from pin T1CKI (on the rising edge)
	TMR1ON  = 1;// bit 0 enables timer
	PEIE =1;
	GIE = 1;
	TMR1IE = 1;
	TMR1H = 0x3C;     // preset for timer1 MSB register
	TMR1L = 0xB0;
}
