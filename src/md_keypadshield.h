/*
  LCDKeypad.h
*/

// ensure this library description is only included once
#ifndef _MD_LCDKEYPAD_H_
  #define _MD_LCDKEYPAD_H_

  #ifdef USE_KEYPADSHIELD
    #include "config.h"

    // library interface description
    #define KPAD_NONE  -1
    #define KPAD_RIGHT  0
    #define KPAD_UP     1
    #define KPAD_DOWN   2
    #define KPAD_LEFT   3
    #define KPAD_SELECT 4

    class md_kpad
    {
      protected:
        uint8_t _adc;

      public:
        md_kpad(uint8_t adc);
        bool    init(uint8_t keysAdc);
        uint8_t getKey();
    };
    extern md_kpad kpad;

  #endif // USE_KEYPADSHIELD
#endif // _MD_LCDKEYPAD_H_


