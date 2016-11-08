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
#include "ws2812b/ws2812.h"
#include "HTU21DF.h"

int main() {

	char Text[40];

	for( int i = 0; i < 40; i++) Text[i] = 0;

	SetBit(DDRC, 1);
	ClearBit(PORTC, 1);

	i2c_Soft_Init();

	LCD_init();

	HTUReset();

	WS2812Init();

	while(1) {
		_delay_ms(100);

		sprintf(Text, "%.1f", HTUreadTemp());
		LCD_Goto(5, 0);
		LCD_Printf(Text, 2);

		sprintf(Text, "%.1f", HTUreadHumidity());
		LCD_Goto(5, 4);
		LCD_Printf(Text, 2);

	}
	return 0;
}
