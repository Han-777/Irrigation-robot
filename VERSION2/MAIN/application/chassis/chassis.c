/**
 * @file chassis.c
 * @author NeoZeng neozng1@hnu.edu.cn
 * @brief 底盘应用,负责接收robot_cmd的控制命令并根据命令进行运动学解算,得到输出
 *        注意底盘采取右手系,对于平面视图,底盘纵向运动的正前方为x正方向;横向运动的右侧为y正方向
 *
 * @version 0.1
 * @date 2022-12-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "chassis.h"
#include "gyro.h"
#include "robot_def.h"
#include "DJI_motor.h"
#include "message_center.h"
#include "general_def.h"
#include "bsp_dwt.h"
#include "usart.h"
#include "math.h"
// #include "gray.h"
// #include "robot_cmd.h"
static GYRO_data_t *gyro_data;
static DJIMotorInstance *motor_lf, *motor_rf, *motor_lb, *motor_rb; // left right forward back
#ifdef ONE_BOARD
static Subscriber_t *chassis_sub;
static Publisher_t *chassis_pub;
#endif
static Chassis_Ctrl_Cmd_s chassis_cmd_recv;         // 底盘接收到的控制命令
static Chassis_Upload_Data_s chassis_feedback_data; // 底盘回传的反馈数据
static uint8_t cross_forward_flag = 0;              // 防止误触
/* 私有函数计算的中介变量,设为静态避免参数传递的开销 */
static float left_target_vt, right_target_vt; // 左边速度一样，右边速度一样
static PIDInstance angle_instance;

void ChassisInit() // 配置中所有pid参数都需要修改
{
    /*  最外层角度环参数   */
    PID_Init_Config_s pid_init_config =
        {
            .Kp = 50, // 200
            .Ki = 16, // 200
            .Kd = 10, // 100
            .IntegralLimit = 250,
            .Improve = PID_Trapezoid_Intergral | PID_Integral_Limit | PID_Derivative_On_Measurement,
            .MaxOut = 2500, // 待测
        };
    // PIDInit(&angle_instance, &pid_init_config);
    PIDInit(&angle_instance, &pid_init_config);
    /*  gyro init    */
    gyro_data = Gyro_Init(&huart5); // 改到初始化之前
    /*  motor init  */
    //
    Motor_Init_Config_s chassis_motor_config =
        {
            .can_init_config.can_handle = &hfdcan1, // can 选择
            .motor_type = M3508,                    // 电机类型
            .controller_setting_init_config =       // 内外环选择
            {
                .angle_feedback_source = MOTOR_FEED,
                .speed_feedback_source = MOTOR_FEED,
                .outer_loop_type = SPEED_LOOP,
                .close_loop_type = SPEED_LOOP | CURRENT_LOOP, // 速度环+电流环
            },
            .controller_param_init_config = // 内外环pid参数选择
            {
                .speed_PID =
                    {
                        .Kp = 2,   //
                        .Ki = 0.5, // 0
                        .Kd = 0,   // 0
                        .IntegralLimit = 3000,
                        .Improve = PID_Trapezoid_Intergral | PID_Integral_Limit | PID_Derivative_On_Measurement,
                        .MaxOut = 15000, // 待测
                    },
                .current_PID =
                    {
                        .Kp = 1,
                        .Ki = 2.5, // 0
                        .Kd = 0,
                        .IntegralLimit = 3000,
                        .Improve = PID_Trapezoid_Intergral | PID_Integral_Limit | PID_Derivative_On_Measurement,
                        .MaxOut = 12000, // 1200
                    },

            },
        };
    chassis_motor_config.can_init_config.tx_id = 1;
    chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_NORMAL; // 正反后面调
    motor_lf = DJIMotorInit(&chassis_motor_config);

    chassis_motor_config.can_init_config.tx_id = 2;
    chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE; // 正反后面调
    motor_rf = DJIMotorInit(&chassis_motor_config);

    chassis_motor_config.can_init_config.tx_id = 4;
    chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_NORMAL; // 正反后面调
    motor_lb = DJIMotorInit(&chassis_motor_config);

    chassis_motor_config.can_init_config.tx_id = 3;
    chassis_motor_config.controller_setting_init_config.motor_reverse_flag = MOTOR_DIRECTION_REVERSE; // 正反后面调
    motor_rb = DJIMotorInit(&chassis_motor_config);

#ifdef ONE_BOARD
    chassis_sub = SubRegister("chassis_cmd", sizeof(Chassis_Ctrl_Cmd_s));
    chassis_pub = PubRegister("chassis_feed", sizeof(Chassis_Upload_Data_s));
#endif
}

/**
 * @brief 根据踩过的cross数量得到需要的目标角度
 *
 * @attention 调用该函数前应该先对gyro数据进行处理，确保最新数据
 * @note 考虑直接创建一个task专门处理
 * gyro_data->target_yaw : target yaw / ref
 * gyro_data->Yaw : current_yaw / measure
 *
 */
static void HeadingTransfer(void)
{
    gyro_data->target_yaw = gyro_data->ori_yaw + 90 * chassis_cmd_recv.clockwise_rotate_flag;
    while (gyro_data->target_yaw > 360)
    {
        gyro_data->target_yaw -= 360;
    }
    while (gyro_data->target_yaw < -360)
    {
        gyro_data->target_yaw += 360;
    }
    // handling the difference
    if (fabs(gyro_data->target_yaw - gyro_data->Yaw) > 180)
    {
        gyro_data->cal_yaw += ((gyro_data->target_yaw > gyro_data->Yaw) ? 360 : -360);
    }
    else
    {
        gyro_data->cal_yaw = gyro_data->Yaw;
    }
}

static void check_arrive(void)
{
    static uint8_t stableCnt = 0;
    if (fabs(angle_instance.Err) < 0.5)
    {
        if (++stableCnt % 50 == 0)
        {
            stableCnt = 0;
            chassis_feedback_data.rotate_arrive = 1;
        }
    }
    else
        chassis_feedback_data.rotate_arrive = 0;

    if (fabs(angle_instance.Err) < 1)
        chassis_feedback_data.rotate_vague_arrive = 1;
    else
        chassis_feedback_data.rotate_vague_arrive = 0;
}

static void SpeedCalculate()
{
    HeadingTransfer();
    PIDCalculate(&angle_instance, gyro_data->cal_yaw, gyro_data->target_yaw);
    if (chassis_cmd_recv.chassis_mode != CHASSIS_ROTATE && chassis_cmd_recv.lidar_com_speed != 0)
    {

        if (fabs(chassis_cmd_recv.lidar_com_speed) > 3000 && angle_instance.Err > 45)
        {
            chassis_cmd_recv.lidar_com_speed = (chassis_cmd_recv.lidar_com_speed > 0) ? 3000 : -3000;
            left_target_vt += chassis_cmd_recv.lidar_com_speed;
            right_target_vt -= chassis_cmd_recv.lidar_com_speed;
        }
        else
        {
            left_target_vt += chassis_cmd_recv.lidar_com_speed;
            right_target_vt -= chassis_cmd_recv.lidar_com_speed;
        }
        if (fabs(gyro_data->Roll - gyro_data->ori_roll) > 0.5)
        {
            left_target_vt += 1000;
            right_target_vt += 1000;
            angle_instance.Output *= 8;
        }
        else
        {
            angle_instance.Output *= 5;
        }
        left_target_vt += angle_instance.Output;  // 系数后面测
        right_target_vt -= angle_instance.Output; // 系数后面测
    }
    else
    {
        // if (chassis_cmd_recv.chassis_mode == CHASSIS_C2C)
        // {
        //     angle_instance.Output *= 8;
        //     left_target_vt += angle_instance.Output;
        //     right_target_vt -= angle_instance.Output;
        //     return;
        // }
        angle_instance.Output *= 8;
        left_target_vt += angle_instance.Output;
        right_target_vt -= angle_instance.Output;
    }
}

/**
 * @brief 根据裁判系统和电容剩余容量对输出进行限制并设置电机参考值
 *
 */
static void SetChassisOutput()
{
    DJIMotorSetRef(motor_lf, left_target_vt);
    DJIMotorSetRef(motor_lb, left_target_vt);

    DJIMotorSetRef(motor_rf, right_target_vt);
    DJIMotorSetRef(motor_rb, right_target_vt);
}

/* 机器人底盘控制核心任务 */
void ChassisTask()
{
    // 获取新的控制信息
#ifdef ONE_BOARD
    SubGetMessage(chassis_sub, (void *)&chassis_cmd_recv);
#endif
    // if(chassis_cmd_recv.gray){
    //     if (chassis_cmd_recv.chassis_mode != CHASSIS_ROTATE) {
    //         // 设置为旋转模式，并设定目标角度
    //         chassis_cmd_recv.chassis_mode = CHASSIS_ROTATE;
    //     }

    // }
    // else {
    //     chassis_cmd_recv.chassis_mode = CHASSIS_FORWARD;

    // }

    if (gyro_data->gyro_Init_Flag != 1)
    {
        chassis_cmd_recv.chassis_mode = CHASSIS_ZERO_FORCE;
    }
    if (chassis_cmd_recv.chassis_mode == CHASSIS_ZERO_FORCE)
    { // 如果出现重要模块离线或遥控器设置为急停,让电机停止
        DJIMotorStop(motor_lf);
        DJIMotorStop(motor_rf);
        DJIMotorStop(motor_lb);
        DJIMotorStop(motor_rb);
    }
    else
    { // 正常工作
        DJIMotorEnable(motor_lf);
        DJIMotorEnable(motor_rf);
        DJIMotorEnable(motor_lb);
        DJIMotorEnable(motor_rb);
    }

    // 根据控制模式设定旋转速度
    switch (chassis_cmd_recv.chassis_mode)
    {
    case CHASSIS_FORWARD:
    case CHASSIS_C2C:
        left_target_vt = right_target_vt = chassis_cmd_recv.speed; // 3500
        // left_target_vt = right_target_vt = 0; // 3500
        break;
    case CHASSIS_ROTATE:
        left_target_vt = right_target_vt = 0; // 后面根据实际情况给速度值
        break;
    default:
        break;
    }

    // 根据控制模式进行正运动学解算,计算底盘输出
    SpeedCalculate();

    // 速度环电流环计算输出
    SetChassisOutput();

    check_arrive();

    // 推送反馈消息
#ifdef ONE_BOARD
    PubPushMessage(chassis_pub, (void *)&chassis_feedback_data);
#endif
#ifdef CHASSIS_BOARD
    CANCommSend(chasiss_can_comm, (void *)&chassis_feedback_data);
#endif // CHASSIS_BOARD
}