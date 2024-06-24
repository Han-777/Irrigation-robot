#include "run.h"

// u8 color_Index = 0; // 车上的数量
// const float slow_move_speed ;

u8 get_Itr(void);
//=================== begin checking =====================:
int data_check(void) // 检查数据接收是否成功
{
    // 蓝牙标志位 + buffer 标志位（帧尾）
    Bluetooth_USART_Init(115200);
    if (bluetooth_receive_flag)
    {
        Bluetooth_USART_Close();
        chassis_Init();
        arm_Init();
        delay_ms(2000);
        return 1;
    }
    return 0;
}
////--------------- TIME CONST --------------//
const u16 GO_PREVENT_MISID_TIME = 4000; // go in case of misidentification time
const u16 GO_HOME_TIME = 10;
// const u16 RUN_SPEED = 10;
const u16 CROSS_TIME = 1000;
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
 * 在run函数里放在cross前面
 * @param    None
 * @return   region_finish_flag
 */
int region_finish(void)
{
    region = (cross_cnt < 2) ? A : ((cross_cnt < 4) ? B : ((cross_cnt < 6) ? C : D));
    if (((plant_cnt >= 5 && plant_cnt < 9) && region == A) || ((plant_cnt >= 11 && plant_cnt < 15) && region == B) || ((plant_cnt >= 23 && plant_cnt < 27) && region == C) || (plant_cnt >= 30 && region == D)) // 21 in total
    {
        plant_cnt = (region == A) ? 6 : ((region == B) ? 12 : 24);
        return 1; // 2/4/6 -> 0
    }
    return 0;
}

// 只改角度，在外面旋转(inner function)
int cross_action(void)
{
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
        set_speed(RUN_SPEED, RUN_SPEED);
        // chassis_run(RUN_SPEED, target_Yaw); // in case of misidentification of the line
        delay_ms(GO_PREVENT_MISID_TIME);
        // }
        return 1;
    }
    return 0;
}

//=================== car control =====================:
// 24 C  B 19   D 18

#define B_error_coefficient 3
#define C_error_coefficient 7
#define D_error_coefficient 3
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
        TIM7_Init(1000 - 1, 840 - 1);
        PE_EXTI_Close(); // PE close
        return 1;
    }
    else
    {
        if (!water_finish()) // 得到浇水标志位
        {
            arm_water_task();
        }
        else
        {
            TIM7_Init(1000 - 1, 840 - 1);
            set_speed(RUN_SPEED, RUN_SPEED);
            if (region == B)
            {
                lidar_err = B_error_coefficient * (right_lidar - left_lidar);
                set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
            }
            else if (region == C)
            {
                set_speed(RUN_SPEED + C_error_coefficient * C_lidar_error, RUN_SPEED - C_error_coefficient * C_lidar_error);
            }
            else if (region == D)
            {
                lidar_err = D_error_coefficient * (right_lidar - left_lidar);
                set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
            }
            // if (region == B)
            // {

            // }
            // if (region == B)
            // {

            //     // lidar_err =
            // set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
            // }
            // chassis_run(RUN_SPEED, target_Yaw); // 需要一个函数区分区域
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

int cross_to_cross(void)
{
    // if (cross_cnt % 2 != 0) //
    // {
    // for (int i = 0; i < 500; ++i)
    // {
    set_speed(RUN_SPEED, RUN_SPEED);
    // chassis_run(RUN_SPEED, target_Yaw);
    // }
    //    delay_ms(CROSS_TIME);
    if (get_cross_flag()) // cross_cnt++
    {
        // PE_EXTI_Init(); // 不确定开了没
        return 1;
    }
    // }
    return 0;
}

///*============color operation=========================*/

int end_return_home(void)
{
    // chassis_run(RUN_SPEED, target_Yaw);
    set_speed(RUN_SPEED, RUN_SPEED);
    delay_ms(GO_HOME_TIME);
    Car_stop();
    //    Target_Run(0, 0, 0);
    //    // speed_limit = 0.08;
    //    servoMove(calibObj, 100);
    //    if (flag_arrive && flag_stable)
    //        return 1;
    //    return 0;
}

//----------- Run Excutor -----------//
int (*operation_sequence[])(void) = {
    data_check,
    _run_, cross_action, cross_to_cross, cross_action, // A区
    _run_, cross_action, cross_to_cross, cross_action, // B区
    _run_, cross_action, cross_to_cross, cross_action, // C区
    _run_,                                             // D区
    end_return_home};                                  // D finish and go home
u8 max_run_itr = 15;

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
