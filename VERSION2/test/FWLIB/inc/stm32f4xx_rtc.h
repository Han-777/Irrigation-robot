/**
  ******************************************************************************
  * @file    stm32f4xx_rtc.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains all the functions prototypes for the RTC firmware
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
#ifndef __STM32F4xx_RTC_H
#define __STM32F4xx_RTC_H

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

/** @addtogroup RTC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  RTC Init structures definition  
  */ 
typedef struct
{
  uint32_t RTC_HourFormat;   /*!< Specifies the RTC Hour Format.
                             This parameter can be a value of @ref RTC_Hour_Formats */
  
  uint32_t RTC_AsynchPrediv; /*!< Specifies the RTC Asynchronous Predivider value.
                             This parameter must be set to a value lower than 0x7F */
  
  uint32_t RTC_SynchPrediv;  /*!< Specifies the RTC Synchronous Predivider value.
                             This parameter must be set to a value lower than 0x7FFF */
}LL_RTC_InitTypeDef;

/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint8_t RTC_Hours;    /*!< Specifies the RTC Time Hour.
                        This parameter must be set to a value in the 0-12 range
                        if the LL_RTC_HOURFORMAT_AMPM is selected or 0-23 range if
                        the LL_RTC_HOURFORMAT_24HOUR is selected. */

  uint8_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes.
                        This parameter must be set to a value in the 0-59 range. */
  
  uint8_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds.
                        This parameter must be set to a value in the 0-59 range. */

  uint8_t RTC_H12;      /*!< Specifies the RTC AM/PM Time.
                        This parameter can be a value of @ref RTC_AM_PM_Definitions */
}LL_RTC_TimeTypeDef; 

/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay.
                        This parameter can be a value of @ref RTC_WeekDay_Definitions */
  
  uint8_t RTC_Month;   /*!< Specifies the RTC Date Month (in BCD format).
                        This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t RTC_Date;     /*!< Specifies the RTC Date.
                        This parameter must be set to a value in the 1-31 range. */
  
  uint8_t RTC_Year;     /*!< Specifies the RTC Date Year.
                        This parameter must be set to a value in the 0-99 range. */
}LL_RTC_DateTypeDef;

/** 
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
  LL_RTC_TimeTypeDef RTC_AlarmTime;     /*!< Specifies the RTC Alarm Time members. */

  uint32_t RTC_AlarmMask;            /*!< Specifies the RTC Alarm Masks.
                                     This parameter can be a value of @ref RTC_AlarmMask_Definitions */

  uint32_t RTC_AlarmDateWeekDaySel;  /*!< Specifies the RTC Alarm is on Date or WeekDay.
                                     This parameter can be a value of @ref RTC_AlarmDateWeekDay_Definitions */
  
  uint8_t RTC_AlarmDateWeekDay;      /*!< Specifies the RTC Alarm Date/WeekDay.
                                     If the Alarm Date is selected, this parameter
                                     must be set to a value in the 1-31 range.
                                     If the Alarm WeekDay is selected, this 
                                     parameter can be a value of @ref RTC_WeekDay_Definitions */
}LL_RTC_AlarmTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */ 


/** @defgroup RTC_Hour_Formats 
  * @{
  */ 
#define LL_RTC_HOURFORMAT_24HOUR              ((uint32_t)0x00000000)
#define LL_RTC_HOURFORMAT_AMPM              ((uint32_t)0x00000040)
#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == LL_RTC_HOURFORMAT_AMPM) || \
                                        ((FORMAT) == LL_RTC_HOURFORMAT_24HOUR))
/**
  * @}
  */ 

/** @defgroup RTC_Asynchronous_Predivider 
  * @{
  */ 
#define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= 0x7F)
 
/**
  * @}
  */ 


/** @defgroup RTC_Synchronous_Predivider 
  * @{
  */ 
#define IS_RTC_SYNCH_PREDIV(PREDIV)    ((PREDIV) <= 0x7FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Time_Definitions 
  * @{
  */ 
#define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)

/**
  * @}
  */ 

/** @defgroup RTC_AM_PM_Definitions 
  * @{
  */ 
#define LL_RTC_TIME_FORMAT_AM_OR_24                     ((uint8_t)0x00)
#define LL_RTC_TIME_FORMAT_PM                     ((uint8_t)0x40)
#define IS_RTC_H12(PM) (((PM) == LL_RTC_TIME_FORMAT_AM_OR_24) || ((PM) == LL_RTC_TIME_FORMAT_PM))

/**
  * @}
  */ 

/** @defgroup RTC_Year_Date_Definitions 
  * @{
  */ 
#define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)

/**
  * @}
  */ 

/** @defgroup RTC_Month_Date_Definitions 
  * @{
  */ 

/* Coded in BCD format */
#define LL_RTC_MONTH_JANUARY              ((uint8_t)0x01)
#define LL_RTC_MONTH_FEBRUARY             ((uint8_t)0x02)
#define LL_RTC_MONTH_MARCH                ((uint8_t)0x03)
#define LL_RTC_MONTH_APRIL                ((uint8_t)0x04)
#define LL_RTC_MONTH_MAY                  ((uint8_t)0x05)
#define LL_RTC_MONTH_JUNE                 ((uint8_t)0x06)
#define LL_RTC_MONTH_JULY                 ((uint8_t)0x07)
#define LL_RTC_MONTH_AUGUST               ((uint8_t)0x08)
#define LL_RTC_MONTH_SEPTEMBER            ((uint8_t)0x09)
#define LL_RTC_MONTH_OCTOBER              ((uint8_t)0x10)
#define LL_RTC_MONTH_NOVEMBER             ((uint8_t)0x11)
#define LL_RTC_MONTH_DECEMBER             ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))

/**
  * @}
  */ 

/** @defgroup RTC_WeekDay_Definitions 
  * @{
  */ 
  
#define LL_RTC_WEEKDAY_MONDAY             ((uint8_t)0x01)
#define LL_RTC_WEEKDAY_TUESDAY            ((uint8_t)0x02)
#define LL_RTC_WEEKDAY_WEDNESDAY          ((uint8_t)0x03)
#define LL_RTC_WEEKDAY_THURSDAY           ((uint8_t)0x04)
#define LL_RTC_WEEKDAY_FRIDAY             ((uint8_t)0x05)
#define LL_RTC_WEEKDAY_SATURDAY           ((uint8_t)0x06)
#define LL_RTC_WEEKDAY_SUNDAY             ((uint8_t)0x07)
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == LL_RTC_WEEKDAY_MONDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_TUESDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_WEDNESDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_THURSDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_FRIDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_SATURDAY) || \
                                 ((WEEKDAY) == LL_RTC_WEEKDAY_SUNDAY))
/**
  * @}
  */ 


/** @defgroup RTC_Alarm_Definitions
  * @{
  */ 
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == LL_RTC_WEEKDAY_MONDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_TUESDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_WEDNESDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_THURSDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_FRIDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_SATURDAY) || \
                                                    ((WEEKDAY) == LL_RTC_WEEKDAY_SUNDAY))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmDateWeekDay_Definitions 
  * @{
  */ 
#define LL_RTC_ALMA_DATEWEEKDAYSEL_DATE      ((uint32_t)0x00000000)
#define LL_RTC_ALMA_DATEWEEKDAYSEL_WEEKDAY   ((uint32_t)0x40000000)

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == LL_RTC_ALMA_DATEWEEKDAYSEL_DATE) || \
                                            ((SEL) == LL_RTC_ALMA_DATEWEEKDAYSEL_WEEKDAY))

/**
  * @}
  */ 


/** @defgroup RTC_AlarmMask_Definitions 
  * @{
  */ 
#define LL_RTC_ALMA_MASK_NONE                ((uint32_t)0x00000000)
#define LL_RTC_ALMA_MASK_DATEWEEKDAY         ((uint32_t)0x80000000)
#define LL_RTC_ALMA_MASK_HOURS               ((uint32_t)0x00800000)
#define LL_RTC_ALMA_MASK_MINUTES             ((uint32_t)0x00008000)
#define LL_RTC_ALMA_MASK_SECONDS             ((uint32_t)0x00000080)
#define LL_RTC_ALMA_MASK_ALL                 ((uint32_t)0x80808080)
#define IS_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)

/**
  * @}
  */ 

/** @defgroup RTC_Alarms_Definitions 
  * @{
  */ 
#define RTC_Alarm_A                       ((uint32_t)0x00000100)
#define RTC_Alarm_B                       ((uint32_t)0x00000200)
#define IS_RTC_ALARM(ALARM)     (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
#define IS_RTC_CMD_ALARM(ALARM) (((ALARM) & (RTC_Alarm_A | RTC_Alarm_B)) != (uint32_t)RESET)

/**
  * @}
  */ 

  /** @defgroup RTC_Alarm_Sub_Seconds_Masks_Definitions
  * @{
  */ 
#define 15         ((uint32_t)0x00000000) /*!< All Alarm SS fields are masked. 
                                                                       There is no comparison on sub seconds 
                                                                       for Alarm */
#define 1      ((uint32_t)0x01000000) /*!< SS[14:1] are don't care in Alarm 
                                                                       comparison. Only SS[0] is compared. */
#define 2      ((uint32_t)0x02000000) /*!< SS[14:2] are don't care in Alarm 
                                                                       comparison. Only SS[1:0] are compared */
#define 3      ((uint32_t)0x03000000) /*!< SS[14:3] are don't care in Alarm 
                                                                       comparison. Only SS[2:0] are compared */
#define 4      ((uint32_t)0x04000000) /*!< SS[14:4] are don't care in Alarm 
                                                                       comparison. Only SS[3:0] are compared */
#define 5      ((uint32_t)0x05000000) /*!< SS[14:5] are don't care in Alarm 
                                                                       comparison. Only SS[4:0] are compared */
#define 6      ((uint32_t)0x06000000) /*!< SS[14:6] are don't care in Alarm 
                                                                       comparison. Only SS[5:0] are compared */
#define 7      ((uint32_t)0x07000000) /*!< SS[14:7] are don't care in Alarm 
                                                                       comparison. Only SS[6:0] are compared */
#define 8      ((uint32_t)0x08000000) /*!< SS[14:8] are don't care in Alarm 
                                                                       comparison. Only SS[7:0] are compared */
#define 9      ((uint32_t)0x09000000) /*!< SS[14:9] are don't care in Alarm 
                                                                       comparison. Only SS[8:0] are compared */
#define 10     ((uint32_t)0x0A000000) /*!< SS[14:10] are don't care in Alarm 
                                                                       comparison. Only SS[9:0] are compared */
#define 11     ((uint32_t)0x0B000000) /*!< SS[14:11] are don't care in Alarm 
                                                                       comparison. Only SS[10:0] are compared */
#define 12     ((uint32_t)0x0C000000) /*!< SS[14:12] are don't care in Alarm 
                                                                       comparison.Only SS[11:0] are compared */
#define 13     ((uint32_t)0x0D000000) /*!< SS[14:13] are don't care in Alarm 
                                                                       comparison. Only SS[12:0] are compared */
#define 14        ((uint32_t)0x0E000000) /*!< SS[14] is don't care in Alarm 
                                                                       comparison.Only SS[13:0] are compared */
#define 0        ((uint32_t)0x0F000000) /*!< SS[14:0] are compared and must match 
                                                                       to activate alarm. */
#define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == 15) || \
                                              ((MASK) == 1) || \
                                              ((MASK) == 2) || \
                                              ((MASK) == 3) || \
                                              ((MASK) == 4) || \
                                              ((MASK) == 5) || \
                                              ((MASK) == 6) || \
                                              ((MASK) == 7) || \
                                              ((MASK) == 8) || \
                                              ((MASK) == 9) || \
                                              ((MASK) == 10) || \
                                              ((MASK) == 11) || \
                                              ((MASK) == 12) || \
                                              ((MASK) == 13) || \
                                              ((MASK) == 14) || \
                                              ((MASK) == 0))
/**
  * @}
  */ 

/** @defgroup RTC_Alarm_Sub_Seconds_Value
  * @{
  */ 

#define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)

/**
  * @}
  */ 

/** @defgroup RTC_Wakeup_Timer_Definitions 
  * @{
  */ 
#define LL_RTC_WAKEUPCLOCK_DIV_16        ((uint32_t)0x00000000)
#define LL_RTC_WAKEUPCLOCK_DIV_8         ((uint32_t)0x00000001)
#define LL_RTC_WAKEUPCLOCK_DIV_4         ((uint32_t)0x00000002)
#define LL_RTC_WAKEUPCLOCK_DIV_2         ((uint32_t)0x00000003)
#define LL_RTC_WAKEUPCLOCK_CKSPRE      ((uint32_t)0x00000004)
#define LL_RTC_WAKEUPCLOCK_CKSPRE_WUT      ((uint32_t)0x00000006)
#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == LL_RTC_WAKEUPCLOCK_DIV_16) || \
                                    ((CLOCK) == LL_RTC_WAKEUPCLOCK_DIV_8) || \
                                    ((CLOCK) == LL_RTC_WAKEUPCLOCK_DIV_4) || \
                                    ((CLOCK) == LL_RTC_WAKEUPCLOCK_DIV_2) || \
                                    ((CLOCK) == LL_RTC_WAKEUPCLOCK_CKSPRE) || \
                                    ((CLOCK) == LL_RTC_WAKEUPCLOCK_CKSPRE_WUT))
#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)
/**
  * @}
  */ 

/** @defgroup RTC_Time_Stamp_Edges_definitions 
  * @{
  */ 
#define LL_RTC_TIMESTAMP_EDGE_RISING          ((uint32_t)0x00000000)
#define LL_RTC_TIMESTAMP_EDGE_FALLING         ((uint32_t)0x00000008)
#define IS_RTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == LL_RTC_TIMESTAMP_EDGE_RISING) || \
                                     ((EDGE) == LL_RTC_TIMESTAMP_EDGE_FALLING))
/**
  * @}
  */ 

/** @defgroup RTC_Output_selection_Definitions 
  * @{
  */ 
#define LL_RTC_ALARMOUT_DISABLE             ((uint32_t)0x00000000)
#define LL_RTC_ALARMOUT_ALMA              ((uint32_t)0x00200000)
#define LL_RTC_ALARMOUT_ALMB              ((uint32_t)0x00400000)
#define LL_RTC_ALARMOUT_WAKEUP              ((uint32_t)0x00600000)
 
#define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == LL_RTC_ALARMOUT_DISABLE) || \
                               ((OUTPUT) == LL_RTC_ALARMOUT_ALMA) || \
                               ((OUTPUT) == LL_RTC_ALARMOUT_ALMB) || \
                               ((OUTPUT) == LL_RTC_ALARMOUT_WAKEUP))

/**
  * @}
  */ 

/** @defgroup RTC_Output_Polarity_Definitions 
  * @{
  */ 
#define LL_RTC_OUTPUTPOLARITY_PIN_HIGH           ((uint32_t)0x00000000)
#define LL_RTC_OUTPUTPOLARITY_PIN_LOW            ((uint32_t)0x00100000)
#define IS_RTC_OUTPUT_POL(POL) (((POL) == LL_RTC_OUTPUTPOLARITY_PIN_HIGH) || \
                                ((POL) == LL_RTC_OUTPUTPOLARITY_PIN_LOW))
/**
  * @}
  */ 


/** @defgroup RTC_Digital_Calibration_Definitions 
  * @{
  */ 
#define LL_RTC_CALIB_SIGN_POSITIVE            ((uint32_t)0x00000000) 
#define LL_RTC_CALIB_SIGN_NEGATIVE            ((uint32_t)0x00000080)
#define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == LL_RTC_CALIB_SIGN_POSITIVE) || \
                                 ((SIGN) == LL_RTC_CALIB_SIGN_NEGATIVE))
#define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20)

/**
  * @}
  */ 

 /** @defgroup RTC_Calib_Output_selection_Definitions 
  * @{
  */ 
#define LL_RTC_CALIB_OUTPUT_512HZ            ((uint32_t)0x00000000) 
#define LL_RTC_CALIB_OUTPUT_1HZ              ((uint32_t)0x00080000)
#define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == LL_RTC_CALIB_OUTPUT_512HZ) || \
                                      ((OUTPUT) == LL_RTC_CALIB_OUTPUT_1HZ))
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_period_Definitions 
  * @{
  */ 
#define LL_RTC_CALIB_PERIOD_32SEC   ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation
                                                             period is 32s,  else 2exp20 RTCCLK seconds */
#define LL_RTC_CALIB_PERIOD_16SEC   ((uint32_t)0x00002000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 16s, else 2exp19 RTCCLK seconds */
#define LL_RTC_CALIB_PERIOD_8SEC    ((uint32_t)0x00004000) /*!<  if RTCCLK = 32768 Hz, Smooth calibation 
                                                             period is 8s, else 2exp18 RTCCLK seconds */
#define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == LL_RTC_CALIB_PERIOD_32SEC) || \
                                             ((PERIOD) == LL_RTC_CALIB_PERIOD_16SEC) || \
                                             ((PERIOD) == LL_RTC_CALIB_PERIOD_8SEC))
                                          
/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions 
  * @{
  */ 
#define LL_RTC_CALIB_INSERTPULSE_SET    ((uint32_t)0x00008000) /*!<  The number of RTCCLK pulses added  
                                                                during a X -second window = Y - CALM[8:0]. 
                                                                 with Y = 512, 256, 128 when X = 32, 16, 8 */
#define LL_RTC_CALIB_INSERTPULSE_NONE  ((uint32_t)0x00000000) /*!<  The number of RTCCLK pulses subbstited
                                                                 during a 32-second window =   CALM[8:0]. */
#define IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == LL_RTC_CALIB_INSERTPULSE_SET) || \
                                         ((PLUS) == LL_RTC_CALIB_INSERTPULSE_NONE))

/**
  * @}
  */ 

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions 
  * @{
  */ 
#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000001FF)

/**
  * @}
  */

/** @defgroup RTC_DayLightSaving_Definitions 
  * @{
  */ 
#define RTC_DayLightSaving_SUB1H   ((uint32_t)0x00020000)
#define RTC_DayLightSaving_ADD1H   ((uint32_t)0x00010000)
#define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == RTC_DayLightSaving_SUB1H) || \
                                      ((SAVE) == RTC_DayLightSaving_ADD1H))

#define RTC_StoreOperation_Reset        ((uint32_t)0x00000000)
#define RTC_StoreOperation_Set          ((uint32_t)0x00040000)
#define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_StoreOperation_Reset) || \
                                           ((OPERATION) == RTC_StoreOperation_Set))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Trigger_Definitions 
  * @{
  */ 
#define RTC_TamperTrigger_RisingEdge            ((uint32_t)0x00000000)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000001)
#define RTC_TamperTrigger_LowLevel              ((uint32_t)0x00000000)
#define RTC_TamperTrigger_HighLevel             ((uint32_t)0x00000001)
#define IS_RTC_TAMPER_TRIGGER(TRIGGER) (((TRIGGER) == RTC_TamperTrigger_RisingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_FallingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_LowLevel) || \
                                        ((TRIGGER) == RTC_TamperTrigger_HighLevel)) 

/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Filter_Definitions 
  * @{
  */ 
#define LL_RTC_TAMPER_FILTER_DISABLE   ((uint32_t)0x00000000) /*!< Tamper filter is disabled */

#define LL_RTC_TAMPER_FILTER_2SAMPLE   ((uint32_t)0x00000800) /*!< Tamper is activated after 2 
                                                          consecutive samples at the active level */
#define LL_RTC_TAMPER_FILTER_4SAMPLE   ((uint32_t)0x00001000) /*!< Tamper is activated after 4 
                                                          consecutive samples at the active level */
#define LL_RTC_TAMPER_FILTER_8SAMPLE   ((uint32_t)0x00001800) /*!< Tamper is activated after 8 
                                                          consecutive samples at the active leve. */
#define IS_RTC_TAMPER_FILTER(FILTER) (((FILTER) == LL_RTC_TAMPER_FILTER_DISABLE) || \
                                      ((FILTER) == LL_RTC_TAMPER_FILTER_2SAMPLE) || \
                                      ((FILTER) == LL_RTC_TAMPER_FILTER_4SAMPLE) || \
                                      ((FILTER) == LL_RTC_TAMPER_FILTER_8SAMPLE))
/**
  * @}
  */ 

/** @defgroup RTC_Tamper_Sampling_Frequencies_Definitions 
  * @{
  */ 
#define LL_RTC_TAMPER_SAMPLFREQDIV_32768  ((uint32_t)0x00000000) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 32768 */
#define LL_RTC_TAMPER_SAMPLFREQDIV_16384  ((uint32_t)0x000000100) /*!< Each of the tamper inputs are sampled
                                                                            with a frequency =  RTCCLK / 16384 */
#define LL_RTC_TAMPER_SAMPLFREQDIV_8192   ((uint32_t)0x00000200) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 8192  */
#define LL_RTC_TAMPER_SAMPLFREQDIV_4096   ((uint32_t)0x00000300) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 4096  */
#define LL_RTC_TAMPER_SAMPLFREQDIV_2048   ((uint32_t)0x00000400) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 2048  */
#define LL_RTC_TAMPER_SAMPLFREQDIV_1024   ((uint32_t)0x00000500) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 1024  */
#define LL_RTC_TAMPER_SAMPLFREQDIV_512    ((uint32_t)0x00000600) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 512   */
#define LL_RTC_TAMPER_SAMPLFREQDIV_256    ((uint32_t)0x00000700) /*!< Each of the tamper inputs are sampled
                                                                           with a frequency =  RTCCLK / 256   */
#define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_32768) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_16384) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_8192) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_4096) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_2048) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_1024) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_512) || \
                                           ((FREQ) ==LL_RTC_TAMPER_SAMPLFREQDIV_256))

/**
  * @}
  */

  /** @defgroup RTC_Tamper_Pin_Precharge_Duration_Definitions 
  * @{
  */ 
#define LL_RTC_TAMPER_DURATION_1RTCCLK ((uint32_t)0x00000000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 1 RTCCLK cycle */
#define LL_RTC_TAMPER_DURATION_2RTCCLK ((uint32_t)0x00002000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 2 RTCCLK cycles */
#define LL_RTC_TAMPER_DURATION_4RTCCLK ((uint32_t)0x00004000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 4 RTCCLK cycles */
#define LL_RTC_TAMPER_DURATION_8RTCCLK ((uint32_t)0x00006000)  /*!< Tamper pins are pre-charged before 
                                                                         sampling during 8 RTCCLK cycles */

#define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == LL_RTC_TAMPER_DURATION_1RTCCLK) || \
                                                    ((DURATION) == LL_RTC_TAMPER_DURATION_2RTCCLK) || \
                                                    ((DURATION) == LL_RTC_TAMPER_DURATION_4RTCCLK) || \
                                                    ((DURATION) == LL_RTC_TAMPER_DURATION_8RTCCLK))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pins_Definitions 
  * @{
  */ 
#define LL_RTC_TAMPER_1                    RTC_TAFCR_TAMP1E
#define IS_RTC_TAMPER(TAMPER) (((TAMPER) == LL_RTC_TAMPER_1))

/**
  * @}
  */

/** @defgroup RTC_Tamper_Pin_Selection 
  * @{
  */ 
#define RTC_TamperPin_PC13                 ((uint32_t)0x00000000)
#define RTC_TamperPin_PI8                  ((uint32_t)0x00010000)
#define IS_RTC_TAMPER_PIN(PIN) (((PIN) == RTC_TamperPin_PC13) || \
                                ((PIN) == RTC_TamperPin_PI8))
/**
  * @}
  */ 

/** @defgroup RTC_TimeStamp_Pin_Selection 
  * @{
  */ 
#define LL_RTC_TimeStampPin_Default              ((uint32_t)0x00000000)
#define LL_RTC_TimeStampPin_Pos1               ((uint32_t)0x00020000)
#define IS_RTC_TIMESTAMP_PIN(PIN) (((PIN) == LL_RTC_TimeStampPin_Default) || \
                                   ((PIN) == LL_RTC_TimeStampPin_Pos1))
/**
  * @}
  */ 

/** @defgroup RTC_Output_Type_ALARM_OUT 
  * @{
  */ 
#define LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN           ((uint32_t)0x00000000)
#define LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL            ((uint32_t)0x00040000)
#define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == LL_RTC_ALARM_OUTPUTTYPE_OPENDRAIN) || \
                                  ((TYPE) == LL_RTC_ALARM_OUTPUTTYPE_PUSHPULL))

/**
  * @}
  */ 

/** @defgroup RTC_Add_1_Second_Parameter_Definitions
  * @{
  */ 
#define LL_RTC_SHIFT_SECOND_DELAY      ((uint32_t)0x00000000)
#define LL_RTC_SHIFT_SECOND_ADVANCE        ((uint32_t)0x80000000)
#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == LL_RTC_SHIFT_SECOND_DELAY) || \
                                 ((SEL) == LL_RTC_SHIFT_SECOND_ADVANCE))
/**
  * @}
  */ 

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */ 
#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)

/**
  * @}
  */

/** @defgroup RTC_Backup_Registers_Definitions 
  * @{
  */

#define LL_RTC_BKP_DR0                       ((uint32_t)0x00000000)
#define LL_RTC_BKP_DR1                       ((uint32_t)0x00000001)
#define LL_RTC_BKP_DR2                       ((uint32_t)0x00000002)
#define LL_RTC_BKP_DR3                       ((uint32_t)0x00000003)
#define LL_RTC_BKP_DR4                       ((uint32_t)0x00000004)
#define LL_RTC_BKP_DR5                       ((uint32_t)0x00000005)
#define LL_RTC_BKP_DR6                       ((uint32_t)0x00000006)
#define LL_RTC_BKP_DR7                       ((uint32_t)0x00000007)
#define LL_RTC_BKP_DR8                       ((uint32_t)0x00000008)
#define LL_RTC_BKP_DR9                       ((uint32_t)0x00000009)
#define LL_RTC_BKP_DR10                      ((uint32_t)0x0000000A)
#define LL_RTC_BKP_DR11                      ((uint32_t)0x0000000B)
#define LL_RTC_BKP_DR12                      ((uint32_t)0x0000000C)
#define LL_RTC_BKP_DR13                      ((uint32_t)0x0000000D)
#define LL_RTC_BKP_DR14                      ((uint32_t)0x0000000E)
#define LL_RTC_BKP_DR15                      ((uint32_t)0x0000000F)
#define LL_RTC_BKP_DR16                      ((uint32_t)0x00000010)
#define LL_RTC_BKP_DR17                      ((uint32_t)0x00000011)
#define LL_RTC_BKP_DR18                      ((uint32_t)0x00000012)
#define LL_RTC_BKP_DR19                      ((uint32_t)0x00000013)
#define IS_RTC_BKP(BKP)                   (((BKP) == LL_RTC_BKP_DR0) || \
                                           ((BKP) == LL_RTC_BKP_DR1) || \
                                           ((BKP) == LL_RTC_BKP_DR2) || \
                                           ((BKP) == LL_RTC_BKP_DR3) || \
                                           ((BKP) == LL_RTC_BKP_DR4) || \
                                           ((BKP) == LL_RTC_BKP_DR5) || \
                                           ((BKP) == LL_RTC_BKP_DR6) || \
                                           ((BKP) == LL_RTC_BKP_DR7) || \
                                           ((BKP) == LL_RTC_BKP_DR8) || \
                                           ((BKP) == LL_RTC_BKP_DR9) || \
                                           ((BKP) == LL_RTC_BKP_DR10) || \
                                           ((BKP) == LL_RTC_BKP_DR11) || \
                                           ((BKP) == LL_RTC_BKP_DR12) || \
                                           ((BKP) == LL_RTC_BKP_DR13) || \
                                           ((BKP) == LL_RTC_BKP_DR14) || \
                                           ((BKP) == LL_RTC_BKP_DR15) || \
                                           ((BKP) == LL_RTC_BKP_DR16) || \
                                           ((BKP) == LL_RTC_BKP_DR17) || \
                                           ((BKP) == LL_RTC_BKP_DR18) || \
                                           ((BKP) == LL_RTC_BKP_DR19))
/**
  * @}
  */ 

/** @defgroup RTC_Input_parameter_format_definitions 
  * @{
  */ 
#define LL_RTC_FORMAT_BIN                    ((uint32_t)0x000000000)
#define LL_RTC_FORMAT_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == LL_RTC_FORMAT_BIN) || ((FORMAT) == LL_RTC_FORMAT_BCD))

/**
  * @}
  */ 

/** @defgroup RTC_Flags_Definitions 
  * @{
  */ 
#define RTC_FLAG_RECALPF                  ((uint32_t)0x00010000)
#define RTC_FLAG_TAMP1F                   ((uint32_t)0x00002000)
#define RTC_FLAG_TSOVF                    ((uint32_t)0x00001000)
#define RTC_FLAG_TSF                      ((uint32_t)0x00000800)
#define RTC_FLAG_WUTF                     ((uint32_t)0x00000400)
#define RTC_FLAG_ALRBF                    ((uint32_t)0x00000200)
#define RTC_FLAG_ALRAF                    ((uint32_t)0x00000100)
#define RTC_FLAG_INITF                    ((uint32_t)0x00000040)
#define RTC_FLAG_RSF                      ((uint32_t)0x00000020)
#define RTC_FLAG_INITS                    ((uint32_t)0x00000010)
#define RTC_FLAG_SHPF                     ((uint32_t)0x00000008)
#define RTC_FLAG_WUTWF                    ((uint32_t)0x00000004)
#define RTC_FLAG_ALRBWF                   ((uint32_t)0x00000002)
#define RTC_FLAG_ALRAWF                   ((uint32_t)0x00000001)
#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_TSOVF) || ((FLAG) == RTC_FLAG_TSF) || \
                               ((FLAG) == RTC_FLAG_WUTF) || ((FLAG) == RTC_FLAG_ALRBF) || \
                               ((FLAG) == RTC_FLAG_ALRAF) || ((FLAG) == RTC_FLAG_INITF) || \
                               ((FLAG) == RTC_FLAG_RSF) || ((FLAG) == RTC_FLAG_WUTWF) || \
                               ((FLAG) == RTC_FLAG_ALRBWF) || ((FLAG) == RTC_FLAG_ALRAWF) || \
                               ((FLAG) == RTC_FLAG_TAMP1F) || ((FLAG) == RTC_FLAG_RECALPF) || \
                                ((FLAG) == RTC_FLAG_SHPF))
#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF00DF) == (uint32_t)RESET))
/**
  * @}
  */ 

/** @defgroup RTC_Interrupts_Definitions 
  * @{
  */ 
#define RTC_IT_TS                         ((uint32_t)0x00008000)
#define RTC_IT_WUT                        ((uint32_t)0x00004000)
#define RTC_IT_ALRB                       ((uint32_t)0x00002000)
#define RTC_IT_ALRA                       ((uint32_t)0x00001000)
#define RTC_IT_TAMP                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper Interrupt */
#define RTC_IT_TAMP1                      ((uint32_t)0x00020000)

#define IS_RTC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF0FFB) == (uint32_t)RESET))
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_TS) || ((IT) == RTC_IT_WUT) || \
                           ((IT) == RTC_IT_ALRB) || ((IT) == RTC_IT_ALRA) || \
                           ((IT) == RTC_IT_TAMP1))
#define IS_RTC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFD0FFF) == (uint32_t)RESET))

/**
  * @}
  */ 

/** @defgroup RTC_Legacy 
  * @{
  */ 
#define RTC_DigitalCalibConfig  RTC_CoarseCalibConfig
#define RTC_DigitalCalibCmd     RTC_CoarseCalibCmd

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the RTC configuration to the default reset state *****/
ErrorStatus LL_RTC_DeInit(RTC);

/* Initialization and Configuration functions *********************************/
ErrorStatus LL_RTC_Init(RTC, LL_RTC_InitTypeDef* RTC_InitStruct);
void LL_RTC_StructInit(LL_RTC_InitTypeDef* RTC_InitStruct);
void RTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus LL_RTC_EnterInitMode(RTC);
void LL_RTC_ExitInitMode(RTC);
ErrorStatus LL_RTC_WaitForSynchro(RTC);
ErrorStatus RTC_RefClockCmd(FunctionalState NewState);
void RTC_BypassShadowCmd(FunctionalState NewState);

/* Time and Date configuration functions **************************************/
ErrorStatus LL_RTC_TIME_Init(RTC, uint32_t RTC_Format, LL_RTC_TimeTypeDef* RTC_TimeStruct);
void LL_RTC_TIME_StructInit(LL_RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetTime(uint32_t RTC_Format, LL_RTC_TimeTypeDef* RTC_TimeStruct);
uint32_t LL_RTC_TIME_GetSubSecond(RTC);
ErrorStatus LL_RTC_DATE_Init(RTC, uint32_t RTC_Format, LL_RTC_DateTypeDef* RTC_DateStruct);
void LL_RTC_DATE_StructInit(LL_RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetDate(uint32_t RTC_Format, LL_RTC_DateTypeDef* RTC_DateStruct);

/* Alarms (Alarm A and Alarm B) configuration functions  **********************/
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, LL_RTC_AlarmTypeDef* RTC_AlarmStruct);
LL_RTC_ALMA_StructInit(RTC_AlarmTypeDef* RTC_AlarmStruct);
void LL_RTC_ALMB_StructInit(LL_RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, LL_RTC_AlarmTypeDef* RTC_AlarmStruct);
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask);
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

/* WakeUp Timer configuration functions ***************************************/
LL_RTC_DisableWriteProtection(RTC);
LL_RTC_WAKEUP_SetClock(RTC, uint32_t RTC_WakeUpClock);
void LL_RTC_EnableWriteProtection(RTC);
LL_RTC_DisableWriteProtection(RTC);
LL_RTC_WAKEUP_SetAutoReload(RTC, uint32_t RTC_WakeUpCounter);
void LL_RTC_EnableWriteProtection(RTC);
uint32_t LL_RTC_WAKEUP_GetAutoReload(RTC);
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState);

/* Daylight Saving configuration functions ************************************/
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t LL_RTC_TIME_IsDayLightStoreEnabled(RTC);

/* Output pin Configuration function ******************************************/
LL_RTC_DisableWriteProtection(RTC);
LL_RTC_SetAlarmOutEvent(RTC, uint32_t RTC_Output);
LL_RTC_SetOutputPolarity(RTC, uint32_t RTC_OutputPolarity);
void LL_RTC_EnableWriteProtection(RTC);

/* Digital Calibration configuration functions *********************************/
ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value);
ErrorStatus RTC_CoarseCalibCmd(FunctionalState NewState);
void RTC_CalibOutputCmd(FunctionalState NewState);
LL_RTC_DisableWriteProtection(RTC);
LL_RTC_CAL_SetOutputFreq(RTC, uint32_t RTC_CalibOutput);
void LL_RTC_EnableWriteProtection(RTC);
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod, uint32_t RTC_SmoothCalibPlusPulses, uint32_t RTC_SmouthCalibMinusPulsesValue);

/* TimeStamp configuration functions ******************************************/
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState);
void RTC_GetTimeStamp(uint32_t RTC_Format, LL_RTC_TimeTypeDef* RTC_StampTimeStruct,
                                      LL_RTC_DateTypeDef* RTC_StampDateStruct);
uint32_t LL_RTC_TS_GetSubSecond(RTC);

/* Tampers configuration functions ********************************************/
void RTC->TAFCR |= (uint32_t)( << 1);
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState);
void LL_RTC_TAMPER_SetFilterCount(RTC, uint32_t RTC_TamperFilter);
void LL_RTC_TAMPER_SetSamplingFreq(RTC, uint32_t RTC_TamperSamplingFreq);
void LL_RTC_TAMPER_SetPrecharge(RTC, uint32_t RTC_TamperPrechargeDuration);
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
void RTC_TamperPullUpCmd(FunctionalState NewState);

/* Backup Data Registers configuration functions ******************************/
void LL_RTC_BAK_SetRegister(RTC, uint32_t RTC_BKP_DR, uint32_t Data);
uint32_t LL_RTC_BAK_GetRegister(RTC, uint32_t RTC_BKP_DR);

/* RTC Tamper and TimeStamp Pins Selection and Output Type Config configuration
   functions ******************************************************************/
void LL_RTC_TAMPER_SetPin(RTC, uint32_t RTC_TamperPin);
void LL_RTC_TS_SetPin(RTC, uint32_t RTC_TimeStampPin);
void LL_RTC_SetAlarmOutputType(RTC, uint32_t RTC_OutputType);

/* RTC_Shift_control_synchonisation_functions *********************************/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS);

/* Interrupts and flags management functions **********************************/
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG);
void RTC_ClearFlag(uint32_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint32_t RTC_IT);
void RTC_ClearITPendingBit(uint32_t RTC_IT);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
