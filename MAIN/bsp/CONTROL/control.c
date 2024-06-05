#include "control.h"
#include "math.h"
//IN1和IN2为右轮，IN3和IN4为左轮
/*******电机控制pwm初始化函数*************/
/**输入参数：左电机pwm值，右电机pwm值*****/

/****角度环的一些变量******/
float new_yaw=0;
float MAX,MIN;
float target_yaw_a_A;//a
float Err_Yaw,Err_Last_Yaw;
float PWM_N100N;//pwm输出
/******电机限幅函数******/


void Err_s_Limit(float Err_S_Limit,float* P_L,float* P_R)
{
	if(*P_L>=Err_S_Limit)
	{
		*P_L=Err_S_Limit;
	}
	if(*P_L<-Err_S_Limit)
	{
		*P_L=-Err_S_Limit;
	}
	if(*P_R>=Err_S_Limit)
	{
		*P_R=Err_S_Limit;
	}
	if(*P_R<-Err_S_Limit)
	{
		*P_R=-Err_S_Limit;
	}
}

extern int Flower_Count;
int t=0;
int Line_Flag=1;
int Line_Count=0;
int Line_OK;
int Line_All_Ok;
/******PID参数******/
float intergal=0;
/********电机参数****/
float Encoder_L=0;
float Encoder_R=0;

int PWM_out=90;//
int PWM_N100=0;
int PWM_out_L=0;
int PWM_out_R=0;
float Roll_PWM=0;

float target_now=100;//设置目标速度
int Target_Left_Distance=10;
int Target_Left_Distance_D=35;

float Bias_Left=0;
float Bias_S_Left=0;
float Bias_Last_Left=0;
float Bias_Last_Last_Left=0;

float Bias_Right=0;
float Bias_S_Right=0;
float Bias_Last_Right=0;

int i=0;

float weifen;
int set=0;
/*******************/
void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) 
	{
		/********判断是否进入*******/
		
		Protect();
		TTL_Hex2Dec();//新加，看有没有解决更新不够快
		t++;
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  
		if(t%10==0)
		{
			BEEP=!BEEP;
			LED1=!LED1;
//			printf("jigang=%d\r\n",Dist_right);
//			printf("L:%f ,%f ,%f, %d\r\n",Encoder_L,Encoder_R,target_now,PWM_N100);
//			printf("really:%f now:%f  err=%f\r\n",Target_Yaw,Read_Yaw(),Level(Target_Yaw,1,0,0));
		}
		if(t%4==0)
		{
			
			/*******编码器读速度*******/
			Encoder_L=-Read_Speed(3);
			Encoder_R=Read_Speed(2);
//			printf("L speed:%f/r/n",Encoder_L);
//			printf("R speed:%fr/rn",Encoder_R);
			/***********角度环*********/
			/******分区域给不同的角度环PID******/
			if(N_Flag==2)
			{
				PWM_N100=Level(Target_Yaw,12,0,0);//(16,0,20)-5
			}
			else
			{
				PWM_N100=Level(Target_Yaw,20,0,0);//(16,0,20)-5
			}
			Limit(180,-180,&PWM_N100,&PWM_N100);
			/*******激光矫正，分区域**************/
			if(N_Flag==1||N_Flag==3||N_Flag==5||N_Flag==0)//非B，C，D区
			{
				Roll_PWM=0;
			}
			if(N_Flag==2)//B区
			{
				Roll_PWM=0.4*(Dist_right-Dist_left);
				if(Dist_right>=30||Dist_left>=30)
				{
					Roll_PWM=0;
				}
				PWM_N100=Level(Target_Yaw+Roll_PWM,12,0,0);
				Roll_PWM=0;
			}
			if(N_Flag==4)//C区
			{
				
				if(Dist_right>=30&&Dist_right<=70)
				{
					Roll_PWM=0.13*(Target_Left_Distance-Dist_right);
				}
				if(Dist_right>=70)
				{
					Roll_PWM=0;
				}
				PWM_N100=Level(Target_Yaw+Roll_PWM,12,0,0);
				Roll_PWM=0;
			}
			if(N_Flag==6)//D区
			{
				Roll_PWM=0.45*(Dist_right-Dist_left);
				if(Dist_left>=30||Dist_right>=30)
				{
					Roll_PWM=0;
				}
				PWM_N100=Level(Target_Yaw+Roll_PWM,12,0,0);
				Roll_PWM=0;
			}
//			Limit(&PWM_N100,&PWM_N100);
			/***********速度环*********红左****绿右***/
			if(set==1)
			{
				/******防止一直积分******/
				float Bias_Left=0;
				float Bias_S_Left=0;
				float Bias_Last_Left=0;
				float Bias_Last_Last_Left=0;
				float Bias_Right=0;
				float Bias_S_Right=0;
				float Bias_Last_Right=0;
				if((N_Flag==2&&(Flower_Count>=8&&Flower_Count<=11))||(N_Flag==4))
				{
					PWM_out_L=110;
				  PWM_out_R=110;
				}
				else
				{
					PWM_out_L=90;
					PWM_out_R=90;
				}
				
			}
			else if(set==0)
			{
				PWM_out_L=Velocity(target_now-PWM_N100+Roll_PWM,0,Encoder_L,0.70,0.054,0.052);//(5.96,0.123,0.268)5,0.101,0.32(2.5,0,-1.2)3.32,0,-2.75   3.2,0.05,-1.//1.399,0.0621,0.2098////1.55,0.054,0.052
				PWM_out_R=Velocity(target_now+PWM_N100-Roll_PWM,1,Encoder_R,0.70,0.054,0.052);//0.099  076  /1.468,0.05285,0.052)/  p:震荡2.088 *（0.6~0.7）=（1.2528~1.4616） i:0.79 *(1.5~1.8)=(1.185~1.422)) ////1.3572,0.63,0.05 ////1.468,0.29285,0.052//
			}
			Limit(250,-250,&PWM_out_L,&PWM_out_R);
			Car_Load(PWM_out_L,PWM_out_R);
		}		
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 
	}
}
/*********************
积分限幅函数
输入参数：target：目标值
					err：偏差
*********************/
float Intergal_Limit(int target,int err)
{
	float intergal=0;
	if(Abs(err)>=(9*target/10))//以一般速度的2/3
	{
		intergal=0;
	}
//	if((Abs(err)<(target*4/5))&&(Abs(err)>=(target/5)))//速度的1/3到2/3
//	{
//		intergal=(4*target/5-Abs(err))/(4*target/5);
//	}
//	if(Abs(err)<(target*4/5))//小于1/3
//	{
	else
	{
		intergal=1;
	}
		
//	}
	return intergal;
}
/*********************
速度环PI：Kp*Ek+Ki*Ek_S
输入参数mode:mode=0  ->left  mode=1 ->right
        Target:目标值
				encoder：编码器读数

Velocity(70+Level(),0,Encoder_L,0,0,0)
*********************/
float Encoder_Err=0;
float EnC_Err_Lowout=0;
float EnC_Err_Lowout_last=0;
//float h=0.7;
int Velocity(int Target,int mode,int encoder,float kp,float ki,float kd)
{
	
	if(mode==0)
	{
		Bias_Left=Target-encoder;
		Bias_S_Left+=Bias_Left;
		Err_s_Limit(5000,&Bias_S_Left,&Bias_S_Left);//第一个参数为限幅参数
		if(Bias_Left>=9*Target/10)
		{
			Bias_S_Left=0;
		}
		else
		{
			Bias_S_Left=Bias_S_Left;
		}
		weifen=kd*(Bias_Left-Bias_Last_Left);
		PWM_out=kp*Bias_Left+Intergal_Limit(Target,Bias_Left)*ki*Bias_S_Left+kd*(Bias_Left-Bias_Last_Left);
//		PWM_out+=kp*(Bias_Left-Bias_Last_Left)+ki*Bias_Left+kd*(Bias_Left-2*Bias_Last_Left+Bias_Last_Last_Left);
//		Bias_Last_Last_Left=Bias_Last_Left;
		Bias_Last_Left=Bias_Left;
		
//		Limit(&PWM_out,&PWM_out);
		return PWM_out;
	}
	else if(mode==1)
	{
		Bias_Right=Target-encoder;
		Bias_S_Right+=Bias_Right;
		Err_s_Limit(5000,&Bias_S_Right,&Bias_S_Right);//第一个参数为限幅参数
		if(Bias_Right>=9*Target/10)
		{
			Bias_S_Right=0;
		}
		else
		{
			Bias_S_Right=Bias_S_Right;
		}
		PWM_out=kp*Bias_Right+Intergal_Limit(Target,Bias_Right)*ki*Bias_S_Right+kd*(Bias_Right-Bias_Last_Right);
		Bias_Last_Right=Bias_Right;
//		Limit(&PWM_out,&PWM_out);
		return PWM_out;
	}
	else if (mode==2)
	{
    	
	}
	
	
	
	
}
/*********************
角度环
输入参数
*********************/
//目标角度，为上电所读取的角度
float Level(float target_yaw_a,float kp,float ki,float kd)//kp为>0
{
	new_yaw=Read_Yaw();
	
	if(target_yaw_a>=0&&target_yaw_a<=180)
	{
		target_yaw_a_A=target_yaw_a+180;
	}
	if(target_yaw_a>180&&target_yaw_a<=360)
	{
		target_yaw_a_A=target_yaw_a-180;
	}
	MIN=Min(target_yaw_a,target_yaw_a_A);
	MAX=Max(target_yaw_a,target_yaw_a_A);
	if(target_yaw_a<=MIN)
	{
		Err_Yaw=((int)(100*(target_yaw_a-new_yaw)+36000)%36000)/100.0;
	}
	if(target_yaw_a>=MAX)
	{
		Err_Yaw=((int)(100*(new_yaw-target_yaw_a)+36000)%36000)/100.0;
	}
	if(new_yaw>MIN&&new_yaw<MAX)
	{
		Err_Yaw=((int)(100*Abs(target_yaw_a-new_yaw)+36000)%36000)/100.0;	
	}
	if(new_yaw>=0&&new_yaw<=MAX)
	{
		if(new_yaw>target_yaw_a||new_yaw<(target_yaw_a-180))
		{
			Err_Yaw=Err_Yaw;
		}
		else
		{
			Err_Yaw=-Err_Yaw;
		}
	}
	if(new_yaw>MAX&&new_yaw<=360&&target_yaw_a<=target_yaw_a_A)
	{
		if(new_yaw>target_yaw_a)
		{
			Err_Yaw=-Err_Yaw;
		}
		else
		{
			Err_Yaw=Err_Yaw;
		}
	}
	
	//向右偏为正，左为负
	if(Abs(Err_Yaw)<=0.01)//如果误差小可以不计入，1可改变
	{
		Err_Yaw=0;
	}
	PWM_N100N=kp*Err_Yaw+kd*(Err_Yaw-Err_Last_Yaw);
	Err_Last_Yaw=Err_Yaw;
//	printf("err=%f",Err_Yaw);
//	Limit(&PWM_N100N,&PWM_N100N);
	return PWM_N100N;
}




