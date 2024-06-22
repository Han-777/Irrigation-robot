#include "run.h"

// u8 color_Index = 0; // ���ϵ�����
// const float slow_move_speed ;

u8 get_Itr(void);
//=================== begin checking =====================:
int data_check(void) // ������ݽ����Ƿ�ɹ�
{
    // ������־λ + buffer ��־λ��֡β��
    PE_EXTI_Init();
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
    if (((plant_cnt >= 6 && plant_cnt < 7) && cross_cnt < 2) || (cross_cnt < 4 && (plant_cnt >= 11 && plant_cnt < 13)) || (cross_cnt < 6 && plant_cnt >= 17 && plant_cnt <= 25) || (plant_cnt == 30 && cross_cnt == 6)) // 21 in total
    {
        plant_cnt = (cross_cnt <= 2) ? 6 : ((cross_cnt <= 4) ? 12 : 24);
        region = (cross_cnt < 2) ? A : ((cross_cnt < 4) ? B : ((cross_cnt < 6) ? C : D));
        return 1; // 2/4/6 -> 0
    }
    return 0;
}

// ֻ�ĽǶȣ���������ת(inner function)
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
        // switch (get_region())
        // {
        // case A:
        // case B:
        //     break;
        // case C:
        // case D:
        //     break;
        // case beg:
        // case home:
        //     break;
        // }

        if (!water_finish()) // �õ���ˮ��־λ
        {
//            TIM7_Close();
            // water: arm_watering(); ���������������/�ҽ�ˮ��־λ���������־λ�������TIM7��
            arm_water_task();
        }
        else
        {
            TIM7_Init(1000 - 1, 840 - 1);
            chassis_run(27, target_Yaw); // ��Ҫһ��������������
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
    _run_, cross_action, cross_to_cross, cross_action, // A��
    _run_, cross_action, cross_to_cross, cross_action, // B��
    _run_, cross_action, cross_to_cross, cross_action, // C��
    _run_,                                             // D��
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
