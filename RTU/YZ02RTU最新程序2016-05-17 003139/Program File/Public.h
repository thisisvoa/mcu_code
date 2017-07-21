/*********************************************************
*�ļ����ƣ�Public.h
*ժ    Ҫ����Ӳ���޹صĳ��ù��ܺ���
*
*��    �ߣ����� 
*��ʼ���ڣ�2013��4��16��
*������ڣ�
**********************************************************/

#ifndef __PUBLIC_H
#define __PUBLIC_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define         uchar           unsigned char
#define         uint            unsigned int
#define         True            1                       //��
#define         False           0                       //��
#define         Null            0                       //��ֵ

/*�ַ���ת��Ϊ���ָ�ʽ���ƿ���*/
#define Zero                    (0x0001u)                                    //����ǰ����
#define Symbol                  (0x0002u)                                    //����ǰ����'+'
#define space                   (0x0004u)                                    //ǰ�����滻Ϊ�ո�
#define DEZero                  (0x0008u)                                    //ɾ��β������                                  


/*����ʱ�����ݽṹ*/
typedef struct
{
  unsigned char Year;
  unsigned char Month;
  unsigned char Day;
  unsigned char Hour;
  unsigned char Minute;
  unsigned char Second; 
}DataTime;

/*�޷���16bit�����ṹ�壬���ü���ֱ�ӵõ���8bit���8bit*/
typedef union 
{
  unsigned int num;
  struct 
  {
    unsigned char nLow;
    unsigned char nHigh;
  }bit16;
}Uint16;

/*�з���32bit�����ṹ�壬���ü���ֱ�ӵõ�ÿ��8bit����*/
typedef union
{
  signed long num;
  struct
  {
    Uint16 nLow;
    Uint16 nHigh;
  }bit32;
}Slong32;

/*IEEE754������*/
typedef union
{
  float num;
  struct
  {
    unsigned char a0;
    unsigned char a1;
    unsigned char a2;
    unsigned char a3;
  }bit;
}float_n;
 
extern const unsigned char HEXASCII[16];

unsigned int strlenght(unsigned char *s);
unsigned char Byte_BCD(unsigned char byte);
unsigned char BCD_Byte(unsigned char bcd);
signed char ASCII_Hex(unsigned char asc2);
unsigned char ToAscii_Hex(unsigned char asc1,unsigned char asc2);
unsigned char ToAscii_U8(unsigned char asc1,unsigned char asc2);
unsigned int crc(unsigned char *crc_pointer,unsigned int data_length);
unsigned int CRC16(unsigned char *puchMsg, unsigned int usDataLen);
unsigned char SInt32_TO_String(unsigned char *p,long int value,unsigned char type,unsigned char cmd);
long int String_TO_SInt32(unsigned char *str);
unsigned char TimeCheck(DataTime time);
long int AtoLong(unsigned char *p,unsigned char length,unsigned char type);
unsigned char Timedaymax(DataTime time);

long atofxy(unsigned char *str,unsigned char type);

unsigned char* Search(unsigned char* base,unsigned char nmemb,unsigned char* key,unsigned char len);
int timecmp(DataTime *t0,DataTime *t1);
unsigned int Getbyte2(unsigned char *pa,unsigned char add);
long Getbyte4(unsigned char *pa,unsigned char add);
void Setbyte2(unsigned char *pa,unsigned char add,unsigned int value);
void Setbyte4(unsigned char *pa,unsigned char add,long value);


#endif  /*#ifndef __PUBLIC_H*/
