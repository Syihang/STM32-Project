#include "stm32f10x.h"                  // Device header

extern uint16_t num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 内部时钟
	TIM_InternalClockConfig(TIM2);
	
	// 初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;					// 自动重装器的值 ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;					// PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// 手动清除更新中断标志位
	
	// 使能中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 配置中断控制器
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	//定时器2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	// 响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	// 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

//定时器2的中断函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
	}
}
