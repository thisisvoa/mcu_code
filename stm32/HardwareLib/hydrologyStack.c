/*
 * hydrologyStack.c
 *
 *  Created on: 2017��8��21��
 *      Author: xiefei
 */
#include "include.h"
/*
 * ��������е�Ҫ��
 * idx����Ҫ�����Ҫ�ص�С�꣬Ϊ������ȫ�����㣻
 */
void clear_element_from_message(messageInf_t *message,int8_t idx){
	uint8_t i;

	if(idx<0){
		for(i=0;i<MAX_ELEMENT_IN_MESSAGE;i++){
			message->elementInf.element[i].dataType=ELEMENT_IDENT_NONE;
			message->elementInf.element[i].value=0;
			message->elementInf.element[i].elementIdentifier=NULL;
		}
	}
	else{
		message->elementInf.element[idx].dataType=ELEMENT_IDENT_NONE;
		message->elementInf.element[idx].value=0;
		message->elementInf.element[idx].elementIdentifier=NULL;
	}
}

int8_t add_element(messageInf_t *message,  uint8_t *str, float value,uint8_t dataType) {
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
		message->elementInf.element[i].dataType = dataType;
	}

	return 0;
}

/*
 * ���ɱ������ĵĹ������ֵ�����buf
 * */
static char* creat_public_message(messageInf_t *message,char *buf){
	uint8_t i;
	/*
	 * ��ˮ�Ŵ���
	 */
	message->serialNum++;
	sprintf(buf, "%4d", message->serialNum);
	buf += 4;

	/*
	 * ����ʱ�䴦��
	 */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	sprintf(buf, "%2d", message->elementInf.date.Year);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.date.Month);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.date.Date);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Hours);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Minutes);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Seconds);
	buf += 2;

	/*
	 * ��ַ��ʶ��
	 */
	*buf++ = 'S';
	*buf++ = 'T';

	/*
	 * ��վ��ַ
	 */
	for(i=0;i<sizeof(message->RtuStationAddr);i++){
		sprintf(buf,"%2d",message->RtuStationAddr[0]);
		buf+=2;
	}

	/*
	 * ң��վ������
	 */
	sprintf(buf, "%2d", rtuParameter.upDataArg.rtuType);
	buf += 2;

	/*
	 * �۲�ʱ���ʶ��
	 */
	*buf++ ='T';
	*buf++ ='T';

	/*
	 *�۲�ʱ��
	 */
	sprintf(buf,"%2d",message->elementInf.date.Year);
	buf += 2;
	sprintf(buf,"%2d",message->elementInf.date.Month);
	buf += 2;
	sprintf(buf,"%2d",message->elementInf.date.Date);
	buf += 2;
	sprintf(buf,"%2d",message->elementInf.time.Hours);
	buf += 2;
	sprintf(buf,"%2d",message->elementInf.time.Minutes);
	buf += 2;

	return buf;
}

/*
 * ���Ҫ�ص�����buf
 */
static char* creat_element_message(messageInf_t *message, char *buf) {
	uint8_t i=0;
	uint8_t str[] = {"%3.4f"};

	while (message->elementInf.element[i].dataType != ELEMENT_IDENT_NONE) {
		/*���Ʊ�ʶ����Ϣ*/
		while (*(message->elementInf.element[i].elementIdentifier)++) {
			*buf++ = *(message->elementInf.element[i].elementIdentifier);
		}

		/*
		 * ��������
		 */
		str[1] = GET_HIGH_4BIT(message->elementInf.element[i].dataType) + '0';//ת���ַ�
		str[3] = GET_LOW_4BIT(message->elementInf.element[i].dataType) + '0';
		sprintf(buf, (const char*) str, (message->elementInf.element[i].value));
		buf += (str[1] + str[3] + 1 - '0' - '0');//�����ܹ�ռ�õĳ���

		i++;
	}
	return buf;
}

/*
 * ��ʱ��
 * */
void creat_timeAverage_message(messageInf_t *message,char *buf){
	/*
	 * ���ӹ�������
	 */
	buf=creat_public_message(message,buf);

	/*
	 * ʱ�䲽��
	 */
	*buf++ ='D';
	*buf++ ='R';
	*buf++ ='D';
	if(rtuParameter.upDataArg.timeAverageInterval <60){        //����
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval);
	}
	else if(rtuParameter.upDataArg.timeAverageInterval>=1440){ //��
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval / 1440 );
	}
	else{                                                      //Сʱ
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval / 60 );
	}
	buf +=2;

	/*
	 * Ҫ�ر�ʶ��������
	 */
	buf=creat_element_message(message,buf);
}

/*
 * ά�ֱ�
 * */
void creat_keep_message(messageInf_t *message, char *buf) {

	/*
	 * ��ˮ�Ŵ���
	 */
	message->serialNum++;
	sprintf(buf, "%4d", message->serialNum);
	buf += 4;

	/*
	 * ����ʱ�䴦��
	 */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	sprintf(buf, "%2d", message->elementInf.date.Year);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.date.Month);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.date.Date);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Hours);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Minutes);
	buf += 2;
	sprintf(buf, "%2d", message->elementInf.time.Seconds);
	buf += 2;
}

/*
 * ��ʱ��
 * */
void creat_timing_mesage(messageInf_t *message,char *buf){
	/*
	 * ���ӹ�������
	 */
	buf=creat_public_message(message,buf);

	/*
	 * ��ʱ�����
	 */
	*buf++ ='D';
	*buf++ ='R';
	*buf++ ='D';
	if(rtuParameter.upDataArg.timeAverageInterval <60){        //����
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval);
	}
	else if(rtuParameter.upDataArg.timeAverageInterval>=1440){ //��
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval / 1440 );
	}
	else{                                                      //Сʱ
		sprintf(buf,"%2d",rtuParameter.upDataArg.timeAverageInterval / 60 );
	}
	buf +=2;

	/*
	 * Ҫ�ر�ʶ��������
	 */
	buf=creat_element_message(message,buf);

	/*
	 * ��ӵ�ѹ��Ϣ
	 */
	*buf++ = 'V';
	*buf++ = 'T';
	sprintf(buf,"%2.2f",rtuStateInf.batteryVoltage);
	buf += 5;
}
/*
 * Сʱ��
 * */
void creat_hour_mesage(messageInf_t *message,char *buf){
	/*
	 * ���ӹ�������
	 */
	buf=creat_public_message(message,buf);
}
/*
 * �ӱ�
 * */
void creat_extra_mesage(messageInf_t *message,uint8_t *buf){
	/*���ӹ�������*/
	buf=creat_public_message(message,buf);

	/*
	 * ����Ҫ��
	 */

	/*
	 * ��ӵ�ѹ��Ϣ
	 */
	*buf++ = 'V';
	*buf++ = 'T';
	sprintf(buf,"%2.2f",rtuStateInf.batteryVoltage);
	buf += 5;
}
/*
 * �˹���
 * */
void creat_manMade_message(messageInf_t *message,uint8_t *buf){

}


/*

 * ���ɱ�������
 *
void create_message_subject(messageMainBody_t * messageSubject) {
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	��ˮ��
	messageSubject->serialNumH = (messageSerialNum & 0xFF00) >> 8;
	messageSubject->serialNumH = (messageSerialNum & 0x00FF);
	messageSerialNum++;

	����ʱ��
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BCD);
	messageSubject->sendTime.yearBCD = date.Year;    //YY
	messageSubject->sendTime.minuteBCD = date.Month; //MM
	messageSubject->sendTime.dayBCD = date.Date;     //DD
	messageSubject->sendTime.hoursBCD = time.Hours;   //HH
	messageSubject->sendTime.minuteBCD = time.Minutes;   //mm
	messageSubject->sendTime.secondBCD = time.Seconds;   //ss

	��ַ��ʶ�� TODO ��ʶ���Ƕ��٣�
	messageSubject->identifierAddr = 0;
	ң��վ��ַ
	messageSubject->RtuStationAddr[0] = 0;
	messageSubject->RtuStationAddr[1] = (rtuParameter.upDataArg.RtuStationAddr & 0xFF000000) >> 24;
	messageSubject->RtuStationAddr[2] = (rtuParameter.upDataArg.RtuStationAddr & 0x00FF0000) >> 16;
	messageSubject->RtuStationAddr[3] = (rtuParameter.upDataArg.RtuStationAddr & 0x0000FF00) >> 8;
	messageSubject->RtuStationAddr[5] = (rtuParameter.upDataArg.RtuStationAddr & 0x000000FF);

	ң��վ������
	messageSubject->RtuType = rtuParameter.upDataArg.rtu_type;
	���Ҫ��
	clear_element_from_message(messageSubject);
}





 * �ϵ����ã���ʼ�������еĳ���
 *
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

 *������ת��ascll�������뷢�ͻ�������
 *
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
	***************�������Ĳ���**********************
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
	***************�������Ĳ���END**********************

	txBuf[i++] =message ->messageStopChar;//����Ҫת��
	convert_byte_to_ascll((message->crc >> 8),(txBuf + i)++,(txBuf + i)++);
	convert_byte_to_ascll((uint8_t)(message->crc),(txBuf + i)++,(txBuf + i)++);
}

void send_messag(void){

}

*/
