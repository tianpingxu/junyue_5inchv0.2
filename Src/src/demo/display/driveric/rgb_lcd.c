/**
 * @file rgb_lcd.c
 * @author Product Application Department
 * @brief  RGB LCD 硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup RGB RGB模块
 * @ingroup Peripherals
 * @{
 */

// 头文件定义
#include "rgb_lcd.h"
#include "delay.h"
// 全局变量定义

#if DISPLAY_RGB565
#define BYTE_RGB 2
#endif

#if DISPLAY_RGB888
#define BYTE_RGB 3
#endif

#if DISPLAY_ARGB8888
#define BYTE_RGB 4
#endif

#define PSRAM2ADDR(x) (uint32_t)((uint32_t)(x) & 0x00ffffff | 0xd0000000)

// L1 层，背景层
uint8_t ADDR_L1_CPU[LV_CCORE_WIDTH * LV_CCORE_HEIGHT * BYTE_RGB] __attribute__((section("EXRAM1"), aligned(8)));

// L2 层，前景层
uint8_t ADDR_L2_CPU[LV_CCORE_WIDTH * LV_CCORE_HEIGHT * BYTE_RGB] __attribute__((section("EXRAM1"), aligned(8)));

static uint32_t lvgl_decoder_flg = 0;
static image_decoder_initstructure_t image_lvgl_decoder_init;

static rgb_input_timing_para_t p_rgb_480272_para =
    {
        .vsync = 4,
        .vbp = 12,
        .vfp = 8,
        .height = 272,
        .hsync = 4,
        .hbp = 43,
        .hfp = 8,
        .width = 480,
        .clcdclk = 9 * 1000000, // 9MHz
        .background_color = RGB_WHITE,
        .l1_default_color = ARGB_CLEAR,
        .l2_default_color = ARGB_CLEAR,
};

static rgb_input_timing_para_t p_rgb_480854_para =
{
    .vsync = 2,
    .vbp = 12,
    .vfp = 360,
    .height = 854,
    .hsync = 2,
    .hbp = 40,
    .hfp = 40,
    .width = 480,
    .clcdclk = 36*1000000,
    .background_color = RGB_WHITE,
    .l1_default_color = ARGB_CLEAR,
    .l2_default_color = ARGB_CLEAR,
};

static rgb_input_timing_para_t p_rgb_1024600_para =
{
    .vsync = 2,
    .vbp = 12,
    .vfp = 95,//95
    .height = 600,
    .hsync = 2,
    .hbp = 40,
    .hfp = 40,
    .width = 1024,
    .clcdclk = 50*1000000,
    .background_color = RGB_WHITE,
    .l1_default_color = ARGB_CLEAR,
    .l2_default_color = ARGB_CLEAR, 
};
	

#define SPI_CS EPORT1_PIN0
#define SPI_CLK EPORT1_PIN1
#define SPI_SDA EPORT1_PIN3

#define LCD_RST EPORT1_PIN2

static void spi_io_init()
{
	SwitchPinFunction(SDH_CLK_FUN, EPORT1_PIN0_FUN);/* lcd_cs */
	SwitchPinFunction(SDH_CMD_FUN, EPORT1_PIN1_FUN);/* lcd_sck */
	SwitchPinFunction(SDH_DATA2_FUN, EPORT1_PIN3_FUN);/* lcd_sda */
	SwitchPinFunction(SDH_DATA3_FUN, EPORT1_PIN2_FUN);/* lcd_rst */

	SwitchPinFunction(UART3_TX_FUN, EPORT2_PIN6_FUN);/* lcd_backlight */
	/* lcd_cs */
	hal_eport_output(EPORT1, EPORT1_PIN0);
	/* lcd_sck */
	hal_eport_output(EPORT1, EPORT1_PIN1);
	/* lcd_sda */
	hal_eport_output(EPORT1, EPORT1_PIN3);
	/* lcd_rst */
	hal_eport_output(EPORT1, EPORT1_PIN2);
	/* lcd_backlight */
	hal_eport_output(EPORT2, EPORT2_PIN6);

	hal_eport_writepinlevel(EPORT1, SPI_CLK, 1);
	hal_eport_writepinlevel(EPORT1, SPI_SDA, 1);
	hal_eport_writepinlevel(EPORT1, SPI_CS, 1);

	hal_eport_writepinlevel(EPORT1, LCD_RST, 1);
	delayms(10);
	hal_eport_writepinlevel(EPORT1, LCD_RST, 0);
	delayms(50);
	hal_eport_writepinlevel(EPORT1, LCD_RST, 1);
	delayms(120);

	hal_eport_writepinlevel(EPORT2, EPORT2_PIN6, 1);
}

static inline void panel_spi_set_scl(uint32_t value)
{
	hal_eport_writepinlevel(EPORT1, SPI_CLK, value);
}

static inline void panel_spi_set_sdi(uint32_t value)
{
    hal_eport_writepinlevel(EPORT1, SPI_SDA, value);
}

static inline void panel_spi_set_cs(uint32_t value)
{
   hal_eport_writepinlevel(EPORT1, SPI_CS, value);
}

void panel_spi_cmd_wr(uint8_t cmd)
{
	uint32_t i;

	panel_spi_set_cs(0);

	panel_spi_set_sdi(0);
	panel_spi_set_scl(0);

	delayus(1);
	panel_spi_set_scl(1);

	delayus(1);
	panel_spi_set_scl(0);

	for (i = 0; i < 8; i++) {
		if ((cmd & 0x80) == 0x80)
			panel_spi_set_sdi(1);
		else
			panel_spi_set_sdi(0);

		delayus(1);
		panel_spi_set_scl(1);
		delayus(1);
		panel_spi_set_scl(0);
		delayus(1);
		cmd = cmd << 1;
	}

	panel_spi_set_cs(1);
	panel_spi_set_sdi(0);
	panel_spi_set_scl(0);
	delayus(1);
}

void panel_spi_data_wr(uint8_t data)
{
	uint32_t i;

	panel_spi_set_cs(0);
	panel_spi_set_scl(0);
	panel_spi_set_sdi(1);

	delayus(1);
	panel_spi_set_scl(1);

	delayus(1);
	panel_spi_set_scl(0);

	for (i = 0; i < 8; i++) {
		if ((data & 0x80) == 0x80)
			panel_spi_set_sdi(1);
		else
			panel_spi_set_sdi(0);

		delayus(1);
		panel_spi_set_scl(1);
		delayus(1);
		panel_spi_set_scl(0);
		delayus(1);
		data = data << 1;
	}
	panel_spi_set_cs(1);
	panel_spi_set_scl(0);
	panel_spi_set_sdi(0);
	delayus(1);
}

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define panel_spi_send_seq(command, seq...) do {                    \
        static const uint8_t d[] = { seq };                              \
        int i;                                                      \
        panel_spi_cmd_wr(command);                                  \
        for (i = 0; i < ARRAY_SIZE(d); i++)                         \
            panel_spi_data_wr(d[i]);                                \
    } while (0)

void LCD_SPI_Init()
{
	spi_io_init();
	//------------- KEY -----------------
	panel_spi_send_seq(0x99,0x71,0x02,0xa2);
	panel_spi_send_seq(0x99,0x71,0x02,0xa3);
	panel_spi_send_seq(0x99,0x71,0x02,0xa4);
	//-----------------------------------
	//------Power------------------------
	//VGH_VGL
	panel_spi_send_seq(0xB0,0x22,0x6B,0x1E,0x89,0x2F,0x39,0x39,0x2F,0x14,0x1F,0x33);
	//Source
	panel_spi_send_seq(0xB7,0x6E,0x6E);
	//VCOM
	panel_spi_send_seq(0xBF,0x54,0x54);
	//-----------------------------------
	//------GIP--------------------------
	//TP 2MS
	panel_spi_send_seq(0xD7,0x00,0x0E,0xC7,0x19,0xAB,0xAB);
	panel_spi_send_seq(0xA3,0x40,0x03,0x80,0xFF,0x44,0x00,0x00,0x00,0x00,0x05,0x00,0x68,0x00,0x0A,0x00,0x45,0x05,0x00,0x00,0x00,0x00,0x46,0x00,0x00,0x02,0x6F,0x52,0x00,0x05,0x00,0x00,0xFF);
	panel_spi_send_seq(0xA6,0x0E,0x00,0x24,0x44,0x35,0x00,0x38,0x00,0x80,0x80,0x00,0x24,0x44,0x36,0x00,0x37,0x00,0x80,0x80,0x02,0xEC,0x77,0x33,0x05,0x00,0x06,0x2F,0x5E,0x00,0xAC,0x11,0x32,0x06,0x00,0x00,0x2F,0x5E,0x00,0x00,0x06,0x00,0x00,0x00,0x00);
	panel_spi_send_seq(0xA7,0x19,0x19,0x00,0x64,0x40,0x05,0x14,0x41,0x02,0x06,0x05,0x80,0x80,0x00,0x64,0x40,0x23,0x67,0x03,0x00,0x04,0x00,0x80,0x80,0x00,0x64,0x40,0x4B,0x5A,0x00,0x00,0x02,0x01,0x80,0x80,0x00,0x24,0x40,0x69,0x78,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x44);
	panel_spi_send_seq(0xAC,0x10,0x13,0x12,0x1B,0x09,0x01,0x04,0x1B,0x06,0x02,0x19,0x1B,0x1B,0x1B,0x18,0x1B,0x11,0x0B,0x0A,0x1B,0x08,0x03,0x04,0x1B,0x06,0x00,0x19,0x1B,0x1B,0x1B,0x18,0x1B,0x77,0x67,0x77,0x67,0x00);
	panel_spi_send_seq(0xAD,0xCC,0x40,0x46,0x00,0x06,0x5E,0x2F);
	panel_spi_send_seq(0xE8,0x30,0x07,0x00,0x9C,0x9C);
	panel_spi_send_seq(0xB2,0x15,0x11,0x05,0x23,0x59,0x83,0x03,0x2E,0x5A);
	//1   2    3	4	 5	  6    7	8	 9	  10   11	12	 13   14   15	16	 17   18   19	20	 21   22   23	24	 25   26   27	28	 29   30   31	32	 33   34   35	36	 37   38   39	40	 41   42   43	44
	panel_spi_send_seq(0xE7,0x8B,0x3C,0x00,0x0C,0xF0,0x5D,0x00,0x5D,0x00,0x5D,0x00,0x5D,0x00,0xFF,0x00,0x08,0x7B,0x00,0x00,0xC8,0x6A,0x5A,0x08,0x1A,0x3C,0x00,0x91,0x01,0xCC,0x01,0x7F,0xF0,0x22);
	
	panel_spi_send_seq(0xE9,0x3C,0x7F,0x08,0x07,0x1A,0x7A,0x22,0x1A,0x33);
	
	//------Gamma------------------------
	panel_spi_send_seq(0xC8,0x00,0x00,0x15,0x26,0x44,0x00,0x78,0x03,0xBE,0x06,0x11,0x1C,0x09,0x8A,0x03,0x21,0xD4,0x01,0x11,0x0F,0x22,0x4A,0x0F,0x8F,0x0A,0x32,0xF0,0x0A,0x41,0x0D,0xF3,0x80,0x0D,0xAE,0xC5,0x03,0xC4);
	panel_spi_send_seq(0xC9,0x00,0x00,0x15,0x26,0x44,0x00,0x78,0x03,0xBE,0x06,0x11,0x1C,0x09,0x8A,0x03,0x21,0xD4,0x01,0x11,0x0F,0x22,0x4A,0x0F,0x8F,0x0A,0x32,0xF0,0x0A,0x41,0x0D,0xF3,0x80,0x0D,0xAE,0xC5,0x03,0xC4);
	//-----------------------------------
	//------------- Lock KEY -----------------
	//panel_spi_send_seq(0x99,0x71,0x02,0x00);
	//-----------------------------------
	panel_spi_send_seq(0x36,0x00);
	//panel_spi_send_seq(0x3a,0x60);
	
	panel_spi_send_seq(0x62,0x00);
	
	panel_spi_send_seq(0x11);	
	
	delayms(120);
	
	panel_spi_send_seq(0x29);	
	
	delayms(30);

}

void LCD_EnterSleep_ST77102(void)
{
    panel_spi_send_seq(0x28); 
    delayms(20);
    panel_spi_send_seq(0x10); 
}
 
void LCD_ExtiSleep_ST77102(void)
{
    panel_spi_send_seq(0x11); 
    delayms(120);
    panel_spi_send_seq(0x29);
}

// 函数定义
/**
 * @brief RGB 模块屏幕初始化函数
 *
 * @param ic 屏幕驱动
 * @return lcd_status_t 初始化成功与否
 */
lcd_status_t RGBLCD_Init(lcd_driveric_t ic)
{
    lcd_status_t status = LCD_OK;
    status_t lcdc_status;
    uint8_t layern = 0;
    uint8_t layer_en = 0;
    uint32_t l1_addr = PSRAM2ADDR((uint32_t)ADDR_L1_CPU);
    uint32_t l2_addr = PSRAM2ADDR((uint32_t)ADDR_L2_CPU);
    uint32_t l1_alpha = 0xFF;
    uint32_t l2_alpha = 0xFF;
    uint8_t l1_f1 = 1;
    uint8_t l1_f2 = 1;
    uint8_t l2_f1 = 1;
    uint8_t l2_f2 = 1;

#if DISPLAY_RGB565
    lcdc_pixel_format_t l1_format = LCDC_RGB565;
    lcdc_pixel_format_t l2_format = LCDC_RGB565;
#endif

#if DISPLAY_RGB888
    lcdc_pixel_format_t l1_format = LCDC_RGB888;
    lcdc_pixel_format_t l2_format = LCDC_RGB888;
#endif

#if DISPLAY_ARGB8888

#if LV_CCORE_RENDER_MODE_NO_A
    lcdc_pixel_format_t l1_format = LCDC_ARGB8888;
#elif LV_CCORE_RENDER_MODE_USE_A
    lcdc_pixel_format_t l1_format = LCDC_RGB888; // 根据背景层图片资源格式调整
#endif

    lcdc_pixel_format_t l2_format = LCDC_ARGB8888;
#endif

    switch (ic)
    {
    case RGB_480272:
        lcdc_status = hal_lcdc_init(&p_rgb_480272_para);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC init fail!\n");
            status = LCD_ERR;
            break;
        }
        lcdc_status = hal_lcdc_format_and_addr_config(&p_rgb_480272_para, l1_format, l2_format, l1_addr, l2_addr);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC format and addr config fail!\n");
            status = LCD_ERR;
            break;
        }
        break;
    case RGB_480854:
        printf("RGB_480854 init start\r\n");
        LCD_SPI_Init();
        lcdc_status = hal_lcdc_init(&p_rgb_480854_para);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC init fail!\n");
            status = LCD_ERR;
            break;
        }
        lcdc_status = hal_lcdc_format_and_addr_config(&p_rgb_480854_para, l1_format, l2_format, l1_addr, l2_addr);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC format and addr config fail!\n");
            status = LCD_ERR;
            break;
        }
        printf("RGB_480854 init end\r\n");
        break;
    case RGB_1024600:
        printf("RGB_1024600 init start\r\n");
		LCD_SPI_Init();
        lcdc_status = hal_lcdc_init(&p_rgb_1024600_para);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC init fail!\n");
            status = LCD_ERR;
            break;
        }
        lcdc_status = hal_lcdc_format_and_addr_config(&p_rgb_1024600_para, l1_format, l2_format, l1_addr, l2_addr);
        if (lcdc_status != STATUS_OK)
        {
            LCDLOG_DEBUG("LCDC format and addr config fail!\n");
            status = LCD_ERR;
            break;
        }
        printf("RGB_1024600 init end\r\n");
        break;
    default:
        LCDLOG_DEBUG("Nothing init.\n");
        break;
    }

#if LV_CCORE_RENDER_MODE_USE_A
    lcdc_status = hal_lcdc_layer_blend_config(l1_alpha, l2_alpha, l1_f1, l1_f2, l2_f1, l2_f2);
    if (lcdc_status != STATUS_OK)
    {
        LCDLOG_DEBUG("LCDC blend config fail!\n");
        status = LCD_ERR;
        return status;
    }
    axiflow_cdc_blend();
#endif

    lcdc_status = hal_lcdc_layer_switch(LAYER_OFF);
    if (lcdc_status != STATUS_OK)
    {
        LCDLOG_DEBUG("LCDC layer1 display fail!\n");
        status = LCD_ERR;
    }

    return status;
}

/**
 * @brief RGB 屏幕刷屏函数
 *
 * @param sx 起始x轴坐标
 * @param sy 起始y轴坐标
 * @param ex 终止x轴坐标
 * @param ey 终止y轴坐标
 * @param color 刷图buffer
 */

void LCD_RGB_Color_Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint8_t *color)
{
    static uint8_t flg = 1;
    static uint32_t switch_flg = 0;
    static uint32_t width, height;
    dma2d_mem2mem_t p_mem2mem;

    if (flg)
    {
        flg = 0;
#if LV_CCORE_RENDER_MODE_USE_A
        hal_lcdc_layer_switch(LAYER_ALL_ON);
#else
        hal_lcdc_layer_switch(LAYER2_ON);
#endif
    }

#if LV_CCORE_RENDER_MODE_PARTIAL
    int32_t x;
    int32_t y;
    uint8_t *color_byte = color;
    width = ex - sx + 1;
    height = ey - sy + 1;
#if DISPLAY_RGB565
    if (width == LV_CCORE_WIDTH && height == LV_CCORE_HEIGHT)
    {
        p_mem2mem.fg_color_mode = CM_RGB565;
        p_mem2mem.out_color_mode = CM_RGB565;
        p_mem2mem.pixels_per_line = LV_CCORE_WIDTH;
        p_mem2mem.lines = LV_CCORE_HEIGHT;
        p_mem2mem.fg_offset = 0;
        p_mem2mem.output_offset = 0;
        p_mem2mem.fg_addr = (uint32_t)color;
        p_mem2mem.out_addr = (uint32_t)ADDR_L2_CPU;
        hal_dma2d_mem2mem(DMA2D, &p_mem2mem);
    }
    else
    {
        for (y = sy; y <= ey; y++)
        {
            uint8_t *dst = ADDR_L2_CPU + (y * LV_CCORE_WIDTH + sx) * 2;
            memcpy(dst, color_byte, width * 2);
            color_byte += width * 2;
        }
    }

#endif

#if DISPLAY_RGB888
    if (width == LV_CCORE_WIDTH && height == LV_CCORE_HEIGHT)
    {
        p_mem2mem.fg_color_mode = CM_RGB888;
        p_mem2mem.out_color_mode = CM_RGB888;
        p_mem2mem.pixels_per_line = LV_CCORE_WIDTH;
        p_mem2mem.lines = LV_CCORE_HEIGHT;
        p_mem2mem.fg_offset = 0;
        p_mem2mem.output_offset = 0;
        p_mem2mem.fg_addr = (uint32_t)color;
        p_mem2mem.out_addr = (uint32_t)ADDR_L2_CPU;
        hal_dma2d_mem2mem(DMA2D, &p_mem2mem);
    }
    else
    {
        for (y = sy; y <= ey; y++)
        {
            uint8_t *dst = ADDR_L2_CPU + (y * LV_CCORE_WIDTH + sx) * 3;
            memcpy(dst, color_byte, width * 3);
            color_byte += width * 3;
        }
    }

#endif

#if DISPLAY_ARGB8888

    if (width == LV_CCORE_WIDTH && height == LV_CCORE_HEIGHT)
    {
        p_mem2mem.fg_color_mode = CM_ARGB8888;
        p_mem2mem.out_color_mode = CM_ARGB8888;
        p_mem2mem.pixels_per_line = LV_CCORE_WIDTH;
        p_mem2mem.lines = LV_CCORE_HEIGHT;
        p_mem2mem.fg_offset = 0;
        p_mem2mem.output_offset = 0;
        p_mem2mem.fg_addr = (uint32_t)color;
        p_mem2mem.out_addr = (uint32_t)ADDR_L2_CPU;
        hal_dma2d_mem2mem(DMA2D, &p_mem2mem);
    }
    else
    {
        for (y = sy; y <= ey; y++)
        {
            uint8_t *dst = ADDR_L2_CPU + (y * LV_CCORE_WIDTH + sx) * 4;
            memcpy(dst, color_byte, width * 4);
            color_byte += width * 4;
        }
    }

#endif

#elif LV_CCORE_RENDER_MODE_FULL
    hal_lcdc_switch_address(LAYER2_ON, PSRAM2ADDR((uint32_t)(color)));
#endif
}

/**
 * @brief LVGL 图像 IRQ 处理函数
 *
 */
static void lvgl_image_irq_handler(void)
{
    lvgl_decoder_flg = 1;
}
/**
 * @brief LVGL 图像解码函数
 *
 * @param img_type 输入图像类型
 * @param output_type 输出图像格式
 * @param img_addr 输入图像地址
 * @param image_len 输入图像长度
 * @param out_addr 输出图像地址
 */
void lvgl_decode(image_type_t img_type, image_output_type_t output_type, uint32_t img_addr, uint32_t image_len, uint32_t out_addr)
{
    status_t ret;
    image_lvgl_decoder_init.image_type = img_type;
    image_lvgl_decoder_init.output_type = output_type;
    image_lvgl_decoder_init.image_addr = img_addr;
    image_lvgl_decoder_init.image_len = image_len;
    image_lvgl_decoder_init.out_addr0 = out_addr;
    image_lvgl_decoder_init.out_addr1 = 0;
    image_lvgl_decoder_init.out_addr2 = 0;
    image_lvgl_decoder_init.alpha = 0; // 输出ARGB才会生效
    image_lvgl_decoder_init.dither_en = 1;
    image_lvgl_decoder_init.crop_en = 0;
    image_lvgl_decoder_init.crop_width = 0;
    image_lvgl_decoder_init.crop_height = 0;
    image_lvgl_decoder_init.decoder_irq_en = 0;
    image_lvgl_decoder_init.image_decoder_irq_cb = lvgl_image_irq_handler;

    ret = hal_imagedecoder_init(&image_lvgl_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }
    if (image_lvgl_decoder_init.decoder_irq_en)
    {
        while (lvgl_decoder_flg == 0)
            ;
        lvgl_decoder_flg = 0;
    }
    else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
            ;
        hal_imagedecoder_clr_status();
    }
    printf("decode ok\n");
}

/** @} */ // 结束 RGB 模块分组
/** @} */ // 结束外设模块分组
