/*********************************************************
*�ļ����ƣ�CPASCII.c
*ժ    Ҫ��ͨ��Э��༭����
*
*��ǰ�汾��1.0
*��    �ߣ�����
*��ʼ���ڣ�2013��09��02��
*������ڣ�
**********************************************************/
#include "include.h"

ClassMessage Message={0};
ClassMessage *pM=&Message;
ComPortClass Com={0}; 
ClassRxdMessage *pRM;
ClassDRPZ DRPZ={0};

const ClassAFN AFN={
0X2F,           //��·ά�ֱ�
0X30,           //���Ա�
0X31,           //����ʱ��ˮ����Ϣ��
0X32,           //ң��վ��ʱ��
0X33,           //ң��վ�ӱ���
0X34,           //ң��վСʱ��
0X35,           //ң��վ�˹�������
0X36,           //ң��ͼƬ��������վ��ѯң��վͼƬ�ɼ���Ϣ
0X37,           //����վ��ѯң��վʵʱ����
0X38,           //����վ��ѯң��վʱ������
0X39,           //����վ��ѯң��վ�˹�����
0X3A,           //����վ��ѯң��ָ��Ҫ������
0X40,           //����վ�޸�ң��վ�������ñ�
0X41,           //����վ��ȡң��վ�������ñ�
0X42,           //����վ�޸�ң��վ���в������ñ�
0X43,           //����վ��ȡң��վ���в������ñ�
0X44,           //��ѯˮ�õ��ʵʱ��������
0X45,           //��ѯң���ն�����汾
0X46,           //��ѯң��վ״̬�ͱ�����Ϣ
0X47,           //��ʼ����̬�洢����
0X48,           //�ָ��ն˻���������
0X49,           //�޸�����
0X4A,           //����ң��վʱ��
0XE0,           //��ȡ�Զ�������
0XE1            //�޸��Զ�������
};

void AddDRPZ(unsigned int page,unsigned int bytes)
{
  if(DRPZ.sp >= DRPZLEN)
  {
    UpdateDRPZ();
  }
  DRPZ.Array[DRPZ.sp].Page = page;
  DRPZ.Array[DRPZ.sp].Bytes = bytes;
  DRPZ.sp++;
 
}

void UpdateDRPZ(void)
`{ 
  unsigned char i=0;

  if(0==DRPZ.sp)
    return;
  
  DRPZ.sp--;
  for(i=0;i<DRPZ.sp;i++)
  {
    DRPZ.Array[i].Page = DRPZ.Array[i+1].Page;
    DRPZ.Array[i].Bytes = DRPZ.Array[i+1].Bytes;
  }
  DRPZ.Array[DRPZ.sp].Page = 0;
  DRPZ.Array[DRPZ.sp].Bytes = 0;
}

/*******************************************************************************
�������ƣ�void ComEventHandlers(void) 
�������ܣ�ͨ���¼�����
�����������                             
���������
����ֵ  ����
*******************************************************************************/
void ComEventHandlers(void) 
{ 
  if(Com.Status.Flag.Online)            //ͨ���豸����
  {    
    if(Com.Status.Flag.Txd == False)    //���ڷ���״̬��
    {
      ComSendMessage();                 //���ͱ���
    }
  }
  else                                  //ͨ���豸������
  {
    if(Com.Status.Flag.Power==False)    //ͨ���豸��ԴΪ�ر�״̬
    {
      OperComPort(&Com);                        //��ͨ���豸
    }
  }
}

/*******************************************************************************
�������ƣ�void ComSendMessage(void) 
�������ܣ�ͨ���豸���ͱ���
�����������                             
���������ͨ���豸���ݡ�״̬��־
����ֵ  ����
*******************************************************************************/
void ComSendMessage(void)
{
  if(Com.TxdCount > Com.TxdMax)         //����������������ط�����
  {
    Com.Status.Flag.ComEvent = False;   //ͨ���¼���λ
    Com.Status.Flag.Txd = False;        //����״̬��־��λ    
    Com.TxdCount = 0;                   //���ͼ�������
    Com.TiTxdTime = 0;                  //���ͳ�ʱ��ʱ����
    
    #if DEBUG>=1
    WriteLineStrUART1("����ʧ��");
    #endif
        
    DisplayRunInfo("����ʧ��");
    
    return;
  }

  DisplayRunInfo("����");
  if(Display.Status.Flag.Mon)
  {
    DisplayNum(6,48,Com.TxdCount,20,space,"",0);
  }
  
  SendMessenge();  
    
  Com.Status.Flag.Txd = True;   //����״̬��־��λ
  Com.TiTxdTime = Com.TxdTime;  //���ͳ�ʱ��ʱ��ʼ��
  Com.TxdCount++;               //���ͼ���
  Com.TiClose = Com.CloseDelay; //��ʼ��ͨ���豸������ʱ

}

void AddMessengeTask(unsigned char gnm)
{
  if(Com.Status.Flag.ComEvent)
  {
    if(AFN.Heartbeat==Message.AFN)
    {
      Message.AFN = gnm;
    }
    Com.TxdCount = 0;
  }
  else
  {
    Message.AFN = gnm;
    Com.Status.Flag.ComEvent = SET;
  }
  if((AFN.ChaXunShiShi==Message.AFN)||(AFN.CeShi==Message.AFN))
  {
    Message.RainTT.Year = System.Time.Year;             //�����������ݸ���
    Message.RainTT.Month = System.Time.Month;
    Message.RainTT.Day = System.Time.Day;
    Message.RainTT.Hour = System.Time.Hour;
    Message.RainTT.Minute = System.Time.Minute;
    Message.PT = Rainfall.PT;
    Message.PJ = Rainfall.PJ;
    Message.PN05 = Rainfall.PN05;
    Message.PN10 = Rainfall.PN10;
    Message.PN30 = Rainfall.PN30;    
  }
}

void SendMessenge(void)
{
  unsigned int lenght=0;
  
  IE1 &= ~URXIE0;       //�رս����ж�
  DELETE_UART0RXD;      //�������
  lenght = WriteMessage(UART0_RxdBuff); //�༭��Ϣ
  WriteUART0(UART0_RxdBuff,lenght);     //����
  IE1 |= URXIE0;
}


/**************************************************************
�������ƣ�unsigned int WriteMessage(unsigned char *p)                                    
�������ܣ��༭����
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
�����������������
����ֵ  �����ĳ���
*************************************************************/
unsigned int WriteMessage(unsigned char *p)
{
  unsigned int AddNbyte=0;
  
  AddNbyte = WriteMessageHead(p,AddNbyte);      //�༭��ͷ
  AddNbyte = WriteHeartbeatPackets(p,AddNbyte);
  
  if((AFN.CeShi==pM->AFN)||
     (AFN.DingShi==pM->AFN)||
     (AFN.ChaXunShiShi==pM->AFN)||
     (AFN.JiaBao==pM->AFN))
  {
    AddNbyte = WriteMessageTextPublic(p,AddNbyte);
    AddNbyte = WriteMessageTextData(p,AddNbyte);
  }
  else if(AFN.GetRunConfig==pM->AFN)    //�ϱ�������Ϣ
  {
    AddNbyte = WriteMessageTextPublic(p,AddNbyte);
    AddNbyte = WriteMessageConfig(p,AddNbyte);
  }
  else if(AFN.ChaXunShiDuan==pM->AFN)
  {
    AddNbyte = WriteMessageTextPublic(p,AddNbyte);
    AddNbyte = WriteMessageTextLiShiDada(p,AddNbyte);
  }
  else if(AFN.XiaoShi==pM->AFN)
  {
    AddNbyte = WriteMessageTextPublic(p,AddNbyte);
    AddNbyte = WriteMessageTextDRPZ(p,AddNbyte);
  }

  AddNbyte = WriteMessageEnd(p,AddNbyte,ETX);     //�༭���Ľ�������*/

  return AddNbyte;
}  


/**************************************************************
�������ƣ�unsigned int WriteMessageHead(unsigned char *p,unsigned int  AddNbyte)                                    
�������ܣ��༭��ͷ
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
������������ı�ͷ����
����ֵ  �����ر��ķ��ͻ������λ��
**************************************************************/
unsigned int WriteMessageHead(unsigned char *p,unsigned int  AddNbyte)
{
  unsigned char temp; 
  
  /********************����֡��ʼ��*************************/
  p[AddNbyte++] = SOH;                                         //֡��ʼ��
  
  /********************��������վ��ַ**********************/ 
  p[AddNbyte++] = HEXASCII[RTU.CenterAdd >> 4];     //����վ��ַ��4λASC����
  p[AddNbyte++] = HEXASCII[RTU.CenterAdd & 0X0F];   //����վ��ַ��4λASC����
  
  /********************����ң��վ��ַ***********************/
  p[AddNbyte++] = HEXASCII[RTU.ST[0] >> 4];         //ң��վ��ַ������ʽΪBCD
  p[AddNbyte++] = HEXASCII[RTU.ST[0] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[1] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[1] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[2] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[2] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[3] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[3] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[4] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[4] & 0X0F]; 
  
  /************************��������**************************/
  temp = (unsigned char)(RTU.Password >> 8);            //�����8λ  
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F];
  
  temp = (unsigned char)(RTU.Password & 0X00FF);        //�����8λ  
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F];
  
  /**********************���빦����**************************/
  p[AddNbyte++] = HEXASCII[Message.AFN >> 4];                   //�������4λASC����
  p[AddNbyte++] = HEXASCII[Message.AFN & 0X0F];                 //�������4λASC����
  
  /*********���������б�ʶ���뱨�����ĳ���*******************/
  p[AddNbyte++] = '0';                                          //���б�ʶ��
            
  p[AddNbyte++] = '0';                                          //���ĳ��� �������ı༭����޸�
  p[AddNbyte++] = '0';
  p[AddNbyte++] = '0';
  
  /********************����������ʼ��*************************/
  p[AddNbyte++] = STX;                              //����������ʼ�� 0X02
  
  return AddNbyte;
}


/****************************************************************************************
�������ƣ�unsigned int WriteHeartbeatPackets(unsigned char *p,unsigned int  AddNbyte)
�������ܣ��༭��������������
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
������������������е� ��ˮ�š�����ʱ��
����ֵ  �����ر��ķ��ͻ������λ��
*****************************************************************************************/
unsigned int WriteHeartbeatPackets(unsigned char *p,unsigned int  AddNbyte)
{
  unsigned char temp;
  static unsigned int snumber=0;                        //��ˮ�ų�ʼ��Ϊ0
    
  if(0 == ++snumber)                                    //������ˮ��
    snumber = 1;
  
  /********************������ˮ��*************************/
  temp = (unsigned char)(snumber >> 8);                 //��ˮ��ת��ΪASC��
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F];
  temp = (unsigned char)(snumber & 0X00FF);
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F];            
  /********************���뷢��ʱ��*************************/
  p[AddNbyte++] = HEXASCII[System.Time.Year / 10]; //�� ʮ����ת��ΪASC��
  p[AddNbyte++] = HEXASCII[System.Time.Year % 10];
  p[AddNbyte++] = HEXASCII[System.Time.Month / 10];
  p[AddNbyte++] = HEXASCII[System.Time.Month % 10];
  p[AddNbyte++] = HEXASCII[System.Time.Day / 10];
  p[AddNbyte++] = HEXASCII[System.Time.Day % 10];
  p[AddNbyte++] = HEXASCII[System.Time.Hour / 10];
  p[AddNbyte++] = HEXASCII[System.Time.Hour % 10];
  p[AddNbyte++] = HEXASCII[System.Time.Minute / 10];
  p[AddNbyte++] = HEXASCII[System.Time.Minute % 10];
  p[AddNbyte++] = HEXASCII[System.Time.Second / 10];
  p[AddNbyte++] = HEXASCII[System.Time.Second % 10];
  
  return AddNbyte;  
}

/***********************************************************
�������ƣ�unsigned int WriteMessageTextPublic(unsigned char *p,unsigned int  AddNbyte)
�������ܣ��༭�������Ĺ�������
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
          Time *PT ----->�۲�ʱ��
����������������Ĺ�������
����ֵ  �����ر��ķ��ͻ������λ��
***********************************************************/
unsigned int WriteMessageTextPublic(unsigned char *p,unsigned int  AddNbyte)
{    
  /********************����ң��վ��ַ***********************/
  p[AddNbyte++] = 'S';                                          //��ַ��ʶ��                               
  p[AddNbyte++] = 'T';
  p[AddNbyte++] = ' ';                          
  p[AddNbyte++] = HEXASCII[RTU.ST[0] >> 4];             //ң��վ��ַ������ʽΪBCD
  p[AddNbyte++] = HEXASCII[RTU.ST[0] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[1] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[1] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[2] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[2] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[3] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[3] & 0X0F]; 
  p[AddNbyte++] = HEXASCII[RTU.ST[4] >> 4];     
  p[AddNbyte++] = HEXASCII[RTU.ST[4] & 0X0F];    
  /********************����ң��վ������***********************/
  p[AddNbyte++] = ' ';
  p[AddNbyte++] = RTU.RTUType;
    
  return AddNbyte;  
}

/***********************************************************
�������ƣ�unsigned int WriteMessageEnd(unsigned char *p,unsigned int  AddNbyte,unsigned char endcod)
�������ܣ��༭���Ľ�������
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
          unsigned char endcod---->ETX(03H)�����ޱ���  ETB(17H)�����б���
������������Ľ�������
����ֵ  �������ܳ���
***********************************************************/
unsigned int WriteMessageEnd(unsigned char *p,unsigned int  AddNbyte,unsigned char endcod)
{
  unsigned int i=0;
  unsigned char temp=0; 
   
  i = AddNbyte - 24;                    //�������ĳ���
  
  temp = (unsigned char)(i >> 8);       //���±�ͷ�б��ĳ���
  p[20] = HEXASCII[temp & 0X0F];
  temp = (unsigned char)(i & 0X00FF);
  p[21] = HEXASCII[temp >> 4];
  p[22] = HEXASCII[temp & 0X0F];
  
  p[AddNbyte++] = endcod;               //���뱨�Ľ�����
  
  i = CRC16(p,AddNbyte);                //�������У����
  
  temp = (unsigned char)(i & 0X00FF);
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F]; 
  temp = (unsigned char)(i >> 8);
  p[AddNbyte++] = HEXASCII[temp >> 4];
  p[AddNbyte++] = HEXASCII[temp & 0X0F];
  
  //p[AddNbyte++] = 0X0D;
  //p[AddNbyte++] = 0X0A;
  if(AFN.ChaXunShiDuan==Message.AFN)
  {
    p[AddNbyte++] = 0X0D;
    p[AddNbyte++] = 0X0A;
  }
     
  return AddNbyte;
}

/*******************************************************************************
�������ƣ�unsigned int WriteMessageVariable(unsigned char *p,unsigned int  AddNbyte,E_data *pE)
�������ܣ��༭�ϱ�Ҫ��
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��        
          E_data *pE ----------->�ϱ�Ҫ�ش洢��ַ
���������Ҫ������
����ֵ  �����ر��ķ��ͻ������λ��
********************************************************************************/
unsigned int WriteMessageVariable(unsigned char *p,unsigned int  AddNbyte,E_data *pE)
{
  unsigned char i=0;
                                              //�����ʶ��
  p[AddNbyte++] = ' ';                
  for(i=0;i<8;i++)
  {
    if((*pE).keyword[i] != '\0')
      p[AddNbyte++] = pE->keyword[i];
    else
      break;      
  }   

  p[AddNbyte++] = ' ';
  i = SInt32_TO_String(&p[AddNbyte],pE->value,pE->DType,DEZero);//����Ҫ������
  
  AddNbyte += i;
  return AddNbyte;
}

/*******************************************************************************
�������ƣ�unsigned int WriteMessageTextRain(unsigned char *p,unsigned int  AddNbyte)
�������ܣ��༭�������Ľ�ˮ������
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
����������������Ľ�ˮ������
����ֵ  �����ر��ķ��ͻ������λ��
*******************************************************************************/
unsigned int WriteMessageTextRain(unsigned char *p,unsigned int  AddNbyte)
{
  E_data element={0};                   //�ϱ�Ҫ��
  
  p[AddNbyte++] = ' '; 
  p[AddNbyte++] = 'T';                                  //�۲�ʱ���ʶ��                               
  p[AddNbyte++] = 'T';    
  p[AddNbyte++] = ' ';  
  p[AddNbyte++] = HEXASCII[pM->RainTT.Year / 10];        //�� ʮ����ת��ΪASC��
  p[AddNbyte++] = HEXASCII[pM->RainTT.Year % 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Month / 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Month % 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Day / 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Day % 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Hour / 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Hour % 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Minute / 10];
  p[AddNbyte++] = HEXASCII[pM->RainTT.Minute % 10];
  
  element.DType = 0X51;
  element.keyword = "PN05";
  element.value = pM->PN05;
  if(pM->PN05 != 0)
  {
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }  
  element.keyword = "PN10";
  element.value = pM->PN10;
  if(pM->PN10 != 0)
  {
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }  
  element.keyword = "PN30";
  element.value = pM->PN30;
  if(pM->PN30 != 0)
  {
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  element.keyword = "PJ";
  element.value = pM->PJ;
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);

  element.keyword = "PT";
  element.value = pM->PT;
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  return AddNbyte;
}

/*******************************************************************************
�������ƣ�unsigned int WriteMessageTextRain(unsigned char *p,unsigned int  AddNbyte)
�������ܣ��༭��������ͨ�����ݲ���
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
�����������������ͨ�����ݲ���
����ֵ  �����ر��ķ��ͻ������λ��
*******************************************************************************/
unsigned int WriteMessageTextTongDao(unsigned char *p,unsigned int  AddNbyte)
{
  E_data element={0};                   //�ϱ�Ҫ��
  
  /*if(0==(Analog1.Name+Analog2.Name+Analog3.Name+Analog4.Name+RS485.Name))//����ͨ���ر�
  {
    return AddNbyte;
  }*/
  if(0==(Analog1.Name+Analog2.Name+RS485.Name))//����ͨ���ر�
  {
    return AddNbyte;
  }
  
  p[AddNbyte++] = ' '; 
  p[AddNbyte++] = 'T';                                  //�۲�ʱ���ʶ��                               
  p[AddNbyte++] = 'T';    
  p[AddNbyte++] = ' ';  
  p[AddNbyte++] = HEXASCII[pM->ATT.Year / 10];        //�� ʮ����ת��ΪASC��
  p[AddNbyte++] = HEXASCII[pM->ATT.Year % 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Month / 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Month % 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Day / 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Day % 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Hour / 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Hour % 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Minute / 10];
  p[AddNbyte++] = HEXASCII[pM->ATT.Minute % 10];
  

  if(Analog1.Name != 0)
  {
    element.DType = YaoSuInfo[Analog1.Name].DataType;
    element.keyword = YaoSuInfo[Analog1.Name].Bzf;
    element.value = pM->Analog1;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  if(Analog2.Name != 0)
  {
    element.DType = YaoSuInfo[Analog2.Name].DataType;
    element.keyword = YaoSuInfo[Analog2.Name].Bzf;
    element.value = pM->Analog2;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  /*if(Analog3.Name != 0)
  {
    element.DType = YaoSuInfo[Analog3.Name].DataType;
    element.keyword = YaoSuInfo[Analog3.Name].Bzf;
    element.value = pM->Analog3;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  if(Analog4.Name != 0)
  {
    element.DType = YaoSuInfo[Analog4.Name].DataType;
    element.keyword = YaoSuInfo[Analog4.Name].Bzf;
    element.value = pM->Analog4;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }*/
  if(RS485.Name != 0)
  {
    element.DType = YaoSuInfo[RS485.Name].DataType;
    element.keyword = YaoSuInfo[RS485.Name].Bzf;
    element.value = pM->RS485;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
 
  return AddNbyte;
}

unsigned int WriteMessageTextData(unsigned char *p,unsigned int  AddNbyte)
{
  E_data element={0};                   //�ϱ�Ҫ��
  
  if(Rainfall.Type!=0)
  {
    AddNbyte = WriteMessageTextRain(p,AddNbyte);
  }
  
  AddNbyte = WriteMessageTextTongDao(p,AddNbyte);
  
  element.keyword = "AI";                               //�༭�豸�¶�
  element.DType = 0X31;
  element.value = RTU.Temp;
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "VT";                               //�༭˲ʱ����
  element.DType = 0X42;
  element.value = RTU.Voltage;
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  p[AddNbyte++] = ' ';
  
  return AddNbyte;
}

/*******************************************************************************
�������ƣ�unsigned int WriteMessageBasicConfig(unsigned char *p,unsigned int  AddNbyte)
�������ܣ��༭�Զ������ñ�����
���������unsigned char *p-------->���ķ��ͻ������׵�ַ
          unsigned int  AddNbyte-->���ķ��ͻ������λ��
����������Զ�����������
����ֵ  �����ر��ķ��ͻ������λ��
*******************************************************************************/
unsigned int WriteMessageConfig(unsigned char *p,unsigned int  AddNbyte)
{
  E_data element={0};                   //�ϱ�Ҫ��
  
  AddNbyte -= 2;                           //�����Ѿ��༭��ɵ�ң��վ������
  
  element.keyword = "20";               //��ʱ�����
  element.DType = 0X20;
  element.value = ReadUInt8(EEPROM.DingShiBaoTime);
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "21";               //�ӱ������
  element.DType = 0X30;
  element.value = ReadUInt8(EEPROM.JiaBaoTime); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "22";               //��ˮ������ʼʱ��
  element.DType = 0X20;
  element.value = ReadUInt8(EEPROM.PDTime); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "23";               //�������
  element.DType = 0X50;
  element.value = ReadUInt16(EEPROM.CaiYangJianGe); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "24";               //�洢���
  element.DType = 0X50;
  element.value = ReadUInt16(EEPROM.CunChuJianGe); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "25";               //�����Ʒֱ���
  element.DType = 0X21;
  element.value = ReadUInt8(EEPROM.RainFBL); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "26";               //�����ӱ�ʱ�� TODO XF �ͱ�׼����
  element.DType = 0X20;
  element.value = ReadUInt8(EEPROM.RainJBSD); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "27";               //�����ӱ���ֵ
  element.DType = 0X51;
  element.value = ReadUInt16(EEPROM.RainJBFZ); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "28";               //ˮλ��ֵ
  element.DType = 0X73;
  element.value = ReadSInt32(EEPROM.ShuiWeiJiZhi);
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "29";               //ˮλ������ֵ
  element.DType = 0X73;
  element.value = ReadSInt32(EEPROM.XiuZhengJiZhi);
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  element.keyword = "30";               //ˮλ�ӱ�����
  element.DType = 0X53;
  element.value = ReadUInt16(EEPROM.WaterChaLiang); 
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  
  p[AddNbyte++] = ' ';
  
  return AddNbyte;
}



/*��ϢУ�飬�ɹ����� ֡��ʼ����ַ��ʧ�ܷ��� NULL*/
unsigned char* RxdMessageCrc(void)
{
  unsigned int k=0;
  unsigned int i=0;
  unsigned int temp=0;

  for(i=0;i<UART0_RxdLeng;i++)
  {
    if((UART0_RxdLeng-i)<40)
      break;
    
    if(SOH==UART0_RxdBuff[i])
    {
      if((STX==UART0_RxdBuff[i+23])&&((0X38==UART0_RxdBuff[i+19])))
      {
        temp = 0;
        temp = ASCII_Hex(UART0_RxdBuff[i+20]);
        temp <<= 4;
        temp += ASCII_Hex(UART0_RxdBuff[i+21]);
        temp <<= 4;
        temp += ASCII_Hex(UART0_RxdBuff[i+22]);
    
        if((temp+24+i)<(UART0_RxdLeng-4))
        {
          k = UART0_RxdBuff[temp+24+i];
          if((k==ENQ)||(k==EOT)||(k==ACK)||(k==NAK)||(k==ESC))
          {
            k = temp+25+i;
            temp = 0;
            temp = ASCII_Hex(UART0_RxdBuff[k]);
            temp <<= 4;
            temp += ASCII_Hex(UART0_RxdBuff[k+1]);
            temp <<= 4;
            temp += ASCII_Hex(UART0_RxdBuff[k+2]);
            temp <<= 4;
            temp += ASCII_Hex(UART0_RxdBuff[k+3]);
            temp = (temp>>8)|(temp<<8); 
            
            k -= i;
            if(temp==CRC16(&UART0_RxdBuff[i],k))
            {
              return &UART0_RxdBuff[i];
            }
            else
            {
              #if  DEBUG>=3
              WriteLineStrUART1("CRC ERROR!");
              #endif
              return NULL;
            }
          }
        }       
      }
    }
  }
  
  #if  DEBUG>=3
  WriteLineStrUART1("ACK ERROR");
  #endif
  
  return NULL;
}

/*******************************************************************************
�������ƣ�void MessageHandlers(void)
�������ܣ��յ���Ϣ����
�����������
�����������
����ֵ  ����
*******************************************************************************/
void MessageHandlers(unsigned char *p)
{
  ClassRxdMessage Messageinfo={0};
  unsigned char i=0;
  
  pRM = &Messageinfo;
  
  Com.Status.Flag.Online = True;                //���߱�־��λ
  Com.TiClose = Com.CloseDelay;                 //��ʼ��������ʱ��ʱ
    
  pRM->ST[0] = ToAscii_Hex(p[1],p[2]);          //ң��վ��ַ
  pRM->ST[1] = ToAscii_Hex(p[3],p[4]);
  pRM->ST[2] = ToAscii_Hex(p[5],p[6]);
  pRM->ST[3] = ToAscii_Hex(p[7],p[8]);
  pRM->ST[4] = ToAscii_Hex(p[9],p[10]);
  
  for(i=0;i<5;i++)
  {
    if(pRM->ST[i]!=RTU.ST[i])
    {
      #if DEBUG >= 3
      WriteLineStrUART1("ST ERROR");
      #endif
      return;
    }    
  }
  
  pRM->CenterAdd = ToAscii_Hex(p[11],p[12]);//����վ��ַ
  pRM->PassWord = ToAscii_Hex(p[13],p[14]); //����
  pRM->PassWord <<= 8;
  pRM->PassWord += ToAscii_Hex(p[15],p[16]);
  pRM->AFN = ToAscii_Hex(p[17],p[18]);          //������
  pRM->TextLeng = ToAscii_Hex(p[21],p[22]);     //���ĳ���
  
  if(pRM->PassWord != RTU.Password)
  {
    #if DEBUG >= 3
    WriteLineStrUART1("Password ERROR");
    #endif
    return;
  }
  
  pRM->RxdTime.Year = ToAscii_U8(p[28],p[29]);
  pRM->RxdTime.Month = ToAscii_U8(p[30],p[31]);
  pRM->RxdTime.Day = ToAscii_U8(p[32],p[33]);
  pRM->RxdTime.Hour = ToAscii_U8(p[34],p[35]);
  pRM->RxdTime.Minute = ToAscii_U8(p[36],p[37]);
  pRM->RxdTime.Second = ToAscii_U8(p[38],p[39]);
  
  if(False == TimeCheck(pRM->RxdTime))   //ʱ�����ݷǷ�
  {
    #if DEBUG >= 3
    WriteLineStrUART1("Time ERROR");
    #endif
    return;
  }
  
  pRM->End = p[pRM->TextLeng+24];
  
  Com.Status.Flag.ComEvent = RESET;   //ͨ���¼���λ
  Com.Status.Flag.Txd = RESET;        //����״̬��־��λ    
  Com.TxdCount = 0;                   //���ͼ�������
  Com.TiTxdTime = 0;                  //���ͳ�ʱ��ʱ����
  
  if(ESC==pRM->End)                     //����������ն˱�������
  {
    Com.Status.Flag.Close = RESET;      //��ֹ�ر�ͨ�ŵ�Դ
    #if DEBUG >= 3
    WriteLineStrUART1("ESC");
    #endif
  }
  else if(EOT==pRM->End)                //����������˳�
  {
    Com.Status.Flag.Close = SET;        //����ر�ͨ�ŵ�Դ  
    #if DEBUG >= 3
    WriteLineStrUART1("EOT");
    #endif
  }
  else if(ENQ==pRM->End)                //����վԶ�̹���
  {
    Com.Status.Flag.Close = RESET;      //��ֹ�ر�ͨ�ŵ�Դ
    #if DEBUG >= 3
    WriteLineStrUART1("ENQ");
    #endif
    if(AFN.ChaXunShiShi==pRM->AFN)      //��ȡʵʱ����
    {
      AddCaiYangTask(AFN.ChaXunShiShi); 
    }
    else if(AFN.GetRunConfig==pRM->AFN) //��ȡ������Ϣ
    {
      AddMessengeTask(AFN.GetRunConfig); 
    }
    else if(AFN.SetRunConfig==pRM->AFN)//�޸�������Ϣ
    {
      SetRunConfig(&p[40]);
      AddMessengeTask(AFN.GetRunConfig); 
    }
    /*else if(AFN.ChaXunShiDuan==pRM->AFN)
    {
      Flash.Satrtime.Year = ToAscii_U8(p[40],p[41]);
      Flash.Satrtime.Month = ToAscii_U8(p[42],p[43]);
      Flash.Satrtime.Day = ToAscii_U8(p[44],p[45]);
      Flash.Satrtime.Hour = ToAscii_U8(p[46],p[47]);
      Flash.Satrtime.Minute = ToAscii_U8(p[48],p[49]);
      Flash.Endtime.Year = ToAscii_U8(p[50],p[51]);
      Flash.Endtime.Month = ToAscii_U8(p[52],p[53]);
      Flash.Endtime.Day = ToAscii_U8(p[54],p[55]);
      Flash.Endtime.Hour = ToAscii_U8(p[56],p[57]);
      Flash.Endtime.Minute = ToAscii_U8(p[58],p[59]);
      
      if(TimeCheck(Flash.Satrtime)&&TimeCheck(Flash.Endtime))
      {
        Message.AFN = AFN.ChaXunShiDuan;
        System.Event.Bit.Flash = SET;
      }           
    }*/
    else if(0XDF==pRM->AFN)             //��λ����
    {
      WriteLineStrUART0("Reset...\x0d\x0a");
      delayms(5000);
      WDTCTL = 0;  
    }
  }
  if(pRM->End!=ENQ)           //ͬ��ʱ��
  {
    System.Time = pRM->RxdTime;
    SetTime(&System.Time);
    #if DEBUG >= 3
    WriteLineStrUART1("Set Time");
    #endif
    if((AFN.XiaoShi==pRM->AFN)&&(AFN.XiaoShi==pM->AFN))//Ӧ���Ĺ�����ΪСʱ�� �� ǰһ�η��͵ı���ΪСʱ��
    {
      UpdateDRPZ();           //����Сʱ������
    }
    if(DRPZ.sp)                 //Сʱ�����治Ϊ�� 
    { 
      AddMessengeTask(AFN.XiaoShi);
      DRPZ.Now = DRPZ.Array[0];
    }
  }
  DisplayRunInfo("�����ɹ�");
}

unsigned char* SetConfiginfo(unsigned char *p)
{
  unsigned char id=0;
  long value=0;
  unsigned char i=0;
  
  for(i=0;i<5;i++)
  {
    if(*p < 0X1C)
      return NULL;
    if(*p != ' ') 
      break;
    
    p++;
  }
  if(i >= 5)
    return NULL;
  
  id = ToAscii_Hex(p[0],p[1]);
  p += 2;
  
  for(i=0;i<5;i++)
  {
    if(*p < 0X1C)
      return NULL;
    if(*p != ' ') 
      break;
    
    p++;
  }
  if(i >= 5)
    return NULL;
  
  for(i=0;i<10;i++)
  {
    if(p[i] < 0X1C)
      return NULL;
    if(' '==p[i])
      break;
  }
  if(i >= 10)
    return NULL;

  switch(id)
  {
    case 0X20:
      {
        value = AtoLong(p,i,0X20);
        WriteUInt8((unsigned char)value,EEPROM.DingShiBaoTime);

      }break;
    case 0X21:
      {
        value = AtoLong(p,i,0X30);
        WriteUInt8((unsigned char)value,EEPROM.JiaBaoTime);

      }break;
    case 0X22:
      {
        value = AtoLong(p,i,0X20);
        WriteUInt8((unsigned char)value,EEPROM.PDTime);
      }break;
    case 0X23:
      {
        value = AtoLong(p,i,0X50);
        WriteUInt16((unsigned int)value,EEPROM.CaiYangJianGe);
      }break;
    case 0X24:
      {
        value = AtoLong(p,i,0X50);
        WriteUInt16((unsigned int)value,EEPROM.CunChuJianGe);
      }break;
    case 0X25:
      {
        value = AtoLong(p,i,0X21);
        WriteUInt8((unsigned char)value,EEPROM.RainFBL);
      }break;
    case 0X26:
      {
        value = AtoLong(p,i,0X20);
        WriteUInt8((unsigned char)value,EEPROM.RainJBSD);
      }break;
    case 0X27:
      {
        value = AtoLong(p,i,0X51);
        WriteUInt16((unsigned int)value,EEPROM.RainJBFZ);
      }break;
    case 0X28:
      {
        value = AtoLong(p,i,0X73);
        WriteSInt32(value,EEPROM.ShuiWeiJiZhi); 
      }break;
    case 0X29:
      {
        value = AtoLong(p,i,0X73);
        WriteSInt32(value,EEPROM.XiuZhengJiZhi);
      }break;
    case 0X30:
      {
        value = AtoLong(p,i,0X53);
        WriteUInt16((unsigned int)value,EEPROM.WaterChaLiang);
      }break;
  }
  
  p += i;
  return p;
}

void SetRunConfig(unsigned char *p)
{
  unsigned char i=0;
  
  for(i=0;i<12;i++)
  {
    p = SetConfiginfo(p);
    if(NULL==p)
    {
      #if DEBUG>=3
        WriteLineStrUART1("NULL==p");
      #endif
        return;
    }     
  }
}


unsigned int WriteMessageTextLiShiDada(unsigned char *p,unsigned int  AddNbyte)
{
  E_data element={0};
  
  p[AddNbyte++] = ' '; 
  p[AddNbyte++] = 'T';                                  //�۲�ʱ���ʶ��                               
  p[AddNbyte++] = 'T';    
  p[AddNbyte++] = ' ';  
  p[AddNbyte++] = HEXASCII[LsData.TT.Year / 10];        //�� ʮ����ת��ΪASC��
  p[AddNbyte++] = HEXASCII[LsData.TT.Year % 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Month / 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Month % 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Day / 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Day % 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Hour / 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Hour % 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Minute / 10];
  p[AddNbyte++] = HEXASCII[LsData.TT.Minute % 10];
   
  element.keyword = "PT";
  element.value = LsData.PT;
  element.DType = 0X51;
  AddNbyte = WriteMessageVariable(p,AddNbyte,&element);  
  
  if(Analog1.Name != 0)
  {
    element.DType = YaoSuInfo[Analog1.Name].DataType;
    element.keyword = YaoSuInfo[Analog1.Name].Bzf;
    element.value = AnalogCalc(Analog1.SType,LsData.A1,Analog1.Max,Analog1.Min);
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  if(Analog2.Name != 0)
  {
    element.DType = YaoSuInfo[Analog2.Name].DataType;
    element.keyword = YaoSuInfo[Analog2.Name].Bzf;
    element.value = AnalogCalc(Analog2.SType,LsData.A2,Analog2.Max,Analog2.Min);
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  if(RS485.Name != 0)
  {
    element.DType = YaoSuInfo[RS485.Name].DataType;
    element.keyword = YaoSuInfo[RS485.Name].Bzf;
    element.value = LsData.Rs485;
    AddNbyte = WriteMessageVariable(p,AddNbyte,&element);
  }
  
  return AddNbyte;
}

unsigned int WriteMessageTextDRPZ(unsigned char *p,unsigned int  AddNbyte)
{
  unsigned char a[40]={0XFF};

  unsigned char i=0;
  
  if((0==DRPZ.Now.Page)||(0==DRPZ.Now.Bytes))
    return AddNbyte;
  
  memset(a,0XFF,sizeof(a));
  
  a[0] = System.Time.Year;
  a[1] = System.Time.Month;
  a[2] = System.Time.Day;
  a[3] = System.Time.Hour;
  
  if(FindFlash())
  {
    SPI_Init();
    AT45DB041B_MainMemoryPageRead(DRPZ.Now.Page,DRPZ.Now.Bytes,a,40);
    SPI_End();
  }
  else
  {
    return AddNbyte;
  }
  
  p[AddNbyte++] = ' '; 
  p[AddNbyte++] = 'T';                        //�۲�ʱ���ʶ��                               
  p[AddNbyte++] = 'T';    
  p[AddNbyte++] = ' ';  
  p[AddNbyte++] = HEXASCII[a[0] / 10];        //�� ʮ����ת��ΪASC��
  p[AddNbyte++] = HEXASCII[a[0] % 10];
  p[AddNbyte++] = HEXASCII[a[1] / 10];
  p[AddNbyte++] = HEXASCII[a[1] % 10];
  p[AddNbyte++] = HEXASCII[a[2] / 10];
  p[AddNbyte++] = HEXASCII[a[2] % 10];
  p[AddNbyte++] = HEXASCII[a[3] / 10];
  p[AddNbyte++] = HEXASCII[a[3] % 10];
  p[AddNbyte++] = HEXASCII[0];
  p[AddNbyte++] = HEXASCII[0];
  if(Rainfall.Type)             //�����ƽ���
  {
    p[AddNbyte++] = ' '; 
    p[AddNbyte++] = 'D'; 
    p[AddNbyte++] = 'R'; 
    p[AddNbyte++] = 'P'; 
    p[AddNbyte++] = ' '; 
    for(i=4;i<16;i++)
    {
      p[AddNbyte++] = HEXASCII[a[i]>>4];
      p[AddNbyte++] = HEXASCII[a[i]&0X0F];
    }
  }
  if(RTU.RTUType!=RTUTYPE_JS)
  {
    p[AddNbyte++] = ' '; 
    p[AddNbyte++] = 'D'; 
    p[AddNbyte++] = 'R'; 
    p[AddNbyte++] = 'Z'; 
    p[AddNbyte++] = '1'; 
    p[AddNbyte++] = ' ';
    for(i=16;i<40;i++)
    {
      p[AddNbyte++] = HEXASCII[a[i]>>4];
      p[AddNbyte++] = HEXASCII[a[i]&0X0F];
    }
  }
  
  p[AddNbyte++] = ' ';
  return AddNbyte;
}

