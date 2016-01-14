#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>

#define ERR_LIGHT   13

#define error() { pinMode( ERR_LIGHT, OUTPUT ); digitalWrite( ERR_LIGHT, HIGH ); }

// DS1302:  CE pin    -> Arduino Digital A0
//          I/O pin   -> Arduino Digital A1
//          SCLK pin  -> Arduino Digital A2
// Set pins:  CE, IO,CLK
DS1302RTC RTC(A0, A1, A2);
void print2digits(int number);

void servo_close ( void );
void servo_open ( void );
void servo_turn_on ( void );
void servo_turn_off ( void );
void servo_fast_close ( void );
void servo_fast_open ( void );
void servo_init ( void );

void lcd_init ( void );
void lcd_show_next_letter ( void );

void play_next_note ( void );

tmElements_t    time_open = { 0, 0, 0, 0, 0, 0, 2016-1970 }, // Second, Minute, Hour, Day, Month, Year
                currentTime;

bool opened_flag = false;

bool is_time_to_open_box ( tmElements_t *curr_time )
{
    if ( curr_time->Year >= time_open.Year &&
         curr_time->Minute >= time_open.Minute )
    {
        return( true );       
    }
    return( false );
}

void output_current_date ( tmElements_t *tm )
{
    Serial.print("Time = ");
    Serial.print(tm->Hour);
    Serial.write(':');
    Serial.print(tm->Minute);
    Serial.write(':');
    Serial.print(tm->Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm->Day);
    Serial.write('/');
    Serial.print(tm->Month);
    Serial.write('/');
    Serial.println(tmYearToCalendar(tm->Year));
}

void read_RTC ( void )
{
    if ( !RTC.read( currentTime ) )
    {
        output_current_date( &currentTime );
    }
    else
    {
        error();
        read_RTC();
    }
}

void setup ( void )
{
    delay( 3000 );
    Serial.begin(115200);     
    servo_init();
    lcd_init();

    read_RTC();
    if ( !is_time_to_open_box( &currentTime ) )
    {
        Serial.println("No time yet!");
        servo_fast_close();
    }
    else
    {
        Serial.println("Already time!");
        servo_fast_open(); 
        opened_flag = true;
    }
}

#define LCD_OUTPUT_DELAY    700

void celebration_loop ( void )
{
    unsigned long delayLCDCounter = 0;
    while ( 1 )
    {
        if ( millis() - delayLCDCounter > LCD_OUTPUT_DELAY )
        {
            lcd_show_next_letter();
            delayLCDCounter = millis();
        }
        play_next_note();
    }
}

void loop ( void )
{
    if ( !opened_flag )
    {
        read_RTC();
        delay( 1000 );
        if ( is_time_to_open_box( &currentTime ) )
        {
            // Serial.println( "Time to open box!" );
            servo_open();
            celebration_loop();
        }
    }
    else
    {
        celebration_loop();
    }
}
