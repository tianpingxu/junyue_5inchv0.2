/**
 * @file can_drv.h
 * @author Product application department
 * @brief  CNA 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __CAN_DRV_H
#define __CAN_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "ioctrl_drv.h"
#include <stdbool.h>
#include "can_reg.h"
#include "status.h"
    
    // 全局变量定义
#define CAN_BUFFER_NUM (64)
#define CAN_RXIMR_ADDR_OFFSET (0x880)
#define CAN_FIFO_ID_TABLE_ADDR_OFFSET (0x0E0)

// MCR register
#define _can_en_module_disable_mode(can) _bit_set(can->CAN_MCR, CAN_MCR_MDIS)
#define _can_dis_module_disable_mode(can) _bit_clr(can->CAN_MCR, CAN_MCR_MDIS)
#define _can_en_generate_wrn_int_flag(can) _bit_set(can->CAN_MCR, CAN_MCR_WRN_EN)
#define _can_dis_generate_wrn_int_flag(can) _bit_clr(can->CAN_MCR, CAN_MCR_WRN_EN)
#define _can_en_soft_rst(can) _bit_set(can->CAN_MCR, CAN_MCR_SOFT_RST)
#define _can_en_support_previous_versions(can) _bit_set(can->CAN_MCR, CAN_MCR_BCC)
#define _can_dis_support_previous_versions(can) _bit_clr(can->CAN_MCR, CAN_MCR_BCC)
#define _can_en_all_message_buffers(can) _bit_set(can->CAN_MCR, CAN_MCR_MAXMB)
#define _can_en_fifo(can) _bit_set(can->CAN_MCR, CAN_MCR_FEN)
#define _can_dis_fifo(can) _bit_clr(can->CAN_MCR, CAN_MCR_FEN)
#define _can_exit_freeze_mode(can) _bit_clr(can->CAN_MCR, (CAN_MCR_HALT | CAN_MCR_FRZ))
#define _can_enter_freeze_mode(can) _bit_set(can->CAN_MCR, (CAN_MCR_HALT | CAN_MCR_FRZ))

// CR register
#define _can_select_peripheral_clock(can) _bit_set(can->CAN_CR, CAN_CR_CLK_SRC)
#define _can_select_crystal_oscillator_clock(can) _bit_clr(can->CAN_CR, CAN_CR_CLK_SRC)
#define _can_select_loop_back_mode(can) _bit_set(can->CAN_CR, CAN_CR_LPB)
#define _can_select_normal_mode(can) _bit_clr(can->CAN_CR, CAN_CR_LPB)
#define _can_en_listen_only_mode(can) _bit_set(can->CAN_CR, CAN_CR_LOM)
#define _can_dis_listen_only_mode(can) _bit_clr(can->CAN_CR, CAN_CR_LOM)
#define _can_lowest_buf_num_first(can) _bit_set(can->CAN_CR, CAN_CR_LBUF)
#define _can_lowest_id_num_first(can) _bit_clr(can->CAN_CR, CAN_CR_LBUF)

// SR register
#define _can_get_esr_val(can) _reg_read(can->CAN_ESR)
#define _can_get_buss_off_int_flag(can) _reg_chk(can->CAN_ESR, CAN_ESR_BOFF_INT)
#define _can_clr_buss_off_int_flag(can) _bit_set(can->CAN_ESR, CAN_ESR_BOFF_INT)
#define _can_get_twrn_int_flag(can) _reg_chk(can->CAN_ESR, CAN_ESR_TWRN_INT)
#define _can_clr_twrn_int_flag(can) _bit_set(can->CAN_ESR, CAN_ESR_TWRN_INT)
#define _can_get_rwrn_int_flag(can) _reg_chk(can->CAN_ESR, CAN_ESR_RWRN_INT)
#define _can_clr_rwrn_int_flag(can) _bit_set(can->CAN_ESR, CAN_ESR_RWRN_INT)
#define _can_get_err_int_flag(can) _reg_chk(can->CAN_ESR, CAN_ESR_ERR_INT)
#define _can_clr_err_int_flag(can) _bit_set(can->CAN_ESR, CAN_ESR_ERR_INT)

// FRT register
#define _can_set_free_time(can, val) _reg_write(can->CAN_FRT, val);
#define _can_get_free_time(can) _reg_read(can->CAN_FRT);

// IMASK register
#define _can_en_mb0_31_int(can) _reg_write(can->CAN_IM1R, 0xffffffff)
#define _can_en_mb32_63_int(can) _reg_write(can->CAN_IM2R, 0xffffffff)
#define _can_dis_mb0_31_int(can) _reg_write(can->CAN_IM1R, 0)
#define _can_dis_mb32_63_int(can) _reg_write(can->CAN_IM2R, 0)

// IFR register
#define _can_get_mb0_31_int_flag(can) _reg_read(can->CAN_IF1R)
#define _can_get_mb32_63_int_flag(can) _reg_read(can->CAN_IF2R)
#define _can_clr_mb0_31_int_flag(can, val) _bit_set(can->CAN_IF1R, val)
#define _can_clr_mb32_63_int_flag(can, val) _bit_set(can->CAN_IF2R, val)

#define BIG_LITTLE_SWAP32(x) ((((*(long int *)&x) & 0xff000000) >> 24) | \
                              (((*(long int *)&x) & 0x00ff0000) >> 8) |  \
                              (((*(long int *)&x) & 0x0000ff00) << 8) |  \
                              (((*(long int *)&x) & 0x000000ff) << 24))

/**
 * @brief CAN 模块标志类型枚举定义
 * 
 */
typedef enum
{
    DRV_CAN_ID_STD = 0x00000000U,
    DRV_CAN_ID_EXT = 0x00200000U,
} can_ide_t;

/**
 * @brief  CAN 模块远程传输请求枚举定义
 * 
 */
 typedef enum
{
    DRV_CAN_RTR_DATA = 0x00000000U,
    DRV_CAN_RTR_REMOTE = 0x00100000U,
} can_rtp_t;

/**
 * @brief CAN 模块发送信息结构体定义
 * 
 */
typedef struct
{
    uint32_t StdId; /*!< Specifies the standard identifier.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF */
    uint32_t ExtId; /*!< Specifies the extended identifier.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF */
    can_ide_t IDE;  /*!< Specifies the type of identifier for the message that will be transmitted.
                                   This parameter can be a value of @ref CAN_Identifier_Type */
    can_rtp_t RTR;  /*!< Specifies the type of frame for the message that will be transmitted.
                                   This parameter can be a value of @ref CAN_remote_transmission_request */
    uint32_t DLC;   /*!< Specifies the length of the frame that will be transmitted.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 8 */
        /*!< Contains the data to be transmitted.
            This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF */
    union
     {
         struct
         {
            uint32_t word0;
                uint32_t word1;
         };
         struct
         {
            uint8_t BYTE3; /*!< CAN Frame payload byte3. */
            uint8_t BYTE2; /*!< CAN Frame payload byte2. */
            uint8_t BYTE1; /*!< CAN Frame payload byte1. */
            uint8_t BYTE0; /*!< CAN Frame payload byte0. */
            uint8_t BYTE7; /*!< CAN Frame payload byte7. */
            uint8_t BYTE6; /*!< CAN Frame payload byte6. */
            uint8_t BYTE5; /*!< CAN Frame payload byte5. */
            uint8_t BYTE4; /*!< CAN Frame payload byte4. */
        };
    };

} can_txmsg_t;

/**
 * @brief CAN 模块接收信息结构体定义
 * 
 */
typedef struct
{
    uint32_t StdId; /*!< Specifies the standard identifier.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF */
    uint32_t ExtId; /*!< Specifies the extended identifier.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF */
    can_ide_t IDE;  /*!< Specifies the type of identifier for the message that will be received.
                                    This parameter can be a value of @ref CAN_Identifier_Type */
    can_rtp_t RTR;  /*!< Specifies the type of frame for the received message.
                                    This parameter can be a value of @ref CAN_remote_transmission_request */
    uint32_t DLC;   /*!< Specifies the length of the frame that will be received.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 8 */
                        /*!< Contains the data to be received.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF */
    union
    {
        struct
        {
            uint32_t word0;
            uint32_t word1;
        };
        struct
        {
            uint8_t BYTE3; /*!< CAN Frame payload byte3. */
            uint8_t BYTE2; /*!< CAN Frame payload byte2. */
            uint8_t BYTE1; /*!< CAN Frame payload byte1. */
            uint8_t BYTE0; /*!< CAN Frame payload byte0. */
            uint8_t BYTE7; /*!< CAN Frame payload byte7. */
            uint8_t BYTE6; /*!< CAN Frame payload byte6. */
            uint8_t BYTE5; /*!< CAN Frame payload byte5. */
            uint8_t BYTE4; /*!< CAN Frame payload byte4. */
        };
    };
    uint32_t RXIM; /*!< Specifies the RX individual mask. */
    uint32_t MBID; /*!< Specifies the MB number.
                            This parameter can be 0 to 32*/
} can_rxmsg_t;

/**
 * @brief  CAN 模块初始化结构体定义
 * 
 */
typedef struct
{
    uint32_t BitRate; /**< CAN模块配置的位速率 */
    uint32_t FEN;     /**< Enable or disable the FIFO .
                               This parameter can be set to ENABLE or DISABLE */
    uint32_t IPSFreq; /**< CAN模块时钟频率 */

} can_init_t, *pcan_init_t;

/**
 * @brief CAN 速率结构体定义
 * 
 */
typedef struct
{
    uint8_t m_propseg; /*CAN control register propseg area*/
    uint8_t m_pseg1;   /*CAN control register pseg1 area*/
    uint8_t m_pseg2;   /*CAN control register pseg2 area*/
} can_timeseg;

// 函数声明
status_t drv_can_init(reg_can_t *pcan, can_init_t *Init);
void drv_can_deinit(reg_can_t *pcan);
status_t drv_can_transmitbytes(reg_can_t *pcan, can_txmsg_t *pTxmsg, uint32_t Timeout);
status_t drv_can_receivebytes(reg_can_t *pcan, can_rxmsg_t *pRxmsg, uint32_t rx_num, uint32_t Timeout);
status_t drv_can_fifo_receivebytes(reg_can_t *pcan, can_rxmsg_t *pRxmsg, uint32_t rx_num, uint32_t Timeout);
void drv_can_enablefreezemode(reg_can_t *pcan, bool enable);
void drv_can_select_crystal_oscillator(reg_can_t *pcan);

#ifdef __cplusplus
}
#endif

#endif
