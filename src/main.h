#ifndef _MAIN_H_
  #define _MAIN_H_

  #include <Arduino.h>
  #include <unity.h>
  #include <Wire.h>
  #include <TimeLib.h>
  //#include <Print.h>
  //#include <SPI.h>
  #include <prj_config.h>
  #include <md_util.h>
  #include <md_defines.h>
    #include <ip_list.hpp>

  // --- user interface
    #ifdef USE_TOUCHSCREEN
      #include "md_touch.h"
    #endif // USE_TOUCHSCREEN

    #ifdef USE_BUZZER
      #include "md_buzzer.h"
    #endif // USE_BUZZER

    #ifdef USE_OLED_I2C
      #include "md_oled.h"
    #endif // USE_OLED_I2C

    #ifdef USE_KEYPADSHIELD
      #include "md_keypadshield.h"
    #endif // USE_KEYPADSHIELD

    #ifdef USE_TFT
      #include "md_lcd.h"
    #endif

    #ifdef USE_FRAM_I2C
      #include <md_FRAM.h>
    #endif
  //
  // --- network
    #ifdef USE_WIFI
      #include <md_webserver.h>
    #endif
  //
  // --- sensors
    #ifdef USE_DS18B20_1W
        #include <OneWire.h>
        #include <DallasTemperature.h>
      #endif

    #ifdef USE_BME280_I2C
        #include <Adafruit_Sensor.h>
        #include <Adafruit_BME280.h>
      #endif
  //
  // -------------------------

#endif // MAIN_H