/**
 * @file pwmt_test.c
 * @author Product Application Department
 * @brief  PWMT 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup PWMT PWMT模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "pwmt_test.h"

// 全局变量定义
#define PWMT_DMA_TEST 0
#define PWM_CAPTURE_TEST 1
#define DUTY_LENGTH (900)
static uint16_t dutybuffer[DUTY_LENGTH] = {0};
static dmac_hdle_t pwmt_hdma;
extern volatile uint8_t capintflag;

// 函数定义

/**
 * @brief PWMT 模块输出测试函数
 *
 * @param PWMT PWMT标号定义
 * @param function PWMT引脚定义
 * @param channel 通道定义
 * @param prescaler 预分频定义
 * @param width 占空比定义
 * @param period 周期定义
 */
void pwmt_output_test(uint8_t PWMT, pwmt_pin_func_t function, uint8_t channel, uint16_t prescaler, uint16_t width, uint16_t period)
{
    pwmt_handle_t pwmt;
    memset(&pwmt, 0, sizeof(pwmt_handle_t));
    printf("%s\r\n", __FUNCTION__);
    switch (PWMT)
    {
    case 1:
    {
        pwmt.instance = PWMT1;
    }
    break;
    case 2:
    {
        pwmt.instance = PWMT2;
    }
    break;
    case 3:
    {
        pwmt.instance = PWMT3;
    }
    break;
    default:
        break;
    }
    pwmt.init.channel = channel;
    pwmt.init.function = function;
    pwmt.init.interrupr_type = ALL_PWMT_INT_DIS;
    pwmt.init.direction = PWMT_OUTPUT;
    pwmt.init.out.autoload = ENABLE;
    pwmt.init.out.clkdiv = CKINT_MUT2;
    pwmt.init.out.deadzone = 10;
    pwmt.init.out.period = period;
    pwmt.init.out.prescaler = prescaler;
    pwmt.init.out.width = width;

    hal_pwmt_pwmoutputinit(&pwmt);
    hal_pwmt_pwmenable(&pwmt, ENABLE);
}

/**
 * @brief PWMT 模块DMA输出测试函数
 *
 * @param PWMT PWMT标号定义
 * @param function PWMT引脚定义
 * @param channel 通道定义
 * @param prescaler 预分频定义
 * @param dutyfactor 占空比定义
 * @param period 周期定义
 */
void pwmt_dma_output(uint8_t PWMT, pwmt_pin_func_t function, uint8_t channel, uint16_t prescaler, uint16_t width, uint16_t period)
{
    pwmt_handle_t pwmt;
    reg_dmac_t *DMANumber;
    uint32_t DMACHNumber = 0;
    uint32_t DMATranPeripheralType = 0;
    status_t st;

    memset(&pwmt, 0, sizeof(pwmt_handle_t));
    for (uint16_t cnt = 0; cnt < DUTY_LENGTH;)
    {
        for (uint16_t i = 0; i < 9; i++)
        {
            dutybuffer[cnt++] = 40;
        }
    }

    switch (PWMT)
    {
    case 1:
    {
        pwmt.instance = PWMT1;
        DMANumber = DMAC2;
        DMACHNumber = 0;
        DMATranPeripheralType = HAL_DMAC2_PERIPHERAL_PWMT1_TX;
    }
    break;
    case 2:
    {
        pwmt.instance = PWMT2;
        DMANumber = DMAC1;
        DMACHNumber = 0;
        DMATranPeripheralType = HAL_DMAC_PERIPHERAL_PWMT2_TX;
    }
    break;
    case 3:
    {
        pwmt.instance = PWMT3;
        DMANumber = DMAC1;
        DMACHNumber = 0;
        DMATranPeripheralType = HAL_DMAC_PERIPHERAL_PWMT3_TX;
    }
    break;
    default:
        break;
    }
    hal_pwmt_pwmenable(&pwmt, DISABLE);
    pwmt.init.channel = channel;
    pwmt.init.function = function;
    pwmt.init.interrupr_type = ALL_PWMT_INT_DIS;
    pwmt.init.direction = PWMT_OUTPUT;
    pwmt.init.out.autoload = ENABLE;
    pwmt.init.out.clkdiv = CKINT_MUT1;
    pwmt.init.out.deadzone = 0;
    pwmt.init.out.period = period;
    pwmt.init.out.prescaler = prescaler;
    pwmt.init.out.width = width;
    hal_pwmt_pwmoutputinit(&pwmt);
    hal_pwmt_dmaupdatereqen(pwmt.instance);

    pwmt_hdma.instance = DMANumber;
    pwmt_hdma.init.channel_num = DMACHNumber;
    hal_dmac_deinit(&pwmt_hdma);
    pwmt_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    pwmt_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    pwmt_hdma.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    pwmt_hdma.init.src_inc = HAL_DMAC_SINC_INC;
    pwmt_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_16BITS;
    pwmt_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_16BITS;
    pwmt_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;

    pwmt_hdma.init.peripheral_type = DMATranPeripheralType;
    pwmt_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;
    if (channel == 0)
    {
        pwmt_hdma.init.dst_addr = (uint32_t)(&pwmt.instance->CCR1);
        hal_pwmt_dmacc1reqen(pwmt.instance);
    }
    else if (channel == 1)
    {
        pwmt_hdma.init.dst_addr = (uint32_t)(&pwmt.instance->CCR2);
        hal_pwmt_dmacc2reqen(pwmt.instance);
    }
    else if (channel == 2)
    {
        pwmt_hdma.init.dst_addr = (uint32_t)(&pwmt.instance->CCR3);
        hal_pwmt_dmacc3reqen(pwmt.instance);
    }
    else
    {
        pwmt_hdma.init.dst_addr = (uint32_t)(&pwmt.instance->CCR4);
        hal_pwmt_dmacc4reqen(pwmt.instance);
    }
    pwmt_hdma.init.src_addr = (uint32_t)dutybuffer;
    pwmt_hdma.init.transfer_size = DUTY_LENGTH;
    st = hal_dmac_init(&pwmt_hdma);
    if (st != STATUS_OK)
    {
        printf("DMA init failed \r\n");
        while (1)
            ;
    }
    dcache_clean_range(dutybuffer, sizeof(dutybuffer));

    st = hal_dmac_startpolling(&pwmt_hdma);
    if (st != STATUS_OK)
    {
        printf("StartPolling failed \r\n");
        while (1)
            ;
    }
    hal_pwmt_counten(pwmt.instance);

    st = hal_dmac_pollfortransfer(&pwmt_hdma, 0, MAX_DELAY);
    if (st != STATUS_OK)
    {
        printf("StartPolling failed \r\n");
        while (1)
            ;
    }
    hal_dmac_clearrawstatus(&pwmt_hdma, DMACHNumber);
    hal_dmac_enable(&pwmt_hdma);
    hal_pwmt_pwmenable(&pwmt, DISABLE);
    printf("transfer done\r\n");
}

/**
 * @brief PWMT 模块捕获测试函数实体
 *
 * @param hpwmt PWMT配置句柄定义
 */
void pwmt_capturetest(pwmt_handle_t *hpwmt)
{
    uint16_t int_status = 0;
    uint8_t dataNum[4] = {0};
    uint16_t data[4][2] = {0};
    uint16_t ccr_reg_tmp = 0;
    uint8_t i, j = 0;
    hal_pwmt_pwmenable(hpwmt, DISABLE);
    hal_pwmt_inputcaptureinit(hpwmt);
    ccr_reg_tmp = ccr_reg_tmp;
    hal_pwmt_pwmenable(hpwmt, ENABLE);
    while (1)
    {
        if (hpwmt->init.interrupr_type != ALL_PWMT_INT_DIS)
        {
            int_status = capintflag;
        }
        else
        {
            int_status = hal_pwmt_getitstatus(hpwmt->instance);
        }

        for (i = CAPTURE_COMPARE1; i <= CAPTURE_COMPARE4; i++)
        {

            if (int_status & (1 << i))
            {
                int_status &= ~(1 << i);

                j = dataNum[i - 1];
                data[i - 1][j] = hal_pwmt_getcapval(hpwmt->instance, hpwmt->init.channel);
                dataNum[i - 1]++;
                if (data[i - 1][j]) // to eliminate warning
                {
                    data[i - 1][j] = data[i - 1][j];
                }
                hal_pwmt_clritstatus(hpwmt->instance, (pwmt_int_t)i);

                if (hal_pwmt_getcapflag(hpwmt->instance, (pwmt_int_t)i))
                {
                    dataNum[i - 1] = 0;
                    ccr_reg_tmp = hal_pwmt_getcapval(hpwmt->instance, hpwmt->init.channel);
                    hal_pwmt_clrcapflag(hpwmt->instance, (pwmt_int_t)i);
                }

                if (dataNum[i - 1] == 2)
                {
                    dataNum[i - 1] = 0;
                }
            }
        }
    }
}

/**
 * @brief PWMT 模块捕获测试函数
 *
 * @param PWMT PWMT标号定义
 * @param function PWMT引脚定义
 * @param channel 通道定义
 * @param prescaler 预分频定义
 * @param dutyfactor 占空比定义
 * @param period 周期定义
 */
void pwmt_capture_test(uint8_t PWMT, pwmt_pin_func_t function, uint8_t channel, uint16_t prescaler, uint16_t width, uint16_t period)
{
    pwmt_handle_t pwmt;
    memset(&pwmt, 0, sizeof(pwmt_handle_t));
    printf("%s.\r\n", __FUNCTION__);

    switch (PWMT)
    {
    case 1:
        pwmt.instance = PWMT1;
        PWMT1_IRQHandler_Callback = hal_pwmt_irqhandler;
        break;
    case 2:
        pwmt.instance = PWMT2;
        PWMT2_IRQHandler_Callback = hal_pwmt_irqhandler;
        break;
    case 3:
        pwmt.instance = PWMT3;
        PWMT3_IRQHandler_Callback = hal_pwmt_irqhandler;
        break;
    default:
        break;
    }

    pwmt.init.interrupr_type = ALL_PWMT_INT_DIS;
    pwmt.init.direction = PWMT_INPUT;
    pwmt.init.channel = channel;
    pwmt.init.function = function;
    pwmt.init.in.autoload = ENABLE;
    pwmt.init.in.clkdiv = CKINT_MUT1;
    pwmt.init.in.period = period;
    pwmt.init.in.prescaler = prescaler;
    pwmt.init.in.trigger = RISING_EDGE;
    pwmt.CaptureCallback = hal_pwmt_capturecallback;
    pwmt_capturetest(&pwmt);

    printf("%s.\r\n", __FUNCTION__);
}

/**
 * @brief PWMT 模块测试示例函数
 *
 */
void pwmt_demo(void)
{
    uint8_t pwmt_module = 1;
    uint16_t prescaler = 1;
    uint16_t width = 30;
    uint16_t period = 100;
    uint8_t channel = CHANNEL1;
    pwmt_pin_func_t function = PWMT_1 | PWMT_1_N;

    SwitchPinFunction(CLCD_DATA2_FUN, PWMT1_1_FUN);
    SwitchPinFunction(CLCD_DATA8_FUN, PWMT1_1_N_FUN);
#if PWMT_DMA_TEST
    pwmt_dma_output(pwmt_module, function, channel, prescaler, width, period);
#elif PWM_CAPTURE_TEST
    pwmt_capture_test(pwmt_module, function, channel, prescaler, width, period);
#else
    pwmt_output_test(pwmt_module, function, channel, prescaler, width, period);
#endif
}

/** @} */  // 结束 PWMT 模块分组
/** @} */  // 结束外设模块分组
