/**
 * @file status.h
 * @author Product application department
 * @brief  状态定义头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef _STATUS_H_
#define _STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief  状态说明枚举定义
 */
typedef enum
{
    STATUS_OK = 0x00,
    STATUS_RESET = 0x01,
    STATUS_READY = 0x02,
    STATUS_ERROR = 0x03,
    STATUS_BUSY = 0x04,
    STATUS_TIMEOUT = 0x05,
    STATUS_IDLE = 0x06,
    STATUS_FULL = 0x07,
    STATUS_HANDLE_ERR = 0x08,
    STATUS_TYPE_ERR = 0x09,
    STATUS_NUM_ERR = 0x0A,
    STATUS_ADDR_ERR = 0x0B,
} status_t;

/**
 * @brief  状态锁枚举定义
 */
typedef enum
{
    UNLOCKED = 0x00,
    LOCKED = 0x01
} lock_t;

#define MAX_DELAY 0xFFFFFFFF

#if (USE_RTOS == 1)
#error " USE_RTOS should be 0 in the current HAL release "
#else
#define __LOCK(__HANDLE__)                \
    do                                    \
    {                                     \
        if ((__HANDLE__)->lock == LOCKED) \
        {                                 \
            return STATUS_BUSY;           \
        }                                 \
        else                              \
        {                                 \
            (__HANDLE__)->lock = LOCKED;  \
        }                                 \
    } while (0)

#define __UNLOCK(__HANDLE__)           \
    do                                 \
    {                                  \
        (__HANDLE__)->lock = UNLOCKED; \
    } while (0)
#endif /* USE_RTOS */

#ifndef __GNUC__
#define __GNUC__
#endif

#if defined(__GNUC__)
#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

#ifndef WEAK
#define WEAK __attribute__((weak)) /*!< Defines 'WEAK' permissions */
#endif                             /* WEAK */

#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */

#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif

#endif
