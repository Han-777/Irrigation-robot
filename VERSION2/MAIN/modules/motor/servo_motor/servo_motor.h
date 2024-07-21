/**
 * @file servo_motor.h
 * @author Han-777
 * @brief 舵机控制头文件
 * @version 0.1
 * @date 2024-7-20
 *
 */

#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "main.h"
#include "tim.h"
#include <stdint.h>

#define SERVO_MOTOR_CNT 7 // number of servo motors

/*servo type structure*/
typedef enum
{
    Servo180 = 0,
    Servo270 = 1,
    Servo360 = 2,
} Servo_Type_e;

/*servo mode structure*/
typedef enum
{
    Free_Angle_mode, // 任意角度模式
    Start_mode,      // 起始角度模式
    Final_mode,      // 终止角度模式
} Servo_Angle_Type_e;

/*angle setting structure*/
typedef struct
{
    /*起止角度模式设置值*/
    int16_t Init_angle;
    int16_t Final_angle;
    /*任意角度模式设置值*/
    int16_t free_angle;
    /*下述值仅仅适用于360°舵机
     *设定值为0-100 为速度值百分比
     *0-50为正转 速度由快到慢
     *51-100为反转 速度由慢到快
     */
    int16_t servo360speed;
} Servo_Angle_s;

/**
 * @brief Servo Init structure
 *
 * @param Servo_type: servo type
 * @param Servo_Angle_Type: servo angle type
 * @param htim: timer handle
 * @param Channel: timer channel
 *        which can be:
 *          TIM_CHANNEL_1
 *          TIM_CHANNEL_2
 *          TIM_CHANNEL_3
 *          TIM_CHANNEL_4
 *          TIM_CHANNEL_ALL
 */
typedef struct
{
    Servo_Type_e Servo_type;
    Servo_Angle_Type_e Servo_Angle_Type;
    TIM_HandleTypeDef *htim;
    uint32_t Channel;
} Servo_Init_Config_s;

/**
 * @brief Servo Instance structure
 *
 * @param Servo_type: servo type
 * @param Servo_Angle_Type: servo angle type
 * @param Servo_Angle: servo angle (different from init config)
 * @param htim: timer handle
 * @param Channel: timer channel
 */
typedef struct
{
    Servo_Type_e Servo_type;
    Servo_Angle_Type_e Servo_Angle_Type;
    Servo_Angle_s Servo_Angle; // +
    // 使用的定时器类型及通道
    TIM_HandleTypeDef *htim;
    uint32_t Channel;
} ServoInstance;

ServoInstance *ServoInit(Servo_Init_Config_s *Servo_Init_Config);
void Servo_Motor_FreeAngle_Set(ServoInstance *Servo_Motor, int16_t S_angle);
void Servo_Motor_Type_Select(ServoInstance *Servo_Motor, int16_t mode);
void ServeoMotorControl();
#endif // SERVO_MOTOR_H