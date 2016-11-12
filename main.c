/*
 * main.c
 *
 *  Created on: 3 но€б. 2016 г.
 *      Author: gavrilov.iv
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "bits_macros.h"
#include "i2c-soft.h"
#include "ssd1306.h"
#include "buttons.h"
#include "HTSensor.h"
#include "ws2812b/ws2812.h"

float Themperature, Humidity;

int HTUVal2HSV(int HueMin, int HueMax, int val)
{
    int Temp;

    Temp = HueMax - (val * ((HueMax - HueMin) / 100));
    return Temp;
}

#define SSD1306_USE

int main() {

	char Text[40];



	for( int i = 0; i < 40; i++) Text[i] = 0;

	SetBit(DDRA, 1);
	ClearBit(PORTA, 1);

	i2c_Soft_Init();

#ifdef SSD1306_USE
	LCD_init();
#endif

	HTSensorReset();

	WS2812Init();

	HTSensorHeat(50);

	while(1) {

		_delay_ms(100);

		Themperature = HTSensorReadTemp();
		Humidity = HTSensorReadCompensatedHumidity();

		for(int i = 0; i < LED_COUNT; i++) WS2812SetHSV(i, HTUVal2HSV(0, 800, Humidity), 255, 255);
		WS2812Write(colors, LED_COUNT);

		sprintf(Text, "%.1f ", Themperature);
#ifdef SSD1306_USE
		LCD_Goto(5, 0);
		LCD_Printf(Text, 2);
#endif


		sprintf(Text, "%.1f ", Humidity);
#ifdef SSD1306_USE
		LCD_Goto(5, 4);
		LCD_Printf(Text, 2);
#endif
	}
	return 0;
}
