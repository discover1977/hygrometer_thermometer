/*
 * main.c
 *
 *  Created on: 3 нояб. 2016 г.
 *      Author: gavrilov.iv
 */

#include <avr/io.h>
#include <util/delay.h>

#include "bits_macros.h"
#include "i2c-soft.h"
#include "ssd1306.h"
#include "buttons.h"
#include "ws2812b/ws2812.h"
#include "HTU21DF.h"

int main() {

	char Text[40];

	SetBit(DDRC, 1);
	ClearBit(PORTC, 1);

	i2c_Soft_Init();

	LCD_init();

	HTUReset();

	WS2812Init();

	LCD_Goto(0, 0);
	LCD_Printf("Привет", 0);

	while(1) {
		_delay_ms(100);
		sprintf(Text, "%d %d", (int)HTUreadTemp(), (int)HTUreadHumidity());
		LCD_Goto(0, 1);
		LCD_Printf(Text, 0);
	}
	return 0;
}
