#ifndef _CONFIG_H_
  #define _CONFIG_H_

  // --------------------------------------------------
  // ------ Modul-Auswahl -----------------------------
  // --------------------------------------------------
  //
  // --- System konfigrieren
  #define SERIAL_DEBUG
  #define CHECK_CONFIG
  // --- User-Interface
  #define USE_TOUCHSCREEN       // Die hoechtse Nr gewinnt
  // --- Netzwerk
  #define USE_WIFI
  #define USE_WEBSERVER
  // --- Projekte
  #define USE_PROJECT     1     // special Projekt-Ablauf (0=def, 1=test)


  // --------------------------------------------------
  // ------- Konfiguration testen ---------------------
  // --------------------------------------------------
  #ifdef CHECK_CONFIG
    // fuer WEBSERVER muss WIFI aktiv sein
    #ifdef USE_WEBSERVER
      #ifndef USE_WIFI
        #define USE_WIFI
      #endif
    #endif
  #endif

  // --------------------------------------------------
  // ------ SW-Konfigurationen ------------------------
  // --------------------------------------------------

  // --- System
  // Error Status
  #define TOUCH_ERRBIT     0x01     // Error-Flag im Error-Status
  #define SERVER_ERRBIT    0x02     // Error-Flag im Status
  #define WIFI_ERRBIT      0x04    // Error-Flag im Status

  //#define LIFE_LED         23

  // --- User-Interface

  // output status line
  #define STAT_LINELEN     20       // length of status line
  #define STAT_TIMEMIN     200ul    // min time to display status
  #define STAT_TIMEDEF    5000u     // default time to clear status

  #ifdef USE_TOUCHSCREEN
    #define DISP_ORIENT    0        // 0:USB oben, 1:USB links, 2:USB unten, 3:USB rechts
    #define DISP_CYCLE     1000ul   // Intervallzeit [us]
  #endif

  // --- Netzwerk
  #ifdef USE_WEBSERVER
    #define WEBSERVER_CYCLE 1000ul  // Intervallzeit [us]
  #endif

  #ifdef USE_WIFI
    #define WIFI_LOCAL_IP

    #if defined(WIFI_LOCAL_IP)
      #define WIFI_IP       "10.0.0.20"
      #define WIFI_GATEWAY  "10.0.0.139"
      #define WIFI_SUBNET   "255.255.255.0"
    #endif
    #define LOGIN_MAMD      0           // WLAN Moosgrabenstrasse 26
    #define LOGIN_HM        1           // WLAN Am Jungberg 9
    #define WIFI_MAMD_SSID  "MAMD-HomeG"
    #define WIFI_HM_SSID    "HS-HomeG"
    #define WIFI_PW         "ElaNanniRalf3"
    #define WIFI_CONN_DELAY 500     // Scan-Abstand [ms]
    #define WIFI_CONN_REP   15      // Anzahle der Connect-Schleifen
    #define WIFI_CONN_CYCLE 4000ul  // Intervallzeit fuer Recoonect [us]
  #endif
  // ------------------------------------------

#endif