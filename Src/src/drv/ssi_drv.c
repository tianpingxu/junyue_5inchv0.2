/**
 *  @file ssi_drv.c
 *  @author Product application department
 *  @brief  SSI 模块驱动层
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "ssi_drv.h"
#include "cpm_drv.h"
#include "ssi_sram.h"
#include "pinswap_drv.h"
#include "eport_hal.h"
// 全局变量定义
static ssi_ops_func_t ssi_ops;
static ssi_para_t ssi_cfg[3];
extern uint8_t OSC500M_EN;

// 函数定义

/**
 *  @brief  SSI 模块获取ID编号函数
 *
 *  @param addr SSI 物理地址
 *  @return uint8_t 返回 SSI 编号数值(0，1，2)
 */
uint8_t drv_ssi_get_ssi_id(uint32_t addr)
{
    uint8_t ssi_id = 0;

    if ((addr >= SSI1_LOW_ADDR) && (addr < SSI1_HIGH_ADDR))
    {
        // SSI1
        ssi_id = 1;
    }
    else if ((addr >= SSI2_LOW_ADDR) && (addr < SSI2_HIGH_ADDR))
    {
        // SSI2
        ssi_id = 2;
    }
    else if ((addr >= SSI3_LOW_ADDR) && (addr < SSI3_HIGH_ADDR))
    {
        // SSI3
        ssi_id = 3;
    }

    return ssi_id;
}

/**
 *  @brief  SSI 模块读取XIP状态函数
 *
 *  @param addr SSI 物理地址
 *  @return uint8_t 返回 XIP 状态值
 */
uint8_t drv_ssi_get_xip_state(uint32_t addr)
{
    uint8_t ssi_id = drv_ssi_get_ssi_id(addr);
    uint8_t xip_state = 0;

    if (ssi_id == 1)
    {
        // SSI1, 待修改
        if (((CCM->SSICFGR & 0x00110000) == 0x00110000) || (((CCM->SSICFGR & 0x00100000) == 0x00000000) && ((CCM->CCR & 0x0300) == 0x0100)))
        {
            xip_state = 1;
        }
        else
        {
            xip_state = 0;
        }
    }
    else if (ssi_id == 2)
    {
        // SSI2, 待修改
        if (((CCM->SSICFGR & 0x00220000) == 0x00220000) || (((CCM->SSICFGR & 0x00200000) == 0x00000000) && ((CCM->CCR & 0x0300) == 0x0200)))
        {
            xip_state = 1;
        }
        else
        {
            xip_state = 0;
        }
    }
    else if (ssi_id == 3)
    {
        // SSI3, 待修改
        if (((CCM->SSICFGR & 0x00440000) == 0x00440000) || (((CCM->SSICFGR & 0x00400000) == 0x00000000) && ((CCM->CCR & 0x0300) == 0x0300)))
        {
            xip_state = 1;
        }
        else
        {
            xip_state = 0;
        }
    }

    return xip_state;
}

/**
 *  @brief  SSI 模块XIP擦除操作函数
 *
 *  @param addr SSI 物理地址
 *  @return uint8_t 返回函数运行状态
 */
uint8_t drv_xip_flash_erase(uint32_t addr)
{
    ssi_para_t ssi_config[1];
    uint8_t ssi_id = drv_ssi_get_ssi_id(addr);

    ssi_config[0].ssi_id = ssi_id;
    ssi_config[0].sys_div = 2;
    ssi_config[0].quad_baud_rate = 2;
    if (g_core_clk / 1000000 == 500)
        ssi_config[0].rx_sample_delay = 0x00000002;
    else
        ssi_config[0].rx_sample_delay = 0x00010001;
    ssi_config[0].cmd = SECT_ERASE_CMD;
    ssi_config[0].isfouraddr = 0;
    ssi_config[0].dummyvalue = 0x04;
    ssi_config[0].std_baud_rate = 2;
    ssi_config[0].addr = addr & 0x03ffffff;
    ssi_config[0].delay = 100;
    ssi_config[0].is_qpi_mode = 0;
    drv_xipflash_erase(&ssi_config[0]);

    return 0;
}

/**
 *  @brief  SSI 模块XIP写入操作函数
 *
 *  @param addr SSI 物理地址
 *  @param p_buff 写入数据内容
 *  @param len 写入数据长度
 *  @return uint8_t 返回函数运行状态
 */
uint8_t drv_xip_flash_program(uint32_t addr, uint8_t *p_buff, uint32_t len)
{
    ssi_para_t ssi_config[1];
    uint8_t ssi_id = drv_ssi_get_ssi_id(addr);

    if (ssi_id == 1) // 0x10001000~0x101FFFFF
    {
        if ((addr >= 0x101FFFFF) || (addr < 0x10001000))
        {
            printf("Attention: You are writing info page.");
        }
    }
    ssi_config[0].ssi_id = ssi_id;
    ssi_config[0].sys_div = 2;
    ssi_config[0].quad_baud_rate = 2;
    if (g_core_clk / 1000000 == 500)
        ssi_config[0].rx_sample_delay = 0x00000002;
    else
        ssi_config[0].rx_sample_delay = 0x00010001;
    ssi_config[0].cmd = QUAD_PROG_CMD;
    ssi_config[0].isfouraddr = 0;
    ssi_config[0].dummyvalue = 0x04;
    ssi_config[0].std_baud_rate = 2;
    ssi_config[0].addr = addr & 0x03ffffff;
    ssi_config[0].program_mode = QUAD_PROGRAM;
    ssi_config[0].len = len;
    ssi_config[0].buf = (uint32_t)p_buff;
    ssi_config[0].delay = 100;
    ssi_config[0].is_qpi_mode = 0;
    drv_xipflash_program(&ssi_config[0]);

    return 0;
}

/**
 *  @brief  SSI 模块获取标志SR状态函数
 *
 *  @param p_ssi SSI 初始化结构体
 *  @param flag_index SSI SR 标志索引
 *  @param pflag 标志状态输出
 *  @return status_t 返回函数运行状态
 */
status_t drv_ssi_get_flag(reg_ssi_t *p_ssi, ssi_flag_index_t flag_index, uint8_t *pflag)
{

    if ((flag_index >= SSI_FLAG_INDEX_BUSY) && (flag_index <= SSI_FLAG_INDEX_RFF))
    {
        if (_ssi_sr_get(p_ssi) & flag_index)
        {
            *pflag = SSI_FLAG_1;
        }
        else
        {
            *pflag = SSI_FLAG_0;
        }
    }
    else
    {
        return (STATUS_ERROR);
    }

    return (STATUS_OK);
}

/**
 * @brief SSI 模块设置发送使能axidma函数
 * @param p_ssi SSI 初始化结构体
 */
void drv_ssitx_set_axidmaen(reg_ssi_t *p_ssi)
{
    _ssi_tdma_en_set(p_ssi, 0x1);
}

/**
 * @brief SSI 模块设置接收使能axidma函数
 * @param p_ssi SSI 初始化结构体
 */
void drv_ssirx_set_axidmaen(reg_ssi_t *p_ssi)
{
    _ssi_rdma_en_set(p_ssi, 0x1);
}

/**
 *  @brief  SSI 模块状态标志flag超时等待函数
 *
 *  @param p_ssi  SSI 初始化结构体
 *  @param index 指定 SSI 状态
 *  @param status 标志状态
 *  @param timeout 超时时间
 *  @return status_t 返回函数运行状态
 */
status_t drv_ssi_wait_flag_timeout(reg_ssi_t *p_ssi, ssi_flag_index_t index, uint8_t status, uint32_t timeout)
{
    uint8_t tmp_flag = SSI_FLAG_0;

    if (timeout == 0)
    {
        drv_ssi_get_flag(p_ssi, index, &tmp_flag);
        if (tmp_flag != status)
        {
            return (STATUS_TIMEOUT);
        }
    }
    else
    {
        while (timeout)
        {
            drv_ssi_get_flag(p_ssi, index, &tmp_flag);
            if (tmp_flag != status)
            {
                break;
            }

            timeout--;
            if (timeout == 0)
            {
                return (STATUS_TIMEOUT);
            }
        }
    }

    return STATUS_OK;
}

/**
 * @brief SSI 获取状态函数
 *
 * @param p_ssi SSI数据结构体
 * @param cmd 命令
 * @return UINT8
 */
uint8_t drv_ssi_get_status(reg_ssi_t *p_ssi, uint8_t cmd)
{
    volatile unsigned char retVal;
    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_LOW);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_LOW);
    }
    p_ssi->DR = cmd;
    p_ssi->DR = DUMMY_BYTE;
    __asm("nop");
    __asm("nop");
    while ((p_ssi->SR & SR_TFE) != SR_TFE)
        ;
    while (p_ssi->SR & SR_BUSY)
        ;
    while (p_ssi->SR & SR_RFNE)
    {
        retVal = p_ssi->DR;
    }
    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_HIGH);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_HIGH);
    }
    return retVal;
}

/**
 *  @brief  SSI 模块结构体数据初始化函数
 *
 *  @param pinit SSI 结构体数据
 */
void drv_ssi_struct_init(ssi_init_t *pinit)
{
    pinit->format = FORMAT_STD_MODE;
    pinit->dfs = DFS_08_BIT;
    pinit->frf = FRF_SPI;
    pinit->scph = SCPH_START_BIT;
    pinit->scpol = SCPOL_INACTIVE_LOW;
    pinit->tmod = TMOD_TX_AND_RX;
    pinit->srl = SRL_NORMAL_MODE;
    pinit->sste = TOGGLE_DISABLE;
    pinit->cfs = CFS_01_BIT;
    pinit->ndf = 0;
    pinit->ssi_baud_rate_prescaler = 0x20;
    pinit->transfer_start_fifo_level = 0;
    pinit->transmit_fifo_threshold = 0;
    pinit->receive_fifo_threshold = 0;
    pinit->trans_type = TT0;
    pinit->address_length = ADDR_L0;
    pinit->instruction_length = INST_L0;
    pinit->wait_cycles = 0x11;
    pinit->clk_stretch_en = CLK_STRETCH_DISABLE;
}

/**
 *  @brief  SSI 模块恢复为默认值函数
 *
 *  @param p_ssi SSI 初始化结构体
 *  @return status_t 返回函数运行状态
 */
status_t drv_ssi_deinit(reg_ssi_t *p_ssi)
{
    // CPM中复位模块
    if (p_ssi == SSI1)
    {
        drv_cpm_module_reset(SSI4_MODULE);
    }
    else if (p_ssi == SSI2)
    {
        drv_cpm_module_reset(SSI5_MODULE);
    }
    else if (p_ssi == SSI3)
    {
        drv_cpm_module_reset(SSI6_MODULE);
    }
    else
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/**
 *  @brief  SSI 模块使能或禁能函数
 *
 *  @param p_ssi SSI 初始化结构体
 *  @param state 使能或禁能
 */
void drv_ssi_cmd(reg_ssi_t *p_ssi, ssi_en_dis_t state)
{
    _ssi_enr_set(p_ssi, state);
}

/**
 *  @brief  SSI 模块初始化函数
 *
 *  @param p_ssi SSI 初始化结构体
 *  @param pinit SSI 数据结构体
 *  @param timeout 超时时间
 *  @return status_t 返回函数运行状态
 */
status_t drv_ssi_initt(reg_ssi_t *p_ssi, ssi_init_t *pinit, uint32_t timeout)
{
    status_t tmp_flag = STATUS_ERROR;
    flagstatus_t flag = RESET;
    uint8_t status;

    tmp_flag = drv_ssi_wait_flag_timeout(p_ssi, SSI_FLAG_INDEX_BUSY, SET, timeout);
    if (tmp_flag != STATUS_OK)
    {
        return tmp_flag;
    }
    drv_ssi_cmd(p_ssi, SSI_DIS);
    p_ssi->CTRLR0 = (pinit->dfs << 0) | (pinit->frf << 6) | (pinit->scph << 8) | (pinit->scpol << 9) | (pinit->tmod << 10) | (pinit->srl << 13) | (pinit->sste << 14) | (pinit->cfs << 16) | (pinit->format << 22);
    p_ssi->CTRLR1 = pinit->ndf;
    p_ssi->BAUDR = pinit->ssi_baud_rate_prescaler;
    p_ssi->TXFTLR = (pinit->transfer_start_fifo_level << 16) | (pinit->transmit_fifo_threshold);
    p_ssi->RXFTLR = pinit->receive_fifo_threshold;
    p_ssi->IMR = 0;
    p_ssi->SPICTRLR0 = (pinit->trans_type << 0) | (pinit->address_length << 2) | (pinit->instruction_length << 8) | (pinit->wait_cycles << 11) | (pinit->clk_stretch_en << 30);
    p_ssi->RXSDR = pinit->rx_sample_delay;
    drv_ssi_cmd(p_ssi, SSI_EN);
    return (STATUS_OK);
}
/**
 * @brief SSI 单线模式初始化函数
 *
 * @param SSIReg SSI数据结构体
 */

void drv_ssi_standard_init(reg_ssi_t **SSIReg)
{
    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->CTRLR1 = 0x00;
    (*SSIReg)->CTRLR0 = 0x07;
    (*SSIReg)->BAUDR = 0x02;
    (*SSIReg)->TXFTLR = 0x00;
    (*SSIReg)->RXFTLR = 0x00;
    (*SSIReg)->SPICTRLR0 = 0x8000;
    (*SSIReg)->IMR = 0x00;
    (*SSIReg)->RXSDR = 0x00000001;
    (*SSIReg)->SSIENR = 0x01;
}

void drv_ssi_quad_init(reg_ssi_t *SSIx, uint8_t read, uint16_t num, uint8_t waitCycles)
{
    while (SSIx->SR & SR_BUSY)
        ;
    SSIx->SSIENR = 0x00;
    SSIx->CTRLR1 = num - 1;
    if (read)
    {
        SSIx->CTRLR0 = SPI_QUAD | RX_ONLY | DFS_08_BIT;
    }
    else
    {
        SSIx->CTRLR0 = SPI_QUAD | TX_ONLY | DFS_08_BIT;
    }
    SSIx->BAUDR = QUAD_BAUDR;
    if (read)
    {
        SSIx->TXFTLR = TXFTHR(1) | TFT(0);
        SSIx->RXFTLR = RFT(7);
    }
    else
    {
        SSIx->TXFTLR = TXFTHR(2) | TFT(0);
        SSIx->RXFTLR = RFT(0);
        SSIx->DMATDLR = TRANS_LEVEL(2);
    }
    SSIx->RXSDR = RSD(1); // default
    SSIx->SPICTRLR0 = CLK_STRETCH | WAIT_CYCLES(waitCycles) | INST_L8_BITS | ADDR_L(6);
    SSIx->IMR = DISABLE;
    SSIx->SSIENR = 0x01;
}
/**
 * @brief SSI xip模式使能函数
 *
 * @param SSIReg SSI数据结构体
 */
void drv_ssi_xip_enable(reg_ssi_t **SSIReg)
{
    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->XIPIIR = 0xeb;
    (*SSIReg)->XIPWIR = 0x0c;
    (*SSIReg)->XIPMBR = 0x00;
    (*SSIReg)->BAUDR = 0x02;
    (*SSIReg)->XIPCR = 0x28c09466;
    (*SSIReg)->CTRLR0 = 0x0080001f;
    (*SSIReg)->RXSDR = 0x00010001;
    (*SSIReg)->SSIENR = 0x01;
}
/**
 * @brief SSI XIP初始化函数
 *
 * @param ssi_id SSI 端口号
 */
void drv_ssi_xip_init(uint8_t ssi_id)
{
    reg_ssi_t *SSIReg;
    unsigned char temp;
    unsigned char reg;
    if (ssi_id == SSIID1)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 16) | (1 << 20))) | (1 << 16);
        SSIReg = SSI1;
    }
    else if (ssi_id == SSIID2)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 17) | (1 << 21))) | (1 << 17);
        SSIReg = SSI2;
    }
    else if (ssi_id == SSIID3)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 18) | (1 << 22))) | (1 << 18);
        SSIReg = SSI3;
    }
    drv_ssi_standard_init(&SSIReg);
    drv_ssi_xip_enable(&SSIReg);
    if (ssi_id == SSIID1)
    {
        CCM->SSICFGR |= ((1 << 16) | (1 << 20));
    }
    if (ssi_id == SSIID2)
    {
        CCM->SSICFGR |= ((1 << 17) | (1 << 21));
    }
    if (ssi_id == SSIID3)
    {
        CCM->SSICFGR |= ((1 << 18) | (1 << 22));
    }
}
/**
 * @brief SSI 打开XIP函数
 *
 * @param ssi_id SSI 端口号
 */
void drv_open_xip(uint8_t ssi_id)
{
    if (ssi_id == SSIID1)
    {
        CCM->SSICFGR |= ((1 << 16) | (1 << 20));
    }
    if (ssi_id == SSIID2)
    {
        CCM->SSICFGR |= ((1 << 17) | (1 << 21));
    }
    if (ssi_id == SSIID3)
    {
        CCM->SSICFGR |= ((1 << 18) | (1 << 22));
    }
}

/**
 * @brief SSI 关闭XIP 函数
 *
 * @param ssi_id SSI 端口号
 */
void drv_close_xip(uint8_t ssi_id)
{
    if (ssi_id == SSIID1)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 16) | (1 << 20))) | (1 << 16);
    }
    else if (ssi_id == SSIID2)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 17) | (1 << 21))) | (1 << 17);
    }
    else if (ssi_id == SSIID3)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 18) | (1 << 22))) | (1 << 18);
    }
}

/**
 *  @brief  SSI 模块Flash擦除操作函数
 *
 *  @param addr SSI 物理地址
 */
void drv_ssi_flash_erase(reg_ssi_t *p_ssi, uint32_t addr)
{

    uint8_t status;
    uint8_t temp;
    drv_ssi_standard_init(&p_ssi);
    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_LOW);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_LOW);
    }
    drv_ssi_eflash_write_enable(p_ssi, 0xffffff);
    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_HIGH);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_HIGH);
    }

    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_LOW);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_LOW);
    }
    p_ssi->DR = SECT_ERASE_CMD;
    p_ssi->DR = (addr >> 16) & 0xff;
    p_ssi->DR = (addr >> 8) & 0xff;
    p_ssi->DR = (addr >> 0) & 0xff;
    __asm("nop");
    __asm("nop");
    while ((p_ssi->SR & SR_TFE) != SR_TFE)
        ;
    while (p_ssi->SR & SR_BUSY)
        ;
    while (p_ssi->SR & SR_RFNE)
    {
        temp = p_ssi->DR;
    }
    if (p_ssi == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_HIGH);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_HIGH);
    }
    do
    {
        status = drv_ssi_get_status(p_ssi, GET_SAT1_CMD);
    } while (status & 0x01);
}

/**
 * @brief SSI 模块编程函数
 *
 * @param addr SSI 物理地址
 * @param buf  待写入数据buffer
 * @param num 待写入数据长度
 */

uint8_t drv_ssi_flash_program(uint32_t addr, uint8_t *buf, uint32_t num)
{
    uint8_t status;
    uint8_t temp;
    reg_ssi_t *SSIReg;

    if ((addr >= SSI1_LOW_ADDR) && (addr < SSI1_HIGH_ADDR))
    {
        SSIReg = SSI1;
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_LOW);
    }
    else if ((addr >= SSI2_LOW_ADDR) && (addr < SSI2_HIGH_ADDR))
    {
        SSIReg = SSI2;
    }
    else if ((addr >= SSI3_LOW_ADDR) && (addr < SSI3_HIGH_ADDR))
    {
        SSIReg = SSI3;
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_LOW);
    }
    drv_ssi_standard_init(&SSIReg);
    drv_ssi_eflash_write_enable(SSIReg, 0xffffff);

    if (SSIReg == SSI1)
    {
        drv_eport_writepinslevel(EPORT2, EPORT2_PIN0, GPIO_HIGH);
        SwitchPinFunction(SPI4_CS_FUN, DEFAULT_FUN);
    }
    else
    {
        drv_eport_writepinslevel(EPORT4, EPORT4_PIN0, GPIO_HIGH);
        SwitchPinFunction(SPI6_CS_FUN, DEFAULT_FUN);
    }

    drv_ssi_quad_init(SSIReg, 0, num, 8);
    SSIReg->DR = QUAD_PROG_CMD;
    SSIReg->DR = addr;
    while (num > 0)
    {
        if (SSIReg->SR & SR_TFNF)
        {
            SSIReg->DR = *buf;
            buf++;
            num--;
        }

        if (SSIReg->SR & SR_RFNE)
        {
            temp = SSIReg->DR;
        }
    }

    while (SSIReg->SR & SR_BUSY)
        ;
    while (SSIReg->SR & SR_RFNE)
    {
        temp = SSIReg->DR;
    }

    drv_ssi_standard_init(&SSIReg);
    do
    {
        status = drv_ssi_get_status(SSIReg, GET_SAT1_CMD);
    } while (status & 0x01);
		return 0;
}

/**
 * @brief SSI 模块读取函数
 *
 * @param addr SSI 物理地址
 * @param buf  待写入数据buffer
 * @param num 待写入数据长度
 */
void drv_ssi_flash_read(reg_ssi_t *p_ssi, uint32_t addr, uint8_t *buf, int num)
{
    volatile uint8_t temp;

    int i = 0;
    uint8_t status;
    if (p_ssi == SSI1)
    {

        SwitchPinFunction(SPI4_CS_FUN, DEFAULT_FUN);
    }
    else
    {
        SwitchPinFunction(SPI6_CS_FUN, DEFAULT_FUN);
    }
    drv_ssi_quad_init(p_ssi, 1, num, 8);

    p_ssi->DR = QUAD_READ_CMD;
    p_ssi->DR = addr;

    __asm("nop");
    __asm("nop");

    while ((p_ssi->SR & SR_TFE) != SR_TFE)
    {
        ;
    }

    while (((num > 0) && (p_ssi->SR & SR_BUSY)) || (p_ssi->SR & SR_RFNE))
    {
        if (p_ssi->SR & SR_RFNE)
        {
            *(buf + i) = p_ssi->DR;
            i++;
            num--;
        }
    }
}