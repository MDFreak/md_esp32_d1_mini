#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include <config.h>
  #include <md_util.h>

  class md_wifi
  {
    public:
      md_wifi();
      bool     md_initWIFI();
      bool     md_scanWIFI();
      bool     md_startWIFI();
      bool     md_getTime(time_t *ntpEpoche );
      bool     md_initNTPTime();
      void     setLocIP();
    protected:
      uint64_t  md_sendNTPpacket(IPAddress& address);

      IPAddress _gateip;
      IPAddress _subnet;
      IPAddress _locip;
      char*     _ssid;
      char*     _passw;
      bool      _isinit;

  };

  class md_server
  {
    public:
      bool md_startServer();
      bool md_handleClient();

    protected:
      String       _header;          // store HTTP-request
  };

extern md_wifi   wifiMD;
extern md_server webMD;

#endif