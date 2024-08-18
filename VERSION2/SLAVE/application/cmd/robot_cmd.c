#include "robot_def.h"
#include "robot_cmd.h"
// module
#include "message_center.h"
#include "bluetooth.h"
#include "general_def.h"
#include "cmsis_os.h"
// bsp
#include "bsp_dwt.h"
#include "usart.h"

static Publisher_t *chassis_cmd_pub;   // 底盘控制消息发布者
static Subscriber_t *chassis_feed_sub; // 底盘反馈信息订阅者
static Publisher_t *water_cmd_pub;     // 浇水控制消息发布者
static Subscriber_t *water_feed_sub;   // 浇水反馈信息订阅者
/*------------------------water message----------------------------*/
static Water_Ctrl_Cmd_s water_cmd_send;
static Water_Upload_Data_s water_feedback_data;

static BLUETOOTH_data_t *bluetooth_data;
void RobotCMDInit()
{
    bluetooth_data = Bluetooth_Init(&huart6);
    /*-----------------------message center-------------------------*/
    water_cmd_pub = PubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_feed_sub = SubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

/* 机器人核心控制任务,200Hz频率运行(后续可调) */
void RobotCMDTask()
{
    SubGetMessage(water_feed_sub, (void *)&water_feedback_data);

    PubPushMessage(water_cmd_pub, (void *)&water_cmd_send);
}
