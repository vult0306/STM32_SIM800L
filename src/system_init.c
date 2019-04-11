//------------------------------------------------
// INCLUDE
//------------------------------------------------
#include "system_init.h"


//------------------------------------------------
// RCC_Configuration
// Cau hinh clock cua cac module can su dung
//------------------------------------------------
void CLK_Config(void)
{
	// RCC_PCLK2Config(RCC_HCLK_Div1);
	
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 |
	// 					   RCC_APB1Periph_USART2, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


//------------------------------------------------
// NVIC_Config
// Config ngat cho Timer 2 de xuat du lieu ra
// Config EXTI de tinh toc do quay cua banh xe
//------------------------------------------------
// void NVIC_Config(void)
// {
// 	NVIC_InitTypeDef NVIC_InitStruct;
	
// 	// NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
// 	// NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
// 	// NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0f;
// 	// NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0d;
// 	// NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
// 	// NVIC_Init(&NVIC_InitStruct);

// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
// 	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
// 	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
// 	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStruct);
 
// }


//------------------------------------------------
// Timer2_Init
//------------------------------------------------
// void Timer2_Init(void)
// { 
// 	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
// 	TIM_TimeBaseStruct.TIM_Period = 90; 
// 	TIM_TimeBaseStruct.TIM_Prescaler = 0;
// 	TIM_TimeBaseStruct.TIM_ClockDivision = 1;
// 	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
// 	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
// 	TIM_ARRPreloadConfig(TIM2, ENABLE);
// 	TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Regular);
// 	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
// 	TIM_Cmd(TIM2, DISABLE);		
// }



//------------------------------------------------
// GPIO_Configuration
//------------------------------------------------
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	/* Configure USARTy Rx as input floating */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	/* Configure USARTy Tx as alternate function push-pull */
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//------------------------------------------------
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
//------------------------------------------------
// void UART1_Config(void)
// {
// 	USART_InitTypeDef USART_InitStructure;
// 	USART_InitStructure.USART_BaudRate = 9600;
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
// 	USART_InitStructure.USART_Parity = USART_Parity_No;
// 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
// 	USART_Init(USART2, &USART_InitStructure);
// 	USART_Cmd(USART2, DISABLE);
// 	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
// 	USART_Cmd(USART2, ENABLE);
// }

//------------------------------------------------
// putchar
//------------------------------------------------
// void putchar(int ch)
// {
// 	USART_SendData(USART1, (uint8_t) ch);
// 	/* Loop until the end of transmission */
// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){};
// }
