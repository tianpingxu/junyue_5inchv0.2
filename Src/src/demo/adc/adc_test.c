/**
 * @file adc_test.c
 * @author Product application department
 * @brief  ADC 模块测试用例，仅供参考
 * @version  V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup ADC ADC模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "adc_test.h"

// 全局变量定义
#define ADC_VOLTAGE_TEST 0
#define ADCPWMT_CPU_TEST 0
#define ADCPWMT_CPU_IRQ_TEST 1
static adc_handle_t adc_handle = {0};
static volatile uint32_t adc_value = 0;
volatile uint8_t adc_conversion_complete = FALSE;

// 函数定义

/**
 * @brief  ADC 模块初始化函数
 * @param channel_1 ADC通道号
 * @return
 */
static uint16_t adc_voltage_test(uint8_t channel_1)
{

    uint32_t resVC;
    uint16_t DATA;
    adc_init_t adc;

    adc.channel = channel_1;

    adc.align = ADC_RIGHT_ALIGN;
    adc.clk_div = ADC_CLK_DIV_4;
    adc.conv = ADC_CONTINUOUS_CONV_MODE;
    adc.overrun = ADC_OVERRUN_MODE_LAST;
    adc.resolution = ADC_RESOLUTION_12BIT;
    adc.smp_time = 0x20;
    adc.stab_time = 0x20;
    adc.trigger_mode = HAL_ADC_TRIGGER_SOFT;
    adc.vref = ADC_EXTERNAL_VREF;
    adc.int_kind = 0;
    hal_adc_init(&adc);
    hal_adc_moduleen(TRUE);

    DATA = hal_adc_getconversionvalue();

    resVC = 33 * DATA / 4095;

    hal_adc_moduleen(FALSE);

    return resVC;
}

/**
 * @brief ADC 模块中断回调函数
 *
 * @param
 */
static void adc_irq_handler(void)
{

    while (drv_adc_check_endflag() != ADC_END_SEQUENCE_FLAG);
        //    printf("_adc_chk_end_sequence_flag=%d\r\n",_adc_chk_end_sequence_flag);
    adc_value = drv_adc_get_data();
    printf("ADC Conversion Value is %d", adc_value);
    adc_conversion_complete = TRUE;
    drv_adc_irq_handler();
}

/**
 * @brief  PWMT 模块输出配置函数
 * @param
 */
static void pwmt1_out(void)
{

    pwmt_handle_t pwmt_t1;
    uint16_t prescaler = 4;    // prescaler：分频系数
    uint16_t width = 625; // dutyfactor：占空比。不能为0
    uint16_t period = 1250;    // 重装载值
    pwmt_t1.instance = PWMT1;
    pwmt_t1.init.interrupr_type = ALL_PWMT_INT_DIS;
    pwmt_t1.init.direction = PWMT_OUTPUT;
    pwmt_t1.init.channel = CHANNEL0;
    pwmt_t1.init.function = PWMT_1;
    pwmt_t1.init.out.autoload = ENABLE;
    pwmt_t1.init.out.clkdiv = CKINT_MUT1;
    pwmt_t1.init.out.deadzone = 0;
    pwmt_t1.init.out.period = period;
    pwmt_t1.init.out.prescaler = prescaler;
    pwmt_t1.init.out.width = width;
    pwmt_t1.init.brk = BRK_ENABLE;   /*断路使能*/
    pwmt_t1.init.trgo_mode = MODE_2; /*TRGO触发模式*/
    hal_channel_outputconfiguration(&pwmt_t1, CHANNEL1);
    hal_channel_outputconfiguration(&pwmt_t1, CHANNEL2);
    hal_pwmt_pwmoutputinit(&pwmt_t1);
    /* 计数器使能 */
    hal_pwmt_pwmenable(&pwmt_t1, ENABLE);
}

/**
 * @brief ADC 模块通过PWMT触发级联CPU方式采集电压函数
 *
 * @param channel_1  ADC通道号
 */

static void adc_pwmt_cpu_test(uint8_t channel_1)
{
    uint8_t i;
    uint32_t resVC;
    uint16_t res;
    adc_handle.instance = ADC;
    adc_handle.init.channel = channel_1;
    adc_handle.init.align = ADC_RIGHT_ALIGN;
    adc_handle.init.clk_div = ADC_CLK_DIV_4;
    adc_handle.init.conv = ADC_CONTINUOUS_CONV_MODE;
    adc_handle.init.overrun = ADC_OVERRUN_MODE_LAST;
    adc_handle.init.resolution = ADC_RESOLUTION_12BIT;
    adc_handle.init.smp_time = 0x20; /*采样时间*/
    adc_handle.init.stab_time = 0x20;
    adc_handle.init.vref = ADC_EXTERNAL_VREF;
    adc_handle.init.int_kind = HAL_ADC_NULL_INT;
    QADC_IRQHandler_Callback = adc_irq_handler;
    adc_handle.init.trigger_mode = HAL_ADC_TRIGGER_SINGLE_LEVEL;
    adc_handle.init.trigger_source = HAL_ADC_TRIGGER_PWMT1; /*ADC触发源*/
    hal_adc_init(&adc_handle.init);
    pwmt1_out();
    hal_adc_moduleen(TRUE);
    while (1)
    {
        res = hal_adc_getconversionvalue();
        printf("ADC Conversion Value is %d", res);
        resVC = 33 * res / 4095;
        printf("ADC calculate VC manually is %d.%dV", resVC / 10, resVC % 10);
        delayms(1000);
    }
    hal_adc_moduleen(FALSE);
}
/**
 * @brief ADC 模块丢弃第一个值函数
 *
 */
static void throwfirstvalue(void)
{
    hal_adc_start();
    while (adc_conversion_complete == FALSE)
        ;
    drv_adc_clr_endflag();
    hal_adc_stop();
    printf("Throw First ADC Value: %d", adc_value);
}
/**
 * @brief ADC 模块通过PWMT触发级联中断方式采集电压函数
 * @param channel_1 ADC通道号
 */
static void adc_pwmt_cpu_irq_test(uint8_t channel_1)
{

    uint32_t resVC;
    adc_handle.instance = ADC;
    adc_handle.init.channel = channel_1;
    adc_handle.init.align = ADC_RIGHT_ALIGN;
    adc_handle.init.clk_div = ADC_CLK_DIV_4;
    adc_handle.init.conv = ADC_SINGLE_CONV_MODE;
    adc_handle.init.overrun = ADC_OVERRUN_MODE_LAST;
    adc_handle.init.resolution = ADC_RESOLUTION_12BIT;
    adc_handle.init.smp_time = 0x20; /*采样时间*/
    adc_handle.init.stab_time = 0x20;
    adc_handle.init.vref = ADC_EXTERNAL_VREF;
    adc_handle.init.int_kind = HAL_ADC_END_SAMPLING_INT;
    QADC_IRQHandler_Callback = adc_irq_handler;
    adc_handle.init.trigger_mode = HAL_ADC_TRIGGER_SINGLE_LEVEL;
    adc_handle.init.trigger_source = HAL_ADC_TRIGGER_PWMT1; /*ADC触发源*/
    hal_adc_init(&adc_handle.init);
    pwmt1_out();
    hal_adc_moduleen(TRUE);
    throwfirstvalue(); /*丢弃模块使能后采集的第一个值*/
    hal_adc_start();
    while (1);
}
/**
 * @brief  ADC 模块测试示例函数
 *
 */
void adc_demo(void)
{
#if ADC_VOLTAGE_TEST
    uint32_t resVC;
    while (1)
    {
        resVC = adc_voltage_test(ADC_IN1);
        printf("ADC calculate VC manually is %d.%dV", resVC / 10, resVC % 10);
        delayms(1000);
    }
#elif ADCPWMT_CPU_TEST
    adc_pwmt_cpu_test(ADC_IN1);

#elif ADCPWMT_CPU_IRQ_TEST
    adc_pwmt_cpu_irq_test(ADC_IN1);
#endif
}

/** @} */  // 结束 ADC 模块分组
/** @} */  // 结束外设模块分组
