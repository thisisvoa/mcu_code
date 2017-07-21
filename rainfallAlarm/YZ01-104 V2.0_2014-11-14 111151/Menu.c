/*********************************************************
*�ļ����ƣ�Menu.c
*ժ    Ҫ���˵����ù��ܶ���
* 
*��    �ߣ� ����
*��ʼ���ڣ� 2013��10��11�� 
*������ڣ�
**********************************************************/

#include "menu.h" 

const struct Menu MainMenu[5]={            //���˵� 
{5,4,"ϵͳ����",Null,(struct Menu*)SysSetMenu,Null},
{5,4,"��������",AlarmValueSet,Null,Null},
{5,4,"ϵͳ��Ϣ",SysInfo,Null,Null},
{5,4,"�ָ�����",SetResetFactory,Null,Null},
{5,4,"ϵͳ�Լ�",SystemSelfTestMenu,Null,Null},
};

const struct Menu SysSetMenu[3]={            //ϵͳ���� 
{3,4,"�����ֱ���",SetYLJFBL,Null,(struct Menu*)MainMenu},
{3,4,"ʱ������",SetClock,Null,(struct Menu*)MainMenu},
{3,4,"��������",SetRainClear,Null,(struct Menu*)MainMenu},
};

const struct TimeSetMenu TimeSet[6]={   //ʱ������
{year,2,8,"��",5,8,settimetype},
{month,2,24,"��",5,24,settimetype},
{day,2,40,"��",5,40,settimetype},
{hour,10,8,"ʱ",13,8,settimetype},
{minute,10,24,"��",13,24,settimetype},
{second,10,40,"��",13,40,settimetype}
};

const AlarmSetClass AlarmSet[11]={
{&Alarm.PN05,AT_PN05I,AT_PN05II,AT_PN05III},
{&Alarm.PN10,AT_PN10I,AT_PN10II,AT_PN10III},
{&Alarm.PN30,AT_PN30I,AT_PN30II,AT_PN30III},
{&Alarm.P1,AT_P1I,AT_P1II,AT_P1III},
{&Alarm.P3,AT_P3I,AT_P3II,AT_P3III},
{&Alarm.P6,AT_P6I,AT_P6II,AT_P6III},
{&Alarm.P12,AT_P12I,AT_P12II,AT_P12III},
{&Alarm.P24,AT_P24I,AT_P24II,AT_P24III},
{&Alarm.PJ,AT_PJI,AT_PJII,AT_PJIII},
{&Alarm.P,AT_PI,AT_PII,AT_PIII},
{&Alarm.PT,AT_PTI,AT_PTII,AT_PTIII}
};

/*��������*/
void AlarmValueSet(void)
{
  char x=0;
  char y=1;

  setnum num={0,0X51,0,"mm",50000,0};
  
  ClearScreen;       //����
  while(True)
  {
    
    Draw(0,1,2,9,0,leftarrow);//���ͷ
    Draw(14,1,2,9,0,rightarrow);//�Ҽ�ͷ
    switch(x)
    {
      case 0: DisplayString(3,0," 5��������",0); break;
      case 1: DisplayString(3,0,"10��������",0); break;
      case 2: DisplayString(3,0,"30��������",0); break;
      case 3: DisplayString(3,0," 1Сʱ����",0); break;
      case 4: DisplayString(3,0," 3Сʱ����",0); break;
      case 5: DisplayString(3,0," 6Сʱ����",0); break; 
      case 6: DisplayString(3,0,"12Сʱ����",0); break; 
      case 7: DisplayString(3,0,"24Сʱ����",0); break;
      case 8: DisplayString(3,0," �������� ",0); break;
      case 9: DisplayString(3,0," �������� ",0); break;
      case 10: DisplayString(3,0," �ۼ����� ",0); break;  
    }
    DisplayString(0,16,"����ת��",0);
    DisplayString(0,32,"׼��ת��",0);
    DisplayString(0,48,"���䱨��",0);
    
    switch(y)
    {
      case 1:
        {
          DisplayString(0,16,"����ת��",0XFFFF);
        }
        break;
      case 2:
        {
          DisplayString(0,32,"׼��ת��",0XFFFF);
        }
        break;
      case 3:
        {
          DisplayString(0,48,"���䱨��",0XFFFF);         
        }
        break;
    }
    DisplayNum(8,16,AlarmSet[x].pA->I,0X51,space,"mm",0);
    DisplayNum(8,32,AlarmSet[x].pA->II,0X51,space,"mm",0);
    DisplayNum(8,48,AlarmSet[x].pA->III,0X51,space,"mm",0);
    
    WaitKey();
    
    switch(System.Key)
    {
      case Up:  
        {
          if(--y < 1)
            y = 3;
        }
        break;
      case Down: 
        {
          if(++y > 3)
            y = 1;
        }
        break;
      case Right: 
        {
          if(++x > 10)
            x = 0;
        }
        break;
      case Left: 
        {
          if(0==x)
            x = 10;
          else
            x--;
        }
        break;
      case Esc: 
        {
          return;
        }
        break;
      case Enter: 
        {
          if(1==y)
          {
            num.value = AlarmSet[x].pA->I;
            AlarmSet[x].pA->I = (unsigned int)SetNum(num,8,16);
            WriteUInt16(AlarmSet[x].pA->I,AlarmSet[x].at_i,0);
          }
          else if(2==y)
          {
            num.value = AlarmSet[x].pA->II;
            AlarmSet[x].pA->II = (unsigned int)SetNum(num,8,32);
            WriteUInt16(AlarmSet[x].pA->II,AlarmSet[x].at_ii,0);
          }
          else if(3==y)
          {
            num.value = AlarmSet[x].pA->III;
            AlarmSet[x].pA->III = (unsigned int)SetNum(num,8,48);
            WriteUInt16(AlarmSet[x].pA->III,AlarmSet[x].at_iii,0);
          }
        }
        break;
    }
    if(Display.Status.Flag.KeyOut)
      return; 
    
  }
  
}




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
  ClearScreen;
  if(0!=PassWord())
  {
    SetMenu();  
  }
  SC_Reset();
  System.Key = Null;
  ReadTime(&System.Time); 
  ClearScreen;
  DisplayMon();      //��ʾ������
  Display.Status.Flag.KeyOut = RESET;
  Display.Status.Flag.SetMode = RESET;

}

/*******************************************************************************
�������ƣ�void ShowMenu(Menu *MenuUser,char DisplayPoint,char refresh)
�������ܣ���ʾ�˵�
���������Menu *MenuUser---->��ʾ�˵���ַ
          DisplayPoint----->��ʾ��
          UserChoose------->��ǰ�û�ѡ��
          USER------------->ǰһ���û�ѡ��
          refresh---------->ȫ��ˢ�±�־
�����������
����ֵ  ����
*******************************************************************************/
void ShowMenu(struct Menu *MenuUser,char DisplayPoint,signed char USER,signed char UserChoose,char refresh)
{
    char i=0;
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
  char i=0;                    //�˵��㼶
  signed char UserChoose = 0;           //��ǰ�û�ѡ��
  signed char USER=0;                   //ǰһ���û�ѡ�� 
  char  DisplayPoint = 0;      //��ʾ��
  char  RefreshMenu = 1;       //ˢ�²˵���־
  struct Menu *MenuPoint = (struct Menu*)MainMenu; 
  
  ClearScreen;   
  while(1)
  {      
    ShowMenu(MenuPoint,DisplayPoint,USER,UserChoose,RefreshMenu);         //��ʾĿ¼
  
    WaitKey();     //�ȴ��������� 
     
      switch(System.Key)
      {
        case Up:
                USER = UserChoose;                      //����ǰһ���û�ѡ��
                UserChoose--;                           //�û�ѡ������
                if(UserChoose < 0)                      //��ǰ�û�ѡ��Ϊ��һ��ʱ ������ѡ��
                {
                  UserChoose = MenuPoint[0].MenuCount - 1;           //�û�ѡ��ָ�����һ��
                  if(MenuPoint[0].MenuCount > 4)                     //�˵����ȴ�����ʾ���������
                  {
                    ClearScreen;                      //����
                    RefreshMenu = 1;
                  }
                }
                else if(((UserChoose+1)%4)==0)          //���Ϸ�ҳ
                {
                  ClearScreen; 
                  RefreshMenu = 1;
                }
                break;   
        case Down:                                      //�û�����ѡ��
                USER = UserChoose;                      //����ǰһ���û�ѡ��
                UserChoose++;
                if(UserChoose >= MenuPoint[0].MenuCount)             //�û�ѡ����ڲ˵�����
                {
                  UserChoose = 0;                       //�û�ѡ��ָ������
                  if(MenuPoint[0].MenuCount > 4) 
                  {
                    ClearScreen;
                    RefreshMenu = 1;
                  }
                }
                break;
    
        case Esc:                                       //�����ϼ��˵�
                if(MenuPoint == MainMenu)               //��ǰ�˵�Ϊ���˵�ʱ �˳��˵�
                {   
                  return;
                }    
                else if(MenuPoint[0].PreviousMenu != Null)
                {
                  MenuPoint = MenuPoint[0].PreviousMenu;
                  UserChoose = user[--i]; //�ָ��ϼ��˵��û�ѡ��
                  ClearScreen;
                  RefreshMenu = 1;
                }    
                break;
    
        case Enter:                                             //������һ���˵�������                            
                if(MenuPoint[UserChoose].Subs != Null)          //�����Ӧ����
                {
                  ClearScreen;
                  (*MenuPoint[UserChoose].Subs)();
                }
                else if(MenuPoint[UserChoose].SubMenu != Null)  //������һ���˵�
                {
                  MenuPoint=MenuPoint[UserChoose].SubMenu;
                  user[i++] = UserChoose;     //���浱ǰ�˵����û�ѡ��
                  UserChoose = 0;                                                     
                } 
                RefreshMenu = 1;
                ClearScreen;
                break;      
      }                     
      
    DisplayPoint = UserChoose-UserChoose%4;     // 4 ָ��Ļ��ʾ�������
    if((UserChoose+USER)%8 == 7)                // ���·�ҳʱ����
    {
      ClearScreen;
      RefreshMenu = 1;
    }
    if(Display.Status.Flag.KeyOut)              //�ȴ�������ʱ ���ؼ�����
    {  
      Display.Status.Flag.KeyOut = False;
      ClearScreen;
      return;
    }      
  }    
}


/*�ȴ�����*/
void WaitKey(void)
{
  unsigned int i=0;
  
  System.Key = Null; 
  while(!System.Key)
  {
    delayms(1);
    if(i++ > 30000)
    {
      Display.Status.Flag.KeyOut = True;
      System.Key = Null;
      return;
    }      
  }
}

/*******************************************************************************
�������ƣ�long int SetNum(setnum num,char H,char Ver)
�������ܣ���������
���������setnum num----->�����������ݽṹ ������menu.h
          H-------------->��ʾˮƽ����
          Ver------------>��ʾ��ֱ����
�����������
����ֵ  �� �û������ֵ

*******************************************************************************/
long int SetNum(setnum num,char H,char Ver)
{
  char strnum[15]={0};
  char i=0,j=0,k=0;
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
    
    switch(System.Key)
    {
      case Up:  if('+'==strnum[user])
                  strnum[user] = '-';
                else if(('-'==strnum[user]))
                  strnum[user] = '+';
                else if(++strnum[user]>'9')
                  strnum[user] = '0';
                break;
      case Down: if('+'==strnum[user])
                   strnum[user] = '-';
                 else if(('-'==strnum[user]))
                   strnum[user] = '+';
                 else if(--strnum[user]<'0')
                   strnum[user] = '9';
                 break;
      case Right: user++;
                  if('.'==strnum[user])
                    user++;
                  else if((strnum[user]>'9')||(strnum[user]<'0'))
                    user = 0;
                  break;
      case Left:  user--;
                  if(user<0)
                    user = k-1;
                  else if('.'==strnum[user])
                    user--;
                  break;
      case Esc:   return num.value;
      case Enter:  
                  num.value = String_TO_SInt32(strnum);
                  Draw(H,Ver,16,16,0,Null);
                  if(num.value > num.max)
                    num.value = num.max;
                  else if(num.value < num.min)
                    num.value = num.min;
                  return num.value;
    }
    
    if(Display.Status.Flag.KeyOut)    //�ȴ�������ʱ
      return num.value;
  }
}

/*******************************************************************************
�������ƣ�char SetString(setstring s,char H,char Ver)
�������ܣ�ѡ���ַ�
���������setstring s----->�ṩ�Ĵ�ѡ��
          H--------------->ˮƽ��ʾ��ַ
          Ver------------->��ֱ��ʾ��ַ
�����������
����ֵ  ���û�ѡ������
*******************************************************************************/
char SetString(setstring s,char H,char Ver)
{
  char i=0,j=0;
  
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
    
    switch(System.Key)
    {
      case Up:  Draw(H,Ver,strlenght(s.str[s.user]),16,0,Null);
                s.user++;
                if(s.user > i)
                  s.user = 0;               
                break;
      case Down: Draw(H,Ver,strlenght(s.str[s.user]),16,0,Null);
                if(0==s.user)
                   s.user = i; 
                 else
                   s.user--;                                            
                 break;
      case Esc: return j;
      case Enter:    
                return s.user;
    }
    if(Display.Status.Flag.KeyOut)
      return j;  
  } 
}


char PassWord(void)
{
  long x=0;
  setnum num={0,0X60,0,"\0"};
  
  DisplayString(4,16,"��������",0);
         
  num.max = 9999999;
  num.min = 0; 
  x = SetNum(num,5,32);
    
  if(Display.Status.Flag.KeyOut)
      return 0;    
  if(UserPass == x)
    return 2;
  if(AdminPass == x)
    return 1;
  
  return 0;
}

/*����ָ������ʱ��*/
void settimetype(char type,char H,char Ver)
{
  unsigned int  con=0X8000;     //���׿���
  char  i;             //����λѡ��  
  char  max;           //�ܹ����õ����ֵ
  char  min;           //�ܹ����õ���Сֵ
  char  vale;          //�����ǰֵ
  char  valetemp;      //������ֵ�ı��洢

  ReadTime(&System.Time);                       //���µ�ǰʱ��  
  switch(type)  //��ʼ��������  
  {
    case year:  max = 99; min = 0; vale = System.Time.Year;
          break;
    case month:  max = 12; min = 1; vale = System.Time.Month;
          break;
    case day:  max = Timedaymax(System.Time); min = 1;vale = System.Time.Day;                              
          break;
    case hour:  max = 23; min = 0; vale = System.Time.Hour;
          break;
    case minute:max = 59; min = 0; vale = System.Time.Minute;
          break;
    case second:max = 59; min = 0; vale = System.Time.Second;
          break;          
    
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
    
      switch(System.Key)
      {
        case Enter:  PCF8563writeData(type,(((valetemp/10)<<4) + (valetemp%10)));   //����ʱ��
              DisplayNum(H,Ver,valetemp,0X20,Zero,"",0);    //��ʾ���ú��ֵ            
              return ;
            
        case Esc:  DisplayNum(H,Ver,vale,0X20,Zero,"",0);     //û��ȷ������ ��ʾ��ʼֵ
              return ;
              
        case Up:  if(1 == i)          //����ֵ����    
                valetemp += 10;
              else
                valetemp++;
              break;

        case Down:  if(valetemp == 0)      //����ֵ��С
              {
                valetemp = max;      //����ֵΪ0ʱ �ټ�С���Ϊ���ֵ
              }
              else
              {
                if(1 == i)       //��ǰѡ��Ϊʮλʱ
                {
                  if(valetemp < 10)  //����ֵС��10
                  {
                    valetemp = max;    //�ټ�С���Ϊ���ֵ
                  }
                  else
                    valetemp -= 10;     //����ֵ��С10
                }
                else
                  valetemp--;      //��ǰѡ��Ϊ��λʱ ����ֵ��С1
              }            
              break;

        case Left:  if(--i < 1) i = 2;     //�û�ѡ������
              break;

        case Right:  if(++i > 2) i = 1;    //�û�ѡ������            
              break;
      }
      if(Display.Status.Flag.KeyOut)  //�ȴ�������ʱ
        return;
  }   
}

/*ʱ������*/
void SetClock(void)
{
  char i;
  char UserChoose=1;  //�û�ѡ��
  
  ReadTime(&System.Time);                       //���µ�ǰʱ��  
  
  DisplayNum(5,8,System.Time.Year,0X20,Zero,"",0);   //��ʼ����ʾ�����õ�ʱ��
  DisplayNum(5,24,System.Time.Month,0X20,Zero,"",0);
  DisplayNum(5,40,System.Time.Day,0X20,Zero,"",0);
  DisplayNum(13,8,System.Time.Hour,0X20,Zero,"",0);
  DisplayNum(13,24,System.Time.Minute,0X20,Zero,"",0);
  DisplayNum(13,40,System.Time.Second,0X20,Zero,"",0);

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
       
      switch(System.Key)
      {         //ȷ������ �������������
        case Enter: (*TimeSet[UserChoose-1].Subs)(TimeSet[UserChoose-1].type,TimeSet[UserChoose-1].disadd_x,TimeSet[UserChoose-1].disadd_y);    
              
                  break;
        case Esc: return;         //�˳�����
        case Down:  if(++UserChoose > 6) UserChoose = 1;   break;   //�û�ѡ�����
        case Up:  if(--UserChoose < 1) UserChoose = 6;   break;   //�û�ѡ��ݼ�
        case Right:  
            
        case Left:  if(UserChoose > 3)      //�û���Ծ����ѡ��
              {
                UserChoose -=3;
              }
              else
              { 
                 UserChoose +=3;
              }
              break; 
      }
      if(Display.Status.Flag.KeyOut)  //�ȴ�������ʱ
      {
        ClearScreen;
        return;
      }
  }
}

/*******************************************************************************
�������ƣ�void SetYLJFBL(void)
�������ܣ����������Ʒֱ���
�����������
��������������Ʒֱ���
����ֵ  ����
*******************************************************************************/
void SetYLJFBL(void)
{
  setnum num={Rainfall.Resolution,0X21,0,"mm",99,0}; 
  
  DisplayString(4,8,"�����ֱ���",0);
  H_LINE(2,49,12);
  Rainfall.Resolution = (char)SetNum(num,6,32);  
  WriteUInt8(Rainfall.Resolution,AT_FBL,0);//��������ֵ 
}

/*������������*/
void SetRainClear(void)
{
  char i=0;
  
  DisplayString(4,10,"��������?",0);
  
  while(1)
  {
    if(1==i)
      DisplayString(5,30,"��  ��",BITF+BITE);
    else
      DisplayString(5,30,"��  ��",BITB+BITA);
    
    WaitKey();  //�ȴ���������
    switch(System.Key)
    {
      case Right: 
      case Left: i = i==1?0:1;break;
      case Enter: if(1==i)
                  {
                    RainfallClear();
                     
                  }
                    
                  
      case Esc: return;
    }
    if(Display.Status.Flag.KeyOut)
      return;         
  } 
}


/*��ʾϵͳ��Ϣ*/
void SysInfo(void)
{
  DisplayString(1,8,"YZ3000 V2.0",0);
  //DisplayString(1,28,"V2.0_20140918",0);
  WaitKey();  //�ȴ���������
}

/*���ûָ�����Ĭ������*/
void SetResetFactory(void)
{
  char i=0;
  
  DisplayString(2,10,"�ָ���������?",0);
  
  while(1)
  {
    if(1==i)
      DisplayString(5,30,"��  ��",BITF+BITE);
    else
      DisplayString(5,30,"��  ��",BITB+BITA);
    
    WaitKey();  //�ȴ���������
    switch(System.Key)
    {
      case Right: 
      case Left: i = i==1?0:1;break;
      case Enter: if(1==i)
                  {
                    ResetFactory(); 
                  }
                    
      case Esc: return;
    }
    if(Display.Status.Flag.KeyOut)
      return;         
  } 
}

void SystemSelfTestMenu(void)
{
  SystemSelfTest();
  ATcmd_LedTest();
}

/*д���������ò���*/
/*void WriteConfig(void)
{
  
}*/

/*�ָ�����Ĭ������*/
void ResetFactory(void)
{
  RainfallClear();      //��������
  DefaultConfig();      //���ò����ָ�ΪԤ��ֵ
  
}
/*�����ָ�ΪĬ��ֵ*/
void DefaultConfig(void)
{
 
  Rainfall.Resolution = 5;
  Alarm.PN05.I = Alarm.PN05.II = Alarm.PN05.III = 0;
  Alarm.PN10.I = Alarm.PN10.II = Alarm.PN10.III = 0;
  Alarm.PN30.I = Alarm.PN30.II = Alarm.PN30.III = 0;
  Alarm.P1.I = Alarm.P1.II = Alarm.P1.III = 0;
  Alarm.P3.I = Alarm.P3.II = Alarm.P3.III = 0;
  Alarm.P6.I = Alarm.P6.II = Alarm.P6.III = 0;
  Alarm.P12.I = Alarm.P12.II = Alarm.P12.III = 0;
  Alarm.P24.I = Alarm.P24.II = Alarm.P24.III = 0;
  Alarm.P.I = Alarm.P.II = Alarm.P.III = 0;
  Alarm.PJ.I = Alarm.PJ.II = Alarm.PJ.III = 0;
  Alarm.PT.I = Alarm.PT.II = Alarm.PT.III = 0;
  Flash.Page = 1;
  Flash.Bytes = 2;
  
  WriteUInt8(Rainfall.Resolution,AT_FBL,0);
  
  WriteUInt16(Alarm.PN05.I,AT_PN05I,0);
  WriteUInt16(Alarm.PN05.II,AT_PN05II,0);
  WriteUInt16(Alarm.PN05.III,AT_PN05III,0);
  WriteUInt16(Alarm.PN10.I,AT_PN10I,0);
  WriteUInt16(Alarm.PN10.II,AT_PN10II,0);
  WriteUInt16(Alarm.PN10.III,AT_PN10III,0);
  WriteUInt16(Alarm.PN30.I,AT_PN30I,0);
  WriteUInt16(Alarm.PN30.II,AT_PN30II,0);
  WriteUInt16(Alarm.PN30.III,AT_PN30III,0);
  WriteUInt16(Alarm.P1.I,AT_P1I,0);
  WriteUInt16(Alarm.P1.II,AT_P1II,0);
  WriteUInt16(Alarm.P1.III,AT_P1III,0);
  WriteUInt16(Alarm.P3.I,AT_P3I,0);
  WriteUInt16(Alarm.P3.II,AT_P3II,0);
  WriteUInt16(Alarm.P3.III,AT_P3III,0);
  WriteUInt16(Alarm.P6.I,AT_P6I,0);
  WriteUInt16(Alarm.P6.II,AT_P6II,0);
  WriteUInt16(Alarm.P6.III,AT_P6III,0);
  WriteUInt16(Alarm.P12.I,AT_P12I,0);
  WriteUInt16(Alarm.P12.II,AT_P12II,0);
  WriteUInt16(Alarm.P12.III,AT_P12III,0);
  WriteUInt16(Alarm.P24.I,AT_P24I,0);
  WriteUInt16(Alarm.P24.II,AT_P24II,0);
  WriteUInt16(Alarm.P24.III,AT_P24III,0);
  WriteUInt16(Alarm.P.I,AT_PI,0);
  WriteUInt16(Alarm.P.II,AT_PII,0);
  WriteUInt16(Alarm.P.III,AT_PIII,0);
  WriteUInt16(Alarm.PJ.I,AT_PJI,0);
  WriteUInt16(Alarm.PJ.II,AT_PJII,0);
  WriteUInt16(Alarm.PJ.III,AT_PJIII,0);
  WriteUInt16(Alarm.PT.I,AT_PTI,0);
  WriteUInt16(Alarm.PT.II,AT_PTII,0);
  WriteUInt16(Alarm.PT.III,AT_PTIII,0);
  WriteUInt16(Flash.Page,AT_PAGE,0);
  WriteUInt16(Flash.Bytes,AT_BYTE,0);
}

