/*
 * ssd1306.h
 *
 *  Created on: 29 򦮲. 2016 ᬍ
 *      Author: gavrilov.iv
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include "compilers_4.h"

#define SSD1306_I2C_ADDRESS					0x78 //0x3C// 0x3D//0x78
//#define SSD1306_I2C_ADDRESS					0x3C// 0x3D//0x78
//#define SSD1306_I2C_ADDRESS					0x3D//0x78


// size
#define SSD1306_LCDWIDTH                 	128
#define SSD1306_LCDHEIGHT               	64
#define SSD1306_DEFAULT_SPACE            	5
// Commands
#define SSD1306_SETCONTRAST                	0x81
#define RESET_CONTRAST                      0x7F
#define SSD1306_DISPLAYALLON_RESUME       	0xA4
#define SSD1306_DISPLAYALLON              	0xA5
#define SSD1306_NORMALDISPLAY             	0xA6
#define SSD1306_INVERTDISPLAY              	0xA7
#define SSD1306_DISPLAYOFF                	0xAE
#define SSD1306_DISPLAYON                  	0xAF
#define SSD1306_SETDISPLAYOFFSET           	0xD3
#define SSD1306_SETCOMPINS                	0xDA
#define SSD1306_SETVCOMDETECT             	0xDB
#define SSD1306_SETDISPLAYCLOCKDIV        	0xD5
#define SSD1306_SETPRECHARGE              	0xD9
#define SSD1306_SETMULTIPLEX               	0xA8
#define SSD1306_SETLOWCOLUMN               	0x00
#define SSD1306_SETHIGHCOLUMN             	0x10
#define SSD1306_SETSTARTLINE             	0x40
#define SSD1306_MEMORYMODE               	0x20
#define SSD1306_COLUMNADDR               	0x21
#define SSD1306_PAGEADDR                   	0x22
#define SSD1306_COMSCANINC                 	0xC0
#define SSD1306_COMSCANDEC                 	0xC8
#define SSD1306_SEGREMAP                  	0xA0
#define SSD1306_CHARGEPUMP                 	0x8D
#define SSD1306_EXTERNALVCC               	0x01
#define SSD1306_SWITCHCAPVCC              	0x02
#define SSD1306_CHARGEPUMP_DISABLE         	0x10
#define SSD1306_CHARGEPUMP_ENABLE           0x14
#define SSD1306_HORIZONTAL_ADDRESSING       0x00
#define SSD1306_VERTICAL_ADDRESSING         0x01
#define SSD1306_SEGREMAP_OFF                0x00
#define SSD1306_SEGREMAP_ON                 0x01
// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL        		0x2F
#define SSD1306_DEACTIVATE_SCROLL           0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL     0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL      0x27
#define SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL 0x29
#define SSD1306_VERT_AND_LEFT_HORIZ_SCROLL  0x2A

#define COMAND		                        0x00
#define DATA		                        0x40

void LCD_init(void);  //ᬼ 鮨��騠��婱𐬥
void LCD_Commmand(unsigned char ControByte, unsigned char DataByte); //믬ᮤ 婱𐬥 鬨 塭
void LCD_Goto(unsigned char x, unsigned char y);    //��鳼 믮񥩭᳻
void LCD_Goto2X(unsigned char x, unsigned char y); //��鳼 믮񥩭᳻ ��禭㡭ힹ�
void LCD_Clear(void);  //︨򳫠 㲥䬠婱𐬥
void LCD_Contrast(char set_contrast); //󱯩랠믭󱡱󞡮𞮠嬠255
void LCD_BigNum(unsigned char num);  //㼢⯫鳠��
void LCD_Char(unsigned int c);  //㼢򩭢ﬠ
void LCD_CharBig(unsigned int c); // 㼢뱳𐮻󡲨쯢
void LCD_Printf(unsigned char* buf, unsigned char size); //𐦷᳠氠򳱮뱠흇�譥񡭨 - 0 򡭻硬欪駠2 - ��鸨 - 3 򡭻硡לּ裡󯬼묠嬿 ��)
void LCD_DrawImage(unsigned char num_image); //㼢泌𡫠񳩭뱠饠��
void LCD_Bat(unsigned char y,unsigned char x, unsigned char z);   //񩲳氠⡲ᱥꫳ 𐬠믮񥩭᳠ꟺ - ﰠ0 嬠10 妫殨狊void LCD_Mode(char set_mode); //1 - inverted / 0 - normal
void LCD_Sleep(char set);   //1 - on sleep / 0 - off sleep
void LCD_Mode(unsigned char set_mode);

#endif /* SSD1306_H_ */
