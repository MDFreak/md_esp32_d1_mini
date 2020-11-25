/*
  LCDKeypad.h
*/

// ensure this library description is only included once
#ifndef _MD_LCD_H_
  #define _MD_LCD_H_

  #include "config.h"
  #ifdef USE_TFT
    #include "LiquidCrystal.h"

    class md_lcd
      {
        protected:
          void* _plcd;

        public:
          md_lcd(void* plcd);
          void start(void* plcd);
          bool wrText(char* msg);
          bool wrText(char* msg, uint8_t row, uint8_t col);
          bool wrStatus(char* msg);
      };

  #endif


#endif // _MD_LCD_H

