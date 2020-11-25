#ifndef _MD_UTIL_H_
  #define _MD_UTIL_H_

  #include <Arduino.h>

  uint16_t setBit(uint16_t inWert, uint16_t inBit, bool inVal);
  uint8_t  scanIIC(uint8_t no, uint8_t start, uint8_t sda, uint8_t scl);

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