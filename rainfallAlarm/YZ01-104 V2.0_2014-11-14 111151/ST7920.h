/*********************************************************
*�ļ����ƣ�ST7920.h
*ժ    Ҫ��ST7920�����ӿں�������
*
*��    �ߣ�����
*��ʼ���ڣ�2012��11��26��
*������ڣ�2012��11��27��
**********************************************************/

#ifndef __ST7920_H
#define __ST7920_H

#include "ST7920code.h"
#include "system.h"

/******************* I/O���� *********************************/
#define LCD_DataIn              P5DIR = 0X00          //���ݿڷ�������Ϊ����
#define LCD_DataOut             P5DIR = 0XFF          //���ݿڷ�������Ϊ���
#define LCD2MCU_Data            P5IN
#define MCU2LCD_Data            P5OUT
#define LCD_CMDOut              P4DIR |= BIT7|BIT6|BIT5|BIT4+BIT3;
#define LCD_CMIn                P4DIR &= ~(BIT7|BIT6|BIT5|BIT4|BIT3);
#define LCD_RS_H                P4OUT |= BIT5      
#define LCD_RS_L                P4OUT &= ~BIT5    
#define LCD_RW_H                P4OUT |= BIT6      
#define LCD_RW_L                P4OUT &= ~BIT6    
#define LCD_EN_H                P4OUT |= BIT7     
#define LCD_EN_L                P4OUT &= ~BIT7     
#define LCD_POWER_ON            P4DIR |= BIT3;P4OUT &= ~BIT3                  //LCD��Դ��
#define LCD_POWER_OFF           P4DIR |= BIT3;P4OUT |= BIT3                   //LCD��Դ��
#define LCD_LIGHT_ON            P4DIR |= BIT4;P4OUT &= ~BIT4                  //LCD���⿪
#define LCD_LIGHT_OFF           P4DIR |= BIT4;P4OUT |= BIT4                   //LCD�����
#define DISPLAYON               ST7920WriteCmd(0x36)            //��ʾ���ܿ�
#define DISPLAYOFF              ST7920WriteCmd(0x34)            //��ʾ���ܹ�

#define ST7920delayms(x)        delayms(x)                      //��ʱ����
#define ST7920delayus(x)        delayus(x)                      //��ʱ����


/*********************************** ���ܺ��� *********************************/
#define H_LINE(x,y,leng)        Draw(x,y,leng,1,0XFF,NULL)      //������
#define ClearScreen             Draw(0,0,16,64,0,0)             //���� 
#define ClearLine_0             Draw(0,0,16,16,0,0)             //�����0����ʾ 
#define ClearLine_1             Draw(0,16,16,16,0,0)            //�����1����ʾ 
#define ClearLine_2             Draw(0,32,16,16,0,0)            //�����2����ʾ 
#define ClearLine_3             Draw(0,48,16,16,0,0)            //�����3����ʾ 


/***************************** �������� ***************************************/
void ST7920WriteCmd(char cmd);
void ST7920WriteData(char dat);
void Coordinate(char H,char Ver,char *x,char *y);
void DisplayString(char H,char Ver,char *str,unsigned int DecimalPoint);
void Ini_Lcd(void);
void Draw(char H,char Ver,char Hleng,char Verleng,char wdata,const char *dat);
char TableNumber_8X6(char asc2);
void Display_8x6(char H,char Ver,char *s);
char  ST7920ReadData(void);
void DisplayNum(char H,char Ver,long int value,
                char type,char cmd,char *s,unsigned int fb);
void DisplayNum8X6(char H,char Ver,long int value,
                char type,char cmd,char *s);

void ST7920Test(void);

#endif /*#ifndef __ST7920_H*/