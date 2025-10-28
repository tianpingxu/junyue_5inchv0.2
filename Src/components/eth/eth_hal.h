/**
 * @file eth_hal.h
 * @author Product Application Department
 * @brief  ETH 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __ETH_HAL_H
#define __ETH_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "debug.h"
#include "status.h"
#include "type.h"
#include "eth_reg.h"

    // 全局变量定义

#if defined(__GNUC__) && !defined(__CC_ARM) /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(4)))
#endif /* __ALIGN_END */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif /* __ALIGN_BEGIN */
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif /* __ALIGN_END */
#ifndef __ALIGN_BEGIN
#if defined(__CC_ARM) /* ARM Compiler */
#define __ALIGN_BEGIN __align(4)
#elif defined(__ICCARM__) /* IAR Compiler */
#define __ALIGN_BEGIN
#endif /* __CC_ARM */
#endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */

    /* ################## Ethernet peripheral configuration ##################### */

/* Section 1 : Ethernet peripheral configuration */

/* MAC ADDRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0 2U
#define MAC_ADDR1 0U
#define MAC_ADDR2 0U
#define MAC_ADDR3 0U
#define MAC_ADDR4 0U
#define MAC_ADDR5 0U

/* Definition of the Ethernet driver buffers size and count */
#define ETH_RX_BUF_SIZE ETH_MAX_PACKET_SIZE /* buffer size for receive               */
#define ETH_TX_BUF_SIZE ETH_MAX_PACKET_SIZE /* buffer size for transmit              */
#define ETH_RXBUFNB ((uint32_t)8U)          /* 8 Rx buffers of size ETH_RX_BUF_SIZE  */
#define ETH_TXBUFNB ((uint32_t)8U)          /* 8 Tx buffers of size ETH_TX_BUF_SIZE  */

    /* Section 2: PHY configuration section */

/* LAN8720_PHY_ADDRESS Address*/
#define LAN8720_PHY_ADDRESS 0U
/* PHY Reset delay these values are based on a 1 ms Systick interrupt*/
#define PHY_RESET_DELAY ((uint32_t)0x00000005U)
/* PHY Configuration delay */
#define PHY_CONFIG_DELAY ((uint32_t)0x00000005U)

#define PHY_READ_TO ((uint32_t)0x0000FFFFU)
#define PHY_WRITE_TO ((uint32_t)0x0000FFFFU)

    /* Section 3: Common PHY Registers */

#define PHY_BCR ((uint16_t)0x00U) /**< Transceiver Basic Control Register   */
#define PHY_BSR ((uint16_t)0x01U) /**< Transceiver Basic Status Register    */
#define PHY_ID1 ((uint16_t)0x02U) /**< PHY_ID1 Register    */
#define PHY_ID2 ((uint16_t)0x03U) /**< PHY_ID2 Register    */

#define PHY_RESET ((uint16_t)0x8000U)                   /**< PHY Reset */
#define PHY_LOOPBACK ((uint16_t)0x4000U)                /**< Select loop-back mode */
#define PHY_FULLDUPLEX_100M ((uint16_t)0x2100U)         /**< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M ((uint16_t)0x2000U)         /**< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M ((uint16_t)0x0100U)          /**< Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M ((uint16_t)0x0000U)          /**< Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION ((uint16_t)0x1000U)         /**< Enable auto-negotiation function     */
#define PHY_RESTART_AUTONEGOTIATION ((uint16_t)0x0200U) /**< Restart auto-negotiation function    */
#define PHY_POWERDOWN ((uint16_t)0x0800U)               /**< Select the power down mode           */
#define PHY_ISOLATE ((uint16_t)0x0400U)                 /**< Isolate PHY from MII                 */

#define PHY_AUTONEGO_COMPLETE ((uint16_t)0x0020U) /**< Auto-Negotiation process completed   */
#define PHY_LINKED_STATUS ((uint16_t)0x0004U)     /**< Valid link established               */
#define PHY_JABBER_DETECTION ((uint16_t)0x0002U)  /**< Jabber condition detected            */

/* Section 4: Extended PHY Registers */
#define PHY_SR ((uint16_t)0x1FU) /**< PHY status register Offset                      */

#define PHY_SPEED_STATUS ((uint16_t)0x0004U)  /**< PHY Speed mask                                  */
#define PHY_DUPLEX_STATUS ((uint16_t)0x0010U) /**< PHY Duplex mask                                 */

#define PHY_ISFR ((uint16_t)0x001DU)      /**< PHY Interrupt Source Flag register Offset   */
#define PHY_ISFR_INT4 ((uint16_t)0x000BU) /**< PHY Link down inturrupt       */

//============================================================================================================
#define SYSCFG_PMC_MII_RMII_SEL_Pos (23U)
#define SYSCFG_PMC_MII_RMII_SEL_Msk (0x1UL << SYSCFG_PMC_MII_RMII_SEL_Pos) /**< 0x00800000 */
#define SYSCFG_PMC_MII_RMII_SEL SYSCFG_PMC_MII_RMII_SEL_Msk                /**<Ethernet PHY interface selection */
/* Old MII_RMII_SEL bit definition, maintained for legacy purpose */
#define SYSCFG_PMC_MII_RMII SYSCFG_PMC_MII_RMII_SEL

#define UNUSED(X) (void)X /* To avoid gcc/g++ warnings */

#define USE_RTOS (0)
#if (USE_RTOS == 1U)
/* Reserved for future use */
#error "USE_RTOS should be 0 in the current HAL release"
#else
#define __HAL_LOCK(__HANDLE__)            \
    do                                    \
    {                                     \
        if ((__HANDLE__)->Lock == LOCKED) \
        {                                 \
            return STATUS_BUSY;           \
        }                                 \
        else                              \
        {                                 \
            (__HANDLE__)->Lock = LOCKED;  \
        }                                 \
    } while (0U)

#define __HAL_UNLOCK(__HANDLE__)       \
    do                                 \
    {                                  \
        (__HANDLE__)->Lock = UNLOCKED; \
    } while (0U)
#endif /* USE_RTOS */

/******************************************************************************/
/*                                                                            */
/*                Ethernet MAC Registers bits definitions                     */
/*                                                                            */
/******************************************************************************/
/* Bit definition for Ethernet MAC Control Register register */
#define ETH_MACCR_WD_Pos (23U)
#define ETH_MACCR_WD_Msk (0x1UL << ETH_MACCR_WD_Pos) /*!< 0x00800000 */
#define ETH_MACCR_WD ETH_MACCR_WD_Msk                /* Watchdog disable */
#define ETH_MACCR_JD_Pos (22U)
#define ETH_MACCR_JD_Msk (0x1UL << ETH_MACCR_JD_Pos) /*!< 0x00400000 */
#define ETH_MACCR_JD ETH_MACCR_JD_Msk                /* Jabber disable */
#define ETH_MACCR_IFG_Pos (17U)
#define ETH_MACCR_IFG_Msk (0x7UL << ETH_MACCR_IFG_Pos) /*!< 0x000E0000 */
#define ETH_MACCR_IFG ETH_MACCR_IFG_Msk                /* Inter-frame gap */
#define ETH_MACCR_IFG_96Bit 0x00000000U                /* Minimum IFG between frames during transmission is 96Bit */
#define ETH_MACCR_IFG_88Bit 0x00020000U                /* Minimum IFG between frames during transmission is 88Bit */
#define ETH_MACCR_IFG_80Bit 0x00040000U                /* Minimum IFG between frames during transmission is 80Bit */
#define ETH_MACCR_IFG_72Bit 0x00060000U                /* Minimum IFG between frames during transmission is 72Bit */
#define ETH_MACCR_IFG_64Bit 0x00080000U                /* Minimum IFG between frames during transmission is 64Bit */
#define ETH_MACCR_IFG_56Bit 0x000A0000U                /* Minimum IFG between frames during transmission is 56Bit */
#define ETH_MACCR_IFG_48Bit 0x000C0000U                /* Minimum IFG between frames during transmission is 48Bit */
#define ETH_MACCR_IFG_40Bit 0x000E0000U                /* Minimum IFG between frames during transmission is 40Bit */
#define ETH_MACCR_CSD_Pos (16U)
#define ETH_MACCR_CSD_Msk (0x1UL << ETH_MACCR_CSD_Pos) /*!< 0x00010000 */
#define ETH_MACCR_CSD ETH_MACCR_CSD_Msk                /* Carrier sense disable (during transmission) */
#define ETH_MACCR_FES_Pos (14U)
#define ETH_MACCR_FES_Msk (0x1UL << ETH_MACCR_FES_Pos) /*!< 0x00004000 */
#define ETH_MACCR_FES ETH_MACCR_FES_Msk                /* Fast ethernet speed */
#define ETH_MACCR_ROD_Pos (13U)
#define ETH_MACCR_ROD_Msk (0x1UL << ETH_MACCR_ROD_Pos) /*!< 0x00002000 */
#define ETH_MACCR_ROD ETH_MACCR_ROD_Msk                /* Receive own disable */
#define ETH_MACCR_LM_Pos (12U)
#define ETH_MACCR_LM_Msk (0x1UL << ETH_MACCR_LM_Pos) /*!< 0x00001000 */
#define ETH_MACCR_LM ETH_MACCR_LM_Msk                /* loopback mode */
#define ETH_MACCR_DM_Pos (11U)
#define ETH_MACCR_DM_Msk (0x1UL << ETH_MACCR_DM_Pos) /*!< 0x00000800 */
#define ETH_MACCR_DM ETH_MACCR_DM_Msk                /* Duplex mode */
#define ETH_MACCR_IPCO_Pos (10U)
#define ETH_MACCR_IPCO_Msk (0x1UL << ETH_MACCR_IPCO_Pos) /*!< 0x00000400 */
#define ETH_MACCR_IPCO ETH_MACCR_IPCO_Msk                /* IP Checksum offload */
#define ETH_MACCR_RD_Pos (9U)
#define ETH_MACCR_RD_Msk (0x1UL << ETH_MACCR_RD_Pos) /*!< 0x00000200 */
#define ETH_MACCR_RD ETH_MACCR_RD_Msk                /* Retry disable */
#define ETH_MACCR_APCS_Pos (7U)
#define ETH_MACCR_APCS_Msk (0x1UL << ETH_MACCR_APCS_Pos) /*!< 0x00000080 */
#define ETH_MACCR_APCS ETH_MACCR_APCS_Msk                /* Automatic Pad/CRC stripping */
#define ETH_MACCR_BL_Pos (5U)
#define ETH_MACCR_BL_Msk (0x3UL << ETH_MACCR_BL_Pos) /*!< 0x00000060 */
#define ETH_MACCR_BL ETH_MACCR_BL_Msk                /* Back-off limit: random integer number (r) of slot time delays before rescheduling \
                             a transmission attempt during retries after a collision: 0 =< r <2^k */
#define ETH_MACCR_BL_10 0x00000000U                  /* k = min (n, 10) */
#define ETH_MACCR_BL_8 0x00000020U                   /* k = min (n, 8) */
#define ETH_MACCR_BL_4 0x00000040U                   /* k = min (n, 4) */
#define ETH_MACCR_BL_1 0x00000060U                   /* k = min (n, 1) */
#define ETH_MACCR_DC_Pos (4U)
#define ETH_MACCR_DC_Msk (0x1UL << ETH_MACCR_DC_Pos) /*!< 0x00000010 */
#define ETH_MACCR_DC ETH_MACCR_DC_Msk                /* Defferal check */
#define ETH_MACCR_TE_Pos (3U)
#define ETH_MACCR_TE_Msk (0x1UL << ETH_MACCR_TE_Pos) /*!< 0x00000008 */
#define ETH_MACCR_TE ETH_MACCR_TE_Msk                /* Transmitter enable */
#define ETH_MACCR_RE_Pos (2U)
#define ETH_MACCR_RE_Msk (0x1UL << ETH_MACCR_RE_Pos) /*!< 0x00000004 */
#define ETH_MACCR_RE ETH_MACCR_RE_Msk                /* Receiver enable */

/* Bit definition for Ethernet MAC Frame Filter Register */
#define ETH_MACFFR_RA_Pos (31U)
#define ETH_MACFFR_RA_Msk (0x1UL << ETH_MACFFR_RA_Pos) /*!< 0x80000000 */
#define ETH_MACFFR_RA ETH_MACFFR_RA_Msk                /* Receive all */
#define ETH_MACFFR_HPF_Pos (10U)
#define ETH_MACFFR_HPF_Msk (0x1UL << ETH_MACFFR_HPF_Pos) /*!< 0x00000400 */
#define ETH_MACFFR_HPF ETH_MACFFR_HPF_Msk                /* Hash or perfect filter */
#define ETH_MACFFR_SAF_Pos (9U)
#define ETH_MACFFR_SAF_Msk (0x1UL << ETH_MACFFR_SAF_Pos) /*!< 0x00000200 */
#define ETH_MACFFR_SAF ETH_MACFFR_SAF_Msk                /* Source address filter enable */
#define ETH_MACFFR_SAIF_Pos (8U)
#define ETH_MACFFR_SAIF_Msk (0x1UL << ETH_MACFFR_SAIF_Pos) /*!< 0x00000100 */
#define ETH_MACFFR_SAIF ETH_MACFFR_SAIF_Msk                /* SA inverse filtering */
#define ETH_MACFFR_PCF_Pos (6U)
#define ETH_MACFFR_PCF_Msk (0x3UL << ETH_MACFFR_PCF_Pos) /*!< 0x000000C0 */
#define ETH_MACFFR_PCF ETH_MACFFR_PCF_Msk                /* Pass control frames: 3 cases */
#define ETH_MACFFR_PCF_BlockAll_Pos (6U)
#define ETH_MACFFR_PCF_BlockAll_Msk (0x1UL << ETH_MACFFR_PCF_BlockAll_Pos) /*!< 0x00000040 */
#define ETH_MACFFR_PCF_BlockAll ETH_MACFFR_PCF_BlockAll_Msk                /* MAC filters all control frames from reaching the application */
#define ETH_MACFFR_PCF_ForwardAll_Pos (7U)
#define ETH_MACFFR_PCF_ForwardAll_Msk (0x1UL << ETH_MACFFR_PCF_ForwardAll_Pos) /*!< 0x00000080 */
#define ETH_MACFFR_PCF_ForwardAll ETH_MACFFR_PCF_ForwardAll_Msk                /* MAC forwards all control frames to application even if they fail the Address Filter */
#define ETH_MACFFR_PCF_ForwardPassedAddrFilter_Pos (6U)
#define ETH_MACFFR_PCF_ForwardPassedAddrFilter_Msk (0x3UL << ETH_MACFFR_PCF_ForwardPassedAddrFilter_Pos) /*!< 0x000000C0 */
#define ETH_MACFFR_PCF_ForwardPassedAddrFilter ETH_MACFFR_PCF_ForwardPassedAddrFilter_Msk                /* MAC forwards control frames that pass the Address Filter. */
#define ETH_MACFFR_BFD_Pos (5U)
#define ETH_MACFFR_BFD_Msk (0x1UL << ETH_MACFFR_BFD_Pos) /*!< 0x00000020 */
#define ETH_MACFFR_BFD ETH_MACFFR_BFD_Msk                /* Broadcast frame disable */
#define ETH_MACFFR_PAM_Pos (4U)
#define ETH_MACFFR_PAM_Msk (0x1UL << ETH_MACFFR_PAM_Pos) /*!< 0x00000010 */
#define ETH_MACFFR_PAM ETH_MACFFR_PAM_Msk                /* Pass all mutlicast */
#define ETH_MACFFR_DAIF_Pos (3U)
#define ETH_MACFFR_DAIF_Msk (0x1UL << ETH_MACFFR_DAIF_Pos) /*!< 0x00000008 */
#define ETH_MACFFR_DAIF ETH_MACFFR_DAIF_Msk                /* DA Inverse filtering */
#define ETH_MACFFR_HM_Pos (2U)
#define ETH_MACFFR_HM_Msk (0x1UL << ETH_MACFFR_HM_Pos) /*!< 0x00000004 */
#define ETH_MACFFR_HM ETH_MACFFR_HM_Msk                /* Hash multicast */
#define ETH_MACFFR_HU_Pos (1U)
#define ETH_MACFFR_HU_Msk (0x1UL << ETH_MACFFR_HU_Pos) /*!< 0x00000002 */
#define ETH_MACFFR_HU ETH_MACFFR_HU_Msk                /* Hash unicast */
#define ETH_MACFFR_PM_Pos (0U)
#define ETH_MACFFR_PM_Msk (0x1UL << ETH_MACFFR_PM_Pos) /*!< 0x00000001 */
#define ETH_MACFFR_PM ETH_MACFFR_PM_Msk                /* Promiscuous mode */

/* Bit definition for Ethernet MAC Hash Table High Register */
#define ETH_MACHTHR_HTH_Pos (0U)
#define ETH_MACHTHR_HTH_Msk (0xFFFFFFFFUL << ETH_MACHTHR_HTH_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACHTHR_HTH ETH_MACHTHR_HTH_Msk                       /* Hash table high */

/* Bit definition for Ethernet MAC Hash Table Low Register */
#define ETH_MACHTLR_HTL_Pos (0U)
#define ETH_MACHTLR_HTL_Msk (0xFFFFFFFFUL << ETH_MACHTLR_HTL_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACHTLR_HTL ETH_MACHTLR_HTL_Msk                       /* Hash table low */

/* Bit definition for Ethernet MAC MII Address Register */
#define ETH_MACMIIAR_PA_Pos (11U)
#define ETH_MACMIIAR_PA_Msk (0x1FUL << ETH_MACMIIAR_PA_Pos) /*!< 0x0000F800 */
#define ETH_MACMIIAR_PA ETH_MACMIIAR_PA_Msk                 /* Physical layer address */
#define ETH_MACMIIAR_MR_Pos (6U)
#define ETH_MACMIIAR_MR_Msk (0x1FUL << ETH_MACMIIAR_MR_Pos) /*!< 0x000007C0 */
#define ETH_MACMIIAR_MR ETH_MACMIIAR_MR_Msk                 /* MII register in the selected PHY */
#define ETH_MACMIIAR_CR_Pos (2U)
#define ETH_MACMIIAR_CR_Msk (0x7UL << ETH_MACMIIAR_CR_Pos) /*!< 0x0000001C */
#define ETH_MACMIIAR_CR ETH_MACMIIAR_CR_Msk                /* CR clock range: 6 cases */
#define ETH_MACMIIAR_CR_Div42 0x00000000U                  /* HCLK:60-100 MHz; MDC clock= HCLK/42   */
#define ETH_MACMIIAR_CR_Div62_Pos (2U)
#define ETH_MACMIIAR_CR_Div62_Msk (0x1UL << ETH_MACMIIAR_CR_Div62_Pos) /*!< 0x00000004 */
#define ETH_MACMIIAR_CR_Div62 ETH_MACMIIAR_CR_Div62_Msk                /* HCLK:100-150 MHz; MDC clock= HCLK/62  */
#define ETH_MACMIIAR_CR_Div16_Pos (3U)
#define ETH_MACMIIAR_CR_Div16_Msk (0x1UL << ETH_MACMIIAR_CR_Div16_Pos) /*!< 0x00000008 */
#define ETH_MACMIIAR_CR_Div16 ETH_MACMIIAR_CR_Div16_Msk                /* HCLK:20-35 MHz; MDC clock= HCLK/16    */
#define ETH_MACMIIAR_CR_Div26_Pos (2U)
#define ETH_MACMIIAR_CR_Div26_Msk (0x3UL << ETH_MACMIIAR_CR_Div26_Pos) /*!< 0x0000000C */
#define ETH_MACMIIAR_CR_Div26 ETH_MACMIIAR_CR_Div26_Msk                /* HCLK:35-60 MHz; MDC clock= HCLK/26    */
#define ETH_MACMIIAR_CR_Div102_Pos (4U)
#define ETH_MACMIIAR_CR_Div102_Msk (0x1UL << ETH_MACMIIAR_CR_Div102_Pos) /*!< 0x00000010 */
#define ETH_MACMIIAR_CR_Div102 ETH_MACMIIAR_CR_Div102_Msk                /* HCLK:150-168 MHz; MDC clock= HCLK/102 */
#define ETH_MACMIIAR_MW_Pos (1U)
#define ETH_MACMIIAR_MW_Msk (0x1UL << ETH_MACMIIAR_MW_Pos) /*!< 0x00000002 */
#define ETH_MACMIIAR_MW ETH_MACMIIAR_MW_Msk                /* MII write */
#define ETH_MACMIIAR_MB_Pos (0U)
#define ETH_MACMIIAR_MB_Msk (0x1UL << ETH_MACMIIAR_MB_Pos) /*!< 0x00000001 */
#define ETH_MACMIIAR_MB ETH_MACMIIAR_MB_Msk                /* MII busy  */

/* Bit definition for Ethernet MAC MII Data Register */
#define ETH_MACMIIDR_MD_Pos (0U)
#define ETH_MACMIIDR_MD_Msk (0xFFFFUL << ETH_MACMIIDR_MD_Pos) /*!< 0x0000FFFF */
#define ETH_MACMIIDR_MD ETH_MACMIIDR_MD_Msk                   /* MII data: read/write data from/to PHY */

/* Bit definition for Ethernet MAC Flow Control Register */
#define ETH_MACFCR_PT_Pos (16U)
#define ETH_MACFCR_PT_Msk (0xFFFFUL << ETH_MACFCR_PT_Pos) /*!< 0xFFFF0000 */
#define ETH_MACFCR_PT ETH_MACFCR_PT_Msk                   /* Pause time */
#define ETH_MACFCR_ZQPD_Pos (7U)
#define ETH_MACFCR_ZQPD_Msk (0x1UL << ETH_MACFCR_ZQPD_Pos) /*!< 0x00000080 */
#define ETH_MACFCR_ZQPD ETH_MACFCR_ZQPD_Msk                /* Zero-quanta pause disable */
#define ETH_MACFCR_PLT_Pos (4U)
#define ETH_MACFCR_PLT_Msk (0x3UL << ETH_MACFCR_PLT_Pos) /*!< 0x00000030 */
#define ETH_MACFCR_PLT ETH_MACFCR_PLT_Msk                /* Pause low threshold: 4 cases */
#define ETH_MACFCR_PLT_Minus4 0x00000000U                /* Pause time minus 4 slot times   */
#define ETH_MACFCR_PLT_Minus28_Pos (4U)
#define ETH_MACFCR_PLT_Minus28_Msk (0x1UL << ETH_MACFCR_PLT_Minus28_Pos) /*!< 0x00000010 */
#define ETH_MACFCR_PLT_Minus28 ETH_MACFCR_PLT_Minus28_Msk                /* Pause time minus 28 slot times  */
#define ETH_MACFCR_PLT_Minus144_Pos (5U)
#define ETH_MACFCR_PLT_Minus144_Msk (0x1UL << ETH_MACFCR_PLT_Minus144_Pos) /*!< 0x00000020 */
#define ETH_MACFCR_PLT_Minus144 ETH_MACFCR_PLT_Minus144_Msk                /* Pause time minus 144 slot times */
#define ETH_MACFCR_PLT_Minus256_Pos (4U)
#define ETH_MACFCR_PLT_Minus256_Msk (0x3UL << ETH_MACFCR_PLT_Minus256_Pos) /*!< 0x00000030 */
#define ETH_MACFCR_PLT_Minus256 ETH_MACFCR_PLT_Minus256_Msk                /* Pause time minus 256 slot times */
#define ETH_MACFCR_UPFD_Pos (3U)
#define ETH_MACFCR_UPFD_Msk (0x1UL << ETH_MACFCR_UPFD_Pos) /*!< 0x00000008 */
#define ETH_MACFCR_UPFD ETH_MACFCR_UPFD_Msk                /* Unicast pause frame detect */
#define ETH_MACFCR_RFCE_Pos (2U)
#define ETH_MACFCR_RFCE_Msk (0x1UL << ETH_MACFCR_RFCE_Pos) /*!< 0x00000004 */
#define ETH_MACFCR_RFCE ETH_MACFCR_RFCE_Msk                /* Receive flow control enable */
#define ETH_MACFCR_TFCE_Pos (1U)
#define ETH_MACFCR_TFCE_Msk (0x1UL << ETH_MACFCR_TFCE_Pos) /*!< 0x00000002 */
#define ETH_MACFCR_TFCE ETH_MACFCR_TFCE_Msk                /* Transmit flow control enable */
#define ETH_MACFCR_FCBBPA_Pos (0U)
#define ETH_MACFCR_FCBBPA_Msk (0x1UL << ETH_MACFCR_FCBBPA_Pos) /*!< 0x00000001 */
#define ETH_MACFCR_FCBBPA ETH_MACFCR_FCBBPA_Msk                /* Flow control busy/backpressure activate */

/* Bit definition for Ethernet MAC VLAN Tag Register */
#define ETH_MACVLANTR_VLANTC_Pos (16U)
#define ETH_MACVLANTR_VLANTC_Msk (0x1UL << ETH_MACVLANTR_VLANTC_Pos) /*!< 0x00010000 */
#define ETH_MACVLANTR_VLANTC ETH_MACVLANTR_VLANTC_Msk                /* 12-bit VLAN tag comparison */
#define ETH_MACVLANTR_VLANTI_Pos (0U)
#define ETH_MACVLANTR_VLANTI_Msk (0xFFFFUL << ETH_MACVLANTR_VLANTI_Pos) /*!< 0x0000FFFF */
#define ETH_MACVLANTR_VLANTI ETH_MACVLANTR_VLANTI_Msk                   /* VLAN tag identifier (for receive frames) */

/* Bit definition for Ethernet MAC Remote Wake-UpFrame Filter Register */
#define ETH_MACRWUFFR_D_Pos (0U)
#define ETH_MACRWUFFR_D_Msk (0xFFFFFFFFUL << ETH_MACRWUFFR_D_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACRWUFFR_D ETH_MACRWUFFR_D_Msk                       /* Wake-up frame filter register data */
/* Eight sequential Writes to this address (offset 0x28) will write all Wake-UpFrame Filter Registers.
   Eight sequential Reads from this address (offset 0x28) will read all Wake-UpFrame Filter Registers. */
/* Wake-UpFrame Filter Reg0 : Filter 0 Byte Mask
   Wake-UpFrame Filter Reg1 : Filter 1 Byte Mask
   Wake-UpFrame Filter Reg2 : Filter 2 Byte Mask
   Wake-UpFrame Filter Reg3 : Filter 3 Byte Mask
   Wake-UpFrame Filter Reg4 : RSVD - Filter3 Command - RSVD - Filter2 Command -
                              RSVD - Filter1 Command - RSVD - Filter0 Command
   Wake-UpFrame Filter Re5 : Filter3 Offset - Filter2 Offset - Filter1 Offset - Filter0 Offset
   Wake-UpFrame Filter Re6 : Filter1 CRC16 - Filter0 CRC16
   Wake-UpFrame Filter Re7 : Filter3 CRC16 - Filter2 CRC16 */

/* Bit definition for Ethernet MAC PMT Control and Status Register */
#define ETH_MACPMTCSR_WFFRPR_Pos (31U)
#define ETH_MACPMTCSR_WFFRPR_Msk (0x1UL << ETH_MACPMTCSR_WFFRPR_Pos) /*!< 0x80000000 */
#define ETH_MACPMTCSR_WFFRPR ETH_MACPMTCSR_WFFRPR_Msk                /* Wake-Up Frame Filter Register Pointer Reset */
#define ETH_MACPMTCSR_GU_Pos (9U)
#define ETH_MACPMTCSR_GU_Msk (0x1UL << ETH_MACPMTCSR_GU_Pos) /*!< 0x00000200 */
#define ETH_MACPMTCSR_GU ETH_MACPMTCSR_GU_Msk                /* Global Unicast                              */
#define ETH_MACPMTCSR_WFR_Pos (6U)
#define ETH_MACPMTCSR_WFR_Msk (0x1UL << ETH_MACPMTCSR_WFR_Pos) /*!< 0x00000040 */
#define ETH_MACPMTCSR_WFR ETH_MACPMTCSR_WFR_Msk                /* Wake-Up Frame Received                      */
#define ETH_MACPMTCSR_MPR_Pos (5U)
#define ETH_MACPMTCSR_MPR_Msk (0x1UL << ETH_MACPMTCSR_MPR_Pos) /*!< 0x00000020 */
#define ETH_MACPMTCSR_MPR ETH_MACPMTCSR_MPR_Msk                /* Magic Packet Received                       */
#define ETH_MACPMTCSR_WFE_Pos (2U)
#define ETH_MACPMTCSR_WFE_Msk (0x1UL << ETH_MACPMTCSR_WFE_Pos) /*!< 0x00000004 */
#define ETH_MACPMTCSR_WFE ETH_MACPMTCSR_WFE_Msk                /* Wake-Up Frame Enable                        */
#define ETH_MACPMTCSR_MPE_Pos (1U)
#define ETH_MACPMTCSR_MPE_Msk (0x1UL << ETH_MACPMTCSR_MPE_Pos) /*!< 0x00000002 */
#define ETH_MACPMTCSR_MPE ETH_MACPMTCSR_MPE_Msk                /* Magic Packet Enable                         */
#define ETH_MACPMTCSR_PD_Pos (0U)
#define ETH_MACPMTCSR_PD_Msk (0x1UL << ETH_MACPMTCSR_PD_Pos) /*!< 0x00000001 */
#define ETH_MACPMTCSR_PD ETH_MACPMTCSR_PD_Msk                /* Power Down                                  */

/* Bit definition for Ethernet MAC debug Register */
#define ETH_MACDBGR_TFF_Pos (25U)
#define ETH_MACDBGR_TFF_Msk (0x1UL << ETH_MACDBGR_TFF_Pos) /*!< 0x02000000 */
#define ETH_MACDBGR_TFF ETH_MACDBGR_TFF_Msk                /* Tx FIFO full                                                            */
#define ETH_MACDBGR_TFNE_Pos (24U)
#define ETH_MACDBGR_TFNE_Msk (0x1UL << ETH_MACDBGR_TFNE_Pos) /*!< 0x01000000 */
#define ETH_MACDBGR_TFNE ETH_MACDBGR_TFNE_Msk                /* Tx FIFO not empty                                                       */
#define ETH_MACDBGR_TFWA_Pos (22U)
#define ETH_MACDBGR_TFWA_Msk (0x1UL << ETH_MACDBGR_TFWA_Pos) /*!< 0x00400000 */
#define ETH_MACDBGR_TFWA ETH_MACDBGR_TFWA_Msk                /* Tx FIFO write active                                                    */
#define ETH_MACDBGR_TFRS_Pos (20U)
#define ETH_MACDBGR_TFRS_Msk (0x3UL << ETH_MACDBGR_TFRS_Pos) /*!< 0x00300000 */
#define ETH_MACDBGR_TFRS ETH_MACDBGR_TFRS_Msk                /* Tx FIFO read status mask                                                */
#define ETH_MACDBGR_TFRS_WRITING_Pos (20U)
#define ETH_MACDBGR_TFRS_WRITING_Msk (0x3UL << ETH_MACDBGR_TFRS_WRITING_Pos) /*!< 0x00300000 */
#define ETH_MACDBGR_TFRS_WRITING ETH_MACDBGR_TFRS_WRITING_Msk                /* Writing the received TxStatus or flushing the TxFIFO                    */
#define ETH_MACDBGR_TFRS_WAITING_Pos (21U)
#define ETH_MACDBGR_TFRS_WAITING_Msk (0x1UL << ETH_MACDBGR_TFRS_WAITING_Pos) /*!< 0x00200000 */
#define ETH_MACDBGR_TFRS_WAITING ETH_MACDBGR_TFRS_WAITING_Msk                /* Waiting for TxStatus from MAC transmitter                               */
#define ETH_MACDBGR_TFRS_READ_Pos (20U)
#define ETH_MACDBGR_TFRS_READ_Msk (0x1UL << ETH_MACDBGR_TFRS_READ_Pos) /*!< 0x00100000 */
#define ETH_MACDBGR_TFRS_READ ETH_MACDBGR_TFRS_READ_Msk                /* Read state (transferring data to the MAC transmitter)                   */
#define ETH_MACDBGR_TFRS_IDLE 0x00000000U                              /* Idle state                                                              */
#define ETH_MACDBGR_MTP_Pos (19U)
#define ETH_MACDBGR_MTP_Msk (0x1UL << ETH_MACDBGR_MTP_Pos) /*!< 0x00080000 */
#define ETH_MACDBGR_MTP ETH_MACDBGR_MTP_Msk                /* MAC transmitter in pause                                                */
#define ETH_MACDBGR_MTFCS_Pos (17U)
#define ETH_MACDBGR_MTFCS_Msk (0x3UL << ETH_MACDBGR_MTFCS_Pos) /*!< 0x00060000 */
#define ETH_MACDBGR_MTFCS ETH_MACDBGR_MTFCS_Msk                /* MAC transmit frame controller status mask                               */
#define ETH_MACDBGR_MTFCS_TRANSFERRING_Pos (17U)
#define ETH_MACDBGR_MTFCS_TRANSFERRING_Msk (0x3UL << ETH_MACDBGR_MTFCS_TRANSFERRING_Pos) /*!< 0x00060000 */
#define ETH_MACDBGR_MTFCS_TRANSFERRING ETH_MACDBGR_MTFCS_TRANSFERRING_Msk                /* Transferring input frame for transmission                               */
#define ETH_MACDBGR_MTFCS_GENERATINGPCF_Pos (18U)
#define ETH_MACDBGR_MTFCS_GENERATINGPCF_Msk (0x1UL << ETH_MACDBGR_MTFCS_GENERATINGPCF_Pos) /*!< 0x00040000 */
#define ETH_MACDBGR_MTFCS_GENERATINGPCF ETH_MACDBGR_MTFCS_GENERATINGPCF_Msk                /* Generating and transmitting a Pause control frame (in full duplex mode) */
#define ETH_MACDBGR_MTFCS_WAITING_Pos (17U)
#define ETH_MACDBGR_MTFCS_WAITING_Msk (0x1UL << ETH_MACDBGR_MTFCS_WAITING_Pos) /*!< 0x00020000 */
#define ETH_MACDBGR_MTFCS_WAITING ETH_MACDBGR_MTFCS_WAITING_Msk                /* Waiting for Status of previous frame or IFG/backoff period to be over   */
#define ETH_MACDBGR_MTFCS_IDLE 0x00000000U                                     /* Idle                                                                    */
#define ETH_MACDBGR_MMTEA_Pos (16U)
#define ETH_MACDBGR_MMTEA_Msk (0x1UL << ETH_MACDBGR_MMTEA_Pos) /*!< 0x00010000 */
#define ETH_MACDBGR_MMTEA ETH_MACDBGR_MMTEA_Msk                /* MAC MII transmit engine active                                          */
#define ETH_MACDBGR_RFFL_Pos (8U)
#define ETH_MACDBGR_RFFL_Msk (0x3UL << ETH_MACDBGR_RFFL_Pos) /*!< 0x00000300 */
#define ETH_MACDBGR_RFFL ETH_MACDBGR_RFFL_Msk                /* Rx FIFO fill level mask                                                 */
#define ETH_MACDBGR_RFFL_FULL_Pos (8U)
#define ETH_MACDBGR_RFFL_FULL_Msk (0x3UL << ETH_MACDBGR_RFFL_FULL_Pos) /*!< 0x00000300 */
#define ETH_MACDBGR_RFFL_FULL ETH_MACDBGR_RFFL_FULL_Msk                /* RxFIFO full                                                             */
#define ETH_MACDBGR_RFFL_ABOVEFCT_Pos (9U)
#define ETH_MACDBGR_RFFL_ABOVEFCT_Msk (0x1UL << ETH_MACDBGR_RFFL_ABOVEFCT_Pos) /*!< 0x00000200 */
#define ETH_MACDBGR_RFFL_ABOVEFCT ETH_MACDBGR_RFFL_ABOVEFCT_Msk                /* RxFIFO fill-level above flow-control activate threshold                 */
#define ETH_MACDBGR_RFFL_BELOWFCT_Pos (8U)
#define ETH_MACDBGR_RFFL_BELOWFCT_Msk (0x1UL << ETH_MACDBGR_RFFL_BELOWFCT_Pos) /*!< 0x00000100 */
#define ETH_MACDBGR_RFFL_BELOWFCT ETH_MACDBGR_RFFL_BELOWFCT_Msk                /* RxFIFO fill-level below flow-control de-activate threshold              */
#define ETH_MACDBGR_RFFL_EMPTY 0x00000000U                                     /* RxFIFO empty                                                            */
#define ETH_MACDBGR_RFRCS_Pos (5U)
#define ETH_MACDBGR_RFRCS_Msk (0x3UL << ETH_MACDBGR_RFRCS_Pos) /*!< 0x00000060 */
#define ETH_MACDBGR_RFRCS ETH_MACDBGR_RFRCS_Msk                /* Rx FIFO read controller status mask                                     */
#define ETH_MACDBGR_RFRCS_FLUSHING_Pos (5U)
#define ETH_MACDBGR_RFRCS_FLUSHING_Msk (0x3UL << ETH_MACDBGR_RFRCS_FLUSHING_Pos) /*!< 0x00000060 */
#define ETH_MACDBGR_RFRCS_FLUSHING ETH_MACDBGR_RFRCS_FLUSHING_Msk                /* Flushing the frame data and status                                      */
#define ETH_MACDBGR_RFRCS_STATUSREADING_Pos (6U)
#define ETH_MACDBGR_RFRCS_STATUSREADING_Msk (0x1UL << ETH_MACDBGR_RFRCS_STATUSREADING_Pos) /*!< 0x00000040 */
#define ETH_MACDBGR_RFRCS_STATUSREADING ETH_MACDBGR_RFRCS_STATUSREADING_Msk                /* Reading frame status (or time-stamp)                                    */
#define ETH_MACDBGR_RFRCS_DATAREADING_Pos (5U)
#define ETH_MACDBGR_RFRCS_DATAREADING_Msk (0x1UL << ETH_MACDBGR_RFRCS_DATAREADING_Pos) /*!< 0x00000020 */
#define ETH_MACDBGR_RFRCS_DATAREADING ETH_MACDBGR_RFRCS_DATAREADING_Msk                /* Reading frame data                                                      */
#define ETH_MACDBGR_RFRCS_IDLE 0x00000000U                                             /* IDLE state                                                              */
#define ETH_MACDBGR_RFWRA_Pos (4U)
#define ETH_MACDBGR_RFWRA_Msk (0x1UL << ETH_MACDBGR_RFWRA_Pos) /*!< 0x00000010 */
#define ETH_MACDBGR_RFWRA ETH_MACDBGR_RFWRA_Msk                /* Rx FIFO write controller active                                         */
#define ETH_MACDBGR_MSFRWCS_Pos (1U)
#define ETH_MACDBGR_MSFRWCS_Msk (0x3UL << ETH_MACDBGR_MSFRWCS_Pos) /*!< 0x00000006 */
#define ETH_MACDBGR_MSFRWCS ETH_MACDBGR_MSFRWCS_Msk                /* MAC small FIFO read / write controllers status  mask                    */
#define ETH_MACDBGR_MSFRWCS_1 (0x2UL << ETH_MACDBGR_MSFRWCS_Pos)   /*!< 0x00000004 */
#define ETH_MACDBGR_MSFRWCS_0 (0x1UL << ETH_MACDBGR_MSFRWCS_Pos)   /*!< 0x00000002 */
#define ETH_MACDBGR_MMRPEA_Pos (0U)
#define ETH_MACDBGR_MMRPEA_Msk (0x1UL << ETH_MACDBGR_MMRPEA_Pos) /*!< 0x00000001 */
#define ETH_MACDBGR_MMRPEA ETH_MACDBGR_MMRPEA_Msk                /* MAC MII receive protocol engine active                                  */

/* Bit definition for Ethernet MAC Status Register */
#define ETH_MACSR_TSTS_Pos (9U)
#define ETH_MACSR_TSTS_Msk (0x1UL << ETH_MACSR_TSTS_Pos) /*!< 0x00000200 */
#define ETH_MACSR_TSTS ETH_MACSR_TSTS_Msk                /* Time stamp trigger status */
#define ETH_MACSR_MMCTS_Pos (6U)
#define ETH_MACSR_MMCTS_Msk (0x1UL << ETH_MACSR_MMCTS_Pos) /*!< 0x00000040 */
#define ETH_MACSR_MMCTS ETH_MACSR_MMCTS_Msk                /* MMC transmit status       */
#define ETH_MACSR_MMMCRS_Pos (5U)
#define ETH_MACSR_MMMCRS_Msk (0x1UL << ETH_MACSR_MMMCRS_Pos) /*!< 0x00000020 */
#define ETH_MACSR_MMMCRS ETH_MACSR_MMMCRS_Msk                /* MMC receive status        */
#define ETH_MACSR_MMCS_Pos (4U)
#define ETH_MACSR_MMCS_Msk (0x1UL << ETH_MACSR_MMCS_Pos) /*!< 0x00000010 */
#define ETH_MACSR_MMCS ETH_MACSR_MMCS_Msk                /* MMC status                */
#define ETH_MACSR_PMTS_Pos (3U)
#define ETH_MACSR_PMTS_Msk (0x1UL << ETH_MACSR_PMTS_Pos) /*!< 0x00000008 */
#define ETH_MACSR_PMTS ETH_MACSR_PMTS_Msk                /* PMT status                */

/* Bit definition for Ethernet MAC Interrupt Mask Register */
#define ETH_MACIMR_TSTIM_Pos (9U)
#define ETH_MACIMR_TSTIM_Msk (0x1UL << ETH_MACIMR_TSTIM_Pos) /*!< 0x00000200 */
#define ETH_MACIMR_TSTIM ETH_MACIMR_TSTIM_Msk                /* Time stamp trigger interrupt mask */
#define ETH_MACIMR_PMTIM_Pos (3U)
#define ETH_MACIMR_PMTIM_Msk (0x1UL << ETH_MACIMR_PMTIM_Pos) /*!< 0x00000008 */
#define ETH_MACIMR_PMTIM ETH_MACIMR_PMTIM_Msk                /* PMT interrupt mask                */

/* Bit definition for Ethernet MAC Address0 High Register */
#define ETH_MACA0HR_MACA0H_Pos (0U)
#define ETH_MACA0HR_MACA0H_Msk (0xFFFFUL << ETH_MACA0HR_MACA0H_Pos) /*!< 0x0000FFFF */
#define ETH_MACA0HR_MACA0H ETH_MACA0HR_MACA0H_Msk                   /* MAC address0 high */

/* Bit definition for Ethernet MAC Address0 Low Register */
#define ETH_MACA0LR_MACA0L_Pos (0U)
#define ETH_MACA0LR_MACA0L_Msk (0xFFFFFFFFUL << ETH_MACA0LR_MACA0L_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACA0LR_MACA0L ETH_MACA0LR_MACA0L_Msk                       /* MAC address0 low */

/* Bit definition for Ethernet MAC Address1 High Register */
#define ETH_MACA1HR_AE_Pos (31U)
#define ETH_MACA1HR_AE_Msk (0x1UL << ETH_MACA1HR_AE_Pos) /*!< 0x80000000 */
#define ETH_MACA1HR_AE ETH_MACA1HR_AE_Msk                /* Address enable */
#define ETH_MACA1HR_SA_Pos (30U)
#define ETH_MACA1HR_SA_Msk (0x1UL << ETH_MACA1HR_SA_Pos) /*!< 0x40000000 */
#define ETH_MACA1HR_SA ETH_MACA1HR_SA_Msk                /* Source address */
#define ETH_MACA1HR_MBC_Pos (24U)
#define ETH_MACA1HR_MBC_Msk (0x3FUL << ETH_MACA1HR_MBC_Pos) /*!< 0x3F000000 */
#define ETH_MACA1HR_MBC ETH_MACA1HR_MBC_Msk                 /* Mask byte control: bits to mask for comparison of the MAC Address bytes */
#define ETH_MACA1HR_MBC_HBits15_8 0x20000000U               /* Mask MAC Address high reg bits [15:8] */
#define ETH_MACA1HR_MBC_HBits7_0 0x10000000U                /* Mask MAC Address high reg bits [7:0]  */
#define ETH_MACA1HR_MBC_LBits31_24 0x08000000U              /* Mask MAC Address low reg bits [31:24] */
#define ETH_MACA1HR_MBC_LBits23_16 0x04000000U              /* Mask MAC Address low reg bits [23:16] */
#define ETH_MACA1HR_MBC_LBits15_8 0x02000000U               /* Mask MAC Address low reg bits [15:8]  */
#define ETH_MACA1HR_MBC_LBits7_0 0x01000000U                /* Mask MAC Address low reg bits [7:0]   */
#define ETH_MACA1HR_MACA1H_Pos (0U)
#define ETH_MACA1HR_MACA1H_Msk (0xFFFFUL << ETH_MACA1HR_MACA1H_Pos) /*!< 0x0000FFFF */
#define ETH_MACA1HR_MACA1H ETH_MACA1HR_MACA1H_Msk                   /* MAC address1 high */

/* Bit definition for Ethernet MAC Address1 Low Register */
#define ETH_MACA1LR_MACA1L_Pos (0U)
#define ETH_MACA1LR_MACA1L_Msk (0xFFFFFFFFUL << ETH_MACA1LR_MACA1L_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACA1LR_MACA1L ETH_MACA1LR_MACA1L_Msk                       /* MAC address1 low */

/* Bit definition for Ethernet MAC Address2 High Register */
#define ETH_MACA2HR_AE_Pos (31U)
#define ETH_MACA2HR_AE_Msk (0x1UL << ETH_MACA2HR_AE_Pos) /*!< 0x80000000 */
#define ETH_MACA2HR_AE ETH_MACA2HR_AE_Msk                /* Address enable */
#define ETH_MACA2HR_SA_Pos (30U)
#define ETH_MACA2HR_SA_Msk (0x1UL << ETH_MACA2HR_SA_Pos) /*!< 0x40000000 */
#define ETH_MACA2HR_SA ETH_MACA2HR_SA_Msk                /* Source address */
#define ETH_MACA2HR_MBC_Pos (24U)
#define ETH_MACA2HR_MBC_Msk (0x3FUL << ETH_MACA2HR_MBC_Pos) /*!< 0x3F000000 */
#define ETH_MACA2HR_MBC ETH_MACA2HR_MBC_Msk                 /* Mask byte control */
#define ETH_MACA2HR_MBC_HBits15_8 0x20000000U               /* Mask MAC Address high reg bits [15:8] */
#define ETH_MACA2HR_MBC_HBits7_0 0x10000000U                /* Mask MAC Address high reg bits [7:0]  */
#define ETH_MACA2HR_MBC_LBits31_24 0x08000000U              /* Mask MAC Address low reg bits [31:24] */
#define ETH_MACA2HR_MBC_LBits23_16 0x04000000U              /* Mask MAC Address low reg bits [23:16] */
#define ETH_MACA2HR_MBC_LBits15_8 0x02000000U               /* Mask MAC Address low reg bits [15:8]  */
#define ETH_MACA2HR_MBC_LBits7_0 0x01000000U                /* Mask MAC Address low reg bits [70]    */
#define ETH_MACA2HR_MACA2H_Pos (0U)
#define ETH_MACA2HR_MACA2H_Msk (0xFFFFUL << ETH_MACA2HR_MACA2H_Pos) /*!< 0x0000FFFF */
#define ETH_MACA2HR_MACA2H ETH_MACA2HR_MACA2H_Msk                   /* MAC address1 high */

/* Bit definition for Ethernet MAC Address2 Low Register */
#define ETH_MACA2LR_MACA2L_Pos (0U)
#define ETH_MACA2LR_MACA2L_Msk (0xFFFFFFFFUL << ETH_MACA2LR_MACA2L_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACA2LR_MACA2L ETH_MACA2LR_MACA2L_Msk                       /* MAC address2 low */

/* Bit definition for Ethernet MAC Address3 High Register */
#define ETH_MACA3HR_AE_Pos (31U)
#define ETH_MACA3HR_AE_Msk (0x1UL << ETH_MACA3HR_AE_Pos) /*!< 0x80000000 */
#define ETH_MACA3HR_AE ETH_MACA3HR_AE_Msk                /* Address enable */
#define ETH_MACA3HR_SA_Pos (30U)
#define ETH_MACA3HR_SA_Msk (0x1UL << ETH_MACA3HR_SA_Pos) /*!< 0x40000000 */
#define ETH_MACA3HR_SA ETH_MACA3HR_SA_Msk                /* Source address */
#define ETH_MACA3HR_MBC_Pos (24U)
#define ETH_MACA3HR_MBC_Msk (0x3FUL << ETH_MACA3HR_MBC_Pos) /*!< 0x3F000000 */
#define ETH_MACA3HR_MBC ETH_MACA3HR_MBC_Msk                 /* Mask byte control */
#define ETH_MACA3HR_MBC_HBits15_8 0x20000000U               /* Mask MAC Address high reg bits [15:8] */
#define ETH_MACA3HR_MBC_HBits7_0 0x10000000U                /* Mask MAC Address high reg bits [7:0]  */
#define ETH_MACA3HR_MBC_LBits31_24 0x08000000U              /* Mask MAC Address low reg bits [31:24] */
#define ETH_MACA3HR_MBC_LBits23_16 0x04000000U              /* Mask MAC Address low reg bits [23:16] */
#define ETH_MACA3HR_MBC_LBits15_8 0x02000000U               /* Mask MAC Address low reg bits [15:8]  */
#define ETH_MACA3HR_MBC_LBits7_0 0x01000000U                /* Mask MAC Address low reg bits [70]    */
#define ETH_MACA3HR_MACA3H_Pos (0U)
#define ETH_MACA3HR_MACA3H_Msk (0xFFFFUL << ETH_MACA3HR_MACA3H_Pos) /*!< 0x0000FFFF */
#define ETH_MACA3HR_MACA3H ETH_MACA3HR_MACA3H_Msk                   /* MAC address3 high */

/* Bit definition for Ethernet MAC Address3 Low Register */
#define ETH_MACA3LR_MACA3L_Pos (0U)
#define ETH_MACA3LR_MACA3L_Msk (0xFFFFFFFFUL << ETH_MACA3LR_MACA3L_Pos) /*!< 0xFFFFFFFF */
#define ETH_MACA3LR_MACA3L ETH_MACA3LR_MACA3L_Msk                       /* MAC address3 low */

/******************************************************************************/
/*                Ethernet MMC Registers bits definition                      */
/******************************************************************************/

/* Bit definition for Ethernet MMC Contol Register */
#define ETH_MMCCR_MCFHP_Pos (5U)
#define ETH_MMCCR_MCFHP_Msk (0x1UL << ETH_MMCCR_MCFHP_Pos) /*!< 0x00000020 */
#define ETH_MMCCR_MCFHP ETH_MMCCR_MCFHP_Msk                /* MMC counter Full-Half preset */
#define ETH_MMCCR_MCP_Pos (4U)
#define ETH_MMCCR_MCP_Msk (0x1UL << ETH_MMCCR_MCP_Pos) /*!< 0x00000010 */
#define ETH_MMCCR_MCP ETH_MMCCR_MCP_Msk                /* MMC counter preset           */
#define ETH_MMCCR_MCF_Pos (3U)
#define ETH_MMCCR_MCF_Msk (0x1UL << ETH_MMCCR_MCF_Pos) /*!< 0x00000008 */
#define ETH_MMCCR_MCF ETH_MMCCR_MCF_Msk                /* MMC Counter Freeze           */
#define ETH_MMCCR_ROR_Pos (2U)
#define ETH_MMCCR_ROR_Msk (0x1UL << ETH_MMCCR_ROR_Pos) /*!< 0x00000004 */
#define ETH_MMCCR_ROR ETH_MMCCR_ROR_Msk                /* Reset on Read                */
#define ETH_MMCCR_CSR_Pos (1U)
#define ETH_MMCCR_CSR_Msk (0x1UL << ETH_MMCCR_CSR_Pos) /*!< 0x00000002 */
#define ETH_MMCCR_CSR ETH_MMCCR_CSR_Msk                /* Counter Stop Rollover        */
#define ETH_MMCCR_CR_Pos (0U)
#define ETH_MMCCR_CR_Msk (0x1UL << ETH_MMCCR_CR_Pos) /*!< 0x00000001 */
#define ETH_MMCCR_CR ETH_MMCCR_CR_Msk                /* Counters Reset               */

/* Bit definition for Ethernet MMC Receive Interrupt Register */
#define ETH_MMCRIR_RGUFS_Pos (17U)
#define ETH_MMCRIR_RGUFS_Msk (0x1UL << ETH_MMCRIR_RGUFS_Pos) /*!< 0x00020000 */
#define ETH_MMCRIR_RGUFS ETH_MMCRIR_RGUFS_Msk                /* Set when Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMCRIR_RFAES_Pos (6U)
#define ETH_MMCRIR_RFAES_Msk (0x1UL << ETH_MMCRIR_RFAES_Pos) /*!< 0x00000040 */
#define ETH_MMCRIR_RFAES ETH_MMCRIR_RFAES_Msk                /* Set when Rx alignment error counter reaches half the maximum value */
#define ETH_MMCRIR_RFCES_Pos (5U)
#define ETH_MMCRIR_RFCES_Msk (0x1UL << ETH_MMCRIR_RFCES_Pos) /*!< 0x00000020 */
#define ETH_MMCRIR_RFCES ETH_MMCRIR_RFCES_Msk                /* Set when Rx crc error counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmit Interrupt Register */
#define ETH_MMCTIR_TGFS_Pos (21U)
#define ETH_MMCTIR_TGFS_Msk (0x1UL << ETH_MMCTIR_TGFS_Pos) /*!< 0x00200000 */
#define ETH_MMCTIR_TGFS ETH_MMCTIR_TGFS_Msk                /* Set when Tx good frame count counter reaches half the maximum value */
#define ETH_MMCTIR_TGFMSCS_Pos (15U)
#define ETH_MMCTIR_TGFMSCS_Msk (0x1UL << ETH_MMCTIR_TGFMSCS_Pos) /*!< 0x00008000 */
#define ETH_MMCTIR_TGFMSCS ETH_MMCTIR_TGFMSCS_Msk                /* Set when Tx good multi col counter reaches half the maximum value */
#define ETH_MMCTIR_TGFSCS_Pos (14U)
#define ETH_MMCTIR_TGFSCS_Msk (0x1UL << ETH_MMCTIR_TGFSCS_Pos) /*!< 0x00004000 */
#define ETH_MMCTIR_TGFSCS ETH_MMCTIR_TGFSCS_Msk                /* Set when Tx good single col counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Receive Interrupt Mask Register */
#define ETH_MMCRIMR_RGUFM_Pos (17U)
#define ETH_MMCRIMR_RGUFM_Msk (0x1UL << ETH_MMCRIMR_RGUFM_Pos) /*!< 0x00020000 */
#define ETH_MMCRIMR_RGUFM ETH_MMCRIMR_RGUFM_Msk                /* Mask the interrupt when Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMCRIMR_RFAEM_Pos (6U)
#define ETH_MMCRIMR_RFAEM_Msk (0x1UL << ETH_MMCRIMR_RFAEM_Pos) /*!< 0x00000040 */
#define ETH_MMCRIMR_RFAEM ETH_MMCRIMR_RFAEM_Msk                /* Mask the interrupt when when Rx alignment error counter reaches half the maximum value */
#define ETH_MMCRIMR_RFCEM_Pos (5U)
#define ETH_MMCRIMR_RFCEM_Msk (0x1UL << ETH_MMCRIMR_RFCEM_Pos) /*!< 0x00000020 */
#define ETH_MMCRIMR_RFCEM ETH_MMCRIMR_RFCEM_Msk                /* Mask the interrupt when Rx crc error counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmit Interrupt Mask Register */
#define ETH_MMCTIMR_TGFM_Pos (21U)
#define ETH_MMCTIMR_TGFM_Msk (0x1UL << ETH_MMCTIMR_TGFM_Pos) /*!< 0x00200000 */
#define ETH_MMCTIMR_TGFM ETH_MMCTIMR_TGFM_Msk                /* Mask the interrupt when Tx good frame count counter reaches half the maximum value */
#define ETH_MMCTIMR_TGFMSCM_Pos (15U)
#define ETH_MMCTIMR_TGFMSCM_Msk (0x1UL << ETH_MMCTIMR_TGFMSCM_Pos) /*!< 0x00008000 */
#define ETH_MMCTIMR_TGFMSCM ETH_MMCTIMR_TGFMSCM_Msk                /* Mask the interrupt when Tx good multi col counter reaches half the maximum value */
#define ETH_MMCTIMR_TGFSCM_Pos (14U)
#define ETH_MMCTIMR_TGFSCM_Msk (0x1UL << ETH_MMCTIMR_TGFSCM_Pos) /*!< 0x00004000 */
#define ETH_MMCTIMR_TGFSCM ETH_MMCTIMR_TGFSCM_Msk                /* Mask the interrupt when Tx good single col counter reaches half the maximum value */

/* Bit definition for Ethernet MMC Transmitted Good Frames after Single Collision Counter Register */
#define ETH_MMCTGFSCCR_TGFSCC_Pos (0U)
#define ETH_MMCTGFSCCR_TGFSCC_Msk (0xFFFFFFFFUL << ETH_MMCTGFSCCR_TGFSCC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTGFSCCR_TGFSCC ETH_MMCTGFSCCR_TGFSCC_Msk                       /* Number of successfully transmitted frames after a single collision in Half-duplex mode. */

/* Bit definition for Ethernet MMC Transmitted Good Frames after More than a Single Collision Counter Register */
#define ETH_MMCTGFMSCCR_TGFMSCC_Pos (0U)
#define ETH_MMCTGFMSCCR_TGFMSCC_Msk (0xFFFFFFFFUL << ETH_MMCTGFMSCCR_TGFMSCC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTGFMSCCR_TGFMSCC ETH_MMCTGFMSCCR_TGFMSCC_Msk                       /* Number of successfully transmitted frames after more than a single collision in Half-duplex mode. */

/* Bit definition for Ethernet MMC Transmitted Good Frames Counter Register */
#define ETH_MMCTGFCR_TGFC_Pos (0U)
#define ETH_MMCTGFCR_TGFC_Msk (0xFFFFFFFFUL << ETH_MMCTGFCR_TGFC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCTGFCR_TGFC ETH_MMCTGFCR_TGFC_Msk                       /* Number of good frames transmitted. */

/* Bit definition for Ethernet MMC Received Frames with CRC Error Counter Register */
#define ETH_MMCRFCECR_RFCEC_Pos (0U)
#define ETH_MMCRFCECR_RFCEC_Msk (0xFFFFFFFFUL << ETH_MMCRFCECR_RFCEC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRFCECR_RFCEC ETH_MMCRFCECR_RFCEC_Msk                       /* Number of frames received with CRC error. */

/* Bit definition for Ethernet MMC Received Frames with Alignement Error Counter Register */
#define ETH_MMCRFAECR_RFAEC_Pos (0U)
#define ETH_MMCRFAECR_RFAEC_Msk (0xFFFFFFFFUL << ETH_MMCRFAECR_RFAEC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRFAECR_RFAEC ETH_MMCRFAECR_RFAEC_Msk                       /* Number of frames received with alignment (dribble) error */

/* Bit definition for Ethernet MMC Received Good Unicast Frames Counter Register */
#define ETH_MMCRGUFCR_RGUFC_Pos (0U)
#define ETH_MMCRGUFCR_RGUFC_Msk (0xFFFFFFFFUL << ETH_MMCRGUFCR_RGUFC_Pos) /*!< 0xFFFFFFFF */
#define ETH_MMCRGUFCR_RGUFC ETH_MMCRGUFCR_RGUFC_Msk                       /* Number of good unicast frames received. */

/******************************************************************************/
/*               Ethernet PTP Registers bits definition                       */
/******************************************************************************/

/* Bit definition for Ethernet PTP Time Stamp Contol Register */
#define ETH_PTPTSCR_TSCNT_Pos (16U)
#define ETH_PTPTSCR_TSCNT_Msk (0x3UL << ETH_PTPTSCR_TSCNT_Pos) /*!< 0x00030000 */
#define ETH_PTPTSCR_TSCNT ETH_PTPTSCR_TSCNT_Msk                /* Time stamp clock node type */
#define ETH_PTPTSSR_TSSMRME_Pos (15U)
#define ETH_PTPTSSR_TSSMRME_Msk (0x1UL << ETH_PTPTSSR_TSSMRME_Pos) /*!< 0x00008000 */
#define ETH_PTPTSSR_TSSMRME ETH_PTPTSSR_TSSMRME_Msk                /* Time stamp snapshot for message relevant to master enable */
#define ETH_PTPTSSR_TSSEME_Pos (14U)
#define ETH_PTPTSSR_TSSEME_Msk (0x1UL << ETH_PTPTSSR_TSSEME_Pos) /*!< 0x00004000 */
#define ETH_PTPTSSR_TSSEME ETH_PTPTSSR_TSSEME_Msk                /* Time stamp snapshot for event message enable */
#define ETH_PTPTSSR_TSSIPV4FE_Pos (13U)
#define ETH_PTPTSSR_TSSIPV4FE_Msk (0x1UL << ETH_PTPTSSR_TSSIPV4FE_Pos) /*!< 0x00002000 */
#define ETH_PTPTSSR_TSSIPV4FE ETH_PTPTSSR_TSSIPV4FE_Msk                /* Time stamp snapshot for IPv4 frames enable */
#define ETH_PTPTSSR_TSSIPV6FE_Pos (12U)
#define ETH_PTPTSSR_TSSIPV6FE_Msk (0x1UL << ETH_PTPTSSR_TSSIPV6FE_Pos) /*!< 0x00001000 */
#define ETH_PTPTSSR_TSSIPV6FE ETH_PTPTSSR_TSSIPV6FE_Msk                /* Time stamp snapshot for IPv6 frames enable */
#define ETH_PTPTSSR_TSSPTPOEFE_Pos (11U)
#define ETH_PTPTSSR_TSSPTPOEFE_Msk (0x1UL << ETH_PTPTSSR_TSSPTPOEFE_Pos) /*!< 0x00000800 */
#define ETH_PTPTSSR_TSSPTPOEFE ETH_PTPTSSR_TSSPTPOEFE_Msk                /* Time stamp snapshot for PTP over ethernet frames enable */
#define ETH_PTPTSSR_TSPTPPSV2E_Pos (10U)
#define ETH_PTPTSSR_TSPTPPSV2E_Msk (0x1UL << ETH_PTPTSSR_TSPTPPSV2E_Pos) /*!< 0x00000400 */
#define ETH_PTPTSSR_TSPTPPSV2E ETH_PTPTSSR_TSPTPPSV2E_Msk                /* Time stamp PTP packet snooping for version2 format enable */
#define ETH_PTPTSSR_TSSSR_Pos (9U)
#define ETH_PTPTSSR_TSSSR_Msk (0x1UL << ETH_PTPTSSR_TSSSR_Pos) /*!< 0x00000200 */
#define ETH_PTPTSSR_TSSSR ETH_PTPTSSR_TSSSR_Msk                /* Time stamp Sub-seconds rollover */
#define ETH_PTPTSSR_TSSARFE_Pos (8U)
#define ETH_PTPTSSR_TSSARFE_Msk (0x1UL << ETH_PTPTSSR_TSSARFE_Pos) /*!< 0x00000100 */
#define ETH_PTPTSSR_TSSARFE ETH_PTPTSSR_TSSARFE_Msk                /* Time stamp snapshot for all received frames enable */

#define ETH_PTPTSCR_TSARU_Pos (5U)
#define ETH_PTPTSCR_TSARU_Msk (0x1UL << ETH_PTPTSCR_TSARU_Pos) /*!< 0x00000020 */
#define ETH_PTPTSCR_TSARU ETH_PTPTSCR_TSARU_Msk                /* Addend register update */
#define ETH_PTPTSCR_TSITE_Pos (4U)
#define ETH_PTPTSCR_TSITE_Msk (0x1UL << ETH_PTPTSCR_TSITE_Pos) /*!< 0x00000010 */
#define ETH_PTPTSCR_TSITE ETH_PTPTSCR_TSITE_Msk                /* Time stamp interrupt trigger enable */
#define ETH_PTPTSCR_TSSTU_Pos (3U)
#define ETH_PTPTSCR_TSSTU_Msk (0x1UL << ETH_PTPTSCR_TSSTU_Pos) /*!< 0x00000008 */
#define ETH_PTPTSCR_TSSTU ETH_PTPTSCR_TSSTU_Msk                /* Time stamp update */
#define ETH_PTPTSCR_TSSTI_Pos (2U)
#define ETH_PTPTSCR_TSSTI_Msk (0x1UL << ETH_PTPTSCR_TSSTI_Pos) /*!< 0x00000004 */
#define ETH_PTPTSCR_TSSTI ETH_PTPTSCR_TSSTI_Msk                /* Time stamp initialize */
#define ETH_PTPTSCR_TSFCU_Pos (1U)
#define ETH_PTPTSCR_TSFCU_Msk (0x1UL << ETH_PTPTSCR_TSFCU_Pos) /*!< 0x00000002 */
#define ETH_PTPTSCR_TSFCU ETH_PTPTSCR_TSFCU_Msk                /* Time stamp fine or coarse update */
#define ETH_PTPTSCR_TSE_Pos (0U)
#define ETH_PTPTSCR_TSE_Msk (0x1UL << ETH_PTPTSCR_TSE_Pos) /*!< 0x00000001 */
#define ETH_PTPTSCR_TSE ETH_PTPTSCR_TSE_Msk                /* Time stamp enable */

/* Bit definition for Ethernet PTP Sub-Second Increment Register */
#define ETH_PTPSSIR_STSSI_Pos (0U)
#define ETH_PTPSSIR_STSSI_Msk (0xFFUL << ETH_PTPSSIR_STSSI_Pos) /*!< 0x000000FF */
#define ETH_PTPSSIR_STSSI ETH_PTPSSIR_STSSI_Msk                 /* System time Sub-second increment value */

/* Bit definition for Ethernet PTP Time Stamp High Register */
#define ETH_PTPTSHR_STS_Pos (0U)
#define ETH_PTPTSHR_STS_Msk (0xFFFFFFFFUL << ETH_PTPTSHR_STS_Pos) /*!< 0xFFFFFFFF */
#define ETH_PTPTSHR_STS ETH_PTPTSHR_STS_Msk                       /* System Time second */

/* Bit definition for Ethernet PTP Time Stamp Low Register */
#define ETH_PTPTSLR_STPNS_Pos (31U)
#define ETH_PTPTSLR_STPNS_Msk (0x1UL << ETH_PTPTSLR_STPNS_Pos) /*!< 0x80000000 */
#define ETH_PTPTSLR_STPNS ETH_PTPTSLR_STPNS_Msk                /* System Time Positive or negative time */
#define ETH_PTPTSLR_STSS_Pos (0U)
#define ETH_PTPTSLR_STSS_Msk (0x7FFFFFFFUL << ETH_PTPTSLR_STSS_Pos) /*!< 0x7FFFFFFF */
#define ETH_PTPTSLR_STSS ETH_PTPTSLR_STSS_Msk                       /* System Time sub-seconds */

/* Bit definition for Ethernet PTP Time Stamp High Update Register */
#define ETH_PTPTSHUR_TSUS_Pos (0U)
#define ETH_PTPTSHUR_TSUS_Msk (0xFFFFFFFFUL << ETH_PTPTSHUR_TSUS_Pos) /*!< 0xFFFFFFFF */
#define ETH_PTPTSHUR_TSUS ETH_PTPTSHUR_TSUS_Msk                       /* Time stamp update seconds */

/* Bit definition for Ethernet PTP Time Stamp Low Update Register */
#define ETH_PTPTSLUR_TSUPNS_Pos (31U)
#define ETH_PTPTSLUR_TSUPNS_Msk (0x1UL << ETH_PTPTSLUR_TSUPNS_Pos) /*!< 0x80000000 */
#define ETH_PTPTSLUR_TSUPNS ETH_PTPTSLUR_TSUPNS_Msk                /* Time stamp update Positive or negative time */
#define ETH_PTPTSLUR_TSUSS_Pos (0U)
#define ETH_PTPTSLUR_TSUSS_Msk (0x7FFFFFFFUL << ETH_PTPTSLUR_TSUSS_Pos) /*!< 0x7FFFFFFF */
#define ETH_PTPTSLUR_TSUSS ETH_PTPTSLUR_TSUSS_Msk                       /* Time stamp update sub-seconds */

/* Bit definition for Ethernet PTP Time Stamp Addend Register */
#define ETH_PTPTSAR_TSA_Pos (0U)
#define ETH_PTPTSAR_TSA_Msk (0xFFFFFFFFUL << ETH_PTPTSAR_TSA_Pos) /*!< 0xFFFFFFFF */
#define ETH_PTPTSAR_TSA ETH_PTPTSAR_TSA_Msk                       /* Time stamp addend */

/* Bit definition for Ethernet PTP Target Time High Register */
#define ETH_PTPTTHR_TTSH_Pos (0U)
#define ETH_PTPTTHR_TTSH_Msk (0xFFFFFFFFUL << ETH_PTPTTHR_TTSH_Pos) /*!< 0xFFFFFFFF */
#define ETH_PTPTTHR_TTSH ETH_PTPTTHR_TTSH_Msk                       /* Target time stamp high */

/* Bit definition for Ethernet PTP Target Time Low Register */
#define ETH_PTPTTLR_TTSL_Pos (0U)
#define ETH_PTPTTLR_TTSL_Msk (0xFFFFFFFFUL << ETH_PTPTTLR_TTSL_Pos) /*!< 0xFFFFFFFF */
#define ETH_PTPTTLR_TTSL ETH_PTPTTLR_TTSL_Msk                       /* Target time stamp low */

/* Bit definition for Ethernet PTP Time Stamp Status Register */
#define ETH_PTPTSSR_TSTTR_Pos (5U)
#define ETH_PTPTSSR_TSTTR_Msk (0x1UL << ETH_PTPTSSR_TSTTR_Pos) /*!< 0x00000020 */
#define ETH_PTPTSSR_TSTTR ETH_PTPTSSR_TSTTR_Msk                /* Time stamp target time reached */
#define ETH_PTPTSSR_TSSO_Pos (4U)
#define ETH_PTPTSSR_TSSO_Msk (0x1UL << ETH_PTPTSSR_TSSO_Pos) /*!< 0x00000010 */
#define ETH_PTPTSSR_TSSO ETH_PTPTSSR_TSSO_Msk                /* Time stamp seconds overflow */

/******************************************************************************/
/*                 Ethernet DMA Registers bits definition                     */
/******************************************************************************/

/* Bit definition for Ethernet DMA Bus Mode Register */
#define ETH_DMABMR_AAB_Pos (25U)
#define ETH_DMABMR_AAB_Msk (0x1UL << ETH_DMABMR_AAB_Pos) /*!< 0x02000000 */
#define ETH_DMABMR_AAB ETH_DMABMR_AAB_Msk                /* Address-Aligned beats */
#define ETH_DMABMR_FPM_Pos (24U)
#define ETH_DMABMR_FPM_Msk (0x1UL << ETH_DMABMR_FPM_Pos) /*!< 0x01000000 */
#define ETH_DMABMR_FPM ETH_DMABMR_FPM_Msk                /* 4xPBL mode */
#define ETH_DMABMR_USP_Pos (23U)
#define ETH_DMABMR_USP_Msk (0x1UL << ETH_DMABMR_USP_Pos) /*!< 0x00800000 */
#define ETH_DMABMR_USP ETH_DMABMR_USP_Msk                /* Use separate PBL */
#define ETH_DMABMR_RDP_Pos (17U)
#define ETH_DMABMR_RDP_Msk (0x3FUL << ETH_DMABMR_RDP_Pos) /*!< 0x007E0000 */
#define ETH_DMABMR_RDP ETH_DMABMR_RDP_Msk                 /* RxDMA PBL */
#define ETH_DMABMR_RDP_1Beat 0x00020000U                  /* maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_DMABMR_RDP_2Beat 0x00040000U                  /* maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_DMABMR_RDP_4Beat 0x00080000U                  /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_DMABMR_RDP_8Beat 0x00100000U                  /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMABMR_RDP_16Beat 0x00200000U                 /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMABMR_RDP_32Beat 0x00400000U                 /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMABMR_RDP_4xPBL_4Beat 0x01020000U            /* maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_DMABMR_RDP_4xPBL_8Beat 0x01040000U            /* maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_DMABMR_RDP_4xPBL_16Beat 0x01080000U           /* maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_DMABMR_RDP_4xPBL_32Beat 0x01100000U           /* maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_DMABMR_RDP_4xPBL_64Beat 0x01200000U           /* maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_DMABMR_RDP_4xPBL_128Beat 0x01400000U          /* maximum number of beats to be transferred in one RxDMA transaction is 128 */
#define ETH_DMABMR_FB_Pos (16U)
#define ETH_DMABMR_FB_Msk (0x1UL << ETH_DMABMR_FB_Pos) /*!< 0x00010000 */
#define ETH_DMABMR_FB ETH_DMABMR_FB_Msk                /* Fixed Burst */
#define ETH_DMABMR_RTPR_Pos (14U)
#define ETH_DMABMR_RTPR_Msk (0x3UL << ETH_DMABMR_RTPR_Pos) /*!< 0x0000C000 */
#define ETH_DMABMR_RTPR ETH_DMABMR_RTPR_Msk                /* Rx Tx priority ratio */
#define ETH_DMABMR_RTPR_1_1 0x00000000U                    /* Rx Tx priority ratio */
#define ETH_DMABMR_RTPR_2_1 0x00004000U                    /* Rx Tx priority ratio */
#define ETH_DMABMR_RTPR_3_1 0x00008000U                    /* Rx Tx priority ratio */
#define ETH_DMABMR_RTPR_4_1 0x0000C000U                    /* Rx Tx priority ratio */
#define ETH_DMABMR_PBL_Pos (8U)
#define ETH_DMABMR_PBL_Msk (0x3FUL << ETH_DMABMR_PBL_Pos) /*!< 0x00003F00 */
#define ETH_DMABMR_PBL ETH_DMABMR_PBL_Msk                 /* Programmable burst length */
#define ETH_DMABMR_PBL_1Beat 0x00000100U                  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_DMABMR_PBL_2Beat 0x00000200U                  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_DMABMR_PBL_4Beat 0x00000400U                  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_DMABMR_PBL_8Beat 0x00000800U                  /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMABMR_PBL_16Beat 0x00001000U                 /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMABMR_PBL_32Beat 0x00002000U                 /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMABMR_PBL_4xPBL_4Beat 0x01000100U            /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_DMABMR_PBL_4xPBL_8Beat 0x01000200U            /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_DMABMR_PBL_4xPBL_16Beat 0x01000400U           /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_DMABMR_PBL_4xPBL_32Beat 0x01000800U           /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_DMABMR_PBL_4xPBL_64Beat 0x01001000U           /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_DMABMR_PBL_4xPBL_128Beat 0x01002000U          /* maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */
#define ETH_DMABMR_EDE_Pos (7U)
#define ETH_DMABMR_EDE_Msk (0x1UL << ETH_DMABMR_EDE_Pos) /*!< 0x00000080 */
#define ETH_DMABMR_EDE ETH_DMABMR_EDE_Msk                /* Enhanced Descriptor Enable */
#define ETH_DMABMR_DSL_Pos (2U)
#define ETH_DMABMR_DSL_Msk (0x1FUL << ETH_DMABMR_DSL_Pos) /*!< 0x0000007C */
#define ETH_DMABMR_DSL ETH_DMABMR_DSL_Msk                 /* Descriptor Skip Length */
#define ETH_DMABMR_DA_Pos (1U)
#define ETH_DMABMR_DA_Msk (0x1UL << ETH_DMABMR_DA_Pos) /*!< 0x00000002 */
#define ETH_DMABMR_DA ETH_DMABMR_DA_Msk                /* DMA arbitration scheme */
#define ETH_DMABMR_SR_Pos (0U)
#define ETH_DMABMR_SR_Msk (0x1UL << ETH_DMABMR_SR_Pos) /*!< 0x00000001 */
#define ETH_DMABMR_SR ETH_DMABMR_SR_Msk                /* Software reset */

/* Bit definition for Ethernet DMA Transmit Poll Demand Register */
#define ETH_DMATPDR_TPD_Pos (0U)
#define ETH_DMATPDR_TPD_Msk (0xFFFFFFFFUL << ETH_DMATPDR_TPD_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMATPDR_TPD ETH_DMATPDR_TPD_Msk                       /* Transmit poll demand */

/* Bit definition for Ethernet DMA Receive Poll Demand Register */
#define ETH_DMARPDR_RPD_Pos (0U)
#define ETH_DMARPDR_RPD_Msk (0xFFFFFFFFUL << ETH_DMARPDR_RPD_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMARPDR_RPD ETH_DMARPDR_RPD_Msk                       /* Receive poll demand  */

/* Bit definition for Ethernet DMA Receive Descriptor List Address Register */
#define ETH_DMARDLAR_SRL_Pos (0U)
#define ETH_DMARDLAR_SRL_Msk (0xFFFFFFFFUL << ETH_DMARDLAR_SRL_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMARDLAR_SRL ETH_DMARDLAR_SRL_Msk                       /* Start of receive list */

/* Bit definition for Ethernet DMA Transmit Descriptor List Address Register */
#define ETH_DMATDLAR_STL_Pos (0U)
#define ETH_DMATDLAR_STL_Msk (0xFFFFFFFFUL << ETH_DMATDLAR_STL_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMATDLAR_STL ETH_DMATDLAR_STL_Msk                       /* Start of transmit list */

/* Bit definition for Ethernet DMA Status Register */
#define ETH_DMASR_TSTS_Pos (29U)
#define ETH_DMASR_TSTS_Msk (0x1UL << ETH_DMASR_TSTS_Pos) /*!< 0x20000000 */
#define ETH_DMASR_TSTS ETH_DMASR_TSTS_Msk                /* Time-stamp trigger status */
#define ETH_DMASR_PMTS_Pos (28U)
#define ETH_DMASR_PMTS_Msk (0x1UL << ETH_DMASR_PMTS_Pos) /*!< 0x10000000 */
#define ETH_DMASR_PMTS ETH_DMASR_PMTS_Msk                /* PMT status */
#define ETH_DMASR_MMCS_Pos (27U)
#define ETH_DMASR_MMCS_Msk (0x1UL << ETH_DMASR_MMCS_Pos) /*!< 0x08000000 */
#define ETH_DMASR_MMCS ETH_DMASR_MMCS_Msk                /* MMC status */
#define ETH_DMASR_EBS_Pos (23U)
#define ETH_DMASR_EBS_Msk (0x7UL << ETH_DMASR_EBS_Pos) /*!< 0x03800000 */
#define ETH_DMASR_EBS ETH_DMASR_EBS_Msk                /* Error bits status */
                                                       /* combination with EBS[2:0] for GetFlagStatus function */
#define ETH_DMASR_EBS_DescAccess_Pos (25U)
#define ETH_DMASR_EBS_DescAccess_Msk (0x1UL << ETH_DMASR_EBS_DescAccess_Pos) /*!< 0x02000000 */
#define ETH_DMASR_EBS_DescAccess ETH_DMASR_EBS_DescAccess_Msk                /* Error bits 0-data buffer, 1-desc. access */
#define ETH_DMASR_EBS_ReadTransf_Pos (24U)
#define ETH_DMASR_EBS_ReadTransf_Msk (0x1UL << ETH_DMASR_EBS_ReadTransf_Pos) /*!< 0x01000000 */
#define ETH_DMASR_EBS_ReadTransf ETH_DMASR_EBS_ReadTransf_Msk                /* Error bits 0-write trnsf, 1-read transfr */
#define ETH_DMASR_EBS_DataTransfTx_Pos (23U)
#define ETH_DMASR_EBS_DataTransfTx_Msk (0x1UL << ETH_DMASR_EBS_DataTransfTx_Pos) /*!< 0x00800000 */
#define ETH_DMASR_EBS_DataTransfTx ETH_DMASR_EBS_DataTransfTx_Msk                /* Error bits 0-Rx DMA, 1-Tx DMA */
#define ETH_DMASR_TPS_Pos (20U)
#define ETH_DMASR_TPS_Msk (0x7UL << ETH_DMASR_TPS_Pos) /*!< 0x00700000 */
#define ETH_DMASR_TPS ETH_DMASR_TPS_Msk                /* Transmit process state */
#define ETH_DMASR_TPS_Stopped 0x00000000U              /* Stopped - Reset or Stop Tx Command issued  */
#define ETH_DMASR_TPS_Fetching_Pos (20U)
#define ETH_DMASR_TPS_Fetching_Msk (0x1UL << ETH_DMASR_TPS_Fetching_Pos) /*!< 0x00100000 */
#define ETH_DMASR_TPS_Fetching ETH_DMASR_TPS_Fetching_Msk                /* Running - fetching the Tx descriptor */
#define ETH_DMASR_TPS_Waiting_Pos (21U)
#define ETH_DMASR_TPS_Waiting_Msk (0x1UL << ETH_DMASR_TPS_Waiting_Pos) /*!< 0x00200000 */
#define ETH_DMASR_TPS_Waiting ETH_DMASR_TPS_Waiting_Msk                /* Running - waiting for status */
#define ETH_DMASR_TPS_Reading_Pos (20U)
#define ETH_DMASR_TPS_Reading_Msk (0x3UL << ETH_DMASR_TPS_Reading_Pos) /*!< 0x00300000 */
#define ETH_DMASR_TPS_Reading ETH_DMASR_TPS_Reading_Msk                /* Running - reading the data from host memory */
#define ETH_DMASR_TPS_Suspended_Pos (21U)
#define ETH_DMASR_TPS_Suspended_Msk (0x3UL << ETH_DMASR_TPS_Suspended_Pos) /*!< 0x00600000 */
#define ETH_DMASR_TPS_Suspended ETH_DMASR_TPS_Suspended_Msk                /* Suspended - Tx Descriptor unavailabe */
#define ETH_DMASR_TPS_Closing_Pos (20U)
#define ETH_DMASR_TPS_Closing_Msk (0x7UL << ETH_DMASR_TPS_Closing_Pos) /*!< 0x00700000 */
#define ETH_DMASR_TPS_Closing ETH_DMASR_TPS_Closing_Msk                /* Running - closing Rx descriptor */
#define ETH_DMASR_RPS_Pos (17U)
#define ETH_DMASR_RPS_Msk (0x7UL << ETH_DMASR_RPS_Pos) /*!< 0x000E0000 */
#define ETH_DMASR_RPS ETH_DMASR_RPS_Msk                /* Receive process state */
#define ETH_DMASR_RPS_Stopped 0x00000000U              /* Stopped - Reset or Stop Rx Command issued */
#define ETH_DMASR_RPS_Fetching_Pos (17U)
#define ETH_DMASR_RPS_Fetching_Msk (0x1UL << ETH_DMASR_RPS_Fetching_Pos) /*!< 0x00020000 */
#define ETH_DMASR_RPS_Fetching ETH_DMASR_RPS_Fetching_Msk                /* Running - fetching the Rx descriptor */
#define ETH_DMASR_RPS_Waiting_Pos (17U)
#define ETH_DMASR_RPS_Waiting_Msk (0x3UL << ETH_DMASR_RPS_Waiting_Pos) /*!< 0x00060000 */
#define ETH_DMASR_RPS_Waiting ETH_DMASR_RPS_Waiting_Msk                /* Running - waiting for packet */
#define ETH_DMASR_RPS_Suspended_Pos (19U)
#define ETH_DMASR_RPS_Suspended_Msk (0x1UL << ETH_DMASR_RPS_Suspended_Pos) /*!< 0x00080000 */
#define ETH_DMASR_RPS_Suspended ETH_DMASR_RPS_Suspended_Msk                /* Suspended - Rx Descriptor unavailable */
#define ETH_DMASR_RPS_Closing_Pos (17U)
#define ETH_DMASR_RPS_Closing_Msk (0x5UL << ETH_DMASR_RPS_Closing_Pos) /*!< 0x000A0000 */
#define ETH_DMASR_RPS_Closing ETH_DMASR_RPS_Closing_Msk                /* Running - closing descriptor */
#define ETH_DMASR_RPS_Queuing_Pos (17U)
#define ETH_DMASR_RPS_Queuing_Msk (0x7UL << ETH_DMASR_RPS_Queuing_Pos) /*!< 0x000E0000 */
#define ETH_DMASR_RPS_Queuing ETH_DMASR_RPS_Queuing_Msk                /* Running - queuing the recieve frame into host memory */
#define ETH_DMASR_NIS_Pos (16U)
#define ETH_DMASR_NIS_Msk (0x1UL << ETH_DMASR_NIS_Pos) /*!< 0x00010000 */
#define ETH_DMASR_NIS ETH_DMASR_NIS_Msk                /* Normal interrupt summary */
#define ETH_DMASR_AIS_Pos (15U)
#define ETH_DMASR_AIS_Msk (0x1UL << ETH_DMASR_AIS_Pos) /*!< 0x00008000 */
#define ETH_DMASR_AIS ETH_DMASR_AIS_Msk                /* Abnormal interrupt summary */
#define ETH_DMASR_ERS_Pos (14U)
#define ETH_DMASR_ERS_Msk (0x1UL << ETH_DMASR_ERS_Pos) /*!< 0x00004000 */
#define ETH_DMASR_ERS ETH_DMASR_ERS_Msk                /* Early receive status */
#define ETH_DMASR_FBES_Pos (13U)
#define ETH_DMASR_FBES_Msk (0x1UL << ETH_DMASR_FBES_Pos) /*!< 0x00002000 */
#define ETH_DMASR_FBES ETH_DMASR_FBES_Msk                /* Fatal bus error status */
#define ETH_DMASR_ETS_Pos (10U)
#define ETH_DMASR_ETS_Msk (0x1UL << ETH_DMASR_ETS_Pos) /*!< 0x00000400 */
#define ETH_DMASR_ETS ETH_DMASR_ETS_Msk                /* Early transmit status */
#define ETH_DMASR_RWTS_Pos (9U)
#define ETH_DMASR_RWTS_Msk (0x1UL << ETH_DMASR_RWTS_Pos) /*!< 0x00000200 */
#define ETH_DMASR_RWTS ETH_DMASR_RWTS_Msk                /* Receive watchdog timeout status */
#define ETH_DMASR_RPSS_Pos (8U)
#define ETH_DMASR_RPSS_Msk (0x1UL << ETH_DMASR_RPSS_Pos) /*!< 0x00000100 */
#define ETH_DMASR_RPSS ETH_DMASR_RPSS_Msk                /* Receive process stopped status */
#define ETH_DMASR_RBUS_Pos (7U)
#define ETH_DMASR_RBUS_Msk (0x1UL << ETH_DMASR_RBUS_Pos) /*!< 0x00000080 */
#define ETH_DMASR_RBUS ETH_DMASR_RBUS_Msk                /* Receive buffer unavailable status */
#define ETH_DMASR_RS_Pos (6U)
#define ETH_DMASR_RS_Msk (0x1UL << ETH_DMASR_RS_Pos) /*!< 0x00000040 */
#define ETH_DMASR_RS ETH_DMASR_RS_Msk                /* Receive status */
#define ETH_DMASR_TUS_Pos (5U)
#define ETH_DMASR_TUS_Msk (0x1UL << ETH_DMASR_TUS_Pos) /*!< 0x00000020 */
#define ETH_DMASR_TUS ETH_DMASR_TUS_Msk                /* Transmit underflow status */
#define ETH_DMASR_ROS_Pos (4U)
#define ETH_DMASR_ROS_Msk (0x1UL << ETH_DMASR_ROS_Pos) /*!< 0x00000010 */
#define ETH_DMASR_ROS ETH_DMASR_ROS_Msk                /* Receive overflow status */
#define ETH_DMASR_TJTS_Pos (3U)
#define ETH_DMASR_TJTS_Msk (0x1UL << ETH_DMASR_TJTS_Pos) /*!< 0x00000008 */
#define ETH_DMASR_TJTS ETH_DMASR_TJTS_Msk                /* Transmit jabber timeout status */
#define ETH_DMASR_TBUS_Pos (2U)
#define ETH_DMASR_TBUS_Msk (0x1UL << ETH_DMASR_TBUS_Pos) /*!< 0x00000004 */
#define ETH_DMASR_TBUS ETH_DMASR_TBUS_Msk                /* Transmit buffer unavailable status */
#define ETH_DMASR_TPSS_Pos (1U)
#define ETH_DMASR_TPSS_Msk (0x1UL << ETH_DMASR_TPSS_Pos) /*!< 0x00000002 */
#define ETH_DMASR_TPSS ETH_DMASR_TPSS_Msk                /* Transmit process stopped status */
#define ETH_DMASR_TS_Pos (0U)
#define ETH_DMASR_TS_Msk (0x1UL << ETH_DMASR_TS_Pos) /*!< 0x00000001 */
#define ETH_DMASR_TS ETH_DMASR_TS_Msk                /* Transmit status */

/* Bit definition for Ethernet DMA Operation Mode Register */
#define ETH_DMAOMR_DTCEFD_Pos (26U)
#define ETH_DMAOMR_DTCEFD_Msk (0x1UL << ETH_DMAOMR_DTCEFD_Pos) /*!< 0x04000000 */
#define ETH_DMAOMR_DTCEFD ETH_DMAOMR_DTCEFD_Msk                /* Disable Dropping of TCP/IP checksum error frames */
#define ETH_DMAOMR_RSF_Pos (25U)
#define ETH_DMAOMR_RSF_Msk (0x1UL << ETH_DMAOMR_RSF_Pos) /*!< 0x02000000 */
#define ETH_DMAOMR_RSF ETH_DMAOMR_RSF_Msk                /* Receive store and forward */
#define ETH_DMAOMR_DFRF_Pos (24U)
#define ETH_DMAOMR_DFRF_Msk (0x1UL << ETH_DMAOMR_DFRF_Pos) /*!< 0x01000000 */
#define ETH_DMAOMR_DFRF ETH_DMAOMR_DFRF_Msk                /* Disable flushing of received frames */
#define ETH_DMAOMR_TSF_Pos (21U)
#define ETH_DMAOMR_TSF_Msk (0x1UL << ETH_DMAOMR_TSF_Pos) /*!< 0x00200000 */
#define ETH_DMAOMR_TSF ETH_DMAOMR_TSF_Msk                /* Transmit store and forward */
#define ETH_DMAOMR_FTF_Pos (20U)
#define ETH_DMAOMR_FTF_Msk (0x1UL << ETH_DMAOMR_FTF_Pos) /*!< 0x00100000 */
#define ETH_DMAOMR_FTF ETH_DMAOMR_FTF_Msk                /* Flush transmit FIFO */
#define ETH_DMAOMR_TTC_Pos (14U)
#define ETH_DMAOMR_TTC_Msk (0x7UL << ETH_DMAOMR_TTC_Pos) /*!< 0x0001C000 */
#define ETH_DMAOMR_TTC ETH_DMAOMR_TTC_Msk                /* Transmit threshold control */
#define ETH_DMAOMR_TTC_64Bytes 0x00000000U               /* threshold level of the MTL Transmit FIFO is 64 Bytes */
#define ETH_DMAOMR_TTC_128Bytes 0x00004000U              /* threshold level of the MTL Transmit FIFO is 128 Bytes */
#define ETH_DMAOMR_TTC_192Bytes 0x00008000U              /* threshold level of the MTL Transmit FIFO is 192 Bytes */
#define ETH_DMAOMR_TTC_256Bytes 0x0000C000U              /* threshold level of the MTL Transmit FIFO is 256 Bytes */
#define ETH_DMAOMR_TTC_40Bytes 0x00010000U               /* threshold level of the MTL Transmit FIFO is 40 Bytes */
#define ETH_DMAOMR_TTC_32Bytes 0x00014000U               /* threshold level of the MTL Transmit FIFO is 32 Bytes */
#define ETH_DMAOMR_TTC_24Bytes 0x00018000U               /* threshold level of the MTL Transmit FIFO is 24 Bytes */
#define ETH_DMAOMR_TTC_16Bytes 0x0001C000U               /* threshold level of the MTL Transmit FIFO is 16 Bytes */
#define ETH_DMAOMR_ST_Pos (13U)
#define ETH_DMAOMR_ST_Msk (0x1UL << ETH_DMAOMR_ST_Pos) /*!< 0x00002000 */
#define ETH_DMAOMR_ST ETH_DMAOMR_ST_Msk                /* Start/stop transmission command */
#define ETH_DMAOMR_FEF_Pos (7U)
#define ETH_DMAOMR_FEF_Msk (0x1UL << ETH_DMAOMR_FEF_Pos) /*!< 0x00000080 */
#define ETH_DMAOMR_FEF ETH_DMAOMR_FEF_Msk                /* Forward error frames */
#define ETH_DMAOMR_FUGF_Pos (6U)
#define ETH_DMAOMR_FUGF_Msk (0x1UL << ETH_DMAOMR_FUGF_Pos) /*!< 0x00000040 */
#define ETH_DMAOMR_FUGF ETH_DMAOMR_FUGF_Msk                /* Forward undersized good frames */
#define ETH_DMAOMR_RTC_Pos (3U)
#define ETH_DMAOMR_RTC_Msk (0x3UL << ETH_DMAOMR_RTC_Pos) /*!< 0x00000018 */
#define ETH_DMAOMR_RTC ETH_DMAOMR_RTC_Msk                /* receive threshold control */
#define ETH_DMAOMR_RTC_64Bytes 0x00000000U               /* threshold level of the MTL Receive FIFO is 64 Bytes */
#define ETH_DMAOMR_RTC_32Bytes 0x00000008U               /* threshold level of the MTL Receive FIFO is 32 Bytes */
#define ETH_DMAOMR_RTC_96Bytes 0x00000010U               /* threshold level of the MTL Receive FIFO is 96 Bytes */
#define ETH_DMAOMR_RTC_128Bytes 0x00000018U              /* threshold level of the MTL Receive FIFO is 128 Bytes */
#define ETH_DMAOMR_OSF_Pos (2U)
#define ETH_DMAOMR_OSF_Msk (0x1UL << ETH_DMAOMR_OSF_Pos) /*!< 0x00000004 */
#define ETH_DMAOMR_OSF ETH_DMAOMR_OSF_Msk                /* operate on second frame */
#define ETH_DMAOMR_SR_Pos (1U)
#define ETH_DMAOMR_SR_Msk (0x1UL << ETH_DMAOMR_SR_Pos) /*!< 0x00000002 */
#define ETH_DMAOMR_SR ETH_DMAOMR_SR_Msk                /* Start/stop receive */

/* Bit definition for Ethernet DMA Interrupt Enable Register */
#define ETH_DMAIER_NISE_Pos (16U)
#define ETH_DMAIER_NISE_Msk (0x1UL << ETH_DMAIER_NISE_Pos) /*!< 0x00010000 */
#define ETH_DMAIER_NISE ETH_DMAIER_NISE_Msk                /* Normal interrupt summary enable */
#define ETH_DMAIER_AISE_Pos (15U)
#define ETH_DMAIER_AISE_Msk (0x1UL << ETH_DMAIER_AISE_Pos) /*!< 0x00008000 */
#define ETH_DMAIER_AISE ETH_DMAIER_AISE_Msk                /* Abnormal interrupt summary enable */
#define ETH_DMAIER_ERIE_Pos (14U)
#define ETH_DMAIER_ERIE_Msk (0x1UL << ETH_DMAIER_ERIE_Pos) /*!< 0x00004000 */
#define ETH_DMAIER_ERIE ETH_DMAIER_ERIE_Msk                /* Early receive interrupt enable */
#define ETH_DMAIER_FBEIE_Pos (13U)
#define ETH_DMAIER_FBEIE_Msk (0x1UL << ETH_DMAIER_FBEIE_Pos) /*!< 0x00002000 */
#define ETH_DMAIER_FBEIE ETH_DMAIER_FBEIE_Msk                /* Fatal bus error interrupt enable */
#define ETH_DMAIER_ETIE_Pos (10U)
#define ETH_DMAIER_ETIE_Msk (0x1UL << ETH_DMAIER_ETIE_Pos) /*!< 0x00000400 */
#define ETH_DMAIER_ETIE ETH_DMAIER_ETIE_Msk                /* Early transmit interrupt enable */
#define ETH_DMAIER_RWTIE_Pos (9U)
#define ETH_DMAIER_RWTIE_Msk (0x1UL << ETH_DMAIER_RWTIE_Pos) /*!< 0x00000200 */
#define ETH_DMAIER_RWTIE ETH_DMAIER_RWTIE_Msk                /* Receive watchdog timeout interrupt enable */
#define ETH_DMAIER_RPSIE_Pos (8U)
#define ETH_DMAIER_RPSIE_Msk (0x1UL << ETH_DMAIER_RPSIE_Pos) /*!< 0x00000100 */
#define ETH_DMAIER_RPSIE ETH_DMAIER_RPSIE_Msk                /* Receive process stopped interrupt enable */
#define ETH_DMAIER_RBUIE_Pos (7U)
#define ETH_DMAIER_RBUIE_Msk (0x1UL << ETH_DMAIER_RBUIE_Pos) /*!< 0x00000080 */
#define ETH_DMAIER_RBUIE ETH_DMAIER_RBUIE_Msk                /* Receive buffer unavailable interrupt enable */
#define ETH_DMAIER_RIE_Pos (6U)
#define ETH_DMAIER_RIE_Msk (0x1UL << ETH_DMAIER_RIE_Pos) /*!< 0x00000040 */
#define ETH_DMAIER_RIE ETH_DMAIER_RIE_Msk                /* Receive interrupt enable */
#define ETH_DMAIER_TUIE_Pos (5U)
#define ETH_DMAIER_TUIE_Msk (0x1UL << ETH_DMAIER_TUIE_Pos) /*!< 0x00000020 */
#define ETH_DMAIER_TUIE ETH_DMAIER_TUIE_Msk                /* Transmit Underflow interrupt enable */
#define ETH_DMAIER_ROIE_Pos (4U)
#define ETH_DMAIER_ROIE_Msk (0x1UL << ETH_DMAIER_ROIE_Pos) /*!< 0x00000010 */
#define ETH_DMAIER_ROIE ETH_DMAIER_ROIE_Msk                /* Receive Overflow interrupt enable */
#define ETH_DMAIER_TJTIE_Pos (3U)
#define ETH_DMAIER_TJTIE_Msk (0x1UL << ETH_DMAIER_TJTIE_Pos) /*!< 0x00000008 */
#define ETH_DMAIER_TJTIE ETH_DMAIER_TJTIE_Msk                /* Transmit jabber timeout interrupt enable */
#define ETH_DMAIER_TBUIE_Pos (2U)
#define ETH_DMAIER_TBUIE_Msk (0x1UL << ETH_DMAIER_TBUIE_Pos) /*!< 0x00000004 */
#define ETH_DMAIER_TBUIE ETH_DMAIER_TBUIE_Msk                /* Transmit buffer unavailable interrupt enable */
#define ETH_DMAIER_TPSIE_Pos (1U)
#define ETH_DMAIER_TPSIE_Msk (0x1UL << ETH_DMAIER_TPSIE_Pos) /*!< 0x00000002 */
#define ETH_DMAIER_TPSIE ETH_DMAIER_TPSIE_Msk                /* Transmit process stopped interrupt enable */
#define ETH_DMAIER_TIE_Pos (0U)
#define ETH_DMAIER_TIE_Msk (0x1UL << ETH_DMAIER_TIE_Pos) /*!< 0x00000001 */
#define ETH_DMAIER_TIE ETH_DMAIER_TIE_Msk                /* Transmit interrupt enable */

/* Bit definition for Ethernet DMA Missed Frame and Buffer Overflow Counter Register */
#define ETH_DMAMFBOCR_OFOC_Pos (28U)
#define ETH_DMAMFBOCR_OFOC_Msk (0x1UL << ETH_DMAMFBOCR_OFOC_Pos) /*!< 0x10000000 */
#define ETH_DMAMFBOCR_OFOC ETH_DMAMFBOCR_OFOC_Msk                /* Overflow bit for FIFO overflow counter */
#define ETH_DMAMFBOCR_MFA_Pos (17U)
#define ETH_DMAMFBOCR_MFA_Msk (0x7FFUL << ETH_DMAMFBOCR_MFA_Pos) /*!< 0x0FFE0000 */
#define ETH_DMAMFBOCR_MFA ETH_DMAMFBOCR_MFA_Msk                  /* Number of frames missed by the application */
#define ETH_DMAMFBOCR_OMFC_Pos (16U)
#define ETH_DMAMFBOCR_OMFC_Msk (0x1UL << ETH_DMAMFBOCR_OMFC_Pos) /*!< 0x00010000 */
#define ETH_DMAMFBOCR_OMFC ETH_DMAMFBOCR_OMFC_Msk                /* Overflow bit for missed frame counter */
#define ETH_DMAMFBOCR_MFC_Pos (0U)
#define ETH_DMAMFBOCR_MFC_Msk (0xFFFFUL << ETH_DMAMFBOCR_MFC_Pos) /*!< 0x0000FFFF */
#define ETH_DMAMFBOCR_MFC ETH_DMAMFBOCR_MFC_Msk                   /* Number of frames missed by the controller */

/* Bit definition for Ethernet DMA Current Host Transmit Descriptor Register */
#define ETH_DMACHTDR_HTDAP_Pos (0U)
#define ETH_DMACHTDR_HTDAP_Msk (0xFFFFFFFFUL << ETH_DMACHTDR_HTDAP_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMACHTDR_HTDAP ETH_DMACHTDR_HTDAP_Msk                       /* Host transmit descriptor address pointer */

/* Bit definition for Ethernet DMA Current Host Receive Descriptor Register */
#define ETH_DMACHRDR_HRDAP_Pos (0U)
#define ETH_DMACHRDR_HRDAP_Msk (0xFFFFFFFFUL << ETH_DMACHRDR_HRDAP_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMACHRDR_HRDAP ETH_DMACHRDR_HRDAP_Msk                       /* Host receive descriptor address pointer */

/* Bit definition for Ethernet DMA Current Host Transmit Buffer Address Register */
#define ETH_DMACHTBAR_HTBAP_Pos (0U)
#define ETH_DMACHTBAR_HTBAP_Msk (0xFFFFFFFFUL << ETH_DMACHTBAR_HTBAP_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMACHTBAR_HTBAP ETH_DMACHTBAR_HTBAP_Msk                       /* Host transmit buffer address pointer */

/* Bit definition for Ethernet DMA Current Host Receive Buffer Address Register */
#define ETH_DMACHRBAR_HRBAP_Pos (0U)
#define ETH_DMACHRBAR_HRBAP_Msk (0xFFFFFFFFUL << ETH_DMACHRBAR_HRBAP_Pos) /*!< 0xFFFFFFFF */
#define ETH_DMACHRBAR_HRBAP ETH_DMACHRBAR_HRBAP_Msk                       /* Host receive buffer address pointer */

#define IS_ETH_PHY_ADDRESS(ADDRESS) ((ADDRESS) <= 0x20U)
#define IS_ETH_AUTONEGOTIATION(CMD) (((CMD) == ETH_AUTONEGOTIATION_ENABLE) || \
                                     ((CMD) == ETH_AUTONEGOTIATION_DISABLE))
#define IS_ETH_SPEED(SPEED) (((SPEED) == ETH_SPEED_10M) || \
                             ((SPEED) == ETH_SPEED_100M))
#define IS_ETH_DUPLEX_MODE(MODE) (((MODE) == ETH_MODE_FULLDUPLEX) || \
                                  ((MODE) == ETH_MODE_HALFDUPLEX))
#define IS_ETH_RX_MODE(MODE) (((MODE) == ETH_RXPOLLING_MODE) || \
                              ((MODE) == ETH_RXINTERRUPT_MODE))
#define IS_ETH_CHECKSUM_MODE(MODE) (((MODE) == ETH_CHECKSUM_BY_HARDWARE) || \
                                    ((MODE) == ETH_CHECKSUM_BY_SOFTWARE))
#define IS_ETH_MEDIA_INTERFACE(MODE) (((MODE) == ETH_MEDIA_INTERFACE_MII) || \
                                      ((MODE) == ETH_MEDIA_INTERFACE_RMII))
#define IS_ETH_WATCHDOG(CMD) (((CMD) == ETH_WATCHDOG_ENABLE) || \
                              ((CMD) == ETH_WATCHDOG_DISABLE))
#define IS_ETH_JABBER(CMD) (((CMD) == ETH_JABBER_ENABLE) || \
                            ((CMD) == ETH_JABBER_DISABLE))
#define IS_ETH_INTER_FRAME_GAP(GAP) (((GAP) == ETH_INTERFRAMEGAP_96BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_88BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_80BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_72BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_64BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_56BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_48BIT) || \
                                     ((GAP) == ETH_INTERFRAMEGAP_40BIT))
#define IS_ETH_CARRIER_SENSE(CMD) (((CMD) == ETH_CARRIERSENCE_ENABLE) || \
                                   ((CMD) == ETH_CARRIERSENCE_DISABLE))
#define IS_ETH_RECEIVE_OWN(CMD) (((CMD) == ETH_RECEIVEOWN_ENABLE) || \
                                 ((CMD) == ETH_RECEIVEOWN_DISABLE))
#define IS_ETH_LOOPBACK_MODE(CMD) (((CMD) == ETH_LOOPBACKMODE_ENABLE) || \
                                   ((CMD) == ETH_LOOPBACKMODE_DISABLE))
#define IS_ETH_CHECKSUM_OFFLOAD(CMD) (((CMD) == ETH_CHECKSUMOFFLAOD_ENABLE) || \
                                      ((CMD) == ETH_CHECKSUMOFFLAOD_DISABLE))
#define IS_ETH_RETRY_TRANSMISSION(CMD) (((CMD) == ETH_RETRYTRANSMISSION_ENABLE) || \
                                        ((CMD) == ETH_RETRYTRANSMISSION_DISABLE))
#define IS_ETH_AUTOMATIC_PADCRC_STRIP(CMD) (((CMD) == ETH_AUTOMATICPADCRCSTRIP_ENABLE) || \
                                            ((CMD) == ETH_AUTOMATICPADCRCSTRIP_DISABLE))
#define IS_ETH_BACKOFF_LIMIT(LIMIT) (((LIMIT) == ETH_BACKOFFLIMIT_10) || \
                                     ((LIMIT) == ETH_BACKOFFLIMIT_8) ||  \
                                     ((LIMIT) == ETH_BACKOFFLIMIT_4) ||  \
                                     ((LIMIT) == ETH_BACKOFFLIMIT_1))
#define IS_ETH_DEFERRAL_CHECK(CMD) (((CMD) == ETH_DEFFERRALCHECK_ENABLE) || \
                                    ((CMD) == ETH_DEFFERRALCHECK_DISABLE))
#define IS_ETH_RECEIVE_ALL(CMD) (((CMD) == ETH_RECEIVEALL_ENABLE) || \
                                 ((CMD) == ETH_RECEIVEAll_DISABLE))
#define IS_ETH_SOURCE_ADDR_FILTER(CMD) (((CMD) == ETH_SOURCEADDRFILTER_NORMAL_ENABLE) ||  \
                                        ((CMD) == ETH_SOURCEADDRFILTER_INVERSE_ENABLE) || \
                                        ((CMD) == ETH_SOURCEADDRFILTER_DISABLE))
#define IS_ETH_CONTROL_FRAMES(PASS) (((PASS) == ETH_PASSCONTROLFRAMES_BLOCKALL) ||   \
                                     ((PASS) == ETH_PASSCONTROLFRAMES_FORWARDALL) || \
                                     ((PASS) == ETH_PASSCONTROLFRAMES_FORWARDPASSEDADDRFILTER))
#define IS_ETH_BROADCAST_FRAMES_RECEPTION(CMD) (((CMD) == ETH_BROADCASTFRAMESRECEPTION_ENABLE) || \
                                                ((CMD) == ETH_BROADCASTFRAMESRECEPTION_DISABLE))
#define IS_ETH_DESTINATION_ADDR_FILTER(FILTER) (((FILTER) == ETH_DESTINATIONADDRFILTER_NORMAL) || \
                                                ((FILTER) == ETH_DESTINATIONADDRFILTER_INVERSE))
#define IS_ETH_PROMISCUOUS_MODE(CMD) (((CMD) == ETH_PROMISCUOUS_MODE_ENABLE) || \
                                      ((CMD) == ETH_PROMISCUOUS_MODE_DISABLE))
#define IS_ETH_MULTICAST_FRAMES_FILTER(FILTER) (((FILTER) == ETH_MULTICASTFRAMESFILTER_PERFECTHASHTABLE) || \
                                                ((FILTER) == ETH_MULTICASTFRAMESFILTER_HASHTABLE) ||        \
                                                ((FILTER) == ETH_MULTICASTFRAMESFILTER_PERFECT) ||          \
                                                ((FILTER) == ETH_MULTICASTFRAMESFILTER_NONE))
#define IS_ETH_UNICAST_FRAMES_FILTER(FILTER) (((FILTER) == ETH_UNICASTFRAMESFILTER_PERFECTHASHTABLE) || \
                                              ((FILTER) == ETH_UNICASTFRAMESFILTER_HASHTABLE) ||        \
                                              ((FILTER) == ETH_UNICASTFRAMESFILTER_PERFECT))
#define IS_ETH_PAUSE_TIME(TIME) ((TIME) <= 0xFFFFU)
#define IS_ETH_ZEROQUANTA_PAUSE(CMD) (((CMD) == ETH_ZEROQUANTAPAUSE_ENABLE) || \
                                      ((CMD) == ETH_ZEROQUANTAPAUSE_DISABLE))
#define IS_ETH_PAUSE_LOW_THRESHOLD(THRESHOLD) (((THRESHOLD) == ETH_PAUSELOWTHRESHOLD_MINUS4) ||   \
                                               ((THRESHOLD) == ETH_PAUSELOWTHRESHOLD_MINUS28) ||  \
                                               ((THRESHOLD) == ETH_PAUSELOWTHRESHOLD_MINUS144) || \
                                               ((THRESHOLD) == ETH_PAUSELOWTHRESHOLD_MINUS256))
#define IS_ETH_UNICAST_PAUSE_FRAME_DETECT(CMD) (((CMD) == ETH_UNICASTPAUSEFRAMEDETECT_ENABLE) || \
                                                ((CMD) == ETH_UNICASTPAUSEFRAMEDETECT_DISABLE))
#define IS_ETH_RECEIVE_FLOWCONTROL(CMD) (((CMD) == ETH_RECEIVEFLOWCONTROL_ENABLE) || \
                                         ((CMD) == ETH_RECEIVEFLOWCONTROL_DISABLE))
#define IS_ETH_TRANSMIT_FLOWCONTROL(CMD) (((CMD) == ETH_TRANSMITFLOWCONTROL_ENABLE) || \
                                          ((CMD) == ETH_TRANSMITFLOWCONTROL_DISABLE))
#define IS_ETH_VLAN_TAG_COMPARISON(COMPARISON) (((COMPARISON) == ETH_VLANTAGCOMPARISON_12BIT) || \
                                                ((COMPARISON) == ETH_VLANTAGCOMPARISON_16BIT))
#define IS_ETH_VLAN_TAG_IDENTIFIER(IDENTIFIER) ((IDENTIFIER) <= 0xFFFFU)
#define IS_ETH_MAC_ADDRESS0123(ADDRESS) (((ADDRESS) == ETH_MAC_ADDRESS0) || \
                                         ((ADDRESS) == ETH_MAC_ADDRESS1) || \
                                         ((ADDRESS) == ETH_MAC_ADDRESS2) || \
                                         ((ADDRESS) == ETH_MAC_ADDRESS3))
#define IS_ETH_MAC_ADDRESS123(ADDRESS) (((ADDRESS) == ETH_MAC_ADDRESS1) || \
                                        ((ADDRESS) == ETH_MAC_ADDRESS2) || \
                                        ((ADDRESS) == ETH_MAC_ADDRESS3))
#define IS_ETH_MAC_ADDRESS_FILTER(FILTER) (((FILTER) == ETH_MAC_ADDRESSFILTER_SA) || \
                                           ((FILTER) == ETH_MAC_ADDRESSFILTER_DA))
#define IS_ETH_MAC_ADDRESS_MASK(MASK) (((MASK) == ETH_MAC_ADDRESSMASK_BYTE6) || \
                                       ((MASK) == ETH_MAC_ADDRESSMASK_BYTE5) || \
                                       ((MASK) == ETH_MAC_ADDRESSMASK_BYTE4) || \
                                       ((MASK) == ETH_MAC_ADDRESSMASK_BYTE3) || \
                                       ((MASK) == ETH_MAC_ADDRESSMASK_BYTE2) || \
                                       ((MASK) == ETH_MAC_ADDRESSMASK_BYTE1))
#define IS_ETH_DROP_TCPIP_CHECKSUM_FRAME(CMD) (((CMD) == ETH_DROPTCPIPCHECKSUMERRORFRAME_ENABLE) || \
                                               ((CMD) == ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE))
#define IS_ETH_RECEIVE_STORE_FORWARD(CMD) (((CMD) == ETH_RECEIVESTOREFORWARD_ENABLE) || \
                                           ((CMD) == ETH_RECEIVESTOREFORWARD_DISABLE))
#define IS_ETH_FLUSH_RECEIVE_FRAME(CMD) (((CMD) == ETH_FLUSHRECEIVEDFRAME_ENABLE) || \
                                         ((CMD) == ETH_FLUSHRECEIVEDFRAME_DISABLE))
#define IS_ETH_TRANSMIT_STORE_FORWARD(CMD) (((CMD) == ETH_TRANSMITSTOREFORWARD_ENABLE) || \
                                            ((CMD) == ETH_TRANSMITSTOREFORWARD_DISABLE))
#define IS_ETH_TRANSMIT_THRESHOLD_CONTROL(THRESHOLD) (((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_64BYTES) ||  \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_128BYTES) || \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_192BYTES) || \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_256BYTES) || \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_40BYTES) ||  \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_32BYTES) ||  \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_24BYTES) ||  \
                                                      ((THRESHOLD) == ETH_TRANSMITTHRESHOLDCONTROL_16BYTES))
#define IS_ETH_FORWARD_ERROR_FRAMES(CMD) (((CMD) == ETH_FORWARDERRORFRAMES_ENABLE) || \
                                          ((CMD) == ETH_FORWARDERRORFRAMES_DISABLE))
#define IS_ETH_FORWARD_UNDERSIZED_GOOD_FRAMES(CMD) (((CMD) == ETH_FORWARDUNDERSIZEDGOODFRAMES_ENABLE) || \
                                                    ((CMD) == ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE))
#define IS_ETH_RECEIVE_THRESHOLD_CONTROL(THRESHOLD) (((THRESHOLD) == ETH_RECEIVEDTHRESHOLDCONTROL_64BYTES) || \
                                                     ((THRESHOLD) == ETH_RECEIVEDTHRESHOLDCONTROL_32BYTES) || \
                                                     ((THRESHOLD) == ETH_RECEIVEDTHRESHOLDCONTROL_96BYTES) || \
                                                     ((THRESHOLD) == ETH_RECEIVEDTHRESHOLDCONTROL_128BYTES))
#define IS_ETH_SECOND_FRAME_OPERATE(CMD) (((CMD) == ETH_SECONDFRAMEOPERARTE_ENABLE) || \
                                          ((CMD) == ETH_SECONDFRAMEOPERARTE_DISABLE))
#define IS_ETH_ADDRESS_ALIGNED_BEATS(CMD) (((CMD) == ETH_ADDRESSALIGNEDBEATS_ENABLE) || \
                                           ((CMD) == ETH_ADDRESSALIGNEDBEATS_DISABLE))
#define IS_ETH_FIXED_BURST(CMD) (((CMD) == ETH_FIXEDBURST_ENABLE) || \
                                 ((CMD) == ETH_FIXEDBURST_DISABLE))
#define IS_ETH_RXDMA_BURST_LENGTH(LENGTH) (((LENGTH) == ETH_RXDMABURSTLENGTH_1BEAT) ||        \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_2BEAT) ||        \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4BEAT) ||        \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_8BEAT) ||        \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_16BEAT) ||       \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_32BEAT) ||       \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_4BEAT) ||  \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_8BEAT) ||  \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_16BEAT) || \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_32BEAT) || \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_64BEAT) || \
                                           ((LENGTH) == ETH_RXDMABURSTLENGTH_4XPBL_128BEAT))
#define IS_ETH_TXDMA_BURST_LENGTH(LENGTH) (((LENGTH) == ETH_TXDMABURSTLENGTH_1BEAT) ||        \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_2BEAT) ||        \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4BEAT) ||        \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_8BEAT) ||        \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_16BEAT) ||       \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_32BEAT) ||       \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_4BEAT) ||  \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_8BEAT) ||  \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_16BEAT) || \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_32BEAT) || \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_64BEAT) || \
                                           ((LENGTH) == ETH_TXDMABURSTLENGTH_4XPBL_128BEAT))
#define IS_ETH_DMA_DESC_SKIP_LENGTH(LENGTH) ((LENGTH) <= 0x1FU)
#define IS_ETH_DMA_ARBITRATION_ROUNDROBIN_RXTX(RATIO) (((RATIO) == ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1) || \
                                                       ((RATIO) == ETH_DMAARBITRATION_ROUNDROBIN_RXTX_2_1) || \
                                                       ((RATIO) == ETH_DMAARBITRATION_ROUNDROBIN_RXTX_3_1) || \
                                                       ((RATIO) == ETH_DMAARBITRATION_ROUNDROBIN_RXTX_4_1) || \
                                                       ((RATIO) == ETH_DMAARBITRATION_RXPRIORTX))

    /*
    #define IS_ETH_DMATXDESC_GET_FLAG(FLAG) (((FLAG) == ETH_DMATXDESC_OWN) || \
                                             ((FLAG) == ETH_DMATXDESC_IC) || \
                                             ((FLAG) == ETH_DMATXDESC_LS) || \
                                             ((FLAG) == ETH_DMATXDESC_FS) || \
                                             ((FLAG) == ETH_DMATXDESC_DC) || \
                                             ((FLAG) == ETH_DMATXDESC_DP) || \
                                             ((FLAG) == ETH_DMATXDESC_TTSE) || \
                                             ((FLAG) == ETH_DMATXDESC_TER) || \
                                             ((FLAG) == ETH_DMATXDESC_TCH) || \
                                             ((FLAG) == ETH_DMATXDESC_TTSS) || \
                                             ((FLAG) == ETH_DMATXDESC_IHE) || \
                                             ((FLAG) == ETH_DMATXDESC_ES) || \
                                             ((FLAG) == ETH_DMATXDESC_JT) || \
                                             ((FLAG) == ETH_DMATXDESC_FF) || \
                                             ((FLAG) == ETH_DMATXDESC_PCE) || \
                                             ((FLAG) == ETH_DMATXDESC_LCA) || \
                                             ((FLAG) == ETH_DMATXDESC_NC) || \
                                             ((FLAG) == ETH_DMATXDESC_LCO) || \
                                             ((FLAG) == ETH_DMATXDESC_EC) || \
                                             ((FLAG) == ETH_DMATXDESC_VF) || \
                                             ((FLAG) == ETH_DMATXDESC_CC) || \
                                             ((FLAG) == ETH_DMATXDESC_ED) || \
                                             ((FLAG) == ETH_DMATXDESC_UF) || \
                                             ((FLAG) == ETH_DMATXDESC_DB))
                                             */

#define IS_ETH_DMA_TXDESC_SEGMENT(SEGMENT) (((SEGMENT) == ETH_DMATXDESC_LASTSEGMENTS) || \
                                            ((SEGMENT) == ETH_DMATXDESC_FIRSTSEGMENT))
#define IS_ETH_DMA_TXDESC_CHECKSUM(CHECKSUM) (((CHECKSUM) == ETH_DMATXDESC_CHECKSUMBYPASS) ||            \
                                              ((CHECKSUM) == ETH_DMATXDESC_CHECKSUMIPV4HEADER) ||        \
                                              ((CHECKSUM) == ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT) || \
                                              ((CHECKSUM) == ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL))
#define IS_ETH_DMATXDESC_BUFFER_SIZE(SIZE) ((SIZE) <= 0x1FFFU)
#define IS_ETH_DMARXDESC_GET_FLAG(FLAG) (((FLAG) == ETH_DMARXDESC_OWN) ||     \
                                         ((FLAG) == ETH_DMARXDESC_AFM) ||     \
                                         ((FLAG) == ETH_DMARXDESC_ES) ||      \
                                         ((FLAG) == ETH_DMARXDESC_DE) ||      \
                                         ((FLAG) == ETH_DMARXDESC_SAF) ||     \
                                         ((FLAG) == ETH_DMARXDESC_LE) ||      \
                                         ((FLAG) == ETH_DMARXDESC_OE) ||      \
                                         ((FLAG) == ETH_DMARXDESC_VLAN) ||    \
                                         ((FLAG) == ETH_DMARXDESC_FS) ||      \
                                         ((FLAG) == ETH_DMARXDESC_LS) ||      \
                                         ((FLAG) == ETH_DMARXDESC_IPV4HCE) || \
                                         ((FLAG) == ETH_DMARXDESC_LC) ||      \
                                         ((FLAG) == ETH_DMARXDESC_FT) ||      \
                                         ((FLAG) == ETH_DMARXDESC_RWT) ||     \
                                         ((FLAG) == ETH_DMARXDESC_RE) ||      \
                                         ((FLAG) == ETH_DMARXDESC_DBE) ||     \
                                         ((FLAG) == ETH_DMARXDESC_CE) ||      \
                                         ((FLAG) == ETH_DMARXDESC_MAMPCE))
#define IS_ETH_DMA_RXDESC_BUFFER(BUFFER) (((BUFFER) == ETH_DMARXDESC_BUFFER1) || \
                                          ((BUFFER) == ETH_DMARXDESC_BUFFER2))
#define IS_ETH_PMT_GET_FLAG(FLAG) (((FLAG) == ETH_PMT_FLAG_WUFR) || \
                                   ((FLAG) == ETH_PMT_FLAG_MPR))
#define IS_ETH_DMA_FLAG(FLAG) ((((FLAG) & 0xC7FE1800U) == 0x00U) && ((FLAG) != 0x00U))
#define IS_ETH_DMA_GET_FLAG(FLAG) (((FLAG) == ETH_DMA_FLAG_TST) || ((FLAG) == ETH_DMA_FLAG_PMT) ||                    \
                                   ((FLAG) == ETH_DMA_FLAG_MMC) || ((FLAG) == ETH_DMA_FLAG_DATATRANSFERERROR) ||      \
                                   ((FLAG) == ETH_DMA_FLAG_READWRITEERROR) || ((FLAG) == ETH_DMA_FLAG_ACCESSERROR) || \
                                   ((FLAG) == ETH_DMA_FLAG_NIS) || ((FLAG) == ETH_DMA_FLAG_AIS) ||                    \
                                   ((FLAG) == ETH_DMA_FLAG_ER) || ((FLAG) == ETH_DMA_FLAG_FBE) ||                     \
                                   ((FLAG) == ETH_DMA_FLAG_ET) || ((FLAG) == ETH_DMA_FLAG_RWT) ||                     \
                                   ((FLAG) == ETH_DMA_FLAG_RPS) || ((FLAG) == ETH_DMA_FLAG_RBU) ||                    \
                                   ((FLAG) == ETH_DMA_FLAG_R) || ((FLAG) == ETH_DMA_FLAG_TU) ||                       \
                                   ((FLAG) == ETH_DMA_FLAG_RO) || ((FLAG) == ETH_DMA_FLAG_TJT) ||                     \
                                   ((FLAG) == ETH_DMA_FLAG_TBU) || ((FLAG) == ETH_DMA_FLAG_TPS) ||                    \
                                   ((FLAG) == ETH_DMA_FLAG_T))
#define IS_ETH_MAC_IT(IT) ((((IT) & 0xFFFFFDF1U) == 0x00U) && ((IT) != 0x00U))
#define IS_ETH_MAC_GET_IT(IT) (((IT) == ETH_MAC_IT_TST) || ((IT) == ETH_MAC_IT_MMCT) || \
                               ((IT) == ETH_MAC_IT_MMCR) || ((IT) == ETH_MAC_IT_MMC) || \
                               ((IT) == ETH_MAC_IT_PMT))
#define IS_ETH_MAC_GET_FLAG(FLAG) (((FLAG) == ETH_MAC_FLAG_TST) || ((FLAG) == ETH_MAC_FLAG_MMCT) || \
                                   ((FLAG) == ETH_MAC_FLAG_MMCR) || ((FLAG) == ETH_MAC_FLAG_MMC) || \
                                   ((FLAG) == ETH_MAC_FLAG_PMT))
#define IS_ETH_DMA_IT(IT) ((((IT) & 0xC7FE1800U) == 0x00U) && ((IT) != 0x00U))
#define IS_ETH_DMA_GET_IT(IT) (((IT) == ETH_DMA_IT_TST) || ((IT) == ETH_DMA_IT_PMT) || \
                               ((IT) == ETH_DMA_IT_MMC) || ((IT) == ETH_DMA_IT_NIS) || \
                               ((IT) == ETH_DMA_IT_AIS) || ((IT) == ETH_DMA_IT_ER) ||  \
                               ((IT) == ETH_DMA_IT_FBE) || ((IT) == ETH_DMA_IT_ET) ||  \
                               ((IT) == ETH_DMA_IT_RWT) || ((IT) == ETH_DMA_IT_RPS) || \
                               ((IT) == ETH_DMA_IT_RBU) || ((IT) == ETH_DMA_IT_R) ||   \
                               ((IT) == ETH_DMA_IT_TU) || ((IT) == ETH_DMA_IT_RO) ||   \
                               ((IT) == ETH_DMA_IT_TJT) || ((IT) == ETH_DMA_IT_TBU) || \
                               ((IT) == ETH_DMA_IT_TPS) || ((IT) == ETH_DMA_IT_T))
#define IS_ETH_DMA_GET_OVERFLOW(OVERFLOW) (((OVERFLOW) == ETH_DMA_OVERFLOW_RXFIFOCOUNTER) || \
                                           ((OVERFLOW) == ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER))
#define IS_ETH_MMC_IT(IT) (((((IT) & 0xFFDF3FFFU) == 0x00U) || (((IT) & 0xEFFDFF9FU) == 0x00U)) && \
                           ((IT) != 0x00U))
#define IS_ETH_MMC_GET_IT(IT) (((IT) == ETH_MMC_IT_TGF) || ((IT) == ETH_MMC_IT_TGFMSC) || \
                               ((IT) == ETH_MMC_IT_TGFSC) || ((IT) == ETH_MMC_IT_RGUF) || \
                               ((IT) == ETH_MMC_IT_RFAE) || ((IT) == ETH_MMC_IT_RFCE))
#define IS_ETH_ENHANCED_DESCRIPTOR_FORMAT(CMD) (((CMD) == ETH_DMAENHANCEDDESCRIPTOR_ENABLE) || \
                                                ((CMD) == ETH_DMAENHANCEDDESCRIPTOR_DISABLE))

/* Delay to wait when writing to some Ethernet registers */
#define ETH_REG_WRITE_DELAY 0x00000001U

/* ETHERNET Errors */
#define ETH_SUCCESS 0U
#define ETH_ERROR 1U

/* ETHERNET DMA Tx descriptors Collision Count Shift */
#define ETH_DMATXDESC_COLLISION_COUNTSHIFT 3U

/* ETHERNET DMA Tx descriptors Buffer2 Size Shift */
#define ETH_DMATXDESC_BUFFER2_SIZESHIFT 16U

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define ETH_DMARXDESC_FRAME_LENGTHSHIFT 16U

/* ETHERNET DMA Rx descriptors Buffer2 Size Shift */
#define ETH_DMARXDESC_BUFFER2_SIZESHIFT 16U

/* ETHERNET DMA Rx descriptors Frame length Shift */
#define ETH_DMARXDESC_FRAMELENGTHSHIFT 16U

/* ETHERNET MAC address offsets */
#define ETH_MAC_ADDR_HBASE (uint32_t)(ETH_MAC_BASE + 0x40U) /* ETHERNET MAC address high offset */
#define ETH_MAC_ADDR_LBASE (uint32_t)(ETH_MAC_BASE + 0x44U) /* ETHERNET MAC address low offset */

/* ETHERNET MACMIIAR register Mask */
#define ETH_MACMIIAR_CR_MASK 0xFFFFFFE3U

/* ETHERNET MACCR register Mask */
#define ETH_MACCR_CLEAR_MASK 0xFF20810FU

/* ETHERNET MACFCR register Mask */
#define ETH_MACFCR_CLEAR_MASK 0x0000FF41U

/* ETHERNET DMAOMR register Mask */
#define ETH_DMAOMR_CLEAR_MASK 0xF8DE3F23U

/* ETHERNET Remote Wake-up frame register length */
#define ETH_WAKEUP_REGISTER_LENGTH 8U

/* ETHERNET Missed frames counter Shift */
#define ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT 17U

    typedef struct
    {
        __IO uint32_t MACCR;                // R0
        __IO uint32_t MACFFR;               // R1
        __IO uint32_t MACHTHR;              // R2
        __IO uint32_t MACHTLR;              // R3
        __IO uint32_t MACMIIAR;             // R4
        __IO uint32_t MACMIIDR;             // R5
        __IO uint32_t MACFCR;               // R6
        __IO uint32_t MACVLANTR; /*    8 */ // R7
        uint32_t RESERVED0[2];
        __IO uint32_t MACRWUFFR; /*   11 */
        __IO uint32_t MACPMTCSR;
        uint32_t RESERVED1;
        __IO uint32_t MACDBGR;
        __IO uint32_t MACSR; /*   15 */
        __IO uint32_t MACIMR;
        __IO uint32_t MACA0HR;            // R13
        __IO uint32_t MACA0LR;            // R14
        __IO uint32_t MACA1HR;            // R15
        __IO uint32_t MACA1LR;            // R16
        __IO uint32_t MACA2HR;            // R17
        __IO uint32_t MACA2LR;            // R18
        __IO uint32_t MACA3HR;            // R19
        __IO uint32_t MACA3LR; /*   24 */ // R20
        uint32_t RESERVED2[40];
        __IO uint32_t MMCCR; /*   65 */
        __IO uint32_t MMCRIR;
        __IO uint32_t MMCTIR;
        __IO uint32_t MMCRIMR;
        __IO uint32_t MMCTIMR; /*   69 */
        uint32_t RESERVED3[14];
        __IO uint32_t MMCTGFSCCR; /*   84 */
        __IO uint32_t MMCTGFMSCCR;
        uint32_t RESERVED4[5];
        __IO uint32_t MMCTGFCR;
        uint32_t RESERVED5[10];
        __IO uint32_t MMCRFCECR;
        __IO uint32_t MMCRFAECR;
        uint32_t RESERVED6[10];
        __IO uint32_t MMCRGUFCR;

        uint32_t RESERVED7[14];
        __IO uint32_t MMCIPCINTMASKRX;
        uint32_t RESERVED70[319];

        //  uint32_t      RESERVED7[334];
        __IO uint32_t PTPTSCR;
        __IO uint32_t PTPSSIR;
        __IO uint32_t PTPTSHR;
        __IO uint32_t PTPTSLR;
        __IO uint32_t PTPTSHUR;
        __IO uint32_t PTPTSLUR;
        __IO uint32_t PTPTSAR;
        __IO uint32_t PTPTTHR;
        __IO uint32_t PTPTTLR;
        __IO uint32_t RESERVED8;
        __IO uint32_t PTPTSSR;
        uint32_t RESERVED9[565];
        __IO uint32_t DMABMR;    // 0x1000     //R0
        __IO uint32_t DMATPDR;   // R1
        __IO uint32_t DMARPDR;   // R2
        __IO uint32_t DMARDLAR;  // R3
        __IO uint32_t DMATDLAR;  // R4
        __IO uint32_t DMASR;     // R5
        __IO uint32_t DMAOMR;    // R6
        __IO uint32_t DMAIER;    // R7
        __IO uint32_t DMAMFBOCR; // R8
        __IO uint32_t DMARSWTR;  // 0x1024    //R9
        uint32_t RESERVED10[8];
        __IO uint32_t DMACHTDR;   // R18
        __IO uint32_t DMACHRDR;   // R19
        __IO uint32_t DMACHTBAR;  // R20
        __IO uint32_t DMACHRBAR;  // R21
        uint32_t RESERVED11;      // 0x1058    //R22
        __IO uint32_t DMACRBR;    // 0x105C    //R23
        __IO uint32_t DMACRMR;    // 0x1060    //R24
        __IO uint32_t DMACRCAR;   // 0x1064    //R25
        __IO uint32_t DMACREAR;   // 0x1068    //R26
        __IO uint32_t DMACRHSR;   // 0x106C    //R27
        __IO uint32_t DMACRBASAR; // 0x1070    //R28
        __IO uint32_t DMACRBBSAR; // 0x1074    //R29
        __IO uint32_t DMACRBAEAR; // 0x1078    //R30
        __IO uint32_t DMACRBBEAR; // 0x107C    //R31

    } ETH_TypeDef;

    typedef enum
    {
        HAL_ETH_STATE_RESET = 0x00U,      /**< Peripheral not yet Initialized or disabled         */
        HAL_ETH_STATE_READY = 0x01U,      /**< Peripheral Initialized and ready for use           */
        HAL_ETH_STATE_BUSY = 0x02U,       /**< an internal process is ongoing                     */
        HAL_ETH_STATE_BUSY_TX = 0x12U,    /**< Data Transmission process is ongoing               */
        HAL_ETH_STATE_BUSY_RX = 0x22U,    /**< Data Reception process is ongoing                  */
        HAL_ETH_STATE_BUSY_TX_RX = 0x32U, /**< Data Transmission and Reception process is ongoing */
        HAL_ETH_STATE_BUSY_WR = 0x42U,    /**< Write process is ongoing                           */
        HAL_ETH_STATE_BUSY_RD = 0x82U,    /**< Read process is ongoing                            */
        HAL_ETH_STATE_TIMEOUT = 0x03U,    /**< Timeout state                                      */
        HAL_ETH_STATE_ERROR = 0x04U       /**< Reception process is ongoing                       */
    } HAL_ETH_StateTypeDef;

    typedef struct
    {
        uint32_t AutoNegotiation; /**< Selects or not the AutoNegotiation mode for the external PHY
                                                               The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                                               and the mode (half/full-duplex).
                                                               This parameter can be a value of @ref ETH_AutoNegotiation */

        uint32_t Speed; /**< Sets the Ethernet speed: 10/100 Mbps.
                                                               This parameter can be a value of @ref ETH_Speed */

        uint32_t DuplexMode; /**< Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                                                               This parameter can be a value of @ref ETH_Duplex_Mode */

        uint16_t PhyAddress; /**< Ethernet PHY address.
                                                               This parameter must be a number between Min_Data = 0 and Max_Data = 32 */

        uint8_t *MACAddr; /**< MAC Address of used Hardware: must be pointer on an array of 6 bytes */

        uint32_t RxMode; /**< Selects the Ethernet Rx mode: Polling mode, Interrupt mode.
                                                               This parameter can be a value of @ref ETH_Rx_Mode */

        uint32_t ChecksumMode; /**< Selects if the checksum is check by hardware or by software.
                                                             This parameter can be a value of @ref ETH_Checksum_Mode */

        uint32_t MediaInterface; /**< Selects the media-independent interface or the reduced media-independent interface.
                                                             This parameter can be a value of @ref ETH_Media_Interface */
        uint32_t EthDMAMode;     /*!< Ethernet DMA Mode             */

    } ETH_InitTypeDef;

    typedef struct
    {
        uint32_t Watchdog; /**< Selects or not the Watchdog timer
                                                               When enabled, the MAC allows no more then 2048 bytes to be received.
                                                               When disabled, the MAC can receive up to 16384 bytes.
                                                               This parameter can be a value of @ref ETH_Watchdog */

        uint32_t Jabber; /**< Selects or not Jabber timer
                                                               When enabled, the MAC allows no more then 2048 bytes to be sent.
                                                               When disabled, the MAC can send up to 16384 bytes.
                                                               This parameter can be a value of @ref ETH_Jabber */

        uint32_t InterFrameGap; /**< Selects the minimum IFG between frames during transmission.
                                                               This parameter can be a value of @ref ETH_Inter_Frame_Gap */

        uint32_t CarrierSense; /**< Selects or not the Carrier Sense.
                                                               This parameter can be a value of @ref ETH_Carrier_Sense */

        uint32_t ReceiveOwn; /**< Selects or not the ReceiveOwn,
                                                               ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                                               in Half-Duplex mode.
                                                               This parameter can be a value of @ref ETH_Receive_Own */

        uint32_t LoopbackMode; /**< Selects or not the internal MAC MII Loopback mode.
                                                               This parameter can be a value of @ref ETH_Loop_Back_Mode */

        uint32_t ChecksumOffload; /**< Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers.
                                                               This parameter can be a value of @ref ETH_Checksum_Offload */

        uint32_t RetryTransmission; /**< Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                                               when a collision occurs (Half-Duplex mode).
                                                               This parameter can be a value of @ref ETH_Retry_Transmission */

        uint32_t AutomaticPadCRCStrip; /**< Selects or not the Automatic MAC Pad/CRC Stripping.
                                                               This parameter can be a value of @ref ETH_Automatic_Pad_CRC_Strip */

        uint32_t BackOffLimit; /**< Selects the BackOff limit value.
                                                               This parameter can be a value of @ref ETH_Back_Off_Limit */

        uint32_t DeferralCheck; /**< Selects or not the deferral check function (Half-Duplex mode).
                                                               This parameter can be a value of @ref ETH_Deferral_Check */

        uint32_t ReceiveAll; /**< Selects or not all frames reception by the MAC (No filtering).
                                                               This parameter can be a value of @ref ETH_Receive_All */

        uint32_t SourceAddrFilter; /**< Selects the Source Address Filter mode.
                                                               This parameter can be a value of @ref ETH_Source_Addr_Filter */

        uint32_t PassControlFrames; /**< Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames)
                                                               This parameter can be a value of @ref ETH_Pass_Control_Frames */

        uint32_t BroadcastFramesReception; /**< Selects or not the reception of Broadcast Frames.
                                                               This parameter can be a value of @ref ETH_Broadcast_Frames_Reception */

        uint32_t DestinationAddrFilter; /**< Sets the destination filter mode for both unicast and multicast frames.
                                                               This parameter can be a value of @ref ETH_Destination_Addr_Filter */

        uint32_t PromiscuousMode; /**< Selects or not the Promiscuous Mode
                                                               This parameter can be a value of @ref ETH_Promiscuous_Mode */

        uint32_t MulticastFramesFilter; /**< Selects the Multicast Frames filter mode: None/HashTableFilter/PerfectFilter/PerfectHashTableFilter.
                                                               This parameter can be a value of @ref ETH_Multicast_Frames_Filter */

        uint32_t UnicastFramesFilter; /**< Selects the Unicast Frames filter mode: HashTableFilter/PerfectFilter/PerfectHashTableFilter.
                                                               This parameter can be a value of @ref ETH_Unicast_Frames_Filter */

        uint32_t HashTableHigh; /**< This field holds the higher 32 bits of Hash table.
                                                               This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFFU */

        uint32_t HashTableLow; /**< This field holds the lower 32 bits of Hash table.
                                                               This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFFFFFU  */

        uint32_t PauseTime; /**< This field holds the value to be used in the Pause Time field in the transmit control frame.
                                                               This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFFU */

        uint32_t ZeroQuantaPause; /**< Selects or not the automatic generation of Zero-Quanta Pause Control frames.
                                                               This parameter can be a value of @ref ETH_Zero_Quanta_Pause */

        uint32_t PauseLowThreshold; /**< This field configures the threshold of the PAUSE to be checked for
                                                               automatic retransmission of PAUSE Frame.
                                                               This parameter can be a value of @ref ETH_Pause_Low_Threshold */

        uint32_t UnicastPauseFrameDetect; /**< Selects or not the MAC detection of the Pause frames (with MAC Address0
                                                               unicast address and unique multicast address).
                                                               This parameter can be a value of @ref ETH_Unicast_Pause_Frame_Detect */

        uint32_t ReceiveFlowControl; /**< Enables or disables the MAC to decode the received Pause frame and
                                                               disable its transmitter for a specified time (Pause Time)
                                                               This parameter can be a value of @ref ETH_Receive_Flow_Control */

        uint32_t TransmitFlowControl; /**< Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                                               or the MAC back-pressure operation (Half-Duplex mode)
                                                               This parameter can be a value of @ref ETH_Transmit_Flow_Control */

        uint32_t VLANTagComparison; /**< Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                                               comparison and filtering.
                                                               This parameter can be a value of @ref ETH_VLAN_Tag_Comparison */

        uint32_t VLANTagIdentifier; /**< Holds the VLAN tag identifier for receive frames */

    } ETH_MACInitTypeDef;

    typedef struct
    {
        uint32_t DropTCPIPChecksumErrorFrame; /**< Selects or not the Dropping of TCP/IP Checksum Error Frames.
                                                                 This parameter can be a value of @ref ETH_Drop_TCP_IP_Checksum_Error_Frame */

        uint32_t ReceiveStoreForward; /**< Enables or disables the Receive store and forward mode.
                                                                 This parameter can be a value of @ref ETH_Receive_Store_Forward */

        uint32_t FlushReceivedFrame; /**< Enables or disables the flushing of received frames.
                                                                 This parameter can be a value of @ref ETH_Flush_Received_Frame */

        uint32_t TransmitStoreForward; /**< Enables or disables Transmit store and forward mode.
                                                                 This parameter can be a value of @ref ETH_Transmit_Store_Forward */

        uint32_t TransmitThresholdControl; /**< Selects or not the Transmit Threshold Control.
                                                                 This parameter can be a value of @ref ETH_Transmit_Threshold_Control */

        uint32_t ForwardErrorFrames; /**< Selects or not the forward to the DMA of erroneous frames.
                                                                 This parameter can be a value of @ref ETH_Forward_Error_Frames */

        uint32_t ForwardUndersizedGoodFrames; /**< Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
                                                                 and length less than 64 bytes) including pad-bytes and CRC)
                                                                 This parameter can be a value of @ref ETH_Forward_Undersized_Good_Frames */

        uint32_t ReceiveThresholdControl; /**< Selects the threshold level of the Receive FIFO.
                                                                 This parameter can be a value of @ref ETH_Receive_Threshold_Control */

        uint32_t SecondFrameOperate; /**< Selects or not the Operate on second frame mode, which allows the DMA to process a second
                                                                 frame of Transmit data even before obtaining the status for the first frame.
                                                                 This parameter can be a value of @ref ETH_Second_Frame_Operate */

        uint32_t AddressAlignedBeats; /**< Enables or disables the Address Aligned Beats.
                                                                 This parameter can be a value of @ref ETH_Address_Aligned_Beats */

        uint32_t FixedBurst; /**< Enables or disables the AHB Master interface fixed burst transfers.
                                                                 This parameter can be a value of @ref ETH_Fixed_Burst */

        uint32_t RxDMABurstLength; /**< Indicates the maximum number of beats to be transferred in one Rx DMA transaction.
                                                                 This parameter can be a value of @ref ETH_Rx_DMA_Burst_Length */

        uint32_t TxDMABurstLength; /**< Indicates the maximum number of beats to be transferred in one Tx DMA transaction.
                                                                 This parameter can be a value of @ref ETH_Tx_DMA_Burst_Length */

        uint32_t EnhancedDescriptorFormat; /**< Enables the enhanced descriptor format.
                                                                 This parameter can be a value of @ref ETH_DMA_Enhanced_descriptor_format */

        uint32_t DescriptorSkipLength; /**< Specifies the number of word to skip between two unchained descriptors (Ring mode)
                                                                 This parameter must be a number between Min_Data = 0 and Max_Data = 32 */

        uint32_t DMAArbitration; /**< Selects the DMA Tx/Rx arbitration.
                                                                 This parameter can be a value of @ref ETH_DMA_Arbitration */
    } ETH_DMAInitTypeDef;

    typedef struct
    {
        __IO uint32_t Status; /**< Status */

        uint32_t ControlBufferSize; /**< Control and Buffer1, Buffer2 lengths */

        uint32_t Buffer1Addr; /**< Buffer1 address pointer */

        uint32_t Buffer2NextDescAddr; /**< Buffer2 or next descriptor address pointer */

        /**< Enhanced ETHERNET DMA PTP Descriptors */
        // uint32_t   ExtendedStatus;        /**< Extended status for PTP receive descriptor */

        // uint32_t   Reserved1;             /**< Reserved */

        // uint32_t   TimeStampLow;          /**< Time Stamp Low value for transmit and receive */

        // uint32_t   TimeStampHigh;         /**< Time Stamp High value for transmit and receive */

    } ETH_DMADescTypeDef;

    typedef struct
    {
        ETH_DMADescTypeDef *FSRxDesc; /**< First Segment Rx Desc */

        ETH_DMADescTypeDef *LSRxDesc; /**< Last Segment Rx Desc */

        uint32_t SegCount; /**< Segment count */

        uint32_t length; /**< Frame length */

        uint32_t buffer; /**< Frame buffer */

    } ETH_DMARxFrameInfos;

#define ETH_DMA_DEFAULT_MODE (0x00U)
#define ETH_DMA_CONTINUOUS_MODE (0x01U)

#if (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    typedef struct __ETH_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
    {
        ETH_TypeDef *Instance; /**< Register base address       */

        ETH_InitTypeDef Init; /**< Ethernet Init Configuration */

        uint32_t LinkStatus; /**< Ethernet link status        */

        ETH_DMADescTypeDef *RxDesc; /**< Rx descriptor to Get        */

        ETH_DMADescTypeDef *TxDesc; /**< Tx descriptor to Set        */

        ETH_DMARxFrameInfos RxFrameInfos; /**< last Rx frame infos         */

        __IO HAL_ETH_StateTypeDef State; /**< ETH communication state     */

        lock_t Lock; /**< ETH Lock                    */

#if (USE_HAL_ETH_REGISTER_CALLBACKS == 1)

        void (*TxCpltCallback)(struct __ETH_HandleTypeDef *heth);    /*!< ETH Tx Complete Callback   */
        void (*RxCpltCallback)(struct __ETH_HandleTypeDef *heth);    /*!< ETH Rx  Complete Callback   */
        void (*DMAErrorCallback)(struct __ETH_HandleTypeDef *heth);  /*!< DMA Error Callback      */
        void (*MspInitCallback)(struct __ETH_HandleTypeDef *heth);   /*!< ETH Msp Init callback       */
        void (*MspDeInitCallback)(struct __ETH_HandleTypeDef *heth); /*!< ETH Msp DeInit callback     */

#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
    } ETH_HandleTypeDef;

#if (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    /**
     * @brief  HAL ETH »Øµ÷IDÃ¶¾Ù¶¨Òå
     */
    typedef enum
    {
        HAL_ETH_MSPINIT_CB_ID = 0x00U,     /*!< ETH MspInit callback ID            */
        HAL_ETH_MSPDEINIT_CB_ID = 0x01U,   /*!< ETH MspDeInit callback ID          */
        HAL_ETH_TX_COMPLETE_CB_ID = 0x02U, /*!< ETH Tx Complete Callback ID        */
        HAL_ETH_RX_COMPLETE_CB_ID = 0x03U, /*!< ETH Rx Complete Callback ID        */
        HAL_ETH_DMA_ERROR_CB_ID = 0x04U,   /*!< ETH DMA Error Callback ID          */

    } HAL_ETH_CallbackIDTypeDef;

    typedef void (*pETH_CallbackTypeDef)(ETH_HandleTypeDef *heth); /*!< pointer to an ETH callback function */

#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

#define ETH_MAX_PACKET_SIZE 1524U     /*!< ETH_HEADER + ETH_EXTRA + ETH_VLAN_TAG + ETH_MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER 14U                /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC 4U                    /*!< Ethernet CRC */
#define ETH_EXTRA 2U                  /*!< Extra bytes in some cases */
#define ETH_VLAN_TAG 4U               /*!< optional 802.1q VLAN Tag */
#define ETH_MIN_ETH_PAYLOAD 46U       /*!< Minimum Ethernet payload size */
#define ETH_MAX_ETH_PAYLOAD 1500U     /*!< Maximum Ethernet payload size */
#define ETH_JUMBO_FRAME_PAYLOAD 9000U /*!< Jumbo frame payload size */

#ifndef ETH_RX_BUF_SIZE
#define ETH_RX_BUF_SIZE ETH_MAX_PACKET_SIZE
#endif

#ifndef ETH_RXBUFNB
#define ETH_RXBUFNB 5U /*  5 Rx buffers of size ETH_RX_BUF_SIZE */
#endif

#ifndef ETH_TX_BUF_SIZE
#define ETH_TX_BUF_SIZE ETH_MAX_PACKET_SIZE
#endif

#ifndef ETH_TXBUFNB
#define ETH_TXBUFNB 5U
#endif

#define ETH_DMATXDESC_OWN 0x80000000U /*!< OWN bit: descriptor is owned by DMA engine */

#define ETH_DMATXDESC_TTSS 0x00020000U /*!< Tx Time Stamp Status */
#define ETH_DMATXDESC_IHE 0x00010000U  /*!< IP Header Error */
#define ETH_DMATXDESC_ES 0x00008000U   /*!< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define ETH_DMATXDESC_JT 0x00004000U   /*!< Jabber Timeout */
#define ETH_DMATXDESC_FF 0x00002000U   /*!< Frame Flushed: DMA/MTL flushed the frame due to SW flush */
#define ETH_DMATXDESC_PCE 0x00001000U  /*!< Payload Checksum Error */
#define ETH_DMATXDESC_LCA 0x00000800U  /*!< Loss of Carrier: carrier lost during transmission */
#define ETH_DMATXDESC_NC 0x00000400U   /*!< No Carrier: no carrier signal from the transceiver */
#define ETH_DMATXDESC_LCO 0x00000200U  /*!< Late Collision: transmission aborted due to collision */
#define ETH_DMATXDESC_EC 0x00000100U   /*!< Excessive Collision: transmission aborted after 16 collisions */
#define ETH_DMATXDESC_VF 0x00000080U   /*!< VLAN Frame */
#define ETH_DMATXDESC_CC 0x00000078U   /*!< Collision Count */
#define ETH_DMATXDESC_ED 0x00000004U   /*!< Excessive Deferral */
#define ETH_DMATXDESC_UF 0x00000002U   /*!< Underflow Error: late data arrival from the memory */
#define ETH_DMATXDESC_DB 0x00000001U   /*!< Deferred Bit */

#define ETH_DMATXDESC_IC 0x80000000U /*!< Interrupt on Completion */
#define ETH_DMATXDESC_LS 0x40000000U /*!< Last Segment */
#define ETH_DMATXDESC_FS 0x20000000U /*!< First Segment */

#define ETH_DMATXDESC_CIC 0x18000000U /*!< Checksum Insertion Control: 4 cases */

#define ETH_DMATXDESC_CIC_BYPASS 0x00000000U             /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMATXDESC_CIC_IPV4HEADER 0x08000000U         /*!< IPV4 header Checksum Insertion */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_SEGMENT 0x10000000U /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATXDESC_CIC_TCPUDPICMP_FULL 0x18000000U    /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */

#define ETH_DMATXDESC_DC 0x04000000U   /*!< Disable CRC */
#define ETH_DMATXDESC_TER 0x02000000U  /*!< Transmit End of Ring */
#define ETH_DMATXDESC_TCH 0x01000000U  /*!< Second Address Chained */
#define ETH_DMATXDESC_DP 0x00800000U   /*!< Disable Padding */
#define ETH_DMATXDESC_TTSE 0x00400000U /*!< Transmit Time Stamp Enable */

#define ETH_DMATXDESC_TBS2 0x003FF800U /*!< Transmit Buffer2 Size */
#define ETH_DMATXDESC_TBS1 0x000007FFU /*!< Transmit Buffer1 Size */
#define ETH_DMATXDESC_B1AP 0xFFFFFFFFU /*!< Buffer1 Address Pointer */

#define ETH_DMATXDESC_B2AP 0xFFFFFFFFU /*!< Buffer2 Address Pointer */

    /*
      DMA Rx
      --------------------------------------------------------------------------------------------------------------------
      RDES0 | OWN(31) |                                             Status [30:0]                                          |
      ---------------------------------------------------------------------------------------------------------------------
      RDES1 | CTRL(31) | Reserved[30:29] | Buffer2 ByteCount[28:16] | CTRL[15:14] | Reserved(13) | Buffer1 ByteCount[12:0] |
      ---------------------------------------------------------------------------------------------------------------------
      RDES2 |                                       Buffer1 Address [31:0]                                                 |
      ---------------------------------------------------------------------------------------------------------------------
      RDES3 |                          Buffer2 Address [31:0] / Next Descriptor Address [31:0]                             |
      ---------------------------------------------------------------------------------------------------------------------
    */

#define ETH_DMARXDESC_OWN 0x80000000U     /*!< OWN bit: descriptor is owned by DMA engine  */
#define ETH_DMARXDESC_AFM 0x40000000U     /*!< DA Filter Fail for the rx frame  */
#define ETH_DMARXDESC_FL 0x3FFF0000U      /*!< Receive descriptor frame length  */
#define ETH_DMARXDESC_ES 0x00008000U      /*!< Error summary: OR of the following bits: DE || OE || IPC || LC || RWT || RE || CE */
#define ETH_DMARXDESC_DE 0x00004000U      /*!< Descriptor error: no more descriptors for receive frame  */
#define ETH_DMARXDESC_SAF 0x00002000U     /*!< SA Filter Fail for the received frame */
#define ETH_DMARXDESC_LE 0x00001000U      /*!< Frame size not matching with length field */
#define ETH_DMARXDESC_OE 0x00000800U      /*!< Overflow Error: Frame was damaged due to buffer overflow */
#define ETH_DMARXDESC_VLAN 0x00000400U    /*!< VLAN Tag: received frame is a VLAN frame */
#define ETH_DMARXDESC_FS 0x00000200U      /*!< First descriptor of the frame  */
#define ETH_DMARXDESC_LS 0x00000100U      /*!< Last descriptor of the frame  */
#define ETH_DMARXDESC_IPV4HCE 0x00000080U /*!< IPC Checksum Error: Rx Ipv4 header checksum error   */
#define ETH_DMARXDESC_LC 0x00000040U      /*!< Late collision occurred during reception   */
#define ETH_DMARXDESC_FT 0x00000020U      /*!< Frame type - Ethernet, otherwise 802.3    */
#define ETH_DMARXDESC_RWT 0x00000010U     /*!< Receive Watchdog Timeout: watchdog timer expired during reception    */
#define ETH_DMARXDESC_RE 0x00000008U      /*!< Receive error: error reported by MII interface  */
#define ETH_DMARXDESC_DBE 0x00000004U     /*!< Dribble bit error: frame contains non int multiple of 8 bits  */
#define ETH_DMARXDESC_CE 0x00000002U      /*!< CRC error */
#define ETH_DMARXDESC_MAMPCE 0x00000001U  /*!< Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error */

#define ETH_DMARXDESC_DIC 0x80000000U  /*!< Disable Interrupt on Completion */
#define ETH_DMARXDESC_RER 0x02000000U  /*!< Receive End of Ring */
#define ETH_DMARXDESC_RCH 0x01000000U  /*!< Second Address Chained */
#define ETH_DMARXDESC_RBS2 0x003FF800U /*!< Receive Buffer2 Size */
#define ETH_DMARXDESC_RBS1 0x000007FFU /*!< Receive Buffer1 Size */

#define ETH_DMARXDESC_B1AP 0xFFFFFFFFU /*!< Buffer1 Address Pointer */

#define ETH_DMARXDESC_B2AP 0xFFFFFFFFU /*!< Buffer2 Address Pointer */

#define ETH_AUTONEGOTIATION_ENABLE 0x00000001U
#define ETH_AUTONEGOTIATION_DISABLE 0x00000000U

#define ETH_SPEED_10M 0x00000000U
#define ETH_SPEED_100M 0x00004000U

#define ETH_MODE_FULLDUPLEX 0x00000800U
#define ETH_MODE_HALFDUPLEX 0x00000000U

#define ETH_RXPOLLING_MODE 0x00000000U
#define ETH_RXINTERRUPT_MODE 0x00000001U

#define ETH_CHECKSUM_BY_HARDWARE 0x00000000U
#define ETH_CHECKSUM_BY_SOFTWARE 0x00000001U

#define ETH_MEDIA_INTERFACE_MII 0x00000000U
#define ETH_MEDIA_INTERFACE_RMII ((uint32_t)SYSCFG_PMC_MII_RMII_SEL)

#define ETH_WATCHDOG_ENABLE 0x00000000U
#define ETH_WATCHDOG_DISABLE 0x00800000U

#define ETH_JABBER_ENABLE 0x00000000U
#define ETH_JABBER_DISABLE 0x00400000U

#define ETH_INTERFRAMEGAP_96BIT 0x00000000U /*!< minimum IFG between frames during transmission is 96Bit */
#define ETH_INTERFRAMEGAP_88BIT 0x00020000U /*!< minimum IFG between frames during transmission is 88Bit */
#define ETH_INTERFRAMEGAP_80BIT 0x00040000U /*!< minimum IFG between frames during transmission is 80Bit */
#define ETH_INTERFRAMEGAP_72BIT 0x00060000U /*!< minimum IFG between frames during transmission is 72Bit */
#define ETH_INTERFRAMEGAP_64BIT 0x00080000U /*!< minimum IFG between frames during transmission is 64Bit */
#define ETH_INTERFRAMEGAP_56BIT 0x000A0000U /*!< minimum IFG between frames during transmission is 56Bit */
#define ETH_INTERFRAMEGAP_48BIT 0x000C0000U /*!< minimum IFG between frames during transmission is 48Bit */
#define ETH_INTERFRAMEGAP_40BIT 0x000E0000U /*!< minimum IFG between frames during transmission is 40Bit */

#define ETH_CARRIERSENCE_ENABLE 0x00000000U
#define ETH_CARRIERSENCE_DISABLE 0x00010000U

#define ETH_RECEIVEOWN_ENABLE 0x00000000U
#define ETH_RECEIVEOWN_DISABLE 0x00002000U

#define ETH_LOOPBACKMODE_ENABLE 0x00001000U
#define ETH_LOOPBACKMODE_DISABLE 0x00000000U

#define ETH_CHECKSUMOFFLAOD_ENABLE 0x00000400U
#define ETH_CHECKSUMOFFLAOD_DISABLE 0x00000000U

#define ETH_RETRYTRANSMISSION_ENABLE 0x00000000U
#define ETH_RETRYTRANSMISSION_DISABLE 0x00000200U

#define ETH_AUTOMATICPADCRCSTRIP_ENABLE 0x00000080U
#define ETH_AUTOMATICPADCRCSTRIP_DISABLE 0x00000000U

#define ETH_BACKOFFLIMIT_10 0x00000000U
#define ETH_BACKOFFLIMIT_8 0x00000020U
#define ETH_BACKOFFLIMIT_4 0x00000040U
#define ETH_BACKOFFLIMIT_1 0x00000060U

#define ETH_DEFFERRALCHECK_ENABLE 0x00000010U
#define ETH_DEFFERRALCHECK_DISABLE 0x00000000U

#define ETH_RECEIVEALL_ENABLE 0x80000000U
#define ETH_RECEIVEAll_DISABLE 0x00000000U

#define ETH_SOURCEADDRFILTER_NORMAL_ENABLE 0x00000200U
#define ETH_SOURCEADDRFILTER_INVERSE_ENABLE 0x00000300U
#define ETH_SOURCEADDRFILTER_DISABLE 0x00000000U

#define ETH_PASSCONTROLFRAMES_BLOCKALL 0x00000040U                /*!< MAC filters all control frames from reaching the application */
#define ETH_PASSCONTROLFRAMES_FORWARDALL 0x00000080U              /*!< MAC forwards all control frames to application even if they fail the Address Filter */
#define ETH_PASSCONTROLFRAMES_FORWARDPASSEDADDRFILTER 0x000000C0U /*!< MAC forwards control frames that pass the Address Filter. */

#define ETH_BROADCASTFRAMESRECEPTION_ENABLE 0x00000000U
#define ETH_BROADCASTFRAMESRECEPTION_DISABLE 0x00000020U

#define ETH_DESTINATIONADDRFILTER_NORMAL 0x00000000U
#define ETH_DESTINATIONADDRFILTER_INVERSE 0x00000008U

#define ETH_PROMISCUOUS_MODE_ENABLE 0x00000001U
#define ETH_PROMISCUOUS_MODE_DISABLE 0x00000000U

#define ETH_MULTICASTFRAMESFILTER_PERFECTHASHTABLE 0x00000404U
#define ETH_MULTICASTFRAMESFILTER_HASHTABLE 0x00000004U
#define ETH_MULTICASTFRAMESFILTER_PERFECT 0x00000000U
#define ETH_MULTICASTFRAMESFILTER_NONE 0x00000010U

#define ETH_UNICASTFRAMESFILTER_PERFECTHASHTABLE 0x00000402U
#define ETH_UNICASTFRAMESFILTER_HASHTABLE 0x00000002U
#define ETH_UNICASTFRAMESFILTER_PERFECT 0x00000000U

#define ETH_ZEROQUANTAPAUSE_ENABLE 0x00000000U
#define ETH_ZEROQUANTAPAUSE_DISABLE 0x00000080U

#define ETH_PAUSELOWTHRESHOLD_MINUS4 0x00000000U   /*!< Pause time minus 4 slot times */
#define ETH_PAUSELOWTHRESHOLD_MINUS28 0x00000010U  /*!< Pause time minus 28 slot times */
#define ETH_PAUSELOWTHRESHOLD_MINUS144 0x00000020U /*!< Pause time minus 144 slot times */
#define ETH_PAUSELOWTHRESHOLD_MINUS256 0x00000030U /*!< Pause time minus 256 slot times */

#define ETH_UNICASTPAUSEFRAMEDETECT_ENABLE 0x00000008U
#define ETH_UNICASTPAUSEFRAMEDETECT_DISABLE 0x00000000U

#define ETH_RECEIVEFLOWCONTROL_ENABLE 0x00000004U
#define ETH_RECEIVEFLOWCONTROL_DISABLE 0x00000000U

#define ETH_TRANSMITFLOWCONTROL_ENABLE 0x00000002U
#define ETH_TRANSMITFLOWCONTROL_DISABLE 0x00000000U

#define ETH_VLANTAGCOMPARISON_12BIT 0x00010000U
#define ETH_VLANTAGCOMPARISON_16BIT 0x00000000U

#define ETH_MAC_ADDRESS0 0x00000000U
#define ETH_MAC_ADDRESS1 0x00000008U
#define ETH_MAC_ADDRESS2 0x00000010U
#define ETH_MAC_ADDRESS3 0x00000018U

#define ETH_MAC_ADDRESSFILTER_SA 0x00000000U
#define ETH_MAC_ADDRESSFILTER_DA 0x00000008U

#define ETH_MAC_ADDRESSMASK_BYTE6 0x20000000U /*!< Mask MAC Address high reg bits [15:8] */
#define ETH_MAC_ADDRESSMASK_BYTE5 0x10000000U /*!< Mask MAC Address high reg bits [7:0] */
#define ETH_MAC_ADDRESSMASK_BYTE4 0x08000000U /*!< Mask MAC Address low reg bits [31:24] */
#define ETH_MAC_ADDRESSMASK_BYTE3 0x04000000U /*!< Mask MAC Address low reg bits [23:16] */
#define ETH_MAC_ADDRESSMASK_BYTE2 0x02000000U /*!< Mask MAC Address low reg bits [15:8] */
#define ETH_MAC_ADDRESSMASK_BYTE1 0x01000000U /*!< Mask MAC Address low reg bits [70] */

#define ETH_DROPTCPIPCHECKSUMERRORFRAME_ENABLE 0x00000000U
#define ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE 0x04000000U

#define ETH_RECEIVESTOREFORWARD_ENABLE 0x02000000U
#define ETH_RECEIVESTOREFORWARD_DISABLE 0x00000000U

#define ETH_FLUSHRECEIVEDFRAME_ENABLE 0x00000000U
#define ETH_FLUSHRECEIVEDFRAME_DISABLE 0x01000000U

#define ETH_TRANSMITSTOREFORWARD_ENABLE 0x00200000U
#define ETH_TRANSMITSTOREFORWARD_DISABLE 0x00000000U

#define ETH_TRANSMITTHRESHOLDCONTROL_64BYTES 0x00000000U  /*!< threshold level of the MTL Transmit FIFO is 64 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_128BYTES 0x00004000U /*!< threshold level of the MTL Transmit FIFO is 128 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_192BYTES 0x00008000U /*!< threshold level of the MTL Transmit FIFO is 192 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_256BYTES 0x0000C000U /*!< threshold level of the MTL Transmit FIFO is 256 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_40BYTES 0x00010000U  /*!< threshold level of the MTL Transmit FIFO is 40 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_32BYTES 0x00014000U  /*!< threshold level of the MTL Transmit FIFO is 32 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_24BYTES 0x00018000U  /*!< threshold level of the MTL Transmit FIFO is 24 Bytes */
#define ETH_TRANSMITTHRESHOLDCONTROL_16BYTES 0x0001C000U  /*!< threshold level of the MTL Transmit FIFO is 16 Bytes */

#define ETH_FORWARDERRORFRAMES_ENABLE 0x00000080U
#define ETH_FORWARDERRORFRAMES_DISABLE 0x00000000U

#define ETH_FORWARDUNDERSIZEDGOODFRAMES_ENABLE 0x00000040U
#define ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE 0x00000000U

#define ETH_RECEIVEDTHRESHOLDCONTROL_64BYTES 0x00000000U  /*!< threshold level of the MTL Receive FIFO is 64 Bytes */
#define ETH_RECEIVEDTHRESHOLDCONTROL_32BYTES 0x00000008U  /*!< threshold level of the MTL Receive FIFO is 32 Bytes */
#define ETH_RECEIVEDTHRESHOLDCONTROL_96BYTES 0x00000010U  /*!< threshold level of the MTL Receive FIFO is 96 Bytes */
#define ETH_RECEIVEDTHRESHOLDCONTROL_128BYTES 0x00000018U /*!< threshold level of the MTL Receive FIFO is 128 Bytes */

#define ETH_SECONDFRAMEOPERARTE_ENABLE 0x00000004U
#define ETH_SECONDFRAMEOPERARTE_DISABLE 0x00000000U

#define ETH_ADDRESSALIGNEDBEATS_ENABLE 0x02000000U
#define ETH_ADDRESSALIGNEDBEATS_DISABLE 0x00000000U

#define ETH_FIXEDBURST_ENABLE 0x00010000U
#define ETH_FIXEDBURST_DISABLE 0x00000000U

#define ETH_RXDMABURSTLENGTH_1BEAT 0x00020000U         /*!< maximum number of beats to be transferred in one RxDMA transaction is 1 */
#define ETH_RXDMABURSTLENGTH_2BEAT 0x00040000U         /*!< maximum number of beats to be transferred in one RxDMA transaction is 2 */
#define ETH_RXDMABURSTLENGTH_4BEAT 0x00080000U         /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RXDMABURSTLENGTH_8BEAT 0x00100000U         /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RXDMABURSTLENGTH_16BEAT 0x00200000U        /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RXDMABURSTLENGTH_32BEAT 0x00400000U        /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RXDMABURSTLENGTH_4XPBL_4BEAT 0x01020000U   /*!< maximum number of beats to be transferred in one RxDMA transaction is 4 */
#define ETH_RXDMABURSTLENGTH_4XPBL_8BEAT 0x01040000U   /*!< maximum number of beats to be transferred in one RxDMA transaction is 8 */
#define ETH_RXDMABURSTLENGTH_4XPBL_16BEAT 0x01080000U  /*!< maximum number of beats to be transferred in one RxDMA transaction is 16 */
#define ETH_RXDMABURSTLENGTH_4XPBL_32BEAT 0x01100000U  /*!< maximum number of beats to be transferred in one RxDMA transaction is 32 */
#define ETH_RXDMABURSTLENGTH_4XPBL_64BEAT 0x01200000U  /*!< maximum number of beats to be transferred in one RxDMA transaction is 64 */
#define ETH_RXDMABURSTLENGTH_4XPBL_128BEAT 0x01400000U /*!< maximum number of beats to be transferred in one RxDMA transaction is 128 */

#define ETH_TXDMABURSTLENGTH_1BEAT 0x00000100U         /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 */
#define ETH_TXDMABURSTLENGTH_2BEAT 0x00000200U         /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 */
#define ETH_TXDMABURSTLENGTH_4BEAT 0x00000400U         /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TXDMABURSTLENGTH_8BEAT 0x00000800U         /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TXDMABURSTLENGTH_16BEAT 0x00001000U        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TXDMABURSTLENGTH_32BEAT 0x00002000U        /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TXDMABURSTLENGTH_4XPBL_4BEAT 0x01000100U   /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 */
#define ETH_TXDMABURSTLENGTH_4XPBL_8BEAT 0x01000200U   /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 */
#define ETH_TXDMABURSTLENGTH_4XPBL_16BEAT 0x01000400U  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 */
#define ETH_TXDMABURSTLENGTH_4XPBL_32BEAT 0x01000800U  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 */
#define ETH_TXDMABURSTLENGTH_4XPBL_64BEAT 0x01001000U  /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 */
#define ETH_TXDMABURSTLENGTH_4XPBL_128BEAT 0x01002000U /*!< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 */

#define ETH_DMAENHANCEDDESCRIPTOR_ENABLE 0x00000080U
#define ETH_DMAENHANCEDDESCRIPTOR_DISABLE 0x00000000U

#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1 0x00000000U
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_2_1 0x00004000U
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_3_1 0x00008000U
#define ETH_DMAARBITRATION_ROUNDROBIN_RXTX_4_1 0x0000C000U
#define ETH_DMAARBITRATION_RXPRIORTX 0x00000002U

#define ETH_DMATXDESC_LASTSEGMENTS 0x40000000U /*!< Last Segment */
#define ETH_DMATXDESC_FIRSTSEGMENT 0x20000000U /*!< First Segment */

#define ETH_DMATXDESC_CHECKSUMBYPASS 0x00000000U            /*!< Checksum engine bypass */
#define ETH_DMATXDESC_CHECKSUMIPV4HEADER 0x08000000U        /*!< IPv4 header checksum insertion  */
#define ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT 0x10000000U /*!< TCP/UDP/ICMP checksum insertion. Pseudo header checksum is assumed to be present */
#define ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL 0x18000000U    /*!< TCP/UDP/ICMP checksum fully in hardware including pseudo header */

#define ETH_DMARXDESC_BUFFER1 0x00000000U /*!< DMA Rx Desc Buffer1 */
#define ETH_DMARXDESC_BUFFER2 0x00000001U /*!< DMA Rx Desc Buffer2 */

#define ETH_PMT_FLAG_WUFFRPR 0x80000000U /*!< Wake-Up Frame Filter Register Pointer Reset */
#define ETH_PMT_FLAG_WUFR 0x00000040U    /*!< Wake-Up Frame Received */
#define ETH_PMT_FLAG_MPR 0x00000020U     /*!< Magic Packet Received */

#define ETH_MMC_IT_TGF 0x00200000U    /*!< When Tx good frame counter reaches half the maximum value */
#define ETH_MMC_IT_TGFMSC 0x00008000U /*!< When Tx good multi col counter reaches half the maximum value */
#define ETH_MMC_IT_TGFSC 0x00004000U  /*!< When Tx good single col counter reaches half the maximum value */

#define ETH_MMC_IT_RGUF 0x10020000U /*!< When Rx good unicast frames counter reaches half the maximum value */
#define ETH_MMC_IT_RFAE 0x10000040U /*!< When Rx alignment error counter reaches half the maximum value */
#define ETH_MMC_IT_RFCE 0x10000020U /*!< When Rx crc error counter reaches half the maximum value */

#define ETH_MAC_FLAG_TST 0x00000200U  /*!< Time stamp trigger flag (on MAC) */
#define ETH_MAC_FLAG_MMCT 0x00000040U /*!< MMC transmit flag  */
#define ETH_MAC_FLAG_MMCR 0x00000020U /*!< MMC receive flag */
#define ETH_MAC_FLAG_MMC 0x00000010U  /*!< MMC flag (on MAC) */
#define ETH_MAC_FLAG_PMT 0x00000008U  /*!< PMT flag (on MAC) */

#define ETH_DMA_FLAG_BBF 0x80000000U               /*!< CRMBBF: buffer B is full in continuous rx data mode */
#define ETH_DMA_FLAG_BAF 0x40000000U               /*!< CRMBBF: buffer A is full in continuous rx data mode */
#define ETH_DMA_FLAG_TST 0x20000000U               /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_FLAG_PMT 0x10000000U               /*!< PMT interrupt (on DMA) */
#define ETH_DMA_FLAG_MMC 0x08000000U               /*!< MMC interrupt (on DMA) */
#define ETH_DMA_FLAG_DATATRANSFERERROR 0x00800000U /*!< Error bits 0-Rx DMA, 1-Tx DMA */
#define ETH_DMA_FLAG_READWRITEERROR 0x01000000U    /*!< Error bits 0-write transfer, 1-read transfer */
#define ETH_DMA_FLAG_ACCESSERROR 0x02000000U       /*!< Error bits 0-data buffer, 1-desc. access */
#define ETH_DMA_FLAG_NIS 0x00010000U               /*!< Normal interrupt summary flag */
#define ETH_DMA_FLAG_AIS 0x00008000U               /*!< Abnormal interrupt summary flag */
#define ETH_DMA_FLAG_ER 0x00004000U                /*!< Early receive flag */
#define ETH_DMA_FLAG_FBE 0x00002000U               /*!< Fatal bus error flag */
#define ETH_DMA_FLAG_ET 0x00000400U                /*!< Early transmit flag */
#define ETH_DMA_FLAG_RWT 0x00000200U               /*!< Receive watchdog timeout flag */
#define ETH_DMA_FLAG_RPS 0x00000100U               /*!< Receive process stopped flag */
#define ETH_DMA_FLAG_RBU 0x00000080U               /*!< Receive buffer unavailable flag */
#define ETH_DMA_FLAG_R 0x00000040U                 /*!< Receive flag */
#define ETH_DMA_FLAG_TU 0x00000020U                /*!< Underflow flag */
#define ETH_DMA_FLAG_RO 0x00000010U                /*!< Overflow flag */
#define ETH_DMA_FLAG_TJT 0x00000008U               /*!< Transmit jabber timeout flag */
#define ETH_DMA_FLAG_TBU 0x00000004U               /*!< Transmit buffer unavailable flag */
#define ETH_DMA_FLAG_TPS 0x00000002U               /*!< Transmit process stopped flag */
#define ETH_DMA_FLAG_T 0x00000001U                 /*!< Transmit flag */

#define ETH_MAC_IT_TST 0x00000200U  /*!< Time stamp trigger interrupt (on MAC) */
#define ETH_MAC_IT_MMCT 0x00000040U /*!< MMC transmit interrupt */
#define ETH_MAC_IT_MMCR 0x00000020U /*!< MMC receive interrupt */
#define ETH_MAC_IT_MMC 0x00000010U  /*!< MMC interrupt (on MAC) */
#define ETH_MAC_IT_PMT 0x00000008U  /*!< PMT interrupt (on MAC) */

#define ETH_DMA_IT_BBF 0x80000000U /*!< CRMBBFIE: Buffer B full status interrupt enable, set to enable the status to generate Abnormal interrupt */
#define ETH_DMA_IT_BAF 0x40000000U /*!< CRMBBFIE: Buffer A full status interrupt enable, set to enable the status to generate Abnormal interrupt */
#define ETH_DMA_IT_TST 0x20000000U /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_IT_TST 0x20000000U /*!< Time-stamp trigger interrupt (on DMA) */
#define ETH_DMA_IT_PMT 0x10000000U /*!< PMT interrupt (on DMA) */
#define ETH_DMA_IT_MMC 0x08000000U /*!< MMC interrupt (on DMA) */
#define ETH_DMA_IT_NIS 0x00010000U /*!< Normal interrupt summary */
#define ETH_DMA_IT_AIS 0x00008000U /*!< Abnormal interrupt summary */
#define ETH_DMA_IT_ER 0x00004000U  /*!< Early receive interrupt */
#define ETH_DMA_IT_FBE 0x00002000U /*!< Fatal bus error interrupt */
#define ETH_DMA_IT_ET 0x00000400U  /*!< Early transmit interrupt */
#define ETH_DMA_IT_RWT 0x00000200U /*!< Receive watchdog timeout interrupt */
#define ETH_DMA_IT_RPS 0x00000100U /*!< Receive process stopped interrupt */
#define ETH_DMA_IT_RBU 0x00000080U /*!< Receive buffer unavailable interrupt */
#define ETH_DMA_IT_R 0x00000040U   /*!< Receive interrupt */
#define ETH_DMA_IT_TU 0x00000020U  /*!< Underflow interrupt */
#define ETH_DMA_IT_RO 0x00000010U  /*!< Overflow interrupt */
#define ETH_DMA_IT_TJT 0x00000008U /*!< Transmit jabber timeout interrupt */
#define ETH_DMA_IT_TBU 0x00000004U /*!< Transmit buffer unavailable interrupt */
#define ETH_DMA_IT_TPS 0x00000002U /*!< Transmit process stopped interrupt */
#define ETH_DMA_IT_T 0x00000001U   /*!< Transmit interrupt */

#define ETH_DMA_TRANSMITPROCESS_STOPPED 0x00000000U   /*!< Stopped - Reset or Stop Tx Command issued */
#define ETH_DMA_TRANSMITPROCESS_FETCHING 0x00100000U  /*!< Running - fetching the Tx descriptor */
#define ETH_DMA_TRANSMITPROCESS_WAITING 0x00200000U   /*!< Running - waiting for status */
#define ETH_DMA_TRANSMITPROCESS_READING 0x00300000U   /*!< Running - reading the data from host memory */
#define ETH_DMA_TRANSMITPROCESS_SUSPENDED 0x00600000U /*!< Suspended - Tx Descriptor unavailable */
#define ETH_DMA_TRANSMITPROCESS_CLOSING 0x00700000U   /*!< Running - closing Rx descriptor */

#define ETH_DMA_RECEIVEPROCESS_STOPPED 0x00000000U   /*!< Stopped - Reset or Stop Rx Command issued */
#define ETH_DMA_RECEIVEPROCESS_FETCHING 0x00020000U  /*!< Running - fetching the Rx descriptor */
#define ETH_DMA_RECEIVEPROCESS_WAITING 0x00060000U   /*!< Running - waiting for packet */
#define ETH_DMA_RECEIVEPROCESS_SUSPENDED 0x00080000U /*!< Suspended - Rx Descriptor unavailable */
#define ETH_DMA_RECEIVEPROCESS_CLOSING 0x000A0000U   /*!< Running - closing descriptor */
#define ETH_DMA_RECEIVEPROCESS_QUEUING 0x000E0000U   /*!< Running - queuing the receive frame into host memory */

#define ETH_DMA_OVERFLOW_RXFIFOCOUNTER 0x10000000U      /*!< Overflow bit for FIFO overflow counter */
#define ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER 0x00010000U /*!< Overflow bit for missed frame counter */

#define ETH_EXTI_LINE_WAKEUP 0x00080000U /*!< External interrupt line 19 Connected to the ETH EXTI Line */

#if (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
#define __HAL_ETH_RESET_HANDLE_STATE(__HANDLE__)   \
    do                                             \
    {                                              \
        (__HANDLE__)->State = HAL_ETH_STATE_RESET; \
        (__HANDLE__)->MspInitCallback = NULL;      \
        (__HANDLE__)->MspDeInitCallback = NULL;    \
    } while (0)
#else
#define __HAL_ETH_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ETH_STATE_RESET)
#endif /*USE_HAL_ETH_REGISTER_CALLBACKS */

#define __HAL_ETH_DMATXDESC_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->TxDesc->Status & (__FLAG__) == (__FLAG__))

#define __HAL_ETH_DMARXDESC_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->RxDesc->Status & (__FLAG__) == (__FLAG__))

#define __HAL_ETH_DMARXDESC_ENABLE_IT(__HANDLE__) ((__HANDLE__)->RxDesc->ControlBufferSize &= (~(uint32_t)ETH_DMARXDESC_DIC))

#define __HAL_ETH_DMARXDESC_DISABLE_IT(__HANDLE__) ((__HANDLE__)->RxDesc->ControlBufferSize |= ETH_DMARXDESC_DIC)

#define __HAL_ETH_DMARXDESC_SET_OWN_BIT(__HANDLE__) ((__HANDLE__)->RxDesc->Status |= ETH_DMARXDESC_OWN)

#define __HAL_ETH_DMATXDESC_GET_COLLISION_COUNT(__HANDLE__) (((__HANDLE__)->TxDesc->Status & ETH_DMATXDESC_CC) >> ETH_DMATXDESC_COLLISION_COUNTSHIFT)

#define __HAL_ETH_DMATXDESC_SET_OWN_BIT(__HANDLE__) ((__HANDLE__)->TxDesc->Status |= ETH_DMATXDESC_OWN)

#define __HAL_ETH_DMATXDESC_ENABLE_IT(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize |= ETH_DMATXDESC_IC)

#define __HAL_ETH_DMATXDESC_DISABLE_IT(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize &= ~ETH_DMATXDESC_IC)

#define __HAL_ETH_DMATXDESC_CHECKSUM_INSERTION(__HANDLE__, __CHECKSUM__) ((__HANDLE__)->TxDesc->Status |= (__CHECKSUM__))

#define __HAL_ETH_DMATXDESC_CRC_ENABLE(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize &= ~ETH_DMATXDESC_DC)

#define __HAL_ETH_DMATXDESC_CRC_DISABLE(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize |= ETH_DMATXDESC_DC)

#define __HAL_ETH_DMATXDESC_SHORT_FRAME_PADDING_ENABLE(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize &= ~ETH_DMATXDESC_DP)

#define __HAL_ETH_DMATXDESC_SHORT_FRAME_PADDING_DISABLE(__HANDLE__) ((__HANDLE__)->TxDesc->ControlBufferSize |= ETH_DMATXDESC_DP)

#define __HAL_ETH_MAC_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->MACIMR |= (__INTERRUPT__))

#define __HAL_ETH_MAC_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->MACIMR &= ~(__INTERRUPT__))

#define __HAL_ETH_INITIATE_PAUSE_CONTROL_FRAME(__HANDLE__) ((__HANDLE__)->Instance->MACFCR |= ETH_MACFCR_FCBBPA)

#define __HAL_ETH_GET_FLOW_CONTROL_BUSY_STATUS(__HANDLE__) (((__HANDLE__)->Instance->MACFCR & ETH_MACFCR_FCBBPA) == ETH_MACFCR_FCBBPA)

#define __HAL_ETH_BACK_PRESSURE_ACTIVATION_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MACFCR |= ETH_MACFCR_FCBBPA)

#define __HAL_ETH_BACK_PRESSURE_ACTIVATION_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MACFCR &= ~ETH_MACFCR_FCBBPA)

#define __HAL_ETH_MAC_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->MACSR & (__FLAG__)) == (__FLAG__))

#define __HAL_ETH_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->DMAIER |= (__INTERRUPT__))

#define __HAL_ETH_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->DMAIER &= ~(__INTERRUPT__))

#define __HAL_ETH_DMA_CLEAR_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->DMASR = (__INTERRUPT__))

#define __HAL_ETH_DMA_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->DMASR & (__FLAG__)) == (__FLAG__))

#define __HAL_ETH_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->DMASR = (__FLAG__))

#define __HAL_ETH_GET_DMA_OVERFLOW_STATUS(__HANDLE__, __OVERFLOW__) (((__HANDLE__)->Instance->DMAMFBOCR & (__OVERFLOW__)) == (__OVERFLOW__))

#define __HAL_ETH_SET_RECEIVE_WATCHDOG_TIMER(__HANDLE__, __VALUE__) ((__HANDLE__)->Instance->DMARSWTR = (__VALUE__))

#define __HAL_ETH_GLOBAL_UNICAST_WAKEUP_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR |= ETH_MACPMTCSR_GU)

#define __HAL_ETH_GLOBAL_UNICAST_WAKEUP_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR &= ~ETH_MACPMTCSR_GU)

#define __HAL_ETH_WAKEUP_FRAME_DETECTION_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR |= ETH_MACPMTCSR_WFE)

#define __HAL_ETH_WAKEUP_FRAME_DETECTION_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR &= ~ETH_MACPMTCSR_WFE)

#define __HAL_ETH_MAGIC_PACKET_DETECTION_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR |= ETH_MACPMTCSR_MPE)

#define __HAL_ETH_MAGIC_PACKET_DETECTION_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR &= ~ETH_MACPMTCSR_WFE)

#define __HAL_ETH_POWER_DOWN_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR |= ETH_MACPMTCSR_PD)

#define __HAL_ETH_POWER_DOWN_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MACPMTCSR &= ~ETH_MACPMTCSR_PD)

#define __HAL_ETH_GET_PMT_FLAG_STATUS(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->MACPMTCSR & (__FLAG__)) == (__FLAG__))

#define __HAL_ETH_MMC_COUNTER_FULL_PRESET(__HANDLE__) ((__HANDLE__)->Instance->MMCCR |= (ETH_MMCCR_MCFHP | ETH_MMCCR_MCP))

#define __HAL_ETH_MMC_COUNTER_HALF_PRESET(__HANDLE__)      \
    do                                                     \
    {                                                      \
        (__HANDLE__)->Instance->MMCCR &= ~ETH_MMCCR_MCFHP; \
        (__HANDLE__)->Instance->MMCCR |= ETH_MMCCR_MCP;    \
    } while (0)

#define __HAL_ETH_MMC_COUNTER_FREEZE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR |= ETH_MMCCR_MCF)

#define __HAL_ETH_MMC_COUNTER_FREEZE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR &= ~ETH_MMCCR_MCF)

#define __HAL_ETH_ETH_MMC_RESET_ONREAD_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR |= ETH_MMCCR_ROR)

#define __HAL_ETH_ETH_MMC_RESET_ONREAD_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR &= ~ETH_MMCCR_ROR)

#define __HAL_ETH_ETH_MMC_COUNTER_ROLLOVER_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR &= ~ETH_MMCCR_CSR)

#define __HAL_ETH_ETH_MMC_COUNTER_ROLLOVER_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->MMCCR |= ETH_MMCCR_CSR)

#define __HAL_ETH_MMC_COUNTERS_RESET(__HANDLE__) ((__HANDLE__)->Instance->MMCCR |= ETH_MMCCR_CR)

#define __HAL_ETH_MMC_RX_IT_ENABLE(__HANDLE__, __INTERRUPT__) (__HANDLE__)->Instance->MMCRIMR &= ~((__INTERRUPT__) & 0xFFFFFFFFU)

#define __HAL_ETH_MMC_RX_IT_DISABLE(__HANDLE__, __INTERRUPT__) (__HANDLE__)->Instance->MMCRIMR |= ((__INTERRUPT__) & 0xFFFFFFFFU)

#define __HAL_ETH_MMC_IPC_IT_DISABLE(__HANDLE__, __INTERRUPT__) (__HANDLE__)->Instance->MMCIPCINTMASKRX |= ((__INTERRUPT__) & 0xFFFFFFFFU) // jshi add 2020.09.25

#define __HAL_ETH_MMC_TX_IT_ENABLE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->MMCTIMR &= ~(__INTERRUPT__))

#define __HAL_ETH_MMC_TX_IT_DISABLE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->MMCTIMR |= (__INTERRUPT__))

#define __HAL_ETH_WAKEUP_EXTI_ENABLE_IT() EXTI->IMR |= (ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_DISABLE_IT() EXTI->IMR &= ~(ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_ENABLE_EVENT() EXTI->EMR |= (ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_DISABLE_EVENT() EXTI->EMR &= ~(ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_GET_FLAG() EXTI->PR &(ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_CLEAR_FLAG() EXTI->PR = (ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_ENABLE_RISING_EDGE_TRIGGER() EXTI->RTSR |= ETH_EXTI_LINE_WAKEUP

#define __HAL_ETH_WAKEUP_EXTI_DISABLE_RISING_EDGE_TRIGGER() EXTI->RTSR &= ~(ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_ENABLE_FALLING_EDGE_TRIGGER() EXTI->FTSR |= (ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_DISABLE_FALLING_EDGE_TRIGGER() EXTI->FTSR &= ~(ETH_EXTI_LINE_WAKEUP)

#define __HAL_ETH_WAKEUP_EXTI_ENABLE_FALLINGRISING_TRIGGER() \
    do                                                       \
    {                                                        \
        EXTI->RTSR |= ETH_EXTI_LINE_WAKEUP;                  \
        EXTI->FTSR |= ETH_EXTI_LINE_WAKEUP;                  \
    } while (0U)

#define __HAL_ETH_WAKEUP_EXTI_DISABLE_FALLINGRISING_TRIGGER() \
    do                                                        \
    {                                                         \
        EXTI->RTSR &= ~(ETH_EXTI_LINE_WAKEUP);                \
        EXTI->FTSR &= ~(ETH_EXTI_LINE_WAKEUP);                \
    } while (0U)

#define __HAL_ETH_WAKEUP_EXTI_GENERATE_SWIT() EXTI->SWIER |= ETH_EXTI_LINE_WAKEUP

    // 函数声明
    status_t HAL_ETH_Init(ETH_HandleTypeDef *heth);
    status_t HAL_ETH_DeInit(ETH_HandleTypeDef *heth);
    void HAL_ETH_MspInit(ETH_HandleTypeDef *heth);
    void HAL_ETH_MspDeInit(ETH_HandleTypeDef *heth);
    status_t HAL_ETH_DMATxDescListInit(ETH_HandleTypeDef *heth, ETH_DMADescTypeDef *DMATxDescTab, uint8_t *TxBuff, uint32_t TxBuffCount);
    status_t HAL_ETH_DMARxDescListInit(ETH_HandleTypeDef *heth, ETH_DMADescTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount);
/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    HAL_StatusTypeDef HAL_ETH_RegisterCallback(ETH_HandleTypeDef *heth, HAL_ETH_CallbackIDTypeDef CallbackID, pETH_CallbackTypeDef pCallback);
    HAL_StatusTypeDef HAL_ETH_UnRegisterCallback(ETH_HandleTypeDef *heth, HAL_ETH_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    status_t HAL_ETH_TransmitFrame(ETH_HandleTypeDef *heth, uint32_t FrameLength);
    status_t HAL_ETH_GetReceivedFrame(ETH_HandleTypeDef *heth);
    /* Communication with PHY functions*/
    status_t HAL_ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint16_t PHYReg, uint32_t *RegValue);
    status_t HAL_ETH_WritePHYRegister(ETH_HandleTypeDef *heth, uint16_t PHYReg, uint32_t RegValue);
    /* Non-Blocking mode: Interrupt */
    status_t HAL_ETH_GetReceivedFrame_IT(ETH_HandleTypeDef *heth);
    void HAL_ETH_IRQHandler(ETH_HandleTypeDef *heth);
    /* Callback in non blocking modes (Interrupt) */
    void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth);
    void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth);
    void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth);
    status_t HAL_ETH_Start(ETH_HandleTypeDef *heth);
    status_t HAL_ETH_Stop(ETH_HandleTypeDef *heth);
    status_t HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *macconf);
    status_t HAL_ETH_ConfigDMA(ETH_HandleTypeDef *heth, ETH_DMAInitTypeDef *dmaconf);
    HAL_ETH_StateTypeDef HAL_ETH_GetState(ETH_HandleTypeDef *heth);

#ifdef __cplusplus
}
#endif

#endif