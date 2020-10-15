
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

  #if (ANZ_SONGS > 0)
    const uint16_t len1    = 62;
    const tone_t   song1[] =
        { // Haenschen klein
          {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
          {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_C ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },
          {NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
          {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
          {NOTE_C ,OP0,MB2},                     { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },
          {NOTE_D ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_F ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },
          {NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
          {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

          {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
          {NOTE_C ,OP0,MB2},                     { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 }
        };
  #endif
  #if (ANZ_SONGS > 1)
    const uint16_t len2    = 8;
    const tone_t   song2[] =
        { // Haenschen klein
          {NOTE_G ,0,MB4 },{NOTE_E ,0, MB4 },{NOTE_E,0,MB4 },{PAUSE,0, MB4 },
          {NOTE_F ,0,MB4 },{NOTE_D ,0, MB4 },{NOTE_D,0,MB4 },{PAUSE,0, MB4 }
        };
  #endif
  #if (ANZ_SONGS > 2)
    const uint16_t len3    = 8;
    const tone_t   song3[] =
        { // Haenschen klein
          {NOTE_G ,0,MB4 },{NOTE_E ,0, MB4 },{NOTE_E,0,MB4 },{PAUSE,0, MB4 },
          {NOTE_F ,0,MB4 },{NOTE_D ,0, MB4 },{NOTE_D,0,MB4 },{PAUSE,0, MB4 }
        };
  #endif

  int8_t nextSong = NN;    // command in
  bool   waitSong = true;  // semaphore out -> wait until finished

  // --- private prottypes
  #ifdef USE_SONGTASK
    void playSong(void * pvParameters);
  #endif
  // --- public implementation

  void md_initMusic()
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

  bool md_setSong(int8_t songIdx)
  {
        Serial.print(millis());
        Serial.print(" setSong "); Serial.print(songIdx);
    // check semaphore
    if ((waitSong == PLAYER_IS_FREE) || (nextSong == NN))
    {
      if (songIdx < ANZ_SONGS)
      {
        nextSong = songIdx;
              Serial.println("ok");
        return MDOK;
      }
      else
      {
            Serial.println(" ERR idx too high");
      }

    }
    else
    {
            Serial.println(" ERR");
    }
    return MDERR;
  }

  // --- private ------------------------------
  void md_playSong()
  {
    {
            Serial.print(millis());
            Serial.println(" playSong .. ");

      // Ckeck, if song is to play
      if (nextSong != NN)
      {
        int8_t   _song = nextSong;
        note_t   _note = (note_t) PAUSE;     // NOTE_C .. NOTE_B
        int8_t   _octa = 0;     // oktave 0 .. 7
        uint64_t _beat = 0;     // MB1 = base
        uint16_t _len  = 0;

        waitSong = OCUPIED;
        nextSong = NN;

                Serial.print(millis());
                Serial.print(" nextSong = "); Serial.print(nextSong);
                Serial.print(" _song = "); Serial.println(_song);

                Serial.println("for ii ");

        switch (_song)
        {
          case 0:
            _len = len1;
            break;
            #if (ANZ_SONGS > 1)
              case 1:
                _len = len2;
                break;
            #endif
            #if (ANZ_SONGS > 2)
              case 2:
                _len = len3;
                break;
            #endif
          default:
            break;
        }

        for (uint16_t ii = 0; ii < _len; ii++)
        {
          switch (_song)
          {
            case 0:
              _note = (note_t) song1[ii].note;
              _beat = song1[ii].beat;
              _octa = song1[ii].octa;
              break;
              #if (ANZ_SONGS > 1)
                case 1:
                  _note = (note_t) song2[ii].note;
                  _beat = song2[ii].beat;
                  _octa = song2[ii].octa;
                  break;
              #endif
              #if (ANZ_SONGS > 2)
                case 2:
                  _note = (note_t) song3[ii].note;
                  _beat = song3[ii].beat;
                  _octa = song3[ii].octa;
                  break;
              #endif
            default:
              break;
          }

          if (_note == PAUSE)
          {
              #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
                Serial.print(millis());
                Serial.print(" ->PAUSE "); Serial.println(ii);
              #endif
            ledcWriteTone(PWM_BUZZ, 0.0);
          }
          else
          {
              #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
                Serial.print(millis());
                Serial.print(" ->NOTE "); Serial.print(_note);
                Serial.print(" ->OCTA "); Serial.println(_octa);
              #endif
            ledcWriteNote(PWM_BUZZ, _note, _octa);
          }

          usleep(_beat);      // duration tone = beat/2

              #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
                Serial.print(millis());
                Serial.print(" ->END "); Serial.println(ii);
              #endif
          ledcWriteTone(PWM_BUZZ, 0.0);  // switch off

          usleep(_beat);      // pause
        }
        waitSong = PLAYER_IS_FREE;
      }
      sleep(1);
    }
  }

#endif // USE_BUZZER