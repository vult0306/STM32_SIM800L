#include "sim800l.h"
#include "system_init.h"
#include "main.h"

extern char SIM_BUFFER[MAX_BUFFER];
char sim_cmd_set_text_mode[LEN_CMD_TEXT_MODE]="AT+CMGF=x"; //set text mode to module SIM
char sim_cmd_read_sms[LEN_CMD_READ_SMS]="AT+CMGR=x";   //read sms command, x = sms index
char sim_cmd_dele_sms[LEN_CMD_DELE_SMS]="AT+CMGD=x";   //delete sms command, x = sms index
char sim_cmd_send_sms[LEN_CMD_SEND_SMS]="AT+CMGS=\"+xxxxxxxxxxx\"";
char sim_cmd_set_cnmi_mode[LEN_CMD_CNMI_MODE]="AT+CNMI=0,0,0,0,0"; //do nothing with new sms, let progran handle it
char sim_cmd_res_ok[LEN_CMD_RESPOND_OK]="\r\nOK\n\r";//respond from module SIM, expected to be "OK"
char topic[LEN_SUBCRIBED_KEY]="water";           //topic
char sms_unread[LEN_REC_UNREAD]="REC UNREAD";    //"REC UNREAD"
char publish_mes[MAX_PUBLISH_MES][LEN_PUBLISH_MES]={"******Loi loc nuoc het han, vui long thay loi loc moi*******",
                                                    "**Dau do khong tiep xuc voi nuoc, vui long kiem tra dau do**",
                                                    "*********************DANG KY THANH CONG*********************"};
/*-----------------------------------------------------------------*/
//find character in buffer, return 255/0 if not found
int find_c(char* buffer, u8 end1, u8 end2, char c)
{
    u8 i;
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


/*-----------------------------------------------------------------*/
//read sms
bool sms_read(u8 sms_idx)
{
    if( sms_idx >= MAX_SMS ) return FALSE;
    memset(SIM_BUFFER,0,sizeof(SIM_BUFFER));        //cleanup buffer first
    sim_cmd_read_sms[LEN_CMD_READ_SMS-1]=sms_idx+0x30+1;    //set sms index
    push_cmd(sim_cmd_read_sms,LEN_CMD_READ_SMS);    //send cmd to module sim
    putchar('\n');
    Delay(100);
    return check_sim_res();
}


/*-----------------------------------------------------------------*/
//delete sms
bool sms_dele(u8 sms_idx)
{
    if( sms_idx >= MAX_SMS ) return FALSE;
    memset(SIM_BUFFER,0,sizeof(SIM_BUFFER));        //cleanup buffer first
    sim_cmd_dele_sms[LEN_CMD_DELE_SMS-1]=sms_idx+0x30+1;    //set sms index
    push_cmd(sim_cmd_dele_sms,LEN_CMD_DELE_SMS);    //send cmd to module sim
    putchar('\n');
    Delay(100);
    return check_sim_res();
}


/*-----------------------------------------------------------------*/
//send sms
bool sms_send(char* phone_number, char* text)
{
    strcpy(sim_cmd_send_sms+9,phone_number,LEN_PHONE_NUM);
    memset(SIM_BUFFER,0,sizeof(SIM_BUFFER));                //cleanup buffer first
    push_cmd(sim_cmd_send_sms,LEN_CMD_SEND_SMS);       //send cmd to module sim
    putchar('\n');
    Delay(100);
    push_cmd(text,LEN_PUBLISH_MES);
    putchar(26);
    return check_sim_res();
}


/*-----------------------------------------------------------------*/
//set text/pdu mode for sms
bool sms_set_text_mode(u8 mode)
{
    if( mode > 1 ) return FALSE;
    memset(SIM_BUFFER,0,sizeof(SIM_BUFFER));        //cleanup buffer first
    sim_cmd_set_text_mode[LEN_CMD_TEXT_MODE-1]=mode+0x30+1;    //set sms index
    push_cmd(sim_cmd_set_text_mode,LEN_CMD_TEXT_MODE);    //send cmd to module sim
    putchar('\n');
    Delay(100);
    return check_sim_res();
}


/*-----------------------------------------------------------------*/
//set text/pdu mode for sms
bool sms_set_cnmi_mode(u8 mode,u8 mt,u8 bm,u8 ds,u8 bfr)
{
    if( mode > 3 ) return FALSE;
    if( mt > 3 ) return FALSE;
    if( bm > 2 ) return FALSE;
    if( ds > 1 ) return FALSE;
    if( bfr > 1 ) return FALSE;
 
    memset(SIM_BUFFER,0,sizeof(SIM_BUFFER));        //cleanup buffer first
    sim_cmd_set_cnmi_mode[LEN_CMD_CNMI_MODE-1]=mode+0x30+1;    //set sms index
    push_cmd(sim_cmd_set_cnmi_mode,LEN_CMD_CNMI_MODE);    //send cmd to module sim
    putchar('\n');
    Delay(100);
    return check_sim_res();
}


/*-----------------------------------------------------------------*/
//execute command
void push_cmd(char* cmd, u8 cmd_len)
{
    u8 i;
    for( i=0; i < cmd_len; i++)
    {
        putchar(*(cmd+i));
    }
}


/*-----------------------------------------------------------------*/
//check sim res
bool check_sim_res(void)
{
  u8 i;
  for(i=MAX_BUFFER-1;i>0;i--)
    if(SIM_BUFFER[i]=='\n'){
      if(!strcmp(&SIM_BUFFER[i]-LEN_CMD_RESPOND_OK+1,sim_cmd_res_ok,LEN_CMD_RESPOND_OK)){
        i=0;
      }
      break;
    }
  if(i==0)
    return FALSE;
  else
    return TRUE;
  
}


/*-----------------------------------------------------------------*/
/* extract phone number from a sms message
 * replace ZZ with country code
 */
struct PHONEBOOK get_phone_num(char* buffer)
{
    u8 i,j;
    struct PHONEBOOK temp={"AT+CMGS=\"+ZZxxxxxxxxx\"",FALSE,FALSE};
    //get phone number
    for(i=0;i<MAX_BUFFER;i++)
        if(buffer[i]==',')
            break;
    for(j=0;j<LEN_PHONE_NUM-9;j++)
        temp.SDT[9+j]=buffer[i+j+2];
    return temp;
}
