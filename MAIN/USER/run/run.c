#include "run.h"

u8 get_Itr(void);
//=================== begin checking =====================:
int data_check(void) // ������ݽ����Ƿ�ɹ�
{
    // ������־λ + buffer ��־λ��֡β��
    // Bluetooth_USART_Init(115200);
    if (bluetooth_receive_flag)
    {
        // Bluetooth_USART_Close();
        chassis_Init();
        delay_ms(1000);
        arm_Init();
        delay_ms(1000);
        return 1;
    }
    return 0;
}
////--------------- TIME CONST --------------//
const u16 GO_PREVENT_MISID_TIME = 200; // go in case of misidentification time
const u16 GO_HOME_TIME = 1000;
// const u16 RUN_SPEED = 10;
const u16 CROSS_TIME = 2000;
// int run_speed = 0;
////--------------- TEST --------------//
//// int test1(void)
//// {
////     Set_Discounter(20);
////     return 1;
//// }

//// int test2(void)
//// {
////     Abs_Speed_Run(0, 0.10, 0);
////     if (Discounter_Arrive())
////         return 1;
////     return 0;
//// }

//// int test3(void)
//// {
////     return 1;
//// }

//=================== gray control =====================:
int plant_cnt = 0; // for 5-7 / 11-13 / 17-30 | cross_cnt   (N_flag)
regionEnum region = home;
int get_region(void)
{
    return region;
}
/**
 * @brief  finish watering for one region (A, B, C, D)
 * ��run���������crossǰ��
 * @param    None
 * @return   region_finish_flag
 */
int region_finish(void)
{
    region = (cross_cnt < 2) ? A : ((cross_cnt < 4) ? B : ((cross_cnt < 6) ? C : D));
    if (((plant_cnt >= 6 && plant_cnt < 9) && region == A) || ((plant_cnt >= 12 && plant_cnt < 15) && region == B) || ((plant_cnt >= 24 && plant_cnt < 27) && region == C) || (plant_cnt >= 30 && region == D)) // 21 in total
    {
        plant_cnt = (region == A) ? 6 : ((region == B) ? 12 : 24);
        return 1; // 2/4/6 -> 0
    }
    return 0;
}

// ֻ�ĽǶȣ���������ת(inner function)
int cross_action(void)
{
    // chassis_mode = rotate_mode;
    chassis_rotate(target_Yaw);
    if (rotate_arrive)
    {
        if (cross_cnt % 2 == 0) // even cross open
        {
            PE_EXTI_Open();
            // TFmini_left_USART_Init(115200);
            // TFmini_right_USART_Init(115200);
            delay_ms(2);
            return 1;
        }
        // for (int i = 0; i < 20; ++i)
        // {
        // for (int i = 0; i < 20; ++i)
        // {
        set_speed(RUN_SPEED, RUN_SPEED);
        chassis_run();
        // chassis_run(RUN_SPEED, target_Yaw); // in case of misidentification of the line
        delay_ms(GO_PREVENT_MISID_TIME);
        // }
        // }
        return 1;
    }
    return 0;
}

//=================== car control =====================:
// 24 C  B 19   D 18

#define B_error_coefficient 0.3
#define C_error_coefficient 0.45
#define D_error_coefficient 0.4
int lidar_err = 0, C_lidar_error = 0;
const int B_lidar_err_dis = 19;
const int C_lidar_err_dis = 24;
const int D_lidar_err_dis = 18;

int _run_(void)
{
    if (region_finish() && get_cross_flag())
    {
        Car_stop();
        // set_speed(0, 0);
        PE_EXTI_Close();
        // set_speed(0, 0);
        // TIM7_Init(1000 - 1, 840 - 1);
        // TIMM7_Open();
        return 1;
    }
    else
    {
        if (!water_finish()) // �õ���ˮ��־λ
        {
            arm_water_task();
        }
        else
        {
            TIMM7_Open();
            // set_speed(RUN_SPEED, RUN_SPEED);
            // chassis_run();
            // TIM7_Init(1000 - 1, 840 - 1);
            // set_speed(RUN_SPEED, RUN_SPEED);
            // if (region == A)
            // {
            //     set_speed(RUN_SPEED, RUN_SPEED);
            //     chassis_run();
            // }
            set_speed(RUN_SPEED, RUN_SPEED);
            chassis_run();
            if ((region == B && plant_cnt >= 7) || (region == D && plant_cnt >= 25))
            {
                lidar_err = B_error_coefficient * (lidar_right - lidar_left);
                set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
                chassis_run();
            }
            else if (region == C && plant_cnt >= 13)
            {
                set_speed(RUN_SPEED + C_error_coefficient * C_lidar_error, RUN_SPEED - C_error_coefficient * C_lidar_error);
                chassis_run();
            }
            else
            {
                set_speed(RUN_SPEED, RUN_SPEED);
                chassis_run();
            }
            // else if (region == D)
            // {
            //     lidar_err = D_error_coefficient * (lidar_right - lidar_left);
            //     set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
            // }
            // if (region == B)
            // {

            // }
            // if (region == B)
            // {

            //     // lidar_err =
            // set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
            // }
            // chassis_run(RUN_SPEED, target_Yaw); // ��Ҫһ��������������
            // if (region == A || region == B)
            // {
            //     PE_EXTI_Close();
            //     delay_ms(2);
            //     chassis_run(RUN_SPEED, target_Yaw);
            //     PE_EXTI_Init();
            // }
            // else if (region == C || region == D)
            // {
            //     PE_EXTI_Close();
            //     delay_ms(3);
            //     chassis_run(RUN_SPEED, target_Yaw);
            //     PE_EXTI_Init();
            // }
        }
        return 0;
    }
}
int temp_flag = 0;
int cross_to_cross(void)
{
    if (!temp_flag)
    {
        temp_flag = 1;
        set_speed(RUN_SPEED + 10, RUN_SPEED + 10);
        chassis_run();
        delay_ms(CROSS_TIME);
    }
    // if (cross_cnt % 2 != 0) //
    // {
    // for (int i = 0; i < 500; ++i)
    // {

    // chassis_run(RUN_SPEED, target_Yaw);
    // }

    // for (int i = 0; i < 15; ++i)
    // {
    // delay_ms(CROSS_TIME);
    // }
    if (get_cross_flag()) // cross_cnt++
    {
        temp_flag = 0;
        PE_EXTI_Init(); // ��ȷ������û
        return 1;
    }
    // }
    return 0;
}

///*============color operation=========================*/

int end_return_home(void)
{
    // chassis_run(RUN_SPEED, target_Yaw);

    for (int i = 0; i < 20; ++i)
    {
        set_speed(RUN_SPEED, RUN_SPEED);
        chassis_run();
        delay_ms(GO_HOME_TIME);
    }
    movement_stop();
    return 1;
    //    Target_Run(0, 0, 0);
    //    // speed_limit = 0.08;
    //    servoMove(calibObj, 100);
    //    if (flag_arrive && flag_stable)
    //        return 1;
    //    return 0;
}

//----------- Run Excutor -----------//
// int (*operation_sequence[])(void) = {
//     data_check,
//     _run_,
//     cross_action, cross_to_cross, cross_action, // A��
//     _run_, cross_action, cross_to_cross,
//     // cross_action, // B��
//     //  _run_, cross_action, cross_to_cross, cross_action, // C��
//     //  _run_,                                             // D��
//     end_return_home}; // D finish and go home
// u8 max_run_itr = 8;

int (*operation_sequence[])(void) = {
    data_check,
    _run_, cross_action, cross_to_cross, cross_action, // A��
    _run_, cross_action, cross_to_cross,
    // cross_action, // B��
    //  _run_, cross_action, cross_to_cross, cross_action, // C��
    //  _run_,                                             // D��
    end_return_home}; // D finish and go home
u8 max_run_itr = 9;

// int(*operation_sequence[])(void) = {test1, test2, test3};
// u8 max_run_itr = 3;

u8 itr = 0;

void Run(void)
{
    if (operation_sequence[itr]())
        itr++;
    if (itr >= max_run_itr)
    {
        itr = 0;
        Car_stop();
    }
}

void stop_running(void)
{
    // flag_start = 0;
    itr = 0;
}

u8 get_Itr(void)
{
    return itr;
}
