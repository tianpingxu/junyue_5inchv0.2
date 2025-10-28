/**
 * @file pwmt_reg.h
 * @author Product Application Department
 * @brief  PWMT模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-13
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

#ifndef __PWMT_REG_H
#define __PWMT_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
//全局变量定义  
#define PWMT1_BASE_ADDR     (0x4002d000)      
#define PWMT2_BASE_ADDR     (0x4002e000)      
#define PWMT3_BASE_ADDR     (0x4002f000)      
#define PWMT1 ((reg_pwmt_t *)(PWMT1_BASE_ADDR))
#define PWMT2 ((reg_pwmt_t *)(PWMT2_BASE_ADDR))
#define PWMT3 ((reg_pwmt_t *)(PWMT3_BASE_ADDR))

// CR1
#define PWMT_CR1_CKD_00 (00 << 8)
#define PWMT_CR1_CKD_01 (01 << 8)
#define PWMT_CR1_CKD_10 (10 << 8)
#define PWMT_CR1_ARPE (1 << 7)
#define PWMT_CR1_CMS_EALIGN (0 << 5)
#define PWMT_CR1_CMS_CALIGN1 (1 << 5)
#define PWMT_CR1_CMS_CALIGN2 (2 << 5)
#define PWMT_CR1_CMS_CALIGN3 (3 << 5)
#define PWMT_CR1_DIR_UP (0 << 4)
#define PWMT_CR1_DIR_DOWN (1 << 4)
#define PWMT_CR1_OPM (1 << 3)
#define PWMT_CR1_URS (1 << 2)
#define PWMT_CR1_UDIS (1 << 1)
#define PWMT_CR1_CEN (1 << 0)

// CR2
#define PWMT_CR2_OIS4N (1 << 15)
#define PWMT_CR2_OIS4 (1 << 14)
#define PWMT_CR2_OIS3N (1 << 13)
#define PWMT_CR2_OIS3 (1 << 12)
#define PWMT_CR2_OIS2N (1 << 11)
#define PWMT_CR2_OIS2 (1 << 10)
#define PWMT_CR2_OIS1N (1 << 9)
#define PWMT_CR2_OIS1 (1 << 8)
#define PWMT_CR2_TI1S (1 << 7)
#define PWMT_CR2_MMS_RESET (0 << 4)
#define PWMT_CR2_MMS_ENABLE (1 << 4)
#define PWMT_CR2_MMS_UPDATE (2 << 4)
#define PWMT_CR2_MMS_COMPP (3 << 4)
#define PWMT_CR2_MMS_COMP1TRGO (4 << 4)
#define PWMT_CR2_MMS_COMP2TRGO (5 << 4)
#define PWMT_CR2_MMS_COMP3TRGO (6 << 4)
#define PWMT_CR2_MMS_COMP4TRGO (7 << 4)
#define PWMT_CR2_CCDS (1 << 2)
#define PWMT_CR2_CCUS (1 << 1)
#define PWMT_CR2_CCPC (1 << 0)

// SMCR
#define PWMT_SMCR_ETP (1 << 15)
#define PWMT_SMCR_ECE (1 << 14)
#define PWMT_SMCR_ETPS_PRESCOFF (0 << 12)
#define PWMT_SMCR_ETPS_PRESCDIV2 (1 << 12)
#define PWMT_SMCR_ETPS_PRESCDIV4 (2 << 12)
#define PWMT_SMCR_ETPS_PRESCDIV8 (3 << 12)
#define PWMT_SMCR_ETF_D1_N1 (00 << 8)
#define PWMT_SMCR_ETF_D1_N2 (01 << 8)
#define PWMT_SMCR_ETF_D1_N4 (02 << 8)
#define PWMT_SMCR_ETF_D1_N8 (03 << 8)
#define PWMT_SMCR_ETF_D2_N6 (04 << 8)
#define PWMT_SMCR_ETF_D2_N8 (05 << 8)
#define PWMT_SMCR_ETF_D4_N6 (06 << 8)
#define PWMT_SMCR_ETF_D4_N8 (07 << 8)
#define PWMT_SMCR_ETF_D8_N6 (08 << 8)
#define PWMT_SMCR_ETF_D8_N8 (09 << 8)
#define PWMT_SMCR_ETF_D16_N5 (10 << 8)
#define PWMT_SMCR_ETF_D16_N6 (11 << 8)
#define PWMT_SMCR_ETF_D16_N8 (12 << 8)
#define PWMT_SMCR_ETF_D32_N5 (13 << 8)
#define PWMT_SMCR_ETF_D32_N6 (14 << 8)
#define PWMT_SMCR_ETF_D32_N8 (15 << 8)
#define PWMT_SMCR_MSM (1 << 7)
#define PWMT_SMCR_TS_TRGI0 (0 << 4)
#define PWMT_SMCR_TS_TRGI1 (1 << 4)
#define PWMT_SMCR_TS_TRGI2 (2 << 4)
#define PWMT_SMCR_TS_TRGI3 (3 << 4)
#define PWMT_SMCR_TS_TI1F_ED (4 << 4)
#define PWMT_SMCR_TS_TI1FP1 (5 << 4)
#define PWMT_SMCR_TS_TI2FP2 (6 << 4)
#define PWMT_SMCR_TS_ETRF (7 << 4)
#define PWMT_SMCR_SMS_SLV_DIS (0 << 0) 
#define PWMT_SMCR_SMS_ENC_MODE1 (1 << 0)
#define PWMT_SMCR_SMS_ENC_MODE2 (2 << 0)
#define PWMT_SMCR_SMS_ENC_MODE3 (3 << 0)
#define PWMT_SMCR_SMS_RESET (4 << 0)   
#define PWMT_SMCR_SMS_GATED (5 << 0)   
#define PWMT_SMCR_SMS_TRIGGER (6 << 0) 
#define PWMT_SMCR_SMS_EXTCLK (7 << 0)

// DIER
#define PWMT_DIER_TDE (1 << 14)
#define PWMT_DIER_COMDE (1 << 13)
#define PWMT_DIER_CC4DE (1 << 12)
#define PWMT_DIER_CC3DE (1 << 11)
#define PWMT_DIER_CC2DE (1 << 10)
#define PWMT_DIER_CC1DE (1 << 9)
#define PWMT_DIER_UDE (1 << 8)
#define PWMT_DIER_BIE (1 << 7)
#define PWMT_DIER_TIE (1 << 6)
#define PWMT_DIER_COMIE (1 << 5)
#define PWMT_DIER_CC4IE (1 << 4)
#define PWMT_DIER_CC3IE (1 << 3)
#define PWMT_DIER_CC2IE (1 << 2)
#define PWMT_DIER_CC1IE (1 << 1)
#define PWMT_DIER_UIE (1 << 0)

// SR
#define PWMT_SR_CC4OF (1 << 12)
#define PWMT_SR_CC3OF (1 << 11)
#define PWMT_SR_CC2OF (1 << 10)
#define PWMT_SR_CC1OF (1 << 9)
#define PWMT_SR_BIF (1 << 7)
#define PWMT_SR_TIF (1 << 6)
#define PWMT_SR_COMIF (1 << 5)
#define PWMT_SR_CC4IF (1 << 4)
#define PWMT_SR_CC3IF (1 << 3)
#define PWMT_SR_CC2IF (1 << 2)
#define PWMT_SR_CC1IF (1 << 1)
#define PWMT_SR_UIF (1 << 0)

// EGR
#define PWMT_EGR_BG (1 << 7)
#define PWMT_EGR_TG (1 << 6)
#define PWMT_EGR_COMG (1 << 5)
#define PWMT_EGR_CC4G (1 << 4)
#define PWMT_EGR_CC3G (1 << 3)
#define PWMT_EGR_CC2G (1 << 2)
#define PWMT_EGR_CC1G (1 << 1)
#define PWMT_EGR_UG (1 << 0)

// CCMR1
#define PWMT_CCMR1_OC2CE (1 << 15)
#define PWMT_CCMR1_OC2M_FROZEN (0 << 12)
#define PWMT_CCMR1_OC2M_ACT_MATCH (1 << 12)
#define PWMT_CCMR1_OC2M_INACT_MATCH (2 << 12)
#define PWMT_CCMR1_OC2M_TOGGLE (3 << 12)
#define PWMT_CCMR1_OC2M_FORCE_ACT_LVL (4 << 12)
#define PWMT_CCMR1_OC2M_FORCE_INACT_LVL (5 << 12)
#define PWMT_CCMR1_OC2M_PWM_MODE1 (6 << 12)
#define PWMT_CCMR1_OC2M_PWM_MODE2 (7 << 12)
#define PWMT_CCMR1_OC2PE (1 << 11)
#define PWMT_CCMR1_OC2FE (1 << 10)
#define PWMT_CCMR1_CC2S_OUT (0 << 8)
#define PWMT_CCMR1_CC2S_IN_IC2_TI2 (1 << 8)
#define PWMT_CCMR1_CC2S_IN_IC2_TI1 (2 << 8)
#define PWMT_CCMR1_CC2S_IN_IC2_TRC (3 << 8)
#define PWMT_CCMR1_OC1CE (1 << 7)
#define PWMT_CCMR1_OC1M_FROZEN (0 << 4)
#define PWMT_CCMR1_OC1M_ACT_MATCH (1 << 4)
#define PWMT_CCMR1_OC1M_INACT_MATCH (2 << 4)
#define PWMT_CCMR1_OC1M_TOGGLE (3 << 4)
#define PWMT_CCMR1_OC1M_FORCE_ACT_LVL (4 << 4)
#define PWMT_CCMR1_OC1M_FORCE_INACT_LVL (5 << 4)
#define PWMT_CCMR1_OC1M_PWM_MODE1 (6 << 4)
#define PWMT_CCMR1_OC1M_PWM_MODE2 (7 << 4)
#define PWMT_CCMR1_OC1PE (1 << 3)
#define PWMT_CCMR1_OC1FE (1 << 2)
#define PWMT_CCMR1_CC1S_OUT (0 << 0)
#define PWMT_CCMR1_CC1S_IN_IC1_TI1 (1 << 0)
#define PWMT_CCMR1_CC1S_IN_IC1_TI2 (2 << 0)
#define PWMT_CCMR1_CC1S_IN_IC1_TRC (3 << 0)
#define PWMT_CCMR1_IC2F_D1_N1 (00 << 12)
#define PWMT_CCMR1_IC2F_D1_N2 (01 << 12)
#define PWMT_CCMR1_IC2F_D1_N4 (02 << 12)
#define PWMT_CCMR1_IC2F_D1_N8 (03 << 12)
#define PWMT_CCMR1_IC2F_D2_N6 (04 << 12)
#define PWMT_CCMR1_IC2F_D2_N8 (05 << 12)
#define PWMT_CCMR1_IC2F_D4_N6 (06 << 12)
#define PWMT_CCMR1_IC2F_D4_N8 (07 << 12)
#define PWMT_CCMR1_IC2F_D8_N6 (08 << 12)
#define PWMT_CCMR1_IC2F_D8_N8 (09 << 12)
#define PWMT_CCMR1_IC2F_D16_N5 (10 << 12)
#define PWMT_CCMR1_IC2F_D16_N6 (11 << 12)
#define PWMT_CCMR1_IC2F_D16_N8 (12 << 12)
#define PWMT_CCMR1_IC2F_D32_N5 (13 << 12)
#define PWMT_CCMR1_IC2F_D32_N6 (14 << 12)
#define PWMT_CCMR1_IC2F_D32_N8 (15 << 12)
#define PWMT_CCMR1_IC2PSC_D1 (0 << 10)
#define PWMT_CCMR1_IC2PSC_D2 (1 << 10)
#define PWMT_CCMR1_IC2PSC_D4 (2 << 10)
#define PWMT_CCMR1_IC2PSC_D8 (3 << 10)
#define PWMT_CCMR1_IC1F_D1_N1 (00 << 4)
#define PWMT_CCMR1_IC1F_D1_N2 (01 << 4)
#define PWMT_CCMR1_IC1F_D1_N4 (02 << 4)
#define PWMT_CCMR1_IC1F_D1_N8 (03 << 4)
#define PWMT_CCMR1_IC1F_D2_N6 (04 << 4)
#define PWMT_CCMR1_IC1F_D2_N8 (05 << 4)
#define PWMT_CCMR1_IC1F_D4_N6 (06 << 4)
#define PWMT_CCMR1_IC1F_D4_N8 (07 << 4)
#define PWMT_CCMR1_IC1F_D8_N6 (08 << 4)
#define PWMT_CCMR1_IC1F_D8_N8 (09 << 4)
#define PWMT_CCMR1_IC1F_D16_N5 (10 << 4)
#define PWMT_CCMR1_IC1F_D16_N6 (11 << 4)
#define PWMT_CCMR1_IC1F_D16_N8 (12 << 4)
#define PWMT_CCMR1_IC1F_D32_N5 (13 << 4)
#define PWMT_CCMR1_IC1F_D32_N6 (14 << 4)
#define PWMT_CCMR1_IC1F_D32_N8 (15 << 4)
#define PWMT_CCMR1_IC1PSC_D1 (0 << 2)
#define PWMT_CCMR1_IC1PSC_D2 (1 << 2)
#define PWMT_CCMR1_IC1PSC_D4 (2 << 2)
#define PWMT_CCMR1_IC1PSC_D8 (3 << 2)

// CCMR2
#define PWMT_CCMR2_OC4CE (1 << 15)
#define PWMT_CCMR2_OC4M_FROZEN (0 << 12)
#define PWMT_CCMR2_OC4M_ACT_MATCH (1 << 12)
#define PWMT_CCMR2_OC4M_INACT_MATCH (2 << 12)
#define PWMT_CCMR2_OC4M_TOGGLE (3 << 12)
#define PWMT_CCMR2_OC4M_FORCE_ACT_LVL (4 << 12)
#define PWMT_CCMR2_OC4M_FORCE_INACT_LVL (5 << 12)
#define PWMT_CCMR2_OC4M_PWM_MODE1 (6 << 12)
#define PWMT_CCMR2_OC4M_PWM_MODE2 (7 << 12)
#define PWMT_CCMR2_OC4PE (1 << 11)
#define PWMT_CCMR2_OC4FE (1 << 10)
#define PWMT_CCMR2_CC4S_OUT (0 << 8)
#define PWMT_CCMR2_CC4S_IN_IC4_TI4 (1 << 8)
#define PWMT_CCMR2_CC4S_IN_IC4_TI3 (2 << 8)
#define PWMT_CCMR2_CC4S_IN_IC4_TRC (3 << 8)
#define PWMT_CCMR2_OC3CE (1 << 7)
#define PWMT_CCMR2_OC3M_FROZEN (0 << 4)
#define PWMT_CCMR2_OC3M_ACT_MATCH (1 << 4)
#define PWMT_CCMR2_OC3M_INACT_MATCH (2 << 4)
#define PWMT_CCMR2_OC3M_TOGGLE (3 << 4)
#define PWMT_CCMR2_OC3M_FORCE_ACT_LVL (4 << 4)
#define PWMT_CCMR2_OC3M_FORCE_INACT_LVL (5 << 4)
#define PWMT_CCMR2_OC3M_PWM_MODE1 (6 << 4)
#define PWMT_CCMR2_OC3M_PWM_MODE2 (7 << 4)
#define PWMT_CCMR2_OC3PE (1 << 3)
#define PWMT_CCMR2_OC3FE (1 << 2)
#define PWMT_CCMR2_CC3S_OUT (0 << 0)
#define PWMT_CCMR2_CC3S_IN_IC3_TI3 (1 << 0)
#define PWMT_CCMR2_CC3S_IN_IC3_TI4 (2 << 0)
#define PWMT_CCMR2_CC3S_IN_IC3_TRC (3 << 0)
#define PWMT_CCMR2_IC4F_D1_N1 (00 << 12)
#define PWMT_CCMR2_IC4F_D1_N2 (01 << 12)
#define PWMT_CCMR2_IC4F_D1_N4 (02 << 12)
#define PWMT_CCMR2_IC4F_D1_N8 (03 << 12)
#define PWMT_CCMR2_IC4F_D2_N6 (04 << 12)
#define PWMT_CCMR2_IC4F_D2_N8 (05 << 12)
#define PWMT_CCMR2_IC4F_D4_N6 (06 << 12)
#define PWMT_CCMR2_IC4F_D4_N8 (07 << 12)
#define PWMT_CCMR2_IC4F_D8_N6 (08 << 12)
#define PWMT_CCMR2_IC4F_D8_N8 (09 << 12)
#define PWMT_CCMR2_IC4F_D16_N5 (10 << 12)
#define PWMT_CCMR2_IC4F_D16_N6 (11 << 12)
#define PWMT_CCMR2_IC4F_D16_N8 (12 << 12)
#define PWMT_CCMR2_IC4F_D32_N5 (13 << 12)
#define PWMT_CCMR2_IC4F_D32_N6 (14 << 12)
#define PWMT_CCMR2_IC4F_D32_N8 (15 << 12)
#define PWMT_CCMR2_IC4PSC_D1 (0 << 10)
#define PWMT_CCMR2_IC4PSC_D2 (1 << 10)
#define PWMT_CCMR2_IC4PSC_D4 (2 << 10)
#define PWMT_CCMR2_IC4PSC_D8 (3 << 10)
#define PWMT_CCMR2_IC3F_D1_N1 (00 << 4)
#define PWMT_CCMR2_IC3F_D1_N2 (01 << 4)
#define PWMT_CCMR2_IC3F_D1_N4 (02 << 4)
#define PWMT_CCMR2_IC3F_D1_N8 (03 << 4)
#define PWMT_CCMR2_IC3F_D2_N6 (04 << 4)
#define PWMT_CCMR2_IC3F_D2_N8 (05 << 4)
#define PWMT_CCMR2_IC3F_D4_N6 (06 << 4)
#define PWMT_CCMR2_IC3F_D4_N8 (07 << 4)
#define PWMT_CCMR2_IC3F_D8_N6 (08 << 4)
#define PWMT_CCMR2_IC3F_D8_N8 (09 << 4)
#define PWMT_CCMR2_IC3F_D16_N5 (10 << 4)
#define PWMT_CCMR2_IC3F_D16_N6 (11 << 4)
#define PWMT_CCMR2_IC3F_D16_N8 (12 << 4)
#define PWMT_CCMR2_IC3F_D32_N5 (13 << 4)
#define PWMT_CCMR2_IC3F_D32_N6 (14 << 4)
#define PWMT_CCMR2_IC3F_D32_N8 (15 << 4)
#define PWMT_CCMR2_IC3PSC_D1 (0 << 2)
#define PWMT_CCMR2_IC3PSC_D2 (1 << 2)
#define PWMT_CCMR2_IC3PSC_D4 (2 << 2)
#define PWMT_CCMR2_IC3PSC_D8 (3 << 2)

// CCER
#define PWMT_CCER_CC4NP (1 << 15)
#define PWMT_CCER_CC4NE (1 << 14)
#define PWMT_CCER_CC4P (1 << 13)
#define PWMT_CCER_CC4E (1 << 12)
#define PWMT_CCER_CC3NP (1 << 11)
#define PWMT_CCER_CC3NE (1 << 10)
#define PWMT_CCER_CC3P (1 << 9)
#define PWMT_CCER_CC3E (1 << 8)
#define PWMT_CCER_CC2NP (1 << 7)
#define PWMT_CCER_CC2NE (1 << 6)
#define PWMT_CCER_CC2P (1 << 5)
#define PWMT_CCER_CC2E (1 << 4)
#define PWMT_CCER_CC1NP (1 << 3)
#define PWMT_CCER_CC1NE (1 << 2)
#define PWMT_CCER_CC1P (1 << 1)
#define PWMT_CCER_CC1E (1 << 0)

// BDTR
#define PWMT_BDTR_MOE (1 << 15)
#define PWMT_BDTR_AOE (1 << 14)
#define PWMT_BDTR_BKP (1 << 13)
#define PWMT_BDTR_BKE (1 << 12)
#define PWMT_BDTR_OSSR (1 << 11)
#define PWMT_BDTR_OSSI (1 << 10)
#define PWMT_BDTR_LOCK_OFF (0 << 8)
#define PWMT_BDTR_LOCK_LEVEL1 (1 << 8)
#define PWMT_BDTR_LOCK_LEVEL2 (2 << 8)
#define PWMT_BDTR_LOCK_LEVEL3 (3 << 8)

// PUE
#define PWMT_PUE_CHO1 (1 << 0)
#define PWMT_PUE_CHO2 (1 << 1)
#define PWMT_PUE_CHO3 (1 << 2)
#define PWMT_PUE_CHO4 (1 << 3)
#define PWMT_PUE_CHO1N (1 << 4)
#define PWMT_PUE_CHO2N (1 << 5)
#define PWMT_PUE_CHO3N (1 << 6)
#define PWMT_PUE_CHO4N (1 << 7)

/**
 * @brief PWMT模块寄存器定义
 * 
 */
typedef struct
{
    __IO uint32_t CR1;         
    __IO uint32_t CR2;         
    __IO uint32_t SMCR;        
    __IO uint32_t DIER;        
    __IO uint32_t SR;          
    __IO uint32_t EGR;         
    __IO uint32_t CCMR1;       
    __IO uint32_t CCMR2;       
    __IO uint32_t CCER;        
    __IO uint32_t CNT;         
    __IO uint32_t PSC;         
    __IO uint32_t ARR;         
    __IO uint32_t RCR;         
    __IO uint32_t CCR1;        
    __IO uint32_t CCR2;        
    __IO uint32_t CCR3;        
    __IO uint32_t CCR4;        
    __IO uint32_t BDTR;        
    __IO uint32_t DCR;         
    __IO uint32_t DMAR;        
    __IO uint32_t PMCR1;       
    __IO uint32_t PMCR2;       
    __IO uint32_t PMCR3;       
    __IO uint32_t PMCR4;       
    __IO uint32_t PMCREN;      
    __IO uint32_t PUE;         
} reg_pwmt_t;

#ifdef __cplusplus
}
#endif

#endif

 