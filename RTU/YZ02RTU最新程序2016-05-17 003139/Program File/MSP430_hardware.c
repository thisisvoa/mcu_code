//---------------------------------------------------------
//�ļ����ƣ�MSP430_hardware.c
//ժ    Ҫ��MSP430Ӳ��
//
//��    �ߣ�����
//��    ����1.0
//�޸����ڣ�2013��11��22��
//---------------------------------------------------------

#include "MSP430_hardware.h"
#include "include.h"



void InitSysCKL(void)                                        //ϵͳʱ�ӳ�ʼ��
{  
  /***********************��������,ϵͳʱ�ӳ�ʼ��**************************/
  unsigned int i;
  BCSCTL1 &= ~XT2OFF;                                        //��XT2����
  do
  {  
    IFG1 &= ~OFIFG;                                          //�������ʧЧ��־
    for (i=0xFF;i>0;i--);                                    //��ʱ���ȴ�XT2����
  }
  while ((IFG1 & OFIFG) != 0);                               //�ж�XT2�Ƿ�����
  BCSCTL2 = SELM_2+SELS;                                     //ѡ��MCLK��SMCLKΪXT2
                                      
}

/*��������λ����*/
void Except(void)
{
  if(IFG1&WDTIFG==WDTIFG)       //���Ź��жϻ�ȫ��ֵ����
  {
    IFG1 &= ~WDTIFG;            //��λ���Ź��жϱ�־    
  }
  else if(FCTL3&KEYV==KEYV)     //FLASH��ȫ��ֵ����
  {
    FCTL3 &= ~KEYV;             //��λFLASH��ȫ��ֵ   
  }
}

//���������ʼ��
void KeyInit(void)
{
  P2IES |=  BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;            //ѡ���½����ж�
  P2IE  |=  BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;            //���ж�ʹ��
  P2DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);          //���ð����ӿ�Ϊ����
 
}

/**************************************************************
�������ƣ�void IniTimerA(void) 
�������ܣ���ʼ����ʱ��A
�����������
�����������ʱ��A��ؼĴ���
����ֵ  ����
*************************************************************/
void IniTimerA(void) 
{  
  /*TACTL = TACLR;                        //ֹͣ
  _NOP();*/
  TACTL = TASSEL_1+MC_0+TACLR;     //ACLK 32768HZ,��������ģʽ�����TAR������ʱ���жϡ�
  TACCTL0 = CCIE;                       //CCR0�ж�ʹ��
  TACCR0 = 16384;                       //����ֵ 0.5s
  TACTL |= TAIE+MC_3;
}

void TimerBInit()
{
  TBCTL=TBSSEL_1+TBCLR+MC_0;		//ѡ��ʱ��ԴΪACLK
  TBCCTL0 = CCIE;    			//����ʱ���ж�
}

/*****************************************************************************
���ö�ʱʱ��
ti��Ҫ��ʱ��ʱ�䣬��ʱ��Դ��Ƶ���й�
*****************************************************************************/
void SetTimerB(unsigned int ti)
{
  TBCCR0=ti;				//��ʱʱ��
}

/*****************************************************************************
�򿪻�رն�ʱ��B ������ģʽ
doit: 0��ֹͣ   1������
*****************************************************************************/
void GotimeDfB(unsigned char doit)
{
  if(doit==1)
  {
    TBCTL |= MC_1+TBCLR;		//�򿪶�ʱ��
  }
  else if(doit==0)
  {
    TBCTL &= ~MC0;					//�رն�ʱ��
  }
}

#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B0(void)   //��ʱ���жϺ���
{
  if(System.Event.Bit.UART0BYTE)
  {
    System.Event.Bit.UART0BYTE = RESET;
    System.Event.Bit.UART0 = SET;
  }
  if(System.Event.Bit.UART1BYTE)
  {
    System.Event.Bit.UART1BYTE = RESET;
    System.Event.Bit.UART1 = SET;
  }
  TBCTL &= ~MC0;        //�رն�ʱ��
  LPM3_EXIT;
}

/*TimerA CCR0 �жϷ������*/
#pragma vector = TIMERA0_VECTOR
__interrupt void Time_A_CCR0(void)
{
  RESETWDT;
  TiTimeHandlers();
  if(Rainfall.InDelay > 0)
  {
    Rainfall.InDelay--;
  }
}

/*TimerA TAR ��ʱ����жϷ������*/
#pragma vector = TIMERA1_VECTOR
__interrupt void Time_A_TAIFG(void)
{      
  RESETWDT;
  
  SysTimePlue();        //����ʱ�����
  if(Rainfall.InDelay > 0)
  {
    Rainfall.InDelay--;
  }
  LPM3_EXIT;
  TACTL &= ~TAIFG;
}

/*******************************************************************************
�������ƣ�__interrupt void  PORT1_ISR(void) 
�������ܣ�P1�˿ڵ��жϷ����� ��ˮ������
�����������                              
���������ϵͳ��־�Ĵ���
����ֵ  ����
*******************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
  unsigned char counts=0;

  RESETWDT;                                     //��λ���Ź�  
  if((0==Rainfall.InDelay)&&Rainfall.Type)      //�����µ��ж������������ƽ���
  {
    if(P1IFG&(RAINPORT_1+RAINPORT_2))           //����ͨ��1������ͨ��2������һ·�����жϴ���
    {
      counts = 0;
      while(RAININ^(RAINPORT_1+RAINPORT_2))     //������Ч�Լ�� �豣��RAINTIME ms�ĵ͵�ƽ����
      {    
        if(counts++ >= RAINTIME)                //�Ƿ񱣳�RAINTIME ms�ĵ͵�ƽ
          break;
        delayms(1);
        RESETWDT;                               //��λ���Ź�      
      }
      if(counts >= RAINTIME)                    //����������Ч
      {        
        System.Event.Bit.Rain = SET;              //���������־��λ
        Rainfall.InDelay = RAINJG;              //��������������
        LPM3_EXIT;
      }
    }   
  } 
  P1IFG = 0x00;                                 //����жϱ�־
  return;
}


/*******************************************************************************
�������ƣ�__interrupt void  PORT2_ISR(void)
�������ܣ�P2�˿ڵ��жϷ����� ��������
�����������                              
�����������ֵ����
����ֵ  ����
*******************************************************************************/
#pragma vector=PORT2_VECTOR
__interrupt void  PORT2_ISR(void)
{  
  unsigned char counts=0;
        
  RESETWDT;                             //��λ���Ź�
  if(P2IFG & 0x3F)                      //��������
  {
    counts = 0;
    while(KEYIN ^ 0X3F)               //��ⰴ���Ƿ�Ϊ��Ч����
    {
      if(counts++ >= KEYINTIME) 
        break;
      delayms(1);
      RESETWDT;
    }
    if(counts >= KEYINTIME)           //����������Ч
    {
      System.Key = KEYIN;            //��ȡ��������
      System.Event.Bit.Key = SET;      //���������¼���λ
      Display.TiOFF = OFFLCDDELAY;    //��ʼ���ر���ʾ��ʱ
      LCD_LIGHT_ON;      //LCD�����
      Display.Status.Flag.Light = SET;
    }
  }
  LPM3_EXIT;
  P2IFG = 0x00;                       //����жϱ�־
  return;
}

