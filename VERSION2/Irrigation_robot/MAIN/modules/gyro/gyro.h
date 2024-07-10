/**
 * @file lidar.h
 * @author Han-777
 * @brief  gyro模块定义头文件
 * @version beta
 * @date 2024-07-07
 *
 */
#ifndef GYRO_H
#define GYRO_H

#include <stdint.h>
#include "main.h"

// gyro最后结算后得到的数据
typedef struct
{
    float RollSpeed;    // unit: degrees/s
    float PitchSpeed;   // unit: degrees/s
    float HeadingSpeed; // unit: degrees/s
    float Roll;         // unit: degrees
    float Pitch;        // unit: degrees
    float Heading;      // unit: degrees
} GYRO_data_t;

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

#endif