#ifndef _MAIN_H_
  #define _MAIN_H_

  #include <Arduino.h>
  #include <Wire.h>
  #include <TimeLib.h>
  //#include <SPI.h>
  #include "config.h"
  #include "md_util.h"

  #ifdef USE_TOUCHSCREEN
    #include "md_touch.h"
  #endif // USE_TOUCHSCREEN

  #ifdef USE_WIFI
    #include "md_webserver.h"
  #endif

  #ifdef USE_BUZZER
    #include "md_buzzer.h"
  #endif

#endif // MAIN_H