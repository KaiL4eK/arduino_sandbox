#include "Servo.h"
#include "Arduino.h"

Servo servo;
#define SERVO_PIN  9
#define SERVO_POWER_PIN 8

#define OPENING_TIME    500
#define SERVO_TIME_DELAY 100
int servo_opened_angle = 165;
int servo_closed_angle = servo_opened_angle - 45;

void servo_init ( void )
{
    pinMode( SERVO_POWER_PIN, OUTPUT );
    servo.attach( SERVO_PIN );
    Serial.println( "Servo initialized" );
}

void servo_turn_on ( void )
{
    digitalWrite( SERVO_POWER_PIN, LOW );
}

void servo_turn_off ( void )
{
    digitalWrite( SERVO_POWER_PIN, HIGH );
}

void servo_fast_close ( void )
{
    servo.write( servo_closed_angle );
    delay( 50 );
    servo_turn_on();
    delay( OPENING_TIME );
    servo_turn_off();  
}

void servo_fast_open ( void )
{
    servo.write( servo_opened_angle );
    delay( 50 );
    servo_turn_on();
    delay( OPENING_TIME );
    servo_turn_off();  
}

void servo_close ( void )
{
    for ( int i = servo_opened_angle; i >= servo_closed_angle; i-- )
    {
        servo.write( i );
        servo_turn_on();
        delay( SERVO_TIME_DELAY ); 
    }
    servo_turn_off();  
}

void servo_open ( void )
{
    for ( int i = servo_closed_angle; i <= servo_opened_angle; i++ )
    {
        servo.write( i );
        servo_turn_on();
        delay( SERVO_TIME_DELAY ); 
    }
    servo_turn_off();  
}