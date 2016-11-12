#include "HTSensor.h"
#include <util/delay.h>

enum HTDataName
{
	MSBData,
	LSBData,
	CRCData
};

static unsigned char UserRegData;

static unsigned char CalcSht21Crc(unsigned char *data,unsigned char nbrOfBytes)
{
	unsigned char byteCtr,bit,crc;
	crc = 0;
	//calculates 8-Bit checksum with given polynomial
	for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
	{
		crc ^= (data[byteCtr]);
		for (bit = 8; bit > 0; --bit)
		{
			if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
				else 		crc = (crc << 1);
		}
	}
	return(crc);
}

void HTSensorHeat(unsigned int duration)
{
	UserRegData |= (1 << 2);

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_WRITE_USER_REGISTER);
	i2c_Soft_Write(UserRegData);
	i2c_Soft_Stop();

	for (int i = 0; i < duration; i++) {
		_delay_ms(1);
	}

	UserRegData &= (~(1 << (2)));

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_WRITE_USER_REGISTER);
	i2c_Soft_Write(UserRegData);
	i2c_Soft_Stop();
}

void HTSensorReset() {
	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_SOFT_RESET);
	i2c_Soft_Stop();
	_delay_ms(15);
	// Read user register data
	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_READ_USER_REGISTER);
	i2c_Soft_Start();
	i2c_Soft_Write(HTU_RD_ADDR);
	UserRegData = i2c_Soft_Read(0);
	i2c_Soft_Stop();
}

RET_TYPE HTSensorReadTemp() {
	unsigned char Data[3], Ack;
	Ack = 0;

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_TEMP_MEAS_noHOLD_MASTER);

	do {
		i2c_Soft_Start();
		Ack = i2c_Soft_Write(HTU_RD_ADDR);
	} while(!Ack);

	Data[MSBData] = i2c_Soft_Read(1);
	Data[LSBData] = i2c_Soft_Read(1);
	Data[CRCData] = i2c_Soft_Read(0);
	i2c_Soft_Stop();
    
	// process data
	if(Data[CRCData] == CalcSht21Crc(Data, 2)) {
	    unsigned int temp = Data[MSBData];
	    temp = temp << 8;
	    temp = temp | (Data[LSBData] & 0xFC);
	    float tempC = -46.85 + 175.72*((float)temp/65536.0);
	    return tempC;
	}
	else {
		return 9999;
	}
}

RET_TYPE HTSensorReadHumidity() {
	unsigned char Data[3], Ack;

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HT_HUM_MEAS_noHOLD_MASTER);

	do {
		i2c_Soft_Start();
		Ack = i2c_Soft_Write(HTU_RD_ADDR);
	} while(!Ack);

	Data[MSBData] = i2c_Soft_Read(1);
	Data[LSBData] = i2c_Soft_Read(1);
	Data[CRCData] = i2c_Soft_Read(0);
	i2c_Soft_Stop();

	// process data
	if(Data[CRCData] == CalcSht21Crc(Data, 2)) {
	    unsigned int rh = Data[MSBData];
	    rh = rh << 8;
	    rh = rh | (Data[LSBData] & 0xFC);
	    float rhfloat = -6 + 125 * (float)rh / 65536;
	    return rhfloat;
	}
	else {
		return 0;
	}
}

float HTSensorReadCompensatedHumidity(void)
{
	float humidity;
	float temperature;
	float compensatedHumidity;

	humidity    = HTSensorReadHumidity();
	temperature = HTSensorReadTemp();

	if (humidity < 0 ) return (0);
	if (humidity > 100 ) return (100);

	if (temperature > 0 && temperature < 80)
	{
		return compensatedHumidity = humidity + (25 - temperature) * HT_TEMP_COEFFICIENT;
	}

	return humidity;
}

// TODO Сделать чтение в режиме блокировки
