/**
 * @file nandflash_interface.c
 * @author Product Application Department
 * @brief   nand flash 测试用例，仅供参考
 * @version V1.0
 * @date 2025-06-04
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#include "nandflash_interface.h"
#include "eport_hal.h"
#include "ssi_hal.h"
#include "pinswap_drv.h"

// 宏定义
#define NANDSPI SSI3
#define NANDSPI_CS_PORT EPORT4
#define NANDSPI_CS_PIN  EPORT4_PIN0
#define NANDSPI4WIRE    1
#define NANDAXIDMA      1
// 全局变量定义
nand_flash_info_t g_nand_info;
static bool g_nand_initialized = false;

nand_flash_info_t nand_known_flash_info[] = {
    // Foresee F35SQA512M
    // 16-bit address, 2048 bytes/page, 64 bytes/spare, 64 pages/block, 512 blocks
    {
        .manufacturer_id = 0xCD,
        .name = "Foresee",
        .device_id_high = 0x70,
        .device_id_low = 0x70,
        .page_size_bytes = 2048,
        .spare_size_bytes = 64,
        .pages_per_block = 64,
        .total_blocks = 512,
    },
    // TO DO: 其他已知的Flash型号
    // ...
    // unknown
    {
        .manufacturer_id = 0x00,
        .name = "unknown",
    }
};

// 函数声明
// SPI接口函数声明 
static void nand_spi_cs_select(void)
{
    hal_eport_writepinlevel(NANDSPI_CS_PORT, NANDSPI_CS_PIN, GPIO_LOW);
}
static void nand_spi_cs_deselect(void)
{
    hal_eport_writepinlevel(NANDSPI_CS_PORT, NANDSPI_CS_PIN, GPIO_HIGH);
}
static void nand_spi_transmit_byte(uint8_t data)
{
    hal_ssi_tx(NANDSPI, &data, 1);
}
static uint8_t nand_spi_receive_byte(void)
{
    uint8_t data;
    hal_ssi_rx(NANDSPI, &data, 1);
    return data;
}
static uint8_t nand_spi_transmit_receive_byte(uint8_t tx_data)
{
    //预留接口，用户根据实际情况实现
    return 0;
}
static void nand_spi_transmit_buffer(uint8_t* p_tx_data, uint16_t len)
{
    hal_ssi_tx(NANDSPI, p_tx_data, len);
    SCB_InvalidateDCache();
}
static void nand_spi_receive_buffer(uint8_t* p_rx_data, uint16_t len)
{
    hal_ssi_rx(NANDSPI, p_rx_data, len);
    SCB_InvalidateDCache();
}

/**
 * @brief 延时函数 (用户需要根据MCU平台实现)
 * @param ms 延时毫秒数
 */
static void nand_delay_ms(volatile uint32_t ms) {
    delayms(ms);
}

/**
 * @brief 发送写使能命令
 */
static void nand_write_enable(void) {
    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_WRITE_ENABLE);
    nand_spi_cs_deselect();
}

/**
 * @brief 发送写禁止命令
 */
static void nand_write_disable(void) {
    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_WRITE_DISABLE);
    nand_spi_cs_deselect();
}

/**
 * @brief 等待NAND Flash操作完成 (通过查询BUSY位)
 * @param timeout_ms 超时时间
 * @return NAND_OK 操作完成, NAND_ERROR_TIMEOUT 超时, NAND_ERROR_BUSY (虽然不太可能，但保留)
 */
static nand_status_t nand_wait_ready(uint32_t timeout_ms) {
    uint8_t status;

    do {
        nand_status_t res = nand_flash_read_status_register(NAND_CMD_STATUS_REGISTER_3, &status);
        if (res != NAND_OK) {
            return res; // 读取状态失败
        }
        if (!(status & NAND_STATUS_REG3_BUSY)) {
            return NAND_OK; // 不再忙碌
        }

        nand_delay_ms(1); // 短暂延时后再次查询
        timeout_ms = (timeout_ms > 0) ? (timeout_ms -1) : 0;

    } while (timeout_ms > 0); // (status & NAND_STATUS_REG3_BUSY) && timeout_ms > 0);

    return NAND_ERROR_TIMEOUT;
}


/**
 * @brief 复位NAND Flash芯片
 */
static nand_status_t nand_device_reset(void) {
    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_DEVICE_RESET);
    nand_spi_cs_deselect();
    
    // 复位后需要等待一段时间才能进行其他操作
    return nand_wait_ready(NAND_TIMEOUT_MS_RESET);
}

/**
 * @brief 内部函数，将页数据加载到NAND内部缓存
 * @param page_addr 页地址
 * @return NAND_OK or error
 */
static nand_status_t nand_load_page_to_cache(uint32_t page_addr) {
    nand_status_t status;
    
    status = nand_wait_ready(NAND_TIMEOUT_MS_READ_STATUS);
    if (status != NAND_OK) return status;

    uint8_t cmd_buffer[4];
    cmd_buffer[0] = NAND_CMD_PAGE_DATA_READ;
    cmd_buffer[1] = (page_addr >> 16) & 0xFF; // Dummy byte for some NANDs or actual address
    cmd_buffer[2] = (page_addr >> 8) & 0xFF;  // Page Address PA15-PA8
    cmd_buffer[3] = (page_addr >> 0) & 0xFF;  // Page Address PA7-PA0

    nand_spi_cs_select();
    nand_spi_transmit_buffer(cmd_buffer, 4);
    nand_spi_cs_deselect();

    // 等待数据从Flash Array加载到Cache完成 (tRD ~25-60us for W25N01GV)
    return nand_wait_ready(NAND_TIMEOUT_MS_READ_STATUS); // Use a short timeout
}


// 外部接口函数申明
/**
 * @brief 初始化NAND Flash
 * @param p_info 指向存储NAND Flash信息的结构体指针
 * @return NAND_OK成功, 其他为错误码
 */
nand_status_t nand_flash_init(nand_flash_info_t* p_info) {
    if (!p_info) return NAND_ERROR_INVALID_ADDR; // Or some other error for null pointer

    // 0. SPI外设的初始化并设置复用关系
    ssi_handle_t SSIHandle;
    SSIHandle.Instance = NANDSPI;
    hal_ssi_init(&SSIHandle);
    SwitchPinFunction(SPI6_CS_FUN, EPORT4_PIN0_FUN);
    hal_eport_output(NANDSPI_CS_PORT, NANDSPI_CS_PIN);

    // 1. 初始化g_nand_info结构体
    memset(&g_nand_info, 0, sizeof(nand_flash_info_t));
    g_nand_initialized = false;

    // 2. 复位NAND Flash芯片
    nand_status_t status = nand_device_reset();
    if (status != NAND_OK) {
        return status; // 复位失败
    }

    nand_flash_write_status_register(NAND_CMD_STATUS_REGISTER_1, 0X00);

    // 3. 读取JEDEC ID
    status = nand_flash_read_jedec_id(
        &g_nand_info.manufacturer_id,
        &g_nand_info.device_id_high,
        &g_nand_info.device_id_low
    );
    if (status != NAND_OK) {
        return status;
    }

    // 4. 根据JEDEC ID填充Flash信息
    if (g_nand_info.manufacturer_id == 0xCD &&  // Foresee
        g_nand_info.device_id_high == 0x70 &&   // Device ID
        g_nand_info.device_id_low == 0x70) {    // F35SQA512M (512Mbit)
        
        g_nand_info = nand_known_flash_info[0];
        printf("Manufacturer: %s\r\n", g_nand_info.name);
        printf("JEDEC ID: 0x%02X 0x%02X 0x%02X\r\n", g_nand_info.manufacturer_id, g_nand_info.device_id_high, g_nand_info.device_id_low);

        // Check Status Register-2 for ECC status, BUF bit (buffer mode)
        uint8_t sr2_val = 0x11, sr_stat; // QE bit
        nand_flash_write_status_register(NAND_CMD_STATUS_REGISTER_2, sr2_val);
        nand_flash_read_status_register(NAND_CMD_STATUS_REGISTER_2, &sr_stat);
        g_nand_info.ecc_enabled_by_default = (sr2_val & (1<<4)); // ECC-E bit in SR2
    } else {
        // TO DO: 完善对不同Flash的支持
        return NAND_ERROR_INVALID_ADDR; // Unknown device
    }
    g_nand_info.total_pages = (uint32_t)g_nand_info.total_blocks * g_nand_info.pages_per_block;

    // 将配置好的信息复制到用户提供的指针
    memcpy(p_info, &g_nand_info, sizeof(nand_flash_info_t));
    g_nand_initialized = true;
    return NAND_OK;
}

/**
 * @brief 读取NAND Flash JEDEC ID
 * @param p_manufacturer_id 指向存储厂商ID的指针
 * @param p_device_id_high 指向存储设备ID高字节的指针
 * @param p_device_id_low 指向存储设备ID低字节的指针
 * @return NAND_OK成功, 其他为错误码
 */
nand_status_t nand_flash_read_jedec_id(uint8_t* p_manufacturer_id, uint8_t* p_device_id_high, uint8_t* p_device_id_low) {
    if (!p_manufacturer_id || !p_device_id_high || !p_device_id_low) {
        return NAND_ERROR_INVALID_ADDR;
    }

    uint8_t id_data[3];

    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_JEDEC_ID);
    
    nand_spi_receive_byte(); // Dummy byte
    nand_spi_receive_buffer(id_data, 3);
    nand_spi_cs_deselect();

    *p_manufacturer_id = id_data[0];
    *p_device_id_high  = id_data[1];
    *p_device_id_low   = id_data[2];

    return NAND_OK;
}

/**
 * @brief 读取NAND Flash状态寄存器
 * @param reg_addr 状态寄存器地址
 * @param p_status 指向存储状态值的指针
 * @return NAND_OK成功, 其他为错误码
 */
nand_status_t nand_flash_read_status_register(uint8_t reg_addr, uint8_t* p_status) {
    if (!p_status) return NAND_ERROR_INVALID_ADDR;

    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_GET_STATUS_REGISTER); 
    nand_spi_transmit_byte(reg_addr); 
    *p_status = nand_spi_receive_byte();
    // while (*p_status & NAND_STATUS_REG3_BUSY) {
    //     *p_status = nand_spi_receive_byte();
    // }
    
    nand_spi_cs_deselect();
    return NAND_OK;
}

/**
 * @brief 写入NAND Flash状态寄存器
 * @param reg_addr 写入哪个状态寄存器的命令
 * @param reg_data 状态寄存器地址
 * @return nand_status_t 
 */
nand_status_t nand_flash_write_status_register(uint8_t reg_addr, uint8_t reg_data)
{
    nand_spi_cs_select();
    nand_spi_transmit_byte(NAND_CMD_SET_STATUS_REGISTER);
    nand_spi_transmit_byte(reg_addr); 
    nand_spi_transmit_byte(reg_data); 
    
    nand_spi_cs_deselect();
    return NAND_OK;
}

/**
 * @brief 从NAND Flash读取一页数据 (包括主数据区和可选的OOB区)
 * @param page_addr 绝对页地址
 * @param p_main_buffer 指向主数据区缓冲区的指针 (大小应为 page_size_bytes)
 * @param p_spare_buffer 指向OOB/Spare区缓冲区的指针 (大小应为 spare_size_bytes), 若为NULL则不读取OOB
 * @return NAND_OK成功, 其他为错误码 (包括ECC状态)
 */
nand_status_t nand_flash_page_read(uint32_t page_addr, uint8_t* p_main_buffer, uint8_t* p_spare_buffer) {
    if (!g_nand_initialized) return NAND_ERROR_NOT_INITIALIZED;
    if (page_addr >= g_nand_info.total_pages) return NAND_ERROR_INVALID_ADDR;
    if (!p_main_buffer) return NAND_ERROR_INVALID_ADDR; // Main buffer is mandatory

    nand_status_t status;
    uint8_t sr3_val;
    ssi_handle_t SSIHandle;
    SSIHandle.Instance = NANDSPI;

    // 1. 将页数据从Flash Array加载到内部数据缓存
    status = nand_load_page_to_cache(page_addr);
    if (status != NAND_OK) return status;

    // 2. 检查状态寄存器中的ECC状态
    nand_flash_read_status_register(NAND_CMD_STATUS_REGISTER_3, &sr3_val);
    uint8_t ecc_status = (sr3_val >> 4) & 0x03;
    if (ecc_status == 0x02) { // 10 = Uncorrectable ECC error
        // Optionally, still read the data but return error
        // For now, just return error.
        return NAND_ERROR_ECC_UNCORRECTABLE;
    }
    // if ecc_status == 0x01, data is corrected. Proceed.
    // if ecc_status == 0x00, no error. Proceed.

    // 3. 从缓存中读取数据
    //    Column Address (CA): 2 bytes for W25N01GV. CA11-CA0.
    //    Main data starts at CA=0x0000. Spare data starts at CA=page_size (e.g. 0x0800 for 2KB page)
    uint8_t cmd_buffer[3]; // Command + 2 bytes Column Address

    #if(NANDSPI4WIRE)
    cmd_buffer[0] = NAND_CMD_READ_FROM_CACHEX4;
    #else
    cmd_buffer[0] = NAND_CMD_READ_FROM_CACHE; // Or NAND_CMD_FAST_READ_FROM_CACHE (0x0B) + dummy byte if needed
    #endif

    // Read main data
    cmd_buffer[1] = 0x00; // Column Address High Byte
    cmd_buffer[2] = 0x00; // Column Address Low Byte

    nand_spi_cs_select();
    #if(NANDAXIDMA)
    #else
    nand_spi_transmit_buffer(cmd_buffer, 3);
    #endif
    // If using FAST_READ (0x0B), often a dummy byte is needed after address before data out
    // nand_spi_transmit_byte(0x00); // Dummy byte for fast read
    #if(NANDSPI4WIRE)
    #if(NANDAXIDMA)
    hal_ssi_qualinit(&SSIHandle, 2047, SSIFreq100M, 1,1, 2);
    hal_axidma_rx(0,p_main_buffer, g_nand_info.page_size_bytes);
    #else
    hal_ssi_qualinit(&SSIHandle, 2047, SSIFreq100M, 1,0, 2);
    nand_spi_receive_buffer(p_main_buffer, g_nand_info.page_size_bytes + 1); // ATT: 多读一位否则会丢最后一个字节
    #endif
    
    // nand_spi_transmit_byte(0x00); // Dummy byte for fast read
    
    hal_ssi_init(&SSIHandle);
    #else
    nand_spi_transmit_byte(0x00); // Dummy byte for fast read
    nand_spi_receive_buffer(p_main_buffer, g_nand_info.page_size_bytes);
    #endif
    nand_spi_cs_deselect(); // Deselect after reading main data to allow new command for spare

    // Read spare data if requested
    if (p_spare_buffer) {
        cmd_buffer[1] = (g_nand_info.page_size_bytes >> 8) & 0xFF; // CA High for spare
        cmd_buffer[2] = (g_nand_info.page_size_bytes >> 0) & 0xFF; // CA Low for spare
        
        nand_spi_cs_select();
        nand_spi_transmit_buffer(cmd_buffer, 3);
        // If using FAST_READ (0x0B), dummy byte here too
        nand_spi_transmit_byte(0x00); // Dummy byte

        #if(NANDSPI4WIRE)
        #if(NANDAXIDMA)
         hal_ssi_qualinit(&SSIHandle, 2047, SSIFreq100M, 1,1, 2);
        #else
         hal_ssi_qualinit(&SSIHandle, 2047, SSIFreq100M, 1,0, 2);
        #endif
        nand_spi_receive_buffer(p_spare_buffer, g_nand_info.spare_size_bytes);
        hal_ssi_init(&SSIHandle);
        #else
        nand_spi_receive_buffer(p_spare_buffer, g_nand_info.spare_size_bytes);
        #endif
        nand_spi_cs_deselect();
    }
    
    if (ecc_status == 0x01) {
        // Data was corrected by internal ECC. Application might want to know.
        // For this basic driver, we treat it as success but a more advanced
        // driver might return a specific status like NAND_WARN_ECC_CORRECTED.
    }
    return NAND_OK;
}

/**
 * @brief 向NAND Flash编程一页数据 (包括主数据区和可选的OOB区)
 * @param page_addr 绝对页地址
 * @param p_main_data 指向主数据区数据的指针 (大小应为 page_size_bytes)
 * @param p_spare_data 指向OOB/Spare区数据的指针 (大小应为 spare_size_bytes), 若为NULL则OOB区可能写入0xFF或由芯片自动处理ECC
 * @return NAND_OK成功, 其他为错误码
 */
nand_status_t nand_flash_page_program(uint32_t page_addr, const uint8_t* p_main_data, const uint8_t* p_spare_data) {
    if (!g_nand_initialized) return NAND_ERROR_NOT_INITIALIZED;
    if (page_addr >= g_nand_info.total_pages) return NAND_ERROR_INVALID_ADDR;
    if (!p_main_data) return NAND_ERROR_INVALID_ADDR; // Main data is mandatory

    nand_status_t status;
    uint8_t sr3_val;
    ssi_handle_t SSIHandle;
    SSIHandle.Instance = NANDSPI;

    // 1. 写使能
    nand_write_enable();

    // 2. 加载数据到缓存 (Program Load)
    //    Column Address (CA) is 0x0000 for starting write from beginning of page.
    uint8_t cmd_buffer[4]; // Max possible size
    uint8_t data_buffer[g_nand_info.page_size_bytes + g_nand_info.spare_size_bytes]; // Max possible size
    uint16_t current_tx_len = 0;

    #if(NANDSPI4WIRE)
    cmd_buffer[0] = NAND_CMD_PROGRAM_LOADX4;
    #else
    cmd_buffer[0] = NAND_CMD_PROGRAM_LOAD;
    #endif
    cmd_buffer[1] = 0x00; // Column Address High Byte
    cmd_buffer[2] = 0x00; // Column Address Low Byte

    memcpy(&data_buffer[0], p_main_data, g_nand_info.page_size_bytes);
    current_tx_len = g_nand_info.page_size_bytes;

    if (p_spare_data) {
        // If spare data is provided, append it.
        // Note: W25N01GV datasheet states that for PROGRAM_LOAD (0x02), data is loaded sequentially.
        // To write only spare or random data, PROGRAM_LOAD_RANDOM (0x84) should be used.
        // Here, we assume writing main + spare sequentially.
        memcpy(&data_buffer[current_tx_len], p_spare_data, g_nand_info.spare_size_bytes);
        current_tx_len += g_nand_info.spare_size_bytes;
    } else {
        // If no spare data provided, and ECC is on, the chip might automatically calculate
        // and store ECC in the spare area. Or, we might need to fill spare with 0xFF.
        // For W25N01GV, if internal ECC is on, it uses first few bytes of spare.
        // It's often good practice to provide a spare buffer filled with 0xFF if not used.
        // For simplicity here, we assume if p_spare_data is NULL, we don't send spare bytes.
        // The chip will likely program 0xFFs for the unsent portion of the page buffer.
    }
    
    nand_spi_cs_select();
    nand_spi_transmit_buffer(cmd_buffer, 3);

    #if(NANDSPI4WIRE)
    uint8_t temp;
    hal_ssi_qualinit(&SSIHandle, 0, SSIFreq100M, 0,0, 0);
    nand_spi_transmit_buffer(data_buffer, current_tx_len);
    hal_ssi_init(&SSIHandle);
    #else
    nand_spi_transmit_buffer(data_buffer, current_tx_len);
    #endif

    nand_spi_cs_deselect();

    // 3. 执行编程 (Program Execute)
    //    Page Address (PA) is sent with this command.
    cmd_buffer[0] = NAND_CMD_PROGRAM_EXECUTE;
    cmd_buffer[1] = (page_addr >> 16) & 0xFF; // Dummy or address for some NANDs
    cmd_buffer[2] = (page_addr >> 8) & 0xFF;  // PA15-PA8
    cmd_buffer[3] = (page_addr >> 0) & 0xFF;  // PA7-PA0

    nand_spi_cs_select();
    #if(NANDSPI4WIRE)
    nand_spi_transmit_buffer(cmd_buffer, 4);
    #else
    nand_spi_transmit_buffer(cmd_buffer, 4);
    #endif
    nand_spi_cs_deselect();

    // 4. 等待编程完成
    status = nand_wait_ready(NAND_TIMEOUT_MS_PAGE_PROGRAM);
    if (status != NAND_OK) {
        nand_write_disable(); // Ensure WEL is cleared on timeout
        return status;
    }

    // 5. 检查编程状态 (PFAIL bit in SR3)
    nand_flash_read_status_register(NAND_CMD_STATUS_REGISTER_3, &sr3_val);
    if (sr3_val & NAND_STATUS_REG3_PFAIL) {
        nand_write_disable();
        return NAND_ERROR_PROGRAM_FAIL;
    }

    // 6. 写禁止 (optional, good practice but WEL is cleared after program/erase)
    // nand_write_disable(); // WEL is automatically cleared by Program Execute

    return NAND_OK;
}

/**
 * @brief 擦除NAND Flash一个块
 * @param block_addr 绝对块地址 (注意: 不是页地址)
 * @return NAND_OK成功, 其他为错误码
 */
nand_status_t nand_flash_block_erase(uint32_t block_addr) {
    if (!g_nand_initialized) return NAND_ERROR_NOT_INITIALIZED;
    if (block_addr >= g_nand_info.total_blocks) return NAND_ERROR_INVALID_ADDR;

    nand_status_t status;
    uint8_t sr3_val;
    uint32_t page_addr_of_block = block_addr * g_nand_info.pages_per_block;

    // 1. 写使能
    nand_write_enable();

    // 2. 发送块擦除命令
    //    Block Erase (0xD8) command takes a page address within the block to be erased.
    //    Any page address within the target block is valid.
    uint8_t cmd_buffer[4];
    cmd_buffer[0] = NAND_CMD_BLOCK_ERASE;
    cmd_buffer[1] = (page_addr_of_block >> 16) & 0xFF; // Dummy or address for some NANDs
    cmd_buffer[2] = (page_addr_of_block >> 8) & 0xFF;  // PA15-PA8
    cmd_buffer[3] = (page_addr_of_block >> 0) & 0xFF;  // PA7-PA0
    
    nand_spi_cs_select();
    nand_spi_transmit_buffer(cmd_buffer, 4);
    nand_spi_cs_deselect();

    // 3. 等待擦除完成 (tBE ~2ms-10ms)
    status = nand_wait_ready(NAND_TIMEOUT_MS_BLOCK_ERASE);
    if (status != NAND_OK) {
        nand_write_disable(); // Ensure WEL is cleared on timeout
        return status;
    }

    // 4. 检查擦除状态 (EFAIL bit in SR3)
    nand_flash_read_status_register(NAND_CMD_STATUS_REGISTER_3, &sr3_val);
    if (sr3_val & NAND_STATUS_REG3_EFAIL) {
        nand_write_disable();
        return NAND_ERROR_ERASE_FAIL;
    }
    
    // 5. 写禁止 (optional, WEL is cleared after program/erase)
    // nand_write_disable(); // WEL is automatically cleared by Erase Execute

    return NAND_OK;
}

