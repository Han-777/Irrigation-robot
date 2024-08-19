#include "robot_def.h"
#include "robot_cmd.h"
// module
#include "message_center.h"
#include "bluetooth.h"
#include "general_def.h"
#include "cmsis_os.h"
#include "can_comm.h"

// bsp
#include "bsp_dwt.h"
#include "usart.h"
#include <string.h>
static Publisher_t *chassis_cmd_pub;   // 底盘控制消息发布者
static Subscriber_t *chassis_feed_sub; // 底盘反馈信息订阅者
static Publisher_t *water_cmd_pub;     // 浇水控制消息发布者
static Subscriber_t *water_feed_sub;   // 浇水反馈信息订阅者
/*------------------------water message----------------------------*/
static Water_Ctrl_Cmd_s water_cmd_send;
static Water_Upload_Data_s water_feedback_data;
/*==============data======================*/
static CANCommInstance *CANComm_ins;
static Comm_Send_Data_s *comm_send_data;
static Comm_Recv_Data_s *comm_recv_data;
static BLUETOOTH_data_t *bluetooth_data;
static uint8_t test[19] = {3, 2, 3, 1, 2, 3,
                           1, 2, 3, 1, 2, 3,
                           1, 2, 3, 1, 2, 3, 7};
void RobotCMDInit()
{
    bluetooth_data = Bluetooth_Init(&huart6);
    /*------------------------Can communication Init---------------------
    send:  CANCommSend(CANComm_ins, comm_send_data);
    recv:  (Comm_Recv_Data_s *) comm_recv_data = CANCommGet(&CANComm_ins);
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
    water_cmd_pub = PubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_feed_sub = SubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

static int drought_info_ready(void)
{
    static uint16_t checkCnt = 0;
    return 0;
}
/* 机器人核心控制任务,200Hz频率运行(后续可调) */
void RobotCMDTask()
{
    SubGetMessage(water_feed_sub, (void *)&water_feedback_data);
    if (bluetooth_data->drought_buff[17] != 0)
    {
        memcpy(comm_send_data->drought_info, bluetooth_data->drought_buff, 18);
    }
    comm_send_data->recv_feedback_flag = 1;
    CANCommSend(CANComm_ins, (uint8_t *)comm_send_data);
    PubPushMessage(water_cmd_pub, (void *)&water_cmd_send);
}
