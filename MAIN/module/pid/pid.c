#include "pid.h"
#include "sys.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// 激光雷达2到车中心距离： 22.5cm

// Internal functions:
//==================== PID Calc related =====================:
void set_pid(PID *pid, float kp, float ki, float kd, float lim_kiout, float lim_output)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->lim_integral = lim_kiout;
	pid->lim_output = lim_output;
}

void reset_pid(PID *pid)
{
	pid->sum_error = 0;
	pid->last_error = 0;
	pid->output = 0;
}

int pid_calculate(PID *pid, int target, int measure)
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

	pid->output = pid->kp * pid->error + pid->ki * pid->sum_error + pid->kd * (pid->error - pid->last_error);

	// output limit
	if (pid->enable_lim_ouput)
	{
		if (fabs(pid->output) > pid->lim_output)
		{
			pid->output = (pid->output > 0) ? pid->lim_output : -pid->lim_output;
		}
	}

	// 	filtering
	if ((pid->last_error > 0 && pid->error < 0) || (pid->last_error < 0 && pid->error > 0))
	{
		// remove overshoot - works pretty good!
		pid->sum_error = 0;
	}

	pid->last_error = pid->error;
	return 0;
}

//==================== INCREMENT PID Calc related =====================:

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
	if (fabs(pid->sum_error) > pid->lim_integral)
	{
		pid->sum_error = (pid->sum_error > 0) ? pid->lim_integral : -pid->lim_integral;
	}

	// pid output calculate
	pid->delta_output = pid->kp * (pid->error - pid->last_error) + pid->ki * pid->sum_error + pid->kd * (pid->error - 2 * pid->last_error + pid->last_last_error);

	pid->output += pid->delta_output;
	// pid output limit
	if (fabs(pid->output) > pid->lim_output)
	{
		pid->output = (pid->output > 0) ? pid->lim_output : -pid->lim_output;
	}

	pid->last_last_error = pid->last_error;
	pid->last_error = pid->error;

	return pid->output;
}
