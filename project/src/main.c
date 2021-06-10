#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"

/**
(1)Things about Delay:
	eg.. delay_ms(1000)
(2)Things about Infrared:
	IF GPIO_ReadInputDataBit == 0
	THEN there is the obstacle
	eg.. 
	if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
			GPIO_ResetBits(GPIOC, LED1);
	else
		GPIO_SetBits(GPIOC, LED1);
(3)Thing about Ultrasonic:

**/

int main(){
	System_Init();
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
			GPIO_ResetBits(GPIOC, LED1);
		else
			GPIO_SetBits(GPIOC, LED1);
	}
}
