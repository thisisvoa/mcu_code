/*********************************************************
*�ļ����ƣ�menu.h
*ժ    Ҫ���˵���������
* 
*��    �ߣ� ����
*��ʼ���ڣ� 2013��10��12��
*������ڣ�
**********************************************************/

#ifndef  _MENU_H
#define  _MENU_H

#include "Alarm.h"
#include "include.h"
 
#define AdminPass               111111           //����Ա����
#define UserPass                111111           //�û�����


/************* �˵��ṹ�嶨�� ********************/
struct Menu
{
  char MenuCount;      //�˵�����
  char H;              //�˵�ѡ����ʾ����ʾˮƽ����  
  char *string;        //�˵�ѡ����ʾ�ַ��� 
  void (*Subs)();               //ѡ���ִ�еĶ���
  struct Menu *SubMenu;         //�Ӽ��˵�  
  struct Menu *PreviousMenu;    //�����˵�   
};

/***************ʱ�����ò˵��ṹ��**********************/
struct TimeSetMenu 
{
  char type;
  char stringadd_x;
  char stringadd_y;
  char *string;
  char disadd_x;
  char disadd_y;
  void (*Subs)(char x,char y,char z);
};


/*�������ֽṹ*/
typedef struct
{
  long value;   //���ó�ʼֵ
  char type;   //�������� N(x,y)
  char negative;//�Ƿ�����ֵ 
  char *str;   //���ֺ�����ʾ���ַ���
  long max;    //���ֵ
  long min;    //��Сֵ
}setnum;

typedef struct
{
  char user;     //��ѡ�е���
  char *str[10];  //ѡ����ʾ�ַ���
}setstring;

typedef struct
{
  AlarmValue *pA;
  char at_i;
  char at_ii;
  char at_iii;  
}AlarmSetClass;

extern const struct Menu MainMenu[5];
extern const struct Menu SysSetMenu[3];

void SetMode(void);
void SetMenu(void); 
void ShowMenu(struct Menu *MenuUser,char DisplayPoint,signed char USER,signed char UserChoose,char refresh);
void WaitKey(void);
long int SetNum(setnum num,char H,char Ver);
char PassWord(void);
void SetClock(void);
void settimetype(char type,char H,char Ver);
void SetYLJFBL(void);
void SetRainClear(void);
void RainfallClear(void);
void SysInfo(void);
void WriteConfig(void);
void ResetFactory(void);
void SetResetFactory(void);
void DefaultConfig(void);
void AlarmValueSet(void);
void SystemSelfTestMenu(void);
#endif  /*#ifndef  _MENU_H*/


