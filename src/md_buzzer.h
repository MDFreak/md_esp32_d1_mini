#ifndef _MD_BUZZER_H_
  #define _MD_BUZZER_H_

  #include <Arduino.h>
  #include "config.h"

  #ifdef USE_BUZZER
    /* --- Musik Noten
     * _Oktave_Note_
     * ------------------------------*/
    #define MUSIKNOTEN
      #ifdef MUSIKNOTEN
      #define PAUSE 0
      #define n0H   31

      #define n1C   33
      #define n1CIS 35
      #define n1D   37
      #define n1DIS 39
      #define n1E   41
      #define n1F   44
      #define n1FIS 46
      #define n1G   49
      #define n1GIS 52
      #define n1A   55
      #define n1AIS 58
      #define n1H   62

      #define n2C   65
      #define n2CIS 69
      #define n2D   73
      #define n2DIS 78
      #define n2E   82
      #define n2F   87
      #define n2FIS 93
      #define n2G   98
      #define n2GIS 104
      #define n2A   110
      #define n2AIS 117
      #define n2H   123

      #define n3C   131
      #define n3CIS 139
      #define n3D   147
      #define n3DIS 156
      #define n3E   165
      #define n3F   175
      #define n3FIS 185
      #define n3G   196
      #define n3GIS 208
      #define n3A   220
      #define n3AIS 233
      #define n3H   247

      #define n4C   262
      #define n4CIS 277
      #define n4D   294
      #define n4DIS 311
      #define n4E   330
      #define n4F   349
      #define n4FIS 370
      #define n4G   392
      #define n4GIS 415
      #define n4A   440
      #define n4AIS 466
      #define n4H   494

      #define n5C   523
      #define n5CIS 554
      #define n5D   587
      #define n5DIS 622
      #define n5E   659
      #define n5F   698
      #define n5FIS 740
      #define n5G   784
      #define n5GIS 831
      #define n5A   880
      #define n5AIS 932
      #define n5H   988

      #define n6C   1047
      #define n6CIS 1109
      #define n6D   1175
      #define n6DIS 1245
      #define n6E   1319
      #define n6F   1397
      #define n6FIS 1480
      #define n6G   1568
      #define n6GIS 1661
      #define n6A   1760
      #define n6AIS 1865
      #define n6H   1976

      #define n7C   2093
      #define n7CIS 2217
      #define n7D   2349
      #define n7DIS 2489
      #define n7E   2637
      #define n7F   2794
      #define n7FIS 2960
      #define n7G   3136
      #define n7GIS 3322
      #define n7A   3520
      #define n7AIS 3729
      #define n7H   3951

      #define n8C   4186
      #define n8CIS 4435
      #define n8D   4699
      #define n8DIS 4978
    #endif // MUSIKNOTEN

    #define TAKT_UNITS// 4/4 Takt = Grundtakt * 4
    #ifdef TAKT_UNITS
      #define M_T1   MUSIK_TAKT_UNIT    // ganze Note = Grundtakt
      #define M_T2   M_T1  / 2
      #define M_T4   M_T1  / 4
      #define M_T8   M_T1  / 8
      #define M_T16  M_T1  / 16
    #endif

    #define MUSIK_ANZ_LIEDER  3
    #define LIED_HAENSCHEN    1
    #define LIED_ALLE_VOEGEL  2
    #define LIED_ALLE_MEINE   3

    typedef struct
    {
      uint16_t note;
      uint16_t dauer;
    } tone_t;

    typedef struct
    {
      uint8_t  idx;
      uint8_t  len;
      tone_t  *ton;
    } song_t;

    class md_buzzer
    {
      public:

      void playSong(uint8_t idx);

      private:

        const tone_t song0[] =
            {
              {  n1G, M_T4},{  n1E, M_T4},{  n1E, M_T4},{PAUSE, M_T4},
              {  n1F, M_T4},{  n1D, M_T4},{  n1D, M_T4},{PAUSE, M_T4},
              {  n1C, M_T4},{  n1D, M_T4},{  n1E, M_T4},{  n1F, M_T4},
              {  n1G, M_T4},{  n1G, M_T4},{  n1G, M_T4},{PAUSE, M_T4}
            };

        song_t songs[MUSIK_ANZ_LIEDER] =
            {
              { 0, 16, &song0[0] }
            };

    };
  #endif // USE_BUZZER

#endif // _MD_BUZZER_H_