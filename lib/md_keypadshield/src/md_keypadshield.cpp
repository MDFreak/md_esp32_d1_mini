//#ifdef DUMMY
/*
  LCDKeypad.cpp
*/
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "config.h"

#ifdef USE_KEYPADSHIELD
  // include this library's description file
  #include "md_keypadshield.h"

    static uint8_t  _KEYS_CNT = KP_NUM_KEYS;
    static uint16_t _ADC_KEY_VAL[KP_NUM_KEYS + 1] =
      {
        0,
        (KP_KEY_VAL_1 * ADC_RES) / ADC_STD_RES,
        (KP_KEY_VAL_2 * ADC_RES) / ADC_STD_RES,
        (KP_KEY_VAL_3 * ADC_RES) / ADC_STD_RES,
        (KP_KEY_VAL_4 * ADC_RES) / ADC_STD_RES,
        (KP_KEY_VAL_5 * ADC_RES) / ADC_STD_RES
      };

  // --- class keypad
  md_kpad::md_kpad(uint8_t adc)
  {
    _adc = adc;
  }

  bool md_kpad::init(uint8_t keysAdc)
    {
      _adc = keysAdc;
      pinMode(_adc,ANALOG);
      return ISOK;
    }

  uint8_t md_kpad::getKey()
    {
      uint8_t  k;
      uint16_t val = analogRead(_adc);

      //SOUT(millis()); SOUT(" getKey val "); SOUTLN(val);

      for (k = 1; k <= _KEYS_CNT; k++)
        {
          if (val < _ADC_KEY_VAL[k])
            return k;
        }
      if (k > _KEYS_CNT)
        k = 0;     // No valid key pressed
      return k;
    }
#endif // USE_KEYPADSHIELD