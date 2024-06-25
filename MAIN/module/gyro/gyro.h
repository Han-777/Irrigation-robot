#ifndef __GYRO_H
#define __GYRO_H

#include "stdio.h"
#include "sys.h"
#include "dma.h"
#define PI 3.14159265f

extern int gyro_init_flag;

extern float ori_target_Yaw, target_Yaw, current_yaw; // ori: fix, target_Yaw: dynamically changed
extern int clockwise_rotate_flag;
void GYRO_Init(void);
void TIMM7_Open(void);

void heading_Trans(void);

extern float Err_Set;
float Read_Yaw(void);
float Read_YawSpeed(void);
float Read_Roll(void);
// float N100N_PID(float kp,float ki,float kd);
void N100N_Turn_90angles(int site, float kp, float ki, float kd); // site表示转弯方向，0为左，1为右
void Close_usart6(void);
float Change_Err(float bias);

#define FRAME_HEADER 0X7B // Frame_header //??
#define FRAME_TAIL 0X7D	  // Frame_tail   //??
#define SEND_DATA_SIZE 24
#define RECEIVE_DATA_SIZE 11
#define IMU_RS 64
#define AHRS_RS 56
#define INSGPS_RS 80
#define RS485_RX_DE PAout(11) // 485????.0,??;1,??.
#define RS485_RX_RE PAout(12) // 485????.0,??;1,??.
typedef struct IMUData_Packet_t
{
	float gyroscope_x;			// unit: rad/s
	float gyroscope_y;			// unit: rad/s
	float gyroscope_z;			// unit: rad/s
	float accelerometer_x;		// m/s^2
	float accelerometer_y;		// m/s^2
	float accelerometer_z;		// m/s^2
	float magnetometer_x;		// mG
	float magnetometer_y;		// mG
	float magnetometer_z;		// mG
	float imu_temperature;		// C
	float Pressure;				// Pa
	float pressure_temperature; // C
	u32 Timestamp;				// us
} IMUData_Packet_t;

typedef struct AHRSData_Packet_t
{
	float RollSpeed;	// unit: rad/s
	float PitchSpeed;	// unit: rad/s
	float HeadingSpeed; // unit: rad/s
	float Roll;			// unit: rad
	float Pitch;		// unit: rad
	float Heading;		// unit: rad
	float Qw;			// w          //Quaternion
	float Qx;			// x
	float Qy;			// y
	float Qz;			// z
	u32 Timestamp;		// unit: us
} AHRSData_Packet_t;

extern u8 ttl_receive;

extern IMUData_Packet_t IMUData_Packet;
extern AHRSData_Packet_t AHRSData_Packet;

extern int rs_imutype;
extern int rs_ahrstype;
extern u8 Fd_data[64];
extern u8 Fd_rsimu[64];
extern u8 Fd_rsahrs[56];
void usart5_send(u8 data);

long long timestamp(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4);
void AHRSData2PC(void);
void IMUData2PC(void);

float XYZ_Target_Speed_transition(u8 High, u8 Low);
u8 TTL_Hex2Dec(void);
float DATA_Trans(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4);

#endif
