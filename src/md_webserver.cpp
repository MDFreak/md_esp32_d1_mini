#include "md_webserver.h"

const char* ssidMAMD = WIFI_MAMD_SSID;
const char* ssidHM   = WIFI_HM_SSID;
const char* nossid   = NULL;
const char *password = WIFI_PW;

// Set Static IP address and Gateway
#ifdef WIFI_LOCAL_IP
  //IPAddress local_IP(192, 168, 1, 184);
  IPAddress local_IP(10,0,0,20);
  IPAddress gateway(10,0,0,139);
  IPAddress subnet(255,255,0,0);
  //IPAddress primaryDNS(8, 8, 8, 8); // optional
  //IPAddress secondaryDNS(8, 8, 4, 4); // optional
#endif

#ifdef USE_NTP_SERVER
  unsigned int localPort = 2390;
  IPAddress timeServer(129, 6, 15, 28);
  const int NTP_PACKET_SIZE = 48;
  byte packetBuffer[ NTP_PACKET_SIZE];
  WiFiUDP udp;
#else
  const char* ntpServer          = "pool.ntp.org";
  const long  gmtOffset_sec      = 3600;
  const int   daylightOffset_sec = 3600;
  WiFiUDP     ntpUDP;
//  NTPClient   timeClient(ntpUDP, ntpServer);
//  NTPClient   timeClient(ntpUDP);
  bool        newDay             = true;
#endif

char*        ssid = (char*) nossid;
WebServer    server(80);
String       header;          // store HTTP-request

// ------ callback functions --------------------------

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

  server.send(200, "image/svg+xml", out);
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
    server.send(200, "text/html", temp);
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
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
    Serial.println(message);
    #ifdef BOARD_LED
      digitalWrite(BOARD_LED, 0);
    #endif
  }

// ------ private functions --------------------------
#ifdef USE_NTP_SERVER
  unsigned long sendNTPpacket(IPAddress& address);
#endif

// ------ Setup-Funktionen --------------------------
bool md_scanWIFI()
{
  bool ret = false;
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println(); Serial.println("WIFI scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
    ret = true;
    //return true;
  }
  else
  {
    bool found = false;
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      if (WiFi.SSID(i) == ssidHM)
      {
        ssid = (char*) ssidHM;
        found = true;
        Serial.print(" used: "); Serial.print(ssid); Serial.print(" - ");
      }
      else if (WiFi.SSID(i) == ssidMAMD)
      {
        ssid = (char*) ssidMAMD;
        found = true;
        Serial.print(" used: "); Serial.print(ssid); Serial.print(" - ");
      }
      Serial.print(WiFi.SSID(i));
      Serial.print(" ("); Serial.print(WiFi.RSSI(i)); Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
      if (found == true)
      {
        break;
      }
    }
  }
  Serial.println("");

  return ret;
}

bool md_startWIFI()
{
  bool ret = false;
// Configures static IP address
  WiFi.mode(WIFI_STA);

  WiFi.disconnect();
  delay(100);

  #ifdef WIFI_LOCAL_IP
//    if ( WiFi.config(local_IP, gateway, subnet /*, primaryDNS, secondaryDNS*/))
    if ( WiFi.config(local_IP, gateway, subnet /*, primaryDNS, secondaryDNS*/) == false)
    {
      Serial.println("STA Failed to configure");
      //ret = true;
      return false;
    }
  #endif

  ret = md_scanWIFI();
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  uint8_t timeout = (uint8_t) WIFI_CONN_REP;
  while ((WiFi.status() != WL_CONNECTED) && (timeout > 0))
  {
    delay(WIFI_CONN_DELAY);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp32"))
    {
      Serial.println("MDNS responder started");
    }
    #ifdef USE_NTP_SERVER
      md_initNTPTime();
    #endif
  }
  else
  {
    Serial.println("Connection failed -> timout");
    ret = true;
  }
  return ret;
}

bool md_startServer()
{
//  if (WiFi.status() != WL_CONNECTED)
//  {
    server.on("/", handleRoot);
    server.on("/test.svg", drawGraph);
    server.on("/inline", []() {
      server.send(200, "text/plain", "this works as well");
      });
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
    return false;
//  }
}

#ifdef USE_NTP_SERVER
  bool md_initNTPTime()
    {
      // Init and get the time
      //configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//      timeClient.setTimeOffset(gmtOffset_sec + daylightOffset_sec);
//      timeClient.begin();
      udp.begin(localPort);

      return false;
    }

  bool md_getTime(time_t *ntpEpoche)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      //if(!getLocalTime(intm))
      //{
      //  Serial.println("Failed to obtain time");
      //  return true;
      //}
//      *ntpEpoche = timeClient.getEpochTime();

            #ifdef Dummy
              Serial.println(intm, "%A, %B %d %Y %H:%M:%S");
              Serial.print("Day of week: ");
              Serial.println(intm, "%A");
              Serial.print("Month: ");
              Serial.println(intm, "%B");
              Serial.print("Day of Month: ");
              Serial.println(intm, "%d");
              Serial.print("Year: ");
              Serial.println(intm, "%Y");
              Serial.print("Hour: ");
              Serial.println(intm, "%H");
              Serial.print("Hour (12 hour format): ");
              Serial.println(intm, "%I");
              Serial.print("Minute: ");
              Serial.println(intm, "%M");
              Serial.print("Second: ");
              Serial.println(intm, "%S");

              Serial.println("Time variables");
              char timeHour[3];
              strftime(timeHour,3, "%H", intm);
              Serial.println(timeHour);
              char timeWeekDay[10];
              strftime(timeWeekDay,10, "%A", intm);
              Serial.println(timeWeekDay);
              Serial.println();
            #endif
      sendNTPpacket(timeServer);
      delay(1000);

      int cb = udp.parsePacket();
      cb = cb;
      udp.read(packetBuffer, NTP_PACKET_SIZE);

      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

      unsigned long secsSince1900 = highWord << 16 | lowWord;

      const unsigned long seventyYears = 2208988800UL;
      //unsigned long epoch = secsSince1900 - seventyYears;
      *ntpEpoche = secsSince1900 - seventyYears
                 + UTC_TIMEZONE + UTC_SUMMERTIME * 3600;
      return false;
    }
    return true;
  }
#endif

bool md_handleClient()
{
  server.handleClient();
  return false;
}

#ifdef USE_NTP_SERVER
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
    return 0;
  }
#endif

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