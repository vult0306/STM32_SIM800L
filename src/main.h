#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x.h"
#include "stdbool.h"
/* Private typedef -----------------------------------------------------------*/
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
/* Private define ------------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOC)              //port use to turn on/off module SIM
#define LED_GPIO_PINS  (GPIO_PIN_3)         //pin use to turn on/off module SIM
#define TIM4_PERIOD       124               //1ms
#define UART_BUFFER 255                     //255 charactor for UART buffer
#define TDS_LIMIT 500                       //watermark value for TDS
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#define VREF 3.0                            // analog reference voltage(Volt) of the ADC
#define SCOUNT  30                          // sum of sample point

#define CMD_TEXT_MODE 1                     //set text mode to module SIM
#define CMD_READ_SMS 2                      //read SMS command index
#define CMD_SEND_SMS 3                      //send SMS command index
#define CMD_DELE_MODE 4                     //delete SMS command index
#define CMD_CNMI_MODE 5                     //config behavior with new sms(do nothing)

#define LEN_TEXT_MODE 9                     //length of text mode command
#define LEN_READ_SMS 9                      //length of read sms command
#define LEN_DELE_SMS 9                      //length of delete sms command
#define LEN_SDT_CMD 22                      //length of string contain phone number
#define LEN_RESPOND_OK 6                    //length of respond from module SIM
#define LEN_CNMI_MODE 17                    //length of CNMI command
#define LEN_REC_UNREAD 10                   //length of responded sms status

#define MAX_CONTACT 10                      //Maximmum contact stored
#define MAX_SMS 35                          //Maximum sms stored
#define TDS_MEASURE_REPEAT 10               //repeat measuring TDS n times to make sure the water is really dirty

#define MAX_SMS_SENT_OUT 3                       //number of warning code
#define TDS_OVER_RANGE 0                    //tds over safe range
#define TDS_UNDER_RANGE 1                   //tds probe is probably not plugged into water
#define ACTIVATE_SUCCESS 2                   //Successfully activated
#define LEN_SEND_TDS_OVF 80                 //length of maximum sms command
#define LEN_SEND_TDS_UDF 80                 //length of maximum sms command
#define LEN_SEND_ACTIVAT 80                 //length of maximum sms command
#define LEN_ACTIVATE_CODE 5
//SDT[LEN_SDT_CMD]="AT+CMGS=\"+xxxxxxxxxxx\"";
struct PHONEBOOK {
  char SDT[LEN_SDT_CMD];                //contact number including send sms command
  bool subcribed;                       //this contact subcribed to receive message
  bool published;                       //published warning/activating code to this contact
};

static char respond_ok[LEN_RESPOND_OK]="\n\rKO\n\r";//{'\n','\r','K','O','\n','\r'};   //respond from module SIM, expected to be "OK"
static char AT_TEXT_MODE[LEN_TEXT_MODE]="AT+CMGF=1";                           //set text mode to module SIM
volatile char AT_READ_SMS[LEN_READ_SMS]="AT+CMGR=x";                             //read sms command, x = sms index
volatile char AT_DELE_SMS[LEN_DELE_SMS]="AT+CMGD=x";                             //delete sms command, x = sms index
static char AT_CNMI_MODE[LEN_CNMI_MODE]="AT+CNMI=0,0,0,0,0";                  //do nothing with new sms, let progran handle it
static char activated_code[LEN_ACTIVATE_CODE]="water";                         //activate code
static char sms_unread[LEN_REC_UNREAD]="REC UNREAD";
static char AT_SEND_SMS_TDS_OVF[LEN_SEND_TDS_OVF]="Loi loc nuoc het han, vui long thay loi loc moi"; //warning message to send to customer
static char AT_SEND_SMS_TDS_UDF[LEN_SEND_TDS_UDF]="Dau do khong tiep xuc voi nuoc, vui long kiem tra dau do"; //warning message to send to customer
static char AT_SEND_SMS_ACTIVAT[LEN_SEND_ACTIVAT]="DANG KY THANH CONG"; //sucessfully activated contact

static void CLK_Config(void);                     //config cpu clock
static void UART1_Config(void);                   //config uC with SIM communication
static void TIM4_Config(void);                    //config timer
static void GPIO_Config(void);                    //config GPIO
static void ADC_Config(void);                     //config ADC to measure TDS
static int getMedianNum(int*);                    //median value of TDS
static void readTDS(void);                        //read TDS value from TDS sensor
static void cmd_send(uint8_t);                    //send command to module SIM
static void eol(void);                            //send break charactor <LF>
static bool check_respond(void);                  //check respond from module SIM after each command
static bool strcmp(char*,char*,uint8_t);          //compare two string/array
static void strcpy(char*,char*,uint8_t);          //copy string 2 to string 1
static void update_phonebook(void);               //add/remove contact
static void inform_customer(void);                //inform customer if TDS value over range or tds probe is not plugged into water
static void booting(void);
struct PHONEBOOK get_phone_num(void);

#endif /* __MAIN_H */
