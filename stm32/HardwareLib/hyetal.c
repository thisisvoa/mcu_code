/*
 * hyetal.c
 *
 *  Created on: 2017��9��21��
 *      Author: Administrator
 */
#include "hyetal.h"

rainGauge_t rainGauge;

uint32_t getRainFall(rainGauge_t *rainGauge){

	return ((rainGauge->rainFallCount * RAIN_GAUGE_RATIO) *10);
}

void clearRainFall(rainGauge_t *rainGauge){
	rainGauge->rainFallCount = 0;
	rainGauge->isRaining = 0;
}

/*
 * �����Ʒ�תһ�ε���һ��
 */
void call_from_rain_signal(rainGauge_t *rainGauge){
	rainGauge->isRaining = 1;
	rainGauge->rainFallCount++;
}


