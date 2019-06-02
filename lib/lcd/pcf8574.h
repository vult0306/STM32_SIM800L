#include "stm32f10x.h"
// #define PCF8574_address                              0x4E
#define PCF8574_address                              0x7E//(3F << 1)
unsigned char PCF8574_read(void);
void PCF8574_write(unsigned char data_byte);
