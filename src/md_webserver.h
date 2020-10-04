#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include "config.h"
  #include "md_util.h"

#ifndef CLASS_SERVER
  bool md_scanWIFI();
  bool md_startWIFI();
  bool md_startServer();
  bool md_handleClient();
  bool md_getTime(time_t *ntpEpoche );
  #ifdef USE_NTP_SERVER
    bool md_initNTPTime();
  #endif
#else
  class md_server
  {
    private:
      char*        _ssid;
      String       _header;          // store HTTP-request

    public:
      bool md_scanWIFI();
      bool md_startWIFI();
      bool md_startServer();
      bool md_handleClient();
      bool md_getTime(time_t *ntpEpoche );
      #ifdef USE_NTP_SERVER
        bool md_initNTPTime();
      #endif

    private:
//      void drawGraph();
//      void handleRoot();
//      void handleNotFound();
      #ifdef USE_NTP_SERVER
        uint64_t md_sendNTPpacket(IPAddress& address);
      #endif

  };
#endif // CLASS_SERVER

#endif