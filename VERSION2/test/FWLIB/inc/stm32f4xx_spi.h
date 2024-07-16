/**
  ******************************************************************************
  * @file    stm32f4xx_spi.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the SPI 
  *          firmware library. 
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
#ifndef __STM32F4xx_SPI_H
#define __STM32F4xx_SPI_H

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

/** @addtogroup SPI
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
  uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}LL_SPI_InitTypeDef;

/** 
  * @brief  I2S Init structure definition  
  */

typedef struct
{

  uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of @ref I2S_Mode */

  uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of @ref I2S_Standard */

  uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref I2S_Data_Format */

  uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref I2S_MCLK_Output */

  uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of @ref I2S_Audio_Frequency */

  uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of @ref I2S_Clock_Polarity */
}LL_I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3) || \
                                   ((PERIPH) == SPI4) || \
                                   ((PERIPH) == SPI5) || \
                                   ((PERIPH) == SPI6))

#define IS_SPI_ALL_PERIPH_EXT(PERIPH) (((PERIPH) == SPI1)    || \
                                       ((PERIPH) == SPI2)    || \
                                       ((PERIPH) == SPI3)    || \
                                       ((PERIPH) == SPI4)    || \
                                       ((PERIPH) == SPI5)    || \
                                       ((PERIPH) == SPI6)    || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_SPI_23_PERIPH(PERIPH)  (((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))

#define IS_SPI_23_PERIPH_EXT(PERIPH)  (((PERIPH) == SPI2)    || \
                                       ((PERIPH) == SPI3)    || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_I2S_EXT_PERIPH(PERIPH)  (((PERIPH) == I2S2ext) || \
                                    ((PERIPH) == I2S3ext))


/** @defgroup SPI_data_direction 
  * @{
  */
  
#define LL_SPI_FULL_DUPLEX ((uint16_t)0x0000)
#define LL_SPI_SIMPLEX_RX     ((uint16_t)0x0400)
#define LL_SPI_HALF_DUPLEX_RX          ((uint16_t)0x8000)
#define LL_SPI_HALF_DUPLEX_TX          ((uint16_t)0xC000)
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == LL_SPI_FULL_DUPLEX) || \
                                     ((MODE) == LL_SPI_SIMPLEX_RX) || \
                                     ((MODE) == LL_SPI_HALF_DUPLEX_RX) || \
                                     ((MODE) == LL_SPI_HALF_DUPLEX_TX))
/**
  * @}
  */

/** @defgroup SPI_mode 
  * @{
  */

#define LL_SPI_MODE_MASTER                 ((uint16_t)0x0104)
#define LL_SPI_MODE_SLAVE                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == LL_SPI_MODE_MASTER) || \
                           ((MODE) == LL_SPI_MODE_SLAVE))
/**
  * @}
  */

/** @defgroup SPI_data_size 
  * @{
  */

#define LL_SPI_DATAWIDTH_16BIT                ((uint16_t)0x0800)
#define LL_SPI_DATAWIDTH_8BIT                 ((uint16_t)0x0000)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == LL_SPI_DATAWIDTH_16BIT) || \
                                   ((DATASIZE) == LL_SPI_DATAWIDTH_8BIT))
/**
  * @}
  */ 

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define LL_SPI_POLARITY_LOW                    ((uint16_t)0x0000)
#define LL_SPI_POLARITY_HIGH                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == LL_SPI_POLARITY_LOW) || \
                           ((CPOL) == LL_SPI_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define LL_SPI_PHASE_1EDGE                  ((uint16_t)0x0000)
#define LL_SPI_PHASE_2EDGE                  ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA) (((CPHA) == LL_SPI_PHASE_1EDGE) || \
                           ((CPHA) == LL_SPI_PHASE_2EDGE))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management 
  * @{
  */

#define LL_SPI_NSS_SOFT                    ((uint16_t)0x0200)
#define LL_SPI_NSS_HARD_INPUT                    ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == LL_SPI_NSS_SOFT) || \
                         ((NSS) == LL_SPI_NSS_HARD_INPUT))
/**
  * @}
  */ 

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */

#define LL_SPI_BAUDRATEPRESCALER_DIV2         ((uint16_t)0x0000)
#define LL_SPI_BAUDRATEPRESCALER_DIV4         ((uint16_t)0x0008)
#define LL_SPI_BAUDRATEPRESCALER_DIV8         ((uint16_t)0x0010)
#define LL_SPI_BAUDRATEPRESCALER_DIV16        ((uint16_t)0x0018)
#define LL_SPI_BAUDRATEPRESCALER_DIV32        ((uint16_t)0x0020)
#define LL_SPI_BAUDRATEPRESCALER_DIV64        ((uint16_t)0x0028)
#define LL_SPI_BAUDRATEPRESCALER_DIV128       ((uint16_t)0x0030)
#define LL_SPI_BAUDRATEPRESCALER_DIV256       ((uint16_t)0x0038)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV2) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV4) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV8) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV16) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV32) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV64) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV128) || \
                                              ((PRESCALER) == LL_SPI_BAUDRATEPRESCALER_DIV256))
/**
  * @}
  */ 

/** @defgroup SPI_MSB_LSB_transmission 
  * @{
  */

#define LL_SPI_MSB_FIRST                ((uint16_t)0x0000)
#define LL_SPI_LSB_FIRST                ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == LL_SPI_MSB_FIRST) || \
                               ((BIT) == LL_SPI_LSB_FIRST))
/**
  * @}
  */

/** @defgroup SPI_I2S_Mode 
  * @{
  */

#define LL_I2S_MODE_SLAVE_TX                ((uint16_t)0x0000)
#define LL_I2S_MODE_SLAVE_RX                ((uint16_t)0x0100)
#define LL_I2S_MODE_MASTER_TX               ((uint16_t)0x0200)
#define LL_I2S_MODE_MASTER_RX               ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE) (((MODE) == LL_I2S_MODE_SLAVE_TX) || \
                           ((MODE) == LL_I2S_MODE_SLAVE_RX) || \
                           ((MODE) == LL_I2S_MODE_MASTER_TX)|| \
                           ((MODE) == LL_I2S_MODE_MASTER_RX))
/**
  * @}
  */
  

/** @defgroup SPI_I2S_Standard 
  * @{
  */

#define LL_I2S_STANDARD_PHILIPS           ((uint16_t)0x0000)
#define LL_I2S_STANDARD_MSB                ((uint16_t)0x0010)
#define LL_I2S_STANDARD_LSB                ((uint16_t)0x0020)
#define LL_I2S_STANDARD_PCM_SHORT           ((uint16_t)0x0030)
#define LL_I2S_STANDARD_PCM_LONG            ((uint16_t)0x00B0)
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == LL_I2S_STANDARD_PHILIPS) || \
                                   ((STANDARD) == LL_I2S_STANDARD_MSB) || \
                                   ((STANDARD) == LL_I2S_STANDARD_LSB) || \
                                   ((STANDARD) == LL_I2S_STANDARD_PCM_SHORT) || \
                                   ((STANDARD) == LL_I2S_STANDARD_PCM_LONG))
/**
  * @}
  */
  
/** @defgroup SPI_I2S_Data_Format 
  * @{
  */

#define LL_I2S_DATAFORMAT_16B              ((uint16_t)0x0000)
#define LL_I2S_DATAFORMAT_16B_EXTENDED      ((uint16_t)0x0001)
#define LL_I2S_DATAFORMAT_24B              ((uint16_t)0x0003)
#define LL_I2S_DATAFORMAT_32B              ((uint16_t)0x0005)
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == LL_I2S_DATAFORMAT_16B) || \
                                    ((FORMAT) == LL_I2S_DATAFORMAT_16B_EXTENDED) || \
                                    ((FORMAT) == LL_I2S_DATAFORMAT_24B) || \
                                    ((FORMAT) == LL_I2S_DATAFORMAT_32B))
/**
  * @}
  */

/** @defgroup SPI_I2S_MCLK_Output 
  * @{
  */

#define LL_I2S_MCLK_OUTPUT_ENABLE           ((uint16_t)0x0200)
#define LL_I2S_MCLK_OUTPUT_DISABLE          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == LL_I2S_MCLK_OUTPUT_ENABLE) || \
                                    ((OUTPUT) == LL_I2S_MCLK_OUTPUT_DISABLE))
/**
  * @}
  */

/** @defgroup SPI_I2S_Audio_Frequency 
  * @{
  */

#define LL_I2S_AUDIOFREQ_192K               ((uint32_t)192000)
#define LL_I2S_AUDIOFREQ_96K                ((uint32_t)96000)
#define LL_I2S_AUDIOFREQ_48K                ((uint32_t)48000)
#define LL_I2S_AUDIOFREQ_44K                ((uint32_t)44100)
#define LL_I2S_AUDIOFREQ_32K                ((uint32_t)32000)
#define LL_I2S_AUDIOFREQ_22K                ((uint32_t)22050)
#define LL_I2S_AUDIOFREQ_16K                ((uint32_t)16000)
#define LL_I2S_AUDIOFREQ_11K                ((uint32_t)11025)
#define LL_I2S_AUDIOFREQ_8K                 ((uint32_t)8000)
#define LL_I2S_AUDIOFREQ_DEFAULT            ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= LL_I2S_AUDIOFREQ_8K) && \
                                 ((FREQ) <= LL_I2S_AUDIOFREQ_192K)) || \
                                 ((FREQ) == LL_I2S_AUDIOFREQ_DEFAULT))
/**
  * @}
  */
            
/** @defgroup SPI_I2S_Clock_Polarity 
  * @{
  */

#define LL_I2S_POLARITY_LOW                    ((uint16_t)0x0000)
#define LL_I2S_POLARITY_HIGH                   ((uint16_t)0x0008)
#define IS_I2S_CPOL(CPOL) (((CPOL) == LL_I2S_POLARITY_LOW) || \
                           ((CPOL) == LL_I2S_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup SPI_I2S_DMA_transfer_requests 
  * @{
  */

#define SPI_I2S_DMAReq_Tx               ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx               ((uint16_t)0x0001)
#define IS_SPI_I2S_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))
/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management 
  * @{
  */

#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))
/**
  * @}
  */

/** @defgroup SPI_CRC_Transmit_Receive 
  * @{
  */

#define SPI_CRC_Tx                      ((uint8_t)0x00)
#define SPI_CRC_Rx                      ((uint8_t)0x01)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))
/**
  * @}
  */

/** @defgroup SPI_direction_transmit_receive 
  * @{
  */

#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))
/**
  * @}
  */

/** @defgroup SPI_I2S_interrupts_definition 
  * @{
  */

#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)
#define I2S_IT_UDR                      ((uint8_t)0x53)
#define SPI_I2S_IT_TIFRFE               ((uint8_t)0x58)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                  ((IT) == SPI_I2S_IT_RXNE) || \
                                  ((IT) == SPI_I2S_IT_ERR))

#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_IT_CRCERR                   ((uint8_t)0x54)

#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))

#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE)|| ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == SPI_IT_CRCERR)  || ((IT) == SPI_IT_MODF) || \
                               ((IT) == SPI_I2S_IT_OVR) || ((IT) == I2S_IT_UDR) ||\
                               ((IT) == SPI_I2S_IT_TIFRFE))
/**
  * @}
  */

/** @defgroup SPI_I2S_flags_definition 
  * @{
  */

#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                 ((uint16_t)0x0004)
#define I2S_FLAG_UDR                    ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                ((uint16_t)0x0080)
#define SPI_I2S_FLAG_TIFRFE             ((uint16_t)0x0100)

#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
                                   ((FLAG) == SPI_I2S_FLAG_TIFRFE))
/**
  * @}
  */

/** @defgroup SPI_CRC_polynomial 
  * @{
  */

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)
/**
  * @}
  */

/** @defgroup SPI_I2S_Legacy 
  * @{
  */

#define SPI_DMAReq_Tx                SPI_I2S_DMAReq_Tx
#define SPI_DMAReq_Rx                SPI_I2S_DMAReq_Rx
#define SPI_IT_TXE                   SPI_I2S_IT_TXE
#define SPI_IT_RXNE                  SPI_I2S_IT_RXNE
#define SPI_IT_ERR                   SPI_I2S_IT_ERR
#define SPI_IT_OVR                   SPI_I2S_IT_OVR
#define SPI_FLAG_RXNE                SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE                 SPI_I2S_FLAG_TXE
#define SPI_FLAG_OVR                 SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY                 SPI_I2S_FLAG_BSY
#define SPI_DeInit                   SPI_I2S_DeInit
#define SPI_ITConfig                 SPI_I2S_ITConfig
#define SPI_DMACmd                   SPI_I2S_DMACmd
#define SPI_SendData                 SPI_I2S_SendData
#define SPI_ReceiveData              SPI_I2S_ReceiveData
#define SPI_GetFlagStatus            SPI_I2S_GetFlagStatus
#define SPI_ClearFlag                SPI_I2S_ClearFlag
#define SPI_GetITStatus              SPI_I2S_GetITStatus
#define SPI_ClearITPendingBit        SPI_I2S_ClearITPendingBit
/**
  * @}
  */
  
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the SPI configuration to the default reset state *****/ 
void LL_SPI_DeInit(SPI_TypeDef* SPIx);

/* Initialization and Configuration functions *********************************/
void LL_SPI_Init(SPI_TypeDef* SPIx, LL_SPI_InitTypeDef* SPI_InitStruct);
void LL_I2S_Init(SPI_TypeDef* SPIx, LL_I2S_InitTypeDef* I2S_InitStruct);
void LL_SPI_StructInit(LL_SPI_InitTypeDef* SPI_InitStruct);
void LL_I2S_StructInit(LL_I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void LL_SPI_SetDataWidth(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

void LL_I2S_InitFullDuplex(SPI_TypeDef* I2Sxext, LL_I2S_InitTypeDef* I2S_InitStruct);

/* Data transfers functions ***************************************************/ 
void LL_SPI_TransmitData16(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t LL_SPI_ReceiveData16(SPI_TypeDef* SPIx);

/* Hardware CRC Calculation functions *****************************************/
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void LL_SPI_SetCRCNext(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t LL_SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

/* DMA transfers management functions *****************************************/
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
