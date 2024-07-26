/**
 * @file gyro.h
 * @author Han-777
 * @brief  gyro模块定义头文件
 * @version beta
 * @date 2024-07-07
 *
 */
#ifndef GYRO_H
#define GYRO_H

#ifndef PI
#define PI 3.1415926535f
#endif

// 数据处理选择
// #define INFO_HANDLE_OUT
// 接收处理宏
#define FRAME_HEAD 0xfc
#define FRAME_END 0xfd
#define TYPE_IMU 0x40
#define TYPE_AHRS 0x41
#define TYPE_INSGPS 0x42
#define TYPE_GROUND 0xf0
#define IMU_LEN 0x38    // 56+8  8组数据
#define AHRS_LEN 0x30   // 48+8  7组数据
#define INSGPS_LEN 0x42 // 72+8  10组数据
#define IMU_CAN 9
#define AHRS_CAN 8
#define INSGPS_CAN 11
// 数据处理选择宏
// #define GYRO_RSIMU      // inertial measurement unit (IMU) data
#define GYRO_RSAHRS // attitude and heading reference system (AHRS) data
// #define GYRO_RSIMU_AHRS // processing IMU and AHRS data together

#include <stdint.h>
#include "main.h"

// gyro最后结算后得到的数据
typedef struct
{
    float RollSpeed;  // unit: degrees/s
    float PitchSpeed; // unit: degrees/s
    float YawSpeed;   // unit: degrees/s
    float Roll;       // unit: degrees
    float Pitch;      // unit: degrees
    float Yaw;        // unit: degrees
    // 上电角
    float ori_yaw;
    float ori_pitch;
    float ori_roll;
} GYRO_data_t; // 只对ahrsdata进行了封装

//
typedef struct IMUData_Packet_t
{
    float gyroscope_x;          // unit: rad/s
    float gyroscope_y;          // unit: rad/s
    float gyroscope_z;          // unit: rad/s
    float accelerometer_x;      // m/s^2
    float accelerometer_y;      // m/s^2
    float accelerometer_z;      // m/s^2
    float magnetometer_x;       // mG
    float magnetometer_y;       // mG
    float magnetometer_z;       // mG
    float imu_temperature;      // C
    float Pressure;             // Pa
    float pressure_temperature; // C
    uint32_t Timestamp;         // us
} IMUData_Packet_t;

typedef struct AHRSData_Packet_t
{
    float RollSpeed;    // unit: rad/s
    float PitchSpeed;   // unit: rad/s
    float HeadingSpeed; // unit: rad/s
    float Roll;         // unit: rad
    float Pitch;        // unit: rad
    float Heading;      // unit: rad
    float Qw;           // w          //Quaternion
    float Qx;           // x
    float Qy;           // y
    float Qz;           // z
    uint32_t Timestamp; // unit: us
} AHRSData_Packet_t;

#ifdef INFO_HANDLE_OUT
void GYRO_buff_to_data(); // 外部处理，中断只负责数据搬运
#endif
GYRO_data_t *Gyro_Init(UART_HandleTypeDef *gyro_usart_handle);

#endif