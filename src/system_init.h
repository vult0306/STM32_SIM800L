#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

// #define CALIB
#define ADC
// #define TEST_SIM
#define DEBUG
#define DBG_BUF 255

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

#if defined ADC
void ADC1_Config(void);
#endif


#if defined DEBUG
/* define debug cmd code */
#define CMD_NEW_TEMPERATOR  0
#define CMD_SET_TEXT_MODE   1
#define CMD_DELE_SMS        2
#define CMD_SEND_SMS        3
#define CMD_CNMI_MODE       4
#define CMD_SIG_STR         5                   //signal strength
#define CMD_REJ_IN_CALL     6                   //reject incomming call
#define CMD_MAX             7

void UART2_Config(void);
void print(char);
#endif

void putchar(char);
uint8_t strcmp(char*,char*,uint8_t);
void strcpy(char*,char*,uint8_t);
void memset(void*,char,uint16_t);
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
