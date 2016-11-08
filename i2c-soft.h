/*
 * i2c-soft.h
 *
 *  Created on: 19.12.2009
 *      Author: Pavel V. Gololobov
 */

#ifndef I2C_H_
#define I2C_H_

#define NO_I2C_ACK 0
#define OK_I2C_ACK 1

#ifndef SDA
#define I2COUT      PORTC	// Write to Port
#define I2CIN       PINC	// Read from Port
#define I2CDIR      DDRC	// Set Port Direction
#define I2CSEL      PORTC	// Alternative Port Functions

#define SCL       	0b00000001		// Serial Clock Line
#define SDA       	0b00000010		// Serial Data Line

#endif

// Init Bus
void i2c_Soft_Init();
// Start Transfer
void i2c_Soft_Start();
// Stop Transfer
void i2c_Soft_Stop();
// Write Transfer
unsigned int i2c_Soft_Write(unsigned int a);
// Read Transfer
unsigned int i2c_Soft_Read(unsigned int ack);
// Read Byte
unsigned int i2c_Soft_ReadByte(unsigned int nAddress, unsigned int nRegister);
// Write Byte
void i2c_Soft_WriteByte(unsigned int nAddress, unsigned int nRegister, unsigned int nValue);

#endif
