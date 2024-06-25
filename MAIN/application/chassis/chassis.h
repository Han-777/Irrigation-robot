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

typedef enum
{
    rotate_mode,
    ahead_mode
} chassis_mode_Enum;
extern chassis_mode_Enum chassis_mode;
extern int vec[2];
extern int rotate_arrive, rotate_vague_arrive;
void chassis_Init(void);
void chassis_pid_Init(void);
// int chassis_ahead(int left_speed, int right_speed);
int chassis_rotate(float heading);
void set_speed(int left_speed, int right_speed); // the speed should be an integer
// int chassis_run(int speed, float target_heading);
int chassis_run(void); // internal
// void lcd_dis(void);

void movement_stop(void);

#endif
