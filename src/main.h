#ifndef _MAIN_H_
  #define _MAIN_H_

  #include <Arduino.h>
  #include <Wire.h>
  #include <TimeLib.h>
  //#include <Print.h>
  //#include <SPI.h>
  #include "config.h"
  #include <md_util.h>

  // --- user interface
    #ifdef USE_TOUCHSCREEN
      #include "md_touch.h"
    #endif // USE_TOUCHSCREEN

    #ifdef USE_BUZZER
      #include "md_buzzer.h"
    #endif // USE_BUZZER

    #ifdef USE_OLED
      #include <md_oled.h>
    #endif // USE_OLED

    #ifdef USE_KEYPADSHIELD
      #include "md_keypadshield.h"
    #endif // USE_KEYPADSHIELD

    #ifdef USE_TFT
      #include "md_lcd.h"
    #endif

    #ifdef USE_FRAM_32K_I2C
      #include "md_FRAM.h"
    #endif
  //
  // --- network
    #ifdef USE_WIFI
      #include "md_webserver.h"
    #endif
  //
  // --- sensors
    #ifdef USE_DS18B20
        #include <OneWire.h>
        #include <DallasTemperature.h>
      #endif
  //
  // -------------------------

#endif // MAIN_H