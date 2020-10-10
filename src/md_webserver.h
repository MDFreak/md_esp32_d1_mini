#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include "config.h"
  #include "md_util.h"

  #define NN  -1  // not used
  #define OFF  0  // not active
  #define ON   1  // active
  class md_wifi
  {
    public:
      md_wifi() { /*_isssid = NN; _isconn = NN;*/ _isinit = false; };
      bool     md_scanWIFI();
      bool     md_startWIFI();
      bool     md_getTime(time_t *ntpEpoche );
      bool     md_initNTPTime();
      void     setLocIP();
      /*
      void     setSSID(int8_t sig) { _isssid = sig;      };
      int8_t   isSSID()            { return _isssid;     };
      void     setCONN(int8_t sig) { _isconn = sig;      };
      int8_t   isCONN()            { return _isconn;     };
      */
    protected:
      uint64_t  md_sendNTPpacket(IPAddress& address);

      IPAddress _gateip;
      IPAddress _subnet;
      IPAddress _locip;
      char*     _ssid;
      //int8_t    _isssid;
      //int8_t    _isconn;
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