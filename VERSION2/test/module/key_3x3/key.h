#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define ls0(a)      LCD_ShowNum(80,0,a,5，16)
#define ls1(a)      LCD_ShowNum(80,16,a,5,16)
#define ls2(a)      LCD_ShowNum(80,32,a,5,16)
#define ls3(a)      LCD_ShowNum(80,48,a,5,16)
#define ls4(a)      LCD_ShowNum(80,64,a,5,16)
#define ls5(a)      LCD_ShowNum(80,80,a,5,16)
#define ls6(a)      LCD_ShowNum(80,96,a,5,16)
#define ls7(a)      LCD_ShowNum(80,112,a,5,16)


#define yf2h0_nc  LCD_ShowString(16, 0,100,16,16,"page-2")//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define yf2h1_nc  {LCD_ShowString(16, 16,100,16,16,"cross_flag");ls1(time);}
#define yf2h2_nc  {LCD_ShowString(16, 32,100,16,16,"ll_flag");ls2(time);}
#define yf2h3_nc  {LCD_ShowString(16, 48,100,16,16, "lr_flag");ls3(time);}
#define yf2h4_nc  {LCD_ShowString(16, 64,100,16,16, "rd_flag");ls4(time);}
#define yf2h5_nc  {LCD_ShowString(16, 80,100,16,16, "ld_flag");ls5(time);}
#define yf2h6_nc  {LCD_ShowString(16, 96,100,16,16, "lu_flag");ls6(time);}
#define yf2h7_nc  {LCD_ShowString(16, 112,100,16,16, "ru_flag");ls7(time);}

#define yf2h0_c  //页(ye)-1 高度（high）0  (实时刷新)(change)
#define yf2h1_c
#define yf2h2_c 
#define yf2h3_c  
#define yf2h4_c  
#define yf2h5_c  
#define yf2h6_c  
#define yf2h7_c  

#define opr_yf2h0_add   //按下按键时执行的操作 (oprate ye f2 high0)
#define opr_yf2h1_add
#define opr_yf2h2_add 
#define opr_yf2h3_add 
#define opr_yf2h4_add
#define opr_yf2h5_add 
#define opr_yf2h6_add 
#define opr_yf2h7_add

#define opr_yf2h0_cut time-=1000  //按下按键时执行的操作 (oprate ye f2 high0)
#define opr_yf2h1_cut
#define opr_yf2h2_cut 
#define opr_yf2h3_cut 
#define opr_yf2h4_cut
#define opr_yf2h5_cut 
#define opr_yf2h6_cut 
#define opr_yf2h7_cut


#define yf1h0_nc  LCD_ShowString(8, 0,100 ,16,16,"page-1")//页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define yf1h1_nc  {LCD_ShowString(16, 16,100,16,16,"3");ls1(time);}
#define yf1h2_nc  {LCD_ShowString(16, 32,100,16,16,"2");ls2(time);}
#define yf1h3_nc  {LCD_ShowString(16, 48,100,16,16, "1");ls3(time);}
#define yf1h4_nc  {LCD_ShowString(16, 64,100,16,16, "leftside");ls4(time);}
#define yf1h5_nc  {LCD_ShowString(16, 80,100,16,16, "rightside");ls5(time);}
#define yf1h6_nc  {LCD_ShowString(16, 96,100,16,16, "r.kd");ls6(time);}
#define yf1h7_nc  {LCD_ShowString(16, 112,100,16,16, "test1");ls7(time);}

#define yf1h0_c  //页(ye)-1 高度（high）0  (实时刷新)(no change)
#define yf1h1_c  
#define yf1h2_c  
#define yf1h3_c  
#define yf1h4_c  
#define yf1h5_c  
#define yf1h6_c
#define yf1h7_c  

#define opr_yf1h0_add time-=1000  //按下按键时执行的操作 (oprate ye fu1 high0)
#define opr_yf1h1_add
#define opr_yf1h2_add
#define opr_yf1h3_add
#define opr_yf1h4_add
#define opr_yf1h5_add  
#define opr_yf1h6_add  
#define opr_yf1h7_add  

#define opr_yf1h0_cut time-=1000  //按下按键时执行的操作 (oprate ye fu1 high0)
#define opr_yf1h1_cut
#define opr_yf1h2_cut
#define opr_yf1h3_cut
#define opr_yf1h4_cut
#define opr_yf1h5_cut 
#define opr_yf1h6_cut 
#define opr_yf1h7_cut 


#define y0h0_nc  LCD_ShowString(16, 0,100, 16, 16, "1")//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y0h1_nc  {LCD_ShowString(16, 16,100,16,16,"pitch1");ls1(time);}
#define y0h2_nc  {LCD_ShowString(16, 32,100,16,16,"yaw1");ls2(time);}
#define y0h3_nc  {LCD_ShowString(16, 48,100,16,16,"3.kp");ls3(time);}
#define y0h4_nc  {LCD_ShowString(16, 64,100,16,16,"3.ki");ls4(time);}
#define y0h5_nc  {LCD_ShowString(16, 80,100,16,16,"3.kd");ls5(time);}
#define y0h6_nc  {LCD_ShowString(16, 96,100,16,16,"roll_kal");ls6(time);}
#define y0h7_nc  {LCD_ShowString(16, 112,100,16,16,"yaw_kal");ls7(time);}

#define y0h0_c  //页(ye)-1 高度（high）0  (实时刷新)(change)
#define y0h1_c  
#define y0h2_c  
#define y0h3_c
#define y0h4_c
#define y0h5_c
#define y0h6_c  
#define y0h7_c  

#define opr_y0h0_add    //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y0h1_add //speed_define+=1000
#define opr_y0h2_add
#define opr_y0h3_add  
#define opr_y0h4_add   
#define opr_y0h5_add  
#define opr_y0h6_add
#define opr_y0h7_add

#define opr_y0h0_cut //time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y0h1_cut //speed_define-=1000
#define opr_y0h2_cut
#define opr_y0h3_cut  
#define opr_y0h4_cut  
#define opr_y0h5_cut  
#define opr_y0h6_cut
#define opr_y0h7_cut


#define y1h0_nc  LCD_ShowString(16, 0,100,16,16,"page1")//页（ye）1 高度（high）0  不变(即只是按下按键刷新(no change)
#define y1h1_nc  {LCD_ShowString(16, 16,100,16,16,"2.kp");ls1(time);}
#define y1h2_nc  {LCD_ShowString(16, 32,100,16,16,"2.ki");ls2(time);}
#define y1h3_nc  {LCD_ShowString(16, 48,100,16,16,"2.kd");ls3(time);}
#define y1h4_nc  {LCD_ShowString(16, 64,100,16,16,"1.kp");ls4(time);}
#define y1h5_nc  {LCD_ShowString(16, 80,100,16,16,"1.ki");ls5(time);}
#define y1h6_nc  {LCD_ShowString(16, 96,100,16,16,"1.kd");ls6(time);}
#define y1h7_nc  {LCD_ShowString(16, 112,100,16,16,"point");ls7(time);}

#define y1h0_c  //页(ye)-1 高度（high）0  (实时刷新)(change)
#define y1h1_c
#define y1h2_c
#define y1h3_c
#define y1h4_c
#define y1h5_c
#define y1h6_c
#define y1h7_c

#define opr_y1h0_add time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y1h1_add  
#define opr_y1h2_add  
#define opr_y1h3_add  
#define opr_y1h4_add  
#define opr_y1h5_add  
#define opr_y1h6_add  
#define opr_y1h7_add  

#define opr_y1h0_cut  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y1h1_cut  
#define opr_y1h2_cut  
#define opr_y1h3_cut  
#define opr_y1h4_cut  
#define opr_y1h5_cut  
#define opr_y1h6_cut 
#define opr_y1h7_cut  


#define y2h0_nc  LCD_ShowString(16, 0,100,16,16,"page2")//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y2h1_nc  LCD_ShowString(16, 16,100,16,16,"siqu_l");ls1(time);
#define y2h2_nc  LCD_ShowString(16, 32,100,16,16,"siqu_r");ls2(time);
#define y2h3_nc  LCD_ShowString(16, 48,100,16,16, "t.kp");ls3(time);
#define y2h4_nc  LCD_ShowString(16, 64,100,16,16, "t.ki");ls4(time);
#define y2h5_nc  LCD_ShowString(16, 80, 100,16,16,"t.kd");ls5(time);
#define y2h6_nc  LCD_ShowString(16, 96,100,16,16, "turn");ls6(time);
#define y2h7_nc  LCD_ShowString(16, 112,100,16,16, "fl_turn");ls7(time);

#define y2h0_c
#define y2h1_c
#define y2h2_c
#define y2h3_c
#define y2h4_c
#define y2h5_c
#define y2h6_c 
#define y2h7_c

#define opr_y2h0_add  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y2h1_add 
#define opr_y2h2_add 
#define opr_y2h3_add 
#define opr_y2h4_add 
#define opr_y2h5_add 
#define opr_y2h6_add
#define opr_y2h7_add 



#define opr_y2h0_cut 
#define opr_y2h1_cut 
#define opr_y2h2_cut 
#define opr_y2h3_cut 
#define opr_y2h4_cut 
#define opr_y2h5_cut 
#define opr_y2h6_cut
#define opr_y2h7_cut 


#define read_key1 LL_GPIO_IsInputPinSet(GPIOF, LL_GPIO_PIN_2)//读取按键io电平//列
#define read_key2 LL_GPIO_IsInputPinSet(GPIOF, LL_GPIO_PIN_0)
#define read_key3 LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_15)

//#define read_key4 gpio_get_level(P20_2)


#define set_key1 LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_14)//设置按键io电平为高//8
#define set_key2 LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_9)
#define set_key3 LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_4)
//#define set_key4 gpio_set_level(P23_1,1)//1

#define reset_key1 LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_14)//设置按键io电平为低
#define reset_key2 LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_9)
#define reset_key3 LL_GPIO_ResetOutputPin(GPIOF, LL_GPIO_PIN_4)
//#define reset_key4 gpio_set_level(P23_1,0)

int key_scan1(void);
int key_scan2(void);
int key_scan3(int i);
extern int flag_test;
extern int a1;
extern float k1;
extern long int time;//程序运行时间计数值，在isr.c定时器中断中计算
void lcd_show(void);
void key_init_1(void);
void KEY_Init(void);
void PF2_IN_Init(void);
void PF0_IN_Init(void);
void PB15_IN_Init(void);
void PD14_OUT_Init(void);
void PD9_OUT_Init(void);
void PF4_OUT_Init(void);














/*下面的方式是通过直接操作库函数方式读取IO*/
//#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
//#define WK_UP 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0
//#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
//#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2

///*下面方式是通过位带操作方式读取IO*/
///*
//#define KEY0 		PEin(4)   	//PE4
//#define KEY1 		PEin(3)		//PE3 
//#define KEY2 		PEin(2)		//P32
//#define WK_UP 	PAin(0)		//PA0
//*/


//#define KEY0_PRES 	1	//KEY0按下
//#define KEY1_PRES	2	//KEY1按下
//#define KEY2_PRES	3	//KEY2按下
//#define WKUP_PRES   4	//KEY_UP按下(即WK_UP)

//void KEY_Init(void);	//IO初始化
//u8 KEY_Scan(u8);  		//按键扫描函数	

#endif
