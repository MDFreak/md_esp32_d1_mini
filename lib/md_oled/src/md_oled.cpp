#include "md_oled.h"

  //
  bool md_oled::begin(uint8_t cols, uint8_t rows)
    {
        _rows = rows;
        _cols = cols;
        if (rows > _MD_OLED_MAX_ROWS)
          {
            _cols = _MD_OLED_MAX_ROWS;
          }
        _statRow = rows;
        if (this->init())
          {
            this->flipScreenVertically();
            for (uint8_t k = 0 ; k < _cols ; k++ )
              {
                _statStr += " ";
              }
            for (uint8_t i = 0 ; i < _rows ; i++)
              {
                _outStr[i] = _statStr;
              }
            SOUTLN("oled init ok");
            return ISOK;
          }
        SOUTLN("oled init err");
      return ISERR;
      //oled1.setFont(ArialMT_Plain_10);
    }

  //
  void md_oled::clear()
    {
      this->connect();
      this->clear();
    }


  //
  bool md_oled::wrText     (String msg, uint8_t col, uint8_t row, uint8_t len) // write to text area
    {
      if ((row > _rows) || (col > _cols))  return ISERR;

      _len = len;
      if ((col + len) > _cols) { _len = _cols - col; }
          //SOUT((uint32_t) millis); SOUT(" wrText1 '"); SOUT(msg); SOUT("' _rows="); SOUT(_rows);
          //SOUT(" col="); SOUT(col); SOUT(" row="); SOUT(row); SOUT(" _len="); SOUTLN(_len);
      this->connect();
      this->setTextAlignment(TEXT_ALIGN_LEFT);
      // clear statusline
      this->setColor(BLACK);
          //SOUT(" OutTxt ")
          //SOUT((uint32_t) millis); SOUT(" wrText2 clr '"); SOUT(_outStr[row]); SOUT("' _rows="); SOUT(_rows);
          //SOUT(" col="); SOUT(col); SOUT(" row="); SOUT(row); SOUT(" _len="); SOUTLN(_len);
      this->drawString(0, row*_hfont, _outStr[row]);
      this->display();
      this->setColor(WHITE);
      // clear out string
      for (uint8_t i = col ; i < (col + _len) ; i++) { _outStr[row][i] = ' '; }
      // enter new message
      if (msg.length() < _len) { _len = msg.length(); }
          //SOUT(" wrText3 vor set '"); SOUT(_outStr[row]); SOUT("' _rows="); SOUT(_rows);
          //SOUT(" col="); SOUT(col); SOUT(" row="); SOUT(row); SOUT(" _len="); SOUTLN(_len);
      for (uint8_t i = 0 ; i < _len ; i++) { _outStr[row][col + i] = msg[i]; }
          //SOUT(" wrText3 nach set '");  SOUT(msg); SOUT("' -> '"); SOUT(_outStr[row]); SOUT("'");
          //SOUT(" col="); SOUT(col); SOUT(" row="); SOUT(row); SOUT(" _len="); SOUTLN(_len);
      this->drawString(0, row*_hfont, _outStr[row]);
      this->display(); // write the buffer to the display
      return 0;
    }

      // Adapted from Adafruit_SSD1306
  //
  void md_oled::drawCircle(void)
     {
      /*
        for (int16_t i=0; i<((SSD1306Wire*) _oled)->getHeight(); i+=2)
          {
            ((SSD1306Wire*) _oled)->drawCircle(
                    ((SSD1306Wire*) _oled)->getWidth()/2,
                    ((SSD1306Wire*) _oled)->getHeight()/2,
                    i);
            ((SSD1306Wire*) _oled)->display();
            sleep(1);
          }
        //sleep(5);
        //((SSD1306Wire*) _oled)->clear();

        // This will draw the part of the circel in quadrant 1
        // Quadrants are numberd like this:
        //   0010 | 0001
        //  ------|-----
        //   0100 | 1000
        //
        ((SSD1306Wire*) _oled)->drawCircleQuads(
                ((SSD1306Wire*) _oled)->getWidth()/2,
                ((SSD1306Wire*) _oled)->getHeight()/2,
                ((SSD1306Wire*) _oled)->getHeight()/4,
                0b00000001);
        ((SSD1306Wire*) _oled)->display();
        sleep(1);
        ((SSD1306Wire*) _oled)->setColor(BLACK);
        ((SSD1306Wire*) _oled)->drawCircleQuads(
                ((SSD1306Wire*) _oled)->getWidth()/2,
                ((SSD1306Wire*) _oled)->getHeight()/2,
                ((SSD1306Wire*) _oled)->getHeight()/4,
                0b00000011);
        ((SSD1306Wire*) _oled)->display();
        sleep(1);
        ((SSD1306Wire*) _oled)->setColor(WHITE);
        ((SSD1306Wire*) _oled)->drawCircleQuads(
                ((SSD1306Wire*) _oled)->getWidth()/2,
                ((SSD1306Wire*) _oled)->getHeight()/2,
                ((SSD1306Wire*) _oled)->getHeight()/4,
                0b00000111);
        ((SSD1306Wire*) _oled)->display();
        sleep(1);
        ((SSD1306Wire*) _oled)->setColor(BLACK);
        ((SSD1306Wire*) _oled)->drawCircleQuads(
                ((SSD1306Wire*) _oled)->getWidth()/2,
                ((SSD1306Wire*) _oled)->getHeight()/2,
                ((SSD1306Wire*) _oled)->getHeight()/4,
                0b00001111);
        ((SSD1306Wire*) _oled)->display();
        sleep(1);
        ((SSD1306Wire*) _oled)->setColor(WHITE);
      */
    }


  //
  void md_oled::wrStatus   (String msg) // write status line
    {
      this->connect();
      this->setTextAlignment(TEXT_ALIGN_LEFT);
      // clear statusline
      this->setColor(BLACK);
      this->drawString(0, (_rows -1)*_hfont, _statStr);
      this->display();
      this->setColor(WHITE);
      for (uint8_t i = 0 ; i < _cols ; i++) { _statStr[i] = ' '; }
      // enter new message
      _len = msg.length();
      if (_len > _cols) { _len = _cols; }
      for (uint8_t i = 0 ; i < _len ; i++) { _statStr[i] = msg[i]; }
      this->drawString(0, (_rows -1)*_hfont, _statStr);
                  SOUT((uint32_t) millis()); SOUT(" oled _statTxt'"); SOUT(_statStr);
                  SOUTLN("' Statuszeile schreiben ");
      this->display();
    }
  //
  void md_oled::wrStatus   (const char *msg)
    {
      wrStatus((String) msg);
    }
  #ifdef NC_RUN_OLED_TEST
      void md_oled::r_frame_box()
        {
          u8g2.drawStr(0, 0, "drawRFrame");
          u8g2.drawRFrame(5, 10, 40, 15, 3);
          u8g2.drawStr(70, 0, "drawRBox");
          u8g2.drawRBox(70, 10, 25, 15, 3);
        }

      void md_oled::disc_circle()
        {
          u8g2.drawStr(0, 0, "drawDisc");
          u8g2.drawDisc(10, 18, 9);
          u8g2.drawDisc(30, 16, 7);
          u8g2.drawStr(60, 0, "drawCircle");
          u8g2.drawCircle(70, 18, 9);
          u8g2.drawCircle(90, 16, 7);
        }

      void md_oled::string_orientation()
        {
          u8g2.setFontDirection(0);
          u8g2.drawStr(0, 0, "  12345");
          //u8g2.setFontDirection(3);
          u8g2.drawStr(25, 8,   "1234567890");
          //u8g2.setFontDirection(2);
          u8g2.drawStr(45, 16, "567890");
        }

      void md_oled::line()
        {
          u8g2.drawStr( 0, 0, "drawLine");
          u8g2.drawLine(7, 10, 40, 32);
          u8g2.drawLine(14, 10, 60, 32);
          u8g2.drawLine(28, 10, 80, 32);
          u8g2.drawLine(35, 10, 100, 32);
        }

      void md_oled::triangle()
        {
          u8g2.drawStr( 0, 0, "drawTriangle");
          u8g2.drawTriangle(14, 7, 45, 30, 10, 32);
        }

      void md_oled::bitmap()
        {
          u8g2.drawXBMP(0, 22, image_width, image_height, image_bits);
        }

      void md_oled::box_frame()
        {
          u8g2.drawStr(0, 0, "drawBox");
          u8g2.drawBox(5, 10, 40, 20);
          u8g2.drawStr(60, 0, "drawFrame");
          u8g2.drawFrame(65, 10, 20, 20);
        }

    #endif
//
/*
  void md_oled::drawStr    (u8g2_uint_t x, u8g2_uint_t y, const char *s)
    {
      u8g2.drawStr(x, y, s);
    }

  void md_oled::sendBuffer()
    {
      u8g2.sendBuffer();
    }

  void md_oled::prepare()
    {
      //u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.setFont(u8g2_font_5x8_tf);
      u8g2.setFontRefHeightExtendedText();
      u8g2.setDrawColor(5);
      u8g2.setFontPosTop();
      u8g2.setFontDirection(0);
    }

  void md_oled::drawFrame  (u8g2_uint_t x, u8g2_uint_t y,u8g2_uint_t w, u8g2_uint_t h)
    {
      u8g2.drawFrame(x, y, w, h);
    }

  void md_oled::drawRFrame (u8g2_uint_t x, u8g2_uint_t y,u8g2_uint_t w, u8g2_uint_t h, u8g2_uint_t r)
    {
      u8g2.drawRFrame(x, y, w, h, r);
    }

  void md_oled::drawBox    (u8g2_uint_t x, u8g2_uint_t y,u8g2_uint_t w,u8g2_uint_t h)
    {
      u8g2.drawBox(x, y, w, h);
    }

  void md_oled::drawRBox   (u8g2_uint_t x, u8g2_uint_t w,u8g2_uint_t h, u8g2_uint_t y, u8g2_uint_t r)
    {
      u8g2.drawRBox(x, y, w, h, r);
    }

  void md_oled::drawDisc   (u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad)
    {
      u8g2.drawDisc(x0, y0, rad);
    }

  void md_oled::drawArcDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, u8g2_uint_t part)
    {
      u8g2.drawDisc(x0, y0, rad, part);
    }

  void md_oled::drawCircle (u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad)
    {
      u8g2.drawCircle(x0, y0, rad);
    }

  void md_oled::drawArcCirc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, u8g2_uint_t part)
    {
      u8g2.drawCircle(x0, y0, rad, part);
    }

  void md_oled::drawLine   (u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2)
    {
      u8g2.drawLine(x1, y1, x2, 2);
    }

  void md_oled::drawTriang (u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2, u8g2_uint_t x3, u8g2_uint_t y3)
    {
      u8g2.drawTriangle(x1, y1, x2, y2, x3, y3);
    }

  void md_oled::drawBitmap (u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t im_w, u8g2_uint_t im_h, const uint8_t *bitmap)
    {
      u8g2.drawXBMP(x, y, im_w, im_h, bitmap);
    }
  */

/*
    void u8g2_unicode()
    {
      u8g2.drawStr(0, 0, "Unicode");
      u8g2.setFont(u8g2_font_unifont_t_symbols);
      u8g2.setFontPosTop();
      u8g2.setFontDirection(0);
      u8g2.drawUTF8(10, 15, " " ☀ );
      u8g2.drawUTF8(30, 15, " " ☁ );
      u8g2.drawUTF8(50, 15, " " ☂ );
      u8g2.drawUTF8(70, 15, " " ☔ );
      u8g2.drawUTF8(95, 15, COPYRIGHT_SYMBOL); //COPYRIGHT SIMBOL
      u8g2.drawUTF8(115, 15, "\xb0"); // DEGREE SYMBOL
    }

    #define image_width 128
    #define image_height 21
    static const unsigned char image_bits[] U8X8_PROGMEM =
      {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00,
        0xfc, 0x1f, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xfe, 0x1f, 0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00,
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x18, 0x00, 0x00,
        0x0c, 0xc0, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x18, 0x00, 0x00, 0x0c, 0xc0, 0xf0, 0x1f, 0x06, 0x63, 0x80, 0xf1,
        0x1f, 0xfc, 0x33, 0xc0, 0x03, 0x18, 0x00, 0x00, 0x0c, 0xc0, 0xf8, 0x3f,
        0x06, 0x63, 0xc0, 0xf9, 0x3f, 0xfe, 0x33, 0xc0, 0x03, 0x18, 0x00, 0x00,
        0x0c, 0xc0, 0x18, 0x30, 0x06, 0x63, 0xc0, 0x18, 0x30, 0x06, 0x30, 0xc0,
        0xff, 0xff, 0xdf, 0xff, 0x0c, 0xc0, 0x18, 0x30, 0x06, 0x63, 0xe0, 0x18,
        0x30, 0x06, 0x30, 0xc0, 0xff, 0xff, 0xdf, 0xff, 0x0c, 0xc0, 0x98, 0x3f,
        0x06, 0x63, 0x60, 0x98, 0x3f, 0x06, 0x30, 0xc0, 0x03, 0x18, 0x0c, 0x00,
        0x0c, 0xc0, 0x98, 0x1f, 0x06, 0x63, 0x70, 0x98, 0x1f, 0x06, 0x30, 0xc0,
        0x03, 0x18, 0x06, 0x00, 0x0c, 0xc0, 0x18, 0x00, 0x06, 0x63, 0x38, 0x18,
        0x00, 0x06, 0x30, 0xc0, 0x03, 0x18, 0x03, 0x00, 0x0c, 0xe0, 0x18, 0x00,
        0x06, 0x63, 0x1c, 0x18, 0x00, 0x06, 0x30, 0xc0, 0x00, 0x80, 0x01, 0x00,
        0xfc, 0x7f, 0xf8, 0x07, 0x1e, 0xe3, 0x0f, 0xf8, 0x07, 0x06, 0xf0, 0xcf,
        0x00, 0xc0, 0x00, 0x00, 0xfc, 0x3f, 0xf0, 0x07, 0x1c, 0xe3, 0x07, 0xf0,
        0x07, 0x06, 0xe0, 0xcf, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
        0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xe0, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0xfc, 0x1f, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f
      };
  */

  #ifdef DUMMY
        void setup(void)
          {
          u8g2.begin();
          u8g2_prepare();
          }

    float i = 0.0;
    void loop(void)
      {
            u8g2.clearBuffer();
            u8g2_prepare();
            u8g2_box_frame();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_disc_circle();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_r_frame_box();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_prepare();
            u8g2_string_orientation();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_line();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_triangle();
            u8g2.sendBuffer();
            delay(1500);

            //one tab
            u8g2.clearBuffer();
            u8g2_prepare();
            u8g2_unicode();
            u8g2.sendBuffer();
            delay(1500);
            u8g2.clearBuffer();
            u8g2_bitmap();
            u8g2.sendBuffer();
            u8g2.clearBuffer();
            u8g2.setCursor(0, 0);
            u8g2.print(i);
            i = i + 1.5;
            u8g2.sendBuffer();
      }
  #endif
