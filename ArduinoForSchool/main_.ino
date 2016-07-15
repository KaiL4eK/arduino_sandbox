int lightPin = 13;
int battery0Pin = A7;

int batCap0 = 0;

char buffer[255],
	 fbuf0[15];
void setup ( void )
{
	pinMode( lightPin, OUTPUT );
	Serial.begin( 9600 );
}

void loop ( void )
{
	digitalWrite( lightPin, HIGH );
	delay( 500 );
	digitalWrite( lightPin, LOW );
	delay( 500 );

	batCap0 = analogRead(battery0Pin);

	dtostrf( batCap0*10.0/1023, 4, 2, fbuf0 );
	sprintf( buffer, "Battery: %sV\n", fbuf0 );

	Serial.print( buffer );
}
