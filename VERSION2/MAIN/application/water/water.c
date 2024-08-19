#include "water.h"

#ifdef water
#include "message_center.h"
#include "servo_motor.h"
#include "robot_def.h"
#include "servo_motor.h"
#include "openmv.h"
#include "usart.h"
#include "can_comm.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
/*================message center============*/
static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;
/*==============data======================*/
static OPENMV_data_t *mv_data;
static CANCommInstance *CANComm_ins;
static Comm_Send_Data_s *comm_send_data;
static Comm_Recv_Data_s *comm_recv_data;
static ServoInstance *pitchServoMotor, *yawServoMotor;
static uint8_t info_buff[18] = {3, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3};
static uint8_t plant_Cnt_record = 0; // number of setting
static uint16_t pitch_angle_index = pitch_standby_angle;
static uint16_t yaw_angle_index = yaw_standby_angle;
static uint16_t pitch_target_angle = pitch_standby_angle;
static uint16_t yaw_target_angle = yaw_standby_angle;
static uint16_t yaw_water_angle = 0;
static uint8_t water_action_idx = 0;
static int (*operation_sequence[])(water_State_e water_flag);
static int (*D_operation_sequence[])(water_State_e water_flag);
static uint8_t max_run_itr = 4;
static uint8_t D_max_run_itr = 3;
static uint16_t angle_buffer[50] = {0};
/*============================private=================================*/
static void water_flag_handle(void)
{
    if (water_recv_data.water_flag == none_water_flag)
    {
        water_feedback_data.water_finish_state = none_water_flag;
        switch (water_recv_data.set_plantCnt_flag)
        {
        case 0:
            break;
        case 6:
            water_feedback_data.plant_cnt = 6;
            break;
        case 12:
            water_feedback_data.plant_cnt = 12;
            break;
        case 18:
            water_feedback_data.plant_cnt = 24;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (water_recv_data.region)
        {
        case A:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                }
                else
                {
                    if (operation_sequence[water_action_idx](left_water_flag))
                        water_action_idx++;
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                }
                else
                {
                    if (operation_sequence[water_action_idx](right_water_flag))
                        water_action_idx++;
                }
            }
            break;
        case B:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                }
                else
                {
                    if (operation_sequence[water_action_idx](left_water_flag))
                        water_action_idx++;
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                }
                else
                {
                    if (operation_sequence[water_action_idx](right_water_flag))
                        water_action_idx++;
                }
            }
            break;
        case C:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                }
                else
                {
                    if (operation_sequence[water_action_idx](left_water_flag))
                        water_action_idx++;
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                }
                else
                {
                    if (operation_sequence[water_action_idx](right_water_flag))
                        water_action_idx++;
                }
            }
            break;
        case D:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (water_action_idx > D_max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                }
                else
                {
                    if (D_operation_sequence[water_action_idx](left_water_flag))
                        water_action_idx++;
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (water_action_idx > max_run_itr)
                {
                    water_action_idx = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                }
                else
                {
                    if (D_operation_sequence[water_action_idx](right_water_flag))
                        water_action_idx++;
                }
            }
            break;
        case home:
            break;
        default:
            break;
        }
    }
}

/*============================public=================================*/
void WaterInit(void)
{
    mv_data = OPENMV_Init(&huart3);
    /*--------------------------Servo Init------------------------------
    Servo_Motor_FreeAngle_Set
    */
    Servo_Init_Config_s servo_init_config =
        {
            .Channel = TIM_CHANNEL_1,
            .Servo_Angle_Type = Free_Angle_mode,
        };
    servo_init_config.htim = &htim13;
    servo_init_config.Servo_type = Servo270; // pitch servo
    yawServoMotor = ServoInit(&servo_init_config);
    servo_init_config.htim = &htim14;
    servo_init_config.Servo_type = Servo180; // yaw servo
    pitchServoMotor = ServoInit(&servo_init_config);
    Servo_Motor_FreeAngle_Set(yawServoMotor, yaw_standby_angle); // 上电给中值
    Servo_Motor_FreeAngle_Set(pitchServoMotor, pitch_standby_angle);
    /*------------------------Can communication Init---------------------
    send:  CANCommSend(CANComm_send_ins, comm_send_data);
    recv:  (Comm_Recv_Data_s *) comm_recv_data = CANCommGet(&comm_recv_data);
    */
    CANComm_Init_Config_s can_comm_config =
        {
            .can_config =
                {
                    .can_handle = &hfdcan2,
                    .tx_id = 0x01,
                    .rx_id = 0x02},
            .send_data_len = sizeof(Comm_Send_Data_s),
            .recv_data_len = sizeof(Comm_Recv_Data_s)};
    CANComm_ins = CANCommInit(&can_comm_config);
    /*-----------------------message center-------------------------*/
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

/*---------------relate to servo-------------------*/
/**
 * @brief 本函数仅在freertos下适用
 *
 * @param delay_time: delay通过计数器实现，不代表具体时间，需要根据实际情况修改
 * @param currentAngle: 应在函数外定义，推荐定义为static
 *
 * @return 0: 未到达， 1：到达
 */
// int servo_action(void)
// {
//     static uint16_t pitch_delay_Cnt = 0;
//     static uint16_t yaw_delay_Cnt = 0;
//     static uint16_t pitch_temp_target = 0;
//     static uint16_t yaw_temp_target = 0;
//     static uint16_t delay_time;
//     if (pitch_angle_index == pitch_target_angle && yaw_angle_index == yaw_target_angle)
//         return 1;
//     if (pitch_angle_index != pitch_target_angle)
//     {
//         if (water_action_idx == 1)
//         {
//             delay_time = fabs(pitch_target_angle - pitch_angle_index) * scan_delay_param;
//         }
//         else
//         {
//             delay_time = 15;
//         }
//         if (++pitch_delay_Cnt % delay_time == 0)
//         {
//             pitch_delay_Cnt = 0;
//             if (pitch_angle_index < pitch_target_angle)
//                 pitch_angle_index++;
//             else
//                 pitch_angle_index--;
//             Servo_Motor_FreeAngle_Set(pitchServoMotor, pitch_angle_index);
//         }
//     }
//     if (yaw_angle_index != yaw_target_angle)
//     {
//         if (water_action_idx == 1)
//         {
//             delay_time = fabs(yaw_target_angle - yaw_angle_index) * scan_delay_param;
//         }
//         else
//         {
//             delay_time = 15;
//         }
//         if (++yaw_delay_Cnt % delay_time == 0)
//         {
//             yaw_delay_Cnt = 0;
//             if (yaw_angle_index < yaw_target_angle)
//                 yaw_angle_index++;
//             else
//                 yaw_angle_index--;
//             Servo_Motor_FreeAngle_Set(yawServoMotor, yaw_angle_index);
//         }
//     }
//     return 0;
// }

int servo_action(void)
{
    static uint16_t delay_time;
    if (pitch_angle_index == pitch_target_angle && yaw_angle_index == yaw_target_angle)
        return 1;
    if (pitch_angle_index != pitch_target_angle)
    {
        if (water_action_idx == 1)
        {
            delay_time = scan_delay_time;
        }
        else
        {
            delay_time = water_delay_time;
        }
        if (pitch_angle_index < pitch_target_angle)
            pitch_angle_index++;
        else
            pitch_angle_index--;
        Servo_Motor_FreeAngle_Set(pitchServoMotor, pitch_angle_index);
        // delay_time /= fabs(pitch_target_angle - pitch_angle_index);
        osDelay(delay_time);
    }
    if (yaw_angle_index != yaw_target_angle)
    {
        if (water_action_idx == 1)
        {
            delay_time = scan_delay_time;
        }
        else
        {
            delay_time = water_delay_time;
        }

        if (yaw_angle_index < yaw_target_angle)
            yaw_angle_index++;
        else
            yaw_angle_index--;
        Servo_Motor_FreeAngle_Set(yawServoMotor, yaw_angle_index);
        // delay_time /= fabs(yaw_target_angle - yaw_angle_index);
        osDelay(delay_time);
    }
    return 0;
}

/**
 * @brief pitch和yaw舵机分别到达指定位置
 *
 * @return 0: 未到达， 1：到达
 */
static int servo_scan_ready(water_State_e water_flag)
{
    pitch_target_angle = pitch_scan_angle;
    if (water_flag == left_water_flag)
        yaw_target_angle = yaw_scan_left_begin_angle;
    else
        yaw_target_angle = yaw_scan_right_begin_angle;

    if (pitch_angle_index == pitch_target_angle && yaw_angle_index == yaw_target_angle)
    {
        if (water_flag == left_water_flag)
            yaw_target_angle = yaw_scan_left_end_angle;
        else
            yaw_target_angle = yaw_scan_right_end_angle;
        return 1;
    }
    return 0;
}

/**
 * @brief yaw找到浇水角度
 *
 * @return 0: 未到达， 1：到达
 */
static int servo_water_ready(water_State_e water_flag)
{
    static uint16_t last_last_found = 0, last_found = 0, current_found = 0, buffer_idx = 0;

    static uint8_t cal_idx = 0;
    static uint16_t last_yaw_idx = 0;
    if (yaw_angle_index == yaw_scan_left_end_angle || yaw_angle_index == yaw_scan_right_end_angle)
    {
        return 1;
    }
    else // 不到位
    {
        if (last_yaw_idx != yaw_angle_index)
        {
            last_last_found = last_found;
            last_found = current_found;
            current_found = 0;
            if (!No_Plant) // 检测到植物(每一度记一次)
            {
                angle_buffer[buffer_idx] = yaw_angle_index;
                ++buffer_idx;
                current_found = 1;
            }
            last_yaw_idx = yaw_angle_index;
            if (last_last_found && !last_found && !current_found)
            {
                for (; cal_idx < buffer_idx; ++cal_idx) // TOD：可能会占用cpu资源导致卡住
                {
                    yaw_water_angle += angle_buffer[cal_idx];
                }
                yaw_water_angle /= buffer_idx;
                last_last_found = 0;
                last_found = 0;
                current_found = 0;
                buffer_idx = 0;
                cal_idx = 0;
                return 1;
            }
        }
    }
    return 0;
}

static int servo_water_action(water_State_e water_flag)
{
    if (water_flag == left_water_flag)
        pitch_target_angle = pitch_water_left_angle(water_recv_data.lidar_left_dis);
    else
        pitch_target_angle = pitch_water_right_angle(water_recv_data.lidar_right_dis);
    pitch_target_angle = (pitch_target_angle < pitch_water_min) ? pitch_water_min : pitch_target_angle;
    if (yaw_water_angle != 0)
    {
        yaw_target_angle = yaw_water_angle;
        yaw_water_angle = 0;
    }

    // 检查是否到达目标位置
    if (yaw_angle_index == yaw_target_angle && pitch_angle_index == pitch_target_angle)
    {
        memset(angle_buffer, 0, sizeof(angle_buffer));
        return 1;
    }

    return 0; // 如果没有完成浇水或到达目标位置，继续执行循环
}

static int relay_water_action(water_State_e water_flag)
{
    // static uint16_t delay_Cnt = 0, stop_Cnt = 0;
    static uint8_t water_cnt = 0;
    // if (water_cnt < info_buff[water_feedback_data.plant_cnt])
    // {
    //     if (++delay_Cnt < 100)
    //     {
    //         watering_Plant;
    //     }
    //     else if (delay_Cnt == 800)
    //     {
    //         delay_Cnt = 0;
    //         water_cnt++;
    //     }
    //     else
    //     {
    //         if (delay_Cnt > 800)
    //         {
    //             delay_Cnt = 0;
    //         }
    //         stop_watering_Plant;
    //     }
    //     return 0;
    // }
    // else
    // { // water_cnt 已经达到植物数量
    //     stop_watering_Plant;
    //     // if (++stop_Cnt > 400)
    //     // {
    //     stop_Cnt = 0;
    //     delay_Cnt = 0;
    //     water_cnt = 0; // 重置浇水计数器
    //     return 1;      // 完成浇水，返回 1
    //     // }
    // }
    if (water_cnt < info_buff[water_feedback_data.plant_cnt])
    {
        watering_Plant;
        osDelay(100);
        stop_watering_Plant;
        osDelay(800);
        water_cnt++;
    }
    else
    {
        stop_watering_Plant;
        water_cnt = 0;
        return 1;
    }
    return 0;
}
static int water_D_scan_action(water_State_e water_flag)
{
    if (water_flag == left_water_flag)
        yaw_target_angle = yaw_scan_left_D_angle;
    else
        yaw_target_angle = yaw_scan_right_D_angle;
    if (yaw_angle_index == yaw_target_angle && pitch_angle_index == pitch_target_angle)
        return 1;
    return 0;
}

static int water_D_get_info(water_State_e water_flag)
{
    static uint16_t cnt = 0;
    if (++cnt % 1000 == 0)
    {
        return 1;
    }
    return 0;
}

static int water_display_finish(void)
{
    comm_recv_data = CANCommGet(CANComm_ins);
    if (comm_recv_data->recv_feedback_flag == 1)
    {
        return 1;
    }
    return 0;
}

static int water_standby_action(void)
{
    yaw_target_angle = yaw_standby_angle;
    pitch_target_angle = pitch_scan_angle;
    if (servo_action())
    {
        return 1;
    }
    return 0;
}
/*----------------------relate to task-------------------------*/
static int (*operation_sequence[])(water_State_e water_flag) = {
    servo_scan_ready,
    servo_water_ready,
    servo_water_action,
    relay_water_action,
    water_standby_action};

static int (*D_operation_sequence[])(water_State_e water_flag) = {
    water_D_scan_action,
    water_D_get_info,
    relay_water_action,
    water_standby_action};
void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    water_flag_handle(); // 赋值给浇水标志位
#ifdef water
    servo_action();
#endif
    // /*** @todo: 根据处理得到的浇水标志位执行浇水动作*/
    // comm_recv_data = CANCommGet(&comm_recv_data);
    PubPushMessage(water_pub, (void *)&water_feedback_data);
}

#else

#include "mp3.h"
// #include "water.h"
#include "message_center.h"
#include "servo_motor.h"
#include "photoelectric.h"
#include "robot_def.h"
#include "servo_motor.h"

static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;

// static ServoInstance *pitchServoMotor, *yawServoMotor;
static uint8_t info_buff[18] = {1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3};
static uint8_t plant_Cnt_record = 0; // number of setting
void WaterInit(void)
{
    MP3_Init();
    // 舵机初始化
    // ServoInstance servo_init_config;
    // servo_init_config.Channel = TIM_CHANNEL_1;
    // servo_init_config.Servo_Angle_Type = Start_mode;
    // servo_init_config.Servo_type = Servo270;
    // servo_init_config.htim = &htim13;
    // pitchServoMotor = ServoInit(&servo_init_config);
    // servo_init_config.htim = &htim14;
    // pitchServoMotor = ServoInit(&servo_init_config);
    // Servo_Init_Config_s *config = (Servo_Init_Config_s
    // ServoInit();
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

void water_flag_handle(void)
{
    static uint8_t cnt = 0;
    // if (water_feedback_data.water_finish_state != water_finish_flag && water_recv_data.water_flag != none_water_flag)
    // {
    //     if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
    //     {
    //         // 左边浇水过程
    //         if (++cnt % 2000 == 0)
    //         {
    //             cnt = 0;
    //             water_feedback_data.water_finish_state |= left_water_flag;
    //             // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
    //         }
    //     }
    //     else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
    //     {
    //         // 右边浇水
    //         if (++cnt % 2000 == 0)
    //         {
    //             cnt = 0;
    //             water_feedback_data.water_finish_state |= right_water_flag;
    //             // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
    //         }
    //     }
    //     if (water_feedback_data.water_finish_state == water_finish_flag)
    //     {
    //         water_feedback_data.plant_cnt++;
    //         water_feedback_data.water_finish_state = none_water_flag;
    //     }
    // }
    // else
    // {
    //     switch (plant_Cnt_record)
    //     {
    //     case 0:
    //         if (water_recv_data.set_plantCnt_flag == 6)
    //         {
    //             plant_Cnt_record = 1;
    //             water_feedback_data.plant_cnt = 6;
    //         }
    //         break;
    //     case 1:
    //         if (water_recv_data.set_plantCnt_flag == 12)
    //         {
    //             plant_Cnt_record = 2;
    //             water_feedback_data.plant_cnt = 12;
    //         }
    //         break;
    //     case 2:
    //         if (water_recv_data.set_plantCnt_flag == 18)
    //         {
    //             plant_Cnt_record = 3;
    //             water_feedback_data.plant_cnt = 18;
    //         }
    //         break;
    //     default:
    //         break;
    //     }
    // }
    if (water_recv_data.water_flag == none_water_flag)
    {
        water_feedback_data.water_finish_state = none_water_flag;
        switch (water_recv_data.set_plantCnt_flag)
        {
        case 0:
            // if (water_recv_data.set_plantCnt_flag == 6)
            // {
            //     plant_Cnt_record = 1;
            //     water_feedback_data.plant_cnt = 6;
            // }
            break;
        case 6:
            // plant_Cnt_record = 2;
            water_feedback_data.plant_cnt = 6;
            break;
        case 12:
            // plant_Cnt_record = 3;
            water_feedback_data.plant_cnt = 12;
            break;
        case 18:
            // plant_Cnt_record = 3;
            water_feedback_data.plant_cnt = 24;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (water_recv_data.region)
        {
        case A:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
        case B:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            // if (water_feedback_data.water_finish_state == water_finish_flag && water_recv_data.water_flag == none_water_flag)
            // {
            //     water_feedback_data.plant_cnt++;
            // }
            break;
        case C:
        case D:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    water_feedback_data.plant_cnt++;

                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;

                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            break;
        }
    }
}

void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    water_flag_handle();

    PubPushMessage(water_pub, (void *)&water_feedback_data);
}
#endif