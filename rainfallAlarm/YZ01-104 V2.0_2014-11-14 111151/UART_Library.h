#ifndef UART_LIBRARY_H_
#define UART_LIBRARY_H_

#include "MSP430_hardware.h"

#define UART0_UCLK              (32768)         //UART0����Ƶ��
#define UART1_UCLK              (32768)         //UART1����Ƶ��

#define UART_delayus(x)         delayus(x)      //��ʱus
#define UART_delayms(x)         delayms(x)      //��ʱms
#define UART_WriteDelay         ;               //�ȴ����������ʱ
#define UART_RS485Delay         UART_delayms(2) //�ȴ�RS485���������ʱ

#define UART0_RXDBUFFLENG       256             //UART0���ջ��泤��
#define UART1_RXDBUFFLENG       20              //UART1���ջ��泤��
#define UART0RXDDELAY           50              //UART0�����ʱ ����
#define UART1RXDDELAY           50              //UART1�����ʱ ����

/*����ʹ��RS458�շ�������ʹ��RS485ʱ�������¶���ע�ͼ���*/
//#define UART0_RS485_
//#define UART1_RS485_

#ifdef  UART0_RS485_
#define UART0_DE                  P2DIR |= BIT6;_NOP();P2OUT |= BIT6; UART_delayus(500);    //����״̬ 
#define UART0_RE                  P2DIR |= BIT6;_NOP();P2OUT &= ~BIT6;UART_delayus(500);    //����״̬
#endif  /*#indef  UART0_RS485_*/

#ifdef  UART1_RS485_
#define UART1_DE                  P2DIR |= BIT7;_NOP();P2OUT |= BIT7; UART_delayus(500);   //����״̬ 
#define UART1_RE                  P2DIR |= BIT7;_NOP();P2OUT &= ~BIT7;UART_delayus(500);   //����״̬
#endif  /*#ifdef  UART1_RS485_*/

#define DELETE_UART0RXD         DeleteUART0_RxdBuff(UART0_RXDBUFFLENG)//��ȫ���UART0���ջ���
#define DELETE_UART1RXD         DeleteUART1_RxdBuff(UART1_RXDBUFFLENG)//��ȫ���UART1���ջ���
#define CRLF_0                  WriteStrUART(0,"\r\n")                  //�س�����
#define CRLF_1                  WriteStrUART(1,"\r\n")

#define BPS_1200                0
#define BPS_2400                1
#define BPS_4800                2
#define BPS_9600                3
#define BPS_19200               4
#define BPS_38400               5
#define BPS_57600               6
#define BPS_115200              7

#define UARTPOWERON     ;/*P3DIR |= BIT6;_NOP(); P3OUT &= ~BIT6; IniUart0(BPS_9600);*/
#define UARTPOWEROFF    ;/*P3DIR |= BIT6;_NOP(); P3OUT |= BIT6;StopU0();*/

extern char UART0_RxdBuff[UART0_RXDBUFFLENG];           //UART0���ջ���
extern char UART1_RxdBuff[UART1_RXDBUFFLENG];           //UART1���ջ���

extern unsigned int UART0_RxdLeng;
extern unsigned int UART1_RxdLeng;

void IniUart0(char bps);
void StopU0(void);
void IniUart1(char bps);
void DeleteUART0_RxdBuff(unsigned int x);
void DeleteUART1_RxdBuff(unsigned int x);
void WriteUART(char uartx ,char *p,unsigned int slenght);
unsigned int WriteStrUART(char uartx,char *str);
int UART_printf(char uartx,const char *format, ...);
#endif  /*#ifndef UART_LIBRARY_H_*/