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

int main()
{
	System_Init();
	delay_ms(1200);
	int head;

	//for the loop
	while(1)
	{	
		//test();
		
		Go_Forward();

		/*******************直行策略*********************/

		//Distance less than threshold return true, else return false
		int vertifyLeft = Get_Infrared(Infra_vertify_Left);
		int vertifyRight = Get_Infrared(Infra_vertify_Right);

		if(vertifyLeft==1 && vertifyRight==0)	Vertify_Right();
		else if(vertifyLeft==0 && vertifyRight==1) Vertify_Left();

		/********************转向策略********************/

		char carDir = 'u';

		//上行时左侧有口
		if((carDir == 'u')&&(Infra_Left == 0)){
			delay_ms(20);
			Turn_Left();	//左转;
			carDir = car_dir_left(carDir); //换车的前端朝向的方向car_dir为l
		}

		//下行时车右侧有口
		if((carDir == 'd')&&(Infra_Right == 0)){
			delay_ms(20);
			Turn_Right();	//右转
			carDir = car_dir_right(carDir); //换方向为r，（r为正方向）
		}

		float lenght = Hcsr04GetLength();
		//need to check
		if(lenght < threshold)	head = 1;
		else head = 0;

		//前方有障碍
		if(head == 1){//车朝向上或者下时
			if((carDir == 'u')||(carDir == 'd')){
				if((Infra_Left == 1)&&(Infra_Right == 1)){//且左右有墙时
					Go_Back();			//先后退防止撞墙，并转180°，
					delay_ms(300);		
					Turn_Around(); 
					carDir = car_dir_back(carDir);
				}
			} 
			else if(carDir == 'l'){//朝右直走转换通道时		
				if(Infra_Left == 1){//车左侧没墙  		
					Turn_Left(); 
					carDir = car_dir_left(carDir); 
				}
				else{//车不能左转就右转，优先左转
					Turn_Right(); 
					carDir = car_dir_right(carDir); 
				}
			}
		}	        
	}
}
