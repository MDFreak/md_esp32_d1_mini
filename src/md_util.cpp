#include "md_util.h"

//--------------------------
// Setzen / Loeschen eines Bit in einer 16-Bit Flags-Wort
uint16_t setBit(const uint16_t inWert, const uint16_t inBit, const bool inVal)
{
  int ret;
  if (inVal)    // Error gefunden
  { // Fehler setzen
    ret = inWert | inBit;
  }
  else
  { // Fehler loeschen
    ret = inWert & (0xffff ^ inBit);
  }
/*
  #ifdef SERIAL_DEBUG
    Serial.print("  inWert="); Serial.print(inWert);
    Serial.print("  inBit="); Serial.print(inBit);
    Serial.print("  !inBit="); Serial.print(0xffff ^ inBit);
    Serial.print("  inVal="); Serial.print(inVal);
    Serial.print("  ret="); Serial.print(ret);
  #endif
*/
  return ret;
}

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
