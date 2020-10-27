#ifndef _MD_DEFINES_H_
  #define _MD_DEFINES_H_

  // ------ config constants --------------------------
  #ifndef CFG_DEFS
    #define CFG_DEFS
    //
    // --- generic
      #define NN  -1  // not used
      #define OFF  0  // not active
      #define ON   1  // active

      #define CR   13 // carrige return
      #define LF   10 // line feed
      #define LN   LF
    //
    // --- macros
      #define SET(b)    (b = true)
      #define RESET(b)  (b = false)

      #define SOUT(c)   (Serial.print(c))
      #define SOUTLN(c) (Serial.println(c))

    //
    // --- boards
      #define  BRD_NN                0
      #define  BRD_ESP32S_NodeMCU_AZ 1
      #define  BRD_ESP32_D1_R32_AZ   2
      #define  BRD_ARD_NANO_V3_AZ    3
    //
    // --- assemblies
      #define ASS_NN                NN
      #define ASS_TOUCH_ESP32_AZ    1

    //
    // --- switching projects
      #define CFG_PROJ_DEFTEST      0   // default Test
      #define CFG_PROJ_DETAILTEST   1   // detailed test

    //
    // --- modes for serial debugging
      #define CFG_DEBUG_NONE        0   // no Serial output
      #define CFG_DEBUG_STARTUP     1   // report initialising
      #define CFG_DEBUG_ACTIONS     2   // report actions
      #define CFG_DEBUG_DETAILS     3   // report details for errors
      #define CFG_DEBUG_SPEZIAL     4   // spezial purpose

    //
    // --- music defines
      //
      // --- structures
        typedef struct {
          int8_t   note;     // NOTE_C .. NOTE_B
          int8_t   octa;     // oktave 0 .. 7
          uint64_t beat;     // MB1 = base
        } tone_t;

      //
      // --- music units
        //
        // --- beat units --------------------
          #define MUSIC_BASEBEAT_US       250000ul  // base beat of 1/4 note = 250 ms
          #define MUSIC_RATIO_P100        80          // 80% ON / 20% OFF
          #define MB44  MUSIC_BASEBEAT_US * 4  // 4/4
          #define MB43  MUSIC_BASEBEAT_US * 3  // 3/4
          #define MB42  MUSIC_BASEBEAT_US * 2  // 2/4
          #define MB4   MUSIC_BASEBEAT_US * 1  // 1/4 note = basebeat
          #define MB8   MUSIC_BASEBEAT_US / 2  // 1/8
          #define MB16  MUSIC_BASEBEAT_US / 4  // 1/16
          #define MB32  MUSIC_BASEBEAT_US / 8  // 1/32
        //
        // --- octave units ------------------
          #ifndef MUSIC_BASE_OCTA
            #define MUSIC_BASE_OCTA  5
          #endif // MUSIC_BASE_OCTA
          #define ON3   MUSIC_BASE_OCTA + 3  // octave negative 1
          #define ON2   MUSIC_BASE_OCTA + 2  // octave negative 1
          #define ON1   MUSIC_BASE_OCTA + 1  // octave negative 1
          #define OP0   MUSIC_BASE_OCTA      // (base-) octave positiv 0
          #define OP1   MUSIC_BASE_OCTA - 1  // octave positiv 1
          #define OP2   MUSIC_BASE_OCTA - 2  // octave positiv 1
          #define OP3   MUSIC_BASE_OCTA - 3  // octave positiv 1
          #define OP4   MUSIC_BASE_OCTA - 4  // octave positiv 1
        //
        // --- notes -------------------------
          #define PAUSE   -1
        //
      //
      // --- songs
  	    #define SONG_HAENSCHEN_KLEIN  0
          const uint64_t SONG0_BEAT_US = MUSIC_BASEBEAT_US;
          const tone_t   SONG0_NOTES[] =
              { // Haenschen klein
                {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_C ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },
                {NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
                {NOTE_C ,OP0,MB42},                    { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },
                {NOTE_D ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_F ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },
                {NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
                {NOTE_C ,OP0,MB42},                    { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 }
              };
            const uint16_t SONG0_LEN     = sizeof(SONG0_NOTES)/sizeof(tone_t);    //62;
        //#define SONG_ALLE_VOEGLEIN    1
        //#define SONG_ALLE_ENTCHEN     2
    //
  #endif // CFG_DEFS

#endif   // _MD_DEFINES_H_