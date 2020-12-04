/*!
 * @file     Adafruit_FRAM_I2C.cpp
 *
 * @mainpage Adafruit FRAM I2C
 *
 * @author   KTOWN (Adafruit Industries)
 *
 * @section intro_sec Introduction
 *
 * Driver for the Adafruit I2C FRAM breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section  HISTORY
 *
 * v1.0 - First release
 *
 * @section license License
 *
 * BSD license, all text above must be included in any redistribution (see
 license.txt)
 */
#include <math.h>
#include <stdlib.h>

#include <md_FRAM.h>
#include <md_defines.h>

// classes
md_FRAM::md_FRAM(void) { _framInitialised = false; }
//
bool md_FRAM::begin(uint8_t addr)
  {
    begin(NN, NN, addr);
    return ISOK;
  }

bool md_FRAM::begin(int sda, int scl, uint8_t addr)
  {
    _i2c_addr = addr;
    _sda      = sda;
    _scl      = scl;

    Wire.begin(_sda, _scl);

    /* Make sure we're actually connected */
    uint16_t manufID, prodID;
    getDeviceID(&manufID, &prodID);
    if (manufID != 0x00A)
      {
        Serial.print("Unexpected Manufacturer ID: 0x");
        Serial.println(manufID, HEX);
        return false;
      }
    if (prodID != 0x510)
      {
        Serial.print("Unexpected Product ID: 0x");
        Serial.println(prodID, HEX);
        return false;
      }

    /* Everything seems to be properly initialised and connected */
    _framInitialised = true;

    return true;
  }
//
void md_FRAM::write8(uint16_t framAddr, uint8_t value)
  {
    Wire.beginTransmission(_i2c_addr);
    Wire.write(framAddr >> 8);
    Wire.write(framAddr & 0xFF);
    Wire.write(value);
    Wire.endTransmission();
  }
//
uint8_t md_FRAM::read8(uint16_t framAddr)
  {
    Wire.beginTransmission(_i2c_addr);
    Wire.write(framAddr >> 8);
    Wire.write(framAddr & 0xFF);
    Wire.endTransmission();

    Wire.requestFrom(_i2c_addr, (uint8_t)1);

    return Wire.read();
  }
//
void md_FRAM::getDeviceID(uint16_t *manufacturerID, uint16_t *productID)
  {
    uint8_t a[3] = {0, 0, 0};
    uint8_t results;

    Wire.beginTransmission(MB85RC_SLAVE_ID >> 1);
    Wire.write(_i2c_addr << 1);
    results = Wire.endTransmission(false);

    Wire.requestFrom(MB85RC_SLAVE_ID >> 1, 3);
    a[0] = Wire.read();
    a[1] = Wire.read();
    a[2] = Wire.read();

    // Shift values to separate manuf and prod IDs
    // http://www.fujitsu.com/downloads/MICRO/fsa/pdf/products/memory/fram/MB85RC256V-DS501-00017-3v0-E.pdf
    *manufacturerID = (a[0] << 4) + (a[1] >> 4);
    *productID = ((a[1] & 0x0F) << 8) + a[2];
  }

//
void md_FRAM::writeBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
  {
    // TODO constrain size < 30 ??
    Wire.beginTransmission(_i2c_addr);
    Wire.write(memaddr >> 8);
    Wire.write(memaddr & 0xFF);
    uint8_t * p = obj;
    for (uint8_t i = 0; i < size; i++)
    {
      Wire.write(*p++);
    }
    Wire.endTransmission();
  }
//
void md_FRAM::readBlock(uint16_t memaddr, uint8_t * obj, uint8_t size)
  {
    Wire.beginTransmission(_i2c_addr);
    Wire.write(memaddr >> 8);
    Wire.write(memaddr & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom(_i2c_addr, size);
    uint8_t * p = obj;
    for (uint8_t i = 0; i < size; i++)
    {
      *p++ = Wire.read();
    }
  }
//
bool md_FRAM::selftest(uint16_t pfirst, uint8_t len)
  {
    char _write[len+1] = "Leute";
    char _read[len+1];
    memset(_read, 0, len+1);

    writeBlock(pfirst + 4, (uint8_t*) _write, strlen(_write));
    usleep(20000);
    readBlock(pfirst, (uint8_t*) _read, strlen(_write) + 4 );
    usleep(20000);
    SOUT(millis()); SOUT(" FRAM selftest addr "); SOUTHEXLN(pfirst);
    SOUT(" text write'"); SOUT(_write); SOUT("' read '"); SOUT(_read); SOUTLN("'");

    if (strcpy(_write, _read) == 0) return ISOK;
    else                            return ISERR;
  }




