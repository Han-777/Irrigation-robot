#include "gray.h"

uint8_t get_gray_cnt(void)
{
    int gray_cnt = 0;
    if (OUT0 == 0)
    {
        gray_cnt++;
    }
    if (OUT1 == 0)
    {
        gray_cnt++;
    }
    if (OUT2 == 0)
    {
        gray_cnt++;
    }
    if (OUT3 == 0)
    {
        gray_cnt++;
    }
    if (OUT4 == 0)
    {
        gray_cnt++;
    }
    if (OUT5 == 0)
    {
        gray_cnt++;
    }
    if (OUT6 == 0)
    {
        gray_cnt++;
    }
    if (OUT7 == 0) // 1 -> 0
    {
        gray_cnt++;
    }
    if (OUT8 == 0)
    {
        gray_cnt++;
    }
    if (OUT9 == 0)
    {
        gray_cnt++;
    }
    if (OUT10 == 0)
    {
        gray_cnt++;
    }
    if (OUT11 == 0)
    {
        gray_cnt++;
    }
    if (OUT12 == 0)
    {
        gray_cnt++;
    }
    if (OUT13 == 0)
    {
        gray_cnt++;
    }
    return gray_cnt;
}
