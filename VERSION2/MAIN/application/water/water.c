#include "mp3.h"
#include "water.h"
#include "message_center.h"
#include "servo_motor.h"
#include "photoelectric.h"
#include "robot_def.h"
#include "servo_motor.h"

#ifdef ONE_BOARD
static Publisher_t *water_pub;
static Subscriber_t *water_sub;
#endif
static Water_Ctrl_Cmd_s *water_cmd_data;
static Water_Upload_Data_s *water_feedback_data;
void WaterInit(void)
{
    MP3_Init();
    // 舵机初始化
    // Servo_Init_Config_s *config = (Servo_Init_Config_s
    // ServoInit();
#ifdef ONE_BOARD
    water_sub = SubRegister("warer_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
#endif
}

void WaterTask(void)
{
#ifdef ONE_BOARD
    SubGetMessage(water_sub, (void *)water_cmd_data);
#endif
    static uint8_t test_cnt = 0;
    if (++test_cnt % 1000 == 0 && water_cmd_data->water_flag & left_water_finish && water_cmd_data->water_flag & right_water_finish)
    {
        water_feedback_data->water_finish_state |= none_water_flag;
        test_cnt = 0;
    }
#ifdef ONE_BOARD
    PubPushMessage(water_pub, (void *)water_feedback_data);
#endif
}