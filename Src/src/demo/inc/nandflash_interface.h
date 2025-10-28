/**
 * @file nandflash_interface.h
 * @author Product Application Department
 * @brief  nand flash 测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef NANDFLASH_INTERFACE_H
#define NANDFLASH_INTERFACE_H

// 头文件包含
#include "type.h"
#include <stdbool.h>

// 宏定义
// 操作超时时间 (可以根据MCU时钟和NAND Flash规格调整)
#define NAND_TIMEOUT_MS_READ_STATUS   100   // 读取状态寄存器超时
#define NAND_TIMEOUT_MS_PAGE_PROGRAM  50    // 页编程超时 (典型值250us-1ms, 芯片手册为准)
#define NAND_TIMEOUT_MS_BLOCK_ERASE   500   // 块擦除超时 (典型值2ms-10ms, 芯片手册为准)
#define NAND_TIMEOUT_MS_RESET         1000  // 复位后等待

// 常用NAND Flash命令
#define NAND_CMD_DEVICE_RESET           0xFF
#define NAND_CMD_JEDEC_ID               0x9F
#define NAND_CMD_SET_STATUS_REGISTER    0x1F
#define NAND_CMD_GET_STATUS_REGISTER    0x0F
#define NAND_CMD_STATUS_REGISTER_1      0xA0
#define NAND_CMD_STATUS_REGISTER_2      0xB0
#define NAND_CMD_STATUS_REGISTER_3      0xC0
#define NAND_CMD_WRITE_ENABLE           0x06
#define NAND_CMD_WRITE_DISABLE          0x04
#define NAND_CMD_BLOCK_ERASE            0xD8 // Erase 64KB Block (some use 0x20 for 128KB erase)
#define NAND_CMD_PAGE_DATA_READ         0x13 // Load Page Data into Cache
#define NAND_CMD_READ_FROM_CACHE        0x03 // Read Data from Cache (normal speed)
#define NAND_CMD_READ_FROM_CACHEX4      0x6B
#define NAND_CMD_FAST_READ_FROM_CACHE   0x0B // Fast Read Data from Cache
// For reading from cache with 2/4 I/O lines, commands are different (e.g., 0x3B, 0x6B, 0xEB)

#define NAND_CMD_PROGRAM_LOAD           0x02 // Load Program Data to Cache (page program)
#define NAND_CMD_PROGRAM_LOADX4         0x32
#define NAND_CMD_PROGRAM_LOAD_RANDOM    0x84 // Load Program Data Randomly to Cache
#define NAND_CMD_PROGRAM_EXECUTE        0x10 // Execute Program (write cache to flash array)

// Status Register-3 (S_STATUS) bits
#define NAND_STATUS_REG3_BUSY           (1 << 0) // BUSY bit (0=Ready, 1=Busy)
#define NAND_STATUS_REG3_WEL            (1 << 1) // Write Enable Latch (0=Disabled, 1=Enabled)
#define NAND_STATUS_REG3_EFAIL          (1 << 2) // Erase Fail
#define NAND_STATUS_REG3_PFAIL          (1 << 3) // Program Fail
#define NAND_STATUS_REG3_ECC_STATUS_0   (1 << 4) // ECC Status bit 0
#define NAND_STATUS_REG3_ECC_STATUS_1   (1 << 5) // ECC Status bit 1
// ECC Status: 00=No error, 01=1-bit error corrected, 10=Uncorrectable, 11=Reserved

// 结构体定义
/**
 * @brief NAND Flash参数结构体 (初始化后填充)
 * 
 */
typedef struct {
    uint8_t  manufacturer_id;
    char     *name;
    char     *description;
    uint8_t  device_id_high;
    uint8_t  device_id_low;    // JEDEC ID often has 3 bytes
    uint16_t page_size_bytes;  // e.g., 2048 bytes
    uint16_t spare_size_bytes; // e.g., 64 bytes per page
    uint16_t pages_per_block;  // e.g., 64 pages
    uint16_t total_blocks;     // e.g., 1024 blocks
    uint32_t total_pages;      // Calculated: total_blocks * pages_per_block
    bool     ecc_enabled_by_default; // Some chips have built-in ECC enabled by default
} nand_flash_info_t;

/**
 * @brief 操作结果枚举
 * 
 */
typedef enum {
    NAND_OK = 0,
    NAND_ERROR_TIMEOUT,
    NAND_ERROR_BUSY,
    NAND_ERROR_ECC_UNCORRECTABLE,
    NAND_ERROR_PROGRAM_FAIL,
    NAND_ERROR_ERASE_FAIL,
    NAND_ERROR_INVALID_ADDR,
    NAND_ERROR_SPI_FAIL,       // For lower level SPI issues if detectable
    NAND_ERROR_NOT_INITIALIZED,
} nand_status_t;



// 全局变量
extern nand_flash_info_t g_nand_info;

// 函数声明
// void nand_spi_cs_select(void);
// void nand_spi_cs_deselect(void);
// void nand_spi_transmit_byte(uint8_t data);
// uint8_t nand_spi_receive_byte(void);
// uint8_t nand_spi_transmit_receive_byte(uint8_t tx_data);
// void nand_spi_transmit_buffer(const uint8_t* p_tx_data, uint16_t length);
// void nand_spi_receive_buffer(uint8_t* p_rx_data, uint16_t length);

nand_status_t nand_flash_init(nand_flash_info_t* p_info);
nand_status_t nand_flash_read_jedec_id(uint8_t* p_manufacturer_id, uint8_t* p_device_id_high, uint8_t* p_device_id_low);
nand_status_t nand_flash_page_read(uint32_t page_addr, uint8_t* p_main_buffer, uint8_t* p_spare_buffer);
nand_status_t nand_flash_page_program(uint32_t page_addr, const uint8_t* p_main_data, const uint8_t* p_spare_data);
nand_status_t nand_flash_block_erase(uint32_t block_addr);
nand_status_t nand_flash_read_status_register(uint8_t reg_addr, uint8_t* p_status);
nand_status_t nand_flash_write_status_register(uint8_t reg_addr, uint8_t reg_data);
const nand_flash_info_t* nand_flash_get_info(void);

#endif
