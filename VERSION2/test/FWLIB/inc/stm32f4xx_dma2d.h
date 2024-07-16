/**
  ******************************************************************************
  * @file    stm32f4xx_dma2d.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the DMA2D firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_DMA2D_H
#define __STM32F4xx_DMA2D_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "legacy.h"
#include "ll_includes.h"
#include "stm32f4xx_hal_conf.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA2D
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
 
/** 
  * @brief  DMA2D Init structure definition  
  */

typedef struct
{
  uint32_t DMA2D_Mode;                           /*!< configures the DMA2D transfer mode.
                                                 This parameter can be one value of @ref DMA2D_MODE */
  
  uint32_t DMA2D_CMode;                          /*!< configures the color format of the output image.
                                                 This parameter can be one value of @ref DMA2D_CMODE */

  uint32_t DMA2D_OutputBlue;                     /*!< configures the blue value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x1F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */

  uint32_t DMA2D_OutputGreen;                    /*!< configures the green value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x2F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */
            
  uint32_t DMA2D_OutputRed;                      /*!< configures the red value of the output image. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0xFF if RGB888 color mode is slected
                                                 - from 0x00 to 0x1F if RGB565 color mode is slected
                                                 - from 0x00 to 0x1F if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */
  
  uint32_t DMA2D_OutputAlpha;                    /*!< configures the alpha channel of the output color. 
                                                 This parameter must range:
                                                 - from 0x00 to 0xFF if ARGB8888 color mode is slected
                                                 - from 0x00 to 0x01 if ARGB1555 color mode is slected
                                                 - from 0x00 to 0x0F if ARGB4444 color mode is slected  */

  uint32_t DMA2D_OutputMemoryAdd;                /*!< Specifies the memory address. This parameter 
                                                 must be range from 0x00000000 to 0xFFFFFFFF. */

  uint32_t DMA2D_OutputOffset;                   /*!< Specifies the Offset value. This parameter must be range from
                                                 0x0000 to 0x3FFF. */

  uint32_t DMA2D_NumberOfLine;                   /*!< Configures the number of line of the area to be transfered.
                                                 This parameter must range from 0x0000 to 0xFFFF */
            
  uint32_t DMA2D_PixelPerLine;                   /*!< Configures the number pixel per line of the area to be transfered.
                                                 This parameter must range from 0x0000 to 0x3FFF */
} LL_DMA2D_InitTypeDef;



typedef struct
{
  uint32_t DMA2D_FGMA;                           /*!< configures the DMA2D foreground memory address.
                                                 This parameter must be range from 0x00000000 to 0xFFFFFFFF. */
  
  uint32_t DMA2D_FGO;                            /*!< configures the DMA2D foreground offset.
                                                 This parameter must be range from 0x0000 to 0x3FFF. */

  uint32_t DMA2D_FGCM;                           /*!< configures the DMA2D foreground color mode . 
                                                 This parameter can be one value of @ref DMA2D_FGCM */

  uint32_t DMA2D_FG_CLUT_CM;                     /*!< configures the DMA2D foreground CLUT color mode. 
                                                 This parameter can be one value of @ref DMA2D_FG_CLUT_CM */
            
  uint32_t DMA2D_FG_CLUT_SIZE;                   /*!< configures the DMA2D foreground CLUT size. 
                                                 This parameter must range from 0x00 to 0xFF. */
  
  uint32_t DMA2D_FGPFC_ALPHA_MODE;               /*!< configures the DMA2D foreground alpha mode. 
                                                 This parameter can be one value of @ref DMA2D_FGPFC_ALPHA_MODE */

  uint32_t DMA2D_FGPFC_ALPHA_VALUE;              /*!< Specifies the DMA2D foreground alpha value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_BLUE;                       /*!< Specifies the DMA2D foreground blue value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_GREEN;                      /*!< Specifies the DMA2D foreground green value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_FGC_RED;                        /*!< Specifies the DMA2D foreground red value 
                                                 must be range from 0x00 to 0xFF. */
            
  uint32_t DMA2D_FGCMAR;                         /*!< Configures the DMA2D foreground CLUT memory address.
                                                 This parameter must range from 0x00000000 to 0xFFFFFFFF. */
} LL_DMA2D_LayerCfgTypeDef;


typedef struct
{
  uint32_t DMA2D_BGMA;                           /*!< configures the DMA2D background memory address.
                                                 This parameter must be range from 0x00000000 to 0xFFFFFFFF. */
  
  uint32_t DMA2D_BGO;                            /*!< configures the DMA2D background offset.
                                                 This parameter must be range from 0x0000 to 0x3FFF. */

  uint32_t DMA2D_BGCM;                           /*!< configures the DMA2D background color mode . 
                                                 This parameter can be one value of @ref DMA2D_FGCM */

  uint32_t DMA2D_BG_CLUT_CM;                     /*!< configures the DMA2D background CLUT color mode. 
                                                 This parameter can be one value of @ref DMA2D_FG_CLUT_CM */
            
  uint32_t DMA2D_BG_CLUT_SIZE;                   /*!< configures the DMA2D background CLUT size. 
                                                 This parameter must range from 0x00 to 0xFF. */
  
  uint32_t DMA2D_BGPFC_ALPHA_MODE;               /*!< configures the DMA2D background alpha mode. 
                                                 This parameter can be one value of @ref DMA2D_FGPFC_ALPHA_MODE */

  uint32_t DMA2D_BGPFC_ALPHA_VALUE;              /*!< Specifies the DMA2D background alpha value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_BLUE;                       /*!< Specifies the DMA2D background blue value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_GREEN;                      /*!< Specifies the DMA2D background green value 
                                                 must be range from 0x00 to 0xFF. */

  uint32_t DMA2D_BGC_RED;                        /*!< Specifies the DMA2D background red value 
                                                 must be range from 0x00 to 0xFF. */
            
  uint32_t DMA2D_BGCMAR;                         /*!< Configures the DMA2D background CLUT memory address.
                                                 This parameter must range from 0x00000000 to 0xFFFFFFFF. */
} LL_DMA2D_LayerCfgTypeDef;



/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA2D_Exported_Constants
  * @{
  */  

/** @defgroup DMA2D_MODE 
  * @{
  */


#define LL_DMA2D_MODE_M2M                            ((uint32_t)0x00000000)
#define LL_DMA2D_MODE_M2M_PFC                        ((uint32_t)0x00010000)
#define LL_DMA2D_MODE_M2M_BLEND                      ((uint32_t)0x00020000)
#define LL_DMA2D_MODE_R2M                            ((uint32_t)0x00030000)

#define IS_DMA2D_MODE(MODE) (((MODE) == LL_DMA2D_MODE_M2M) || ((MODE) == LL_DMA2D_MODE_M2M_PFC) || \
                             ((MODE) == LL_DMA2D_MODE_M2M_BLEND) || ((MODE) == LL_DMA2D_MODE_R2M))


/**
  * @}
  */  

/** @defgroup DMA2D_CMODE 
  * @{
  */
#define LL_DMA2D_OUTPUT_MODE_ARGB8888                       ((uint32_t)0x00000000)
#define LL_DMA2D_OUTPUT_MODE_RGB888                         ((uint32_t)0x00000001)
#define LL_DMA2D_OUTPUT_MODE_RGB565                         ((uint32_t)0x00000002)
#define LL_DMA2D_OUTPUT_MODE_ARGB1555                       ((uint32_t)0x00000003)
#define LL_DMA2D_OUTPUT_MODE_ARGB4444                       ((uint32_t)0x00000004)

#define IS_DMA2D_CMODE(MODE_ARGB) (((MODE_ARGB) == LL_DMA2D_OUTPUT_MODE_ARGB8888) || ((MODE_ARGB) == LL_DMA2D_OUTPUT_MODE_RGB888) || \
                                   ((MODE_ARGB) == LL_DMA2D_OUTPUT_MODE_RGB565) || ((MODE_ARGB) == LL_DMA2D_OUTPUT_MODE_ARGB1555) || \
                                   ((MODE_ARGB) == LL_DMA2D_OUTPUT_MODE_ARGB4444))


/**
  * @}
  */  

/** @defgroup DMA2D_OUTPUT_COLOR 
  * @{
  */
#define DMA2D_Output_Color                 ((uint32_t)0x000000FF)

#define IS_DMA2D_OGREEN(OGREEN) ((OGREEN) <= DMA2D_Output_Color)
#define IS_DMA2D_ORED(ORED)     ((ORED) <= DMA2D_Output_Color)
#define IS_DMA2D_OBLUE(OBLUE)   ((OBLUE) <= DMA2D_Output_Color)
#define IS_DMA2D_OALPHA(OALPHA) ((OALPHA) <= DMA2D_Output_Color)

/**
  * @}
  */  

/** @defgroup DMA2D_OUTPUT_OFFSET 
  * @{
  */
#define DMA2D_OUTPUT_OFFSET      ((uint32_t)0x00003FFF)

#define IS_DMA2D_OUTPUT_OFFSET(OOFFSET) ((OOFFSET) <= DMA2D_OUTPUT_OFFSET)


/**
  * @}
  */  

/** @defgroup DMA2D_SIZE 
  * @{
  */

#define DMA2D_pixel          ((uint32_t)0x00003FFF)
#define DMA2D_Line           ((uint32_t)0x0000FFFF)

#define IS_DMA2D_LINE(LINE)  ((LINE) <= DMA2D_Line)
#define IS_DMA2D_PIXEL(PIXEL) ((PIXEL) <= DMA2D_pixel)


/**
  * @}
  */  

/** @defgroup DMA2D_OFFSET
  * @{
  */
#define OFFSET               ((uint32_t)0x00003FFF)

#define IS_DMA2D_FGO(FGO)  ((FGO) <= OFFSET)

#define IS_DMA2D_BGO(BGO)  ((BGO) <= OFFSET) 

/**
  * @}
  */  


/** @defgroup DMA2D_FGCM
  * @{
  */

#define LL_DMA2D_INPUT_MODE_ARGB8888        ((uint32_t)0x00000000)
#define LL_DMA2D_INPUT_MODE_RGB888          ((uint32_t)0x00000001)
#define LL_DMA2D_INPUT_MODE_RGB565          ((uint32_t)0x00000002)
#define LL_DMA2D_INPUT_MODE_ARGB1555        ((uint32_t)0x00000003)
#define LL_DMA2D_INPUT_MODE_ARGB4444        ((uint32_t)0x00000004)
#define LL_DMA2D_INPUT_MODE_L8              ((uint32_t)0x00000005)
#define LL_DMA2D_INPUT_MODE_AL44            ((uint32_t)0x00000006)
#define LL_DMA2D_INPUT_MODE_AL88            ((uint32_t)0x00000007)
#define LL_DMA2D_INPUT_MODE_L4              ((uint32_t)0x00000008)
#define LL_DMA2D_INPUT_MODE_A8              ((uint32_t)0x00000009)
#define LL_DMA2D_INPUT_MODE_A4              ((uint32_t)0x0000000A)

#define IS_DMA2D_FGCM(FGCM) (((FGCM) == LL_DMA2D_INPUT_MODE_ARGB8888) || ((FGCM) == LL_DMA2D_INPUT_MODE_RGB888) || \
                             ((FGCM) == LL_DMA2D_INPUT_MODE_RGB565) || ((FGCM) == LL_DMA2D_INPUT_MODE_ARGB1555) || \
                             ((FGCM) == LL_DMA2D_INPUT_MODE_ARGB4444) || ((FGCM) == LL_DMA2D_INPUT_MODE_L8) || \
                             ((FGCM) == LL_DMA2D_INPUT_MODE_AL44) || ((FGCM) == LL_DMA2D_INPUT_MODE_AL88) || \
                             ((FGCM) == LL_DMA2D_INPUT_MODE_L4) || ((FGCM) == LL_DMA2D_INPUT_MODE_A8) || \
                             ((FGCM) == LL_DMA2D_INPUT_MODE_A4))

#define IS_DMA2D_BGCM(BGCM) (((BGCM) == LL_DMA2D_INPUT_MODE_ARGB8888) || ((BGCM) == LL_DMA2D_INPUT_MODE_RGB888) || \
                             ((BGCM) == LL_DMA2D_INPUT_MODE_RGB565) || ((BGCM) == LL_DMA2D_INPUT_MODE_ARGB1555) || \
                             ((BGCM) == LL_DMA2D_INPUT_MODE_ARGB4444) || ((BGCM) == LL_DMA2D_INPUT_MODE_L8) || \
                             ((BGCM) == LL_DMA2D_INPUT_MODE_AL44) || ((BGCM) == LL_DMA2D_INPUT_MODE_AL88) || \
                             ((BGCM) == LL_DMA2D_INPUT_MODE_L4) || ((BGCM) == LL_DMA2D_INPUT_MODE_A8) || \
                             ((BGCM) == LL_DMA2D_INPUT_MODE_A4))

/**
  * @}
  */

/** @defgroup DMA2D_FG_CLUT_CM
  * @{
  */

#define LL_DMA2D_CLUT_COLOR_MODE_ARGB8888        ((uint32_t)0x00000000)
#define LL_DMA2D_CLUT_COLOR_MODE_RGB888          ((uint32_t)0x00000001)

#define IS_DMA2D_FG_CLUT_CM(FG_CLUT_CM) (((FG_CLUT_CM) == LL_DMA2D_CLUT_COLOR_MODE_ARGB8888) || ((FG_CLUT_CM) == LL_DMA2D_CLUT_COLOR_MODE_RGB888))

#define IS_DMA2D_BG_CLUT_CM(BG_CLUT_CM) (((BG_CLUT_CM) == LL_DMA2D_CLUT_COLOR_MODE_ARGB8888) || ((BG_CLUT_CM) == LL_DMA2D_CLUT_COLOR_MODE_RGB888))

/**
  * @}
  */

/** @defgroup DMA2D_FG_COLOR_VALUE
  * @{
  */

#define COLOR_VALUE             ((uint32_t)0x000000FF)

#define IS_DMA2D_FG_CLUT_SIZE(FG_CLUT_SIZE) ((FG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_FG_ALPHA_VALUE(FG_ALPHA_VALUE) ((FG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_BLUE(FGC_BLUE) ((FGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_GREEN(FGC_GREEN) ((FGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_FGC_RED(FGC_RED) ((FGC_RED) <= COLOR_VALUE)

#define IS_DMA2D_BG_CLUT_SIZE(BG_CLUT_SIZE) ((BG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_BG_ALPHA_VALUE(BG_ALPHA_VALUE) ((BG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_BLUE(BGC_BLUE) ((BGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_GREEN(BGC_GREEN) ((BGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_BGC_RED(BGC_RED) ((BGC_RED) <= COLOR_VALUE)

/**
  * @}
  */

/** DMA2D_FGPFC_ALPHA_MODE
  * @{
  */

#define LL_DMA2D_ALPHA_MODE_NO_MODIF       ((uint32_t)0x00000000)
#define LL_DMA2D_ALPHA_MODE_REPLACE        ((uint32_t)0x00000001)
#define LL_DMA2D_ALPHA_MODE_COMBINE        ((uint32_t)0x00000002)

#define IS_DMA2D_FG_ALPHA_MODE(FG_ALPHA_MODE) (((FG_ALPHA_MODE) ==  LL_DMA2D_ALPHA_MODE_NO_MODIF) || \
                                              ((FG_ALPHA_MODE) == LL_DMA2D_ALPHA_MODE_REPLACE) || \
                                              ((FG_ALPHA_MODE) == LL_DMA2D_ALPHA_MODE_COMBINE))

#define IS_DMA2D_BG_ALPHA_MODE(BG_ALPHA_MODE) (((BG_ALPHA_MODE) ==  LL_DMA2D_ALPHA_MODE_NO_MODIF) || \
                                              ((BG_ALPHA_MODE) == LL_DMA2D_ALPHA_MODE_REPLACE) || \
                                              ((BG_ALPHA_MODE) == LL_DMA2D_ALPHA_MODE_COMBINE))

/**
  * @}
  */

/** @defgroup DMA2D_Interrupts 
  * @{
  */

#define LL_DMA2D_IT_CEIE                      DMA2D_CR_CEIE
#define LL_DMA2D_IT_CTCIE                     DMA2D_CR_CTCIE
#define LL_DMA2D_IT_CAEIE                     DMA2D_CR_CAEIE
#define LL_DMA2D_IT_TWIE                      DMA2D_CR_TWIE
#define LL_DMA2D_IT_TCIE                      DMA2D_CR_TCIE
#define LL_DMA2D_IT_TEIE                      DMA2D_CR_TEIE

#define IS_DMA2D_IT(IT) (((IT) == LL_DMA2D_IT_CTCIE) || ((IT) == LL_DMA2D_IT_CAEIE) || \
                        ((IT) == LL_DMA2D_IT_TWIE) || ((IT) == LL_DMA2D_IT_TCIE) || \
                        ((IT) == LL_DMA2D_IT_TEIE) || ((IT) == LL_DMA2D_IT_CEIE))

/**
  * @}
  */
      
/** @defgroup DMA2D_Flag 
  * @{
  */

#define LL_DMA2D_FLAG_CEIF                      DMA2D_ISR_CEIF
#define LL_DMA2D_FLAG_CTCIF                     DMA2D_ISR_CTCIF
#define LL_DMA2D_FLAG_CAEIF                     DMA2D_ISR_CAEIF
#define LL_DMA2D_FLAG_TWIF                      DMA2D_ISR_TWIF
#define LL_DMA2D_FLAG_TCIF                      DMA2D_ISR_TCIF
#define LL_DMA2D_FLAG_TEIF                      DMA2D_ISR_TEIF


#define IS_DMA2D_GET_FLAG(FLAG) (((FLAG) == LL_DMA2D_FLAG_CTCIF) || ((FLAG) == LL_DMA2D_FLAG_CAEIF) || \
                                ((FLAG) == LL_DMA2D_FLAG_TWIF) || ((FLAG) == LL_DMA2D_FLAG_TCIF) || \
                                ((FLAG) == LL_DMA2D_FLAG_TEIF) || ((FLAG) == LL_DMA2D_FLAG_CEIF)) 


/**
  * @}
  */
      
/** @defgroup DMA2D_DeadTime 
  * @{
  */

#define DEADTIME                  ((uint32_t)0x000000FF)
  
#define IS_DMA2D_DEAD_TIME(DEAD_TIME) ((DEAD_TIME) <= DEADTIME)


#define LINE_WATERMARK            DMA2D_LWR_LW

#define IS_DMA2D_LineWatermark(LineWatermark) ((LineWatermark) <= LINE_WATERMARK)

/**
  * @}
  */
  
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the DMA2D configuration to the default reset state *****/
void LL_DMA2D_DeInit(DMA2D);

/* Initialization and Configuration functions *********************************/
void LL_DMA2D_Init(DMA2D, LL_DMA2D_InitTypeDef* DMA2D_InitStruct);
void LL_DMA2D_StructInit(LL_DMA2D_InitTypeDef* DMA2D_InitStruct);
void LL_DMA2D_Start(DMA2D);
void LL_DMA2D_Abort(DMA2D);
void DMA2D_Suspend(FunctionalState NewState);
void LL_DMA2D_ConfigLayer(DMA2D, LL_DMA2D_LayerCfgTypeDef* DMA2D_FG_InitStruct, 1);
void LL_DMA2D_LayerCfgStructInit(LL_DMA2D_LayerCfgTypeDef* DMA2D_FG_InitStruct);
void LL_DMA2D_ConfigLayer(DMA2D, LL_DMA2D_LayerCfgTypeDef* DMA2D_BG_InitStruct, 0);
void LL_DMA2D_LayerCfgStructInit(LL_DMA2D_LayerCfgTypeDef* DMA2D_BG_InitStruct);
void DMA2D_FGStart(FunctionalState NewState);
void DMA2D_BGStart(FunctionalState NewState);
void DMA2D_DeadTimeConfig(uint32_t DMA2D_DeadTime, FunctionalState NewState);
void LL_DMA2D_SetLineWatermark(DMA2D, uint32_t DMA2D_LWatermarkConfig);

/* Interrupts and flags management functions **********************************/
void DMA2D_ITConfig(uint32_t DMA2D_IT, FunctionalState NewState);
FlagStatus DMA2D_GetFlagStatus(uint32_t DMA2D_FLAG);
void DMA2D_ClearFlag(uint32_t DMA2D_FLAG);
ITStatus DMA2D_GetITStatus(uint32_t DMA2D_IT);
void DMA2D_ClearITPendingBit(uint32_t DMA2D_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_DMA2D_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
