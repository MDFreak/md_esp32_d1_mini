#include "md_webserver.h"
#include "config.h"

const char *ssid     = WIFI_SSID;
const char *password = WIFI_PW;

WebServer    server(80);

// ------ Callback-Funktionen --------------------------

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
          <title>ESP32 Demo</title>\
          <style>\
            body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
          </style>\
        </head>\
        <body>\
          <h1>Hello from ESP32!</h1>\
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

// ------ Setup-Funktionen --------------------------

bool md_startWIFI()
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
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
    Serial.println("");

    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    uint8_t timeout = (uint8_t) WIFI_SCAN_TOUT;
    while ((WiFi.status() != WL_CONNECTED) && (timeout > 0))
    {
      delay(WIFI_SCAN_DELAY);
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
    }
    else
    {
      Serial.println("Connection failed -> timout");
      ret = true;
    }
  }
  return ret;
}

bool md_startServer()
{
  server.on("/", handleRoot);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
    });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  Serial.println(); Serial.println("Setup done");

  return false;
}

bool md_handleClient()
{
  server.handleClient();
  return false;
}

