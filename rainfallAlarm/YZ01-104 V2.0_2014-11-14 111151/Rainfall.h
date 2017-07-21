//---------------------------------------------------------
//�ļ����ƣ�Rainfall.h
//ժ    Ҫ����ˮ��ģ������
//
//��    �ߣ�����
//��    ����1.0
//�޸����ڣ�2013��11��25��
//---------------------------------------------------------

#ifndef __RAINFALL_H
#define __RAINFALL_H

#define RAINPORT_1              BIT7                                    //����1����˿�
#define RAINPORT_2              BIT7                                    //����2����˿�
#define RAIN_IES                P2IES
#define RAIN_DIR                P2DIR
#define RAIN_IE                 P2IE
#define RAIN_IN                 P2IN
#define RAININ                  (RAIN_IN & (RAINPORT_1|RAINPORT_2))        //��������
#define RAIN_1                  (RAIN_IN & RAINPORT_1)                     //����ͨ��1����
#define RAIN_2                  (RAIN_IN & RAINPORT_2)                     //����ͨ��2����
#define RAINTIME                10                                      //������Ᵽ��ʱ�� x ms   �豣��x ms�ĵ͵�ƽ������������ж�Ϊ��Ч��
#define RAINJG                  1                                       //���������ź���Ч��� 0.5~1s



typedef struct
{
  //unsigned int Count;
  unsigned int PT;              //��ˮ���ۼ�ֵ       N(5,1)  ��λ ����  
  unsigned int PN05;            //5���� ʱ�ν�ˮ��   N(5,1)
  unsigned int PN10;            //10����ʱ�ν�ˮ��   N(5,1)
  unsigned int PN30;            //30����ʱ�ν�ˮ��   N(5,1) 
  unsigned int P1;
  unsigned int P3;
  unsigned int P6;
  unsigned int P12;
  unsigned int P24;
  unsigned int PJ;              //��ǰ��ˮ��
  unsigned int P;
  char Resolution;     //�ֱ���
  char InDelay;        //������
}RainfallClass;

extern RainfallClass Rainfall;
extern char RainArray[288];

void RainInit(void);
void SysEventHandlers_Rain(void);
void RainfallClear(void);
void IniRainArray(char value);
void RainArrayRefresh(void);
unsigned int GetRain(unsigned int x);

#endif  /*#ifndef __RAINFALL_H*/