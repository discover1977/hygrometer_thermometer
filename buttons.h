//***************************************************************************
//
//  Author(s)...: ����� ������  http://ChipEnable.Ru   
//
//  Target(s)...: avr
//
//  Compiler....: IAR
//
//  Description.: ������� ������, �������� �������� � �.�.
//
//  Data........: 12.12.13
//
//***************************************************************************
#ifndef BUT_H
#define BUT_H

#ifdef  __ICCAVR__ 
   #include <ioavr.h>
   #include <intrinsics.h>
#elif  __GNUC__
   #include <avr/io.h>
   #include <avr/interrupt.h>
#elif __CODEVISIONAVR__
   #include <io.h>
#endif

#include <stdint.h>

/****************** �� ������ ****************************/

#define BUT_EV_PRESSED       (1<<0)
#define BUT_EV_HELD          (1<<1) 
#define BUT_EV_RELEASED      (1<<2)
#define BUT_EV_RELEASED_LONG (1<<3)
#define BUT_EV_DOUBLE_CLICK  (1<<4)
#define BUT_EV_ALL           (BUT_EV_PRESSED|BUT_EV_HELD|BUT_EV_RELEASED|BUT_EV_RELEASED_LONG|BUT_EV_DOUBLE_CLICK)


/***************** ��������� �������� *********************/

/*���������� ������*/

#define BUT_AMOUNT           1

/*������� ������ ������ ����� ���������� 
������, ����� ��� ��������� �������. 
������ ���� ������ BUT_COUNT_HELD */

#define BUT_COUNT_THR        10

/*������������ ���������� ������ ����� ������ 
� ������ �������� ������ ��� �������� ������*/

#define BUT_COUNT_THR_2      125

/*������� ������ ������ ����� ���������� ������,
����� ��� ��������� ��������� �������
������ ���� ������ BUT_COUNT_THR */

#define BUT_COUNT_HELD       400


/*������ ������ �������.
��� �������� ������ ���� 
������ ������� ������ (2, 4, 8, 16...).*/

#define BUT_SIZE_BUF   2

/*����������� ����� ��� ���. 
0 - ����� ���� ������ �� ���� ����� BUT_poll()
1 - ����� ����� ������ �� ���� ����� BUT_poll()*/

#define BUT_POLL_ROTATION    0

/* �������, ������� ����������� � ������. 
0 - ��� ������� �� �����������
1 - ������� �����������, ���� ��������� �������������� ����������*/

#define BUT_PRESSED_EN          1
#define BUT_HELD_EN             1
#define BUT_RELEASED_EN         1
#define BUT_RELEASE_LONG_EN     1
#define BUT_DOUBLE_CLICK_EN     1

/* ���� �������. ����� ��������� 
����� �������� �� 1 �� 255 */

#define BUT_PRESSED_CODE        1
#define BUT_HELD_CODE           2 
#define BUT_RELEASED_CODE       3
#define BUT_RELEASED_LONG_CODE  4
#define BUT_DOUBLE_CLICK_CODE   5

/* ��������� ������
BUT_1_ID     ��� ������. ������������� �� ������. �������� �� ������� (1, 2, 3 .. 32)
BUT_1_DDRX   ���� ����������������, �������� ����������� ������ ����
BUT_1_PORTX  ���� ����������������, ��� ���������� ������������� ��������
BUT_1_PINX   ���� ����������������, ������������ ��������� ����
BUT_1_PIN    ����� ���� ����������������
BUT_1_LEV    �������� ������� ����
BUT_1_PULL   0 - �� �������� ������������� ��������, 1 - ��������
BUT_1_EVEN   ������ �������, ������� ����������� � ������ (BUT_EV_PRESSED|BUT_EV_RELEASED|...)*/

#define BUT_1_ID     1
#define BUT_1_DDRX   DDRB
#define BUT_1_PORTX  PORTB
#define BUT_1_PINX   PINB
#define BUT_1_PIN    4
#define BUT_1_LEV    0
#define BUT_1_PULL   1
#define BUT_1_EVENT  (BUT_EV_RELEASED|BUT_EV_RELEASED_LONG|BUT_EV_DOUBLE_CLICK)

/**************** ���������������� ������� *****************/

/*�������������. 
���������� � ������ ���������*/

void BUT_Init(void);

/*����� ������/������. 
���������� ������������*/

void BUT_Poll(void);

/*����� ������� �� ������.����� �������� ��� ����.
������ ��� ������������ ID ������. ������ ��� ������������ ��� �������*/

uint8_t BUT_GetBut(void);

#endif //BUT_H

