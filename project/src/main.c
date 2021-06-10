#include "stm32f10x.h"

void LED1_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//init a structure of GPIO
	//open the GPIO_C's clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	//config the GPIO_C Pin12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//init GPIO_C
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
}

int main(){
	LED1_Init();
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	}
}
