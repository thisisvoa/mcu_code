//---------------------------------------------------------
//�ļ����ƣ�UART_Library.c
//ժ    Ҫ������ͨ��
//
//��    �ߣ�����
//��    ����1.1
//�޸����ڣ�2014��04��22�� 
//2014��05��21�� �������� int UART_printf(char uartx,const char *format, ...)
//          
//---------------------------------------------------------

#include "UART_Library.h"
#include "include.h"

char UART0_RxdBuff[UART0_RXDBUFFLENG]={0};           //UART0���ջ���
char UART1_RxdBuff[UART1_RXDBUFFLENG]={0};           //UART1���ջ���
unsigned int UART0_RxdLeng=0;
unsigned int UART1_RxdLeng=0;

/**************************************************************
�������ƣ�IniUart0(char bps)
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
void IniUart0(char bps)
{
  P3SEL |= BIT4+BIT5;
  /*P3DIR |= BIT4;
  P3DIR &= ~BIT5;*/
    
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

void StopU0(void)
{
   P3SEL &= ~(BIT4+BIT5);
   UCTL0 |= SWRST;
   ME1 &= ~UTXE0 + ~URXE0;
   IE1 &= ~URXIE0;
}

/**************************************************************
�������ƣ�IniUart1(char bps)
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
void IniUart1(char bps)
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

/**************************************************************
�������ƣ�void DeleteUART0_RxdBuff(unsigned int x)
�������ܣ����UART0���ջ���
���������unsigned int x----->��ճ���        
�����������
����ֵ  ����
*************************************************************/
void DeleteUART0_RxdBuff(unsigned int x)
{
  unsigned int i=0;
  
  if(x > UART0_RXDBUFFLENG)
  {
    x = UART0_RXDBUFFLENG;
  }
  
  for(i=0;i<x;i++)
  {
    UART0_RxdBuff[i] = 0;
  }
  UART0_RxdLeng = 0;
}

void DeleteUART1_RxdBuff(unsigned int x)
{
  unsigned int i=0;
  if(x > UART1_RXDBUFFLENG)
  {
    x = UART1_RXDBUFFLENG;
  }
  
  for(i=0;i<x;i++)
  {
    UART1_RxdBuff[i] = 0;
  }
  UART1_RxdLeng = 0;
  
}

/**************************************************************
�������ƣ�void WriteByteUART0(char value)
�������ܣ�UART0���� 1 byte
���������char value-->���͵�����ֵ        
�����������
����ֵ  ����
*************************************************************/
void WriteByteUART0(char value)
{
    TXBUF0 = value;                             //��������
    while(!(IFG1 & UTXIFG0));                   //�ȴ��������                         
    IFG1 &= ~UTXIFG0;
}
/**************************************************************
�������ƣ�void WriteByteUART1(char value)
�������ܣ�UART1���� 1 byte
���������char value-->���͵�����ֵ        
�����������
����ֵ  ����
*************************************************************/
void WriteByteUART1(char value)
{
    TXBUF1 = value;                             //��������
    while(!(IFG2 & UTXIFG1));                   //�ȴ��������                         
    IFG2 &= ~UTXIFG1;
}

/**************************************************************
�������ƣ�void EndWriteUART(char uartx)
�������ܣ����ͽ�������
���������char uartx-->���Ͷ˿�        
�����������
����ֵ  ����
*************************************************************/
void EndWriteUART(char uartx)
{
  UART_WriteDelay;
#ifdef  UART0_RS485_                    //��������ΪRS485
  if(0 == uartx)
  {
    UART_RS485Delay;                    //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
    UART0_RE;                           //����״̬
  }
#endif
  
#ifdef  UART1_RS485_                    //��������ΪRS485
  if(1 == uartx)
  {
    UART_RS485Delay;                    //��ʱһ��ʱ��ȴ�485���߿����������һ���ֽڷ������
    UART1_RE;                           //����״̬
  }
#endif
}

/**************************************************************
�������ƣ�void WriteUART(char uartx ,char *p,unsigned int slenght)
�������ܣ�UART��������
���������char uartx----->���Ͷ˿�
          char *p-------->�����������׵�ַ
          unsigned int  slenght--->���ͳ���
�����������
����ֵ  ����
���Ķ˿ڲ���ֻ��Ϊ0/1������ֵ��ֱ�ӷ��أ����������ݡ�
*************************************************************/
void WriteUART(char uartx ,char *p,unsigned int slenght)
{  
  unsigned int i=0;
  void (*WriteByte)(char value);        //����1byte����ָ��

  if(0 == uartx)
  {
#ifdef  UART0_RS485_                    //��������ΪRS485
    UART0_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART0;
  }  
  else if(1 == uartx)
  {
#ifdef  UART0_RS485_                    //��������ΪRS485
    UART1_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART1;
  }
  else                                  //���Ͷ˿ڲ������󷵻�
  {
    return;
  }
 
  for(i=0;i<slenght;i++)
  {  
    WriteByte(*p);                      //����1byte
    p++;                                //ָ����һ������    
  }
  EndWriteUART(uartx);                  //���ͽ���        
}

/**************************************************************
�������ƣ�unsigned int WriteStrUART(char uartx,char *str)
�������ܣ������ַ���
���������char uartx---------------->���Ͷ˿�
          char *str-------->�ַ����׵�ַ
�����������
����ֵ  �������ֽ������ַ������ȣ���������������
*************************************************************/
unsigned int WriteStrUART(char uartx,char *str)
{  
  unsigned int count=0;                 //���ͳ��ȼ���
  void (*WriteByte)(char value);        //����1byte����ָ��

  if(0 == uartx)
  {
#ifdef  UART0_RS485_                    //��������ΪRS485
    UART0_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART0;
  }  
  else if(1 == uartx)
  {
#ifdef  UART1_RS485_                    //��������ΪRS485
    UART1_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART1;
  }
  else                                  //���Ͷ˿ڲ������󷵻�
  {
    return 0;
  }  
  
  while(*str != '\0')
  {  
    WriteByte(*str);                    //����1byte
    str++;                              //ָ����һ������
    count++;
  }
  EndWriteUART(uartx);                  //���ͽ���
  return count;                         //���ط����ֽ���
}

/**********************���ݽ����ж�*********************************/
/*UART0���жϷ�����*/
#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX(void)
{
  if(UART0_RxdLeng < UART0_RXDBUFFLENG)         //�����е����ݳ���С����󳤶�
  {
    UART0_RxdBuff[UART0_RxdLeng++] = RXBUF0;    //���յ������ݴ�����ջ���
    System.Event.Bit.UART0BYTE = SET;           //��λ���ձ�־
    SETTBMS(UART0RXDDELAY);                     //��ʼ����ʱ��B
    TBCTL |= MC_1+TBCLR;                        //�򿪶�ʱ��B
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
    System.Event.Bit.UART1BYTE = SET;
    SETTBMS(UART1RXDDELAY); 
    TBCTL |= MC_1+TBCLR;        //�򿪶�ʱ��B
  }
  //LPM3_EXIT;
}     

int UART_printf(char uartx,const char *format, ...)
{
  //static const char hex[] = "0123456789ABCDEF";
  void (*WriteByte)(char value);        //����1byte����ָ��
  char format_flag;
  unsigned int u_val, div_val, base;
  char *ptr;
  va_list ap;
  
  if(0 == uartx)
  {
#ifdef  UART0_RS485_                    //��������ΪRS485
    UART0_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART0;
  }
  else if(1 == uartx)
  {
#ifdef  UART1_RS485_                    //��������ΪRS485
    UART1_DE;                           //����״̬ 
#endif
    WriteByte = WriteByteUART1;
  }
  else                                  //���Ͷ˿ڲ������󷵻�
  {
    return 0;
  }

  va_start(ap, format);

  for (;;)    /* Until full format string read */
  {
    while ((format_flag = *format++) != '%')      /* Until '%' or '\0' */
    {
      if (!format_flag)
      {
        va_end(ap);
        EndWriteUART(uartx);
        return 0;
      }
      WriteByte(format_flag);
    }

    switch (format_flag = *format++)
    {
    case 'c':
      format_flag = va_arg(ap, int);
    default:
      WriteByte(format_flag);
      continue;

    case 's':
      ptr = VAPTR(char);
      while (format_flag = *ptr++)
      {
        WriteByte(format_flag);
      }
      continue;

    case 'o':
      base = 8;
      if (sizeof(int) == 2)
        div_val = 0x8000;
      else
        div_val = 0x40000000;
      goto CONVERSION_LOOP;

    case 'd':
      base = 10;
      if (sizeof(int) == 2)
        div_val = 10000;
      else
        div_val = 1000000000;
      goto CONVERSION_LOOP;

    case 'x':
      base = 16;
      if (sizeof(int) == 2)
        div_val = 0x1000;
      else
        div_val = 0x10000000;

CONVERSION_LOOP:
      u_val = va_arg(ap,int);
      if (format_flag == 'd')
      {
        if (((int)u_val) < 0)
        {
          u_val = - u_val;
          WriteByte('-');
        }
        while (div_val > 1 && div_val > u_val)
        {
          div_val /= 10;
        }
      }

      do
      {
        WriteByte(HEXASCII[u_val / div_val]);
        u_val %= div_val;
        div_val /= base;
      }
      while (div_val);
    }
  }
}

