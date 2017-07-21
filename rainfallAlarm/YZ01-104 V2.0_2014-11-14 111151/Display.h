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

#define OFFLCDDELAY     50              //�ر���ʾ��ʱ

/*��ʾ״̬��Ϣ*/
typedef struct
{
  unsigned int TiOFF;                  //�ر���ʱ��ʱ
  char Mon;                            //��������
  union
  {
    char Register;
    struct
    {
      char Light       :1;     //����״̬
      char Power       :1;     //��Դ״̬
      char Mon         :1;     //������
      char Menu        :1;     //���ò˵�����
      char KeyOut      :1;     //�ȴ�������ʱ��־
      char OFFEvent    :1;     //��ʾ�ر��¼���־
      char SetMode     :1;     //����ģʽ
    }Flag;   
  }Status; 
}DisplayClass;

extern DisplayClass Display;

void LCDOFF(void);
void LCDON(void);     
      
void DisplayMon(void);
void DisBattery(char H,char Ver,char power);
void DisplayRunInfo(char *infostr);

void DisplayRainfall(void);

void DisplayMonData(void);
void DisplaySysTime(void);
void Battery(unsigned char H,unsigned char Ver, unsigned int dianya);
#endif  /*#ifndef __DISPLAY_H*/


