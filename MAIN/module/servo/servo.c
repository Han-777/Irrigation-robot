#include "servo.h"

void servo_Init_All()
{
	Servo_Pitch_PWM_Init(2000 - 1, 840 - 1);
	Servo_Yaw_PWM_Init(2000 - 1, 840 - 1);
}

void Servo_Pitch_Control(uint16_t Compare)
{
	TIM_SetCompare1(TIM13, Compare);
}

void Servo_Yaw_Control(uint16_t Compare)
{
	TIM_SetCompare1(TIM14, Compare);
}

/* brief: for fine-grained control of servo
 */
void ServoControl(servoName name, uint16_t currentAngle, uint16_t targetAngle, uint16_t delay_time)
{
	if (name & pitch_servo)
	{
		for (int angle = currentAngle; angle < targetAngle; ++angle)
		{
			Servo_Pitch_Control(angle);
			delay_ms(delay_time);
		}
	}
	else if (name & yaw_servo)
	{
		for (int angle = currentAngle; angle < targetAngle; ++angle)
		{
			Servo_Yaw_Control(angle);
			delay_ms(delay_time);
		}
	}
}

// servo roughly move function (without hesitation)
void ServoMove(uint16_t angel1, uint16_t angel2) // (in 500us - 2500us)
{
	// arr = 2000 ~ 20ms ==>> (0.5ms - 2.5ms)*100 = 50 - 250
	Servo_Pitch_Control(angel1 / 180 * 200 + 50);
	Servo_Yaw_Control(angel2 / 180 * 200 + 50);
}

// Servo_PWM_Init(2000,3360/2);   //20ms, 0.5ms-- -135度,1.0ms-- -67度,1.5ms-- 0度,2.0-- 67度,2.5--135度					168Mhz/1000/3360
// 50-250

// 正常状态高电平,检测到目标低电平
// 0是左侧,1是右侧
//		TIM_SetCompare3(TIM8,down);	//下
//		TIM_SetCompare4(TIM8,up);		//上

// double Get_Water_Angle(void)
// {
// 	double angle;
// 	double Angle;
// 	if(R_r==1)
// 	{
// 		angle=asin(-length_A/sqrt(H*H+(D_d+R_R+Dist_right)*(D_d+R_R+Dist_right)))-atan(-(D_d+R_R+Dist_right)/H);
// 	}
// 	else if(L_l==1)
// 	{
// 		angle=asin(-length_A/sqrt(H*H+(D_d+R_R+Dist_left)*(D_d+R_R+Dist_left)))-atan(-(D_d+R_R+Dist_left)/H);
// 	}
// 	Angle=angle*180.0/PI;
// 	if(Angle<=0)
// 	{
// 		Angle=0;
// 	}
// 	if(Angle<=10&&Angle>=0)
// 	{
// 		Angle=10;
// 	}
// 	if(Angle>=45&&N_Flag==4)
// 	{
// 		Angle=45;
// 	}
// 	return Angle;
// }
// int Get_Servo_Pwm(double ANGLE)
// {
// 	double PWM;
// 	PWM=185.0-ANGLE;
// 	return (int)PWM;
// }
// int Water_angle_A; 	   //浇水角度
// int Water_angle_B;			//浇水角度
// int Water_angle_C; 	  	//浇水角度
// int Water_angle_D;			//浇水角度
// int plant=0;
// int D_mess=0;
// int jishu=0;
// void Water(int site,int times)
// {//{ u8 Flower_Count[21]={0x01,0x02,0x03,0x01,0x02,0x03,
// //                       0x01,0x02,0x03,0x01,0x02,0x03,
// //                       0x01,0x02,0x03,0x01,0x02,0x03};//既定的干旱信息
// 	int i; 		//循环变量
// 	if(site==1)
// 	{
// 		delay_ms(100);//用来给激光测距提供时间
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 		MP3_broadcast(drought_buff[Flower_Count]);
// 		LCD_DisplayOn();
// 	  LCD_hanqing(drought_buff[Flower_Count],Flower_Count);
// 		Water_angle_A=Get_Servo_Pwm(Get_Water_Angle()+2);
// //		TIM_SetCompare1(TIM13,Water_angle_A);//TIM8用于提起水管浇水
// 	  serove_move(13,Scan_angle_A,Water_angle_A,800);

// 		for(i=0;i<drought_buff[Flower_Count];i++)
// 		{
// 			GPIO_SetBits(GPIOB, GPIO_Pin_4);//浇水
// 			if(i==0)
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			else
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			GPIO_ResetBits(GPIOB, GPIO_Pin_4);//关闭浇水
// 			delay_ms(1000);
// 			delay_ms(500);
// 		}
// 	  serove_move(13,Water_angle_A,Lift_angle,500);

// 		jishu++;
// 		if(jishu==2)
// 		{
// 			jishu=0;
// 			Flower_Count++;
// 		}
// 	}
// 	else	if(site==2)
// 	{
// 		delay_ms(100);//用来给激光测距提供时间
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 		Water_angle_B=Get_Servo_Pwm(Get_Water_Angle()+12);
// 				MP3_broadcast(drought_buff[Flower_Count]);
// 		LCD_DisplayOn();
// 		LCD_hanqing(drought_buff[Flower_Count],Flower_Count);
// 		 serove_move(13,Scan_angle_B,Water_angle_B,800);
// //		TIM_SetCompare1(TIM13,Water_angle_B); //浇水竖立角度

// //		delay_ms(800);
// 		for(i=0;i<drought_buff[Flower_Count];i++)
// 		{
// 			GPIO_SetBits(GPIOB, GPIO_Pin_4);
// 			if(i==0)
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			else
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			GPIO_ResetBits(GPIOB, GPIO_Pin_4);
// 			delay_ms(500);
// 			delay_ms(500);
// 		}
// 		jishu++;
// 		serove_move(13,Water_angle_B,Lift_angle,500);
// 		if(jishu==2)
// 		{
// 			jishu=0;
// 			Flower_Count++;
// 		}
// 		//TIM_SetCompare4(TIM8,Lift_angle);
// 	}
// 	else	if(site==3)
// 	{

// 		delay_ms(100);//用来给激光测距提供时间
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 				LCD_DisplayOn();
// 		MP3_broadcast(drought_buff[Flower_Count]);
// 		LCD_hanqing(drought_buff[Flower_Count],Flower_Count);
// 		Water_angle_C=Get_Servo_Pwm(Get_Water_Angle()+6);
// 		 serove_move(13,Scan_angle_C,Water_angle_C,800);
// //		TIM_SetCompare1(TIM13,Water_angle_C);

// //		delay_ms(800);
// 		for(i=0;i<drought_buff[Flower_Count];i++)
// 		{
// 			GPIO_SetBits(GPIOB, GPIO_Pin_4);
// 			if(i==0)
// 			{
// 				delay_ms(1000);delay_ms(500);
// 			}
// 			else
// 			{
// 				delay_ms(1000);delay_ms(500);
// 			}
// 			GPIO_ResetBits(GPIOB, GPIO_Pin_4);
// 			delay_ms(1000);
// 			delay_ms(500);
// 		}
// 		jishu++;
// 		serove_move(13,Water_angle_C,Lift_angle,500);
// 		if(jishu==2)
// 		{
// 			jishu=0;
// 			Flower_Count++;
// 		}
// 		//TIM_SetCompare4(TIM8,Lift_angle);
// 	}

// 	else if(site==4)
// 	{
// 		delay_ms(100);//用来给激光测距提供时间
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 		Water_angle_D=Get_Servo_Pwm(Get_Water_Angle()+7);
// 				POINT_COLOR=RED;
// 		LCD_DisplayOn();
// 		LCD_hanqing(times,Flower_Count);
// 		MP3_broadcast(times);
// 		serove_move(13,Scan_angle_D,Water_angle_D,800);
// //		TIM_SetCompare1(TIM13,Water_angle_D);
// //    delay_ms(800);

// 		for(i=0;i<times;i++)
// 		{
// 			GPIO_SetBits(GPIOB, GPIO_Pin_4);
// 			if(i==0)
// 			{
// 				delay_ms(1000);delay_ms(500);
// 			}
// 			else
// 			{
// 				delay_ms(1000);delay_ms(500);
// 			}
// 			GPIO_ResetBits(GPIOB, GPIO_Pin_4);
// 			delay_ms(1000);
// 			delay_ms(500);
// 		}
// 			Flower_Count++;
// 		serove_move(13,Water_angle_D,Lift_angle,500);
// 		//TIM_SetCompare4(TIM8,Lift_angle);
// 	}

// }
// int an;
// int angle;								//循环变量
// int Last_last_finish=0,Last_finish=0,finish=0; //检测标志位
// int over=0;       //检测结束
// int	stride=1; 				//角度变化步长
// int left_target[200],right_target[200];		//左右目标角度
// int Err_Count=0;//记录扫描次数,达到两次视为没有扫到
// void serove_move (int num,int now_angle,int to_angle,int delaytime)
// {

// 	if (num==13)
// 	{
// 		if(now_angle<=to_angle)
// 		{
// 		for(an=now_angle;an<=to_angle;an++)
// 		 {	TIM_SetCompare1(TIM13,an);
// 			delay_ms(delaytime/abs((to_angle-now_angle)));
// 		 }
// 	  }
// 	   if(to_angle<=now_angle)
// 	  {
// 		for(an=now_angle;an>=to_angle;an--)
// 		 {	TIM_SetCompare1(TIM13,an);
// 			delay_ms(delaytime/abs((to_angle-now_angle)));
// 		 }

// 	  }

// 		}

// 	if (num==14)
// 	{
// 		if(now_angle<=to_angle)
// 		{
// 		for(an=now_angle;an<=to_angle;an++)
// 		 {	TIM_SetCompare1(TIM14,an);
// 			delay_ms(delaytime/abs((to_angle-now_angle)));
// 		 }
// 	  }
// 	  if(to_angle<=now_angle)
// 	  {
// 		for(an=now_angle;an>=to_angle;an--)
// 		 {	TIM_SetCompare1(TIM14,an);
// 			delay_ms(delaytime/abs((to_angle-now_angle)));
// 		 }

// 	  }

// 		}
// }
// void Rotation(int site,int direct)//云台旋转
// {
// 	int i;
// //	static int jishu=0;
// 	int D;
// 	int count=0;   //扫描次数
// 	int first=0;
// 	int target_i=0,j=0;   //循环变量
// 	int left_begin=120,left=60;
// 	int right_begin=195,right=240;

// 	int left_begin_A=198,left_A=240;// A区左开始和结束角度
// 	int right_begin_A=102,right_A=42;

// 	int left_begin_B=200,left_B=240;//B区左开始和结束角度
// 	int right_begin_B=105,right_B=42;

// 	int left_begin_C=200,left_C=240;//C区 左开始和结束角度
// 	int right_begin_C=100,right_C=42;

// 	int time=120;  //舵机旋转变化时间

// 	int L_begin,L,R_begin,R;
// 	Car_stop();
// //	delay_init(168);
// 	if(site==1)
// 	{
// 		serove_move(13,Lift_angle,Scan_angle_A,500);

// //			TIM_SetCompare1(TIM13,Scan_angle_A);  //A区抬起一定角度
// //			delay_ms(500);
// 	}
// 	else if(site==2)
// 	{
//     serove_move(13,Lift_angle,Scan_angle_B,500);
// //			TIM_SetCompare1(TIM13,Scan_angle_B); //B区抬起一定角度
// //			delay_ms(500);
// 	}
// 	else if(site==3)
// 	{
// 		   serove_move(13,Lift_angle,Scan_angle_C,500);
// //		TIM_SetCompare1(TIM13,Scan_angle_C);//C区抬起一定角度
// //		delay_ms(500);
// 	}
// 	else if(site==4)
// 	{
// 		   serove_move(13,Lift_angle,Scan_angle_D,500);

// //		TIM_SetCompare1(TIM13,Scan_angle_D);  //D区抬起一定角度
// //		delay_ms(500);
// 	}

// 	//已经抬起
// /************************************左侧*************************/
// 	if(site!=4 && direct==0)//非第四区左侧
// 	{
// 		over=0;
// 		while(!over)//没检测
// 		{
// 			Last_last_finish=0;Last_finish=0;finish=0;target_i=0;
// 			count++;first=1;
// //		  serove_move(14,Mid,Mid,500);
// 			TIM_SetCompare1(TIM14,Mid);//3区喷头移到中央
// 			delay_ms(500);
// 			if(site==1)//3区初始左移赋值
// 			{
// 				L_begin=left_begin_A;
// 				L=left_A;
// 			}
// 			else if(site==3)
// 			{
// 				L_begin=left_begin_C;
// 				L=left_C;
// 			}
// 			else if(site==2)
// 			{
// 				L_begin=left_begin_B;
// 				L=left_B;
// 			}

// 			else//2区浇水初始左移赋值
// 			{
// 				L_begin=left_begin;
// 				L=left;
// 			}
// 			for(angle=L_begin;angle<=L;angle=angle+stride)
// 			{
// 				Car_stop();
// //				Protect();

// 				Last_last_finish=Last_finish;
// 				Last_finish=finish;
// 				TIM_SetCompare1(TIM14,angle);//云台舵机移到初始左边
// 				if(first==1)
// 				{
// 					delay_ms(700);
// 					first=0;
// 				}
// 				else
// 					delay_ms(time);//云台右移

// 				if(sensor==0)//光电检测到
// 				{
// 					left_target[target_i]=angle;//达到目标角度
// 					target_i++;
// 					finish=1;
// 				}
// 				else
// 				{
// 					finish=0;//光电右移后检测不到 满足下面if条件

// 				}
// 				if((Last_last_finish==1 && Last_finish==0 && finish==0)||(Err_Count==2))
// 				{
// 					angle=0;
// 					for(j=0;j<target_i;j++)
// 					{
// 						angle+=left_target[j];
// 					}
// 					angle=(int)angle/target_i;
// 					TIM_SetCompare1(TIM14,angle-3);    //左侧回调到中间
// 					delay_ms(1000);
// 					Water(site,0);

// //					TIM_SetCompare1(TIM13,Lift_angle);
// //					delay_ms(500);
// 					serove_move(14,angle-3,Mid,500);
// //					TIM_SetCompare1(TIM14,Mid);
// //					delay_ms(500);

// 					over=1;
// 					break;

// 				}
// 				if(angle==L)
// 				{
// 					over=1;
// 					TIM_SetCompare1(TIM14,(L_begin+L)/2-10);
// 					delay_ms(500);
// 					Water(site,0);
// 										if(site==1)
// 				  {serove_move(13,Scan_angle_A,Lift_angle,500);}
// 					if(site==2)
// 					{serove_move(13,Scan_angle_B,Lift_angle,500);}
// 					if(site==3)
// 					{serove_move(13,Scan_angle_C,Lift_angle,500);}
// 					serove_move(14,angle-3,Mid,500);
// //					TIM_SetCompare1(TIM13,Lift_angle);
// //					delay_ms(500);
// //					TIM_SetCompare1(TIM14,Mid);
// //					delay_ms(500);

// 				}
// 			}
// 		}
// 	}
// 	/************************非D区右侧******************************/
// 	else if(site!=4 && direct==1)
// 	{
// 		count=0;over=0;
// 		while(!over)
// 		{
// 			Last_last_finish=0;Last_finish=0;finish=0;target_i=0;
// 			count++;first=1;

// //			serove_move(14,Mid,Mid,500);
// 			TIM_SetCompare1(TIM14,Mid);
// 			delay_ms(500);

// 			if(site==1)
// 			{
// 				R_begin=right_begin_A;
// 				R=right_A;
// 			}
// 			else if(site==3)
// 			{
// 				R_begin=right_begin_C;
// 				R=right_C;
// 			}
// 			else if(site==2)
// 			{
// 				R_begin=right_begin_B;
// 				R=right_B;
// 			}
// 			else
// 			{
// 				R_begin=right_begin;
// 				R=right;
// 			}

// 			for(angle=R_begin;angle>=R;angle=angle-stride)
// 			{
// 				Car_stop();
// //				Protect();
// 				Last_last_finish=Last_finish;
// 				Last_finish=finish;

// 				TIM_SetCompare1(TIM14,angle);
// 				if(first==1)
// 				{
// 					delay_ms(700);
// 					first=0;
// 				}
// 				else
// 					delay_ms(time);

// 				if(sensor==0)
// 				{
// 					right_target[target_i]=angle;
// 					target_i++;
// 					finish=1;
// 				}
// 				else
// 				{
// 					finish=0;
// 				}
// 				if((Last_last_finish==1 && Last_finish==0 && finish==0)||(Err_Count==2))
// 				{
// 					angle=0;
// 					for(j=0;j<target_i;j++)

// 					{
// 						angle+=right_target[j];
// 					}
// 					angle=(int)angle/target_i;
// 					TIM_SetCompare1(TIM14,angle-4); //右侧
// 					delay_ms(1000);
// 					Water(site,0);
// 					serove_move(14,angle-3,Mid,500);
// //					TIM_SetCompare1(TIM13,Lift_angle);
// //					delay_ms(500);
// //					TIM_SetCompare1(TIM14,Mid);
// //					delay_ms(500);

// 					over=1;
// //					printf("water\r\n");
// 					break;
// 				}
// 				if(angle==R)
// 				{
// 					over=1;
// 					serove_move(14,R,(R_begin+R)/2+10,500);
// //					TIM_SetCompare1(TIM14,(R_begin+R)/2+10);
// //					delay_ms(500);
// 					Water(site,0);
// 					if(site==1)
// 				  {serove_move(13,Scan_angle_A,Lift_angle,500);}
// 					if(site==2)
// 					{serove_move(13,Scan_angle_B,Lift_angle,500);}
// 					if(site==3)
// 					{serove_move(13,Scan_angle_C,Lift_angle,500);}
// 					serove_move(14,angle-3,Mid,500);
// //					TIM_SetCompare1(TIM13,Lift_angle);
// //					delay_ms(500);
// //					TIM_SetCompare1(TIM14,Mid);
// //					delay_ms(500);

// 				}
// 			}
// 		}

// 	}
// 	//**********************D区**********************************//
// 	//D区左侧
// 	else if(site==4 && direct==0)
// 	{
// 		Car_stop();
// 		serove_move(14,Mid,Left_D,1000);
// 		D=Openmv_gain();
// //		printf("D=%d\r\n",D);
// 		delay_ms(1500);
// 		Water(4,D);

// 		serove_move(13,Scan_angle_D,Lift_angle,500);

// 		serove_move(14,Left_D,Mid,500);
// //		TIM_SetCompare1(TIM13,Lift_angle);
// //		delay_ms(500);
// //		TIM_SetCompare1(TIM14,Mid);
// //		delay_ms(500);

// 	}
// //D区右侧
// 	else if(site==4 && direct==1)
// 	{
// //		TIM_SetCompare1(TIM14,Right_D);
// 		Car_stop();
// 			serove_move(14,Mid,Right_D,1000);

// 		D=Openmv_gain();
// 		Water(4,D);
// 		serove_move(13,Scan_angle_D,Lift_angle,500);
// 		serove_move(14,Right_D,Mid,500);
// //		TIM_SetCompare1(TIM13,Lift_angle);
// //		delay_ms(500);
// //		TIM_SetCompare1(TIM14,Mid);
// //		delay_ms(500);

// 	}

// //	if(site==2 && jishu==2)
// //	{
// //		jishu=0;
// //		TIM_SetCompare4(TIM8,Balance_angle);  //平衡重心
// //		delay_ms(1000);
// //	}
// //
// //	if(site==3)
// //	{
// //		TIM_SetCompare4(TIM8,Balance_angle);  //平衡重心
// //		delay_ms(1000);
// //	}
// }
