#ifndef __WATER_H
#define __WATER_H
#include "main.h"
// 浇水
#define watering_Plant HAL_GPIO_WritePin(RELAY_GPIO_GPIO_Port, RELAY_GPIO_Pin, GPIO_PIN_SET)
#define stop_watering_Plant HAL_GPIO_WritePin(RELAY_GPIO_GPIO_Port, RELAY_GPIO_Pin, GPIO_PIN_RESET)

#define water
// 扫描到
#define No_Plant HAL_GPIO_ReadPin(HEAD_PE_GPIO_Port, HEAD_PE_Pin)
/*==================water angle====================*/
/*---------------standby angle---------------*/
#define pitch_standby_angle 130 // pitch mid angle 140
#define yaw_standby_angle 130   // yaw mid angle 135
/*---------------scan angle------------------*/
#define scan_delay_time 40 // 30
#define water_delay_time 8 // 12
#define water_angle_offset 5
#define pitch_scan_angle 180
#define pitch_scan_D_angle 160
#define yaw_scan_left_begin_angle 200
#define yaw_scan_left_end_angle 250
#define yaw_scan_right_begin_angle 65
#define yaw_scan_right_end_angle 15
#define yaw_scan_left_D_angle 210
#define yaw_scan_right_D_angle 50
/*---------------water angle-----------------*/
#define pitch_water_left_angle(lidar_left_dis) (170 - lidar_left_dis * 0.7)
#define pitch_water_right_angle(lidar_right_dis) (170 - lidar_right_dis * 0.7)
#define pitch_water_min 150
#define pitch_water_D_left_angle(lidar_left_dis) (170 - lidar_left_dis * 0.5)
#define pitch_water_D_right_angle(lidar_right_dis) (170 - lidar_right_dis * 0.5)

#ifdef water
#endif
void WaterInit(void);
void WaterTask(void);

#endif