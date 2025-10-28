/**
 * @file can_test.c
 * @author Product application department
 * @brief  CAN 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup CAN CAN模块
 * @ingroup Peripherals
 * @{
 */

// 头文件定义
#include "can_test.h"

// 全局变量定义
#define CAN_TRANSMIT         0
#define CAN_RECEIVE         0
#define CAN_TRANS_RECV_IRQ     1

can_handle_typedef_t g_can_handle;

// 函数定义

/**
 * @brief CAN 模块发送测试例程
 */
void can_transmitdemo(void)
{
    while (1)
    {
        uint32_t argv[8] = {1, 500000, 0, 0, 0, 8, 0x12345678, 0x87654321};
        uint8_t argc = 8;

        hal_can_transmit_init(&g_can_handle, argc, argv);

        hal_can_transmit(argv, 0);
    }
}

/**
 * @brief CAN 模块接收测试例程
 */
void can_receivedemo(void)
{
    while (1)
    {

        uint32_t argv[8] = {1, 500000, 0, 0, 0, 8, 0x12345678, 0x87654321};
        uint8_t argc = 8;

        hal_can_receive_init(&g_can_handle, argc, argv);

        hal_can_receive(argv, 0);
    }
}

/**
 * @brief CAN 发送和接收例程
 */
void can_transfer_demo(void)
{
    uint32_t argv[8] = {1, 500000, 0, 0, 0, 8, 0x12345678, 0x87654321};
    int trans_recv_mode = 1;
    int st = 0;
    int rx_int_flag = 0;

    hal_can_transfer_intinit(&g_can_handle, argv, 0xFFFFFF);

    while (1)
    {
        if (trans_recv_mode == 1)
        {
            st = hal_can_transmitbytes(&g_can_handle, 0xFFFFFF);
            HAL_CAN_DEBUG("can transmit data\r\n");

            do
            {
                hal_can_query_rxintstatus(&rx_int_flag);
            } while (rx_int_flag != 1);
            HAL_CAN_DEBUG("can receive data\r\n");
            rx_int_flag = 0;
        }
        else if (trans_recv_mode == 2)
        {
            do
            {
                hal_can_query_rxintstatus(&rx_int_flag);
            } while (rx_int_flag != 1);
            HAL_CAN_DEBUG("can receive data\r\n");
            rx_int_flag = 0;

            st = hal_can_transmitbytes(&g_can_handle, 0xFFFFFF);
            HAL_CAN_DEBUG("can transmit data, %d\r\n", st);
        }
    }
}

/**
 * @brief CAN 模块测试示例函数
 * @param
 */
void can_demo(void)
{
    
#if CAN_TRANSMIT
    can_transmitdemo();
#endif

#if CAN_RECEIVE
    can_receivedemo();
#endif

#if CAN_TRANS_RECV_IRQ
    can_transfer_demo();
#endif
}

/** @} */  // 结束 CAN 模块分组
/** @} */  // 结束外设模块分组
