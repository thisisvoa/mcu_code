/*
 * hydrologyStack.h
 *
 *  Created on: 2017��8��21��
 *      Author: Administrator
 */

#ifndef HYDROLOGYSTACK_H_
#define HYDROLOGYSTACK_H_

#include "stm32f1xx_hal.h"
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
#define         RTU_TYPE_JS      'P'             //ң��վ������ ��ˮ
#define         RTU_TYPE_HD      'H'             //ң��վ������ �ӵ�
#define         RTU_TYPE_SK      'K'             //ң��վ������ ˮ�⣨������
#define         RTU_TYPE_ZB      'Z'             //ң��վ������ բ��
#define         RTU_TYPE_BZ      'D'             //ң��վ������ ��վ
#define         RTU_TYPE_CX      'T'             //ң��վ������ ��ϫ
#define         RTU_TYPE_SQ      'M'             //ң��վ������ ����
#define         RTU_TYPE_DXS     'G'             //ң��վ������ ����ˮ
#define         RTU_TYPE_SZ      'Q'             //ң��վ������ ˮ��
#define         RTU_TYPE_QSK     'I'             //ң��վ������ ȡˮ��
#define         RTU_TYPE_PSK     'O'             //ң��վ������ ��ˮ��
/****************************�����붨��***************************************/
#define         FUN_CODE_LLWC        0X2F            //��·ά�ֱ�
#define         FUN_CODE_CSB         0X30            //���Ա�
#define         FUN_CODE_JYSD        0X31            //����ʱ��ˮ����Ϣ��
#define         FUN_CODE_DSB         0X32            //ң��վ��ʱ��
#define         FUN_CODE_JBB         0X33            //ң��վ�ӱ���
#define         FUN_CODE_XSB         0X34            //ң��վСʱ��
#define         FUN_CODE_RGZS        0X35            //ң��վ�˹�������
#define         FUN_CODE_TPB         0X36            //ң��ͼƬ��������վ��ѯң��վͼƬ�ɼ���Ϣ
#define         FUN_CODE_CXSS        0X37            //����վ��ѯң��վʵʱ����
#define         FUN_CODE_CXSD        0X38            //����վ��ѯң��վʱ������
#define         FUN_CODE_CXRGZS      0X39            //����վ��ѯң��վ�˹�����
#define         FUN_CODE_CXZDYS      0X3A            //����վ��ѯң��ָ��Ҫ������
#define         FUN_CODE_XGJBPZ      0X40            //����վ�޸�ң��վ�������ñ�
#define         FUN_CODE_DQJBPZ      0X41            //����վ��ȡң��վ�������ñ�/ң��վ�Ա��������ñ�
#define         FUN_CODE_XGYXCS      0X42            //����վ�޸�ң�����в������ñ�
#define         FUN_CODE_DQYXCS      0X43            //����վ��ȡң�����в������ñ�/ң��վ�Ա����в������ñ�
#define         FUN_CODE_CXSBDJ      0X44            //��ѯˮ�õ��ʵʱ��������
#define         FUN_CODE_CXRJBB      0X45            //��ѯң���ն�����汾
#define         FUN_CODE_CXZTBJ      0X46            //��ѯң��վ״̬�ͱ�����Ϣ
#define         FUN_CODE_CSHSJ       0X47            //��ʼ����̬�洢����
#define         FUN_CODE_HFCCSZ      0X48            //�ָ��ն˻���������
#define         FUN_CODE_XGMM        0X49            //�޸�����
#define         FUN_CODE_SZSZ        0X4A            //����ң��վʱ��
#define         FUN_CODE_SWJB        0XE0            //�Զ��幦���� ˮλ�ӱ�
#define         FUN_CODE_XGPZ        0XE1            //�Զ��幦���� �޸��Զ�������
#define         FUN_CODE_DQPZ        0XE2            //�Զ��幦���� ��ȡ�Զ�������

#endif /* HYDROLOGYSTACK_H_ */
