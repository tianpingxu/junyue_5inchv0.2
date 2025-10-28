/**
 * @file i2c_hal.c
 * @author Product Application Department
 * @brief  I2C 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
 
// 头文件包含
#include "i2c_hal.h"

// 全局变量定义
volatile static i2c_handle_t *g_hi2c;

// 函数定义

/**
 * @brief I2C 模块初始化函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @return status_t
 */
status_t hal_i2c_init(i2c_handle_t *hi2c)
{

    hi2c->State = HAL_I2C_STATE_BUSY;

    /*初始化硬件层相关*/
    drv_i2c_init(hi2c->Instance, &hi2c->Init);

    hi2c->XferCnt = 0;
    hi2c->XferSize = 0;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    /*状态更改为READY*/
    hi2c->State = HAL_I2C_STATE_READY;
    g_hi2c = hi2c;
    return (STATUS_OK);
}

/**
 * @brief I2C 模块查循方式发送数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param MemAddress 从机寄存器地址;
 * @param MemAddSize 从机寄存器地址长度，单位字节;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_memwrite(i2c_handle_t *hi2c,
                          uint16_t DevAddress,
                          uint32_t MemAddress,
                          uint16_t MemAddSize,
                          uint8_t *pData,
                          uint16_t Size,
                          uint32_t Timeout)

{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    drv_i2c_dis(hi2c->Instance);
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;
        /*中断处理函数为空*/
        hi2c->XferISR = 0;
        drv_i2c_en(hi2c->Instance);
        DrvStatus = drv_i2c_memwrite(hi2c->Instance,
                                     DevAddress,
                                     hi2c->Init.AddBits,
                                     MemAddress,
                                     MemAddSize,
                                     hi2c->Init.HighSpeed,
                                     hi2c->pXferBuf,
                                     hi2c->XferSize,
                                     Timeout);

        if (DrvStatus != STATUS_OK)
        {
            hi2c->State = HAL_I2C_STATE_READY;
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块查循方式读取数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param MemAddress 从机寄存器地址;
 * @param MemAddSize 从机寄存器地址长度，单位字节;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_memread(i2c_handle_t *hi2c,
                         uint16_t DevAddress,
                         uint32_t MemAddress,
                         uint16_t MemAddSize,
                         uint8_t *pData,
                         uint16_t Size,
                         uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;

        /*中断处理函数为空*/
        hi2c->XferISR = 0;

        DrvStatus = drv_i2c_memread(hi2c->Instance,
                                    DevAddress,
                                    hi2c->Init.AddBits,
                                    MemAddress,
                                    MemAddSize,
                                    hi2c->Init.HighSpeed,
                                    hi2c->pXferBuf,
                                    hi2c->XferSize,
                                    Timeout);

        if (DrvStatus != STATUS_OK)
        {
            hi2c->State = HAL_I2C_STATE_READY;
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块中断处理函数
 *
 */
void hal_i2c_irqhandler(void)
{
    uint8_t BasicFlags;
    uint8_t SlaveHighspeedFlags;
    uint8_t ItSource;

    drv_i2c_getitflags(g_hi2c->Instance, &BasicFlags, &SlaveHighspeedFlags);
    drv_i2c_getitsource(g_hi2c->Instance, &ItSource);

    if (g_hi2c->XferISR != NULL)
    {
        g_hi2c->XferISR((i2c_handle_t *)g_hi2c,
                        BasicFlags,
                        SlaveHighspeedFlags,
                        ItSource);
    }
}

/**
 * @brief I2C 模块查循方式通过指定的I2C端口发送数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_mastertransmit(i2c_handle_t *hi2c,
                                    uint16_t DevAddress,
                                    uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /**/
        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;
        /*中断处理函数为空*/
        hi2c->XferISR = 0;

        DrvStatus = drv_i2c_transmit(hi2c->Instance,
                                     hi2c->Init.Add,
                                     hi2c->Init.AddBits,
                                     hi2c->Init.HighSpeed,
                                     hi2c->pXferBuf,
                                     hi2c->XferSize,
                                     Timeout);

        if (DrvStatus != STATUS_OK)
        {
            hi2c->State = HAL_I2C_STATE_READY;
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块查循方式通过指定的I2C端口接收数据
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_masterreceive(i2c_handle_t *hi2c,
                                   uint16_t DevAddress,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /**/
        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;
        /*中断处理函数为空*/
        hi2c->XferISR = 0;

        DrvStatus = drv_i2c_receive(hi2c->Instance,
                                    hi2c->Init.Add,
                                    hi2c->Init.AddBits,
                                    hi2c->Init.HighSpeed,
                                    hi2c->pXferBuf,
                                    hi2c->XferSize,
                                    Timeout);

        if (DrvStatus != STATUS_OK)
        {
            hi2c->State = HAL_I2C_STATE_READY;
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块从模式查循方式通过指定的I2C端口发送数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_slavetransmit(i2c_handle_t *hi2c,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;
        /*中断处理函数为空*/
        hi2c->XferISR = 0;

        DrvStatus = drv_i2c_slavetransmit(hi2c->Instance,
                                          hi2c->pXferBuf,
                                          hi2c->XferSize,
                                          Timeout);

        if (DrvStatus != STATUS_OK)
        {
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (DrvStatus);
}

/**
 * @brief I2C 模块从模式查循方式通过指定的I2C端口接收数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param pData 待接收数据指针;
 * @param Size 待接收数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_slavereceive(i2c_handle_t *hi2c,
                                  uint8_t *pData,
                                  uint16_t Size,
                                  uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /**/
        hi2c->State = HAL_I2C_STATE_BUSY_RX;

        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;
        /*中断处理函数为空*/
        hi2c->XferISR = 0;

        DrvStatus = drv_i2c_slavereceive(hi2c->Instance,
                                         hi2c->pXferBuf,
                                         hi2c->XferSize,
                                         Timeout);

        if (DrvStatus != STATUS_OK)
        {
            return (DrvStatus);
        }

        hi2c->State = HAL_I2C_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (DrvStatus);
}

/**
 * @brief I2C 模块作为主机模式时中断服务函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param BasicFlags 除高速模式之外状态;
 * @param SlaveHighspeedFlags 高速模式状态;
 * @param ItSource 中断源;
 */
void hal_i2c_masterirqhandler(i2c_handle_t *hi2c,
                              uint8_t BasicFlags,
                              uint8_t SlaveHighspeedFlags,
                              uint8_t ItSource)
{
    //    uint32_t loop = 0;
    uint8_t I2CStatus;
    uint8_t I2CHighspeedStatus;
    //   volatile uint8_t tmp = 0;
    uint8_t TmpItSourceFlag;

    /**************************************************************/
    /*获取中断状态*/
    I2CStatus = BasicFlags;
    I2CHighspeedStatus = SlaveHighspeedFlags;
    I2CHighspeedStatus = I2CHighspeedStatus; // to eliminate warning
    TmpItSourceFlag = ItSource & I2C_IT_INDEX_IEN;
    TmpItSourceFlag = TmpItSourceFlag; // to eliminate warning
    if ((I2CStatus & (I2C_FLAG_RC | I2C_FLAG_TF)))
    {
        {
            if ((I2CStatus & I2C_FLAG_RXTX) != I2C_FLAG_RXTX)
            {
                /**************************************************************/
                /*处于接收模式:接收数据或者发送完读取请求之后的中断*/
                if (hi2c->State == HAL_I2C_STATE_BUSY_DEVADD_READ)
                {
                    /*转入接收数据阶段*/
                    if (hi2c->XferSize == 1)
                    {
                        drv_i2c_nack(hi2c->Instance);
                    }
                    else
                    {
                        drv_i2c_ack(hi2c->Instance);
                    }
                    hi2c->State = HAL_I2C_STATE_BUSY_RX;
                    hi2c->XferCnt = 0;
                }
                else
                {
                    /*接收到的是数据*/
                    drv_i2c_getdr(hi2c->Instance, (hi2c->pXferBuf + hi2c->XferCnt));
                    hi2c->XferCnt++;

                    if (hi2c->XferCnt >= hi2c->XferSize)
                    {
                        hi2c->XferCnt = hi2c->XferSize;

/*产生停止条件:因无停止条件中断，需要查询BUSY*/
#if 0
                        drv_i2c_mastergeneratestop(hi2c->Instance);
#else
                        drv_i2c_mastergeneratestop(hi2c->Instance, DISABLE, 0);
#endif

                        drv_i2c_disit(hi2c->Instance);

                        hi2c->State = HAL_I2C_STATE_READY;
                    }
                    else
                    {
                        if (hi2c->XferSize > 1)
                        {
                            if (hi2c->XferCnt == (hi2c->XferSize - 1))
                            {
                                /*最后一个字节应答*/
                                drv_i2c_nack(hi2c->Instance);
                            }
                            else
                            {
                                /*应答*/
                                drv_i2c_ack(hi2c->Instance);
                            }
                        }
                    }
                }
            } /*接收模式*/
            /**************************************************************/
            /**************************************************************/
            else
            {
                // if(hi2c->State == HAL_I2C_STATE_BUSY_MEM_TX)
                {
                    if (hi2c->XferCnt == hi2c->XferSize)
                    {
                        hi2c->State = HAL_I2C_STATE_READY;
                        hi2c->XferCnt = hi2c->XferSize;
/*发送停止条件*/
/*产生停止条件:因无停止条件中断，需要查询BUSY*/
#if 0
                            _i2c_generate_stop(hi2c->Instance);
#else
                        drv_i2c_mastergeneratestop(hi2c->Instance, DISABLE, 0);
#endif

                        drv_i2c_disit(hi2c->Instance);
                    }
                    else
                    {
                        /*数据阶段*/
                        drv_i2c_setdr(hi2c->Instance, *(hi2c->pXferBuf + hi2c->XferCnt));

                        hi2c->XferCnt++;
                    }
                }
            } /*发送模式*/

            /**************************************************************/
        }
    }
}

/**
 * @brief I2C 模块作为从机模式时中断服务函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param BasicFlags 除高速模式之外状态;
 * @param SlaveHighspeedFlags 高速模式状态;
 * @param ItSource 中断源;
 */
void hal_i2c_slaveirqhandler(i2c_handle_t *hi2c,
                             uint8_t BasicFlags,
                             uint8_t SlaveHighspeedFlags,
                             uint8_t ItSource)
{
    //    uint32_t loop = 0;
    uint8_t I2CStatus;
    uint8_t I2CHighspeedStatus;
    volatile uint8_t tmp = 0;
    uint8_t TmpItSourceFlag;
    /**************************************************************/

    /*获取中断状态*/
    I2CStatus = BasicFlags;
    I2CHighspeedStatus = SlaveHighspeedFlags;
    TmpItSourceFlag = ItSource & I2C_IT_INDEX_SLV_HSIE;
    TmpItSourceFlag = TmpItSourceFlag;
    if (I2CHighspeedStatus & I2C_FLAG_SLAVE_HIGH_SPEED)
    {
        /*write 1 to clear the flag*/
        drv_i2c_clrflagslavehighspeed(hi2c->Instance);
    }

    TmpItSourceFlag = ItSource & I2C_IT_INDEX_IEN;

    if ((I2CStatus & (I2C_FLAG_RC | I2C_FLAG_TF)))
    {
        if (I2CStatus & I2C_FLAG_AASLV)
        {
            /*地址匹配了*/
            if ((I2CStatus & I2C_FLAG_RXTX) != I2C_FLAG_RXTX)
            {
                /**************************************************************/
                /*处于接收模式:接收数据或者地址*/
                if ((I2CStatus & I2C_FLAG_TF) != I2C_FLAG_TF)
                {
                    /*接收到的是地址*/
                    /*应答主机同时清除RC标志*/
                    drv_i2c_ack(hi2c->Instance);

                    hi2c->XferCnt = 0;
                }
                else
                {
                    /*接收到的是数据*/
                    drv_i2c_getdr(hi2c->Instance, (hi2c->pXferBuf + hi2c->XferCnt));

                    hi2c->XferCnt++;
                    /*应答主机同时清除RC标志*/
                    drv_i2c_ack(hi2c->Instance);

                    if (hi2c->XferCnt >= hi2c->XferSize)
                    {
                        hi2c->State = HAL_I2C_STATE_READY;
                        hi2c->XferCnt = hi2c->XferSize;

                        drv_i2c_disit(hi2c->Instance);

                        //_i2c_dis_add_match_it(hi2c->Instance);
                    }
                }
            } /*接收模式*/
            /**************************************************************/
            /**************************************************************/
            else
            {
                /*发送模式*/
                drv_i2c_setdr(hi2c->Instance, *(hi2c->pXferBuf + hi2c->XferCnt));
                hi2c->XferCnt++;

                if (hi2c->XferCnt == hi2c->XferSize)
                {
                    hi2c->State = HAL_I2C_STATE_READY;
                    hi2c->XferCnt = hi2c->XferSize;

                    drv_i2c_disit(hi2c->Instance);

                    //_i2c_dis_add_match_it(hi2c->Instance);
                }
            } /*发送模式*/

            /**************************************************************/
        } /*地址匹配*/
    }
}

/**
 * @brief I2C 模块中断方式通过指定的I2C端口接收数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param pData 待接收数据指针;
 * @param Size 待接收数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_slavereceiveit(i2c_handle_t *hi2c,
                                    uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;

        /*中断服务函数中的回调函数*/
        if (hi2c->XferISR == NULL)
        {
            hi2c->XferISR = hal_i2c_slaveirqhandler;
        }

        /*中断接收时打开中断允许，此处以或的形式打开,因HAL_MspInit之中可能打开高速中断*/
        drv_i2c_enit(hi2c->Instance);

        //_i2c_en_add_match_it(hi2c->Instance);
    }
    else
    {
        return (STATUS_BUSY);
    }

    DrvStatus = drv_i2c_waitonflagtimeout(hi2c->Instance, I2C_FLAG_INDEX_BUSY, RESET, Timeout);

    if (DrvStatus != STATUS_OK)
    {
         return (DrvStatus);
    }

    return (DrvStatus);
}

/**
 * @brief I2C 模块中断方式通过指定的I2C端口发送数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_slavetransmitit(i2c_handle_t *hi2c,
                                     uint8_t *pData,
                                     uint16_t Size,
                                     uint32_t Timeout)
{
    status_t DrvStatus = STATUS_OK;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;

        /*中断服务函数中的回调函数*/
        if (hi2c->XferISR == NULL)
        {
            hi2c->XferISR = hal_i2c_slaveirqhandler;
        }

        /*中断接收时打开中断允许*/
        drv_i2c_enit(hi2c->Instance);

        //_i2c_en_add_match_it(hi2c->Instance);
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (DrvStatus);
}

/**
 * @brief I2C 模块中断方式通过指定的I2C端口发送数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param Timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_mastertransmitit(i2c_handle_t *hi2c,
                                      uint16_t DevAddress,
                                      uint8_t *pData,
                                      uint16_t Size,
                                      uint32_t Timeout)
{
    status_t  DrvStatus = STATUS_OK;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /**/
        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;

        hi2c->MemAdd = 0;
        hi2c->MemAddSize = 0;
        hi2c->XferFlag = 0;
        /*中断处理函数*/
        hi2c->XferISR = hal_i2c_masterirqhandler;

        /*发送起始条件*/
        drv_i2c_enit(hi2c->Instance);
        drv_i2c_disaddmatchit(hi2c->Instance);
        DevAddress &= ~0x01;
        drv_i2c_setdr(hi2c->Instance, DevAddress);
        drv_i2c_generate_start(hi2c->Instance);
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块查循方式通过指定的I2C端口接收数据函数
 *
 * @param hi2c 指向hal_i2c_handle_t结构体的指针,此结构体包含了I2C模块的配置信息;
 * @param DevAddress 从机地址;
 * @param pData 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t hal_i2c_masterreceiveit(i2c_handle_t *hi2c,
                                     uint16_t DevAddress,
                                     uint8_t *pData,
                                     uint16_t Size,
                                     uint32_t timeout)
{
    status_t  DrvStatus = STATUS_OK;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->State = HAL_I2C_STATE_BUSY_DEVADD_READ;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        hi2c->pXferBuf = pData;
        hi2c->XferCnt = 0;
        hi2c->XferSize = Size;

        hi2c->MemAdd = 0;
        hi2c->MemAddSize = 0;
        hi2c->XferFlag = 0;
        /*中断处理函数*/
        hi2c->XferISR = hal_i2c_masterirqhandler;

        /*发送起始条件*/
        DevAddress |= 0x01;
        drv_i2c_enit(hi2c->Instance);
        drv_i2c_disaddmatchit(hi2c->Instance);
        drv_i2c_setdr(hi2c->Instance, DevAddress);
        drv_i2c_generate_start(hi2c->Instance);
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}
