#ifndef __PID_H
#define __PID_H
#include "sys.h"

typedef volatile struct
{
	float desired;     //����ֵ
	float offset;      //
	float prevError;    //ǰһ�����ֵ
	float integ;        //������
	float kp;           //����
	float ki;          //����
	float kd;           //΢��
	float IntegLimitHigh;       //< integral limit
	float IntegLimitLow;
	float measured;     //����ֵ
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


void CascadePID(PidObject* pidRate,PidObject* pidAngE,const float dt);  //����PID
void pidRest(PidObject **pid,const uint8_t len); //pid���ݸ�λ
void pidUpdate(PidObject* pid,const float dt);  //PID
#endif
