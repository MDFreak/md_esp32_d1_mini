#ifndef _MD_BUZZER_H_
  #define _MD_BUZZER_H_

  #include <Arduino.h>
  #include "config.h"

  #ifdef USE_BUZZER
    #define BEAT_UNITS
    #ifdef BEAT_UNITS
      #define MB1   MUSIC_BEAT_UNIT    // ganze Note = Grundtakt
      #define MB2   MB1  / 2
      #define MB4   MB1  / 4
      #define MB8   MB1  / 8
      #define MB16  MB1  / 16
    #endif

    #define PAUSE   -1

    // initializing variables for playing melody
    #define SONG_HAENSCHEN_KLEIN  0
    //#define SONG_ALLE_VOEGLEIN    1
    //#define SONG_ALLE_ENTCHEN     2
    #define ANZ_SONGS        1

    void initMusic();
    bool setSong(int8_t song);
    void playSong();

  #endif
#endif // _MD_BUZZER_H_