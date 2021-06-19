#include "stm32f10x.h"
#include "init.h"
#include "delay.h"
#include "port.h"
#include "infrared.h"
#include "ultrasonic.h"
#include "motor.h"
#include "stdio.h"
#include "test.h"

#define threshold 10
#define turn_time 550
#define verify_time 80

int main()
{
	System_Init();
	delay_ms(1200);
	int head;
	int traversed = 0;
	char carDir = 'u';//init dir
	//for the loop
	while(1)
	{
		/*test*/
		//test();
		Dir_test(carDir);//for debug
		//Ultrasonic_test(threshold);
		
		/*function*/

		Go_Forward();
		delay_ms(300);
		
		//Go_Little_Forward();

		//上行时左侧有口
		if((carDir == 'u')&&(Get_Infrared(Rear_Left) == 0)&&traversed)
		{
			delay_ms(50);
			Car_Stop();delay_ms(1000);
			Turn_Left(turn_time);
			Car_Stop();delay_ms(300);
			carDir = car_dir_left(carDir); // change dir
		}
		
		//下行时车右侧有口
		if((carDir == 'd')&&(Get_Infrared(Rear_Right) == 0)&&traversed)
		{
			delay_ms(50);
			Car_Stop();delay_ms(1000);
			Turn_Right(turn_time);	
			Car_Stop();delay_ms(300);
			carDir = car_dir_right(carDir); 
		}

		float length = Hcsr04GetLength();
		if(length < threshold)
		{
			head = 1;
			traversed = 1;
		}
		else
			head = 0;

		//前方有障碍
		if(head == 1)
		{//车朝向上或者下时
			
			if((carDir == 'u')||(carDir == 'd'))
			{
				if((Get_Infrared(Rear_Left) == 1) && (Get_Infrared(Rear_Right) == 1))//且左右有墙时
				{
					Go_Back();			//先后退防止撞墙，并转180°，
					delay_ms(300);
					Turn_Around(2*turn_time); 
					Car_Stop();delay_ms(300);
					carDir = car_dir_back(carDir);
				}
			} 
			else if(carDir == 'l')
			{
				if(Get_Infrared(Rear_Left) == 0)
				{//车左侧没墙 
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Left(turn_time);
					Car_Stop();delay_ms(300);
					carDir = car_dir_left(carDir);
					if(carDir == 'u'||carDir == 'd') traversed = 0; //重新遍历
				}
				else if (Get_Infrared(Rear_Right) == 0) 
				{//车不能左转就右转，优先左转
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Right(turn_time);
					Car_Stop();delay_ms(300);
					carDir = car_dir_right(carDir);
					if(carDir == 'u'||carDir == 'd') traversed = 0; //重新遍历
				}
				
				/*if(Get_Infrared(Rear_Right) == 0)
				{//车右侧没墙 
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Right(turn_time);
					Car_Stop();delay_ms(300);
					carDir = car_dir_right(carDir);
				}
				else if (Get_Infrared(Rear_Left) == 0) 
				{//车不能右转就左转，优先右转
					delay_ms(20);
					Car_Stop();delay_ms(1000);
					Turn_Left(turn_time);
					Car_Stop();delay_ms(300);
					carDir = car_dir_left(carDir);
				}*/
				else 
				{
					Car_Stop();delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
				}
			}
		}//if(head == 1)
		
		if((carDir == 'u')||(carDir == 'd'))
		{
		
			//Distance less than threshold return true, else return false
			
			/*int vertifyLeft = Get_Infrared(Rear_Left);
			int vertifyRight = Get_Infrared(Rear_Right);*/
			
			/*int vertifyLeft = Get_Infrared(Front_Left) && !Get_Infrared(Rear_Left);
			int vertifyRight = Get_Infrared(Front_Right) && !Get_Infrared(Rear_Right);*/
			
			int vertifyLeft = Get_Infrared(Front_Left);
			int vertifyRight = Get_Infrared(Front_Right);

			if(vertifyLeft==1 && vertifyRight==0)	Vertify_Right(verify_time);  //左侧离得近
			else if(vertifyLeft==0 && vertifyRight==1) Vertify_Left(verify_time);  //右侧离得近
			
		}
		
	}//while
}//main
