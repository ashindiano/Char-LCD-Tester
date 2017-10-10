#define CLOCK   RB0 
#define DATAPIN RB1 
void InitKeyBoard(void); //function declaration
void decode(unsigned char sc);
void put_kbbuff(unsigned char c);
int getchar_kb(void);  
void print_hexbyte(unsigned char i); 
unsigned char bitcount;