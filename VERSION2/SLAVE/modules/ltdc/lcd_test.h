#ifndef __LCD_TEST_H
#define __LCD_TEST_H

#include "stm32h7xx_hal.h"
#include "lcd_rgb.h"
#include "lcd_image.h"
#include "robot_def.h"

void LCD_Test_Clear(void);       // ��������
void LCD_Test_Text(void);        //	�ı���ʾ����
void LCD_Test_Variable(void);    // ������ʾ������������С��
void LCD_Test_Color(void);       // ��ɫ����
void LCD_Test_GrahicTest(void);  // 2Dͼ�λ���
void LCD_Test_FillRect(void);    // ����������
void LCD_Test_Image(void);       // ͼƬ��ʾ����
void LCD_Test_Vertical(void);    // ��ֱ��ʾ����
void LCD_Test_DoubleLayer(void); // ˫����ʾ
void Qinwei(int flower);
void Yiban(int flower);
void Yanzhong(int flower);
void LCD_hanqing(uint8_t drought_info, uint8_t flower_Cnt);
void LCD_Display_One(Drought_Info_e drought_info, uint8_t flower_Cnt);
void LCD_Display_All(Drought_Info_e *drought_info_buff);
void screenTask();
#endif //__LCD_TEST_H
