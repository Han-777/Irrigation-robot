/***
	************************************************************************************************************************************************************************************************
	*************************************************************************************************
	*	@version V1.1
	*  @date    2024-6-19
	*	@author  ���ͿƼ�
   *************************************************************************************************
   *  @description
	*
	*	ʵ��ƽ̨������STM32H743XIH6���İ� ���ͺţ�FK743M5-XIH6��+ ����800*480�ֱ��ʵ�RGB��Ļ
	*	�Ա���ַ��https://shop212360197.taobao.com
	*	QQ����Ⱥ��536665479
	*
>>>>> V1.1 �汾���˵����2024-6-19����
	*
	*	ɾ�������ļ��ĳ�ʼ�����ã�����ԭ��cubeMX�����ã�����ͻ���ֲ��ʹ��
	*
>>>>> ��Ҫ˵����
	*
	*	1. ʹ�õ����ⲿSDRAM��Ϊ�Դ棬��ʼ��ַ0xC0000000
	*	2. �ڸ����������ʱ����Ļ����΢��������˸�����������󣬵ȴ�Ƭ�̻��������ϵ缴�ɻָ�����
	* 	3. LTDCʱ���� main.c �ļ���� SystemClock_Config()�������ã�����Ϊ33MHz����ˢ������60֡���ң����߻��߹��Ͷ��������˸
	*
>>>>> ����˵����
	*
	*	1. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ���û����Ը�����������������ɾ��
	*	2. ���������Ĺ��ܺ�ʹ�ÿ��Բο�������˵���Լ� lcd_test.c �ļ���Ĳ��Ժ���
	*
	*********************************************************************************************************************************************************************************************FANKE*****
***/

#include "lcd_rgb.h"

extern DMA2D_HandleTypeDef hdma2d; // DMA2D���
extern LTDC_HandleTypeDef hltdc;   // LTDC���

static pFONT *LCD_Fonts;   // Ӣ������
static pFONT *LCD_CHFonts; // ��������

// LCD��ز����ṹ��
struct
{
	uint32_t Color;			 //	LCD��ǰ������ɫ
	uint32_t BackColor;		 //	����ɫ
	uint32_t ColorMode;		 // ��ɫ��ʽ
	uint32_t LayerMemoryAdd; //	���Դ��ַ
	uint8_t Layer;			 //	��ǰ��
	uint8_t Direction;		 //	��ʾ����
	uint8_t BytesPerPixel;	 // ÿ��������ռ�ֽ���
	uint8_t ShowNum_Mode;	 // ������ʾģʽ
} LCD;

/*************************************************************************************************
*	�� �� ��:	LCD_GPIO_Init

*	��������:	��ʼ��LTDC���ŵı�������

*************************************************************************************************/

void LCD_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_LDC_Backlight_CLK_ENABLE; // ʹ�ܱ�������IO��ʱ��

	// ��ʼ����������

	GPIO_InitStruct.Pin = LCD_Backlight_PIN;			 // ��������
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;			 // �������ģʽ
	GPIO_InitStruct.Pull = GPIO_NOPULL;					 // ��������
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;		 // �ٶȵȼ���
	HAL_GPIO_Init(LCD_Backlight_PORT, &GPIO_InitStruct); // ��ʼ��

	LCD_Backlight_OFF; // �ȹرձ������ţ���ʼ��LTDC֮���ٿ���
}

/*************************************************************************************************
*	�� �� ��:	LCD_RGB_Init

*	��������:	��ʼ����Ļ

*************************************************************************************************/

void LCD_RGB_Init(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0}; // layer0 ��ز���

	/*---------------------------------- layer0 ��ʾ���� --------------------------------*/

	pLayerCfg.WindowX0 = 0;				 // ˮƽ���
	pLayerCfg.WindowX1 = LCD_Width;		 // ˮƽ�յ�
	pLayerCfg.WindowY0 = 0;				 // ��ֱ���
	pLayerCfg.WindowY1 = LCD_Height;	 // ��ֱ�յ�
	pLayerCfg.ImageWidth = LCD_Width;	 // ��ʾ�������
	pLayerCfg.ImageHeight = LCD_Height;	 // ��ʾ����߶�
	pLayerCfg.PixelFormat = ColorMode_0; // ��ɫ��ʽ

	// ���� layer0 �ĺ㶨͸���ȣ�����д�� LTDC_LxCACR �Ĵ���
	//	��Ҫע����ǣ����������ֱ���������� layer0 ��͸���ȣ���������Ϊ255����͸��
	pLayerCfg.Alpha = 255; // ȡֵ��Χ0~255��255��ʾ��͸����0��ʾ��ȫ͸��

	// ���� layer0 �Ĳ���ϵ��������д�� LTDC_LxBFCR �Ĵ���
	// �ò����������� layer0 �� �ײ㱳�� ֮�����ɫ���ϵ�������㹫ʽΪ ��
	// ��Ϻ����ɫ =  BF1 * layer0����ɫ + BF2 * �ײ㱳������ɫ
	// ��� layer0 ʹ����͸��ɫ����������ó� LTDC_BLENDING_FACTOR1_PAxCA �� LTDC_BLENDING_FACTOR2_PAxCA������ARGB�е�Aͨ����������
	//	����Ľ��ܿ��Բ��� �ο��ֲ���� LTDC_LxBFCR �Ĵ����Ľ���
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA; // ���ϵ��1
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA; // ���ϵ��2

	pLayerCfg.FBStartAdress = LCD_MemoryAdd; // �Դ��ַ

	// ���� layer0 �ĳ�ʼĬ����ɫ������A,R,G,B ��ֵ ������д�� LTDC_LxDCCR �Ĵ���
	pLayerCfg.Alpha0 = 0;		   // ��ʼ��ɫ��A
	pLayerCfg.Backcolor.Blue = 0;  //	��ʼ��ɫ��R
	pLayerCfg.Backcolor.Green = 0; //	��ʼ��ɫ��G
	pLayerCfg.Backcolor.Red = 0;   //	��ʼ��ɫ��B

	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0); // ����layer0

#if ((ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888) || (ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888)) // �ж��Ƿ�ʹ��24λ����32λɫ

	// ��Ϊ750ÿ��ͨ���ĵ�λ���ǲ���α�����������������������ɫ���������޷�������ʾ24λ����32λɫ

	HAL_LTDC_EnableDither(&hltdc); // ������ɫ����

#endif

	LCD_GPIO_Init(); // ��ʼ��LTDC���ŵı�������

	/*---------------------------------- layer1 ��ʾ���� --------------------------------*/

#if (LCD_NUM_LAYERS == 2) // ���������˫��

	LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

	pLayerCfg1.WindowX0 = 0;			  // ˮƽ���
	pLayerCfg1.WindowX1 = LCD_Width;	  // ˮƽ�յ�
	pLayerCfg1.WindowY0 = 0;			  // ��ֱ���
	pLayerCfg1.WindowY1 = LCD_Height;	  // ��ֱ�յ�
	pLayerCfg1.ImageWidth = LCD_Width;	  // ��ʾ�������
	pLayerCfg1.ImageHeight = LCD_Height;  // ��ʾ����߶�
	pLayerCfg1.PixelFormat = ColorMode_1; // ��ɫ��ʽ��layer1 Ӧ����Ϊ����͸��ɫ�ĸ�ʽ������ARGB8888��ARGB1555

	// ���� layer1 �ĺ㶨͸���ȣ�����д�� LTDC_LxCACR �Ĵ���
	//	��Ҫע����ǣ����������ֱ���������� layer1 ��͸���ȣ���������Ϊ255����͸��
	pLayerCfg1.Alpha = 255; // ȡֵ��Χ0~255��255��ʾ��͸����0��ʾ��ȫ͸��

	// ���� layer1 �Ĳ���ϵ��������д�� LTDC_LxBFCR �Ĵ���
	// �ò����������� layer1 �� (layer0+������֮�����ɫ���ϵ�������㹫ʽΪ ��
	// ��Ϻ����ɫ =  BF1 * layer1����ɫ + BF2 * (layer0+������Ϻ����ɫ��
	// ��� layer1 ʹ����͸��ɫ����������ó� LTDC_BLENDING_FACTOR1_PAxCA �� LTDC_BLENDING_FACTOR2_PAxCA������ARGB�е�Aͨ����������
	//	����Ľ��ܿ��Բ��� �ο��ֲ���� LTDC_LxBFCR �Ĵ����Ľ���
	pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA; // ���ϵ��1
	pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA; // ���ϵ��2

	pLayerCfg1.FBStartAdress = LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; // �Դ��ַ

	// ����layer1 �ĳ�ʼĬ����ɫ������A,R,G,B ��ֵ ������д�� LTDC_LxDCCR �Ĵ���
	pLayerCfg1.Alpha0 = 0;			// ��ʼ��ɫ��A
	pLayerCfg1.Backcolor.Red = 0;	//	��ʼ��ɫ��R
	pLayerCfg1.Backcolor.Green = 0; //	��ʼ��ɫ��G
	pLayerCfg1.Backcolor.Blue = 0;	//	��ʼ��ɫ��B

	HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1); // ��ʼ�� layer1 ������

#if ((ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888) || (ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB8888)) // �ж��Ƿ�ʹ��24λ����32λɫ

	// ��Ϊ750ÿ��ͨ���ĵ�λ���ǲ���α�����������������������ɫ���������޷�������ʾ24λ����32λɫ

	HAL_LTDC_EnableDither(&hltdc); // ������ɫ����

#endif

#endif

	/*---------------------------------- ��ʼ��һЩĬ������ --------------------------------*/

	LCD_DisplayDirection(Direction_H); //	���ú�����ʾ
	LCD_SetFont(&Font24);			   //	����Ĭ������
	LCD_ShowNumMode(Fill_Space);	   //	����������ʾĬ�����ո�

	LCD_SetLayer(0);			 // �л��� layer0
	LCD_SetBackColor(LCD_WHITE); //	���ñ���ɫ
	LCD_SetColor(LCD_BLACK);	 //	���û�����ɫ
	LCD_Clear();				 //	������ˢ����ɫ

	/*---------------------------------- ���������������ʾ --------------------------------*/

#if LCD_NUM_LAYERS == 2

	LCD_SetLayer(1);			 // �л���ǰ���� layer1��layer1ʼ����layer0֮��
	LCD_SetBackColor(LCD_WHITE); //	���ñ���ɫ
	LCD_SetColor(LCD_BLACK);	 //	���û�����ɫ
	LCD_Clear();				 //	������ˢ����ɫ

#endif

	// LTDC�ڳ�ʼ��֮���ϵ��˲�����һ�����ݵİ�����
	//	��ʹһ��ʼ�ͽ������������Ͳ�����Ļ���������õ����������ǻ����������
	//	�����Ҫ����������󣬿����ڳ�ʼ�����֮�󣬽���һ�����ݵ���ʱ�ٴ򿪱���
	//
	//	HAL_Delay(200);	// ��ʱ200ms

	LCD_Backlight_ON; // ��������
}

/*************************************************************************************************
 *	�� �� ��:	LCD_SetLayer
 *	��ڲ���:	layer - Ҫ��ʾ�Ͳ����Ĳ㣬��������Ϊ0��1����ѡ�� layer0 �� layer1
 *	�� �� ֵ:	��
 *	��������:	����Ҫ��ʾ�Ͳ����Ĳ㣬�л���Ӧ���Դ��ַ����ɫ��ʽ��
 *	˵    ��:	750��LTDC��˳���ǹ̶��ģ�layer1 �� layer0֮�ϣ�������������ʾʱ��
 *					layer1 ��ǰ���㣬ͨ��ʹ�ô�͸��ɫ����ɫ��ʽ��layer0 �Ǳ����㣬
 *					ֻ��������ʱ��Ĭ��ֻ���� layer0
 *************************************************************************************************/

void LCD_SetLayer(uint8_t layer)
{
#if LCD_NUM_LAYERS == 2 // �������˫��

	if (layer == 0) // ������õ��� layer0
	{
		LCD.LayerMemoryAdd = LCD_MemoryAdd;	 // ��ȡ layer0 ���Դ��ַ
		LCD.ColorMode = ColorMode_0;		 // ��ȡ layer0 ����ɫ��ʽ
		LCD.BytesPerPixel = BytesPerPixel_0; // ��ȡ layer0 ��ÿ�����������ֽ����Ĵ�С
	}
	else if (layer == 1) // ������õ��� layer1
	{
		LCD.LayerMemoryAdd = LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; // ��ȡ layer1 ���Դ��ַ
		LCD.ColorMode = ColorMode_1;							   // ��ȡ layer1 ����ɫ��ʽ
		LCD.BytesPerPixel = BytesPerPixel_1;					   // ��ȡ layer1 ��ÿ�����������ֽ����Ĵ�С
	}
	LCD.Layer = layer; // ��¼��ǰ���ڵĲ�

#else // ���ֻ�������㣬Ĭ�ϲ��� layer0

	LCD.LayerMemoryAdd = LCD_MemoryAdd;	 // ��ȡ layer0 ���Դ��ַ
	LCD.ColorMode = ColorMode_0;		 // ��ȡ layer0 ����ɫ��ʽ
	LCD.BytesPerPixel = BytesPerPixel_0; // ��ȡ layer0 ��ÿ�����������ֽ����Ĵ�С
	LCD.Layer = 0;						 // ��������Ϊ layer0

#endif
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_SetColor
 *
 *	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0xff0000FF ��ʾ��͸������ɫ��0xAA0000FF ��ʾ͸����Ϊ66.66%����ɫ
 *
 *	��������:	�˺�������������ʾ�ַ������㻭�ߡ���ͼ����ɫ
 *
 *	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
 *					2. 32λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ A��R��G��B  4����ɫͨ��
 *					3. ��8λ��͸��ͨ���У�ff��ʾ��͸����0��ʾ��ȫ͸��
 *					4. ����ʹ��ARGB1555��ARGB8888��֧��͸��ɫ����ɫ��ʽ����Ȼ͸��ɫ�������ã�����ARGB1555��֧��һλ
 *						͸��ɫ��������͸���Ͳ�͸������״̬��ARGB8888֧��255��͸����
 *					5. ����˵����͸������ָ �����㡢layer0��layer1 ֮���͸��
 *
 ***************************************************************************************************************/

void LCD_SetColor(uint32_t Color)
{
	uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0; // ������ɫͨ����ֵ

	if (LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB565) // ��32λɫת��Ϊ16λɫ
	{
		Red_Value = (uint16_t)((Color & 0x00F80000) >> 8);
		Green_Value = (uint16_t)((Color & 0x0000FC00) >> 5);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
		LCD.Color = (uint16_t)(Red_Value | Green_Value | Blue_Value);
	}
	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB1555) // ��32λɫת��ΪARGB1555��ɫ
	{
		if ((Color & 0xFF000000) == 0) // �ж��Ƿ�ʹ��͸��ɫ
			Alpha_Value = 0x0000;
		else
			Alpha_Value = 0x8000;

		Red_Value = (uint16_t)((Color & 0x00F80000) >> 9);
		Green_Value = (uint16_t)((Color & 0x0000F800) >> 6);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
		LCD.Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
	}
	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB4444) // ��32λɫת��ΪARGB4444��ɫ
	{

		Alpha_Value = (uint16_t)((Color & 0xf0000000) >> 16);
		Red_Value = (uint16_t)((Color & 0x00F00000) >> 12);
		Green_Value = (uint16_t)((Color & 0x0000F000) >> 8);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 4);
		LCD.Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
	}
	else
		LCD.Color = Color; // 24λɫ��32λɫ����Ҫת��
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_SetBackColor
 *
 *	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0xff0000FF ��ʾ��͸������ɫ��0xAA0000FF ��ʾ͸����Ϊ66.66%����ɫ
 *
 *	��������:	���ñ���ɫ,�˺������������Լ���ʾ�ַ��ı���ɫ
 *
 *	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
 *					2. 32λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ A��R��G��B  4����ɫͨ��
 *					3. ��8λ��͸��ͨ���У�ff��ʾ��͸����0��ʾ��ȫ͸��
 *					4. ����ʹ��ARGB1555��ARGB8888��֧��͸��ɫ����ɫ��ʽ����Ȼ͸��ɫ�������ã�����ARGB1555��֧��һλ
 *						͸��ɫ��������͸���Ͳ�͸������״̬��ARGB8888֧��255��͸����
 *					5. ����˵����͸������ָ �����㡢layer0��layer1֮���͸��
 *
 ***************************************************************************************************************/

void LCD_SetBackColor(uint32_t Color)
{
	uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0; // ������ɫͨ����ֵ

	if (LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB565) // ��32λɫת��Ϊ16λɫ
	{
		Red_Value = (uint16_t)((Color & 0x00F80000) >> 8);
		Green_Value = (uint16_t)((Color & 0x0000FC00) >> 5);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
		LCD.BackColor = (uint16_t)(Red_Value | Green_Value | Blue_Value);
	}
	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB1555) // ��32λɫת��ΪARGB1555��ɫ
	{
		if ((Color & 0xFF000000) == 0) // �ж��Ƿ�ʹ��͸��ɫ
			Alpha_Value = 0x0000;
		else
			Alpha_Value = 0x8000;

		Red_Value = (uint16_t)((Color & 0x00F80000) >> 9);
		Green_Value = (uint16_t)((Color & 0x0000F800) >> 6);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 3);
		LCD.BackColor = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
	}
	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB4444) // ��32λɫת��ΪARGB4444��ɫ
	{

		Alpha_Value = (uint16_t)((Color & 0xf0000000) >> 16);
		Red_Value = (uint16_t)((Color & 0x00F00000) >> 12);
		Green_Value = (uint16_t)((Color & 0x0000F000) >> 8);
		Blue_Value = (uint16_t)((Color & 0x000000F8) >> 4);
		LCD.BackColor = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
	}

	else
		LCD.BackColor = Color; // 24λɫ��32λɫ����Ҫת��
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_SetFont
 *
 *	��ڲ���:	*fonts - Ҫ���õ�ASCII����
 *
 *	��������:	����ASCII���壬��ѡ��ʹ�� 3216/2412/2010/1608/1206 ���ִ�С������
 *
 *	˵    ��:	1. ʹ��ʾ�� LCD_SetFont(&Font24) �������� 2412�� ASCII����
 *					2. �����ģ����� lcd_fonts.c
 *
 ***************************************************************************************************************/

void LCD_SetFont(pFONT *fonts)
{
	LCD_Fonts = fonts;
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayDirection
 *
 *	��ڲ���:	direction - Ҫ��ʾ�ķ���
 *
 *	��������:	����Ҫ��ʾ�ķ��򣬿�������� Direction_H ����������ʾ��Direction_V ������ֱ��ʾ
 *
 *	˵    ��:   ʹ��ʾ�� LCD_DisplayDirection(Direction_H) ����������Ļ������ʾ
 *
 ***************************************************************************************************************/

void LCD_DisplayDirection(uint8_t direction)
{
	LCD.Direction = direction;
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_Clear
 *
 *	��������:	������������LCD���Ϊ LCD.BackColor ����ɫ��ʹ��DMA2Dʵ��
 *
 *	˵    ��:	���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
 *
 ***************************************************************************************************************/

void LCD_Clear(void)
{

	DMA2D->CR &= ~(DMA2D_CR_START);				   //	ֹͣDMA2D
	DMA2D->CR = DMA2D_R2M;						   //	�Ĵ�����SDRAM
	DMA2D->OPFCCR = LCD.ColorMode;				   //	������ɫ��ʽ
	DMA2D->OOR = 0;								   //	������ƫ��
	DMA2D->OMAR = LCD.LayerMemoryAdd;			   // ��ַ
	DMA2D->NLR = (LCD_Width << 16) | (LCD_Height); //	�趨���ȺͿ���
	DMA2D->OCOLR = LCD.BackColor;				   //	��ɫ

	/******
	�ȴ� ��ֱ����ʹ����ʾ״̬ ����LTDC����ˢ��һ�������ݵ�ʱ��
	��Ϊ����Ļû��ˢ��һ֡ʱ����ˢ��������˺�ѵ�����
	�û�Ҳ����ʹ�� �Ĵ��������ж� �����жϣ�����Ϊ�˱�֤���̵ļ���Լ���ֲ�ķ����ԣ�����ֱ��ʹ���жϼĴ����ķ���

	��������жϣ�DMA2Dˢ���ٶ�����

	��ɫ��ʽ	RGB565	 RGB888	 ARGB888
	��ʱ	   4.3ms	    7.5ms	  11.9ms


	����֮�󣬲������ָ�ʽ������Ҫ17.6msˢһ����������Ļ������ˢ����ֻ��60֡���ң�LTDCʱ��33MHz����
	17.6ms���ٶ��Ѿ��㹻�ˣ������Ƕ��ٶ�Ҫ���ر�ߵĳ��ϣ���Ȼ��������жϴ�ֱ�ȴ�����䣬���Ա���˺��ЧӦ

	******/
	while (LTDC->CDSR != 0X00000001)
		; // �ж� ��ʾ״̬�Ĵ���LTDC_CDSR �ĵ�0λ VDES����ֱ����ʹ����ʾ״̬

	DMA2D->CR |= DMA2D_CR_START; //	����DMA2D

	while (DMA2D->CR & DMA2D_CR_START)
		; //	�ȴ��������
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_ClearRect
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					width  - Ҫ�������ĺ��򳤶�
 *					height - Ҫ���������������
 *
 *	��������:	�ֲ�������������ָ��λ�ö�Ӧ���������Ϊ LCD.BackColor ����ɫ
 *
 *	˵    ��:	1. ���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
 *					2. ʹ��ʾ�� LCD_ClearRect( 10, 10, 100, 50) ���������(10,10)��ʼ�ĳ�100��50������
 *
 ***************************************************************************************************************/

void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	DMA2D->CR &= ~(DMA2D_CR_START); //	ֹͣDMA2D
	DMA2D->CR = DMA2D_R2M;			//	�Ĵ�����SDRAM
	DMA2D->OPFCCR = LCD.ColorMode;	//	������ɫ��ʽ
	DMA2D->OCOLR = LCD.BackColor;	//	��ɫ

	if (LCD.Direction == Direction_H) // �������
	{
		DMA2D->OOR = LCD_Width - width;												//	������ƫ��
		DMA2D->OMAR = LCD.LayerMemoryAdd + LCD.BytesPerPixel * (LCD_Width * y + x); // ��ַ;
		DMA2D->NLR = (width << 16) | (height);										//	�趨���ȺͿ���
	}
	else // �������
	{
		DMA2D->OOR = LCD_Width - height;																	   //	������ƫ��
		DMA2D->OMAR = LCD.LayerMemoryAdd + LCD.BytesPerPixel * ((LCD_Height - x - 1 - width) * LCD_Width + y); // ��ַ
		DMA2D->NLR = (width) | (height << 16);																   //	�趨���ȺͿ���
	}

	DMA2D->CR |= DMA2D_CR_START; //	����DMA2D

	while (DMA2D->CR & DMA2D_CR_START)
		; //	�ȴ��������
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_DrawPoint
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					color  - Ҫ���Ƶ���ɫ��ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
 *
 *	��������:	��ָ���������ָ����ɫ�ĵ�
 *
 *	˵    ��:	1. ֱ���ڶ�Ӧ���Դ�λ��д����ɫֵ������ʵ�ֻ���Ĺ���
 *					2. ʹ��ʾ�� LCD_DrawPoint( 10, 10, 0xff0000FF) ��������(10,10)������ɫ�ĵ�
 *
 ***************************************************************************************************************/

void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color)
{

	/*----------------------- 32λɫ ARGB8888 ģʽ ----------------------*/

	if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB8888)
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			*(__IO uint32_t *)(LCD.LayerMemoryAdd + 4 * (x + y * LCD_Width)) = color;
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			*(__IO uint32_t *)(LCD.LayerMemoryAdd + 4 * ((LCD_Height - x - 1) * LCD_Width + y)) = color;
		}
	}
	/*----------------------------- 24λɫ RGB888 ģʽ -------------------------*/

	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB888)
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			*(__IO uint16_t *)(LCD.LayerMemoryAdd + 3 * (x + y * LCD_Width)) = color;
			*(__IO uint8_t *)(LCD.LayerMemoryAdd + 3 * (x + y * LCD_Width) + 2) = color >> 16;
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			*(__IO uint16_t *)(LCD.LayerMemoryAdd + 3 * ((LCD_Height - x - 1) * LCD_Width + y)) = color;
			*(__IO uint8_t *)(LCD.LayerMemoryAdd + 3 * ((LCD_Height - x - 1) * LCD_Width + y) + 2) = color >> 16;
		}
	}

	/*----------------------- 16λɫ ARGB1555��RGB565����ARGB4444 ģʽ ----------------------*/
	else
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			*(__IO uint16_t *)(LCD.LayerMemoryAdd + 2 * (x + y * LCD_Width)) = color;
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			*(__IO uint16_t *)(LCD.LayerMemoryAdd + 2 * ((LCD_Height - x - 1) * LCD_Width + y)) = color;
		}
	}
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_ReadPoint
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *
 *	�� �� ֵ��  ��ȡ������ɫ
 *
 *	��������:	��ȡָ����������ɫ����ʹ��16��24λɫģʽʱ������������ɫ���ݶ�ӦΪ16λ��24λ
 *
 *	˵    ��:	1. ֱ�Ӷ�ȡ��Ӧ���Դ�ֵ������ʵ�ֶ���Ĺ���
 *					2. ʹ��ʾ�� color = LCD_ReadPoint( 10, 10) ��color Ϊ��ȡ���������(10,10)����ɫ
 *
 ***************************************************************************************************************/

uint32_t LCD_ReadPoint(uint16_t x, uint16_t y)
{
	uint32_t color = 0;

	/*----------------------- 32λɫ ARGB8888 ģʽ ----------------------*/
	if (LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB8888)
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			color = *(__IO uint32_t *)(LCD.LayerMemoryAdd + 4 * (x + y * LCD_Width));
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			color = *(__IO uint32_t *)(LCD.LayerMemoryAdd + 4 * ((LCD_Height - x - 1) * LCD_Width + y));
		}
	}

	/*----------------------------- 24λɫ RGB888 ģʽ -------------------------*/
	else if (LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB888)
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			color = *(__IO uint32_t *)(LCD.LayerMemoryAdd + 3 * (x + y * LCD_Width)) & 0x00ffffff;
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			color = *(__IO uint32_t *)(LCD.LayerMemoryAdd + 3 * ((LCD_Height - x - 1) * LCD_Width + y)) & 0x00ffffff;
		}
	}

	/*----------------------- 16λɫ ARGB1555��RGB565����ARGB4444 ģʽ ----------------------*/
	else
	{
		if (LCD.Direction == Direction_H) // ˮƽ����
		{
			color = *(__IO uint16_t *)(LCD.LayerMemoryAdd + 2 * (x + y * LCD_Width));
		}
		else if (LCD.Direction == Direction_V) // ��ֱ����
		{
			color = *(__IO uint16_t *)(LCD.LayerMemoryAdd + 2 * ((LCD_Height - x - 1) * LCD_Width + y));
		}
	}
	return color;
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayChar
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					c  - ASCII�ַ�
 *
 *	��������:	��ָ��������ʾָ�����ַ�
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetFont(&Font24) ����Ϊ 2412��ASCII����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayChar( 10, 10, 'a') ��������(10,10)��ʾ�ַ� 'a'
 *
 ***************************************************************************************************************/

void LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t c)
{
	uint16_t index = 0, counter = 0; // ��������
	uint8_t disChar;				 // �洢�ַ��ĵ�ַ
	uint16_t Xaddress = x;			 // ˮƽ����

	c = c - 32; // ����ASCII�ַ���ƫ��

	for (index = 0; index < LCD_Fonts->Sizes; index++)
	{
		disChar = LCD_Fonts->pTable[c * LCD_Fonts->Sizes + index]; // ��ȡ�ַ���ģֵ
		for (counter = 0; counter < 8; counter++)
		{
			if (disChar & 0x01)
			{
				LCD_DrawPoint(Xaddress, y, LCD.Color); // ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
			}
			else
			{
				LCD_DrawPoint(Xaddress, y, LCD.BackColor); // ����ʹ�ñ���ɫ���Ƶ�
			}
			disChar >>= 1;
			Xaddress++; // ˮƽ�����Լ�

			if ((Xaddress - x) == LCD_Fonts->Width) // ���ˮƽ����ﵽ���ַ����ȣ����˳���ǰѭ��
			{										// ������һ�еĻ���
				Xaddress = x;
				y++;
				break;
			}
		}
	}
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayString
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					p - ASCII�ַ������׵�ַ
 *
 *	��������:	��ָ��������ʾָ�����ַ���
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetFont(&Font24) ����Ϊ 2412��ASCII����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayString( 10, 10, "FANKE") ������ʼ����Ϊ(10,10)�ĵط���ʾ�ַ���"FANKE"
 *
 ***************************************************************************************************************/

void LCD_DisplayString(uint16_t x, uint16_t y, char *p)
{
	while ((x < LCD_Width) && (*p != 0)) // �ж���ʾ�����Ƿ񳬳���ʾ�������ַ��Ƿ�Ϊ���ַ�
	{
		LCD_DisplayChar(x, y, *p);
		x += LCD_Fonts->Width; // ��ʾ��һ���ַ�
		p++;				   // ȡ��һ���ַ���ַ
	}
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_SetTextFont
 *
 *	��ڲ���:	*fonts - Ҫ���õ��ı�����
 *
 *	��������:	�����ı����壬�������ĺ�ASCII�ַ���
 *
 *	˵    ��:	1. ��ѡ��ʹ�� 3232/2424/2020/1616/1212 ���ִ�С���������壬
 *						���Ҷ�Ӧ������ASCII����Ϊ 3216/2412/2010/1608/1206
 *					2. �����ģ����� lcd_fonts.c
 *					3. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ
 *					4. ʹ��ʾ�� LCD_SetTextFont(&CH_Font24) �������� 2424�����������Լ�2412��ASCII�ַ�����
 *
 ***************************************************************************************************************/

void LCD_SetTextFont(pFONT *fonts)
{
	LCD_CHFonts = fonts; // ������������
	switch (fonts->Width)
	{
	case 12:
		LCD_Fonts = &Font12;
		break; // ����ASCII�ַ�������Ϊ 1206
	case 16:
		LCD_Fonts = &Font16;
		break; // ����ASCII�ַ�������Ϊ 1608
	case 20:
		LCD_Fonts = &Font20;
		break; // ����ASCII�ַ�������Ϊ 2010
	case 24:
		LCD_Fonts = &Font24;
		break; // ����ASCII�ַ�������Ϊ 2412
	case 32:
		LCD_Fonts = &Font32;
		break; // ����ASCII�ַ�������Ϊ 3216
	default:
		break;
	}
}
/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayChinese
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					pText - �����ַ�
 *
 *	��������:	��ָ��������ʾָ���ĵ��������ַ�
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayChinese( 10, 10, "��") ��������(10,10)��ʾ�����ַ�"��"
 *
 ***************************************************************************************************************/

void LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText)
{
	uint16_t i = 0, index = 0, counter = 0; // ��������
	uint16_t addr;							// ��ģ��ַ
	uint8_t disChar;						// ��ģ��ֵ
	uint16_t Xaddress = x;					// ˮƽ����

	while (1)
	{
		// �Ա������еĺ��ֱ��룬���Զ�λ�ú�����ģ�ĵ�ַ
		if (*(LCD_CHFonts->pTable + (i + 1) * LCD_CHFonts->Sizes + 0) == *pText && *(LCD_CHFonts->pTable + (i + 1) * LCD_CHFonts->Sizes + 1) == *(pText + 1))
		{
			addr = i; // ��ģ��ַƫ��
			break;
		}
		i += 2; // ÿ�������ַ�����ռ���ֽ�

		if (i >= LCD_CHFonts->Table_Rows)
			break; // ��ģ�б�������Ӧ�ĺ���
	}

	for (index = 0; index < LCD_CHFonts->Sizes; index++)
	{
		disChar = *(LCD_CHFonts->pTable + (addr)*LCD_CHFonts->Sizes + index); // ��ȡ��Ӧ����ģ��ַ

		for (counter = 0; counter < 8; counter++)
		{
			if (disChar & 0x01)
			{
				LCD_DrawPoint(Xaddress, y, LCD.Color); // ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
			}
			else
			{
				LCD_DrawPoint(Xaddress, y, LCD.BackColor); // ����ʹ�ñ���ɫ���Ƶ�
			}
			disChar >>= 1;
			Xaddress++; // ˮƽ�����Լ�

			if ((Xaddress - x) == LCD_CHFonts->Width) //	���ˮƽ����ﵽ���ַ����ȣ����˳���ǰѭ��
			{										  //	������һ�еĻ���
				Xaddress = x;
				y++;
				break;
			}
		}
	}
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_DisplayText
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					pText - �ַ�����������ʾ���Ļ���ASCII�ַ�
 *
 *	��������:	��ָ��������ʾָ�����ַ���
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayChinese( 10, 10, "���ͿƼ�STM32") ��������(10,10)��ʾ�ַ���"���ͿƼ�STM32"
 *
 ***************************************************************************************************************/

void LCD_DisplayText(uint16_t x, uint16_t y, char *pText)
{

	while (*pText != 0) // �ж��Ƿ�Ϊ���ַ�
	{
		if (*pText <= 0x7F) // �ж��Ƿ�ΪASCII��
		{
			LCD_DisplayChar(x, y, *pText); // ��ʾASCII
			x += LCD_Fonts->Width;		   // ˮƽ���������һ���ַ���
			pText++;					   // �ַ�����ַ+1
		}
		else // ���ַ�Ϊ����
		{
			LCD_DisplayChinese(x, y, pText); // ��ʾ����
			x += LCD_CHFonts->Width;		 // ˮƽ���������һ���ַ���
			pText += 2;						 // �ַ�����ַ+2�����ֵı���Ҫ2�ֽ�
		}
	}
}

/***************************************************************************************************************
 *	�� �� ��:	LCD_ShowNumMode
 *
 *	��ڲ���:	mode - ���ñ�������ʾģʽ
 *
 *	��������:	���ñ�����ʾʱ����λ��0���ǲ��ո񣬿�������� Fill_Space ���ո�Fill_Zero �����
 *
 *	˵    ��:   1. ֻ�� LCD_DisplayNumber() ��ʾ���� �� LCD_DisplayDecimals()��ʾС�� �����������õ�
 *					2. ʹ��ʾ�� LCD_ShowNumMode(Fill_Zero) ���ö���λ���0������ 123 ������ʾΪ 000123
 *
 ***************************************************************************************************************/

void LCD_ShowNumMode(uint8_t mode)
{
	LCD.ShowNum_Mode = mode;
}

/*****************************************************************************************************************************************
 *	�� �� ��:	LCD_DisplayNumber
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					number - Ҫ��ʾ������,��Χ�� -2147483648~2147483647 ֮��
 *					len - ���ֵ�λ�������λ������len��������ʵ�ʳ�������������������š��������Ҫ��ʾ��������Ԥ��һ��λ�ķ�����ʾ�ռ�
 *
 *	��������:	��ָ��������ʾָ������������
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayNumber( 10, 10, a, 5) ��������(10,10)��ʾָ������a,�ܹ�5λ������λ��0��ո�
 *						���� a=123 ʱ������� LCD_ShowNumMode()����������ʾ  123(ǰ�������ո�λ) ����00123
 *
 *****************************************************************************************************************************************/

void LCD_DisplayNumber(uint16_t x, uint16_t y, int32_t number, uint8_t len)
{
	char Number_Buffer[15]; // ���ڴ洢ת������ַ���

	if (LCD.ShowNum_Mode == Fill_Zero) // ����λ��0
	{
		sprintf(Number_Buffer, "%0.*d", len, number); // �� number ת�����ַ�����������ʾ
	}
	else // ����λ���ո�
	{
		sprintf(Number_Buffer, "%*d", len, number); // �� number ת�����ַ�����������ʾ
	}

	LCD_DisplayString(x, y, (char *)Number_Buffer); // ��ת���õ����ַ�����ʾ����
}

/***************************************************************************************************************************************
 *	�� �� ��:	LCD_DisplayDecimals
 *
 *	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *					decimals - Ҫ��ʾ������, double��ȡֵ1.7 x 10^��-308��~ 1.7 x 10^��+308����������ȷ��׼ȷ����Чλ��Ϊ15~16λ
 *
 *       			len - ������������λ��������С����͸��ţ�����ʵ�ʵ���λ��������ָ������λ��������ʵ�ʵ��ܳ���λ�����
 *							ʾ��1��С�� -123.123 ��ָ�� len <=8 �Ļ�����ʵ���ճ���� -123.123
 *							ʾ��2��С�� -123.123 ��ָ�� len =10 �Ļ�����ʵ�����   -123.123(����ǰ����������ո�λ)
 *							ʾ��3��С�� -123.123 ��ָ�� len =10 �Ļ��������ú��� LCD_ShowNumMode() ����Ϊ���0ģʽʱ��ʵ����� -00123.123
 *
 *					decs - Ҫ������С��λ������С����ʵ��λ��������ָ����С��λ����ָ���Ŀ��������������
 *							 ʾ����1.12345 ��ָ�� decs Ϊ4λ�Ļ�����������Ϊ1.1235
 *
 *	��������:	��ָ��������ʾָ���ı���������С��
 *
 *	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
 *					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
 *					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
 *					4. ʹ��ʾ�� LCD_DisplayDecimals( 10, 10, a, 5, 3) ��������(10,10)��ʾ�ֱ���a,�ܳ���Ϊ5λ�����б���3λС��
 *
 *****************************************************************************************************************************************/

void LCD_DisplayDecimals(uint16_t x, uint16_t y, double decimals, uint8_t len, uint8_t decs)
{
	char Number_Buffer[20]; // ���ڴ洢ת������ַ���

	if (LCD.ShowNum_Mode == Fill_Zero) // ����λ���0ģʽ
	{
		sprintf(Number_Buffer, "%0*.*lf", len, decs, decimals); // �� number ת�����ַ�����������ʾ
	}
	else // ����λ���ո�
	{
		sprintf(Number_Buffer, "%*.*lf", len, decs, decimals); // �� number ת�����ַ�����������ʾ
	}

	LCD_DisplayString(x, y, (char *)Number_Buffer); // ��ת���õ����ַ�����ʾ����
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawImage
 *
 *	��ڲ���: x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *				 y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *			 	 width  - ͼƬ��ˮƽ���ȣ����ȡֵ800
 *				 height - ͼƬ�Ĵ�ֱ���ȣ����ȡֵ480
 *				*pImage - ͼƬ���ݴ洢�����׵�ַ
 *
 *	��������: ��ָ�����괦��ʾͼƬ
 *
 *	˵    ��: Ҫ��ʾ��ͼƬ��Ҫ���Ƚ���ȡģ����ֻ����ʾһ����ɫ��ʹ�� LCD_SetColor() �������û���ɫ
 *
 *****************************************************************************************************************************************/

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pImage)
{
	uint8_t disChar;	   // ��ģ��ֵ
	uint16_t Xaddress = x; // ˮƽ����
	uint16_t i = 0, j = 0, m = 0;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < (float)width / 8; j++)
		{
			disChar = *pImage;

			for (m = 0; m < 8; m++)
			{
				if (disChar & 0x01)
				{
					LCD_DrawPoint(Xaddress, y, LCD.Color); // ��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
				}
				else
				{
					LCD_DrawPoint(Xaddress, y, LCD.BackColor); // ����ʹ�ñ���ɫ���Ƶ�
				}
				disChar >>= 1;
				Xaddress++; // ˮƽ�����Լ�

				if ((Xaddress - x) == width) // ���ˮƽ����ﵽ���ַ����ȣ����˳���ǰѭ��
				{							 // ������һ�еĻ���
					Xaddress = x;
					y++;
					break;
				}
			}
			pImage++;
		}
	}
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawLine
 *
 *	��ڲ���: x1 - ��� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y1 - ��� ��ֱ���꣬ȡֵ��Χ 0~479
 *
 *				 x2 - �յ� ˮƽ���꣬ȡֵ��Χ 0~799
 *            y2 - �յ� ��ֱ���꣬ȡֵ��Χ 0~479
 *
 *	��������: ������֮�仭��
 *
 *	˵    ��: �ú�����ֲ��ST�ٷ������������
 *
 *****************************************************************************************************************************************/

#define ABS(X) ((X) > 0 ? (X) : -(X))

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
			yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
			curpixel = 0;

	deltax = ABS(x2 - x1); /* The difference between the x's */
	deltay = ABS(y2 - y1); /* The difference between the y's */
	x = x1;				   /* Start x off at the first pixel */
	y = y1;				   /* Start y off at the first pixel */

	if (x2 >= x1) /* The x-values are increasing */
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else /* The x-values are decreasing */
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) /* The y-values are increasing */
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else /* The y-values are decreasing */
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay) /* There is at least one x-value for every y-value */
	{
		xinc1 = 0; /* Don't change the x when numerator >= denominator */
		yinc2 = 0; /* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax; /* There are more x-values than y-values */
	}
	else /* There is at least one y-value for every x-value */
	{
		xinc2 = 0; /* Don't change the x for every iteration */
		yinc1 = 0; /* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay; /* There are more y-values than x-values */
	}
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		LCD_DrawPoint(x, y, LCD.Color); /* Draw the current pixel */
		num += numadd;					/* Increase the numerator by the top of the fraction */
		if (num >= den)					/* Check if numerator >= denominator */
		{
			num -= den; /* Calculate the new numerator value */
			x += xinc1; /* Change the x as appropriate */
			y += yinc1; /* Change the y as appropriate */
		}
		x += xinc2; /* Change the x as appropriate */
		y += yinc2; /* Change the y as appropriate */
	}
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawRect
 *
 *	��ڲ���: x - ��ʼˮƽ���꣬ȡֵ��Χ0~799
 *				 y - ��ʼ��ֱ���꣬ȡֵ��Χ0~479
 *			 	 width  - ͼƬ��ˮƽ���ȣ����ȡֵ800
 *				 height - ͼƬ�Ĵ�ֱ���ȣ����ȡֵ480
 *
 *	��������: ��ָ��λ�û���ָ�������ľ�������
 *
 *	˵    ��: �ú�����ֲ��ST�ٷ������������
 *
 *****************************************************************************************************************************************/

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	/* draw horizontal lines */
	LCD_DrawLine(x, y, x + width, y);
	LCD_DrawLine(x, y + height, x + width, y + height);

	/* draw vertical lines */
	LCD_DrawLine(x, y, x, y + height);
	LCD_DrawLine(x + width, y, x + width, y + height);
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawCircle
 *
 *	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 r  - �뾶
 *
 *	��������: ������ (x,y) ���ư뾶Ϊ r ��Բ������
 *
 *	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r)
{
	int Xadd = -r, Yadd = 0, err = 2 - 2 * r, e2;
	do
	{

		LCD_DrawPoint(x - Xadd, y + Yadd, LCD.Color);
		LCD_DrawPoint(x + Xadd, y + Yadd, LCD.Color);
		LCD_DrawPoint(x + Xadd, y - Yadd, LCD.Color);
		LCD_DrawPoint(x - Xadd, y - Yadd, LCD.Color);

		e2 = err;
		if (e2 <= Yadd)
		{
			err += ++Yadd * 2 + 1;
			if (-Xadd == Yadd && e2 <= Xadd)
				e2 = 0;
		}
		if (e2 > Xadd)
			err += ++Xadd * 2 + 1;
	} while (Xadd <= 0);
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_DrawEllipse
 *
 *	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 r1  - ˮƽ����ĳ���
 *				 r2  - ��ֱ����ĳ���
 *
 *	��������: ������ (x,y) ����ˮƽ����Ϊ r1 ��ֱ����Ϊ r2 ����Բ����
 *
 *	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_DrawEllipse(int x, int y, int r1, int r2)
{
	int Xadd = -r1, Yadd = 0, err = 2 - 2 * r1, e2;
	float K = 0, rad1 = 0, rad2 = 0;

	rad1 = r1;
	rad2 = r2;

	if (r1 > r2)
	{
		do
		{
			K = (float)(rad1 / rad2);

			LCD_DrawPoint(x - Xadd, y + (uint16_t)(Yadd / K), LCD.Color);
			LCD_DrawPoint(x + Xadd, y + (uint16_t)(Yadd / K), LCD.Color);
			LCD_DrawPoint(x + Xadd, y - (uint16_t)(Yadd / K), LCD.Color);
			LCD_DrawPoint(x - Xadd, y - (uint16_t)(Yadd / K), LCD.Color);

			e2 = err;
			if (e2 <= Yadd)
			{
				err += ++Yadd * 2 + 1;
				if (-Xadd == Yadd && e2 <= Xadd)
					e2 = 0;
			}
			if (e2 > Xadd)
				err += ++Xadd * 2 + 1;
		} while (Xadd <= 0);
	}
	else
	{
		Yadd = -r2;
		Xadd = 0;
		do
		{
			K = (float)(rad2 / rad1);

			LCD_DrawPoint(x - (uint16_t)(Xadd / K), y + Yadd, LCD.Color);
			LCD_DrawPoint(x + (uint16_t)(Xadd / K), y + Yadd, LCD.Color);
			LCD_DrawPoint(x + (uint16_t)(Xadd / K), y - Yadd, LCD.Color);
			LCD_DrawPoint(x - (uint16_t)(Xadd / K), y - Yadd, LCD.Color);

			e2 = err;
			if (e2 <= Xadd)
			{
				err += ++Xadd * 3 + 1;
				if (-Yadd == Xadd && e2 <= Yadd)
					e2 = 0;
			}
			if (e2 > Yadd)
				err += ++Yadd * 3 + 1;
		} while (Yadd <= 0);
	}
}
/***************************************************************************************************************************************
 *	�� �� ��: LCD_FillRect
 *
 *	��ڲ���: x - ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 width  - ͼƬ��ˮƽ���ȣ����ȡֵ800
 *				 height - ͼƬ�Ĵ�ֱ���ȣ����ȡֵ480
 *
 *	��������: ������ (x,y) ���ָ��������ʵ�ľ���
 *
 *	˵    ��: 1. ʹ��DMA2Dʵ��
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	DMA2D->CR &= ~(DMA2D_CR_START); //	ֹͣDMA2D
	DMA2D->CR = DMA2D_R2M;			//	�Ĵ�����SDRAM
	DMA2D->OPFCCR = LCD.ColorMode;	//	������ɫ��ʽ
	DMA2D->OCOLR = LCD.Color;		//	��ɫ

	if (LCD.Direction == Direction_H) // �������
	{
		DMA2D->OOR = LCD_Width - width;												//	������ƫ��
		DMA2D->OMAR = LCD.LayerMemoryAdd + LCD.BytesPerPixel * (LCD_Width * y + x); // ��ַ;
		DMA2D->NLR = (width << 16) | (height);										//	�趨���ȺͿ���
	}
	else // �������
	{
		DMA2D->OOR = LCD_Width - height;																	   //	������ƫ��
		DMA2D->OMAR = LCD.LayerMemoryAdd + LCD.BytesPerPixel * ((LCD_Height - x - 1 - width) * LCD_Width + y); // ��ַ
		DMA2D->NLR = (width) | (height << 16);																   //	�趨���ȺͿ���
	}

	DMA2D->CR |= DMA2D_CR_START; //	����DMA2D

	while (DMA2D->CR & DMA2D_CR_START)
		; //	�ȴ��������
}

/***************************************************************************************************************************************
 *	�� �� ��: LCD_FillCircle
 *
 *	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~799
 *			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~479
 *			 	 r  - �뾶
 *
 *	��������: ������ (x,y) ���뾶Ϊ r ��Բ������
 *
 *	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
 *				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
 *
 *****************************************************************************************************************************************/

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r)
{
	int32_t D;	   /* Decision Variable */
	uint32_t CurX; /* Current X Value */
	uint32_t CurY; /* Current Y Value */

	D = 3 - (r << 1);

	CurX = 0;
	CurY = r;

	while (CurX <= CurY)
	{
		if (CurY > 0)
		{
			LCD_DrawLine(x - CurX, y - CurY, x - CurX, y - CurY + 2 * CurY);
			LCD_DrawLine(x + CurX, y - CurY, x + CurX, y - CurY + 2 * CurY);
		}

		if (CurX > 0)
		{
			LCD_DrawLine(x - CurY, y - CurX, x - CurY, y - CurX + 2 * CurX);
			LCD_DrawLine(x + CurY, y - CurX, x + CurY, y - CurX + 2 * CurX);
		}
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}

	LCD_DrawCircle(x, y, r);
}
/**************************************************************************************************************************************************************************************************************************************************************************FANKE***/
// ʵ��ƽ̨������ STM32H750���İ�
//

void Qinwei(int flower) //	��΢�ɺ� flower������
{
	char S;
	if (flower >= 0 && flower <= 5)
	{
		S = 'A';
	}
	if (flower >= 6 && flower <= 11)
	{
		S = 'B';
	}
	if (flower >= 12 && flower <= 17)
	{
		S = 'C';
	}
	if (flower >= 18 && flower <= 23)
	{
		S = 'D';
	}
	if (S == 'A')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(10, 10 + 60 * (flower), "��ȸɺ�");
	}
	if (S == 'B')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(200, 10 + 60 * (flower - 6), "��ȸɺ�");
	}
	if (S == 'C')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(390, 10 + 60 * (flower - 12), "��ȸɺ�");
	}
	if (S == 'D')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(580, 10 + 60 * (flower - 18), "��ȸɺ�");
	}
}
void Yiban(int flower) // һ��ɺ�
{
	char S;
	if (flower >= 0 && flower <= 5)
	{
		S = 'A';
	}
	if (flower >= 6 && flower <= 11)
	{
		S = 'B';
	}
	if (flower >= 12 && flower <= 17)
	{
		S = 'C';
	}
	if (flower >= 18 && flower <= 23)
	{
		S = 'D';
	}
	if (S == 'A')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(10, 10 + 60 * (flower), "һ��ɺ�");
	}
	if (S == 'B')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(200, 10 + 60 * (flower - 6), "һ��ɺ�");
	}
	if (S == 'C')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(390, 10 + 60 * (flower - 12), "һ��ɺ�");
	}
	if (S == 'D')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(580, 10 + 60 * (flower - 18), "һ��ɺ�");
	}
}
void Yanzhong(int flower)
{
	char S;
	if (flower >= 0 && flower <= 5)
	{
		S = 'A';
	}
	if (flower >= 6 && flower <= 11)
	{
		S = 'B';
	}
	if (flower >= 12 && flower <= 17)
	{
		S = 'C';
	}
	if (flower >= 18 && flower <= 23)
	{
		S = 'D';
	}
	if (S == 'A')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(10, 10 + 60 * (flower), "���ظɺ�");
	}
	if (S == 'B')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(200, 10 + 60 * (flower - 6), "���ظɺ�");
	}
	if (S == 'C')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(390, 10 + 60 * (flower - 12), "���ظɺ�");
	}
	if (S == 'D')
	{
		LCD_SetTextFont(&CH_Font32);
		LCD_DisplayText(580, 10 + 60 * (flower - 18), "���ظɺ�");
	}
}

void LCD_hanqing(uint8_t drought_info, uint8_t flower_Cnt)
{
	if (drought_info == 0x01)
		Qinwei(flower_Cnt);
	else if (drought_info == 0x02)
		Yiban(flower_Cnt);
	else if (drought_info == 0x03)
		Yanzhong(flower_Cnt);
}

void screenTask(void)
{
	//    LCD_SetTextFont(&CH_Font32);
	//    LCD_DisplayText(200, 10,"���ظɺ�");
	LCD_hanqing(0x02, 4);
	LCD_hanqing(0x01, 8);
	LCD_hanqing(0x03, 17);
}
