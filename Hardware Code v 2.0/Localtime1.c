#include<pic.h>
#include "Localtime1.h"
void local_clock_init(void)
{
	T0IE = 1;  // Interrupt disabled SInce polling method is preffered 
	T0IF = 0;
	PS0 = 1;
	PS1 = 0;
    PS2 = 0; // prescalar 1:4
	TMR0 =6; //initial Value
	CTIME_DISP_FLAG = 0 ;
}
