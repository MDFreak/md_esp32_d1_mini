#ifndef _CONFIG_H_
  #define _CONFIG_H_

  // --------------------------------------------------
  // ------ config constants --------------------------
  // --------------------------------------------------
  // switching projects
  #define CFG_PROJ_DEFTEST    0   // default Test
  #define CFG_PROJ_DETAILTEST 1   // detailed test

  // modes for serial debugging
  #define CFG_DEBUG_NONE      0   // no Serial output
  #define CFG_DEBUG_STARTUP   1   // report initialising
  #define CFG_DEBUG_ACTIONS   2   // report actions
  #define CFG_DEBUG_DETAILS   3   // report details for errors
  #define CFG_DEBUG_SPEZIAL   4   // spezial purpose

  // --------------------------------------------------
  // ------ modul activation ---------------------------
  // --------------------------------------------------
  //
  // --- system
  #define CHECK_CONFIG
  // --- user interface
  #define USE_TOUCHSCREEN
  //#define USE_LCD1602A
  //#define USE_KEYPAD_D1ROBOT
  //#define USE_OLED_13
  // --- network
  #define USE_WIFI
  #define USE_WEBSERVER
  // --- projects
  #define USE_PROJECT     CFG_PROJ_DETAILTEST
  // --- debugging
  #define DEBUG_MODE      CFG_DEBUG_STARTUP /*CFG_DEBUG_ACTIONS*/ /*CFG_DEBUG_DETAILS*/

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
  #define UTC_TIMEZONE     3600           // +1 hour
  #define UTC_SUMMERTIME   1
  #define MDOK             false
  #define MDERR            true

  // Error Status
  #define TOUCH_ERRBIT     0x00000001     // touchscreen
  #define SERVER_ERRBIT    0x00000002     // webserver
  #define WIFI_ERRBIT      0x00000004     // WIFI connection
  #define NTPTIME_ERRBIT   0x00000008     // NTP timeserver connection
  // serial connection
  #define SER_BAUDRATE     115200ul

  // #define LIFE_LED         1

  // --- User-Interface
  // output status line
  #define STAT_LINELEN     16       // length of status line
  #define STAT_TIMEMIN     200ul    // min time to display status
  #define STAT_TIMEDEF     5000u    // default time to clear status

  #define DISP_CYCLE       1000ul   // Intervallzeit [us]
  #ifdef USE_TOUCHSCREEN
    #define DISP_ORIENT    0        // 0:USB oben, 1:USB links, 2:USB unten, 3:USB rechts
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
    #define NTPSERVER_CYCLE 1000ul  // Intervallzeit [us]
  #endif

  #if (USE_PROJECT == CFG_PROJ_DETAILTEST)
    #define PROJ_TITLE "   ESP32 TEST"

    #ifdef USE_TOUCHSCREEN
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
      // Keypad start position, key sizes and spacing
      #define KEY_X          40 // Centre of key
      #define KEY_Y          287
      #define KEY_W          62 // Width and height
      #define KEY_H          26
      #define KEY_SPACING_X  18 // X and Y gap
      #define KEY_SPACING_Y  20
      #define KEY_TEXTSIZE   1   // Font size multiplier
      #define KEY_NUM_LEN    3 // Anzahl der Tasten
    #endif

    #ifdef USE_WIFI
      #define USE_NTP_SERVER
    #endif

    #ifdef USE_WEBSERVER
      #define CLASS_SERVER
    #endif

  #endif


  // ------------------------------------------

#endif