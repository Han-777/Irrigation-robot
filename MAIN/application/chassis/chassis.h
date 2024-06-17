#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "sys.h"
#include "pid.h"
#include "gyro.h"
#include "motor.h"
#include "encoder.h"
#include "lcd.h"
#include "lidar.h"
#include "gray.h"

extern int vec[2];
extern float current_yaw;

void chassis_pid_Init(void);
int chassis_ahead(int left_speed, int right_speed);
int chassis_rotate(float heading);
int chassis_run(int speed, float heading);
void lcd_dis(void);

#endif
