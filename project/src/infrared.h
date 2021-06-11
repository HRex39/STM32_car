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
	//init the Infra_Left
	GPIO_InitStructure.GPIO_Pin = Infra_Left;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init the Infra_front
	GPIO_InitStructure.GPIO_Pin = Infra_Front;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//init the Infra_right
	GPIO_InitStructure.GPIO_Pin = Infra_Right;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_Check_Infrared(uint16_t GPIO_Pin){
	if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
		GPIO_ResetBits(GPIOC, LED1);
	else
		GPIO_SetBits(GPIOC, LED1);
}

//Distance less than threshold return true, else return false 
bool Get_Infrared(uint16_t GPIO_Pin){
	if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
		return false;
	else
		return true;
}


#endif // INFRARED_H_INCLUDED
