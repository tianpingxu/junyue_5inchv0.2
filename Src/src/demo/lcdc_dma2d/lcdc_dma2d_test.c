/**
 * @file lcdc_test.c 
 * @author Product application department 
 * @brief  LCDC 模块测试用例，仅供参考
 * @version V1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup LCDC&DMA2D LCDC&DMA2D模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "lcdc_test_pic.h"
#include "lcdc_dma2d_test.h"

// 全局变量定义
#define L1_ADDR 	(0x1D000000)
#define L2_ADDR 	(0x1D400000)
#define LCDC_WIDTH 	(480)
#define LCDC_HEIGHT (272)


static rgb_input_timing_para_t p_rgb_para1 =
{
    .vsync = 4,
    .vbp = 12,
    .vfp = 8,
    .height = LCDC_HEIGHT,
    .hsync = 4,
    .hbp = 43,
    .hfp = 8,
    .width = LCDC_WIDTH,
    .background_color = RGB_WHITE,
    .l1_default_color = ARGB_CLEAR,
    .l2_default_color = ARGB_CLEAR, 
};

static rgb_input_timing_para_t p_rgb_para2 =
{
    .vsync = 4,
    .vbp = 12,
    .vfp = 8,
    .height = LCDC_HEIGHT,
    .hsync = 4,
    .hbp = 43,
    .hfp = 8,
    .width = LCDC_HEIGHT,
    .background_color = RGB_WHITE,
    .l1_default_color = ARGB_CLEAR,
    .l2_default_color = ARGB_CLEAR, 
};

static dma2d_reg2mem_t p_reg2mem =
{
	.color_mode = CM_ARGB8888,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
	.output_offset = 0,
	.out_addr = L1_ADDR,
	.out_color = ARGB_MAGENTA
};

static dma2d_reg2mem_t p_reg2mem1 =
{
	.color_mode = CM_ARGB8888,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
	.output_offset = 0,
	.out_addr = L2_ADDR,
	.out_color = ARGB_GREEN
};

static dma2d_mem2mem_t p_mem2mem =
{
	.fg_color_mode = CM_ARGB8888,
    .out_color_mode= CM_ARGB8888, 
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
	.fg_offset = 0,
	.output_offset = 0,
	.out_addr = L1_ADDR,	
    .fg_addr = (uint32_t)&image0_h_272_w_480
};

static dma2d_mem2mem_pfc_t p_mem2mem_f =
{
	.fg_color_mode = CM_RGB888,
    .out_color_mode= CM_RGB565, 
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
	.fg_offset = 0,
	.output_offset = 0,
	.out_addr = L2_ADDR,	
    .fg_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_mf_t p_mem2mem_mirror_h =
{
    .rotab_color_mode = CM_RGB888,
    .rotc_color_mode = CM_ARGB8888,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
    .rotab_offset = 0,
    .rotc_offset = 0,
    .rotc_addr = L1_ADDR,
    .rotab_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_mf_t p_mem2mem_mirror_v =
{
    .rotab_color_mode = CM_ARGB8888,
    .rotc_color_mode = CM_RGB565,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
    .rotab_offset = 0,
    .rotc_offset = 0,
    .rotc_addr = L2_ADDR,
    .rotab_addr = (uint32_t)&image0_h_272_w_480
};

static dma2d_mem2mem_mf_t p_mem2mem_rot180 =
{
    .rotab_color_mode = CM_ARGB8888,
    .rotc_color_mode = CM_RGB565,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
    .rotab_offset = 0,
    .rotc_offset = 0,
    .rotc_addr = L2_ADDR,
    .rotab_addr = (uint32_t)&image0_h_272_w_480
};

static dma2d_mem2mem_t p_mem2mem1 =
{
	.fg_color_mode = CM_RGB888,
    .out_color_mode= CM_RGB888, 
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
	.fg_offset = 0,
	.output_offset = 0,
	.out_addr = L1_ADDR,	
    .fg_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_mf_t p_mem2mem_rot90 =
{
    .rotab_color_mode = CM_RGB888,
    .rotc_color_mode = CM_RGB888,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
    .rotab_offset = 0,
    .rotc_offset = 0,
    .rotc_addr = L2_ADDR,
    .rotab_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_mf_t p_mem2mem_rot270 =
{
    .rotab_color_mode = CM_RGB888,
    .rotc_color_mode = CM_RGB888,
	.pixels_per_line = LCDC_WIDTH,
	.lines = LCDC_HEIGHT,
    .rotab_offset = 0,
    .rotc_offset = 0,
    .rotc_addr = L2_ADDR,
    .rotab_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_blend_t p_mem2mem_blend =
{
    .fg_color_mode = CM_ARGB8888,
    .bg_color_mode = CM_RGB888, 
    .out_color_mode = CM_RGB565, 
    .fg_alpha_mode = NO_MODIFY,
    .bg_alpha_mode = NO_MODIFY,
    .fg_fixed_alpha = 0XFF,
    .bg_fixed_alpha = 0XFF, 
    .pixels_per_line = LCDC_WIDTH / 2,
    .lines = LCDC_HEIGHT,
    .fg_offset = LCDC_WIDTH / 2,
    .bg_offset = LCDC_WIDTH / 2,
    .output_offset = LCDC_WIDTH / 2,
    .out_addr = L2_ADDR,
    .fg_addr = (uint32_t)&image0_h_272_w_480,
    .bg_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_blend_t p_mem2mem_rbs =
{
    .fg_color_mode = CM_ARGB8888,
    .bg_color_mode = CM_RGB888, 
    .out_color_mode = CM_RGB565, 
    .fg_alpha_mode = NO_MODIFY,
    .bg_alpha_mode = NO_MODIFY,
    .fg_fixed_alpha = 0XFF,
    .bg_fixed_alpha = 0XFF, 
    .pixels_per_line = LCDC_WIDTH,
    .lines = LCDC_HEIGHT,
    .fg_offset = 0,
    .bg_offset = 0,
    .output_offset = 0,
    .out_addr = L2_ADDR,
    .fg_addr = (uint32_t)&image0_h_272_w_480,
    .bg_addr = (uint32_t)&image1_h_272_w_480
};

static dma2d_mem2mem_rot_t p_mem2mem_rot =
{
    .rota_color_mode = CM_ARGB8888,
    .rotb_color_mode = CM_RGB888, 
    .rotc_color_mode = CM_RGB565, 
    .rota_alpha_mode = NO_MODIFY,
    .rotb_alpha_mode = NO_MODIFY,
    .rota_fixed_alpha = 0XFF,
    .rotb_fixed_alpha = 0XFF, 
    .rota_center_w = LCDC_WIDTH / 4,
    .rota_center_h = LCDC_HEIGHT / 4,
    .rota_w = LCDC_WIDTH,
    .rota_h = LCDC_HEIGHT,
    .rotb_center_w = LCDC_WIDTH / 4,
    .rotb_center_h = LCDC_HEIGHT / 4,
    .rotb_w = LCDC_WIDTH,
    .rotb_h = LCDC_HEIGHT,	
    .rotc_addr = L1_ADDR,
    .rota_addr = (uint32_t)&image0_h_272_w_480,
    .rotb_addr = (uint32_t)&image1_h_272_w_480,
    .sinv = 0.707,
    .cosv = 0.707,
	
};

// 函数定义
/**
 *  @brief  LCDC 模块测试示例函数
 * 
 */
void lcdc_dma2d_demo(void)
{
    status_t status = STATUS_OK;
	dma2d_func_t func = MEM2MEM_BLEND_FUNC;
    uint8_t layern = 0;
    uint8_t layer_en = 0;
	uint32_t l1_addr = L1_ADDR;
	uint32_t l2_addr = L2_ADDR;
	
    lcdc_pixel_format_t l1_format = LCDC_ARGB8888;
    lcdc_pixel_format_t l2_format = LCDC_RGB888;

	memset((uint8_t *)l1_addr, 0x00, LCDC_WIDTH * LCDC_HEIGHT * 4);
	memset((uint8_t *)l2_addr, 0x00, LCDC_WIDTH * LCDC_HEIGHT * 4);
	
    status = hal_lcdc_init(&p_rgb_para1);
    if (status != STATUS_OK)
    {
        printf("LCDC init fail!\n");
		return;
    }
    status = hal_lcdc_layer_switch(LAYER_OFF);
    if (status != STATUS_OK)
    {
        printf("LCDC background display fail!\n");
		return;
    }
    delay(100);
	
	switch(func)
	{
		case REG2MEM_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB888;
			hal_dma2d_reg2mem(DMA2D, &p_reg2mem);
			memcpy((uint8_t *)l2_addr,(uint8_t *)image1_h_272_w_480, p_rgb_para1.height * p_rgb_para1.width * 3);
		break;
		
		case MEM2MEM_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB888;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem);
			memcpy((uint8_t *)l2_addr,(uint8_t *)image1_h_272_w_480, p_rgb_para1.height * p_rgb_para1.width * 3);
		break;	
		
		case MEM2MEM_PFC_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem);
			hal_dma2d_mem2mem_pfc(DMA2D, &p_mem2mem_f);
		break;	
		
		case MEM2MEM_BLEND_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_reg2mem(DMA2D, &p_reg2mem);
			hal_dma2d_mem2mem_blend(DMA2D, &p_mem2mem_blend);
		break;	
		
		case MEM2MEM_MIRROR_V_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem);	
			hal_dma2d_mem2mem_mf(DMA2D, &p_mem2mem_mirror_v, ROT_ANT_VER_MIRROR);
		break;
		
		case MEM2MEM_MIRROR_H_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_mem2mem_pfc(DMA2D, &p_mem2mem_f);
			hal_dma2d_mem2mem_mf(DMA2D, &p_mem2mem_mirror_h, ROT_ANT_HOR_MIRROR);
		break;	
		
		case MEM2MEM_FIX_ROT180_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem);	
			hal_dma2d_mem2mem_mf(DMA2D, &p_mem2mem_rot180, ROT_ANT_ROTATE_180);
		break;	
		
		case MEM2MEM_FIX_ROT90_FUNC:
			l1_format = LCDC_RGB888;
			l2_format = LCDC_RGB888;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem1);	
			hal_dma2d_mem2mem_mf(DMA2D, &p_mem2mem_rot90, ROT_ANT_ROTATE_90);
		break;	
		
		case MEM2MEM_FIX_ROT270_FUNC:
			l1_format = LCDC_RGB888;
			l2_format = LCDC_RGB888;
			hal_dma2d_mem2mem(DMA2D, &p_mem2mem1);	
			hal_dma2d_mem2mem_mf(DMA2D, &p_mem2mem_rot270, ROT_ANT_ROTATE_270);
		break;		
		
		case MEM2MEM_RBS_FUNC:
			l1_format = LCDC_ARGB8888;
			l2_format = LCDC_RGB565;
			hal_dma2d_reg2mem(DMA2D, &p_reg2mem);
			hal_dma2d_mem2mem_rbs(DMA2D, &p_mem2mem_rbs, 1); 
		break;	
		
		case MEM2MEM_ROT_FUNC:
			l1_format = LCDC_RGB565;
			l2_format = LCDC_ARGB8888;
			hal_dma2d_reg2mem(DMA2D, &p_reg2mem1);
			hal_dma2d_mem2mem_rot(DMA2D, &p_mem2mem_rot, ROT_ANT_ROTATE_ANY); 
		break;		
		
		default:
			memcpy((uint8_t *)l1_addr,(uint8_t *)image0_h_272_w_480, p_rgb_para1.height * p_rgb_para1.width * 4);
			memcpy((uint8_t *)l2_addr,(uint8_t *)image1_h_272_w_480, p_rgb_para1.height * p_rgb_para1.width * 3);
		break;
	}

	delay(100);
    status = hal_lcdc_format_and_addr_config(&p_rgb_para1, l1_format, l2_format, l1_addr, l2_addr);
    if (status != STATUS_OK)
    {
        printf("LCDC sets L1 layer and L2 layer color format fail!\n");
		return;
    }

	delay(100);
    status = hal_lcdc_layer_switch(LAYER1_ON);
    if (status != STATUS_OK)
    {
        printf("LCDC L1层显示失败\n");
		return;
    }
    delay(100);
	
	status = hal_lcdc_layer_switch(LAYER_OFF);
    if (status != STATUS_OK)
    {
        printf("LCDC L1层显示失败\n");
		return;
    }
    delay(100);
	
    status = hal_lcdc_layer_switch(LAYER2_ON);
    if (status != STATUS_OK)
    {
        printf("LCDC L2层显示失败\n");
		return;
    }
    delay(100);
    while(1)
    {

    }
}

/** @} */  // 结束 LCDC&DMA2D 模块分组
/** @} */  // 结束外设模块分组
