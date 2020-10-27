#ifndef _PRJ_CONFIG_H_
  #define _PRJ_CONFIG_H_

  #include <Arduino.h>
  #include "md_defines.h"

  #define PROJ_TITLE "   ESP32 TEST"
  //
  // --- board
    //#define USED_BOARD   BRD_ESP32S_NodeMCU_AZ
    #define USED_BOARD   BRD_ESP32_D1_R32_AZ

  //
  // --- usage
    #if (USED_BOARD == BRD_ESP32S_NodeMCU_AZ)
        #define USE_TASKING
      // --- user interface
        #define USE_TOUCHSCREEN
        #define USE_BUZZER
      // --- network
        #define USE_WIFI
        #define USE_WEBSERVER
    #elif (USED_BOARD == BRD_ESP32_D1_R32_AZ)
        #define USE_TASKING
      // --- user interface
        //#define USE_OLED_091
        //#define USE_OLED_130
        //#define USE_TOUCHSCREEN
        //#define USE_BUZZER
        //#define USE_TFT1602_IIC
        #define USE_TFT1602_GPIO      // used by KEYPADSHIELD
        //#define USE_KEYPADSHIELD
      // --- network
        #define USE_WIFI
        #define USE_WEBSERVER
    #endif // USED_BOARD
  //
  // --- combined usage
    #if   (defined(USE_TOUCHSCREEN) || defined(USE_OLED_091) || defined(USE_OLED_130))
      #define USE_DISPLAY
      #define USE_OLED
    #elif (defined(USE_TFT1602_GPIO))
      #define USE_DISPLAY
      #define USE_TFT
    #elif (defined(USE_TFT1602_IIC))
      #define USE_DISPLAY
    #endif
  //
  // --- specification
    // system
      // --- IO-pins
      #define PIN_BOARD_LED 2
      #define PIN_BUZZ      21
    #ifdef USE_TASKING
      #define USE_SONGTASK
      #define TASK_SLICE_T  5000ul   // task beat [us]
    #endif // USE_TASKING
    // user interface
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

    #ifdef USE_BUZZER
      #define PLAY_MUSIC
      #define PLAY_START_MUSIC
      #define PWM_BUZZ      1
      #define MUSIC_BASE_OCTA 5        // base oktave for musik
    #endif // USE_BUZZER

    #ifdef USE_OLED
      //#define RUN_OLED_TEST
      #define DATE_DISP_LINE 3      // line on display for date / time
    #endif // USE_OLED

    #ifdef USE_TFT1602_GPIO
      #define LCD_BL 5    // D10/SS  ARDUINO
      #define LCD_EN 13   // D9
      #define LCD_RS 12   // D8
      #define LCD_D7 14   // D7
      #define LCD_D6 27   // D6
      #define LCD_D5 16   // D5
      #define LCD_D4 17   // D4
      #define LCD_ROWS 2
      #define LCD_CULS 2
    #endif // USE_TFT1602_GPIO

    #ifdef USE_KEYPADSHIELD
      #define KEYS_ADC     2    // ADC Pin GPIO02
      #define ADC_STD_RES  12   // default resolution 12 Bit
      #define ADC_RES      12   // active resolution
      #define KP_NUM_KEYS  5
      #define KP_KEY_VAL_0 354  // max ADC value of button 0
      #define KP_KEY_VAL_1 1159
      #define KP_KEY_VAL_2 2039
      #define KP_KEY_VAL_3 3045
      #define KP_KEY_VAL_4 4310
    #endif // USE_KEYPADSHIELD

    // network
    #ifdef USE_WIFI
        #define USE_NTP_SERVER
    #endif // USE_WIFI

  //
#endif // _PRJ_CONFIG_H_