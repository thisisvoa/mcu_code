/*********************************************************
*�ļ����ƣ�CPASCII.h
*ժ    Ҫ��ͨ��Э��༭��������
*
*��ǰ�汾��1.0
*��    �ߣ�����
*��ʼ���ڣ�2013��09��02��
*������ڣ�
**********************************************************/
#ifndef __CPASCII_H
#define __CPASCII_H


/**************************�����ַ�����**************************************/
#define         SOH             0X01            //֡��ʼ
#define         STX             0X02            //����������ʼ
#define         SYN             0X16            //�������������
#define         ETX             0X03            //���Ľ����������ޱ���
#define         ETB             0X17            //���Ľ����������б���
#define         ENQ             0X05            //ѯ��
#define         EOT             0X04            //����������˳�
#define         ACK             0X06            //�϶�ȷ�ϣ���������
#define         NAK             0X15            //��Ӧ�𣬷����ط�
#define         ESC             0X1B            //����������ն˱�������
/**************************ң��վ������***************************************/
#define         RTUTYPE_JS      'P'             //ң��վ������ ��ˮ 
#define         RTUTYPE_HD      'H'             //ң��վ������ �ӵ� 
#define         RTUTYPE_SK      'K'             //ң��վ������ ˮ�⣨������
#define         RTUTYPE_ZB      'Z'             //ң��վ������ բ��
#define         RTUTYPE_BZ      'D'             //ң��վ������ ��վ
#define         RTUTYPE_CX      'T'             //ң��վ������ ��ϫ
#define         RTUTYPE_SQ      'M'             //ң��վ������ ����
#define         RTUTYPE_DXS     'G'             //ң��վ������ ����ˮ
#define         RTUTYPE_SZ      'Q'             //ң��վ������ ˮ��
#define         RTUTYPE_QSK     'I'             //ң��վ������ ȡˮ��
#define         RTUTYPE_PSK     'O'             //ң��վ������ ��ˮ��
/****************************�����붨��***************************************/
#define         GNM_LLWC        0X2F            //��·ά�ֱ�
#define         GNM_CSB         0X30            //���Ա�
#define         GNM_JYSD        0X31            //����ʱ��ˮ����Ϣ��
#define         GNM_DSB         0X32            //ң��վ��ʱ��
#define         GNM_JBB         0X33            //ң��վ�ӱ���
#define         GNM_XSB         0X34            //ң��վСʱ��
#define         GNM_RGZS        0X35            //ң��վ�˹�������
#define         GNM_TPB         0X36            //ң��ͼƬ��������վ��ѯң��վͼƬ�ɼ���Ϣ
#define         GNM_CXSS        0X37            //����վ��ѯң��վʵʱ����
#define         GNM_CXSD        0X38            //����վ��ѯң��վʱ������
#define         GNM_CXRGZS      0X39            //����վ��ѯң��վ�˹�����
#define         GNM_CXZDYS      0X3A            //����վ��ѯң��ָ��Ҫ������
#define         GNM_XGJBPZ      0X40            //����վ�޸�ң��վ�������ñ�
#define         GNM_DQJBPZ      0X41            //����վ��ȡң��վ�������ñ�/ң��վ�Ա��������ñ�
#define         GNM_XGYXCS      0X42            //����վ�޸�ң�����в������ñ�
#define         GNM_DQYXCS      0X43            //����վ��ȡң�����в������ñ�/ң��վ�Ա����в������ñ�
#define         GNM_CXSBDJ      0X44            //��ѯˮ�õ��ʵʱ��������
#define         GNM_CXRJBB      0X45            //��ѯң���ն�����汾
#define         GNM_CXZTBJ      0X46            //��ѯң��վ״̬�ͱ�����Ϣ
#define         GNM_CSHSJ       0X47            //��ʼ����̬�洢����
#define         GNM_HFCCSZ      0X48            //�ָ��ն˻���������
#define         GNM_XGMM        0X49            //�޸�����
#define         GNM_SZSZ        0X4A            //����ң��վʱ��
#define         GNM_SWJB        0XE0            //�Զ��幦���� ˮλ�ӱ�
#define         GNM_XGPZ        0XE1            //�Զ��幦���� �޸��Զ�������
#define         GNM_DQPZ        0XE2            //�Զ��幦���� ��ȡ�Զ�������

#define         MessageTxdNByte         250             //���б�����󳤶�/���ͻ��泤��
#define         MessageLength           10              //��Ϣ���泤��
#define         DRPZLEN         240              //Сʱ�����泤��

typedef struct
{
  unsigned char Heartbeat;      //��·ά�ֱ�
  unsigned char CeShi;          //���Ա�
  unsigned char JunYunShiDuan;  //����ʱ��ˮ����Ϣ��
  unsigned char DingShi;        //ң��վ��ʱ��
  unsigned char JiaBao;         //ң��վ�ӱ���
  unsigned char XiaoShi;        //ң��վСʱ��
  unsigned char RenGong;        //ң��վ�˹�������
  unsigned char TuPian;         //ң��ͼƬ��������վ��ѯң��վͼƬ�ɼ���Ϣ
  unsigned char ChaXunShiShi;   //����վ��ѯң��վʵʱ����
  unsigned char ChaXunShiDuan;  //����վ��ѯң��վʱ������
  unsigned char ChaXuanRenGong; //����վ��ѯң��վ�˹�����
  unsigned char CXZhiDingYaoSu; //����վ��ѯң��ָ��Ҫ������
  unsigned char SetBasicConfig; //����վ�޸�ң�������ñ�
  unsigned char GetBasicConfig; //����վ��ȡң��վ�������ñ�
  unsigned char SetRunConfig;   //����վ�޸�ң��վ���в������ñ�
  unsigned char GetRunConfig;   //����վ��ȡң��վ���в������ñ�
  unsigned char ChaXunShuiBeng; //��ѯˮ�õ��ʵʱ��������
  unsigned char ChaXunBanBen;   //��ѯң���ն�����汾
  unsigned char ChaXunZhuangTai;//��ѯң��վ״̬�ͱ�����Ϣ
  unsigned char InitData;       //��ʼ����̬�洢����
  unsigned char HuiFuChuChang;  //�ָ��ն˻���������
  unsigned char SetPassWord;    //�޸�����
  unsigned char SetRTUTime;     //����ң��վʱ��
  unsigned char GetDefinConfig; //��ȡ�Զ�������
  unsigned char SetDefinConfig; //�޸��Զ�������
}ClassAFN;


/*�۲�ʱ��*/
typedef struct
{
  unsigned char Year;
  unsigned char Month;
  unsigned char Day;
  unsigned char Hour;
  unsigned char Minute;
}TT;


typedef struct
{
  unsigned int Page;
  unsigned int Bytes;
}ClassFlashDRPZ;

typedef struct
{ 
  long int Analog1;
  long int Analog2;
  //long int Analog3;
  //long int Analog4;
  long int RS485;
  unsigned int PT;
  unsigned int PN05;
  unsigned int PN10;
  unsigned int PN30;
  unsigned int PJ;
  unsigned char AFN;            //������
  
  TT RainTT;
  TT ATT;

}ClassMessage;

typedef struct
{
  ClassFlashDRPZ Now;
  ClassFlashDRPZ Array[DRPZLEN];
  unsigned int sp; 
}ClassDRPZ;

/*�����ϱ�Ҫ�ؽṹ*/
typedef struct
{
  unsigned char *keyword;       //Ҫ�ر�ʶ��
  long int value;               //Ҫ������ֵ
  unsigned char DType;          //�������� BCD�� N(x,y)
}E_data;

typedef struct
{
  unsigned int PassWord;
  unsigned char CenterAdd;
  unsigned char AFN;    
  unsigned char TextLeng;
  unsigned char End;
  unsigned char ST[5];
  DataTime  RxdTime;
}ClassRxdMessage;

extern ClassMessage Message;
extern const ClassAFN AFN;
extern ComPortClass Com;
extern ClassDRPZ DRPZ;



void AddDRPZ(unsigned int page,unsigned int bytes);
void UpdateDRPZ(void);

void ComEventHandlers(void);
void ComSendMessage(void);
void AddMessengeTask(unsigned char gnm);
void SendMessenge(void);
unsigned int WriteMessage(unsigned char *p);
unsigned int WriteMessageHead(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteHeartbeatPackets(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageTextPublic(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageEnd(unsigned char *p,unsigned int  AddNbyte,unsigned char endcod);
unsigned int WriteMessageVariable(unsigned char *p,unsigned int  AddNbyte,E_data *pE);
unsigned int WriteMessageTextRain(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageTextTongDao(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageTextData(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageConfig(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageTextLiShiDada(unsigned char *p,unsigned int  AddNbyte);
unsigned int WriteMessageTextDRPZ(unsigned char *p,unsigned int  AddNbyte);
unsigned char* RxdMessageCrc(void);
void MessageHandlers(unsigned char *p);
unsigned char* SetConfiginfo(unsigned char *p);
void SetRunConfig(unsigned char *p);
#endif  /*#ifndef __CPASCII_H*/
