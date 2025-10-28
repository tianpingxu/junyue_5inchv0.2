/**
 * @file sdio_drv.h
 * @author Product Application Department
 * @brief  SDIO 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef SDIO_DRV_H_
#define SDIO_DRV_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "sdio_reg.h"
#include "delay.h"
#include "common.h"

// 全局变量定义
#define USE_INTERNAL_DMAC
// #define SEND_AUTO_STOP
// #define UNDEFINED_TRANS_NUM
// 函数声明
void drv_sdio_hcon(void);
uint8_t drv_sdio_pollstatus(uint32_t flag_s);
void drv_sdio_startcmd(void);
void drv_sdio_init(void);
void drv_sdio_setclk(uint32_t slot_num, uint32_t div_val);
void drv_sdio_switchclk(uint8_t flag);
uint8_t drv_sdio_reset(void);
void drv_sdio_fifodmareset(void);
uint8_t drv_sdio_carddetect(void);
void drv_sdio_cardvolt(uint32_t slot_num, uint8_t flag);
void drv_sdio_powerup(uint32_t slot_num, uint8_t flag);
uint8_t drv_sdio_getpowerstate(uint32_t slot_num);
void drv_sdio_internaldmacctrl(uint8_t flag);
void drv_sdio_configdesc(uint32_t dbaddr, uint32_t baddr, uint16_t dscnt);
void drv_sdio_cmd0sdtsk(uint32_t arg);
void drv_sdio_cmd1sdtsk(uint32_t arg);
void drv_sdio_cmd8sdtsk(uint32_t arg);
void drv_sdio_cmd11sdtsk(void);
void drv_sdio_cmd55sdtsk(uint32_t rca);
void drv_sdio_acmd41sdtsk(uint32_t arg);
void drv_sdio_cmd2sdtsk(void);
void drv_sdio_cmd3sdtsk(uint32_t rca);
void drv_sdio_cmd9sdtsk(uint32_t rca);
void drv_sdio_cmd7sdtsk(uint32_t rca);
void drv_sdio_cmd13sdtsk(uint32_t rca);
void drv_sdio_acmd42sdtsk(uint32_t rca, uint32_t set_cd);
void drv_sdio_acmd51sdtsk(uint32_t rca, uint32_t byte_num);
void drv_sdio_acmd6sdtsk(uint32_t rca);
void drv_sdio_cmd16sdtsk(uint16_t blocklen);
void drv_sdio_cmd6sdtsk(uint32_t arg, uint32_t byte_num);
void drv_sdio_cmd17sdtsk(uint32_t arg, uint32_t byte_num);
void drv_sdio_cmd18sdtsk(uint32_t arg, uint32_t byte_num);
void drv_sdio_cmd12sdtsk(void);
void drv_sdio_cmd24sdtsk(uint32_t arg, uint32_t byte_num);
void drv_sdio_cmd25sdtsk(uint32_t arg, uint32_t byte_num);

#ifdef __cplusplus
}
#endif

#endif
