#ifndef __ARM_H
#define __ARM_H

#include "sys.h"
#include "servo.h"
#include "run.h"
#include "photoelectric.h"
#include "openmv.h"
#include "bluetooth.h"
#include "mp3.h"
#include "lidar.h"
#define plant_found !PE_NOZZLE
#define lidar_water_dist_threshold 30
typedef struct
{
    u8 left_water_scan_finish;
    u8 right_water_scan_finish;
    u8 left_water_finish;
    u8 right_water_finish;
} water_finish_Structure_TypeDef;
extern water_finish_Structure_TypeDef water_finish_structure;
// 上电角度
#define pitch_mid 120 // 150
#define yaw_mid 40

// yaw scan angle
#define left_scan_begin 80
#define left_scan_end 40

#define right_scan_begin 200
#define right_scan_end 240

#define left_scan_mid 150  // 左侧居中
#define right_scan_mid 150 // 右侧居中

#define left_D_angle 80
#define right_D_angle 150
#define pitch_D_water_angle 120
// pitch scan angle
#define pitch_scan_angle 120

#define length_A 27.50 // 浇水的机械臂长度
#define H 32.50        // 激光底座到舵机云台的垂直  H要尽量低
#define D_d 20.00      // 车的几何中心到最外侧距离
#define R_R 9.50       // 圆形花盆的半径

#define pitch_lift_angle 170 // 抬高角度//机械臂的垂直角度 90为直角,
#define Balance_angle 195    // 平衡角度    max

// 云台角度
#define Left_D 202 // D区云台
#define Right_D 98 // D区云台

#define Mid 150 // 归中//云台的中央角度

int water_finish(void);
void arm_water_task(void);

#endif
