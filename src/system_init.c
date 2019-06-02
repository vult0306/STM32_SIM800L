//------------------------------------------------
// INCLUDE
//------------------------------------------------
#include "system_init.h"

static __IO uint32_t TimingDelay;
static __IO uint32_t sim_led_on;
static __IO uint32_t tds_led_on;
static __IO uint32_t sim_led_on_count;
static __IO uint32_t tds_led_on_count;

NVIC_InitTypeDef NVIC_InitStruct;
//------------------------------------------------
// booting the system
// Cau hinh cac module can su dung
//------------------------------------------------
void booting(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

  /* Setup SysTick Timer for 1 msec interrupts.
     ------------------------------------------
    1. The SysTick_Config() function is a CMSIS function which configure:
       - The SysTick Reload register with value passed as function parameter.
       - Configure the SysTick IRQ priority to the lowest value (0x0F).
       - Reset the SysTick Counter register.
       - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
       - Enable the SysTick Interrupt.
       - Start the SysTick Counter.
    
    2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
       SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
       inside the misc.c file.

    3. You can change the SysTick IRQ priority by calling the
       NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
       call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

    4. To adjust the SysTick time base, use the following formula:
                            
         Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
    
       - Reload Value is the parameter to be passed for SysTick_Config() function
       - Reload Value should not exceed 0xFFFFFF
   */
  	uint16_t i=0xFFFF;
	    while(i>0)	i--;
        while(i<0xFFFF)	i++;
	CLK_Config();
	NVIC_Config();
	GPIO_Config();
#if defined SMS
	UART1_Config();
#endif
#if defined DEBUG
    UART2_Config();
#endif
#if defined ADC
    ADC1_Config();
#endif
#if defined LCD
    LCD_Config();
#endif
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}



//------------------------------------------------
// RCC_Configuration
// Cau hinh clock cua cac module can su dung
//------------------------------------------------
void CLK_Config(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
#if defined ADC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
#endif
#if defined DEBUG
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
#endif
#if defined LCD
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
#endif
}


//------------------------------------------------
// NVIC_Config
// Config ngat cho Timer 2 de xuat du lieu ra
// Config EXTI de tinh toc do quay cua banh xe
//------------------------------------------------
void NVIC_Config(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
 
 #if defined DEBUG
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
#endif
}



//------------------------------------------------
// GPIO_Configuration
//------------------------------------------------
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#if defined SMS
    /* SIM STATUS LED */
	GPIO_InitStructure.GPIO_Pin = SIM_STATUS_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_Init(SIM_STATUS_PORT, &GPIO_InitStructure);

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = SIM_Rx_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SIM_PORT, &GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = SIM_Tx_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SIM_PORT, &GPIO_InitStructure);
#endif
    /* TDS STATUS LED */
	GPIO_InitStructure.GPIO_Pin = TDS_STATUS_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_Init(TDS_STATUS_PORT, &GPIO_InitStructure);

#if defined DEBUG
    GPIO_InitStructure.GPIO_Pin = DBG_Rx_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DBG_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DBG_Tx_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(DBG_PORT, &GPIO_InitStructure);
#endif

#if defined ADC
    /* Configure PB.00 (ADC Channel08) as analog input -------------------------*/
    GPIO_InitStructure.GPIO_Pin = ADC_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(ADC_PORT, &GPIO_InitStructure);
#endif

#if defined LCD
	GPIO_InitStructure.GPIO_Pin = SCL_pin | SDA_pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(I2C_PORT, &GPIO_InitStructure);
#endif
}

#if defined SMS
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
void UART1_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
    USART_Cmd(USART1, DISABLE);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
#endif

#if defined DEBUG
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
void UART2_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
    USART_Cmd(USART2, DISABLE);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}
#endif

#if defined ADC
//------------------------------------------------
  /* ADC1 configured as follow:
  */
//------------------------------------------------
void ADC1_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel08 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
    
    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
}
#endif

#if defined LCD
void LCD_Config(void)
{
    I2C_InitTypeDef I2C_InitStruct;
    // Step 1: Initialize I2C
    I2C_InitStruct.I2C_ClockSpeed = 100000;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}
#endif

#if defined SMS
//------------------------------------------------
// putchar
//------------------------------------------------
void putchar(char ch)
{
	USART_SendData(USART1, (char) ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){};
}
#endif

#if defined DEBUG
//------------------------------------------------
// print
//------------------------------------------------
void print(char ch)
{
    USART_SendData(USART2, (char) ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){};
}
#endif

//------------------------------------------------
// strcmp
// if Return value < 0 then it indicates X is less than Y.
// if Return value > 0 then it indicates Y is less than X.
// if Return value = 0 then it indicates X is equal to Y.
//------------------------------------------------
uint8_t strcmp(char*s1,char*s2,uint8_t len){
    while(len>0){
        if( *(s1+len-1) != *(s2+len-1) ){
            break;
        }
        len-=1;
    }
    return len;
}


//------------------------------------------------
// strcpy
//------------------------------------------------
void strcpy(char* des,char* src,uint8_t len){
  while(len>0){
    *(des+len-1) = *(src+len-1);
    len-=1;
  }
  return;
}


//------------------------------------------------
// memset
//------------------------------------------------
void memset(void* str, char ch, uint16_t n){
	int i;
	//type cast the str from void* to char*
	char *s = (char*) str;
	//fill "n" elements/blocks with ch
	for(i=0; i<n; i++)
		s[i]=ch;
    return;
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    { 
        TimingDelay--;
    }

#if defined SMS
    if (sim_led_on != 0x00)
    {
        if(sim_led_on_count == 0)
        {
            GPIO_WriteBit(SIM_STATUS_PORT, SIM_STATUS_Pin, (BitAction)(1 - GPIO_ReadOutputDataBit(SIM_STATUS_PORT, SIM_STATUS_Pin)));        
            sim_led_on_count = sim_led_on;  //reload counter
        }
        else
        {
            sim_led_on_count--;
        }  
    }
#endif
    if (tds_led_on != 0x00)
    {
        if(tds_led_on_count == 0)
        {
            GPIO_WriteBit(TDS_STATUS_PORT, TDS_STATUS_Pin, (BitAction)(1 - GPIO_ReadOutputDataBit(TDS_STATUS_PORT, TDS_STATUS_Pin)));        
            tds_led_on_count = tds_led_on;  //reload counter
        }
        else
        {
            tds_led_on_count--;
        }  
    }
}

/**
  * @brief  blinking led.
  * @param  port,pin,period
  * @retval None
  */
void blink_led(uint8_t led_idx, uint32_t period)
{
    switch (led_idx)
    {
#if defined SMS
        case SIM_STATUS_Pin:
        sim_led_on = period;
        break;
#endif
        case TDS_STATUS_Pin:
        tds_led_on = period;
        break;

        default:
        break;
    }
}
