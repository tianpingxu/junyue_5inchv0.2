/**
 * @file wdt_test.c
 * @author Product application department
 * @brief  WDT 模块测试用例，仅供参考
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
 * @defgroup WDT WDT模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "wdt_test.h"


/**
 *  @brief  WDT 模块测试示例函数
 *  @note  调试看门狗请先将startup_ARMCM7.s中关闭看门狗的操作去掉。看门狗在芯片上电后只能开或关一次，默认为开
 *
 */
void wdt_demo(void)
{
    uint32_t i = 0;

    hal_wdt_init(0xfffe); // don't close WDT in startup_ARMCM7.s

    for (i = 0x50000; i > 0; i--)
    {
        if ((i % 0x400) == 0x00)
        {
            hal_wdt_feed_watchdog();
            printf("1 WDT Count: 0x%04x\r\n", hal_wdt_get_counter());
        }
        else
        {
            if ((i % 150) == 0x00)
            {
                printf("2 WDT Count: 0x%04x\r\n", hal_wdt_get_counter());
            }
        }
    }

    printf("No Feed ...\r\n");
    while (1)
    {
        i++;
        if ((i % 0x1000) == 0x00)
        {
            printf("WDT Count: 0x%04x\r\n", hal_wdt_get_counter());
        }
    }
}

/** @} */  // 结束 WDT 模块分组
/** @} */  // 结束外设模块分组
