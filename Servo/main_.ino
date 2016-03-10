#include <Servo.h> 

Servo myservo;

void setup ( void )
{
	myservo.attach( 6 );
}

void loop ( void )
{
	int pos = 0;
	for ( pos = 0; pos < 90; pos += 5 )  // от 0 до 180 градусов
	{                                  // с шагом в 1 градус 
		myservo.write(pos);              // 
		delay(150);                       // ждём 15ms пока серва займёт новое положение
	} 
	for( pos = 90; pos >= 0; pos -= 5 )     // от 180 до 0 градусов
	{                                
		myservo.write(pos);               
		delay(150);                       
	} 
	delay( 1000 );
}
