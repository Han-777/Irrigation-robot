#include "key.h"
#include "delay.h" 
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
void PF2_IN_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    // ʹ��GPIOD��ʱ��
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;        
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;       // ����
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;  // ����
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

}
void PF0_IN_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    // ʹ��GPIOD��ʱ��
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;        
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;       // ����
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;  // ����
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

}

void PB15_IN_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
 
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_15;        
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;       // ����
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;  // ����
    GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void PD14_OUT_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
 
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

		GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
		LL_GPIO_Init(GPIOD, &GPIO_InitStruct); 
	
}
void PD9_OUT_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
 
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

		GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
		LL_GPIO_Init(GPIOD, &GPIO_InitStruct); 
	
}
void PF4_OUT_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
 
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);

		GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
		LL_GPIO_Init(GPIOF, &GPIO_InitStruct); 
	
}



void KEY_Init(void)
{
	
	PF2_IN_Init();
  PF0_IN_Init();
	PB15_IN_Init();
	PD14_OUT_Init();
	PD9_OUT_Init();
	PF4_OUT_Init();
 
} 


/*****************************************************************************
 * @name       :u8 KEY_Scan(void)
 * @date       :2018-08-09 
 * @function   :Key processing,Response priority:KEY0>KEY1>WK_UP!!
 * @parameters :None
 * @retvalue   :0-No buttons were pressed.
								1-The KEY0 button is pressed
								2-The KEY1 button is pressed
								3-The KEY2 button is pressed
								4-The WK_UP button is pressed
******************************************************************************/ 
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)return 1;
//		else if(KEY1==0)return 2;
//		else if(KEY2==0)return 3;
//		else if(WK_UP==1)return 4;
//	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
// 	return 0;// �ް�������
//}

int flag_test=0;
int a1=-30;
float k1=0.70;
int count1=0;
int flag_tc=0;//�����˵�ҳ����־λ
long int speed1,speed2;//1�ҵ��  2����
int start1=0,start2=0;
int frame1,count0;//֡�������֡�ʵļ���ֵ
long int distance;//����������ľ��룬��isr.c��ʱ���ж��м���
long int time;//��������ʱ�����ֵ����isr.c��ʱ���ж��м���
long int speed_define=20000;
int point=0;
int flag_lx,flag_sc;
int key_scan1(void)
{

    if(read_key1)return 1;
    if(read_key2)return 2;
    if(read_key3)return 3;
//    if(read_key4)return 4;
    return 0;
}
void key_init_1(void)
{
    y0h0_nc;
    y0h1_nc;
    y0h2_nc;
    y0h3_nc;
    y0h4_nc;
    y0h5_nc;
    y0h6_nc;
    y0h7_nc;
}


int key_scan2(void)
{
    int i=0;
    set_key1;
    reset_key2;
    reset_key3;
//    reset_key4;//1000
    i=key_scan1();
    switch(i)
    {
        case 1: return 1;//sw1
        case 2: return 2;//sw5
        case 3: return 3;//sw9
//        case 4: return 4;//sw13
        default:break;
    }
    reset_key1;
    set_key2;//0100
    i=key_scan1();
    switch(i)
    {
        case 1: return 5;//sw5
        case 2: return 6;
        case 3: return 7;
//        case 4: return 8;//sw8
        default:break;
    }
    reset_key2;
    set_key3;//0010
    i=key_scan1();
    switch(i)
    {
        case 1: return 9;
        case 2: return 10;
        case 3: return 11;
//        case 4: return 12;
        default:break;
    }
//    reset_key3;
//    set_key4;//0001
//    i=key_scan1();
//    switch(i)
//    {
//        case 1: return 13;
//        case 2: return 14;
//        case 3: return 15;
////        case 4: return 16;
//        default:break;
//    }
return 0;
}


int key_scan3(int i)
{
    switch(i)
    {
        case 0:return 0;
        case 1:{flag_tc--;break;}//��һҳ
        case 2:{if(point>0)point-=16;else point=0;break;}//��
        case 3:{flag_tc++;break;}//��һҳ
        case 4:{speed_define-=1000;break;}
        case 6:{ time=0 ;break;}
        case 8:{speed_define+=1000;break;}
        case 10:{if(point<112)point+=16;else point=112;break;}//��
        case 14:{flag_test=2;flag_lx=0;break;}//hd_time[0]=flag_test;
        case 15:{start2=1;break;}//����ʱ����ִ�а���ɨ�裬δ��������ʱ�رհ���ɨ��
        case 13://֡����ʾ
        {
            
            break;
        }
        default://���ҽ��б�������
        {
            switch (flag_tc)
            {
                case 0://��0ҳ
                {
                    if(i==11)     //��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y0h0_cut;break;}
                            case 16:{opr_y0h1_cut;break;}
                            case 32:{opr_y0h2_cut;break;}
                            case 48:{opr_y0h3_cut;break;}
                            case 64:{opr_y0h4_cut;break;}
                            case 80:{opr_y0h5_cut;break;}
                            case 96:{opr_y0h6_cut;break;}
                            case 112:{opr_y0h7_cut;break;}
                        }
                    }

                    if(i==9)  // ��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y0h0_add;break;}
                            case 16:{opr_y0h1_add;break;}
                            case 32:{opr_y0h2_add;break;}
                            case 48:{opr_y0h3_add;break;}
                            case 64:{opr_y0h4_add;break;}
                            case 80:{opr_y0h5_add;break;}
                            case 96:{opr_y0h6_add;break;}
                            case 112:{opr_y0h7_add;break;}
                        }
                    }
                    break;
                }
                case -1://-1ҳ
                {
                     if(i==11)     //��
                     {
                         switch (point)//��point��
                         {
                           case 0:{opr_yf1h0_cut;break;}
                           case 16:{opr_yf1h1_cut;break;}
                           case 32:{opr_yf1h2_cut;break;}
                           case 48:{opr_yf1h3_cut;break;}
                           case 64:{opr_yf1h4_cut;break;}
                           case 80:{opr_yf1h5_cut;break;}
                           case 96:{opr_yf1h6_cut;break;}
                           case 112:{opr_yf1h7_cut;break;}
                         }
                     }

                     if(i==9)  // ��
                     {
                         switch (point)//��point��
                         {
                             case 0:{opr_yf1h0_add;break;}
                             case 16:{opr_yf1h1_add;break;}
                             case 32:{opr_yf1h2_add;break;}
                             case 48:{opr_yf1h3_add;break;}
                             case 64:{opr_yf1h4_add;break;}
                             case 80:{opr_yf1h5_add;break;}
                             case 96:{opr_yf1h6_add;break;}
                             case 112:{opr_yf1h7_add;break;}
                         }
                     }
                     break;
                }
                case -2://-2ҳ
                {
                    if(i==11)     //��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_yf2h0_cut;break;}
                            case 16:{opr_yf2h1_cut;break;}
                            case 32:{opr_yf2h2_cut;break;}
                            case 48:{opr_yf2h3_cut;break;}
                            case 64:{opr_yf2h4_cut;break;}
                            case 80:{opr_yf2h5_cut;break;}
                            case 96:{opr_yf2h6_cut;break;}
                            case 112:{opr_yf2h7_cut;break;}
                        }
                    }

                    if(i==9)  // ��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_yf2h0_add;break;}
                            case 16:{opr_yf2h1_add;break;}
                            case 32:{opr_yf2h2_add;break;}
                            case 48:{opr_yf2h3_add;break;}
                            case 64:{opr_yf2h4_add;break;}
                            case 80:{opr_yf2h5_add;break;}
                            case 96:{opr_yf2h6_add;break;}
                            case 112:{opr_yf2h7_add;break;}
                        }
                    }
                    break;
                }
                case 1://-2ҳ
                {
                    if(i==11)     //��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y1h0_cut;break;}
                            case 16:{opr_y1h1_cut;break;}
                            case 32:{opr_y1h2_cut;break;}
                            case 48:{opr_y1h3_cut;break;}
                            case 64:{opr_y1h4_cut;break;}
                            case 80:{opr_y1h5_cut;break;}
                            case 96:{opr_y1h6_cut;break;}
                            case 112:{opr_y1h7_cut;break;}
                        }
                    }

                    if(i==9)  // ��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y1h0_add;break;}
                            case 16:{opr_y1h1_add;break;}
                            case 32:{opr_y1h2_add;break;}
                            case 48:{opr_y1h3_add;break;}
                            case 64:{opr_y1h4_add;break;}
                            case 80:{opr_y1h5_add;break;}
                            case 96:{opr_y1h6_add;break;}
                            case 112:{opr_y1h7_add;break;}
                        }
                    }
                    break;
                }
                case 2://2ҳ
                {
                    if(i==11)     //��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y2h0_cut;break;}
                            case 16:{opr_y2h1_cut;break;}
                            case 32:{opr_y2h2_cut;break;}
                            case 48:{opr_y2h3_cut;break;}
                            case 64:{opr_y2h4_cut;break;}
                            case 80:{opr_y2h5_cut;break;}
                            case 96:{opr_y2h6_cut;break;}
                            case 112:{opr_y2h7_cut;break;}
                        }
                    }

                    if(i==9)  // ��
                    {
                        switch (point)//��point��
                        {
                            case 0:{opr_y2h0_add;break;}
                            case 16:{opr_y2h1_add;break;}
                            case 32:{opr_y2h2_add;break;}
                            case 48:{opr_y2h3_add;break;}
                            case 64:{opr_y2h4_add;break;}
                            case 80:{opr_y2h5_add;break;}
                            case 96:{opr_y2h6_add;break;}
                            case 112:{opr_y2h7_add;break;}
                        }
                    }
                    break;
                }
            }
        }
    }
    if(i!=13)
    {
        switch(flag_tc)
        {
            case -2://-2ҳ
            {
                LCD_Clear(WHITE);
                LCD_ShowString(0, point,100,16,16, "-");
                yf2h0_nc;
                yf2h1_nc;
                yf2h2_nc;
                yf2h3_nc;
                yf2h4_nc;
                yf2h5_nc;
                yf2h6_nc;
                yf2h7_nc;
                break;
            }
            case -1://-1ҳ
            {
                LCD_Clear(WHITE);
                LCD_ShowString(0, point,100,16,16, "-");
                yf1h0_nc;
                yf1h1_nc;
                yf1h2_nc;
                yf1h3_nc;
                yf1h4_nc;
                yf1h5_nc;
                yf1h6_nc;
                yf1h7_nc;
                break;
            }
            case 0://0ҳ
            {
                LCD_Clear(WHITE);
                LCD_ShowString(0, point,100,16,16, "-");
                y0h0_nc;
                y0h1_nc;
                y0h2_nc;
                y0h3_nc;
                y0h4_nc;
                y0h5_nc;
                y0h6_nc;
                y0h7_nc;
                break;
            }
            case 1://1ҳ
            {
                LCD_Clear(WHITE);
                LCD_ShowString(0, point,100,16,16,"-");
                y1h0_nc;
                y1h1_nc;
                y1h2_nc;
                y1h3_nc;
                y1h4_nc;
                y1h5_nc;
                y1h6_nc;
                y1h7_nc;
                break;
            }
            case 2://2ҳ
            {
                LCD_Clear(WHITE);
                LCD_ShowString(0, point,100,16,16, "-");
                y2h0_nc;
                y2h1_nc;
                y2h2_nc;
                y2h3_nc;
                y2h4_nc;
                y2h5_nc;
                y2h6_nc;
                y2h7_nc;
                break;
            }
            default:
            {
                 LCD_Clear(WHITE);
            }
        }
    }
    return 1;
}
void lcd_show(void)
{
    static int flag1=0;
   
    int i=key_scan2();
   
   
    if((flag1==0)&&i)
    {
        flag1=1;
        key_scan3(i);
    }
    else flag1=i;
    //����Ϊ����ɨ�貿��

    //����Ϊlcd��ʾ��������
    if(flag_tc==-2)
    {
        yf2h0_c;
        yf2h1_c;
        yf2h2_c;
        yf2h3_c;
        yf2h4_c;
        yf2h5_c;
        yf2h6_c;
        yf2h7_c;

    }
    else if(flag_tc==-1)
    {
        yf1h0_c;
        yf1h1_c;
        yf1h2_c;
        yf1h3_c;
        yf1h4_c;
        yf1h5_c;
        yf1h6_c;
        yf1h7_c;

    }
    else if(flag_tc==0)
    {
        y0h0_c;
        y0h1_c;
        y0h2_c;
        y0h3_c;
        y0h4_c;
        y0h5_c;
        y0h6_c;
        y0h7_c;

    }
    else if(flag_tc==1)
    {
        y1h0_c;
        y1h1_c;
        y1h2_c;
        y1h3_c;
        y1h4_c;
        y1h5_c;
        y1h6_c;
        y1h7_c;

    }
    else if(flag_tc==2)
    {
        y2h0_c;
        y2h1_c;
        y2h2_c;
        y2h3_c;
        y2h4_c;
        y2h5_c;
        y2h6_c;
        y2h7_c;

    }
    else if(flag_tc==3||flag_tc==4)
    {
        if(flag_tc==4){
            
        }

      //  tft180_displayimage03x((const uint8 *)*PerImg_ip, 70, 80);
//       tft180_displayimage03x((const uint8 *)mt9v03x_image_2, 160, 120);

        if(flag_tc==3)
        {
           
//            showline();
        }
//        if(flag_tc==4) tft180_show_gray_image(0, 0, (mt9v03x_image_2), 188, 120,160, 120,th);

        //zhongxianxianshi();
       // lcd_displayimage032(mt9v03x_image[0], 188, 120);
//        lcd_showint8(0, 7, flag_hd);
//        lcd_showint8(32, 7, flag_sc);
//        lcd_showint8(64,7,flag_sz1);
//        lcd_showint8(96,7,flag_zebra);
//        lcd_showint16(96,6,out);
//        lcd_showint8(0,6,flag_status);
//        lcd_showint16(96,5,flag_status);
//        lcd_showint16(0,5,yaw);
//        lcd_showint16(0,4,roll);
//        lcd_showint16(96,4,dif_roll);
    }
 //   IMU_quaterToEulerianAngles();
    //lcd_showint16(0,0,(int)(100*pitch));
   //lcd_showint16(0,1,(int)(yaw));
   // lcd_showint16(0,2,(int)(100*roll));

}




















//������ʼ������
//void KEY_Init(void)
//{

//	GPIO_InitTypeDef  GPIO_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //KEY0 ��Ӧ����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4
//	 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
// 
//} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==1||WK_UP==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==1)return KEY0_PRES;
//		else if(WK_UP==1)return WKUP_PRES;
//	}else if(KEY0==0&&WK_UP==0)key_up=1; 	    
// 	return 0;// �ް�������
//}
