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

#define TRIG_PIN 7
#define ECHO_PIN 6

#define IR_INPUT_80  A5
#define IR_INPUT_500 A4

#define QRD_INPUT 5

#define MS_TO_CM(x) (x/58L)

int step = 0;
void makeStep ( int xw );
void turnRightFive ( void );
void turnLeftFive ( void );
void makeStepRight ( void );
void makeStepLeft ( void );
int stepperMakeCalibration ( void );

void setup()
{
    Serial.begin(115200);
    pinMode(IN1, OUTPUT); 
    pinMode(IN2, OUTPUT); 
    pinMode(IN3, OUTPUT); 
    pinMode(IN4, OUTPUT); 

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(QRD_INPUT, INPUT);

    digitalWrite(TRIG_PIN, LOW);
}

int UZ_offset = 4; // 4 cm error
int stepDelay = 5;

void loop()
{
/*    digitalWrite( TRIG_PIN, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( TRIG_PIN, LOW );

    long pulseWidth = pulseIn( ECHO_PIN, HIGH ),
         dist_UZ_cm = -1;
    if ( pulseWidth < 26000 )
    {
        dist_UZ_cm = MS_TO_CM( pulseWidth ) - UZ_offset;
    }

    // float dist_IR_500_cm = 1000000.0/map( analogRead( IR_INPUT_500 ), 287, 512, 2000L, 10000L );
    // float dist_IR_80_cm = ( 6762/(analogRead( IR_INPUT_80 ) - 9) ) - 4;
    
    int IR_80_ADC_input = analogRead( IR_INPUT_80 ),
        dist_IR_80_cm = -1;

    if ( IR_80_ADC_input > 41 ) // 41 from ADC = 0.2 V
    {
        dist_IR_80_cm = ( 7802.0/((float)IR_80_ADC_input + 6.175) ) - 7.182;
    }

    // Serial.print(dist_IR_500_cm);
    // Serial.print(", ");
    Serial.print(digitalRead(QRD_INPUT));
    Serial.print(", ");
    Serial.print(dist_IR_80_cm);
    Serial.print(", ");
    Serial.println(dist_UZ_cm);

    delay(100);*/

    int res = stepperMakeCalibration(); // -1 - error; 0 - found from left, 1 - found from right
    if ( res < 0 )
    {
        Serial.println( "Calibration failed" );
    } 
    
    int count = 0;

    while ( digitalRead( QRD_INPUT ) )
    {
        count++;
        if ( res )
        {
            makeStepRight();
        }
        else
        {
            makeStepLeft();
        }
        delay( stepDelay );
    }

    Serial.println( count );

    count /= 2;

    for ( int i = 0; i < count; i++ )
    {
        if ( res )
        {
            makeStepLeft();
        }
        else
        {
            makeStepRight();
        }
        delay( stepDelay );
    }

    Serial.println( count );
    makeStep( -1 );

    while ( 1 );
}

// 5 means 5.625
int stepsFor90by5 = 90.0/5.625;

// Just for sure that we are no on the border
int additionSteps = 0;

int stepperMakeCalibration ( void )
{
    int calibrationDelay = 100;
    if ( digitalRead( QRD_INPUT ) )
    {
        turnLeftFive();
        turnLeftFive();
    }

    for ( int i = 0; i < stepsFor90by5*32; i++ )
    {
        makeStepRight();
        delay( stepDelay );
        if ( digitalRead( QRD_INPUT ) )
        {
            makeStep( -1 );
            return( 1 );
        }
    }

    makeStep( -1 );
    delay( calibrationDelay );
    
    for ( int i = 0; i < stepsFor90by5*2*32; i++ )
    {
        makeStepLeft();
        delay( stepDelay );
        if ( digitalRead( QRD_INPUT ) )
        {
            makeStep( -1 );
            return( 0 );
        }
    }

    makeStep( -1 );
    delay( calibrationDelay );

    for ( int i = 0; i < stepsFor90by5*32; i++ )
    {
        makeStepRight();
        delay( stepDelay );
        if ( digitalRead( QRD_INPUT ) )
        {
            makeStep( -1 );
            return( 1 );
        }
    }

    makeStep( -1 );
    delay( calibrationDelay );

    return( -1 );
}

void turnRightFive ( void ) // 5.625 angle
{
    for ( int i = 0; i < 32; i++ )
    {
        makeStepRight();
    }
}

void turnLeftFive ( void )
{
    for ( int i = 0; i < 32; i++ )
    {
        makeStepLeft();
    }
}

void makeStepRight ( void )
{
    if ( ++step > MAX_STEP )
    {
        step = MIN_STEP;
    }
    makeStep( step );
    delay( 3 );
}

void makeStepLeft ( void )
{
    if ( --step < MIN_STEP )
    {
        step = MAX_STEP;
    }
    makeStep( step );
    delay( 3 );
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
