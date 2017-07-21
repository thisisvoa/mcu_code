//---------------------------------------------------------
//�ļ����ƣ�UART_Library.c
//ժ    Ҫ������ͨ��
//
//��    �ߣ�����
//��    ����1.0
//�޸����ڣ�2013��12��08��
//---------------------------------------------------------

#include "UART_Library.h"
#include "system.h"
#include "include.h"

unsigned char UART0_RxdBuff[UART0_RXDBUFFLENG]={0};           //UART0���ջ���
//unsigned char UART0_RxdBuff[UART0_RXDBUFFLENG]={"00123456780112342F80160009131224153136331B"};
unsigned char UART1_RxdBuff[UART1_RXDBUFFLENG]={0};           //UART1���ջ���
unsigned int UART0_RxdLeng=0;
unsigned int UART1_RxdLeng=0;
//unsigned char UART0_RxdFlag=0;
//unsigned char UART1_RxdFlag=0;

/**************************************************************
�������ƣ�IniUart0(unsigned char bps)
�������ܣ���ʼ������0  ��·����ͨ��ģʽ
���������unsigned char bps-->������        
�����������
����ֵ  ����
������� bps        ��ʼ��������
     0                  1200
     1                  2400
     2                  4800
     3                  9600 
     4                  19200
     5                  38400
     6                  57600
     7                  115200
����ֵ����������Ϊ 9600
*************************************************************/
void IniUart0(unsigned char bps)
{
  P3SEL |= BIT4+BIT5;
  P3DIR |= BIT4;
  P3DIR &= ~BIT5;
    
  UCTL0 |= CHAR;                                
#if  UART0_UCLK==32768 //UCLK=32768HZ
  UTCTL0 |= SSEL0;     //UCLK = ACLK;
#else
  UTCTL0 |= SSEL1;     //UCLK = SMCLK;
#endif

#if  UART0_UCLK==32768 //UCLK=32768HZ
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X1B;UBR10 = 0X00;UMCTL0 = 0X22;break; //1200
    case BPS_2400: UBR00 = 0X0D;UBR10 = 0X00;UMCTL0 = 0X6D;break; //2400
    case BPS_4800: UBR00 = 0X06;UBR10 = 0X00;UMCTL0 = 0XFB;break; //4800
    case BPS_9600: UBR00 = 0X03;UBR10 = 0X00;UMCTL0 = 0X4A;break; //9600
    default:UBR00 = 0X03;UBR10 = 0X00;UMCTL0 = 0X4A;break;//9600
  }
#elif UART0_UCLK==1000000  //UCLK=1MHZ
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X41;UBR10 = 0X03;UMCTL0 = 0X00;break; //1200
    case BPS_2400: UBR00 = 0XA0;UBR10 = 0X01;UMCTL0 = 0X6b;break; //2400
    case BPS_4800: UBR00 = 0XD0;UBR10 = 0X00;UMCTL0 = 0X40;break; //4800
    case BPS_9600: UBR00 = 0X68;UBR10 = 0X00;UMCTL0 = 0X40;break; //9600
    case BPS_19200: UBR00 = 0X34;UBR10 = 0X00;UMCTL0 = 0X40;break; //19200
    case BPS_38400: UBR00 = 0X1A;UBR10 = 0X00;UMCTL0 = 0X00;break; //38400
    case BPS_57600: UBR00 = 0X11;UBR10 = 0X00;UMCTL0 = 0X52;break; //57600 
    case BPS_115200: UBR00 = 0X08;UBR10 = 0X00;UMCTL0 = 0X6D;break; //115200
    default:UBR00 = 0X68;UBR10 = 0X00;UMCTL0 = 0X40;break;//9600
  }
#elif UART0_UCLK==2000000  //UCLK=2MHZ 
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X82;UBR10 = 0X06;UMCTL0 = 0X00;break; //1200
    case BPS_2400: UBR00 = 0X41;UBR10 = 0X03;UMCTL0 = 0X00;break; //2400
    case BPS_4800: UBR00 = 0XA0;UBR10 = 0X01;UMCTL0 = 0XC0;break; //4800
    case BPS_9600: UBR00 = 0XD0;UBR10 = 0X00;UMCTL0 = 0X40;break; //9600
    case BPS_19200: UBR00 = 0X68;UBR10 = 0X00;UMCTL0 = 0X40;break; //19200
    case BPS_38400: UBR00 = 0X34;UBR10 = 0X00;UMCTL0 = 0X40;break; //38400
    case BPS_57600: UBR00 = 0X22;UBR10 = 0X00;UMCTL0 = 0XED;break; //57600 
    case BPS_115200: UBR00 = 0X11;UBR10 = 0X00;UMCTL0 = 0X52;break; //115200
    default:UBR00 = 0XD0;UBR10 = 0X00;UMCTL0 = 0X40;break;//9600
  }
#elif UART0_UCLK==4000000  //UCLK=4MHZ
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X05;UBR10 = 0X0D;UMCTL0 = 0X00;break; //1200
    case BPS_2400: UBR00 = 0X82;UBR10 = 0X06;UMCTL0 = 0X00;break; //2400
    case BPS_4800: UBR00 = 0X41;UBR10 = 0X03;UMCTL0 = 0X00;break; //4800
    case BPS_9600: UBR00 = 0XA0;UBR10 = 0X01;UMCTL0 = 0XC0;break; //9600
    case BPS_19200: UBR00 = 0XD0;UBR10 = 0X00;UMCTL0 = 0X40;break; //19200
    case BPS_38400: UBR00 = 0X68;UBR10 = 0X00;UMCTL0 = 0X40;break; //38400
    case BPS_57600: UBR00 = 0X45;UBR10 = 0X00;UMCTL0 = 0X4A;break; //57600 
    case BPS_115200: UBR00 = 0X22;UBR10 = 0X00;UMCTL0 = 0XED;break; //115200
    default:UBR00 = 0XA0;UBR10 = 0X01;UMCTL0 = 0XC0;break;//9600
  }
#elif UART0_UCLK==6000000  //UCLK=6MHZ
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X88;UBR10 = 0X13;UMCTL0 = 0X00;break; //1200
    case BPS_2400: UBR00 = 0XC4;UBR10 = 0X09;UMCTL0 = 0X00;break; //2400
    case BPS_4800: UBR00 = 0XE2;UBR10 = 0X04;UMCTL0 = 0X00;break; //4800
    case BPS_9600: UBR00 = 0X71;UBR10 = 0X02;UMCTL0 = 0X00;break; //9600
    case BPS_19200: UBR00 = 0X38;UBR10 = 0X01;UMCTL0 = 0X40;break; //19200
    case BPS_38400: UBR00 = 0X9C;UBR10 = 0X00;UMCTL0 = 0X40;break; //38400
    case BPS_57600: UBR00 = 0X68;UBR10 = 0X00;UMCTL0 = 0X40;break; //57600 
    case BPS_115200: UBR00 = 0X34;UBR10 = 0X00;UMCTL0 = 0X40;break; //115200
    default:UBR00 = 0X71;UBR10 = 0X02;UMCTL0 = 0X00;break;//9600
  }
#elif UART0_UCLK==8000000  //UCLK=8MHZ
  switch(bps)
  {
    case BPS_1200: UBR00 = 0X0A;UBR10 = 0X1A;UMCTL0 = 0X00;break; //1200
    case BPS_2400: UBR00 = 0X05;UBR10 = 0X0D;UMCTL0 = 0X00;break; //2400
    case BPS_4800: UBR00 = 0X82;UBR10 = 0X06;UMCTL0 = 0X00;break; //4800
    case BPS_9600: UBR00 = 0X41;UBR10 = 0X03;UMCTL0 = 0X00;break; //9600
    case BPS_19200: UBR00 = 0XA0;UBR10 = 0X01;UMCTL0 = 0XC0;break; //19200
    case BPS_38400: UBR00 = 0XD0;UBR10 = 0X00;UMCTL0 = 0X40;break; //38400
    case BPS_57600: UBR00 = 0X8A;UBR10 = 0X00;UMCTL0 = 0XDE;break; //57600 
    case BPS_115200: UBR00 = 0X45;UBR10 = 0X00;UMCTL0 = 0X4A;break; //115200
    default:UBR00 = 0X41;UBR10 = 0X03;UMCTL0 = 0X00;break;//9600
  }
#endif
                      
  UCTL0 &= ~SWRST;                             
  ME1 |= UTXE0 + URXE0;                        
  IE1 |= URXIE0;  
  
  DELETE_UART0RXD;        //��ս��ջ���
#ifdef  UART0_RS485_
  UART0_RE;                    //RS485����ģʽ
#endif
}

/**************************************************************
�������ƣ�IniUart1(unsigned char bps)
�������ܣ���ʼ������1    ��·����ͨ��ģʽ
���������unsigned char bps-->������        
�����������
����ֵ  ����
������� bps        ��ʼ��������
     0                  1200
     1                  2400
     2                  4800
     3                  9600 
     4                  19200
     5                  38400
     6                  57600
     7                  115200
����ֵ����������Ϊ 9600
*************************************************************/
void IniUart1(unsigned char bps)
{
  P3SEL |= BIT6+BIT7;
  P3DIR |= BIT6;
  P3DIR &= ~BIT7;
    
  UCTL1 |= CHAR;                                
#if  UART1_UCLK==32768 //UCLK=32768HZ
  UTCTL1 |= SSEL0;     //UCLK = ACLK;
#else
  UTCTL1 |= SSEL1;     //UCLK = SMCLK;
#endif

#if  UART1_UCLK==32768 //UCLK=32768HZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X1B;UBR11 = 0X00;UMCTL1 = 0X22;break; //1200
    case BPS_2400: UBR01 = 0X0D;UBR11 = 0X00;UMCTL1 = 0X6D;break; //2400
    case BPS_4800: UBR01 = 0X06;UBR11 = 0X00;UMCTL1 = 0XFB;break; //4800
    case BPS_9600: UBR01 = 0X03;UBR11 = 0X00;UMCTL1 = 0X4A;break; //9600
    default:UBR01 = 0X03;UBR11 = 0X00;UMCTL1 = 0X4A;break;//9600
  }
#elif UART1_UCLK==1000000  //UCLK=1MHZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X41;UBR11 = 0X03;UMCTL1 = 0X00;break; //1200
    case BPS_2400: UBR01 = 0XA0;UBR11 = 0X01;UMCTL1 = 0X6b;break; //2400
    case BPS_4800: UBR01 = 0XD0;UBR11 = 0X00;UMCTL1 = 0X40;break; //4800
    case BPS_9600: UBR01 = 0X68;UBR11 = 0X00;UMCTL1 = 0X40;break; //9600
    case BPS_19200: UBR01 = 0X34;UBR11 = 0X00;UMCTL1 = 0X40;break; //19200
    case BPS_38400: UBR01 = 0X1A;UBR11 = 0X00;UMCTL1 = 0X00;break; //38400
    case BPS_57600: UBR01 = 0X11;UBR11 = 0X00;UMCTL1 = 0X52;break; //57600 
    case BPS_115200: UBR01 = 0X08;UBR11 = 0X00;UMCTL1 = 0X6D;break; //115200
    default:UBR01 = 0X68;UBR11 = 0X00;UMCTL1 = 0X40;break;//9600
  }
#elif UART1_UCLK==2000000  //UCLK=2MHZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X82;UBR11 = 0X06;UMCTL1 = 0X00;break; //1200
    case BPS_2400: UBR01 = 0X41;UBR11 = 0X03;UMCTL1 = 0X00;break; //2400
    case BPS_4800: UBR01 = 0XA0;UBR11 = 0X01;UMCTL1 = 0XC0;break; //4800
    case BPS_9600: UBR01 = 0XD0;UBR11 = 0X00;UMCTL1 = 0X40;break; //9600
    case BPS_19200: UBR01 = 0X68;UBR11 = 0X00;UMCTL1 = 0X40;break; //19200
    case BPS_38400: UBR01 = 0X34;UBR11 = 0X00;UMCTL1 = 0X40;break; //38400
    case BPS_57600: UBR01 = 0X22;UBR11 = 0X00;UMCTL1 = 0XED;break; //57600 
    case BPS_115200: UBR01 = 0X11;UBR11 = 0X00;UMCTL1 = 0X52;break; //115200
    default:UBR01 = 0XD0;UBR11 = 0X00;UMCTL1 = 0X40;break;//9600
  }
#elif UART1_UCLK==4000000  //UCLK=4MHZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X05;UBR11 = 0X0D;UMCTL1 = 0X00;break; //1200
    case BPS_2400: UBR01 = 0X82;UBR11 = 0X06;UMCTL1 = 0X00;break; //2400
    case BPS_4800: UBR01 = 0X41;UBR11 = 0X03;UMCTL1 = 0X00;break; //4800
    case BPS_9600: UBR01 = 0XA0;UBR11 = 0X01;UMCTL1 = 0XC0;break; //9600
    case BPS_19200: UBR01 = 0XD0;UBR11 = 0X00;UMCTL1 = 0X40;break; //19200
    case BPS_38400: UBR01 = 0X68;UBR11 = 0X00;UMCTL1 = 0X40;break; //38400
    case BPS_57600: UBR01 = 0X45;UBR11 = 0X00;UMCTL1 = 0X4A;break; //57600 
    case BPS_115200: UBR01 = 0X22;UBR11 = 0X00;UMCTL1 = 0XED;break; //115200
    default:UBR01 = 0XA0;UBR11 = 0X01;UMCTL1 = 0XC0;break;//9600
  }
#elif UART1_UCLK==6000000  //UCLK=6MHZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X88;UBR11 = 0X13;UMCTL1 = 0X00;break; //1200
    case BPS_2400: UBR01 = 0XC4;UBR11 = 0X09;UMCTL1 = 0X00;break; //2400
    case BPS_4800: UBR01 = 0XE2;UBR11 = 0X04;UMCTL1 = 0X00;break; //4800
    case BPS_9600: UBR01 = 0X71;UBR11 = 0X02;UMCTL1 = 0X00;break; //9600
    case BPS_19200: UBR01 = 0X38;UBR11 = 0X01;UMCTL1 = 0X40;break; //19200 
    case BPS_38400: UBR01 = 0X9C;UBR11 = 0X00;UMCTL1 = 0X40;break; //38400
    case BPS_57600: UBR01 = 0X68;UBR11 = 0X00;UMCTL1 = 0X40;break; //57600 
    case BPS_115200: UBR01 = 0X34;UBR11 = 0X00;UMCTL1 = 0X40;break; //115200
    default:UBR01 = 0X71;UBR11 = 0X02;UMCTL1 = 0X00;break;//9600
  }
#elif UART1_UCLK==8000000  //UCLK=8MHZ
  switch(bps)
  {
    case BPS_1200: UBR01 = 0X0A;UBR11 = 0X1A;UMCTL1 = 0X00;break; //1200
    case BPS_2400: UBR01 = 0X05;UBR11 = 0X0D;UMCTL1 = 0X00;break; //2400
    case BPS_4800: UBR01 = 0X82;UBR11 = 0X06;UMCTL1 = 0X00;break; //4800
    case BPS_9600: UBR01 = 0X41;UBR11 = 0X03;UMCTL1 = 0X00;break; //9600
    case BPS_19200: UBR01 = 0XA0;UBR11 = 0X01;UMCTL1 = 0XC0;break; //19200
    case BPS_38400: UBR01 = 0XD0;UBR11 = 0X00;UMCTL1 = 0X40;break; //38400
    case BPS_57600: UBR01 = 0X8A;UBR11 = 0X00;UMCTL1 = 0XDE;break; //57600 
    case BPS_115200: UBR01 = 0X45;UBR11 = 0X00;UMCTL1 = 0X4A;break; //115200
    default:UBR01 = 0X41;UBR11 = 0X03;UMCTL1 = 0X00;break;//9600
  }
#endif
                        
  UCTL1 &= ~SWRST;                             
  ME2 |= UTXE1 + URXE1;                        
  IE2 |= URXIE1;     
  
  DELETE_UART1RXD;        //��ս��ջ���
#ifdef  UART1_RS485_
  UART1_RE;                    //RS485����ģʽ
#endif
}

void WriteByteUART0(unsigned char value)
{
    TXBUF0 = value;                             //��������
    while(!(IFG1 & UTXIFG0));                   //�ȴ��������                         
    IFG1 &= ~UTXIFG0;
}

void WriteByteUART1(unsigned char value)
{
    TXBUF1 = value;                             //��������
    while(!(IFG2 & UTXIFG1));                   //�ȴ��������                         
    IFG2 &= ~UTXIFG1;
}

/**************************************************************
�������ƣ�void WriteUART0(unsigned char *p,unsigned int slenght)
�������ܣ�UART0�ӿڷ�������
���������unsigned char *p-------->�����������׵�ַ
          unsigned int  slenght--->���ͳ���
�����������
����ֵ  ����
*************************************************************/
void WriteUART0(unsigned char *p,unsigned int slenght)
{  
  unsigned int i=0;

#ifdef  UART0_RS485_                         //��������ΪRS485
  UART0_DE;                                       //����״̬  
#endif
  for(i=0;i<slenght;i++)
  {  
    WriteByteUART0(*p);                         //����1byte
    p++;                                        //ָ����һ������    
  }
  UART_WriteDelay;
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART_RS485Delay;                                  //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART0_RE;                                    //����״̬
#endif
}

/**************************************************************
�������ƣ�void WriteUART1(unsigned char *p,unsigned int slenght)
�������ܣ�UART1�ӿڷ�������
���������unsigned char *p-------->�����������׵�ַ
          unsigned int  slenght--->���ͳ���
�����������
����ֵ  ����
*************************************************************/
void WriteUART1(unsigned char *p,unsigned int slenght)
{  
  unsigned int i=0;
  
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART1_DE;                                    //����״̬ 
#endif
  for(i=0;i<slenght;i++)
  {  
    WriteByteUART1(*p);                         //����1byte
    p++;                                        //ָ����һ������    
  }
  UART_WriteDelay;
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART_RS485Delay;                             //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART1_RE;                                   //����״̬
#endif
}

/**************************************************************
�������ƣ�void WriteLineUART0(unsigned char *p,unsigned int slenght)
�������ܣ�UART0�ӿڴ����з������ݣ��Զ����У�����һ����ʾ�����ݡ�
���������unsigned char *p-------->�����������׵�ַ
          unsigned int  slenght--->���ͳ���
�����������
����ֵ  ����
*************************************************************/
void WriteLineUART0(unsigned char *p,unsigned int slenght)
{  
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART0_DE;                                    //����״̬  
#endif
  WriteByteUART0(0X0D);                         //����1byte  
  WriteByteUART0(0X0A);                         //����1byte 
  WriteUART0(p,slenght);                       //��������
}

/**************************************************************
�������ƣ�void WriteLineUART1(unsigned char *p,unsigned int slenght)
�������ܣ�UART1�ӿڴ����з������ݣ��Զ����У�����һ����ʾ�����ݡ�
���������unsigned char *p-------->�����������׵�ַ
          unsigned int  slenght--->���ͳ���
�����������
����ֵ  ����
*************************************************************/
void WriteLineUART1(unsigned char *p,unsigned int slenght)
{
#ifdef  UART1_RS485_                           //��������ΪRS485
  UART1_DE;                                    //����״̬  
#endif
  WriteByteUART1(0X0D);                         //����1byte 
  WriteByteUART1(0X0A);                         //����1byte 
  WriteUART1(p,slenght);                       //��������
}

/**************************************************************
�������ƣ�unsigned int WriteStrUART0(unsigned char *str)
�������ܣ�UART0�����ַ���
���������unsigned char *str-------->�ַ����׵�ַ
�����������
����ֵ  �������ֽ������ַ������ȣ���������������
*************************************************************/
unsigned int WriteStrUART0(unsigned char *str)
{  
  unsigned int count=0;                         //���ͳ��Ȼ���
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART0_DE;                                    //����״̬  
#endif                                        
  while(*str != '\0')
  {  
    WriteByteUART0(*str);                         //����1byte
    str++;                                        //ָ����һ������
    count++;
  }
  UART_WriteDelay;
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART_RS485Delay;                                  //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART0_RE;                                    //����״̬
#endif
  return count;                                 //���ط����ֽ���
}

/**************************************************************
�������ƣ�unsigned int WriteStrUART1(unsigned char *str)
�������ܣ�UART1�����ַ���
���������unsigned char *str-------->�ַ����׵�ַ
�����������
����ֵ  �������ֽ������ַ������ȣ���������������
*************************************************************/
unsigned int WriteStrUART1(unsigned char *str)
{  
  unsigned int count=0;                         //���ͳ��Ȼ���
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART1_DE;                                    //����״̬  
#endif                                        
  while(*str != '\0')
  {  
    WriteByteUART1(*str);                         //����1byte
    str++;                                      //ָ����һ������
    count++;
  }
  UART_WriteDelay;
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART_RS485Delay;                                  //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART1_RE;                                    //����״̬
#endif
  return count;                                 //���ط����ֽ���
}

/**************************************************************
�������ƣ�unsigned int WriteLineStrUART0(unsigned char *str)
�������ܣ�UART0�ӿڴ����з����ַ������Զ����У�����һ����ʾ�����ݡ�
���������unsigned char *str-------->�������ַ����׵�ַ
�����������
����ֵ  �������ֽ������ַ������ȣ���������������س����з���
*************************************************************/
unsigned int WriteLineStrUART0(unsigned char *str)
{
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART0_DE;                                    //����״̬  
#endif
  WriteByteUART0(0X0D);                         //����1byte
  WriteByteUART0(0X0A);                         //����1byte
   
  return WriteStrUART0(str);                   //��������
}

/**************************************************************
�������ƣ�unsigned int WriteLineStrUART1(unsigned char *str)
�������ܣ�UART1�ӿڴ����з����ַ������Զ����У�����һ����ʾ�����ݡ�
���������unsigned char *str-------->�������ַ����׵�ַ
�����������
����ֵ  �������ֽ������ַ������ȣ���������������س����з���
*************************************************************/
unsigned int WriteLineStrUART1(unsigned char *str)
{
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART1_DE;                                    //����״̬  
#endif
  WriteByteUART1(0X0D);                         //����1byte
  WriteByteUART1(0X0A);                         //����1byte

  return WriteStrUART1(str);                   //�������� 
}

void DeleteUART0_RxdBuff(unsigned int x)
{
  unsigned int i=0;
  
  if(x >= UART0_RXDBUFFLENG)
  {
    x = UART0_RXDBUFFLENG;
  }
  
  for(i=0;i<x;i++)
  {
    UART0_RxdBuff[i] = 0;
  }
  //UART0_RxdLeng = 0;
  //UART0_RxdFlag =0;
  UART0_RxdLeng = 0;
  System.Event.Bit.UART0BYTE = RESET;
  System.Event.Bit.UART0 = RESET;
}

void DeleteUART1_RxdBuff(unsigned int x)
{
  unsigned int i=0;
  if(x >= UART1_RXDBUFFLENG)
  {
    x = UART1_RXDBUFFLENG;
  }
  
  for(i=0;i<x;i++)
  {
    UART1_RxdBuff[i] = 0;
  }
  //UART1_RxdLeng = 0;
  //UART1_RxdFlag = 0;
  UART1_RxdLeng = 0;
  System.Event.Bit.UART1BYTE = RESET;
  System.Event.Bit.UART1 = RESET;
}

/**************************************************************
�������ƣ�unsigned char UART0_RxdPack(unsigned int ms)
�������ܣ��ж�һ�������Ƿ�������
���������unsigned int ms-------->���ʱ�� ����
�����������
����ֵ  ��1 ���ճɹ�  0 ���ڽ���
*************************************************************/
unsigned char UART0_RxdPack(unsigned int ms)
{ 
  //UART0_RxdFlag = 0;
  System.Event.Bit.UART0BYTE = RESET;
  ms *= 10;
  while(ms--)
  {
    //if(1==UART0_RxdFlag)
    if(System.Event.Bit.UART0BYTE)
      return 0;
    
    UART_delayus(100);
  }
  return 1;
}

unsigned char UART1_RxdPack(unsigned int ms)
{
  //UART1_RxdFlag = 0;
  System.Event.Bit.UART1BYTE = RESET;
  ms *= 10;
  while(ms--)
  {
    //if(1==UART1_RxdFlag)
    if(System.Event.Bit.UART1BYTE)
      return 0;
    
    UART_delayus(100);
  }
  return 1;
}

void PrintHEXU1(unsigned char *padd,unsigned int length)
{ 
  unsigned int i=0;
  unsigned char asc=0;

#ifdef  UART1_RS485_                         //��������ΪRS485
  UART1_DE;                                    //����״̬ 
#endif   
  WriteByteUART1(0X0D);
  WriteByteUART1(0X0A);
  WriteByteUART1('{');
  WriteByteUART1(' '); 
  for(i=0;i<length;i++)
  {   
    asc = HEXASCII[padd[i]>>4];   
    WriteByteUART1(asc); 
    asc = HEXASCII[padd[i]&0X0F];
    WriteByteUART1(asc);     
    WriteByteUART1(' '); 
  }
  WriteByteUART1('}');
  
#ifdef  UART1_RS485_                         //��������ΪRS485
  UART_RS485Delay;                             //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART1_RE;                                   //����״̬
#endif
}

void PrintHEXU0(unsigned char *padd,unsigned int length)
{ 
  unsigned int i=0;
  unsigned char asc=0;

#ifdef  UART0_RS485_                         //��������ΪRS485
  UART0_DE;                                    //����״̬ 
#endif   
  WriteByteUART0(0X0D);
  WriteByteUART0(0X0A);
  WriteByteUART0('{');
  WriteByteUART0(' '); 
  for(i=0;i<length;i++)
  {   
    asc = HEXASCII[padd[i]>>4];   
    WriteByteUART0(asc); 
    asc = HEXASCII[padd[i]&0X0F];
    WriteByteUART0(asc);     
    WriteByteUART0(' '); 
  }
  WriteByteUART0('}');
  
#ifdef  UART0_RS485_                         //��������ΪRS485
  UART_RS485Delay;                             //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
  UART0_RE;                                   //����״̬
#endif
}


void SendNum(long int value,unsigned char type,unsigned char cmd)
{
  unsigned char strtmep[16]={0};

  SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
    
  WriteLineStrUART0(strtmep);
}

void SendNumUART1(long int value,unsigned char type,unsigned char cmd)
{
  unsigned char strtmep[16]={0};

  SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
    
  WriteLineStrUART1(strtmep);
}

void sendtime(void)
{
  unsigned char timestr[22]={"2000/00/00 00:00:00"};
  
  timestr[2] = HEXASCII[System.Time.Year/10];
  timestr[3] = HEXASCII[System.Time.Year%10];
  timestr[5] = HEXASCII[System.Time.Month/10];
  timestr[6] = HEXASCII[System.Time.Month%10];
  timestr[8] = HEXASCII[System.Time.Day/10];
  timestr[9] = HEXASCII[System.Time.Day%10];
  timestr[11] = HEXASCII[System.Time.Hour/10];
  timestr[12] = HEXASCII[System.Time.Hour%10];
  timestr[14] = HEXASCII[System.Time.Minute/10];
  timestr[15] = HEXASCII[System.Time.Minute%10];
  timestr[17] = HEXASCII[System.Time.Second/10];
  timestr[18] = HEXASCII[System.Time.Second%10];

  WriteLineStrUART1(timestr);
}

/**********************���ݽ����ж�*********************************/
/*UART0���жϷ�����*/
#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX(void)
{
  if(UART0_RxdLeng < UART0_RXDBUFFLENG)
  {
    UART0_RxdBuff[UART0_RxdLeng++] = RXBUF0;
    //UART0_RxdFlag = 1;
    System.Event.Bit.UART0BYTE = SET;
     
    SETTBMS(UART0RXDDELAY);  
    TBCTL |= MC_1+TBCLR;        //�򿪶�ʱ��B
  }
  //LPM3_EXIT;
}          

/*UART1���жϷ�����*/
#pragma vector=UART1RX_VECTOR
__interrupt void UART1_RX(void)
{
  if(UART1_RxdLeng < UART1_RXDBUFFLENG)
  {
    UART1_RxdBuff[UART1_RxdLeng++] = RXBUF1;
    //UART1_RxdFlag = 1;
    System.Event.Bit.UART1BYTE = SET;
    SETTBMS(UART1RXDDELAY); 
    TBCTL |= MC_1+TBCLR;        //�򿪶�ʱ��B
  }
  //LPM3_EXIT;
}     
