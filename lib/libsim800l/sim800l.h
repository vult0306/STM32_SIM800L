#ifndef __Sim800L_h
#define __Sim800L_h

#include "stm32f10x.h"

/* uC-SIM buffer */
#define MAX_BUFFER 255
#define FORWARD 0
#define BACKWARD 1

/* define SIM command */
#define IDX_CMD_MAX             6
#define IDX_CMD_TEXT_MODE       1
#define IDX_CMD_READ_SMS        2
#define IDX_CMD_DELE_SMS        3
#define IDX_CMD_SEND_SMS        4
#define IDX_CMD_CNMI_MODE       5
#define IDX_CMD_RESPOND_OK      6

#define LEN_PHONE_NUM           12
#define LEN_CMD_TEXT_MODE       9                     //length of text mode command
#define LEN_CMD_READ_SMS        9                      //length of read sms command
#define LEN_CMD_DELE_SMS        9                      //length of delete sms command
#define LEN_CMD_SEND_SMS        22
#define LEN_CMD_CNMI_MODE       17                    //length of CNMI command
#define LEN_CMD_RESPOND_OK      6                    //length of respond from module SIM

/* define message code */
#define LEN_SUBCRIBED_KEY 5
#define LEN_REC_UNREAD 10
#define MAX_PUBLISH_MES 3
#define LEN_PUBLISH_MES 60
#define MAX_SMS 35
#define MAX_CLIENT 10

/* manage contact */
struct PHONEBOOK {
  char SDT[LEN_CMD_SEND_SMS];                //contact number including send sms command
  bool subscribed;                       //this contact subscribed to receive message
  bool published;                       //published warning/activating code to this contact
};

bool sms_read(u8);
bool sms_dele(u8);
bool sms_send(char*,char*);
bool sms_set_text_mode(u8);
bool sms_set_cnmi_mode(u8,u8,u8,u8,u8);
void push_cmd(char*,u8);
int find_c(char*,u8, u8, char);    //return index of char in buffer
bool check_sim_res(void);
struct PHONEBOOK get_phone_num(char*);

#endif 
