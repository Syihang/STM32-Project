#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

int8_t Speed;
uint8_t KeyNum;

int main(void) 
{
	OLED_Init();
	Motor_Init();
	OLED_ShowString(1, 1, "Speed:");
	OLED_ShowSignedNum(1, 7, Speed, 3);
	Motor_SetSpeed(0);
	while(1)
	{
		KeyNum = Key_GetNum();
		if(1 == KeyNum)
		{
			Speed += 20;
			if(Speed > 100)
			{
				Speed = -100;
			}
		}
		OLED_ShowSignedNum(1, 7, Speed, 3);
		Motor_SetSpeed(Speed);
	}
}
