#ifndef __BALANCETANK_H
#define __BALANCETANK_H

#include "sys.h"

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

/*=====================public========================*/
extern float pitch,roll,yaw; 		//ŷ����
extern short aacx,aacy,aacz;		  //���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����
// extern float a;
int mpu_get(void);
void MPU_Display_Spect(void);


extern PidObject Pid_roll;
extern PidObject Pid_pitch;
extern PidObject *(pidobject[]);
extern Data_Para  Sending_data;

void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid���ݳ�ʼ��
void pidUpdate(PidObject* pid);                                                                            		 //PID����
void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //����PID
void Pid_input_parameters(PidObject **pid);                                                                    //pid��ڲ�������                   
void Pid_Calculate(PidObject **pid);
void Send_data(Data_Para *data);
void PWM_Calculate(PidObject **pid);



#endif
