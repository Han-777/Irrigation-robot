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
#include <string.h>
#include "bluetooth.h"
/*================message center============*/
static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;
/*==============data======================*/
static OPENMV_data_t *mv_data;
// static BLUETOOTH_data_t *bluetooth_data;
static CANCommInstance *CANComm_ins;
static Comm_Send_Data_s *comm_send_data;
static Comm_Recv_Data_s *comm_recv_data;
static ServoInstance *pitchServoMotor, *yawServoMotor;
static Drought_Info_e default_info_buff[24] = {3, 2, 3, 1, 2, 3,
                                               1, 2, 3, 1, 2, 3,
                                               1, 2, 3, 1, 2, 3,
                                               1, 2, 3, 1, 2, 3};
static Drought_Info_e drought_info_buff[24] = {0};
static uint8_t pitch_angle_index = pitch_standby_angle;
static uint16_t yaw_angle_index = yaw_standby_angle;
static uint8_t pitch_target_angle = pitch_standby_angle;
static uint16_t yaw_target_angle = yaw_standby_angle;
static uint64_t yaw_water_angle = 0;
static uint8_t water_action_idx = 0;
static int (*operation_sequence[])(water_State_e water_flag);
static int (*D_operation_sequence[])(water_State_e water_flag);
static int (*water_task_sequence[])(void);
#define max_run_itr 5
#define D_max_run_itr 4
#define water_max_run_itr 2

void WaterInit(void)
{
    mv_data = OPENMV_Init(&huart3);
    Mv_Close();
    // HAL_UART_Abort_IT(&huart2);
    // bluetooth_data = Bluetooth_Init(&huart6);

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
    send:  CANCommSend(CANComm_ins, comm_send_data);
    recv:  (Comm_Recv_Data_s *) comm_recv_data = CANCommGet(&CANComm_ins);
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
    memset(comm_recv_data, 0, sizeof(Comm_Recv_Data_s)); // debug 看看是否清0
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
static int servo_action(void)
{
    static uint8_t delay_time;
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
        // delay_time /= fabs(pitch_target_angle - pitch_angle_index);
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
        // delay_time /= fabs(yaw_target_angle - yaw_angle_index);
    }
    Servo_Motor_FreeAngle_Set(pitchServoMotor, pitch_angle_index);
    Servo_Motor_FreeAngle_Set(yawServoMotor, yaw_angle_index);
    osDelay(delay_time);
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

    if (servo_action())
    {
        if (water_flag == left_water_flag)
            yaw_target_angle = yaw_scan_left_end_angle;
        else
            yaw_target_angle = yaw_scan_right_end_angle;
        comm_send_data->plant_Cnt = water_feedback_data.plant_cnt + 1;
        // comm_send_data->recv_feedback_flag = 0;
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
    static uint8_t last_last_found = 0, last_found = 0, current_found = 0, buffer_idx = 0;
    static uint16_t last_yaw_idx = 0;
    if (yaw_angle_index == yaw_scan_left_end_angle || yaw_angle_index == yaw_scan_right_end_angle)
    {
        yaw_water_angle /= buffer_idx;
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
                yaw_water_angle += yaw_angle_index;
                ++buffer_idx;
                current_found = 1;
            }
            last_yaw_idx = yaw_angle_index;
            if (last_last_found && !last_found && !current_found)
            {
                yaw_water_angle /= buffer_idx;
                last_last_found = 0;
                last_found = 0;
                current_found = 0;
                buffer_idx = 0;
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
    if (servo_action())
    {
        return 1;
    }
    else
    {
        return 0; // 如果没有完成浇水或到达目标位置，继续执行循环
    }
}

static int relay_water_action(water_State_e water_flag)
{
    static uint8_t water_cnt = 0;

    if (water_cnt < drought_info_buff[water_feedback_data.plant_cnt])
    {
        watering_Plant;
        osDelay(50);
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
    pitch_target_angle = pitch_scan_D_angle;
    if (water_flag == left_water_flag)
    {
        yaw_target_angle = yaw_scan_left_D_angle;
    }
    else
    {
        yaw_target_angle = yaw_scan_right_D_angle;
    }
    if (servo_action())
    {
        mv_data->color = 0;
        memset(comm_recv_data, 0, sizeof(Comm_Recv_Data_s));
        comm_send_data->plant_Cnt = water_feedback_data.plant_cnt + 1;
        Mv_Open();
        return 1;
    }
    return 0;
}

static int water_D_get_info(water_State_e water_flag)
{
    static uint8_t cnt = 0;
    if ((mv_data->color == GREEN || mv_data->color == BLUE || mv_data == RED) || (cnt > 10 || (mv_data->color != GREEN && mv_data->color != BLUE && mv_data->color != RED)))
    {
        cnt = 0;
        if (mv_data->color)
        {
            drought_info_buff[water_feedback_data.plant_cnt] = mv_data->color;
        }
        comm_send_data->D_Drougnt_info = drought_info_buff[water_feedback_data.plant_cnt];
        if (water_flag == left_water_flag)
        {
            pitch_target_angle = pitch_water_D_left_angle(water_recv_data.lidar_left_dis);
        }
        else
        {
            pitch_target_angle = pitch_water_D_right_angle(water_recv_data.lidar_right_dis);
        }
        Mv_Close();
        return 1;
    }
    else
    {
        cnt++;
        osDelay(1000);
    }
    return 0;
}

static int water_standby_action(water_State_e water_flag)
{
    yaw_target_angle = yaw_standby_angle;
    pitch_target_angle = pitch_scan_angle;
    if (servo_action())
    {
        return 1;
    }
    return 0;
}

/*** @todo 待测试 */
static int Data_Check(void)
{
    if (comm_recv_data->drought_info[17] != 0)
    {
        memcpy(drought_info_buff, comm_recv_data->drought_info, sizeof(comm_recv_data->drought_info));
        return 1;
    }
    else
    {
        if (water_recv_data.water_flag != none_water_flag)
        {
            memcpy(drought_info_buff, default_info_buff, 24);
            return 1;
        }
    }
    if (water_recv_data.water_flag == none_water_flag)
    {
        if (comm_recv_data->drought_info[17] != 0)
        {
            memcpy(drought_info_buff, comm_recv_data->drought_info, sizeof(comm_recv_data->drought_info));
        }
        else
        {
            memcpy(drought_info_buff, default_info_buff, 18);
        }
        comm_send_data->recv_feedback_flag = 1;
        if (comm_recv_data->recv_feedback_flag == 1)
        {
            return 1;
        }
    }
    return 0;
    // return 1;
}

static int water_flag_handle(void)
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
            water_feedback_data.plant_cnt = 18;
            break;
        default:
            break;
        }
    }
    else if (water_recv_data.water_flag != 100)
    {
        switch (water_recv_data.region)
        {
        case A:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= max_run_itr)
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
                if (water_action_idx >= D_max_run_itr)
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
                if (water_action_idx >= D_max_run_itr)
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
    else // water_recv_data.water_flag == 100
    {
        pitch_target_angle = pitch_standby_angle;
        if (servo_action())
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

static int (*water_task_sequence[])(void) = {
    Data_Check,
    water_flag_handle};

void WaterTask(void)
{
    static uint8_t water_task_idx = 0;
    SubGetMessage(water_sub, (void *)&water_recv_data);
    comm_recv_data = (Comm_Recv_Data_s *)CANCommGet(CANComm_ins);

    if (water_task_sequence[water_task_idx]())
        water_task_idx++;
    if (water_action_idx >= water_max_run_itr)
        return;
        // water_flag_handle(); // 赋值给浇水标志位
#ifdef water
    servo_action();
#endif
    // /*** @todo: 根据处理得到的浇水标志位执行浇水动作*/
    // comm_send_data->recv_feedback_flag = 1;
    CANCommSend(CANComm_ins, (uint8_t *)comm_send_data);
    PubPushMessage(water_pub, (void *)&water_feedback_data);
}

#else

#endif