/*********************************************************
*�ļ����ƣ�ST7920.c
*ժ    Ҫ��ST7920��ͼģʽ����(����)
*
*��    �ߣ�����
*��ʼ���ڣ�2012��11��26��
*          2014-03-24 ������ˮƽ��ַ��ʼдʱ������ԭ��ʾGDRAM��
���ݣ�������д�룬ԭ���İ汾��д��0X00��
          2014��4��23�� ����ʾ���ֵȺ����������ļ��м���
**********************************************************/
#include "ST7920.h"
#include "Public.h"
#include "include.h"
/*******************************************
�������ƣ�ST7920WriteCmd
��    �ܣ���Һ����д��������
��    ����cmd--��������
����ֵ  ����
********************************************/
void ST7920WriteCmd(char cmd)
{
  char lcdtemp = 0;
  unsigned int error=0XFFFF;

  LCD_RS_L;
  LCD_RW_H;
  LCD_DataIn;  
  do                       //��æ
  {    
    LCD_EN_H;
    _NOP();					
    lcdtemp = LCD2MCU_Data; 
    LCD_EN_L;
    error--;  
  }
  while((lcdtemp & 0x80) && error); 
    
    LCD_DataOut;    
    LCD_RW_L;  		
    MCU2LCD_Data = cmd; 
    LCD_EN_H;
    _NOP();						  			
    LCD_EN_L;  
}

/*******************************************
�������ƣ�ST7920WriteData
��    �ܣ���Һ����д��ʾ����
��    ����dat--��ʾ����
����ֵ  ����
********************************************/
void  ST7920WriteData(char dat)
{
    char lcdtemp = 0; 
    unsigned int error=0XFFFF;
       
    LCD_RS_L;
    LCD_RW_H;  
    LCD_DataIn;   
    do                       //��æ
    {    
        LCD_EN_H;
        _NOP();						
        lcdtemp = LCD2MCU_Data; 
        LCD_EN_L;  
        error--;
    }
    while((lcdtemp & 0x80) && error);  
    
    LCD_DataOut; 
    LCD_RS_H;
    LCD_RW_L;  
        
    MCU2LCD_Data = dat;
    LCD_EN_H;
    _NOP();
    LCD_EN_L;
} 

/*******************************************
�������ƣ�unsigned char ST7920ReadData(void)
��    �ܣ���Һ������ʾ����
��    ������
����ֵ  ����ǰ��ַ��ʾ����
********************************************/
char ST7920ReadData(void)
{
    char lcdtemp = 0; 
    unsigned int error=0XFFFF;
       
    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;   
    do                       //��æ
    {    
        LCD_EN_H;
        _NOP();				
        lcdtemp = LCD2MCU_Data;
        LCD_EN_L;
        error--;
    }
    while((lcdtemp & 0x80) && error);  
    
    LCD_RS_H;
    LCD_RW_H;  
    LCD_EN_H;	
    lcdtemp = 0;  
    _NOP(); 
    lcdtemp = LCD2MCU_Data;

    LCD_EN_L;
    return lcdtemp;
} 
/*******************************************
�������ƣ�Ini_Lcd
��    �ܣ���ʼ��Һ��ģ��
��    ������
����ֵ  ����
********************************************/
void Ini_Lcd(void)
{     
    LCD_CMDOut;                                 //Һ�����ƶ˿�����Ϊ���   
    LCD_LIGHT_ON;                               //���⿪��         
    Display.Status.Flag.Light = True;           //LCD�����־
    ST7920delayms(50);
    LCD_POWER_ON;                               //LCD��Դ����
    Display.Status.Flag.Power = True;           //LCD��Դ��־
    //ST7920delayms(500);
    System.Temp = Readtemp(Do1Convert());          //���¶�
    ST7920WriteCmd(0x34);                       //��չָ�
    ClearScreen;                                //���� 
    DISPLAYON;                                  //��ʾ���ܿ�
    Display.TiOFF = OFFLCDDELAY;
    IniUart0(BPS_9600);
}

/*********************************************************************
                    ��ʾ�ַ��� 
H----------- ˮƽ����
Ver--------- ��ֱ����
*str  ------ �ַ�����ַ
DecimalPoint  ���׿���    
DecimalPoint��ĳһλΪ 1 ʱ ��λ��Ӧ���ַ�������ʾ

DecimalPoint  BIT15 BIT14 BIT13 BIT12 BIT11 BIT10 BIT9 BIT8 BIT7 BIT6 BIT5 BIT4  BIT3 BIT2 BIT1 BIT0 
�ַ�λ��        0     1     2     3     4     5     6    7    8    9   11   10    12   13   14   15   

Խ�紦�������߽粻��ʾ
*********************************************************************/
void DisplayString(char H,char Ver,char *str,unsigned int DecimalPoint)
{
  char i,j,k;
  char xadd,yadd;        //��ͼ����
  char coding;           //ASC2�뻺��
  char *strtemp;         //�ַ������ַ���� 
  unsigned int GBcoding;          //GB2312�뻺��
  char Hleng=0;          //���д�볤��
  char temp=0;
  
  Coordinate(H,Ver,&xadd,&yadd);    //�����е�ַ���е�ַ�����ͼ x���� y����
    
  for(i=0;i<16;i++)
  {          
    strtemp = str;
    Hleng = 16 - H;
    ST7920WriteCmd(yadd);    	                // дY����
    ST7920WriteCmd(xadd);       		// дX����
    
    if((H % 2) == 1 )                           // ˮƽ����Ϊ��������ԭGDRAM���ֽ���ʾ����
    {         
      ST7920ReadData();                         //2014-03-24 �޸�
      temp = ST7920ReadData();
      ST7920WriteCmd(yadd);    	                // дY����
      ST7920WriteCmd(xadd);       		// дX����
      ST7920WriteData(temp);
    }    
    yadd++;                                     //��ֱ��ͼ����++
    if(yadd > 0X9F)                             //�������л�
    {    
      xadd -= 8;                                
      yadd = 0X80;
    }        
    else if((yadd > 0X8F) && (xadd <= 0X8F))    //�ı�ˮƽ��ͼ����
    {
      xadd += 16;
    }
    
    for(j=0;j<Hleng;)
    {		 
      if('\0' == *strtemp)
      {       
        break;                //�ַ��������˳�        
      }
      	
      coding = *strtemp;      //ȡ�ַ�����
      
      if(coding < 0X80)       //�ַ�����GB2312�ַ�
      {
        for(k=0;k<ASC2StringCodeLeng;k++)
        {
          if(ASC2Code[k].ASC2 == coding)   //�����ַ������Ӧ����ģ�ṹ������
            break;
        }
      
        if(k >= ASC2StringCodeLeng)        //�ַ��������
        {
          k = 0;
        }
    
        if((DecimalPoint << j) & 0X8000)       //���׿��� ����ʾ�� j ���ַ�ʱ����(0 =< j < 16)
        {
          ST7920WriteData(~ASC2Code[k].ASC2Code[i]);//����
        }
        else
        {
          ST7920WriteData(ASC2Code[k].ASC2Code[i]);//������
        }                           
      }
      else                                   //��ʾ����
      {
         GBcoding = coding;                  //GB2312����ֽ�
         GBcoding <<= 8;
         strtemp++;                          //ָ��GB2312����ֽ�
         coding = *strtemp;                  //GB2312����ֽ�
         GBcoding += coding;                 //16λGB2312��
         
         for(k=0;k<GB2312StringCodeLeng;k++)
         {
          if(GB2312Code[k].GB2312 == GBcoding)   //GB2312���Ӧ����ģ�ṹ������
            break;
         }
      
         if(k >= GB2312StringCodeLeng)           //�ַ��������
         {
           k = 0;
         }
         
         //д���ַ������ģ����
         if((DecimalPoint << j) & 0X8000)                 //���׿���
         {
           ST7920WriteData(~GB2312Code[k].GB2312LeftCode[i]);  //����
         }
         else
         {
           ST7920WriteData(GB2312Code[k].GB2312LeftCode[i]);  //������
         }
         j++;                                            //��ʾ���ȼ�1
         if(j >= Hleng)                                  //Խ���˳�
          break;
         
         //д���ַ��ұ���ģ����
         if((DecimalPoint << j) & 0X8000)                //���׿���
         {
           ST7920WriteData(~GB2312Code[k].GB2312RightCode[i]);//����
         }
         else
         {
           ST7920WriteData(GB2312Code[k].GB2312RightCode[i]); //������
         }                  
      }
      j++;                                            //��ʾ���ȼ�1
      strtemp++;                                      //ָ����һ���ַ�����
    }    
  }	 
}

/****************************************************************************************
�������ƣ�Coordinate(char H,char Ver,char *x,char *y)
��    �ܣ���ȡ��ͼ����
��    ����H---ˮƽ���꣬Ver---��ֱ����,
          *x---��ͼ���� x �����ַ
          *y---��ͼ���� y �����ַ
����ֵ  ����
******************************************************************************************/
void Coordinate(char H,char Ver,char *x,char *y)
{   
  if(H > 15)
    *x = 0;
  else
    *x = H / 2;
  
  if(Ver < 16)  //����ˮƽ��ͼ����
  {
    *x += 0X80;
  }
  else if(Ver < 32)
  {
    *x += 0X90;
  }
  else if(Ver < 48)
  {
    *x += 0X88;
  }
  else 
  {
    *x += 0X98;
  }
   
  if(Ver >31)   //���㴹ֱ��ͼ����
  {
    Ver -=32;
  }
  if(Ver > 127) //���곬����Χ Ϊ0
  {
    Ver = 0;
  }
  
  *y = Ver + 0X80;   
}


/****************************************************************************************
�������ƣ�void Draw(char H,char Ver,char Hleng,char Verleng,char wdata,const char *dat)
��    �ܣ���ͼ
          *dat��ΪNullʱд��*dat���ݣ�����д��wdata
          wdata==1��ʱ*dat����ȡ����ʾ
��    ����H---ˮƽ���꣬Ver---��ֱ����,
          Hleng---ˮƽ����
          Verleng---��ֱ����
          wdata---д�������
          *dat---д������ݵ�ַ
����ֵ  ����
******************************************************************************************/
void Draw(char H,char Ver,char Hleng,char Verleng,char wdata,const char *dat)
{
  char xadd;
  char yadd;
  char i,j;
  char temp=0;
  
  Coordinate(H,Ver,&xadd,&yadd);//��ȡ��ͼ��ʼ����
  
   for(i=0;i<Verleng;i++)   //д��
      {                              
        ST7920WriteCmd(yadd);    			// дY����
        ST7920WriteCmd(xadd);       			// дX����  
    
        if((H % 2) == 1 )                       // ˮƽ����Ϊ��������ԭGDRAM���ֽ���ʾ����
        {                                       //2014-03-24 �޸�
          ST7920ReadData();
          temp = ST7920ReadData();
          ST7920WriteCmd(yadd);    	                // дY����
          ST7920WriteCmd(xadd);       		// дX����
          ST7920WriteData(temp);
        }   
        yadd++;
        
        if(yadd > 0X9F)
        {
          xadd -= 8;
          yadd = 0X80;   
        }        
        else if((yadd > 0X8F) && (xadd <= 0X8F))
        {
          xadd += 16;
        }
               
        for(j=0;j<Hleng;j++) //д��
        {   
          if(dat != 0)    //д��ͼƬ
          {
            if(1 == wdata)//ȡ����ʾͼƬ
            {
              ST7920WriteData(~*dat);
            }
            else
            {
              ST7920WriteData(*dat);//������ʾͼƬ
            }
            dat++;      //ͼƬ��ģ�����±��1     
          }
          else
          {
            ST7920WriteData(wdata);//ȫ��д����ͬ������
          }         
        }
    }       
}

/****************************************************************************************
�������ƣ�void Display_8x6(char H,char Ver,char *s)
��    �ܣ���ʾ8*6�����ַ�
��    ����H---ˮƽ���꣬Ver---��ֱ����,
          *s---�ַ�����ַ
����ֵ  ����
******************************************************************************************/
void Display_8x6(char H,char Ver,char *s)
{
  char i,j,k;
  char xadd,yadd;
  char wdata;
  char temp;
  
  Coordinate(H,Ver,&xadd,&yadd);        //��ȡ��ͼ��ʼ����
  
  for(i=0;i<8;i++)                      //д��
  {
    ST7920WriteCmd(yadd);    			// дY����
    ST7920WriteCmd(xadd);       		// дX����
    if((H % 2) == 1 )                           // ˮƽ����Ϊ��������ԭGDRAM���ֽ���ʾ����
    {                                           // 2014-03-24 �޸�    
      ST7920ReadData();
      temp = ST7920ReadData();
      ST7920WriteCmd(yadd);    	                // дY����
      ST7920WriteCmd(xadd);       		// дX����
      ST7920WriteData(temp);
      ST7920WriteData(0x00);
    }                 
    yadd++;                                    //��ֱ�����       
    if(yadd > 0X9F)                            //���°����л�
    {
      xadd -= 8;
      yadd = 0X80;
    }        
    else if((yadd > 0X8F) && (xadd <= 0X8F)) //����
    {
      xadd += 16;
    }
               
    for(j=0;j<21;j++) //д��
    {
      if(s[j] == '\0')          //�ַ��������˳�
        break;
      
      k = TableNumber_8X6(s[j]);
      
      switch(j % 4)
      {
        case 0:
          wdata = ASC2Code_8X6[k].ASC2Code[i];//��һ���ַ���ģ
          if(s[j+1] != '\0')
          {
            k = TableNumber_8X6(s[j+1]);      //��һ���ַ����ֿ��е�λ��
            wdata |= (ASC2Code_8X6[k].ASC2Code[i] >> 6);//����д���8bit����
          }
          ST7920WriteData(wdata);                //д��8bit����    
          break;
          
        case 1:
          wdata = ASC2Code_8X6[k].ASC2Code[i] << 2;//�ڶ����ַ���ģ
          if(s[j+1] != '\0')
          {
            k = TableNumber_8X6(s[j+1]);      //��һ���ַ����ֿ��е�λ��
            wdata |= (ASC2Code_8X6[k].ASC2Code[i] >> 4);//����д���8bit���� 
          }
          ST7920WriteData(wdata);                //д��8bit����    
          break;
          
        case 2:
          wdata = ASC2Code_8X6[k].ASC2Code[i] << 4;//�������ַ���ģ
          if(s[j+1] != '\0')
          {
            k = TableNumber_8X6(s[j+1]);      //��һ���ַ����ֿ��е�λ��
            wdata |= (ASC2Code_8X6[k].ASC2Code[i] >> 2);//����д���8bit����
          } 
          ST7920WriteData(wdata);                //д��8bit����    
          break; 
        case 3:
          break;
        default: break;                          
      }
    }
  }  
}

/****************************************************************************************
�������ƣ�unsigned char TableNumber_8X6(char asc2)
��    �ܣ������ַ����ֿ��е�λ��
��    ����unsigned char asc2 --- �ַ�ASC2��
����ֵ  ���ַ����ֿ��еı��
******************************************************************************************/
char TableNumber_8X6(char asc2)
{
  char number;
  
  for(number=0;number<ASC2StringCodeLeng_8X6;number++)
  {
      if(ASC2Code_8X6[number].ASC2 == asc2)   //GB2312���Ӧ����ģ�ṹ������
          break;
  }
  if(number >= ASC2StringCodeLeng_8X6)
  {
      number = 0;
  }
  return number;
}


/**************************************************************
�������ƣ�void DisplayNum(char H,char Ver,long int value,
                char type,char cmd,char *s,char fb)
�������ܣ���ʾ����
���������unsigned char H---->ˮƽ����
          char Ver--->��ֱ����
          long int value------>��ʾ������
          char type-->��������
          char cmd--->����ת������
          char *s---->��������ʾ����β�����ַ��� ��󳤶�Ϊ10
          unsigned int fb---->���Կ���
�����������
����ֵ  ����           
***************************************************************/
void DisplayNum(char H,char Ver,long int value,char type,char cmd,char *s,unsigned int fb)
{
  char strtmep[16]={0};
  char i=0,j=0;
   
  i = SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
  for(j=0;j<10;j++)//��ʾ���ֵ�β��������Ҫ��ʾ���ַ���
  {
    if(s[j]=='\0')
      break;
    if(i < 16)
    {
      strtmep[i++] = s[j];
    }   
  }
    
  DisplayString(H,Ver,strtmep,fb);
}

/**************************************************************
�������ƣ�void DisplayNum8X6(char H,char Ver,long int value,
                char type,char cmd,char *s)
�������ܣ���ʾ����8X6
���������unsigned char H---->ˮƽ����
          char Ver--->��ֱ����
          long int value------>��ʾ������
          char type-->��������
          char cmd--->����ת������
          char *s---->��������ʾ����β�����ַ��� ��󳤶�Ϊ10
�����������
����ֵ  ����           
***************************************************************/
void DisplayNum8X6(char H,char Ver,long int value,char type,char cmd,char *s)
{
  char strtmep[16]={0};
  char i=0,j=0;
   
  i = SInt32_TO_String(strtmep,value,type,cmd);//��ʾ����ת��Ϊ�ַ���
  for(j=0;j<10;j++)
  {
    if(s[j]=='\0')
      break;
    
    if(i < 16)
    {
      strtmep[i++] = s[j];
    }   
  } 
  Display_8x6(H,Ver,strtmep);
}

