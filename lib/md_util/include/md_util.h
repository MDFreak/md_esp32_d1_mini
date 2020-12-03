#ifndef _MD_UTIL_H_
  #define _MD_UTIL_H_

  #include <Arduino.h>
  #include <md_defines.h>

  uint16_t setBit(uint16_t inWert, uint16_t inBit, bool inVal = true);
  uint16_t clrBit(uint16_t inWert, uint16_t inBit);
  bool     getBit(uint16_t inWert, uint16_t inBit);
  uint8_t  scanI2C(uint8_t no, uint8_t start, uint8_t sda, uint8_t scl);

  class msTimer
  {
    private:
      unsigned long _tout;
      unsigned long _tstart;

    public:
      msTimer();
      msTimer(const unsigned long inTOut);

      bool TOut();
      void startT();
      void startT(const unsigned long inTOut);
  };

#endif