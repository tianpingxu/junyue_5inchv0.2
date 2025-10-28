/**
 *  @file ssi_test.c
 *  @author Product application department
 *  @brief  SSI 模块测试用例，仅供参考
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup SSI SSI模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "ssi_test.h"
#include "ssi_sram.h"
// 函数定义
/**
 *  @brief  随机数生成函数
 *
 *  @param seed 伪随机数生成
 *  @param psrc 伪随机数据指针
 *  @param len 生成长度
 */
static void dummy_trng(uint32_t seed, uint8_t *psrc, uint32_t len)
{
    uint32_t next = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    next = seed;
    for (i = len, j = 0; i > 0;)
    {
        next = next * 1103515245 + 12345;
        if (i > 4)
        {
            memcpy(psrc + j, (uint8_t *)&next, 4);
            i -= 4;
            j += 4;
        }
        else
        {
            memcpy(psrc + j, (uint8_t *)&next, i);
            i -= i;
            j += i;
        }
    }
}
#include "pinswap_drv.h"
#include "eport_hal.h"
/**
 *  @brief  SSI 模块测试示例函数
 *
 */
void ssi_demo(void)
{
    uint8_t write[SSI_SECTOR_SIZE];
    uint8_t read[SSI_SECTOR_SIZE];
    uint32_t address = 0;
    uint8_t i = 0;
    uint8_t ssi_id = SSIID1;

    printf("\t|-FLASH擦除测试: ");
    printf("erase start\r\n");
    for (i = 0; i < 32; i++)
    {
        if (hal_ssi_flash_sector_erase(DATA_FIELDS_BEGIN_ADDR))
        {
            printf("行号: %d ERR\r\n", __LINE__);
        }
    }
    printf("erase end!\r\n");

    printf("通过\r\n");

    dummy_trng(0x55AA5A5A, write, SSI_SECTOR_SIZE);

    printf("\t|-FLASH PAGE对其写测试: ");
    if (hal_ssi_flash_program(DATA_FIELDS_BEGIN_ADDR, write, SSI_PAGE_SIZE))
    {
        printf("行号: %d ERR\r\n", __LINE__);
    }

    hal_ssi_flash_read(DATA_FIELDS_BEGIN_ADDR, read, SSI_PAGE_SIZE);

    if (memcmp(write, read, SSI_PAGE_SIZE))
    {
        printf("行号: %d ERR\r\n", __LINE__);
    }
    printf("通过\r\n");

    printf("\t|-FLASH SECTOR编程测试\r\n");
    printf("\t|---开始: 0x%08x\r\n", DATA_FIELDS_BEGIN_ADDR);
    printf("\t|---结束: 0x%08x\r\n", DATA_FIELDS_END_ADDR);
    printf("\t|---大小: 0x%08x\r\n", DATA_FIELDS_SIZE);
    for (address = DATA_FIELDS_BEGIN_ADDR; address < DATA_FIELDS_END_ADDR; address += SSI_SECTOR_SIZE)
    {
        printf("address = %08x\r\n", address);
        if (hal_ssi_flash_sector_erase(address))
        {
            printf("erase address = %08x\t", address);
            printf("行号: %d ERR\r\n", __LINE__);
        }

        if (hal_ssi_flash_program(address, write, SSI_SECTOR_SIZE))
        {
            printf("program address = %08x\t", address);
            printf("行号: %d ERR\r\n", __LINE__);
        }

        hal_ssi_flash_read(address, read, SSI_SECTOR_SIZE);
        if (memcmp(write, read, SSI_SECTOR_SIZE) != 0)
        {
          printf("address = %08x\t", address);
          printf("行号: %d ERR\r\n", __LINE__);
        }
    }
    printf("通过\r\n");
    printf("=========================================\r\n");
}

/** @} */  // 结束 SSI 模块分组
/** @} */  // 结束外设模块分组
