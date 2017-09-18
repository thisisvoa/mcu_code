/*
 * hydrologyStack.c
 *
 *  Created on: 2017��8��21��
 *      Author: xiefei
 */
#include "include.h"

txBuf_t       txDataBuf;
messageInf_t  messageHandle;

uint16_t getLen_of_txBuf(void){
	return (txDataBuf.dataIdx + 1);
}

uint8_t *get_addr_txBuf(void){
	return (uint8_t*)(txDataBuf.dataBuf);
}

void clear_txBuf(void){
	memset(txDataBuf.dataBuf,0,TX_BUF_LEN);
	txDataBuf.dataIdx = 0;
}

void clear_tail(uint16_t len){
	txDataBuf.dataIdx -= len;
}

void push_char_to_txBuf(uint8_t ch){
	txDataBuf.dataBuf[txDataBuf.dataIdx] = ch;
	txDataBuf.dataIdx++;
}

void push_integer_to_txBuf(uint32_t num , uint8_t dataType){
	uint8_t str[]={"%0ald"};

	str[2] = GET_HIGH_4BIT(dataType) + '0';

	sprintf((char*)(txDataBuf.dataBuf  + txDataBuf.dataIdx),(const char*)str,num);
	txDataBuf.dataIdx += GET_HIGH_4BIT(dataType);
}

void push_float_to_txBuf(float num,uint8_t dataType){
	uint8_t str[]={"%a.bf"};

	str[1] = GET_HIGH_4BIT(dataType) + '0';
	str[3] = GET_LOW_4BIT(dataType) +  '0';
	sprintf((char*)(txDataBuf.dataBuf  + txDataBuf.dataIdx),(const char *)str,num);
	txDataBuf.dataIdx += (GET_HIGH_4BIT(dataType) +  GET_LOW_4BIT(dataType) + 1);
}

void push_data_to_txBuf(uint8_t *srcData,uint16_t len){
	uint8_t i;

	for(i=0;i<len;i++){
		txDataBuf.dataBuf[txDataBuf.dataIdx] = srcData[i];
		txDataBuf.dataIdx++;
	}
}
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

int8_t add_element(messageInf_t *message,const char* str, float value,uint8_t dataType) {
	uint8_t i = 0;

	/*��ȡ��ǰʱ����Ϊ�۲�ʱ��*/
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);

	while ((message->elementInf.element[i].dataType != ELEMENT_IDENT_NONE) && (i < MAX_ELEMENT_IN_MESSAGE)) {
		i++;
	}

	if (i > MAX_ELEMENT_IN_MESSAGE -1 ) { //Ҫ������
		return -1;
	} else {
		message->elementInf.element[i].elementIdentifier = (uint8_t*)str; //Ҫ�ر�ʶ����һ���ַ�������
		message->elementInf.element[i].value = value;
		message->elementInf.element[i].dataType = dataType;
	}
	return 0;
}

/*
 * ���ɱ������ĵĹ������ֵ�����buf
 * */
static void creat_public_message(messageInf_t *message){
	uint8_t i;
	/*
	 * ��ˮ�Ŵ���
	 */
	push_integer_to_txBuf(message->serialNum++,N(4,0));

	/*
	 * ����ʱ�䴦��
	 */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	push_integer_to_txBuf(message->elementInf.date.Year,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Month,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Date,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Hours,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Minutes,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Seconds,N(2,0));

	/*
	 * ��ַ��ʶ��
	 */
	push_char_to_txBuf('S');
	push_char_to_txBuf('T');
	push_char_to_txBuf(' ');

	/*
	 * ��վ��ַ
	 */
	for(i=0;i<sizeof(rtuParameter.upDataArg.RtuStationAddr);i++){
		push_integer_to_txBuf(rtuParameter.upDataArg.RtuStationAddr[i],N(2,0));
	}
	push_char_to_txBuf(' ');

	/*
	 * ң��վ������
	 */
	push_char_to_txBuf(rtuParameter.upDataArg.rtuType);
	push_char_to_txBuf(' ');

	/*
	 * �۲�ʱ���ʶ��
	 */
	push_char_to_txBuf('T');
	push_char_to_txBuf('T');
	push_char_to_txBuf(' ');

	/*
	 *�۲�ʱ��
	 */
	push_integer_to_txBuf( message->elementInf.date.Year,N(2,0));
	push_integer_to_txBuf( message->elementInf.date.Month,N(2,0));
	push_integer_to_txBuf( message->elementInf.date.Date,N(2,0));
	push_integer_to_txBuf( message->elementInf.time.Hours,N(2,0));
	push_integer_to_txBuf( message->elementInf.time.Minutes,N(2,0));
	push_char_to_txBuf(' ');

}

/*
 * ���Ҫ�ص�����buf
 */
static void creat_element_message(messageInf_t *message) {
	uint8_t i=0;
	uint8_t j=0;

	while (message->elementInf.element[i].dataType != ELEMENT_IDENT_NONE) {

		/*���Ʊ�ʶ����Ϣ*/
		while(message->elementInf.element[i].elementIdentifier[j]){
			push_char_to_txBuf(message->elementInf.element[i].elementIdentifier[j]);
			j++;
		}
		push_char_to_txBuf(' ');

		/*
		 * ��������
		 */
		push_float_to_txBuf(message->elementInf.element[i].value,
				message->elementInf.element[i].dataType);
		push_char_to_txBuf(' ');

		i++;
	}
}

/*
 * ��ʱ��
 * */
static uint16_t creat_timeAverage_message(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();
	/*
	 * ���ӹ�������
	 */
	creat_public_message(message);

	/*
	 * ʱ�䲽��
	 */
	push_char_to_txBuf('D');
	push_char_to_txBuf('R');

	if (rtuParameter.upDataArg.timeAverageInterval < 60) {        //����
		push_char_to_txBuf('N');
		push_char_to_txBuf(' ');
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval,N(2,0));
	} else if (rtuParameter.upDataArg.timeAverageInterval >= 1440) { //��
		push_char_to_txBuf('D');
		push_char_to_txBuf(' ');
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval / 1440 ,N(2,0));

	} else {
		push_char_to_txBuf('H');
		push_char_to_txBuf(' ');
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval / 60,N(2,0));
	}
	push_char_to_txBuf(' ');

	/*
	 * Ҫ�ر�ʶ��������
	 */
	creat_element_message(message);

	return getLen_of_txBuf() - lenBefor;
}

/*
 * ά�ֱ�
 * */
static uint16_t creat_keep_message(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();

	/*
	 * ��ˮ�Ŵ���
	 */
	push_integer_to_txBuf(message->serialNum++,N(4,0));
	push_char_to_txBuf(' ');

	/*
	 * ����ʱ�䴦��
	 */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	push_integer_to_txBuf(message->elementInf.date.Year,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Month,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Date,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Hours,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Minutes,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Seconds,N(2,0));
	push_char_to_txBuf(' ');

	return getLen_of_txBuf() - lenBefor;
}

/*
 * ��ʱ��
 * */
static uint16_t creat_timing_mesage(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();

	/*
	 * ���ӹ�������
	 */
	creat_public_message(message);

	/*
	 * ��ʱ�����
	 */
	push_char_to_txBuf('D');
	push_char_to_txBuf('R');


	if (rtuParameter.upDataArg.timeAverageInterval < 60) {        //����
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval,N(2,0));
		push_char_to_txBuf('N');
		push_char_to_txBuf(' ');
	} else if (rtuParameter.upDataArg.timeAverageInterval >= 1440) { //��
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval / 1440,N(2,0));
		push_char_to_txBuf('D');
		push_char_to_txBuf(' ');
	} else {                                                      //Сʱ
		push_integer_to_txBuf(rtuParameter.upDataArg.timeAverageInterval / 60,N(2,0));
		push_char_to_txBuf('H');
		push_char_to_txBuf(' ');
	}

	/*Ҫ�ر�ʶ��������*/
	creat_element_message(message);
	push_char_to_txBuf(' ');

	/*��ӵ�ѹ��Ϣ*/
	push_char_to_txBuf('V');
	push_char_to_txBuf('T');
	push_char_to_txBuf(' ');
	push_float_to_txBuf(message->rtu_state.batteryVoltage, N(2, 2));
	push_char_to_txBuf(' ');
	return getLen_of_txBuf() - lenBefor;
}
/*
 * Сʱ��
 * */
static uint16_t creat_hour_mesage(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();

	/*���ӹ�������*/
	creat_public_message(message);

	/*Ҫ��: 1h��ÿ5minʱ�ν�ˮ������ˮ���ۼ�ֵ��1h��ÿ5minʱ�μ�����ˮλ*/
	creat_element_message(message);

	/*
	 * ��ӵ�ѹ��Ϣ
	 */
	push_char_to_txBuf('V');
	push_char_to_txBuf('T');
	push_char_to_txBuf(' ');
	push_float_to_txBuf(message->rtu_state.batteryVoltage,N(2, 2));
	push_char_to_txBuf(' ');

	return getLen_of_txBuf() - lenBefor;
}

/*
 * �ӱ�
 * */
static uint16_t creat_extra_mesage(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();

	/*���ӹ�������*/
	creat_public_message(message);

	/* ����Ҫ�� */
	creat_element_message(message);

	/*
	 * ��ӵ�ѹ��Ϣ
	 */
	push_char_to_txBuf('V');
	push_char_to_txBuf('T');
	push_char_to_txBuf(' ');
	push_float_to_txBuf(message->rtu_state.batteryVoltage, N(2,2));
	push_char_to_txBuf(' ');

	return getLen_of_txBuf() - lenBefor;
}


/*
 * �˹���
 * */
static uint16_t creat_manMade_message(messageInf_t *message) {
	uint16_t lenBefor = getLen_of_txBuf();

	push_integer_to_txBuf(message->serialNum++,N(2,0));

	/*
	 * ����ʱ�䴦��
	 */
	HAL_RTC_GetTime(&hrtc, &(message->elementInf.time), RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &(message->elementInf.date), RTC_FORMAT_BCD);
	push_integer_to_txBuf(message->elementInf.date.Year,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Month,N(2,0));
	push_integer_to_txBuf(message->elementInf.date.Date,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Hours,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Minutes,N(2,0));
	push_integer_to_txBuf(message->elementInf.time.Seconds,N(2,0));
	push_char_to_txBuf(' ');

	/*
	 * �˹�������ʶ�����˹�������
	 */
	//TODO �ȴ�����
	return getLen_of_txBuf() - lenBefor;
}

/*
 * ���ô˺�������ˮ������֡
 * ����funCode����֡������
 *
 * */
void creat_msg(messageInf_t *message,  uint8_t funCode) {
	uint8_t i = 0;
	uint16_t len=0;

	clear_txBuf();

	/* ֡��ʼ��*/
	push_char_to_txBuf(CT_SOH_ASCLL);

	/*����վ��ַ*/
	push_integer_to_txBuf(rtuParameter.upDataArg.centreStationAddr,N(2,0));

	/*
	 * ��վ��ַ
	 */
	for (i = 0; i < sizeof(rtuParameter.upDataArg.RtuStationAddr); i++) {
		push_integer_to_txBuf(rtuParameter.upDataArg.RtuStationAddr[i],N(2,0));
	}

	/*����*/
	push_integer_to_txBuf(rtuParameter.upDataArg.passWord,N(4,0));

	/*������*/
	push_integer_to_txBuf(funCode,N(2,0));

	/*�����б�ʶ��*/
	push_char_to_txBuf(MESSAGE_TYPE_UP);

	switch (funCode) {
	/*
	 * ��ʱ��
	 */
	case FUN_CODE_JYSD:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_timeAverage_message(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_timeAverage_message(message);
		break;

		/*
		 * Сʱ��
		 * */
	case FUN_CODE_XSB:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_hour_mesage(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_hour_mesage(message);
		break;

		/*
		 * ��ʱ��
		 * */
	case FUN_CODE_DSB:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_timing_mesage(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_timing_mesage(message);
		break;

		/*
		 * ��·ά�ֱ�
		 */
	case FUN_CODE_LLWC:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_keep_message(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_keep_message(message);
		break;

		/*
		 * �ӱ�
		 */
	case FUN_CODE_JBB:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_extra_mesage(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_extra_mesage(message);
		break;

		/*
		 * �˹�������
		 */
	case FUN_CODE_RGZS:
		/*
		 * �ȼƵõ����ĳ���
		 * ��ӳ��ȱ�ʶ
		 */
		len = creat_manMade_message(message);
		clear_tail(len);
		push_integer_to_txBuf(len, N(3, 0));

		/*������ʼ��*/
		push_char_to_txBuf(CT_STX);

		/*�������*/
		creat_manMade_message(message);
		break;

	default:
		break;
	}

	/*���Ľ�����*/
	push_char_to_txBuf(CT_ETX);

	/*��У��*/
	push_integer_to_txBuf(CRC16(get_addr_txBuf(),getLen_of_txBuf()) ,N(4,0));
}
