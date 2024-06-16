#include "chassis.h"
#include "pid.h"
#include "gyro.h"
<<<<<<< Updated upstream
#include "gray.h"
#include "encoder.h"

=======
#include "motor.h"
#include "encoder.h"
>>>>>>> Stashed changes
//==================== Public vars =====================:
float speed_limit = 20, heading_speed_limit = 0.7; // speed lmit should be smaller than 0.8 m/s

//==================== Internal vars =====================:
// constants & PIDs
// PID heading_PID;

Increment_PID left_inc_PID, right_inc_PID, heading_inc_PID;
PID head_PID;
// const float H = 0.188, W = 0.25, R = 0.413, PI = 3.1415926535;
const float speed_kp = 0.5, speed_ki = 0.00, speed_kd = 0.02, speed_ki_limit = 0.08,
            heading_kp = 0.1, heading_ki = 0.00, heading_kd = 0.0017, heading_ki_limit = 0.5,
            head_kp = 0.1, head_ki = 0, head_kd = 0, head_ki_limit = 2, head_out_limit = 180;
// motor speed unit is m/s, should start from a small value

// pid
//			motor_kp = 0.01, motor_ki = 0.0018, motor_kd = 0.001, motor_ki_limit = 80,   // î£Ýæ²ÎÊý
// motor_kp = 0.1, motor_ki = 0.002, motor_kd = 0.001, motor_ki_limit = 80,

// Turning functions
// int ideal_heading = 0, ideal_ring = 0; // For 90 degree turning

/**
 * @brief  Initialization for all chassis elements
 *
 * Including motors, encoders and increment pid parameters.
 *
 * @param    None
 * @return   None
 */
void chassis_Init(void)
{
    Motor_Init();
    Encoder_TIM_Init_All();
    chassis_pid_Init();
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
    set_increment_pid(&left_inc_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, 20);
    set_increment_pid(&right_inc_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, 20);
    set_increment_pid(&heading_inc_PID, heading_kp, heading_ki, heading_kd, heading_ki_limit, heading_speed_limit); // m/s
    set_pid(&head_PID, head_kp, head_ki, head_kd, head_ki_limit, head_out_limit);
}

/* the function in motor.h for using:
void Car_Load(int L, int R);
void Car_stop(void);
*/

int chassis_ahead(int speed)
{
    // pid calculation
    increment_pid_calculate(&left_inc_PID, speed, Read_Speed(LEFT_ENCODER));
    increment_pid_calculate(&right_inc_PID, speed, Read_Speed(RIGHT_ENCODER));
    // load motor
    Car_Load(left_inc_PID.output, right_inc_PID.output);
    return 1;
}

// the function should not be stopped until reaching the target
// Ë«»·pid
int chassis_rotate(float heading)
{
    static int cnt = 0; // cnt is for controlling the update of inner ring be 10 times of the outer ring
    if (cnt < 10)
    {
        // heading speed calculation
        increment_pid_calculate(&heading_inc_PID, heading, Read_Speed(LEFT_ENCODER));
    }
    else
    {
        cnt = 0;
    }

    Read_Yaw();
    return 1;
}

// output function
int chassis_run(int speed, float heading)
{
    // if pid output satisfy some condition return 1
}
