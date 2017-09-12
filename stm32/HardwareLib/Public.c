/*********************************************************
*�ļ����ƣ�Public.c
*ժ    Ҫ����Ӳ���޹صĳ��ù��ܺ���
*
*��ǰ�汾��1.0
*��    �ߣ����� 
*�������ڣ�2013��12��03��
*
**********************************************************/

#include "Public.h"

const unsigned char HEXASCII[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

const unsigned char auchCRCHi[] = 
{
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
  0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
  0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
  0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
  0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;

const unsigned char auchCRCLo[] = 
{
  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
  0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
  0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
  0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
  0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
  0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
  0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
  0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
  0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
  0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
  0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
  0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
  0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
  0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
  0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
  0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
  0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
  0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
  0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
  0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
  0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
  0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
  0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
  0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

/*******************************************************************************
�������ƣ�unsigned int CRC16(unsigned char *puchMsg, unsigned int usDataLen)
�������ܣ����CRC16
���������unsigned char *puchMsg-------->CRCУ��������ݵ��׵�ַ
          unsigned int usDataLen-------->��ҪУ��ĳ���
���������CRCУ����
����ֵ  ��CRCУ����
*******************************************************************************/
unsigned int CRC16(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned char uchCRCHi = 0xFF; 
  unsigned char uchCRCLo = 0xFF;
  unsigned char uIndex ; 			

  while (usDataLen--) 		
  {
    uIndex = uchCRCHi ^ *puchMsg++;
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
    uchCRCLo = auchCRCLo[uIndex];
  }
  return (uchCRCHi << 8 | uchCRCLo);
}


/**************************************************************
�������ƣ�unsigned int strlenght(unsigned char *s) 
�������ܣ������ַ������ȣ�����������
����������ַ�����ַ
���������
����ֵ  ���ɹ������ַ������ȣ��մ��򳤶ȴ���65530����0
*************************************************************/
unsigned int strlenght(unsigned char *s) 
{
  unsigned int i;
  
  for(i=0;i<65530;i++)
  {
    if(*s == '\0')
    {
      return i;
    }
    s++;
  }
  return 0;
}

/*******************************************************************************
�������ƣ�unsigned char Byte_BCD(unsigned char byte)
�������ܣ�������Ϊ1byte���޷���������ת��ΪBCD��
���������unsigned char byte-------->��Ҫת�����޷���������
�����������
����ֵ  ���ɹ�����BCD��
          ʧ�ܷ���0,HEX������99
*******************************************************************************/
unsigned char Byte_BCD(unsigned char byte)
{
  unsigned char bcd=0;
  
  if(byte > 99)
    return 0;
  
  bcd = byte / 10;
  bcd <<= 4;
  bcd += byte%10;
  
  return bcd;
}

/**************************************************************
�������ƣ�unsigned char BCD_Byte(unsigned char bcd)
�������ܣ�����λBCD��ת��Ϊ����Ϊ1byte���޷���������
���������unsigned char bcd---->��ת����BCD��
�����������
����ֵ  ��ת����ɵ��޷���������
*************************************************************/
unsigned char BCD_Byte(unsigned char bcd)
{
  unsigned char temp=0;
  
  temp = bcd >> 4;
  temp *= 10;
  temp += bcd & 0X0F;
  return temp;
}

/**************************************************************
�������ƣ�signed char ASCII_Hex(unsigned char asc2)
�������ܣ���һ��ʮ������ASCII���ַ�ת��Ϊ8bitHEX�޷�������
          ��Ч�ַ� 0~9 a~f A~F
���������unsigned char asc2---->ASC2�ַ�
�����������
����ֵ  ���ɹ����� ת��ֵ  ʧ�ܷ��� -1;
*************************************************************/
signed char ASCII_Hex(unsigned char asc2)
{
  if((asc2>='0')&&(asc2<='9'))
  {
    return (asc2 & 0X0F);
  }
  else if((asc2>='A')&&(asc2<='F'))
  {
    return (asc2 - 55);
  }
  else if((asc2>='a')&&(asc2<='f'))
  {
    return (asc2 - 87);
  }
  
  return -1;
}

/**************************************************************
�������ƣ�unsigned char ToAscii_Hex(unsigned char asc1,unsigned char asc2)
�������ܣ���2��ASC2���ַ�ת��ΪHEX
���������unsigned char asc1---->��һ��ASC2�ַ�
          unsigned char asc1---->�ڶ���ASC2�ַ�
�����������
����ֵ  ���ɹ����� ת��ֵ  ʧ�ܷ��� 0;
*************************************************************/
unsigned char ToAscii_Hex(unsigned char asc1,unsigned char asc2)
{
  unsigned char hex=0;
  signed char temp=0;
  
  temp = ASCII_Hex(asc1);
  if(-1 == temp)                 //�Ƿ��ַ�
    return 0;
  
  hex = temp;
  hex <<= 4;
  temp = ASCII_Hex(asc2);
  if(-1 == temp)                 //�Ƿ��ַ�
    return 0;
  
  hex += temp;
  return hex; 
}

/**************************************************************
�������ƣ�unsigned char ToAscii_U8(unsigned char asc1,unsigned char asc2)
�������ܣ���2��ASC2���ַ�ת��Ϊ8bitʮ�����޷�������
���������unsigned char asc1---->��һ��ASC2�ַ�
          unsigned char asc1---->�ڶ���ASC2�ַ�
�����������
����ֵ  ���ɹ����� ת��ֵ  �����Ƿ��ַ����� 0
*************************************************************/
unsigned char ToAscii_U8(unsigned char asc1,unsigned char asc2)
{
  unsigned char u8=0;
  
  if((asc1>='0')&&(asc1<='9'))
  {
    asc1 &= 0X0F;
    u8 = asc1 * 10;
  }
  else
  {
    return 0;
  }
  if((asc2>='0')&&(asc2<='9'))
  {
    asc2 &= 0X0F;
    u8 += asc2;
  }
  else
  {
    return 0;
  }
  
  return u8; 
}

/*******************************************************************************
�������ƣ�unsigned int crc(unsigned char *crc_pointer,unsigned int data_length)
�������ܣ�CRC16
���������unsigned char *crc_pointer-------->CRCУ��������ݵ��׵�ַ
          unsigned int data_length  -------->��ҪУ��ĳ���
���������CRCУ����
����ֵ  ��CRCУ����
*******************************************************************************/
unsigned int crc(unsigned char *crc_pointer,unsigned int data_length)
{
  unsigned int k,k0,bit_flag;
  unsigned int int_crc=0xffff;
  for (k=0;k<data_length;k++)
  {
    int_crc ^= *(crc_pointer++);
    for(k0=0;k0<8;k0++)
    {
      bit_flag = int_crc&0x0001;
      int_crc >>= 1;
      if (bit_flag == 1)
        int_crc ^= 0xa001;                         
    }
  }
  return(int_crc);                     //��λ��ǰ��λ�ں�
}

/*********************************************************************************************
�������ƣ�unsigned char SInt32_TO_String(unsigned char *p,long int value,unsigned char point)
�������ܣ���long int ��תΪASC2���ַ���         
          �����Զ�����'-'��ת��ʱ�����ַ���������'\0'
���������unsigned char *p----->ת����ɺ��ַ����ı����ַ
          long int value------->��Ҫת���ĳ�������
          unsigned char type--->��������  type=0Xxy, N(x,y)[����λ��С��λ]
          unsigned char cmd---->��ʽ���� Symbol����+-���ţ�Zero����ǰ��0��spaceǰ��0�滻Ϊ�ո�
                                           DEZero ɾ��β������
���������ת����ɵ��ַ���
����ֵ  ��С��λ����9ʱ���� 0

          ����ת����ɵ��ַ������ȣ��������ַ���������
*********************************************************************************************/
unsigned char SInt32_TO_String(unsigned char *p,long int value,unsigned char type,unsigned char cmd)
{
  unsigned char str[14]={0};                     //ת���ַ�������
  unsigned char flag=False;                      //������ʶ
  unsigned long int quan=1;                      //ʮ����Ȩ 

  unsigned char i=0,j=0,k=0;
  ldiv_t lnum={0,0};

  if(0==type)
    return 0;
  
  if((type>>4)>9)
    return 0;
  if((type&0X0F)>9)
    return 0;
  
  i = type>>4;                                  //����λ��  
  for(;i>0;i--)                                 //���λ��Ȩ
  {
    quan *= 10;
  }
  
  if((type&0X0F) > 8)                           //С��λ������8����0                                                
  {
    return 0;
  }
  
  if(value < 0)                                 //ת������Ϊ����ʱ
  {
    value = 0 - value;                          //�������ֵ
    flag = True;
  }
                       
  lnum = ldiv(value,quan);
  quan /= 10;
  
  /*ת��ΪASC���ַ�������ʮ�������ֵ�����λ��ʼ*/
  for(i=0;i<11;i++)
  {
    if((type>>4)==((type&0x0f)+i))                           //����С����
    {      
      if((type&0x0f) != 0)
        str[i] = '.';     
      continue;
    }
    
    lnum = ldiv(lnum.rem,quan);                 //���������� ����ʮ��������λ��Ȩ ��=lnum.quot�� ����=lnum.rem
    quan /= 10;                                 
    str[i]=HEXASCII[(unsigned char)lnum.quot];//ת��ΪASC����
    if(0 == quan)
      break;
  } 

  for(i=0;i<11;i++)                             //���ҵ�һ����Ϊ'0'�ַ���λ��
  {
    if('\0' == str[i])                          //�ҵ��������˳�����
    {
      i--;
      break;
    }    
    if(str[i] != '0')  
    {
      if('.' == str[i])
        i--;
      break;
    }   
  }
  
  if(cmd & space)                        //ǰ��0ת��Ϊ�ո�
  {
    if(0==i)                            //��Ϊ��0����λ��Ϊ0
    {
      j = 0;                                               
      if(flag == True)                              //Ϊ����ʱ��д�븺�� '-'
      {
        p[j++] = '-';
      }
      else if(cmd & Symbol)                         //�Ƿ����+��
      {
        p[j++] = '+';
      }
    }
    else
    {
      for(j=0;j<i;j++)
      {
        str[j] = ' ';
      }
      if(flag == True)
      {
        str[--j] = '-';
      }
      else if(cmd & Symbol)
      {
        str[--j] = '+';
      }
      j = 0;
    }    
  }
  else
  {
    j = 0;                                               
    if(flag == True)                              //Ϊ����ʱ��д�븺�� '-'
    {
      p[j++] = '-';
    }
    else if(cmd & Symbol)                         //�Ƿ����+��
    {
      p[j++] = '+';
    }
  }
  
  if((cmd&DEZero)&&(type&0X0F))                              //��С��ʱɾ��β������
  {
    for(k=0;k<14;k++)                           //���ҽ�����
    {
      if(str[k] == 0)
        break;
    }
    if(k < 13)
    {
      k--;
      for(;k>0;k--)
      {
        if(str[k]=='0')
        {
          str[k] = 0;
        }
        else if(str[k]=='.')
        {
          str[k] = 0;
          break;
        }
        else
        {
          break;
        }  
      }     
    }
  }
  
  if(cmd &(Zero+space))                  //����ǰ��0��ǰ��0�滻Ϊ�ո�
    i = 0;
   
  for(;j<12;j++)
  {
    p[j] = str[i++];
    if('\0' == p[j])
      break;
  }
  
  return j;   
}

/*******************************************************************************
�������ƣ�long atofxy(unsigned char *str,unsigned char type)
�������ܣ��ַ���ת��Ϊָ����ʽ����С��
���������unsigned char *str-------->ת�����ַ���      
���������unsigned char type-------->��������  N(x,y)[����λ��С��λ]
����ֵ  �� ת�������
ʧ�ܷ��� 0
*******************************************************************************/
long atofxy(unsigned char *str,unsigned char type)
{
  double num=0;
  unsigned long x=1,max=1;
  unsigned char i=0;
  
  i = type & 0X0F;      //ת����С��λ��
  for(;i>0;i--)
  {
    x *= 10;
  } 
  
  i = type >> 4;         //ת��ֵ��������ֵ
  for(;i>0;i--)
  {
    max *= 10;
  }
  num = atof((char const*)str); //ת�����
  num *= x;
  
  if((unsigned long)(fabs(num)) >= max) //ת�����������������ֵ����0
  {
    return 0;
  }
  
  return (long)num;
}

/*******************************************************************************
�������ƣ�long int String_TO_SInt32(unsigned char *str)
�������ܣ��ַ���ת��Ϊ32λ�з�������
���������*str-------->ת�����ַ���      
�����������
����ֵ  �� ת����ɵ�32λ�з���������
ʧ�ܷ��� 0
*******************************************************************************/
long int String_TO_SInt32(unsigned char *str)
{
  unsigned char i=0,j=0;
  unsigned long quan=1;
  long rvalue=0;
  
  i = strlenght(str);
  
  for(j=0;j<10;j++)     //�������һλ���ֵ�λ��
  {
    i--;
    if((str[i]>='0')&&(str[i]<='9'))
      break;
    
    if(0==i)
      break;
  }
  for(j=0;j<10;j++)
  {
    if((str[i]>='0')&&(str[i]<='9'))
    {
      rvalue += (str[i]&0X0F)*quan;
      quan *= 10;
    }
    else if(!(str[i]=='+'||str[i]=='-'||str[i]=='.'))//�Ƿ��ַ�
    {
        return 0;
    }
    if(0==i)
      break;
    i--;
  } 
  if(str[0]=='-')       //����
    rvalue = 0 - rvalue;
     
  return rvalue;  
}

/*******************************************************************************
�������ƣ�unsigned char TimeCheck(Time time)
�������ܣ����ʱ�������Ƿ�Ϸ�
���������Time time-------->����ʱ��                                
�����������Ҫ����ʱ������
����ֵ  ����ȷ����1 
          ���󷵻�0
*******************************************************************************/
unsigned char TimeCheck(DataTime time)
{
  if(time.Year > 99)
    return 0; 
  if(time.Month<1 || time.Month>12)
    return 0;
  if(time.Day<1 || time.Day>31)
    return 0;
  if(time.Hour > 23)
    return 0;
  if(time.Minute > 59)
    return 0;
  if(time.Second > 59)
    return 0;
  
  return 1; 
}

/*******************************************************************************
�������ƣ�long int AtoLong(unsigned char *p,unsigned char length,unsigned type)
�������ܣ���ָ�����ȵ��ڴ�����ָ����ʽ����С��
���������unsigned char *p-------->�׵�ַ 
          unsigned char length---->����
          unsigned char type------>��������
�����������
����ֵ  ����ȷ���� ת����� 
          ���󷵻� 0
*******************************************************************************/
long int AtoLong(unsigned char *p,unsigned char length,unsigned char type)
{
  unsigned char strtemp[15]={0};
  unsigned char i=0;
  
  for(i=0;i<length;i++)
  {
    strtemp[i] = p[i];
  }
  return atofxy(strtemp,type);
}

/*******************************************************************************
�������ƣ�unsigned char Timedaymax(Time time)
�������ܣ�����ʱ�����������ֵ
���������Time time-------->�����ʱ��       
�����������
����ֵ  �����������ֵ
*******************************************************************************/
unsigned char Timedaymax(DataTime time)
{
   unsigned char mont[7]={1,3,5,7,8,10,12};//���Ϊ31����·�
   unsigned char i=0;
   unsigned char max=0;
   
   for(i=0;i<7;i++)
   {
     if(time.Month == mont[i])
       break;
   }
   if(i < 7)
   {
     max = 31;
   }
   else if(time.Month == 2)
   {
     max = 28;
     if(time.Year%4 == 0)//����
      max = 29;
   }
   else
     max = 30;
   
   return max;
}


/*******************************************************************************
�������ƣ�unsigned char* Search(unsigned char* base,unsigned char nmemb,unsigned char* key,unsigned char len)
�������ܣ�����
���������unsigned char* base---->����������ָ�� 
          unsigned char nmemb---->����������Ԫ�ظ���
          unsigned char* key ---->Ҫ������������ָ��
          unsigned char len  ---->Ҫ��������Ԫ�ظ���
�����������
����ֵ  ���ɹ�����base����key������ͬ��ָ��
          ʧ�ܷ��ؿ�ָ�� NULL
*******************************************************************************/
unsigned char* Search(unsigned char* base,unsigned char nmemb,unsigned char* key,unsigned char len)
{
  unsigned char i=0;
  unsigned char j=0,k=0;

  if(nmemb < len)
    return NULL;
  
  for(i=0;i<=nmemb-len;i++)
  {
    if(base[i]==key[0])
    {
      k = i;
      for(j=0;j<len;j++,k++)
      {
        if(base[k] != key[j])
          break;
      }
      if(j >= len)
        return &base[i];
    }
  }  
  
  return NULL;
}
/*�Ƚ�����ʱ��
t0 > t1 ���� 1
t0 < t1 ����-1
t0 = t1 ����0
*/
int timecmp(DataTime *t0,DataTime *t1)
{
  unsigned char *pt0,*pt1;
  unsigned char i=0;
  
  pt0 = (unsigned char*)t0;
  pt1 = (unsigned char*)t1;
  
  for(i=0;i<6;i++)
  {
    if(pt0[i]>pt1[i])
      return 1;
    
    if(pt0[i]<pt1[i])
      return -1;
  }
  
  return 0;
}

unsigned int Getbyte2(unsigned char *pa,unsigned char add)
{
  Uint16 value={0};
  
  value.bit16.nHigh = pa[add++];
  value.bit16.nLow = pa[add];
  return value.num;
}

long Getbyte4(unsigned char *pa,unsigned char add)
{
  Slong32 s32={0};
  
  s32.bit32.nHigh.bit16.nHigh = pa[add++];          //��16bit�еĸ�8bit
  s32.bit32.nHigh.bit16.nLow = pa[add++];           //��16bit�еĵ�8bit
  s32.bit32.nLow.bit16.nHigh = pa[add++];           //��16bit�еĸ�8bit
  s32.bit32.nLow.bit16.nLow = pa[add];              //��16bit�еĵ�8bit
  
  return s32.num;
}

void Setbyte2(unsigned char *pa,unsigned char add,unsigned int value)
{
  Uint16 u16={0};
  
  u16.num = value;
  pa[add++] = u16.bit16.nHigh;
  pa[add] = u16.bit16.nLow;
}

void Setbyte4(unsigned char *pa,unsigned char add,long value)
{
  Slong32 s32={0};
  
  s32.num = value;
  
  pa[add++] = s32.bit32.nHigh.bit16.nHigh;
  pa[add++] = s32.bit32.nHigh.bit16.nLow;
  pa[add++] = s32.bit32.nLow.bit16.nHigh;
  pa[add] = s32.bit32.nLow.bit16.nLow;
}
/*******************************************************************************
�������ƣ�convert_byte_to_ascall
�������ܣ���byteת�������ֽڵ�ascall
���������

�������:
����ֵ  ��
*******************************************************************************/

void convert_byte_to_ascall(uint8_t byte,uint8_t *asc1,uint8_t *asc2){
	uint8_t hByte = byte >> 16;
	uint8_t lByte = byte - (byte >> 16);

	if(hByte >= 10){
		*asc1 = hByte + 'a' - 10;//a-f
	}
	else{
		*asc1 = hByte + '0';
 	}

	if(lByte >= 10){
		*asc2 = lByte + 'a' - 10;
	}
	else{
		*asc2 = lByte + '0';
 	}
}

