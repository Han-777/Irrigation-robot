#include "chassis.h"
#include "openmv.h"

// u8 color_Index = 0; // 车上的数量
const float slow_move_speed = 0.3;
void qr_Run_Main(void);
void obj_Run_Main(void);
void rough_Run_Main(void);
void deposit_Run_Main(void);
void backObj_Run_Main(void);
void obj2_Run_Main(void);
void deposit2_Run_Main(void);
void home_Run_Main(void);
void stop_running(void);
u8 get_Itr(void);

//=================== gray control =====================:
int region_finish_flag = 0, cross_cnt = 0, plant_cnt = 0; // for 5-7 / 11-13 / 17-30 | cross_cnt(N_flag)
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
        region_finish_flag = 1;
        return region_finish_flag; // 2/4/6 -> 0
    }
    return region_finish_flag;
}

// 只改角度，在外面旋转(inner function)
void cross_action(void)
{
    cross_cnt++;
    if (cross_cnt == 2 || cross_cnt == 4 || cross_cnt == 6)
    {
        clockwise_rotate_flag += ((cross_cnt == 4) ? -1 : 1);
        PE_EXTI_Init(); // pe open
    }
    else if (cross_cnt == 1 || cross_cnt == 3 || cross_cnt == 5)
    {
        clockwise_rotate_flag += ((cross_cnt == 3) ? -1 : 1);
    }
}

int gray_control(void)
{
    PE_EXTI_Close(); // pe_close
    if (get_cross_flag() && region_finish_flag)
    {
        region_finish_flag = 0;
        Car_stop();
        // change clockwise_rotate_flag to 1 or -1
        cross_action();
    }
    chassis_rotate(target_Yaw);
    if (rotate_arrive)
    {
        return 1;
    }
    return 0;
}

////--------------- TIME CONST --------------//
// u16 mv_calib_time = 5000;
// u16 get_put_time = 10000;
// u16 to_idle_time = 5000;

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

////------------ QR Code ------------//
//// int qr1_1(void)
////{
////    Target_Run(-0.18, 0.6, 0);
////    speed_limit = 0.08;
////    if (flag_arrive)
////        return 1;
////    return 0;
////}

//// int qr1_2(void)
////{
////     Abs_Speed_Run(0, 0.05, 0);
////     if (QR_Ready() == qrWrong)
////     {
////         Stop_Run(); // 错了停车再扫
////     }
////     else if (QR_Ready() == scanning && OPS_y > 1.8f)
////     {
////         Stop_Run();
////         stop_running(); // 走太远了，直接锁死，等手动重置
////     }
////     else if (QR_Ready() == qrRight)
////     {
////         return 1;
////     }
////     return 0;
//// }
///*============color operation=========================*/
// void color_operation(void)
//{
//     switch (omv_color_data)
//     {
//     // Target_Run(0.97, -0.59, 0);  // yellow
//     // Target_Run(-0.89, -0.64, 0); // red
//     // Target_Run(-0.98, 0.30, 180);  // blue
//     // Target_Run(0.60, -0.95, 0); // green
//     case red:
//         Target_Run(-0.78, -0.52, 0);
//         break;
//     case green:
//         Target_Run(0.5, -0.77, 0);
//         break;
//     case blue:
//         Target_Run(-0.78, 0.26, 90);
//         break;
//     case yellow:
//         Target_Run(0.80, -0.48, 0);
//         break;
//     default:
//         Stop_Run();
//         // 红坐标
//     }
// }

// void color_put(void)
//{
//     switch (omv_color_data)
//     {
//     case red:
//         servoMove(putRed, 3000);
//         delay_ms(1000);
//         break;
//     case green:
//         servoMove(putGreen, 3000);
//         delay_ms(1000);
//         break;
//     case blue:
//         servoMove(putGreen, 3000);
//         delay_ms(1000);
//         break;
//     case yellow:
//         servoMove(putYellow, 3000);
//         delay_ms(1000);
//         break;
//     }
// }
////------------ Get Object ------------//
//// int obj1_1(void)
//// {
////     Target_Run(-0.20, 1.25, 0);
////     speed_limit = 0.08;
////     if (flag_vague_arrive)
////         return 1;
////     return 0;
//// }
// int obj1_1(void)
//{
//     Target_Run(0.49, 0.72, 0);

//    // Target_Run(-0.1, 0.3, 0);
//    servoMove(calibObj, 100);
//    omv_color_data = black;
//    if (flag_vague_arrive)
//    {
//        Stop_Run();
//        return 1;
//    }
//    return 0;
//}

// u8 temp_itr = 0;
// int obj1_2(void)
//{
//     // Target_Run(-0.1, 0.3, 0);
//     Target_Run(0.5, 0.78, 0);
//     if (flag_arrive && omv_color_data != black)
//     {
//         Stop_Run();
//         delay_ms(500);
//         servoMove(getObj, 2000);
//         return 1;
//     }
//     //    set_mode(openmvMode);
//     //    if (check_openmv_arrive())
//     //    {
//     //        OPS_Calibrate(0.2, 1, 0);
//     //        return 1;
//     //    }
//     // delay_ms(2000);

//    // Target_Run(0.61, 0.93, 0);
//    // if (flag_arrive)
//    // {
//    // }
//    return 0;
//}

// int obj1_3(void)
//{
//     // Target_Run(0.97, -0.59, 0);  // yellow
//     // Target_Run(-0.89, -0.64, 0); // red
//     // Target_Run(-0.98, 0.30, 180);  // blue
//     // Target_Run(0.60, -0.95, 0); // green
//     color_operation();
//     if (flag_vague_arrive)
//         return 1;
//     return 0;
//     // judge
//     // if ((mv_color == red
//     // || mv_color == green
//     // || mv_color == blue
//     // || mv_color == yellow)
//     // && temp_itr == 0)
//     // {
//     // 	delay_ms(100);
//     //     servoMove(getObj, 7000);
//     // 	temp_itr++;
//     //     return 1;
//     // }

//    //	        servoMove(getObj, 5000);

//    // else if (temp_itr == 1)
//    // {
//    // 	switch (mv_color)
//    //     {
//    //     case red:
//    //         Target_Run(0, 0, 0);
//    // 		break;
//    // 	case green:
//    // 		Target_Run(0, 0, 0);
//    // 		break;
//    // 	case blue:
//    // 		Target_Run(0, 0, 0);
//    // 		break;
//    // 	case yellow:
//    // 		Target_Run(0, 0, 0);
//    // 		break;
//    // 	default:
//    //         flag_vague_arrive = 0;
//    // 		break;
//    //     }
//    // 	if (flag_vague_arrive)
//    // 	{
//    // 		temp_itr++;
//    // 	}
//    // }
//    // else if (temp_itr == 2)
//    // {
//    //     servoMove(mv_color, 5000);  // put obj
//    //     temp_itr = 0;
//    //     mv_color = black;
//    // }
//}

// int obj1_4(void)
//{
//     Stop_Run();
//     color_put();
//     // servoMove(putRed, 3000); // 需要抬起来
//     return 1;
// }

// int obj2_1(void)
//{
//     Target_Run(0.24, 0.68, 0);
//     servoMove(calibObj, 100);
//     omv_color_data = black;
//     if (flag_vague_arrive)
//     {
//         Stop_Run();
//         return 1;
//     }
//     return 0;
// }

// int obj2_2(void)
//{
//     // Target_Run(0.30, 0.93, 0);
//     // if (flag_arrive)
//     // {
//     //     Stop_Run();
//     //     servoMove(getObj, 3000);
//     //     return 1;
//     // }
//     Target_Run(0.24, 0.78, 0);
//     if (flag_arrive && omv_color_data != black)
//     {
//         Stop_Run();
//         // delay_ms(500);
//         delay_ms(500);
//         servoMove(getObj, 2000);
//         return 1;
//     }
//     return 0;
// }

//// int obj2_3(void)
//// {
////     // Target_Run(0.97, -0.59, 0);  // yellow
////     // Target_Run(-0.89, -0.64, 0);  // red
////     // Target_Run(-0.98, 0.30, 180);  // blue
////     // Target_Run(0.60, -0.95, 0); // green
////     color_operation();
////     if (flag_vague_arrive)
////         return 1;
////     return 0;
//// }

//// int obj2_4(void)
//// {
////     Stop_Run();
////     // servoMove(putGreen, 3000);
////     color_put();
////     return 1;
//// }

// int obj3_1(void)
//{
//     Target_Run(-0.24, 0.72, 0);
//     servoMove(calibObj, 100);
//     omv_color_data = black;
//     if (flag_vague_arrive)
//     {
//         Stop_Run();
//         return 1;
//     }
//     return 0;
// }

// int obj3_2(void)
//{
//     // delay_ms(2000);
//     // Stop_Run();
//     // Target_Run(-0.29, 0.93, 0);
//     // if (flag_arrive)
//     // {
//     //     Stop_Run();
//     //     servoMove(getObj, 3000);
//     //     return 1;
//     // }
//     //	delay_ms(100);
//     Target_Run(-0.24, 0.78, 0);
//     // delay_ms(1000);
//     // servoMove(getObj, 2000);
//     if (flag_arrive && omv_color_data != black)
//     {
//         Stop_Run();
//         delay_ms(500);
//         servoMove(getObj, 2000);
//         return 1;
//     }
//     return 0;
// }

//// int obj3_3(void)
//// {
////     // Target_Run(-0.89, -0.64, 0);  // red
////     Target_Run(0.97, -0.59, 0); // yellow
////     // Target_Run(-0.98, 0.30, 180);  // blue
////     // Target_Run(0.60, -0.95, 0); // green
////     if (flag_vague_arrive)
////         return 1;
////     return 0;
//// }

//// int obj3_4(void)
//// {
////     Stop_Run();
////     servoMove(putYellow, 3000);
////     return 1;
//// }

// int obj4_1(void)
//{
//     Target_Run(-0.50, 0.72, 0);
//     servoMove(calibObj, 100);
//     omv_color_data = black;
//     if (flag_vague_arrive)
//     {
//         Stop_Run();
//         return 1;
//     }
//     return 0;
// }

// int obj4_2(void)
//{
//     // Target_Run(-0.58, 0.93, 0);
//     // if (flag_arrive)
//     // {
//     //     // Stop_Run();
//     //     servoMove(getObj, 3000);
//     //     return 1;
//     // }
//     Target_Run(-0.50, 0.78, 0);

//    if (flag_arrive && omv_color_data != black)
//    {
//        Stop_Run();
//        delay_ms(500);
//        servoMove(getObj, 2000);
//        return 1;
//    }
//    // servoMove(getObj, 3000);
//    return 0;
//}

int end_return_home(void)
{
    chassis_run(20, target_Yaw);
    gray_control();
    //    Target_Run(0, 0, 0);
    //    // speed_limit = 0.08;
    //    servoMove(calibObj, 100);
    //    if (flag_arrive && flag_stable)
    //        return 1;
    //    return 0;
}

//----------- Run Excutor -----------//
int (*operation_sequence[])(void) = {
    region_finish, gray_control,

    //    obj1_1, obj1_2, obj1_3, obj1_4,
    //    obj2_1, obj2_2, obj1_3, obj1_4,
    //    obj3_1, obj3_2, obj1_3, obj1_4,
    //    obj4_1, obj4_2, obj1_3, obj1_4,
    //    obj2_1, obj2_2, obj2_3, obj2_4, obj2_5,
    //    obj3_1, obj3_2, obj3_3, obj3_4, obj3_5,
    region_finish, end_return_home}; // D finish and go home
u8 max_run_itr = 17;

// int(*operation_sequence[])(void) = {test1, test2, test3};
// u8 max_run_itr = 3;

u8 itr = 0;

void Run(void)
{
    if (operation_sequence[itr]())
        itr++;
    if (itr >= max_run_itr)
    {
        //        itr = 0;
        //        flag_start = 0;
        //        Stop_Run();
    }
} // 做固定动作组

void stop_running(void)
{
    //    flag_start = 0;
    itr = 0;
}

u8 get_Itr(void)
{
    return itr;
}
