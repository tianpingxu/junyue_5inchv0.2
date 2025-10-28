/**
 * @file sdio_drv.c
 * @author Product Application Department
 * @brief  SDIO 模块驱动层
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件定义
#include "sdio_drv.h"

// 函数定义

/**
 * @brief 检查SDIO硬件配置
 *
 * @details 读取SDMMC_HCON寄存器并检查卡类型是否为SD/MMC类型(1)
 */
void drv_sdio_hcon(void)
{
    sdio_hcon_t hcon_reg;
    *(uint32_t *)&hcon_reg = R32(SDMMC_HCON);
    if (hcon_reg.card_type != 1)
    {
        __asm("bkpt 0");
    }
}

/**
 * @brief 轮询SDIO状态标志
 *
 * @param flag_s 需要轮询的状态标志位
 * @return uint8_t  0:成功 1:超时
 *
 * @details 轮询SDMMC_RINTSTS寄存器直到指定标志位置位或超时
 */
uint8_t drv_sdio_pollstatus(uint32_t flag_s)
{
    uint32_t status = 0;
    uint32_t poll_cnt = 0;

    status = R32(SDMMC_RINTSTS);
    while ((status & flag_s) != flag_s)
    {
        status = R32(SDMMC_RINTSTS);
        if (flag_s == SDMMC_INT_CMD_DONE) // only CMDDONE is expected
        {
            poll_cnt++;
            if (poll_cnt == RESP_TIMEOUT)
            { // software detect Response timeout
                __asm("bkpt 0");
                return 1;
            }
        }
    }
    // clear
    W32(SDMMC_RINTSTS, flag_s);
    return 0;
}

/**
 * @brief 等待SDIO命令启动完成
 *
 * @details 轮询SDMMC_CMD寄存器的START位直到清零，表示命令已被接受
 */
void drv_sdio_startcmd(void)
{
    uint32_t status = 0;

    status = R32(SDMMC_CMD);
    while (status & SDMMC_CMD_START)
    {
        status = R32(SDMMC_CMD); // Hardware
    }
}

/**
 * @brief 设置SDIO时钟
 *
 * @param slot_num 卡槽号
 * @param div_val 时钟分频值
 *
 * @details 配置SDIO控制器时钟，包括禁用时钟、设置分频值和重新启用时钟
 */
void drv_sdio_setclk(uint32_t slot_num, uint32_t div_val)
{
    /*  P213
     * Before disabling the clocks, ensure that the card is not busy due to any previous data command.
     * To determine this, check for 0 in bit 9 of the STATUS register.
     */
    //    while(R32(SDMMC_STATUS)&BIT_X(9));

    /* disable clock to CIU */
    W32(SDMMC_CLKENA, 0);
    /* inform CIU: P220 */
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT);
    drv_sdio_startcmd();

    /* set clock to desired speed */
    W32(SDMMC_CLKSRC, 0);
    W32(SDMMC_CLKDIV, (div_val << 0));
    /* inform CIU */
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT);
    drv_sdio_startcmd();

    /* enable clock */
    W32(SDMMC_CLKENA, (slot_num << SDMMC_CLKEN_LOW_PWR) | (slot_num << SDMMC_CLKEN_ENABLE));
    /* inform CIU */                                                              // P219+P162
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT); // do not use:(EMMC_SLOT0 <<16)/(SD_SLOT1 <<16)
    drv_sdio_startcmd();
}

/**
 * @brief 切换SDIO时钟状态
 *
 * @param flag 0:停止时钟 1:启用时钟
 *
 * @details 控制SDIO时钟的开启和关闭，并通知CIU
 */
void drv_sdio_switchclk(uint8_t flag)
{
    if (flag == 0) // stop clock
    {
        /* disable clock to CIU */
        W32(SDMMC_CLKENA, 0);
        /* inform CIU: P220 */
        W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_VOLT_SWITCH);
        drv_sdio_startcmd();
    }
    else
    {
        /* enable clock */
        //      W32(SDMMC_CLKENA, ((1<<SD_SLOT1) <<SDMMC_CLKEN_ENABLE) | (1<<SD_SLOT1) << SDMMC_CLKEN_LOW_PWR);
        W32(SDMMC_CLKENA, (1 << SD_SLOT1) << SDMMC_CLKEN_ENABLE);
        /* inform CIU */                                                                                      // P219+P162
        W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_VOLT_SWITCH); // do not use:(EMMC_SLOT0 <<16)/(SD_SLOT1 <<16)
        drv_sdio_startcmd();
    }
}

/**
 * @brief 复位SDIO控制器
 *
 * @return uint8_t  0:复位成功 1:复位超时
 *
 * @details 同时复位控制器、FIFO和DMA，等待复位完成或超时
 */
uint8_t drv_sdio_reset(void)
{
    uint32_t ctrl, timeout = 1000;

    W32(SDMMC_CTRL, SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET);
    /* wait till resets clear */
    do
    {
        ctrl = R32(SDMMC_CTRL);
        if (!(ctrl & (SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET)))
            return 0;
    } while (timeout--);

    return 1;
}

/**
 * @brief SDIO中断处理函数
 *
 * @details 读取并打印SDMMC_RINTSTS寄存器的值
 */
void drv_sdio_irqhandler()
{
    uint32_t reg;

    reg = R32(SDMMC_RINTSTS);
}

/**
 * @brief 初始化SDIO控制器
 *
 * @details 配置中断、超时、数据宽度、去抖动时间和FIFO阈值等参数
 */
void drv_sdio_init(void)
{
    uint32_t fifo_size;
    uint32_t reg;

    /* Clear(Wr 1) the interrupts for the host controller */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);
    /* 0=disable all mmc interrupt first */
    W32(SDMMC_INTMASK, 0);
    /* Put in max timeout */
    W32(SDMMC_TMOUT, 0xFFFFFFFF);
    /* .py:  0:1-bit mode */
    W32(SDMMC_CTYPE, SDMMC_CTYPE_1BIT);
    W32(SDMMC_DEBNCE, 0xffffff);
    // drive(write timing), //sample(read timing)  -->0,1,2,3
    W32(SDMMC_UHS_EXT, 1 << 23 | 2 << 16);

    //  W32(SDMMC_ENABLE_SHIFT, 0x01);

#if 0
    fifo_size = R32(SDMMC_FIFOTH);
    fifo_size = 1 + ((fifo_size >> 16) & 0xfff);
#else
    fifo_size = FIFO_DEPTH; // Recommended: MSize = 8, TX_WMark = 8, RX_WMark = 7
#endif
    W32(SDMMC_FIFOTH, ((0x2 << 28) | ((fifo_size / 2 - 1) << 16) | ((fifo_size / 2) << 0)));

    //  MY_NVIC_Init(3, 3, SD_EMMCn, 2);
    //  R32(SDMMC_CTRL) |= (1 << 4);    //global int en
    //  R32(SDMMC_INTMASK) |= (0xFFFF);    //mask int en

    //  reg = R32(SDMMC_CDETECT);
    //  printf("SDMMC_CDETECT = 0x%08x\r\n", reg);

    //  reg = R32(SDMMC_RINTSTS);
    //  printf("SDMMC_RINTSTS = 0x%08x\r\n", reg);
}

/**
 * @brief 检测SD卡是否插入
 *
 * @return uint8_t  0:检测到卡 1:未检测到卡
 *
 * @details 检查卡是否存在，如果存在则进行上电和电压配置
 */
uint8_t drv_sdio_carddetect(void)
{
    uint32_t card_det;

    card_det = R32(SDMMC_CDETECT);
    if ((card_det & (1 << SD_SLOT1)) == SDMMC_CDETECT_CARD_PRESENT) // pin7=DETECT_N[0]=GND
    {
        drv_sdio_powerup(1 << SD_SLOT1, 1); // pin086=CARD_POWER_EN[0]/#EN1---eMMC  (VDDQ)
        delay(0x1000);
        drv_sdio_cardvolt(1 << SD_SLOT1, 0); // 3.3Vdd
        // return drv_sdio_pollstatus(SDMMC_INT_CD);
        return 0;
    }
    return 1;
}

//-----------------------power--------------------------------------------------
/*
 * FPGA: U10=>FPGA_gpio4=>OE   /J10.008=CARD_BIU_VOLT[1]= #FPGA_GPIO4
 *   P207/Output Decoded Voltage
 */
/**
 * @brief 设置SD卡接口电压
 *
 * @param slot_num 卡槽号
 * @param flag 0:3.3V 1:1.8V
 *
 * @details 配置SD卡接口的工作电压
 */
void drv_sdio_cardvolt(uint32_t slot_num, uint8_t flag)
{
    uint32_t uhs_1_reg;

    uhs_1_reg = R32(SDMMC_UHS_REG);
    if (flag == 0) // 3.3 vdd
    {
        uhs_1_reg &= ~slot_num;
    }
    else // 1.8Vdd
    {
        uhs_1_reg |= slot_num;
    }
    W32(SDMMC_UHS_REG, uhs_1_reg); // P185: 1 – Buffers supplied with 1.8V Vdd
}

/**
 * @brief 控制SD卡电源
 *
 * @param slot_num 卡槽号
 * @param flag 0:关闭电源 1:开启电源
 *
 * @details 控制指定卡槽的电源状态
 */
void drv_sdio_powerup(uint32_t slot_num, uint8_t flag)
{
    uint32_t power;

    power = R32(SDMMC_PWREN);
    if (flag == 0) // off
    {
        power &= ~slot_num;
    }
    else // on
    {
        power |= slot_num;
    }
    W32(SDMMC_PWREN, power);
}

/**
 * @brief 获取SD卡电源状态
 *
 * @param slot_num 卡槽号
 * @return uint8_t  0:电源关闭 1:电源开启
 *
 * @details 读取指定卡槽的电源状态
 */
uint8_t drv_sdio_getpowerstate(uint32_t slot_num)
{
    uint32_t power;

    power = R32(SDMMC_PWREN) & slot_num;
    return (power == 0) ? 0 : 1;
}

/**
 * @brief 控制内部DMA
 *
 * @param flag 1:启用DMA 0:禁用DMA
 *
 * @details 配置SDIO控制器的内部DMA功能
 */
void drv_sdio_internaldmacctrl(uint8_t flag)
{
    uint32_t data;

    data = R32(SDMMC_CTRL);
    if (flag == 1) // enable
    {
        data |= SDMMC_CTRL_USE_IDMAC;
        W32(SDMMC_CTRL, data);
        W32(SDMMC_BMOD, (1 << 7) | (1 << 1));
    }
    else // disable
    {
        data &= ~SDMMC_CTRL_USE_IDMAC;
        W32(SDMMC_CTRL, data);
        data = SDMMC_BMOD;
        data &= ~(1 << 7);
        W32(SDMMC_BMOD, data);
    }
}

/**
 * @brief 配置DMA描述符
 *
 * @param dbaddr DMA描述符基地址
 * @param baddr 数据缓冲区地址
 * @param dscnt 描述符数量
 *
 * @details 初始化DMA描述符链表，配置数据传输参数
 */
void drv_sdio_configdesc(uint32_t dbaddr, uint32_t baddr, uint16_t dscnt)
{
    uint16_t idx;
    uint32_t temp_baddr, start_addr = dbaddr;

#if 1
    for (idx = 0; idx < dscnt * 8; idx++)
    {
        W32(start_addr + idx * 4, 0);
    }
    for (idx = 0; idx < dscnt; idx++)
    {
        temp_baddr = start_addr + idx * 32; // 16bytes for 32-bit dma haddr, 32bytes for 64-bit dma haddr
        if (idx == (dscnt - 1))
            W32(temp_baddr, (OWN | FS | SD_CH | LD));
        else
            W32(temp_baddr, (OWN | FS | SD_CH));
        temp_baddr = start_addr + idx * 32 + 8;
        W32(temp_baddr, BLOCK_SIZE);
        temp_baddr = start_addr + idx * 32 + 16;
        W32(temp_baddr, baddr);
        W32(temp_baddr + 4, dbaddr + 0x50); // high 32bit, no used in this version
        temp_baddr = start_addr + idx * 32 + 24;
        W32(temp_baddr, (start_addr + 32 * (idx + 1)));
        W32(temp_baddr + 4, dbaddr + 0x50); // high 32bit, no used in this version
        baddr += BLOCK_SIZE;
    }
#else
    for (idx = 0; idx < dscnt * 4; idx++)
    {
        W32(start_addr + idx * 4, 0);
    }
    for (idx = 0; idx < dscnt; idx++)
    {
        temp_baddr = start_addr + idx * 16; // 16bytes for 32-bit dma haddr, 32bytes for 64-bit dma haddr
        if (idx == (dscnt - 1))
            W32(temp_baddr, (OWN | FS | SD_CH | LD));
        else
            W32(temp_baddr, (OWN | FS | SD_CH));
        temp_baddr = start_addr + idx * 16 + 4;
        W32(temp_baddr, BLOCK_SIZE);
        temp_baddr = start_addr + idx * 16 + 8;
        W32(temp_baddr, baddr);
        temp_baddr = start_addr + idx * 16 + 12;
        W32(temp_baddr, (start_addr + 16 * (idx + 1)));
        baddr += BLOCK_SIZE;
    }
#endif
}

/**
 * @brief 发送CMD0命令(GO_IDLE_STATE)
 *
 * @param arg 命令参数
 *
 * @details 发送复位命令，使卡进入空闲状态
 */
void drv_sdio_cmd0sdtsk(uint32_t arg)
{
    W32(SDMMC_CMDARG, arg);
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_INIT | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(0));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD1命令(SEND_OP_COND)
 *
 * @param arg 命令参数，包含操作条件寄存器值
 *
 * @details 发送操作条件命令，获取卡的工作电压范围
 */
void drv_sdio_cmd1sdtsk(uint32_t arg)
{
    W32(SDMMC_CMDARG, arg);
    // 4.5-P120: R3 has no CRC. +Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(1));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD8命令(SEND_IF_COND)
 *
 * @param arg 命令参数，包含电压范围和校验模式
 *
 * @details 发送接口条件命令，检查卡是否支持指定的电压范围
 */
void drv_sdio_cmd8sdtsk(uint32_t arg)
{
    W32(SDMMC_CMDARG, arg);
    // R7 +Res index=001000'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT //|BIT(29)
                       | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(8));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD11命令(VOLTAGE_SWITCH)
 *
 * @details 发送电压切换命令，将卡接口电压从3.3V切换到1.8V
 */
void drv_sdio_cmd11sdtsk(void)
{
    W32(SDMMC_CMDARG, 0);
    // R1.+Res CMD index.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_VOLT_SWITCH | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(11));
    drv_sdio_pollstatus(SDMMC_INT_VOLT_SWITCH);
}

/**
 * @brief 发送CMD55命令(APP_CMD)
 *
 * @param rca 相对卡地址
 *
 * @details 发送应用特定命令前缀，表示下一个命令是应用特定命令
 */
void drv_sdio_cmd55sdtsk(uint32_t rca)
{
    W32(SDMMC_CMDARG, (rca << 16));
    // R1.+Res CMD index.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(55));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送ACMD41命令(SD_SEND_OP_COND)
 *
 * @param arg 命令参数，包含操作条件寄存器值
 *
 * @details 发送SD卡特定的操作条件命令，获取卡的工作电压范围和容量信息
 */
void drv_sdio_acmd41sdtsk(uint32_t arg)
{
    drv_sdio_cmd55sdtsk(0x0000); // CMD55 in idle_state shall be the card’s default RCA=0x0000.

    W32(SDMMC_CMDARG, arg); // the host should set HCS to 0 if the card returns no response to CMD8.
    // R3 has no CRC. +Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(41));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD2命令(ALL_SEND_CID)
 *
 * @details 请求卡发送CID(Card Identification)寄存器内容
 */
void drv_sdio_cmd2sdtsk(void)
{
    W32(SDMMC_CMDARG, 0);
    // 136 bits R2 has CRC. + Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_LONG | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(2));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD3命令(SEND_RELATIVE_ADDR)
 *
 * @param rca 相对卡地址
 *
 * @details 请求卡发布一个新的相对地址(RCA)
 */
void drv_sdio_cmd3sdtsk(uint32_t rca)
{
    W32(SDMMC_CMDARG, (rca << 16));
    // eMMC: R1.+Res CMD index.
    // SD: R6.+Res CMD index. + new RCA+ status:
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(3));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD9命令(SEND_CSD)
 *
 * @param rca 相对卡地址
 *
 * @details 请求卡发送CSD(Card Specific Data)寄存器内容
 */
void drv_sdio_cmd9sdtsk(uint32_t rca)
{
    W32(SDMMC_CMDARG, (rca << 16));
    // 136 bits R2 has CRC. + Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_LONG | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(9));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD7命令(SELECT/DESELECT_CARD)
 *
 * @param rca 相对卡地址
 *
 * @details 选择或取消选择指定的卡
 */
void drv_sdio_cmd7sdtsk(uint32_t rca)
{
    W32(SDMMC_CMDARG, (rca << 16));
    // R1/R1b.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(7));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD13命令(SEND_STATUS)
 *
 * @param rca 相对卡地址
 *
 * @details 请求卡发送其状态寄存器内容
 */
void drv_sdio_cmd13sdtsk(uint32_t rca)
{
    W32(SDMMC_CMDARG, (rca << 16));
    // R1.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(13));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送ACMD42命令(SET_CLR_CARD_DETECT)
 *
 * @param rca 相对卡地址
 * @param set_cd 卡检测设置，0:断开 1:连接
 *
 * @details 设置或清除卡的内部检测电阻
 */
void drv_sdio_acmd42sdtsk(uint32_t rca, uint32_t set_cd)
{
    drv_sdio_cmd55sdtsk(rca);

    W32(SDMMC_CMDARG, set_cd);
    // R1.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(42));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送ACMD51命令(SEND_SCR)
 *
 * @param rca 相对卡地址
 * @param byte_num 读取的字节数
 *
 * @details 读取SD卡配置寄存器(SCR)内容
 */
void drv_sdio_acmd51sdtsk(uint32_t rca, uint32_t byte_num)
{
    drv_sdio_cmd55sdtsk(rca);

    W32(SDMMC_CMDARG, 0);
    W32(SDMMC_BLKSIZ, byte_num);
    W32(SDMMC_BYTCNT, byte_num);
    // R1.+data.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(51));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER);
}

/**
 * @brief 发送ACMD6命令(SD_SET_BUS_WIDTH)
 *
 * @param rca 相对卡地址
 *
 * @details 设置SD卡数据总线宽度
 */
void drv_sdio_acmd6sdtsk(uint32_t rca)
{
    drv_sdio_cmd55sdtsk(rca); // CMD55 in idle_state shall be the card’s default RCA=0x0000.

    W32(SDMMC_CMDARG, 0x02); // the host should set HCS to 0 if the card returns no response to CMD8.
    // R3 has no CRC. +Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(6));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD16命令(SET_BLOCKLEN)
 *
 * @param blocklen 块长度
 *
 * @details 设置数据块长度(字节)
 */
void drv_sdio_cmd16sdtsk(uint16_t blocklen)
{
    W32(SDMMC_CMDARG, blocklen); // the host should set HCS to 0 if the card returns no response to CMD8.
    // R3 has no CRC. +Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(16));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD6命令(SWITCH_FUNC)
 *
 * @param arg 命令参数
 * @param byte_num 读取的字节数
 *
 * @details 切换或检查卡的功能，用于高速模式切换
 */
void drv_sdio_cmd6sdtsk(uint32_t arg, uint32_t byte_num)
{
    W32(SDMMC_CMDARG, arg);
    W32(SDMMC_BLKSIZ, byte_num);
    W32(SDMMC_BYTCNT, byte_num);
    // R1.+data.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(6));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER);
}

/**
 * @brief 发送CMD17命令(READ_SINGLE_BLOCK)
 *
 * @param arg 命令参数，包含读取地址
 * @param byte_num 读取的字节数
 *
 * @details 从卡中读取单个数据块
 */
void drv_sdio_cmd17sdtsk(uint32_t arg, uint32_t byte_num)
{
    W32(SDMMC_BYTCNT, byte_num);
    W32(SDMMC_BLKSIZ, BLOCK_SIZE);
    W32(SDMMC_CARDTHRCTL, (CARD_THRESHOLD << 16) | 0x01);
#ifdef USE_INTERNAL_DMAC
    W32(SDMMC_DBADDRL, DESCRIPTION_ADDR);
    W32(SDMMC_DBADDRU, DESCRIPTION_ADDR + 0x50); // high 32bit, no used in this version
#endif
    W32(SDMMC_CMDARG, arg);
    // R1.+data.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(17));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD18命令(READ_MULTIPLE_BLOCK)
 *
 * @param arg 命令参数，包含起始读取地址
 * @param byte_num 读取的总字节数
 *
 * @details 从卡中连续读取多个数据块
 */
void drv_sdio_cmd18sdtsk(uint32_t arg, uint32_t byte_num)
{
#ifdef UNDEFINED_TRANS_NUM
    W32(SDMMC_BYTCNT, 0);
#else
    W32(SDMMC_BYTCNT, byte_num);
#endif
    W32(SDMMC_BLKSIZ, BLOCK_SIZE);
    W32(SDMMC_CARDTHRCTL, (CARD_THRESHOLD << 16) | 0x01);
#ifdef USE_INTERNAL_DMAC
    W32(SDMMC_DBADDRL, DESCRIPTION_ADDR);
    W32(SDMMC_DBADDRU, DESCRIPTION_ADDR + 0x50); // high 32bit, no used in this version
#endif
    W32(SDMMC_CMDARG, arg);
    // R1.+data.
#ifdef SEND_AUTO_STOP
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(18) | SDMMC_CMD_SEND_AUTO_STOP);
#else
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(18));
#endif
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD12命令(STOP_TRANSMISSION)
 *
 * @details 强制停止当前的数据传输
 */
void drv_sdio_cmd12sdtsk(void)
{
    W32(SDMMC_CMDARG, 0); // the host should set HCS to 0 if the card returns no response to CMD8.
    // R3 has no CRC. +Res index=111111'b
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_STOP | SDMMC_CMD_RESP_CRC | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(12));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD24命令(WRITE_BLOCK)
 *
 * @param arg 命令参数，包含写入地址
 * @param byte_num 写入的字节数
 *
 * @details 向卡中写入单个数据块
 */
void drv_sdio_cmd24sdtsk(uint32_t arg, uint32_t byte_num)
{
    W32(SDMMC_BYTCNT, byte_num);
    W32(SDMMC_BLKSIZ, BLOCK_SIZE);
    W32(SDMMC_CARDTHRCTL, (CARD_THRESHOLD << 16) | 0x04);
#ifdef USE_INTERNAL_DMAC
    W32(SDMMC_DBADDRL, DESCRIPTION_ADDR);
    W32(SDMMC_DBADDRU, DESCRIPTION_ADDR + 0x50); // high 32bit, no used in this version
#endif
    W32(SDMMC_CMDARG, arg);
    // R1.+data.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_DAT_WR | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(24));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief 发送CMD25命令(WRITE_MULTIPLE_BLOCK)
 *
 * @param arg 命令参数，包含起始写入地址
 * @param byte_num 写入的总字节数
 *
 * @details 向卡中连续写入多个数据块
 */
void drv_sdio_cmd25sdtsk(uint32_t arg, uint32_t byte_num)
{
#ifdef UNDEFINED_TRANS_NUM
    W32(SDMMC_BYTCNT, 0);
#else
    W32(SDMMC_BYTCNT, byte_num);
#endif
    W32(SDMMC_BLKSIZ, BLOCK_SIZE);
    W32(SDMMC_CARDTHRCTL, (CARD_THRESHOLD << 16) | 0x04);
#ifdef USE_INTERNAL_DMAC
    W32(SDMMC_DBADDRL, DESCRIPTION_ADDR);
    W32(SDMMC_DBADDRU, DESCRIPTION_ADDR + 0x50); // high 32bit, no used in this version
#endif
    W32(SDMMC_CMDARG, arg);
    // R1.+data.
    W32(SDMMC_CMD, SDMMC_CMD_START | SDMMC_CMD_USE_HOLD | SDMMC_CMD_RESP_EXP | SDMMC_CMD_PRV_DAT_WAIT | SDMMC_CMD_DAT_WR | SDMMC_CMD_RESP_CRC | SDMMC_CMD_DAT_EXP | (SD_SLOT1 << 16) | SDMMC_CMD_INDX(25));
    drv_sdio_pollstatus(SDMMC_INT_CMD_DONE);
}

/**
 * @brief sdmmc模块fifo，dma复位
 * 
 */
void drv_sdio_fifodmareset(void)
{
    uint32_t timeout=1000, ctrl;
    W32(SDMMC_CTRL, SDMMC_CTRL_FIFO_RESET|SDMMC_CTRL_DMA_RESET);
    do
    {
        ctrl = R32(SDMMC_CTRL);
        if (!(ctrl & (SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET)))
        {
            break;
        }
        
    } while (timeout--);
    
}

