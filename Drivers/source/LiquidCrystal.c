#include "LiquidCrystal.h"
#include "gpio.h"
#include "delay.h"


////////////////////////////////////////////////////////////////////Variable
uint8 _rs_pin; // LOW: command.  HIGH: character.
uint8 _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
uint8 _enable_pin; // activated by a HIGH pulse.
uint8 _data_pins[8];

uint8 _displayfunction;
uint8 _displaycontrol;
uint8 _displaymode;

uint8 _initialized;

uint8 _numlines;
uint8 _row_offsets[4];
////////////////////////////////////////////////////////////////////Variable


void init1(uint8 rs, uint8 rw,	uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7) {
  initialization(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}
void init2(uint8 rs, 						uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7) {
  initialization(0, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}
void init3(uint8 rs, uint8 rw, 	uint8 enable, 																				uint8 d4, uint8 d5, uint8 d6, uint8 d7) {
  initialization(1, rs, rw, enable, 0, 0, 0, 0, d4, d5, d6, d7);
}
void init4(uint8 rs,						uint8 enable, 																				uint8 d4, uint8 d5, uint8 d6, uint8 d7) {
  initialization(1, rs, 255, enable, 0, 0, 0, 0, d4, d5, d6, d7);
}

void initialization(uint8 fourbitmode, uint8 rs, uint8 rw, uint8 enable, uint8 d0, uint8 d1, uint8 d2, uint8 d3, uint8 d4, uint8 d5, uint8 d6, uint8 d7) {
  
	int i;
	
	_rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 

  if (fourbitmode) {
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

		for ( i=0; i<8; i++ ) {
			pinMode(_data_pins[i], Neither, OUTPUT);
		}
	}
  else {
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
		
		for ( i=4; i<8; i++ ) {
			pinMode(_data_pins[i], Neither, OUTPUT);
		}
	}
  
  begin(16, 1, LCD_5x8DOTS);
}

void begin(uint8 cols, uint8 lines, uint8 dotsize) {
  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);  

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  pinMode(_rs_pin, Neither, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (_rw_pin != 255) { 
    pinMode(_rw_pin, Neither, OUTPUT);
  }
  pinMode(_enable_pin, Neither, OUTPUT);

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  delayUs(50000); 
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  if (_rw_pin != 255) { 
    digitalWrite(_rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (_displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    delayUs(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delayUs(4500); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    delayUs(150);

    // finally, set to 4-bit interface
    write4bits(0x02); 
  } 
	else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(LCD_FUNCTIONSET | _displayfunction);
    delayUs(4500);  // wait more than 4.1ms

    // second try
    command(LCD_FUNCTIONSET | _displayfunction);
    delayUs(150);

    // third go
    command(LCD_FUNCTIONSET | _displayfunction);
  }

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);
}


void setRowOffsets(int row0, int row1, int row2, int row3) {
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

//********* high level commands, for the user!
void clear(void) {
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayUs(2000);  // this command takes a long time!
}

void home(void) {
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayUs(2000);  // this command takes a long time!
}

void setCursor(uint8 col, uint8 row) {
  const char max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
void noDisplay(void) {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void display(void) {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void noCursor(void) {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor(void) {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void noBlink(void) {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink(void) {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(uint8 location, char charmap[]) {
  int i;
	location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for ( i=0; i<8; i++ ) {
    write(charmap[i]);
  }
}

// Show Data
void write(char value) {
  send(value, HIGH);
}
void print(char *data) {
	unsigned char i;
	
	for(i=0; data[i]!='\0'; i++)
		write( data[i] );
}
void printNumber(int data, int base) {
  char buf[8 * sizeof(long) + 1];
  char *str = &buf[sizeof(buf) - 1];
	char c;
	unsigned long m;
  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    m = data;
    data /= base;
    c = m - base * data;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(data);

  print( str );
}

//*********** low level data pushing commands **********
// write either command or data, with automatic 4/8-bit selection
void send(uint8 value, uint8 mode) {
  digitalWrite(_rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    digitalWrite(_rw_pin, LOW);
  }
  
  if (_displayfunction & LCD_8BITMODE) {
    write8bits(value); 
  } else {
    write4bits(value>>4);
    write4bits(value);
  }
}

void pulseEnable(void) {
  digitalWrite(_enable_pin, LOW);
  delayUs(1);    
  digitalWrite(_enable_pin, HIGH);
  delayUs(1);    // enable pulse must be >450ns
  digitalWrite(_enable_pin, LOW);
  delayUs(100);   // commands need > 37us to settle
}

void write4bits(uint8 value) {
  int i;
	for ( i = 0; i < 4; i++ ) {
    digitalWrite(_data_pins[i+4], (value >> i) & 0x01);
  }

  pulseEnable();
}

void write8bits(uint8 value) {
  
	int i;
	for ( i = 0; i < 8; i++ ) {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }
  
  pulseEnable();
}

void command(uint8 value) {
  send(value, LOW);
}
