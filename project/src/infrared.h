#ifndef INFRARED_H_INCLUDED
#define INFRARED_H_INCLUDED
#include "stm32f10x.h"
#include "port.h"
#include "stdbool.h"

void Infrared_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//init a structure of GPIO
	//config the GPIO_A
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//init the Front_Left
	GPIO_InitStructure.GPIO_Pin = Front_Left;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init the Front_Right
	GPIO_InitStructure.GPIO_Pin = Front_Right;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init the Rear_Left
	GPIO_InitStructure.GPIO_Pin = Rear_Left;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init the Rear_Right
	GPIO_InitStructure.GPIO_Pin = Rear_Right;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_Check_Infrared(uint16_t GPIO_Pin){
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin) == 0)
		GPIO_ResetBits(GPIOC, LED1);
	else
		GPIO_SetBits(GPIOC, LED1);
}

//Distance less than threshold return true, else return false 
bool Get_Infrared(uint16_t GPIO_Pin){
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin) == 0)
		return true;
	else
		return false;
}


#endif // INFRARED_H_INCLUDED
