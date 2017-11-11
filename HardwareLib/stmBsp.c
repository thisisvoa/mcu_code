/*
 * stmBsp.c
 *
 *  Created on: 2017��11��9��
 *      Author: Administrator
 */

#include "include.h"

void BSP_setPinDir(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint16_t Dir){
	 GPIO_InitTypeDef GPIO_InitStruct;

	 GPIO_InitStruct.Mode = Dir;
	 GPIO_InitStruct.Pin = GPIO_Pin;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;

	 HAL_GPIO_Init(GPIOx,&GPIO_InitStruct);
}

void BSP_delayUs(uint32_t num){
	uint32_t count=0;
	__HAL_TIM_SET_COUNTER(&htim2,0);

	HAL_TIM_Base_Start(&htim2);

	while(count < num){
		count = __HAL_TIM_GET_COUNTER(&htim2);
	}

	HAL_TIM_Base_Stop(&htim2);

}

//__HAL_TIM_SetCounter(&htim17, 0);//htim17
//
//__HAL_TIM_ENABLE(&htim17);
//
//while(__HAL_TIM_GetCounter(&htim17) < (36 * nus));//36��ϵͳʱ�ӣ�������������ˡ�
///* Disable the Peripheral */
//__HAL_TIM_DISABLE(&htim17);