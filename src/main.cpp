#include "main.h"

// --- declarations
  // ------ system -----------------------
    #define CHECK_ERRORS
    #ifdef CHECK_ERRORS
      uint16_t     md_error  = 0    // Error-Status bitkodiert -> 0: alles ok
                               #ifdef USE_WIFI
                                 + ERRBIT_WIFI
                                 #ifdef USE_NTP_SERVER
                                   + ERRBIT_NTPTIME
                                 #endif
                               #endif
                               #ifdef USE_WEBSERVER
                                 + ERRBIT_SERVER
                               #endif
                               #ifdef USE_TOUCHSCREEN
                                 + ERRBIT_TOUCH
                               #endif
                               ;
      #endif
  //
  // ------ network ----------------------
    #ifdef USE_WIFI
      msTimer wifiT = msTimer(WIFI_CONN_CYCLE);
      #endif

    #ifdef USE_WEBSERVER
      msTimer servT = msTimer(WEBSERVER_CYCLE);
      #endif // USE_WEBSERVER

    #ifdef USE_NTP_SERVER
      msTimer ntpT    = msTimer(NTPSERVER_CYCLE);
      time_t  ntpTime = 0;
      bool    ntpGet  = true;
      #endif // USE_WEBSERVER

  //
  // ------ User-Interface ---------------
    md_touch      touch      = md_touch();
    msTimer       dispT      = msTimer(DISP_CYCLE);
    uint32_t      ze         = 1;      // aktuelle Schreibzeile
    char          outBuf[2*STAT_LINELEN] = "";
//
// --- private functions
  // ------ NTP server -------------------
    #ifdef USE_NTP_SERVER
      void initNTPTime()
        {
          bool ret = wifiMD.md_initNTPTime();
                #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                  Serial.print("initNTPTime ret="); Serial.print(ret);
                #endif
          md_error = setBit(md_error, ERRBIT_NTPTIME, ret);
                #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                  Serial.print("  md_error="); Serial.println(md_error);
                #endif
          #ifdef USE_TOUCHSCREEN
            if ((md_error & ERRBIT_WIFI) == 0)
            {
              while (touch.wrStatus("NTPTime ok"));
            }
            else
            {
              while (touch.wrStatus("NTPTime error"));
            }
            #endif
        }
    #endif // USE_NTP_SERVER
  //
  // ------ WIFI -------------------------
    #ifdef USE_WIFI
      void startWIFI()
        {
          #ifdef USE_TOUCHSCREEN
            while (touch.wrStatus("  start WIFI"));
          #endif
          wifiMD.setLocIP();
          bool ret = wifiMD.md_initWIFI();
                  #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                    Serial.print(millis());
                    Serial.print(" initWIFI ret="); Serial.println(ret);
                  #endif
          if (ret == MDOK)
          {
            ret = wifiMD.md_scanWIFI();
                  #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                    Serial.print(millis());
                    Serial.print(" scanWIFI ret="); Serial.println(ret);
                  #endif
          }
          if (ret == MDOK)
          {
            ret = wifiMD.md_startWIFI();
                  #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                    Serial.print("startWIFI ret="); Serial.print(ret);
                  #endif
          }
          md_error = setBit(md_error, ERRBIT_WIFI, ret);
                #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                  Serial.print("  md_error="); Serial.println(md_error);
                  #endif

          #ifdef USE_TOUCHSCREEN
            if ((md_error & ERRBIT_WIFI) == 0)
            {
              while (touch.wrStatus("WIFI connected"));
            }
            else
            {
              while (touch.wrStatus("WIFI error"));
            }
            #endif
          #ifdef USE_NTP_SERVER
            if((md_error & ERRBIT_WIFI) == 0) // WiFi ok
            {
              if((md_error & ERRBIT_NTPTIME) != 0) // WiFi ok
              {
                initNTPTime();
              }
            }
            #endif
        }
    #endif // USE_WIFI

    #ifdef USE_WEBSERVER
      void startWebServer()
        {
          bool ret = MDERR;
          if ((md_error & ERRBIT_SERVER) != 0)
          {
            #ifdef USE_TOUCHSCREEN
              while (touch.wrStatus("start webserver"));
            #endif
            if ((md_error & ERRBIT_WIFI) == 0)
            {
              ret = webMD.md_startServer();
                  #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
        //              Serial.print("startServer ret="); Serial.print(ret);
                  #endif
            }
            md_error = setBit(md_error, ERRBIT_SERVER, ret);
                  #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
        //            Serial.print("  md_error="); Serial.println(md_error);
                  #endif

            #ifdef USE_TOUCHSCREEN
              if ((md_error & ERRBIT_SERVER) == 0)
              {
                while (touch.wrStatus("Webserver online"));
              }
              else
              {
                while (touch.wrStatus("Webserver error"));
              }
            #endif
          }
        }
    #endif // USE_WEBSERVER
  //
  // ------ touchscreen -----------------
    #ifdef USE_TOUCHSCREEN
      void startTouch()
        {
          bool ret = touch.startTouch();
                #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                  Serial.print("startTouch ret="); Serial.print(ret);
                #endif
          md_error = setBit(md_error, ERRBIT_TOUCH, ret);
                #if (DEBUG_MODE >= CFG_DEBUG_DETAIL)
                  Serial.print("  md_error="); Serial.println(md_error);
                #endif
        }
    #endif // USE_TOUCHSCREEN
  //
  // ------ passive buzzer --------------
    #ifdef PLAY_MUSIC
      void playSong(int8_t songIdx)
        {
          while (md_setSong(songIdx) == MDERR);
          md_playSong();
        }
    #endif
//
// --- system startup
void setup()
  {
    // start system
      Serial.begin(SER_BAUDRATE);

      // init project
          #if (DEBUG_MODE >= CFG_DEBUG_STARTUP)
            Serial.println(); Serial.println("setup start ...");
          #endif

    //
    // start touch
      #ifdef USE_TOUCHSCREEN
        startTouch();
        if ((md_error & ERRBIT_TOUCH) == 0 )
        {
          touch.wrTouch(PROJ_TITLE, 0, 1);
          while (touch.wrStatus("setup start ..."));
        }
      #endif // USE_TOUCHSCREEN

    //
    // start WIFI
      #ifdef USE_WIFI
        startWIFI();
              #ifdef USE_TOUCHSCREEN
                if ((md_error & ERRBIT_WIFI) == 0)
                {
                  while (touch.wrStatus("WIFI connected"));
                }
                else
                {
                  while (touch.wrStatus("WIFI error"));
                }
              #endif
      #endif // USE_WIFI

    //
    // start buzzer (task)
      #ifdef USE_BUZZER
        pinMode(PIN_BUZZ, OUTPUT);                                                                               // Setting pin 11 as output
        #ifdef PLAY_MUSIC
          md_initMusic();
          #ifdef PLAY_START_MUSIC
            playSong(SONG_HAENSCHEN_KLEIN);
          #endif
        #endif
      #endif

    //
    // finish setup
          #if (DEBUG_MODE >= CFG_DEBUG_STARTUP)
            Serial.println();
            Serial.print("... end setup -- error="); Serial.println(md_error);
            Serial.println();
          #endif

  }

// --- system run = endless loop
void loop()
  {
    //uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

    // run WIFI
      #ifdef USE_WIFI  // restart WIFI if offline
        if(wifiT.TOut())
        {
          //Serial.print("WiFi md_error = "); Serial.println(md_error);
          wifiT.startT();
          if((md_error & ERRBIT_WIFI) > 0)
          {
            Serial.println("WiFi startWIFI");
            startWIFI();
          }
        }
      #endif // USE_WIFI
    //
    // run NTP server (time)
      #ifdef USE_NTP_SERVER
        if (ntpT.TOut() == true)
        {
          if ((md_error & ERRBIT_WIFI) == 0)
          { // WiFi online
            if (((md_error & ERRBIT_NTPTIME) > 0) || (year() < 2000))   // time not initialized
            {
              initNTPTime();
              ntpGet = true;
            }
            if ((md_error & ERRBIT_NTPTIME) == 0) // time initialized
            {
              if (ntpGet == true)
              {
                ntpGet = wifiMD.md_getTime(&ntpTime);
                setTime(ntpTime);
              }
              else
              {
                setTime(++ntpTime);

              }

            }
            else // NTPTIME ok
            {
              setTime(++ntpTime);
            }
          }
          else // Wifi error
          {
            setTime(++ntpTime);
          }
          ntpT.startT();
                #if (DEBUG_MODE == CFG_DEBUG_DETAILS)
                  Serial.print("Datum "); Serial.print(day()); Serial.print("."); Serial.print(month()); Serial.print("."); Serial.print(year()); Serial.print(" ");
                  Serial.print("Zeit "); Serial.print(hour()); Serial.print("."); Serial.print(minute()); Serial.print(":"); Serial.println(second());
                #endif
          #ifdef USE_TOUCHSCREEN
            sprintf(outBuf,"  %02d.%02d %02d:%02d:%02d", day(), month(), hour(), minute(), second());
            touch.wrTouch(outBuf, 0, DATE_DISP_LINE);
          #endif
        }
      #endif // USE_NTP_SERVER
    //
    // run Webserver
      #ifdef USE_WEBSERVER
        if (servT.TOut()) // run webserver - restart on error
        {
          servT.startT();
          if ((md_error & ERRBIT_SERVER) != 0)
          {
            startWebServer();
          }
          else
          {
            bool ret = webMD.md_handleClient();
            md_error = setBit(md_error, ERRBIT_SERVER, ret);
          }
        }
      #endif
    //
    // run Touchpad
      #ifdef USE_TOUCHSCREEN
        touch.runTouch(outBuf);
        if (dispT.TOut())    // handle touch output
        {
          dispT.startT();
          touch.wrStatus();  // trigger status for deleting
        }
      #endif // USE_TOUCHSCREEN
    //

    usleep(TASK_SLICE_T);
  }
// --- end of implementation
//
// --- templates
// template websever
  #ifdef USE_WEBSERVER
    #ifdef DUMMY
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
      digitalWrite(led, 1);
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
      digitalWrite(led, 0);
    }

    void handleNotFound()
    {
      digitalWrite(led, 1);
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
      digitalWrite(led, 0);
    }
    #endif
  #endif // USE_WEBSERVER

//
// template touchscreen
  #ifdef USE_TOUCHSCREEN
    #ifdef DUMMY

    #include "FS.h"

    #include <SPI.h>
    #include <TFT_eSPI.h>      // Hardware-specific library

    TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

    // This is the file name used to store the calibration data
    // You can change this to create new calibration files.
    // The SPIFFS file name must start with "/".
    #define CALIBRATION_FILE "/TouchCalData1"

    // Set REPEAT_CAL to true instead of false to run calibration
    // again, otherwise it will only be done once.
    // Repeat calibration if you change the screen rotation.
    #define REPEAT_CAL false

    // Keypad start position, key sizes and spacing
    #define KEY_X 40 // Centre of key
    #define KEY_Y 96
    #define KEY_W 62 // Width and height
    #define KEY_H 30
    #define KEY_SPACING_X 18 // X and Y gap
    #define KEY_SPACING_Y 20
    #define KEY_TEXTSIZE 1   // Font size multiplier

    // Using two fonts since numbers are nice when bold
    #define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
    #define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2

    // Numeric display box size and location
    #define DISP_X 1
    #define DISP_Y 10
    #define DISP_W 238
    #define DISP_H 50
    #define DISP_TSIZE 3
    #define DISP_TCOLOR TFT_CYAN

    // Number length, buffer for storing it and character index
    #define NUM_LEN 12
    char numberBuffer[NUM_LEN + 1] = "";
    uint8_t numberIndex = 0;

    // We have a status line for messages
    #define STATUS_X 120 // Centred on this
    #define STATUS_Y 65

    // Create 15 keys for the keypad
    char keyLabel[15][5] = {"New", "Del", "Send", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "#" };
    uint16_t keyColor[15] = {TFT_RED, TFT_DARKGREY, TFT_DARKGREEN,
                             TFT_BLUE, TFT_BLUE, TFT_BLUE,
                             TFT_BLUE, TFT_BLUE, TFT_BLUE,
                             TFT_BLUE, TFT_BLUE, TFT_BLUE,
                             TFT_BLUE, TFT_BLUE, TFT_BLUE
                            };

    // Invoke the TFT_eSPI button class and create all the button objects
    TFT_eSPI_Button key[15];

    //------------------------------------------------------------------------------------------

    void setup() {
      // Use serial port
      Serial.begin(9600);

      // Initialise the TFT screen
      tft.init();

      // Set the rotation before we calibrate
      tft.setRotation(0);

      // Calibrate the touch screen and retrieve the scaling factors
      touch_calibrate();

      // Clear the screen
      tft.fillScreen(TFT_BLACK);

      // Draw keypad background
      tft.fillRect(0, 0, 240, 320, TFT_DARKGREY);

      // Draw number display area and frame
      tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
      tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

      // Draw keypad
      drawKeypad();
    }

    //------------------------------------------------------------------------------------------

    void loop(void) {
      uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

      // Pressed will be set true is there is a valid touch on the screen
      boolean pressed = tft.getTouch(&t_x, &t_y);

      // / Check if any key coordinate boxes contain the touch coordinates
      for (uint8_t b = 0; b < 15; b++) {
        if (pressed && key[b].contains(t_x, t_y)) {
          key[b].press(true);  // tell the button it is pressed
        } else {
          key[b].press(false);  // tell the button it is NOT pressed
        }
      }

      // Check if any key has changed state
      for (uint8_t b = 0; b < 15; b++) {

        if (b < 3) tft.setFreeFont(LABEL1_FONT);
        else tft.setFreeFont(LABEL2_FONT);

        if (key[b].justReleased()) key[b].drawButton();     // draw normal

        if (key[b].justPressed()) {
          key[b].drawButton(true);  // draw invert

          // if a numberpad button, append the relevant # to the numberBuffer
          if (b >= 3) {
            if (numberIndex < NUM_LEN) {
              numberBuffer[numberIndex] = keyLabel[b][0];
              numberIndex++;
              numberBuffer[numberIndex] = 0; // zero terminate
            }
            status(""); // Clear the old status
          }

          // Del button, so delete last char
          if (b == 1) {
            numberBuffer[numberIndex] = 0;
            if (numberIndex > 0) {
              numberIndex--;
              numberBuffer[numberIndex] = 0;//' ';
            }
            status(""); // Clear the old status
          }

          if (b == 2) {
            status("Sent value to serial port");
            Serial.println(numberBuffer);
          }
          // we dont really check that the text field makes sense
          // just try to call
          if (b == 0) {
            status("Value cleared");
            numberIndex = 0; // Reset index to 0
            numberBuffer[numberIndex] = 0; // Place null in buffer
          }

          // Update the number display field
          tft.setTextDatum(TL_DATUM);        // Use top left corner as text coord datum
          tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
          tft.setTextColor(DISP_TCOLOR);     // Set the font colour

          // Draw the string, the value returned is the width in pixels
          int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

          // Now cover up the rest of the line up by drawing a black rectangle.  No flicker this way
          // but it will not work with italic or oblique fonts due to character overlap.
          tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

          delay(10); // UI debouncing
        }
      }
    }


    #endif
    //------------------------------------------------------------------------------------------



  #endif // USE_TOUCHSCREEN

