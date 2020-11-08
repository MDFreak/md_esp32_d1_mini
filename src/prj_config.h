#ifndef _PRJ_CONFIG_H_
  #define _PRJ_CONFIG_H_

  #include <Arduino.h>
  #include "md_defines.h"

  #define PROJ_TITLE "   ESP32 TEST"
  //
  // --- board
    #define BOARD   BRD_ESP32_D1_R32_AZ
      //#define BOARD   BRD_ARD_NANO_V3_AZ_V5
      //#define BOARD   BRD_ARD_UNO_V3_AZ_V5
      //#define BOARD   BRD_ESP32S_Node_AZ_3V3
  //
  // --- usage
    #if !(BOARD ^ BRD_ESP32S_Node_AZ_3V3)
        #define USE_TASKING
      // --- network
        #define USE_WIFI
        #define USE_WEBSERVER
      // --- user interface
        #define USE_OLED_091_AZ_3V3
          //#define USE_OLED_096_AZ_3V3
          //#define USE_OLED_130_AZ_3V3
          //#define USE_TFT1602_IIC_XA_3V3
          //#define USE_TOUCHSCREEN
        #ifdef  USE_TOUCHSCREEN
            #define USE_TOUCHXPT2046_AZ_3V3
            #define KEYS KEYS_TOUCHXPT2046_AZ_3V3
          #endif // USE_TOUCHSCREEN
        #define AOUT AOUT_PAS_BUZZ_3V5V
      // --- connections
        #define SDA1 21
        #define SCL1 22
        #define SDA2 17
        #define SCL2 16

    #elif !(BOARD ^ BRD_ESP32_D1_R32_AZ)
        #define USE_TASKING
      // --- network
        #define USE_WIFI
        #define USE_WEBSERVER
      // --- user interface
        #define USE_DISP
        #ifdef USE_DISP
            #define USE_OLED
            #ifdef USE_OLED
                // select I2C device
                #define OLED1 DISP_OLED_130_AZ_3V3
                  #define STATUS1_LINE    5
                  #define OLED1_I2C_ADDR  0x3C
                #define OLED2 DISP_OLED_091_AZ_3V3
                  #define STATUS2_LINE    3
                  #define OLED2_I2C_ADDR  0x3C
                //#define OLED?  DISP_OLED_096_AZ_3V3
              #endif //USE_OLED

            //#define USE_TFT
            #ifdef USE_TFT
                    //#define USE_TFT1602_IIC_XA_3V3
                    //#define USE_TOUCHXPT2046_AZ_3V3
              #endif
          #endif
        //#define KEYS KEYS_TOUCHXPT2046_AZ_3V3
        //#define USE_KEYPADSHIELD
        //#define OUT1 AOUT_PAS_BUZZ_3V5V
        #ifdef USE_KEYPADSHIELD
            #define USE_TFT1602_GPIO_RO_3V3 // used by KEYPADSHIELD
            #define KEYS KEYS_Keypad_ANA0_RO_3V3  // used by KEYPADSHIELD
          #endif // USE_KEYPADSHIELD
      // --- connections
        #define I2C1_SDA   21
        #define I2C1_SCL   22
        #define I2C2_SDA   17
        #define I2C2_SCL   16

    #elif !(BOARD ^ BRD_ARD_NANO_V3_AZ_V5)
        #define USE_KEYPADSHIELD
        #ifdef USE_KEYPADSHIELD
            #define USE_TFT1602_GPIO_RO_V5  // used by KEYPADSHIELD
            #define KEYS_Keypad_ANA0_RO_V5        // used by KEYPADSHIELD
          #endif // USE_KEYPADSHIELD
    #elif !(BOARD ^ BRD_ARD_UNO_V3_AZ_V5)
        #define USE_KEYPADSHIELD
        #ifdef USE_KEYPADSHIELD
            #define USE_TFT1602_GPIO_RO_V5  // used by KEYPADSHIELD
            #define KEYS_Keypad_ANA0_RO_V5        // used by KEYPADSHIELD
          #endif // USE_KEYPADSHIELD

    #endif // BOARD
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
      //#define SCAN_IIC
    // network
    #ifdef USE_WIFI
        #define USE_NTP_SERVER
      #endif // USE_WIFI
    // user interface
    #ifdef AOUT
        #if !(AOUT ^ AOUT_PAS_BUZZ_3V5V)
            #define PLAY_MUSIC
            #define PLAY_START_MUSIC
            #define PWM_BUZZ      1
            #define MUSIC_BASE_OCTA 5        // base oktave for musik
          #endif // AOUT
      #endif

    #ifdef USE_DISP
        #define USE_STATUS
        #define DISP1_MAXCOLS 20
        #define DISP1_MAXROWS 6
        #define DISP2_MAXCOLS 20
        #define DISP2_MAXROWS 3
        #ifdef USE_OLED
            #ifdef OLED1
                #ifdef USE_STATUS
                    #define USE_STATUS1
                  #endif
              #endif
            #ifdef OLED2
                #ifdef USE_STATUS
                    #define USE_STATUS2
                  #endif
              #endif
          #endif
        #ifdef USE_TOUCHSCREEN
          #endif // USE_TOUCHSCREEN


        #if defined(USE_TOUCHXPT2046_AZ_3V3)
          #define DISP_ORIENT    0      // 0:USB oben, 1:USB links, 2:USB unten, 3:USB rechts
          #define DATE_DISP_COL  0
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
          #endif
        #if (defined(USE_TFT1602_GPIO_RO_V5) || defined(USE_TFT1602_GPIO_RO_3V3))
          #define DATE_DISP_COL   0
          #define DATE_DISP_LINE  0    // line on display for date / time
          #define LCD_BL          5    // D10/SS  ARDUINO
          #define LCD_EN          13   // D9
          #define LCD_RS          12   // D8
          #define LCD_D7          14   // D7
          #define LCD_D6          27   // D6
          #define LCD_D5          16   // D5
          #define LCD_D4          17   // D4
          #define LCD_ROWS        2
          #define LCD_CULS        2
          #endif
      #endif // DISP

    #if (!(KEYS ^ KEYS_Keypad_ANA0_RO_V5) || !(KEYS ^ KEYS_Keypad_ANA0_RO_3V3))
        #define USE_KEYPADSHIELD
        #define KEYS_ADC        34   // ADC Pin GPIO02
        #define ADC_STD_RES     12   // default resolution 12 Bit
        #define ADC_RES         12   // active resolution
        #define KP_NUM_KEYS     5
        #define KP_KEY_VAL_1    200  // max ADC value of button 0
        #define KP_KEY_VAL_2    750
        #define KP_KEY_VAL_3    1470
        #define KP_KEY_VAL_4    2330
        #define KP_KEY_VAL_5    3200

    #elif !(KEYS ^ KEYS_TOUCHXPT2046_AZ_3V3)
        // Keypad start position, key sizes and spacing
        #define KEY_X          40 // Centre of key
        #define KEY_Y          287
        #define KEY_W          62 // Width and height
        #define KEY_H          26
        #define KEY_SPACING_X  18 // X and Y gap
        #define KEY_SPACING_Y  20
        #define KEY_TEXTSIZE   1   // Font size multiplier
        #define KEY_NUM_LEN    3 // Anzahl der Tasten
      #endif // KEYS_Keypad_ANA0_RO_V5

  //
#endif // _PRJ_CONFIG_H_