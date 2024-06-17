#ifndef __PID_H
#define __PID_H
#include "sys.h"

typedef volatile struct
{
	unsigned int enable_lim_sum_error : 1;
	unsigned int enable_lim_ouput : 1;

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
	unsigned int enable_lim_sum_error : 1;
	unsigned int enable_lim_output : 1; // 1-bit 标志，是否启用输出的限制
	float kp;							// 比例系数
	float ki;							// 积分系数
	float kd;							// 微分系数

	float lim_output; // 输出限制

	float last_error;	   // 上一次的误差
	float last_last_error; // 上上次的误差

	float delta_output; // 本次增量输出
	float output;		// 最终的控制输出
	float error;		// 当前误差
	float sum_error;	// for test
} Increment_PID;

typedef enum
{
	stop,
	openmvMode,
	relativeSpeedMode,
	absoluteSpeedMode,
	coordinateMode
} ControlMode;

void set_pid(PID *pid, float kp, float ki, float kd, float lim_kiout, float lim_output);
void reset_pid(PID *pid);
int pid_calculate(PID *pid, int target, int measure);

//==================== INCREMENT PID Calc related =====================:

void set_increment_pid(Increment_PID *pid, float kp, float ki, float kd, float lim_output);
void reset_increment_pid(Increment_PID *pid);
float increment_pid_calculate(Increment_PID *pid, float target, float measure);

extern float speed_limit, angular_speed_limit;

#endif
