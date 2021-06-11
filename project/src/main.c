#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"
#include "motor.h"
#include "stdio.h"
#include "test.h"

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

/**
				README
										YSK 2021/6/11
(1)You can just use following code to run the car:
	Next two should  use with delay:
		Go_Forward();delay_ms(1000);
		Go_Back();delay_ms(1000);
	Others just easily use it:
		Car_Stop();
		Turn_Left();
		Turn_Right();
		Turn_Around();
(2)I move some test code to test() in test.h



**/

int main()
{
	System_Init();
	//for the loop
	while(1)
	{	
	//test();
	}
}
