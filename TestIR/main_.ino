void setup ( void )
{
	Serial3.begin( 2400 );
	Serial.begin( 115200 );
}

void loop ( void )
{
	bool end = false;
	while ( Serial3.available() ) {
		Serial.print( Serial3.read() );
		Serial.print( " " );
		end = true;
	}

	if ( end ) {
		Serial.println( " " );
	}


	delay( 100 );
}
