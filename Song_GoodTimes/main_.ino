
/**
* Arduino playing 'Good Times' Bassline by Chic
* Some code used and repurposed from:
* http://rob.gubler.net/devel/ArduinoJingleBells/jinglebells.pde
* 
* Hook up a Piezo Buzzer or small speaker's ground (-) to pin 13, and (+) to 5v
*
* Note frequencies courtesy of:
* http://www.phy.mtu.edu/~suits/notefreqs.html
*
*/

#define FREQ_C2 65.41
#define FREQ_CS2 69.30 
#define FREQ_D2 73.42
#define FREQ_DS2 77.78
#define FREQ_E2 82.41
#define FREQ_F2 87.31
#define FREQ_FS2 92.5
#define FREQ_G2 98
#define FREQ_GS2 103.83
#define FREQ_A2 110.00
#define FREQ_B2 123.47

#define FREQ_C3 130.81 
#define FREQ_CS3 138.59 
#define FREQ_D3 146.83
#define FREQ_DS3 155.56
#define FREQ_E3 164.81
#define FREQ_F3 174.61
#define FREQ_FS3 185
#define FREQ_G3 196
#define FREQ_GS3 207.65
#define FREQ_A3 220.00
#define FREQ_AS3 233.08
#define FREQ_B3 246.94

#define FREQ_C4 261.63 //Middle C
#define FREQ_CS4 277.18
#define FREQ_DF4 277.18
#define FREQ_D4 293.66
#define FREQ_DS4 311.13
#define FREQ_E4 329.63
#define FREQ_F4 349.23
#define FREQ_FS4 369.99
#define FREQ_G4 392.00
#define FREQ_GS4 415.30
#define FREQ_A4 440.00
#define FREQ_B4 493.88

#define FREQ_C5 523.25
#define FREQ_D5 587.33

#define WHOLE_NOTE_TIME 2000


#define OUTPIN 13
void PlayMusicString(char* music, int outputPin);
void Sound(float freq, int durationMS, int outputPin);

void setup() {
}
void loop() {
 char music[] =
   "ee eee eee q seeesfegeaebecedeEeae eae eae q saeasFsasGsasFeaeasbsesge e";
 PlayMusicString(music,OUTPIN);
}

void PlayMusicString(char* music, int outputPin){
 int noteCount=strlen(music);
 float freq;
 int duration;
 for (int i=0; i < noteCount; i += 2) {
   switch(music[i]){
     case ' ' :
       freq=0;
       break;
     case 'D' :
       freq=FREQ_D2;
       break;
     case 'e' :
       freq=FREQ_E2;
       break;
     case 'f' :
       freq=FREQ_FS2;
       break;
     case 'g' :
       freq=FREQ_G2;
       break;
     case 'a' :
       freq=FREQ_A2;
       break;
     case 'b' :
       freq=FREQ_B2;
       break;
     case 'c' :
       freq=FREQ_CS3;
       break;
     case 'd' :
       freq=FREQ_D3;
       break;
     case 'E' :
       freq=FREQ_E3;
       break;
     case 'F' :
       freq=FREQ_FS3;
       break;
     case 'G' :
       freq=FREQ_G3;
       break;
       
   }
   //Note Timing
   switch(music[i+1]){
     case 'w' :
       duration=WHOLE_NOTE_TIME;
       break;
     case 'h' :
       duration=WHOLE_NOTE_TIME/2;
       break;
     case 'q' :
       duration=WHOLE_NOTE_TIME/4;
       break;
     case 'e' :
       duration=WHOLE_NOTE_TIME/8;
       break;
     case 's' :
       duration=WHOLE_NOTE_TIME/16;
       break;  
   }
   Sound(freq,duration,outputPin);
   delay(WHOLE_NOTE_TIME/64);
 }
}

void Sound(float freq, int durationMS, int outputPin) {
 int halfPeriod;
 float period;
 int durationCycles;
 //Check for rest, 0 frequency is a rest for durationMS.
 if(freq==0.0) {
   //0 frequency so we stay quiet for duration
   delay (durationMS);
 }
 else { //Frequency is not zero so we have work to do
   // turn on output pin
   pinMode(outputPin, OUTPUT);
   //calculate the period or cycle time for the given frequency
   period=1/freq; //Take the reciprocal to get time in seconds
   period=period*1.0E6; //to covert seconds to uS.
   //divide that by 2 to get the 1/2 cycle time. convert to int at the same time
   halfPeriod = (int)(period/2.0) - 7; // subtract 7 us to make up for digitalWrite overhead

   // calculate cycles for duration.
   durationCycles = (int)(((float)durationMS*1000.0)/period); // play note for duration ms
   for (int i=0; i<durationCycles; i++){
     digitalWrite(outputPin, HIGH);
     delayMicroseconds(halfPeriod);
     digitalWrite(outputPin, LOW);
     delayMicroseconds(halfPeriod - 1); // - 1 to make up for fractional microsecond                                              in digitaWrite overhead
   }
   // shut off pin to avoid noise from other operations
   pinMode(outputPin, INPUT);
 }
}