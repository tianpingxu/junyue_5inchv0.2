/**
 * @file pit32_drv.h
 * @author Product application department
 * @brief  PIT32 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __PIT32_DRV_H
#define __PIT32_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "pit32_reg.h"
    
// 全局变量定义
// PCSR
#define _pit32_start(pit) _bit_set(pit->PCSR, PIT_PCSR_EN)                  // PIT功能启动
#define _pit32_stop(pit) _bit_clr(pit->PCSR, PIT_PCSR_EN)                   // PIT功能停止
#define _pit32_en_reload(pit) _bit_set(pit->PCSR, PIT_PCSR_RLD)             // 当PIT计数器为0时,重载PMR值到PIT计数器
#define _pit32_dis_reload(pit) _bit_clr(pit->PCSR, PIT_PCSR_RLD)            // 当PIT计数器为0时,重载0xFFFF到PIT计数器
#define _pit32_get_int_flag(pit) _reg_chk(pit->PCSR, PIT_PCSR_PIF)          // 检测PIT中断标志位
#define _pit32_clr_int_flag(pit) _bit_set(pit->PCSR, PIT_PCSR_PIF)          // 清除PIT中断标志位
#define _pit32_en_interrupt(pit) _bit_set(pit->PCSR, PIT_PCSR_PIE)          // PIT中断请求开启
#define _pit32_dis_interrupt(pit) _bit_clr(pit->PCSR, PIT_PCSR_PIE)         // PIT中断请求关闭
#define _pit32_reload_mode_immediate(pit) _bit_set(pit->PCSR, PIT_PCSR_OVW) // 写PMR寄存器,则立即更新PIT计数器
#define _pit32_reload_mode_cnt_zero(pit) _bit_clr(pit->PCSR, PIT_PCSR_OVW)  // 写PMR寄存器,不立即更新PIT计数器,直到PIT计数为0
#define _pit32_set_debug_stop(pit) _bit_set(pit->PCSR, PIT_PCSR_PDBG)       // 在调试模式下，PIT功能停止
#define _pit32_set_debug_run(pit) _bit_clr(pit->PCSR, PIT_PCSR_PDBG)        // 在调试模式下，PIT功能不受影响
#define _pit32_set_doze_stop(pit) _bit_set(pit->PCSR, PIT_PCSR_PDOZE)       // 在瞌睡模式下，PIT功能停止
#define _pit32_set_doze_run(pit) _bit_clr(pit->PCSR, PIT_PCSR_PDOZE)        // 在瞌睡模式下，PIT功能不受影响
#define _pit32_set_prescaler(pit, value) _reg_modify(pit->PCSR, 0xF0FF, value);
#define _pit32_clr_pcsr_all(pit) _reg_clear(pit->PCSR)
#define _pit32_get_pcsr_all(pit) _reg_read(pit->PCSR)
#define _pit32_set_pcsr_all(pit, value) _reg_write(pit->PCSR)

// PMR
#define _pit32_clr_pmr_all(pit) _reg_clear(pit->PMR)
#define _pit32_get_pmr_all(pit) _reg_read(pit->PMR)
#define _pit32_set_pmr_all(pit, value) _reg_write(pit->PMR, value)

// PCNTR
#define _pit32_get_pcntr_all(pit) _reg_read(pit->PCNTR)

/**
 *  @brief  PIT32 模块计数器数值计算函数
 *
 */
#define pit32_calc_counter(clk, div, time) (uint32_t)(clk / (1 << (div >> 8)) * time)

/**
 *  @brief  PIT32 模块分频定义函数
 *
 */
typedef enum
{
    PIT32_CLK_DIV_1 = PIT_PCSR_PRESCALER_1,         // 1分频
    PIT32_CLK_DIV_2 = PIT_PCSR_PRESCALER_2,         // 2分频
    PIT32_CLK_DIV_4 = PIT_PCSR_PRESCALER_4,         // 4分频
    PIT32_CLK_DIV_8 = PIT_PCSR_PRESCALER_8,         // 8分频
    PIT32_CLK_DIV_16 = PIT_PCSR_PRESCALER_16,       // 16分频
    PIT32_CLK_DIV_32 = PIT_PCSR_PRESCALER_32,       // 32分频
    PIT32_CLK_DIV_64 = PIT_PCSR_PRESCALER_64,       // 64分频
    PIT32_CLK_DIV_128 = PIT_PCSR_PRESCALER_128,     // 128分频
    PIT32_CLK_DIV_256 = PIT_PCSR_PRESCALER_256,     // 256分频
    PIT32_CLK_DIV_512 = PIT_PCSR_PRESCALER_512,     // 512分频
    PIT32_CLK_DIV_1024 = PIT_PCSR_PRESCALER_1024,   // 1024分频
    PIT32_CLK_DIV_2048 = PIT_PCSR_PRESCALER_2048,   // 2048分频
    PIT32_CLK_DIV_4096 = PIT_PCSR_PRESCALER_4096,   // 4096分频
    PIT32_CLK_DIV_8192 = PIT_PCSR_PRESCALER_8192,   // 8192分频
    PIT32_CLK_DIV_16384 = PIT_PCSR_PRESCALER_16384, // 16384分频
    PIT32_CLK_DIV_32768 = PIT_PCSR_PRESCALER_32768  // 32768分频
} pit32_clkdiv_t;
// 函数声明
void drv_pit32_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_interrupt_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_reload_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_immediately_update_cnt_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_debug_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_doze_cmd(reg_pit32_t *ppit32, uint8_t status);
void drv_pit32_set_prescaler(reg_pit32_t *ppit32, pit32_clkdiv_t prescaler);
void drv_pit32_set_counter(reg_pit32_t *ppit32, uint32_t cnt);
uint32_t drv_pit32_get_counter(reg_pit32_t *ppit32);
void drv_pit32_clear_intr_flag(reg_pit32_t *ppit32);
#ifdef __cplusplus
}
#endif

#endif
