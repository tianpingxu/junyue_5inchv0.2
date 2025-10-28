/**
 * @file nandflash_test.c
 * @author Product Application Department
 * @brief   nand flash 测试用例，仅供参考
 * @version V1.0
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup nand nand模块
 * @ingroup Peripherals
 * @{
 */
 

// 头文件包含
#include "nandflash_test.h"
#include "debug.h"

// 函数定义
/**
 *  @brief  NAND 测试示例函数
 * 
 */
void nandflash_demo(void)
{
    nand_status_t nanstatus;
    uint8_t g_main_buffer[2048] = {0};

    printf("nand_flash demo...\r\n");
    nanstatus = nand_flash_init(&g_nand_info);
    if (nanstatus != NAND_OK)
    {
        printf("nand_flash_init error.\r\n");
    }else{
        printf("nand_flash_init ok.\r\n");
    }

    nanstatus = nand_flash_page_read(0, g_main_buffer, NULL);
    if (nanstatus != NAND_OK) {
        printf("nand_flash_page_read error\r\n");
        return; // Or handle error appropriately
    } else {
        printf("nand_flash_page_read ok.\r\n");
    }
    printf(">> buff: \r\n");
    for (int i = 0; i < 512; i++)
    {
        printf("0x%02x ", g_main_buffer[i]);
        if ((i+1)%16 == 0)
        {
            printf("\r\n");
        }
    }

    nanstatus = nand_flash_block_erase(10);
    if (nanstatus != NAND_OK) {
        printf("nand_flash_block_erase error\r\n");
        return; // Or handle error appropriately
    } else {
        printf("nand_flash_block_erase ok.\r\n");
    }

    for (int i = 0; i < 2048; i++)
    {
        g_main_buffer[i] = i+8;
    }

    nanstatus = nand_flash_page_program(640, g_main_buffer, NULL);
    if (nanstatus != NAND_OK) {
        printf("nand_flash_page_program error\r\n");
        return; // Or handle error appropriately
    } else {
        printf("nand_flash_page_program ok.\r\n");
    }
    printf(">> write buff: \r\n");
    for (int i = 0; i < 2048; i++)
    {
        printf("0x%02x ", g_main_buffer[i]);
        if ((i+1)%16 == 0)
        {
            printf("\r\n"); 
        }
    }

    memset(g_main_buffer, 0, sizeof(g_main_buffer));
    nanstatus = nand_flash_page_read(640, g_main_buffer, NULL);
    if (nanstatus != NAND_OK) {
        printf("nand_flash_page_read error\r\n");
        return; // Or handle error appropriately
    } else {
        printf("nand_flash_page_read ok.\r\n");
    }
    printf(">> read buff: \r\n");
    for (int i = 0; i < 2048; i++)
    {
        printf("0x%02x ", g_main_buffer[i]);
        if ((i+1)%16 == 0)
        {
            printf("\r\n");
        }
    }
}

/** @} */  // 结束 nand 模块分组
/** @} */  // 结束外设模块分组
