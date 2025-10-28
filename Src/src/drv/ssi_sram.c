/**
 *  @file ssi_drv.c
 *  @author Product application department
 *  @brief  SSI flash模块驱动层
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "ssi_sram.h"
#include "cpm_drv.h"
#include "ssi_drv.h"
/**
 *  @brief  SSI 模块初始化函数
 *  @note 在 system 初始化调用
 */
__attribute__((section(".sram_code"))) void drv_ssi_setsamdelay(reg_ssi_t *ssi_id, uint32_t sample_delay)
{
    if (ssi_id == SSI1)
    {
        _ccm_dis_ssi4_xip_en(CCM);
        _ccm_dis_ssi4_xip_sel(CCM);
        _ccm_en_ssi4_xip_en(CCM);

        _ssi_sr_get_status(SSI1);
        _ssi_enr_set(SSI1, SSI_DIS);
        _ssi_rsd_set(SSI1, sample_delay);
        _ssi_enr_set(SSI1, SSI_EN);
        _ssi_sr_get_status(SSI1);
        _ccm_en_ssi4_xip_sel(CCM);
        _ccm_en_ssi4_auto(CCM);
        _ssi_sr_get_status(SSI1);
    }
    else if (ssi_id == SSI2)
    {
        _ccm_dis_ssi5_xip_en(CCM);
        _ccm_dis_ssi5_xip_sel(CCM);
        _ccm_en_ssi5_xip_en(CCM);
        _ssi_sr_get_status(SSI2);
        _ssi_enr_set(SSI2, SSI_DIS);
        _ssi_rsd_set(SSI2, sample_delay);
        _ssi_enr_set(SSI2, SSI_EN);
        _ssi_sr_get_status(SSI2);
        _ccm_en_ssi5_xip_sel(CCM);
        _ccm_en_ssi5_auto(CCM);
        _ssi_sr_get_status(SSI2);
    }
    else if (ssi_id == SSI3)
    {
        _ccm_dis_ssi6_xip_en(CCM);
        _ccm_dis_ssi6_xip_sel(CCM);
        _ccm_en_ssi6_xip_en(CCM);
        _ssi_sr_get_status(SSI3);
        _ssi_enr_set(SSI3, SSI_DIS);
        _ssi_rsd_set(SSI3, sample_delay);
        _ssi_enr_set(SSI3, SSI_EN);
        _ssi_sr_get_status(SSI3);
        _ccm_en_ssi6_xip_sel(CCM);
        _ccm_en_ssi6_auto(CCM);
        _ssi_sr_get_status(SSI3);
    }
}

__attribute__((section(".sram_code"))) void drv_ssi_flash_init(ssi_para_t *pssi, reg_ssi_t **SSIReg)
{
    uint8_t data_frame_format;

    data_frame_format = 0x2;

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->CTRLR1 = 0x00;

    (*SSIReg)->IMR = 0x00;
    (*SSIReg)->TXFTLR = 0x00;
    (*SSIReg)->RXFTLR = 0x00;
    (*SSIReg)->RXSDR = pssi->rx_sample_delay;
    if (pssi->is_qpi_mode == ENABLE)
    {
        (*SSIReg)->BAUDR = pssi->quad_baud_rate;
        (*SSIReg)->CTRLR0 = 0x00000407 | ((data_frame_format & 0x3) << 22); // quad or dual mode/tx_only
        (*SSIReg)->SPICTRLR0 = 0x40000202 | ((pssi->dummyvalue & 0x1f) << 11);
    }
    else
    {
        (*SSIReg)->BAUDR = pssi->std_baud_rate;
        (*SSIReg)->CTRLR0 = 0x00000007;
        (*SSIReg)->SPICTRLR0 = 0x00;
    }

    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");
}

__attribute__((section(".sram_code"))) uint8_t drv_getflashstatus(ssi_para_t *pssi, reg_ssi_t **SSIReg, uint8_t get_status_cmd)
{
    volatile uint32_t temp;

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->TXFTLR = 0x00010000;
    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");

    (*SSIReg)->DR = get_status_cmd;
    (*SSIReg)->DR = DUMMY_BYTE;
    __asm("nop");
    __asm("nop");

    while (((*SSIReg)->SR & SR_TFE) != SR_TFE)
        ;
    while ((*SSIReg)->SR & SR_BUSY)
        ;
    while ((*SSIReg)->SR & SR_RFNE)
    {
        temp = (*SSIReg)->DR;
    }

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->TXFTLR = 0x00000000;
    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");

    return temp;
}
__attribute__((section(".sram_code"))) uint8_t drv_waitforflash_satuas(ssi_para_t *pssi, reg_ssi_t *SSIReg)
{
    volatile uint8_t status;
    uint32_t time;

    uint8_t (*GetStatus)(ssi_para_t *pssi, reg_ssi_t **SSIReg, uint8_t get_status_cmd);

    GetStatus = drv_getflashstatus;
    if (pssi->timeout == 0)
    {
        do
        {
            status = GetStatus(pssi, &SSIReg, GET_SAT1_CMD);
        } while (status & 0x01);
        return 1;
    }
    else
    {
        time = pssi->timeout;
        while (time)
        {
            status = GetStatus(pssi, &SSIReg, GET_SAT1_CMD);
            if ((status & 0x01) == 0)
                break;
            time--;
            if (time == 0)
            {
                if (pssi->sys_div == 0) // 变量复用
                {
                }
                return 0;
            }
        }
        return 1;
    }
}
/**
 *  @brief  SSI 模块Flash 写使能函数
 *
 *  @param p_ssi SSI 初始化结构体
 *  @param timeout 超时时间
 *  @return status_t 返回函数运行状态
 */
__attribute__((section(".sram_code"))) void drv_ssi_eflash_write_enable(reg_ssi_t *SSIReg, uint32_t timeout)
{
    volatile uint32_t temp;
	(*SSIReg).DR = WRITE_EN_CMD;
	 
	__asm("nop");	__asm("nop");	 
	
  while(((*SSIReg).SR&SR_TFE)!=SR_TFE);		
	while((*SSIReg).SR&SR_BUSY);

	while((*SSIReg).SR&SR_RFNE)
	{
			temp=(*SSIReg).DR; 
	}	
}
__attribute__((section(".sram_code"))) uint8_t drv_ssi_falsh_erase(ssi_para_t *pssi, reg_ssi_t **SSIReg)
{
    volatile uint8_t status;
    volatile uint32_t temp;

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->TXFTLR = 0x00030000;
    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");

    (*SSIReg)->DR = pssi->cmd;
    if (pssi->isfouraddr == 0x01)
    {
        (*SSIReg)->DR = ((pssi->addr) >> 24) & 0xff;
    }
    (*SSIReg)->DR = ((pssi->addr) >> 16) & 0xff;
    (*SSIReg)->DR = ((pssi->addr) >> 8) & 0xff;
    (*SSIReg)->DR = ((pssi->addr) >> 0) & 0xff;

    __asm("nop");
    __asm("nop");

    while (((*SSIReg)->SR & SR_TFE) != SR_TFE)
        ;
    while ((*SSIReg)->SR & SR_BUSY)
        ;

    while ((*SSIReg)->SR & SR_RFNE)
    {
        temp = (*SSIReg)->DR;
    }

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->TXFTLR = 0x00000000;
    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");

    return drv_waitforflash_satuas(pssi, *SSIReg);
}
reg_ssi_t *SSIReg_Save;
/**
 * @brief SSI 模块XIP擦除操作函数
 *
 * @param pssi SSI 参数
 */
__attribute__((section(".sram_code"))) void drv_xipflash_erase(ssi_para_t *pssi)
{
    uint32_t reg;
    reg_ssi_t *SSIReg;
    uint32_t delay;
    uint16_t QuadBaudrReg;
    uint32_t RxSampleDelayReg;
    //以下delay操作注意不能被优化
    if (pssi->delay)
    {
        delay = pssi->delay;
        while (delay--)
            ;
    }
    if (pssi->ssi_id == SSIID1)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 16) | (1 << 20))) | (1 << 16);
        SSIReg = SSI1;
    }
    else if (pssi->ssi_id == SSIID2)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 17) | (1 << 21))) | (1 << 17);
        SSIReg = SSI2;
    }
    else if (pssi->ssi_id == SSIID3)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 18) | (1 << 22))) | (1 << 18);
        SSIReg = SSI3;
    }
    SSIReg_Save = SSIReg;
    QuadBaudrReg = SSIReg->BAUDR;
    RxSampleDelayReg = SSIReg->RXSDR;
    drv_ssi_flash_init(pssi, &SSIReg);
    drv_ssi_eflash_write_enable(SSIReg, 0xffffff);
    drv_ssi_falsh_erase(pssi, &SSIReg);
    SSIReg->BAUDR = QuadBaudrReg;
    SSIReg->RXSDR = RxSampleDelayReg;

    SSIReg = SSIReg_Save;
    if (pssi->ssi_id == SSIID1)
    {
        CCM->SSICFGR |= ((1 << 16) | (1 << 20));
    }
    if (pssi->ssi_id == SSIID2)
    {
        CCM->SSICFGR |= ((1 << 17) | (1 << 21));
    }
    if (pssi->ssi_id == SSIID3)
    {
        CCM->SSICFGR |= ((1 << 18) | (1 << 22));
    }
    //以下delay操作注意不能被优化
    if (pssi->delay)
    {
        delay = pssi->delay;
        while (delay--)
            ;
    }
}
__attribute__((section(".sram_code"))) uint8_t drv_ssi_falsh_program(ssi_para_t *pssi, reg_ssi_t **SSIReg)
{

    volatile uint8_t status;
    volatile uint32_t temp;
    volatile uint32_t len;

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->CTRLR0 = 0x0080041f;

    if (pssi->isfouraddr == 0x01)
    {
        (*SSIReg)->SPICTRLR0 = 0x40000220;
    }
    else
    {
        (*SSIReg)->SPICTRLR0 = 0x40000218; // 3Byte
    }

    (*SSIReg)->TXFTLR = 0x00020000;
    (*SSIReg)->CTRLR1 = pssi->len / 4 - 1;
    (*SSIReg)->BAUDR = pssi->quad_baud_rate;
    (*SSIReg)->SSIENR = 0x01;
    __asm("nop");
    __asm("nop");

    (*SSIReg)->DR = pssi->cmd;
    (*SSIReg)->DR = pssi->addr; // 地址作为一个设置的len,一起发送
    __asm("nop");
    __asm("nop");

    len = pssi->len;
    while (len > 0)
    {
        if ((*SSIReg)->SR & SR_TFNF)
        {
            (*SSIReg)->DR = (*((volatile uint32_t *)pssi->buf));
            pssi->buf = pssi->buf + 4;
            len = len - 4;
        }
    }
    while ((*SSIReg)->SR & SR_BUSY)
        ;
    while ((*SSIReg)->SR & SR_RFNE)
    {
        temp = (*SSIReg)->DR;
    }

    (*SSIReg)->SSIENR = 0x00;
    (*SSIReg)->CTRLR0 = 0x00000007;
    (*SSIReg)->SPICTRLR0 = 0x00;
    (*SSIReg)->TXFTLR = 0x00000000;
    (*SSIReg)->CTRLR1 = 0x00;
    (*SSIReg)->BAUDR = pssi->std_baud_rate;
    (*SSIReg)->SSIENR = 0x01;

    return drv_waitforflash_satuas(pssi, *SSIReg);
}
__attribute__((section(".sram_code"))) void drv_xipflash_program(ssi_para_t *pssi)
{
    uint32_t reg;
    uint32_t delay;
    reg_ssi_t *SSIReg;
    uint16_t QuadBaudrReg;
    uint32_t RxSampleDelayReg;
    //以下delay操作注意不能被优化
    if (pssi->delay)
    {
        delay = pssi->delay;
        while (delay--)
            ;
    }

    if (pssi->ssi_id == SSIID1)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 16) | (1 << 20))) | (1 << 16);
        SSIReg = SSI1;
    }
    else if (pssi->ssi_id == SSIID2)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 17) | (1 << 21))) | (1 << 17);
        SSIReg = SSI2;
    }
    else if (pssi->ssi_id == SSIID3)
    {
        CCM->SSICFGR = (CCM->SSICFGR & ~((1 << 18) | (1 << 22))) | (1 << 18);
        SSIReg = SSI3;
    }
    SSIReg_Save = SSIReg;
    QuadBaudrReg = SSIReg->BAUDR;
    RxSampleDelayReg = SSIReg->RXSDR;

    drv_ssi_flash_init(pssi, &SSIReg);
    drv_ssi_eflash_write_enable(SSIReg, 0xffffff);
    drv_ssi_falsh_program(pssi, &SSIReg);
    SSIReg->BAUDR = QuadBaudrReg;
    SSIReg->RXSDR = RxSampleDelayReg;
    //	 SSIReg->SSIENR = 0x01;
    SSIReg = SSIReg_Save;
    if (pssi->ssi_id == SSIID1)
    {
        CCM->SSICFGR |= ((1 << 16) | (1 << 20));
    }
    if (pssi->ssi_id == SSIID2)
    {
        CCM->SSICFGR |= ((1 << 17) | (1 << 21));
    }
    if (pssi->ssi_id == SSIID3)
    {
        CCM->SSICFGR |= ((1 << 18) | (1 << 22));
    }
    //以下delay操作注意不能被优化
    if (pssi->delay)
    {
        delay = pssi->delay;
        while (delay--)
            ;
    }
}
