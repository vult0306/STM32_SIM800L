#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
void CLK_Config(void);
void NVIC_Config(void);
void Timer2_Init(void);
void GPIO_Config(void);
void UART1_Config(void);
void putchar(int c);
void getchar(void);
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
