#include "gray.h"

static uint8_t gray_cnt = 0;
void get_gray_cnt(void)
{
    int i = 0;
    if (OUT0 == 0)
    {
        i++;
    }
    if (OUT1 == 0)
    {
        i++;
    }
    if (OUT2 == 0)
    {
        i++;
    }
    if (OUT3 == 0)
    {
        i++;
    }
    if (OUT4 == 0)
    {
        i++;
    }
    if (OUT5 == 0)
    {
        i++;
    }
    if (OUT6 == 0)
    {
        i++;
    }
    if (OUT7 == 0) // 1 -> 0
    {
        i++;
    }
    if (OUT8 == 0)
    {
        i++;
    }
    if (OUT9 == 0)
    {
        i++;
    }
    if (OUT10 == 0)
    {
        i++;
    }
    if (OUT11 == 0)
    {
        i++;
    }
    if (OUT12 == 0)
    {
        i++;
    }
    if (OUT13 == 0)
    {
        i++;
    }
    gray_cnt = i;
    return;
}

uint8_t *Gray_Init(void)
{
    return &gray_cnt;
}
// int cross_cnt = 0;
// put to application
// this function should followed by next operation, IT CAN NOT BE CALLED MULTIPLE TIMES!!!
// int get_cross_flag(void)
// {
//     if ((OUT0 || OUT1 || OUT2 || OUT3 || OUT4 || OUT5 || OUT6 || OUT7 || OUT8 || OUT9 || OUT10 || OUT11 || OUT12 || OUT13))
//     {
//         if (get_gray_cnt() > GRAY_THRESHOLD)
//         {
//             cross_cnt++;
//             // if (cross_cnt == 2 || cross_cnt == 4 || cross_cnt == 6)
//             // {
//             // 	clockwise_rotate_flag += ((cross_cnt == 4) ? -1 : 1);
//             // }
//             // else if (cross_cnt == 1 || cross_cnt == 3 || cross_cnt == 5)
//             // {
//             // 	clockwise_rotate_flag += ((cross_cnt == 3) ? -1 : 1);
//             // }
//             if (cross_cnt == 1 || cross_cnt == 2 || cross_cnt == 5 || cross_cnt == 6)
//             {
//                 clockwise_rotate_flag += 1;
//             }
//             else if (cross_cnt == 3 || cross_cnt == 4)
//             {
//                 clockwise_rotate_flag -= 1;
//             }
//             return 1;
//         }
//     }
//     return 0;
// }
