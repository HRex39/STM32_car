# STM32_car
robot car use STM32F103RB

## HCR 2021/6/10

1. Things about Delay:
   	`eg.. delay_ms(1000)`

2. Things about Infrared:
	IF GPIO_ReadInputDataBit == 0
   	THEN there is the obstacle
   	eg.. 
   
   ```c
   if (GPIO_ReadInputDataBit(GPIOA, Infra_Left) == 0)
      		GPIO_ResetBits(GPIOC, LED1);
      	else
      		GPIO_SetBits(GPIOC, LED1);
   ```
3. Thing about Ultrasonic:
    - `RCC_APB1PeriphClockCmd`: Enables or disables the Low Speed APB (APB1) peripheral clock
    - `RCC_APB2PeriphClockCmd`: Enables or disables the High Speed APB (APB2) peripheral clock.
## YSK 2021/6/11
- You can just use following code to run the car:
	
  - Next two should  use with delay:		
    ```c
    Go_Forward();delay_ms(1000);
    Go_Back();delay_ms(1000);
    ```
  -  Others just easily use it:
      ```c
      Car_Stop();
      Turn_Left();
      Turn_Right();
      Turn_Around();
      ```
  
- You can just use following code to test or use Infrared:

  ```c
  //Distance less than threshold will light the LED
  void LED_Check_Infrared(uint16_t GPIO_Pin);
  //Distance less than threshold return true, else return false 
  bool Get_Infrared(uint16_t GPIO_Pin);
  ```

- I move some test code to test() in test.h

## YSK 2021/6/16

1. 4个红外pin口的的定义，初始化时使用的是GPIOA。

   1. port.h	line9

2. 修正轨迹时的时间延迟（即修正的幅度）。

   #define vertifyTime 50

3. 前方障碍的阈值修改。

   #define threshold 10（cm）