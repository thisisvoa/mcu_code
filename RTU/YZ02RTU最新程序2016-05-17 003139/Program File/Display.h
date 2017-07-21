/*********************************************************
*�ļ����ƣ�Display.h
*ժ    Ҫ����ʾ���ܺ�������
*
*��    �ߣ�����
*��ʼ���ڣ�2013��4��16��
*������ڣ�
**********************************************************/

#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "ST7920.h"
#include "Public.h"

#define OFFLCDDELAY     100              //�ر���ʾ��ʱ

/*��ʾ״̬��Ϣ*/
typedef struct
{
  unsigned int TiOFF;                  //�ر���ʱ��ʱ
  unsigned char Mon;                            //��������
  union
  {
    unsigned char Register;
    struct
    {
      unsigned char Light       :1;     //����״̬
      unsigned char Power       :1;     //��Դ״̬
      unsigned char Mon         :1;     //������
      unsigned char Menu        :1;     //���ò˵�����
      unsigned char KeyOut      :1;     //�ȴ�������ʱ��־
      unsigned char OFFEvent    :1;     //��ʾ�ر��¼���־
      unsigned char SetMode     :1;     //����ģʽ
    }Flag;   
  }Status; 
}DisplayClass;

extern DisplayClass Display;

void LCDOFF(void);
void LCDON(void);     
      
void BootDisplay(void);

void DisplayNum(unsigned char H,unsigned char Ver,long int value,unsigned char type,
                unsigned char cmd,unsigned char *s,unsigned int fb);

void DisplayNum8X6(unsigned char H,unsigned char Ver,long int value,
                unsigned char type,unsigned char cmd,unsigned char *s);

void DisplaySysTime(void);

void DisplayMon(void);
void DisBattery(unsigned char H,unsigned char Ver, unsigned char power);
void DisplayRunInfo(unsigned char *infostr);

void DisplayRainfall(void);
void DisplayAnalogData(void);
void DisplayMonData(void);

#endif  /*#ifndef __DISPLAY_H*/


