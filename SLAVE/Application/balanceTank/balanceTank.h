#ifndef __BALANCETANK_H
#define __BALANCETANK_H

#include "sys.h"
#include "servo.h"

#define PI 3.1415926
// 增量pid
typedef volatile struct
{
	float desired;		  // 期望值
	float offset;		  //
	float prevError;	  // 前一次误差值
	float integ;		  // 积分量
	float kp;			  // 比例
	float ki;			  // 积分
	float kd;			  // 微分
	float IntegLimitHigh; // 积分量上限
	float IntegLimitLow;  // 积分量下限
	float measured;		  // 测量值
	float out;			  // 输出量
	float OutLimitHigh;	  // 输出量上限
	float OutLimitLow;	  // 输出量下限
} PidObject;

typedef struct
{
	short roll;
	short pitch;
	uint16_t Dist_left;
} Data_Para;

typedef struct
{
	float angle;
	float _angle;
} Servos;

// my
typedef volatile struct
{
	u8 enable_lim_sum_error : 1;
	u8 enable_lim_ouput : 1;

	float kp;
	float ki;
	float kd;

	//	float sum_error_lim;
	float lim_integral;
	float lim_output;

	float sum_error;
	float last_error;
	// float last_last_error;

	float output;
	float error;
} PID;

/// @brief 增量式pid: 速度环
typedef volatile struct
{
	u8 enable_lim_sum_error : 1;
	u8 enable_lim_output : 1; // 1-bit 标志，是否启用输出的限制
	float kp;				  // 比例系数
	float ki;				  // 积分系数
	float kd;				  // 微分系数

	float lim_integral;
	float lim_output; // 输出限制

	float last_error;	   // 上一次的误差
	float last_last_error; // 上上次的误差

	float delta_output; // 本次增量输出
	float output;		// 最终的控制输出
	float error;		// 当前误差
	float sum_error;	// for test
} Increment_PID;
/*=====================public========================*/
extern float pitch, roll, yaw; // 欧拉角
// extern short aacx,aacy,aacz;		  //加速度传感器原始数据
// extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
// extern float a;
int mpu_control(void);
void Control_Init(void);
void Control_loop(void);

// void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid数据初始化
// void pidUpdate(PidObject* pid);                                                                            		 //PID更新
// void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //串级PID
// void Pid_input_parameters(PidObject **pid);                                                                    //pid入口参数更新
// void Pid_Calculate(PidObject **pid);
// void Send_data(Data_Para *data);
// void PWM_Calculate(PidObject **pid);

#endif
