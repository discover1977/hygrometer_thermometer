#include "HTSensor.h"

#include <util/delay.h>

void HTSensorReset() {
	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HTU_SOFT_RESET);
	i2c_Soft_Stop();
	_delay_ms(15);
}

RET_TYPE HTSensorReadTemp() {
	unsigned char MSBData, LSBData, CRCData, Ack;
	Ack = 0;

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HTU_TEMP_MEAS_noHOLD_MASTER);

	do {
		i2c_Soft_Start();
		Ack = i2c_Soft_Write(HTU_RD_ADDR);
	} while(!Ack);

	MSBData = i2c_Soft_Read(1);
	LSBData = i2c_Soft_Read(1);
	CRCData = i2c_Soft_Read(0);
	i2c_Soft_Stop();
    
    // handle data
    unsigned int temp = MSBData;
    temp = temp << 8; 
    temp = temp | (LSBData & 0xFC);
    float tempC = -46.85 + 175.72*((float)temp/65536.0); // Use formula from datasheet
    //float tempF = tempC*9.0/5.0 + 32.0; //  Convert to Fahrenheit
    return tempC;
}

RET_TYPE HTSensorReadHumidity() {
	unsigned char MSBData, LSBData, CRCData, Ack;
	Ack = 0;

	i2c_Soft_Start();
	i2c_Soft_Write(HTU_WR_ADDR);
	i2c_Soft_Write(HTU_HUM_MEAS_noHOLD_MASTER);

	do {
		i2c_Soft_Start();
		Ack = i2c_Soft_Write(HTU_RD_ADDR);
	} while(!Ack);

	MSBData = i2c_Soft_Read(1);
	LSBData = i2c_Soft_Read(1);
	CRCData = i2c_Soft_Read(0);
	i2c_Soft_Stop();
    
    // process data 
    unsigned int rh = MSBData;
    rh = rh << 8;
    rh = rh | (LSBData & 0xFC);
    float rhfloat = -6 + 125 * (float)rh / 65536;
    return rhfloat;
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
		return compensatedHumidity = humidity + (25 - temperature) * HTU21D_TEMP_COEFFICIENT;
	}

	return humidity;
}

// TODO Сделать чтение в режиме блокировки
// TODO CRC
