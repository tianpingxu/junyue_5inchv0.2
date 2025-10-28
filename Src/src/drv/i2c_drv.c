/**
 * @file i2c_drv.c
 * @author Product Application Department
 * @brief  I2C 模块驱动层
 * @version V1.0
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "i2c_drv.h"


// 函数定义

/**
 * @brief I2C 模块清除HS标志位函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_clrflagslavehighspeed(reg_i2c_t *pi2c)
{
    _i2c_clr_flag_slave_high_speed(pi2c);
}

/**
 * @brief I2C 模块使能地址匹配中断函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_enaddmatchit(reg_i2c_t *pi2c)
{
    _i2c_en_add_match_it(pi2c);
}

/**
 * @brief I2C 模块禁止地址匹配中断函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_disaddmatchit(reg_i2c_t *pi2c)
{
    _i2c_dis_add_match_it(pi2c);
}

/**
 * @brief I2C 模块应答函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_ack(reg_i2c_t *pi2c)
{
    _i2c_ack(pi2c);
}

/**
 * @brief I2C 模块不应答函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_nack(reg_i2c_t *pi2c)
{
    _i2c_nack(pi2c);
}

/**
 * @brief I2C 模块停止信号函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_stop(reg_i2c_t *pi2c)
{
    /*SDL 高 SDA LOW--HIGH*/
    _i2c_set_scl_bit(pi2c);
    _i2c_reset_sda_bit(pi2c);
    _i2c_set_sda_bit(pi2c);
}

/**
 * @brief I2C 模块恢复设置函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @return status_t
 */
status_t drv_i2c_deinit(reg_i2c_t *pi2c)
{
    pi2c->CCR = 0x00;

    return (STATUS_OK);
}

/**
 * @brief I2C 模块管脚切换功能函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_funcswap(reg_i2c_t *pi2c)
{
}

/**
 * @brief I2C 模块初始化设置函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pinit 指向i2c_init_t结构体的指针;
 * @return status_t
 */
status_t drv_i2c_init(reg_i2c_t *pi2c, i2c_init_t *pinit)
{
    //    uint8_t tmp_val = 0x00;

    drv_i2c_funcswap(pi2c);

    _i2c_en(pi2c);

    /*管脚配置为主功能*/
    _i2c_sda_configure_as_primary(pi2c);
    _i2c_scl_configure_as_primary(pi2c);

    if (pinit->Mode == I2C_MODE_MASTER)
    {
        _i2c_nack(pi2c);
        /*主模式初始化以下:
         *- 时钟频
         */
        if (pinit->ClockMode == I2C_CLOCK_MODE_TEST)
        {
            _i2c_en_clock_test_mode(pi2c);
        }
        else if (pinit->ClockMode == (uint8_t)I2C_CLOCK_MODE_NORMAL)
        {
            _i2c_en_clock_normal_mode(pi2c);
        }

        /*分频系数*/
        pi2c->PR &= ~(I2C_CLOCK_PRESCALE);
        pi2c->PR |= pinit->Prescaler & I2C_CLOCK_PRESCALE;
    }
    else if (pinit->Mode == I2C_MODE_SLAVE)
    {
        /*从机高速模式中断使能*/
        if (pinit->HighSpeed == ENABLE)
        {
            _i2c_en_slave_highspeed_it(pi2c);
        }

        /*从机地址*/
        if (pinit->AddBits == I2C_SLAVE_ADD_7BITS)
        {
#if 1
            //            pi2c->SARL = 0;
            pi2c->SARH = pinit->Add;
#else
            pi2c->SAR = pinit->Add;
            _i2c_ack(pi2c);
#endif
        }
        else if (pinit->AddBits == I2C_SLAVE_ADD_10BITS)
        {
#if 1
            /*MSB 2bits放在SAR的高8bits掩码11110XX0*/
            pi2c->SARH = (uint8_t)(((pinit->Add >> 8) << 1) | 0XF0);
            /*低8位*/
            pi2c->SARL = (pinit->Add) & 0XFF;
#else

#endif
        }
    }
    else
    {
        _i2c_dis(pi2c);
        return (STATUS_ERROR);
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 模块使能函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_en(reg_i2c_t *pi2c)
{
    _i2c_en(pi2c);
}

/**
 * @brief I2C 模块禁止函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_dis(reg_i2c_t *pi2c)
{
    _i2c_dis(pi2c);
}

/**
 * @brief I2C 模块使能或禁止函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param NewState 新的状态;
 */
void drv_i2c_cmd(reg_i2c_t *pi2c, functionalstate_t NewState)
{
    if (NewState == ENABLE)
    {
        _i2c_en(pi2c);
    }
    else
    {
        _i2c_dis(pi2c);
    }
}

/**
 * @brief I2C 模块中断使能函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_enit(reg_i2c_t *pi2c)
{
    _i2c_en_it(pi2c);
}

/**
 * @brief I2C 模块中断禁止函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_disit(reg_i2c_t *pi2c)
{
    _i2c_dis_it(pi2c);
}

/**
 * @brief I2C 模块获取状态标志函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param index 标志索引;
 * @param pFlag 状态值指针
 * @return status_t
 */
status_t drv_i2c_getflag(reg_i2c_t *pi2c,
                             i2c_flag_index_t index,
                             flagstatus_t *pFlag)
{
    *pFlag = (pi2c->SR & (1 << index)) ? SET : RESET;

    return (STATUS_OK);
}

/**
 * @brief I2C 模块等待标志状态函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param index 标志索引;
 * @param status 状态值;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_waitonflagtimeout(reg_i2c_t *pi2c,
                                       i2c_flag_index_t index,
                                       flagstatus_t status,
                                       uint32_t timeout)
{
#if 1
    flagstatus_t tmp_flag = RESET;

    if (timeout == 0)
    {
        do
        {
            delay(10000);
            drv_i2c_getflag(pi2c, index, &tmp_flag);
        } while (tmp_flag != status);
    }
    else
    {
        if (status == SET)
        {
            drv_i2c_getflag(pi2c, index, &tmp_flag);

            while (tmp_flag != SET)
            {
                timeout--;

                if (timeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }
                delay(10000);
                drv_i2c_getflag(pi2c, index, &tmp_flag);
            }
        }
        else if (status == RESET)
        {
            drv_i2c_getflag(pi2c, index, &tmp_flag);

            while (tmp_flag != RESET)
            {

                timeout--;

                if (timeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }
                delay(10000);
                drv_i2c_getflag(pi2c, index, &tmp_flag);
            }
        }
    }

#endif
    return STATUS_OK;
}

/**
 * @brief I2C 模块获取高速模式状态标志函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param status 状态值;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_waitonslvhsflagtimeout(reg_i2c_t *pi2c,
                                            flagstatus_t status,
                                            uint32_t timeout)
{
    flagstatus_t tmp_flag = RESET;

    if (timeout == 0)
    {
        do
        {
            if (_i2c_get_flag_slave_high_speed(pi2c))
                tmp_flag = SET;
            else
                tmp_flag = RESET;
        } while (tmp_flag != SET);
    }
    else
    {
        if (status == SET)
        {
            if (_i2c_get_flag_slave_high_speed(pi2c))
                tmp_flag = SET;
            else
                tmp_flag = RESET;

            while (tmp_flag != SET)
            {
                timeout--;

                if (timeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }

                if (_i2c_get_flag_slave_high_speed(pi2c))
                    tmp_flag = SET;
                else
                    tmp_flag = RESET;
            }
        }
        else if (status == RESET)
        {
            if (_i2c_get_flag_slave_high_speed(pi2c))
                tmp_flag = SET;
            else
                tmp_flag = RESET;

            while (tmp_flag != RESET)
            {
                timeout--;

                if (timeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }

                if (_i2c_get_flag_slave_high_speed(pi2c))
                    tmp_flag = SET;
                else
                    tmp_flag = RESET;
            }
        }
    }

    return STATUS_OK;
}

/**
 * @brief I2C 模块主模式写操作请求函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits 地址bit长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_masterwriterequest(reg_i2c_t *pi2c, uint8_t SlaveAdd, i2c_slave_addbits_t Addbits, uint32_t timeout)
{
    status_t status;
    flagstatus_t tmp_flag;
    uint8_t addr = 0;

    if (Addbits == I2C_SLAVE_ADD_10BITS)
    {

        addr = (uint8_t)(((SlaveAdd >> 8) << 1) | 0xf0);
        pi2c->DR = addr;
        _i2c_generate_start(pi2c);

        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }

        addr = SlaveAdd;
        pi2c->DR = addr;
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }
    }
    else
    {
        /*产生起始条件:读请求最低位为0*/
        SlaveAdd &= ~0x01;
        pi2c->DR = SlaveAdd;
        _i2c_generate_start(pi2c);

        /*查TF标志*/
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);

        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }
    }

    return (status);
}

/**
 * @brief I2C 模块主模式读操作请求函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits 地址bit长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_masterreadrequest(reg_i2c_t *pi2c, uint8_t SlaveAdd, i2c_slave_addbits_t Addbits, uint32_t timeout)
{
    status_t status;
    flagstatus_t tmp_flag;

    if (Addbits == I2C_SLAVE_ADD_10BITS)
    {

        pi2c->DR = (uint8_t)(((SlaveAdd >> 8) << 1) | 0xf0);
        _i2c_generate_start(pi2c);

        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);

        pi2c->DR = (uint8_t)(SlaveAdd & 0xff);
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);
        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }

        _i2c_repeat_start(pi2c);
        pi2c->DR = (uint8_t)(((SlaveAdd >> 8) << 1) | 0xf1);
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);
        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }
    }
    else
    {
        /*产生起始条件:写请求最低位为1*/
        SlaveAdd |= 0x01;
        pi2c->DR = SlaveAdd;
        _i2c_generate_start(pi2c);

        /*查询RC标志*/
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
        }
    }

    return (status);
}

/**
 * @brief I2C 模块主模式生成停止条件函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param NewState 高速使能;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_mastergeneratestop(reg_i2c_t *pi2c, functionalstate_t NewState, uint32_t timeout)
{
    status_t status = STATUS_OK;
    //    flagstatus_t tmp_flag;

    _i2c_generate_stop(pi2c);

    /*查询BUSY标志*/
    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_BUSY, RESET, timeout);

    if (NewState == ENABLE)
    {
        _i2c_dis_highspeed(pi2c);
    }

    return (status);
}

/**
 * @brief I2C 模块生成停止条件函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_generate_stop(reg_i2c_t *pi2c)
{
    _i2c_generate_stop(pi2c);
}

/**
 * @brief I2C 模块生成停止条件函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void drv_i2c_generate_start(reg_i2c_t *pi2c)
{
    _i2c_generate_start(pi2c);
}

/**
 * @brief I2C 模块主模式生成重复起始读条件函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_masterrestartreadrequest(reg_i2c_t *pi2c, uint8_t SlaveAdd, uint32_t timeout)
{
    status_t status;
    //    flagstatus_t tmp_flag;

    /*产生起始条件:写请求最低位为1*/
    _i2c_repeat_start(pi2c);
    SlaveAdd |= 0x01;
    pi2c->DR = SlaveAdd;
    _i2c_reset_repeat_start(pi2c);

    /*查询标志*/
    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

    return (status);
}

/**
 * @brief I2C 模块主模式高速写操作请求函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SLaveAdd 从机地址;
 * @param Addbits 地址bit长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_masterhighspeedwriterequest(reg_i2c_t *pi2c,
                                                 uint8_t SLaveAdd,
                                                 i2c_slave_addbits_t Addbits,
                                                 uint32_t timeout)
{
    status_t status = STATUS_OK;
    flagstatus_t tmp_flag;

    /**************************************************************/
    /*禁止高速模式*/
    _i2c_dis_highspeed(pi2c);
    _i2c_dis_clock_test_mode(pi2c);
    /**************************************************************/

    /**************************************************************/
    /*常速模式下发送主机码*/
    pi2c->DR = I2C_MASTER_CODE;
    _i2c_generate_start(pi2c);

    /*polling tf falg*/
    status = drv_i2c_waitonflagtimeout(pi2c,
                                       I2C_FLAG_INDEX_TF,
                                       SET,
                                       timeout);

    if (status != STATUS_OK)
    {
        return status;
    }
    else
    {
        ;
    }

    /**************************************************************/
    /*高速使能:发送写请求*/
    //    _i2c_en_clock_test_mode(pi2c);
    _i2c_en_highspeed(pi2c);

    _i2c_repeat_start(pi2c);

    if (Addbits == I2C_SLAVE_ADD_10BITS)
    {
        pi2c->DR = (uint8_t)(((SLaveAdd >> 8) << 1) | 0xf0);

        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }
        pi2c->DR = SLaveAdd;
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);
        drv_i2c_getflag(pi2c, I2C_FLAG_INDEX_AACK, &tmp_flag);

        if (tmp_flag == SET)
        {
            return (STATUS_ERROR);
            ;
        }
    }
    else
    {
        SLaveAdd &= 0xfe;
        pi2c->DR = SLaveAdd;
        _i2c_reset_repeat_start(pi2c);

        if (drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout) != STATUS_OK)
        {
            return STATUS_TIMEOUT;
        }
        else
        {
            ;
        }

        if (pi2c->SR & (1 << I2C_FLAG_INDEX_AACK))
        {
            return STATUS_TIMEOUT;
        }
        else
        {
            ;
        }
    }

    /**************************************************************/
    return STATUS_OK;
}

/**
 * @brief I2C 模块发送数据到总线函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param tosend 待发送数据;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_transmitbyte(reg_i2c_t *pi2c, uint8_t tosend, uint32_t timeout)
{
    status_t status;

    pi2c->DR = tosend;
    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_TF, SET, timeout);

    return (status);
}

/**
 * @brief I2C 模块读取总线数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param Rx 接收数据指针;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_receivebyte(reg_i2c_t *pi2c, uint8_t *Rx, uint32_t timeout)
{
    status_t status;

    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

    if (status == STATUS_OK)
    {
        *Rx = pi2c->DR;
    }

    return (status);
}

/**
 * @brief  I2C 模块查询方式发送数据到设备函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits 地址bit长度;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_transmit(reg_i2c_t *pi2c,
                              uint8_t SlaveAdd,
                              i2c_slave_addbits_t Addbits,
                              functionalstate_t Highspeed,
                              uint8_t *pBuf,
                              uint32_t Size,
                              uint32_t timeout)
{
    uint32_t loop = 0;
    status_t status;

    /*是否是高速模式   */
    if (Highspeed == ENABLE)
    {
        if (drv_i2c_masterhighspeedwriterequest(pi2c, SlaveAdd, Addbits, timeout) != STATUS_OK)
            return (status);
    }
    else
    {
        /*发送起始条件写操作*/
        if (drv_i2c_masterwriterequest(pi2c, SlaveAdd, Addbits, timeout) != STATUS_OK)
            return (status);
    }

    /**************************************************************/
    /*发送数据*/
    for (loop = 0; loop < Size; loop++)
    {
        status = drv_i2c_transmitbyte(pi2c, *(pBuf + loop), timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }
    }

/*发送停止条件*/
#if 1
    status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);
#else
    delay(1000000);
    _i2c_generate_stop(pi2c);
#endif
    return (status);
}

/**
 * @brief I2C 模块查询方式从设备读取数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits 地址bit长度;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待接收数据指针;
 * @param Size 待接收数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_receive(reg_i2c_t *pi2c,
                             uint8_t SlaveAdd,
                             i2c_slave_addbits_t Addbits,
                             functionalstate_t Highspeed,
                             uint8_t *pBuf,
                             uint32_t Size,
                             uint32_t timeout)
{
    uint32_t loop = 0;
    status_t status;

    /*发送起始条件读操作*/
    status = drv_i2c_masterreadrequest(pi2c, SlaveAdd, Addbits, timeout);

    if (status != STATUS_OK)
    {
        return (status);
    }

    /**************************************************************/
    /*读取数据*/
    if (Size == 1)
    {
        _i2c_nack(pi2c);

        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }

        *(pBuf) = pi2c->DR;
    }
    else
    {
        for (loop = 0; loop < Size - 1; loop++)
        {
            _i2c_ack(pi2c);
            status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

            if (status != STATUS_OK)
            {
                return (status);
            }

            *(pBuf + loop) = pi2c->DR;
        }

        /**************************************************************/
        /*最后一字节数据NACK*/
        _i2c_nack(pi2c);
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }

        *(pBuf + loop) = pi2c->DR;
    }

    /*发送停止条件*/
    status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);
    //    delay(1000000);
    //    _i2c_generate_stop(pi2c);
    return (status);
}

/**
 * @brief I2C 模块中断方式发送数据到设备函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待发送数据指针;
 * @param Size 待发送数据长度;
 * @return status_t
 */
status_t drv_i2c_transmitit(reg_i2c_t *pi2c,
                                uint8_t SlaveAdd,
                                functionalstate_t Highspeed,
                                uint8_t *pBuf,
                                uint32_t Size)
{
    //    uint32_t loop = 0;
    //    status_t status;

    /*高速模式还是普通模式*/
    if (Highspeed == ENABLE)
    {
        /*先禁止高速模式以普通模式发送高速起始信号*/
        _i2c_dis_highspeed(pi2c);
        /*使能相应的中断*/
        _i2c_en_it(pi2c);
        pi2c->DR = I2C_MASTER_CODE;
        _i2c_generate_start(pi2c);
        /**/
    }

    else
    {
        /*使能相应的中断*/
        _i2c_en_it(pi2c);
        pi2c->DR = SlaveAdd;
        _i2c_generate_start(pi2c);
    }

    /**/
    return (STATUS_OK);
}

/**
 * @brief I2C 模块查询方式从设备读取数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待接收数据指针;
 * @param Size 待接收数据长度;
 * @return status_t
 */
status_t drv_i2c_receiveit(reg_i2c_t *pi2c,
                               uint8_t SlaveAdd,
                               functionalstate_t Highspeed,
                               uint8_t *pBuf,
                               uint32_t Size)
{
    //    uint32_t loop = 0;
    //    status_t status;

    /*高速模式还是普通模式*/
    if (Highspeed == ENABLE)
    {
        /*先禁止高速模式以普通模式发送高速起始信号*/
        _i2c_dis_highspeed(pi2c);
        /*使能相应的中断*/
        _i2c_en_it(pi2c);
        pi2c->DR = I2C_MASTER_CODE;
        _i2c_generate_start(pi2c);
        /**/
    }

    else
    {
        /*使能相应的中断*/
        _i2c_en_it(pi2c);
        pi2c->DR = SlaveAdd | 0x01;
        _i2c_generate_start(pi2c);
    }

    /**/
    return (STATUS_OK);
}

/**
 * @brief I2C 模块查询方式写数据到存储器函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits bit长度;
 * @param MemAdd 存储器地址;
 * @param MemAddBytes 存储器地址长度，单位字节;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_memwrite(reg_i2c_t *pi2c,
                              uint8_t SlaveAdd,
                              i2c_slave_addbits_t Addbits,
                              uint32_t MemAdd,
                              uint8_t MemAddBytes,
                              functionalstate_t Highspeed,
                              uint8_t *pBuf,
                              uint32_t Size,
                              uint32_t timeout)
{
    uint32_t loop = 0;
    status_t status;
    uint8_t AddBuf[4];

#if 1
    /*等到不忙*/
    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_BUSY, RESET, timeout);

    if (status != STATUS_OK)
    {
        return (status);
    }
#endif
    /*是否是高速模式   */
    if (Highspeed == ENABLE)
    {
        if (drv_i2c_masterhighspeedwriterequest(pi2c, SlaveAdd, Addbits, timeout) != STATUS_OK)
            return (status);
    }
    else
    {
        /*发送起始条件写操作*/
        if (drv_i2c_masterwriterequest(pi2c, SlaveAdd, Addbits, timeout) != STATUS_OK)
        {
            status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);
            
            return (status);
        }
            
    }

    /*发送子地址*/
    AddBuf[0] = (uint8_t)(MemAdd);
    AddBuf[1] = (MemAdd >> 8) & 0XFF;
    AddBuf[2] = (MemAdd >> 16) & 0XFF;
    AddBuf[3] = (MemAdd >> 24) & 0XFF;

    if (MemAddBytes > 4)
        MemAddBytes = 4;

    for (loop = 0; loop < MemAddBytes; loop++)
    {
        status = drv_i2c_transmitbyte(pi2c, *(AddBuf + loop), timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }
    }

    /**************************************************************/
    /*发送数据*/
    for (loop = 0; loop < Size; loop++)
    {
        status = drv_i2c_transmitbyte(pi2c, *(pBuf + loop), timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }
    }

    /*发送停止条件*/
    status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);

    return (status);
}

/**
 * @brief I2C 模块查询方式读取存储器数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param SlaveAdd 从机地址;
 * @param Addbits bit长度;
 * @param MemAdd 存储器地址;
 * @param MemAddBytes 存储器地址长度，单位字节;
 * @param Highspeed 是否高速模式;
 * @param pBuf 待接收数据指针;
 * @param Size 待接收数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_memread(reg_i2c_t *pi2c,
                             uint8_t SlaveAdd,
                             i2c_slave_addbits_t Addbits,
                             uint32_t MemAdd,
                             uint8_t MemAddBytes,
                             functionalstate_t Highspeed,
                             uint8_t *pBuf,
                             uint32_t Size,
                             uint32_t timeout)
{
    uint32_t loop = 0;
    uint8_t AddBuf[4];
    status_t status;

#if 1
    /*等到不忙*/
    status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_BUSY, RESET, timeout);

    if (status != STATUS_OK)
    {
        return (status);
    }
#endif
    /*是否是高速模式   */
    if (Highspeed == ENABLE)
    {
        status = drv_i2c_masterhighspeedwriterequest(pi2c, SlaveAdd, Addbits, timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }
    }
    else
    {
        /*发送起始条件写操作*/
        status = drv_i2c_masterwriterequest(pi2c, SlaveAdd, Addbits, timeout);

        if (status != STATUS_OK)
        {
            status = drv_i2c_mastergeneratestop(pi2c,Highspeed, timeout);
            
            return (status);
        }
    }

    /*发送子地址*/
    AddBuf[0] = (uint8_t)(MemAdd);
    AddBuf[1] = (MemAdd >> 8) & 0XFF;
    AddBuf[2] = (MemAdd >> 8) & 0XFF;
    AddBuf[3] = (MemAdd >> 8) & 0XFF;

    if (MemAddBytes > 4)
        MemAddBytes = 4;

    for (loop = 0; loop < MemAddBytes; loop++)
    {
        status = drv_i2c_transmitbyte(pi2c, *(AddBuf + loop), timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }
    }

/**************************************************************/
#if 0

    /*发送重复条件读请求*/
    if(iic_master_restart_read_request(hiic, slave_add, timeout) != HAL_OK)
    {
        hiic->lock = HAL_UNLOCKED;
        return HAL_TIMEOUT;
    }

#else

    /*发送停止条件*/
    status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);

    if (status != STATUS_OK)
    {
        return (status);
    }

    status = drv_i2c_masterreadrequest(pi2c, SlaveAdd, Addbits, timeout);

    if (status != STATUS_OK)
    {
        return (status);
    }

#endif

    /**************************************************************/
    /*读取数据*/
    if (Size == 1)
    {
        _i2c_nack(pi2c);

        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }

        *(pBuf) = pi2c->DR;
    }
    else
    {
        /**************************************************************/
        for (loop = 0; loop < Size - 1; loop++)
        {
            _i2c_ack(pi2c);
            status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

            if (status != STATUS_OK)
            {
                return (status);
            }

            *(pBuf + loop) = pi2c->DR;
        }

        /**************************************************************/
        /*最后一字节数据NACK*/
        _i2c_nack(pi2c);
        status = drv_i2c_waitonflagtimeout(pi2c, I2C_FLAG_INDEX_RC, SET, timeout);

        if (status != STATUS_OK)
        {
            return (status);
        }

        *(pBuf + loop) = pi2c->DR;
    }

    /*发送停止条件*/
    status = drv_i2c_mastergeneratestop(pi2c, Highspeed, timeout);

    return (status);
}

/**
 * @brief I2C 模块从机查询方式发送接收函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pBuf 数据指针：
 * @param Size 数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_slavetransmitreceive(reg_i2c_t *pi2c,
                                          uint8_t *pBuf,
                                          uint32_t Size,
                                          uint32_t timeout)
{
    uint32_t loop = 0;
    uint8_t I2CStatus;
    uint8_t I2CHighspeedStatus;
    volatile uint8_t tmp = 0;

    /**************************************************************/
    do
    {
        /*获取状态*/
        I2CStatus = pi2c->SR;
        I2CHighspeedStatus = pi2c->SHIR;

        /**/
        if (I2CHighspeedStatus & I2C_FLAG_SLAVE_HIGH_SPEED)
        {
            /*write 1 to clear the flag*/
            _i2c_clr_flag_slave_high_speed(pi2c);
        }

        if (I2CStatus & (I2C_FLAG_RC | I2C_FLAG_TF))
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
                        _i2c_ack(pi2c);
                    }
                    /**************************************************************/

                    /**************************************************************/
                    else
                    {
                        /*接收到的是数据*/
                        pBuf[loop] = pi2c->DR;
                        loop++;
                        /*应答主机同时清除RC标志*/
                        _i2c_ack(pi2c);
                    }

                    /**************************************************************/
                } /*接收模式*/

                /**************************************************************/
                else
                {
                    /*发送模式*/
                    pi2c->DR = pBuf[loop];
                    loop++;
                } /*发送模式*/

                /**************************************************************/
            } /*地址匹配*/
        } /*RC/TF置位*/
    } while (loop < Size);

    return (STATUS_OK);
}

/**
 * @brief I2C 模块从机查询方式发送数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pBuf 待发送数据指针;
 * @param Size 待发送数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_slavetransmit(reg_i2c_t *pi2c,
                                   uint8_t *pBuf,
                                   uint32_t Size,
                                   uint32_t timeout)
{
    uint32_t loop = 0;
    uint32_t TmpTimeout = timeout;
    uint8_t I2CStatus;
    uint8_t I2CHighspeedStatus;
    volatile uint8_t tmp = 0;

    /**************************************************************/
    do
    {
        /*获取中断状态*/
        I2CStatus = pi2c->SR;
        I2CHighspeedStatus = pi2c->SHIR;

        /**/
        if (I2CHighspeedStatus & I2C_FLAG_SLAVE_HIGH_SPEED)
        {
            /*write 1 to clear the flag*/
            _i2c_clr_flag_slave_high_speed(pi2c);
        }

        if (I2CStatus & (I2C_FLAG_RC | I2C_FLAG_TF))
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
                        _i2c_ack(pi2c);
                    }
                } /*接收模式*/
                /**************************************************************/
                else
                {
                    /*发送模式*/
                    pi2c->DR = pBuf[loop];
                    loop++;
                } /*发送模式*/

                /**************************************************************/
            } /*地址匹配*/
        }
        else
        {
            /*超时处理*/
            if (timeout)
            {
                TmpTimeout--;

                if (TmpTimeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }
            }
        }
    } while (loop < Size);

    return (STATUS_OK);
}

/**
 * @brief I2C 模块从机查询方式接收数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pBuf 待接收数据指针;
 * @param Size 待接收数据长度;
 * @param timeout 超时时间;
 * @return status_t
 */
status_t drv_i2c_slavereceive(reg_i2c_t *pi2c,
                                  uint8_t *pBuf,
                                  uint32_t Size,
                                  uint32_t timeout)
{
    uint32_t loop = 0;
    uint8_t I2CStatus;
    volatile uint8_t tmp = 0;
    uint32_t TempTimeout = timeout;
    uint8_t I2CHighspeedStatus;

    /**************************************************************/
    do
    {
        /*获取中断状态*/
        I2CStatus = pi2c->SR;
        I2CHighspeedStatus = pi2c->SHIR;

        if (I2CHighspeedStatus & I2C_FLAG_SLAVE_HIGH_SPEED)
        {
            /*write 1 to clear the flag*/
            _i2c_clr_flag_slave_high_speed(pi2c);
        }

        if (I2CStatus & (I2C_FLAG_RC | I2C_FLAG_TF))
        {
            TempTimeout = timeout;

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
                        _i2c_ack(pi2c);
                    }
                    /**************************************************************/

                    /**************************************************************/
                    else
                    {
                        /*接收到的是数据*/
                        pBuf[loop] = pi2c->DR;
                        loop++;
                        /*应答主机同时清除RC标志*/
                        _i2c_ack(pi2c);
                    }

                    /**************************************************************/
                } /*接收模式*/
            } /*地址匹配*/
        }
        else
        {
            if (timeout)
            {
                TempTimeout--;

                if (TempTimeout == 0)
                {
                    return (STATUS_TIMEOUT);
                }
            }
        }
    } while (loop < Size);

    return (STATUS_OK);
}

/**
 * @brief I2C 模块获取使能的中断源函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pItSource 中断源指针;
 * @return status_t
 */
status_t drv_i2c_getitsource(reg_i2c_t *pi2c,
                                 uint8_t *pItSource)
{
    *pItSource = 0;

    if (_bit_get(pi2c->CCR, I2C_IT_INDEX_IEN))
    {
        *pItSource |= I2C_IT_INDEX_IEN;
    }

    if (_bit_get(pi2c->CCR, I2C_IT_INDEX_AMIE))
    {
        *pItSource |= I2C_IT_INDEX_AMIE;
    }

    if (_bit_get(pi2c->CCR, I2C_IT_INDEX_SLV_HSIE))
    {
        *pItSource |= I2C_IT_INDEX_SLV_HSIE;
    }

    return (STATUS_OK);
}

/**
 * @brief I2C 获取标志状态函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pBasicFlags 基本状态指针;
 * @param pSlvHighspeedFlags 高速状态指针;
 * @return status_t
 */
status_t drv_i2c_getitflags(reg_i2c_t *pi2c, uint8_t *pBasicFlags, uint8_t *pSlvHighspeedFlags)
{
    *pBasicFlags = pi2c->SR;
    *pSlvHighspeedFlags = pi2c->SHIR;

    return (STATUS_OK);
}

/**
 * @brief I2C 模块获取当前数据寄存器内的数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pData 获取的数据
 */
void drv_i2c_getdr(reg_i2c_t *pi2c, uint8_t *pData)
{
    *pData = pi2c->DR;
}

/**
 * @brief I2C 模块写数据寄存器数据函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param Data 发送的数据;
 */
void drv_i2c_setdr(reg_i2c_t *pi2c, uint8_t Data)
{
    pi2c->DR = Data;
}

/**
 * @brief I2C 模块管脚用作GPIO初始化（非复用关系）函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param Init 初始化结构体指针;
 * @return status_t
 */
status_t drv_i2c_gpioinit(reg_i2c_t *pi2c, gpio_init_t *Init)
{

    drv_i2c_funcswap(pi2c);

    /*用作GPIO功能*/
    _i2c_pin_gpio(pi2c, Init->Pin);

    /*方向*/
    if (Init->Dir == GPIO_DIR_OUT)
    {
        _i2c_pin_dir_output(pi2c, Init->Pin);

        if (Init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
        {
            _i2c_pin_output_cmos(pi2c, Init->Pin);
        }
        else if (Init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
        {
            _i2c_pin_output_opendrain(pi2c, Init->Pin);
        }
        else
        {
            return (STATUS_ERROR);
        }
    }
    else if (Init->Dir == GPIO_DIR_IN)
    {
        _i2c_pin_dir_input(pi2c, Init->Pin);
    }
    else if (Init->Dir == GPIo_DIR_TRIGATE)
    {
        /*用作输主之后IOCONTROL部分禁止输入*/
        _i2c_pin_dir_input(pi2c, Init->Pin);
        /**/
    }

    /*上下拉*/
    if (Init->PullMode == GPIO_PULL_MODE_UP)
    {
        _i2c_pin_pullup_en(pi2c, Init->Pin);
        _i2c_pin_pulldown_dis(pi2c, Init->Pin);
    }
    else if (Init->PullMode == GPIO_PULL_MODE_UP)
    {
        _i2c_pin_pulldown_en(pi2c, Init->Pin);
        _i2c_pin_pullup_dis(pi2c, Init->Pin);
    }
    else
    {
        return (STATUS_ERROR);
    }

    /**/
    return (STATUS_OK);
}

/**
 * @brief I2C 模块管脚恢复初始设置（非复用关系）函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pin I2C的管脚;
 * @return status_t
 */
status_t drv_i2c_gpiodeinit(reg_i2c_t *pi2c, uint8_t pin)
{
    /*用作FUN功能*/
    _i2c_pin_primary_fun(pi2c, pin);
    _i2c_pin_dir_input(pi2c, pin);

    return (STATUS_OK);
}

/**
 * @brief I2C 模块管脚输出指定电平函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pin I2C的管脚;
 * @param state IO状态;
 */
void drv_i2c_writepin(reg_i2c_t *pi2c, uint8_t pin, gpio_pinstate_t state)
{
    if (state == RESET)
    {
        _i2c_reset_pin_bit(pi2c, pin);
    }
    else
    {
        _i2c_set_pin_bit(pi2c, pin);
    }
}

/**
 * @brief I2C 模块获取管脚电平函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pin I2C的管脚;
 * @return gpio_pinstate_t
 */
gpio_pinstate_t drv_i2c_readpin(reg_i2c_t *pi2c, uint8_t pin)
{
    if (_i2c_get_pin_bit(pi2c, pin))
    {
        return (GPIO_HIGH);
    }
    else
    {
        return (GPIO_LOW);
    }
}

/**
 * @brief I2C 模块管脚电平翻转函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param pin I2C的管脚;
 */
void drv_i2c_togglepin(reg_i2c_t *pi2c, uint8_t pin)
{
    pi2c->DDR &= ~(1 << pin);
}
