
#include <Arduino.h>
#include "config.h"

#ifdef USE_BUZZER
  #include "md_buzzer.h"

  #ifdef USE_SONGTASK
    TaskHandle_t songTask;
  #endif

  #define PLAYER_IS_FREE false
  #define OCUPIED        true

  typedef struct
  {
    int8_t   note;     // NOTE_C .. NOTE_B
    int8_t   octa;     // oktave 0 .. 7
    uint64_t beat;     // MB1 = base
  } tone_t;

  const uint16_t len1    = 8;
  const tone_t   song1[] =
      { // Haenschen klein
        {NOTE_G ,0,MB4 },{NOTE_E ,0, MB4 },{NOTE_E,0,MB4 },{PAUSE,0, MB4 },
        {NOTE_F ,0,MB4 },{NOTE_D ,0, MB4 },{NOTE_D,0,MB4 },{PAUSE,0, MB4 }
      };
//        ,
//        {  n1C, M_T4},{  n1D, M_T4},{  n1E, M_T4},{  n1F, M_T4},
//        {  n1G, M_T4},{  n1G, M_T4},{  n1G, M_T4},{PAUSE, M_T4}
//      };

  int8_t nextSong = NN;    // command in
  bool   waitSong = true;  // semaphore out -> wait until finished

  // --- private prottypes
  #ifdef USE_SONGTASK
    void playSong(void * pvParameters);
  #endif
  // --- public implementation

  void initMusic()
  {
    ledcAttachPin(PIN_BUZZ, PWM_BUZZ);
    Serial.print(millis());
    Serial.println(" initMusic .. Song einlesen");

    #ifdef USE_SONGTASK
      xTaskCreatePinnedToCore(
                          playSong,   /* Task function. */
                          "Task1",     /* name of task. */
                          10000,       /* Stack size of task */
                          NULL,        /* parameter of the task */
                          4 | portPRIVILEGE_BIT,           /* priority of the task */
                          &songTask,      /* Task handle to keep track of created task */
                          1);          /* pin task to core 0 */
    #endif
    Serial.print(millis());
    Serial.println(" .. initMusic finished");
    usleep(500000);
  }

  bool setSong(int8_t song)
  {
        Serial.print(millis());
        Serial.print(" setSong "); Serial.print(song);
    // check semaphore
    if ((waitSong == PLAYER_IS_FREE) || (nextSong == NN))
    {
      nextSong = song;
            Serial.println("ok");
      return MDOK;
    }
    else
    {
            Serial.println(" ERR");
      return MDERR;
    }
  }

  // --- private ------------------------------
  #ifdef USE_SONGTASK
    void playSong(void * pvParameters)
  #else
    void playSong()
  #endif
  {
    song_t* psong;
    tone_t* pnote;

        Serial.print(millis());
        Serial.println(" playSong .. ");
    #ifdef USE_SONGTASK
      // endless loop
      while (true)
    #endif
    {
      // Ckeck, if song is to play
      if (nextSong != NN)
      {
        waitSong = true;
        nextSong = NN;

                Serial.print(millis());
                Serial.print(" psong = "); Serial.println((int) psong);
                Serial.print(" .. nextSong = "); Serial.println(nextSong);
        psong  = &(songs[nextSong]);
                Serial.print("pnote = "); Serial.println((int) psong->pton);
        pnote  = psong->pton;

                Serial.println("for ii ");
        for (uint16_t ii = 0; ii < 8/*psong->len*/; ii++)
        {
          if (pnote->note == PAUSE)
          {
                Serial.print(millis());
                Serial.print(" ->PAUSE "); Serial.println(ii);
            ledcWriteTone(PWM_BUZZ, 0.0);
          }
          else
          {
                Serial.print(millis());
                Serial.print(" ->NOTE "); Serial.println(ii);
            ledcWriteNote(PWM_BUZZ, (note_t) pnote->note, pnote->octa);
          }

          usleep(pnote->beat >> 1);      // duration tone

                Serial.print(millis());
                Serial.print(" ->END "); Serial.println(ii);
          ledcWriteTone(PWM_BUZZ, 0.0);  // switch off

          usleep(pnote->beat >> 1);      // duration off
        }
        waitSong = OCUPIED;
      }
      sleep(1);
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