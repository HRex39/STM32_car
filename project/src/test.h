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
    if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
    GPIO_ResetBits(GPIOC, LED1);
    else
        GPIO_SetBits(GPIOC, LED1);
    LED_Check_Infrared(Infra_Left);
		
    /****************Move Of Car****************/   
    Go_Forward();
    delay_ms(1000);
    Car_Stop();
    delay_ms(1000);
    Turn_Left();
    Car_Stop();
    delay_ms(1000);
    Turn_Right();
    Car_Stop();
    delay_ms(1000);
    Turn_Around();
    Car_Stop();
    delay_ms(1000);
}

#endif // TEST_H_INCLUDED