#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include "WiFi.h"
  #include <WiFiUdp.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include "config.h"
  #include "md_util.h"

  bool md_scanWIFI();
  bool md_startWIFI();
  bool md_startServer();
  bool md_handleClient();
  bool md_getTime(time_t *ntpEpoche );
  #ifdef USE_NTP_SERVER
    bool md_initNTPTime();
  #endif

#endif