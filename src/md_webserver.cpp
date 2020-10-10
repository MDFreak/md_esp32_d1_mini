#include "md_webserver.h"

const char* ssidMAMD = WIFI_MAMD_SSID;
const char* ssidHM   = WIFI_HM_SSID;
const char* nossid   = NULL;
const char* password = WIFI_PW;

// Set Static IP address and Gateway
#ifdef WIFI_LOCAL_IP
  //IPAddress local_IP(192, 168, 1, 184);
  IPAddress locIP (WIFI_LOCIP3, WIFI_LOCIP2, WIFI_LOCIP1, WIFI_FIXIP);
  IPAddress gateIP(WIFI_LOCIP3, WIFI_LOCIP2, WIFI_LOCIP1, WIFI_GATEWAY);
  IPAddress subNET(WIFI_SUBNET3,WIFI_SUBNET2,WIFI_SUBNET1,WIFI_SUBNET0);
#endif

#ifdef USE_NTP_SERVER
  unsigned int localPort = 2390;
  IPAddress    timeServer(129, 6, 15, 28);
  const int    NTP_PACKET_SIZE = 48;
  byte         packetBuffer[ NTP_PACKET_SIZE];
  WiFiUDP      udp;
#endif

md_wifi   wifiMD  = md_wifi();
WebServer webServ(80);
md_server webMD   = md_server();

// ------ callback WIFI --------------------------

void WiFiEvent(WiFiEvent_t event)
{
    #if (DEBUG_MODE > CFG_DEBUG_NONE)
      Serial.printf("     [WiFi-event] event: %d\n", event);
    #endif
    switch (event)
    {
      case SYSTEM_EVENT_WIFI_READY:
          Serial.println("WiFi interface ready");
          break;
      case SYSTEM_EVENT_SCAN_DONE:
          //Serial.println("Completed scan for access points");
          break;
      case SYSTEM_EVENT_STA_START:
          Serial.println("WiFi client started");
//          wifiMD.setSSID(ON);
          break;
      case SYSTEM_EVENT_STA_STOP:
          Serial.println("WiFi clients stopped");
//          wifiMD.setSSID(OFF);
          break;
      case SYSTEM_EVENT_STA_CONNECTED:
          Serial.println("Connected to access point");
//          wifiMD.setSSID(ON);
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          //Serial.print("Disconnected from WiFi status = "); Serial.println(WiFi.status());
//          wifiMD.setSSID(OFF);
          break;
      case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
          Serial.println("Authentication mode of access point has changed");
          break;
      case SYSTEM_EVENT_STA_GOT_IP:
          //Serial.print("Obtained IP address: "); Serial.println(WiFi.localIP());
//          wifiMD.setSSID(ON);
          break;
      case SYSTEM_EVENT_STA_LOST_IP:
          Serial.println("Lost IP address and IP address is reset to 0");
//          wifiMD.setSSID(OFF);
          break;
      case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
          Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
          break;
      case SYSTEM_EVENT_STA_WPS_ER_FAILED:
          Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
          break;
      case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
          Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
          break;
      case SYSTEM_EVENT_STA_WPS_ER_PIN:
          Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
          break;
              #ifdef USE_WIFI_AP
                // access point events
                case SYSTEM_EVENT_AP_START:
                    Serial.println("WiFi access point started");
                    break;
                case SYSTEM_EVENT_AP_STOP:
                    Serial.println("WiFi access point  stopped");
                    break;
                case SYSTEM_EVENT_AP_STACONNECTED:
                    Serial.println("Client connected");
                    break;
                case SYSTEM_EVENT_AP_STADISCONNECTED:
                    Serial.println("Client disconnected");
                    break;
                case SYSTEM_EVENT_AP_STAIPASSIGNED:
                    Serial.println("Assigned IP address to client");
                    break;
                case SYSTEM_EVENT_AP_PROBEREQRECVED:
                    Serial.println("Received probe request");
                    break;
                case SYSTEM_EVENT_GOT_IP6:
                    Serial.println("IPv6 is preferred");
                    break;
              #endif
              #ifdef USE_WIFI_ETHERNET
                    // ethernet events
                case SYSTEM_EVENT_ETH_START:
                    Serial.println("Ethernet started");
                    break;
                case SYSTEM_EVENT_ETH_STOP:
                    Serial.println("Ethernet stopped");
                    break;
                case SYSTEM_EVENT_ETH_CONNECTED:
                    Serial.println("Ethernet connected");
                    break;
                case SYSTEM_EVENT_ETH_DISCONNECTED:
                    Serial.println("Ethernet disconnected");
                    break;
                case SYSTEM_EVENT_ETH_GOT_IP:
                    Serial.println("Obtained IP address");
                    break;
              #endif
      default:
          break;
    }
  }

  #ifdef Dummy
    void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
  {
    Serial.print("WiFi connected - ");
    Serial.print("IP: ");
    Serial.println(IPAddress(info.got_ip.ip_info.ip.addr));
  }
  #endif
// ------ callback webserver --------------------------

void drawGraph()
{
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  webServ.send(200, "image/svg+xml", out);
}

void handleRoot()
{
  #ifdef BOARD_LED
    digitalWrite(BOARD_LED, 1);
  #endif
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

    "<html>\
      <head>\
        <meta http-equiv='refresh' content='5'/>\
        <title>ESP32 Gruss an Mathi</title>\
        <style>\
          body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
        </style>\
      </head>\
      <body>\
        <h1>Hallo Mathi vom ESP32!</h1>\
        <p>Uptime: %02d:%02d:%02d</p>\
        <img src=\"/test.svg\" />\
      </body>\
    </html>",

             hr, min % 60, sec % 60
            );
  webServ.send(200, "text/html", temp);
  #ifdef BOARD_LED
    digitalWrite(BOARD_LED, 0);
  #endif
}

void handleNotFound()
{
  #ifdef BOARD_LED
    digitalWrite(BOARD_LED, 1);
  #endif
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServ.uri();
  message += "\nMethod: ";
  message += (webServ.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServ.args();
  message += "\n";

  for (uint8_t i = 0; i < webServ.args(); i++)
  {
    message += " " + webServ.argName(i) + ": " + webServ.arg(i) + "\n";
  }

  webServ.send(404, "text/plain", message);
  Serial.println(message);
  #ifdef BOARD_LED
    digitalWrite(BOARD_LED, 0);
  #endif
}

// ------ class md_wifi --------------------------

void md_wifi::setLocIP()
{
  _locip  = locIP;
  _gateip = gateIP;
  _subnet = subNET;
}

bool md_wifi::md_scanWIFI()
{
  bool ret = MDOK;
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  _ssid = (char*) nossid;
          Serial.println(); Serial.println("WIFI scan");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
  {
          Serial.println("no networks found");
    ret = MDERR;
  }
  else
  {
            Serial.print(n); Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
              Serial.print(i + 1);
      if (WiFi.SSID(i) == ssidHM)
      {
        _ssid = (char*) ssidHM;
                Serial.print(" used: "); Serial.print(_ssid); Serial.print(" - ");
      }
      else if (WiFi.SSID(i) == ssidMAMD)
      {
        _ssid = (char*) ssidMAMD;
                Serial.print(" used: "); Serial.print(_ssid); Serial.print(" - ");
      }
      else
      {
              Serial.print("       ");
      }

              Serial.print(WiFi.SSID(i));
              Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print(")");
              Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
              #if (DEBUG_MODE == CFG_DEBUG_NONE)
                if (_isssid == ON)
                {
                  break;
                }
              #endif
    }
  }
  WiFi.disconnect();
          #if (DEBUG_MODE == CFG_DEBUG_NONE)
            Serial.println("");
          #endif
  return ret;
}

bool md_wifi::md_startWIFI()
{
  bool ret = MDERR;
          Serial.println("md_startWIFI");
  if (_isinit == false)
  {
    #ifdef WIFI_LOCAL_IP
      if ( WiFi.config(_locip, _gateip, _subnet /*, primaryDNS, secondaryDNS*/) == false)
      {
              #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
                Serial.println("STA Failed to configure -> exit");
              #endif
        return false;
      }
    #endif

    WiFi.mode(WIFI_STA);
    WiFi.onEvent(WiFiEvent); // start interrupt handler
    _isinit = true;
  }
          #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
            Serial.print("disconnect - stat "); Serial.print(WiFi.status());
            Serial.print(" _isconn "); Serial.println((int8_t) _isconn);
          #endif
  WiFi.disconnect();       // disconnect first
  delay(100);

  ret = md_scanWIFI();     // scan WiFi
  if (ret == MDOK)
  {
          #if (DEBUG_MODE >= CFG_DEBUG_DETAILS)
            Serial.print("nach scan _isssid = ");Serial.println((int8_t) _isssid);
          #endif

    WiFi.begin(_ssid, password); // start connection
    Serial.println("");

    // Wait for connection
    uint8_t timeout = (uint8_t) WIFI_CONN_REP;
    while ((WiFi.status() != WL_CONNECTED) && (timeout > 0))
    {
      delay(WIFI_CONN_DELAY);
              #if (DEBUG_MODE > CFG_DEBUG_NONE)
                Serial.print(".");
              #endif
      timeout--;
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
            #if (DEBUG_MODE > CFG_DEBUG_NONE)
              Serial.println("");
              Serial.print("Connected to ");
              Serial.println(_ssid);
              Serial.print("IP address: ");
              Serial.println(WiFi.localIP());
              Serial.print("MAC address: ");
              Serial.println(WiFi.macAddress());
            #endif
    if (MDNS.begin("esp32"))
    {
              #if (DEBUG_MODE > CFG_DEBUG_NONE)
                Serial.println("MDNS responder started");Serial.println();
              #endif
    }
//    #ifdef USE_NTP_SERVER
//      md_initNTPTime();
//    #endif
  }
  else
  {
    ret = MDERR;
            #if (DEBUG_MODE > CFG_DEBUG_NONE)
              Serial.println("Connection failed -> timout");
            #endif
  }
  return ret;
}

#ifdef USE_NTP_SERVER
  bool md_wifi::md_initNTPTime()
    {
      udp.begin(localPort);

      return MDOK;
    }

  bool md_wifi::md_getTime(time_t *ntpEpoche)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      md_sendNTPpacket(timeServer);
      sleep(1);
      //delay(1000);

      int cb = udp.parsePacket();
Serial.print("parsePacket cb = "); Serial.println(cb);
      if (cb > 0)
      {
        cb = udp.read(packetBuffer, NTP_PACKET_SIZE);
Serial.print("read Packet cb = "); Serial.println(cb);
        if (cb == NTP_PACKET_SIZE)
        {
          unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
          unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

          unsigned long secsSince1900 = highWord << 16 | lowWord;

          const unsigned long seventyYears = 2208988800UL;
          //unsigned long epoch = secsSince1900 - seventyYears;
          *ntpEpoche = secsSince1900 - seventyYears
                     + UTC_TIMEZONE + UTC_SUMMERTIME * 3600;
          return MDOK;
        }
      }
    }
    return MDERR;
  }

  uint64_t md_wifi::md_sendNTPpacket(IPAddress& address)
  {
    //Serial.println("sending NTP packet...");
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12]  = 49;
    packetBuffer[13]  = 0x4E;
    packetBuffer[14]  = 49;
    packetBuffer[15]  = 52;

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    udp.beginPacket(address, 123); //NTP requests are to port 123
    udp.write(packetBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
    return 0;
  }
#endif


// ------ class md_server --------------------------

bool md_server::md_startServer()
{
    webServ.on("/", handleRoot);
    webServ.on("/test.svg", drawGraph);
    webServ.on("/inline", []()
      {
        webServ.send(200, "text/plain", "this works as well");
      });
    webServ.onNotFound(handleNotFound);
    webServ.begin();
    Serial.println("HTTP server started");
    return false;
//  }
}

bool md_server::md_handleClient()
{
  webServ.handleClient();
  return false;
}

#ifdef Dummy
void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }


  udp.begin(localPort);

}

void loop()
{
  sendNTPpacket(timeServer);
  delay(1000);

  int cb = udp.parsePacket();

    udp.read(packetBuffer, NTP_PACKET_SIZE);

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    unsigned long secsSince1900 = highWord << 16 | lowWord;

    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;

    int stund  = (epoch  % 86400L) / 3600 + 1;
    int minut   = (epoch  % 3600) / 60;
    int sekunde = epoch % 60;
    String stunde = String(stund);
    String minutestring = String(minut);
    if(minut < 10)
    {
      minutestring = "0" + minutestring;
    }


    Serial.println(stunde);
    Serial.println("|");
    Serial.println(minutestring);
    Serial.println("|");
    Serial.println(sekunde);
    Serial.println("|");

  delay(10000);
}


unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
#endif