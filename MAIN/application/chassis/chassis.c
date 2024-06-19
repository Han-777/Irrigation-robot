#include "chassis.h"

//==================== Public vars =====================:
int vec[2] = {0};
float info[20] = {0};

float speed_limit = 50, heading_speed_limit = 40; // speed lmit should be smaller than 0.8 m/s
//==================== Internal vars =====================:
// constants & PIDs
// PID heading_PID;

Increment_PID left_inc_PID, right_inc_PID, heading_inc_PID;
// PID head_PID;
//  const float H = 0.188, W = 0.25, R = 0.413, PI = 3.1415926535;
const float speed_kp = 0.2, speed_ki = 0.12, speed_kd = 0.00,
            heading_kp = 1, heading_kd = 0.001; // for rotate
float heading_ki = 0;
// head_kp = 0.1, head_ki = 0, head_kd = 0, head_ki_limit = 2, head_out_limit = 180;
// motor speed unit is m/s, should start from a small value

// pid
//			motor_kp = 0.01, motor_ki = 0.0018, motor_kd = 0.001, motor_ki_limit = 80,   // ????????
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
    TFmini_right_USART_Init(115200);
    TFmini_left_USART_Init(115200);
    gyro_USART_Init(921600);
    delay_ms(100);
    TTL_Hex2Dec();
    ori_target_Yaw = Read_Yaw();
    target_Yaw = ori_target_Yaw;
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

int chassis_ahead(int left_speed, int right_speed)
{
    // pid calculation
    increment_pid_calculate(&left_inc_PID, left_speed, vec[0]);
    increment_pid_calculate(&right_inc_PID, right_speed, vec[1]);
    // load motor
    Car_Load(left_inc_PID.output, right_inc_PID.output);
    info[17] = left_inc_PID.output - heading_inc_PID.output;
    info[18] = right_inc_PID.output + heading_inc_PID.output;
    return 1;
}

// the function should not be stopped until reaching the target
// ???·pid
int chassis_rotate(float target_yaw)
{
    heading_Trans();
    heading_ki = 0.005;
    heading_speed_limit = 50;
    set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit);
    increment_pid_calculate(&heading_inc_PID, target_yaw, current_yaw);
    info[17] = heading_inc_PID.output;
    info[18] = -heading_inc_PID.output;
    Car_Load(heading_inc_PID.output, -heading_inc_PID.output);
    return 1;
}

// output function
int chassis_run(int speed, float target_heading)
{
    heading_Trans();
    heading_ki = 0.00;
    heading_speed_limit = 50;
    set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit);
    increment_pid_calculate(&heading_inc_PID, target_heading, current_yaw);        // 角度外环
    chassis_ahead(speed + heading_inc_PID.output, speed - heading_inc_PID.output); // 速度内环
    return 1;
    // if pid output satisfy some condition return 1
}

// int chassis_run(int speed, float target_heading)
// {
//     heading_Trans();
//     heading_ki = 0.00;
//     heading_speed_limit = 10;
//     set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_speed_limit);
//     increment_pid_calculate(&heading_inc_PID, target_heading, current_yaw); // heading
//     increment_pid_calculate(&left_inc_PID, speed, vec[0]);
//     increment_pid_calculate(&right_inc_PID, speed, vec[1]);
//     Car_Load(left_inc_PID.output - heading_inc_PID.output, right_inc_PID.output + heading_inc_PID.output);
//     // chassis_ahead(speed - heading_inc_PID.output, speed + heading_inc_PID.output);
// 	info[17] = left_inc_PID.output - heading_inc_PID.output;
// 	info[18] = right_inc_PID.output + heading_inc_PID.output;
//     return 1;
//     // if pid output satisfy some condition return 1
// }

void TIM7_IRQHandler(void)
{
    if (TIM_GetFlagStatus(TIM7, TIM_FLAG_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        TTL_Hex2Dec();
        vec[0] = Read_Speed(LEFT_ENCODER);
        vec[1] = Read_Speed(RIGHT_ENCODER);
        info[1] = left_inc_PID.output;
        info[2] = left_inc_PID.sum_error;
        info[3] = left_inc_PID.error;
        info[4] = right_inc_PID.output;
        info[5] = right_inc_PID.sum_error;
        info[6] = right_inc_PID.error;
        info[7] = heading_inc_PID.output;
        info[8] = heading_inc_PID.error;
        info[9] = heading_inc_PID.sum_error;
        info[10] = Dist_right;
        info[11] = Dist_left;

        current_yaw = Read_Yaw();
        //        chassis_ahead(20, 20);
        // chassis_rotate(ori_target_Yaw);
        //        chassis_run(5, ori_target_Yaw);
		chassis_run(10, target_Yaw);
//        chassis_rotate(target_Yaw);
//		Car_Load(-10, 10);

        Get_Count();
    }
}

// void lcd_dis(void)
// {
//     LCD_ShowString(10, 20, 100, 16, 16, "left");
//     LCD_ShowNum(10, 200, vec[0], 5, 16);
//     LCD_ShowString(30, 20, 100, 16, 16, "right");
//     LCD_ShowNum(30, 200, vec[1], 5, 16);
// }
