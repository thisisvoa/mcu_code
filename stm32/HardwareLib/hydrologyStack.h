/*
 * hydrologyStack.h
 *
 *  Created on: 2017��8��21��
 *      Author: xiefei
 */

#ifndef HYDROLOGYSTACK_H_
#define HYDROLOGYSTACK_H_

#include "stm32f1xx_hal.h"
#include "include.h"

/**************************Э������**************************************/
#define MAX_ELEMENT_IN_MESSAGE  6
#define TX_BUF_LEN 255
/**************************�����ַ�����**************************************/
#define CT_SOH_ASCLL   0x01
#define CT_SOH_HEX_BCD 0x7EE
#define CT_STX         0x02
#define CT_SYN         0x16
#define CT_ETX         0x03
#define CT_ETB         0x17
#define CT_ENQ         0x05
#define CT_EOT         0x04
#define CT_ACK         0x06
#define CT_NAK         0x15
#define CT_ESC         0x1B4
/**************************ң��վ������***************************************/
#define RTU_TYPE_JS      'P'             //ң��վ������ ��ˮ
#define RTU_TYPE_HD      'H'             //ң��վ������ �ӵ�
#define RTU_TYPE_SK      'K'             //ң��վ������ ˮ�⣨������
#define RTU_TYPE_ZB      'Z'             //ң��վ������ բ��
#define RTU_TYPE_BZ      'D'             //ң��վ������ ��վ
#define RTU_TYPE_CX      'T'             //ң��վ������ ��ϫ
#define RTU_TYPE_SQ      'M'             //ң��վ������ ����
#define RTU_TYPE_DXS     'G'             //ң��վ������ ����ˮ
#define RTU_TYPE_SZ      'Q'             //ң��վ������ ˮ��
#define RTU_TYPE_QSK     'I'             //ң��վ������ ȡˮ��
#define RTU_TYPE_PSK     'O'             //ң��վ������ ��ˮ��
/****************************�����붨��***************************************/
#define FUN_CODE_LLWC        0X2F        //��·ά�ֱ�
#define FUN_CODE_CSB         0X30        //���Ա�
#define FUN_CODE_JYSD        0X31        //����ʱ��ˮ����Ϣ��
#define FUN_CODE_DSB         0X32        //ң��վ��ʱ��
#define FUN_CODE_JBB         0X33        //ң��վ�ӱ���
#define FUN_CODE_XSB         0X34        //ң��վСʱ��
#define FUN_CODE_RGZS        0X35        //ң��վ�˹�������
#define FUN_CODE_TPB         0X36        //ң��ͼƬ��������վ��ѯң��վͼƬ�ɼ���Ϣ
#define FUN_CODE_CXSS        0X37        //����վ��ѯң��վʵʱ����
#define FUN_CODE_CXSD        0X38        //����վ��ѯң��վʱ������
#define FUN_CODE_CXRGZS      0X39        //����վ��ѯң��վ�˹�����
#define FUN_CODE_CXZDYS      0X3A        //����վ��ѯң��ָ��Ҫ������
#define FUN_CODE_XGJBPZ      0X40        //����վ�޸�ң��վ�������ñ�
#define FUN_CODE_DQJBPZ      0X41        //����վ��ȡң��վ�������ñ�/ң��վ�Ա��������ñ�
#define FUN_CODE_XGYXCS      0X42        //����վ�޸�ң�����в������ñ�
#define FUN_CODE_DQYXCS      0X43        //����վ��ȡң�����в������ñ�/ң��վ�Ա����в������ñ�
#define FUN_CODE_CXSBDJ      0X44        //��ѯˮ�õ��ʵʱ��������
#define FUN_CODE_CXRJBB      0X45        //��ѯң���ն�����汾
#define FUN_CODE_CXZTBJ      0X46        //��ѯң��վ״̬�ͱ�����Ϣ
#define FUN_CODE_CSHSJ       0X47        //��ʼ����̬�洢����
#define FUN_CODE_HFCCSZ      0X48        //�ָ��ն˻���������
#define FUN_CODE_XGMM        0X49        //�޸�����
#define FUN_CODE_SZSZ        0X4A        //����ң��վʱ��
#define FUN_CODE_SWJB        0XE0        //�Զ��幦���� ˮλ�ӱ�
#define FUN_CODE_XGPZ        0XE1        //�Զ��幦���� �޸��Զ�������
#define FUN_CODE_DQPZ        0XE2        //�Զ��幦���� ��ȡ�Զ�������

/**************************Ҫ�ر�ʶ��**************************************/
#define ELEMENT_IDENT_NONE 0x00


/**************************Э������**************************************/
#define MESSAGE_TYPE_UP  '0'
#define MESSAGE_TYPE_DOW '8'

#define N(a,b) (uint8_t)( a << 4 | b)
#define GET_HIGH_4BIT(a) (a >> 4)
#define GET_LOW_4BIT(a)  (a & 0x0F)

/*Ҫ�ؽṹ*/
typedef struct
{
  uint8_t* elementIdentifier;        //Ҫ�ر�ʶ��
  float value;                        //Ҫ������ֵ
  uint8_t dataType;
}element_t;

typedef struct{
	element_t element[MAX_ELEMENT_IN_MESSAGE];
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;
}elementInf_t;

/*ʱ�����*/
typedef struct{
	uint8_t yearBCD;
	uint8_t monthBCD;
	uint8_t dayBCD;
	uint8_t hoursBCD;
	uint8_t minuteBCD;
	uint8_t secondBCD;
}sendTime_t;

typedef struct{
	float batteryVoltage;
}rtuStateInf_t;


/*���Ĳ���*/
typedef struct{
	uint16_t serialNum;
	elementInf_t elementInf;
	rtuStateInf_t rtu_state;
}messageInf_t;

typedef struct{
	uint8_t dataBuf[TX_BUF_LEN];
	uint16_t dataIdx;
}txBuf_t;

extern txBuf_t txDataBuf;
extern messageInf_t messageHandle;

uint16_t getLen_of_txBuf();

void clear_txBuf();
void clear_tail(uint16_t len);
void push_byte_to_txBuf(uint8_t num);
void push_short_to_txBuf(uint16_t num);
void push_int_to_txBuf(uint32_t num);
void push_float_to_txBuf(float num,uint8_t dataType);
void push_data_to_txBuf(uint8_t *srcData,uint16_t len);
uint8_t *get_addr_txBuf(void);
uint16_t getLen_of_txBuf(void);
void clear_element_from_message(messageInf_t *message,int8_t idx);

int8_t add_element(messageInf_t *message,const char* str, float value,uint8_t dataType);
void creat_msg(messageInf_t *message,  uint8_t funCode);

#endif /* HYDROLOGYSTACK_H_ */
