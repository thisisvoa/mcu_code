#include "RS485.h"

ComPortClass RS485Com={0};
ClassRs485 RS485={0};
ClassModbus Modbus={0};
unsigned int Height=15000;  //ˮλ�ư�װ�߶�

/*******************************************************************************
�������ƣ�void RS485Read(void)
�������ܣ���ȡRS485
�����������                             
�����������
����ֵ  ����
*******************************************************************************/
void RS485Read(void)
{
  if(RS485Com.TxdCount > RS485Com.TxdMax)    //��ȡ������������ȡ����
  {
    RS485Com.Status.Flag.ComEvent = False;   //��ȡ�¼���λ
    RS485Com.Status.Flag.Txd = False;        //����״̬��־��λ    
    RS485Com.TxdCount = 0;                   //���ͼ�������
    RS485Com.TiTxdTime = 0;                  //���ͳ�ʱ��ʱ����

    DisplayRunInfo("Failure");
    DELETE_UART1RXD;
    CaiYangOk();
    return;
  }

  DisplayRunInfo("Read");
  if(Display.Status.Flag.Mon)
  {
    DisplayNum(6,48,RS485Com.TxdCount,20,space,"",0);
  }
  
  RS485SendReadCmd(0X01);                   //���Ͷ�ȡ����
}

/*******************************************************************************
�������ƣ�void RS485EventHandlers(void)
�������ܣ�RS485�����¼�����
�����������                             
�����������
����ֵ  ����
*******************************************************************************/
void RS485EventHandlers(void)
{
  if(RS485Com.Status.Flag.Online)            //�豸����
  {    
    if(RS485.Name&&(RS485Com.Status.Flag.Txd == False))    //���ڷ���״̬��
    {
      RS485Read();                           //��ȡ����
    }
    if(CaiYang.Event)
    {
      CaiYangHandlers();
    }
  }
  else                                       //�豸������
  {
    if(RS485Com.Status.Flag.Power==False)    //�豸��ԴΪ�ر�״̬
    {
      OperComPort(&RS485Com);                //���豸��Դ
    }
  }
}

/*******************************************
�������ƣ�void RS485SendReadCmd(unsigned char st,unsigned char startadd)
��    �ܣ�RS485�ӿڷ��Ͷ�����
��    ����unsigned char st---->�豸��ַ
����ֵ  ����
********************************************/
void RS485SendReadCmd(unsigned char st)
{
  DELETE_UART1RXD;                      //��ȫ������ջ���
  switch(RS485.CgqType)
  {
    case 1:                             //�Ͽس�����Һλ�� 
      {
        Modbus.SN = 0X01;
        Modbus.AFN = 0X03;
        Modbus.StartSN.num = 0X02;
        Modbus.Lenght.num = 0X03;
        SendModbusCmd();
      }break;
    case 2:                             //��������������
      {
        Modbus.SN = 0X01;
        Modbus.AFN = 0X03;
        Modbus.StartSN.num = 0X00;
        Modbus.Lenght.num = 0X02;
        SendModbusCmd();
      }break; 
    case 3:                             //�״�Һλ��
      {
        Modbus.SN = 0X01;
        Modbus.AFN = 0X03;
        Modbus.StartSN.num = 0X10;
        Modbus.Lenght.num = 0X01;
        SendModbusCmd();
      }break;     
    case 4:                             //�������������� V1.4 Ǳɽ����ˮ��
      {
        Modbus.SN = 0X01;
        Modbus.AFN = 0X03;
        Modbus.StartSN.num = 0X00;
        Modbus.Lenght.num = 0X01;
        SendModbusCmd();
      }break;   
    case 5:                             //�Ӻ�����
      {
        Modbus.SN = 0X01;
        Modbus.AFN = 0X03;
        Modbus.StartSN.num = 0;
        Modbus.Lenght.num = 1;
        SendModbusCmd();
      } break;   
    case 6:                         //������ͨ�״�Һλ�� ��ȡҺλ
        {
            Modbus.SN = 0X01;
            Modbus.AFN = 0X03;
            Modbus.StartSN.num = 3;
            Modbus.Lenght.num = 2;
            SendModbusCmd();
        }break;
      case 7:
      {
            Modbus.SN = 0X01;
            Modbus.AFN = 0X03;
            Modbus.StartSN.num = 0;
            Modbus.Lenght.num = 1;
            SendModbusCmd();
      }break;
      
  }
  RS485Com.Status.Flag.Txd = True;           //����״̬��־��λ
  RS485Com.TiTxdTime = RS485Com.TxdTime;     //���ͳ�ʱ��ʱ��ʼ��
  RS485Com.TxdCount++;                       //���ͼ���
  RS485Com.TiClose = RS485Com.CloseDelay;    //��ʼ���豸������ʱ
  
}

void SendModbusCmd(void)
{
  unsigned char modarray[8]={0};
  Uint16 crccode={0};
  
  modarray[0] = Modbus.SN;
  modarray[1] = Modbus.AFN;
  modarray[2] = Modbus.StartSN.bit16.nHigh;
  modarray[3] = Modbus.StartSN.bit16.nLow;
  modarray[4] = Modbus.Lenght.bit16.nHigh;
  modarray[5] = Modbus.Lenght.bit16.nLow;
  crccode.num = CRC16(modarray,6);
  modarray[6] = crccode.bit16.nHigh;
  modarray[7] = crccode.bit16.nLow;
  WriteUART1(modarray,8);
  
}

/*******************************************
�������ƣ�unsigned char GetModbusData(unsigned char datalen,unsigned char nbyte,unsigned char minlen)
��    �ܣ��ӽ��ջ�������ȡModbusЭ������
��    ����unsigned int max      ---->�������ֵ
          unsigned char nbyte   ---->���ݸ��ֽ�����豸��ַƫ����
          unsigned char minlen  ---->����֡����
���������У��ɹ�ʱ���޸�RS485ͨ����ֵRS485.Value
����ֵ  ��1----> �ɹ�
          2----> У�����
          3----> �Ƿ���ֵ
          0----> ��������
********************************************/
unsigned char GetModbusData(unsigned int max,unsigned char nbyte,unsigned char minlen)
{
  Uint16 data16={0};
  unsigned char array[2]={0};
  unsigned char *p_0;  
  
  if(UART1_RxdLeng < minlen)
    return 0;
  
  array[0] = Modbus.SN;
  array[1] = Modbus.AFN;
  
  p_0 = Search(UART1_RxdBuff,20,array,2);
  if(p_0 != NULL)
  {
    data16.num = CRC16(p_0,p_0[2]+3);
    if((data16.bit16.nHigh!=p_0[p_0[2]+3])||(data16.bit16.nLow!=p_0[p_0[2]+4]))
      return 2;
    data16.bit16.nHigh = p_0[nbyte];                //���ݻ�ȡ
    data16.bit16.nLow = p_0[nbyte+1];
    if(data16.num > max)
      return 3;
    
    if(1==RS485.CgqType)//�Ͽس����� ˮλ=��װ�߶�-��ֵ
    {
      RS485.Value = Height-data16.num;
    }
    else
    {
      RS485.Value = data16.num;
    }
    
  }
  else
  {
    return 0;
  }
  return 1;
}

/*�ɹ��յ��������ݴ���*/
void RS485RxdDataHandlers(void)
{
  //RS485Com.Status.Flag.Online = True;              //���߱�־��λ
  RS485Com.TiClose = RS485Com.CloseDelay;            //��ʼ��������ʱ��ʱ

  if(1==RS485GetData())
  {
    DisplayRunInfo("ReadOk!");
    RS485Com.Status.Flag.Txd = False;                //����״̬��λ
    RS485Com.TiTxdTime = 0;                          //��ʱ��ʱ����
    RS485Com.Status.Flag.ComEvent = False;           //��ȡ�¼���λ
    RS485Com.TxdCount = 0;                           //���ͼ�������
    
    if((8==RS485.Name)||(9==RS485.Name)||(10==RS485.Name))
    {
      RS485.Value += RTU.ShuiWeiJiZhi + RTU.XiuZhengJiZhi;
    }
    
    /*if((3==Display.Mon)&&(Display.Status.Flag.Mon))
    {
      DisplayNum(15-(YaoSuInfo[RS485.Name].DataType>>4),32,RS485.Value,YaoSuInfo[RS485.Name].DataType,space,"",0);
    }*/
    
    Message.RS485 = RS485.Value;
    CaiYangOk();
  }
}

/*******************************************
�������ƣ�unsigned char GetWater(unsigned int *pwater)
��    �ܣ��ӽ��ջ�������ȡ����
��    ������
����ֵ  ��1----> �ɹ�
          2----> У�����
          3----> �Ƿ���ֵ
          0----> ��������
********************************************/
unsigned char RS485GetData(void)
{
  unsigned char i=0;
  switch(RS485.CgqType)
  {
    case 1:
      {
       i = GetModbusData(Height,3,11);
      }break; 
    case 2:
      {
        i = GetModbusData(Height/10,3,7);
        if(1==i)
        {
          RS485.Value *=10;
        }
      }break;
    case 3:
      {
        i = GetModbusData(Height/10,3,7);
        if(1==i)
        {
          RS485.Value *=10;
        }
      }break;
    case 4:
      {
        i = GetModbusData(Height/10,3,7);
        if(1==i)
        {
          RS485.Value *=10;
        }
      }break;
      case 5:
        {
           i = GetModbusData(8000,3,7);
            if(1==i)
            {
              RS485.Value *=10;
            }
        }break;
      case 6:
        {
           i = GetModbusData(Height,3,7);
           
        }break;
      case 7:
        {
           i = GetModbusData(Height,3,7);
        }break;
        
  } 
  return i;
}


