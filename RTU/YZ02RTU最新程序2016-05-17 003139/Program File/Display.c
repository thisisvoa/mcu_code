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
  
}

void LCDON(void)
{
  Ini_Lcd();                    //��ʾ�豸��ʼ��  
  DisplayMon();      //��ʾ������
  Display.TiOFF = OFFLCDDELAY;  //��ʼ���رռ�ʱ
}

void DisplayRunInfo(unsigned char *infostr)
{
  if(Display.Status.Flag.Mon)
  {
    Draw(0,48,8,16,0,0);
    DisplayString(0,48,infostr,0);
  }
}

/**************************************************************
�������ƣ�void DisplayNum(unsigned char H,unsigned char Ver,long int value,
                unsigned char type,unsigned char cmd,unsigned char *s,unsigned char fb)
�������ܣ���ʾ����
���������unsigned char H---->ˮƽ����
          unsigned char Ver--->��ֱ����
          long int value------>��ʾ������
          unsigned char type-->��������
          unsigned char cmd--->����ת������
          unsigned char *s---->��������ʾ����β�����ַ��� ��󳤶�Ϊ4
          unsigned int fb---->���Կ���
�����������
����ֵ  ����           
***************************************************************/
void DisplayNum(unsigned char H,unsigned char Ver,long int value,
                unsigned char type,unsigned char cmd,unsigned char *s,unsigned int fb)
{
  unsigned char strtmep[16]={0};
  unsigned char i=0,j=0;
   
  i = SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
  for(j=0;j<10;j++)//��ʾ���ֵ�β��������Ҫ��ʾ���ַ���
  {
    if(s[j]=='\0')
      break;
    strtmep[i++] = s[j];
  }
    
  DisplayString(H,Ver,strtmep,fb);
}

/**************************************************************
�������ƣ�void DisplayNum8X6(unsigned char H,unsigned char Ver,long int value,
                unsigned char type,unsigned char cmd,unsigned char *s)
�������ܣ���ʾ����8X6
���������unsigned char H---->ˮƽ����
          unsigned char Ver--->��ֱ����
          long int value------>��ʾ������
          unsigned char type-->��������
          unsigned char cmd--->����ת������
          unsigned char *s---->��������ʾ����β�����ַ��� ��󳤶�Ϊ4
�����������
����ֵ  ����           
***************************************************************/
void DisplayNum8X6(unsigned char H,unsigned char Ver,long int value,
                unsigned char type,unsigned char cmd,unsigned char *s)
{
  unsigned char strtmep[16]={0};
  unsigned char i=0,j=0;
   
  i = SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
  for(j=0;j<4;j++)
  {
    if(s[j]=='\0')
      break;
    strtmep[i++] = s[j];
  } 
  Display_8x6(H,Ver,strtmep);
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
  if(Display.Mon > 4)
    Display.Mon = 1;
  if(Display.Mon < 1)
    Display.Mon = 4;
  
  Draw(0,0,16,48,0,0);                        //��������Ϣ��ʾ��

  if(1 == Display.Mon)
  {
    DisplayString(0,0," 5���ӽ�",0);
    DisplayString(0,16,"10���ӽ�",0);
    DisplayString(0,32,"30���ӽ�",0);
    DisplayRainfall();
  }
  else if(2 == Display.Mon)
  {
    DisplayString(0,0," ��ǰ��",0);
    DisplayString(0,16," �ۼƽ�",0);
    //DisplayString(0,32,YaoSuInfo[RS485.Name].NameStr,0);
    DisplayRainfall();
    /*if(0==RS485.Name)
    {
      DisplayString(8,32,"-------",0);
    }
    else
    {
      DisplayNum(15-(YaoSuInfo[RS485.Name].DataType>>4),32,RS485.Value,YaoSuInfo[RS485.Name].DataType,space,"",0);
    }*/
  }
  else if(3 == Display.Mon)
  {
    DisplayString(0,0,YaoSuInfo[Analog1.Name].NameStr,0);
    DisplayString(0,16,YaoSuInfo[Analog2.Name].NameStr,0);
    //DisplayString(0,32,YaoSuInfo[Analog3.Name].NameStr,0);
    DisplayString(0,32,YaoSuInfo[RS485.Name].NameStr,0);
    DisplayAnalogData();
  }
  else if(4 == Display.Mon)
  {
    //DisplayString(0,0,YaoSuInfo[Analog4.Name].NameStr,0);
    DisplayString(0,16,"��Դ��ѹ",0);
    DisplayString(0,32,"�豸�¶�",0);
    DisplayMonData();                   //��ʾ�������
  }
  DisplaySysTime();                      //��ʾʱ��
  Display.Status.Flag.Mon = SET;         //�������־��λ
  Display.Status.Flag.Menu = RESET;      //�˵������־��λ
  
}

 

void DisplaySysTime(void)
{
  //unsigned char daystring[11]={"00-00-00"};
  unsigned char timestring[9]={"00:00:00"};
  
  /*daystring[0] = HEXASCII[System.Time.Year/10];
  daystring[1] = HEXASCII[System.Time.Year%10];
  daystring[3] = HEXASCII[System.Time.Month/10];
  daystring[4] = HEXASCII[System.Time.Month%10];
  daystring[6] = HEXASCII[System.Time.Day/10];
  daystring[7] = HEXASCII[System.Time.Day%10];*/
  
  timestring[0] = HEXASCII[System.Time.Hour/10];
  timestring[1] = HEXASCII[System.Time.Hour%10];
  timestring[3] = HEXASCII[System.Time.Minute/10];
  timestring[4] = HEXASCII[System.Time.Minute%10];
  timestring[6] = HEXASCII[System.Time.Second/10];
  timestring[7] = HEXASCII[System.Time.Second%10];
  //Display_8x6(10,48,daystring);
  Display_8x6(10,56,timestring);
}
/*��ʾ������*/
void DisplayRainfall(void)
{
  if(1==Display.Mon)
  {
    DisplayNum(9,0,Rainfall.PN05,0X51,space,"",0);
    DisplayNum(9,16,Rainfall.PN10,0X51,space,"",0);
    DisplayNum(9,32,Rainfall.PN30,0X51,space,"",0);
  }
  else if(2==Display.Mon)
  {
    DisplayNum(9,0,Rainfall.PJ,0X51,space,"",0);
    DisplayNum(9,16,Rainfall.PT,0X51,space,"",0);
  }
}

void DisplayAnalogData(void)
{
  if(0==Analog1.Name)
  {
    DisplayString(8,0,"-------",0);
  }
  else
  {
    DisplayNum(15-(YaoSuInfo[Analog1.Name].DataType>>4),0,Analog1.Value,YaoSuInfo[Analog1.Name].DataType,space,"",0);
  }
  if(0==Analog2.Name)
  {
    DisplayString(8,16,"-------",0);
  }
  else
  {
    DisplayNum(15-(YaoSuInfo[Analog2.Name].DataType>>4),16,Analog2.Value,YaoSuInfo[Analog2.Name].DataType,space,"",0);
  }
  /*if(0==Analog3.Name)
  {
    DisplayString(8,32,"-------",0);
  }
  else
  {
    DisplayNum(15-(YaoSuInfo[Analog3.Name].DataType>>4),32,Analog3.Value,YaoSuInfo[Analog3.Name].DataType,space,"",0);
  }*/
  if(0==RS485.Name)
  {
    DisplayString(8,32,"-------",0);
  }
  else
  {
    DisplayNum(15-(YaoSuInfo[RS485.Name].DataType>>4),32,RS485.Value,YaoSuInfo[RS485.Name].DataType,space,"",0);
  }
  
}
void DisplayMonData(void)
{
  /*if(0==Analog4.Name)
  {
    DisplayString(8,0,"-------",0);
  }
  else
  {
    DisplayNum(15-(YaoSuInfo[Analog4.Name].DataType>>4),0,Analog4.Value,YaoSuInfo[Analog4.Name].DataType,space,"",0);
  }*/
  DisplayNum(9,16,RTU.Voltage,0X42,space,"",0);    //��ʾ��Դ��ѹ 
  DisplayNum(9,32,RTU.Temp,0X31,space,"",0);       //��ʾ�豸�¶�
}


/***************************************************************
                    ������ʾ
X�ķ�Χ0-10�����ܵ�����Ϊ10�ȷ���ʾ��0��ʾ�յ�����10��ʾ����
x>10��ʾ���ϡ�
****************************************************************/
/*void DisBattery(unsigned char H,unsigned char Ver, unsigned char power)
{
  unsigned int a[3]={0x1ffe,0x7002,0x5002};    //�յ�����ʾ����
  unsigned int temp;
  unsigned char i;
  unsigned char xadd,yadd;
  
  temp=0x0002;
      
  for(i=0;i<power;i++)                                //������ʾ���ݴ���
  { 
    temp <<= 1;                                       //����ÿ����һ������ʾ���ݴӵ�λ����λ������λ
    temp |= 0x0002;                                   //��ʾ�ұ߽籣��
  }
  
  a[1] |= temp;                                       //��ʾ��߽籣��
  a[2] |= temp;
  
  if(Voltage < 100 || Voltage > 1500)                  //��ѹ������Χ  1v < x < 15v ��ʾ����
  {
    a[1] = 0x7122;                                    //������ʾ����
    a[2] = 0x50C2;
  } 
  
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
}*/

