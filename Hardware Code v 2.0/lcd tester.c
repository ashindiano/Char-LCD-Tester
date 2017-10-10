                                    
/*
LCD TESTER v 2.0

Serial Interface Available for the device
															///////////////////////////
																Author - Ash Indiano
															///////////////////////////

THE IMPORTANT FACTOR ABOUT THIS PROGRAM IS THE POWER SHOULD BE RESET AFTER THE MODE  SELECT
In 4 Bit Mode, Lower nibble of the LCD module is interfaced

Ignore the Hardawre Stack error  -- Program Verified with the hardware
*/

#include<pic.h>
#include<string.h>
#include "Localtime.h"
#define _XTAL_FREQ 8e6
                                        //Defined for __delay_ms,__delay_us functions
#define		PB(p,b) 			((unsigned)&(p)*8+(b))
/******* LCD Definitions********/
#define RS   RC0 //
#define EN   RC1  //
#define RW 	 RC2
#define STATUS_LED_ON RC3=1
#define STATUS_LED_OFF RC3=0
#define databits PORTB
#define _4bit_mode 1
#define _8bit_mode 0

#define clear_2nd_line		lcd_cmd(0xc0),lcd_string("                ");
#define clear_1st_line		lcd_cmd(0x80),lcd_string("                ");

bit MODE,CTIME_DISP_FLAG;
unsigned char str_set1[17];
/*****LCD Definitions ends******/


/***********PS2 Keyboar**************/
#define PS2Key_BUF_SIZE   16                  /* Size of PS2 keyboard buffer */
#define PS2Key_START      1                  /* Start bit for PS/2 protocol */
#define PS2Key_PARITY     10                  /* Parity bit for PS/2 protocol */
#define PS2Key_STOP       11                  /* Stop bit for PS/2 protocol */



#define		ON					1
#define		OFF					0
#define		TRUE				1
#define		FALSE				0


bit			KBD_CLK 	 	@	 PB(PORTB,0);                           
bit			KBD_DATA	 	@	 PB(PORTB,1);
#define     KBD_ON				RC4=1,STATUS_LED_ON;
#define     KBD_OFF				RC4=0,STATUS_LED_OFF;


unsigned char KEY_CODE,KEY_POINTER,SCAN_CODE;

unsigned char bit_count;
bit	ready_flag;

bit PS2_KEYDATA_STATE,PS2_PARITY,PS2_BREAKCODE,PS2_SHIFT,PS2_SPL_BREAKCODE,PS2_SPL_KEY; 

/***********PS2 Keyboar**************/
/*******************************LCD MENU******************/
bit LCD_PAGE_FLAG;
unsigned char choice;
/*********************************************************/
/****serial Definitions*********/

#define NEWLINE send_byte('\r'),send_byte('\n');
#define SERIAL_OFF 
bank1 unsigned char RECIEVED_BYTE, rec_string[22],rec_count;  
bit RECIEVED_FLAG;
/****Serial Definitions ends******/
void EEPROM_putc(unsigned char address, unsigned char data);
unsigned char EEPROM_getc(unsigned char address);
/*----------------PIC INITIALIZATION------------*/
void pic_init(void)
{
    TRISC= 0;
   	TRISB=0x03;
	PORTB=0x00;
	STATUS_LED_ON;
	rec_count=0;
}
/*------------STATUS LED BLINK------------------*/ 
	
void led_blink(int i)
{
	while(i--)
	{
		STATUS_LED_ON;
		__delay_ms(50);
		STATUS_LED_OFF;
		__delay_ms(50);
	}
	if(RC4 == 1)
	STATUS_LED_ON;
}
/*-------------LCD FUNCTIONS BEGIN--------------*/
void LCD_STROBE(void)
{
    EN = 1;
	__delay_us(1);
    EN = 0;
}

void data_4bit(unsigned char c)
{
    RS = 1;
    __delay_us(50);
    databits = (c);    
    LCD_STROBE();
	databits = (c << 4);
    LCD_STROBE();
}

void data_8bit(unsigned char c)
{
	databits = c;	
	__delay_ms(1);
    RS = 1;
	RW=0;
    LCD_STROBE();
}
unsigned char data_8bit_read(void)
{
	RS =1;
	RW= 1;
	LCD_STROBE();
	return(databits);
}
void lcd_data(unsigned char data)
{
	if(MODE==_4bit_mode)
	data_4bit(data);
	else if(MODE==_8bit_mode)
    data_8bit(data);
}
void cmd_4bit(unsigned char c)
{
    RS = 0;
    __delay_us(50);
    databits = (c);
    LCD_STROBE();
    databits = (c << 4);
    LCD_STROBE();
}

void cmd_8bit(unsigned char c)
{
    databits = c;
    RS = 0;
//	RW=0;
    LCD_STROBE();
}
void lcd_cmd(unsigned char cmd)
{
	if(MODE==_4bit_mode)
	cmd_4bit(cmd);
	else if(MODE==_8bit_mode)
    cmd_8bit(cmd);
}
void lcd_clear(void)
{
    lcd_cmd(0x01);
	__delay_ms(2);

}

void lcd_4bit_init(void)
{
	MODE = _4bit_mode;
	TRISB =0x03;
	KBD_ON;
    __delay_ms(15);
    cmd_4bit(0x38);
    __delay_ms(1);
    cmd_4bit(0x38);
    __delay_us(100);
    cmd_4bit(0x38);
    cmd_4bit(0x28);            // Function set (4-bit interface, 2 lines, 5*7Pixels)
    cmd_4bit(0x28);            // Function set (4-bit interface, 2 lines, 5*7Pixels)
    cmd_4bit(0x0c);            // Make cursorinvisible
    cmd_4bit(0x01);
    __delay_ms(2);            // Clear screen
    cmd_4bit(0x6);            // Set entry Mode(auto increment of cursor)
}
 
void lcd_8bit_init(void)
{
	MODE = _8bit_mode;
	TRISB =0x00;
	KBD_OFF;
	__delay_ms(5);
	cmd_8bit(0x38);
	__delay_ms(1);
	cmd_8bit(0x38);
	__delay_ms(1);
	cmd_8bit(0x06);
	__delay_ms(1);
	cmd_8bit(0x0c);
	__delay_ms(1);
}
void lcd_init(void)
{
	if(MODE==_4bit_mode)
	lcd_4bit_init();
	else if(MODE==_8bit_mode)
	lcd_8bit_init();
}

void lcd_string(const char *q)
{
    while (*q) {
		
//		led_blink(1);
		if(MODE==_4bit_mode)
        data_4bit(*q++);
		else
		data_8bit(*q++);
    }
}
void lcd_read_string(unsigned char *q, unsigned char i)
{
    while (i--) {
		
//		led_blink(1);
	
		(*q++) = data_8bit_read();
    }
}
void lcd_1(const char *q)
{
	clear_1st_line;
	lcd_cmd(0x80);
	lcd_string(q);
}
void lcd_2(const char *q)
{
	clear_2nd_line;
	lcd_cmd(0xc0);
	lcd_string(q);
}
/*-------------LCD END--------------------*/
/*---------- Serial ---------------------*/
unsigned char lowtoup_case(unsigned char ch)
{
	if(ch > 96 && ch < 123)
	return ch-32;
	return ch;
}

void SERIAL_INIT(void)
{
	TRISC=0x80;
	GIE=1;
	PEIE=1;
	SPBRG=53;
	BRGH=1;
	SYNC=0;
	SPEN=1;
	TXEN=1;
	RCIE=0;
	CREN=1;
}

void send_byte(const unsigned char val)
{
	TXREG=val;
	while(!TXIF);
	TXIF=0;
	__delay_ms(1); //This delay is included due to a random error in transmission
}

void send_string(const unsigned char *str)
{
	while(*str)
	{
		send_byte(*str++);
	}
}
void Amode_off(void)
{
	EEPROM_putc(0x0f,0x00);
	send_string("Auto Swap Mode DeActivated...");
	NEWLINE;
	lcd_1(" Auto Swap Mode ");
	lcd_2("   DEACTIVATED  ");
}

void Amode_on(void)
{
		EEPROM_putc(0x0f,'A');
		send_string("MODE Set to Auto Swap Mode ");
		NEWLINE;NEWLINE;
		send_string("Auto Swap Mode Activated..  Mode Would change on every Reset.....");
		NEWLINE;
		lcd_1(" Auto Swap Mode ");
		lcd_2("    ACTIVATED   ");
}
void mode_8_set(void)
{
		EEPROM_putc(0xf0,'8');
		send_string("MODE Set to 8 Bit Mode ");
		NEWLINE;NEWLINE;
		send_string("MANUAL POWER RESET Required to change Mode..............");
		NEWLINE;
		lcd_1("  MANUAL POWER  ");
		lcd_2(" RESET REQUIRED ");
}
void mode_4_set(void)
{
		EEPROM_putc(0xf0,'4');
		send_string("MODE Set to 4 Bit Mode ");
		NEWLINE;NEWLINE;
		send_string("MANUAL POWER RESET Required to change Mode..............");
		NEWLINE;
		lcd_1("  MANUAL POWER  ");
		lcd_2(" RESET REQUIRED ");
}
void ctime(void)
{
	CTIME_DISP_FLAG =1;
	CREATE_TIME_STRING();
	send_string("Current Time : ");
	send_string(TIME);
	lcd_1("Current Time    ");
	clear_2nd_line;
	lcd_2(TIME);
}
void cdate(void)
{
	CREATE_DATE_STRING();
	send_string("Current Date : ");
	send_string(DATE);
	lcd_1("Current Date    ");
	clear_2nd_line;
	lcd_2(DATE);
}
int EXEC_COMMAND(void )
{	
	unsigned char temp[7],temp1[17];
	int i;
	
	for(i=0;i<6;i++)
	temp[i] = rec_string[i];
	temp[6]='\0';
	if(rec_count > 5 && rec_count < 23)
	{
		for(i=0;i<rec_count-6;i++)
		temp1[i] = rec_string[i+6];
		temp1[rec_count-6]= '\0';
		if(strcmp(temp,"LCD.1 ")==0)
		{	
			send_string("Sending Data to LCD's 1st Line ");
			NEWLINE;NEWLINE;
			send_string(temp1);
			lcd_1(temp1);
			send_string(" Sent...");
			NEWLINE;NEWLINE;
			temp1[0] = temp[0] = '\0';
			return 0;
		}
		else if(strcmp(temp,"LCD.2 ")==0)
		{
			send_string("Sending Data to LCD's 2nd Line");
			NEWLINE;NEWLINE;
			lcd_2(temp1);
			send_string(" Sent...");
			NEWLINE;NEWLINE;
			temp1[0] = temp[0] = '\0';
			return 0;
		}
		else if(strcmp(temp,"CTIME ")==0)
		{
			send_string("Recieved Current Time...");
			NEWLINE;NEWLINE;
			lcd_1("  Current Time  ");
			lcd_2(temp1);
			strcpy(TIME,temp1); //synching local clock with pc time
			send_string(" Sent...");
			NEWLINE;NEWLINE;
			temp1[0] = temp[0] = '\0';
			return 0;
		}
		else if(strcmp(temp,"CDATE ")==0)
		{
			send_string("Recieved Current Date");
			NEWLINE;NEWLINE;
			lcd_1("  Current Date  ");
			lcd_2(temp1);
			strcpy(DATE,temp1);
			send_string(" Sent...");
			__delay_ms(1000);
			lcd_2("    Updated     ");
			__delay_ms(1000);
			lcd_clear();
			lcd_1("      Enter     ");
			lcd_2("     Command    ");
			NEWLINE;NEWLINE;
			temp1[0] = temp[0] = '\0';
			return 0;
		}
	} 
	if(strcmp(temp,"LCD.1 ")!=0 || strcmp(temp,"LCD.2 ")!=0 || strcmp(temp,"CDATE ")!=0 ||strcmp(temp,"CDATE ")!=0)
	{
		if(strcmp(rec_string,"RUN")==0)
		{
			send_string("RUN command Executed");
		}
		else if(strcmp(rec_string,"STOP")==0)
		{
			send_string("STOP command Executed");
		}
		else if(strcmp(rec_string,"WHO")==0)
		{
			send_string("LCD TESTER");
		}
		else if(strcmp(rec_string,"MODE?")==0)
		{
			send_string("Current Mode is : ");
			if(MODE==_4bit_mode)
			send_string("4 Bit Mode");
			else if(MODE==_8bit_mode)
			send_string("8 Bit Mode");
			NEWLINE;NEWLINE;
			if(EEPROM_getc(0x0f)=='A')
			send_string("Auto Swap Mode is ON");
		}
		else if(strcmp(rec_string,"MODE=4")==0 || strcmp(rec_string,"MODE= 4")==0)
		{
			EEPROM_putc(0xf0,'4');
			send_string("MODE Set to 4 Bit Mode ");
			NEWLINE;NEWLINE;
			send_string("MANUAL POWER RESET Required to change Mode..............");
			NEWLINE;
			lcd_clear();
			lcd_1("  MANUAL POWER  ");
			lcd_2(" RESET REQUIRED ");
		}
		else if(strcmp(rec_string,"MODE=8")==0 || strcmp(rec_string,"MODE= 8")==0)
		mode_8_set();

		else if(strcmp(rec_string,"MODE=A")==0 || strcmp(rec_string,"MODE= A")==0)
		Amode_on();
		
		else if(strcmp(rec_string,"AMODE off")==0 || strcmp(rec_string,"AMODE OFF")==0)
		Amode_off();

		else if(strcmp(rec_string,"MODE=")==0)
		{
			send_string("Arguments required or Invalid Argumets Passed");
		}
		else if(strcmp(rec_string,"HELP")==0)
		{
			send_string("The Commands Authorized are :");
			NEWLINE;NEWLINE;
			send_string("RUN,STOP,LCD.1,LCD.2,MODE?,MODE=,AMODE OFF,HELP");
		}
		else if(strcmp(rec_string,"CTIME?")==0)
		{
			ctime();
		}
		else if(strcmp(rec_string,"CDATE?")==0)
		{
			cdate();
		}
		else
		{
			send_string("Not an Authorized command Type HELP to know the list of Commands");
		}
	}
NEWLINE;
NEWLINE;
temp1[0] = temp[0] = '\0';
return 0;
}
                                                                                                                                
/*---------------serial end--------------*/
/***************EEPROM ********************/
void EEPROM_putc(unsigned char address, unsigned char data)
{
    unsigned char INTCON_SAVE;

    EEADR  = address;
    EEDATA = data;

    EEPGD= 0; // 0 = Access data EEPROM memory
    WREN = 1; // enable writes to internal EEPROM

    INTCON_SAVE=INTCON; // Save INTCON register contants
    INTCON=0;             // Disable interrupts, Next two lines SHOULD run without interrupts
    
    EECON2=0x55;        // Required sequence for write to internal EEPROM
    EECON2=0xaa;        // Required sequence for write to internal EEPROM
	
	WR=1;    // begin write to internal EEPROM
    INTCON=INTCON_SAVE; //Now we can safely enable interrupts if previously used
    
    while (!EEIF);//Wait till write operation complete
   
    WREN=0; // Disable writes to EEPROM on write complete (EEIF flag on set PIR2 )
    EEIF=0; //Clear EEPROM write complete flag. (must be cleared in software. So we do it here)

}

// This function reads data from address given in internal EEPROM of PIC 
unsigned char EEPROM_getc(unsigned char address)
{
    EEADR=address;
	EEPGD= 0; // 0 = Access data EEPROM memory
    RD   = 1; // EEPROM Read
    return EEDATA;       // return data
}
/***************EEPROM END********************/
/*************** LCD MODE SELECT***************/

void mode_select(void)
{
	unsigned char eedata;
	
	eedata = EEPROM_getc(0xf0);
	if(eedata == '4')
	{
		MODE = _4bit_mode;
		EEPROM_putc(0xf1,'0');
		send_string(" Current MODE is 4 Bit Mode...");
		NEWLINE;NEWLINE;
		send_string(" KeyBoard Access Granted ...");
		NEWLINE;NEWLINE;
	}
	else if(eedata == '8')
	{
		MODE = _8bit_mode;
		if(EEPROM_getc(0x0f)!= 'A')
		{
			eedata = EEPROM_getc(0xf1);
			if(eedata == '2')                   // On 3 manual power reset the mode automatically shifts to 4 bit mode for the sake of Keyboard interface
			EEPROM_putc(0xf0,'4');
			else
			EEPROM_putc(0xf1,eedata+1);
		}
		send_string(" Current MODE is 8 Bit Mode...");
		NEWLINE;NEWLINE;
		send_string(" KeyBoard Access Denied ...");
		NEWLINE;NEWLINE;
		send_string(" If KeyBoard is Access Required, Please Manually Reset the Device twice  ...");
		NEWLINE;NEWLINE;
	}
	else
	{
		EEPROM_putc(0xf0,'4');
		EEPROM_putc(0xf1,'0');
		MODE = _4bit_mode;  //Default Selection Made MODE is 4bit mode
		send_string(" Default Mode Chosen");
		NEWLINE;
		send_string(" Current MODE is 4 Bit Mode");
		NEWLINE;NEWLINE;
	}
	
	eedata = EEPROM_getc(0x0f);   // 0x0f is the location where the Auto mode data is stored
	if(eedata == 'A')
	{
		send_string(" Auto Swap Mode is ON ");
		if(MODE == _8bit_mode)
		{
			EEPROM_putc(0xf0,'4');
			MODE = _4bit_mode;
			send_string(" Current MODE is 4 Bit Mode");
		}
		else if(MODE == _4bit_mode)
		{
			EEPROM_putc(0xf0,'8');
			MODE = _8bit_mode;
			send_string(" Current MODE is 8 Bit Mode");
		}		
		NEWLINE;NEWLINE;
	}
}

/******************PS2 KEYBOARD************************/

const unsigned char PS2KeyUnshifted[]={

0x00,   //00
0x00,   //01  F9
0x00,   //02
0x00,   //03  F5
0x00,   //04  F3
0x00,   //05  F1
0x00,   //06  F2   
0x00,   //07  F12
0x00,   //08
0x00,   //09  F10
0x00,   //0A  F8
0x00,   //0B  F6
0x00,   //0C  F4
0x09,   //0D  TAB
'`',   //0E  ` or ~
0x00,   //0F

0x00,   //10
0x00,   //11  Left ALT
0x00,   //12  Left SHIFT
0x00,   //13
0x00,   //14  Left Ctrl
'q',   //15  Q
'1',   //16  1 or !
0x00,   //17
0x00,   //18
0x00,   //19
'z',   //1A  Z
's',   //1B  S
'a',   //1C  A
'w',   //1D  W
'2',   //1E  2 or @
0x00,   //1F

0x00,   //20
'c',   //21  C
'x',   //22  X
'd',   //23  D
'e',   //24  E
'4',   //25  4 or $
'3',   //26  3 or #
0x00,   //27
0x00,   //28
' ',   //29  Space
'v',   //2A  V
'f',   //2B  F
't',   //2C  T
'r',   //2D  R
'5',   //2E  5 or %
0x00,   //2F

0x00,   //30
'n',   //31  N
'b',   //32  B
'h',   //33  H
'g',   //34  G
'y',   //35  Y
'6',   //36  6 or ^
0x00,   //37
0x00,   //38
0x00,   //39
'm',   //3A  M
'j',   //3B  J
'u',   //3C  U
'7',   //3D  7 or &
'8',   //3E  8 or *
0x00,   //3F

0x00,   //40
',',   //41  , or <
'k',   //42  K
'i',   //43  I
'o',   //44  O
'0',   //45  0 or )
'9',   //46  9 or (
0x00,   //47
0x00,   //48
'.',   //49  . or >
'/',   //4A  / or ?
'l',   //4B  L
';',   //4C  ; or :
'p',   //4D  P
'-',   //4E  - or _
0x00,   //4F

0x00,   //50
0x00,   //51
0x27,   //52  ' or "
0x00,   //53
'[',   //54  [ or {
'=',   //55  = or +
0x00,   //56
0x00,   //57
0x00,   //58  Caps Lock
0x00,   //59  Right Shift
'\n',   //5A  Enter
']',   //5B  ] or }
0x00,   //5C
'\'',   //5D  \ or |
0x00,   //5E
0x00,   //5F

0x00,   //60 DOWN Arrow
0x00,   //61 LEFT Arrow
0x00,   //62
0x00,   //63 UP Arrow
0x00,   //64
0x00,   //65
'\b',   //66  Backspace
0x00,   //67
0x00,   //68
'1',   //69  NUM - 1 or END
0x00,  //6A  RIGHT Arrow
'4',   //6B  NUM - 4 or LEFT
'7',   //6C  NUM - 7 or HOME
0x00,   //6D
0x00,   //6E
0x00,   //6F

'0',   //70  NUM - 0 or INS
'.',   //71  NUM - . or DEL
'2',   //72  NUM - 2 or DOWN
'5',   //73  NUM - 5
'6',   //74  NUM - 6 or RIGHT
'8',   //75  NUM - 8 or UP
0x1B,   //76  ESC
0x00,   //77  NUM LOCK
0x00,   //78  F11
'+',   //79  NUM - + (Plus)
'3',   //7A  NUM 3 or PAGE DOWN
'-',   //7B  NUM - - (Minus)
'*',   //7C  NUM - *
'9',   //7D  NUM - 9 or PAGE UP
0x00,   //7E  SCROLL LOCK
0x00,   //7F

0x00,   //80
0x00,   //81
0x00,   //82
0x00,   //83  F7
};

/*
*****************************************************
*                                                   *
*   Shift - Lookup Table Used when Shift Hold       *
*                                                   *
*****************************************************
*/

const unsigned char PS2KeyShifted[]={
     0x00,   //00
     0x00,  //01  F9
     0x00,   //02
     0x00,   //03  F5
     0x00,   //04  F3
     0x00,   //05  F1
     0x00,   //06  F2
     0x00,   //07  F12
     0x00,   //08
     0x00,   //09  F10
     0x00,   //0A  F8
     0x00,   //0B  F6
     0x00,   //0C  F4
     0x09,   //0D  TAB
     '~' ,  //0E  ` or ~
     0x0 ,  //0F

     0x00,  //10
     0x00,   //11  Left ALT
     0x00,   //12  Left SHIFT
     0x00,   //13
     0x00,   //14  Left Ctrl
     'Q' ,  //15  Q
     '!' ,  //16  1 or !
     0x00,   //17
     0x00,   //18
     0x00,   //19
     'Z' ,  //1A  Z
     'S' ,  //1B  S
     'A' ,  //1C  A
     'W' ,  //1D  W
     '@' ,  //1E  2 or @
     0x00,   //1F

     0x00,   //20
     'C' , //21  C
     'X' ,  //22  X
     'D' ,  //23  D
     'E' ,  //24  E
     '$' ,  //25  4 or $
     '#' ,  //26  3 or #
     0x00,   //27
     0x00,   //28
     ' ' ,  //29  Space
     'V' ,  //2A  V
     'F' ,  //2B  F
     'T' ,  //2C  T
     'R' ,  //2D  R
     '%' ,  //2E  5 or %
     0x00,   //2F

     0x00,   //30
     'N' ,  //31  N
     'B' ,  //32  B
     'H' ,  //33  H
     'G' ,  //34  G
     'Y' ,  //35  Y
     '^' ,  //36  6 or ^
     0x00,   //37
     0x00,   //38
     0x00,   //39
     'M' ,  //3A  M
     'J' ,  //3B  J
     'U' ,  //3C  U
     '&' ,  //3D  7 or &
     '*' ,  //3E  8 or *
     0x00,   //3F

     0x0 ,  //40
     '<' ,  //41  , or <
     'K' ,  //42  K
     'I' ,  //43  I
     'O' ,  //44  O
     ')' ,  //45  0 or )
     '(' ,  //46  9 or (
     0x00,   //47
     0x00,   //48
     '>' ,  //49  > or .
     '?' ,  //4A  / or ?
     'L' ,  //4B  L
     ':' ,  //4C  ; or :
     'P' ,  //4D  P
     '_' ,  //4E  - or _
     0x00,   //4F

     0x00,   //50
     0x00,   //51
     0x22,   //52  ' or "
     0x00,   //53
     '{' ,  //54  [ or {
     '+' ,  //55  = OR +
     0x00,   //56
     0x00,   //57
     0x00,   //58  Caps Lock
     0x00,   //59  Right Shift
     0x00,   //5A  Enter
     '}' ,  //5B  ] or }
     0x00,   //5C
     '|' ,  //5D  \ or |
     0x00,   //5E
     0x00,   //5F

     0x00,   //60
     0x00,   //61
     0x00,   //62
     0x00,   //63
     0x00,   //64
     0x00,   //65
     '\b',   //66  Backspace
     0x00,   //67
     0x00,   //68
     '1' ,  //69  NUM - 1 or END
     0x00,   //6A
     '4' ,  //6B  NUM - 4 or LEFT
     '7' ,  //6C  NUM - 7 or HOME
     0x00,   //6D
     0x00,   //6E
     0x00,   //6F

     '0' ,  //70  NUM - 0 or INS
     '.' ,  //71  NUM - . or DEL
     '2' ,  //72  NUM - 2 or DOWN
     '5' ,  //73  NUM - 5
     '6' ,  //74  NUM - 6 or RIGHT
     '8' ,  //75  NUM - 8 or UP
     0x1B,   //76  ESC
     0x00,   //77  NUM LOCK
     0x00,   //78  F11
     '+' ,  //79  NUM - + (Plus)
     '3' ,  //7A  NUM 3 or PAGE DOWN
     '-' ,  //7B  NUM - - (Minus)
     '*' ,  //7C  NUM - *
     '9' ,  //7D  NUM - 9 or PAGE UP
     0x00,   //7E  SCROLL LOCK
     0x00,   //7F

     0x00,   //80
     0x00,   //81
     0x00,   //82
     0x00,   //83  F7
};

/*********SPECIAL KEYBOARD KEYS*********************************************************/

const unsigned char PS2KeySpecial[]={
	0xE0, // 6b  left Arrow
	0x00, // 6c
	0x00, // 6d
	0x00, // 6e
	0x00, // 6f
	0x00, // 70
	0x00, // 71
	0xE3, // 72  Down Arrrow
	0x00, // 73
	0xE1, // 74  Right Arrow
	0xE2, // 75  Up Arrow
	0x00, // 76
	0x00, // 78
	0x00, // 79
	0x00, // 7A
};


/********************************************************************************************************************/
void interrupt ISR(void)
{

   if(INTF)  // Only Keyboard interrupt is recommended to avoid disturbances to keyboard interface
      {
         PS2_KEYDATA_STATE = KBD_DATA;
          bit_count++;
       switch (bit_count)
             {
                case PS2Key_START:
                                 {
                                 //  if(PS2_KEYDATA_STATE || (KBD_CLK))
                                  //    bit_count = 0;
                                       KEY_CODE = 0;
                                       PS2_PARITY = 0;
                                 }
                                 break;
                 case PS2Key_PARITY:
                                   {
                                     PS2_PARITY  =  PS2_KEYDATA_STATE;

                                   }
                                   break;
                 case PS2Key_STOP:
                                  {
 									
                                  	  if ((KEY_CODE == 0x12) || (KEY_CODE==0x59))   // Key=Left shift or right shift
                                      {   
                                         if (PS2_BREAKCODE==TRUE)            
                                             PS2_SHIFT=FALSE;
                                          else
                                             PS2_SHIFT=TRUE;
                                        }
									  else if (KEY_CODE == 0xF0)                  // Is a break code!
                                           {
											PS2_BREAKCODE=TRUE;
											PS2_SPL_KEY = FALSE;
										   }
									  else if (KEY_CODE == 0xE0)
										   PS2_SPL_KEY = TRUE;
					//				  else if (PS2_SPL_KEY==TRUE)
            		//						PS2_SPL_KEY = FALSE;
 									  else if (PS2_BREAKCODE==TRUE)
											{
            									PS2_BREAKCODE = FALSE;
												PS2_SPL_KEY = FALSE;
											}
			                          else if(KEY_CODE < 0x83)
                                            {
											
                                                  SCAN_CODE = KEY_CODE;
                                                   ready_flag =1;           
                                            }
                                          bit_count = 0;
                                     }
                                  break;
                 default:
                         {
                            KEY_CODE = KEY_CODE >> 1;
                            if(PS2_KEYDATA_STATE)
                                KEY_CODE = KEY_CODE |0x80;
                          }
                         break;  
                         
               }
         INTF = 0;
                       
    }// end intf 
 
}//interrupt ends

void PS2Keyboard_init(void)
{
  PEIE=1;
  GIE=1;
  INTE = 1;
  INTF = 0;
  OPTION_REG=0x80;
  PS2_BREAKCODE = FALSE;
  PS2_SHIFT = FALSE;
  KEY_POINTER =0;
	bit_count=0;
	LCD_PAGE_FLAG=0;
}
void str_clear(unsigned char * str)
{
	int i;
	for(i=0;i<17;i++)
	str[i] = '\0';
}

void lcd_page_start(void)
{
	str_clear(str_set1);
	lcd_clear();
	KEY_POINTER = 0;
	lcd_1("Lcd Page Setup ");
	send_string("LCD PAGE SETUP");
	NEWLINE;
	NEWLINE;
	__delay_ms(1000);
	lcd_clear();
	LCD_PAGE_FLAG = 1;
	lcd_1("AUTO SWAP ON    ");
	lcd_2("AUTO SWAP OFF   ");
	lcd_cmd(0x8f);
	lcd_data(0x7f); 
	choice = 1;
}

void lcd_page(unsigned char key)
{
KEY_POINTER = 0;
str_clear(str_set1);
	if (key == 0xE2)
	{
		choice--;
		if(choice == 0)
		choice = 7;
	}
	if (key == 0xE3)
	{
		choice++;
		if(choice == 8)
		choice = 1;
	}
	if(key != '\n')
	switch(choice)
		{
			case 1: 
					lcd_1("AUTO SWAP ON    ");
					lcd_2("AUTO SWAP OFF   ");
					break;	
			case 2: 
					lcd_1("AUTO SWAP OFF    ");
					lcd_2("SET 8 BIT MODE   ");
					break;	
			case 3: 
					lcd_1("SET 8 BIT MODE   ");
					lcd_2("SET 4 BIT MODE   ");
					break;	
			case 4: 
					lcd_1("SET 4 BIT MODE   ");
					lcd_2("CURRENT TIME     ");
					break;	
			case 5:
					lcd_1("CURRENT TIME     ");
					lcd_2("CURRENT DATE     ");
					break;
			case 6:
					lcd_1("CURRENT DATE     ");
					lcd_2("EXIT             ");
					break;
			case 7:
					lcd_1("EXIT             ");
					lcd_2("AUTO SWAP ON     ");
					break;	
		}	
		lcd_cmd(0x8f);
		lcd_data(0x7f);                 //arrow Display in the lcd in the end
		if(key == '\n')
		switch(choice)
		{
			case 1:
				Amode_on();
				break;
			case 2:
				Amode_off();
				break;
			case 3:
				mode_8_set();
				break;
			case 4:
				mode_4_set();
				break;
			case 5:
				ctime();
				break;
			case 6:
				cdate();
				break;
			case 7:
				LCD_PAGE_FLAG = 0;
				lcd_clear();
				lcd_1("4 Bit Mode On   ");
				lcd_2("Keyboard On     ");
				break;
		}
}

void EXEC_COMMAND_FROM_LCD(void)
{
	if(strcmp(str_set1,"START")== 0 || strcmp(str_set1,"start")==0)
	lcd_page_start();
	else if(strcmp(str_set1,"amode off")== 0 || strcmp(str_set1,"AMODE OFF")==0)
	Amode_off();
	
	else if(strcmp(str_set1,"MODE=A")==0 || strcmp(str_set1,"mode=A")==0 || strcmp(str_set1,"mode=a")==0)
	Amode_on();
	else if(strcmp(str_set1,"MODE=8")==0 || strcmp(str_set1,"mode=8")==0)
	mode_8_set();
	else
	{
		lcd_1("Invalid Command ");
		lcd_2("    Recieved    ");
		__delay_ms(1000);
		lcd_clear();
	}
}
/******************PS2 KEYBOARD ENDS********************/
/*************** LCD MODE SELECT***************/
main()
{
	int i;
	unsigned char temp ;
	   	pic_init();
		SERIAL_INIT();
		NEWLINE;
		send_string("/--------------------------------/");
		NEWLINE;
		NEWLINE;
		send_string("   Welcome to LCD Tester v 1.0");
		NEWLINE;
		NEWLINE;
		send_string("   AUTHOR : Ash Indiano  ");
		NEWLINE;
		NEWLINE;
		send_string("/--------------------------------/");
		NEWLINE;
		NEWLINE;
		mode_select();
		lcd_init();
		if(MODE == _4bit_mode)
        {
			for(i=0;i<3;i++)
			{
				clear_1st_line;
				__delay_ms(300);
				lcd_1("4 Bit Mode Works");
				__delay_ms(700);
			}
			lcd_2("KeyBoard On     ");
		}
		else if(MODE == _8bit_mode)
		{
	        for(i=0;i<3;i++)
			{
				clear_1st_line;
				__delay_ms(300);
				lcd_1("8 Bit Mode Works");
				__delay_ms(700);
			}
			lcd_2("KeyBoard OFF   ");
				__delay_ms(700);
			if(EEPROM_getc(0xf1)=='1')
			{
				lcd_1("PowerReset Twice");
				lcd_2("To ON Keyboard  ");
				__delay_ms(700);
			}
		}
		led_blink(5);
		PS2Keyboard_init();	
		local_clock_init();
		 while(1)
		 {
			
		   if(ready_flag)
		      {
				CTIME_DISP_FLAG = 0;
				lcd_clear();
		        ready_flag = 0;
		      	if(PS2_SPL_KEY == TRUE && (LCD_PAGE_FLAG) )
					{
						lcd_page(PS2KeySpecial[SCAN_CODE-0x6b]);
						PS2_SPL_KEY = FALSE;
						PS2_SHIFT = FALSE;
					}
				else if(PS2_SPL_KEY == TRUE && (!LCD_PAGE_FLAG))
					{
						PS2_SPL_KEY = FALSE;
						str_set1[KEY_POINTER]='\0';
						KEY_POINTER--;
					}
		        else if(PS2_SHIFT == TRUE && PS2_SPL_KEY == FALSE)
		           str_set1[KEY_POINTER] = PS2KeyShifted[SCAN_CODE];
		        else if(PS2_SHIFT == FALSE && PS2_SPL_KEY == FALSE)
		           str_set1[KEY_POINTER] = PS2KeyUnshifted[SCAN_CODE]; 
				if(!LCD_PAGE_FLAG )
				{
					if(str_set1[KEY_POINTER] == '\b')
					{	
						str_set1[KEY_POINTER] = '\0';
						str_set1[--KEY_POINTER] = '\0';
						if(KEY_POINTER>0)
						--KEY_POINTER; 
						send_byte('\b');
						send_byte(' ');
						send_byte('\b');						
					}
					else
					send_byte(str_set1[KEY_POINTER]);
					if(str_set1[KEY_POINTER] == '\n')
					{
						send_byte('\r'); //sending a carriage return to the  kserial terminal
						str_set1[KEY_POINTER] = '\0';
						EXEC_COMMAND_FROM_LCD();
						KEY_POINTER = 0;
						str_clear(str_set1);				
					}
					else
					{
			           KEY_POINTER++;
			           if(KEY_POINTER >16)
			           {
						 temp = str_set1[--KEY_POINTER];
			            strcpy(str_set1,"                "); 
						str_set1[0]=temp;
						KEY_POINTER=1;
			           }
			           str_set1[16]='\0';
			           lcd_1(str_set1);	                   //Every Time a Key is Pressed the Lcd is erased and rewritten from the start 
					}
					 
			    }
				else
				lcd_page(str_set1[KEY_POINTER]);
			 } //key polling ends here
			if(RCIF)  //RS232 polling
			{	
				RECIEVED_BYTE=RCREG;
				CTIME_DISP_FLAG = 0;
				if(RECIEVED_BYTE!= 0x0A)
				{
					send_byte(RECIEVED_BYTE);
					if(rec_count<6)
					rec_string[rec_count++] =  lowtoup_case(RECIEVED_BYTE);
					else
					rec_string[rec_count++] = RECIEVED_BYTE;
					if(rec_count > 23)
					{
						rec_count =0;
						rec_string[0] = '\0';
					}
					if(RECIEVED_BYTE == '\r')
					{	
													
							send_byte('\n');
							if(rec_count > 23) //Enter key pressed is the 23rd count
							{
								send_string("Command or Argument to long");
								NEWLINE;
							}
							else
							{
								rec_string[--rec_count] = '\0';
								EXEC_COMMAND();
							}
							rec_string[0]='\0';
							rec_count = 0;
					}
				}
			} //serial polling ends here
			time_polling();      
 		} //while ends here

}
