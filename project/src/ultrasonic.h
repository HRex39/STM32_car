#ifndef ULTRASONIC_H_INCLUDED
#define ULTRASONIC_H_INCLUDED
#include "stm32f10x.h"
#include "port.h"
#include "delay.h"

//超声波计数
u16 msHcCount = 0;

 //NVIC配置
void hcsr04_NVIC()
{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;             //选择串口1中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占式中断优先级设置为1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //响应式中断优先级设置为1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //使能中断
		NVIC_Init(&NVIC_InitStructure);
}

void Ultra_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //init a structure of timer
	GPIO_InitTypeDef  GPIO_InitStructure;	//init a structure of GPIO
	//config the Ultra_Front_Trg(GPIOC)
	GPIO_InitStructure.GPIO_Pin = Ultra_Front_Trg;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//config the Ultra_Front_Echo(GPIOB)
	GPIO_InitStructure.GPIO_Pin = Ultra_Front_Echo;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//enable timer4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_DeInit(TIM2);//这个是什么意思啊不懂！！
	
	TIM_TimeBaseStructure.TIM_Period = (1000-1); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值         计数到1000为1ms
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //设置用来作为TIMx时钟频率除数的预分频值  1M的计数频率 1US计数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位		 
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);   		//清除更新中断，免得一打开中断立即产生中断
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	hcsr04_NVIC();
	TIM_Cmd(TIM4,DISABLE);
}

//打开定时器4
static void OpenTimerForHc()
{
	TIM_SetCounter(TIM4,0);
	msHcCount = 0;
	TIM_Cmd(TIM4, ENABLE);
}

//关闭定时器4
static void CloseTimerForHc()
{
	TIM_Cmd(TIM4, DISABLE);
}

//定时器4终中断
void TIM4_IRQHandler()
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		msHcCount++;
	}
}

//获取定时器4时间
u32 GetEchoTimer(void)
{
	u32 t = 0;
	t = msHcCount*1000;//得到ms
	t += TIM_GetCounter(TIM4);//得到us
	TIM4->CNT = 0;  //将TIM2计数寄存器的计数值清零
	delay_ms(50);
	return t;
}

//一次获取超声波测距数据 两次测距之间需要相隔一段时间，隔断回响信号
//为了消除余震的影响，取五次数据的平均值进行加权滤波。
float Hcsr04GetLength()
{
	u32 t = 0;
	int i = 0;
	float lengthTemp = 0;
	float sum = 0;
	while(i!=3)
	{
		GPIO_SetBits(GPIOC, Ultra_Front_Trg);      //发送口高电平输出
		delay_us(20);
		GPIO_ResetBits(GPIOC, Ultra_Front_Trg);
		while(GPIO_ReadInputDataBit(GPIOB, Ultra_Front_Echo) == 0);      //等待接收口高电平输出
		OpenTimerForHc();        //打开定时器
		i = i + 1;
		while(GPIO_ReadInputDataBit(GPIOB, Ultra_Front_Echo) == 1);
		CloseTimerForHc();        //关闭定时器
		t = GetEchoTimer();        //获取时间,分辨率为1uS
		lengthTemp = ((float)t/58.0);//cm
		sum = lengthTemp + sum ;
	}
	lengthTemp = sum/3.0;
	return lengthTemp;
}





#endif // ULTRASONIC_H_INCLUDED
