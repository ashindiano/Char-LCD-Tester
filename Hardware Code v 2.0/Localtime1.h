#include<pic.h>

struct Local_Date_Structure
{
	unsigned char day1;
	unsigned char day2;
	unsigned char colon1;
	unsigned char month1;
	unsigned char month2;
	unsigned char colon2;
	unsigned char year1;
	unsigned char year2;
	unsigned char year3;
	unsigned char year4;
};
struct Local_Date_Structure *Local_Date;
struct Local_Time_Structure
{
	unsigned char hour2;
	unsigned char hour1;
	unsigned char colon1;
	unsigned char minute2;
	unsigned char minute1;
	unsigned char colon2;
	unsigned char second2;
	unsigned char second1;
};
struct Local_Time_Structure *Local_Time;
unsigned char local_time_disp[9],local_date_disp[11];
void local_clock_init(void);
unsigned int tmr0_count;
bit CTIME_DISP_FLAG;