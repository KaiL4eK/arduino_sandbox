/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  http://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

#define MIN_STEP 0
#define MAX_STEP 3


int step = 0;
void makeStep ( int xw );
void turnRightFive ( void );
void turnLeftFive ( void );

void setup()
{
    Serial.begin(115200);
    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 
    pinMode(IN3, OUTPUT); 
    pinMode(IN4, OUTPUT); 
}

void loop()
{

    for ( int i = 0; i < 16; i++ )
    {
        turnRightFive();
    }
    makeStep( -1 );
    delay( 1000 );

    for ( int i = 0; i < 20; i++ )
    {
        Serial.println( analogRead(1) );
        delay(100);
    }

    for ( int i = 0; i < 16; i++ )
    {
        turnLeftFive();
    }
    makeStep( -1 );
    delay( 1000 );

    for ( int i = 0; i < 20; i++ )
    {
        Serial.println( analogRead(1) );
        delay(100);
    }

    for ( int i = 0; i < 16; i++ )
    {
        turnLeftFive();
    }
    makeStep( -1 );
    delay( 1000 );

    for ( int i = 0; i < 20; i++ )
    {
        Serial.println( analogRead(1) );
        delay(100);
    }

    for ( int i = 0; i < 16; i++ )
    {
        turnRightFive();
    }
    makeStep( -1 );
    delay( 1000 );

    for ( int i = 0; i < 20; i++ )
    {
        Serial.println( analogRead(1) );
        delay(100);
    }
}

void turnRightFive ( void ) // 5.625 angle
{
    for ( int i = 0; i < 32; i++ )
    {
        if ( ++step > MAX_STEP )
        {
            step = MIN_STEP;
        }
        makeStep( step );
        delay( 3 );
    }
}

void turnLeftFive ( void )
{
    for ( int i = 0; i < 32; i++ )
    {
        if ( --step < MIN_STEP )
        {
            step = MAX_STEP;
        }
        makeStep( step );
        delay( 3 );
    }
}

void makeStep ( int step )
{
    switch( step ){
        case 0:
            digitalWrite(IN1, LOW); 
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, HIGH);
        break;  
        case 1:
            digitalWrite(IN1, LOW); 
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
        break; 
        case 2:
            digitalWrite(IN1, HIGH); 
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        break; 
        case 3:
            digitalWrite(IN1, HIGH); 
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
        break; 
        default:
            digitalWrite(IN1, LOW); 
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, LOW);
        break; 
    }
} 
