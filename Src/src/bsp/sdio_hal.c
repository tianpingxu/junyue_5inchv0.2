/**
 * @file sdio_hal.c
 * @author Product Application Department
 * @brief SDIO模块硬件抽象层文件，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-04
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

 //头文件定义
#include "sdio_hal.h"
#include "uart_drv.h"
#include "ioctrl_hal.h"
#include "debug.h"

//全局变量定义
sdio_sd_cardinfo_t SDCardInfo;
static uint32_t  CSD_Tab[4], CID_Tab[4], RCA = 0;
static uint32_t  SCR[2], Switch_Func[16];
static uint32_t  CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0;
static uint8_t  start_write_block = 0;
static uint8_t isvoltagesw = 0;

// 函数定义
/**
 * @brief SDIO 模块枚举并初始化SD卡函数
 * 
 * @return sdio_sd_error_t 
 * 
 * @details 执行SD卡的完整初始化流程：
 *          1. 初始化SDIO主机控制器
 *          2. 获取卡信息
 *          3. 选择卡
 *          4. 配置总线宽度
 *          5. 读取SCR寄存器
 *          6. 根据卡类型切换工作模式
 */
sdio_sd_error_t hal_sd_enumcard(void)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status, response, count = 0;

    errorstatus = hal_sd_init();  
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

    errorstatus = hal_sd_getcardinfo(&SDCardInfo);
    errorstatus = hal_sd_selectdeselect(SDCardInfo.RCA);
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

    errorstatus = hal_sd_enwidebus();
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

    errorstatus = hal_sd_sendscr(SCR);
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }
    if(CardType == SDIO_HIGH_CAPACITY_SD_CARD_V3_0)
    {
        // TO DO.
        printf("Run V3.0\n");
        errorstatus = hal_sd_switchfunc_v3_0(Switch_Func);
        if (errorstatus != SD_OK)
        {
            errorstatus = SD_OK;
            printf("Failed to Run V3.0\n");
            printf("Switch to V2.0\n");

            drv_cpm_module_reset(SD_EMMC_HOST);

            ioctrl_sdhinit_t psdh;
            psdh.pue = PUE_PULL_EN;
            hal_ioctrl_sdhinit(&psdh);

            delayms(100);

            /* Assert Reset - active-low */
            if(drv_sdio_reset())
            {
                /* Reset timeout(wait for hw rest flag) */
                errorstatus = SD_ERROR;
                return(errorstatus);
            }

            drv_sdio_init();

            // while(drv_sdio_carddetect());

            drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_400kHz_DIV);
            /* CMD0: GO_IDLE_STATE -------------------------------------------------------*/
            /* No CMD response required */
            drv_sdio_cmd0sdtsk( CMD0ARG_GO_IDLE_STATE);

            delayms(100);
            /* CMD8: SEND_IF_COND --------------------------------------------------------*/
            /* Send CMD8 to verify SD card interface operating condition */
            /* Argument: - [31:12]: reserved(shall be set to '0')
                        - [11:8]: Supply voltage(VHS) 0x1 (Range: 2.7-3.6 V)
                        - [7:0]: Check pattern(recommended 0xAA) */
            /* CMD Response: R7 */
            while(response!=0x000001AA)
            {
                drv_sdio_cmd8sdtsk(0x000001AA);
                response = R32(SDMMC_RESP0);
                delay(10000);
            }
            
            if(response != 0x000001AA)
            {
                __asm("bkpt 0");
            }

            status = R32(SDMMC_RINTSTS);
            if(status & DWC_MSH_CMD_ERROR_FLAGS)
            {
                W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
                return SD_ERROR;
            }
            else
            {
                CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0; /* SD Card 2.0 */
            }

            /* If errorstatus is Command TimeOut, it is a MMC card */
            /* If errorstatus is SD_OK it is a SD card: SD card 2.0 (voltage range mismatch)
                or SD card 1.x */
            /* SD CARD */
            /* Send ACMD41 SD_APP_OP_COND with Argument 0x80100000 */
            while(count < SD_MAX_VOLT_TRIAL)
            {
                //host support High Capacity SD + host support 2.7V-3.V
                //bit24: S18R --Supports voltage switching for 1.8V
                drv_sdio_acmd41sdtsk(0x403c0000);
                // drv_sdio_acmd41sdtsk(0x513c0000);
                status = R32(SDMMC_RINTSTS);
                if(status & DWC_MSH_CMD_ERROR_FLAGS)
                {
                    W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
                    return SD_ERROR;
                }
                status = R32(SDMMC_RESP0);
                count++;
                if((status & OCR_BUSY_Bit31) != OCR_POWER_BUSY)
                {
                    break;
                }
                delayms(10);
            }

            if(count >= SD_MAX_VOLT_TRIAL)
            {
                errorstatus = SD_INVALID_VOLTRANGE;
                return(errorstatus);
            }

            if((status & SD_HIGH_CAPACITY) == SD_HIGH_CAPACITY)
            {
                CardType = SDIO_HIGH_CAPACITY_SD_CARD;
            }

            errorstatus = hal_sd_initializecards();
            if(errorstatus != SD_OK)
            {
                /* CMD Response timeout(wait for CMDSENT flag) */
                return(errorstatus);
            }

            errorstatus = hal_sd_getcardinfo(&SDCardInfo);
            errorstatus = hal_sd_selectdeselect(SDCardInfo.RCA);
            if(errorstatus != SD_OK)
            {
                return(errorstatus);
            }

            errorstatus = hal_sd_enwidebus();
            if(errorstatus != SD_OK)
            {
                return(errorstatus);
            }

            errorstatus = hal_sd_sendscr(SCR);
            if(errorstatus != SD_OK)
            {
                return(errorstatus);
            }

            errorstatus = hal_sd_switchfunc_v2_0(Switch_Func);
        }
        
    }
    else
    {
        printf("Run V2.0\n");
        errorstatus = hal_sd_switchfunc_v2_0(Switch_Func);
    }

    // drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_24MHz_DIV);

    return(errorstatus);
}

/**
 * @brief SDIO 模块初始化SD卡和SDIO主机控制器函数
 * 
 * @return sdio_sd_error_t 
 * 
 * @details 执行以下初始化步骤：
 *          1. 配置GPIO
 *          2. 复位SDIO控制器
 *          3. 配置初始时钟
 *          4. 执行卡上电序列
 *          5. 初始化卡信息
 */
sdio_sd_error_t hal_sd_init(void)
{
    sdio_sd_error_t errorstatus = SD_OK;

    /* SD_EMMC_HOST FPGA V1.0, test item select by gpios */
    // TO DO:
    // gpio_configuration(0);
    drv_cpm_module_reset(SD_EMMC_HOST);

    ioctrl_sdhinit_t psdh;
    psdh.pue = PUE_PULL_EN;
    hal_ioctrl_sdhinit(&psdh);

    delay(0x2000);

    /* Assert Reset - active-low */
    if(drv_sdio_reset())
    {
        /* Reset timeout(wait for hw rest flag) */
        errorstatus = SD_ERROR;
        return(errorstatus);
    }

    drv_sdio_init();

    // while(drv_sdio_carddetect());

    drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_400kHz_DIV);

    errorstatus = hal_sd_poweron();
    if(errorstatus != SD_OK)
    {
        /* CMD Response timeout(wait for CMDSENT flag) */
        return(errorstatus);
    }

    errorstatus = hal_sd_initializecards();
    if(errorstatus != SD_OK)
    {
        /* CMD Response timeout(wait for CMDSENT flag) */
        return(errorstatus);
    }

    return(errorstatus);
}

/**
 * @brief SDIO 模块执行SD卡上电序列函数
 * 
 * @return sdio_sd_error_t 
 * 
 * @details 执行标准的SD卡上电初始化流程：
 *          1. 发送CMD0使卡进入空闲状态
 *          2. 发送CMD8检查卡接口条件
 *          3. 发送ACMD41完成卡初始化
 *          4. 根据需要执行电压切换
 */
sdio_sd_error_t hal_sd_poweron(void)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status, response, count = 0;

    /* CMD0: GO_IDLE_STATE -------------------------------------------------------*/
    /* No CMD response required */
    drv_sdio_cmd0sdtsk( CMD0ARG_GO_IDLE_STATE);

    delayms(100);
    /* CMD8: SEND_IF_COND --------------------------------------------------------*/
    /* Send CMD8 to verify SD card interface operating condition */
    /* Argument: - [31:12]: reserved(shall be set to '0')
                - [11:8]: Supply voltage(VHS) 0x1 (Range: 2.7-3.6 V)
                - [7:0]: Check pattern(recommended 0xAA) */
    /* CMD Response: R7 */
    while(response!=0x000001AA)
    {
        drv_sdio_cmd8sdtsk(0x000001AA);
        response = R32(SDMMC_RESP0);
        delay(10000);
    }
    
    if(response != 0x000001AA)
    {
        __asm("bkpt 0");
    }

    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    else
    {
        CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0; /* SD Card 2.0 */
    }

    /* If errorstatus is Command TimeOut, it is a MMC card */
    /* If errorstatus is SD_OK it is a SD card: SD card 2.0 (voltage range mismatch)
        or SD card 1.x */
    /* SD CARD */
    /* Send ACMD41 SD_APP_OP_COND with Argument 0x80100000 */
    while(count < SD_MAX_VOLT_TRIAL)
    {
        //host support High Capacity SD + host support 2.7V-3.V
        //bit24: S18R --Supports voltage switching for 1.8V
        //drv_sdio_acmd41sdtsk(0x403c0000);
        drv_sdio_acmd41sdtsk(0x513c0000);
        status = R32(SDMMC_RINTSTS);
        if(status & DWC_MSH_CMD_ERROR_FLAGS)
        {
            W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
            return SD_ERROR;
        }
        status = R32(SDMMC_RESP0);
        count++;
        if((status & OCR_BUSY_Bit31) != OCR_POWER_BUSY)
        {
            break;
        }
        delayms(10);
    }

    if(count >= SD_MAX_VOLT_TRIAL)
    {
        errorstatus = SD_INVALID_VOLTRANGE;
        return(errorstatus);
    }

    if((status & SD_HIGH_CAPACITY) == SD_HIGH_CAPACITY)
    {
        CardType = SDIO_HIGH_CAPACITY_SD_CARD;
    }

    if((status & OCR_S18A_Bit24) == OCR_S18A_Bit24) //voltage switch
    {
        drv_sdio_cmd11sdtsk();
        status = R32(SDMMC_RINTSTS);
        response = R32(SDMMC_RESP0);
        if(status & DWC_MSH_CMD_ERROR_FLAGS)
        {
            W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
            return SD_ERROR;
        }
        delay(0x3000);
        drv_sdio_switchclk(0);
        delayms(10);
        drv_sdio_cardvolt(1<<SD_SLOT1, 1); //1.8Vdd
        isvoltagesw = 1;
        delayms(10);
        status = R32(SDMMC_UHS_EXT);
        status |= 0xffff;
        delayms(10);
        W32(SDMMC_UHS_EXT, status);
        // TO DO.
        // gpio_configuration(1);
        delayms(10); //min >=7ms
        drv_sdio_switchclk(1);
        delayms(10);

        drv_sdio_pollstatus(SDMMC_INT_CMD_DONE|SDMMC_INT_VOLT_SWITCH);
    }
    return(errorstatus);
}

/**
 * @brief SDIO 模块初始化SD卡信息函数
 * 
 * @return sdio_sd_error_t 
 * 
 * @details 获取卡的基本信息：
 *          1. 读取CID(卡识别号)
 *          2. 获取RCA(相对卡地址)
 *          3. 读取CSD(卡特定数据)
 */
sdio_sd_error_t hal_sd_initializecards(void)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;
    uint16_t  rca = 0x0001;

    //  if(sdio_getpowerstate(1<<SD_SLOT1) == SDIO_PowerState_OFF)
    //  {
    //    errorstatus = SD_REQUEST_NOT_APPLICABLE;
    //    return(errorstatus);
    //  }

    /* Send CMD2 ALL_SEND_CID */
    drv_sdio_cmd2sdtsk();
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    CID_Tab[3] = R32(SDMMC_RESP0);
    CID_Tab[2] = R32(SDMMC_RESP1);
    CID_Tab[1] = R32(SDMMC_RESP2);
    CID_Tab[0] = R32(SDMMC_RESP3);

    /* Send CMD3 SET_REL_ADDR with argument 0 */
    /* SD Card publishes its RCA. */
    drv_sdio_cmd3sdtsk(0x0000);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    { 
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }

    status = R32(SDMMC_RESP0);
    if(0 == (status & (SD_R6_GENERAL_UNKNOWN_ERROR | SD_R6_ILLEGAL_CMD | SD_R6_COM_CRC_FAILED)))
    {
        rca = (uint16_t ) (status >> 16);
    }
    else
    {
        if(status & SD_R6_GENERAL_UNKNOWN_ERROR)
        {
            return(SD_GENERAL_UNKNOWN_ERROR);
        }
        if(status & SD_R6_ILLEGAL_CMD)
        {
            return(SD_ILLEGAL_CMD);
        }
        if(status & SD_R6_COM_CRC_FAILED)
        {
            return(SD_COM_CRC_FAILED);
        }
    }

    RCA = rca;
    /* Send CMD9 SEND_CSD with argument as card's RCA */
    drv_sdio_cmd9sdtsk(RCA);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    CSD_Tab[3] = R32(SDMMC_RESP0);
    CSD_Tab[2] = R32(SDMMC_RESP1);
    CSD_Tab[1] = R32(SDMMC_RESP2);
    CSD_Tab[0] = R32(SDMMC_RESP3);

    errorstatus = SD_OK; /* All cards get intialized */

    return(errorstatus);
}

/**
 * @brief SDIO 模块获取SD卡详细信息函数
 *
 * @param cardinfo 指向存储卡信息的结构体指针，用于存储解析后的卡信息
 * @return sdio_sd_error_t 
 *
 * @details 从CSD和CID寄存器解析SD卡的详细信息：
 *          1. 基本信息
 *             - 卡类型(标准容量/高容量)
 *             - 相对卡地址(RCA)
 *          2. CSD寄存器信息
 *             - CSD结构版本
 *             - 时序参数(TAAC, NSAC)
 *             - 最大总线频率
 *             - 支持的命令类别
 *             - 读写块长度
 *             - 卡容量计算
 *             - 写保护相关参数
 *          3. CID寄存器信息
 *             - 制造商ID
 *             - OEM/应用ID
 *             - 产品名称
 *             - 产品版本
 *             - 序列号
 *             - 生产日期
 *          4. 根据卡类型使用不同算法计算实际存储容量
 */
sdio_sd_error_t hal_sd_getcardinfo(sdio_sd_cardinfo_t *cardinfo)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint8_t  tmp = 0;

    cardinfo->CardType = (uint8_t )CardType;
    cardinfo->RCA = (uint16_t )RCA;

    /* Byte 0 */
    tmp = (uint8_t )((CSD_Tab[0] & 0xFF000000) >> 24);
    cardinfo->SD_csd.CSDStruct = (tmp & 0xC0) >> 6;
    cardinfo->SD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
    cardinfo->SD_csd.Reserved1 = tmp & 0x03;

    /* Byte 1 */
    tmp = (uint8_t )((CSD_Tab[0] & 0x00FF0000) >> 16);
    cardinfo->SD_csd.TAAC = tmp;

    /* Byte 2 */
    tmp = (uint8_t )((CSD_Tab[0] & 0x0000FF00) >> 8);
    cardinfo->SD_csd.NSAC = tmp;

    /* Byte 3 */
    tmp = (uint8_t )(CSD_Tab[0] & 0x000000FF);
    cardinfo->SD_csd.MaxBusClkFrec = tmp;

    /* Byte 4 */
    tmp = (uint8_t )((CSD_Tab[1] & 0xFF000000) >> 24);
    cardinfo->SD_csd.CardComdClasses = tmp << 4;

    /* Byte 5 */
    tmp = (uint8_t )((CSD_Tab[1] & 0x00FF0000) >> 16);
    cardinfo->SD_csd.CardComdClasses |= (tmp & 0xF0) >> 4;
    cardinfo->SD_csd.RdBlockLen = tmp & 0x0F;

    /* Byte 6 */
    tmp = (uint8_t )((CSD_Tab[1] & 0x0000FF00) >> 8);
    cardinfo->SD_csd.PartBlockRead = (tmp & 0x80) >> 7;
    cardinfo->SD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
    cardinfo->SD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
    cardinfo->SD_csd.DSRImpl = (tmp & 0x10) >> 4;
    cardinfo->SD_csd.Reserved2 = 0; /* Reserved */

    if(CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0)
    {
        cardinfo->SD_csd.DeviceSize = (tmp & 0x03) << 10;

        /* Byte 7 */
        tmp = (uint8_t )(CSD_Tab[1] & 0x000000FF);
        cardinfo->SD_csd.DeviceSize |= (tmp) << 2;

        /* Byte 8 */
        tmp = (uint8_t )((CSD_Tab[2] & 0xFF000000) >> 24);
        cardinfo->SD_csd.DeviceSize |= (tmp & 0xC0) >> 6;

        cardinfo->SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
        cardinfo->SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);

        /* Byte 9 */
        tmp = (uint8_t )((CSD_Tab[2] & 0x00FF0000) >> 16);
        cardinfo->SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
        cardinfo->SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
        cardinfo->SD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
        /* Byte 10 */
        tmp = (uint8_t )((CSD_Tab[2] & 0x0000FF00) >> 8);
        cardinfo->SD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;

        cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) ;
        cardinfo->CardCapacity *= (1 << (cardinfo->SD_csd.DeviceSizeMul + 2));
        cardinfo->CardBlockSize = 1 << (cardinfo->SD_csd.RdBlockLen);
        cardinfo->CardCapacity *= cardinfo->CardBlockSize;
    }
    else if(CardType == SDIO_HIGH_CAPACITY_SD_CARD)
    {
        /* Byte 7 */
        tmp = (uint8_t )(CSD_Tab[1] & 0x000000FF);
        cardinfo->SD_csd.DeviceSize = (tmp & 0x3F) << 16;

        /* Byte 8 */
        tmp = (uint8_t )((CSD_Tab[2] & 0xFF000000) >> 24);

        cardinfo->SD_csd.DeviceSize |= (tmp << 8);

        /* Byte 9 */
        tmp = (uint8_t )((CSD_Tab[2] & 0x00FF0000) >> 16);

        cardinfo->SD_csd.DeviceSize |= (tmp);

        /* Byte 10 */
        tmp = (uint8_t )((CSD_Tab[2] & 0x0000FF00) >> 8);

        cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) * 512 * 1024;
        cardinfo->CardBlockSize = 512;
    }


    cardinfo->SD_csd.EraseGrSize = (tmp & 0x40) >> 6;
    cardinfo->SD_csd.EraseGrMul = (tmp & 0x3F) << 1;

    /* Byte 11 */
    tmp = (uint8_t )(CSD_Tab[2] & 0x000000FF);
    cardinfo->SD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
    cardinfo->SD_csd.WrProtectGrSize = (tmp & 0x7F);

    /* Byte 12 */
    tmp = (uint8_t )((CSD_Tab[3] & 0xFF000000) >> 24);
    cardinfo->SD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
    cardinfo->SD_csd.ManDeflECC = (tmp & 0x60) >> 5;
    cardinfo->SD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
    cardinfo->SD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;

    /* Byte 13 */
    tmp = (uint8_t )((CSD_Tab[3] & 0x00FF0000) >> 16);
    cardinfo->SD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
    cardinfo->SD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
    cardinfo->SD_csd.Reserved3 = 0;
    cardinfo->SD_csd.ContentProtectAppli = (tmp & 0x01);

    /* Byte 14 */
    tmp = (uint8_t )((CSD_Tab[3] & 0x0000FF00) >> 8);
    cardinfo->SD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
    cardinfo->SD_csd.CopyFlag = (tmp & 0x40) >> 6;
    cardinfo->SD_csd.PermWrProtect = (tmp & 0x20) >> 5;
    cardinfo->SD_csd.TempWrProtect = (tmp & 0x10) >> 4;
    cardinfo->SD_csd.FileFormat = (tmp & 0x0C) >> 2;
    cardinfo->SD_csd.ECC = (tmp & 0x03);

    /* Byte 15 */
    tmp = (uint8_t )(CSD_Tab[3] & 0x000000FF);
    cardinfo->SD_csd.CSD_CRC = (tmp & 0xFE) >> 1;
    cardinfo->SD_csd.Reserved4 = 1;


    /* Byte 0 */
    tmp = (uint8_t )((CID_Tab[0] & 0xFF000000) >> 24);
    cardinfo->SD_cid.ManufacturerID = tmp;

    /* Byte 1 */
    tmp = (uint8_t )((CID_Tab[0] & 0x00FF0000) >> 16);
    cardinfo->SD_cid.OEM_AppliID = tmp << 8;

    /* Byte 2 */
    tmp = (uint8_t )((CID_Tab[0] & 0x000000FF00) >> 8);
    cardinfo->SD_cid.OEM_AppliID |= tmp;

    /* Byte 3 */
    tmp = (uint8_t )(CID_Tab[0] & 0x000000FF);
    cardinfo->SD_cid.ProdName1 = tmp << 24;

    /* Byte 4 */
    tmp = (uint8_t )((CID_Tab[1] & 0xFF000000) >> 24);
    cardinfo->SD_cid.ProdName1 |= tmp << 16;

    /* Byte 5 */
    tmp = (uint8_t )((CID_Tab[1] & 0x00FF0000) >> 16);
    cardinfo->SD_cid.ProdName1 |= tmp << 8;

    /* Byte 6 */
    tmp = (uint8_t )((CID_Tab[1] & 0x0000FF00) >> 8);
    cardinfo->SD_cid.ProdName1 |= tmp;

    /* Byte 7 */
    tmp = (uint8_t )(CID_Tab[1] & 0x000000FF);
    cardinfo->SD_cid.ProdName2 = tmp;

    /* Byte 8 */
    tmp = (uint8_t )((CID_Tab[2] & 0xFF000000) >> 24);
    cardinfo->SD_cid.ProdRev = tmp;

    /* Byte 9 */
    tmp = (uint8_t )((CID_Tab[2] & 0x00FF0000) >> 16);
    cardinfo->SD_cid.ProdSN = tmp << 24;

    /* Byte 10 */
    tmp = (uint8_t )((CID_Tab[2] & 0x0000FF00) >> 8);
    cardinfo->SD_cid.ProdSN |= tmp << 16;

    /* Byte 11 */
    tmp = (uint8_t )(CID_Tab[2] & 0x000000FF);
    cardinfo->SD_cid.ProdSN |= tmp << 8;

    /* Byte 12 */
    tmp = (uint8_t )((CID_Tab[3] & 0xFF000000) >> 24);
    cardinfo->SD_cid.ProdSN |= tmp;

    /* Byte 13 */
    tmp = (uint8_t )((CID_Tab[3] & 0x00FF0000) >> 16);
    cardinfo->SD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
    cardinfo->SD_cid.ManufactDate = (tmp & 0x0F) << 8;

    /* Byte 14 */
    tmp = (uint8_t )((CID_Tab[3] & 0x0000FF00) >> 8);
    cardinfo->SD_cid.ManufactDate |= tmp;

    /* Byte 15 */
    tmp = (uint8_t )(CID_Tab[3] & 0x000000FF);
    cardinfo->SD_cid.CID_CRC = (tmp & 0xFE) >> 1;
    cardinfo->SD_cid.Reserved2 = 1;

    return(errorstatus);
}

/**
 * @brief SDIO 模块选择或取消选择SD卡函数
 *
 * @param addr 卡的相对地址(RCA)
 *            - 非零值: 选择指定的卡
 *            - 0: 取消选择当前卡
 * @return sdio_sd_error_t 
 *         - SD_OK: 操作成功
 *         - SD_ERROR: 命令错误
 *         - 其他错误码: 命令响应中的具体错误
 *
 * @details 通过发送CMD7命令选择或取消选择卡：
 *          1. 发送CMD7(SDIO_SEL_DESEL_CARD)命令
 *          2. 检查命令响应错误
 *          3. 发送ACMD42配置连接器写保护
 *          4. 等待命令完成
 *          
 *          注意：
 *          - 只有被选中的卡才能响应数据传输命令
 *          - 一次只能选中一张卡
 *          - 选中新卡会自动取消之前选中的卡
 */
sdio_sd_error_t hal_sd_selectdeselect(uint32_t  addr)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;

    /* Send CMD7 SDIO_SEL_DESEL_CARD */
    drv_sdio_cmd7sdtsk(addr);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    if(errorstatus != SD_OK)
    {
        return errorstatus;
    }

    drv_sdio_acmd42sdtsk(addr, 0);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }

    return(errorstatus);
}

/**
 * @brief SDIO 模块配置SD卡为4位总线模式函数
 *
 * @return sdio_sd_error_t 
 *         - SD_OK: 配置成功
 *         - SD_ERROR: 命令错误
 *         - 其他错误码: 命令响应中的具体错误
 *
 * @details 执行以下步骤配置4位总线模式：
 *          1. 发送ACMD6命令切换总线宽度
 *          2. 检查命令响应
 *          3. 配置SDIO主机控制器为4位模式
 *          4. 发送CMD16设置块长度为512字节
 *          
 *          注意：
 *          - 切换前应确保卡支持4位模式
 *          - 切换后数据传输速率可提高4倍
 *          - 需要同时配置卡和主机控制器
 */
sdio_sd_error_t hal_sd_enwidebus(void)
{
  sdio_sd_error_t errorstatus = SD_OK;
  uint32_t  status;

  drv_sdio_acmd6sdtsk(RCA);
  status = R32(SDMMC_RINTSTS);
  if(status & DWC_MSH_CMD_ERROR_FLAGS)
  {
    W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
    return SD_ERROR;
  }
  errorstatus = hal_sd_cmdresp1error();
  W32(SDMMC_CTYPE, SDMMC_CTYPE_4BIT); //Data Bus Width = 4bit

  drv_sdio_cmd16sdtsk(512);
  status = R32(SDMMC_RINTSTS);
  if(status & DWC_MSH_CMD_ERROR_FLAGS)
  {
    W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
    return SD_ERROR;
  }
  errorstatus = hal_sd_cmdresp1error();

  return(errorstatus);
}

/**
 * @brief SDIO 模块读取SD卡的SCR(SD Card Configuration Register)寄存器函数
 *
 * @param scr 指向存储SCR数据的缓冲区(8字节)
 * @return sdio_sd_error_t 
 *         - SD_OK: 读取成功
 *         - SD_ERROR: 命令错误
 *         - 其他错误码: 命令响应中的具体错误
 *
 * @details 执行以下步骤读取SCR寄存器：
 *          1. 发送ACMD51命令请求SCR数据
 *          2. 检查命令响应
 *          3. 从FIFO读取8字节SCR数据
 *          4. 根据SCR数据判断SD规范版本
 *          
 *          注意：
 *          - SCR寄存器包含SD卡的配置信息
 *          - 可用于确定卡支持的总线宽度和速度模式
 *          - 通过版本信息判断是否为SD3.0卡
 */
sdio_sd_error_t hal_sd_sendscr(uint32_t  *scr)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;

    /* ACMD51:SEND_SCR */
    drv_sdio_acmd51sdtsk(RCA, 8);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    scr[0] = R32(SDMMC_FIFO_DATA);
    scr[1] = R32(SDMMC_FIFO_DATA);
    if(((scr[0]&0x800000) == 0x800000) && (isvoltagesw==1)) //SD_SPEC3: Version 3.0
    {
        CardType = SDIO_HIGH_CAPACITY_SD_CARD_V3_0;
    }

    return(errorstatus);
}

/**
 * @brief SDIO 模块切换功能(V2.0)函数
 * 
 * @param switch_func 指向存储切换功能数据的缓冲区
 * @return sdio_sd_error_t 
 * 
 * @details 执行SD卡V2.0的功能切换：
 *          1. 发送CMD6检查功能支持情况
 *          2. 发送CMD6执行功能切换
 *          3. 配置新的时钟设置
 */
sdio_sd_error_t hal_sd_switchfunc_v2_0(uint32_t  *switch_func)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;
    uint8_t  i;

    drv_sdio_cmd6sdtsk(0x80fffff1, 64);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }

    drv_sdio_cmd6sdtsk(0x00fffff1, 64);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }

    //  readl(CPM_BASE + 0x24) |= bit(2);        //bit2 reverse the drv clk, bit3 reverse the sample clk.
    //  readl(CPM_BASE + 0x24) |= bit(3);        //bit2 reverse the drv clk, bit3 reverse the sample clk.
    // TO DO.
    // hal_sdio_card_ddr_mode(1, 1); // 使能主机的DDR模式
    drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_50MHz_DIV);

    return(errorstatus);
}

/**
 * @brief SDIO 模块设置DDR模式函数
 * 
 * @param slot_num 卡槽号
 * @param flag 模式选择
 *          - 0: SD2/3D3模式
 *          - 1: UHS-1D8模式
 * 
 * @details 配置SDIO控制器的DDR工作模式
 */
void hal_sdio_card_ddr_mode(uint32_t  slot_num, uint8_t  flag)
{
    uint32_t  uhs_1_reg;

    uhs_1_reg = R32(SDMMC_UHS_REG);
    if( flag == SD2_3D3 )
    {
        uhs_1_reg &= ~(slot_num<<16);
    }
    else
    {
        uhs_1_reg |= (slot_num<<16);  // DDR mode
    }
    W32(SDMMC_UHS_REG, uhs_1_reg);
}

/**
 * @brief SDIO 模块切换功能(V3.0)函数
 * 
 * @param switch_func 指向存储切换功能数据的缓冲区
 * @return sdio_sd_error_t 
 * 
 * @details 执行SD卡V3.0的功能切换：
 *          1. 检查功能支持情况
 *          2. 切换到DDR50模式
 *          3. 配置DDR模式和时钟设置
 */
sdio_sd_error_t hal_sd_switchfunc_v3_0(uint32_t *switch_func)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;
    uint8_t  i;

    drv_sdio_cmd6sdtsk(0x00ffffff, 64); //bit31: 0:check function 1:switch function; group 1&2&3&4
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }

    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }
    #if 1
    drv_sdio_cmd6sdtsk(0x00fffff3, 64); //bit31: 0:check function 1:switch function; group 1&2&3&4
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }
    #endif
    //4: ddr50; 3: sdr104; 2: sdr50; 1: sdr12.
    drv_sdio_cmd6sdtsk(0x80fffff4, 64); //bit31: 0:check function 1:switch function; group 1&2&3&4
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }

    // 使能DDR模式
    hal_sdio_card_ddr_mode( 1/* <<SD_SLOT0 */, 1 );
    //  readl(CPM_BASE + 0x10) |= bit(2);        //bit2 reverse the drv clk, bit3 reverse the sample clk.
    //  readl(CPM_BASE + 0x10) |= bit(3);        //bit2 reverse the drv clk, bit3 reverse the sample clk.

    drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_400kHz_DIV);
    delayms(20);

    drv_sdio_cmd6sdtsk(0x00ffffff, 64); //bit31: 0:check function 1:switch function; group 1&2&3&4
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }

    if(status & DWC_MSH_DATA_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_DATA_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    for(i=0; i<16; i++)
    {
        switch_func[i] = R32(SDMMC_FIFO_DATA);
    }

    drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_50MHz_DIV);
    delayms(20);

    return(errorstatus);
}

/**
 * @brief SDIO 模块检查命令响应错误函数
 * 
 * @return sdio_sd_error_t 
 * 
 * @details 分析R1响应中的错误标志位，返回对应的错误码：
 *          - 地址错误
 *          - CRC错误
 *          - 非法命令
 *          - 写保护错误等
 */
sdio_sd_error_t hal_sd_cmdresp1error(void)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  response_r1;

    /* We have received response, retrieve it for analysis  */
    response_r1 = R32(SDMMC_RESP0);

    if((response_r1 & SD_OCR_ERRORBITS) == 0)
    {
        return(errorstatus);
    }

    if(response_r1 & SD_OCR_ADDR_OUT_OF_RANGE)
    {
        return(SD_ADDR_OUT_OF_RANGE);
    }

    if(response_r1 & SD_OCR_ADDR_MISALIGNED)
    {
        return(SD_ADDR_MISALIGNED);
    }

    if(response_r1 & SD_OCR_BLOCK_LEN_ERR)
    {
        return(SD_BLOCK_LEN_ERR);
    }

    if(response_r1 & SD_OCR_ERASE_SEQ_ERR)
    {
        return(SD_ERASE_SEQ_ERR);
    }

    if(response_r1 & SD_OCR_BAD_ERASE_PARAM)
    {
        return(SD_BAD_ERASE_PARAM);
    }

    if(response_r1 & SD_OCR_WRITE_PROT_VIOLATION)
    {
        return(SD_WRITE_PROT_VIOLATION);
    }

    if(response_r1 & SD_OCR_LOCK_UNLOCK_FAILED)
    {
        return(SD_LOCK_UNLOCK_FAILED);
    }

    if(response_r1 & SD_OCR_COM_CRC_FAILED)
    {
        return(SD_COM_CRC_FAILED);
    }

    if(response_r1 & SD_OCR_ILLEGAL_CMD)
    {
        return(SD_ILLEGAL_CMD);
    }

    if(response_r1 & SD_OCR_CARD_ECC_FAILED)
    {
        return(SD_CARD_ECC_FAILED);
    }

    if(response_r1 & SD_OCR_CC_ERROR)
    {
        return(SD_CC_ERROR);
    }

    if(response_r1 & SD_OCR_GENERAL_UNKNOWN_ERROR)
    {
        return(SD_GENERAL_UNKNOWN_ERROR);
    }

    if(response_r1 & SD_OCR_STREAM_READ_UNDERRUN)
    {
        return(SD_STREAM_READ_UNDERRUN);
    }

    if(response_r1 & SD_OCR_STREAM_WRITE_OVERRUN)
    {
        return(SD_STREAM_WRITE_OVERRUN);
    }

    if(response_r1 & SD_OCR_CID_CSD_OVERWRIETE)
    {
        return(SD_CID_CSD_OVERWRITE);
    }

    if(response_r1 & SD_OCR_WP_ERASE_SKIP)
    {
        return(SD_WP_ERASE_SKIP);
    }

    if(response_r1 & SD_OCR_CARD_ECC_DISABLED)
    {
        return(SD_CARD_ECC_DISABLED);
    }

    if(response_r1 & SD_OCR_ERASE_RESET)
    {
        return(SD_ERASE_RESET);
    }

    if(response_r1 & SD_OCR_AKE_SEQ_ERROR)
    {
        return(SD_AKE_SEQ_ERROR);
    }
    return(errorstatus);
}

/**
 * @brief SDIO 模块读取SD卡数据块函数
 * 
 * @param addr 读取的起始地址
 * @param readbuff 数据接收缓冲区
 * @param BlockSize 块大小(字节)
 * @param NumberOfBlocks 要读取的块数
 * @return sdio_sd_error_t 
 * 
 * @details 从SD卡读取指定数量的数据块：
 *          1. 支持单块和多块读取
 *          2. 支持DMA和非DMA传输
 *          3. 自动处理停止命令
 */
sdio_sd_error_t hal_sd_readblock(uint32_t  addr, uint32_t  *readbuff, uint16_t  BlockSize, uint32_t  NumberOfBlocks)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  TotalNumberOfBytes = 0, *tempbuff = readbuff, status;
#ifndef USE_INTERNAL_DMAC
    uint32_t  i,len;
#endif

    if(0 == readbuff)
    {
        errorstatus = SD_INVALID_PARAMETER;
        return(errorstatus);
    }

    drv_sdio_fifodmareset();
    // drv_sdio_setclk(1<<SD_SLOT1, FPGA_CLKOUT_24MHz_DIV);

#ifdef USE_INTERNAL_DMAC
    drv_sdio_internaldmacctrl(1);
    drv_sdio_configdesc(DESCRIPTION_ADDR, (uint32_t )tempbuff, NumberOfBlocks);
#endif

    TotalNumberOfBytes = NumberOfBlocks * BlockSize;
    if(NumberOfBlocks > 1)
    {
        drv_sdio_cmd18sdtsk(addr, TotalNumberOfBytes);
    }
    else
    {
        drv_sdio_cmd17sdtsk(addr, TotalNumberOfBytes);
    }
    dcache_invalidate_range(tempbuff, TotalNumberOfBytes);
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    if(status & DWC_MSH_DATA_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_DATA_ERROR_FLAGS);
        return SD_ERROR;
    }

    errorstatus = hal_sd_cmdresp1error();
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

#ifdef USE_INTERNAL_DMAC
    while(!(status & SDMMC_INT_DATA_OVER))
    {
        status = R32(SDMMC_RINTSTS);
    //      if(sd_read_complete())
    //      {
    //          W32(0x63F00000+0x14, R32(0x63F00000+0x14)|0x10000000);
    //      }
        /*if(sd_read_stop())
        {
            W32(SDMMC_CTRL, SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET);
            delay(100);
            break;
        }*/
    }
#else
    #if 0
    len = (TotalNumberOfBytes > (FIFO_DEPTH<<2)) ? FIFO_DEPTH : (TotalNumberOfBytes>>2);
    while(!(status & SDMMC_INT_DATA_OVER))
    {
        if(status & SDMMC_INT_RXDR)
        {
            for(i=0; i<len; i++)
            {
                *tempbuff = R32(SDMMC_FIFO_DATA);
                tempbuff++;
            }
        }
        status = R32(SDMMC_RINTSTS);
    }
    while(!(R32(SDMMC_STATUS) & 0x4)) //fifo not empty
    {
        *tempbuff = R32(SDMMC_FIFO_DATA);
        tempbuff++;
    }
    #endif

        len = 0;
        {
            while(len < TotalNumberOfBytes)
            {
                if(!(R32(SDMMC_STATUS) & 0x4)) //fifo not empty
                {
                    *tempbuff = R32(SDMMC_FIFO_DATA);
                    tempbuff++;
                    len++;
                }
            }
        }
    

    #endif

    if(NumberOfBlocks > 1)
    {
    #ifdef SEND_AUTO_STOP
        while(!(status & SDMMC_INT_ACD))
        {
            status = R32(SDMMC_RINTSTS);
        }
    #else
        errorstatus = hal_sd_stoptransfer();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
    #endif
    }

    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    return(errorstatus);
}

/**
 * @brief SDIO 模块写入SD卡数据块函数
 * 
 * @param addr 写入的起始地址
 * @param writebuff 待写入的数据缓冲区
 * @param BlockSize 块大小(字节)
 * @param NumberOfBlocks 要写入的块数
 * @return sdio_sd_error_t 
 * 
 * @details 向SD卡写入指定数量的数据块：
 *          1. 支持单块和多块写入
 *          2. 支持DMA和非DMA传输
 *          3. 自动处理停止命令
 *          4. 等待写入完成
 */
sdio_sd_error_t hal_sd_writeblock(uint32_t  addr, uint32_t  *writebuff, uint16_t  BlockSize, uint32_t  NumberOfBlocks)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  cardstate = 0, TotalNumberOfBytes, status;
    uint32_t  *tempbuff = writebuff;

    #ifndef USE_INTERNAL_DMAC
    uint16_t  i;
    #endif

    if(writebuff == 0)
    {
        errorstatus = SD_INVALID_PARAMETER;
        return(errorstatus);
    }

    TotalNumberOfBytes = NumberOfBlocks * BlockSize;

    #ifdef USE_INTERNAL_DMAC
    drv_sdio_internaldmacctrl(1);
    drv_sdio_configdesc(DESCRIPTION_ADDR, (uint32_t )tempbuff, NumberOfBlocks);
    #else
    for(i=0; i<TotalNumberOfBytes>>2; i++) 
    {
        W32(SDMMC_FIFO_DATA, *tempbuff);
        tempbuff++;
    }
    #endif
    dcache_clean_range(tempbuff, TotalNumberOfBytes);
    if(NumberOfBlocks > 1)
    {
        drv_sdio_cmd25sdtsk(addr, TotalNumberOfBytes);
    }
    else
    {
        drv_sdio_cmd24sdtsk(addr, TotalNumberOfBytes);
    }
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    if(status & DWC_MSH_DATA_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_DATA_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

    while((status & (SDMMC_INT_DATA_OVER|SDMMC_INT_TXDR)) != (SDMMC_INT_DATA_OVER|SDMMC_INT_TXDR))
    {
        status = R32(SDMMC_RINTSTS);
        ///TODO
            //if(sd_write_complete())
        {
            //  W32(0x63F00000+0x14, R32(0x63F00000+0x14)|0x02000000);
        }
    }
    //W32(0x63F00000+0x14, R32(0x63F00000+0x14)&~0x02000000);

    if(NumberOfBlocks > 1)
    {
        errorstatus = hal_sd_stoptransfer();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
    }

    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    /* Wait till the card is in programming state */
    do
    {
        while(R32(SDMMC_STATUS) & BIT_X(9)); //1: card data busy
        drv_sdio_cmd13sdtsk(RCA);
        status = R32(SDMMC_RINTSTS);
        if(status & DWC_MSH_CMD_ERROR_FLAGS)
        {
            W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
            return SD_ERROR;
        }
        errorstatus = hal_sd_cmdresp1error();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
        cardstate = (R32(SDMMC_RESP0)>>9) & 0xf;
    }while((errorstatus == SD_OK) && ((cardstate == SD_CARD_PROGRAMMING) || (cardstate == SD_CARD_RECEIVING)));


    #ifdef USE_INTERNAL_DMAC
        drv_sdio_internaldmacctrl(0);
    #endif
    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    return(errorstatus);
}

/**
 * @brief SDIO 模块停止数据传输函数
 * 
 * @return sdio_sd_error_t 操作状态码
 * 
 * @details 发送CMD12停止当前的数据传输
 */
sdio_sd_error_t hal_sd_stoptransfer(void)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  status;

    drv_sdio_cmd12sdtsk();
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();

    return(errorstatus);
}

/**
 * @brief SDIO 模块启动数据块读取函数
 * 
 * @param addr 读取的起始地址
 * @param BlockSize 块大小(字节)
 * @param NumberOfBlocks 要读取的块数
 * @return sdio_sd_error_t 
 * 
 * @details 启动数据块读取操作，但不等待完成
 */
sdio_sd_error_t hal_sd_readblock_start(uint32_t  addr, uint16_t  BlockSize, uint32_t  NumberOfBlocks)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  TotalNumberOfBytes = 0, status;

    TotalNumberOfBytes = NumberOfBlocks * BlockSize;
    if(NumberOfBlocks > 1)
    {
        drv_sdio_cmd18sdtsk(addr, TotalNumberOfBytes);
    }
    else
    {
        drv_sdio_cmd17sdtsk(addr, TotalNumberOfBytes);
    }
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    if(status & DWC_MSH_DATA_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_DATA_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }

    while(!(R32(SDMMC_RINTSTS) & SDMMC_INT_RXDR));

    return(errorstatus);
}

/**
 * @brief SDIO 模块停止数据块读取函数
 * 
 * @param multi 读取模式
 *          - 0: 单块读取
 *          - 1: 多块读取
 * @return sdio_sd_error_t 
 * 
 * @details 结束数据块读取操作，处理停止命令
 */
sdio_sd_error_t hal_sd_readblock_stop(uint8_t  multi)
{
    sdio_sd_error_t errorstatus = SD_OK;

    if(multi == MULTI_READ_CMD_START)
    {
    #ifdef SEND_AUTO_STOP
        while(!(status & SDMMC_INT_ACD))
        {
            status = R32(SDMMC_RINTSTS);
        }
    #else
        errorstatus = hal_sd_stoptransfer();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
    #endif
    }

    W32(SDMMC_CTRL, SDMMC_CTRL_FIFO_RESET);
    while(R32(SDMMC_CTRL)&SDMMC_CTRL_FIFO_RESET);
    while(!(R32(SDMMC_RINTSTS) & SDMMC_INT_DATA_OVER));
    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    return(errorstatus);
}

/**
 * @brief SDIO 模块启动数据块写入函数
 * 
 * @param addr 写入的起始地址
 * @param BlockSize 块大小(字节)
 * @param NumberOfBlocks 要写入的块数
 * @return sdio_sd_error_t 
 * 
 * @details 启动数据块写入操作，但不等待完成
 */
sdio_sd_error_t hal_sd_writeblock_start(uint32_t  addr, uint16_t  BlockSize, uint32_t  NumberOfBlocks)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  TotalNumberOfBytes, status;

    if(start_write_block == 1)
    {
        return SD_OK;
    }

    TotalNumberOfBytes = NumberOfBlocks * BlockSize;
    if(NumberOfBlocks > 1)
    {
        drv_sdio_cmd25sdtsk(addr, TotalNumberOfBytes);
    }
    else
    {
        drv_sdio_cmd24sdtsk(addr, TotalNumberOfBytes);
    }
    status = R32(SDMMC_RINTSTS);
    if(status & DWC_MSH_CMD_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
        return SD_ERROR;
    }
    if(status & DWC_MSH_DATA_ERROR_FLAGS)
    {
        W32(SDMMC_RINTSTS, DWC_MSH_DATA_ERROR_FLAGS);
        return SD_ERROR;
    }
    errorstatus = hal_sd_cmdresp1error();
    if(errorstatus != SD_OK)
    {
        return(errorstatus);
    }
    start_write_block = 1;

    return(errorstatus);
}

/**
 * @brief SDIO 模块停止数据块写入函数
 * 
 * @param multi 写入模式
 *          - 0: 单块写入
 *          - 1: 多块写入
 * @return sdio_sd_error_t 
 * 
 * @details 结束数据块写入操作：
 *          1. 处理停止命令
 *          2. 等待写入完成
 *          3. 检查卡状态
 */
sdio_sd_error_t hal_sd_writeblock_stop(uint8_t  multi)
{
    sdio_sd_error_t errorstatus = SD_OK;
    uint32_t  cardstate = 0, status;

    while(!(R32(SDMMC_RINTSTS)&SDMMC_INT_TXDR));

    if(multi == MULTI_WRITE_CMD_START)
    {
        errorstatus = hal_sd_stoptransfer();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
    }

    while(!(R32(SDMMC_RINTSTS) & SDMMC_INT_DATA_OVER));
    W32(SDMMC_CTRL, SDMMC_CTRL_FIFO_RESET);
    while(R32(SDMMC_CTRL)&SDMMC_CTRL_FIFO_RESET);
    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    /* Wait till the card is in programming state */
    do
    {
        while(R32(SDMMC_STATUS) & BIT_X(9)); //1: card data busy
        drv_sdio_cmd13sdtsk(RCA);
        status = R32(SDMMC_RINTSTS);
        if(status & DWC_MSH_CMD_ERROR_FLAGS)
        {
            W32(SDMMC_RINTSTS, DWC_MSH_CMD_ERROR_FLAGS);
            return SD_ERROR;
        }
        errorstatus = hal_sd_cmdresp1error();
        if(errorstatus != SD_OK)
        {
            return(errorstatus);
        }
        cardstate = (R32(SDMMC_RESP0)>>9) & 0xf;
    }while((errorstatus == SD_OK) && ((cardstate == SD_CARD_PROGRAMMING) || (cardstate == SD_CARD_RECEIVING)));

    start_write_block = 0;
    /* Clear all the static flags */
    W32(SDMMC_RINTSTS, 0xFFFFFFFF);

    return(errorstatus);
}
