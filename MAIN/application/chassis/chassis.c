#include "chassis.h"

//==================== Public vars =====================:
float speed_limit = 27, heading_speed_limit = 0.7; // speed lmit should be smaller than 0.8 m/s

//==================== Internal vars =====================:
// constants & PIDs
// PID heading_PID;

Increment_PID left_inc_PID, right_inc_PID, heading_inc_PID;
// PID head_PID;
//  const float H = 0.188, W = 0.25, R = 0.413, PI = 3.1415926535;
const float speed_kp = 0.2, speed_ki = 0.01, speed_kd = 0.0, speed_ki_limit = 1,
            heading_kp = 0.1, heading_ki = 0.00, heading_kd = 0.0017, heading_ki_limit = 10;
// head_kp = 0.1, head_ki = 0, head_kd = 0, head_ki_limit = 2, head_out_limit = 180;
// motor speed unit is m/s, should start from a small value

// pid
//			motor_kp = 0.01, motor_ki = 0.0018, motor_kd = 0.001, motor_ki_limit = 80,   // î£Ýæ²ÎÊý
// motor_kp = 0.1, motor_ki = 0.002, motor_kd = 0.001, motor_ki_limit = 80,

// Turning functions
// int ideal_heading = 0, ideal_ring = 0; // For 90 degree turning

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
    gyro_USART_Init(921600);
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
    set_increment_pid(&left_inc_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, speed_limit);
    set_increment_pid(&right_inc_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, speed_limit);
    set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_ki_limit, heading_speed_limit); // m/s
    // set_pid(&head_PID, head_kp, head_ki, head_kd, head_ki_limit, head_out_limit);
}

/* the function in motor.h for using:
void Car_Load(int L, int R);
void Car_stop(void);
*/

int chassis_ahead(int left_speed, int right_speed)
{
    // pid calculation
    increment_pid_calculate(&left_inc_PID, left_speed, Read_Speed(LEFT_ENCODER));
    increment_pid_calculate(&right_inc_PID, right_speed, Read_Speed(RIGHT_ENCODER));
    // load motor
    Car_Load(left_inc_PID.output, right_inc_PID.output);
    return 1;
}

// the function should not be stopped until reaching the target
// Ë«»·pid
int chassis_rotate(float target_yaw)
{
    static int cnt = 0; // cnt is for controlling the update of inner ring be 10 times of the outer ring
    increment_pid_calculate(&heading_inc_PID, target_yaw, Read_Yaw());
    // chassis_ahead();

    return 1;
}

// output function
int chassis_run(int speed, float heading)
{
    // if pid output satisfy some condition return 1
}

int vec[2] = {0};
float info[10] = {0};
void TIM7_IRQHandler(void)
{
    if (TIM_GetFlagStatus(TIM7, TIM_FLAG_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        vec[0] = Read_Speed(LEFT_ENCODER);
        vec[1] = Read_Speed(RIGHT_ENCODER);
        info[1] = left_inc_PID.output;
        info[2] = left_inc_PID.sum_error;
        info[3] = left_inc_PID.error;
        info[4] = right_inc_PID.output;
        info[5] = right_inc_PID.sum_error;
        info[6] = right_inc_PID.error;
        TTL_Hex2Dec();
//        chassis_ahead(1, 1);
    }
}

// void lcd_dis(void)
// {
//     LCD_ShowString(10, 20, 100, 16, 16, "left");
//     LCD_ShowNum(10, 200, vec[0], 5, 16);
//     LCD_ShowString(30, 20, 100, 16, 16, "right");
//     LCD_ShowNum(30, 200, vec[1], 5, 16);
// }