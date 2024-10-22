#pragma once // 可以用#pragma once代替#ifndef ROBOT_DEF_H(header guard)
#ifndef ROBOT_DEF_H
#define ROBOT_DEF_H

// #include "master_process.h"
#include "stdint.h"
#define ROBOT_DEF_PARAM_WARNING
// #define A_speed 6500
// #define C_speed 6500
// #define B_speed 9000
// #define D_speed 8000
#define A_speed 6500
#define C_speed 6000
#define B_speed 10000
#define D_speed 8000
/*=====================A===========================*/
#define LD_A_DIS_THRESHOLD 27
#define LD_A_DIS_MIN_THRESHOLD 10 // 正中心对应雷达距离 中心：14
#define LD_A_DIS_MAX_THRESHOLD 26
/*=====================B===========================*/
#define LD_B_DIS_THRESHOLD 40

#define LD_B_DIS_MIN_THRESHOLD 17 // 正中心对应雷达距离 中心：22
#define LD_B_DIS_MAX_THRESHOLD 16 // 防掉坡：加强远端修复能力（可以偏右）
/*=====================C===========================*/
// C理想位置左：31 右：17
// #define LD_C_DIS_MIN_THRESHOLD 15 // 正中心对应雷达距离 中心：24
// #define LD_C_DIS_MAX_THRESHOLD 30 // 防掉坡：加强近端修复能力（可以偏右）
#define LD_C_LEFT_DIS_THRESHOLD 40
#define LD_C_LEFT_DIS_MIN_THRESHOLD 28
#define LD_C_LEFT_DIS_MAX_THRESHOLD 33 // mid : 19
#define LD_C_RIGHT_DIS_THRESHOLD 35
#define LD_C_RIGHT_DIS_MIN_THRESHOLD 14
#define LD_C_RIGHT_DIS_MAX_THRESHOLD 20 // mid:
// #define LD_C_LEFT_DIS_THRESHOLD 40
// #define LD_C_LEFT_DIS_MIN_THRESHOLD 24
// #define LD_C_LEFT_DIS_MAX_THRESHOLD 24 // mid : 19
// #define LD_C_RIGHT_DIS_THRESHOLD 35
// #define LD_C_RIGHT_DIS_MIN_THRESHOLD 24
// #define LD_C_RIGHT_DIS_MAX_THRESHOLD 24 // mid:
/*=====================D===========================*/
#define LD_D_DIS_THRESHOLD 33
#define LD_D_DIS_MIN_THRESHOLD 14 // 正中心对应雷达距离 中心：22
#define LD_D_DIS_MAX_THRESHOLD 32
/*====================补偿=========================*/
#define COM_PARAMETER_A 100
#define COM_PARAMETER_B 200
#define COM_PARAMETER_D 200
#define COM_C_PARAMETER 200

#define ONE_BOARD // 单板控制整车 (实际上是双板，没有完善代码)
// #define CHASSIS_BOARD //底盘板
// #define GIMBAL_BOARD  //云台板

// 底盘模式设置
/**
 * @brief 后续考虑修改为云台跟随底盘,而不是让底盘去追云台,云台的惯量比底盘小.
 *
 */
typedef enum
{
    CHASSIS_ZERO_FORCE = 0, // 电流零输入
    CHASSIS_FORWARD = 1,    // 前进模式
    CHASSIS_ROTATE = 2,     // 旋转模式
    CHASSIS_C2C
} chassis_mode_e;

typedef enum
{
    left_water_flag = 0b00000001,
    right_water_flag = 0b00000010,
    none_water_flag = 0b00000000,
    water_finish_flag = 0b00000011,
    pair_water_flag = 0b00000011
    // left_water_finish = 0b11111110,
    // right_water_finish = 0b11111101,
} water_State_e;

#pragma pack(1) // 压缩结构体,取消字节对齐,下面的数据都可能被传输
/* -------------------------基本控制模式和数据类型定义-------------------------*/
/**
 * @brief 这些枚举类型和结构体会作为CMD控制数据和各应用的反馈数据的一部分
 *
 */
// 机器人状态
typedef enum
{
    ROBOT_STOP = 0,
    ROBOT_READY,
} Robot_Status_e;

/* ----------------CMD应用发布的控制数据,应当由gimbal/chassis/shoot订阅---------------- */
/**
 * @brief 灌溉区域ENUN
 */
typedef enum
{
    A,
    B,
    C,
    D,
    // C2C,
    home
} regionEnum;

/**
 * @brief 对于双板情况,遥控器和pc在云台,裁判系统在底盘
 *
 */

// cmd发布的底盘控制数据,由chassis订阅
typedef struct
{
    // 控制部分
    chassis_mode_e chassis_mode; // ？
    uint8_t clockwise_rotate_flag;
    uint8_t *pe_state;
    float speed;
    float lidar_com_speed; // 雷达补偿速度
    regionEnum region;
    // uint8_t gray; // 处理为crosscnt之后删除
} Chassis_Ctrl_Cmd_s;

typedef struct
{
    uint8_t water_flag;
    uint8_t set_plantCnt_flag; // 1: 6, 2: 12, 3: 18, 4: 24
    uint16_t lidar_left_dis;
    uint16_t lidar_right_dis;
    regionEnum region;
} Water_Ctrl_Cmd_s;

/* ----------------gimbal/shoot/chassis发布的反馈数据----------------*/
/**
 * @brief 由cmd订阅,其他应用也可以根据需要获取.
 *
 */

typedef struct
{
    uint8_t rotate_arrive;
    uint8_t rotate_vague_arrive;
} Chassis_Upload_Data_s;

typedef struct
{
    uint8_t water_finish_state; // water state (完成为1)
    uint8_t plant_cnt;          // number of plant
} Water_Upload_Data_s;

/*=================双板通信================*/
typedef enum
{
    SLIGHT = 0x01,
    GENERAL = 0x02, // Corrected typo from "GENERAl" to "GENERAL"
    SERIOUS = 0x03,
} Drought_Info_e;

typedef struct
{
    uint8_t plant_Cnt;
    uint8_t D_Drougnt_info;
    uint8_t recv_feedback_flag; // 接收到正确数据返回1
} Comm_Send_Data_s;             // 板间通信结构体

typedef struct
{
    Drought_Info_e drought_info[18];
    uint8_t recv_feedback_flag; // 接收到正确数据返回1
} Comm_Recv_Data_s;
#pragma pack() // 开启字节对齐,结束前面的#pragma pack(1)

#endif // !ROBOT_DEF_H