#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"

typedef enum
{
    pitch_servo = 0x01, // 01
    yaw_servo = 0x02,    // 10
} servoName;

// #define sensor GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)  //��⵽Ŀ��͵�ƽ

// #define Servo_ENABLE 			1		//����ɨ��
// #define Speed_up_ENABLE 	1		//����ģʽ

// //��е�۽Ƕ�
// #define Scan_angle_A 		165		//ɨ��Ƕ�
// #define Scan_angle_B 		160		//ɨ��Ƕ�
// #define Scan_angle_C 		160  	//ɨ��Ƕ�
// #define Scan_angle_D 		165		//ɨ��Ƕ�

// #define Correct_angle    105  //�յ�����Ƕ�

// #define length_A 27.50//��ˮ�Ļ�е�۳���
// #define H    32.50//��������������̨�Ĵ�ֱ  HҪ������
// #define D_d  20.00//���ļ������ĵ���������
// #define R_R  9.50//Բ�λ���İ뾶
// //#define Water_angle_A 	122   //��ˮ�Ƕ�
// //#define Water_angle_B 	134		//��ˮ�Ƕ�
// //#define Water_angle_C 	128  	//��ˮ�Ƕ�
// //#define Water_angle_D 	125		//��ˮ�Ƕ�

// #define Lift_angle 			110		//̧�߽Ƕ�//��е�۵Ĵ�ֱ�Ƕ� 90Ϊֱ��,
// #define Balance_angle 	195		//ƽ��Ƕ�

// //��̨�Ƕ�
// #define Left_D					 202   //D����̨
// #define Right_D					98		//D����̨

// #define Mid							150		//����//��̨������Ƕ�

// #define Left_mid 			 	 83		//������
// #define Right_mid 			215		//�Ҳ����

// //TIM_SetCompare4(TIM8,195);	//ƽ��Ƕ�
// //TIM_SetCompare4(TIM8,115);  //��ˮangle

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
