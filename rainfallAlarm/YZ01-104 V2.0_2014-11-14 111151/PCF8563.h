/***********************************************************************************/
//                       PCF8563.h With MSP430F149 Driver
//Version: 1.0.0
//Author:  LiHuaiLiang
//Email:   li-huai-liang@163.com
//Date:    2009-03-14
//Modify:  
//====================================================================================
//                       PCF8563.h With MSP430F149 Driver
//�汾: 1.0.0
//����:  ���
//Email:   li-huai-liang@163.com
//����:    2009-03-14
//�޸�:    ���� 2012-05-16
///***********************************************************************************/

#ifndef __PCF8563_H
#define __PCF8563_H

#include "MSP430_hardware.h"
#include "Public.h"


#define RTCIN           (P1IN & 0X04)

#define WRITE_ADDR      0xA2
#define READ_ADDR       0xA3

//PCF8563��ַ�궨��
#define year          	0x08
#define month         	0x07
#define day          	0x05
#define week          	0x06
#define hour         	0x04
#define minute       	0x03
#define second        	0x02

#define PCF8563delayus(x)       delayus(x)

///***********************************************************************************/
void PCF8563writeData(char address,char mdata);
//char PCF8563ReadData(char address); /*���ֽ�*/
//char PCF8563WriteData(char address,char *p,char count);
char PCF8563ReadDatas(char address,char  *p,char count);//���ֽ�


/*��ȡϵͳʱ��*/
char ReadTime(DataTime *t);
void SetTime(DataTime *t);
char PCF8563Ini(void);
//unsigned int TimeInterval(Time *t0,Time *t1);

#endif /*#ifndef __PCF8563_H*/