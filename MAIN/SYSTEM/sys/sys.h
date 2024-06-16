#ifndef __SYS_H
#define __SYS_H
#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ALIENTEK STM32F407������
// ϵͳʱ�ӳ�ʼ��
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// ��������:2014/5/2
// �汾��V1.0
// ��Ȩ���У�����ؾ���
// Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
// All rights reserved
//********************************************************************************
// �޸�˵��
// ��
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

// extern int set;//������ֹת��֮�����
// extern int R_r;//�����ж��������������Ƿ�Ҫ��ˮ
// extern int L_l;//�����ж��������������Ƿ�Ҫ��ˮ����
// extern int Flag_L;//�����ж���������󼤹���Ժ�����̧�Ƕ�
// extern int Flag_R;
// extern int FLAG;

// extern int TURN_LEFT;
// extern int TURN_RIGHT;
// extern int SET_TURN;

// extern	u8 drought_buff[40];
// extern int jishu;

// extern int Err_Count;//��¼ɨ�����
// extern int Line_Count;
// extern float KP;
// extern float KI;
// extern float KD;

// 0,��֧��ucos
// 1,֧��ucos
// JTAGģʽ���ö���
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
#define IMU_LEN 0x38    // 56+8  8������
#define AHRS_LEN 0x30   // 48+8  7������
#define INSGPS_LEN 0x42 // 72+8  10������
#define IMU_CAN 9
#define AHRS_CAN 8
#define INSGPS_CAN 11
// RS-485
#define RS485_RX_DE PAout(11) // 485ģʽ����.0,����;1,����.
#define RS485_RX_RE PAout(12) // 485ģʽ����.0,����;1,����.
#define SYSTEM_SUPPORT_OS 0   // ����ϵͳ�ļ����Ƿ�֧��UCOS

// λ������,ʵ��51���Ƶ�GPIO���ƹ���
// ����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
// IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
// IO�ڵ�ַӳ��
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

// IO�ڲ���,ֻ�Ե�һ��IO��!
// ȷ��n��ֵС��16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) // ���
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  // ����

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) // ���
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  // ����

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) // ���
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  // ����

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) // ���
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  // ����

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) // ���
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  // ����

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) // ���
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // ����

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) // ���
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  // ����

#define PHout(n) BIT_ADDR(GPIOH_ODR_Addr, n) // ���
#define PHin(n) BIT_ADDR(GPIOH_IDR_Addr, n)  // ����

#define PIout(n) BIT_ADDR(GPIOI_ODR_Addr, n) // ���
#define PIin(n) BIT_ADDR(GPIOI_IDR_Addr, n)  // ����

// ����Ϊ��ຯ��
void WFI_SET(void);      // ִ��WFIָ��
void INTX_DISABLE(void); // �ر������ж�
void INTX_ENABLE(void);  // ���������ж�
void MSR_MSP(u32 addr);  // ���ö�ջ��ַ
#endif
