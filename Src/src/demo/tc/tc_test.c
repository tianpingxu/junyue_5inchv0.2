/**
 * @file tc_test.c
 * @author Product application department
 * @brief  TC 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup TC TC模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "tc_test.h"


// 函数定义

/**
 *  @brief  TC 模块测试示例函数
 *
 */
void tc_demo(void)
{
    uint32_t i = 0;
    tc_init_t tcit;

    tcit.instance = TC;
    tcit.wait_mode = ENABLE;
    tcit.doze_mode = ENABLE;
    tcit.stop_mode = ENABLE;
    tcit.debug_mode = DISABLE;
    tcit.prescaler = TC_WDP_128;
    tcit.interrupt_enable = DISABLE;
    tcit.reset_enable = ENABLE;
    tcit.tcmr = 5000;

    printf("函数名：%s \r\n", __FUNCTION__);

    hal_tc_init(&tcit);

    hal_tc_feed_watchdog(&tcit);
    printf("\t TC测试：\r\n");
    for (i = 0x5000; i > 0; i--)
    {
        if ((i % 0x400) == 0)
        {
            printf("\t当前计数器值：%04x \r\n", hal_tc_get_counter(&tcit));
            hal_tc_feed_watchdog(&tcit);
        }
    }
    printf("\t TC 不喂狗测试：\r\n");
    i = 0;
    while (1)
    {
        i++;
        if (i == 0x1000)
        {
            i = 0;
            printf("\t当前计数器值：%04x \r\n", hal_tc_get_counter(&tcit));
        }
    }
}

/** @} */  // 结束 TC 模块分组
/** @} */  // 结束外设模块分组
