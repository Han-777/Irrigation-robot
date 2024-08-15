#include "mp3.h"
#include "water.h"
#include "message_center.h"
#include "servo_motor.h"
#include "photoelectric.h"
#include "robot_def.h"
#include "servo_motor.h"

static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;

// static ServoInstance *pitchServoMotor, *yawServoMotor;
static uint8_t info_buff[18] = {1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3};
static uint8_t plant_Cnt_record = 0; // number of setting
void WaterInit(void)
{
    MP3_Init();
    // 舵机初始化
    // ServoInstance servo_init_config;
    // servo_init_config.Channel = TIM_CHANNEL_1;
    // servo_init_config.Servo_Angle_Type = Start_mode;
    // servo_init_config.Servo_type = Servo270;
    // servo_init_config.htim = &htim13;
    // pitchServoMotor = ServoInit(&servo_init_config);
    // servo_init_config.htim = &htim14;
    // pitchServoMotor = ServoInit(&servo_init_config);
    // Servo_Init_Config_s *config = (Servo_Init_Config_s
    // ServoInit();
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

void water_flag_handle(void)
{
    static uint8_t cnt = 0;
    // if (water_feedback_data.water_finish_state != water_finish_flag && water_recv_data.water_flag != none_water_flag)
    // {
    //     if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
    //     {
    //         // 左边浇水过程
    //         if (++cnt % 2000 == 0)
    //         {
    //             cnt = 0;
    //             water_feedback_data.water_finish_state |= left_water_flag;
    //             // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
    //         }
    //     }
    //     else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
    //     {
    //         // 右边浇水
    //         if (++cnt % 2000 == 0)
    //         {
    //             cnt = 0;
    //             water_feedback_data.water_finish_state |= right_water_flag;
    //             // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
    //         }
    //     }
    //     if (water_feedback_data.water_finish_state == water_finish_flag)
    //     {
    //         water_feedback_data.plant_cnt++;
    //         water_feedback_data.water_finish_state = none_water_flag;
    //     }
    // }
    // else
    // {
    //     switch (plant_Cnt_record)
    //     {
    //     case 0:
    //         if (water_recv_data.set_plantCnt_flag == 6)
    //         {
    //             plant_Cnt_record = 1;
    //             water_feedback_data.plant_cnt = 6;
    //         }
    //         break;
    //     case 1:
    //         if (water_recv_data.set_plantCnt_flag == 12)
    //         {
    //             plant_Cnt_record = 2;
    //             water_feedback_data.plant_cnt = 12;
    //         }
    //         break;
    //     case 2:
    //         if (water_recv_data.set_plantCnt_flag == 18)
    //         {
    //             plant_Cnt_record = 3;
    //             water_feedback_data.plant_cnt = 18;
    //         }
    //         break;
    //     default:
    //         break;
    //     }
    // }
    if (water_recv_data.water_flag == none_water_flag)
    {
        water_feedback_data.water_finish_state = none_water_flag;
        switch (water_recv_data.set_plantCnt_flag)
        {
        case 0:
            // if (water_recv_data.set_plantCnt_flag == 6)
            // {
            //     plant_Cnt_record = 1;
            //     water_feedback_data.plant_cnt = 6;
            // }
            break;
        case 6:
            // plant_Cnt_record = 2;
            water_feedback_data.plant_cnt = 6;
            break;
        case 12:
            // plant_Cnt_record = 3;
            water_feedback_data.plant_cnt = 12;
            break;
        case 18:
            // plant_Cnt_record = 3;
            water_feedback_data.plant_cnt = 24;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (water_recv_data.region)
        {
        case A:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
        case B:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;
                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            // if (water_feedback_data.water_finish_state == water_finish_flag && water_recv_data.water_flag == none_water_flag)
            // {
            //     water_feedback_data.plant_cnt++;
            // }
            break;
        case C:
        case D:
            if ((water_recv_data.water_flag & left_water_flag) && !(water_feedback_data.water_finish_state & left_water_flag))
            {
                // 左边浇水过程
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= left_water_flag;
                    water_feedback_data.plant_cnt++;

                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            else if ((water_recv_data.water_flag & right_water_flag) && !(water_feedback_data.water_finish_state & right_water_flag))
            {
                // 右边浇水
                if (++cnt % 2000 == 0)
                {
                    cnt = 0;
                    water_feedback_data.water_finish_state |= right_water_flag;
                    water_feedback_data.plant_cnt++;

                    // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
                }
            }
            break;
        }
    }
}

void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    water_flag_handle();

    PubPushMessage(water_pub, (void *)&water_feedback_data);
}