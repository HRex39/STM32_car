#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED
#include "stm32f10x.h"
#include "port.h"

#define vertifyTime 50
#define speed 4000

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
{  
	RCC->APB1ENR|=1<<1; //TIM3时钟使能	 PA6是TIM3的通道1，PA7是TIM3的通道2、PB0是TIM3的通道3、PB1是TIM3的通道4
	GPIOA->CRL&=0X00FFFFFF;//PA6,PA7输出
	GPIOA->CRL|=0XBB000000;//复用功能输出
	GPIOA->ODR|=1<<6|1<<7;//PA6,PA7上拉
	GPIOB->CRL&=0XFFFFFF00;//PB0,PB1输出
	GPIOB->CRL|=0X000000BB;//复用功能输出
	GPIOB->ODR|=1<<0|1<<1;//PB0,PB1上拉

	TIM3->ARR=arr;//设定计数器自动重装值    
	TIM3->PSC=psc;//预分频器不分频
	TIM3->CCER|=1<<1|1<<5|1<<9|1<<13;	 //CH1、CH2、CH3、CH4高电平有效
	TIM3->CCMR1|=7<<12|7<<4; //CH1、CH2 PWM2模式    定时器3通道1、2
	TIM3->CCMR1|=1<<11|1<<3; //TIM3 CH1、CH2预装载使能
	TIM3->CCMR2|=7<<12|7<<4; //CH3、CH4 PWM2模式    定时器3通道3、4
	TIM3->CCMR2|=1<<11|1<<3; //TIM3 CH1、CH2预装载使能
	TIM3->CCER|=1<<12|1<<8|1<<4|1<<0; //TIM3 OC1、OC2、OC3、OC4输出使能
	TIM3->CR1=0x0080; //ARPE使能  	
	TIM3->CR1|=1<<4;	//向下计数模式 
	TIM3->EGR |= 1<<0; //初始化所有的寄存器更新事件发生
	TIM3->CR1|=0x01; //使能定时器3
}

// 1-left wheel forward     2-left wheel backword
// 3-right wheel forward    4-right wheel backward
void Go_Forward()
{
	TIM3->CCR1 = speed-2000;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = 0;	
}

void Go_Little_Forward()
{
	TIM3->CCR1 = 3000-2000;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 3000;
	TIM3->CCR4 = 0;	
}

void Go_Back()
{
	TIM3->CCR1 = 0;
	TIM3->CCR2 = speed-2000;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = speed;	
}

void Car_Stop(){
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
}

void Turn_Right(int ms){
	TIM3->CCR1 = 0;
	TIM3->CCR2 = speed-2000;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = 0;
	delay_ms(ms);
}

void Turn_Left(int ms){
	TIM3->CCR1 = speed-2000;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = speed;
	delay_ms(ms);
}

void Turn_Around(int ms){
	TIM3->CCR1 = speed-2000;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = speed;
	delay_ms(ms);
}

//turn right to vertify
void Vertify_Right(){
	TIM3->CCR1 = 0;
	TIM3->CCR2 = speed-2000;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = 0;
	
	//need to check in real car
	delay_ms(vertifyTime);
}

//turn left to vertify
void Vertify_Left(){
	TIM3->CCR1 = 0;
	TIM3->CCR2 = speed-2000;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = 0;
	
	//need to check in real car
	delay_ms(vertifyTime);
}


char car_dir_left(char car_dir)
{
	switch(car_dir)
	{
		case 'u': car_dir = 'l'; break;
		case 'l': car_dir = 'd'; break;
		case 'd': car_dir = 'r'; break;
		case 'r': car_dir = 'u'; break;
		default:			   break;
	}
	return car_dir;
}

char car_dir_right(char car_dir)
{
	switch(car_dir)
	{
		case 'u': car_dir = 'r'; break;
		case 'l': car_dir = 'u'; break;
		case 'd': car_dir = 'l'; break;
		case 'r': car_dir = 'd'; break;
		default:			   break;
	}
	return car_dir;
}

char car_dir_back(char car_dir)
{
	switch(car_dir)
	{
		case 'u': car_dir = 'd'; break;
		case 'l': car_dir = 'r'; break;
		case 'd': car_dir = 'u'; break;
		case 'r': car_dir = 'l'; break;
		default:			   break;
	}
	return car_dir;
}


#endif // MOTOR_H_INCLUDED
