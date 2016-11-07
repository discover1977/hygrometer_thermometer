/* 
 * File:   HTU21DF.c
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
 
#include "HTU21DF.h"

void HTUReset() {

}

float HTUreadTemp() {
    i2c_Soft_Start(); // start
    i2c_Soft_Write(HTU_WR_ADDR); // I2C address + write
    // while(ACKSTAT); // wait for ack
    i2c_Soft_Write(HTU_TEMP_CMD); // send commnand
    //while(ACKSTAT); // wait for ack
    i2c_Soft_Start(); // start again
    i2c_Soft_Write(HTU_RD_ADDR); // I2C address + read
    // while(ACKSTAT); // wait for ack
    unsigned char msb = i2c_Soft_Read(1); // read 8 bits
    //I2Cack(); // send ack
    unsigned char lsb = i2c_Soft_Read(1); // read 8 bits
    //I2Cack(); // send ack
    unsigned char crc = i2c_Soft_Read(1);// read crc
    //I2Cnack(); // send nack
    i2c_Soft_Stop(); // send stop bit
    
    // handle data
    unsigned int temp = msb;
    temp = temp << 8; 
    temp = temp | (lsb & 0xFC);
    float tempC = -46.85 + 175.72*((float)temp/65536.0); // Use formula from datasheet
    float tempF = tempC*9.0/5.0 + 32.0; //  Convert to Fahrenheit
    return tempF;
}

float HTUreadHumidity() {
    i2c_Soft_Start(); // start
    i2c_Soft_Write(HTU_WR_ADDR); // I2C address + write
    //while(ACKSTAT); // wait for ack
    i2c_Soft_Write(HTU_HUMI_CMD); // send commnand
    //while(ACKSTAT); // wait for ack
    i2c_Soft_Start();
    i2c_Soft_Write(HTU_RD_ADDR); // I2C address + read
    //while(ACKSTAT); // wait for ack
    unsigned char msb = i2c_Soft_Read(1); // read 8 bits
    //I2Cack(); // send ack
    unsigned char lsb = i2c_Soft_Read(1); // read 8 bits
    //I2Cack(); // send ack
    unsigned char crc = i2c_Soft_Read(1);// read crc
    //I2Cnack(); // send nack
    i2c_Soft_Stop(); // send stop bit
    
    // process data 
    unsigned int rh = msb;
    rh = rh << 8;
    rh = rh | (lsb & 0xFC); 
    float rhfloat = -6 + 125*(float)rh/65536;
    return rhfloat;
}
