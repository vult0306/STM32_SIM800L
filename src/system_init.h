#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
#define SIM                   USART1
#define SIM_GPIO              GPIOA
#define SIM_CLK               RCC_APB2Periph_USART1
#define SIM_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SIM_RxPin             GPIO_Pin_10
#define SIM_TxPin             GPIO_Pin_9
#define SIM_IRQn              USART1_IRQn
#define SIM_IRQHandler        USART1_IRQHandler

void booting(void);
void CLK_Config(void);
void NVIC_Config(void);
void Timer2_Init(void);
void GPIO_Config(void);
void UART1_Config(void);
void putchar(int c);
uint8_t strcmp(char*,char*,u8);
void strcpy(char*,char*,u8);
void memset(void*,char,u16);
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t);

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


#ifdef __cplusplus
}
#endif


#endif /* __SYSTEM_INIT_H */


/******************* (C) COPYRIGHT 2009 ARMVietNam *****END OF FILE****/
