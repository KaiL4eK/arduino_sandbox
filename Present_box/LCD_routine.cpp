#include "Arduino.h"
#include <LiquidCrystal.h>

/* 
 * The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 7
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 5
 * LCD D7 pin to digital pin 4
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
LiquidCrystal lcd( 2, 3, 7, 6, 5, 4 );

byte smiley[8] = {
	B00000,
	B10001,
	B00000,
	B00000,
	B10001,
	B01110,
	B00000,
};

byte snowflake[8] = {
	B00100,
	B10101,
	B01110,
	B11111,
	B01110,
	B10101,
	B00100,
};

byte heart[8] = {
	B00000,
	B01010,
	B11111,
	B11111,
	B01110,
	B00100,
	B00000,
};

void lcd_long_output ( const char *string )
{
	while ( *string != 0 )
	{
		lcd.write( *string++ );
		delay( 500 );
	}  
}

int currentLCDString = 0,
	currentLetter = 0,
	currentCelebrity = 0;

#define AMOUNT_OF_CELEBRITIES 8

char *celebrations[] = { "Happy New Year!)", 
						 "I love you 222  ", 
						 "Don`t forget:",
						 "You`re my happy!  ",
						 "Family 000", 
						 "Snow 111  ", 
						 "You are cool!=)",
						 "My best of best!)  "
						};
						
char *currentCelebration = celebrations[currentCelebrity];

void lcd_show_next_letter ( void )
{
	switch ( *currentCelebration )
	{
		case '\0':
			currentLetter = 0;
			if ( ++currentLCDString == 2 )
			{
				currentLCDString = 0;
				lcd.clear();
			}
			lcd.setCursor( 0, currentLCDString );
			if ( ++currentCelebrity == AMOUNT_OF_CELEBRITIES )
			{
				currentCelebrity = 0;
			}
			currentCelebration = celebrations[currentCelebrity];
			break;
		case '0':
			lcd.write( byte(0) );
			currentCelebration++;
			return;
		case '1':
			lcd.write( byte(1) );
			currentCelebration++;
			return;
		case '2':
			lcd.write( byte(2) );
			currentCelebration++;
			return;
	}
	lcd.print( *currentCelebration++ );
}

void lcd_init ( void )
{
	lcd.createChar( 0, smiley );
	lcd.createChar( 1, snowflake );
	lcd.createChar( 2, heart );
	lcd.begin( 16, 2 );
	lcd.clear();
}
