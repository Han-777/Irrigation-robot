#ifndef __BALANCETANK_H
#define __BALANCETANK_H

#include "sys.h"
#include "servo.h"

#define PI 3.1415926
// ����pid
 typedef volatile struct
{
	float desired;              //����ֵ
	float offset;               //
	float prevError;            //ǰһ�����ֵ
	float integ;                //������
	float kp;                   //����
	float ki;                   //����
	float kd;                   //΢��
	float IntegLimitHigh;       //����������
	float IntegLimitLow;        //����������
	float measured;             //����ֵ
	float out;                  //�����
	float OutLimitHigh;         //���������
	float OutLimitLow;          //���������
}PidObject;

typedef struct
{
	short roll;
	short pitch;
	uint16_t Dist_left;
}Data_Para;

typedef struct
{
	float angle;
	float _angle;
}Servos;


// my
typedef struct
{
	u8 enable_lim_sum_error	: 1;
	u8 enable_lim_ouput		: 1;
	
	float kp;
	float ki;
	float kd;
	
	float kiout_lim;
	float lim_output;

	float sum_error;
	float last_error;
	float last_last_error;
	
	float kd_output;
	float ki_output;
	float kp_output;

	float output;
	float error;
}  PID;

/*=====================public========================*/
 extern float pitch,roll,yaw; 		//ŷ����
// extern short aacx,aacy,aacz;		  //���ٶȴ�����ԭʼ����
// extern short gyrox,gyroy,gyroz;	//������ԭʼ����
// extern float a;
int mpu_control(void);
void Control_Init(void);
void Control_loop(void);


extern PidObject Pid_roll;
extern PidObject Pid_pitch;
extern PidObject *(pidobject[]);
extern Data_Para  Sending_data;

//void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid���ݳ�ʼ��
//void pidUpdate(PidObject* pid);                                                                            		 //PID����
//void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //����PID
//void Pid_input_parameters(PidObject **pid);                                                                    //pid��ڲ�������                   
//void Pid_Calculate(PidObject **pid);
//void Send_data(Data_Para *data);
//void PWM_Calculate(PidObject **pid);



#endif
