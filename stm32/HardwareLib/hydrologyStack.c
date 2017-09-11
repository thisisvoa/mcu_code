/*
 * hydrologyStack.c
 *
 *  Created on: 2017��8��21��
 *      Author: xiefei
 */
#include "hydrologyStack.h"
#include "Public.h"

static messageInf_t         message;
static messageMainBody_t messageSubject;
static uint16_t          messageSerialNum=0;

/*
 * ��������е�Ҫ��
 * */
void clear_element_from_message(messageInf_t *message){
	memset((uint8_t)(message->elementInf),ELEMENT_IDENT_NONE,sizeof(message->elementInf));
}

int8_t add_element(messageInf_t *message, const uint8_t *str, float value,uint8_t dataType) {
	uint8_t i = 0;

	/*��ȡ��ǰʱ����Ϊ�۲�ʱ��*/
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);

	while ((message->elementInf.element[i].dataType == ELEMENT_IDENT_NONE)
			&& (i < MAX_ELEMENT_IN_MESSAGE)) {
		i++;
	}

	if (i == MAX_ELEMENT_IN_MESSAGE - 1) { //Ҫ������
		return -1;
	} else {
		message->elementInf.element[i].elementIdentifier = str; //Ҫ�ر�ʶ����һ���ַ�������
		message->elementInf.element[i].value = value;
		message->elementInf.element.dataType = dataType;
	}
}
void convert_short_to_ascll(uint16_t num, uint8_t *p){
	convert_byte_to_ascll(num >> 8,p++,p++);
	convert_byte_to_ascll((uint8_t)num ,p++,p++);
	sprintf(p,"%4d",num);
}

void convert_float_to_ascll(float num, uint8_t *p , uint8_t dataType){
	uint8_t z = dataType >> 8;
	uint8_t x = (uint8_t)dataType;
	sprintf(p,"%z.xf",num);
}

/*
 * ��ʱ��
 * */
void creat_timeAverage_message(messageInf_t *message,uint8_t *buf){
	uint8_t i = 0;

	/*
	 * ��ˮ�Ŵ���
	 * */
	message->serialNum++;
	sprintf(buf, "%4d", essage->serialNum);
	buf += 4;

	/*
	 * ����ʱ�䴦��
	 * */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	sprintf(buf, "%2d", message->elementInf.date.Year);
	sprintf(buf, "%2d", message->elementInf.date.Month);
	sprintf(buf, "%2d", message->elementInf.date.Date);
	sprintf(buf, "%2d", message->elementInf.time.Hours);
	sprintf(buf, "%2d", message->elementInf.time.Minutes);
	buf += 10;

	/*
	 *
	 * */

}

/*
 * ά�ֱ�
 * */
void creat_keep_message(messageInf_t *message,uint8_t *buf){

}
/*
 * ��ʱ��
 * */
void creat_timing_mesage(messageInf_t *message,uint8_t *buf){

}
/*
 * Сʱ��
 * */
void creat_hour_mesage(messageInf_t *message,uint8_t *buf){

}
/*
 * �ӱ�
 * */
void creat_extra_mesage(messageInf_t *message,uint8_t *buf){

}
/*
 * �˹���
 * */
void creat_manMade_message(messageInf_t *message,uint8_t *buf){

}


/*
 * ���ɱ�������
 * */
void create_message_subject(messageMainBody_t * messageSubject) {
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	/*��ˮ��*/
	messageSubject->serialNumH = (messageSerialNum & 0xFF00) >> 8;
	messageSubject->serialNumH = (messageSerialNum & 0x00FF);
	messageSerialNum++;

	/*����ʱ��*/
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BCD);
	messageSubject->sendTime.yearBCD = date.Year;    //YY
	messageSubject->sendTime.minuteBCD = date.Month; //MM
	messageSubject->sendTime.dayBCD = date.Date;     //DD
	messageSubject->sendTime.hoursBCD = time.Hours;   //HH
	messageSubject->sendTime.minuteBCD = time.Minutes;   //mm
	messageSubject->sendTime.secondBCD = time.Seconds;   //ss

	/*��ַ��ʶ�� TODO ��ʶ���Ƕ��٣�*/
	messageSubject->identifierAddr = 0;
	/*ң��վ��ַ*/
	messageSubject->RtuStationAddr[0] = 0;
	messageSubject->RtuStationAddr[1] = (rtuParameter.upDataArg.RtuStationAddr & 0xFF000000) >> 24;
	messageSubject->RtuStationAddr[2] = (rtuParameter.upDataArg.RtuStationAddr & 0x00FF0000) >> 16;
	messageSubject->RtuStationAddr[3] = (rtuParameter.upDataArg.RtuStationAddr & 0x0000FF00) >> 8;
	messageSubject->RtuStationAddr[5] = (rtuParameter.upDataArg.RtuStationAddr & 0x000000FF);

	/*ң��վ������*/
	messageSubject->RtuType = rtuParameter.upDataArg.rtu_type;
	/*���Ҫ��*/
	clear_element_from_message(messageSubject);
}




/*
 * �ϵ����ã���ʼ�������еĳ���
 * */
void init_msg_prg(messageInf_t *message ,messageMainBody_t *messageSubject){
	message->frameStartChar = CT_SOH_ASCLL;
	message->centreStationAddr = rtuParameter.upDataArg.centreStationAddr;

	message->RtuStationAddr[0]= 0;
	message->RtuStationAddr[1]= (rtuParameter.upDataArg.RtuStationAddr & 0xFF000000)>>24;
	message->RtuStationAddr[2]= (rtuParameter.upDataArg.RtuStationAddr & 0x00FF0000)>>16;
	message->RtuStationAddr[3]= (rtuParameter.upDataArg.RtuStationAddr & 0x0000FF00)>>8;
	message->RtuStationAddr[4]= (rtuParameter.upDataArg.RtuStationAddr & 0x000000FF);

	message->pswH= (rtuParameter.upDataArg.password & 0xff00)>>8;
	message->pswL= (rtuParameter.upDataArg.password & 0x00ff);

	message->identifierAndLen = (messageInf_tYPE_DOW << 15);
	message->identifierAndLen |= sizeof (messageMainBody_t);

	message->messageStartChar = CT_STX;
	message->messageMainBody = messageSubject;
	message->messageStopChar = CT_ETX;
}
/*
 *������ת��ascll�������뷢�ͻ�������
 * */
void convert_message_ascll(messageInf_t *message,uint8_t *txBuf){
	uint8_t i=0;

	txBuf[i++] = message->frameStartChar;//����Ҫת��

	convert_byte_to_ascll(message->centreStationAddr,(txBuf + i)++,(txBuf + i)++);

	convert_byte_to_ascll(message->RtuStationAddr[0],(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->RtuStationAddr[1],(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->RtuStationAddr[2],(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->RtuStationAddr[3],(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->RtuStationAddr[4],(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->pswH ,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->pswL ,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->funCode,(txBuf + i)++,(txBuf + i)++);

	convert_byte_to_ascll(message->identifierAndLen >> 8,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll((uint8_t)(message->identifierAndLen),(txBuf + i)++,(txBuf + i)++);
	txBuf[i++] =message ->messageStartChar;//����Ҫת��
	/****************�������Ĳ���***********************/
	convert_byte_to_ascll(message->messageMainBody->serialNumH,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->serialNumL,(txBuf + i)++,(txBuf + i)++);

	convert_byte_to_ascll(message->messageMainBody->sendTime.yearBCD,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->sendTime.monthBCD,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->sendTime.dayBCD,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->sendTime.hoursBCD,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->sendTime.minuteBCD,(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll(message->messageMainBody->sendTime.secondBCD,(txBuf + i)++,(txBuf + i)++);
	txBuf[i++]='S';
	txBuf[i++]='T';

	txBuf[i++]=' ';
	convert_byte_to_ascll(message->messageMainBody->identifierAddr,(txBuf + i)++,(txBuf + i)++);
	/****************�������Ĳ���END***********************/

	txBuf[i++] =message ->messageStopChar;//����Ҫת��
	convert_byte_to_ascll((message->crc >> 8),(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll((uint8_t)(message->crc),(txBuf + i)++,(txBuf + i)++);
}

void send_messag(void){

}

