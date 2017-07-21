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
  P2IES |=  BIT0 + BIT1 + BIT6 + BIT3 + BIT4 + BIT5;            //ѡ���½����ж�
  P2IE  |=  BIT0 + BIT1 + BIT6 + BIT3 + BIT4 + BIT5;            //���ж�ʹ��
  P2DIR &= ~(BIT0 + BIT1 + BIT6 + BIT3 + BIT4 + BIT5);          //���ð����ӿ�Ϊ����
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
void GotimeDfB(char doit)
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
  unsigned int counts=0;
  RESETWDT;                             //��λ���Ź�
  if(P1IFG & BIT5)                      //P2�ж�����
  {
    counts = 0;
    while((P1IN&BIT5) ^ BIT5)    //���������Ч��
    {
      if(counts++ >= KEYINTIME) 
        break;
      delayms(1);
      RESETWDT;
    }
    if(counts >= KEYINTIME) 
    {
      if(0==Rainfall.InDelay)
      {
        System.Event.Bit.Rain = SET;          //���������־��λ
        Rainfall.InDelay = RAINJG;           //��������������
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
 unsigned int counts=0;
        
  RESETWDT;                             //��λ���Ź�
  if(P2IFG & BIT7)
  {
    counts = 0;
    while((P2IN&BIT7) ^ BIT7)    //���������Ч��
    {
      if(counts++ >= KEYINTIME) 
        break;
      delayms(1);
      RESETWDT;
    }
    if(counts >= KEYINTIME) 
    {
      if(0==Rainfall.InDelay)
      {
        System.Event.Bit.Rain = SET;          //���������־��λ
        Rainfall.InDelay = RAINJG;           //��������������
        LPM3_EXIT;
      }          
    }  
  }
  else
  {
    counts = 0;
    while((P2IN&(BIT0+BIT1+BIT3+BIT4+BIT5+BIT6) ^ (BIT0+BIT1+BIT3+BIT4+BIT5+BIT6)))    //���������Ч��
    {
      if(counts++ >= KEYINTIME) 
        break;
      delayms(1);
      RESETWDT;
    }
    if(counts >= KEYINTIME)  
    {
      System.Key = KEYIN;            //��ȡ��������    

      Display.TiOFF = OFFLCDDELAY;    //��ʼ���ر���ʾ��ʱ          
      System.Event.Bit.Key = SET;      //���������¼���λ 
      LPM3_EXIT;  
    }
  }
  /*if(P2IFG & (~BIT2))                      //P2�ж�����
    {
      counts = 0;
      while((P2IN&(~BIT2)) ^ (~BIT2))    //���������Ч��
      {
        if(counts++ >= KEYINTIME) 
          break;
        delayms(1);
        RESETWDT;
      }
      if(counts >= KEYINTIME)           //������Ч
      {       
        if(RAININ^RAINPORT_1)           //��������
        {
          if(0==Rainfall.InDelay)
          {
            System.Event.Bit.Rain = SET;          //���������־��λ
            Rainfall.InDelay = RAINJG;          //��������������
          }            
        }
        else if(KEYIN^(~(BIT2|BIT7)))      //��������
        {
          System.Key = KEYIN;            //��ȡ��������    
          UART_printf(0,"Key: %x \r\n",System.Key);
          Display.TiOFF = OFFLCDDELAY;    //��ʼ���ر���ʾ��ʱ          
          System.Event.Bit.Key = SET;      //���������¼���λ     
        }      
      }     
    }*/
    //LPM3_EXIT;
    P2IFG = 0x00;                       //����жϱ�־
    return;
}

/********************************************************************** 
���������жϺ���
***********************************************************************/ 
#pragma vector=NMI_VECTOR 
__interrupt void Nmi() 
{ 
//����Ϊ�ο�������򣬲�ʹ�õ��ж�ԴӦ��ɾ��
  if((IFG1&OFIFG)==OFIFG) 
  { 
    //����ʧЧ
    IFG1 &= ~OFIFG; 
    WDTCTL = 0;         //��λ
  } 
  /*else if((IFG1&NMIIFG)==NMIIFG) 
  { 
    //RST/NMI���������ж�
    IFG1 &= ~NMIIFG; 
  
  } 
  else if((FCTL3&ACCVIFG)==ACCVIFG) 
  { 
    //�洢���Ƿ�����
    FCTL3 &= ~ACCVIFG; 
  
  } */
  //LPM3_EXIT; //�˳��жϺ��˳��͹���ģʽ�����˳��жϺ�Ҫ�����͹���ģʽ������������
} 
