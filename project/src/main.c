#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"


#include "stdio.h"

/**
				README
										HCR 2021/6/10
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
	RCC_APB1PeriphClockCmd: Enables or disables the Low Speed APB (APB1) peripheral clock
	RCC_APB2PeriphClockCmd: Enables or disables the High Speed APB (APB2) peripheral clock.

**/

int main()
{
	float length;
	
	System_Init();
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
			GPIO_ResetBits(GPIOC, LED1);
		else
			GPIO_SetBits(GPIOC, LED1);
		length = Hcsr04GetLength();
		if (length > 10)
			GPIO_ResetBits(GPIOC, LED2);
		else
			GPIO_SetBits(GPIOC, LED2);
	}
}
