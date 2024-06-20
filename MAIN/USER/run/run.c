#include "run.h"

// u8 color_Index = 0; // 车上的数量
//const float slow_move_speed ;

u8 get_Itr(void);
//=================== begin checking =====================:
int data_check(void) // 检查数据接收是否成功
{
    // 蓝牙标志位 + buffer 标志位（帧尾）
    return 1;
}

////--------------- TIME CONST --------------//
const u16 GO_PREVENT_MISID_TIME = 200; // go in case of misidentification time
const u16 GO_HOME_TIME = 500; 
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
int plant_cnt = 0; // for 5-7 / 11-13 / 17-30 | cross_cnt(N_flag)
/**
 * @brief  finish watering for one region (A, B, C, D)
 * 在run函数里放在cross前面
 * @param    None
 * @return   region_finish_flag
 */
int region_finish(void)
{
    if ((plant_cnt >= 5 && plant_cnt < 7) || (plant_cnt >= 11 && plant_cnt < 13) || (plant_cnt >= 17 && plant_cnt < 30)) // 21 in total
    {
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
            PE_EXTI_Init();
            return 1;
        }
        chassis_run(30, target_Yaw); // in case of misidentification of the line
        delay_ms(GO_PREVENT_MISID_TIME);
        return 1;
    }
    return 0;
}

//=================== car control =====================:

int _run_(void)
{
    if (region_finish() && get_cross_flag())
    {
        Car_stop();
        PE_EXTI_Close(); // PE close
        return 1;
    }
    else
    {
        if (left_water_flag || right_water_flag) // 得到浇水标志位
        {
            // water: arm_watering(); （函数负责清楚左/右浇水标志位，如果两标志位都无则给TIM7）
        }
        else
        {
            chassis_run(30, target_Yaw); // 需要一个函数区分区域
        }
        return 0;
    }
}

int cross_to_cross(void)
{
    // if (cross_cnt % 2 != 0) //
    // {
    chassis_run(30, target_Yaw);
    if (get_cross_flag()) // cross_cnt++
    {
        return 1;
    }
    // }
    return 0;
}


///*============color operation=========================*/


int end_return_home(void)
{
    chassis_run(10, target_Yaw);
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
u8 max_run_itr = 5;

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
