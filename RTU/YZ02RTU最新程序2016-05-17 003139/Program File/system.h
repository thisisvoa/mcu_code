#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Public.h"

#define Model                   "YZ02-101 V3.0"
#define Version                 "V1.2_20170721"

#define DEBUG                   0                       //���Եȼ�
#define SET                     1                       //��λ 
#define RESET                   0                       //��λ

#define KEYIN                   (P2IN & 0X3F)                           //��������
#define KEYINTIME               20                                      //�������뱣��ʱ�� x ms
//��ֵ����
/*#define Esc	                0X1F                                    //����
#define Up	                0X37                                    //��
#define Down	                0X3B                                    //��
#define Left	                0X2F                                    //��
#define Right	                0X3D                                    //��
#define Enter	                0X3E                                    //ȷ��
#define Esc_Up                  0X17                                    //����+��
#define Esc_Enter               0X1E                                    //����+ȷ��*/

#define Esc	                0X3E                                    //����
#define Up	                0X3B                                    //��
#define Down	                0X37                                    //��
#define Left	                0X3D                                    //��
#define Right	                0X2F                                    //��
#define Enter	                0X1F                                    //ȷ��
#define Esc_Up                  0X3A                                    //����+��
#define Esc_Enter               0X1E                                    //����+ȷ��



typedef struct                  
{ 
  union                         //ϵͳ�¼��Ĵ���
  {
    unsigned int Register;
    struct
    {
      unsigned char Second        :1;//1�붨ʱ
      unsigned char Minute        :1;//1���Ӷ�ʱ
      unsigned char Hour          :1;//���㶨ʱ
      unsigned char UART0BYTE     :1;//�յ�1byte
      unsigned char UART1BYTE     :1;
      unsigned char UART0         :1;
      unsigned char UART1         :1;
      unsigned char Rain          :1;//��������
      unsigned char Key           :1;//��������
      unsigned char Flash         :1;//��ȡ��ʷ����
    }Bit;
  }Event;
  DataTime Time;                        //ϵͳ����ʱ��
  unsigned char Key;                    //��ֵ���� 
  
}ClassSystem;

typedef union
{
  unsigned int Register;
  struct
  {
    unsigned char RTC   :1;
    unsigned char EROM  :1;
    unsigned char Flash :1;
    
  }Bit;
}ClsaaSysError;


extern ClassSystem System;
extern ClsaaSysError SysError;


void SysInitHandlers(void);
void SysTimePlue(void);
void SysEventHandlers(void);
void SysEventHandlers_Second(void);
void SysEventHandlers_Minute(void);
void SysEventHandlers_Hour(void);
void SysEventHandlers_UART0_Rxd(void);
void SysEventHandlers_UART1_Rxd(void);
void SysEventHandlers_Key(void);
void UserEventHandlers(void);

void ICInit(void);
void ReadSysConfig(void);
void RestorationData(void);
void PeripheralsInit(void);
void SystemSelfTest(void);

#endif  /*#ifndef SYSTEM_H_*/