//#include "pid.h"

//PidObject Pidroll;
//PidObject Pidpitch;
//PidObject Pidyaw;

//PidObject Pidratex;
//PidObject Pidratey;
//PidObject Pidratez;

//PidObject Pidhight;
//PidObject Pidhightrate;

//PidObject *(pidobject[])={&Pidroll,&Pidpitch,&Pidyaw,&Pidratex,&Pidratey,&Pidratez
//                            ,&Pidhight,&Pidhightrate};

//void pidRest(PidObject **pid,const uint8_t len) //pid���ݸ�λ
//{
//	uint8_t i=0;
//	for(i=0;i<len;i++)
//	{
//		pid[i]->integ=0;
//		pid[i]->prevError=0;
//		pid[i]->out=0;
//	}
//}

//void pidUpdate(PidObject* pid,const float dt)  //PID
//{
//	float error;
//	float deriv;
//	
//	error = pid->desired-pid->measured;     //���
//	pid->integ += error*dt;                  //������
//	deriv = (error-pid->prevError)/dt;         //΢����
//	pid->out = pid->kp*error + pid->ki*pid->integ + pid->kd*deriv;    //���
//	pid->prevError = error;                  //��һ�������

//}

//void CascadePID(PidObject* pidRate,PidObject* pidAngE,const float dt) //����PID
//{
//	pidUpdate(pidAngE,dt);
//	pidRate->desired=pidAngE->out;
//	pidUpdate(pidRate,dt);
//}






