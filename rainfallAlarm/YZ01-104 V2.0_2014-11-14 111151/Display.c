/*********************************************************
*�ļ����ƣ�Display.c
*ժ    Ҫ����ʾ���ܺ���
*
*��    �ߣ�����
*��ʼ���ڣ�2013��4��16��
*������ڣ�
**********************************************************/
#include "Display.h"
#include "include.h"

DisplayClass Display={0};

void LCDOFF(void)
{
  ClearScreen;                  //���� 
  LCD_POWER_OFF;                
  LCD_LIGHT_OFF;                //LCD�����
  Display.Status.Register = 0;  //��ʾ״̬�Ĵ�������
  LCD_DataIn;
  LCD_CMIn;
  delayms(500);
  System.Key = 0;
  System.Event.Bit.Key = RESET;
  StopU0();
}
 
void LCDON(void)
{
  Ini_Lcd();                    //��ʾ�豸��ʼ��  
  DisplayMon();                 //��ʾ������
  Display.TiOFF = OFFLCDDELAY;  //��ʼ���رռ�ʱ
}

void DisplayRunInfo(char *infostr)
{
  if(Display.Status.Flag.Mon)
  {
    Draw(0,48,8,16,0,0);
    DisplayString(0,48,infostr,0);
  }
}


/*******************************************************************************
�������ƣ�void DisplayMon(void) 
�������ܣ���ʾ������
�����������                             
�����������
����ֵ  ����
*******************************************************************************/
void DisplayMon(void)
{ 
  if(Display.Mon > 5)
    Display.Mon = 1;
  if(Display.Mon < 1)
    Display.Mon = 5;
  
  Display.Status.Flag.Mon = SET;         //�������־��λ
  Display.Status.Flag.Menu = RESET;      //�˵������־��λ
  //Draw(0,0,16,48,0,0);                        //��������Ϣ��ʾ��
  ClearScreen;
  if(0==Rainfall.PN30)
  {
    Draw(0,0,2,16,0,qingtian);
  }
  else
  {
    DisplayString(0,0,"��",0);
  } 
  if(AlarmMode.Status.Flag.Run)
  {
    Draw(2,0,2,16,0,baojing);
  }
  if(LI==AlarmLevel.Level)
  {
    DisplayString(4,0,"����ת��",0);
  }
  else if(LII==AlarmLevel.Level)
  {
    DisplayString(4,0,"׼��ת��",0);
  }
  else if(LIII==AlarmLevel.Level)
  {
    DisplayString(4,0,"���䱨��",0);
  }

  if(1 == Display.Mon)
  {
    DisplayString(0,16," 5���ӽ�",0);     //��ʾ������ʾ             
    DisplayString(0,32,"10���ӽ�",0);  
    DisplayString(0,48,"30���ӽ�",0);
    DisplayRainfall();
  }
  else if(2 == Display.Mon)
  {
    DisplayString(0,16," 1Сʱ��",0);
    DisplayString(0,32," 3Сʱ��",0);
    DisplayString(0,48," 6Сʱ��",0);
    DisplayRainfall();
  }
  else if(3 == Display.Mon)
  {     
    DisplayString(0,16,"12Сʱ��",0);
    DisplayString(0,32,"24Сʱ��",0);
    DisplayString(0,48,"  ���ս�",0);
    DisplayRainfall();
  }
  else if(4 == Display.Mon)
  {
    DisplayString(0,16,"������",0);
    DisplayString(0,32,"�ۼƽ�",0);
    DisplayRainfall();
  }
  else if(5 == Display.Mon)
  {
    DisplayString(0,16,"��Դ��ѹ",0);
    DisplayString(0,32,"�豸�¶�",0);
    DisplayMonData();                   //��ʾ�������
  }
  Battery(14,0,System.Voltage);            //��ʾ���
  DisplaySysTime();

}

/*��ʾ������*/
void DisplayRainfall(void)
{
  if(Display.Status.Flag.Mon&&Display.Mon<5)
  {
    if(0==Rainfall.PN30)
    {
      Draw(0,0,2,16,0,qingtian);
    }
    else
    {
      DisplayString(0,0,"��",0);
    } 
    if(1==Display.Mon)
    {
      DisplayNum(8,16,Rainfall.PN05,0X51,space,"mm",AlarmValueif(&Alarm.PN05,Rainfall.PN05));
      DisplayNum(8,32,Rainfall.PN10,0X51,space,"mm",AlarmValueif(&Alarm.PN10,Rainfall.PN10));
      DisplayNum(8,48,Rainfall.PN30,0X51,space,"mm",AlarmValueif(&Alarm.PN30,Rainfall.PN30));
    }
    else if(2==Display.Mon)
    {
      DisplayNum(8,16,Rainfall.P1,0X51,space,"mm",AlarmValueif(&Alarm.P1,Rainfall.P1));
      DisplayNum(8,32,Rainfall.P3,0X51,space,"mm",AlarmValueif(&Alarm.P3,Rainfall.P3));
      DisplayNum(8,48,Rainfall.P6,0X51,space,"mm",AlarmValueif(&Alarm.P6,Rainfall.P6));
    }
    else if(3==Display.Mon)
    {
      DisplayNum(8,16,Rainfall.P12,0X51,space,"mm",AlarmValueif(&Alarm.P12,Rainfall.P12));
      DisplayNum(8,32,Rainfall.P24,0X51,space,"mm",AlarmValueif(&Alarm.P24,Rainfall.P24));
      DisplayNum(8,48,Rainfall.PJ,0X51,space,"mm",AlarmValueif(&Alarm.PJ,Rainfall.PJ));
    }
    else if(4==Display.Mon)
    {
      DisplayNum(8,16,Rainfall.P,0X51,space,"mm",AlarmValueif(&Alarm.P,Rainfall.P));
      DisplayNum(8,32,Rainfall.PT,0X51,space,"mm",AlarmValueif(&Alarm.PT,Rainfall.PT));
    }
  }
}

void DisplayMonData(void)
{
  if(Display.Status.Flag.Mon&&(Display.Mon==5))
  {
    System.Voltage = GetVcc();
    DisplayNum(9,16,System.Voltage,0X42,space,"V",0);          //��ʾ��Դ��ѹ 
    DisplayNum(9,32,System.Temp,0X31,space,"��",0);     //��ʾ�豸�¶�
  }
}

void DisplaySysTime(void)
{
  char timestring[6]={'0','0',':','0','0','\0'};
  
  timestring[0] = HEXASCII[System.Time.Hour/10];
  timestring[1] = HEXASCII[System.Time.Hour%10];
  timestring[3] = HEXASCII[System.Time.Minute/10];
  timestring[4] = HEXASCII[System.Time.Minute%10];

  Display_8x6(12,7,timestring);
}


void Battery(unsigned char H,unsigned char Ver, unsigned int dianya)
{
  unsigned char level=0;
  unsigned char i=0;
  unsigned int val=370;
  
  for(i=0;i<10;i++)                    
  {
    if(dianya > val)
    {
      val += 4;
    }
    else break;
  }
  level=i;   
  
  DisBattery(H,Ver,level);
}

/***************************************************************
                    ������ʾ
X�ķ�Χ0-10�����ܵ�����Ϊ10�ȷ���ʾ��0��ʾ�յ�����10��ʾ����
x>10��ʾ���ϡ�
****************************************************************/
void DisBattery(char H,char Ver,char power)
{
  unsigned int a[3]={0x1ffe,0x7002,0x5002};    //�յ�����ʾ����
  unsigned int temp;
  char i;
  char xadd,yadd;
  
  temp=0x0002;
      
  for(i=0;i<power;i++)                                //������ʾ���ݴ���
  { 
    temp <<= 1;                                       //����ÿ����һ������ʾ���ݴӵ�λ����λ������λ
    temp |= 0x0002;                                   //��ʾ�ұ߽籣��
  }
  
  a[1] |= temp;                                       //��ʾ��߽籣��
  a[2] |= temp;
  
 /* if(Sys.Voltage < 100 || Sys.Voltage > 700)                  //��ѹ������Χ  1v < x < 7v ��ʾ����
  {
    a[1] = 0x7122;                                    //������ʾ����
    a[2] = 0x50C2;
  } */
  
  Coordinate(H,Ver,&xadd,&yadd);//��ȡ��ͼ��ʼ����
  
  for(i=0;i<6;i++)                                  //����д��8��
  {
    ST7920WriteCmd(yadd);    			// дY����
    ST7920WriteCmd(xadd);       			// дX����  
    
    if((H % 2) == 1 )                     // ˮƽ����Ϊ����д��հ�
    {         
      ST7920WriteData(0x00);
    }   
     yadd++;
        
    if(yadd > 0X9F)
    {
      xadd -= 8;
      yadd = 0X80;
    }        
    else if((yadd > 0X8F) && (xadd <= 0X8F))
    {
      xadd += 16;
    }                
    //дˮƽ����
    if(i==0 || i==5)                                //д��0�����7��ʱ��д����ͬ���ݣ����±߽磩
    {
      ST7920WriteData(a[0] >> 8);                   //��ʾ���ݸ�8λ
      ST7920WriteData(a[0] & 0x00ff);               //��ʾ���ݵ�8λ
      continue;                                     //��������ѭ��
    }
    if(i < 3)                                       //��ʾ�ϰ벿�֣����²��ֶԳƣ�
    {
      ST7920WriteData(a[i] >> 8);
      ST7920WriteData(a[i] & 0x00ff);
    }
    else                                            //��ʾ�°벿��
    {
      ST7920WriteData(a[5-i] >> 8);
      ST7920WriteData(a[5-i] & 0x00ff);
    }
  }
}