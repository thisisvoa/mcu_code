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
 
#include ""
  
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

#define WriteUInt8(x,y)         Write_1Byte(x,y)                        //д��1byte����
#define ReadUInt8(x)            Read_1Byte_Randomaddress(x)             //��1byte����


unsigned char AT24C04TEST(unsigned char testadd);
unsigned char WriteUInt16(unsigned int num,unsigned char dataaddr);
unsigned int ReadUInt16(unsigned char addr);
unsigned char WriteSInt32(long num,unsigned char dataaddr);
signed long ReadSInt32(unsigned char addr);
unsigned char Write_1Byte(unsigned char wdata,unsigned char dataaddress);                        
unsigned char Write_NByte(unsigned char * outbuf,unsigned char n,unsigned char dataaddress);
unsigned char Read_1Byte_currentaddress(void);
unsigned char Read_NByte_currentaddress(unsigned char * readbuf,unsigned char n);
unsigned char Read_1Byte_Randomaddress(unsigned char dataaddress);
unsigned char Read_NByte_Randomaddress(unsigned char * readbuf,unsigned char n,unsigned char dataaddress);

#endif /* #ifndef __AT24C04_H */