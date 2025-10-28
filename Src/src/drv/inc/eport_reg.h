/**
 * @file eport_reg.h
 * @author Product application department
 * @brief  EPORT 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __EPORT_REG_H_
#define __EPORT_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define EPORT0 ((reg_eport_t *)EPORT0_BASE_ADDR)
#define EPORT1 ((reg_eport_t *)EPORT1_BASE_ADDR)
#define EPORT2 ((reg_eport_t *)EPORT2_BASE_ADDR)
#define EPORT3 ((reg_eport_t *)EPORT3_BASE_ADDR)
#define EPORT4 ((reg_eport_t *)EPORT4_BASE_ADDR)
#define EPORT5 ((reg_eport_t *)EPORT5_BASE_ADDR)
#define EPORT6 ((reg_eport_t *)EPORT6_BASE_ADDR)
#define EPORT7 ((reg_eport_t *)EPORT7_BASE_ADDR)
#define EPORT8 ((reg_eport_t *)EPORT8_BASE_ADDR)
#define EPORT9 ((reg_eport_t *)EPORT9_BASE_ADDR)
#define EPORT0_BASE_ADDR (0x40019000) /**< EPORT寄存器基地址 */
#define EPORT1_BASE_ADDR (0x4001A000) /**< EPORT1寄存器基地址 */
#define EPORT2_BASE_ADDR (0x40024000) /**< EPORT2寄存器基地址 */
#define EPORT3_BASE_ADDR (0x40025000) /**< EPORT3寄存器基地址 */
#define EPORT4_BASE_ADDR (0x40026000) /**< EPORT4寄存器基地址 */
#define EPORT5_BASE_ADDR (0x40027000) /**< EPORT5寄存器基地址 */
#define EPORT6_BASE_ADDR (0x40028000) /**< EPORT6寄存器基地址 */
#define EPORT7_BASE_ADDR (0x40029000) /**< EPORT7寄存器基地址 */
#define EPORT8_BASE_ADDR (0x40022000) /**< EPORT8寄存器基地址 */
#define EPORT9_BASE_ADDR (0x40023000) /**< EPORT9寄存器基地址 */

// EPPAR
#define EPORT_EPPAR_EPPA0 (0)
#define EPORT_EPPAR_EPPA1 (2)
#define EPORT_EPPAR_EPPA2 (4)
#define EPORT_EPPAR_EPPA3 (6)
#define EPORT_EPPAR_EPPA4 (8)
#define EPORT_EPPAR_EPPA5 (10)
#define EPORT_EPPAR_EPPA6 (12)
#define EPORT_EPPAR_EPPA7 (14)

// EPDDR
#define EPORT_EPDDR_EPDD (0)
#define EPORT_EPDDR_EPDD0 ((uint32_t)1 << 0)
#define EPORT_EPDDR_EPDD1 ((uint32_t)1 << 1)
#define EPORT_EPDDR_EPDD2 ((uint32_t)1 << 2)
#define EPORT_EPDDR_EPDD3 ((uint32_t)1 << 3)
#define EPORT_EPDDR_EPDD4 ((uint32_t)1 << 4)
#define EPORT_EPDDR_EPDD5 ((uint32_t)1 << 5)
#define EPORT_EPDDR_EPDD6 ((uint32_t)1 << 6)
#define EPORT_EPDDR_EPDD7 ((uint32_t)1 << 7)

// EPIER
#define EPORT_EPIER_EPIE (0)
#define EPORT_EPIER_EPIE0 ((uint32_t)1 << 0)
#define EPORT_EPIER_EPIE1 ((uint32_t)1 << 1)
#define EPORT_EPIER_EPIE2 ((uint32_t)1 << 2)
#define EPORT_EPIER_EPIE3 ((uint32_t)1 << 3)
#define EPORT_EPIER_EPIE4 ((uint32_t)1 << 4)
#define EPORT_EPIER_EPIE5 ((uint32_t)1 << 5)
#define EPORT_EPIER_EPIE6 ((uint32_t)1 << 6)
#define EPORT_EPIER_EPIE7 ((uint32_t)1 << 7)

// EPDR
#define EPORT_EPDR_EPD (0)
#define EPORT_EPDR_EPD0 ((uint32_t)1 << 0)
#define EPORT_EPDR_EPD1 ((uint32_t)1 << 1)
#define EPORT_EPDR_EPD2 ((uint32_t)1 << 2)
#define EPORT_EPDR_EPD3 ((uint32_t)1 << 3)
#define EPORT_EPDR_EPD4 ((uint32_t)1 << 4)
#define EPORT_EPDR_EPD5 ((uint32_t)1 << 5)
#define EPORT_EPDR_EPD6 ((uint32_t)1 << 6)
#define EPORT_EPDR_EPD7 ((uint32_t)1 << 7)

// EPPDR
#define EPORT_EPPDR_EPPD (0)
#define EPORT_EPPDR_EPPD0 ((uint32_t)1 << 0)
#define EPORT_EPPDR_EPPD1 ((uint32_t)1 << 1)
#define EPORT_EPPDR_EPPD2 ((uint32_t)1 << 2)
#define EPORT_EPPDR_EPPD3 ((uint32_t)1 << 3)
#define EPORT_EPPDR_EPPD4 ((uint32_t)1 << 4)
#define EPORT_EPPDR_EPPD5 ((uint32_t)1 << 5)
#define EPORT_EPPDR_EPPD6 ((uint32_t)1 << 6)
#define EPORT_EPPDR_EPPD7 ((uint32_t)1 << 7)

// EPFR
#define EPORT_EPFR_EPF (0)
#define EPORT_EPFR_EPF0 ((uint32_t)1 << 0)
#define EPORT_EPFR_EPF1 ((uint32_t)1 << 1)
#define EPORT_EPFR_EPF2 ((uint32_t)1 << 2)
#define EPORT_EPFR_EPF3 ((uint32_t)1 << 3)
#define EPORT_EPFR_EPF4 ((uint32_t)1 << 4)
#define EPORT_EPFR_EPF5 ((uint32_t)1 << 5)
#define EPORT_EPFR_EPF6 ((uint32_t)1 << 6)
#define EPORT_EPFR_EPF7 ((uint32_t)1 << 7)

// EPPUER
#define EPORT_EPPUER_EPPUE (0)
#define EPORT_EPPUER_EPPUE0 ((uint32_t)1 << 0)
#define EPORT_EPPUER_EPPUE1 ((uint32_t)1 << 1)
#define EPORT_EPPUER_EPPUE2 ((uint32_t)1 << 2)
#define EPORT_EPPUER_EPPUE3 ((uint32_t)1 << 3)
#define EPORT_EPPUER_EPPUE4 ((uint32_t)1 << 4)
#define EPORT_EPPUER_EPPUE5 ((uint32_t)1 << 5)
#define EPORT_EPPUER_EPPUE6 ((uint32_t)1 << 6)
#define EPORT_EPPUER_EPPUE7 ((uint32_t)1 << 7)

// EPLPR
#define EPORT_EPLPR_EPLP (0)
#define EPORT_EPLPR_EPLP0 ((uint32_t)1 << 0)
#define EPORT_EPLPR_EPLP1 ((uint32_t)1 << 1)
#define EPORT_EPLPR_EPLP2 ((uint32_t)1 << 2)
#define EPORT_EPLPR_EPLP3 ((uint32_t)1 << 3)
#define EPORT_EPLPR_EPLP4 ((uint32_t)1 << 4)
#define EPORT_EPLPR_EPLP5 ((uint32_t)1 << 5)
#define EPORT_EPLPR_EPLP6 ((uint32_t)1 << 6)
#define EPORT_EPLPR_EPLP7 ((uint32_t)1 << 7)

// EPODER
#define EPORT_EPODER_EPODE (0)
#define EPORT_EPODER_EPODE0 ((uint32_t)1 << 0)
#define EPORT_EPODER_EPODE1 ((uint32_t)1 << 1)
#define EPORT_EPODER_EPODE2 ((uint32_t)1 << 2)
#define EPORT_EPODER_EPODE3 ((uint32_t)1 << 3)
#define EPORT_EPODER_EPODE4 ((uint32_t)1 << 4)
#define EPORT_EPODER_EPODE5 ((uint32_t)1 << 5)
#define EPORT_EPODER_EPODE6 ((uint32_t)1 << 6)
#define EPORT_EPODER_EPODE7 ((uint32_t)1 << 7)

/**
 * @brief  EPORT 模块寄存器结构体定义
 */
typedef struct
{
    union
    {
        __IO uint16_t EPPAR; /**< 0x00 */
        struct
        {
            __IO uint8_t EPPAR_L;
            __IO uint8_t EPPAR_H;
        } EPPARHL;
    };

    __IO uint8_t EPIER;  /**< 0x02 */
    __IO uint8_t EPDDR;  /**< 0x03 */
    __IO uint8_t EPPDR;  /**< 0x04 */
    __IO uint8_t EPDR;   /**< 0x05 */
    __IO uint8_t EPPUER; /**< 0x06 */
    __IO uint8_t EPFR;   /**< 0x07 */
    __IO uint8_t EPODER; /**< 0x08 */
    __IO uint8_t EPLPR;  /**< 0x09 */
} reg_eport_t;

#ifdef __cplusplus
}
#endif

#endif
