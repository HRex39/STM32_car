#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"
#include "motor.h"
#include "stdio.h"
#include "test.h"

#define threshold 15

int main()
{
	System_Init();
	delay_ms(1200);
	int head;
	char carDir = 'u';//init dir
	//for the loop
	while(1)
	{
		//test();
		Dir_test(carDir);//for debug

		Go_Forward();
		delay_ms(300);
		
		//Go_Little_Forward();

		//上行时左侧有口
		if((carDir == 'u')&&(Get_Infrared(Infra_vertify_Left) == 0))
		{
			delay_ms(20);
			Car_Stop();delay_ms(1000);
			Turn_Left(300);
			carDir = car_dir_left(carDir); // change dir
		}
		
		//下行时车右侧有口
		if((carDir == 'd')&&(Get_Infrared(Infra_vertify_Right) == 0)){
			delay_ms(20);
			Car_Stop();delay_ms(1000);
			Turn_Right(300);	
			carDir = car_dir_right(carDir); 
		}

		float length = Hcsr04GetLength();
		if(length < threshold)
			head = 1;
		else
			head = 0;

		//前方有障碍
		if(head == 1)
		{//车朝向上或者下时
			
			if((carDir == 'u')||(carDir == 'd'))
			{
				if((Get_Infrared(Infra_Left) == 1) && (Get_Infrared(Infra_Right) == 1))//且左右有墙时
				{
					Go_Back();			//先后退防止撞墙，并转180°，
					delay_ms(300);
					Turn_Around(600); 
					carDir = car_dir_back(carDir);
				}
			} 
			else if(carDir == 'l')
			{
				if(Get_Infrared(Infra_Left) == 0)
				{//车左侧没墙 
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Left(300);
					carDir = car_dir_left(carDir);
				}
				else if (Get_Infrared(Infra_Right) == 1) 
				{//车不能左转就右转，优先左转
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Right(300);
					carDir = car_dir_right(carDir);
				}
				else 
				{
					Car_Stop();delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
				}
			}
		}//if(head == 1)
		
		if((carDir == 'u')||(carDir == 'd'))
		{
		
			//Distance less than threshold return true, else return false
			int vertifyLeft = Get_Infrared(Infra_vertify_Left);
			int vertifyRight = Get_Infrared(Infra_vertify_Right);

			if(vertifyLeft==1 && vertifyRight==0)	Vertify_Right();
			else if(vertifyLeft==0 && vertifyRight==1) Vertify_Left();
			
		}
		
	}//while
}//main
