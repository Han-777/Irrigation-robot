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
#include "cmsis_os.h"
// #include "gray.h"
// #include "robot_cmd.h"
static GYRO_data_t *gyro_data;
static GYRO_Ctrl_Data_t gyro_ctrl_data;
static DJIMotorInstance *motor_lf, *motor_rf, *motor_lb, *motor_rb; // left right forward back
#ifdef ONE_BOARD
static Subscriber_t *chassis_sub;
static Publisher_t *chassis_pub;
#endif
static Chassis_Ctrl_Cmd_s chassis_cmd_recv;         // 底盘接收到的控制命令
static Chassis_Upload_Data_s chassis_feedback_data; // 底盘回传的反馈数据
/* 私有函数计算的中介变量,设为静态避免参数传递的开销 */
static float left_target_vt, right_target_vt; // 左边速度一样，右边速度一样
static PIDInstance angle_instance;
#define speedComLimit 2500
void ChassisInit() // 配置中所有pid参数都需要修改
{
    /*  最外层角度环参数   */
    PID_Init_Config_s pid_init_config =
        {
            .Kp = 50, // 200
            .Ki = 16, // 200
            .Kd = 10, // 100
            .IntegralLimit = 500,
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
                        .MaxOut = 0, // 1200
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
// static void HeadingTransfer(void)
// {
//     gyro_data->target_yaw = gyro_data->ori_yaw + 90 * chassis_cmd_recv.clockwise_rotate_flag;
//     while (gyro_data->target_yaw > 360)
//     {
//         gyro_data->target_yaw -= 360;
//     }
//     while (gyro_data->target_yaw < -360)
//     {
//         gyro_data->target_yaw += 360;
//     }
//     // handling the difference
//     gyro_data->cal_yaw = gyro_data->Yaw;
//     if (fabs(gyro_data->target_yaw - gyro_data->cal_yaw) > 180)
//     {
//         gyro_data->cal_yaw += ((gyro_data->target_yaw > gyro_data->Yaw) ? 360 : -360);
//     }
// }
static void HeadingTransfer(void)
{
    gyro_ctrl_data.target_yaw = gyro_ctrl_data.ori_yaw + 90 * chassis_cmd_recv.clockwise_rotate_flag;
    while (gyro_ctrl_data.target_yaw > 360)
    {
        gyro_ctrl_data.target_yaw -= 360;
    }
    while (gyro_ctrl_data.target_yaw < -360)
    {
        gyro_ctrl_data.target_yaw += 360;
    }
    // handling the difference
    gyro_ctrl_data.cal_yaw = gyro_data->Yaw;
    if (fabs(gyro_ctrl_data.target_yaw - gyro_ctrl_data.cal_yaw) > 180)
    {
        gyro_ctrl_data.cal_yaw += ((gyro_ctrl_data.target_yaw > gyro_data->Yaw) ? 360 : -360);
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
    uint8_t roll_err = 0;
    HeadingTransfer();
    PIDCalculate(&angle_instance, gyro_ctrl_data.cal_yaw, gyro_ctrl_data.target_yaw);
    if (chassis_cmd_recv.chassis_mode != CHASSIS_ROTATE && chassis_cmd_recv.lidar_com_speed != 0)
    {
        roll_err = fabs(gyro_data->Roll - gyro_ctrl_data.ori_roll);
        if (roll_err > 0.3)
        {
            // if (chassis_cmd_recv.region != C)
            // {
            //     left_target_vt += 1500;s
            //     right_target_vt += 1000;
            //     angle_instance.Output *= 8;
            // }
            // else
            // {
            //     // left_target_vt -= 1000;
            //     // right_target_vt -= 1000;
            //     angle_instance.Output *= 6;
            // }
            // if (chassis_cmd_recv.region != C)
            // {
            if (roll_err < 2)
            {
                left_target_vt += 2500;
                right_target_vt += 2500;
                angle_instance.Output *= 8;
            }

            // }
            else
            {
                left_target_vt -= 1000;
                right_target_vt -= 1000;
                angle_instance.Output *= 6;
                chassis_cmd_recv.lidar_com_speed = (chassis_cmd_recv.lidar_com_speed > 2000) ? 2000 : -2000;
            }
        }
        else
        {
            // if (chassis_cmd_recv.region == A || chassis_cmd_recv.region == C)
            //     angle_instance.Output *= 6;
            // else
            //     angle_instance.Output *= 5;
            switch (chassis_cmd_recv.region)
            {
            case A:
                angle_instance.Output *= 6;
                break;
            case B:
                angle_instance.Output *= 5;
                break;
            case C:
                angle_instance.Output *= 5;
                break;
            case D:
                angle_instance.Output *= 6;
                break;

            default:
                break;
            }
        }
        left_target_vt += angle_instance.Output;  // 系数后面测
        right_target_vt -= angle_instance.Output; // 系数后面测
        if (fabs(chassis_cmd_recv.lidar_com_speed) > speedComLimit && angle_instance.Err > 30)
        {
            chassis_cmd_recv.lidar_com_speed = (chassis_cmd_recv.lidar_com_speed > 0) ? speedComLimit : -speedComLimit;
            left_target_vt += chassis_cmd_recv.lidar_com_speed;
            right_target_vt -= chassis_cmd_recv.lidar_com_speed;
        }
        else
        {
            left_target_vt += chassis_cmd_recv.lidar_com_speed;
            right_target_vt -= chassis_cmd_recv.lidar_com_speed;
        }

        // 防止卡车
        if (left_target_vt < 1500 && right_target_vt < 1500)
        {
            left_target_vt = 6000;
            right_target_vt = 6000;
        }
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

    if (gyro_ctrl_data.init_flag != 1)
    {
        chassis_cmd_recv.chassis_mode = CHASSIS_ZERO_FORCE;
        osDelay(5000);
        if (fabs(gyro_data->Yaw - gyro_data->last_Yaw) < 0.02 && fabs(gyro_data->last_Roll - gyro_data->Roll) < 0.02)
        {
            gyro_ctrl_data.ori_yaw = gyro_data->Yaw; // 陀螺仪初始值不为0,记录初始值
            // gyro_data->ori_pitch = gyro_data->Pitch;
            gyro_ctrl_data.ori_roll = gyro_data->Roll;
            gyro_ctrl_data.init_flag = 1;
        }
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
        left_target_vt = right_target_vt = chassis_cmd_recv.speed; // 3500
        if (chassis_cmd_recv.region == A)
        {
            angle_instance.IntegralLimit = 200;
            angle_instance.MaxOut = 1500;
        }
        else
        {
            angle_instance.IntegralLimit = 250;
            angle_instance.MaxOut = 2500;
        }
        break;
    case CHASSIS_C2C:
        left_target_vt = right_target_vt = chassis_cmd_recv.speed; // 3500
        angle_instance.MaxOut = 4000;
        angle_instance.IntegralLimit = 1000;
        // left_target_vt = right_target_vt = 0; // 3500
        break;
    case CHASSIS_ROTATE:
        left_target_vt = right_target_vt = 0; // 后面根据实际情况给速度值
        angle_instance.IntegralLimit = 300;
        if (fabs(angle_instance.Err) > 45)
        {
            angle_instance.MaxOut = 1500;
        }
        else if (fabs(angle_instance.Err) > 30)
        {
            angle_instance.MaxOut = 1000;
        }
        else if (fabs(angle_instance.Err) > 15)
        {
            angle_instance.MaxOut = 700;
        }
        else if (fabs(angle_instance.Err) > 10)
        {
            angle_instance.MaxOut = 300;
        }
        else if (fabs(angle_instance.Err) > 5)
        {
            angle_instance.MaxOut = 200;
        }
        else if (fabs(angle_instance.Err) > 2.5)
        {
            angle_instance.MaxOut = 100;
        }
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