#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "sys.h"
#include "pid.h"
#include "gyro.h"
#include "gray.h"
#include "motor.h"
#include "encoder.h"

void chassis_pid_Init(void);
int chassis_ahead(int speed);
int chassis_rotate(float heading);
int chassis_run(int speed, float heading);

#endif
