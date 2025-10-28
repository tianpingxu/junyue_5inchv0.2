/**
 * @file ioctrl_hal.c
 * @author Product Application Department
 * @brief  IOCTRL 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "ioctrl_hal.h"
#include "eport_hal.h"

// 函数定义

/**
 * @brief IOCTRL 模块SPI初始化函数
 * @param pIOSPIInit 指向IO control SPI初始化结构体的指针
 * @return

 */
status_t hal_ioctrl_spiinit(ioctrl_spiinit_t *pIOSPIInit)
{
    if (pIOSPIInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_setspiie(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->ie);
        drv_ioctrl_setspips(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->ps);
        drv_ioctrl_setspisr(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->sr);
        drv_ioctrl_setspiis(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->is);
    }
    else
    {
        drv_ioctrl_setspiie(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->ie);
        drv_ioctrl_setspids(pIOSPIInit->id, pIOSPIInit->pins, pIOSPIInit->ds);
    }
    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块I2C初始化函数
 * @param pIOI2CInit 指向IO control I2C初始化结构体的指针
 * @return
 */
status_t hal_ioctrl_i2cinit(ioctrl_i2cinit_t *pIOI2CInit)
{
    if (pIOI2CInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_seti2cie(pIOI2CInit->id, pIOI2CInit->pins, pIOI2CInit->ie);
        drv_ioctrl_seti2cps(pIOI2CInit->id, pIOI2CInit->pins, pIOI2CInit->ps);
        drv_ioctrl_seti2csr(pIOI2CInit->sr);
        drv_ioctrl_seti2cis(pIOI2CInit->is);
    }
    else
    {
        drv_ioctrl_seti2cie(pIOI2CInit->id, pIOI2CInit->pins, pIOI2CInit->ie);
        drv_ioctrl_seti2cds(pIOI2CInit->ds);
    }

    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块UART初始化函数
 * @param pIOUARTInit 指向IO control UART初始化结构体的指针
 * @return
 */
status_t hal_ioctrl_uartinit(ioctrl_uartinit_t *pIOUARTInit)
{
    if (pIOUARTInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_setuartps(pIOUARTInit->id, pIOUARTInit->pins, pIOUARTInit->ps);
        drv_ioctrl_setuartsr(pIOUARTInit->sr);
        drv_ioctrl_setuartis(pIOUARTInit->is);
    }
    else
    {
        drv_ioctrl_setuartds(pIOUARTInit->ds);
    }

    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块SSI1初始化函数
 * @param pIOSSIInit 指向IO control SSI1初始化结构体的指针
 * @return
 */

status_t hal_ioctrl_ssiinit(ioctrl_ssiinit_t *pIOSSIInit)
{
    if (pIOSSIInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_setssiie(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->ie);
        drv_ioctrl_setssips(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->ps);
        drv_ioctrl_setssisr(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->sr);
    }
    else
    {
        drv_ioctrl_setssiie(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->ie);
        drv_ioctrl_setssiide(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->ode);
        drv_ioctrl_setssids(pIOSSIInit->id, pIOSSIInit->pins, pIOSSIInit->ds);
    }
    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块配置GPIO输入函数，上下拉,电压转换率
 *
 * @param pEPORTInit eport初始化结构体的指针
 * @return status_t 是否成功
 */
status_t hal_ioctrl_eportinit(hal_ioctrl_eportinit_t *pEPORTInit)
{
    if (pEPORTInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_seteportps(pEPORTInit->id,pEPORTInit->pins, pEPORTInit->ps);
        drv_ioctrl_seteportsr(pEPORTInit->id,pEPORTInit->pins, pEPORTInit->sr);
    }
    else
    {
        drv_ioctrl_seteportds(pEPORTInit->id,pEPORTInit->pins, pEPORTInit->ds);
    }

    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块SPI初始化函数
 * 
 * @param pIOSPIInit 指向IO control SPI初始化结构体的指针
 * @return status_t
 */
status_t hal_ioctrl_i2sinit(ioctrl_i2sinit_t *pIOI2SInit)
{
    if (pIOI2SInit->ie == IE_INPUT_EN)
    {
        drv_ioctrl_seti2sie(pIOI2SInit->id, pIOI2SInit->pins, pIOI2SInit->ie);
        drv_ioctrl_seti2sps(pIOI2SInit->id, pIOI2SInit->pins, pIOI2SInit->ps);
        drv_ioctrl_seti2ssr(pIOI2SInit->id, pIOI2SInit->pins, pIOI2SInit->sr);
    }
    else
    {
        drv_ioctrl_seti2sie(pIOI2SInit->id, pIOI2SInit->pins, pIOI2SInit->ie);
        drv_ioctrl_seti2sds(pIOI2SInit->id, pIOI2SInit->pins, pIOI2SInit->ds);
    }
    return STATUS_OK;
}

/**
 * @brief IOCTRL 模块SDH初始化函数
 * 
 * @param pIOSDHInit IOCTRL 模块SDH初始化结构体定义
 * @return status_t 
 */
status_t hal_ioctrl_sdhinit(ioctrl_sdhinit_t *pIOSDHInit)
{
    drv_ioctrl_setsdhpue(pIOSDHInit->pue);
    return STATUS_OK;
    // TO DO: other settings
}
