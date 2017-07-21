/*********************************************************
*�ļ����ƣ�SC8035.h
*ժ    Ҫ������оƬ��������
*          
*��    �ߣ�����
**********************************************************/

#ifndef 	__SC8035_H
#define 	__SC8035_H 

#include"System.h"
#include"Public.h"

#define SC_RST_OUT              P4DIR |= BIT2  //���帴λ��
#define SC_DATA_OUT             P4DIR |= BIT1
#define SC_RST_IN               P4DIR &= ~BIT2  //���帴λ��
#define SC_DATA_IN              P4DIR &= ~BIT1
#define SC_RST_1                P4OUT |= BIT2  //���帴λ��
#define SC_RST_0                P4OUT &= ~BIT2
#define SC_DATA_1               P4OUT |= BIT1
#define SC_DATA_0               P4OUT &= ~BIT1

void SC_Reset(void);
void SC_Speech(char cnt);

#endif 	/*#ifndef __SC8035_H*/