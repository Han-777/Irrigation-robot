// app
#include "robot_def.h"
#include "robot_cmd.h"
// module
#include "lidar.h"
#include "gray.h"
#include "openmv.h"
#include "gray.h"
#include "photoelectric.h"
#include "message_center.h"
#include "general_def.h"
// bsp
#include "bsp_dwt.h"
#include "usart.h"
#ifdef ONE_BOARD
static Publisher_t *chassis_cmd_pub;   // 底盘控制消息发布者
static Subscriber_t *chassis_feed_sub; // 底盘反馈信息订阅者
#endif

static Chassis_Ctrl_Cmd_s chassis_cmd_send; // 发送给底盘应用的信息,包括陀螺仪信息和灰度转弯信息

static LD_data_t *ld_data;
static uint8_t *gray_cnt;
static OPENMV_data_t *openmv_data;
static uint8_t *pe_state;
void RobotCMDInit()
{
    ld_data = Lidar_Init(&huart2);
    ld_data = Lidar_Init(&huart4);
    // openmv_data = OPENMV_Init(&huart3);
    pe_state = PE_Init(LEFT_PE_Pin);
    pe_state = PE_Init(RIGHT_PE_Pin);
    chassis_cmd_pub = PubRegister("chassis_cmd", sizeof(Chassis_Ctrl_Cmd_s)); // 注册发布星系
    chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE;                       // 启动时机器人进入工作模式,后续加入所有应用初始化完成之后再进入
}

static void HeadingTrans()
{
}

static void CmdInfoHandle(void)
{
}

/* 机器人核心控制任务,200Hz频率运行(后续可调) */
void RobotCMDTask()
{
    // if water flag -> speed = 0
}
