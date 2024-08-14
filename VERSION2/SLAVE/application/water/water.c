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
static uint8_t info_buff[18] = {1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3,
                                1, 2, 3, 1, 2, 3};
static uint8_t plant_Cnt_record = 0; // number of setting
void WaterInit(void)
{
    MP3_Init();
    // 舵机初始化
    // Servo_Init_Config_s *config = (Servo_Init_Config_s
    // ServoInit();
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

void water_flag_handle(void)
{
    static uint8_t cnt = 0;
    if (water_feedback_data.water_finish_state != water_finish_flag)
    {
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
                // MP3_broadcast(info_buff[water_feedback_data.plant_cnt]);
            }
        }
        if (water_feedback_data.water_finish_state == water_finish_flag)
        {
            water_feedback_data.plant_cnt++;
        }
    }
    else
    {
        if (water_recv_data.water_flag == none_water_flag)
        {
            water_feedback_data.water_finish_state = none_water_flag;
            switch (plant_Cnt_record)
            {
            case 0:
                if (water_recv_data.set_plantCnt_flag == 6)
                {
                    plant_Cnt_record = 1;
                    water_feedback_data.plant_cnt = 6;
                }
                break;
            case 1:
                if (water_recv_data.set_plantCnt_flag == 12)
                {
                    plant_Cnt_record = 2;
                    water_feedback_data.plant_cnt = 12;
                }
                break;
            case 2:
                if (water_recv_data.set_plantCnt_flag == 18)
                {
                    plant_Cnt_record = 3;
                    water_feedback_data.plant_cnt = 18;
                }
                break;
            default:
                break;
            }
        }
    }
}

void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    water_flag_handle();
    // if (water_feedback_data->water_finish_state == water_finish_flag)
    // {
    //     water_flag_handle();
    // }
    // else
    // {
    // }
    // static uint8_t test_cnt = 0;
    // if (++test_cnt % 1000 == 0 && water_recv_data->water_flag & left_water_finish && water_recv_data->water_flag & right_water_finish)
    // {
    //     water_feedback_data->water_finish_state &= none_water_flag;
    //     water_feedback_data->plant_cnt++;
    //     test_cnt = 0;
    // }

    PubPushMessage(water_pub, (void *)&water_feedback_data);
}