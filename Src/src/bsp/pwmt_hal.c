/**
 * @file pwmt_hal.c
 * @author Product Application Department
 * @brief  PWMT模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "pwmt_hal.h"

// 全局变量定义
static pwmt_handle_t *g_hpwmt;
volatile uint8_t capintflag = 0;

// 函数定义

/**
 * @brief PWMT 模块复用使能函数
 *
 * @param module PWMT模块寄存器定义
 * @param ch 通道定义
 */
void hal_pwmt_swapenable(reg_pwmt_t *module, uint8_t ch)
{
}

/**
 * @brief PWMT 模块pwm输出初始化函数
 *
 * @param hpwmt PWMT配置句柄定义
 * @return uint8_t
 */
uint8_t hal_pwmt_pwmoutputinit(pwmt_handle_t *hpwmt)
{
    /* 计数器不使能 */
    drv_pwmt_counterenable(hpwmt->instance, DISABLE);

    /* 通道配置为输出 */
    drv_pwmt_channeloutput(hpwmt->instance, hpwmt->init.channel);

    /* PWM模式1-高电平有效*/
    drv_pwmt_outputcomparemode(hpwmt->instance, hpwmt->init.channel, PWM_MODE1);

    /* 使能预装载寄存器 */
    drv_pwmt_outputcomparepreloadenable(hpwmt->instance, hpwmt->init.channel);

    /* 低电平有效 */
    drv_pwmt_capturecompareoutputpolarity(hpwmt->instance, hpwmt->init.channel, BIT_RESET);

    /* 通道输出使能 */
    drv_pwmt_channeloutputenable(hpwmt->instance, hpwmt->init.channel, ENABLE);

    /* 设置占空比 */
    drv_pwmt_setdutyfactor(hpwmt->instance, hpwmt->init.channel, hpwmt->init.out.width);

    /* 死区时间 */
    if (hpwmt->init.out.deadzone > 0)
    {
        drv_pwmt_setdeadzone(hpwmt->instance, hpwmt->init.channel, hpwmt->init.out.deadzone);
    }

    /* 上拉使能 */
    drv_pwmt_pullenable(hpwmt->instance, hpwmt->init.channel, ENABLE);

    /* 设置分频系数 */
    drv_pwmt_setprescaler(hpwmt->instance, hpwmt->init.out.prescaler);

    /* 设置自动重装载值 */
    drv_pwmt_setperiod(hpwmt->instance, hpwmt->init.out.period);

    /* 计数器递增 */
    drv_pwmt_setcounterdir(hpwmt->instance, UP_COUNTER);

    /* 边缘对齐模式 */
    drv_pwmt_centeralignmode(hpwmt->instance, EDGE_ALIGN);

    /* 生成一个更新事件，相关寄存器将清零 */
    drv_pwmt_updtgeneration(hpwmt->instance);

    /* 使能自动重载预装载寄存器 */
    drv_pwmt_autoreloaden(hpwmt->instance);

    /* 主模式输出使能 */
    drv_pwmt_mainoutputen(hpwmt->instance);

    /* 断路使能 */
    drv_pwmt_breaken(hpwmt->instance, hpwmt->init.brk);

    /*TRGO触发模式*/
    drv_pwmt_trgomodesel(hpwmt->instance, hpwmt->init.trgo_mode);

    /* 使能PWMT引脚功能    */
    hal_pwmt_swapenable(hpwmt->instance, hpwmt->init.function);
    return 0;
}

/**
 * @brief PWMT 模块pwm使能函数
 *
 * @param hpwmt PWMT配置句柄定义
 * @param status 功能状态定义
 */
void hal_pwmt_pwmenable(pwmt_handle_t *hpwmt, functionalstate_t status)
{
    /* 计数器使能 */
    drv_pwmt_counterenable(hpwmt->instance, status);
}

/**
 * @brief PWMT 模块中断处理函数
 *
 */
void hal_pwmt_irqhandler(void)
{
    if (g_hpwmt->RisingCallback ||
        g_hpwmt->FallingCallback ||
        g_hpwmt->CaptureCallback)
    {
        if (g_hpwmt->RisingCallback)
        {
            g_hpwmt->RisingCallback((void *)g_hpwmt);
        }

        if (g_hpwmt->FallingCallback)
        {
            g_hpwmt->FallingCallback((void *)g_hpwmt);
        }

        if (g_hpwmt->CaptureCallback)
        {
            g_hpwmt->CaptureCallback((void *)g_hpwmt);
        }

        return;
    }
}

/**
 * @brief PWMT 模块捕获回调函数
 *
 * @param pwmt PWMT空句柄定义
 */
void hal_pwmt_capturecallback(void *pwmt)
{

    pwmt_handle_t *tmp_pwmt = (pwmt_handle_t *)pwmt;

    /* 输入捕获中断 */
    if (drv_pwmt_getdir(tmp_pwmt->instance, tmp_pwmt->init.channel) == PWMT_INPUT)
    {
        // capintflag |= (drv_pwmt_getstatusreg(tmp_pwmt->instance) & 0xff);
        // TO DO
        drv_pwmt_getinterruptstatus(tmp_pwmt->instance);
    }
    else /* 输出比较中断 */
    {
        // comintflag
    }

    drv_pwmt_clearinterruptstatus(tmp_pwmt->instance, (pwmt_int_t)capintflag);
}

/**
 * @brief PWMT 模块输入捕获初始化函数
 *
 * @param hpwmt PWMT配置句柄定义
 * @return uint8_t
 */
uint8_t hal_pwmt_inputcaptureinit(pwmt_handle_t *hpwmt)
{
    /* 配置为输入，映射端口可手动修改
     * input capture 1 映射端口为Ti1
     * input capture 2 映射端口为Ti2
     * input capture 3 映射端口为Ti3
     * input capture 4 映射端口为Ti4
     */
    drv_pwmt_channelinput(hpwmt->instance, hpwmt->init.channel);

    /* 捕获比较使能 */
    drv_pwmt_channelcaptureenable(hpwmt->instance, hpwmt->init.channel, ENABLE);

    /* 选择触发方式 */
    if (hpwmt->init.in.trigger != RESERVED_WAY)
    {
        drv_pwmt_settriggerway(hpwmt->instance, hpwmt->init.channel, hpwmt->init.in.trigger);
    }

    /* 中断使能 */
    drv_pwmt_interruptenable(hpwmt->instance, hpwmt->init.interrupr_type);

    /* 设置分频系数 */
    drv_pwmt_setprescaler(hpwmt->instance, hpwmt->init.in.prescaler);

    /* 设置自动重装载值 */
    drv_pwmt_setperiod(hpwmt->instance, hpwmt->init.in.period);
    /* 使能PWMT引脚功能    */
    hal_pwmt_swapenable(hpwmt->instance, hpwmt->init.function);
    return 0;
}

/**
 * @brief PWMT 模块通道输出配置函数
 *
 * @param hpwmt PWMT配置句柄定义
 * @param ch 通道定义
 * @return uint8_t
 */
uint8_t hal_channel_outputconfiguration(pwmt_handle_t *hpwmt, uint8_t ch)
{
    /* 使能PWMT引脚功能    */
    hal_pwmt_swapenable(hpwmt->instance, ch);
    /* 通道配置为输出 */
    drv_pwmt_channeloutput(hpwmt->instance, ch);
    /* PWM模式1-高电平有效*/
    drv_pwmt_outputcomparemode(hpwmt->instance, ch, PWM_MODE1);
    /* 低电平有效 */
    drv_pwmt_capturecompareoutputpolarity(hpwmt->instance, ch, BIT_RESET);
    /* 通道输出使能 */
    drv_pwmt_channeloutputenable(hpwmt->instance, ch, ENABLE);
    /* 设置占空比 */
    drv_pwmt_setdutyfactor(hpwmt->instance, ch, hpwmt->init.out.width);
    /* 死区时间 */
    if (hpwmt->init.out.deadzone > 0)
    {
        drv_pwmt_setdeadzone(hpwmt->instance, ch, hpwmt->init.out.deadzone);
    }
    /* 上拉使能 */
    drv_pwmt_pullenable(hpwmt->instance, ch, ENABLE);
    return 0;
}
/**
 * @brief PWMT模块dma更新请求使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_dmaupdatereqen(reg_pwmt_t *ppwmt)
{
    drv_pwmt_updatedmarequestenable(ppwmt);
}

/**
 * @brief PWMT模块dma捕获比较1使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_dmacc1reqen(reg_pwmt_t *ppwmt)
{
    drv_pwmt_cc1dmarequestenable(ppwmt);
}

/**
 * @brief PWMT模块dma捕获比较2使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_dmacc2reqen(reg_pwmt_t *ppwmt)
{
    drv_pwmt_cc2dmarequestenable(ppwmt);
}

/**
 * @brief PWMT模块dma捕获比较3使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_dmacc3reqen(reg_pwmt_t *ppwmt)
{
    drv_pwmt_cc3dmarequestenable(ppwmt);
}

/**
 * @brief PWMT模块dma捕获比较4使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_dmacc4reqen(reg_pwmt_t *ppwmt)
{
    drv_pwmt_cc4dmarequestenable(ppwmt);
}

/**
 * @brief PWMT模块计数使能
 *
 * @param ppwmt PWMT配置句柄定义
 */
void hal_pwmt_counten(reg_pwmt_t *ppwmt)
{
    drv_pwmt_counterenable(ppwmt, ENABLE);
}

/**
 * @brief PMWT模块获取寄存器中断状态
 *
 * @param ppwmt PWMT配置句柄定义
 * @return uint8_t
 */
uint8_t hal_pwmt_getitstatus(reg_pwmt_t *ppwmt)
{
    return drv_pwmt_getinterruptstatus(ppwmt);
}

/**
 * @brief PMWT模块获取捕获比较值
 *
 * @param ppwmt PWMT配置句柄定义
 * @param portnum 端口定义
 * @return uint16_t
 */
uint16_t hal_pwmt_getcapval(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    return drv_pwmt_getccr(ppwmt, portnum);
}

/**
 * @brief PMWT模块清除中断状态
 *
 * @param ppwmt PWMT配置句柄定义
 * @param flag 中断方式标志
 */
void hal_pwmt_clritstatus(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    drv_pwmt_clearinterruptstatus(ppwmt, flag);
}

/**
 * @brief PMWT模块获取过采样标志
 *
 * @param ppwmt PWMT配置句柄定义
 * @param flag 中断方式标志
 * @return flagstatus_t
 */
flagstatus_t hal_pwmt_getcapflag(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    return drv_pwmt_getovercaptureflag(ppwmt, flag);
}

/**
 * @brief PMWT模块清除过采样标志
 *
 * @param ppwmt PWMT配置句柄定义
 * @param flag 中断方式标志
 * @return flagstatus_t
 */
void hal_pwmt_clrcapflag(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    drv_pwmt_clearovercaptureflag(ppwmt, flag);
}
