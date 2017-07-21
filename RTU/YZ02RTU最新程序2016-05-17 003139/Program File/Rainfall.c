#include "include.h"
#include "Rainfall.h"

RainfallClass Rainfall={0};

//���������ʼ��
void RainInit(void)
{
  RAIN_IES |=  RAINPORT_1+RAINPORT_2;                         //��������ѡ���½����ж�
  RAIN_IE  |=  RAINPORT_1+RAINPORT_2;                         //���ж�ʹ��
  RAIN_DIR &= ~(RAINPORT_1+RAINPORT_2);                       //��������I/OΪ����
  Rainfall.InDelay = 0;
}

void SysEventHandlers_Rain(void)
{
  System.Event.Bit.Rain = RESET;

  Rainfall.PN05 += Rainfall.Resolution; //��ˮ������
  Rainfall.PN10 += Rainfall.Resolution;
  Rainfall.PN30 += Rainfall.Resolution;
  Rainfall.PJ += Rainfall.Resolution;
  Rainfall.PT += Rainfall.Resolution;     
  if(Display.Status.Flag.Mon)
  {
    DisplayRainfall();
  }
  
  WriteUInt16(Rainfall.PT,EEPROM.PT);
  WriteUInt16(Rainfall.PJ,EEPROM.PJ);
  WriteUInt16(Rainfall.PN05,EEPROM.PN05);
  WriteUInt16(Rainfall.PN10,EEPROM.PN10);
  WriteUInt16(Rainfall.PN30,EEPROM.PN30);
}

/*��������*/
void RainfallClear(void)
{
  Rainfall.PN05 = 0;
  Rainfall.PN10 = 0;
  Rainfall.PN30 = 0;
  Rainfall.PJ = 0;
  Rainfall.PT = 0;
  WriteUInt16(Rainfall.PT,EEPROM.PT);
  WriteUInt16(Rainfall.PJ,EEPROM.PJ);
  WriteUInt16(Rainfall.PN05,EEPROM.PN05);
  WriteUInt16(Rainfall.PN10,EEPROM.PN10);
  WriteUInt16(Rainfall.PN30,EEPROM.PN30);
  InitDRP();
  SaveDRP();
}