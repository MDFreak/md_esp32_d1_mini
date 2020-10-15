#ifndef _MD_BUZZER_H_
  #define _MD_BUZZER_H_

  #include <Arduino.h>
  #include "config.h"

  #ifdef USE_BUZZER
    #define BEAT_UNITS
    #ifdef BEAT_UNITS
      #define MBL4  MUSIC_BEAT_UNIT * 4
      #define MBL3  MUSIC_BEAT_UNIT * 3
      #define MBL2  MUSIC_BEAT_UNIT * 2
      #define MB1   MUSIC_BEAT_UNIT       // 4/4 note = basebeat
      #define MB2   MUSIC_BEAT_UNIT / 2
      #define MB4   MUSIC_BEAT_UNIT / 4
      #define MB8   MUSIC_BEAT_UNIT / 8
      #define MB16  MUSIC_BEAT_UNIT / 16
    #endif

    #ifdef MUSIC_BASE_OCTA
      #define ON3   MUSIC_BASE_OCTA + 3  // octave negative 1
      #define ON2   MUSIC_BASE_OCTA + 2  // octave negative 1
      #define ON1   MUSIC_BASE_OCTA + 1  // octave negative 1
      #define OP0   MUSIC_BASE_OCTA      // (base-) octave positiv 0
      #define OP1   MUSIC_BASE_OCTA - 1  // octave positiv 1
      #define OP2   MUSIC_BASE_OCTA - 2  // octave positiv 1
      #define OP3   MUSIC_BASE_OCTA - 3  // octave positiv 1
      #define OP4   MUSIC_BASE_OCTA - 4  // octave positiv 1
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