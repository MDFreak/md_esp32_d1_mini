

// include this library's description file

#include "config.h"

#ifdef USE_TFT
  #include "md_lcd.h"

  md_lcd::md_lcd(void* plcd)
  {
    _plcd = plcd;
  }

  void md_lcd::start(void* plcd)
    {
      _plcd = plcd;
      ((LiquidCrystal*) _plcd)->begin(LCD_CULS, LCD_ROWS);
      ((LiquidCrystal*) _plcd)->print("hello world");
    }

  bool md_lcd::wrText(char* msg)
  {
    return wrText(msg, 0, 0);
  }

  bool md_lcd::wrText(char* msg, uint8_t row, uint8_t col)
  {
    ((LiquidCrystal*) _plcd)->setCursor(col, row);
    ((LiquidCrystal*) _plcd)->write(msg);
    return ISOK;
  }


  bool md_lcd::wrStatus(char* msg)
  {
    ((LiquidCrystal*) _plcd)->setCursor(0, 1);
    ((LiquidCrystal*) _plcd)->write(msg);
    return ISOK;
  }

#endif // USE_TFT