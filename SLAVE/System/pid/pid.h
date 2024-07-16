#ifndef __PID_H
#define __PID_H
#include "sys.h"

typedef volatile struct
{
	float desired;     //期望值
	float offset;      //
	float prevError;    //前一次误差值
	float integ;        //积分量
	float kp;           //比例
	float ki;          //积分
	float kd;           //微分
	float IntegLimitHigh;       //< integral limit
	float IntegLimitLow;
	float measured;     //测量值
	float out;
	float OutLimitHigh;
	float OutLimitLow;
}PidObject;

extern PidObject Pidroll;
extern PidObject Pidpitch;
extern PidObject Pidyaw;

extern PidObject Pidratex;
extern PidObject Pidratey;
extern PidObject Pidratez;

extern PidObject Pidhight;
extern PidObject Pidhightrate;

extern PidObject *(pidobject[]);


void CascadePID(PidObject* pidRate,PidObject* pidAngE,const float dt);  //串级PID
void pidRest(PidObject **pid,const uint8_t len); //pid数据复位
void pidUpdate(PidObject* pid,const float dt);  //PID
#endif
