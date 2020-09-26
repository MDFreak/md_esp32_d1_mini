#ifndef _CONFIG_H_
  #define _CONFIG_H_

  // ------ Modul-Auswahl ---------------
  // --- System konfigrieren
  #define SERIAL_DEBUG
  #define CHECK_CONFIG
  // --- User-Interface
  #define USE_TOUCHSCREEN       // Die hoechtse Nr gewinnt
  #define USE_DEFTOUCH          // Demo Touch-Ablauf
  //#define USE_MD_TOUCH1         // Projekt-Ablauf 1
  //#define USE_MD_TOUCH2         // Projekt-Ablauf 2
  //#define USE_MD_TOUCH3         // Projekt-Ablauf 3
  //#define USE_MD_TOUCH4         // Projekt-Ablauf 3
  // --- Netzwerk
  #define USE_WIFI
  #define USE_WEBSERVER

  // ------- Konfiguration testen
  #ifdef CHECK_CONFIG
    // fuer WEBSERVER muss WIFI aktiv sein
    #ifdef USE_WEBSERVER
      #ifndef USE_WIFI
        #define USE_WIFI
      #endif
    #endif

    // nur eine Anwendung darf aktiv sein
    #if defined(USE_MD_TOUCH1) && defined(USE_DEFTOUCH)
      #undef USE_DEFTOUCH
    #endif

    #if defined(USE_MD_TOUCH2) && defined(USE_DEFTOUCH)
      #undef USE_DEFTOUCH
    #endif
    #if defined(USE_MD_TOUCH2) && defined(USE_MD_TOUCH1)
      #undef USE_MD_TOUCH1
    #endif

    #if defined(USE_MD_TOUCH3) && defined(USE_DEFTOUCH)
      #undef USE_DEFTOUCH
    #endif
    #if defined(USE_MD_TOUCH3) && defined(USE_MD_TOUCH1)
      #undef USE_MD_TOUCH1
    #endif
    #if defined(USE_MD_TOUCH3) && defined(USE_MD_TOUCH2)
      #undef USE_MD_TOUCH2
    #endif

    #if defined(USE_MD_TOUCH4) && defined(USE_DEFTOUCH)
      #undef USE_DEFTOUCH
    #endif
    #if defined(USE_MD_TOUCH4) && defined(USE_MD_TOUCH1)
      #undef USE_MD_TOUCH1
    #endif
    #if defined(USE_MD_TOUCH4) && defined(USE_MD_TOUCH2)
      #undef USE_MD_TOUCH1
    #endif
    #if defined(USE_MD_TOUCH4) && defined(USE_MD_TOUCH3)
      #undef USE_MD_TOUCH1
    #endif
  #endif

  // ------ SW-Konfigurationen ---------------
  // --- System
  #define BOARD_LED   1

  // --- User-Interface
  #ifdef USE_TOUCHSCREEN
    #define TOUCH_CYCLE  10ul       // Intervallzeit [us]
    #define TOUCH_ERRBIT 0x01       // Error-Flag im Status
  #endif

  // --- Netzwerk
  #ifdef USE_WEBSERVER
    #define WEBSERVER_CYCLE 1000ul  // Intervallzeit [us]
    #define SERVER_ERRBIT   0x02    // Error-Flag im Status
  #endif

  #ifdef USE_WIFI
    #define WIFI_SSID "MAMD-HomeG"
    #define WIFI_PW   "ElaNanniRalf3"
    #define WIFI_ERRBIT     0x04    // Error-Flag im Status
    #define WIFI_SCAN_DELAY 500     // Scan-Abstand [ms]
    #define WIFI_SCAN_TOUT  30      // Anzahle der Scan-Wiederholungen
  #endif
  // ------------------------------------------

#endif