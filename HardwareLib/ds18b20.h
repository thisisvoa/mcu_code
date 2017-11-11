/*********************************************************
*�ļ����ƣ�ds18b20.h
*ժ    Ҫ���¶ȴ�����DS18B20�ӿ�
*
*��ǰ�汾��1.0
*��    �ߣ�����
*��ʼ���ڣ�2012��5��15��
*������ڣ�2012��5��16��
*
**********************************************************/

#ifndef __DS18B20_H
#define __DS18B20_H

#include "system.h"
#include "Public.h"


/***************************************************************
                    DS18B20 I/O�ڶ���
***************************************************************/
#define B20                     BIT3                    
#define PORTIN                  P6IN
#define DQ1                     P6OUT |= BIT3
#define DQ0                     P6OUT &= ~BIT3
#define DQIN                    P6DIR &=~ BIT3
#define DQOUT                   P6DIR |= BIT3

#define DS18B20delayus(x)       delayus(x)
#define DS18B20delayms(x)       delayms(x)


typedef struct
{
  unsigned char Ti;
  unsigned char Event;
}ClassDS18B20;

extern ClassDS18B20 DS18B20;

//extern int Temperature;


/***************************************************************
                        �ӿں���                          
****************************************************************/
 
/*************** ����DS18B20 ���һ���¶ȶ�ȡ ******************/
unsigned int Do1Convert(void);

int Readtemp(unsigned int temper);

unsigned char Ini_18B20(void);
unsigned char StartDS18B20(void);
unsigned int ReadDs18B20temp(void);

#endif /*__DS18B20_H*/