#include "md_util.h"

int setBit(const int inWert, const int inBit, const bool inVal)
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
  #ifdef SERIAL_DEBUG
    Serial.print("  inWert="); Serial.print(inWert);
    Serial.print("  inBit="); Serial.print(inBit);
    Serial.print("  !inBit="); Serial.print(0xffff ^ inBit);
    Serial.print("  inVal="); Serial.print(inVal);
    Serial.print("  ret="); Serial.print(ret);
  #endif
  return ret;
}