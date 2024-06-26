#include "run.h"

u8 get_Itr(void);
//=================== begin checking =====================:
int data_check(void) // 检查数据接收是否成功
{
    // 蓝牙标志位 + buffer 标志位（帧尾）
    // Bluetooth_USART_Init(115200);
    if (bluetooth_receive_flag)
    {
        // Bluetooth_USART_Close();
        chassis_Init();
        delay_ms(2000);
        arm_Init();
        delay_ms(2000);
        return 1;
    }
    return 0;
}
////--------------- TIME CONST --------------//
const u16 GO_PREVENT_MISID_TIME =
    200; // go in case of misidentification time
const u16 GO_HOME_TIME = 1000;
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
    if (((plant_cnt >= 5 && plant_cnt < 9) && region == A) || ((plant_cnt > 10 && plant_cnt < 17) && region == B) || ((plant_cnt > 20 && plant_cnt < 29) && region == C) || (plant_cnt >= 28 && region == D)) // 21 in total
    {
        plant_cnt = (region == A) ? 6 : ((region == B) ? 12 : 24);
        TIMM7_Open();
        return 1; // 2/4/6 -> 0
    }
    return 0;
}

// 只改角度，在外面旋转(inner function)
int cross_action(void)
{
    // chassis_mode = rotate_mode;
    // rotate_arrive = 0;
    // get_cross_flag();
    chassis_rotate(target_Yaw);
    if (rotate_arrive && abs(target_Yaw - current_yaw) < 1)
    {
        //        MP3_broadcast(1);
        //        delay_ms(5000);
        if (cross_cnt % 2 == 0) // even cross open
        {
            PE_EXTI_Open();
            // TFmini_left_USART_Init(115200);
            // TFmini_right_USART_Init(115200);
            delay_ms(2);
            // PE_EXTI_Open();
            return 1;
        }
        // for (int i = 0; i < 20; ++i)
        // {
        // for (int i = 0; i < 20; ++i)
        // {
        for (int i = 0; i < 10; ++i)
        {
            set_speed(RUN_SPEED, RUN_SPEED);
            chassis_run();
            // chassis_run(RUN_SPEED, target_Yaw); // in case of misidentification of the line
            delay_ms(GO_PREVENT_MISID_TIME);
        }
        // }
        // }
        return 1;
    }
    return 0;
}

//=================== car control =====================:
// 24 C  B 19   D 18

#define B_error_coefficient 0.4
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
        TIMM7_Open();
        delay_ms(10);
        //        delay_ms(10);
        //        TIMM7_Open();
        return 1;
    }
    else
    {
        if (!water_finish()) // 得到浇水标志位
        {
            Car_stop();
            arm_water_task();
            PE_EXTI_Open();
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
            // set_speed(RUN_SPEED, RUN_SPEED);
            // chassis_run();
            lidar_err = 0;
            if ((region == B && plant_cnt >= 7))
            {
                if (lidar_right)
                {
                    lidar_err = B_error_coefficient * (lidar_right - B_lidar_err_dis);
                }
                if (abs(lidar_err) > 12)
                {
                    lidar_err = (lidar_err > 0) ? 12 : -12;
                }
                set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
                chassis_run();
            }
            else if (region == C && plant_cnt >= 12)
            {
                if (abs(C_lidar_error) > 12)
                {
                    C_lidar_error = (C_lidar_error > 0) ? 12 : -12;
                }
                set_speed(RUN_SPEED + C_error_coefficient * C_lidar_error, RUN_SPEED - C_error_coefficient * C_lidar_error);
                chassis_run();
            }
            else if ((region == D && plant_cnt >= 25))
            {
                lidar_err = D_error_coefficient * (lidar_right - lidar_left);
                if (abs(lidar_err) > 12)
                {
                    lidar_err = (lidar_err > 0) ? 12 : -12;
                }
                set_speed(RUN_SPEED + lidar_err, RUN_SPEED - lidar_err);
                chassis_run();
            }
            else
            {
                set_speed(RUN_SPEED, RUN_SPEED); // A
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
// int temp_flag = 0;
int cross_to_cross(void)
{
    //    if (!temp_flag)
    //    {
    //        temp_flag = 1;
    //        for (int i = 0; i < 3; ++i)
    //        {
    // set_speed(RUN_SPEED, RUN_SPEED);
    chassis_run();
    //            delay_ms(CROSS_TIME);
    //        }
    //    }
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
        // delay_ms(5000);
        TIMM7_Open();
        //        temp_flag = 0;
        //        PE_EXTI_Init(); // 不确定开了没
        return 1;
    }
    // }
    return 0;
}

///*============color operation=========================*/

int end_return_home(void)
{
    // chassis_run(RUN_SPEED, target_Yaw);

    for (int i = 0; i < 3; ++i)
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
//     cross_action, cross_to_cross, cross_action, // A区
//     _run_, cross_action, cross_to_cross,
//     // cross_action, // B区
//     //  _run_, cross_action, cross_to_cross, cross_action, // C区
//     //  _run_,                                             // D区
//     end_return_home}; // D finish and go home
// u8 max_run_itr = 8;

int (*operation_sequence[])(void) = {
    data_check,
    _run_, cross_action, cross_to_cross, cross_action, // A区
    _run_, cross_action, cross_to_cross, cross_action, // B区
    _run_, cross_action, cross_to_cross, cross_action, // C区
    _run_,                                             // D区
    end_return_home};                                  // D finish and go home
u8 max_run_itr = 15;

// int (*operation_sequence[])(void) = {test1, test2, test3};
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
