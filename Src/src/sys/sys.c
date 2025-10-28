/**
 * @file sys.c
 * @author Product application department
 * @brief  系统时钟配置文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "sys.h"
#include "ssi_reg.h"
#include "cpm_drv.h"
#include "ssi_sram.h"
#include "updata.h"
#include "chipconfig.h"
#include "ssi_hal.h"

//全局变了定义
#define TRIM_VALUE_500M (*(volatile unsigned int *)(0x480000E8))

// 函数定义
#define drv_ssi_sraminit  (*(void (*)(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint32_t))(((uint32_t *)(0x20002801))))


/**
 * @brief 系统初始化，包括系统时钟、SSI初始化函数
 *
 */
void sys_init(void)
{
    sys_clkinit_t clk_init;
    /* 系统时钟源选择内部400M、内部8M、内部240M和外部12M，推荐内部400M  */
    clk_init.SysClkSource = CPM_SYSCLK_OSC400M;
    /* 系统时钟源可以trim到400M、480M */
    clk_init.SysClkTrim = OSC_480M_HZ;
    clk_init.CoreClkDiv = CLK_DIV_1;
    /* 最小2分频，最大256分频  */
    clk_init.SysClkDiv = CLK_DIV_2;
    /* 最小2分频，最大16分频  */
    clk_init.IpsClkDiv = CLK_DIV_2;
  //  g_trim_clk = clk_init.SysClkTrim;
    /* 初始化时钟 */
    sys_sysclkconfig(&clk_init);
}

/**
 * @brief 设置系统时钟函数
 *
 * @param[in] CPM_SYSCLKSource 配置的系统时钟源
 * @param[in] sys_clk_trim 系统时钟源Trim,注意只能Trim内部400M晶振
 * @param[in] sys_div 系统时钟源分频系数，取值范围【0x00~0xff】
 * @param[in] ips_div IPS时钟源分频系数，取值范围【0x00~0x0f】
 * @return @ref CPM_ErrCodeTypeDef
 */
void sys_sysclkconfig(sys_clkinit_t *pClkInit)
{
    uint32_t sample_delay, i;
    uint32_t core_clk,sys_clk,ips_clk;
    memcpy((unsigned char*)(0x20002800),updata_bin_data,totalbytes);
    if ((OSC_400M_HZ < pClkInit->SysClkTrim) && (CLK_DIV_2 == pClkInit->SysClkDiv))
    {
        drv_cpm_systemclkvreftrim(CPM_VREF_TRIM_121);
    }
    // 配置IPS时钟（分频系数不可以为0）
    if (CLK_DIV_1 == pClkInit->IpsClkDiv)
    {
        pClkInit->IpsClkDiv = pClkInit->IpsClkDiv + 1;
    }
    if(OSC_500M_HZ == pClkInit->SysClkTrim)
    {
        drv_cpm_clktrim(TRIM_VALUE_500M & 0x01FFFFFF);//F48
        sample_delay = 0x00000002;
    }
    else
    {
        sample_delay = 0x00010001;
    }
    drv_ssi_sraminit(SSI_ID,pClkInit->CoreClkDiv,pClkInit->SysClkDiv,pClkInit->IpsClkDiv,2,sample_delay);
    // 获取内核时钟 
    core_clk = drv_cpm_getcoreclk();
    // 获取系统时钟
    sys_clk = drv_cpm_getsysclk();

    // 系统时钟60M以下，电压trim到0.9V，可以降低功耗
    if (sys_clk <= 60000000)
    drv_cpm_systemclkvreftrim(CPM_VREF_TRIM_105);
}

/**
 * @brief 获取系统时钟函数
 *
 */
void sys_cpm_getclk(void)
{

  //  g_trim_clk = drv_cpm_gettrimclk();
    // 获取内核时钟
    g_core_clk = drv_cpm_getcoreclk();
    // 获取系统时钟
    g_sys_clk = drv_cpm_getsysclk();

    // 获取ips时钟
    g_ips_clk = drv_cpm_getipsclk();

    // 获取ahb3时钟
    g_ahb3_clk = drv_cpm_getahbclk();
}
/**
 * @brief CACHE 初始化函数
 *
 */
void sys_cacheinit(void)
{
}

/**
 * @brief 芯片启动模式设置函数
 *
 * @param Mode 启动模式
 * @param ResetEN 是否复位
 */
void sys_startupconfig(startupmode_t Mode, functionalstate_t ResetEN)
{
    if (Mode == Startup_From_ROM)
    {
        if(SSI_ID == SSIID1)
        hal_ssi_flash_sector_erase(0x10000000);
        else if(SSI_ID == SSIID3)
        hal_ssi_flash_sector_erase(0x14000000);
    }
    else if (Mode == Startup_From_FLASH)
    {
    }
    else
    {
        return;
    }

    if (ResetEN == ENABLE)
    {
        // 恢复boot后，不断电直接重启
        //         Set_POR_Reset();
    }

    while (1)
        ;
}

/**
 * @brief 系统串口初始化函数
 * @param UARTx 串口号
 * @param pclk IPS时钟
 * @param bound 波特率
 */
void sys_uartdebuginit(uart_typedef_t *UARTx, uint32_t pclk, uint32_t bound)
{
    uart_debug_init(UARTx, pclk, bound);
}

/**
 * @brief 系统进入待机模式函数
 *
 */
void sys_standby(void)
{
    // 使能SLEEPDEEP位 (SYS->CTRL)
    SCB->SCR |= 1 << 2;

    _cpm_set_vcc_3v3_lv_detect_dis;

    // 执行WFI指令,进入待机模式
    wfi_set();

    _cpm_set_vcc_3v3_lv_detect_en;
}

/**
 * @brief 系统软复位函数
 *
 */
void sys_soft_reset(void)
{
    SCB->AIRCR = 0X05FA0000 | (uint32_t)0x04;
}

/**
 * @brief 系统停止运行函数
 *
 */
void wfi_set(void)
{
    __ASM volatile("wfi");
}

// 设置栈顶地址
// addr:栈顶地址

/*
 * Arm Compiler 4/5
 */
#if defined(__CC_ARM)

__asm void MSR_MSP(uint32_t addr)
{
    MSR MSP, r0 // set Main Stack value
    BX r14
}
/*
 * Arm Compiler 6.6 LTM (armclang)
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) && (__ARMCC_VERSION < 6100100)

#error "This case not support \r\n"
/*
 * Arm Compiler above 6.10.1 (armclang)
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
/*
Modified by ZYQ to support GNU Assembly syntax.
*/
void MSR_MSP(uint32_t addr)
{

    __ASM volatile(
        "MSR MSP, r0 \n\t" // set Main Stack value
        "BX r14         \n\t"

    );
}

#endif
