/**
  ******************************************************************************
  * @file    SysTick/TimeBase/main.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define SIM                   USART1
#define SIM_GPIO              GPIOA
#define SIM_CLK               RCC_APB2Periph_USART1
#define SIM_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SIM_RxPin             GPIO_Pin_10
#define SIM_TxPin             GPIO_Pin_9
#define SIM_IRQn              USART1_IRQn
#define SIM_IRQHandler        USART1_IRQHandler

#define MAX_SMS 35
#define MAX_CLIENT 10
#define LEN_TOPIC      5
#define SIM_BUFFER MIN_BUFFER

#define MAX_PUBLISH_MES 3
#define PUBLISH_WATER_UNSAFE 0
#define PUBLISH_TDS_PROBE_NOWATER 1
#define PUBLISH_SUBSCRIBED_OK 2
#define LEN_PUBLISH_MES 60

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t);
void update_phonebook(void);
// void Delay(__IO uint32_t nTime);
#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
