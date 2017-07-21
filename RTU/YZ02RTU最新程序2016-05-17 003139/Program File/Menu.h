/*********************************************************
*�ļ����ƣ�menu.h
*ժ    Ҫ���˵���������
* 
*��    �ߣ� ����
*��ʼ���ڣ� 2012��12��22��
*������ڣ�
**********************************************************/

#ifndef  _MENU_H
#define  _MENU_H

#include "include.h"
 
#define AdminPass               111111           //����Ա����
#define UserPass                111111           //�û�����

/************* �˵��ṹ�嶨�� ********************/
struct Menu
{
  unsigned char MenuCount;      //�˵�����
  unsigned char H;              //�˵�ѡ����ʾ����ʾˮƽ����  
  unsigned char *string;        //�˵�ѡ����ʾ�ַ��� 
  void (*Subs)();               //ѡ���ִ�еĶ���
  struct Menu *SubMenu;         //�Ӽ��˵�  
  struct Menu *PreviousMenu;    //�����˵�   
};

/***************ʱ�����ò˵��ṹ��**********************/
struct TimeSetMenu 
{
  unsigned char type;
  unsigned char stringadd_x;
  unsigned char stringadd_y;
  unsigned char *string;
  unsigned char disadd_x;
  unsigned char disadd_y;
  void (*Subs)(unsigned char x,unsigned char y,unsigned char z);
};


/*�������ֽṹ*/
typedef struct
{
  long value;   //���ó�ʼֵ
  unsigned char type;   //�������� N(x,y)
  unsigned char negative;//�Ƿ�����ֵ 
  unsigned char *str;   //���ֺ�����ʾ���ַ���
  long max;    //���ֵ
  long min;    //��Сֵ
}setnum;

typedef struct
{
  unsigned char user;     //��ѡ�е���
  unsigned char *str[10];  //ѡ����ʾ�ַ���
}setstring;



void SetMode(void);
void WaitKey(void);
unsigned char PassWord(void);
long int SetNum(setnum num,unsigned char H,unsigned char Ver);
void SetMenu(void);
void ShowMenu(struct Menu *MenuUser,unsigned char DisplayPoint,signed char USER,signed char UserChoose,unsigned char refresh);
unsigned char SetString(setstring s,unsigned char H,unsigned char Ver);
void settimetype(unsigned char type,unsigned char H,unsigned char Ver);
void SetClock(void);
void SetResetFactory(void);

unsigned char SetYaoSu(unsigned char ys,unsigned char H,unsigned char Ver);
void SetRTUtype(void);
void SetCenteradd(void);
void SetST(void);
void SetWorkMode(void);
void SetDSBJG(void);
void SetJBJG(void); 
void SetPDTime(void);
void SetCYJG(void);
void SetCCJG(void);
void SetYLJFBL(void);
void SetYLJBFZ(void);
void SetYLJType(void);
void SetSWJZ(void);
void SetSWXZJZ(void);
void SetDTUPower(void);
void SetDTUPreheat(void);
void SetDTUPreheat(void);
void SetDTUCloseDelay(void);
void SetDTUTxdTime(void);
void SetDTUTxdMax(void);
void SetPT(void);
void SetRainJBSD(void);
void SetRainClear(void);
void SetDTUbps(void);
void SetWaterChaliang(void);
void SetRS485bps(void);
void SetRS485Power(void);
void SetRS485Preheat(void);
void SetRS485CgqType(void);
void SetRS485Name(void);
void SetTongDaoName_1(void);
void SetTongDaoSType_1(void);
void SetTongDaoMax_1(void);
void SetTongDaoMin_1(void);
void SetTongDaoName_2(void);
void SetTongDaoName_3(void);
void SetTongDaoName_4(void);
void SetTongDaoSType_2(void);
void SetTongDaoSType_3(void);
void SetTongDaoSType_4(void);
void SetTongDaoMax_2(void);
void SetTongDaoMax_3(void);
void SetTongDaoMax_4(void);
void SetTongDaoMin_2(void);
void SetTongDaoMin_3(void);
void SetTongDaoMin_4(void);
void SetHeight(void);
void SysInfo(void);
  
#endif  /*#ifndef  _MENU_H*/


