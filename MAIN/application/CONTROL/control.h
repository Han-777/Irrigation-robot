#ifndef _CONTROL__H
#define _CONTROL__H
#include "sys.h"


void Err_s_Limit(float Err_S_Limit,float* P_L,float* P_R);
void TIM7_IRQHandler(void);
int Velocity(int Target,int mode,int encoder,float kp,float ki,float kd);
float Level(float target_yaw_a,float kp,float ki,float kd);





//typedef volatile struct
//{
//	float desired;              //???
//	float offset;               //
//	float prevError;            //??????
//	float integ;                //???
//	float kp;                   //??
//	float ki;                   //??
//	float kd;                   //??
//	float IntegLimitHigh;       //?????
//	float IntegLimitLow;        //?????
//	float measured;             //???
//	float out;                  //???
//	float OutLimitHigh;         //?????
//	float OutLimitLow;          //?????
//}PidObject;

//typedef struct
//{
//	short dist_left;
//	short dist_right;
//	
//}Data_Para;

//typedef struct//????????
//{
//	float left;
//	float right;
//}TFMINI;

//extern PidObject Pid_tfmini_left;
//extern PidObject Pid_tfmini_right;
//extern PidObject *(pidobject[]);
//extern Data_Para  Sending_data;

//void pid_Init(PidObject **pid,float kp,float ki,float kd,float integ_limit,float out_limit,const uint8_t len); //pid?????
//void pidUpdate(PidObject* pid);                                                                            		 //PID??
//void CascadePID(PidObject* pid_inside,PidObject* pid_outside);                                                 //??PID
//void Pid_input_parameters(PidObject **pid);                                                                    //pid??????                   
//void Pid_Calculate(PidObject **pid);










#endif
