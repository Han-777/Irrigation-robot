#include <math.h>
#include "gyro.h"

int gyro_init_flag = 0;

float ori_target_Yaw = 0, target_Yaw = 0, current_yaw = 0, target_roll, current_roll = 0; // ori: fix, target_Yaw: dynamically changed
int clockwise_rotate_flag = 0;															  // rotate flag

IMUData_Packet_t IMUData_Packet;
AHRSData_Packet_t AHRSData_Packet;
u8 ttl_receive;
/*=============data receive (original data)=============*/
u8 Fd_data[64];	  // data receive buffer
u8 Fd_rsimu[64];  // (Inertial Measurement Unit) data store buffer
u8 Fd_rsahrs[56]; // (Attitude and Heading Reference System) data store buffer

int rs_imutype = 0; // 接收完成标志位
int rs_ahrstype = 0;
extern int Time_count;
void GYRO_Init(void)
{
	gyro_USART_Init(921600);
	GYRO_DMA_Config();
	gyro_init_flag = 1;
}
// float Target_Yaw;
// float target_yaw;
// int Flower_Count=0;

void UART5_IRQHandler(void)
{
	static u8 Count = 0;
	static u8 rs_count = 0;
	static u8 last_rsnum = 0;
	u8 Usart_Receive;
	static u8 rsimu_flag = 0; // 接收开始标志位
	static u8 rsacc_flag = 0;
	RS485_RX_RE = 0;
	RS485_RX_DE = 0;
	ttl_receive = 1;

	if (USART_GetITStatus(UART5, USART_IT_RXNE) == SET) // Check if data is received //判断是否接收到数据
	{
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
		Usart_Receive = USART_ReceiveData(UART5);									   // Read the data //读取数据
		Fd_data[Count] = Usart_Receive;												   // 串口数据填入数组
		if (((last_rsnum == FRAME_END) && (Usart_Receive == FRAME_HEAD)) || Count > 0) // 重新对帧
		{
			rs_count = 1;
			Count++;
			if ((Fd_data[1] == TYPE_IMU) && (Fd_data[2] == IMU_LEN))
				rsimu_flag = 1;
			if ((Fd_data[1] == TYPE_AHRS) && (Fd_data[2] == AHRS_LEN))
				rsacc_flag = 1;
		}
		else
			Count = 0;
		last_rsnum = Usart_Receive;

		// 接收完整后进入
		if (rsimu_flag == 1 && Count == IMU_RS) // 将本帧数据保存至Fd_rsimu数组中
		{
			Count = 0;
			rsimu_flag = 0;
			rs_imutype = 1;						  // imu data available flag
			if (Fd_data[IMU_RS - 1] == FRAME_END) // 帧尾校验
				memcpy(Fd_rsimu, Fd_data, sizeof(Fd_data));
		}
		if (rsacc_flag == 1 && Count == AHRS_RS)
		{
			Count = 0;
			rsacc_flag = 0;
			rs_ahrstype = 1; // ahrs data available flag
			if (Fd_data[AHRS_RS - 1] == FRAME_END)
				memcpy(Fd_rsahrs, Fd_data, sizeof(Fd_data));
		}
	}
}

/**
 * @brief  Handling the angle for pid
 *
 * to ensure the difference of target and measute is always
 * < 180 degree
 * @note   this function should be called after the inilization of ori_target_+Yaw (in chassis_Init())
 * @param    None
 * @return   None
 */
void heading_Trans(void)
{
	target_Yaw = ori_target_Yaw + 90 * clockwise_rotate_flag;
	// set the target_Yaw (0 - 360)
	while (target_Yaw > 360)
	{
		target_Yaw -= 360;
	}
	while (target_Yaw < -360)
	{
		target_Yaw += 360;
	}
	// handling the difference
	if (fabs(target_Yaw - current_yaw) > 180)
	{
		current_yaw += ((target_Yaw > current_yaw) ? 360 : -360);
	}
}

/*******************************
16进制转浮点型数据
*******************************/
int j, j1;
float b[50];
float a[50];
int F = 0;
int F_L = 0;
int F_R = 0;
int C = 0;
float ROLL;
u8 TTL_Hex2Dec(void)
{
	u8 i;
	if (rs_ahrstype == 1)
	{
		if (Fd_rsahrs[1] == TYPE_AHRS && Fd_rsahrs[2] == AHRS_LEN)
		{
			AHRSData_Packet.RollSpeed = DATA_Trans(Fd_rsahrs[7], Fd_rsahrs[8], Fd_rsahrs[9], Fd_rsahrs[10]);	   // 横滚角速度
			AHRSData_Packet.PitchSpeed = DATA_Trans(Fd_rsahrs[11], Fd_rsahrs[12], Fd_rsahrs[13], Fd_rsahrs[14]);   // 俯仰角速度
			AHRSData_Packet.HeadingSpeed = DATA_Trans(Fd_rsahrs[15], Fd_rsahrs[16], Fd_rsahrs[17], Fd_rsahrs[18]); // 偏航角速度

			AHRSData_Packet.Roll = DATA_Trans(Fd_rsahrs[19], Fd_rsahrs[20], Fd_rsahrs[21], Fd_rsahrs[22]);	  // 横滚角
			AHRSData_Packet.Pitch = DATA_Trans(Fd_rsahrs[23], Fd_rsahrs[24], Fd_rsahrs[25], Fd_rsahrs[26]);	  // 俯仰角
			AHRSData_Packet.Heading = DATA_Trans(Fd_rsahrs[27], Fd_rsahrs[28], Fd_rsahrs[29], Fd_rsahrs[30]); // 偏航角

			// heading_Trans();
			// for (j = 0; j <= 3 && F == 0; j++)
			// {
			// 	b[j] = AHRSData_Packet.Heading * 180 / PI;
			// 	if (j == 3)
			// 	{
			// 		F = 1;
			// 	}
			// 	//				delay_ms(10);
			// 	Target_Yaw = b[2];
			// }

			// for (j = 0; j <= 3 && C == 0; j++)
			// {
			// 	a[j] = AHRSData_Packet.Roll * 1000;
			// 	if (j == 3)
			// 	{
			// 		C = 1;
			// 	}
			// }
			// ROLL = a[2];

			// if (F_R == 1)
			// {
			// 	Target_Yaw = Target_Yaw + 90;
			// 	if (Target_Yaw >= 359.8)
			// 	{
			// 		Target_Yaw = Target_Yaw - 359.8;
			// 	}
			// 	F_R = 0;
			// }
			// if (F_L == 1)
			// {
			// 	Target_Yaw = Target_Yaw - 90;
			// 	if (Target_Yaw <= 0)
			// 	{
			// 		Target_Yaw = Target_Yaw + 359.8;
			// 	}
			// 	F_L = 0;
			// }
			AHRSData_Packet.Qw = DATA_Trans(Fd_rsahrs[31], Fd_rsahrs[32], Fd_rsahrs[33], Fd_rsahrs[34]); // 四元数
			AHRSData_Packet.Qx = DATA_Trans(Fd_rsahrs[35], Fd_rsahrs[36], Fd_rsahrs[37], Fd_rsahrs[38]);
			AHRSData_Packet.Qy = DATA_Trans(Fd_rsahrs[39], Fd_rsahrs[40], Fd_rsahrs[41], Fd_rsahrs[42]);
			AHRSData_Packet.Qz = DATA_Trans(Fd_rsahrs[43], Fd_rsahrs[44], Fd_rsahrs[45], Fd_rsahrs[46]);
			AHRSData_Packet.Timestamp = timestamp(Fd_rsahrs[47], Fd_rsahrs[48], Fd_rsahrs[49], Fd_rsahrs[50]); // 时间戳
			AHRSData2PC();
		}
		rs_ahrstype = 0;
	}
	if (rs_imutype == 1)
	{
		if (Fd_rsimu[1] == TYPE_IMU && Fd_rsimu[2] == IMU_LEN)
		{
			IMUData_Packet.gyroscope_x = DATA_Trans(Fd_rsimu[7], Fd_rsimu[8], Fd_rsimu[9], Fd_rsimu[10]); // 角速度
			IMUData_Packet.gyroscope_y = DATA_Trans(Fd_rsimu[11], Fd_rsimu[12], Fd_rsimu[13], Fd_rsimu[14]);
			IMUData_Packet.gyroscope_z = DATA_Trans(Fd_rsimu[15], Fd_rsimu[16], Fd_rsimu[17], Fd_rsimu[18]);

			IMUData_Packet.accelerometer_x = DATA_Trans(Fd_rsimu[19], Fd_rsimu[20], Fd_rsimu[21], Fd_rsimu[22]); // 线加速度
			IMUData_Packet.accelerometer_y = DATA_Trans(Fd_rsimu[23], Fd_rsimu[24], Fd_rsimu[25], Fd_rsimu[26]);
			IMUData_Packet.accelerometer_z = DATA_Trans(Fd_rsimu[27], Fd_rsimu[28], Fd_rsimu[29], Fd_rsimu[30]);

			IMUData_Packet.magnetometer_x = DATA_Trans(Fd_rsimu[31], Fd_rsimu[32], Fd_rsimu[33], Fd_rsimu[34]); // 磁力计数据
			IMUData_Packet.magnetometer_y = DATA_Trans(Fd_rsimu[35], Fd_rsimu[36], Fd_rsimu[37], Fd_rsimu[38]);
			IMUData_Packet.magnetometer_z = DATA_Trans(Fd_rsimu[39], Fd_rsimu[40], Fd_rsimu[41], Fd_rsimu[42]);

			IMUData_Packet.Timestamp = timestamp(Fd_rsimu[55], Fd_rsimu[56], Fd_rsimu[57], Fd_rsimu[58]); // 时间戳
			IMUData2PC();
		}
		rs_imutype = 0;
	}
	return 0;
}

/*************
实现16进制的can数据转换成浮点型数据
* brief： transfer data from hexadecimaml to floating-point values
****************/
float DATA_Trans(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4)
{
	long long transition_32;
	float tmp = 0;
	int sign = 0;
	int exponent = 0;
	float mantissa = 0;
	transition_32 = 0;
	transition_32 |= Data_4 << 24;
	transition_32 |= Data_3 << 16;
	transition_32 |= Data_2 << 8;
	transition_32 |= Data_1;
	sign = (transition_32 & 0x80000000) ? -1 : 1; // 符号位
	// 先右移操作，再按位与计算，出来结果是30到23位对应的e
	exponent = ((transition_32 >> 23) & 0xff) - 127;
	// 将22~0转化为10进制，得到对应的x系数
	mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
	tmp = sign * mantissa * pow(2, exponent);
	return tmp;
}
long long timestamp(u8 Data_1, u8 Data_2, u8 Data_3, u8 Data_4)
{
	u32 transition_32;
	transition_32 = 0;
	transition_32 |= Data_4 << 24;
	transition_32 |= Data_3 << 16;
	transition_32 |= Data_2 << 8;
	transition_32 |= Data_1;
	return transition_32;
}
void AHRSData2PC(void)
{
	//	printf("AHRS: The RollSpeed =  %f\r\n", AHRSData_Packet.RollSpeed);
	//	printf("AHRS: The PitchSpeed =  %f\r\n", AHRSData_Packet.PitchSpeed);
	//	printf("AHRS: The HeadingSpeed =  %f\r\n", AHRSData_Packet.HeadingSpeed);
	//	printf("AHRS: The Roll =  %f\r\n", AHRSData_Packet.Roll);
	//	printf("AHRS: The Pitch =  %f\r\n", AHRSData_Packet.Pitch);
	//	printf("AHRS: The Heading =  %f\r\n", AHRSData_Packet.Heading);
	//	printf("AHRS: The Quaternion.Qw =  %f\r\n", AHRSData_Packet.Qw);
	//	printf("AHRS: The Quaternion.Qx =  %f\r\n", AHRSData_Packet.Qx);
	//	printf("AHRS: The Quaternion.Qy =  %f\r\n", AHRSData_Packet.Qy);
	//	printf("AHRS: The Quaternion.Qz =  %f\r\n", AHRSData_Packet.Qz);
	//	printf("AHRS: The Timestamp =  %d\r\n", AHRSData_Packet.Timestamp);
}
void IMUData2PC(void)
{
	//	printf("Now start sending IMU data.\r\n");
	//	printf("IMU: The gyroscope_x =  %f\r\n", IMUData_Packet.gyroscope_x);
	//	printf("IMU:The gyroscope_y =  %f\r\n", IMUData_Packet.gyroscope_y);
	//	printf("IMU:The gyroscope_z =  %f\r\n", IMUData_Packet.gyroscope_z);
	//	printf("IMU:The accelerometer_x =  %f\r\n", IMUData_Packet.accelerometer_x);
	//	printf("IMU:The accelerometer_y =  %f\r\n", IMUData_Packet.accelerometer_y);
	//	printf("IMU:The accelerometer_z =  %f\r\n", IMUData_Packet.accelerometer_z);
	//	printf("IMU:The magnetometer_x =  %f\r\n", IMUData_Packet.magnetometer_x);
	//	printf("IMU:The magnetometer_y =  %f\r\n", IMUData_Packet.magnetometer_y);
	//	printf("IMU:The magnetometer_z =  %f\r\n", IMUData_Packet.magnetometer_z);
	//	printf("IMU:The Timestamp =  %d\r\n", IMUData_Packet.Timestamp);
	//	printf("Now the data of IMU has been sent.\r\n");
}

// void usart5_send(u8 data)
//{
//	UART5->DR = data;
//	while ((UART5->SR & 0x40) == 0)
//		;
// }

float Read_Yaw(void)
{
	return AHRSData_Packet.Heading * 180.0 / PI;
}
float Read_YawSpeed(void)
{
	return AHRSData_Packet.HeadingSpeed * 180 / PI;
}
float Read_Roll(void)
{
	return AHRSData_Packet.Roll * 1000;
}
float Change_Err(float bias)
{
	if (Abs(bias) <= 0.3)
	{
		bias = 0;
	}
	if (bias > 0.3 && bias <= 5)
	{
		bias = 2;
	}
	if (bias > 5 && bias <= 10)
	{
		bias = 2.4;
	}
	if (bias > 10 && bias <= 15)
	{
		bias = 2.8;
	}
	if (bias > 15 && bias <= 20)
	{
		bias = 3.2;
	}
	if (bias > 20 && bias <= 25)
	{
		bias = 3.6;
	}
	if (bias > 25 && bias <= 50)
	{
		bias = 4;
	}
	if (bias >= -5 && bias < -0.3)
	{
		bias = -2;
	}
	if (bias >= -10 && bias < -5)
	{
		bias = -2.4;
	}
	if (bias >= -15 && bias < -10)
	{
		bias = -2.8;
	}
	if (bias >= -20 && bias < -15)
	{
		bias = -3.2;
	}
	if (bias >= -25 && bias < -20)
	{
		bias = -3.6;
	}
	if (bias >= -30 && bias <= -50)
	{
		bias = -4;
	}
	if (Abs(bias) > 50)
	{
		bias = 400;
	}
	return bias;
}

// float target_yaw_A; // 时钟方向的对角
// float min;
// float max;
// float New_Yaw;
// float Set_Yaw;
// int PWM_Turn = 0;
// float Err_L_Angle, Err_R_Angle;
// float Err_L_Last_Angle, Err_R_Lats_Angle;
// void N100N_Turn_90angles(int site, float kp, float ki, float kd) // site表示转弯方向，0为左，1为右
//{
//	//	if(site==1)
//	//	{
//	//		if(N_Flag==5)
//	//		{
//	//
//	////			TIM7_Int_Init(1000-1,840-1);//10ms进入一次中断s
//	////			delay_ms(100);
//	////			site=0;
//	////
//	//			Car_Load(100,100);
//	//			delay_ms(100);
//	//		}
//	//    else if(N_Flag==6)
//	//		{
//	////			TIM7_Int_Init(1000-1,840-1);//10ms进入一次中断s
//	////			delay_ms(200);
//	////			site=0;
//	////
//	//			Car_Load(100,100);
//	//			delay_ms(100);
//	//		}
//	//		delay_ms(200);
//	//	}
//	Err_Set = 90;
//	while (Abs(Err_Set) > 0)
//	{
//		//		delay_ms(50);
//		TTL_Hex2Dec();
//		//		printf("err_set=%f,k=%d\r\n",Err_Set,k);
//		target_yaw = Target_Yaw;
//		New_Yaw = Read_Yaw();
//		if (site == 1) // 右偏变大为正为标准，实践值比目标值大为正
//		{
//			New_Yaw = Read_Yaw();
//			Set_Yaw = target_yaw + 90;
//			if (Set_Yaw >= 360)
//			{
//				Set_Yaw = (((int)(Set_Yaw * 100)) % 36000) / 100.0;
//			}
//			if (target_yaw >= 0 && target_yaw <= 180)
//			{
//				target_yaw_A = target_yaw + 180;
//			}
//			if (target_yaw > 180 && target_yaw <= 360)
//			{
//				target_yaw_A = target_yaw - 180;
//			}
//			min = Min(target_yaw, target_yaw_A);
//			max = Max(target_yaw, target_yaw_A);
//			if (target_yaw <= min)
//			{
//				Err_Set = ((int)(100 * (target_yaw - New_Yaw) + 36000) % 36000) / 100.0;
//			}
//			if (target_yaw >= max)
//			{
//				Err_Set = ((int)(100 * (New_Yaw - target_yaw) + 36000) % 36000) / 100.0;
//			}
//			if (New_Yaw > min && New_Yaw < max)
//			{
//				Err_Set = ((int)(100 * (Abs(target_yaw - New_Yaw)) + 36000) % 36000) / 100.0;
//			}
//			if (New_Yaw >= 0 && New_Yaw <= max)
//			{
//				if (New_Yaw > target_yaw || New_Yaw <= (target_yaw - 180))
//				{
//					Err_Set = Err_Set;
//				}
//				else
//				{
//					Err_Set = -Err_Set;
//				}
//			}
//			if (New_Yaw > max && New_Yaw <= 360 && target_yaw <= target_yaw_A)
//			{
//				if (New_Yaw > target_yaw)
//				{
//					Err_Set = -Err_Set;
//				}
//				else
//				{
//					Err_Set = Err_Set;
//				}
//			}
//			Err_Set = -Err_Set + 90;
//		}
//		if (site == 0)
//		{
//			New_Yaw = Read_Yaw();
//			Set_Yaw = target_yaw + 90;
//			if (Set_Yaw >= 360)
//			{
//				Set_Yaw = (((int)(100 * Set_Yaw)) % 36000) / 100.0;
//			}
//			if (target_yaw >= 0 && target_yaw <= 180)
//			{
//				target_yaw_A = target_yaw + 180;
//			}
//			if (target_yaw > 180 && target_yaw <= 360)
//			{
//				target_yaw_A = target_yaw - 180;
//			}
//			min = Min(target_yaw, target_yaw_A);
//			max = Max(target_yaw, target_yaw_A);
//			if (target_yaw <= min)
//			{
//				Err_Set = ((int)(100 * (target_yaw - New_Yaw) + 36000) % 36000) / 100.0;
//			}
//			if (target_yaw >= max)
//			{
//				Err_Set = ((int)(100 * (New_Yaw - target_yaw) + 36000) % 36000) / 100.0;
//			}
//			if (New_Yaw > min && New_Yaw < max)
//			{
//				Err_Set = ((int)(100 * (Abs(target_yaw - New_Yaw)) + 36000) % 36000) / 100.0;
//			}
//			if (New_Yaw >= 0 && New_Yaw <= max)
//			{
//				if (New_Yaw > target_yaw || New_Yaw <= (target_yaw - 180))
//				{
//					Err_Set = Err_Set;
//				}
//				else
//				{
//					Err_Set = -Err_Set;
//				}
//			}
//			if (New_Yaw > max && New_Yaw <= 360 && target_yaw <= target_yaw_A)
//			{
//				if (New_Yaw > target_yaw)
//				{
//					Err_Set = -Err_Set;
//				}
//				else
//				{
//					Err_Set = Err_Set;
//				}
//			}
//			Err_Set = Err_Set + 90;
//		}
//		if (Abs(Err_Set) <= 0.5)
//		{
//			Err_Set = 0;
//		}

//		if (site == 0) // 左转
//		{
//			if (Abs(Err_Set) <= 1)
//			{
//				//				F=0;//用来更新陀螺仪数据
//				k = 0; // 把k置回0，避免在主函数和中断一起执行
//				set = 1;
//				Car_stop();

//				TTL_Hex2Dec();
//				delay_ms(200);
//				F_L = 1;
//				delay_ms(200);
//				TIM7_Int_Init(1000 - 1, 840 - 1); // 打开定时器
//				delay_ms(1200);
//				FLAG = 1;
//				set = 0;
//				if (N_Flag == 2 || N_Flag == 4 || N_Flag == 6)
//				{
//					EXTIX_Init();
//				}
//				Err_Set = 0;
//			}
//			else
//			{
//				if (Err_Set >= 0.5 && Err_Set <= 15)
//				{
//					Err_R_Angle = 2.2;
//				}
//				if (Err_Set > 15 && Err_Set <= 30)
//				{
//					Err_R_Angle = 2.2;
//				}
//				if (Err_Set > 30 && Err_Set <= 45)
//				{
//					Err_R_Angle = 2.4;
//				}
//				if (Err_Set > 45 && Err_Set <= 60)
//				{
//					Err_R_Angle = 2.6;
//				}
//				if (Err_Set > 60 && Err_Set <= 75)
//				{
//					Err_R_Angle = 2.8;
//				}
//				if (Err_Set > 75 && Err_Set <= 90)
//				{
//					Err_R_Angle = 3.0;
//				}
//				if (Err_Set > 90)
//				{
//					Err_R_Angle = 3.0;
//				}
//				//////////////////
//				if (Err_Set >= -15 && Err_Set <= -0.5)
//				{
//					Err_R_Angle = -2.2;
//				}
//				if (Err_Set >= -30 && Err_Set < -15)
//				{
//					Err_R_Angle = -2.2;
//				}
//				if (Err_Set >= -45 && Err_Set < -30)
//				{
//					Err_R_Angle = -2.4;
//				}
//				if (Err_Set >= -60 && Err_Set < -45)
//				{
//					Err_R_Angle = -2.6;
//				}
//				if (Err_Set >= -75 && Err_Set < -60)
//				{
//					Err_R_Angle = -2.8;
//				}
//				if (Err_Set >= -90 && Err_Set < -75)
//				{
//					Err_R_Angle = -3;
//				}
//				if (Err_Set < -90)
//				{
//					Err_R_Angle = -3;
//				}
//				PWM_Turn = (kp * Err_R_Angle) + (kd * (Err_R_Angle - Err_R_Lats_Angle)); // 效果如果不好可以换成陀螺仪速度
//				Err_R_Lats_Angle = Err_R_Angle;
//				Limit(200, -200, &PWM_Turn, &PWM_Turn);
//				Car_Load(-PWM_Turn, PWM_Turn);
//				//				delay_ms(10);
//			}
//		}
//		if (site == 1) // 右转
//		{
//			if (Abs(Err_Set) <= 1.1) // 可以变
//			{

//				k = 0; // 把k置回0，避免在主函数和中断一起执行
//				set = 1;
//				Car_stop();
//				delay_ms(500);
//				//				F=0;
//				TTL_Hex2Dec();
//				delay_ms(200);
//				F_R = 1;
//				TIM7_Int_Init(1000 - 1, 840 - 1); // 打开定时器
//				delay_ms(1200);
//				FLAG = 1;
//				set = 0;
//				if (N_Flag == 2 || N_Flag == 4 || N_Flag == 6)
//				{
//					EXTIX_Init();
//				}
//				Err_Set = 0;
//			}
//			else
//			{
//				if (Err_Set >= 0.5 && Err_Set <= 15)
//				{
//					Err_R_Angle = 2.2;
//				}
//				if (Err_Set > 15 && Err_Set <= 30)
//				{
//					Err_R_Angle = 2.2;
//				}
//				if (Err_Set > 30 && Err_Set <= 45)
//				{
//					Err_R_Angle = 2.4;
//				}
//				if (Err_Set > 45 && Err_Set <= 60)
//				{
//					Err_R_Angle = 2.6;
//				}
//				if (Err_Set > 60 && Err_Set <= 75)
//				{
//					Err_R_Angle = 2.8;
//				}
//				if (Err_Set > 75 && Err_Set <= 90)
//				{
//					Err_R_Angle = 3.0;
//				}
//				if (Err_Set > 90)
//				{
//					Err_R_Angle = 3.0;
//				}
//				//////////////////
//				if (Err_Set >= -15 && Err_Set <= -0.5)
//				{
//					Err_R_Angle = -2;
//				}
//				if (Err_Set >= -30 && Err_Set < -15)
//				{
//					Err_R_Angle = -2.2;
//				}
//				if (Err_Set >= -45 && Err_Set < -30)
//				{
//					Err_R_Angle = -2.4;
//				}
//				if (Err_Set >= -60 && Err_Set < -45)
//				{
//					Err_R_Angle = -2.6;
//				}
//				if (Err_Set >= -75 && Err_Set < -60)
//				{
//					Err_R_Angle = -2.8;
//				}
//				if (Err_Set >= -90 && Err_Set < -75)
//				{
//					Err_R_Angle = -3.0;
//				}
//				if (Err_Set < -90)
//				{
//					Err_R_Angle = -3.0;
//				}
//				PWM_Turn = (kp * Err_R_Angle) + (kd * (Err_R_Angle - Err_R_Lats_Angle)); // 效果如果不好可以换成陀螺仪速度
//				Err_R_Lats_Angle = Err_R_Angle;
//				Limit(200, -200, &PWM_Turn, &PWM_Turn);
//				Car_Load(PWM_Turn, -PWM_Turn);
//				//				delay_ms(10);
//			}
//		}
//	}
//}
