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

#define RAINPORT_1              BIT6                                    //����1����˿�
#define RAINPORT_2              BIT5                                    //����2����˿�
#define RAIN_IES                P1IES
#define RAIN_DIR                P1DIR
#define RAIN_IE                 P1IE
#define RAIN_IN                 P1IN
#define RAININ                  (RAIN_IN & (RAINPORT_1+RAINPORT_2))        //��������
#define RAIN_1                  (RAIN_IN & RAINPORT_1)                     //����ͨ��1����
#define RAIN_2                  (RAIN_IN & RAINPORT_2)                     //����ͨ��2����
#define RAINTIME                10                                      //������Ᵽ��ʱ�� x ms   �豣��x ms�ĵ͵�ƽ������������ж�Ϊ��Ч��
#define RAINJG                  2                                       //���������ź���Ч��� 0.5~1s


typedef struct
{
  unsigned int PT;              //��ˮ���ۼ�ֵ       N(5,1)  ��λ ����  
  unsigned int PJ;              //��ǰ��ˮ��
  unsigned int PN05;            //5���ӽ�ˮ��
  unsigned int PN10;            //10���ӽ�ˮ��
  unsigned int PN30;            //30���ӽ�ˮ��
  unsigned int JBFZ;            //�ӱ���ֵ
  unsigned char YLJBSD;         //��ˮ���ӱ���ʽ/ʱ��
  unsigned char PDTime;         //��ˮ������ʼʱ��0~23
  unsigned char Type;           //����������         0δ�� 1 ����ʽ������
  unsigned char Resolution;     //�ֱ���
  unsigned char InDelay;        //������
}RainfallClass;

extern RainfallClass Rainfall;

void RainInit(void);
void SysEventHandlers_Rain(void);
void RainfallClear(void);

#endif  /*#ifndef __RAINFALL_H*/