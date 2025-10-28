/**
 * @file tp_test.c
 * @author Product application department
 * @brief  TOUCH 模块测试用例，仅供参考
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
 * @defgroup TOUCH TOUCH模块
 * @ingroup Peripherals
 * @{
 */


/*** 头文件定义 ***************************************************************/
#include "tp_test.h"
#include "tp_interface.h"
#include "lcd_interface.h"


/*** 全局变量定义 ***************************************************************/
tp_handle_t tp_dev;

/*** 函数定义 *******************************************************************/


/**
 * @brief TOUCH 模块测试示例函数
 * @param  
 */
void touch_demo(void)
{

    tp_dev.touchtype = TP_INTERFACE;
    tp_init(&tp_dev);
    TPLOG_DEBUG("init ok\r\n");
    delayms(100);
    TPLOG_DEBUG("/****Start Scan****/\r\n");
    tp_scan(&tp_dev);
}

/** @} */  // 结束 TC 模块分组
/** @} */  // 结束外设模块分组
