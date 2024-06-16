#include "balanceTank.h"


float pitch, roll, yaw;    // 欧拉角
short aacx, aacy, aacz;    // 加速度传感器原始数据
short gyrox, gyroy, gyroz; // 陀螺仪原始数据

/*===================my==========================*/
/* pid parameter for servo
p:
I:
D:
target: 0 degree
回中角度：test: 100
pitch: 后正， row: 右正
*/
//PID pitch_pid, roll_pid;
Increment_PID pitch_inc_pid, roll_inc_pid;
/*=====================private============================*/
/*----------------------pid-------------------------*/
//void set_pid(PID *pid, float kp, float ki, float kd, float lim_kiout, float lim_output)
//{
//    pid->kp = kp;
//    pid->ki = ki;
//    pid->kd = kd;
//    pid->lim_integral = lim_kiout;
//    pid->lim_output = lim_output;
//}

//void reset_pid(PID *pid)
//{
//    pid->sum_error = 0;
//    pid->last_error = 0;
//    pid->output = 0;
//}

//float pid_calculate(PID *pid, float target, float measure)
//{
//    pid->error = target - measure;
//    pid->sum_error += pid->error;

//    // integral limit
//    if (pid->enable_lim_sum_error)
//    {
//        if (fabs(pid->sum_error) > pid->lim_integral)
//        {
//            pid->sum_error = (pid->sum_error > 0) ? pid->lim_integral : -pid->lim_integral;
//        }
//    }

//    pid->output = pid->kp * pid->error + pid->ki * pid->sum_error + pid->kd * (pid->error - pid->last_error);

//    // output limit
//    if (pid->enable_lim_ouput)
//    {
//        if (fabs(pid->output) > pid->lim_output)
//        {
//            pid->output = (pid->output > 0) ? pid->lim_output : -pid->lim_output;
//        }
//    }

//    // 	filtering
//    if ((pid->last_error > 0 && pid->error < 0) || (pid->last_error < 0 && pid->error > 0))
//    {
//        // remove overshoot - works pretty good!
//        pid->sum_error = 0;
//    }

//    pid->last_error = pid->error;
//    return 0;
//}
/*----------------------increment_pid-------------------------*/
void set_increment_pid(Increment_PID *pid, float kp, float ki, float kd, float lim_integral, float lim_output)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->lim_integral = lim_integral;
    pid->lim_output = lim_output;
    pid->last_error = 0;
    pid->last_last_error = 0;
    pid->output = 0;
    pid->delta_output = 0;

    pid->sum_error = 0; // for test
}

void reset_increment_pid(Increment_PID *pid)
{
    pid->last_error = 0;
    pid->last_last_error = 0;
    pid->output = 0;
    pid->delta_output = 0;
}

float increment_pid_calculate(Increment_PID *pid, float target, float measure)
{
    pid->error = target - measure;
    pid->sum_error += pid->error;
    // integral limit
    if (pid->enable_lim_sum_error)
    {
        if (fabs(pid->sum_error) > pid->lim_integral)
        {
            pid->sum_error = (pid->sum_error > 0) ? pid->lim_integral : -pid->lim_integral;
        }
    }

    // pid output calculate
    pid->delta_output = pid->kp * (pid->error - pid->last_error) + pid->ki * pid->sum_error + pid->kd * (pid->error - 2 * pid->last_error + pid->last_last_error);

    pid->output += pid->delta_output;
    // pid output limit
    if (pid->enable_lim_output)
    {
        if (fabs(pid->output) > pid->lim_output)
        {
            pid->output = (pid->output > 0) ? pid->lim_output : -pid->lim_output;
        }
    }

    pid->last_last_error = pid->last_error;
    pid->last_error = pid->error;

    return pid->output;
}
/*======================public======================*/
void Control_Init(void)
{
    // servo 初始化
    servoInit();
    ServoControl(110, 110, 110, 110); // 平衡
    // mpu 初始化
    MPU_Init();
    while (mpu_dmp_init())
        ;
    //    USART2_Init(9600);
    TIM2_Init(999, 719); // 72M / 1000 / 720 = 1000Hz = 10ms (used as timer)
    // pid 初始化
    // set_pid(&pitch_pid, 0.1, 0.00, 0.1, 2, 10);
    // set_pid(&roll_pid, 0.1, 0.00, 0.1, 2, 10);
    set_increment_pid(&pitch_inc_pid, 0.2, 0, 0.07, 0, 10);
    set_increment_pid(&roll_inc_pid, 0.2, 0, 0.07, 0, 10);
}

void Control_loop(void)
{
    // pid_calculate(&pitch_pid, 0, pitch);
    // pid_calculate(&roll_pid, 0, roll);
    increment_pid_calculate(&pitch_inc_pid, 0, pitch);
    increment_pid_calculate(&roll_inc_pid, 0, roll);
    //	printf("ppppppppppppppppppp-error: %.2f   output: %.2f   sum_error: %.2f \n\r", pitch_pid.error, pitch_pid.output, pitch_pid.sum_error);
    //	printf("rrrrrrrrrrrrrrrrr------error: %.2f   output: %.2f   sum_error: %.2f \n\r", roll_pid.error, roll_pid.output, roll_pid.sum_error);

    //    printf("error: %d", (int)pitch_pid.error * 100);
    //    printf("output: %d", (int)pitch_pid.output * 100);

    // pid to servo
    //	ServoControl(100, 100, 130, 100);  // 平衡

    // ServoControl(110 + 12 * pitch_pid.output, 110 - 12 * roll_pid.output, 110 - 12 * pitch_pid.output, 110 + 12 * roll_pid.output);
    ServoControl(110 + 17 * pitch_inc_pid.output, 110 - 17 * roll_inc_pid.output, 110 - 17 * pitch_inc_pid.output, 110 + 17 * roll_inc_pid.output);
}

/*=================public(mpu)===================*/
int mpu_control(void)
{
    if (mpu_dmp_get_data(&roll, &pitch, &yaw) == 0)
    {
        Control_loop();
        // MPU_Get_Accelerometer(&aacx, &aacy, &aacz); // 得到加速度传感器数据
        // MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  // 得到陀螺仪数据
        //        printf("pitch=%.2f     row=%.2f     yaw=%.2f \n\r", pitch, roll, yaw);
        return 1;
    }
    return 0;
}
