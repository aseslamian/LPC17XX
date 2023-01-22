// Write by DMF313.IR
#ifndef LiquidCrystal_h
#define LiquidCrystal_h


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00



typedef unsigned char uint8;



void init1(uint8 rs, uint8 rw,	uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7);
void init2(uint8 rs, 						uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7);
void init3(uint8 rs, uint8 rw, 	uint8 enable, 																				uint8 d4, uint8 d5, uint8 d6, uint8 d7);
void init4(uint8 rs,						uint8 enable, 																				uint8 d4, uint8 d5, uint8 d6, uint8 d7);

void initialization(uint8 fourbitmode, uint8 rs, uint8 rw, uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7);

void begin(uint8 cols, uint8 rows, uint8 charsize);

void clear(void);
void home(void);

void noDisplay(void);
void display(void);
void noBlink(void);
void blink(void);
void noCursor(void);
void cursor(void);
void scrollDisplayLeft(void);
void scrollDisplayRight(void);
void leftToRight(void);
void rightToLeft(void);
void autoscroll(void);
void noAutoscroll(void);

void setRowOffsets(int row1, int row2, int row3, int row4);
void createChar(uint8, char[]);
void setCursor(uint8, uint8);

void write(char);
void print(char *data);
void printNumber(int data, int base);

void command(uint8);
void send(uint8, uint8);
void write4bits(uint8);
void write8bits(uint8);
void pulseEnable(void);


#endif
