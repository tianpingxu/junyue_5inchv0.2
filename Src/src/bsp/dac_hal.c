/**
 * @file dac_hal.c
 * @author Product application department
 * @brief  DAC 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// 头文件包含
#include "dac_hal.h"

// 全局变量定义
dmac_hdle_t *g_hdma;
dmac_hdle_t hdma;
uint8_t dma_tran_complete = 0;

// 函数定义

/**
 * @brief DAC 模块启动传输函数
 * 
 * @param trigger_select 触发模式选择
 * @param rate 传输速率
 */
void hal_dac_start(dac_trigger_sel_t trigger_select, uint32_t rate)
{
  float us;
  hal_pit32_handler_t dac_hpit32;
  if (TRIGGER_SOFTWARE == trigger_select)
    drv_dac_sw_trig();
  else if (TRIGGER_PIT == trigger_select)
  {
    us = 1000000 / (float)rate;
    double time_cnt = g_ips_clk / 1000000 * us;

    dac_hpit32.instance = PIT2;

    dac_hpit32.init.counter = time_cnt;

    dac_hpit32.init.enable_ie = DISABLE;

    dac_hpit32.init.reload = ENABLE;

    dac_hpit32.init.prescaler = PIT32_CLK_DIV_1;

    dac_hpit32.init.run_at_debug = ENABLE;

    dac_hpit32.init.run_at_doze = ENABLE;

    dac_hpit32.init.update_cnt = ENABLE;

    hal_pit32_init(&dac_hpit32);
  }
}

/**
 * @brief DAC 模块发送数据函数
 * 
 * @param data 待发送的数据
 * @return status_t 成功
 */

 status_t hal_dac_senddata(uint16_t data)
{
  drv_adc_send_data(data);

  return (STATUS_OK);
}

/**
 * @brief DAC 模块反初始化函数
 * 
 * @return status_t 成功
 */
status_t hal_dac_deinit(void)
{

  drv_dac_deinit();

  return (STATUS_OK);
}

/**
 * @brief DAC DMA传输中断服务回调函数
 * 
 */
static void hal_dma_callback()
{
  dma_tran_complete = 1;
  hal_dmac_deinit(&hdma);
  hal_dac_deinit();
}

/**
 * @brief DAC 模块中断处理函数
 * 
 */
void hal_dac_irqhandler(void)
{
  uint8_t dmac_isr_flag;
  /*dmac complete intrrupt*/
  if (drv_dmac_getrawirq_en(g_hdma->instance, g_hdma->init.channel_num)) // dma channel raw intrrupt ie enable;
  {
    if (drv_dmac_getrawstatus(g_hdma->instance, g_hdma->init.channel_num))
    {
      hal_dma_callback();

      dmac_isr_flag |= (1 << g_hdma->init.channel_num);

      /*清除raw中断状态标志*/
      drv_dmac_clearrawstatus(g_hdma->instance, g_hdma->init.channel_num);
    }
  }
  /*dmac block interrupt*/
  if (drv_dmac_getblockirq_en(g_hdma->instance, g_hdma->init.channel_num)) // dma channel raw intrrupt ie enable;
  {
    if (drv_dmac_getblockstatus(g_hdma->instance, g_hdma->init.channel_num))
    {
      hal_dma_callback();

      dmac_isr_flag |= (0x10 << g_hdma->init.channel_num);

      /*清除block中断状态标志*/
      drv_dmac_clearblocktatus(g_hdma->instance, g_hdma->init.channel_num);
    }
  }
  /*dmac min interrupt*/
  if (drv_dmac_getminirq_en(g_hdma->instance, g_hdma->init.channel_num)) // dma channel raw intrrupt ie enable;
  {
    if (drv_dmac_getminstatus(g_hdma->instance, g_hdma->init.channel_num))
    {

      dmac_isr_flag |= (0x100 << g_hdma->init.channel_num);

      /*清除min中断状态标志*/
      drv_dmac_clearmintatus(g_hdma->instance, g_hdma->init.channel_num);
    }
  }
  /*dmac error interrupt*/
}

/**
 * @brief DAC 模块初始化函数
 * @param data_format 数据格式
 * @param trigger_select 触发方式
 * @param external_mode 外部触发模块
 * @param dma_en 是否使能DMA
 */
void hal_dac_init(dac_data_format_t data_format, dac_trigger_sel_t trigger_select, dac_ext_tmod_t external_mode,uint8_t dma_en)
{
  drv_dac_init(data_format,trigger_select,external_mode,dma_en);
}

