/**
 * @file main.c
 * @author Product Application Department
 * @brief  主程序文件
 * @version V1.0
 * @date 2025-03-04
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
// 头文件包含
#include "sys.h"
#include "main.h"
#include "libpsram.h"
#include "pinswap_drv.h"
#include "eport_hal.h"

// 函数定义
/**
 * @brief 恢复芯片出厂模式接口函数
 *
 */
static void reback_boot(void)
{
    uint8_t value_level;
    SwitchPinFunction(WAKEUP_FUN, EPORT6_PIN3_FUN);
    hal_eport_input(EPORT6, EPORT6_PIN3, PS_PULL_UP);
    value_level = hal_eport_readpinslevel(EPORT6, EPORT6_PIN3);
    if (value_level == BIT_SET)
    {
        sys_startupconfig(Startup_From_ROM, ENABLE);
        while (1)
            ;
    }
}

/**
 * @brief 打印固件版本信息函数
 *
 */
static void printfversion(void)
{
    printf("/**************************************************/\r\n");
    printf(" date = %s,time = %s    \r\n", (char *)__DATE__, (char *)__TIME__);
    printf(" C*CORE CCM4211 FW V1.1.0  \r\n");
    printf(" core clk    = %dMHz         \r\n", g_core_clk / 1000000);
    printf(" system clk = %dMHz         \r\n", g_sys_clk / 1000000);
    printf(" ips clk    = %dMHz         \r\n", g_ips_clk / 1000000);
    printf("/**************************************************/\r\n");
}

/**
 * @brief SDK 测试用例接口函数
 *
 */
void app_demo(void)
{

#ifdef ALGO_DEMO
    algo_demo();
#endif

#ifdef UART_DEMO
    uart_demo();
#endif

#ifdef CAN_DEMO
    can_demo();
#endif

#ifdef PWMT_DEMO
    pwmt_demo();
#endif

#ifdef PIT_DEMO
    pit32_demo();
#endif

#ifdef TC_DEMO
    tc_demo();
#endif

#ifdef WDT_DEMO
    wdt_demo();
#endif

#ifdef EPORT_DEMO
    eport_demo();
#endif

#ifdef SPI_DEMO
    spi_demo();
#endif

#ifdef ADC_DEMO
    adc_demo();
#endif

#ifdef DAC_DEMO
    dac_demo();
#endif

#ifdef RTC_DEMO
    rtc_demo();
#endif

#ifdef I2C_DEMO
    i2c_demo();
#endif

#ifdef I2S_DEMO
    i2s_demo();
#endif

#ifdef RESET_DEMO
    reset_demo();
#endif

#ifdef LOWPOWER_DEMO
    lowerpower_demo();
#endif

#ifdef SSI_DEMO
    ssi_demo();
#endif

#ifdef SIDO_SD_TEST
    sdio_sd_test();
    // sdio_fatfs_test();
#endif

#ifdef ETH_DEMO
    eth_demo();
#endif

#ifdef FREERTOS_DEMO
    freertos_demo();
#endif

#ifdef IMGDEC_DEMO
    image_decoder_demo();
#endif

#ifdef AXIDMA_DEMO
    axidma_demo();
#endif

#ifdef I8080_DEMO
    i8080_demo();
#endif

#ifdef LCDC_DEMO
    lcdc_demo();
#endif

#ifdef TOUCH_DEMO
    touch_demo();
#endif
#ifdef DMA2D_DEMO
    dma2d_demo();
#endif

#ifdef LCDC_DMA2D_DEMO
    lcdc_dma2d_demo();
#endif

#ifdef JPEG_ACCELERATE_DEMO
    jpeg_accelerate_demo();
#endif

#ifdef USB_DEVICE_DEMO
    usb_device_demo();
#endif
#ifdef USB_HOST_DEMO
    usb_host_demo();
#endif

#ifdef DAC_AUDIO_DEMO
    audio_demo();
#endif

#ifdef NAND_FLASH_DEMO
    nandflash_demo();
#endif

#ifdef IAP_DEMO
    iap_demo();
#endif

#ifdef LVGL_DEMO
    lvgl_demo();
#endif

#ifdef USBH_UVC_DEMO
    usbh_uvc_demo();
#endif
}

/**
 * @brief 主函数入口
 *
 * @return int
 */
int main(void)
{
    // __enable_irq();
    // 获取系统时钟
    sys_cpm_getclk();

    // 初始化UART1, 默认波特率115200，8个有效数据位，无校验
    sys_uartdebuginit(UART1, g_ips_clk, 115200);

    // UART打印版本信息
    printfversion();

    // extern void iap_demo(void);
    // iap_demo();

    extern void uart_demo(void);
    uart_demo();

    extern void lvgl_demo(void);
    lvgl_demo();
	
    while (1)
    {
        // printf("app_run...\r\n");
    };

    return 0;
}
