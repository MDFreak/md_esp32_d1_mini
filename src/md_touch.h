#ifndef _MD_TOUCH_H_
  #define _MD_TOUCH_H_

  #include "config.h"

  #ifdef USE_TOUCHSCREEN
    #include "FS.h"
    #include <SPI.h>
    #include <TFT_eSPI.h>      // Hardware-specific library
    #include "config.h"

    #if (USE_PROJECT == 1)
      #define KEY_X 40 // Centre of key
      #define KEY_Y 96
      #define KEY_W 62 // Width and height
      #define KEY_H 30
      // Keypad start position, key sizes and spacing

      // We have a status line for messages
      #define STATUS_XCENT 120 // Centred on this
      #define STATUS_YCENT 315
      #define STATUS_XLI     0
      #define STATUS_XRE   239
      #define STATUS_YOB   300
      #define STATUS_YUN   319
      #define STATUS_FCOL  TFT_MAGENTA
      #define STATUS_BCOL  TFT_BLACK
      #define DISP_BCOL    TFT_NAVY
      #define DISP_ANZ_SP   20
      #define DISP_ANZ_ZE   12
      #define DISP_Hoe_ZE   25
      #define DISP_TX_FCOL TFT_GREENYELLOW
      #define DISP_TX_BCOL DISP_BCOL
    #else
      // Keypad start position, key sizes and spacing
      #define KEY_X 40 // Centre of key
      #define KEY_Y 96
      #define KEY_W 62 // Width and height
      #define KEY_H 30
      #define KEY_SPACING_X 18 // X and Y gap
      #define KEY_SPACING_Y 20
      #define KEY_TEXTSIZE 1   // Font size multiplier

      // Using two fonts since numbers are nice when bold
      #define NORM_FONT &FreeSansOblique12pt7b // Key label font 1
      #define BOLD_FONT &FreeSansBold12pt7b    // Key label font 2

      // Numeric display box size and location
      #define DISP_X 1
      #define DISP_Y 10
      #define DISP_W 238
      #define DISP_H 50
      #define DISP_TSIZE 3
      #define DISP_TCOLOR TFT_CYAN

      // We have a status line for messages
      #define STATUS_X 120 // Centred on this
      #define STATUS_Y 65

      // Number length, buffer for storing it and character index
      #define NUM_LEN 12
    #endif

    bool md_startTouch();
    bool md_calTouch();
    bool md_runTouch(char* pStatus);
    bool md_wrTouch(const char *msg, uint8_t zeile, uint8_t spalte);
    bool md_wrStatus(const char* msg, uint32_t stayTime);
  #endif
#endif
