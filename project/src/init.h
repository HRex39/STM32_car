#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "stm32f10x.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"
#include "delay.h"

void LED_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//init a structure of GPIO
	//config the GPIO_C Pin12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//init LED1
	GPIO_InitStructure.GPIO_Pin = LED1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, LED1);
	//init LED2
	GPIO_InitStructure.GPIO_Pin = LED2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, LED2);
}

void System_Init()
{
	//open the GPIO_A GPIO_B GPIO_C clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	//set delay clock 
	delay_init(80);
	//init LED
	LED_Init();
	//init Infrared
	Infrared_Init();
	//init ultrasonic
	Ultra_Init();
	
}


#endif // INIT_H_INCLUDED
