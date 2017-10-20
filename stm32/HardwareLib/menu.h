/*
 * menu.h
 *
 *  Created on: 2017��10��16��
 *      Author: Administrator
 */

/*********************************************************
*�ļ����ƣ�menu.h
*ժ    Ҫ���˵���������
*
*��    �ߣ� ����
*��ʼ���ڣ� 2012��12��22��
*
*�޸� ��л��
*�޸����ڣ�2017��10��16��
**********************************************************/

#ifndef  _MENU_H
#define  _MENU_H

#include "include.h"

#define AdminPass               111111           //����Ա����
#define UserPass                111111           //�û�����

#define KEY_TIME_OUT 0

/************* �˵��ṹ�嶨�� ********************/
struct Menu
{
  uint8_t MenuCount;      //�˵�����
  uint8_t H;              //�˵�ѡ����ʾ����ʾˮƽ����
  const char *string;        //�˵�ѡ����ʾ�ַ���
  void (*Subs)();               //ѡ���ִ�еĶ���
  struct Menu *SubMenu;         //�Ӽ��˵�
  struct Menu *PreviousMenu;    //�����˵�
};

typedef enum {
H_YEAR,
H_MONTH,
H_DAY,
H_HOUR,
H_MINUTE,
H_SECOND,
} timeType_t;

/***************ʱ�����ò˵��ṹ��**********************/
struct TimeSetMenu
{
  timeType_t type;
  uint8_t stringadd_x;
  uint8_t stringadd_y;
  const char *string;
  uint8_t disadd_x;
  uint8_t disadd_y;
  void (*Subs)(uint8_t x,uint8_t y,uint8_t z);
};


/*�������ֽṹ*/
typedef struct
{
  long value;   //���ó�ʼֵ
  uint8_t type;   //�������� N(x,y)
  uint8_t negative;//�Ƿ�����ֵ
  uint8_t *str;   //���ֺ�����ʾ���ַ���
  long max;    //���ֵ
  long min;    //��Сֵ
}setnum;

typedef struct
{
  uint8_t user;     //��ѡ�е���
  const char *str[11];  //ѡ����ʾ�ַ���
}setstring;

void SetMode(void);
void WaitKey(void);
uint8_t PassWord(void);
long int SetNum(setnum num,uint8_t H,uint8_t Ver);
void SetMenu(void);
void ShowMenu(struct Menu *MenuUser,uint8_t DisplayPoint,signed char USER,signed char UserChoose,uint8_t refresh);
uint8_t SetString(setstring s,uint8_t H,uint8_t Ver);
void settimetype(uint8_t type,uint8_t H,uint8_t Ver);
void SetClock(void);
void SetResetFactory(void);

uint8_t SetYaoSu(uint8_t ys,uint8_t H,uint8_t Ver);
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
void SetDTKEY_UPower(void);
void SetDTKEY_UPreheat(void);
void SetCKEY_SETadd(void);

#endif  /*#ifndef  _MENU_H*/


