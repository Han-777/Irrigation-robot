#include "arm.h"

water_finish_Structure_TypeDef water_finish_structure;

// TIME CONST
const int PITCH_TRANSFER_TIME = 400, // 400
    YAW_TRANSFER_TIME = 150,         // 120
    OPENMV_WAIT = 1000,              // 1000
    WATER_TIME = 2000;

void arm_Init(void)
{
    servo_Init_All();
    photoelectric_GPIO_Init();
    pump_GPIO_Init();
    PE_EXTI_Init();
    Servo_Pitch_Control(pitch_mid);
    Servo_Yaw_Control(yaw_mid);
    VirtualTx_Config();
    LCD_Init();
    lidar_Init(DISABLE);
}

int lidar_water_confirm(void)
{
    if (left_water_flag && lidar_left < lidar_water_dist_threshold)
    {
        return 1;
    }
    else if (right_water_flag && lidar_left < lidar_water_dist_threshold)
    {
        return 1;
    }
    else
    {
        left_water_flag = 0;
        right_water_flag = 0;
        return 0;
    }
    return 1;
}

int water_finish(void)
{
    if (!left_water_flag && !right_water_flag)
    {
        return 1;
        // gyro_USART_Init(921600);
    }
    set_speed(0, 0);
    if (left_water_flag || right_water_flag) // ���������ȼ�
    {
        left_lidar_state(left_water_flag ? ENABLE : DISABLE);
        right_lidar_state(left_water_flag && right_water_flag ? DISABLE : ENABLE);
        delay_ms(50);
        if (region == C)
        {
            C_lidar_error = left_water_flag ? 24 - left_lidar : right_lidar - 24;
            // C_lidar_error = right_lidar - 24;
        }
    }
    return 0;
}

void water(colorIdx waterTimes)
{
    static int water_cnt = 0;
    if (waterTimes == INFO_DROUGHT)
    {
        for (int times = 0; times < drought_buff[plant_cnt]; ++times) // �������if buff = 0
        {
            open_pump;
            delay_ms(WATER_TIME);
            close_pump;
            delay_ms(WATER_TIME);
            // LCD_hanqing(drought_buff[plant_cnt], plant_cnt);
        }
        LCD_hanqing(drought_buff[plant_cnt], plant_cnt);
        MP3_broadcast(drought_buff[plant_cnt]);
    }
    else
    {
        MP3_broadcast(waterTimes);
        LCD_hanqing(waterTimes, plant_cnt);
        for (int times = 0; times < waterTimes; ++times)
        {
            open_pump;
            delay_ms(WATER_TIME);
            close_pump;
            delay_ms(WATER_TIME);
            // LCD_hanqing(drought_buff[plant_cnt], plant_cnt);
        }
        LCD_hanqing(drought_buff[plant_cnt], plant_cnt);
        MP3_broadcast(drought_buff[plant_cnt]);
    }
    ++water_cnt;
    // if (water_cnt == 1)
    // {

    // ServoControl(yaw_servo, , yaw_mid);
    // }
    if (water_finish_structure.left_water_scan_finish)
    {
        water_finish_structure.left_water_scan_finish = 0;
        water_finish_structure.left_water_finish = 1;
        ServoControl(yaw_servo, left_scan_begin, yaw_mid, YAW_TRANSFER_TIME);
        left_water_flag = 0;
        //        TFmini_left_USART_Close();
        left_lidar_state(DISABLE);
    }
    else if (water_finish_structure.right_water_scan_finish)
    {
        water_finish_structure.right_water_scan_finish = 0;
        water_finish_structure.right_water_finish = 1;
        ServoControl(yaw_servo, right_scan_begin, yaw_mid, YAW_TRANSFER_TIME);
        right_water_flag = 0;
        //        TFmini_right_USART_Close();
        right_lidar_state(DISABLE);
    }
    if (water_cnt == 2 && water_finish_structure.left_water_finish && water_finish_structure.right_water_finish)
    {
        water_cnt = 0;
        plant_cnt++;
        // PE_EXTI_Init();
    }
}

// to yaw water angle
void get_water_direction(void)
{
    int last_last_found = 0, last_found = 0, current_found = 0, buffer_idx = 0, angle = 0; // plant found flag
    int angle_buffer[200];
    Servo_Pitch_Control(pitch_scan_angle);

    // ServoControl(pitch_servo, pitch_lift_angle, pitch_scan_angle, PITCH_TRANSFER_TIME);
    if (region != D)
    {
        if (left_water_flag)
        {
            angle = left_scan_begin;
            ServoControl(yaw_servo, yaw_mid, angle, YAW_TRANSFER_TIME);
            for (; angle < left_scan_end; ++angle)
            {
                last_last_found = last_found;
                last_found = current_found;
                Servo_Yaw_Control(angle);
                delay_ms(YAW_TRANSFER_TIME); // delay for servo movement
                if (PE_NOZZLE == 0)
                {
                    angle_buffer[buffer_idx] = angle + 5;
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
            ServoControl(yaw_servo, yaw_mid, angle, YAW_TRANSFER_TIME);
            for (; angle > right_scan_end; --angle)
            {
                last_last_found = last_found;
                last_found = current_found;
                Servo_Yaw_Control(angle);
                delay_ms(YAW_TRANSFER_TIME); // delay for servo movement
                if (PE_NOZZLE == 0)
                {
                    angle_buffer[buffer_idx] = angle + 5;
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
            angle += angle_buffer[idx];
        }
        angle /= buffer_idx;
        Servo_Yaw_Control(angle);
        delay_ms(YAW_TRANSFER_TIME);
    }
    else if (region == D) // else Ҳ�ɣ�
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
        ServoControl(pitch_servo, pitch_scan_angle, left_water_flag ? (lidar_left * 0.7 + 110) : (lidar_right * 0.7 + 110), PITCH_TRANSFER_TIME); // ��ˮ�Ƕ���Ҫ�������
        water(INFO_DROUGHT);                                                                                                                      // ��D�����־λ
    }
    else if (region == D)
    {
        if (left_water_flag)
        {
            OpenMV_USART_Init(115200);
            ServoControl(pitch_servo, pitch_scan_angle, pitch_D_left_water_angle, YAW_TRANSFER_TIME);
            delay_ms(OPENMV_WAIT);
            water(get_OpenMV());
            ServoControl(yaw_servo, left_D_angle, yaw_mid, YAW_TRANSFER_TIME);
        }
        else if (right_water_flag)
        {
            OpenMV_USART_Init(115200);
            ServoControl(pitch_servo, pitch_scan_angle, pitch_D_left_water_angle, YAW_TRANSFER_TIME);
            delay_ms(OPENMV_WAIT);
            water(get_OpenMV());
            ServoControl(yaw_servo, yaw_mid, right_D_angle, YAW_TRANSFER_TIME);
        }
        OpenMV_USART_Close();
    }
}

int B_add = 0;
void arm_water_task(void)
{
    get_region();
    while (!water_finish() && lidar_water_confirm()) // һ����һ����־λ
    {
        get_water_direction();
        water_task();
    }
    if (water_finish_structure.left_water_finish && water_finish_structure.right_water_finish)
    {
        water_finish_structure.left_water_finish = 0;
        water_finish_structure.right_water_finish = 0;
        //        if (region == C || region == D)
        //        {q
        GYRO_Init();
        if (abs(target_roll - current_roll) > 70 && region == B)
        {
            B_add = 2 * (lidar_right - 19);
            if (abs(B_add) > 7)
            {
                B_add = (B_add > 0) ? 7 : -7;
            }
            Car_Load(25 + B_add, 25 - B_add);
            delay_ms(1000);
            Car_stop();
        }
        // else if (region == C)
        // {
        // }
        // else if (region == B && plant_cnt > 9 || plant_cnt < 14)
        // {
        //     Car_Load(20, 20);
        //     delay_ms(100);
        //     Car_stop();
        // }
        PE_EXTI_Open();
        // delay_ms(10);
        // delay_ms(10);
        //        }
    }
}
// void task_A(void)
//{
//	char i = 0;
//	int plant = 0;

//	for (i = 0; i < 6; i++)
//	{
//		Rotation(1, 0); // ���ˮ���ƶ�����ˮ
//		Rotation(1, 1); // �ұ�ˮ���ƶ�����ˮ
//	}
//}

// void task_B(void)
//{
//	char i = 0;

//	//	delay_init(168);
//	//	TIM_SetCompare4(TIM8,Balance_angle);	//ƽ��Ƕ�
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
//		R_r = 1; // ���������жϵ�
//		//		Flower_Count++;
//		//		printf("distance_r=%d\r\n",lidar_right);//���Լ����ܲ�����������
//		//		printf("Flower_Count=%d, N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // ˫�ر���
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
//		//		printf("distance_l=%d\r\n",lidar_left);//���Լ����ܲ�����������
//		//		printf("Flower_Count=%d,N_Flag=%d/r/n",Flower_Count,N_Flag);
//		delay_ms(500);
//		if (N_Flag == 0) // ˫�ر���
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
//	set = 1;	  // �¼ӵģ���С���տ�ʼ��һ���ٶ�
//	delay_ms(20); //
//	TIM7_Int_Init(1000 - 1, 840 - 1);
//	delay_ms(80); //
//	set = 0;
//	delay_ms(80); // 200->100
//	set = 0;
//	//	BEEP=1;
//}
