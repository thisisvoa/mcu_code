/*
 * tinyRTu.h
 *
 *  Created on: 2017��11��2��
 *      Author: Administrator
 */

#ifndef TINYRTU_H_
#define TINYRTU_H_

#include "include.h"

#define TIME_COUNT_MINUTE  60
#define TIME_COUNT_5MINUTE 300
#define TIME_COUNT_HOUR    3600
#define TIME_COUNT_6HOUR   21600
#define TIME_COUNT_DAY     86400


/*
 * ͨ���¼�
 */
typedef enum {
	COMM_EVENT_NULL,
	COMM_SEND_MSG_HANG,

}commEvent_t;
/*
 * ʱ���¼�
 */
typedef enum {
	TIME_EVENT_NULL,
	TIME_EVENT_MINUTE,
	TIME_EVENT_5MINUTE,
	TIME_HOUR_HANG,
	TIME_6HOUR_HANG,
	TIME_DAY_HANG,
}timeEvent_t;

/*
 * �ɼ��¼�
 */
typedef enum {
	COLL_EVENT_NULL,
	COLL_RAINFAIL,
}collEvent_t;

typedef struct{
	commEvent_t commEvent;
	timeEvent_t timeEvent;
	collEvent_t collEvent;
}event_t;


#endif /* TINYRTU_H_ */
