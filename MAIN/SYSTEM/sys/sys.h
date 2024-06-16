#ifndef __SYS_H
#define __SYS_H
#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// ALIENTEK STM32F407开发板
// 系统时钟初始化
// 正点原子@ALIENTEK
// 技术论坛:www.openedv.com
// 创建日期:2014/5/2
// 版本：V1.0
// 版权所有，盗版必究。
// Copyright(C) 广州市星翼电子科技有限公司 2014-2024
// All rights reserved
//********************************************************************************
// 修改说明
// 无
//////////////////////////////////////////////////////////////////////////////////

#include "delay.h"
#include "tim.h"
#include "gpio.h"
#include "iic.h"
#include "usart.h"
#include "math.h"
// #include "led.h"
// #include "delay.h"
// #include "timer.h"
// #include "exti.h"
// #include "guandian.h"
// #include "control.h"
// #include "encoder.h"
// #include "lcd.h"
// #include "key.h"
// #include "line.h"
// #include "openmv.h"
// #include "mp3.h"
// #include "motor.h"
// #include "InfCollect.h"
// #include "usartx.h"
// #include "serove.h"
// #include  "math.h"
// extern float ROLL;

// extern int F;
// extern int k;
// extern int Flower_Count;
// extern u8 color ;
// extern int PWM_L;
// extern int PWM_R;
// extern float Target_Yaw;
// extern float NEW_Target_Yaw;
// extern float target_Yaw;
// extern int N_Flag;
// extern float Err_Yaw;
// extern float New_Yaw;

// extern float Err_Set;

// extern uint16_t Dist_left;
// extern uint16_t Dist_right;
// extern uint16_t Distance_left_max;
// extern uint16_t Distance_left_min;
// extern uint16_t Distance_right_max;
// extern uint16_t Distance_right_min;

// extern int set;//用来防止转弯之后过冲
// extern int R_r;//用来判断在主函数里面是否要浇水
// extern int L_l;//用来判断在主函数里面是否要浇水，左
// extern int Flag_L;//用来判断是左边算左激光测试后舵机所抬角度
// extern int Flag_R;
// extern int FLAG;

// extern int TURN_LEFT;
// extern int TURN_RIGHT;
// extern int SET_TURN;

// extern	u8 drought_buff[40];
// extern int jishu;

// extern int Err_Count;//记录扫描次数
// extern int Line_Count;
// extern float KP;
// extern float KI;
// extern float KD;

// 0,不支持ucos
// 1,支持ucos
// JTAG模式设置定义
#define JTAG_SWD_DISABLE 0X02
#define SWD_ENABLE 0X01
#define JTAG_SWD_ENABLE 0X00
#define PRESCALER 14
#define ZHONGZHI -1
// FDlink candata
#define FRAME_HEAD 0xfc
#define FRAME_END 0xfd
#define TYPE_IMU 0x40
#define TYPE_AHRS 0x41
#define TYPE_INSGPS 0x42
#define TYPE_GROUND 0xf0
#define IMU_LEN 0x38    // 56+8  8组数据
#define AHRS_LEN 0x30   // 48+8  7组数据
#define INSGPS_LEN 0x42 // 72+8  10组数据
#define IMU_CAN 9
#define AHRS_CAN 8
#define INSGPS_CAN 11
// RS-485
#define RS485_RX_DE PAout(11) // 485模式控制.0,接收;1,发送.
#define RS485_RX_RE PAout(12) // 485模式控制.0,接收;1,发送.
#define SYSTEM_SUPPORT_OS 0   // 定义系统文件夹是否支持UCOS

// 位带操作,实现51类似的GPIO控制功能
// 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
// IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 20) // 0x40020014
#define GPIOB_ODR_Addr (GPIOB_BASE + 20) // 0x40020414
#define GPIOC_ODR_Addr (GPIOC_BASE + 20) // 0x40020814
#define GPIOD_ODR_Addr (GPIOD_BASE + 20) // 0x40020C14
#define GPIOE_ODR_Addr (GPIOE_BASE + 20) // 0x40021014
#define GPIOF_ODR_Addr (GPIOF_BASE + 20) // 0x40021414
#define GPIOG_ODR_Addr (GPIOG_BASE + 20) // 0x40021814
#define GPIOH_ODR_Addr (GPIOH_BASE + 20) // 0x40021C14
#define GPIOI_ODR_Addr (GPIOI_BASE + 20) // 0x40022014

#define GPIOA_IDR_Addr (GPIOA_BASE + 16) // 0x40020010
#define GPIOB_IDR_Addr (GPIOB_BASE + 16) // 0x40020410
#define GPIOC_IDR_Addr (GPIOC_BASE + 16) // 0x40020810
#define GPIOD_IDR_Addr (GPIOD_BASE + 16) // 0x40020C10
#define GPIOE_IDR_Addr (GPIOE_BASE + 16) // 0x40021010
#define GPIOF_IDR_Addr (GPIOF_BASE + 16) // 0x40021410
#define GPIOG_IDR_Addr (GPIOG_BASE + 16) // 0x40021810
#define GPIOH_IDR_Addr (GPIOH_BASE + 16) // 0x40021C10
#define GPIOI_IDR_Addr (GPIOI_BASE + 16) // 0x40022010

// IO口操作,只对单一的IO口!
// 确保n的值小于16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) // 输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  // 输入

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) // 输出
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  // 输入

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) // 输出
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  // 输入

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) // 输出
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  // 输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) // 输出
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  // 输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) // 输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // 输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) // 输出
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  // 输入

#define PHout(n) BIT_ADDR(GPIOH_ODR_Addr, n) // 输出
#define PHin(n) BIT_ADDR(GPIOH_IDR_Addr, n)  // 输入

#define PIout(n) BIT_ADDR(GPIOI_ODR_Addr, n) // 输出
#define PIin(n) BIT_ADDR(GPIOI_IDR_Addr, n)  // 输入

// 以下为汇编函数
void WFI_SET(void);      // 执行WFI指令
void INTX_DISABLE(void); // 关闭所有中断
void INTX_ENABLE(void);  // 开启所有中断
void MSR_MSP(u32 addr);  // 设置堆栈地址
#endif
