#ifndef __BALANCETANK_H
#define __BALANCETANK_H

#include "sys.h"

#define PI 3.1415926
// 增量pid
 typedef volatile struct
{
	float desired;              //期望值
	float offset;               //
	float prevError;            //前一次误差值
	float integ;                //积分量
	float kp;                   //比例
	float ki;                   //积分
	float kd;                   //微分
	float IntegLimitHigh;       //积分量上限
	float IntegLimitLow;        //积分量下限
	float measured;             //测量值
	float out;                  //输出量
	float OutLimitHigh;         //输出量上限
	float OutLimitLow;          //输出量下限
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
extern float pitch,roll,yaw; 		//欧拉角
extern short aacx,aacy,aacz;		  //加速度传感器原始数据
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
// extern float a;
int mpu_get(void);
void MPU_Display_Spect(void);


extern PidObject Pid_roll;
extern PidObject Pid_pitch;
extern PidObject *(pidobject[]);
extern Data_Para  Sending_data;

void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid数据初始化
void pidUpdate(PidObject* pid);                                                                            		 //PID更新
void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //串级PID
void Pid_input_parameters(PidObject **pid);                                                                    //pid入口参数更新                   
void Pid_Calculate(PidObject **pid);
void Send_data(Data_Para *data);
void PWM_Calculate(PidObject **pid);



#endif
