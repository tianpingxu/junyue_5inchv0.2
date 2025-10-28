/**
 * @file common.c
 * @author Product application department
 * @brief
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "common.h"

// 全局变量定义
/*
 * Arm Compiler 4/5
 */
#if defined(__CC_ARM)
uint32_t enter_critical_sr_save()
{
    register uint32_t __regPriMask __asm("primask");
    return (__regPriMask);
}

void exit_critical_sr_restore(uint32_t primask)
{
    register uint32_t __regPriMask __asm("primask");
    __regPriMask = (primask);
}

uint32_t Read_VEC()
{
    uint32_t vec_num;
    register uint32_t _reg_IPSR __asm("ipsr");

    vec_num = (_reg_IPSR & 0x1FF) - 16;

    return vec_num;
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
uint32_t enter_critical_sr_save()
{
    register uint32_t __regPriMask = 0;

    __asm volatile(

        "MRS %[__regPriMask] ,primask \n\t"

        : [__regPriMask] "+&r"(__regPriMask)
        :
        :);
    return (__regPriMask);
}

void exit_critical_sr_restore(uint32_t primask)
{
    register uint32_t __regPriMask = 0;

    __asm volatile(

        "MSR primask ,%[primask] \n\t"
        :
        : [primask] "r"(primask)
        :);
}

uint32_t Read_VEC()
{
    uint32_t vec_num = 0;
    register uint32_t _reg_IPSR = 0;
    __asm volatile(
        "MRS %[_reg_IPSR], ipsr \n\t"
        : [_reg_IPSR] "+&r"(_reg_IPSR)
        :
        :);
    vec_num = (_reg_IPSR & 0x1FF) - 16;

    return vec_num;
}

#endif
