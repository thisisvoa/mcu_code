#include "include.h"

main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P3DIR &=~BIT1+~BIT3;
  P3OUT |=BIT0;
  SC_RST_OUT; 
  SC_DATA_OUT;
  _NOP();
  SC_DATA_0;     							 //���������
  SC_RST_1;     							 //��λ�����
  delayus(20);                    		                         //��ʱ100US
  SC_RST_0;     							 //��λ�����
  delayus(20); 							         //��ʱ100US 
  SC_RST_IN;
  SC_DATA_IN;
  
  SysInitHandlers();  
  while(1)
  {
    RESETWDT;                   //��λ���Ź�
    SysEventHandlers();         //ϵͳ�¼�����
    UserEventHandlers();        //������ 

    if(Display.Status.Flag.SetMode)
    {
      SetMode();
    }

    if(0==System.Event.Register)//���¼�����LPM3
    {
      RESETWDT;                 //��λ���Ź�
      _NOP();
      LPM3;
      _NOP();
    }
  }
}

