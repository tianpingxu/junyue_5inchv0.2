/**
 * @file i2c_test.c
 * @author Product Application Department
 * @brief  I2C 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup I2C I2C模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "i2c_test.h"

// 全局变量定义
#define I2C_MASTER_DEV_TEST 0
#define I2C_SLAVE_DEV_TEST 0
#define I2C_SLAVE_DEV_IT_TEST 0
#define I2C_MASTER_DEV_IT_TEST 1

static i2c_handle_t I2C1_Handle;
uint8_t I2CXferBuf[32];

// 函数定义

/**
 * @brief I2C 模块主模式初始化函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void i2c_master_boardinit(reg_i2c_t *pi2c)
{
    I2C1_Handle.Instance = pi2c;
    I2C1_Handle.Init.Mode = I2C_MODE_MASTER;
    I2C1_Handle.Init.AddBits = I2C_SLAVE_ADD_7BITS;
    I2C1_Handle.Init.Add = 0X60;
    I2C1_Handle.Init.HighSpeed = DISABLE;
    I2C1_Handle.Init.ClockMode = I2C_CLOCK_MODE_NORMAL;
    I2C1_Handle.Init.Prescaler = 0X08;

    hal_i2c_init(&I2C1_Handle);
}

/**
 * @brief I2C 模块从模式初始化函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 * @param AddBits 地址bit长度;
 * @param Add 地址;
 */
void i2c_slave_boardinit(reg_i2c_t *pi2c, i2c_slave_addbits_t AddBits, uint16_t Add)
{
    I2C1_Handle.Instance = pi2c;
    I2C1_Handle.Init.Mode = I2C_MODE_SLAVE;
    I2C1_Handle.Init.AddBits = AddBits;
    I2C1_Handle.Init.Add = Add;
    I2C1_Handle.Init.HighSpeed = DISABLE;
    I2C1_Handle.Init.ClockMode = I2C_CLOCK_MODE_NORMAL;
    I2C1_Handle.Init.Prescaler = 0X04;

    hal_i2c_init(&I2C1_Handle);
}

/**
 * @brief I2C 模块中断初始化函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
static void i2c_itinit(reg_i2c_t *pi2c)
{

    if (pi2c == I2C1)
    {
        NVIC_Init(3, 1, I2C1_IRQn, 2);
        I2C1_IRQHandler_Callback = hal_i2c_irqhandler;
    }
    else if (pi2c == I2C2)
    {
        NVIC_Init(3, 1, I2C2_IRQn, 2);
        I2C2_IRQHandler_Callback = hal_i2c_irqhandler;
    }
}

/**
 * @brief I2C 模块主模式测试函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void i2c_master_test(reg_i2c_t *pi2c)
{
    uint16_t loop = 0;
    status_t HalStatus = STATUS_OK;

    if (pi2c == I2C1)
    {
        printf("I2C1-->\r\n");
    }
    else if (pi2c == I2C2)
    {
        printf("I2C2-->\r\n");
    }
    printf("i2c_master_test\r\n");
    i2c_master_boardinit(pi2c);

    while (1)
    {
        /*I2C MASTER DEV*/
        /*发送8字节数据到从机*/
        I2CXferBuf[0] = 0x80; /**< cal     */
        I2CXferBuf[1] = 0x01; /**< ins     */
        I2CXferBuf[2] = 0x00; /**< p1      */
        I2CXferBuf[3] = 0x00; /**< p2      */
        I2CXferBuf[4] = 0x00; /**< p3      */
        I2CXferBuf[5] = 0x00; /**< le_high */
        I2CXferBuf[6] = 0x20; /**< le_low  */

        printf("\r\nhal_i2c_mastertransmit:\r\n");

        for (loop = 0; loop < 7; loop++)
        {
            printf("%x ", I2CXferBuf[loop]);
        }

        printf("\r\n");
        HalStatus = hal_i2c_mastertransmit(&I2C1_Handle, 0X60, I2CXferBuf, 7, 0);

        if (HalStatus != STATUS_OK)
        {
            printf("hal_i2c_mastertransmit failed\r\n");
        }
        else
        {
            printf("hal_i2c_mastertransmit passed To read response\r\n");
            /*读取8字节数据*/
            HalStatus = hal_i2c_masterreceive(&I2C1_Handle, 0X60, I2CXferBuf, 8, 0);

            if (HalStatus != STATUS_OK)
            {
                printf("hal_i2c_masterreceive failed\r\n");
            }
            else
            {
                printf("hal_i2c_masterreceive response\r\n");

                for (loop = 0; loop < 8; loop++)
                {
                    printf("%x ", I2CXferBuf[loop]);
                }

                printf("\r\n");
            }
        }
        delayms(800);
    }
}

/**
 * @brief I2C 模块从模式测试函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void i2c_slave_test(reg_i2c_t *pi2c)
{
    uint16_t loop = 0;
    status_t HalStatus = STATUS_OK;

    if (pi2c == I2C1)
    {
        printf("I2C1-->\r\n");
    }
    else if (pi2c == I2C2)
    {
        printf("I2C2-->\r\n");
    }
    printf("\r\n i2c_slave_test polling\r\n");

    i2c_slave_boardinit(pi2c, I2C_SLAVE_ADD_7BITS, 0X60);
    // interrupt_setup((INT_SOURCE_I2C + 0X20), 0, hal_i2c_irqhandler);

    while (1)
    {
        /*I2C MASTER DEV*/
        /*读取7字节数据*/
        HalStatus = hal_i2c_slavereceive(&I2C1_Handle, I2CXferBuf, 7, 0);

        if (HalStatus != STATUS_OK)
        {
            printf("\r\nhal_i2c_slavereceive failed\r\n");
        }
        else
        {
            printf("\r\rx:\r\n");

            for (loop = 0; loop < 7; loop++)
            {
                printf("%x ", I2CXferBuf[loop]);
            }

            printf("\r\n");
        }

        if (HalStatus == STATUS_OK)
        {
            /*发送8字节数据到主机*/
            I2CXferBuf[0] = 0X90;
            I2CXferBuf[1] = 0X00;
            I2CXferBuf[2] = 0X00;
            I2CXferBuf[3] = 0X04;
            I2CXferBuf[4] = 0X30;
            I2CXferBuf[5] = 0X31;
            I2CXferBuf[6] = 0X32;
            I2CXferBuf[7] = 0X33;
            HalStatus = hal_i2c_slavetransmit(&I2C1_Handle, I2CXferBuf, 8, 0);

            if (HalStatus != STATUS_OK)
            {
                printf("\r\nhal_i2c_slavetransmit failed\r\n");
            }
            else
            {
                printf("\r\nresponse over\r\n");
            }
        }
    }
}

/**
 * @brief I2C 模块从模式中断测试函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void i2c_slave_it_test(reg_i2c_t *pi2c)
{
    uint32_t RxTimeout = 1000000;
    uint32_t TxTimeout = 1000000;

    uint16_t loop = 0;
    status_t HalStatus = STATUS_OK;

    if (pi2c == I2C1)
    {
        printf("I2C1-->\r\n");
    }
    else if (pi2c == I2C2)
    {
        printf("I2C2-->\r\n");
    }
    printf("i2c_slave_it_test\r\n");

    i2c_slave_boardinit(pi2c, I2C_SLAVE_ADD_7BITS, 0X60);
    i2c_itinit(pi2c);

    while (1)
    {
        /*读取7字节数据*/
        HalStatus = hal_i2c_slavereceiveit(&I2C1_Handle, I2CXferBuf, 7, RxTimeout);

        while (I2C1_Handle.State != HAL_I2C_STATE_READY)
            ;

        printf("\r\rx:\r\n");

        for (loop = 0; loop < 7; loop++)
        {
            printf("%x ", I2CXferBuf[loop]);
        }

        printf("\r\n");

        if (HalStatus == STATUS_OK)
        {
            /*发送8字节数据到主机*/
            I2CXferBuf[0] = 0X90;
            I2CXferBuf[1] = 0X00;
            I2CXferBuf[2] = 0X00;
            I2CXferBuf[3] = 0X04;
            I2CXferBuf[4] = 0X30;
            I2CXferBuf[5] = 0X31;
            I2CXferBuf[6] = 0X32;
            I2CXferBuf[7] = 0X33;
            printf("to resp:\r\n");

            for (loop = 0; loop < 8; loop++)
            {
                printf("%x ", I2CXferBuf[loop]);
            }

            printf("\r\n");
            HalStatus = hal_i2c_slavetransmitit(&I2C1_Handle, I2CXferBuf, 8, TxTimeout);

            while (I2C1_Handle.State != HAL_I2C_STATE_READY)
                ;

            printf("\r\nresponse over\r\n");
        }
    }
}

/**
 * @brief I2C 模块主模式中断测试函数
 *
 * @param pi2c 指向reg_i2c_t结构体的指针;
 */
void i2c_master_it_test(reg_i2c_t *pi2c)
{
    uint32_t RxTimeout = 1000000;
    uint32_t TxTimeout = 1000000;
    uint16_t loop = 0;
    status_t HalStatus = STATUS_OK;

    if (pi2c == I2C1)
    {
        printf("I2C1-->\r\n");
    }
    else if (pi2c == I2C2)
    {
        printf("I2C2-->\r\n");
    }
    printf("i2c_master_it_test\r\n");

    i2c_master_boardinit(pi2c);
    i2c_itinit(pi2c);

    while (1)
    {
        /*发送7字节数据到从机*/
        I2CXferBuf[0] = 0X80;
        I2CXferBuf[1] = 0X01;
        I2CXferBuf[2] = 0X01;
        I2CXferBuf[3] = 0X02;
        I2CXferBuf[4] = 0X33;
        I2CXferBuf[5] = 0X34;
        I2CXferBuf[6] = 0X04;

        printf("\r hal_i2c_mastertransmitit:\r\n");

        for (loop = 0; loop < 7; loop++)
        {
            printf("%x ", I2CXferBuf[loop]);
        }

        printf("\r\n");
        HalStatus = hal_i2c_mastertransmitit(&I2C1_Handle,
                                             0X60,
                                             I2CXferBuf,
                                             7,
                                             TxTimeout);

        while (I2C1_Handle.State != HAL_I2C_STATE_READY)
            ;

        printf("\r  hal_i2c_masterreceiveit\r\n");

#if 1
        /*读取8字节数据*/
        HalStatus = hal_i2c_masterreceiveit(&I2C1_Handle,
                                            0x60,
                                            I2CXferBuf,
                                            8,
                                            RxTimeout);
        HalStatus = HalStatus; // to eliminate warning
        while (I2C1_Handle.State != HAL_I2C_STATE_READY)
        {
            printf("\r\nrx:\r\n");

            for (loop = 0; loop < 8; loop++)
            {
                printf("%x ", I2CXferBuf[loop]);
            }

            printf("\r\n");
        }
#endif
    }
}

/**
 * @brief I2C 模块测试示例函数
 *
 */
void i2c_demo(void)
{
#if I2C_MASTER_DEV_TEST
    SwitchPinFunction(UART5_TX_FUN, I2C1_SDA_FUN); // I2C1_SDA_FUN
    SwitchPinFunction(UART5_RX_FUN, I2C1_SCL_FUN); // I2C1_SCL_FUN
    i2c_master_test(I2C1);
#endif

#if I2C_SLAVE_DEV_TEST
    SwitchPinFunction(UART5_TX_FUN, I2C1_SDA_FUN); // I2C1_SDA_FUN
    SwitchPinFunction(UART5_RX_FUN, I2C1_SCL_FUN); // I2C1_SCL_FUN
    i2c_slave_test(I2C1);
#endif

#if I2C_SLAVE_DEV_IT_TEST
    SwitchPinFunction(UART5_TX_FUN, I2C1_SDA_FUN); // I2C1_SDA_FUN
    SwitchPinFunction(UART5_RX_FUN, I2C1_SCL_FUN); // I2C1_SCL_FUN
    i2c_slave_it_test(I2C1);
#endif

#if I2C_MASTER_DEV_IT_TEST
    SwitchPinFunction(UART5_TX_FUN, I2C1_SDA_FUN); // I2C1_SDA_FUN
    SwitchPinFunction(UART5_RX_FUN, I2C1_SCL_FUN); // I2C1_SCL_FUN
    i2c_master_it_test(I2C1);
#endif
}


/** @} */  // 结束 I2C 模块分组
/** @} */  // 结束外设模块分组
