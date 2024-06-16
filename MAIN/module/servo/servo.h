#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"

typedef enum
{
    pitch_servo = 0x01, // 01
    yaw_servo = 0x02,    // 10
} servoName;

// #define sensor GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)  //检测到目标低电平

// #define Servo_ENABLE 			1		//开启扫描
// #define Speed_up_ENABLE 	1		//快速模式

// //机械臂角度
// #define Scan_angle_A 		165		//扫描角度
// #define Scan_angle_B 		160		//扫描角度
// #define Scan_angle_C 		160  	//扫描角度
// #define Scan_angle_D 		165		//扫描角度

// #define Correct_angle    105  //终点矫正角度

// #define length_A 27.50//浇水的机械臂长度
// #define H    32.50//激光底座到舵机云台的垂直  H要尽量低
// #define D_d  20.00//车的几何中心到最外侧距离
// #define R_R  9.50//圆形花盆的半径
// //#define Water_angle_A 	122   //浇水角度
// //#define Water_angle_B 	134		//浇水角度
// //#define Water_angle_C 	128  	//浇水角度
// //#define Water_angle_D 	125		//浇水角度

// #define Lift_angle 			110		//抬高角度//机械臂的垂直角度 90为直角,
// #define Balance_angle 	195		//平衡角度

// //云台角度
// #define Left_D					 202   //D区云台
// #define Right_D					98		//D区云台

// #define Mid							150		//归中//云台的中央角度

// #define Left_mid 			 	 83		//左侧居中
// #define Right_mid 			215		//右侧居中

// //TIM_SetCompare4(TIM8,195);	//平衡角度
// //TIM_SetCompare4(TIM8,115);  //浇水angle

// extern int plant;

// // void Rotation(int site, int direct);
// // void Water(int site,int times);
// // void get_N(int site);
// // double Get_Water_Angle(void);
// // int Get_Servo_Pwm(double ANGLE);
// // void serove_move (int num,int now_angle,int to_angle,int delaytime);
void servo_Init_All(void);
void Servo_Pitch_Control(uint16_t Compare);
void Servo_Yaw_Control(uint16_t Compare);
void ServoMove(uint16_t angel1, uint16_t angel2);
void ServoControl(servoName name, uint16_t currentAngle, uint16_t targetAngle, uint16_t delay_time);

#endif
