#ifndef _MAIN_H_
  #define _MAIN_H_

  #include <Arduino.h>
  #include <Wire.h>
  #include <TimeLib.h>
  //#include <SPI.h>
  #include "config.h"
  #include "md_util.h"

  // --- user interface
    #ifdef USE_TOUCHSCREEN
      #include "md_touch.h"
    #endif // USE_TOUCHSCREEN

    #ifdef USE_BUZZER
      #include "md_buzzer.h"
    #endif // USE_BUZZER

    #ifdef USE_OLED
      #include "md_oled.h"
    #endif // USE_OLED

    #ifdef USE_KEYPADSHIELD
      #include "md_keypadshield.h"
    #endif // USE_KEYPADSHIELD

    #ifdef USE_TFT
      #include "md_lcd.h"
    #endif
  //
  // --- network
    #ifdef USE_WIFI
      #include "md_webserver.h"
    #endif
  //
  // -------------------------

#endif // MAIN_H