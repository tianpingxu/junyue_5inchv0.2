/**
 * @file lowpower_test.c
 * @author Product Application Department
 * @brief  低功耗测试用例，仅供参考
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup LOWPOWER LOWPOWER模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "lowpower_test.h"

// 全局变量定义
//#define LOWPOWER_LOWPOWER_TEST
#define LOWPOWER_HIBWE_TEST

// 函数定义
/**
 * @brief 低功耗 测试示例函数
 *
 */
void lowerpower_demo(void)
{
#ifdef LOWPOWER_LOWPOWER_TEST
    // Wakeup_EPORT_Init();
    printf("LOWPOWER_LOWPOWER_TEST\r\n");
    delayms(3000);
    printf("Will sleep\r\n");
    hal_cpm_lowpower();
    printf("wake up!\r\n");
    while (1)
    {
        ;
    }

#endif

#ifdef LOWPOWER_HIBWE_TEST

    delayms(3000);
    printf("LOWPOWER_HIBWE_TEST\r\n");
    hal_cpm_poweroff();
#endif
}


/** @} */  // 结束 LOWPOWER 模块分组
/** @} */  // 结束外设模块分组
