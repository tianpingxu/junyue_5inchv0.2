/**
 * @file can_hal.c
 * @author Product application department 
 * @brief  CAN 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

//头文件定义 
#include "can_hal.h"
#include "cpm_drv.h"
#include "pinswap_drv.h"
//全局变量定义 
#define HAL_CAN_SWITCH()                   \
    {                                      \
        switch (argv[0])                   \
        {                                  \
            case 1:                        \
            {                              \
                g_pcan = CAN1;          \
                break;                     \
            }                              \
            case 2:                        \
            {                              \
                g_pcan = CAN2;          \
                break;                     \
            }                              \
            default:                       \
                HAL_CAN_ARGV_ERROR(0);     \
                return;                    \
        }                                  \
    }
volatile int g_rx_inttrigger = 0;
reg_can_t *g_pcan;
can_handle_typedef_t *g_hcan;
can_txmsg_t g_tx_msg;
can_rxmsg_t g_rx_msg[8];
    
//函数定义
/**
 * @brief CAN 模块恢复到初始状态函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @return status_t 当前状态
 */
status_t hal_can_deinit(can_handle_typedef_t *hcan)
{
    hcan->State = HAL_CAN_STATE_BUSY;

    drv_can_deinit(hcan->Instance);

    hcan->pRxMsg = NULL;
    hcan->pTxMsg = NULL;

    hcan->ErrorCode = HAL_CAN_ERROR_NONE;
    hcan->State = HAL_CAN_STATE_RESET;

    return STATUS_OK;
}

/**
 * @brief CAN 模块初始化函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @return status_t 当前状态
 */
status_t hal_can_init(can_handle_typedef_t *hcan)
{
    status_t st;

    /* Check CAN handle */
    if (hcan == NULL)
    {
        return STATUS_ERROR;
    }
    if(hcan->Instance == CAN1)
    {
        SwitchPinFunction(UART1_RX_FUN,CAN1_TX_FUN);
        SwitchPinFunction(UART1_TX_FUN,CAN1_RX_FUN);
    }
    else if(hcan->Instance == CAN2)
    {
        SwitchPinFunction(UART2_RX_FUN,CAN2_TX_FUN);
        SwitchPinFunction(UART2_TX_FUN,CAN2_RX_FUN);
    }

    if (hcan->State == HAL_CAN_STATE_RESET)
    {
    }

    /* Initialize the CAN state*/
    hcan->State = HAL_CAN_STATE_BUSY;

    st = (status_t)drv_can_init(hcan->Instance, &hcan->Init);
    if (st != STATUS_OK)
    {
        return st;
    }
    hcan->ErrorCode = HAL_CAN_ERROR_NONE;
    hcan->State = HAL_CAN_STATE_READY;
    g_hcan = hcan;
    return STATUS_OK;
}

/**
 * @brief CAN 模块配置使用外部晶振函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 */
void hal_can_select_crystal_oscillator(can_handle_typedef_t *hcan)
{
    drv_can_select_crystal_oscillator(hcan->Instance);
}

/**
 * @brief CAN 模块通过指定的端口发送数据函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t hal_can_transmitbytes(can_handle_typedef_t *hcan, uint32_t timeout)
{
    status_t st;

    if (hcan->State != HAL_CAN_STATE_READY)
    {
        return STATUS_ERROR;
    }

    hcan->State = HAL_CAN_STATE_BUSY_TX;
    hcan->ErrorCode = HAL_CAN_ERROR_NONE;

    st = (status_t)drv_can_transmitbytes(hcan->Instance, hcan->pTxMsg, timeout);
    if (st != STATUS_OK)
    {
        return st;
    }

    hcan->State = HAL_CAN_STATE_READY;

    return STATUS_OK;
}

/**
 * @brief CAN 模块中断服务函数
 */
void hal_can_irqhandle(void)
{
    uint32_t mb_int_flag0 = 0;
    uint32_t mb_int_flag1 = 0;
    mb_int_flag0 = _can_get_mb0_31_int_flag(g_hcan->Instance);
    mb_int_flag1 = _can_get_mb32_63_int_flag(g_hcan->Instance);

    /*如果中断源是MB*/
    if (mb_int_flag0 || mb_int_flag1)
    {
        if (g_hcan->MBIsrCallback != NULL)
        {
            g_hcan->MBIsrCallback((void *)g_hcan);
        }

        _can_clr_mb0_31_int_flag(g_hcan->Instance, mb_int_flag0);
        //_can_clr_mb32_63_int_flag(g_hcan->Instance, mb_int_flag1);
    }

    /*handle bus off interrupt*/
    if (_can_get_buss_off_int_flag(g_hcan->Instance))
    {
        _can_clr_buss_off_int_flag(g_hcan->Instance);
        if (g_hcan->BOFFCallback != NULL)
        {
            g_hcan->BOFFCallback((void *)g_hcan);
        }
    }
    /*handle receive warning interrupt*/
    if (_can_get_rwrn_int_flag(g_hcan->Instance))
    {
        _can_clr_rwrn_int_flag(g_hcan->Instance);
        if (g_hcan->RwrnCallback != NULL)
        {
            g_hcan->RwrnCallback((void *)g_hcan);
        }
    }
    /*handle transmit warning interrupt*/
    if (_can_get_twrn_int_flag(g_hcan->Instance))
    {
        _can_clr_twrn_int_flag(g_hcan->Instance);
        if (g_hcan->TwrnCallback != NULL)
        {
            g_hcan->TwrnCallback((void *)g_hcan);
        }
    }
    /*handle error interrupt*/
    if (_can_get_err_int_flag(g_hcan->Instance))
    {
        _can_clr_err_int_flag(g_hcan->Instance);
        if (g_hcan->ErrCallback != NULL)
        {
            g_hcan->ErrCallback((void *)g_hcan);
        }
    }
}

/**
 * @brief CAN 模块通过指定的CAN端口接收数据函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t hal_can_receivebytes(can_handle_typedef_t *hcan, uint32_t timeout)
{
    status_t st;

    if (hcan->State != HAL_CAN_STATE_READY)
    {
        return STATUS_ERROR;
    }

    hcan->State = HAL_CAN_STATE_BUSY_TX;
    hcan->ErrorCode = HAL_CAN_ERROR_NONE;

    if (hcan->Init.FEN == ENABLE)
    {
        st = (status_t)drv_can_fifo_receivebytes(hcan->Instance, hcan->pRxMsg, hcan->RxSize, timeout);
    }
    else
    {
        st = (status_t)drv_can_receivebytes(hcan->Instance, hcan->pRxMsg, hcan->RxSize, timeout);
    }

    if (st != STATUS_OK)
    {
        return st;
    }

    hcan->State = HAL_CAN_STATE_READY;

    return STATUS_OK;
}

/**
 * @brief CAN 模块发送初始化函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @param argc  参数数量
 * @param argv[] 参数数组
 *            - argv[0]: 1 = CAN1, 2 = CAN2
 *            - argv[1]: BitRate
 *            - argv[2]: 0 = Standard Id, 1 = Extended Id
 *            - argv[3]: Specifies the identifier
 *            - argv[4]: 0 = Data frame, 1 =  Remote frame
 *            - argv[5]: DATA len  0 ~ 8
 *            - argv[6]: DATA0
 *            - argv[7]: DATA1
 */
void hal_can_transmit_init(can_handle_typedef_t *hcan, uint8_t argc, uint32_t argv[])
{
    HAL_CAN_SWITCH();
    if (argv[1] > 1000000)
    {
        HAL_CAN_ARGV_ERROR(1);
        goto Fail;
    }
    HAL_CAN_DEBUG("CAN%d BitRate:%dkbps\r\n", argv[0], argv[1] / 1000);
    g_tx_msg.ExtId = argv[3];
    g_tx_msg.StdId = argv[3];

    if (argv[2])
    {
        g_tx_msg.IDE = DRV_CAN_ID_EXT;
    }
    else
    {
        g_tx_msg.IDE = DRV_CAN_ID_STD;
    }

    if (argv[4])
    {
        g_tx_msg.RTR = DRV_CAN_RTR_REMOTE;
    }
    else
    {
        g_tx_msg.RTR = DRV_CAN_RTR_DATA;
    }

    if (argv[5] <= 8)
    {
        g_tx_msg.DLC = argv[5];
    }
    else
    {
        HAL_CAN_ARGV_ERROR(5);
        goto Fail;
    }
    g_tx_msg.BYTE0 = (uint8_t)argv[6];          
    g_tx_msg.BYTE1 = (uint8_t)(argv[6] >> 8);   
    g_tx_msg.BYTE2 = (uint8_t)(argv[6] >> 16);  
    g_tx_msg.BYTE3 = (uint8_t)(argv[6] >> 24);  
    g_tx_msg.BYTE4 = (uint8_t)argv[7];          
    g_tx_msg.BYTE5 = (uint8_t)(argv[7] >> 8);   
    g_tx_msg.BYTE6 = (uint8_t)(argv[7] >> 16);  
    g_tx_msg.BYTE7 = (uint8_t)(argv[7] >> 24);  
    g_tx_msg.DLC = 8;
    hcan->Instance = g_pcan;
    hcan->pTxMsg = &g_tx_msg;
    hcan->TxSize = 1;
    hcan->Init.BitRate = argv[1];
    hcan->Init.IPSFreq = DRV_SYS_OSC_CLK_12M;
    hcan->Init.FEN = DISABLE;
    hal_can_init(hcan);
    HAL_CAN_DEBUG("CAN Init Success\r\n");
    return;
Fail:
    HAL_CAN_DEBUG("CAN%d TRANSMIT TEST: Fail\r\n", argv[0]);
    hal_can_deinit(hcan);
    return;
}


/**
 * @brief CAN 模块接收初始化函数
 * @param hcan 指向can_handle_typedef_t结构体的指针,此结构体包含了CAN模块的配置信息
 * @param argc 参数数量 
 * @param argv[] 参数数组
 *            - argv[0]: 1 = CAN1, 2 = CAN2
 *            - argv[1]: BitRate
 *            - argv[2]: 0 = Standard Id, 1 = Extended Id
 *            - argv[3]: Specifies the identifier
 *            - argv[4]: 0 = Data frame, 1 =  Remote frame
 *            - argv[5]: DATA len  0 ~ 8
 *            - argv[6]: DATA0
 *            - argv[7]: DATA1
 */
void hal_can_receive_init(can_handle_typedef_t *hcan, uint8_t argc, uint32_t argv[])
{
    HAL_CAN_SWITCH();
    if (argv[1] > 1000000)
    {
        HAL_CAN_ARGV_ERROR(1);
        goto Fail;
    }
    HAL_CAN_DEBUG("CAN%d BitRate:%dkbps\r\n", argv[0], argv[1] / 1000);
    g_tx_msg.ExtId = argv[3];
    g_tx_msg.StdId = argv[3];

    if (argv[2])
    {
        g_tx_msg.IDE = DRV_CAN_ID_EXT;
    }
    else
    {
        g_tx_msg.IDE = DRV_CAN_ID_STD;
    }

    if (argv[4])
    {
        g_tx_msg.RTR = DRV_CAN_RTR_REMOTE;
    }
    else
    {
        g_tx_msg.RTR = DRV_CAN_RTR_DATA;
    }

    g_rx_msg[0].DLC = 0;
    g_rx_msg[0].MBID = 0;
    g_rx_msg[0].RXIM = 0;

    hcan->Instance = g_pcan;
    hcan->pRxMsg = g_rx_msg;
    hcan->RxSize = 1;
    hcan->pTxMsg = &g_tx_msg;
    hcan->Init.BitRate = argv[1];
    hcan->Init.IPSFreq = DRV_SYS_OSC_CLK_12M;
    hcan->Init.FEN = DISABLE;
    hal_can_init(hcan);
    HAL_CAN_DEBUG("CAN Init Success\r\n");
    return;
Fail:
    HAL_CAN_DEBUG("CAN%d RECEIVE TEST: Fail\r\n", argv[0]);
    hal_can_deinit(hcan);
    return;
}

/**
 * @brief CAN 模块发送函数
 * @param argv 参数数组
 * @param timeout 超时时间
 */
void hal_can_transmit(uint32_t argv[], uint32_t timeout)
{
    hal_can_transmitbytes(g_hcan, timeout);
    HAL_CAN_DEBUG("CAN%d TRANSMIT TEST: Success\r\n", argv[0]);
    hal_can_deinit(g_hcan);
}

/**
 * @brief CAN 模块接收函数
 * @param argv 参数数组
 * @param timeout 超时时间
 */
void hal_can_receive(uint32_t argv[], uint32_t timeout)
{
    uint8_t i, j;
    uint8_t recv_buffer[8] = {0};
    hal_can_receivebytes(g_hcan, 0);
    for (i = 0; i < 1; i++)
    {
        if (g_rx_msg[i].IDE == DRV_CAN_ID_STD)
        {
            HAL_CAN_DEBUG("CAN%d StdId:0x%x\r\n", argv[0], g_rx_msg[i].StdId);
        }
        else
        {
            HAL_CAN_DEBUG("CAN%d ExtId:0x%x\r\n", argv[0], g_rx_msg[i].ExtId);
        }

        HAL_CAN_DEBUG("CAN%d DATA LEN:%d\r\n", argv[0], g_rx_msg[i].DLC);
        recv_buffer[0] = g_rx_msg[i].BYTE0;
        recv_buffer[1] = g_rx_msg[i].BYTE1;
        recv_buffer[2] = g_rx_msg[i].BYTE2;
        recv_buffer[3] = g_rx_msg[i].BYTE3;
        recv_buffer[4] = g_rx_msg[i].BYTE4;
        recv_buffer[5] = g_rx_msg[i].BYTE5;
        recv_buffer[6] = g_rx_msg[i].BYTE6;
        recv_buffer[7] = g_rx_msg[i].BYTE7;

        for (j = 0; j < g_rx_msg[i].DLC; j++)
        {
            HAL_CAN_DEBUG("0x%.2x ", recv_buffer[j]);
        }
        HAL_CAN_DEBUG("\r\n");
    }

    HAL_CAN_DEBUG("CAN%d RECEIVE TEST: Success\r\n", argv[0]);
    hal_can_deinit(g_hcan);
}

/**
 * @brief CAN 模块读取数据函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param prxmsg 接收数据buffer
 * @return status_t 当前状态 
 */
status_t hal_can_readrxmb(reg_can_t *pcan, can_rxmsg_t *prxmsg)
{
    uint32_t cs_value = pcan->CAN_MB[prxmsg->MBID].MB_CS;

    if (0u != (cs_value & DRV_CAN_ID_EXT))
    {

        prxmsg->ExtId = pcan->CAN_MB[prxmsg->MBID].MB_ID;
    }
    else
    {
        prxmsg->StdId = pcan->CAN_MB[prxmsg->MBID].MB_ID >> 18;
    }
    prxmsg->DLC = (cs_value >> 16) & 0x0F;
    prxmsg->word0 = pcan->CAN_MB[prxmsg->MBID].MB_WORD0;
    prxmsg->word1 = pcan->CAN_MB[prxmsg->MBID].MB_WORD1;

    (void)pcan->CAN_FRT;

    return STATUS_OK;
}

/**
 * @brief CAN 模块中断读回调函数
 */
void hal_can_isr(reg_can_t *pcan)
{
    uint8_t recv_buffer[8];

    hal_can_readrxmb(g_hcan->Instance, &g_rx_msg[0]);
    recv_buffer[0] = g_rx_msg[0].BYTE0;
    recv_buffer[1] = g_rx_msg[0].BYTE1;
    recv_buffer[2] = g_rx_msg[0].BYTE2;
    recv_buffer[3] = g_rx_msg[0].BYTE3;
    recv_buffer[4] = g_rx_msg[0].BYTE4;
    recv_buffer[5] = g_rx_msg[0].BYTE5;
    recv_buffer[6] = g_rx_msg[0].BYTE6;
    recv_buffer[7] = g_rx_msg[0].BYTE7;
    for (uint8_t i = 0; i < g_rx_msg[0].DLC; i++)
    {
        printf("0x%0.2x ", recv_buffer[i]);
    }
    printf("\r\n");
    printf("ID IS 0x%.2x \r\n", g_rx_msg[0].StdId);

    g_rx_inttrigger = 1;
}

/**
 * @brief CAN 模块查询接收中断是否触发函数
 */
void hal_can_query_rxintstatus(int *rx_int_status)
{
    if(g_rx_inttrigger == 0)
    {
        *rx_int_status = 0;
        return;
    }

    *rx_int_status = 1;
    g_rx_inttrigger = 0;
}
 
/**
 * @brief CAN 模块中断配置函数
 * @param pcan 指向can_typedef_t结构体的指针
 * @param prxmsg 指向can_rxmsgtypedef_t结构体的指针
 */
void hal_can_rxmb_it_config(reg_can_t *pcan, can_rxmsg_t *prxmsg)
{
    drv_can_enablefreezemode(pcan, ENABLE);
    if (prxmsg->IDE == DRV_CAN_ID_EXT)
    {
        pcan->CAN_MB[prxmsg->MBID].MB_ID = prxmsg->ExtId;
        pcan->CAN_MB[prxmsg->MBID].MB_CS = CAN_RXCODE_EMPTY | CAN_MBS_IDE | CAN_MBS_SRR | prxmsg->RTR;
    }
    
    /*configure the MB to send an standard data frame*/
    else
    {
        pcan->CAN_MB[prxmsg->MBID].MB_ID = prxmsg->StdId << 18;
        pcan->CAN_MB[prxmsg->MBID].MB_CS = CAN_RXCODE_EMPTY | prxmsg->RTR;
    }
    drv_can_enablefreezemode(pcan, FALSE);

    _can_en_mb0_31_int(pcan);
    _can_en_mb32_63_int(pcan);
    if (pcan == CAN1)
    {
        NVIC_Init(3, 3, CAN1_BUF00_03_IRQn, 2);
        NVIC_Init(3, 3, CAN1_BUF04_07_IRQn, 2);
        NVIC_Init(3, 3, CAN1_BUF08_11_IRQn, 2);
        NVIC_Init(3, 3, CAN1_BUF12_15_IRQn, 2);
        NVIC_Init(3, 3, CAN1_BUF16_31_IRQn, 2);
        NVIC_Init(3, 3, CAN1_BUF32_63_IRQn, 2);
        NVIC_Init(3, 3, BOFF_TRWARN_IRQn, 2);
    }
    else
    {
        NVIC_Init(3, 3, CAN2_BUF00_03_IRQn, 2);
        NVIC_Init(3, 3, CAN2_BUF04_07_IRQn, 2);
        NVIC_Init(3, 3, CAN2_BUF08_11_IRQn, 2);
        NVIC_Init(3, 3, CAN2_BUF12_15_IRQn, 2);
        NVIC_Init(3, 3, CAN2_BUF16_31_IRQn, 2);
        NVIC_Init(3, 3, CAN2_BUF32_63_IRQn, 2);
        NVIC_Init(3, 3, BOFF2_TRWARN_IRQn, 2);
    }
}

/**
 * @brief CAN 模块中断接收初始化函数
 * @param hcan 指向can_typedef_t结构体的指针
 * @param argv 参数数组
 * @param timeout 超时时间
 */
void hal_can_transfer_intinit(can_handle_typedef_t *hcan, uint32_t argv[], uint32_t timeout)
{
    uint8_t i, j;

    HAL_CAN_SWITCH();
    if (argv[1] > 1000000)
    {
        HAL_CAN_ARGV_ERROR(1);
        goto Fail;
    }
    HAL_CAN_DEBUG("CAN%d BitRate:%dkbps\r\n", argv[0], argv[1] / 1000);

    HAL_CAN_DEBUG("CAN%d RECEIVE TRANSMIT TEST\r\n", argv[0]);
    HAL_CAN_DEBUG("CAN%d BitRate:%dkbps\r\n", argv[0], 500000 / 1000);

    g_rx_msg[0].ExtId = argv[3];
    g_rx_msg[0].StdId = argv[3];

    if (argv[2])
    {
        g_rx_msg[0].IDE = DRV_CAN_ID_EXT;
    }
    else
    {
        g_rx_msg[0].IDE = DRV_CAN_ID_STD;
    }

    if (argv[4])
    {
        g_rx_msg[0].RTR = DRV_CAN_RTR_REMOTE;
    }
    else
    {
        g_rx_msg[0].RTR = DRV_CAN_RTR_DATA;
    }

    g_rx_msg[0].DLC = 0;
    g_rx_msg[0].MBID = 0;
    g_rx_msg[0].RXIM = 0;

    g_tx_msg.ExtId = argv[3];
    g_tx_msg.StdId = argv[3];
    
    if (argv[2])
    {
        g_tx_msg.IDE = DRV_CAN_ID_EXT;
    }
    else
    {
       g_tx_msg.IDE = DRV_CAN_ID_STD;
    }

    if (argv[4])
    {
        g_tx_msg.RTR = DRV_CAN_RTR_REMOTE;
    }
    else
    {
        g_tx_msg.RTR = DRV_CAN_RTR_DATA;
    }
    g_tx_msg.DLC = 8;
    g_tx_msg.BYTE0 = (uint8_t)argv[6];          
    g_tx_msg.BYTE1 = (uint8_t)(argv[6] >> 8);   
    g_tx_msg.BYTE2 = (uint8_t)(argv[6] >> 16);  
    g_tx_msg.BYTE3 = (uint8_t)(argv[6] >> 24);  
    g_tx_msg.BYTE4 = (uint8_t)argv[7];          
    g_tx_msg.BYTE5 = (uint8_t)(argv[7] >> 8);   
    g_tx_msg.BYTE6 = (uint8_t)(argv[7] >> 16);  
    g_tx_msg.BYTE7 = (uint8_t)(argv[7] >> 24); 

    hcan->Instance = g_pcan;
    hcan->pRxMsg = g_rx_msg;
    hcan->RxSize = 1;
    hcan->pTxMsg = &g_tx_msg;
    hcan->Init.BitRate = argv[1];
    hcan->Init.IPSFreq = DRV_SYS_OSC_CLK_12M;
    hcan->Init.FEN = DISABLE;
    hcan->MBIsrCallback = hal_can_isr;
    hal_can_init(hcan);    
    hal_can_rxmb_it_config(hcan->Instance, hcan->pRxMsg);

    printf("---->>>\r\n");
    return;
Fail:
    HAL_CAN_DEBUG("CAN%d RECEIVE TEST: Fail\r\n", argv[0]);
    hal_can_deinit(g_hcan);
    return;
}

