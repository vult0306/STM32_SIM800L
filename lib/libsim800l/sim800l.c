#include "sim800l.h"
#include "system_init.h"
#include "main.h"

uint16_t RxCounter=0;
// extern char SIM_BUFFER[MAX_BUFFER];
char sim_cmd_set_text_mode[LEN_CMD_TEXT_MODE]="AT+CMGF=x"; //set text mode to module SIM
char sim_cmd_read_sms[LEN_CMD_READ_SMS]="AT+CMGR=x";   //read sms command, x = sms index
char sim_cmd_dele_sms[LEN_CMD_DELE_SMS]="AT+CMGD=x";   //delete sms command, x = sms index
char sim_cmd_send_sms[LEN_CMD_SEND_SMS + LEN_PHONE_NUM]="AT+CMGS=\"+xxxxxxxxxxx\"";
char sim_cmd_set_cnmi_mode[LEN_CMD_CNMI_MODE]="AT+CNMI=0,0,0,0,0"; //do nothing with new sms, let progran handle it
char sim_cmd_res_ok[LEN_CMD_RESPOND_OK]="\r\nOK\r\n";//respond from module SIM, expected to be "OK"

/*-----------------------------------------------------------------
 * return sms state (read/unread)
 */
uint8_t sim_get_sms_state(char* buf)
{
    char* sms_unread ="REC UNREAD";
    char* sms_read ="REC READ";
    uint8_t i;
    //if this is "REC UNREAD"
    for(i=0; i<MIN_BUFFER; i++)
        if( *(buf+i) == '"' ){
            if( !strcmp(buf+i+1,sms_unread,10 ) )
                return SMS_UNREAD;
            else if( !strcmp(buf+i+1,sms_read,8 ) )
                return SMS_READ;
        }
    if( i == MIN_BUFFER )
        return NO_SMS;
} 
/*-----------------------------------------------------------------
 * find character in buffer, return 255/0 if not found
 */
int find_c(char* buffer, uint8_t end1, uint8_t end2, char c)
{
    uint8_t i;
    //find forward
    if( end1 <= end2 ){
        end2 = end2-end1;
        for( i=0; i <= end2; i++ )
            if( buffer[end1+i] == c ){
                i=end1+i;
                break;
            }
    }
    //find backward
    else{
        end2 = end1-end2;
        for( i=0; i <= end2; i++ )
            if( buffer[end1-i] == c ){
                i=end1-i;
                break;
            }
    }
    return i;
}


/*-----------------------------------------------------------------
 * read sms
 * return input sms_idx if it is out of range
 * return respond of module SIM
 */
uint8_t sim_read_sms(uint8_t sms_idx, char* buf)
{
    if( sms_idx > MAX_SMS ) return IDX_OOR;
    memset(buf,0,MIN_BUFFER);        //cleanup buffer first
    RxCounter=0;                     //reset received buffer counter
    sim_cmd_read_sms[LEN_CMD_READ_SMS-1]=sms_idx+0x30;    //set sms index
    push_cmd(sim_cmd_read_sms,LEN_CMD_READ_SMS);    //send cmd to module sim
    // putchar('\r');
    putchar('\n');
    Delay(1000);
    return sim_check_res(buf);
}


/*-----------------------------------------------------------------
 * delete sms
 * return respond of module SIM
 */
uint8_t sim_dele_sms(uint8_t sms_idx, char* buf)
{
    if( sms_idx >= MAX_SMS ) return IDX_OOR;
    memset(buf,0,MIN_BUFFER);        //cleanup buffer first
    RxCounter=0;                     //reset received buffer counter
    sim_cmd_dele_sms[LEN_CMD_DELE_SMS-1]=sms_idx+0x30;    //set sms index
    push_cmd(sim_cmd_dele_sms,LEN_CMD_DELE_SMS);    //send cmd to module sim
    // putchar('\r');
    putchar('\n');
    Delay(1000);
    return sim_check_res(buf);
}


/*-----------------------------------------------------------------
 * send sms
 * return respond of module SIM
 */
uint8_t sim_send_sms(char* phone_number, char* text, char* buf)
{
    strcpy(&sim_cmd_send_sms[LEN_CMD_SEND_SMS-1],phone_number,LEN_PHONE_NUM);
    memset(buf,0,MIN_BUFFER);                //cleanup buffer first
    RxCounter=0;                     //reset received buffer counter
    push_cmd(sim_cmd_send_sms,LEN_CMD_SEND_SMS+LEN_PHONE_NUM);       //send cmd to module sim
    // putchar('\r');
    putchar('\n');
    Delay(1000);
    push_cmd(text,LEN_PUBLISH_MES);
    putchar(26);
    return sim_check_res(buf);
}


/*-----------------------------------------------------------------
 * set text/pdu mode for sms
 * return respond of module SIM
 */
uint8_t sim_set_text_mode(uint8_t mode, char* buf)
{
    if( mode > 1 ) return IDX_OOR;
    memset(buf,0,MIN_BUFFER);        //cleanup buffer first
    RxCounter=0;                     //reset received buffer counter
    sim_cmd_set_text_mode[LEN_CMD_TEXT_MODE-1]=mode+0x30;    //set mode index
    push_cmd(sim_cmd_set_text_mode,LEN_CMD_TEXT_MODE);    //send cmd to module sim
    // putchar('\r');
    putchar('\n');
    Delay(1000);
    return sim_check_res(buf);
}


/*-----------------------------------------------------------------
 * set behaviour for new message
 * return respond of module SIM
 */
bool sim_set_cnmi_mode(uint8_t mode, uint8_t mt, uint8_t bm, uint8_t ds, uint8_t bfr, char* buf)
{
    if( (mode > 3) || (mt > 3) || (bm > 2) || (ds > 1) || (bfr > 1) ) return IDX_OOR;
    memset(buf,0,MIN_BUFFER);        //cleanup buffer first
    RxCounter=0;                     //reset received buffer counter
    sim_cmd_set_cnmi_mode[LEN_CMD_CNMI_MODE-1]=mode+0x30;    //set mode index
    push_cmd(sim_cmd_set_cnmi_mode,LEN_CMD_CNMI_MODE);    //send cmd to module sim
    // putchar('\r');
    putchar('\n');
    Delay(1000);
    return sim_check_res(buf);
}


/*-----------------------------------------------------------------
 * push command to module sim
 */
void push_cmd(char* cmd, uint8_t cmd_len)
{
    uint8_t i;
    for( i=0; i < cmd_len; i++)
    {
        putchar(*(cmd+i));
    }
}


/*-----------------------------------------------------------------
 * check respond status of module sim
 */
bool sim_check_res(char* buf)
{
  uint8_t i;
  for(i=MIN_BUFFER-1;i>0;i--)
    if( *(buf + i) == '\n' ){
      if(!strcmp(buf+i-LEN_CMD_RESPOND_OK+1,sim_cmd_res_ok,LEN_CMD_RESPOND_OK)){
        i=0;
      }
      break;
    }
  if(i==0)
    return SIM_RES_ERROR;
  else
    return SIM_RES_OK;
}


/*-----------------------------------------------------------------*/
/* extract phone number from a sms message
 * replace ZZ with country code
 */
uint8_t sim_get_sms_contact(char* num,char* buf)
{
    uint8_t i;

    // struct PHONEBOOK temp={"AT+CMGS=\"+ZZxxxxxxxxx\"",FALSE,FALSE};
    //get phone number
    if( sim_check_res(buf) ){
        for(i=0;i<MIN_BUFFER;i++)
            if(buf[i]==',')
                break;
        if( i == 0 ) return NO_SMS;
        strcpy(num,buf+i+2,LEN_PHONE_NUM);
        return SIM_RES_OK;
    }
    else
    {
        return SIM_RES_ERROR;
    }
    // for(j=0;j<LEN_PHONE_NUM-10;j++)
    //     temp.SDT[10+j]=buf[i+j+3];
    // return temp;
}

/*-----------------------------------------------------------------*/
/* extract data partion from a sms message
 * src: respond message from module sim
 * det: string to contain sms data
 * return len of data. return 0 if message is empty or exceed
 * message max size
 */
uint8_t sim_get_sms_data(char* data, char* buf)
{
    uint8_t i,j;
    if( sim_check_res(buf) ){
        for(i=MIN_BUFFER-1; i>0; i--)
            if( *(buf+i) == '"' ){
                i+=2;
                break;
            }
        if( i == 0 ) return NO_SMS;
        for(j=MIN_BUFFER-1; j>0; j--)
            if( *(buf+j) == '\r' )
                break;
        strcpy(data,buf+i,j-i);
        return SIM_RES_OK;
    }
    else
    {
        return SIM_RES_ERROR;
    }
}

