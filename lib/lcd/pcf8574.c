#include "pcf8574.h"
#include "stm32f10x.h"

unsigned char PCF8574_read(void)
{
   unsigned char port_byte = 0x00;
   unsigned char num_of_bytes = 0x01;
   while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
   I2C_GenerateSTART(I2C1,ENABLE);
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C1,PCF8574_address, I2C_Direction_Receiver);
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
   while(num_of_bytes)
   {
        if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED))
        {  
            if(num_of_bytes == 0)
            {
                I2C_AcknowledgeConfig(I2C1,DISABLE);
                I2C_GenerateSTOP(I2C1,ENABLE);  
            }
            port_byte = I2C_ReceiveData(I2C1);
            num_of_bytes--;
        }
   }; 
   return port_byte;
}
void PCF8574_write(unsigned char data_byte)
{
   I2C_GenerateSTART(I2C1,ENABLE);
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C1,PCF8574_address, I2C_Direction_Transmitter);
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
   I2C_SendData(I2C1,data_byte);
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
   I2C_GenerateSTOP(I2C1,ENABLE);  
}
