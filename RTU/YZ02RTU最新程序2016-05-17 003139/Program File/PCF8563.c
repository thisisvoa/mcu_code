//====================================================================================
//                       PCF8563.C With MSP430F149 Driver
//Platform: IAR Embedded Workbench Version: 3.42A
//�汾: 1.0.0
//����:  ���
//Email:   li-huai-liang@163.com
//QQ:      769996244
//����:    2009-03-23
//�޸�:    ���� 2013-04-17
///***********************************************************************************/


#include "IIC.h"
#include "PCF8563.h" 
#include "Public.h"
#include "include.h"

/********************************************
�������->pcf8563
********************************************/
void PCF8563writeData(unsigned char address,unsigned char mdata)
{
   P1DIR |= IICSCL;  //define to output 
   IICSDAOut(); //define to output
   IICStart();
   IICWriteByte(0xa2); //д����
   IICWriteByte(address); //д��ַ
   IICWriteByte(mdata); //д����
   IICStop();

}

/********************************************
��������<-pcf8563
********************************************/
/*unsigned char PCF8563ReadData(unsigned char address) //���ֽ�
{ 
   unsigned char rdata;
   P1DIR |= IICSCL;  //define to output 
   IICSDAOut(); //define to output
   IICStart();
   IICWriteByte(0xa2); //д����
   IICWriteByte(address);//д��ַ
   IICStart();
   IICWriteByte(0xa3); //������
   rdata=IICReadByteWithAck();
   //WriteACK(1);
   IICStop();
   return(rdata);
}*/

/********************************************************************************************************
** ��������: PCF8563WriteData
** ��������: 
** �䡡��: ��
** �䡡��: ��
** ȫ�ֱ���: ��
*-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
/*unsigned char PCF8563WriteData(unsigned char address,unsigned char *p,unsigned char count)
{
    unsigned char i;
    
    P1DIR |= IICSCL;  //define to output 
    IICSDAOut(); //define to output
  
    IICStart();
    
    if(IICWriteByte(0XA2))return(1);
    if(IICWriteByte(address))return(1);
    
    for(i=0;i<count;i++)
    {
        if(IICWriteByte(*p))return(1);
        p++;
    };
    
    IICStop();
    return(0);
}*/

/********************************************************************************************************
** ��������: PCF8563ReadData
** ��������: 
** �䡡��: ��
** �䡡��: ��
** ȫ�ֱ���: ��
*-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
unsigned char PCF8563ReadDatas(unsigned char address,unsigned char  *p,unsigned char count)
{
    unsigned char i;

    P1DIR |= IICSCL;  //define to output 
    IICSDAOut(); //define to output
    PCF8563delayus(20);
    IICStart();
    PCF8563delayus(20);
    if(IICWriteByte(0xA2)) return(1);
    if(IICWriteByte(address)) return(1);
    PCF8563delayus(20);
    IICStart();
    if(IICWriteByte(0xA3))return(1);
    PCF8563delayus(20);
    for(i=1;i<count;i++)
    {
        *p=IICReadByteWithAck();PCF8563delayus(20);
        p++;  
    };
    *p=IICReadByteWithoutAck();
    PCF8563delayus(20);
    IICStop();
    PCF8563delayus(20);
      
    return(0); 
}

/***************************************************
PCF8563��ʼ�����ر����б���
�ɹ���⵽��������1��
δ��⵽��������0.
**************************************************/
unsigned char PCF8563Ini(void)
{
  unsigned char timebcd[7]={0};
  
  PCF8563writeData(0x01,0x02);		 //�رձ����ж�
  PCF8563writeData(0x09,0x00);		 //00�ֱ��� 
  PCF8563writeData(0x0A,0x80);		 
  PCF8563writeData(0x0B,0x80);
  PCF8563writeData(0x0C,0x80);

  PCF8563writeData(week,0X01);  //��������Ϊ 1
  PCF8563delayus(1000);         //��ʱ1ms
  PCF8563ReadDatas(second,timebcd,7);   //��ȡʱ��
  timebcd[4] &= 0X07;                   //����
  
  if(timebcd[4]==1)
    return 1;                   //���سɹ�
  else
    return 0;                   //����ʧ��
  
}


/*******************************************
�������ƣ�unsigned char ReadTime(DataTime *t)
��    �ܣ���ȡϵͳʱ�䣬��ʱ��t����ΪRTC��ǰʱ��
��    ����struct Timestamp *t---->ʱ��
����ֵ  ���ɹ�����1��ʧ�ܷ���0.
********************************************/
unsigned char ReadTime(DataTime *t)
{
  unsigned char timebcd[7]={0};
  unsigned char i=0;            
   
  do
  {
    i++;
    PCF8563ReadDatas(second,timebcd,7);   //��ȡʱ��
    timebcd[0] &= 0X7F;                   //��             ��Чλ����
    timebcd[1] &= 0X7F;                   //����
    timebcd[2] &= 0X3F;                   //Сʱ
    timebcd[3] &= 0X3F;                   //��
    timebcd[4] &= 0X07;                   //����
    timebcd[5] &= 0X1F;                   //��
     
/*************��ʱ��BCD��ת��Ϊ8bit����************/
    (*t).Year = BCD_Byte(timebcd[6]); //��
    (*t).Month = BCD_Byte(timebcd[5]);//��
    (*t).Day = BCD_Byte(timebcd[3]);         
    (*t).Hour = BCD_Byte(timebcd[2]);
    (*t).Minute = BCD_Byte(timebcd[1]);
    (*t).Second = BCD_Byte(timebcd[0]);
    
    if(1==TimeCheck(*t))                  //������ʱ��Ϸ�
      return 1;                          //���ض�ȡ�ɹ�
       
  }while(i < 5);                        //������ʱ�䲻�Ϸ� ����ض�5��
  return 0;                             //���ض�ȡʧ��
  
}

/*******************************************
�������ƣ�unsigned char SetTime(DataTime *t)
��    �ܣ�����ϵͳʱ�䣬��ʱ��t����Ϊϵͳ��ǰʱ��
��    ����DataTime *t---->ʱ��
����ֵ  ���ɹ�����1��ʧ�ܷ���0.
********************************************/
void SetTime(DataTime *t)
{
  PCF8563writeData(year,Byte_BCD(t->Year));
  PCF8563writeData(month,Byte_BCD(t->Month));
  PCF8563writeData(day,Byte_BCD(t->Day));
  PCF8563writeData(hour,Byte_BCD(t->Hour));
  PCF8563writeData(minute,Byte_BCD(t->Minute));
  PCF8563writeData(second,Byte_BCD(t->Second));
  
}

/*******************************************
�������ƣ�unsigned int TimeInterval(struct Timestamp *t0,struct Timestamp *t1)
��    �ܣ�ʱ��������
��    ����struct Timestamp *t0 ----> ��ǰʱ��
          struct Timestamp *t1 ----> ��ʱ���ʱ��
����ֵ  ��ʱ���� ��λ��
********************************************/
/*unsigned int TimeInterval(Time *t0,Time *t1)
{
  unsigned int timevalue;
 
  //Сʱ����
  if((*t0).Hour < (*t1).Hour)           //����ͬһ�� ���Сʱ��
  {
    timevalue = (24-(*t1).Hour) + (*t0).Hour;
  }
  else          //��ͬһ�� ���Сʱ��
  {
    timevalue = (*t0).Hour - (*t1).Hour;
  }
  timevalue *= 60;
  //���Ӽ���
  if((*t0).Minute < (*t1).Minute)
  {
    timevalue -= (*t1).Minute - (*t0).Minute;		
  }
  else
  {
    timevalue += (*t0).Minute - (*t1).Minute;  
  }
  timevalue *= 60;
  //���Ӽ���
  if((*t0).Second < (*t1).Second)
  {
    timevalue -= (*t1).Second - (*t0).Second;		
  }
  else
  {
    timevalue += (*t0).Second - (*t1).Second;  
  }
  
  return timevalue;
}*/



/*void timeini(void)
{
  PCF8563writeData(year,0X13);  
  PCF8563writeData(month,0X05); 
  PCF8563writeData(day,0X13); 
  PCF8563writeData(week,0X05); 
  PCF8563writeData(hour,0X10); 
  PCF8563writeData(minute,0X05); 
}*/



