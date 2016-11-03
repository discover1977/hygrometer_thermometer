/*
 * main.c
 *
 *  Created on: 3 но€б. 2016 г.
 *      Author: gavrilov.iv
 */

#include <avr/io.h>
#include <util/delay.h>

#include "bits_macros.h"
#include "i2c-soft.h"
#include "ssd1306.h"
#include "buttons.h"
#include "ws2812b/ws2812.h"


int main() {

	SetBit(DDRC, 1);
	ClearBit(PORTC, 1);

	WS2812Init();

	while(1) {
		for (int j = 0; j < 256; j++) {
			for (int i = 0; i < 256; i++) {
				//WS2812SetRGB(i, 255, 255, 255);
				WS2812SetHSV(i, 1530, 0, j);
			}
			WS2812Write(colors, LED_COUNT);
			_delay_ms(10);
		}
		_delay_ms(250);
		for (int j = 255; j > -1; j--) {
			for (int i = 0; i < 256; i++) {
				//WS2812SetRGB(i, 255, 255, 255);
				WS2812SetHSV(i, 1530, 0, j);
			}
			WS2812Write(colors, LED_COUNT);
			_delay_ms(10);
		}
		_delay_ms(250);
	}
	return 0;
}
