/**
 * @file can_drv.c
 * @author Product application department
 * @brief  CAN 模块驱动层
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "can_drv.h"
#include "cpm_drv.h"
// 全局变量定义

/**
 * @brief 比特率定义
 */
static can_timeseg g_timesegments[18] =
    {
        {1, 2, 1}, /* 0: total 8 timequanta */
        {1, 2, 2}, /* 1: total 9 timequanta */
        {2, 2, 2}, /* 2: total 10 timequanta */
        {2, 2, 3}, /* 3: total 11 timequanta */
        {2, 3, 3}, /* 4: total 12 timequanta */
        {3, 3, 3}, /* 5: total 13 timequanta */
        {3, 3, 4}, /* 6: total 14 timequanta */
        {3, 4, 4}, /* 7: total 15 timequanta */
        {4, 4, 4}, /* 8: total 16 timequanta */
        {4, 4, 5}, /* 9: total 17 timequanta */
        {4, 5, 5}, /* 10: total 18 timequanta */
        {5, 5, 5}, /* 11: total 19 timequanta */
        {5, 5, 6}, /* 12: total 20 timequanta */
        {5, 6, 6}, /* 13: total 21 timequanta */
        {6, 6, 6}, /* 14: total 22 timequanta */
        {6, 6, 7}, /* 15: total 23 timequanta */
        {6, 7, 7}, /* 16: total 24 timequanta */
        {7, 7, 7}  /* 17: total 25 timequanta */
};

// 函数定义

/**
 * @brief CAN 模块管脚切换为CAN功能函数
 * @param pcan 指向can_typedef_t结构体的指针
 */
void drv_can_funcswap(reg_can_t *pcan)
{
 
}

/**
 * @brief CAN 模块软件复位函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @return status_t 当前状态
 */
status_t drv_can_softreset(reg_can_t *pcan)
{
    /* Wait until FlexCAN exit from any Low Power Mode. */
    while (0u != (pcan->CAN_MCR & CAN_MCR_LPM_ACK))
    {
    }
    _can_en_soft_rst(pcan);
    while ((pcan->CAN_MCR & CAN_MCR_SOFT_RST) != 0)
    {
    }
    return STATUS_OK;
}

/**
 * @brief CAN 模块恢复默认设置函数
 * @param pcan 指向can_typedef_t结构体的指针
 */
void drv_can_deinit(reg_can_t *pcan)
{
    uint8_t i, j;
    pcan->CAN_MCR = 0x5980000F;
    pcan->CAN_CR = 0;
    pcan->CAN_ECR = 0;
    pcan->CAN_ESR = 0;
    pcan->CAN_FRT = 0;
    pcan->CAN_IF1R = 0;
    pcan->CAN_IF2R = 0;
    pcan->CAN_IM1R = 0;
    pcan->CAN_IM2R = 0;
    pcan->CAN_RXGM = 0xFFFFFFFF;
    pcan->CAN_RX14M = 0xFFFFFFFF;
    pcan->CAN_RX15M = 0xFFFFFFFF;
    for (i = 0; i < 63; i++)
    {
        pcan->CAN_MB[0].MB_CS = 0;
        pcan->CAN_MB[0].MB_ID = 0;
        for (j = 0; j < 8; j++)
        {
            pcan->CAN_MB[0].MB_DATA[0] = 0;
        }
    }
}

/**
 * @brief CAN 模块使用外部晶振函数
 * @param pcan 指向can_typedef_t结构体的指针
 */
void drv_can_select_crystal_oscillator(reg_can_t *pcan)
{
    _cpm_set_oscext_clk_en; 
    while(!_cpm_get_oscext_stable_flag);
    _can_select_crystal_oscillator_clock(pcan);	
}

/**
 * @brief CAN 模块初始化函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param init 指向can_inittypedef_t结构体的指针
 * @return status_t 当前状态
 */
status_t drv_can_init(reg_can_t *pcan, can_init_t *init)
{
    uint8_t ucIndex0 = 0;
    uint8_t ucIndex1 = 0;
    uint32_t i = 0;
    uint32_t ulRegTmp = 0;
    uint8_t ucPresDiv = 0;
    can_timeseg *pTimeSeg = 0;
    uint32_t clk_ratio = init->IPSFreq / init->BitRate;
    can_rxindividualmask_t *pCanRxMaskRegs;

    drv_can_funcswap(pcan);

    if (pcan == CAN1)
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN1_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
    }
    else
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN2_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
    }

    /* select peripheral clock */
    drv_can_select_crystal_oscillator(pcan);

    /*exit module disable mode*/
    _can_dis_module_disable_mode(pcan);

    drv_can_softreset(pcan);

    _can_select_normal_mode(pcan);
    /* enable the generation of transmit and receive warning */
    _can_en_generate_wrn_int_flag(pcan);
    /* support backwards compatibility */
    _can_en_support_previous_versions(pcan);
    /* enable all the MBs */
    _can_en_all_message_buffers(pcan);

    if (init->FEN == ENABLE)
    {
        _can_en_fifo(pcan);
    }
    else
    {
        _can_dis_fifo(pcan);
    }

    /*clear all the MBs and their mask to 0*/
    for (ucIndex0 = 0; ucIndex0 < CAN_BUFFER_NUM; ucIndex0++)
    {
        if (ucIndex0 < 32)
        {
            pcan->CAN_MB[ucIndex0].MB_CS = 0;
        }
        else
        {
            pcan->CAN_MB[ucIndex0].MB_CS = 0x08000000;
        }
        pcan->CAN_MB[ucIndex0].MB_ID = 0;
        for (ucIndex1 = 0; ucIndex1 < 8; ucIndex1++)
        {
            pcan->CAN_MB[ucIndex0].MB_DATA[ucIndex1] = 0;
        }
        pCanRxMaskRegs->CAN_RXIMR[ucIndex0] = 0;
    }

    for (i = 8; i <= 25; i++)
    {
        if (0 == (clk_ratio % i))
        {
            pTimeSeg = &g_timesegments[i - 8];
            ucPresDiv = clk_ratio / i - 1;
            break;
        }
    }

    if (i >= 26)
    {
        return STATUS_ERROR;
    }

    ulRegTmp = pcan->CAN_CR;
    ulRegTmp &= CAN_TIMING_MASK;
    pcan->CAN_CR = ulRegTmp | (ucPresDiv << 24) | (pTimeSeg->m_pseg1 << 19) | (pTimeSeg->m_pseg2 << 16) | (pTimeSeg->m_propseg);

    return STATUS_OK;
}

/**
 * @brief CAN 模块发送数据函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param ptxmsg 指向can_txmsgtypedef_t结构体的指针
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t drv_can_transmitbytes(reg_can_t *pcan, can_txmsg_t *ptxmsg, uint32_t timeout)
{
    uint8_t ucMBID = 0;
    uint32_t ulWaitCnt = 0;

    /* check MB is valid or not
     * if valid, clear the flag;if not, Wait for some time
     * */
    for (ucMBID = 0; ucMBID < 32;)
    {
        if (((pcan->CAN_MB[ucMBID + 32].MB_CS & 0x0f000000) == CAN_TXCODE_INACT))
        {
            break;
        }
        else
        {
            ucMBID++;
        }

        if (ucMBID >= 32)
        {
            ucMBID = 0;
            if (timeout != 0)
            {
                ulWaitCnt++;
                if (ulWaitCnt > timeout)
                {
                    return STATUS_TIMEOUT;
                }
            }
        }
    }

    /*clear the MB interrupt flag  */
    pcan->CAN_IF2R |= 1 << ucMBID;

    /*disable the MB interrupt*/
    pcan->CAN_IM2R &= ~(1 << ucMBID);

#if 0
    /*store data in the MB*/
    for(ucIndex = 0; ucIndex < ptxmsg->DLC; ucIndex++)
    {
        pcan->CAN_MB[ucMBID + 32].MB_DATA[ucIndex] = ptxmsg->Data[ucIndex];
    }
#else
    pcan->CAN_MB[ucMBID + 32].MB_WORD0 = ptxmsg->word0;
    pcan->CAN_MB[ucMBID + 32].MB_WORD1 = ptxmsg->word1;
#endif
    /*configure the MB to send an extended data frame*/
    if (ptxmsg->IDE == DRV_CAN_ID_EXT)
    {
        pcan->CAN_MB[ucMBID + 32].MB_ID = ptxmsg->ExtId;
        pcan->CAN_MB[ucMBID + 32].MB_CS = CAN_TXCODE_ONCE | ptxmsg->RTR | CAN_MBS_IDE | CAN_MBS_SRR | (ptxmsg->DLC << 16);
    }
    /*configure the MB to send an standard data frame*/
    else
    {
        pcan->CAN_MB[ucMBID + 32].MB_ID = ptxmsg->StdId << 18;
        pcan->CAN_MB[ucMBID + 32].MB_CS = CAN_TXCODE_ONCE | ptxmsg->RTR | (ptxmsg->DLC << 16);
    }

    /*exit Freeze Mode*/
    pcan->CAN_MCR &= ~(CAN_MCR_HALT | CAN_MCR_FRZ);
    pcan->CAN_MCR |= CAN_MCR_SRX_DIS;
    /*wait trans done*/
    while ((pcan->CAN_IF2R &= 1 << ucMBID) != 1 << ucMBID);
    pcan->CAN_IF2R |= 1 << ucMBID;

    /*send successfully*/
    return STATUS_OK;
}

/**
 * @brief CAN 模块接收数据函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param prxmsg 指向can_rxmsgtypedef_t结构体的指针
 * @param rx_num 接收数据长度
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t drv_can_receivebytes(reg_can_t *pcan, can_rxmsg_t *prxmsg, uint32_t rx_num, uint32_t timeout)
{
    uint32_t i;
    can_rxindividualmask_t *pCanRxMaskRegs;
    //    can_rxfifoidtable_t *pCanFifoIDtable;

    if (pcan == CAN1)
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN1_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
        //        pCanFifoIDtable = (can_rxfifoidtable_t *)(CAN1_BASE_ADDR + CAN_FIFO_ID_TABLE_ADDR_OFFSET);
    }
    else
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN2_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
        //        pCanFifoIDtable = (can_rxfifoidtable_t *)(CAN2_BASE_ADDR + CAN_FIFO_ID_TABLE_ADDR_OFFSET);
    }

    /*Can must enter freeze mode before updating RX individual mask*/
    pcan->CAN_MCR |= CAN_MCR_HALT;
    while ((pcan->CAN_MCR & CAN_MCR_FRZ_ACK) == 0)
    {
    };

    /*set RX individual mask*/
    pCanRxMaskRegs->CAN_RXIMR[prxmsg->MBID] = prxmsg->RXIM;

    /*clear the MB interrupt flag  */
    pcan->CAN_IF1R |= 1 << prxmsg->MBID;

    /*disable the MB interrupt*/
    pcan->CAN_IM1R &= ~(1 << prxmsg->MBID);

    /*configure the MB to send an extended data frame*/
    if (prxmsg->IDE == DRV_CAN_ID_EXT)
    {
        pcan->CAN_MB[prxmsg->MBID].MB_ID = prxmsg->ExtId;
        pcan->CAN_MB[prxmsg->MBID].MB_CS = CAN_RXCODE_EMPTY | CAN_MBS_IDE | CAN_MBS_SRR;
    }
    /*configure the MB to send an standard data frame*/
    else
    {
        pcan->CAN_MB[prxmsg->MBID].MB_ID = prxmsg->StdId << 18;
        pcan->CAN_MB[prxmsg->MBID].MB_CS = CAN_RXCODE_EMPTY;
    }

    /*exit Freeze Mode*/
    pcan->CAN_MCR &= ~(CAN_MCR_HALT | CAN_MCR_FRZ);

    for (i = 0; i < rx_num; i++)
    {
        /*wait the MB interrupt flag */
        while ((pcan->CAN_IF1R & (1 << prxmsg->MBID)) != (1 << prxmsg->MBID))
            ;
        pcan->CAN_IF1R |= 1 << prxmsg->MBID;

        if (prxmsg->IDE == DRV_CAN_ID_STD)
        {
            prxmsg->StdId = pcan->CAN_MB[prxmsg->MBID].MB_ID >> 18;
        }
        else
        {
            prxmsg->ExtId = pcan->CAN_MB[prxmsg->MBID].MB_ID;
        }

        prxmsg->DLC = (pcan->CAN_MB[prxmsg->MBID].MB_CS >> 16) & 0x0f;
        /*read data in the MB*/
#if 0        
        for(ucIndex = 0; ucIndex < prxmsg->DLC ; ucIndex++)
        {
            prxmsg->Data[ucIndex] = pcan->CAN_MB[prxmsg->MBID].MB_DATA[ucIndex];
        }
#else
        prxmsg->word0 = pcan->CAN_MB[prxmsg->MBID].MB_WORD0;
        prxmsg->word1 = pcan->CAN_MB[prxmsg->MBID].MB_WORD1;

        //    prxmsg->word0 = BIG_LITTLE_SWAP32(prxmsg->word0);
        //    prxmsg->word1 = BIG_LITTLE_SWAP32(prxmsg->word1);

#endif
    }

    /*recieve successfully*/
    return STATUS_OK;
}

/**
 * @brief CAN 模块FIFO接收数据函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param prxmsg 指向can_rxmsgtypedef_t结构体的指针
 * @param rx_num 接收数据长度
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t drv_can_fifo_receivebytes(reg_can_t *pcan, can_rxmsg_t *prxmsg, uint32_t rx_num, uint32_t timeout)
{
    uint32_t i;
    can_rxindividualmask_t *pCanRxMaskRegs;
    can_rxfifoidtable_t *pCanFifoIDtable;

    if (pcan == CAN1)
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN1_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
        pCanFifoIDtable = (can_rxfifoidtable_t *)(CAN1_BASE_ADDR + CAN_FIFO_ID_TABLE_ADDR_OFFSET);
    }
    else
    {
        pCanRxMaskRegs = (can_rxindividualmask_t *)(CAN2_BASE_ADDR + CAN_RXIMR_ADDR_OFFSET);
        pCanFifoIDtable = (can_rxfifoidtable_t *)(CAN2_BASE_ADDR + CAN_FIFO_ID_TABLE_ADDR_OFFSET);
    }

    /*Can must enter freeze mode before updating RX individual mask*/
    pcan->CAN_MCR |= CAN_MCR_HALT;
    while ((pcan->CAN_MCR & CAN_MCR_FRZ_ACK) == 0)
    {
    };

    /*set RX individual mask*/
    pCanRxMaskRegs->CAN_RXIMR[prxmsg[0].MBID] = prxmsg->RXIM;

    /*clear the FIFO interrupt flag  */
    pcan->CAN_IF1R |= CAN_IF1R_RX_FIFO_FLAG;
    /*disable FIFO interrupt*/
    pcan->CAN_IM1R &= CAN_IM1R_RX_FIFO_INT_MASK;

    /*configure FIFO to receive extended frames*/
    if (prxmsg[0].IDE == DRV_CAN_ID_EXT)
    {
        pCanFifoIDtable->ID_TABLE[prxmsg[0].MBID] = (prxmsg[0].ExtId << 1) | CAN_FIFO_EXT_MSK;
    }
    /*configure FIFO to receive standard frames*/
    else
    {
        pCanFifoIDtable->ID_TABLE[prxmsg[0].MBID] = (prxmsg[0].StdId << 19);
    }
    /*exit Freeze Mode*/
    pcan->CAN_MCR &= ~(CAN_MCR_HALT | CAN_MCR_FRZ);

    for (i = 0; i < rx_num; i++)
    {
        /*wait the MB interrupt flag */
        while ((pcan->CAN_IF1R & CAN_IF1R_RX_FIFO_FLAG) != CAN_IF1R_RX_FIFO_FLAG)
            ;

        prxmsg[i].IDE = (can_ide_t)((pcan->CAN_MB[0].MB_CS >> 21) & 0x1);

        if (prxmsg[i].IDE == DRV_CAN_ID_STD)
        {
            prxmsg[i].StdId = pcan->CAN_MB[0].MB_ID >> 18;
        }
        else
        {
            prxmsg[i].ExtId = pcan->CAN_MB[0].MB_ID;
        }

        prxmsg[i].DLC = (pcan->CAN_MB[0].MB_CS >> 16) & 0x0f;

        /*read data in the MB*/
#if 0        
        for(ucIndex = 0; ucIndex < prxmsg[i].DLC; ucIndex++)
        {
             prxmsg[i].Data[ucIndex] = pcan->CAN_MB[0].MB_DATA[ucIndex];
             printf("%.2x ", prxmsg[i].Data[ucIndex]);
        }         
         printf("\r\n");
#else
        prxmsg[i].word0 = pcan->CAN_MB[0].MB_WORD0;
        prxmsg[i].word1 = pcan->CAN_MB[0].MB_WORD1;

        //    prxmsg[i].word0 = BIG_LITTLE_SWAP32(prxmsg[i].word0);
        //    prxmsg[i].word1 = BIG_LITTLE_SWAP32(prxmsg[i].word1);

#endif

        /*clear the FIFO interrupt flag  */
        pcan->CAN_IF1R |= CAN_IF1R_RX_FIFO_FLAG;
    }

    /*recieve successfully*/
    return STATUS_OK;
}

/**
 * @brief CAN 模块配置进入或退出Freeze模式函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param enable 配置Freeze使能或者关闭
 */
void drv_can_enablefreezemode(reg_can_t *pcan, bool enable)
{
    if (enable)
    {
        _can_enter_freeze_mode(pcan);
        /* Wait a period of time for entering. */
        while (0u == (pcan->CAN_MCR & CAN_MCR_FRZ_ACK))
        {
        }
    }
    else
    {
        _can_exit_freeze_mode(pcan);
        /* Wait a period of time for entirely exiting. */
        while (0u != (pcan->CAN_MCR & CAN_MCR_FRZ_ACK))
        {
        }
    }
}
