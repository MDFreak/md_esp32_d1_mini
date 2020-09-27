#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include "WiFi.h"
  #include <WiFiClient.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include "config.h"

  bool md_scanWIFI();
  bool md_startWIFI();
  bool md_startServer();
  bool md_handleClient();

#endif