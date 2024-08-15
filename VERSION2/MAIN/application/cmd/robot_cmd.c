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
#include "bluetooth.h"
#include "cmsis_os.h"
// bsp
#include "bsp_dwt.h"
#include "usart.h"
#ifdef ONE_BOARD
static Publisher_t *chassis_cmd_pub;   // 底盘控制消息发布者
static Subscriber_t *chassis_feed_sub; // 底盘反馈信息订阅者
static Publisher_t *water_cmd_pub;     // 浇水控制消息发布者
static Subscriber_t *water_feed_sub;   // 浇水反馈信息订阅者
#endif
/*------------------------chassis message----------------------------F*/
static Chassis_Ctrl_Cmd_s chassis_cmd_send;      // 发送给底盘应用的信息,包括陀螺仪信息和灰度转弯信息
static Chassis_Upload_Data_s chassis_fetch_data; // 从底盘应用接收的反馈信息信息,底盘功率枪口热量与底盘运动状态等
/*------------------------water message----------------------------F*/
static Water_Ctrl_Cmd_s water_cmd_send;
static Water_Upload_Data_s water_feedback_data; //

static LD_data_t *ld_data;
#define LD_DIS_THRESHOLD 30
static OPENMV_data_t *openmv_data;
static uint8_t *pe_state;
static uint8_t cross_cnt;
static uint8_t itr = 0;
/*------------------water cmd handle---------------------*/
/**
 * @brief 针对光电传感器的数据和浇水状态的反馈数据给出对应的浇水、运动命令
 *
 */
static int waterFlagHandle(void)
{
    /*--------------浇水任务完成，清除标志位-------------------*/
    // if (water_feedback_data.water_finish_state & left_water_finish)
    // {
    //     *pe_state &= ~LEFT_PE_FLAG; //
    // }
    // else if (water_feedback_data.water_finish_state & right_water_finish)
    // {
    //     *pe_state &= ~RIGHT_PE_FLAG; //
    // }
    // water_cmd_send.water_flag |= *pe_state;
    // *pe_state &= ~water_feedback_data.water_finish_state;
    // water_cmd_send.water_flag |= *pe_state;

    /*============================================*/
    // static uint8_t pe_Cnt = 0;
    // if (++pe_Cnt % 5 == 0)
    // {
    switch (water_cmd_send.region)
    {
    case A:
        chassis_cmd_send.speed = A_speed;
        if ((*pe_state & LEFT_PE_FLAG) && (ld_data->lld_distance < LD_DIS_THRESHOLD - 5))
        // if ((*pe_state & LEFT_PE_FLAG))
        {
            if (ld_data->lld_distance < LD_DIS_A_MIN_THRESHOLD)
            {
                chassis_cmd_send.lidar_com_speed = (LD_DIS_A_MIN_THRESHOLD - ld_data->lld_distance) * COM_PARAMETER;
            }
            else if (ld_data->lld_distance > LD_DIS_A_MAX_THRESHOLD)
            {
                chassis_cmd_send.lidar_com_speed = (LD_DIS_A_MAX_THRESHOLD - ld_data->lld_distance) * COM_PARAMETER;
            }
            water_cmd_send.water_flag = pair_water_flag; // A 看左浇两边
            // chassis_cmd_send.lidar_com_speed = 0;
            *pe_state &= NONE_PE_FLAG;
            return 1;
        }
        if (water_cmd_send.water_flag == pair_water_flag && water_feedback_data.water_finish_state != water_finish_flag) // 浇水中
            return 1;
        else if (water_feedback_data.water_finish_state == water_finish_flag) // 浇水完成
        {
            water_cmd_send.water_flag &= none_water_flag;
            return 0;
        }
        break;
    case B:
        chassis_cmd_send.speed = BD_speed;
        if ((*pe_state & RIGHT_PE_FLAG) && (ld_data->rld_distance < LD_DIS_THRESHOLD + 10))
        // if ((*pe_state & LEFT_PE_FLAG))
        {
            if (ld_data->rld_distance < LD_DIS_B_MIN_THRESHOLD)
            {
                chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_B_MIN_THRESHOLD) * COM_PARAMETER;
            }
            else if (ld_data->rld_distance > LD_DIS_B_MAX_THRESHOLD)
            {
                chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_B_MAX_THRESHOLD) * COM_PARAMETER;
            }
            water_cmd_send.water_flag = pair_water_flag; // B 看右浇两边
            *pe_state &= NONE_PE_FLAG;
            return 1;
        }
        if (water_cmd_send.water_flag == pair_water_flag && water_feedback_data.water_finish_state != water_finish_flag) // 浇水中
            return 1;
        else if (water_feedback_data.water_finish_state == water_finish_flag) // 浇水完成
        {
            water_cmd_send.water_flag &= none_water_flag;
            return 0;
        }
        break;
    case C:
        chassis_cmd_send.speed = C_speed;
        if ((*pe_state & LEFT_PE_FLAG && ld_data->lld_distance < LD_DIS_THRESHOLD + 12) || (*pe_state & RIGHT_PE_FLAG && ld_data->rld_distance < LD_DIS_THRESHOLD + 12))
        {
            if (*pe_state & LEFT_PE_FLAG)
            {
                if (ld_data->lld_distance < LD_DIS_C_MIN_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (LD_DIS_C_MIN_THRESHOLD - ld_data->lld_distance) * COM_C_PARAMETER;
                }
                else if (ld_data->lld_distance > LD_DIS_C_MAX_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (LD_DIS_C_MAX_THRESHOLD - ld_data->lld_distance) * COM_C_PARAMETER;
                }
                if (ld_data->lld_distance < LD_DIS_THRESHOLD + 12)
                {
                    water_cmd_send.water_flag |= left_water_flag;
                    *pe_state &= ~LEFT_PE_FLAG;
                    return 1;
                }
            }
            if (*pe_state & RIGHT_PE_FLAG)
            {
                if (ld_data->rld_distance < LD_DIS_C_MIN_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_C_MIN_THRESHOLD) * COM_C_PARAMETER;
                }
                else if (ld_data->rld_distance > LD_DIS_C_MAX_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_C_MAX_THRESHOLD) * COM_C_PARAMETER;
                }
                if (ld_data->rld_distance < LD_DIS_THRESHOLD + 10)
                {
                    water_cmd_send.water_flag |= right_water_flag;
                    *pe_state &= ~RIGHT_PE_FLAG;
                    return 1;
                }
            }
            // *pe_state &= NONE_PE_FLAG;
        }
        if ((water_cmd_send.water_flag & LEFT_PE_FLAG && !(water_feedback_data.water_finish_state & left_water_flag)) || (water_cmd_send.water_flag & RIGHT_PE_FLAG && !(water_feedback_data.water_finish_state & right_water_flag)))
            return 1;
        else if (water_feedback_data.water_finish_state == water_finish_flag)
        {
            water_cmd_send.water_flag &= none_water_flag;
        }
        return 0;
        break;
    case D:
        chassis_cmd_send.speed = BD_speed;
        if ((*pe_state & LEFT_PE_FLAG && ld_data->lld_distance < LD_DIS_THRESHOLD) || (*pe_state & RIGHT_PE_FLAG && ld_data->rld_distance < LD_DIS_THRESHOLD))
        {
            if (*pe_state & LEFT_PE_FLAG)
            {
                if (ld_data->lld_distance < LD_DIS_D_MIN_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (LD_DIS_D_MIN_THRESHOLD - ld_data->lld_distance) * COM_PARAMETER;
                }
                else if (ld_data->lld_distance > LD_DIS_D_MAX_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (LD_DIS_D_MAX_THRESHOLD - ld_data->lld_distance) * COM_PARAMETER;
                }
                if (ld_data->lld_distance < LD_DIS_THRESHOLD)
                {
                    water_cmd_send.water_flag |= left_water_flag;
                    *pe_state &= ~LEFT_PE_FLAG;
                    return 1;
                }
            }
            else
            {
                if (ld_data->rld_distance < LD_DIS_D_MIN_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_D_MIN_THRESHOLD) * COM_PARAMETER;
                }
                else if (ld_data->rld_distance > LD_DIS_D_MAX_THRESHOLD)
                {
                    chassis_cmd_send.lidar_com_speed = (ld_data->rld_distance - LD_DIS_D_MAX_THRESHOLD) * COM_PARAMETER;
                }
                if (ld_data->rld_distance < LD_DIS_THRESHOLD + 5)
                {
                    water_cmd_send.water_flag |= right_water_flag;
                    *pe_state &= ~RIGHT_PE_FLAG;
                    return 1;
                }
            }
            // water_cmd_send.water_flag |= *pe_state; // |= 应该也同时处理了浇两边的情况
            // *pe_state &= NONE_PE_FLAG;
        }
        if ((water_cmd_send.water_flag & left_water_flag && !(water_feedback_data.water_finish_state & left_water_flag)) || (water_cmd_send.water_flag & RIGHT_PE_FLAG && !(water_feedback_data.water_finish_state & right_water_flag)))
            return 1;
        else if (water_feedback_data.water_finish_state == water_finish_flag)
        {
            water_cmd_send.water_flag &= none_water_flag;
            return 0;
        }
        break;
    }
    return 0;
}

static int region_finish(void)
{
    water_cmd_send.region = (cross_cnt < 2) ? A : ((cross_cnt < 4) ? B : ((cross_cnt < 6) ? C : D));
    if (((water_feedback_data.plant_cnt >= 6 && water_feedback_data.plant_cnt < 9) && water_cmd_send.region == A) || ((water_feedback_data.plant_cnt >= 12 && water_feedback_data.plant_cnt < 17) && water_cmd_send.region == B) || (water_feedback_data.plant_cnt >= 18 && water_cmd_send.region == C) || (water_feedback_data.plant_cnt >= 28 && water_cmd_send.region == D)) // 21 in total
    {
        water_cmd_send.set_plantCnt_flag = (water_cmd_send.region == A) ? 6 : ((water_cmd_send.region == B) ? 12 : 18);
        return 1; // 2/4/6 -> 0
    }
    return 0;
}

static int get_cross_flag(void)
{
    if (get_gray())
    {
        cross_cnt++;
        if (cross_cnt == 1 || cross_cnt == 2 || cross_cnt == 5 || cross_cnt == 6)
        {
            chassis_cmd_send.clockwise_rotate_flag += 1;
        }
        else if (cross_cnt == 3 || cross_cnt == 4)
        {
            chassis_cmd_send.clockwise_rotate_flag -= 1;
        }
        return 1;
    }
    return 0;
}

static int data_check(void)
{
    static uint8_t bluetooth_recv_flag = 1; // 后面放到bluetooth中(maybe?)
    return bluetooth_recv_flag;
}

static int _run_(void)
{
    if (region_finish() && get_cross_flag())
    {
        chassis_cmd_send.chassis_mode = CHASSIS_ROTATE; //
        return 1;
    }
    else
    {
        if (waterFlagHandle())
        {
            chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE;
        }
        else
        {
            // chassis_cmd_send.lidar_com_speed = 0;
            chassis_cmd_send.chassis_mode = CHASSIS_FORWARD;
        }
        return 0;
    }
}

static int cross_action(void)
{
    chassis_cmd_send.chassis_mode = CHASSIS_ROTATE;
    water_cmd_send.set_plantCnt_flag = 0; // 不干扰标志位
    water_cmd_send.water_flag = none_water_flag;
    *pe_state = none_water_flag;
    if (chassis_fetch_data.rotate_arrive) // 可能条件不够多
    {
        if (cross_cnt % 2 == 0) // even cross open
        {
            *pe_state &= none_water_flag;
        }
        chassis_cmd_send.chassis_mode = CHASSIS_FORWARD;
        chassis_cmd_send.lidar_com_speed = 0;
        return 1;
    }
    return 0;
}

static int cross_to_cross(void)
{
    static uint8_t forward_cnt = 0;
    chassis_cmd_send.lidar_com_speed = 0;
    chassis_cmd_send.chassis_mode = CHASSIS_C2C;
    chassis_cmd_send.speed = 8000;
    if (++forward_cnt % 1000 == 0)
    {
        forward_cnt = 999;
        chassis_cmd_send.lidar_com_speed = 0;
        chassis_cmd_send.chassis_mode = CHASSIS_FORWARD;
        if (get_cross_flag())
        {
            forward_cnt = 0;
            return 1;
        }
    }
    return 0;
}

static int end_return_home(void)
{
    static uint8_t forward_cnt = 0;
    if (++forward_cnt % 25 == 0)
    {
        forward_cnt = 24;
        chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE;
        return 1;
    }
    chassis_cmd_send.chassis_mode = CHASSIS_FORWARD;
    return 0;
}

static int stop(void)
{
    chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE;
    return 0;
}
static int (*operation_sequence[])(void) = {
    data_check,
    _run_, cross_action, cross_to_cross, cross_action, // A
    _run_, cross_action, cross_to_cross, cross_action, // B
    _run_, cross_action, cross_to_cross, cross_action, // C
    _run_,                                             // D
    end_return_home};                                  // D finish and go home
static uint8_t max_run_itr = 16;
/*====================================================================*/
void RobotCMDInit()
{
    ld_data = Lidar_Init(&huart2);
    ld_data = Lidar_Init(&huart4);
    // openmv_data = OPENMV_Init(&huart3);
    pe_state = PE_Init(LEFT_PE_Pin);
    pe_state = PE_Init(RIGHT_PE_Pin);
    *pe_state = NONE_PE_FLAG;
    chassis_cmd_pub = PubRegister("chassis_cmd", sizeof(Chassis_Ctrl_Cmd_s)); // 注册发布
    chassis_feed_sub = SubRegister("chassis_feed", sizeof(Chassis_Upload_Data_s));
    water_cmd_pub = PubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s)); //
    water_feed_sub = SubRegister("water_feed", sizeof(Water_Upload_Data_s));
    chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE; // 启动时机器人进入工作模式,后续加入所有应用初始化完成之后再进入
    // chassis_cmd_send.pe_state = pe_state;
    water_cmd_send.region = home;
}

/* 机器人核心控制任务,200Hz频率运行(后续可调) */
void RobotCMDTask()
{
// 获取最新数据
#ifdef ONE_BOARD
    SubGetMessage(chassis_feed_sub, (void *)&chassis_fetch_data); // chassis 反馈数据
    SubGetMessage(water_feed_sub, (void *)&water_feedback_data);  // water
#endif
    if (operation_sequence[itr]())
        itr++;
    if (itr >= max_run_itr)
    {
        chassis_cmd_send.chassis_mode = CHASSIS_ZERO_FORCE;
    }
#ifdef ONE_BOARD
    PubPushMessage(chassis_cmd_pub, (void *)&chassis_cmd_send);
    PubPushMessage(water_cmd_pub, (void *)&water_cmd_send);
#endif // ONE_BOARD
}
