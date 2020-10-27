

// include this library's description file

#include "config.h"

#ifdef USE_TFT
  #include "md_lcd.h"

  void* _plcd;

  void start(void* plcd)
    {
      _plcd = plcd;
      ((LiquidCrystal*) _plcd)->begin(LCD_CULS, LCD_ROWS);
      ((LiquidCrystal*) _plcd)->print("hello world");
    }


#endif // USE_TFT