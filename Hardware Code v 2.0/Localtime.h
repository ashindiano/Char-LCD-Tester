int _5ms_sec,sec, min,hour,today,month,year;
unsigned char SEC[3],MIN[3],HOUR[3],TIME[9];
unsigned char TODAY[3],MONTH[3],YEAR[4],DATE[11];
unsigned char time_temp;
void CREATE_TIME_STRING();
void CREATE_DATE_STRING();
void local_clock_init();
void time_polling();