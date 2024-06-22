#include "arm.h"

water_finish_Structure_TypeDef water_finish_structure;
// TIME CONST
const int PITCH_TRANSFER_TIME = 0, // 500
    YAW_TRANSFER_TIME = 0,         // 120
    OPENMV_WAIT = 1000,            // 1000
    WATER_TIME = 1000;

void arm_Init(void)
{
    servo_Init_All();
    PE_EXTI_Init();
}

int water_finish(void)
{
    if (left_water_flag || right_water_flag)
    {
        return 0;
    }
    return 1;
}

void water(colorIdx waterTimes)
{
    static int water_cnt = 0;
    if (waterTimes == INFO_DROUGHT)
    {
        for (int times = 0; times < drought_buff[plant_cnt]; ++times) // 后面加上if buff = 0
        {
            // open_pump;
            // delay_ms(WATER_TIME);
            // close_pump;
            // delay_ms(WATER_TIME);
            MP3_broadcast(drought_buff[plant_cnt]);
        }
    }
    else
    {
        for (int times = 0; times < waterTimes; ++times)
        {
            // open_pump;
            // delay_ms(WATER_TIME);
            // close_pump;
            // delay_ms(WATER_TIME);
            MP3_broadcast(waterTimes);
        }
    }
    ++water_cnt;
    if (water_finish_structure.left_water_scan_finish)
    {
        water_finish_structure.left_water_scan_finish = 0;
        water_finish_structure.left_water_finish = 1;
        left_water_flag = 0;
    }
    else if (water_finish_structure.right_water_scan_finish)
    {
        water_finish_structure.right_water_scan_finish = 0;
        water_finish_structure.right_water_finish = 1;
        right_water_flag = 0;
    }
    if (water_cnt == 2 && water_finish_structure.left_water_finish && water_finish_structure.right_water_finish)
    {
        water_cnt = 0;
        plant_cnt++;
    }
}

// to yaw water angle
void get_water_direction(void)
{
    int last_last_found = 0, last_found = 0, current_found = 0, buffer_idx = 0, angle = 0; // plant found flag
    int angle_buffer[200];
    ServoControl(pitch_servo, pitch_lift_angle, pitch_scan_angle, PITCH_TRANSFER_TIME);
    if (region != D)
    {
        if (left_water_flag)
        {
            angle = left_scan_begin;
            for (; angle < left_scan_end; ++angle)
            {
                last_last_found = last_found;
                last_found = current_found;
                Servo_Yaw_Control(angle);
                delay_ms(YAW_TRANSFER_TIME); // delay for servo movement
                if (plant_found)
                {
                    angle_buffer[buffer_idx] = angle;
                    ++buffer_idx;
                    current_found = 1;
                }
                if (last_last_found && !last_found && !current_found)
                {
                    break;
                }
            }
            water_finish_structure.left_water_scan_finish = 1;
        }
        else if (right_water_flag)
        {
            angle = right_scan_begin;
            for (; angle < right_scan_end; ++angle)
            {
                last_last_found = last_found;
                last_found = current_found;
                Servo_Yaw_Control(angle);
                delay_ms(YAW_TRANSFER_TIME); // delay for servo movement
                if (plant_found)
                {
                    angle_buffer[buffer_idx] = angle;
                    ++buffer_idx;
                    current_found = 1;
                }
                if (last_last_found && !last_found && !current_found)
                {
                    break;
                }
            }
            water_finish_structure.right_water_scan_finish = 1;
        }
        angle = 0;
        for (int idx = 0; idx < buffer_idx; ++idx)
        {
            angle += angle_buffer[buffer_idx];
        }
        angle /= buffer_idx;
        Servo_Yaw_Control(angle);
        delay_ms(YAW_TRANSFER_TIME);
    }
    else if (region == D) // else 也可？
    {
        if (left_water_flag)
        {
            ServoControl(yaw_servo, yaw_mid, left_D_angle, YAW_TRANSFER_TIME);
        }
        else if (right_water_flag)
        {
            ServoControl(yaw_servo, yaw_mid, right_D_angle, YAW_TRANSFER_TIME);
        }
    }
}

// for pitch servo
void water_task(void)
{
    if (region != D)
    {
        ServoControl(pitch_servo, pitch_scan_angle, pitch_lift_angle, PITCH_TRANSFER_TIME); // 浇水角度需要后面测量
        water(INFO_DROUGHT);                                                                // 非D特殊标志位
    }
    else if (region == D)
    {
        if (left_water_flag)
        {
            OpenMV_USART_Init(115200);
            ServoControl(pitch_servo, pitch_scan_angle, pitch_D_water_angle, YAW_TRANSFER_TIME);
            delay_ms(OPENMV_WAIT);
            water(get_OpenMV());
            ServoControl(yaw_servo, left_D_angle, yaw_mid, YAW_TRANSFER_TIME);
        }
        else if (right_water_flag)
        {
            OpenMV_USART_Init(115200);
            ServoControl(pitch_servo, pitch_scan_angle, pitch_D_water_angle, YAW_TRANSFER_TIME);
            delay_ms(OPENMV_WAIT);
            water(get_OpenMV());
            ServoControl(yaw_servo, yaw_mid, right_D_angle, YAW_TRANSFER_TIME);
        }
        OpenMV_USART_Close();
    }
}

void arm_water_task(void)
{
    get_region();
    while (!water_finish()) // 一次清一个标志位
    {
        get_water_direction();
        water_task();
    }
	if (water_finish_structure.left_water_finish && water_finish_structure.right_water_finish)
	{
		water_finish_structure.left_water_finish = 0;
		water_finish_structure.right_water_finish = 0;
		PE_EXTI_Init();
	}
	
}
// void task_A(void)
//{
//	char i = 0;
//	int plant = 0;

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(1, 0); // 左边水管移动并浇水
//		Rotation(1, 1); // 右边水管移动并浇水
//	}
//}

// void task_B(void)
//{
//	char i = 0;

//	//	delay_init(168);
//	//	TIM_SetCompare4(TIM8,Balance_angle);	//平衡角度
//	//	delay_ms(1000);

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(2, 0);
//		Rotation(2, 1);
//	}
//}

// void task_C(void)
//{
//	char i = 0;

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(3, 0);
//		Rotation(3, 1);
//	}
//}

// void task_D(void)
//{

//	Rotation(4, 0);
//	Rotation(4, 1);
//}
// int Flower_Count = 0;
// void Task_Init(void)
//{
//	if (Flag_R == 1)
//	{
//		TTL_Hex2Dec();
//		R_r = 1; // 用来激光判断的
//		//		Flower_Count++;
//		//		printf("distance_r=%d\r\n",Dist_right);//测试激光能不能正常工作
//		//		printf("Flower_Count=%d, N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // 双重保险
//		{
//			Rotation(1, 1);
//		}
//		else if (N_Flag == 2)
//		{
//			Rotation(2, 1);
//		}
//		else if (N_Flag == 4)
//		{
//			Rotation(3, 1);
//		}
//		else if (N_Flag == 6)
//		{
//			Rotation(4, 1);
//		}
//		R_r = 0;
//		Flag_R = 0;
//		TTL_Hex2Dec();
//	}
//	if (Flag_L == 1)
//	{
//		TTL_Hex2Dec();
//		L_l = 1;
//		//		Flower_Count++;
//		//		printf("distance_l=%d\r\n",Dist_left);//测试激光能不能正常工作
//		//		printf("Flower_Count=%d,N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // 双重保险
//		{
//			Rotation(1, 0);
//		}
//		else if (N_Flag == 2)
//		{
//			Rotation(2, 0);
//		}
//		else if (N_Flag == 4)
//		{
//			Rotation(3, 0);
//		}
//		else if (N_Flag == 6)
//		{
//			Rotation(4, 0);
//		}
//		L_l = 0;
//		Flag_L = 0;
//		TTL_Hex2Dec();
//	}
//	//	BEEP=0;
//	delay_ms(500);

//	EXTInterruppt_Mode();
//	NVIC_Configuration();
//	set = 1;	  // 新加的，让小车刚开始有一定速度
//	delay_ms(20); //
//	TIM7_Int_Init(1000 - 1, 840 - 1);
//	delay_ms(80); //
//	set = 0;
//	delay_ms(80); // 200->100
//	set = 0;
//	//	BEEP=1;
//}
