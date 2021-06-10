#ifndef INFRARED_H_INCLUDED
#define INFRARED_H_INCLUDED
#include "stm32f10x.h"
#include "port.h"

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


#endif // INFRARED_H_INCLUDED
