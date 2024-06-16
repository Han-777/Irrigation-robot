#ifndef __BALANCETANK_H
#define __BALANCETANK_H

#include "sys.h"
#include "servo.h"

#define PI 3.1415926
// ����pid
typedef volatile struct
{
	float desired;		  // ����ֵ
	float offset;		  //
	float prevError;	  // ǰһ�����ֵ
	float integ;		  // ������
	float kp;			  // ����
	float ki;			  // ����
	float kd;			  // ΢��
	float IntegLimitHigh; // ����������
	float IntegLimitLow;  // ����������
	float measured;		  // ����ֵ
	float out;			  // �����
	float OutLimitHigh;	  // ���������
	float OutLimitLow;	  // ���������
} PidObject;

typedef struct
{
	short roll;
	short pitch;
	uint16_t Dist_left;
} Data_Para;

typedef struct
{
	float angle;
	float _angle;
} Servos;

// my
typedef volatile struct
{
	u8 enable_lim_sum_error : 1;
	u8 enable_lim_ouput : 1;

	float kp;
	float ki;
	float kd;

	//	float sum_error_lim;
	float lim_integral;
	float lim_output;

	float sum_error;
	float last_error;
	// float last_last_error;

	float output;
	float error;
} PID;

/// @brief ����ʽpid: �ٶȻ�
typedef volatile struct
{
	u8 enable_lim_sum_error : 1;
	u8 enable_lim_output : 1; // 1-bit ��־���Ƿ��������������
	float kp;				  // ����ϵ��
	float ki;				  // ����ϵ��
	float kd;				  // ΢��ϵ��

	float lim_integral;
	float lim_output; // �������

	float last_error;	   // ��һ�ε����
	float last_last_error; // ���ϴε����

	float delta_output; // �����������
	float output;		// ���յĿ������
	float error;		// ��ǰ���
	float sum_error;	// for test
} Increment_PID;
/*=====================public========================*/
extern float pitch, roll, yaw; // ŷ����
// extern short aacx,aacy,aacz;		  //���ٶȴ�����ԭʼ����
// extern short gyrox,gyroy,gyroz;	//������ԭʼ����
// extern float a;
int mpu_control(void);
void Control_Init(void);
void Control_loop(void);

// void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid���ݳ�ʼ��
// void pidUpdate(PidObject* pid);                                                                            		 //PID����
// void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //����PID
// void Pid_input_parameters(PidObject **pid);                                                                    //pid��ڲ�������
// void Pid_Calculate(PidObject **pid);
// void Send_data(Data_Para *data);
// void PWM_Calculate(PidObject **pid);

#endif
