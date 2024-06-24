#include "chassis.h"
#include "run.h"
//==================== Public vars =====================:
int vec[2] = {0};
float info[20] = {0};

float speed_limit = 50, heading_speed_limit = 10; // speed lmit should be smaller than 0.8 m/s
//==================== Internal vars =====================:
// constants & PIDs
// PID heading_PID;

Increment_PID left_inc_PID, right_inc_PID, heading_inc_PID;
// PID head_PID;
//  const float H = 0.188, W = 0.25, R = 0.413, PI = 3.1415926535;
const float speed_kp = 0.1, speed_ki = 0.12, speed_kd = 0.00, speed_Kv = 0.1, // feed forward gain
                                                                              //    heading_kp = 0.07, heading_ki = 0.00, heading_kd = 0.017;                   // for rotate
    heading_kp = 0.05, heading_ki = 0.0000, heading_kd = 0.01;                // for rotate

float left_target_speed = 0, right_target_speed = 0;
// head_kp = 0.1, head_ki = 0, head_kd = 0, head_ki_limit = 2, head_out_limit = 180;
// motor speed unit is m/s, should start from a small value

// pid
//			motor_kp = 0.01, motor_ki = 0.0018, motor_kd = 0.001, motor_ki_limit = 80,   // ????????
// motor_kp = 0.1, motor_ki = 0.002, motor_kd = 0.001, motor_ki_limit = 80,

//==================== chassis movement =====================:
/**
 * @brief  TIM7, GYRO and pe close, stop car
 *
 * @param    None
 * @return   None
 */
void movement_stop(void)
{
    TIM7_Close();
    gyro_USART_Close();
    gyro_init_flag = 0;
    Car_stop();
    PE_EXTI_Close();
    delay_ms(20);
}
/**
 * @brief  Initialization for all chassis elements
 *
 * Including motors, encoders, gyro and increment pid parameters.
 *
 * @param    None
 * @return   None
 */
void chassis_Init(void)
{
    Motor_Init();
    Encoder_TIM_Init_All();
    chassis_pid_Init();
    GYRO_Init();
    delay_ms(5000); // wait for stable(it is not necassary)
    TTL_Hex2Dec();
    ori_target_Yaw = Read_Yaw();
    target_Yaw = ori_target_Yaw;
    lidar_Init(left_lidar); //  for test
    lidar_Init(right_lidar);
    VirtualTx_Config();
    TIM7_Init(1000 - 1, 840 - 1); // 84M / 4200 / 1000 = 20ms
}

/**
 * @brief  Initialization for chassis pid parameters
 *
 * Including the initialization of left, right and heading pid parameters
 *
 * @param    None
 * @return   None
 */
void chassis_pid_Init(void)
{
    set_increment_pid(&left_inc_PID, speed_kp, speed_ki, speed_kd, speed_limit);
    set_increment_pid(&right_inc_PID, speed_kp, speed_ki, speed_kd, speed_limit);
    set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit); // m/s
    // set_pid(&head_PID, head_kp, head_ki, head_kd, head_ki_limit, head_out_limit);
}

/* the function in motor.h for using:
void Car_Load(int L, int R);
void Car_stop(void);
*/

// int chassis_ahead(int left_speed, int right_speed)
//{
//     // pid calculation
//     increment_pid_calculate(&left_inc_PID, left_speed, vec[0]);
//     increment_pid_calculate(&right_inc_PID, right_speed, vec[1]);
//     // load motor
//     Car_Load(left_inc_PID.output, right_inc_PID.output);
//     info[17] = left_inc_PID.output;
//     info[18] = right_inc_PID.output;
//     return 1;
// }

// int rotate_stable = 0;
// void check_stable(void) // 根据位置的误差来判断稳定性
// {
//     static float prev_heading;
//     if (fabs(prev_heading - current_yaw) < 0.7)
//         rotate_stable = 1;
//     else
//         rotate_stable = 0;
//     prev_heading = current_yaw;
// }

int rotate_arrive = 0, rotate_vague_arrive = 0;
void check_arrive(void) // 到达判断
{
    // 精确到达判断
    if (fabs(heading_inc_PID.error) < 1)
        rotate_arrive = 1;
    else
        rotate_arrive = 0;

    // 模糊到达判断
    if (fabs(heading_inc_PID.error) < 2)
        rotate_vague_arrive = 1;
    else
        rotate_vague_arrive = 0;
}

// the function should not be stopped until reaching the target
// ???·pid
int chassis_rotate(float target_yaw)
{
    set_speed(0, 0);
    check_arrive();
    heading_Trans();
    // heading_speed_limit = 50;
    increment_pid_calculate(&heading_inc_PID, target_yaw, current_yaw);
    info[17] = 100 * heading_inc_PID.output;
    info[18] = -100 * heading_inc_PID.output;
    info[17] = ((abs(info[17]) > 10) ? info[17] : (info[17] > 0) ? 10
                                                                 : -10);
    info[18] = ((abs(info[18]) > 10) ? info[18] : (info[18] > 0) ? 10
                                                                 : -10);
    Car_Load(info[17], info[18]);
    return 1;
}

// output function
// int chassis_run(int speed, float target_heading)
// {
//     heading_Trans();
//     heading_speed_limit = 50;
//     set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit);
//     increment_pid_calculate(&heading_inc_PID, target_heading, current_yaw);        // 角度外环
//     chassis_ahead(speed + heading_inc_PID.output, speed - heading_inc_PID.output); // 速度内环
//     return 1;
// }

// 串
// int chassis_run(int speed, float target_heading)
//{
//    heading_Trans();
//    // heading_speed_limit = 50;
//    // set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit);
//    increment_pid_calculate(&heading_inc_PID, target_heading, current_yaw);        // 角度外环
//    chassis_ahead(speed + heading_inc_PID.output, speed - heading_inc_PID.output); // 速度内环
//    return 1;
//}
// 并级
int chassis_run(void)
{
    static int left_ff_speed = 0, right_ff_speed;
    heading_Trans();
    increment_pid_calculate(&heading_inc_PID, target_Yaw, current_yaw); // 角度外环
    increment_pid_calculate(&left_inc_PID, left_target_speed, vec[0]);
    increment_pid_calculate(&right_inc_PID, right_target_speed, vec[1]);
    left_ff_speed = speed_Kv * left_target_speed;
    right_ff_speed = speed_Kv * right_target_speed;
    info[17] = left_inc_PID.output + 200 * heading_inc_PID.output + left_ff_speed;
    info[18] = right_inc_PID.output - 200 * heading_inc_PID.output + right_ff_speed;
    Car_Load(info[17], info[18]);
    return 1;
}

void set_speed(int left_speed, int right_speed) // the speed should be an integer
{
    left_target_speed = left_speed;
    right_target_speed = right_speed;
}
void TIM7_IRQHandler(void)
{
    if (TIM_GetFlagStatus(TIM7, TIM_FLAG_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        TTL_Hex2Dec();
        current_yaw = Read_Yaw();
        vec[0] = Read_Speed(LEFT_ENCODER);
        vec[1] = Read_Speed(RIGHT_ENCODER);
        // info[1] = left_inc_PID.output;
        // info[2] = left_inc_PID.sum_error;
        // info[3] = left_inc_PID.error;
        // info[4] = right_inc_PID.output;
        // info[5] = right_inc_PID.sum_error;
        // info[6] = right_inc_PID.error;
        // info[7] = heading_inc_PID.output;
        // info[8] = heading_inc_PID.error;
        // info[9] = heading_inc_PID.sum_error;
        // info[10] = lidar_right;
        // info[11] = lidar_left;
        chassis_run();

        //        		chassis_rotate(target_Yaw);
        //  		chassis_run(10, target_Yaw);
        //        chassis_ahead(20, 20);
        // chassis_rotate(ori_target_Yaw);
        //        chassis_run(5, ori_target_Yaw);
        // chassis_run(0, target_Yaw);
        //        chassis_rotate(target_Yaw);

        //        info[12] = Get_Count();
    }
}

// void lcd_dis(void)
// {
//     LCD_ShowString(10, 20, 100, 16, 16, "left");
//     LCD_ShowNum(10, 200, vec[0], 5, 16);
//     LCD_ShowString(30, 20, 100, 16, 16, "right");
//     LCD_ShowNum(30, 200, vec[1], 5, 16);
// }
