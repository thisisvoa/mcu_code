#ifndef RTU_H_
#define RTU_H_
 
#include "MSP430_hardware.h"


#define JD1_ON                  P4DIR |= BIT1;_NOP();P4OUT |= BIT1;     //�򿪼̵���1
#define JD1_OFF                 P4DIR |= BIT1;_NOP();P4OUT &= ~BIT1;    //�رռ̵���2
#define JD2_ON                  P4DIR |= BIT0;_NOP();P4OUT |= BIT0;     //�򿪼̵���2
#define JD2_OFF                 P4DIR |= BIT0;_NOP();P4OUT &= ~BIT0;    //�رռ̵���2

#define PNC                     0                                       //����
#define PNO                     1                                       //����
#define PAUTO                   2                                       //�Զ�

#define Com0Write(x,y)          WriteUSART0(x,y)                        //�˿�0��������
#define Com1Write(x,y)          WriteUSART1(x,y)                        //�˿�1��������

#define Analog_4ma              740                                     //4maAD��ֵ
#define Analog_20ma             3718                                    //20maAD��ֵ
#define Analog_0V               0                                       //0V AD��ֵ
#define Analog_1V               1241                                    //1V AD��ֵ
#define Analog_2V               2482                                    //2V AD��ֵ

#define STYPE_4_20MA            0                                       //�����ź�4-20ma
#define STYPE_0_2V              1                                       //�����ź�0-2V

#define TONGDAO_1               6
#define TONGDAO_2               5
#define TONGDAO_3               7
#define TONGDAO_4               6

#define WMODE_1                 1                                       //�Ա�
#define WMODE_2                 2                                       //�Ա�ȷ��
#define WMODE_3                 3                                       //��ѯӦ��
#define WMODE_4                 4                                       //����ά��

#define YAOSULENG               11                                      //��ѡ���Ҫ�����ֵ

typedef struct
{
  long ShuiWeiJiZhi;
  long XiuZhengJiZhi;
  long qwater;
  unsigned int CaiYangJianGe;
  unsigned int CunChuJianGe;
  unsigned int WaterChaLiang;
  unsigned int Voltage; //��ѹ
  int Temp;             //�¶� 
  unsigned int Password;        //��������
  unsigned char ST[5];          //ң��վ��ַ BCD��洢
  unsigned char CenterAdd;      //����վ��ַ
  unsigned char RTUType;        //ң��վ������
  unsigned char DingShiBaoTime;
  unsigned char JiaBaoTime;
  unsigned char WorkMode;

}ClassRTUConfig;
 
/*ͨ�Ŷ˿����ݽṹ*/
typedef struct
{
  union
  {
    unsigned char value;                //״̬��־�Ĵ���
    struct
    {
      unsigned char Power       :1;     //��Դ״̬
      unsigned char Online      :1;     //����״̬
      unsigned char Close       :1;     //��Դ�ر�����     
      unsigned char Txd         :1;     //���ڷ����еȴ�Ӧ���־
      //unsigned char TxdTimeout  :1;     //���ͳ�ʱ��־
      unsigned char ComEvent    :1;     //ͨ���¼���־
      //unsigned char RxdSwitch   :1;     //���տ���
    }Flag;   
  }Status;
  unsigned char PowerType;              //��Դ�������� 0���� 1���� 2�Զ�
  unsigned char Com;                    //�˿ں�
  unsigned char bps;                    //������
  unsigned char Preheat;                //Ԥ��ʱ�� ��
  unsigned char TiPreheat;              //Ԥ�ȼ�ʱ
  unsigned char CloseDelay;             //�رյ�Դ��ʱʱ�� ��
  unsigned char TiClose;                //�رյ�Դ��ʱ
  unsigned char TxdMax;                 //����ط����� 
  unsigned char TxdCount;               //���ͼ���
  unsigned char TxdTime;                //��ʱ�ط�ʱ�� ��
  unsigned char TiTxdTime;              //��ʱ�ط�ʱ���ʱ

}ComPortClass;

/*ģ����ͨ��*/
typedef struct
{
  long Value;      //��ǰ��ֵ
  long Min;       //������Сֵ
  long Max;       //�������ֵ
  unsigned int ADValue;//AD��ֵ
  unsigned char Name;           //����Ҫ������
  unsigned char SType;          //�ź�����
   
}ClassAnalog;

/*�۲�Ҫ��*/
typedef struct
{
  unsigned char *NameStr;
  unsigned char DataType;
  unsigned char *Bzf;
}ClassYaoSuInfo;

/*typedef struct
{
  union
  {
    unsigned char Register;
    struct
    {
      unsigned char Event       :1;
      unsigned char Run         :1;
      unsigned char Ok          :1;
    }Bit;
  }Flag;
  unsigned char AFN;
}ClassCaiYang;*/

typedef struct
{
  unsigned char Event;
  unsigned char AFN;
}ClassCaiYang;

typedef struct
{
  unsigned char PT;
  unsigned char PJ;
  unsigned char PN05;
  unsigned char PN10;
  unsigned char PN30;
  unsigned char RainJBFZ;
  unsigned char RainJBSD;
  unsigned char PDTime;
  unsigned char RainType;
  unsigned char RainFBL;
  unsigned char RTUtype;
  unsigned char CenterAdd;
  unsigned char ST;
  unsigned char WorkMode;
  unsigned char DingShiBaoTime;
  unsigned char JiaBaoTime;
  unsigned char CaiYangJianGe;
  unsigned char CunChuJianGe;
  unsigned char ShuiWeiJiZhi;
  unsigned char XiuZhengJiZhi;
  unsigned char ComPowerType;
  unsigned char ComPreheat;
  unsigned char ComCloseDelay;
  unsigned char ComBps;
  unsigned char ComTxdTime;
  unsigned char TxdMax;
  unsigned char WaterChaLiang;
  unsigned char RS485Bps;
  unsigned char RS485PowerType;
  unsigned char RS485Preheat;
  unsigned char RS485CgqType;
  unsigned char RS485Name;
  unsigned char TD1name;
  unsigned char TD1stype;
  unsigned char TD1max;
  unsigned char TD1min;
  unsigned char TD2name;
  unsigned char TD2stype;
  unsigned char TD2max;
  unsigned char TD2min;
  unsigned char TD3name;
  unsigned char TD3stype;
  unsigned char TD3max;
  unsigned char TD3min;
  unsigned char TD4name;
  unsigned char TD4stype;
  unsigned char TD4max;
  unsigned char TD4min;
  unsigned char Page;
  unsigned char Bytes;
  unsigned char AnZhuangGaoDu;
}ClassEEPROM;

extern ClassRTUConfig RTU;
extern const ClassYaoSuInfo YaoSuInfo[];
extern ClassAnalog Analog1;
extern ClassAnalog Analog2;
//extern ClassAnalog Analog3;
//extern ClassAnalog Analog4;
extern const ClassEEPROM EEPROM;
extern ClassCaiYang CaiYang;
extern unsigned int Relvtive;

void TiTimeHandlers(void);
void AnalogCaiYang(void);
long int AnalogCalc(unsigned char type,unsigned int advalue,long int max,long int min);
void OperComPort(ComPortClass *Pcom);
void CloseComPort(ComPortClass *Pcom);
void CaiYangHandlers(void);
void DefaultConfig(void);
void WriteConfig(void);
void AddCaiYangTask(unsigned char afn);
void CaiYangOk(void);
#endif /*#ifndef RTU_H_*/