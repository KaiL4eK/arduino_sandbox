void setup ( void )
{
	Serial1.begin( 2400 );
	Serial.begin( 115200 );
}

void loop ( void )
{
	bool end = false;
	while ( Serial1.available() ) {
		Serial.print( Serial1.read() );
		Serial.print( " " );
		end = true;
	}

	if ( end ) {
		Serial.println( " " );
	}


	delay( 100 );
}
