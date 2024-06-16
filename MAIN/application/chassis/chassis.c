#include "chassis.h"
#include "pid.h"
#include "gyro.h"

//==================== Public vars =====================:
float speed_limit = 20, heading_speed_limit = 0.7; // speed lmit should be smaller than 0.8 m/s

//==================== Internal vars =====================:
// constants & PIDs
// PID heading_PID;

Increment_PID left_increment_PID, right_increment_PID, heading_increment_PID;
const float H = 0.188, W = 0.25, R = 0.413, PI = 3.1415926535;
const float speed_kp = 0.5, speed_ki = 0.00, speed_kd = 0.02, speed_ki_limit = 0.08,
            heading_kp = 0.1, heading_ki = 0.00, heading_kd = 0.0017, heading_ki_limit = 0.5;
// motor speed unit is m/s, should start from a small value

// pid
//			motor_kp = 0.01, motor_ki = 0.0018, motor_kd = 0.001, motor_ki_limit = 80,   // î£Ýæ²ÎÊý
// motor_kp = 0.1, motor_ki = 0.002, motor_kd = 0.001, motor_ki_limit = 80,

// Turning functions
// int ideal_heading = 0, ideal_ring = 0; // For 90 degree turning

/* pid parameters:


*/
void chassis_pid_Init(void)
{
    set_increment_pid(&left_increment_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, 20);
    set_increment_pid(&right_increment_PID, speed_kp, speed_ki, speed_kd, speed_ki_limit, 20);
    set_increment_pid(&heading_increment_PID, heading_kp, heading_ki, heading_kd, heading_ki_limit, heading_speed_limit); // m/s
}

int chassis_ahead(int speed)
{
}

int chassis_rotate(float heading)
{
}

// output function
int chassis_run(int speed, float heading)
{
    // if pid output satisfy some condition return 1
}
