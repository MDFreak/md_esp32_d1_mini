/*
  LCDKeypad.h
*/

// ensure this library description is only included once
#ifndef _MD_LCD_H_
  #define _MD_LCD_H_

  #include "config.h"
  #ifdef USE_TFT
    #include "LiquidCrystal.h"



    void lcd_start(void* plcd);
  #endif

#endif // _MD_LCD_H

