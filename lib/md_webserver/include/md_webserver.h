#ifndef _MD_WEB_SERVER_H_
  #define _MD_WEB_SERVER_H_

  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
  #include <md_defines.h>
  #include <md_util.h>
  #include <ip_list.hpp>

  #define WIFI_OK   false
  #define WIFI_ERR  true
  enum // locIP Status
    {
      LOCIP_FREE = 0x00,
      LOCIP_IP   = 0x01,
      LOCIP_GW   = 0x02,
      LOCIP_SN   = 0x04,
      LOCIP_OK   = LOCIP_IP | LOCIP_GW | LOCIP_SN
    };

  typedef char LoginTxt_t[14];

/*
  class md_localIP
    {
      public:
        md_localIP(){}
        md_localIP(uint32_t ip, uint32_t gw, uint32_t sn);
        ~md_localIP(){}
        void       setIP(uint32_t ip, uint32_t gw, uint32_t sn);
        uint32_t   getIP()  { return uint32_t(_IP); }
        uint32_t   getGW()  { return uint32_t(_GW); }
        uint32_t   getSN()  { return uint32_t(_SN); }
        uint8_t    status() { return ((uint8_t) _stat); }

      private:
        uint8_t    _stat = LOCIP_FREE;
        IPAddress  _IP;
        IPAddress  _GW;
        IPAddress  _SN;
    };
*/
  class md_NTPTime
    {
      public:
        md_NTPTime(){}
        ~md_NTPTime(){}
        bool getTime(time_t *ntpEpoche );
        bool initNTPTime(uint8_t summer);
      protected:
        uint64_t sendNTPpacket(IPAddress& address);
        uint8_t  _timezone = 0;
    };

  class md_wifi: public md_NTPTime
    {
      public:
        md_wifi();
        ~md_wifi(){}
        //bool initWIFI(LoginTxt_t* ssids, LoginTxt_t* pws, uint8_t anz);
        bool scanWIFI(ip_list* iplist);
        bool startWIFI();
        //void setIPList(md_localIP* piplist);
        bool getNTPTime(time_t *ntpEpoche ) { return getTime(ntpEpoche); }
        bool initNTP(uint8_t summer) { return initNTPTime(summer); }

      private:
        IPAddress   _gateip; //IPAddress
        IPAddress   _subnet; //IPAddress
        IPAddress   _locip;  //IPAddress
        char        _ssid[NET_MAX_SSID_LEN];
        char        _passw[NET_MAX_PW_LEN];
        bool        _isinit;
        //uint8_t     _lenlist;
        //LoginTxt_t* _pssidlist;
        //LoginTxt_t* _ppwlist;
        //md_localIP* _piplist;
        uint64_t    _conn_delay = 500000ul;
        uint8_t     _conn_rep   = 5;
    };

  class md_server
    {
      public:
        bool md_startServer();
        bool md_handleClient();

      protected:
        String       _header;          // store HTTP-request
    };

extern md_wifi   wifi;
extern md_server webMD;

#endif