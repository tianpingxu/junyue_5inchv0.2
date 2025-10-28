/**
 * @file sdio_hal.h
 * @author Product Application Department
 * @brief  SDIO模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-04
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef SDIO_HAL_H_
#define SDIO_HAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "sdio_drv.h"

// 全局变量定义
#define SD2_3D3 0
#define UHS_1D8 1

#define SD_DMA_MODE ((uint32_t)0x00000000)
#define SD_INTERRUPT_MODE ((uint32_t)0x00000001)
#define SD_POLLING_MODE ((uint32_t)0x00000002)

#define SDIO_STD_CAPACITY_SD_CARD_V1_1 ((uint32_t)0x0)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0 ((uint32_t)0x1)
#define SDIO_HIGH_CAPACITY_SD_CARD ((uint32_t)0x2)
#define SDIO_HIGH_CAPACITY_SD_CARD_V3_0 ((uint32_t)0x3)
#define SDIO_MULTIMEDIA_CARD ((uint32_t)0x4)
#define SDIO_SECURE_DIGITAL_IO_CARD ((uint32_t)0x5)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD ((uint32_t)0x6)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD ((uint32_t)0x7)
#define SDIO_HIGH_CAPACITY_MMC_CARD ((uint32_t)0x8)

#define MULTI_READ_CMD_START (1)
#define MULTI_WRITE_CMD_START (2)

#define SD_MAX_VOLT_TRIAL ((uint32_t)0x0000FFFF)
#define SD_HIGH_CAPACITY ((uint32_t)0x40000000)
#define SD_R6_GENERAL_UNKNOWN_ERROR ((uint32_t)0x00002000)
#define SD_R6_ILLEGAL_CMD ((uint32_t)0x00004000)
#define SD_R6_COM_CRC_FAILED ((uint32_t)0x00008000)
#define SD_DATATIMEOUT ((uint32_t)0x001FFFFF)
#define SD_CARD_PROGRAMMING ((uint32_t)0x00000007)
#define SD_CARD_RECEIVING ((uint32_t)0x00000006)

#define SD_OCR_ADDR_OUT_OF_RANGE ((uint32_t)0x80000000)
#define SD_OCR_ADDR_MISALIGNED ((uint32_t)0x40000000)
#define SD_OCR_BLOCK_LEN_ERR ((uint32_t)0x20000000)
#define SD_OCR_ERASE_SEQ_ERR ((uint32_t)0x10000000)
#define SD_OCR_BAD_ERASE_PARAM ((uint32_t)0x08000000)
#define SD_OCR_WRITE_PROT_VIOLATION ((uint32_t)0x04000000)
#define SD_OCR_LOCK_UNLOCK_FAILED ((uint32_t)0x01000000)
#define SD_OCR_COM_CRC_FAILED ((uint32_t)0x00800000)
#define SD_OCR_ILLEGAL_CMD ((uint32_t)0x00400000)
#define SD_OCR_CARD_ECC_FAILED ((uint32_t)0x00200000)
#define SD_OCR_CC_ERROR ((uint32_t)0x00100000)
#define SD_OCR_GENERAL_UNKNOWN_ERROR ((uint32_t)0x00080000)
#define SD_OCR_STREAM_READ_UNDERRUN ((uint32_t)0x00040000)
#define SD_OCR_STREAM_WRITE_OVERRUN ((uint32_t)0x00020000)
#define SD_OCR_CID_CSD_OVERWRIETE ((uint32_t)0x00010000)
#define SD_OCR_WP_ERASE_SKIP ((uint32_t)0x00008000)
#define SD_OCR_CARD_ECC_DISABLED ((uint32_t)0x00004000)
#define SD_OCR_ERASE_RESET ((uint32_t)0x00002000)
#define SD_OCR_AKE_SEQ_ERROR ((uint32_t)0x00000008)
#define SD_OCR_ERRORBITS ((uint32_t)0xFDFFE008)

#define SDIO_GO_IDLE_STATE ((uint8_t)0)
#define SDIO_SEND_OP_COND ((uint8_t)1)
#define SDIO_ALL_SEND_CID ((uint8_t)2)
#define SDIO_SET_REL_ADDR ((uint8_t)3)
#define SDIO_SET_DSR ((uint8_t)4)
#define SDIO_SDIO_SEN_OP_COND ((uint8_t)5)
#define SDIO_HS_SWITCH ((uint8_t)6)
#define SDIO_SEL_DESEL_CARD ((uint8_t)7)
#define SDIO_HS_SEND_EXT_CSD ((uint8_t)8)
#define SDIO_SEND_CSD ((uint8_t)9)
#define SDIO_SEND_CID ((uint8_t)10)
#define SDIO_READ_DAT_UNTIL_STOP ((uint8_t)11)
#define SDIO_STOP_TRANSMISSION ((uint8_t)12)
#define SDIO_SEND_STATUS ((uint8_t)13)
#define SDIO_HS_BUSTEST_READ ((uint8_t)14)
#define SDIO_GO_INACTIVE_STATE ((uint8_t)15)
#define SDIO_SET_BLOCKLEN ((uint8_t)16)
#define SDIO_READ_SINGLE_BLOCK ((uint8_t)17)
#define SDIO_READ_MULT_BLOCK ((uint8_t)18)
#define SDIO_HS_BUSTEST_WRITE ((uint8_t)19)
#define SDIO_WRITE_DAT_UNTIL_STOP ((uint8_t)20)
#define SDIO_SET_BLOCK_COUNT ((uint8_t)23)
#define SDIO_WRITE_SINGLE_BLOCK ((uint8_t)24)
#define SDIO_WRITE_MULT_BLOCK ((uint8_t)25)
#define SDIO_PROG_CID ((uint8_t)26)
#define SDIO_PROG_CSD ((uint8_t)27)
#define SDIO_SET_WRITE_PROT ((uint8_t)28)
#define SDIO_CLR_WRITE_PROT ((uint8_t)29)
#define SDIO_SEND_WRITE_PROT ((uint8_t)30)
#define SDIO_SD_ERASE_GRP_START ((uint8_t)32)

#define SDIO_SD_ERASE_GRP_END ((uint8_t)33)

#define SDIO_ERASE_GRP_START ((uint8_t)35)

#define SDIO_ERASE_GRP_END ((uint8_t)36)

#define SDIO_ERASE ((uint8_t)38)
#define SDIO_FAST_IO ((uint8_t)39)
#define SDIO_GO_IRQ_STATE ((uint8_t)40)
#define SDIO_LOCK_UNLOCK ((uint8_t)42)
#define SDIO_APP_CMD ((uint8_t)55)
#define SDIO_GEN_CMD ((uint8_t)56)
#define SDIO_NO_CMD ((uint8_t)64)

#define SDIO_APP_SD_SET_BUSWIDTH ((uint8_t)6)
#define SDIO_SD_APP_STAUS ((uint8_t)13)
#define SDIO_SD_APP_SEND_NUM_WRITE_BLOCKS ((uint8_t)22)
#define SDIO_SD_APP_OP_COND ((uint8_t)41)
#define SDIO_SD_APP_SET_CLR_CARD_DETECT ((uint8_t)42)
#define SDIO_SD_APP_SEND_SCR ((uint8_t)51)
#define SDIO_SDIO_RW_DIRECT ((uint8_t)52)
#define SDIO_SDIO_RW_EXTENDED ((uint8_t)53)

#define SDIO_SD_APP_GET_MKB ((uint8_t)43)
#define SDIO_SD_APP_GET_MID ((uint8_t)44)
#define SDIO_SD_APP_SET_CER_RN1 ((uint8_t)45)
#define SDIO_SD_APP_GET_CER_RN2 ((uint8_t)46)
#define SDIO_SD_APP_SET_CER_RES2 ((uint8_t)47)
#define SDIO_SD_APP_GET_CER_RES1 ((uint8_t)48)
#define SDIO_SD_APP_SECURE_READ_MULTIPLE_BLOCK ((uint8_t)18)
#define SDIO_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK ((uint8_t)25)
#define SDIO_SD_APP_SECURE_ERASE ((uint8_t)38)
#define SDIO_SD_APP_CHANGE_SECURE_AREA ((uint8_t)49)
#define SDIO_SD_APP_SECURE_WRITE_MKB ((uint8_t)48)

/**
 * @brief SDIO 模块错误类型定义
 * 
 */
typedef enum
{
    /* SDIO specific error defines */
    SD_CMD_CRC_FAIL = (1),           /* Command response received (but CRC check failed) */
    SD_DATA_CRC_FAIL = (2),          /* Data bock sent/received (CRC check Failed) */
    SD_CMD_RSP_TIMEOUT = (3),        /* Command response timeout */
    SD_DATA_TIMEOUT = (4),           /* Data time out */
    SD_TX_UNDERRUN = (5),            /* Transmit FIFO under-run */
    SD_RX_OVERRUN = (6),             /* Receive FIFO over-run */
    SD_START_BIT_ERR = (7),          /* Start bit not detected on all data signals in widE bus mode */
    SD_CMD_OUT_OF_RANGE = (8),       /* CMD's argument was out of range.*/
    SD_ADDR_MISALIGNED = (9),        /* Misaligned address */
    SD_BLOCK_LEN_ERR = (10),         /* Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
    SD_ERASE_SEQ_ERR = (11),         /* An error in the sequence of erase command occurs.*/
    SD_BAD_ERASE_PARAM = (12),       /* An Invalid selection for erase groups */
    SD_WRITE_PROT_VIOLATION = (13),  /* Attempt to program a write protect block */
    SD_LOCK_UNLOCK_FAILED = (14),    /* Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
    SD_COM_CRC_FAILED = (15),        /* CRC check of the previous command failed */
    SD_ILLEGAL_CMD = (16),           /* Command is not legal for the card state */
    SD_CARD_ECC_FAILED = (17),       /* Card internal ECC was applied but failed to correct the data */
    SD_CC_ERROR = (18),              /* Internal card controller error */
    SD_GENERAL_UNKNOWN_ERROR = (19), /* General or Unknown error */
    SD_STREAM_READ_UNDERRUN = (20),  /* The card could not sustain data transfer in stream read operation. */
    SD_STREAM_WRITE_OVERRUN = (21),  /* The card could not sustain data programming in stream mode */
    SD_CID_CSD_OVERWRITE = (22),     /* CID/CSD overwrite error */
    SD_WP_ERASE_SKIP = (23),         /* only partial address space was erased */
    SD_CARD_ECC_DISABLED = (24),     /* Command has been executed without using internal ECC */
    SD_ERASE_RESET = (25),           /* Erase sequence was cleared before executing because an out of erase sequence command was received */
    SD_AKE_SEQ_ERROR = (26),         /* Error in sequence of authentication. */
    SD_INVALID_VOLTRANGE = (27),
    SD_ADDR_OUT_OF_RANGE = (28),
    SD_SWITCH_ERROR = (29),
    SD_SDIO_DISABLED = (30),
    SD_SDIO_FUNCTION_BUSY = (31),
    SD_SDIO_FUNCTION_FAILED = (32),
    SD_SDIO_UNKNOWN_FUNCTION = (33),
    /* Standard error defines */
    SD_INTERNAL_ERROR,
    SD_NOT_CONFIGURED,
    SD_REQUEST_PENDING,
    SD_REQUEST_NOT_APPLICABLE,
    SD_INVALID_PARAMETER,
    SD_UNSUPPORTED_FEATURE,
    SD_UNSUPPORTED_HW,
    SD_ERROR,
    SD_OK,
} sdio_sd_error_t;

/**
 * @brief SDIO 模块传输状态定义
 * 
 */
typedef enum
{
    SD_NO_TRANSFER = 0,
    SD_TRANSFER_IN_PROGRESS
} sdio_sd_transfer_state_t;


/**
 * @brief SDIO 模块最新传输信息定义
 * 
 */
typedef struct
{
    uint16_t TransferredBytes;
    sdio_sd_error_t TransferError;
    uint8_t padding;
} sdio_sd_lasttransfer_info_t;

/**
 * @brief SDIO 模块初始化CSD定义
 * 
 */
typedef struct
{
    volatile uint8_t CSDStruct;
    volatile uint8_t SysSpecVersion;
    volatile uint8_t Reserved1;
    volatile uint8_t TAAC;
    volatile uint8_t NSAC;
    volatile uint8_t MaxBusClkFrec;
    volatile uint16_t CardComdClasses;
    volatile uint8_t RdBlockLen;
    volatile uint8_t PartBlockRead;
    volatile uint8_t WrBlockMisalign;
    volatile uint8_t RdBlockMisalign;
    volatile uint8_t DSRImpl;
    volatile uint8_t Reserved2;
    volatile uint32_t DeviceSize;
    volatile uint8_t MaxRdCurrentVDDMin;
    volatile uint8_t MaxRdCurrentVDDMax;
    volatile uint8_t MaxWrCurrentVDDMin;
    volatile uint8_t MaxWrCurrentVDDMax;
    volatile uint8_t DeviceSizeMul;
    volatile uint8_t EraseGrSize;
    volatile uint8_t EraseGrMul;
    volatile uint8_t WrProtectGrSize;
    volatile uint8_t WrProtectGrEnable;
    volatile uint8_t ManDeflECC;
    volatile uint8_t WrSpeedFact;
    volatile uint8_t MaxWrBlockLen;
    volatile uint8_t WriteBlockPaPartial;
    volatile uint8_t Reserved3;
    volatile uint8_t ContentProtectAppli;
    volatile uint8_t FileFormatGrouop;
    volatile uint8_t CopyFlag;
    volatile uint8_t PermWrProtect;
    volatile uint8_t TempWrProtect;
    volatile uint8_t FileFormat;
    volatile uint8_t ECC;
    volatile uint8_t CSD_CRC;
    volatile uint8_t Reserved4;
} sdio_sd_csd_t;

/**
 * @brief SDIO 模块CID定义
 * 
 */
typedef struct
{
    volatile uint8_t ManufacturerID;
    volatile uint16_t OEM_AppliID;
    volatile uint32_t ProdName1;
    volatile uint8_t ProdName2;
    volatile uint8_t ProdRev;
    volatile uint32_t ProdSN;
    volatile uint8_t Reserved1;
    volatile uint16_t ManufactDate;
    volatile uint8_t CID_CRC;
    volatile uint8_t Reserved2;
} sdio_sd_cid_t;

/**
 * @brief SDIO 模块卡信息定义
 * 
 */
typedef struct
{
    sdio_sd_csd_t SD_csd;
    sdio_sd_cid_t SD_cid;
    uint32_t CardCapacity;
    uint32_t CardBlockSize;
    uint16_t RCA;
    uint8_t CardType;
} sdio_sd_cardinfo_t;

// 函数声明
sdio_sd_error_t hal_sd_init(void);
sdio_sd_error_t hal_sd_poweron(void);
sdio_sd_error_t hal_sd_poweroff(void);
sdio_sd_error_t hal_sd_initializecards(void);
sdio_sd_error_t hal_sd_getcardinfo(sdio_sd_cardinfo_t *cardinfo);
sdio_sd_error_t hal_sd_enablewidebusoperation(uint32_t WideMode);
sdio_sd_error_t hal_sd_setdevicemode(uint32_t Mode);
sdio_sd_error_t hal_sd_selectdeselect(uint32_t addr);
sdio_sd_error_t hal_sd_readblock(uint32_t addr, uint32_t *readbuff, uint16_t BlockSize, uint32_t NumberOfBlocks);
sdio_sd_error_t hal_sd_writeblock(uint32_t addr, uint32_t *writebuff, uint16_t BlockSize, uint32_t NumberOfBlocks);
sdio_sd_error_t hal_sd_stoptransfer(void);
sdio_sd_error_t hal_sd_erase(uint32_t startaddr, uint32_t endaddr);
sdio_sd_error_t hal_sd_sendsdstatus(uint32_t *psdstatus);
sdio_sd_error_t hal_sd_enumcard(void);
sdio_sd_error_t hal_sd_sendstatus(void);
sdio_sd_error_t hal_sd_sendscr(uint32_t *scr);
sdio_sd_error_t hal_sd_enwidebus(void);
sdio_sd_error_t hal_sd_switchfunc_v2_0(uint32_t *switch_func);
sdio_sd_error_t hal_sd_switchfunc_v3_0(uint32_t *switch_func);
sdio_sd_error_t hal_sd_cmdresp1error(void);
sdio_sd_error_t hal_sd_readblock_start(uint32_t addr, uint16_t BlockSize, uint32_t NumberOfBlocks);
sdio_sd_error_t hal_sd_readblock_stop(uint8_t multi);
sdio_sd_error_t hal_sd_writeblock_start(uint32_t addr, uint16_t BlockSize, uint32_t NumberOfBlocks);
sdio_sd_error_t hal_sd_writeblock_stop(uint8_t multi);
void hal_sdio_card_ddr_mode(uint32_t  slot_num, uint8_t  flag);

#ifdef __cplusplus
}
#endif

#endif
