#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void) 
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// 设置低电平
	// GPIO_SetBits(GPIOA, GPIO_Pin_0);		// 设置高电平
	
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);	// 设置指定输出
	unsigned int LEDPIN = 0x0001;
	while(1)
	{
		if (LEDPIN == 0x0020) LEDPIN = 0x0001;
		GPIO_Write(GPIOA, ~LEDPIN);
		LEDPIN <<= 1;
		Delay_ms(100);
	}
}
