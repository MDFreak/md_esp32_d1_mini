#include "md_buzzer.h"

#ifdef USE_BUZZER

  // initializing variables for playing melody
  #define HAENSCHEN_KLEIN  1
  //#define ALLE_VOEGLEIN    2
  //#define ALLE_ENTCHEN     3
  #define ANZ_SONGS        1

  //uint16_t lenSongs[ANZ_SONGS] = {sizeof(song1)};
  //tone_t *psongs[ANZ_SONGS   ] = {       song1 }; // , song2, song3};

  // MUSIK_ANZ_LIEDER

  // ---- Lieder --------------------------
  // ---- Haenschen klein

  // ---- Alle Voeglein sind schon da

  void md_buzzer::playSong(uint8_t idx)
  {
    for (int ii = 0; ii < lenSongs[idx]; ii++)
    {
      // pin8 output the voice, every scale is 0.5 sencond
      ledcWriteNote(IO_BUZZER, psongs[ii]->note, psongs[ii]->dauer); // melody[thisNote], duration);

      // Output the voice after several minutes
      delay(1000);
    }

  }

  /* Example
    // This code is for playing a melody

    int buzzerpin = 11;
     int DEBUG = 1;

     void setup() {
       pinMode(buzzerpin, OUTPUT);                                                                               // Setting pin 11 as output
       if (DEBUG) {
         Serial.begin(9600);                                                                                      // Setting baud rate at 9600
       }
     }


     int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };                         // initializing variables for playing melody
     int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };   // initializing the beat values
     int MAX_COUNT = sizeof(melody)


     long tempo = 10000;                                                                       // This will Set overall tempo

     int pause = 1000;                                                              // initializing the variable for pause between tones

     int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

     // Initialize core variables
     int tone_ = 0;
     int beat = 0;
     long duration  = 0;

     // PLAY TONE  ==============================================
     // Pulse the speaker to play a tone for a particular duration
     void playTone() {
       long elapsed_time = 0;
       if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
         //  played less long than 'duration', pulse speaker HIGH and LOW
         while (elapsed_time < duration) {

           digitalWrite(buzzerpin,HIGH);
           delayMicroseconds(tone_ / 2);

           // DOWN
           digitalWrite(buzzerpin, LOW);
           delayMicroseconds(tone_ / 2);

           // Keep track of how long we pulsed
           elapsed_time += (tone_);
         }
       }
       else { // Rest beat; loop times delay
         for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
           delayMicroseconds(duration);
         }
       }
     }

     // LET THE WILD RUMPUS BEGIN =============================
     void loop() {
       // Set up a counter to pull from melody[] and beats[]
       for (int i=0; i<MAX_COUNT; i++) {
         tone_ = melody[i];
         beat = beats[i];

         duration = beat * tempo; // Set up timing

         playTone();
         // A pause between notes...
         delayMicroseconds(pause);

         if (DEBUG) { // If debugging, report loop, tone, beat, and duration
           Serial.print(i);
           Serial.print(":");
           Serial.print(beat);
           Serial.print(" ");
           Serial.print(tone_);
           Serial.print(" ");
           Serial.println(duration);
         }
       }
     }

  Example */



#endif // USE_BUZZER