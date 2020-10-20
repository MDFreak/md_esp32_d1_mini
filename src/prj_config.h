#ifndef _PRJ_CONFIG_H_
  #define _PRJ_CONFIG_H_

  #include <Arduino.h>
  #include "md_defines.h"

  #define PROJ_TITLE "   ESP32 TEST"
  //
  // --- usage
    #define USE_TASKING
    #define USE_TOUCHSCREEN
    #define USE_BUZZER
    // --- network
    #define USE_WIFI
    #define USE_WEBSERVER

  // --- specification
    // system
      // --- IO-pins
      #define PIN_BOARD_LED 2
      #define PIN_BUZZ      21
    #ifdef USE_TASKING
      #define USE_SONGTASK
      #define TASK_SLICE_T  5000ul   // task beat [us]
    #endif // USE_TASKING

    #ifdef USE_TOUCHSCREEN
        #define DISP_ORIENT    0      // 0:USB oben, 1:USB links, 2:USB unten, 3:USB rechts
        #define DATE_DISP_LINE 9      // line on display for date / time
        // text display area
        #define DISP_X         0
        #define DISP_Y         0
        #define DISP_W         240
        #define DISP_H         300
        #define DISP_BCOL      0x000F // TFT_NAVY
        #define DISP_ANZ_SP    20
        #define DISP_ANZ_ZE    12
        #define DISP_Hoe_ZE    25
        #define DISP_TX_FCOL   0xB7E0 // TFT_GREENYELLOW
        #define DISP_TX_BCOL   DISP_BCOL
        // status line for messages
        #define STATUS_XCENT   120 // Centred on this
        #define STATUS_YCENT   315
        #define STATUS_XLI     0
        #define STATUS_XRE     239
        #define STATUS_YOB     DISP_H // 300
        #define STATUS_YUN     319
        #define STATUS_FCOL    0xF81F // TFT_MAGENTA
        #define STATUS_BCOL    0x0000 // TFT_BLACK
        // Keypad start position, key sizes and spacing
        #define KEY_X          40 // Centre of key
        #define KEY_Y          287
        #define KEY_W          62 // Width and height
        #define KEY_H          26
        #define KEY_SPACING_X  18 // X and Y gap
        #define KEY_SPACING_Y  20
        #define KEY_TEXTSIZE   1   // Font size multiplier
        #define KEY_NUM_LEN    3 // Anzahl der Tasten
    #endif // USE_TOUCHSCREEN

    #ifdef USE_WIFI
        #define USE_NTP_SERVER
    #endif // USE_WIFI

    #ifdef USE_BUZZER
      #define PLAY_MUSIC
      #define PLAY_START_MUSIC
      #define PWM_BUZZ      1
      #define MUSIC_BASE_OCTA 5        // base oktave for musik
    #endif // USE_BUZZER
  //
#endif // _PRJ_CONFIG_H_