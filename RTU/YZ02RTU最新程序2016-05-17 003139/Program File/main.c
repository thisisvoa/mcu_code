#include "include.h"


main()
{
  // Stop watchdog timer to prevent time out reset
  
  WDTCTL = WDTPW + WDTHOLD;
  
  SysInitHandlers();            //ϵͳ��ʼ��

  while(1)
  {
    RESETWDT;                   //��λ���Ź�
 
    SysEventHandlers();         //ϵͳ�¼����� 
    
    UserEventHandlers();        //������ 
    
    if(Display.Status.Flag.SetMode)
    {
      SetMode(); 
    }
    
    if(System.Event.Bit.Flash)
    {
      System.Event.Bit.Flash = RESET;
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
 
