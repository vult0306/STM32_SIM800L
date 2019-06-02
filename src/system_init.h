#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"

// #define CALIB
#define LCD
#define ADC
// #define SMS
// #define DEBUG
#define DBG_BUF 255

#if defined SMS
#define SIM_STATUS_PORT       GPIOA
#define SIM_STATUS_Pin        GPIO_Pin_6
#define SIM_PORT              GPIOA
#define SIM_Tx_Pin            GPIO_Pin_9
#define SIM_Rx_Pin            GPIO_Pin_10
void UART1_Config(void);
#endif

#define TDS_STATUS_PORT       GPIOA
#define TDS_STATUS_Pin        GPIO_Pin_7

void booting(void);
void CLK_Config(void);
void NVIC_Config(void);
void Timer2_Init(void);
void GPIO_Config(void);
void blink_led(uint8_t, uint32_t);


#if defined ADC
void ADC1_Config(void);
#define ADC_PORT              GPIOB
#define ADC_Pin               GPIO_Pin_0
#endif

#if defined LCD
#define I2C_PORT              GPIOB
#define SDA_pin               GPIO_Pin_7
#define SCL_pin               GPIO_Pin_6
void LCD_Config(void);
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

#define DBG_PORT            GPIOA
#define DBG_Tx_Pin          GPIO_PIN_2
#define DBG_Rx_Pin          GPIO_PIN_3

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
