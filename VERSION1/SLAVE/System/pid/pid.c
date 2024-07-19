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

//void pidRest(PidObject **pid,const uint8_t len) //pid数据复位
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
//	error = pid->desired-pid->measured;     //误差
//	pid->integ += error*dt;                  //积分量
//	deriv = (error-pid->prevError)/dt;         //微分量
//	pid->out = pid->kp*error + pid->ki*pid->integ + pid->kd*deriv;    //输出
//	pid->prevError = error;                  //上一次误差量

//}

//void CascadePID(PidObject* pidRate,PidObject* pidAngE,const float dt) //串级PID
//{
//	pidUpdate(pidAngE,dt);
//	pidRate->desired=pidAngE->out;
//	pidUpdate(pidRate,dt);
//}






