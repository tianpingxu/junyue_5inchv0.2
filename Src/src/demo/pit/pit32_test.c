/**
 * @file pit32_test.c
 * @author Product application department
 * @brief  PIT32 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */


/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup PIT32 PIT32模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "pit32_test.h"

// 全局变量定义
hal_pit32_handler_t hal_hpit32;

// 函数定义

/**
 *  @brief  PIT32 模块测试实例函数
 *
 *  @param time PIT32 设定 ms 定时时间
 */
void pit32_test(uint32_t time)
{
    double time_cnt = time * 0.001;

    hal_hpit32.instance = PIT1;
    hal_hpit32.init.counter = hal_pit32_calc_counter(g_ips_clk, PIT32_CLK_DIV_32, time_cnt);
    hal_hpit32.init.enable_ie = 1;
    hal_hpit32.init.reload = 1;
    hal_hpit32.init.prescaler = PIT32_CLK_DIV_32;
    hal_hpit32.init.run_at_debug = 1;
    hal_hpit32.init.run_at_doze = 1;
    hal_hpit32.init.update_cnt = 1;

    hal_pit32_init(&hal_hpit32);
}

/**
 *  @brief  PIT32 模块测试示例函数
 *
 */
void pit32_demo(void)
{
    pit32_test(1000);
}


/** @} */  // 结束 PIT32 模块分组
/** @} */  // 结束外设模块分组
