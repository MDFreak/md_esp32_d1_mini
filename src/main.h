#ifndef _MAIN_H_
  #define _MAIN_H_

  #include <Arduino.h>
  #include "config.h"
  #include "md_util.h"

  #ifdef USE_WIFI
    #include "md_webserver.h"
  #endif

  #ifdef USE_TOUCHSCREEN
    #include "md_touch.h"
  #endif // USE_DISPLAY

#endif // MAIN_H