#include "balanceTank.h"
#include "OLED.h"
#include "inv_mpu.h"
PidObject Pid_roll; // 舵机x,y方向pid结构体
PidObject Pid_pitch;
PidObject *(pidobject[]) = {&Pid_roll, &Pid_pitch}; // 舵机pid指针数组

//void pid_Init(PidObject **pid, float kp, float ki, float kd, float integ_limit, float out_limit, const uint8_t len) // pid数据初始化
//{
//   uint8_t i = 0;
//   for (i = 0; i < len; i++) // len = 2
//   {
//       pid[i]->integ = 0;
//       pid[i]->prevError = 0;
//       pid[i]->out = 0;
//       pid[i]->kp = kp;
//       pid[i]->ki = ki;
//       pid[i]->kd = kd;
//       pid[i]->IntegLimitHigh = integ_limit;
//       pid[i]->IntegLimitLow = -integ_limit;
//       pid[i]->OutLimitHigh = out_limit;
//       pid[i]->OutLimitLow = -out_limit;
//   }
//}

//void pidUpdate(PidObject *pid)
//{
//   float error;
//   float deriv;

//   error = pid->desired - pid->measured; // 误差
//   pid->integ += error;                  // 积分量
//   if (pid->integ > pid->IntegLimitHigh) // 积分量限幅
//       pid->integ = pid->IntegLimitHigh;
//   if (pid->integ < pid->IntegLimitLow)
//       pid->integ = pid->IntegLimitLow;
//   deriv = (error - pid->prevError);                                    // 微分量
//   pid->out = pid->kp * error + pid->ki * pid->integ + pid->kd * deriv; // 输出
//   pid->prevError = error;                                              // 上一次误差量
//   if (pid->out > pid->OutLimitHigh)                                    // 对输出进行限幅
//       pid->out = pid->OutLimitHigh;
//   if (pid->out < pid->OutLimitLow)
//       pid->out = pid->OutLimitLow;
//}

//void CascadePID(PidObject *pid_inside, PidObject *pid_outside) // 串级PID
//{
//   pidUpdate(pid_outside);
//   pid_inside->desired = pid_outside->out;
//   pidUpdate(pid_inside);
//}

//// pid入口参数更新
//void Pid_input_parameters(PidObject **pid)
//{
//   u8 i = 0;
//   for (i = 0; i < 2; i++)
//   {
//       pid[i]->desired = 0;
//   }
//   pid[0]->measured = roll;
//   pid[1]->measured = pitch;
//}

//void Pid_Calculate(PidObject **pid)
//{
//   Pid_input_parameters(pid);
//   for (uint8_t i = 0; i < 2; i++)
//   {
//       pidUpdate(pid[i]);
//   }
//}

//char tx_data[8] = {0x0E, 0x0F};
//Data_Para Sending_data;

//void Send_data(Data_Para *data)
//{
//   data->roll = (short)(roll * 100);
//   data->pitch = ((short)(pitch * 100));
//   //	data->Dist_left=((uint16_t)(TFmini_left.Dist));
//   for (uint8_t i = 2; i < 8; i++)
//   {
//       tx_data[i] = *((uint8_t *)data + i - 2);     // 数据低位
//       tx_data[i + 1] = *((uint8_t *)data + i - 1); // 数据高位
//   }
//   for (uint8_t i = 0; i < 8; i++)
//   {
//       USART_SendData(USART3, tx_data[i]);
//       while (!(USART3->SR & USART_FLAG_TXE));
//   }
//}

//uint16_t PWM[4] = {125, 150, 130, 130};
//void PWM_Calculate(PidObject **pid)
//{

//   //	float a=3.7,b0=10,b1=7.5,c0=10.66,c1=8.36;                       //初始舵机支架三边常度  左右初始角度20.26   前后初始角度 25.19
//   Servos servos[2];
//   //	 	printf("pitch->out:%.2f,%.2f,%.2f,%.2f\r\n ",pitch,pid[1]->out,roll,pid[0]->out);

//   //		servos[0].angle		=		acos((pow(b0,2)+pow((pid[0]->out+c0),2)-pow(a,2))/(2*b0*(pid[0]->out+c0)));
//   //		servos[0]._angle	=		acos((pow(b0,2)+pow((-pid[0]->out+c0),2)-pow(a,2))/(2*b0*(-(pid[0]->out)+c0)));
//   //		servos[1].angle		=		acos((pow(b1,2)+pow((pid[1]->out+c1),2)-pow(a,2))/(2*b1*(pid[1]->out+c1)));
//   //		servos[1]._angle	=		acos((pow(b1,2)+pow((-pid[1]->out+c1),2)-pow(a,2))/(2*b1*(-(pid[1]->out)+c1)));
//   //
//   //    if(servos[1].angle>=0.52){servos[1].angle=0.52;}
//   //		if(servos[1].angle<=0.45){servos[1].angle=0.45;}
//   //
//   //		if(servos[1]._angle>=0.47){servos[1]._angle=0.47;}
//   //		if(servos[1]._angle<=0.30){servos[1]._angle=0.30;}
//   //
//   //		if(servos[0].angle>=0.37){servos[0].angle=0.37;}
//   //		if(servos[0].angle<=0.28){servos[0].angle=0.28;}
//   //
//   //		if(servos[0]._angle<=0.33){servos[0]._angle=0.33;}
//   //		if(servos[0]._angle>=0.38){servos[0]._angle=0.38;}
//   //
//   //
//   //
//   //	printf("左右  serove[0].angle:%.2f    ,serove[0]._angle:%.2f\r\n",70+(100*(servos[0].angle-0.35)/90*92),70+(100*(servos[0]._angle-0.36)/90*92));
//   //  printf("前后  serove[1].angle:%.2f,    serove[1]._angle:%.2f\r\n",70+(100*(servos[1].angle-0.45)/90*92),65+(100*(servos[1]._angle-0.46)/90*92));
//   //		PWM[0]	=	140+(100*(servos[1].angle-0.45)/90*92);//前
//   //		PWM[2]	=	65+(100*(servos[1]._angle-0.46)/90*92);// 后   pitch 调节
//   //		PWM[1]	=	70+(100*(servos[0]._angle-0.36)/90*92);//左
//   //		PWM[3]	=	70+(100*(servos[0].angle-0.35)/90*92);//右   roll 调节

//   PWM[0] = 145 - 12 * pid[1]->out; // 前
//   PWM[2] = 160 + 12 * pid[1]->out; // 后   pitch 调节
//   PWM[1] = 175 + 12 * pid[0]->out; // 左
//   PWM[3] = 170 - 12 * pid[0]->out; // 右   roll 调节

//   //		if(pitch<=0.5||yaw<=0.5)
//   //		{
//   //	  PWM[0]	=	150;//前
//   //		PWM[2]	=	151;// 后   pitch 调节
//   //		PWM[1]	=	171;//左
//   //		PWM[3]	=	171;//右   roll 调节
//   //		}

//   // printf("pwm :%d   ,%d   ,%d   ,%d\r\n ",PWM[0],PWM[1],PWM[2],PWM[3]);

//   //		for(int i=0;i<=3;i++)
//   //		{
//   //    if(PWM[i]>=85){PWM[i]=85;}
//   //		if(PWM[i]<=40){PWM[i]=40;}

//   TIM_SetCompare1(TIM3, PWM[0]);
//   TIM_SetCompare2(TIM3, PWM[1]);
//   TIM_SetCompare3(TIM3, PWM[2]);
//   TIM_SetCompare4(TIM3, PWM[3]);

//   //			printf("前后")
//   //		}

//   //	TIM_SetCompare1(TIM3,70);
//   //	TIM_SetCompare2(TIM3,75);
//   //	TIM_SetCompare3(TIM3,65);
//   //	TIM_SetCompare4(TIM3,70);

//   ////
//   //
//   //
//   //
//   //
//   //		//前上 右上
//   //	float a,c1,c2,d,e,y1,y2,y3,y4,angle1,angle2;
//   //		a=37.8;
//   //		c1=75;
//   //		c2=100;
//   //		d=29.34;
//   //		e=39;
//   //	y1=c1*sin(pid[1]->out)+a;
//   //	y2=-c2*sin(angle1)+a;
//   //		y3=c2*sin(angle1)+a;
//   //	y2=-c2*sin(angle1)+a;
//   //
//   //
//   //		servos[1].angle=asin((pow(y1,2)+pow(d,2)-pow(e,2))/(2*y1*d));
//   //		servos[1]._angle=asin((pow(y2,2)+pow(d,2)-pow(e,2))/(2*y2*d));
//   //		servos[0].angle=asin((pow(y1,2)+pow(d,2)-pow(e,2))/(2*y1*d));
//   //		servos[0]._angle=asin((pow(y2,2)+pow(d,2)-pow(e,2))/(2*y2*d));

//   //		PWM[0]	=	35+(int)(servos[1].angle/90*92);//前
//   //		PWM[2]	=	35+(servos[1].angle/90*92);// 后   pitch 调节
//   //
//   //		PWM[1]	=	35+(servos[0].angle/90*92);//左
//   //		PWM[3]	=	35+(servos[0].angle/90*92);//右   roll 调节
//   //		TIM_SetCompare1(TIM3,PWM[0]);
//   //
//   //		printf("pid[1]->out:%.2f,PWM[0]: %d\r\n",pid[1]->out,PWM[0]);
//   //		printf("pid[1]->out:%.2f,PWM[2]: %d\r\n",pid[1]->out,PWM[2]);
//   //		printf("pid[0]->out:%.2f,PWM[1]: %d\r\n",pid[0]->out,PWM[1]);
//   //		printf("pid[0]->out:%.2f,PWM[3]: %d\r\n",pid[0]->out,PWM[3]);
//   //
//}

float pitch,roll,yaw; 		//欧拉角
short aacx,aacy,aacz;		  //加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据

int mpu_get(void)
{
    if(mpu_dmp_get_data(&roll,&pitch,&yaw)==0)
    { 	
        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
        return 1;
    }
    return 0;
}

////void MPU_Display_Spect(void)
////{
//// 	OLED_ShowString(1, 1, "Mpu:");
//////     extern float pitch,roll,yaw; 		//欧拉角
////// extern short aacx,aacy,aacz;		  //加速度传感器原始数据
////// extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
////    OLED_ShowString(2, 1, "Pitch: ");
////    OLED_ShowString(3, 1, "roll:  ");
////    OLED_ShowString(4, 1, "yaw:   ");
////    OLED_ShowSignedNum(2, 8, pitch*100, 3);
//// 	OLED_ShowSignedNum(3, 8, roll*100, 3);
//// 	OLED_ShowSignedNum(4, 8, yaw*100, 3);
//// 	// OLED_ShowSignedNum(3, 6, Enc_Motor_D_Speed*100, 3);
////}
