/**
 * @file ioctrl_hal.h
 * @author Product Application Department
 * @brief  IOCTRL 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IOCTRL_HAL_H__
#define __IOCTRL_HAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "ioctrl_drv.h"
#include "status.h"
    
// 全局变量定义
#define _IOCTRL_CLKOUT_SWAP_EN _ioctrl_clkrstcr_clkout_en
#define _IOCTRL_CLKOUT_SWAP_DIS _ioctrl_clkrstcr_clkout_dis
#define _IOCTRL_RSTOUT_SWAP_EN _ioctrl_clkrstcr_rstout_en
#define _IOCTRL_RSTOUT_SWAP_DIS _ioctrl_clkrstcr_rstout_dis

/**
 * @brief  IOCTRL 模块SPI初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_spiid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    ioctrl_spipin_t pins;
} ioctrl_spiinit_t;

/**
 * @brief IOCTRL I2C初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_i2cid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    uint8_t pins;
} ioctrl_i2cinit_t;

/**
 * @brief IOCTRL UART初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_uartid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    uint8_t pins;
} ioctrl_uartinit_t;

/**
 * @brief IOCTRL EPORT初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_eportid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    uint8_t pins;
} ioctrl_eportinit_t;

/**
 * @brief IOCTRL SSI初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_ssiid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_pue_t pue;
    ioctrl_ode_t ode;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    uint8_t pins;
} ioctrl_ssiinit_t;

/**
 * @brief IOCTRL 输入类型初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_eportid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    uint8_t pins;
} hal_ioctrl_eportinit_t;

/**
 * @brief IOCTRL 模块SPI初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_i2sid_t id;
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_ps_t ps;
    ioctrl_ie_t ie;
    ioctrl_i2spin_t pins;
} ioctrl_i2sinit_t;

/**
 * @brief IOCTRL 模块SDH初始化结构体定义
 * 
 */
typedef struct
{
    ioctrl_ds_t ds;
    ioctrl_sr_t sr;
    ioctrl_is_t is;
    ioctrl_pue_t pue;
} ioctrl_sdhinit_t;


// 函数声明
status_t hal_ioctrl_spiinit(ioctrl_spiinit_t *pIOSPIInit);
status_t hal_ioctrl_i2cinit(ioctrl_i2cinit_t *pIOI2CInit);
status_t hal_ioctrl_uartinit(ioctrl_uartinit_t *pIOUARTInit);
status_t hal_ioctrl_ssiinit(ioctrl_ssiinit_t *pIOSSIInit);
status_t hal_ioctrl_eportinit(hal_ioctrl_eportinit_t *pEPORTInit);
status_t hal_ioctrl_i2sinit(ioctrl_i2sinit_t *pIOI2SInit);
status_t hal_ioctrl_sdhinit(ioctrl_sdhinit_t *pIOSDHInit);

#ifdef __cplusplus
}
#endif

#endif