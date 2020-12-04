#include <md_util.h>
#include <wire.h>


// TwoWire I2Cone = TwoWire(0);
// TwoWire I2Ctwo = TwoWire(1);
//#define _MT_UTIL_DEBUG

//--------------------------
// Setzen / Loeschen eines Bit in einer 16-Bit Flags-Wort
uint16_t clrBit(const uint16_t inWert, const uint16_t inBit)
  {
    uint16_t ret = inWert & (0xffff ^ inBit);
    #if defined( _MT_UTIL_DEBUG )
      SOUT(millis()); SOUT(" setBit: inWert= "); SOUTHEX(inWert);
      SOUT("  inBit="); SOUT(inBit); SOUT(" ret= "); SOUTHEXLN(ret)
    #endif
    return ret;
  }

uint16_t setBit(const uint16_t inWert, const uint16_t inBit, const bool inVal)
  {

    if (inVal == 0)
      {
        return clrBit(inWert, inBit);
      }

    uint16_t ret = inWert | inBit;
    #if defined( _MT_UTIL_DEBUG )
      SOUT(millis()); SOUT(" setBit: inWert= "); SOUTHEX(inWert);
      SOUT("  inBit="); SOUT(inBit); SOUT(" ret= "); SOUTHEXLN(ret);
    #endif
    return ret;
  }

//--------------------------
// scan I2C - serial output
uint8_t scanI2C(uint8_t no, uint8_t start, uint8_t sda, uint8_t scl)
  {
    uint8_t i = 0;
    TwoWire I2C = TwoWire(no-1);
    I2C.begin(sda,scl,400000);
    SOUTLN();
    SOUT("Scanning I2C Addresses Channel "); SOUTLN(no);
    //uint8_t cnt=0;
    for(i = start; i < 128 ; i++)
      {
        I2C.beginTransmission(i);
        uint8_t ec=I2C.endTransmission(true);
        if(ec==0)
          {
            SOUT(" device at address 0x");
            if (i<16) Serial.print('0');
            SOUTHEXLN(i);
          }
      }
    I2C.~TwoWire();
    Serial.println();
    return i;
  }

// class msTimer
msTimer::msTimer()
  {
    startT(0);
  }

msTimer::msTimer(const unsigned long inTOut)
  {
    startT(inTOut);
  }


bool msTimer::TOut()
  {
    if ((millis() - _tstart) > _tout)
      return true;
    else
      return false;
  }

void msTimer::startT()
  {
    _tstart = millis();
  }

void msTimer::startT(const unsigned long inTOut)
  {
    _tstart = millis();
    _tout   = inTOut;
  }
