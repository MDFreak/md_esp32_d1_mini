#ifndef _CONFIG_H_
  #define _CONFIG_H_

  #include "prj_config.h"

  // --- debugging
  #define DEBUG_MODE      CFG_DEBUG_STARTUP
  //#define DEBUG_MODE      CFG_DEBUG_ACTIONS
  //#define DEBUG_MODE      CFG_DEBUG_DETAILS

  // ------ SW-Konfigurationen ------------------------

  // --- system
  #define UTC_TIMEZONE     3600           // +1 hour
  #define UTC_SUMMERTIME   1
  #define MDOK             false
  #define MDERR            true

  // --- error status bits
  #define ERRBIT_TOUCH     0x00000001     // touchscreen
  #define ERRBIT_SERVER    0x00000002     // webserver
  #define ERRBIT_WIFI      0x00000004     // WIFI connection
  #define ERRBIT_NTPTIME   0x00000008     // NTP timeserver connection

  // --- serial connection
  #define SER_BAUDRATE     115200ul

  // output status line
  #define STAT_LINELEN     16       // length of status line
  #define STAT_TIMEMIN     200ul    // min time to display status
  #define STAT_TIMEDEF     5000u    // default time to clear status

  #define DISP_CYCLE       1000ul   // Intervallzeit [us]

  // --- Netzwerk
  #ifdef USE_WEBSERVER
    #define WEBSERVER_CYCLE 1000ul  // Intervallzeit [us]
  #endif

  #ifdef USE_WIFI
    #define WIFI_LOCAL_IP
    #if defined(WIFI_LOCAL_IP)
      #define WIFI_LOCIP3   10
      #define WIFI_LOCIP2   0
      #define WIFI_LOCIP1   0
      #define WIFI_FIXIP    20
      #define WIFI_GATEWAY  139
      #define WIFI_SUBNET3  255
      #define WIFI_SUBNET2  255
      #define WIFI_SUBNET1  0
      #define WIFI_SUBNET0  0
    #endif
    #define LOGIN_MAMD      0           // WLAN Moosgrabenstrasse 26
    #define LOGIN_HM        1           // WLAN Am Jungberg 9
    #define WIFI_MAMD_SSID  "MAMD-HomeG"
    #define WIFI_HM_SSID    "HS-HomeG"
    #define WIFI_PW         "ElaNanniRalf3"
    #define WIFI_CONN_DELAY 500000ul // Scan-Abstand [us]
    #define WIFI_CONN_REP   5        // Anzahle der Connect-Schleifen
    #define WIFI_CONN_CYCLE 4000ul   // Intervallzeit fuer Recoonect [us]
    #define NTPSERVER_CYCLE 1000ul   // Intervallzeit [us]
  #endif

#endif