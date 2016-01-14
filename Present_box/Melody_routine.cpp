#include "Arduino.h"
#include "notes.h"

#define BUZZER_PIN	11
#define MELODY_LENGHT	49

int jingleBells[] = { NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_G6, 
                    NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_F6, NOTE_F6, NOTE_F6, NOTE_F6, 
                    NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_D6, NOTE_D6, NOTE_E6, NOTE_D6, 
                    NOTE_G6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_E6, 
                    NOTE_G6, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_F6, NOTE_F6, NOTE_F6, 
                    NOTE_F6, NOTE_E6, NOTE_E6, NOTE_E6, NOTE_G6, NOTE_G6, NOTE_E6, NOTE_D6, NOTE_C6};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4, 4, 2, 4, 4, 2, 4, 4, 
                        4, 4, 1, 4, 4, 4, 4, 4, 
                        4, 4, 4, 4, 4, 4, 4, 2, 
                        2, 4, 4, 2, 4, 4, 2, 4, 
                        4, 4, 4, 1, 4, 4, 4, 4, 
                        4, 4, 4, 4, 4, 4, 4, 4, 1};

int 			currentNote = 0, 
				pauseBetweenNotes = 0;
unsigned long 	lastWritedMillis = 0;

void play_next_note ( void ) 
{
	if ( millis() - lastWritedMillis < pauseBetweenNotes )
		return;
	
	noTone( BUZZER_PIN );
    int noteDuration = 1000/noteDurations[currentNote];
    tone( BUZZER_PIN, jingleBells[currentNote],noteDuration );
    pauseBetweenNotes = noteDuration * 1.30;
    lastWritedMillis = millis();
    if ( ++currentNote == MELODY_LENGHT )
    	currentNote = 0;
}
