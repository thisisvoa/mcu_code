#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Public.h"

#define DEBUG                   0                       //���Եȼ�
#define SET                     1                       //��λ 
#define RESET                   0                       //��λ

#define KEYIN                   (P2IN & (~(BIT2|BIT7)))                           //��������
#define KEYINTIME               10                                      //�������뱣��ʱ�� x ms
//��ֵ����
#define Esc	                0X5B                    //����
#define Up	                0X73                    //��
#define Down	                0X79                    //��
#define Left	                0X6B                    //��
#define Right	                0X7A                    //��
#define Enter	                0X3B                    //ȷ��


typedef struct                  
{ 
  union                         //ϵͳ�¼��Ĵ���
  {
    unsigned int Register;
    struct
    {
      char Second        :1;//1�붨ʱ
      char Minute        :1;//1���Ӷ�ʱ
      char Hour          :1;//���㶨ʱ
      char UART0BYTE     :1;//�յ�1byte
      char UART1BYTE     :1;
      char UART0         :1;//�յ�һ��
      char UART1         :1;
      char Rain          :1;//��������
      char Key           :1;//��������
      char Flash         :1;//��ȡ��ʷ����
    }Bit;
  }Event;
  unsigned int Voltage;                      //��Դ��ѹ
  int Temp;                         //�¶�
  DataTime Time;                        //ϵͳ����ʱ��
  char Key;                    //��ֵ���� 
  
}ClassSystem;

typedef union
{
  unsigned int Register;
  struct
  {
    char RTC   :1;
    char EROM  :1;
    char Flash :1;
    
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
void TiTimeHandlers(void);


#endif  /*#ifndef SYSTEM_H_*/