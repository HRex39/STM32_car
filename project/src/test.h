#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"
#include "motor.h"
#include "stdio.h"

void test(){
    /****************UltraSonic****************/
    float length;
	length = Hcsr04GetLength();
    if (length > 10)
        GPIO_ResetBits(GPIOC, LED2);
    else
        GPIO_SetBits(GPIOC, LED2);	
            
            
    /****************Infrared****************/     
    if (GPIO_ReadInputDataBit(GPIOA, Front_Left) == 0)
    GPIO_ResetBits(GPIOC, LED1);
    else
        GPIO_SetBits(GPIOC, LED1);
    LED_Check_Infrared(Front_Left);
		
    /****************Move Of Car****************/   
    Go_Forward();
    delay_ms(1000);
    Car_Stop();
    delay_ms(1000);
    Turn_Left(450);
    Car_Stop();
    delay_ms(1000);
    Turn_Right(450);
    Car_Stop();
    delay_ms(1000);
    Turn_Around(800);
    Car_Stop();
    delay_ms(1000);
}

void Dir_test(char car_dir)
{
	switch(car_dir)
	{
		case 'u': GPIO_SetBits(GPIOC, LED1);GPIO_SetBits(GPIOC, LED2); break;
		case 'l': GPIO_SetBits(GPIOC, LED1);GPIO_ResetBits(GPIOC, LED2); break;
		case 'r': GPIO_ResetBits(GPIOC, LED1);GPIO_SetBits(GPIOC, LED2); break;
		case 'd': GPIO_ResetBits(GPIOC, LED1);GPIO_ResetBits(GPIOC, LED2); break;
	}

}

void Ultrasonic_test(int threshold)
{
	if(Hcsr04GetLength() < threshold) { GPIO_ResetBits(GPIOC, LED1);GPIO_ResetBits(GPIOC, LED2);}
	else  { GPIO_SetBits(GPIOC, LED1);GPIO_SetBits(GPIOC, LED2);}
}

#endif // TEST_H_INCLUDED
