/*********************************************************
*�ļ����ƣ�AT24C04.h
*ժ    Ҫ��AT24C04�����ļ�
*
*��ǰ�汾��1.0
*��    �ߣ�����
*��ʼ���ڣ�2012��5��17��
*������ڣ�
**********************************************************/

#ifndef __AT24C04_H
#define __AT24C04_H
 
#include "MSP430_hardware.h"
  
//I/O�ڶ���
#define SCL_H                   P1OUT |= BIT4
#define SCL_L                   P1OUT &= ~BIT4
#define SDA_H                   P1OUT |= BIT3
#define SDA_L                   P1OUT &= ~BIT3
#define SDA_in                  P1DIR &= ~BIT3        //SDA�ĳ�����ģʽ
#define SDA_out                 P1DIR |= BIT3         //SDA������ģʽ
#define SDA_val                 P1IN&BIT3             //SDA��λֵ
#define IniRAM                  P1DIR |= BIT3+BIT4; 
#define STOPRAM                 P1DIR &= ~(BIT4 +BIT3);//����I/OΪ����
#define deviceaddress           0xa0                  //AT24C02���豸��ַ

#define AT24C04delayus(x)       delayus(x)      //��ʱus
#define AT24C04delayms(x)       delayms(x)      //��ʱms

#define WriteUInt8(x,y,p)         Write_1Byte(x,y,p)                        //д��1byte����
#define ReadUInt8(x,y)            Read_1Byte_Randomaddress(x,y)             //��1byte����


char AT24C04TEST(char testadd);
char WriteUInt16(unsigned int num,char dataaddr,char page);
unsigned int ReadUInt16(char addr,char page);
char WriteSInt32(long num,char dataaddr,char page);
signed long ReadSInt32(char addr,char page);
char Write_1Byte(char wdata,char dataaddress,char page);                        
char Write_NByte(char * outbuf,char n,char dataaddress,char page);
char Read_1Byte_currentaddress(void);
char Read_NByte_currentaddress(char * readbuf,char n,char page);
char Read_1Byte_Randomaddress(char dataaddress,char page);
char Read_NByte_Randomaddress(char * readbuf,char n,char dataaddress,char page);
void WriteNByte(char *outbuf,char n,char dataaddress,char page);

#endif /* #ifndef __AT24C04_H */