/*
 * menu.c
 *
 *  Created on: 2017��10��16��
 *      Author: Administrator
 */

/*********************************************************
*�ļ����ƣ�SetKEY_UPMenu.c
*ժ    Ҫ���˵����ù��ܶ���
*
*��    �ߣ�����
*��ʼ���ڣ� 2013��05��26��
*
*�޸� ��л��
*�޸����ڣ�2017��10��16��
*
**********************************************************/

#include "menu.h"
#include "key.h"
#include "lcd_12864.h"

extern const struct Menu MainMenu[8];
extern const struct Menu ConfigMenu[7];
extern const struct Menu RainfallMenu[7];
extern const struct Menu WaterMenu[4];
extern const struct Menu ComConfigMenu[6];
extern const struct Menu RS485Menu[3];
extern const struct Menu TongDaoMenu[2];
extern const struct Menu TongDao1Menu[4];
extern const struct Menu TongDao2Menu[4];
//extern const struct Menu TongDao3Menu[4];
//extern const struct Menu TongDao4Menu[4];
extern const struct Menu CaiYangMenu[5];

const struct Menu MainMenu[8]={            //���˵�
{8,4,"��������",NULL,(struct Menu*)ConfigMenu,NULL},
{8,4,"��������",NULL,(struct Menu*)RainfallMenu,NULL},
{8,4,"ˮλ����",NULL,(struct Menu*)WaterMenu,NULL},
{8,4,"��������",NULL,(struct Menu*)CaiYangMenu,NULL},
{8,4,"ͨ������",NULL,(struct Menu*)ComConfigMenu,NULL},
{8,4,"ϵͳʱ��",SetClock,NULL,NULL},
{8,4,"�ָ�����",SetResetFactory,NULL,NULL},
{8,4,"ϵͳ��Ϣ",SysInfo,NULL,NULL}
};


const struct Menu ConfigMenu[7]={        //��������
{7,4,"��վ����",SetRTUtype,NULL,(struct Menu*)MainMenu},
{7,4,"���ĵ�ַ",SetCKEY_SETadd,NULL,(struct Menu*)MainMenu},
{7,4,"��վ��ַ",SetST,NULL,(struct Menu*)MainMenu},
{7,4,"����ģʽ",SetWorkMode,NULL,(struct Menu*)MainMenu},
{7,4,"��ʱ�����",SetDSBJG,NULL,(struct Menu*)MainMenu},
{7,4,"�ӱ����",SetJBJG,NULL,(struct Menu*)MainMenu},
{7,4,"�洢���",SetCCJG,NULL,(struct Menu*)MainMenu}
};

const struct Menu RainfallMenu[7]={		//��������
{7,4,"����������",SetYLJType,NULL,(struct Menu*)MainMenu},
{7,4,"�����ֱ���",SetYLJFBL,NULL,(struct Menu*)MainMenu},
{7,4,"����ʼʱ��",SetPDTime,NULL,(struct Menu*)MainMenu},
{7,4,"�ӱ�ʱ��",SetRainJBSD,NULL,(struct Menu*)MainMenu},
{7,4,"�ӱ���ֵ",SetYLJBFZ,NULL,(struct Menu*)MainMenu},
{7,4,"�ۼ�����",SetPT,NULL,(struct Menu*)MainMenu},
{7,4,"��������",SetRainClear,NULL,(struct Menu*)MainMenu}
};

const struct Menu WaterMenu[4]={	   //ˮλ����
{4,4,"ˮλ��ֵ",SetSWJZ,NULL,(struct Menu*)MainMenu},
{4,4,"������ֵ",SetSWXZJZ,NULL,(struct Menu*)MainMenu},
{4,4,"ˮλ����",SetWaterChaliang,NULL,(struct Menu*)MainMenu},
{4,4,"��װ�߶�",SetHeight,Null,(struct Menu*)MainMenu}
};

const struct Menu ComConfigMenu[6]={    //ͨ������
{6,4,"ͨ�ŵ�Դ",SetDTKEY_UPower,Null,(struct Menu*)MainMenu},
{6,4,"ͨ��Ԥ��",SetDTKEY_UPreheat,Null,(struct Menu*)MainMenu},
{6,4,"������ʱ",SetDTUCloseDelay,Null,(struct Menu*)MainMenu},
{6,3,"ͨ�Ų�����",SetDTUbps,Null,(struct Menu*)MainMenu},
{6,4,"��ʱʱ��",SetDTUTxdTime,Null,(struct Menu*)MainMenu},
{6,4,"�ط�����",SetDTUTxdMax,Null,(struct Menu*)MainMenu}
};

const struct Menu RS485Menu[3]={		//RS485ͨ��
{3,4,"����Ҫ��",SetRS485Name,NULL,(struct Menu*)MainMenu},
{3,4,"������",SetRS485bps,NULL,(struct Menu*)MainMenu},
{3,3,"����������",SetRS485CgqType,NULL,(struct Menu*)MainMenu}
};

const struct Menu TongDaoMenu[2]={		//ģ��ͨ��
{2,2,"ģ����ͨ��1",NULL,(struct Menu*)TongDao1Menu,(struct Menu*)MainMenu},
{2,2,"ģ����ͨ��2",NULL,(struct Menu*)TongDao2Menu,(struct Menu*)MainMenu},
//{4,2,"ģ����ͨ��3",NULL,(struct Menu*)TongDao3Menu,(struct Menu*)MainMenu},
//{4,2,"ģ����ͨ��4",NULL,(struct Menu*)TongDao4Menu,(struct Menu*)MainMenu},
};

const struct Menu TongDao1Menu[4]={		//ģ��ͨ�� 1
{4,4,"����Ҫ��",SetTongDaoName_1,NULL,(struct Menu*)TongDaoMenu},
{4,4,"�����ź�",SetTongDaoSType_1,NULL,(struct Menu*)TongDaoMenu},
{4,3,"�������ֵ",SetTongDaoMax_1,NULL,(struct Menu*)TongDaoMenu},
{4,3,"������Сֵ",SetTongDaoMin_1,NULL,(struct Menu*)TongDaoMenu},
};

const struct Menu TongDao2Menu[4]={		//ģ��ͨ�� 2
{4,4,"����Ҫ��",SetTongDaoName_2,NULL,(struct Menu*)TongDaoMenu},
{4,4,"�����ź�",SetTongDaoSType_2,NULL,(struct Menu*)TongDaoMenu},
{4,3,"�������ֵ",SetTongDaoMax_2,NULL,(struct Menu*)TongDaoMenu},
{4,3,"������Сֵ",SetTongDaoMin_2,NULL,(struct Menu*)TongDaoMenu},
};

/*const struct Menu TongDao3Menu[4]={	//ģ��ͨ�� 3
{4,4,"����Ҫ��",SetTongDaoName_3,NULL,(struct Menu*)TongDaoMenu},
{4,4,"�����ź�",SetTongDaoSType_3,NULL,(struct Menu*)TongDaoMenu},
{4,3,"�������ֵ",SetTongDaoMax_3,NULL,(struct Menu*)TongDaoMenu},
{4,3,"������Сֵ",SetTongDaoMin_3,NULL,(struct Menu*)TongDaoMenu},
};

const struct Menu TongDao4Menu[4]={		//ģ��ͨ�� 4
{4,4,"����Ҫ��",SetTongDaoName_4,NULL,(struct Menu*)TongDaoMenu},
{4,4,"�����ź�",SetTongDaoSType_4,NULL,(struct Menu*)TongDaoMenu},
{4,3,"�������ֵ",SetTongDaoMax_4,NULL,(struct Menu*)TongDaoMenu},
{4,3,"������Сֵ",SetTongDaoMin_4,NULL,(struct Menu*)TongDaoMenu},
};*/

const struct Menu CaiYangMenu[5]={	//��������
{5,4,"�������",SetCYJG,NULL,(struct Menu*)MainMenu},
{5,4,"������Դ",SetRS485Power,NULL,(struct Menu*)MainMenu},
{5,4,"����Ԥ��",SetRS485Preheat,NULL,(struct Menu*)MainMenu},
{5,4,"RS485ͨ��",NULL,(struct Menu*)RS485Menu,NULL},
{5,3,"ģ����ͨ��",NULL,(struct Menu*)TongDaoMenu,NULL},
};


const struct TimeSetMenu TimeSet[6]={   //ʱ������
	{H_YEAR,2,8,"��",5,8,settimetype},
	{H_MONTH,2,24,"��",5,24,settimetype},
	{H_DAY,2,40,"��",5,40,settimetype},
	{H_HOUR,10,8,"ʱ",13,8,settimetype},
	{H_MINUTE,10,24,"��",13,24,settimetype},
	{H_SECOND,10,40,"��",13,40,settimetype}
};

/*******************************************************************************
�������ƣ�void SetMenu(void)
�������ܣ�����ģʽ
�����������
�����������
����ֵ  ����
*******************************************************************************/
void SetMode(void)
{
  Display.Status.Flag.Mon = RESET;
  Display.Status.Flag.Menu = SET;  //���ý���״̬��־��λ
  lcd_clear_ddram();
  if(0!=PassWord())
  {
    SetMenu();
  }

  key_event_handle = Null;
  lcd_clear_ddram();
  DisplayMon();      //��ʾ������
  KEY_TIME_OUT = RESET;
  Display.Status.Flag.SetMode = RESET;
}

/*******************************************************************************
�������ƣ�void ShowMenu(Menu *MenuUser,uint8_t DisplayPoint,uint8_t refresh)
�������ܣ���ʾ�˵�
���������Menu *MenuUser---->��ʾ�˵���ַ
          DisplayPoint----->��ʾ��
          UserChoose------->��ǰ�û�ѡ��
          USER------------->ǰһ���û�ѡ��
          refresh---------->ȫ��ˢ�±�־
�����������
����ֵ  ����
*******************************************************************************/
void ShowMenu(struct Menu *MenuUser,uint8_t DisplayPoint,signed char USER,signed char UserChoose,uint8_t refresh)
{
  uint8_t i=0;
  while(i<4)
  {
    if(1==refresh)    //��ʾȫ��ˢ��
    {
      if(UserChoose == DisplayPoint) //��ǰ��ʾ�Ĳ˵�ѡ���Ƿ��Ǳ��û�ѡ��
        DisplayString(MenuUser[DisplayPoint].H,i<<4,MenuUser[DisplayPoint].string,0XFFFF);
      else
        DisplayString(MenuUser[DisplayPoint].H,i<<4,MenuUser[DisplayPoint].string,0);    //��ʾ�˵�ѡ���ַ���
    }
    else    //ֻˢ���û�ѡ����
    {
      if(USER == DisplayPoint)//��ʾ�����ǰһ���û�ѡ��
      {
        DisplayString(MenuUser[DisplayPoint].H,i<<4,MenuUser[USER].string,0);    //��ʾ�˵�ѡ���ַ���
      }
      else if(UserChoose == DisplayPoint)//��ʾ��Ϊ��ǰ�û�ѡ��
      {
        DisplayString(MenuUser[DisplayPoint].H,i<<4,MenuUser[DisplayPoint].string,0XFFFF);    //��ʾ�˵�ѡ���ַ���
      }
    }
    i++;
    DisplayPoint++;     //��ʾ���1
    if(DisplayPoint==MenuUser[0].MenuCount)
      return;
  }
}

/*******************************************************************************
�������ƣ�void SetMenu(void)
�������ܣ����ò˵�
�����������
�����������
����ֵ  ����
*******************************************************************************/
void SetMenu(void)
{
  signed char user[5]={0};              //��ͬ�㼶�˵��û�ѡ�񻺴�
  uint8_t i=0;                    //�˵��㼶
  signed char UserChoose = 0;           //��ǰ�û�ѡ��
  signed char USER=0;                   //ǰһ���û�ѡ��
  uint8_t  DisplayPoint = 0;      //��ʾ��
  uint8_t  RefreshMenu = 1;       //ˢ�²˵���־
  struct Menu *MenKEY_UPoint = (struct Menu*)MainMenu;

  lcd_clear_ddram();
  while(1)
  {
    ShowMenu(MenKEY_UPoint,DisplayPoint,USER,UserChoose,RefreshMenu);         //��ʾĿ¼

    WaitKey();     //�ȴ���������

      switch(key_event_handle)
      {
        case KEY_UP:
                USER = UserChoose;                      //����ǰһ���û�ѡ��
                UserChoose--;                           //�û�ѡ������
                if(UserChoose < 0)                      //��ǰ�û�ѡ��Ϊ��һ��ʱ ������ѡ��
                {
                  UserChoose = MenKEY_UPoint[0].MenuCount - 1;           //�û�ѡ��ָ�����һ��
                  if(MenKEY_UPoint[0].MenuCount > 4)                     //�˵����ȴ�����ʾ���������
                  {
                    lcd_clear_ddram();                      //����
                    RefreshMenu = 1;
                  }
                }
                else if(((UserChoose+1)%4)==0)          //���Ϸ�ҳ
                {
                  lcd_clear_ddram();
                  RefreshMenu = 1;
                }
                break;
        case KEY_DOWN:                                      //�û�����ѡ��
                USER = UserChoose;                      //����ǰһ���û�ѡ��
                UserChoose++;
                if(UserChoose >= MenKEY_UPoint[0].MenuCount)             //�û�ѡ����ڲ˵�����
                {
                  UserChoose = 0;                       //�û�ѡ��ָ������
                  if(MenKEY_UPoint[0].MenuCount > 4)
                  {
                    lcd_clear_ddram();
                    RefreshMenu = 1;
                  }
                }
                break;

        case KEY_RETURN:                                       //�����ϼ��˵�
                if(MenKEY_UPoint == MainMenu)               //��ǰ�˵�Ϊ���˵�ʱ �˳��˵�
                {
                  return;
                }
                else if(MenKEY_UPoint[0].PreviousMenu != NULL)
                {
                  MenKEY_UPoint = MenKEY_UPoint[0].PreviousMenu;
                  UserChoose = user[--i]; //�ָ��ϼ��˵��û�ѡ��
                  lcd_clear_ddram();
                  RefreshMenu = 1;
                }
                break;

        case KEY_SET:                                             //������һ���˵�������
                if(MenKEY_UPoint[UserChoose].Subs != NULL)          //�����Ӧ����
                {
                  lcd_clear_ddram();
                  (*MenKEY_UPoint[UserChoose].Subs)();
                }
                else if(MenKEY_UPoint[UserChoose].SubMenu != NULL)  //������һ���˵�
                {
                  MenKEY_UPoint=MenKEY_UPoint[UserChoose].SubMenu;
                  user[i++] = UserChoose;     //���浱ǰ�˵����û�ѡ��
                  UserChoose = 0;
                }
                RefreshMenu = 1;
                lcd_clear_ddram();
                break;
        default :break;
      }

    DisplayPoint = UserChoose-UserChoose%4;     // 4 ָ��Ļ��ʾ�������
    if((UserChoose+USER)%8 == 7)                // ���·�ҳʱ����
    {
      lcd_clear_ddram();
      RefreshMenu = 1;
    }
    if(KEY_TIME_OUT)              //�ȴ�������ʱ ���ؼ�����
    {
      KEY_TIME_OUT = False;
      lcd_clear_ddram();
      return;
    }
  }
}

/*�ȴ�����*/
void WaitKey(void)
{
  unsigned int i=0;

  key_event_handle = Null;
  while(!key_event_handle)
  {
    SysEventHandlers();         //ϵͳ�¼�����
    UserEventHandlers();        //������
    delayms(1);
    if(i++ > 20000)
    {
      KEY_TIME_OUT = True;
      key_event_handle = Null;
      return;
    }
  }
}

uint8_t PassWord(void)
{
  long x=0;
  setnum num={0,0X60,0,"\0"};

  DisplayString(4,16,"��������",0);

  num.max = 9999999;
  num.min = 0;
  x = SetNum(num,5,32);

  if(KEY_TIME_OUT)
      return 0;
  if(UserPass == x)
    return 2;
  if(AdminPass == x)
    return 1;

  return 0;
}


/*******************************************************************************
�������ƣ�long int SetNum(setnum num,uint8_t H,uint8_t Ver)
�������ܣ���������
���������setnum num----->�����������ݽṹ ������menu.h
          H-------------->��ʾˮƽ����
          Ver------------>��ʾ��ֱ����
�����������
����ֵ  �� �û������ֵ

*******************************************************************************/
long int SetNum(setnum num,uint8_t H,uint8_t Ver)
{
  uint8_t strnum[15]={0};
  uint8_t i=0,j=0,k=0;
  int user=0;
  unsigned int fb=0;

  i = SInt32_TO_String(strnum,num.value,num.type,num.negative+Zero);//ת��Ϊ�ַ���ʱ����ǰ����
  k = i;                //�ַ�������
  for(j=0;j<10;j++)      //ת����ɺ��ַ��� β��������Ҫ��ʾ���ַ�
  {
    if(num.str[j]=='\0')
      break;
    strnum[i++] = num.str[j];
  }

  while(1)
  {
    fb = 0X8000 >> user;
    DisplayString(H,Ver,strnum,fb);

    WaitKey();//�ȴ���������

    switch(key_event_handle)
    {
      case KEY_UP:  if('+'==strnum[user])
                  strnum[user] = '-';
                else if(('-'==strnum[user]))
                  strnum[user] = '+';
                else if(++strnum[user]>'9')
                  strnum[user] = '0';
                break;
      case KEY_DOWN: if('+'==strnum[user])
                   strnum[user] = '-';
                 else if(('-'==strnum[user]))
                   strnum[user] = '+';
                 else if(--strnum[user]<'0')
                   strnum[user] = '9';
                 break;
      case KEY_RIGHT: user++;
                  if('.'==strnum[user])
                    user++;
                  else if((strnum[user]>'9')||(strnum[user]<'0'))
                    user = 0;
                  break;
      case KEY_LEFT:  user--;
                  if(user<0)
                    user = k-1;
                  else if('.'==strnum[user])
                    user--;
                  break;
      case KEY_RETURN:   return num.value;
      case KEY_SET: num.value = String_TO_SInt32(strnum);
                  Draw(H,Ver,16,16,0,Null);
                  if(num.value > num.max)
                    num.value = num.max;
                  else if(num.value < num.min)
                    num.value = num.min;
                  return num.value;
      default :break;
    }

    if(KEY_TIME_OUT)    //�ȴ�������ʱ
      return num.value;
  }
}

/*******************************************************************************
�������ƣ�uint8_t SetString(setstring s,uint8_t H,uint8_t Ver)
�������ܣ�ѡ���ַ�
���������setstring s----->�ṩ�Ĵ�ѡ��
          H--------------->ˮƽ��ʾ��ַ
          Ver------------->��ֱ��ʾ��ַ
�����������
����ֵ  ���û�ѡ������
*******************************************************************************/
uint8_t SetString(setstring s,uint8_t H,uint8_t Ver)
{
  uint8_t i=0,j=0;

  j = s.user;
  for(i=0;i<10;i++)
  {
    if(s.str[i][0]=='\0')
      break;
  }
  i--;
  while(1)
  {
    DisplayString(H,Ver,s.str[s.user],0);

    WaitKey();//�ȴ���������

    switch(key_event_handle)
    {
      case KEY_UP:  Draw(H,Ver,strlenght(s.str[s.user]),16,0,Null);
                s.user++;
                if(s.user > i)
                  s.user = 0;
                break;
      case KEY_DOWN: Draw(H,Ver,strlenght(s.str[s.user]),16,0,Null);
                if(0==s.user)
                   s.user = i;
                 else
                   s.user--;
                 break;
      case KEY_RETURN: return j;
      case KEY_SET:return s.user;
    }
    if(KEY_TIME_OUT)
      return j;
  }
}

uint8_t SetYaoSu(uint8_t ys,uint8_t H,uint8_t Ver)
{
  uint8_t i;

  if(ys >= YAOSULENG)
  {
    i=ys=0;
  }
  else
  {
    i = ys;
  }

  while(1)
  {
    DisplayString(H,Ver,YaoSuInfo[ys].NameStr,0);

    WaitKey();//�ȴ���������

    switch(key_event_handle)
    {
      case KEY_UP:  Draw(H,Ver,strlenght(YaoSuInfo[ys].NameStr),16,0,Null);
                ys++;
                if(ys > YAOSULENG-1)
                  ys = 0;
                break;
      case KEY_DOWN: Draw(H,Ver,strlenght(YaoSuInfo[ys].NameStr),16,0,Null);
                if(0==ys)
                   ys = YAOSULENG-1;
                 else
                   ys--;
                 break;
      case KEY_RETURN: return i;
      case KEY_SET:return ys;
      default :break;
    }
    if(KEY_TIME_OUT)
      return i;
  }
}

void SetRTUtype(void)
{
  uint8_t temp[5]={'P','H','K','Z','M'};//ң��վ������
  uint8_t i=0;
  setstring settemp={0,{"��ˮ","�ӵ�","ˮ��","բ��","��վ","","����","����ˮ","ˮ��","ȡˮ��","��ˮ��",}};

  DisplayString(4,8,"��վ����",0);
  H_LINE(2,49,12);
  for(i=0;i<5;i++)//����������Χ�ָ�Ϊ ��ˮ
  {
    if(rtuParameter.upDataArg.rtuType == temp[i])
      break;
  }
  if(i >= 5)
    i = 0;
  settemp.user = i;

  settemp.user = SetString(settemp,6,32);

  rtuParameter.upDataArg.rtuType = temp[settemp.user];

}

void SetCKEY_SETadd(void)
{
  setnum num={rtuParameter.upDataArg.centreStationAddr,0X30,0,""};
  num.max = 255;
  num.min = 0;

  DisplayString(3,8,"����վ��ַ",0);
  H_LINE(2,49,12);
  rtuParameter.upDataArg.centreStationAddr = (unsigned char)SetNum(num,6,32);
  WriteUInt8(rtuParameter.upDataArg.centreStationAddr,EEPROM.CKEY_SETAdd);//��������ֵ
}

void SetST(void)
{
  uint8_t strtemp[11]={0};
  uint8_t i=0,j=0;
  unsigned int fb=0;

  DisplayString(4,8,"��վ��ַ",0);
  H_LINE(2,49,12);
  for(i=0;i<10;)
  {
    strtemp[i++] = HEXASCII[RTU.ST[j]>>4];
    strtemp[i++] = HEXASCII[RTU.ST[j]&0X0F];
    j++;
    if(5==j)
      break;
  }
  i=0;
  while(1)
  {
    fb=0X8000>>i;
    DisplayString(3,32,strtemp,fb);

    WaitKey();//�ȴ���������

      switch(key_event_handle)
      {
        case KEY_UP: if(++strtemp[i]>'9')
                   strtemp[i] = '0';
                 break;
        case KEY_DOWN: if(--strtemp[i]<'0')
                   strtemp[i] = '9';
                 break;
        case KEY_RIGHT: if(++i > 9)
                      i = 0;
                    break;
        case KEY_LEFT: if(0==i)
                      i = 9;
                   else
                     i--;
                   break;
        case KEY_SET: RTU.ST[0] = strtemp[0]<<4;
                    RTU.ST[0] += strtemp[1]&0X0F;
                    RTU.ST[1] = strtemp[2]<<4;
                    RTU.ST[1] += strtemp[3]&0X0F;
                    RTU.ST[2] = strtemp[4]<<4;
                    RTU.ST[2] += strtemp[5]&0X0F;
                    RTU.ST[3] = strtemp[6]<<4;
                    RTU.ST[3] += strtemp[7]&0X0F;
                    RTU.ST[4] = strtemp[8]<<4;
                    RTU.ST[4] += strtemp[9]&0X0F;
                    Write_NByte(RTU.ST,5,EEPROM.ST);//��������
                    return;
         case KEY_RETURN:  return;
         default :break;
      }
      if(KEY_TIME_OUT)
        return;

  }
}

void SetWorkMode(void)
{
  uint8_t temp[4]={WMODE_1,WMODE_2,WMODE_3,WMODE_4};
  uint8_t i=0;
  setstring settemp={0,{"  �Ա�  ","�Ա�ȷ��","��ѯӦ��","����ά��",""}};

  DisplayString(4,8,"����ģʽ",0);
  H_LINE(2,49,12);
  for(i=0;i<4;i++)//����������λ �ָ�Ϊ��ѯӦ��
  {
    if(RTU.WorkMode==temp[i])
      break;
  }
  if(i >= 4)
    i = 2;
  settemp.user = i;

  settemp.user = SetString(settemp,4,32);

  RTU.WorkMode = temp[settemp.user];
  WriteUInt8(RTU.WorkMode,EEPROM.WorkMode);//��������ֵ
}

void SetDSBJG(void)
{
  setnum num={RTU.DingShiBaoTime,0X20,0,"H"};
  num.max = 24;
  num.min = 0;

  DisplayString(3,8,"��ʱ�����",0);
  H_LINE(2,49,12);
  RTU.DingShiBaoTime = (unsigned char)SetNum(num,6,32);
  WriteUInt8(RTU.DingShiBaoTime,EEPROM.DingShiBaoTime);//��������ֵ
}

void SetJBJG(void)
{
  setnum num={RTU.JiaBaoTime,0X30,0,"����"};
  num.max = 250;
  num.min = 0;

  DisplayString(4,8,"�ӱ����",0);
  H_LINE(2,49,12);
  RTU.JiaBaoTime = (unsigned char)SetNum(num,6,32);
  WriteUInt8(RTU.JiaBaoTime,EEPROM.JiaBaoTime);   //��������ֵ
}

void SetPDTime(void)
{
  setnum num={Rainfall.PDTime,0x20,0,"ʱ"};
  num.max = 23;
  num.min = 0;

  DisplayString(3,8,"����ʼʱ��",0);
  H_LINE(2,49,12);
  Rainfall.PDTime = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Rainfall.PDTime,EEPROM.PDTime);//��������ֵ
}

void SetPT(void)
{
  setnum num={Rainfall.PT,0X51,0,"mm"};
  num.max = 65535;
  num.min = 0;

  DisplayString(4,8,"�ۼ�����",0);
  H_LINE(2,49,12);
  Rainfall.PT = (unsigned int)SetNum(num,5,32);
  WriteUInt16(Rainfall.PT,EEPROM.PT);//��������ֵ
}


void SetCYJG(void)
{
  setnum num={RTU.CaiYangJianGe,0X50,0,"����"};
  num.max = 65535;
  num.min = 0;

  DisplayString(4,8,"�������",0);
  H_LINE(2,49,12);
  RTU.CaiYangJianGe = (unsigned int)SetNum(num,5,32);
  WriteUInt16(RTU.CaiYangJianGe,EEPROM.CaiYangJianGe);//��������ֵ
}

void SetCCJG(void)
{
  setnum num={RTU.CunChuJianGe,0X50,0,"����"};
  num.max = 65535;
  num.min = 0;

  DisplayString(4,8,"�洢���",0);
  H_LINE(2,49,12);
  RTU.CunChuJianGe = (unsigned int)SetNum(num,5,32);
  WriteUInt16(RTU.CunChuJianGe,EEPROM.CunChuJianGe);//��������ֵ
}

void SetYLJType(void)
{
  setstring settemp={Rainfall.Type,{" NONE","����ʽ",""}};

  DisplayString(3,8,"����������",0);
  H_LINE(2,49,12);
  if(settemp.user > 1)
  settemp.user = 1;

  settemp.user = SetString(settemp,5,32);

  Rainfall.Type = settemp.user;
  WriteUInt8(Rainfall.Type,EEPROM.RainType);//��������ֵ

}

void SetYLJFBL(void)
{
  setnum num={Rainfall.Resolution,0X21,0,"mm"};
  num.max = 99;
  num.min = 0;

  DisplayString(2,8,"�����Ʒֱ���",0);
  H_LINE(2,49,12);
  Rainfall.Resolution = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Rainfall.Resolution,EEPROM.RainFBL);//��������ֵ
}

void SetRainJBSD(void)
{
  uint8_t temp[4]={0,5,10,30};
  uint8_t i=0;

  setstring settemp={0,{" NONE"," 5����","10����","30����",""}};

  DisplayString(2,8,"�����ӱ�ʱ��",0);

  H_LINE(2,49,12);
  for(i=0;i<4;i++)                      //������ΧĬ��Ϊ 5����
  {
    if(Rainfall.YLJBSD==temp[i])
      break;
  }
  if(i >= 4)
    i = 1;

  settemp.user = i;
  settemp.user = SetString(settemp,5,32);
  Rainfall.YLJBSD = temp[settemp.user];
  WriteUInt8(Rainfall.YLJBSD ,EEPROM.RainJBSD);//��������ֵ
}


void SetYLJBFZ(void)
{
  setnum num={Rainfall.JBFZ,0x51,0,"mm"};
  num.max = 65535;
  num.min = 0;

  DisplayString(3,8,"�����ӱ���ֵ",0);
  H_LINE(2,49,12);
  Rainfall.JBFZ = (unsigned int)SetNum(num,5,32);
  WriteUInt16(Rainfall.JBFZ,EEPROM.RainJBFZ);//��������ֵ
}

void SetSWJZ(void)
{
  setnum num={RTU.ShuiWeiJiZhi,0X73,Symbol,"m"};
  num.max = 9999999;
  num.min = -9999999;

  DisplayString(4,8,"ˮλ��ֵ",0);
  H_LINE(2,49,12);
  RTU.ShuiWeiJiZhi = SetNum(num,3,32);
  WriteSInt32(RTU.ShuiWeiJiZhi,EEPROM.ShuiWeiJiZhi); //�洢����ֵ
}

void SetSWXZJZ(void)
{
  setnum num={RTU.XiuZhengJiZhi,0X53,Symbol,"m"};
  num.max = 99999;
  num.min = -99999;

  DisplayString(2,8,"ˮλ������ֵ",0);
  H_LINE(2,49,12);
  RTU.XiuZhengJiZhi = SetNum(num,4,32);
  WriteSInt32(RTU.XiuZhengJiZhi,EEPROM.XiuZhengJiZhi); //�洢����ֵ
}

void SetDTKEY_UPower(void)
{
  setstring settemp ={Com.PowerType,{"����","����","�Զ�",""}};

  DisplayString(4,8,"ͨ�ŵ�Դ",0);
  H_LINE(2,49,12);
  if(settemp.user>2)  //������Χ �ָ�Ĭ��ֵ �Զ�
  {
    settemp.user = 2;
  }
  Com.PowerType = SetString(settemp,6,32);
  WriteUInt8(Com.PowerType,EEPROM.ComPowerType);//��������ֵ
  if(Com.PowerType!=PAUTO)
  {
    OperComPort(&Com);
  }
}

void SetDTKEY_UPreheat(void)
{
  setnum num={Com.Preheat,0X30,0,"S"};
  num.max = 255;
  num.min = 0;

  DisplayString(4,8,"ͨ��Ԥ��",0);
  H_LINE(2,49,12);
  Com.Preheat = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Com.Preheat,EEPROM.ComPreheat);//��������ֵ
}

void SetDTUCloseDelay(void)
{
  setnum num={Com.CloseDelay,0X30,0,"S"};
  num.max = 255;
  num.min = 0;

  DisplayString(4,8,"������ʱ",0);
  H_LINE(2,49,12);
  Com.CloseDelay = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Com.CloseDelay,EEPROM.ComCloseDelay);//��������ֵ
}

void SetDTUTxdTime(void)
{
  setnum num={Com.TxdTime,0X20,0,"S"};
  num.max = 20;
  num.min = 0;

  DisplayString(4,8,"��ʱʱ��",0);
  H_LINE(2,49,12);
  Com.TxdTime = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Com.TxdTime,EEPROM.ComTxdTime);//��������ֵ
}

void SetDTUTxdMax(void)
{
  setnum num={Com.TxdMax,0X10,0," T"};
  num.max = 9;
  num.min = 0;

  DisplayString(4,8,"�ط�����",0);
  H_LINE(2,49,12);
  Com.TxdMax = (unsigned char)SetNum(num,6,32);
  WriteUInt8(Com.TxdMax,EEPROM.TxdMax);//��������ֵ
}

void SetDTUbps(void)
{
  setstring settemp ={Com.bps,{"1200","2400","4800","9600","19200","38400","57600","115200",""}};

  DisplayString(3,8,"ͨ�Ų�����",0);
  H_LINE(2,49,12);

  if(settemp.user>7) //������Χ �ָ�Ĭ��ֵ 9600
  {
    settemp.user = 3;
  }

  Com.bps = SetString(settemp,6,32);
  IniUart0(Com.bps); //��ʼ��ͨ�Ŵ���
  WriteUInt8(Com.bps,EEPROM.ComBps);//��������ֵ
}

void SetWaterChaliang(void)
{
  setnum num={RTU.WaterChaLiang,0X53,0,"m"};
  num.max = 50000;
  num.min = 0;

  DisplayString(4,8,"ˮλ����",0);
  H_LINE(2,49,12);
  RTU.WaterChaLiang = (unsigned int)SetNum(num,6,32);
  WriteUInt16(RTU.WaterChaLiang,EEPROM.WaterChaLiang); //�洢����ֵ
}

/*������������*/
void SetRainClear(void)
{
  uint8_t i=0;

  DisplayString(4,10,"��������?",0);

  while(1)
  {
    if(1==i)
      DisplayString(5,30,"��  ��",BITF+BITE);
    else
      DisplayString(5,30,"��  ��",BITB+BITA);

    WaitKey();  //�ȴ���������
    switch(key_event_handle)
    {
      case KEY_RIGHT:
      case KEY_LEFT: i = i==1?0:1;break;
      case KEY_SET: if(1==i)
                    RainfallClear();
      case KEY_RETURN: return;
      default :break;
    }
    if(KEY_TIME_OUT)
      return;
  }
}

void SetRS485bps(void)
{
  setstring settemp ={RS485Com.bps,{"1200","2400","4800","9600","19200","38400","57600","115200",""}};

  DisplayString(3,8,"����������",0);
  H_LINE(2,49,12);

  if(settemp.user>7) //������Χ �ָ�Ĭ��ֵ 9600
  {
    settemp.user = 3;
  }

  RS485Com.bps = SetString(settemp,6,32);
  IniUart1(RS485Com.bps); //��ʼ��ͨ�Ŵ���
  WriteUInt8(RS485Com.bps,EEPROM.RS485Bps);//��������ֵ
}

void SetRS485Power(void)
{
  setstring settemp ={RS485Com.PowerType,{"����","����","�Զ�",""}};

  DisplayString(4,8,"������Դ",0);
  H_LINE(2,49,12);
  if(settemp.user>2)  //������Χ �ָ�Ĭ��ֵ �Զ�
  {
    settemp.user = 2;
  }
  RS485Com.PowerType = SetString(settemp,6,32);
  WriteUInt8(RS485Com.PowerType,EEPROM.RS485PowerType);//��������ֵ
  if(RS485Com.PowerType!=PAUTO)
  {
    OperComPort(&RS485Com);
  }
}

void SetRS485Preheat(void)
{
  setnum num={RS485Com.Preheat,0X30,0,"S"};
  num.max = 255;
  num.min = 0;

  DisplayString(4,8,"����Ԥ��",0);
  H_LINE(2,49,12);
  RS485Com.Preheat = (unsigned char)SetNum(num,6,32);
  WriteUInt8(RS485Com.Preheat,EEPROM.RS485Preheat);//��������ֵ
}

void SetRS485CgqType(void)
{
  setnum num={RS485.CgqType,0X30,0,""};
  num.max = 255;
  num.min = 0;

  DisplayString(3,8,"����������",0);
  H_LINE(2,49,12);
  RS485.CgqType = (unsigned char)SetNum(num,6,32);
  WriteUInt8(RS485.CgqType,EEPROM.RS485CgqType);//��������ֵ
}

void SetRS485Name(void)
{
  DisplayString(4,8,"����Ҫ��",0);
  H_LINE(2,49,12);
  RS485.Name = SetYaoSu(RS485.Name,6,32);
  WriteUInt8(RS485.Name,EEPROM.RS485Name);
}

void SetTongDaoName_1(void)
{
  DisplayString(4,8,"����Ҫ��",0);
  H_LINE(2,49,12);
  Analog1.Name = SetYaoSu(Analog1.Name,6,32);
  WriteUInt8(Analog1.Name,EEPROM.TD1name);
}

void SetTongDaoName_2(void)
{
  DisplayString(4,8,"����Ҫ��",0);
  H_LINE(2,49,12);
  Analog2.Name = SetYaoSu(Analog2.Name,6,32);
  WriteUInt8(Analog2.Name,EEPROM.TD2name);
}

/*void SetTongDaoName_3(void)
{
  DisplayString(4,8,"����Ҫ��",0);
  H_LINE(2,49,12);
  Analog3.Name = SetYaoSu(Analog3.Name,6,32);
  WriteUInt8(Analog3.Name,EEPROM.TD3name);
}

void SetTongDaoName_4(void)
{
  DisplayString(4,8,"����Ҫ��",0);
  H_LINE(2,49,12);
  Analog4.Name = SetYaoSu(Analog4.Name,6,32);
  WriteUInt8(Analog4.Name,EEPROM.TD4name);
}*/

void SetTongDaoSType_1(void)
{
  setstring settemp ={Analog1.SType,{"4-20mA","0-2V",""}};

  DisplayString(4,8,"�����ź�",0);
  H_LINE(2,49,12);
  if(settemp.user>1)    //������Χ �ָ�Ĭ��ֵ4-20mA
  {
    settemp.user = 0;
  }
  Analog1.SType = SetString(settemp,6,32);
  WriteUInt8(Analog1.SType,EEPROM.TD1stype);//��������ֵ
}

void SetTongDaoSType_2(void)
{
  setstring settemp ={Analog2.SType,{"4-20mA","0-2V",""}};

  DisplayString(4,8,"�����ź�",0);
  H_LINE(2,49,12);
  if(settemp.user>1)    //������Χ �ָ�Ĭ��ֵ4-20mA
  {
    settemp.user = 0;
  }
  Analog2.SType = SetString(settemp,6,32);
  WriteUInt8(Analog2.SType,EEPROM.TD2stype);//��������ֵ
}

/*void SetTongDaoSType_3(void)
{
  setstring settemp ={Analog3.SType,{"4-20mA","0-2V",""}};

  DisplayString(4,8,"�����ź�",0);
  H_LINE(2,49,12);
  if(settemp.user>1)    //������Χ �ָ�Ĭ��ֵ4-20mA
  {
    settemp.user = 0;
  }
  Analog3.SType = SetString(settemp,6,32);
  WriteUInt8(Analog3.SType,EEPROM.TD3stype);//��������ֵ
}

void SetTongDaoSType_4(void)
{
  setstring settemp ={Analog4.SType,{"4-20mA","0-2V",""}};

  DisplayString(4,8,"�����ź�",0);
  H_LINE(2,49,12);
  if(settemp.user>1)    //������Χ �ָ�Ĭ��ֵ4-20mA
  {
    settemp.user = 0;
  }
  Analog4.SType = SetString(settemp,6,32);
  WriteUInt8(Analog4.SType,EEPROM.TD4stype);//��������ֵ
}*/

void SetTongDaoMax_1(void)
{
  setnum num={Analog1.Max,YaoSuInfo[Analog1.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"�������ֵ",0);
  H_LINE(2,49,12);
  Analog1.Max = SetNum(num,4,32);
  WriteSInt32(Analog1.Max,EEPROM.TD1max);//��������ֵ
}

void SetTongDaoMax_2(void)
{
  setnum num={Analog2.Max,YaoSuInfo[Analog2.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"�������ֵ",0);
  H_LINE(2,49,12);
  Analog2.Max = SetNum(num,4,32);
  WriteSInt32(Analog2.Max,EEPROM.TD2max);//��������ֵ
}

/*void SetTongDaoMax_3(void)
{
  setnum num={Analog3.Max,YaoSuInfo[Analog3.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"�������ֵ",0);
  H_LINE(2,49,12);
  Analog3.Max = SetNum(num,4,32);
  WriteSInt32(Analog3.Max,EEPROM.TD3max);//��������ֵ
}

void SetTongDaoMax_4(void)
{
  setnum num={Analog4.Max,YaoSuInfo[Analog4.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"�������ֵ",0);
  H_LINE(2,49,12);
  Analog4.Max = SetNum(num,4,32);
  WriteSInt32(Analog4.Max,EEPROM.TD4max);//��������ֵ
}*/

void SetTongDaoMin_1(void)
{
  setnum num={Analog1.Min,YaoSuInfo[Analog1.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"������Сֵ",0);
  H_LINE(2,49,12);
  Analog1.Min = SetNum(num,4,32);
  WriteSInt32(Analog1.Min,EEPROM.TD1min);//��������ֵ
}

void SetTongDaoMin_2(void)
{
  setnum num={Analog2.Min,YaoSuInfo[Analog2.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"������Сֵ",0);
  H_LINE(2,49,12);
  Analog2.Min = SetNum(num,4,32);
  WriteSInt32(Analog2.Min,EEPROM.TD2min);//��������ֵ
}

/*void SetTongDaoMin_3(void)
{
  setnum num={Analog3.Min,YaoSuInfo[Analog3.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"������Сֵ",0);
  H_LINE(2,49,12);
  Analog3.Min = SetNum(num,4,32);
  WriteSInt32(Analog3.Min,EEPROM.TD3min);//��������ֵ
}

void SetTongDaoMin_4(void)
{
  setnum num={Analog4.Min,YaoSuInfo[Analog4.Name].DataType,Symbol,""};
  num.max = 99999999;
  num.min = -99999999;

  DisplayString(3,8,"������Сֵ",0);
  H_LINE(2,49,12);
  Analog4.Min = SetNum(num,4,32);
  WriteSInt32(Analog4.Min,EEPROM.TD4min);//��������ֵ
}
*/
/*��ʾϵͳ��Ϣ*/
void SysInfo(void)
{
  DisplayString(2,8,Model,0);
  DisplayString(2,28,Version,0);
  WaitKey();  //�ȴ���������
}

/*���ûָ�����Ĭ������*/
void SetResetFactory(void)
{
  uint8_t i=0;

  DisplayString(2,10,"�ָ���������?",0);

  while(1)
  {
    if(1==i)
      DisplayString(5,30,"��  ��",BITF+BITE);
    else
      DisplayString(5,30,"��  ��",BITB+BITA);

    WaitKey();  //�ȴ���������
    switch(key_event_handle)
    {
      case KEY_RIGHT:
      case KEY_LEFT: i = i==1?0:1;break;
      case KEY_SET: if(1==i)
                  {
                    DefaultConfig();
                    RainfallClear();
                    WriteConfig();
                  }
      case KEY_RETURN: return;
      default :break;
    }
    if(KEY_TIME_OUT)
      return;
  }
}


/*����ָ������ʱ��*/
void settimetype(uint8_t type,uint8_t H,uint8_t Ver)
{
  unsigned int  con=0X8000;     //���׿���
  uint8_t  i;             //����λѡ��
  uint8_t  max;           //�ܹ����õ����ֵ
  uint8_t  min;           //�ܹ����õ���Сֵ
  uint8_t  vale;          //�����ǰֵ
  uint8_t  valetemp;      //������ֵ�ı��洢

  ReadTime(&System.Time);                       //���µ�ǰʱ��
  switch(type)  //��ʼ��������
  {
    case H_YEAR:  max = 99; min = 0; vale = System.Time.H_YEAR;
          break;
    case H_MONTH:  max = 12; min = 1; vale = System.Time.H_MONTH;
          break;
    case H_DAY:  max = TimeH_DAYmax(System.Time); min = 1;vale = System.Time.H_DAY;
          break;
    case H_HOUR:  max = 23; min = 0; vale = System.Time.H_HOUR;
          break;
    case H_MINUTE:max = 59; min = 0; vale = System.Time.H_MINUTE;
          break;
    case H_SECOND:max = 59; min = 0; vale = System.Time.H_SECOND;
          break;
    default :break;

  }
  valetemp = vale;    //�����õ�ֵ��ʼ��Ϊ��ǰֵ
  i = 1;              //��ʼ������λ��Ϊʮλ
  while(1)
  {
    if(1==i)
      con = BITF;
    else
      con = BITE;

    if(valetemp > max) //����ֵ������Χ����
    {
      valetemp = min;
    }
    else if(valetemp < min)
    {
      valetemp = max;
    }

    DisplayNum(H,Ver,valetemp,0X20,Zero,"",con);   //��ʾ����ֵ

    WaitKey();     //�ȴ���������

      switch(key_event_handle)
      {
        case KEY_SET:  PCF8563writeData(type,(((valetemp/10)<<4) + (valetemp%10)));   //����ʱ��
              DisplayNum(H,Ver,valetemp,0X20,Zero,"",0);    //��ʾ���ú��ֵ
              ReadTime(&System.Time);
              return ;

        case KEY_RETURN:  DisplayNum(H,Ver,vale,0X20,Zero,"",0);     //û��ȷ������ ��ʾ��ʼֵ
              return ;

        case KEY_UP:  if(1 == i)          //����ֵ����
                valetemp += 10;
              else
                valetemp++;
              break;

        case KEY_DOWN:  if(valetemp == 0)//����ֵ��С
              {
                valetemp = max;      //����ֵΪ0ʱ �ټ�С���Ϊ���ֵ
              }
              else
              {
                if(1 == i)           //��ǰѡ��Ϊʮλʱ
                {
                  if(valetemp < 10)  //����ֵС��10
                  {
                    valetemp = max;    //�ټ�С���Ϊ���ֵ
                  }
                  else
                    valetemp -= 10;     //����ֵ��С10
                }
                else
                  valetemp--;           //��ǰѡ��Ϊ��λʱ ����ֵ��С1
              }
              break;

        case KEY_LEFT:  if(--i < 1) i = 2;     //�û�ѡ������
              break;

        case KEY_RIGHT:  if(++i > 2) i = 1;    //�û�ѡ������
              break;
        default :break;
      }
      if(KEY_TIME_OUT)       //�ȴ�������ʱ
        return;
  }
}

/*ʱ������*/
void SetClock(void)
{
  uint8_t i;
  uint8_t UserChoose=1;  //�û�ѡ��

  ReadTime(&System.Time);                       //���µ�ǰʱ��

  DisplayNum(5,8,System.Time.H_YEAR,0X20,Zero,"",0);   //��ʼ����ʾ�����õ�ʱ��
  DisplayNum(5,24,System.Time.H_MONTH,0X20,Zero,"",0);
  DisplayNum(5,40,System.Time.H_DAY,0X20,Zero,"",0);
  DisplayNum(13,8,System.Time.H_HOUR,0X20,Zero,"",0);
  DisplayNum(13,24,System.Time.H_MINUTE,0X20,Zero,"",0);
  DisplayNum(13,40,System.Time.H_SECOND,0X20,Zero,"",0);

  while(1)
  {
    for(i=1;i<7;i++)    //�û�ѡ����ʾ
    {
      if(i == UserChoose)     //����ʾ�û�ѡ����ʱ
      {
        DisplayString(TimeSet[i-1].stringadd_x,TimeSet[i-1].stringadd_y,TimeSet[i-1].string,0XC000); // ����
      }
      else
      {
        DisplayString(TimeSet[i-1].stringadd_x,TimeSet[i-1].stringadd_y,TimeSet[i-1].string,0);   //������ʾ
      }
    }

    WaitKey();     //�ȴ���������

      switch(key_event_handle)
      {         //ȷ������ �������������
        case KEY_SET: (*TimeSet[UserChoose-1].Subs)(TimeSet[UserChoose-1].type,TimeSet[UserChoose-1].disadd_x,TimeSet[UserChoose-1].disadd_y);
              break;
        case KEY_RETURN: return;         //�˳�����
        case KEY_DOWN:  if(++UserChoose > 6) UserChoose = 1;   break;   //�û�ѡ�����
        case KEY_UP:  if(--UserChoose < 1) UserChoose = 6;   break;   //�û�ѡ��ݼ�
        case KEY_RIGHT:

        case KEY_LEFT:  if(UserChoose > 3)      //�û���Ծ����ѡ��
              {
                UserChoose -=3;
              }
              else
              {
                 UserChoose +=3;
              }
              break;
        default :break;
      }
      if(KEY_TIME_OUT)  //�ȴ�������ʱ
      {
        lcd_clear_ddram();
        return;
      }
  }
}

/*���ð�װ�߶�*/
void SetHeight(void)
{
  setnum num={Height,0X53,0,"m"};
  num.max = 50000;
  num.min = 0;

  lcd_clear_ddram();
  DisplayString(4,8,"��װ�߶�",0);
  H_LINE(2,49,12);
  Height = (unsigned int)SetNum(num,5,32);
  WriteUInt16(Height,EEPROM.AnZhuangGaoDu);//��������ֵ
  lcd_clear_ddram();
}
