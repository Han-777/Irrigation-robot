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

// Servo_PWM_Init(2000,3360/2);   //20ms, 0.5ms-- -135��,1.0ms-- -67��,1.5ms-- 0��,2.0-- 67��,2.5--135��					168Mhz/1000/3360
// 50-250

// ����״̬�ߵ�ƽ,��⵽Ŀ��͵�ƽ
// 0�����,1���Ҳ�
//		TIM_SetCompare3(TIM8,down);	//��
//		TIM_SetCompare4(TIM8,up);		//��

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
// int Water_angle_A; 	   //��ˮ�Ƕ�
// int Water_angle_B;			//��ˮ�Ƕ�
// int Water_angle_C; 	  	//��ˮ�Ƕ�
// int Water_angle_D;			//��ˮ�Ƕ�
// int plant=0;
// int D_mess=0;
// int jishu=0;
// void Water(int site,int times)
// {//{ u8 Flower_Count[21]={0x01,0x02,0x03,0x01,0x02,0x03,
// //                       0x01,0x02,0x03,0x01,0x02,0x03,
// //                       0x01,0x02,0x03,0x01,0x02,0x03};//�ȶ��ĸɺ���Ϣ
// 	int i; 		//ѭ������
// 	if(site==1)
// 	{
// 		delay_ms(100);//�������������ṩʱ��
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 		MP3_broadcast(drought_buff[Flower_Count]);
// 		LCD_DisplayOn();
// 	  LCD_hanqing(drought_buff[Flower_Count],Flower_Count);
// 		Water_angle_A=Get_Servo_Pwm(Get_Water_Angle()+2);
// //		TIM_SetCompare1(TIM13,Water_angle_A);//TIM8��������ˮ�ܽ�ˮ
// 	  serove_move(13,Scan_angle_A,Water_angle_A,800);

// 		for(i=0;i<drought_buff[Flower_Count];i++)
// 		{
// 			GPIO_SetBits(GPIOB, GPIO_Pin_4);//��ˮ
// 			if(i==0)
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			else
// 			{
// 				delay_ms(500);delay_ms(500);
// 			}
// 			GPIO_ResetBits(GPIOB, GPIO_Pin_4);//�رս�ˮ
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
// 		delay_ms(100);//�������������ṩʱ��
// //		printf("Angle=%f\r\n",Get_Water_Angle());
// 		Water_angle_B=Get_Servo_Pwm(Get_Water_Angle()+12);
// 				MP3_broadcast(drought_buff[Flower_Count]);
// 		LCD_DisplayOn();
// 		LCD_hanqing(drought_buff[Flower_Count],Flower_Count);
// 		 serove_move(13,Scan_angle_B,Water_angle_B,800);
// //		TIM_SetCompare1(TIM13,Water_angle_B); //��ˮ�����Ƕ�

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

// 		delay_ms(100);//�������������ṩʱ��
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
// 		delay_ms(100);//�������������ṩʱ��
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
// int angle;								//ѭ������
// int Last_last_finish=0,Last_finish=0,finish=0; //����־λ
// int over=0;       //������
// int	stride=1; 				//�Ƕȱ仯����
// int left_target[200],right_target[200];		//����Ŀ��Ƕ�
// int Err_Count=0;//��¼ɨ�����,�ﵽ������Ϊû��ɨ��
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
// void Rotation(int site,int direct)//��̨��ת
// {
// 	int i;
// //	static int jishu=0;
// 	int D;
// 	int count=0;   //ɨ�����
// 	int first=0;
// 	int target_i=0,j=0;   //ѭ������
// 	int left_begin=120,left=60;
// 	int right_begin=195,right=240;

// 	int left_begin_A=198,left_A=240;// A����ʼ�ͽ����Ƕ�
// 	int right_begin_A=102,right_A=42;

// 	int left_begin_B=200,left_B=240;//B����ʼ�ͽ����Ƕ�
// 	int right_begin_B=105,right_B=42;

// 	int left_begin_C=200,left_C=240;//C�� ��ʼ�ͽ����Ƕ�
// 	int right_begin_C=100,right_C=42;

// 	int time=120;  //�����ת�仯ʱ��

// 	int L_begin,L,R_begin,R;
// 	Car_stop();
// //	delay_init(168);
// 	if(site==1)
// 	{
// 		serove_move(13,Lift_angle,Scan_angle_A,500);

// //			TIM_SetCompare1(TIM13,Scan_angle_A);  //A��̧��һ���Ƕ�
// //			delay_ms(500);
// 	}
// 	else if(site==2)
// 	{
//     serove_move(13,Lift_angle,Scan_angle_B,500);
// //			TIM_SetCompare1(TIM13,Scan_angle_B); //B��̧��һ���Ƕ�
// //			delay_ms(500);
// 	}
// 	else if(site==3)
// 	{
// 		   serove_move(13,Lift_angle,Scan_angle_C,500);
// //		TIM_SetCompare1(TIM13,Scan_angle_C);//C��̧��һ���Ƕ�
// //		delay_ms(500);
// 	}
// 	else if(site==4)
// 	{
// 		   serove_move(13,Lift_angle,Scan_angle_D,500);

// //		TIM_SetCompare1(TIM13,Scan_angle_D);  //D��̧��һ���Ƕ�
// //		delay_ms(500);
// 	}

// 	//�Ѿ�̧��
// /************************************���*************************/
// 	if(site!=4 && direct==0)//�ǵ��������
// 	{
// 		over=0;
// 		while(!over)//û���
// 		{
// 			Last_last_finish=0;Last_finish=0;finish=0;target_i=0;
// 			count++;first=1;
// //		  serove_move(14,Mid,Mid,500);
// 			TIM_SetCompare1(TIM14,Mid);//3����ͷ�Ƶ�����
// 			delay_ms(500);
// 			if(site==1)//3����ʼ���Ƹ�ֵ
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

// 			else//2����ˮ��ʼ���Ƹ�ֵ
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
// 				TIM_SetCompare1(TIM14,angle);//��̨����Ƶ���ʼ���
// 				if(first==1)
// 				{
// 					delay_ms(700);
// 					first=0;
// 				}
// 				else
// 					delay_ms(time);//��̨����

// 				if(sensor==0)//����⵽
// 				{
// 					left_target[target_i]=angle;//�ﵽĿ��Ƕ�
// 					target_i++;
// 					finish=1;
// 				}
// 				else
// 				{
// 					finish=0;//������ƺ��ⲻ�� ��������if����

// 				}
// 				if((Last_last_finish==1 && Last_finish==0 && finish==0)||(Err_Count==2))
// 				{
// 					angle=0;
// 					for(j=0;j<target_i;j++)
// 					{
// 						angle+=left_target[j];
// 					}
// 					angle=(int)angle/target_i;
// 					TIM_SetCompare1(TIM14,angle-3);    //���ص����м�
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
// 	/************************��D���Ҳ�******************************/
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
// 					TIM_SetCompare1(TIM14,angle-4); //�Ҳ�
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
// 	//**********************D��**********************************//
// 	//D�����
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
// //D���Ҳ�
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
// //		TIM_SetCompare4(TIM8,Balance_angle);  //ƽ������
// //		delay_ms(1000);
// //	}
// //
// //	if(site==3)
// //	{
// //		TIM_SetCompare4(TIM8,Balance_angle);  //ƽ������
// //		delay_ms(1000);
// //	}
// }
