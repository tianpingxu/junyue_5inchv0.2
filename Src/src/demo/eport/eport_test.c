/**
 * @file eport_test.c
 * @author Product application department
 * @brief  EPORT 模块测试用例，仅供参考
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
 * @defgroup EPORT EPORT模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "eport_test.h"


// 全局变量定义
#define OUTPUT_TEST
// #define INPUT_TEST
// #define INTERRUPT_TEST

// 函数定义

/**
 * @brief EPORT 模块输出测试功能函数
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 */
void eport_singleoutput_test(reg_eport_t *pEport, uint8_t Pinx)
{
    hal_eport_output(pEport, Pinx);

    while (1)
    {
        hal_eport_writepinlevel(pEport, Pinx, GPIO_HIGH);
        delayms(100);
        hal_eport_writepinlevel(pEport, Pinx, GPIO_LOW);
        delayms(100);
    }
}

/**
 * @brief EPORT 模块输入测试功能函数
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 * @param ps 上拉/下拉/浮空
 */
void eport_singleinput_test(reg_eport_t *pEport, uint8_t Pinx, ioctrl_ps_t ps)
{
    uint8_t value_level;
    hal_eport_input(pEport, Pinx, ps);
    while (1)
    {
        value_level = hal_eport_readpinslevel(pEport, Pinx);
        printf(" value_level = %d\r\n", value_level);
        delayms(500);
    }
}

/**
 * @brief EPORT 模块输入中断测试功能函数
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 * @param int_type 中断类型
 * @param ps 上拉/下拉/浮空
 */
void eport_singleinterrupu_test(reg_eport_t *pEport, uint8_t Pinx, eport_intmode_t int_type, ioctrl_ps_t ps)
{

    hal_eport_interrupt(pEport, Pinx, int_type, ps);
}

/**
 * @brief EPORT 模块测试示例函数
 *
 */
void eport_demo(void)
{
    printf("EPORT TEST\r\n");
    delayms(1000); // EPORT1_PIN5 EPORT1_PIN7 仿真脚 延时以防连不上仿真
//    SwitchPinFunction(EPORT0_0_FUN,EPORT0_0_FUN);
#ifdef OUTPUT_TEST
    eport_singleoutput_test(EPORT0, EPORT0_PIN0);
#elif INPUT_TEST
    eport_singleinput_test(EPORT0, EPORT0_PIN0, PS_PULL_UP);
#elif INTERRUPT_TEST
    eport_singleinterrupu_test(EPORT0, EPORT0_PIN0, EPORT_FALLING_TRIGGER, PS_PULL_UP);
#endif
}

/** @} */  // 结束 EPORT 模块分组
/** @} */  // 结束外设模块分组
