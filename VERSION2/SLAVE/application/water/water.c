#include "water.h"
#include "robot_def.h"
#include "message_center.h"

/*================message center============*/
static Publisher_t *water_pub;
static Subscriber_t *water_sub;
static Water_Ctrl_Cmd_s water_recv_data;
static Water_Upload_Data_s water_feedback_data;

void WaterInit(void)
{

    /*-----------------------message center-------------------------*/
    water_sub = SubRegister("water_cmd", sizeof(Water_Ctrl_Cmd_s));
    water_pub = PubRegister("water_feed", sizeof(Water_Upload_Data_s));
}

void WaterTask(void)
{
    SubGetMessage(water_sub, (void *)&water_recv_data);
    // LCD_hanqing(GENERAL, 1);
    // LCD_hanqing(SLIGHT, 8);
    // LCD_hanqing(SERIOUS, 17);
    static uint16_t cnt = 0;
    // if (++cnt % 1000)
    // {
    //     cnt = 0;
    //     MP3_broadcast(GENERAL);
    // }

    PubPushMessage(water_pub, (void *)&water_feedback_data);
}