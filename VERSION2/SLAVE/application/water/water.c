#include "water.h"
#include "robot_def.h"
#include "can_comm.h"
#include "message_center.h"
#include "usart.h"
#include "mp3.h"
/*================message center============*/
static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;
/*==============data======================*/
static CANCommInstance *CANComm_ins;
static Comm_Send_Data_s *comm_send_data;
static Comm_Recv_Data_s *comm_recv_data;
void WaterInit(void)
{
    MP3_Init(&huart5);
    /*------------------------Can communication Init---------------------
send:  CANCommSend(CANComm_send_ins, comm_send_data);
recv:  (Comm_Recv_Data_s *) comm_recv_data = CANCommGet(&comm_recv_data);
*/
    CANComm_Init_Config_s can_comm_config =
        {
            .can_config =
                {
                    .can_handle = &hfdcan1,
                    .tx_id = 0x02,
                    .rx_id = 0x01},
            .send_data_len = sizeof(Comm_Send_Data_s),
            .recv_data_len = sizeof(Comm_Recv_Data_s)};
    CANComm_ins = CANCommInit(&can_comm_config);
    /*-----------------------message center-------------------------*/
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    LCD_hanqing(GENERAL, 1);
    LCD_hanqing(SLIGHT, 8);
    LCD_hanqing(SERIOUS, 17);

    PubPushMessage(water_pub, (void *)&water_feedback_data);
}