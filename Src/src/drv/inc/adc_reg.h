/**
 * @file adc_reg.h
 * @author Product application department
 * @brief  ADC 模块寄存器配置文件
 * @version  V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __ADC_REG_H_
#define __ADC_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define ADC_BASE_ADDR (0x40020000)
#define ADC ((reg_adc_t *)ADC_BASE_ADDR)

// ADC_ISR
#define ADC_ANALOG_WD_FLAG (((uint32_t)1 << 7))
#define ADC_FIFO_EMPTY_STATUS (((uint32_t)1 << 6))
#define ADC_FIFO_FULL_STATUS (((uint32_t)1 << 5))
#define ADC_OVER_RUN_FLAG (((uint32_t)1 << 4))
#define ADC_END_SEQUENCE_FLAG (((uint32_t)1 << 3))
#define ADC_END_CONVERSION_FLAG (((uint32_t)1 << 2))
#define ADC_END_SAMPLING_FLAG (((uint32_t)1 << 1))
#define ADC_READY_FLAG (((uint32_t)1 << 0))

// ADC_IER
#define ADC_ANALOG_WD_INT_EN (((uint32_t)1 << 7))
#define ADC_OVER_RUN_INT_EN (((uint32_t)1 << 4))
#define ADC_END_SEQUENCE_INT_EN (((uint32_t)1 << 3))
#define ADC_END_CONVERSION_INT_EN (((uint32_t)1 << 2))
#define ADC_END_SAMPLING_INT_EN (((uint32_t)1 << 1))
#define ADC_READY_INT_EN (((uint32_t)1 << 0))

// ADC_CR
#define ADC_STOP_CONVERSION_CMD_EN (((uint32_t)1 << 3))
#define ADC_START_CONVERSION_CMD_EN (((uint32_t)1 << 2))
#define ADC_DISABLE_CMD_EN (((uint32_t)1 << 1))
#define ADC_ENABLE_CMD_EN (((uint32_t)1 << 0))

// ADC_CFGR1
#define ADC_ANALOG_INPUT_DIFF_MASK (((uint32_t)1 << 31))
#define ADC_OVERRUN_MODE_MASK (((uint32_t)1 << 30))
#define ADC_QADC_CLK_DISABLE_MASK (((uint32_t)1 << 29))
#define ADC_SAMPLE_OUTPUT_BUFFER_EN (((uint32_t)1 << 28))
#define ADC_DISCONTINUOUS_EN (((uint32_t)1 << 23))
#define ADC_AUTO_OFF_MODE_EN (((uint32_t)1 << 22))
#define ADC_WAIT_CONVERSION_MODE_MASK (((uint32_t)1 << 21))
#define ADC_CONTINUOUS_CONVERSION_MASK (((uint32_t)1 << 20))
#define ADC_EXTERNAL_VREF_MASK (((uint32_t)1 << 15))
#define ADC_CFGR1_ALIGN_LEFT_ALIGNMENT (((uint32_t)1 << 10))
#define ADC_CFGR1_ALIGN_RIGHT_ALIGNMENT ((uint32_t)(0 << 10))
#define ADC_LEFT_ALIGNMENT_MASK (((uint32_t)1 << 10))
#define ADC_CFGR1_RES_10BIT (((uint32_t)1 << 8))
#define ADC_CFGR1_DMATH_2 ((uint32_t)(2 << 4))
#define ADC_DMA_ACCESS_EN (((uint32_t)1 << 0))
#define ADC_CFGR1_SEQ_LEN_SHIFT ((uint32_t)(24))

// ADC_CFGR2
#define ADC_ANALOG_INPUT_BYPASS_EN (((uint32_t)1 << 15))
#define ADC_CFGR2_QPR_0 ((uint32_t)(0 << 8))
#define ADC_CFGR2_QPR_1 (((uint32_t)1 << 8))
#define ADC_CFGR2_QPR_F ((uint32_t)(0x0f << 8))
#define ADC_CFGR2_SCTNT_10H ((uint32_t)(0x10))
#define ADC_CFGR2_SCTNT_20H ((uint32_t)(0x20))

// ADC_SMPR
#define ADC_SMPR_SMP_6 ((uint32_t)(6))
#define ADC_SMPR_SMP_8 ((uint32_t)(8))

// ADC_WDG
#define ADC_ANALOG_WATCHDOG_EN (((uint32_t)1 << 7))
#define ADC_WATCHDOG_CHANNEL_MASK (((uint32_t)1 << 6))

// ADC_TR
#define ADC_NOTE_FOR_HT_MASK (((uint32_t)1 << 28))
#define ADC_NOTE_FOR_LT_MASK (((uint32_t)1 << 12))

// ADC_CHSELR1 ADC_CHSELR2
#define ADC_CHSELR_MASK ((uint8_t)(0x1F))

// ADC_FIFO ADC_ISR2
#define ADC_FIFO_TIMEOUT_FLAG (((uint32_t)1 << 31))
#define ADC_DATA_BUFFER_TIMEOUT_FLAG (((uint32_t)1 << 15))
#define ADC_DATA_BUFFER_READY_FLAG (((uint32_t)1 << 12))

// DC_DGATR
#define ADC_DATA_BUFFER_TIMEOUT_INT_EN (((uint32_t)1 << 15))
#define ADC_DATA_BUFFER_TIMEOUT_EN (((uint32_t)1 << 14))
#define ADC_DATA_BUFFER_READY_INT_EN (((uint32_t)1 << 12))
#define ADC_DATA_GATHER_FUNCTION_EN (((uint32_t)1 << 0))

// ADC_DBUFR ADC_FIFOTOR
#define ADC_FIFO_TIMEOUT_INT_EN (((uint32_t)1 << 15))
#define ADC_FIFO_TIMEOUT_EN (((uint32_t)1 << 14))

/**
 * @brief ADC 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t ADC_ISR;   /**< 00 ADC interrupt and status register                */
    __IO uint32_t ADC_IER;   /**< 04 ADC interrupt enable register                    */
    __IO uint32_t ADC_CR;    /**< 08 ADC control register                             */
    __IO uint32_t ADC_CFGR1; /**< 0C ADC configuration register 1                     */

    __IO uint32_t ADC_CFGR2; /**< 10 ADC configuration register 2                     */
    __IO uint32_t ADC_SMPR;  /**< 14 ADC sampling time register                       */
    __IO uint32_t ADC_WDG;   /**< 18 ADC watch dog register                           */
    __IO uint32_t ADC_TR;    /**< 1C ADC watch dog threshold register                 */

    __IO uint32_t RESERVED1[3]; /**< 20 24 28                                            */
    __IO uint32_t ADC_CHSELR1;  /**< 2C ADC channel selection register 1                 */

    __IO uint32_t ADC_CHSELR2;  /**< 30 ADC channel selection register 2                 */
    __IO uint32_t RESERVED2[6]; /**< 40                                                  */

    __IO uint32_t ADC_FIFOR; /**< 4C ADC FIFO access register                         */

    __IO uint32_t RESERVED3; /**< 50                                                  */
    __IO uint32_t ADC_ISR2;  /**< 54 ADC interrupt and status register 2              */
    __IO uint32_t ADC_DGATR; /**< 58 ADC data gather register                         */
    __IO uint32_t ADC_DBUFR; /**< 5C ADC data buffer register                         */

    __IO uint32_t ADC_FIFOTOR;  /**< 60 ADC FIFO timeout register                        */
    __IO uint32_t RESERVED4[7]; /**< 64                                                  */

    union
    {
        __IO uint32_t ADC_DET3; /**< 80 ADC data for test 3                              */
        struct
        {
            __IO uint16_t CHANEL6;
            __IO uint16_t CHANEL7;
        } DET3;
    };
    union
    {
        __IO uint32_t ADC_DET2; /**< 84 ADC data for test 2                              */
        struct
        {
            __IO uint16_t CHANEL4;
            __IO uint16_t CHANEL5;
        } DET2;
    };
    union
    {
        __IO uint32_t ADC_DET1; /**< 88 ADC data for test 1                              */
        struct
        {
            __IO uint16_t CHANEL2;
            __IO uint16_t CHANEL3;
        } DET1;
    };
    union
    {
        __IO uint32_t ADC_DET0; /**< 8C ADC data for test 0                              */
        struct
        {
            __IO uint16_t CHANEL0;
            __IO uint16_t CHANEL1;
        } DET0;
    };

    union
    {
        __IO uint32_t ADC_DET7; /**< 90 ADC data for test 7                              */
        struct
        {
            __IO uint16_t CHANEL14;
            __IO uint16_t CHANEL15;
        } DET7;
    };
    union
    {
        __IO uint32_t ADC_DET6; /**< 94 ADC data for test 6                              */
        struct
        {
            __IO uint16_t CHANEL12;
            __IO uint16_t CHANEL13;
        } DET6;
    };
    union
    {
        __IO uint32_t ADC_DET5; /**< 98 ADC data for test 5                              */
        struct
        {
            __IO uint16_t CHANEL10;
            __IO uint16_t CHANEL11;
        } DET5;
    };
    union
    {
        __IO uint32_t ADC_DET4; /**< 9C ADC data for test 4                              */
        struct
        {
            __IO uint16_t CHANEL8;
            __IO uint16_t CHANEL9;
        } DET4;
    };

    union
    {
        __IO uint32_t ADC_DET8; /**< A0 ADC data for test 8                              */
        struct
        {
            __IO uint16_t CHANEL16;
            __IO uint16_t RESERVED5;
        } DET8;
    };
    __IO uint32_t ADC_CHSELR3; /**< A4 ADC channel selection register 3                 */
    __IO uint32_t ADC_TRIGSEL; /*< A8 ADC trigger source selection register*/
} reg_adc_t;

#ifdef __cplusplus
}
#endif

#endif