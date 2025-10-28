/**
 * @file dma_reg.h
 * @author Product application department
 * @brief  DMA 模块寄存器配置文件
 * @version  V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DMA_REG_H_
#define __DMA_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define DMAC1_BASE_ADDR (0x40046000)
#define DMAC2_BASE_ADDR (0x40047000)
#define DMAC1 ((reg_dmac_t *)DMAC1_BASE_ADDR)
#define DMAC2 ((reg_dmac_t *)DMAC2_BASE_ADDR)

// DMAC_CTRLn
#define DMAC_INT_MIN (((uint32_t)1 << 31))
#define DMAC_LLP_SRC_EN (((uint32_t)1 << 28))
#define DMAC_LLP_DST_EN (((uint32_t)1 << 27))
#define DMAC_TT_FC_MASK ((uint32_t)(0x00700000))
#define DMAC_TT_FC_SHIFT_MASK ((uint32_t)(20))
#define DMAC_TT_FC_BITS_MASK ((uint32_t)(0xFF8FFFFF))
#define DMAC_SRC_MSIZE_MASK ((uint32_t)(0x0001C000))
#define DMAC_SRC_MSIZE_SHIFT_MASK (((uint32_t)14))
#define DMAC_SRC_MSIZE_BITS_MASK ((uint32_t)(0xFFFE3FFF))

#define DMAC_DEST_MSIZE_MASK ((uint32_t)(0x00003800))
#define DMAC_DEST_MSIZE_SHIFT_MASK (((uint32_t)11))
#define DMAC_DEST_MSIZE_BITS_MASK ((uint32_t)(0xFFFC7FFF))

#define DMAC_SINC_INC (((uint32_t)1 << 0))
#define DMAC_SINC_DEC                                      (((uint32_t)1<<9)
#define DMAC_SINC_NO_CHANGE (((uint32_t)1 << 10))
#define DMAC_SINC_INC_MASK ((uint32_t)(0x00000600))
#define DMAC_SINC_INC_SHIFT_MASK ((uint32_t)(9))
#define DMAC_SINC_INC_BITS_MASK ((uint32_t)(0xFFFFF9FF))

#define DMAC_DINC_INC (((uint32_t)1 << 0))
#define DMAC_DINC_DEC                                      (((uint32_t)1<<7)
#define DMAC_DINC_NO_CHANGE (((uint32_t)1 << 8))
#define DMAC_DINC_INC_MASK ((uint32_t)(0x00000180))
#define DMAC_DINC_INC_SHIFT_MASK ((uint32_t)(7))
#define DMAC_DINC_INC_BITS_MASK ((uint32_t)(0xFFFFFE7F))

#define DMAC_SRC_TR_WIDTH_MASK ((uint32_t)(0x00000070))
#define DMAC_SRC_TR_WIDTH_SHIFT_MASK ((uint32_t)(4))
#define DMAC_SRC_TR_WIDTH_BITS_MASK ((uint32_t)(0xFFFFFF1F))
#define DMAC_DST_TR_WIDTH_MASK ((uint32_t)(0x00000007))
#define DMAC_DST_TR_WIDTH_SHIFT_MASK (((uint32_t)1))
#define DMAC_DST_TR_WIDTH_BITS_MASK ((uint32_t)(0xFFFFFFF1))
#define DMAC_INT_EN (((uint32_t)1 << 0))
// DMA_CFGn
#define DMAC_MAX_ABRS_MASK ((uint32_t)(0x3FF00000))
#define DMAC_MAX_ABRS_SHIFT_MASK ((uint32_t)(20))
#define DMAC_MAX_ABRS_BITS_MASK ((uint32_t)(0xC00FFFFF))
#define DMAC_HS_SEL_SRC (((uint32_t)1 << 11))
#define DMAC_HS_SEL_DST (((uint32_t)1 << 10))
#define DMAC_FIFO_EMPTY (((uint32_t)1 << 9))
#define DMAC_CH_SUSP (((uint32_t)1 << 8))

#define DMAC_CH_PRIOR_MASK ((uint32_t)(0x000000E0))
#define DMAC_CH_PRIOR_SHIFT_MASK ((uint32_t)(5))
#define DMAC_CH_PRIOR_BITS_MASK ((uint32_t)(0xFFFFFF1F))

// DMA_CFG_HIGHn
#define DMAC_DST_PER_MASK ((uint32_t)(0x00007800))
#define DMAC_DST_PER_SHIFT_MASK (((uint32_t)11))
#define DMAC_DST_PER_BITS_MASK ((uint32_t)(0xFFFF87FF))

#define DMAC_SRC_PER_MASK ((uint32_t)(0x00000780))
#define DMAC_SRC_PER_SHIFT_MASK ((uint32_t)(7))
#define DMAC_SRC_PER_BITS_MASK ((uint32_t)(0xFFFFF87F))

#define DMAC_FC_MODE (((uint32_t)1 << 0))

#define DMAC_CH_WE_EN_SHIFT_MASK ((uint32_t)(8))
#define DMAC_CH_EN_MASK ((uint32_t)(0x0000000F))
#define DMAC_EN ((uint8_t)(1 << 0))

/**
 * @brief DMA 通道寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t SRCADDR;
    __IO uint32_t RESERVED0;
    __IO uint32_t DSTADDR;
    __IO uint32_t RESERVED1;
    __IO uint32_t LLI;
    __IO uint32_t RESERVED2;
    __IO uint32_t CTRL;
    __IO uint32_t CTRL_HIGH;
    __I uint32_t RESERVED3[8];
    __IO uint32_t CONFIG;
    __IO uint32_t CONFIG_HIGH;
    __I uint32_t RESERVED4[4];
} dmac_channel_t;

/**
 * @brief DMAC 模块 MIN ADDR寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t SARADDR;
    __IO uint32_t DSTADDR;
} dmac_minaddr_t;

/**
 * @brief DMAC 模块寄存器结构体定义
 *
 */
typedef struct
{
    dmac_channel_t CH[4]; /**< 0x0000---> 0x015C */

    __IO uint32_t RESERVED0[88]; /**< 0x0160---> 0x02BC */
    __IO uint32_t RAWTFR;        /**< 0x02C0 raw status for intTfr interrupt */
    __IO uint32_t RESERVED1;
    __IO uint32_t RAWBLOCK; /**< 0x02C8 raw status for intBlock interrupt */
    __IO uint32_t RESERVED2;
    __IO uint32_t RAWSRCTRAN; /**< 0x02D0 raw status for intScTran interrupt */
    __IO uint32_t RESERVED3;
    __IO uint32_t RAWDETTRAN; /**< 0x02D8 raw status for intDestTran interrupt */
    __IO uint32_t RESERVED4;
    __IO uint32_t RAWERR; /**< 0x02EO raw status for intErr interrupt */
    __IO uint32_t RESERVED5;
    __IO uint32_t STATTFR; /**< 0x02E8  status for intTfr interrupt */
    __IO uint32_t RESERVED6;
    __IO uint32_t STATBLOCK; /**< 0x02F0  status for intBlock interrupt */
    __IO uint32_t RESERVED7;
    __IO uint32_t STATSRC; /**< 0x02F8  status for intScTran interrupt */
    __IO uint32_t RESERVED8;
    __IO uint32_t STATDST; /**< 0x0300  status for intDestTran interrupt */
    __IO uint32_t RESERVED9;
    __IO uint32_t ERR; /**< 0x0308  status for intErr interrupt */
    __IO uint32_t RESERVED10;
    __IO uint32_t MASKTFR; /**< 0x0310 mask for intTfr interrupt */
    __IO uint32_t RESERVED11;
    __IO uint32_t MASKBLOCK; /**< 0x0318 mask for intBlock interrupt */
    __IO uint32_t RESERVED12;
    __IO uint32_t MASKSRC; /**< 0x0320 mask for intScTran interrupt */
    __IO uint32_t RESERVED13;
    __IO uint32_t MASKDST; /**< 0x0328 mask for intDestTran interrupt */
    __IO uint32_t RESERVED14;
    __IO uint32_t MASKERR; /**< 0x0330 mask for intErr interrupt */
    __IO uint32_t RESERVED15;
    __IO uint32_t CLRTFR; /**< 0x0338 clear for intTfr interrupt */
    __IO uint32_t RESERVED16;
    __IO uint32_t CLRBLOCK; /**< 0x0340 clear for intBlock interrupt */
    __IO uint32_t RESERVED17;
    __IO uint32_t CLRSRC; /**< 0x0348 clear for intScTran interrupt */
    __IO uint32_t RESERVED18;
    __IO uint32_t CLRDST; /**< 0x0350 clear for intDestTran interrupt */
    __IO uint32_t RESERVED19;
    __IO uint32_t CLRERR; /**< 0x0358 clear for intErr interrupt */
    __IO uint32_t RESERVED20;
    __IO uint32_t STATUSINT; /**< 0x0360 status for each interrupt type */
    __IO uint32_t RESERVED21;
    __IO uint32_t SRCREQ; /**< 0x0368 transacion request */
    __IO uint32_t RESERVED22;
    __IO uint32_t DESTREQ; /**< 0x0370 transacion request */
    __IO uint32_t RESERVED23;
    __IO uint32_t SINGLESRC; /**< 0x0378 transacion request */
    __IO uint32_t RESERVED24;
    __IO uint32_t SINGLEDST; /**< 0x0380 transacion request */
    __IO uint32_t RESERVED25;
    __IO uint32_t LASTSRC; /**< 0x0388 transacion request */
    __IO uint32_t RESERVED26;
    __IO uint32_t LASTDST; /**< 0x0390 transacion request */
    __IO uint32_t RESERVED27;
    __IO uint32_t CONFIG; /**< 0x0398 confuration  */
    __IO uint32_t RESERVED28;
    __IO uint32_t CHEN;          /**< 0x03A0 cannel enable  */
    __IO uint32_t RESERVED29[7]; /**< 0x03A4---> 0x03BC */
    __IO uint32_t RAWMIN;        /**< 0x03C0 raw status for intMIN interrupt */
    __IO uint32_t RESERVED30;
    __IO uint32_t MASKMIN; /**< 0x03C8 mask status for intMIN interrupt */
    __IO uint32_t RESERVED31;
    __IO uint32_t CLRMIN; /**< 0x03D0 clear status for intMIN interrupt */
    __IO uint32_t RESERVED32;

    dmac_minaddr_t MIN_CH[4]; /**< 0x03D8---> 0x03F4 */
} reg_dmac_t;

/**
 * @brief DMAC 模块控制寄存器结构体定义
 *
 */
typedef struct _dmac_controlreg_t
{
    __IO uint32_t DMA_RAWTFR;     // 0x00//0x2c0
    __IO uint32_t RESERVED1;      // 0x04//0x2c4
    __IO uint32_t DMA_RAWBLOCK;   // 0x08////0x2c8
    __IO uint32_t RESERVED2;      // 0x0c////0x2cc
    __IO uint32_t DMA_RAWSRCTRAN; // 0x10//0x2d0
    __IO uint32_t RESERVED3;      // 0x14//0x2d4
    __IO uint32_t DMA_RAWDSTTRAN; // 0x18//0x2d8
    __IO uint32_t RESERVED4;      // 0x1c//0x2dc
    __IO uint32_t DMA_RAWERR;     // 0x20//0x2e0
    __IO uint32_t RESERVED5;      // 0x24//0x2e4
    __IO uint32_t DMA_STATTFR;    // 0x28//0x2e8
    __IO uint32_t RESERVED6;      // 0x2c//0x2ec
    __IO uint32_t DMA_STATBLOCK;  // 0x30//0x2f0
    __IO uint32_t RESERVED7;      // 0x34//0x2f4
    __IO uint32_t DMA_STATSRC;    // 0x38//0x2f8
    __IO uint32_t RESERVED8;      // 0x3c //0x2fc

    __IO uint32_t DMA_STATDST; // 0x40//0x300
    __IO uint32_t RESERVED9;   // 0x44//0x304
    __IO uint32_t DMA_STATERR; // 0x48//0x308
    __IO uint32_t RESERVED10;  // 0x4c//0x30c

    __IO uint32_t DMA_MASKTFR;   // 0x50//0x310
    __IO uint32_t RESERVED11;    // 0x54//0x314
    __IO uint32_t DMA_MASKBLOCK; // 0x58//0x318
    __IO uint32_t RESERVED12;    // 0x5c//0x31c

    __IO uint32_t DMA_MASKSRC; // 0x60//0x320
    __IO uint32_t RESERVED13;  // 0x64//0x324
    __IO uint32_t DMA_MASKDST; // 0x68//0x328
    __IO uint32_t RESERVED14;  // 0x6c//0x32c

    __IO uint32_t DMA_MASKERR; // 0x70//0x330
    __IO uint32_t RESERVED15;  // 0x74//0x334
    __IO uint32_t DMA_CLRTFR;  // 0x78//0x338
    __IO uint32_t RESERVED16;  // 0x7c//0x33c

    __IO uint32_t DMA_CLRBLOCK; // 0x80//0x340
    __IO uint32_t RESERVED17;   // 0x84//0x344
    __IO uint32_t DMA_CLRSRC;   // 0x88//0x348
    __IO uint32_t RESERVED18;   // 0x8c//0x34c

    __IO uint32_t DMA_CLRDST; // 0x90//0x350
    __IO uint32_t RESERVED19; // 0x94//0x354
    __IO uint32_t DMA_CLRERR; // 0x98//0x358
    __IO uint32_t RESERVED20; // 0x9c//0x35c

    __IO uint32_t DMA_STATUSINT; // 0x100//0x360
    __IO uint32_t RESERVED21;    // 0x104//0x364
    __IO uint32_t DMA_SRCREQ;    // 0x108//0x368
    __IO uint32_t RESERVED22;    // 0x10c//0x36c

    __IO uint32_t DMA_DSTREQ;    // 0x110//0x370
    __IO uint32_t RESERVED23;    // 0x114//0x374
    __IO uint32_t DMA_SINGLESRC; // 0x118//0x378
    __IO uint32_t RESERVED24;    // 0x11c//0x37c

    __IO uint32_t DMA_SINGLEDST; // 0x120//0x380
    __IO uint32_t RESERVED25;    // 0x124//0x384
    __IO uint32_t DMA_LASTSRC;   // 0x128//0x388
    __IO uint32_t RESERVED26;    // 0x12c//0x38c

    __IO uint32_t DMA_LASTDST; // 0x130//0x390
    __IO uint32_t RESERVED27;  // 0x134//0x394
    __IO uint32_t DMA_CONFIG;  // 0x138//0x398
    __IO uint32_t RESERVED28;  // 0x13c//0x39c

    __IO uint32_t DMA_CHEN; // 0x140//0x3a0

} dmac_controlreg_t;

#ifdef __cplusplus
}
#endif

#endif
