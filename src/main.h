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
#include "sim800l.h"

#define MAX_CLIENT      10
#define LEN_TOPIC       12
#define SIM_BUFFER MIN_BUFFER

#define MAX_PUBLISH_MES 3
#define PUBLISH_WATER_UNSAFE 0
#define PUBLISH_TDS_PROBE_NOWATER 1
#define PUBLISH_SUBSCRIBED_OK 2
#define TDS_MEASURE_REPEAT 10               //repeat measuring TDS n times to make sure the water is really dirty
#define TDS_LIMIT 500                       //watermark value for TDS

#define SUBSCONFIRMEDF  0x1         //subscribed flag
#define UNSAFEF         0x2         //unsafe flag
#define UNDIGF          0x4         //undig flag

#define VREF 3.0                            // analog reference voltage(Volt) of the ADC
#define SCOUNT  30                          // sum of sample point

/* manage contact */
struct PHONEBOOK {
  char number[LEN_PHONE_NUM];       //contact number including send sms command
  uint32_t stat;                    //SUBSCONFIRMEDF,UNSAFEF,UNDIGF
};
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void update_phonebook(void);
uint16_t read_tds(void);
void inform_customer(void);

uint16_t read_adc(void);
int getMedianNum(int*);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
