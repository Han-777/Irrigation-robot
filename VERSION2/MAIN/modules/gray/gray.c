#include "gray.h"
#include <string.h>
// uint8_t get_gray(void)
// {
//     int gray_cnt = 0;
//     if (OUT0 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT1 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT2 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT3 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT4 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT5 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT6 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT7 == 0) // 1 -> 0
//     {
//         gray_cnt++;
//     }
//     if (OUT8 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT9 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT10 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT11 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT12 == 0)
//     {
//         gray_cnt++;
//     }
//     if (OUT13 == 0)
//     {
//         gray_cnt++;
//     }
//     if (gray_cnt > GRAY_THRESHOLD)
//     {
//         return 1;
//     }
//     return 0;
// }
#include "gray.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

#define times 2
uint8_t gray_Cnt = 0;
static uint8_t left_gray_cnt[times] = {0};
static uint8_t right_gray_cnt[times] = {0};
uint8_t get_gray(void)
{
    uint8_t gray_cnt = 0;
    for (uint8_t i = 0; i < times; ++i)
    {
        if (OUT0 == 0)
        {
            left_gray_cnt[i] |= 0b00000001;
        }
        if (OUT1 == 0)
        {
            left_gray_cnt[i] |= 0b00000010;
        }
        if (OUT2 == 0)
        {
            left_gray_cnt[i] |= 0b00000100;
        }
        if (OUT3 == 0)
        {
            left_gray_cnt[i] |= 0b00001000;
        }
        if (OUT4 == 0)
        {
            left_gray_cnt[i] |= 0b00010000;
        }
        if (OUT5 == 0)
        {
            left_gray_cnt[i] |= 0b00100000;
        }
        if (OUT6 == 0)
        {
            left_gray_cnt[i] |= 0b01000000;
        }
        if (OUT7 == 0) // 1 -> 0
        {
            right_gray_cnt[i] |= 0b00000001;
        }
        if (OUT8 == 0)
        {
            right_gray_cnt[i] |= 0b00000010;
        }
        if (OUT9 == 0)
        {
            right_gray_cnt[i] |= 0b00000100;
        }
        if (OUT10 == 0)
        {
            right_gray_cnt[i] |= 0b00001000;
        }
        if (OUT11 == 0)
        {
            right_gray_cnt[i] |= 0b00010000;
        }
        if (OUT12 == 0)
        {
            right_gray_cnt[i] |= 0b00100000;
        }
        if (OUT13 == 0)
        {
            right_gray_cnt[i] |= 0b01000000;
        }
        // osDelay(1);
    }
    for (uint8_t j = 0; j < 7; ++j)
    {
        if (left_gray_cnt[0] >> j & 0b00000001 && left_gray_cnt[1] >> j & 0b00000001)
        {
            gray_cnt++;
        }
        if (right_gray_cnt[0] >> j & 0b00000001 && right_gray_cnt[1] >> j & 0b00000001)
        {
            gray_cnt++;
        }
    }
    memset(left_gray_cnt, 0, sizeof(left_gray_cnt));
    memset(right_gray_cnt, 0, sizeof(right_gray_cnt));
    return gray_cnt;
}
