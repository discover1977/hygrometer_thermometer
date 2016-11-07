/* 
 * File:   HTU21DF.h
 * Author: Jason McGuire (j.mcguire.2015@ieee.org)
 * Description: A library for a HTU21D-F Humidity/Temperature Sensor
 * for the PIC18F using I2C.
 * See example.c for implementation of the library
 * Sample Product: https://www.adafruit.com/products/1899
 * Created on March 27, 2016, 9:08 AM
 
License Information:
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
 
 */

#ifndef HTU21DF_H
#define HTU21DF_H

#include "i2c-soft.h"

#define HTU_WR_ADDR 0x80 // write address for temp/humidity sensor 
#define HTU_RD_ADDR 0x81 // read address for temp/humidity sensor
#define HTU_TEMP_CMD 0xE3 // command to trigger temperature reading 
#define HTU_HUMI_CMD 0xE5 // command to trigger humidity reading

// Available Functions:
float HTUreadTemp(); // Get a temperature reading
float HTUreadHumidity(); // Get a humidity reading
void HTUReset(); // Soft reset of sensor 

#endif // HTU21DF_H
