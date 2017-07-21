
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
#include "stdio.h"
#include "stdarg.h"
#include "sysmac.h"

#define         uchar           char
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
  char Year;
  char Month;
  char Day;
  char Hour;
  char Minute;
  char Second; 
}DataTime;

/*�޷���16bit�����ṹ�壬���ü���ֱ�ӵõ���8bit���8bit*/
typedef union 
{
  unsigned int num;
  struct 
  {
    char nLow;
    char nHigh;
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
    char a0;
    char a1;
    char a2;
    char a3;
  }bit;
}float_n;

typedef union
{
  unsigned int i;
  struct
  {
    char L;
    char H;
  }CharPart;
}UnionInt;

typedef union
{
  long l;
  struct
  {
    unsigned int L;
    unsigned int H;
  }IntPart;
  struct
  {
    char LL;
    char LH;
    char HL;
    char HH;
  }CharPart;
}UnionLong;
 
extern const char HEXASCII[16];

unsigned int strlenght(char *s);
char Byte_BCD(char byte);
char BCD_Byte(char bcd);
signed char ASCII_Hex(char asc2);
char ToAscii_Hex(char asc1,char asc2);
char ToAscii_U8(char asc1,char asc2);
unsigned int crc(char *crc_pointer,unsigned int data_length);
unsigned int CRC16(char *puchMsg, unsigned int usDataLen);
char SInt32_TO_String(char *p,long int value,char type,char cmd);
long int String_TO_SInt32(char *str);
char TimeCheck(DataTime time);
long int AtoLong(char *p,char length,char type);
char Timedaymax(DataTime time);
long atofxy(char *str,char type);
char* Search(char* base,char nmemb,char* key,char len);
int timecmp(DataTime *t0,DataTime *t1);
void reverse(char* begin, char* end);
void itoa(int value, char* str, int base);
void ltoax(long value, char* str, int base) ;
void ltoa(long int n,char *str);
unsigned int Getbyte2(char *pa,char add);
long Getbyte4(char *pa,char add);
void Setbyte2(char *pa,char add,unsigned int value);
void Setbyte4(char *pa,char add,long value);


#endif  /*#ifndef __PUBLIC_H*/
