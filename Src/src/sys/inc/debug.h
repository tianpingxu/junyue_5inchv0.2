/**
 * @file debug.h
 * @author Product application department
 * @brief  DEBUG 打印配置头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "drv.h"
#include "uart_reg.h"
#include "cache_util.h"

#define PRINTF_DSP 1

#if PRINTF_DSP
#include "stdio.h"
#else
#include <stdarg.h>

// 全局变量定义
#define printf xprintf

// #define _USE_XFUNC_OUT    1    /* 1: Use output functions */
#define _CR_CRLF 1            /* 1: Convert \n ==> \r\n in the output char */
#define _USE_LONGLONG 0       /* 1: Enable long long integer in type "ll". */
#define _LONGLONG_t long long /* Platform dependent long long integer type */
#endif

#define DEBUG

#define DEBUG_PRINTF 1

#define UART_CR2_TE_MASK 0x08
#define UART_SR1_TDRE_MASK 0x80
#define UART_SR1_TC_MASK 0x40

/* Exported macro ------------------------------------------------------------*/
#ifdef DEBUG

#define LOG(fmt, ...)                                                                  \
    do                                                                                 \
    {                                                                                  \
        if (DEBUG_PRINTF == 1)                                                         \
        {                                                                              \
            uint32_t tmp = SCB->DFSR;                                                  \
            printf("[D][%s\t%d]\t" fmt "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); \
        }                                                                              \
    } while (0)

#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

// 函数声明
void xprintf(const char *fmt, ...);
void assert_failed(uint8_t *file, uint32_t line);
void uart_debug_init(uart_typedef_t *UARTx, uint32_t pclk, uint32_t bound);
uint8_t Getchar(void);
void Putchar(int ch);
#else
#define assert_param(expr) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif
