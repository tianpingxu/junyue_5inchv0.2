/**
 * @file lv_ccore_decoder.c
 * @author Product application department
 * @brief CCORE 解码模块文件
 * @version V1.0
 * @date 2025-06-02
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */
// 头文件定义
#include "draw/lv_image_decoder_private.h"
#include "lvgl.h"
#include "ff.h"
#include "lv_ccore_decoder.h"
#include <string.h>
#include "image_decoder_test.h"
#include "chipconfig.h"

// 全局变量定义
#define DECODER_NAME "CCORE_DECODER"
static jfif_info_t image_info = {0};
static jpeg_outset_t jpeg_outset;

static uint8_t *lv_jpeg_image_sdr;
static uint8_t *lv_jpeg_image_sdr_out;
volatile uint32_t imagedecoder_flg1;
static lv_color_format_t lv_jpeg_image_cf;
FIL file;
__ALIGNED(8)
uint8_t buf_jpg[1024 * 600] __attribute__((section("NO_INIT")));
__ALIGNED(8)
uint8_t buf_raw[1024 * 600 * 4] __attribute__((section("NO_INIT")));
// 函数定义
static lv_result_t decoder_info(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc, lv_image_header_t *header);
static lv_result_t decoder_open(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc);
static void decoder_close(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc);
static lv_result_t decoder_get_area(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc,
                                    const lv_area_t *full_area, lv_area_t *decoded_area);
static int ccore_is_jpg(const uint8_t *raw_data, size_t len);

static void image_irq_handler1(void)
{
    imagedecoder_flg1 = 1;
    // printf("image decode irq\n");
}

void image_jpeg_decode1(uint32_t img_addr, uint32_t image_len, uint32_t out_addr)
{
    //	printf("img_addr=0x%0x,out_addr=0x%0x\r\n",img_addr,out_addr);
    status_t ret;
    uint8_t *jpeg_image_sdr;
    uint32_t i = 0;
    imagedecoder_flg1 = 0;
    image_decoder_initstructure_t image_decoder_init;
    image_decoder_init.image_type = IMAGE_JPEG;
    image_decoder_init.output_type = JPEG_OUTPUT_RGB888;
    image_decoder_init.image_addr = (uint32_t)img_addr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0; // 输出ARGB才会生效
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_irq_handler1;
    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }
    if (image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_flg1 == 0)
            ;
        imagedecoder_flg1 = 0;
    }
    else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
            ;
        hal_imagedecoder_clr_status();
    }
//    printf("jpeg decode ok\n");
}

void image_png_decode1(uint32_t img_addr, uint32_t image_len, uint32_t out_addr)
{
    status_t ret;
    imagedecoder_flg1 = 0;
    image_decoder_initstructure_t image_decoder_init;
    image_decoder_init.image_type = IMAGE_PNG;
    image_decoder_init.output_type = PNG_OUTPUT_ARGB888;
    image_decoder_init.image_addr = (uint32_t)img_addr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0;
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_irq_handler1;

    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }

    if (image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_flg1 == 0)
            ;
        imagedecoder_flg1 = 0;
    }
    else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
            ;
        hal_imagedecoder_clr_status();
    }

    //printf("png decode ok\n");
}
void lv_ccore_decoder_init(void)
{
    lv_image_decoder_t *dec = lv_image_decoder_create();
    lv_image_decoder_set_info_cb(dec, decoder_info);
    lv_image_decoder_set_open_cb(dec, decoder_open);
    //	lv_image_decoder_set_get_area_cb(dec, decoder_get_area);
    lv_image_decoder_set_close_cb(dec, decoder_close);

    dec->name = DECODER_NAME;
}

void lv_ccore_decoder_deinit(void)
{
    lv_image_decoder_t *dec = NULL;
    while ((dec = lv_image_decoder_get_next(dec)) != NULL)
    {
        if (dec->info_cb == decoder_info)
        {
            lv_image_decoder_delete(dec);
            break;
        }
    }
}

static lv_result_t decoder_info(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc, lv_image_header_t *header)
{
    LV_UNUSED(decoder); /*Unused*/
    const void *src = dsc->src;
    lv_image_src_t src_type = dsc->src_type; /*Get the source type*/

    if (src_type == LV_IMAGE_SRC_VARIABLE)
    {
		return LV_RESULT_INVALID;
        const lv_image_dsc_t *img_dsc = src;
        uint8_t *raw_data = (uint8_t *)img_dsc->data;
        const uint32_t raw_data_size = img_dsc->data_size;

        if (ccore_is_jpg(raw_data, raw_data_size) == true)
        {
#if LV_USE_FS_MEMFS
            header->cf = LV_COLOR_FORMAT_RAW;
            header->w = img_dsc->header.w;
            header->h = img_dsc->header.h;
            header->stride = img_dsc->header.w * 3;
            return LV_RESULT_OK;
#else
            LV_LOG_WARN("LV_USE_FS_MEMFS needs to enabled to decode from data");
            return LV_RESULT_INVALID;
#endif
        }
    }

    /*If it's a JPEG file...*/
    else if (src_type == LV_IMAGE_SRC_FILE)
    {
        const lv_image_dsc_t *img_dsc = src;
        const char *src = dsc->src;
        FATFS fs;
        const char *fn = src;
        FILINFO info;
        UINT br = 0;
        png_parse_info_t png_info = {0};
        const char *ext = lv_fs_get_ext(fn);
        if ((lv_strcmp(ext, "jpg") == 0) || (lv_strcmp(ext, "jpeg") == 0))
        {
            if(CM4211_FAFTS_MODE == 0)
            {
            f_mount(&fs, "0:", 1);
            }
            if(CM4211_FAFTS_MODE == 1)
            {
            f_mount(&fs, "1:", 1);
            }
            if(CM4211_FAFTS_MODE == 2)
            {
            f_mount(&fs, "2:", 1);
            }
            if(CM4211_FAFTS_MODE == 3)
            {
            f_mount(&fs, "3:", 1);
            }
            f_open(&file, fn, FA_CREATE_ALWAYS | FA_READ);
            f_stat(fn, &info);

            f_read(&file, buf_jpg, info.fsize, &br);
      

            if (hal_jpeg_parse((uint8_t *)buf_jpg, info.fsize, &image_info) != JFIF_RES_OK)
                return LV_RESULT_INVALID;
            header->cf = LV_COLOR_FORMAT_RAW;
            header->w = image_info.width;
            header->h = image_info.height;
            header->stride = image_info.width * 3;
        }
        else if (lv_strcmp(ext, "png") == 0)
        {
             if(CM4211_FAFTS_MODE == 0)
            {
            f_mount(&fs, "0:", 1);
            }
            if(CM4211_FAFTS_MODE == 1)
            {
            f_mount(&fs, "1:", 1);
            }
            if(CM4211_FAFTS_MODE == 2)
            {
            f_mount(&fs, "2:", 1);
            }
            if(CM4211_FAFTS_MODE == 3)
            {
            f_mount(&fs, "3:", 1);
            }
            f_open(&file, fn, FA_CREATE_ALWAYS | FA_READ);
            f_stat(fn, &info);

            f_read(&file, buf_jpg, info.fsize, &br);
           
            hal_png_fileparse(buf_jpg);
            png_info = hal_png_getparsedinfo();

            header->cf = LV_COLOR_FORMAT_RAW;
            header->w = png_info.ihdr_info.width;
            header->h = png_info.ihdr_info.height;
            header->stride = png_info.ihdr_info.width * 4;
           
        }

        return LV_RESULT_OK;
    }

    return LV_RESULT_OK; /*If didn't succeeded earlier then it's an error*/
}

static lv_result_t decoder_open(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc)
{
    LV_UNUSED(decoder);
    // lv_fs_file_t *f = lv_malloc(sizeof(lv_fs_file_t));
    if (dsc->src_type == LV_IMAGE_SRC_VARIABLE)
    {

#if LV_USE_FS_MEMFS
        const lv_image_dsc_t *img_dsc = dsc->src;
        if (is_jpg(img_dsc->data, img_dsc->data_size) == true)
        {
            lv_fs_path_ex_t path;
            lv_fs_make_path_from_buffer(&path, LV_FS_MEMFS_LETTER, img_dsc->data, img_dsc->data_size);
            lv_fs_res_t res;
            res = lv_fs_open(f, (const char *)&path, LV_FS_MODE_RD);
            if (res != LV_FS_RES_OK)
            {
                lv_free(f);
                return LV_RESULT_INVALID;
            }
        }
#else
        LV_LOG_WARN("LV_USE_FS_MEMFS needs to enabled to decode from data");
        return LV_RESULT_INVALID;
#endif
    }
    else if (dsc->src_type == LV_IMAGE_SRC_FILE)
    {
        FILINFO info;
        UINT br = 0;
        const char *fn = dsc->src;
        png_parse_info_t png_info = {0};
        lv_draw_buf_t *decoded = (void *)dsc->decoded;

        if (decoded == NULL)
        {
            decoded = lv_malloc_zeroed(sizeof(lv_draw_buf_t));
            dsc->decoded = decoded;
        }
        if ((lv_strcmp(lv_fs_get_ext(fn), "jpg") == 0) || (lv_strcmp(lv_fs_get_ext(fn), "jpeg") == 0))
        {
            f_open(&file,fn, FA_CREATE_ALWAYS | FA_READ);
            f_stat(fn, &info);
            SCB_InvalidateDCache();
            f_read(&file, buf_jpg, info.fsize, &br);
           
            image_jpeg_decode1((uint32_t)buf_jpg, info.fsize, (uint32_t)buf_raw);
            hal_jpeg_parse((uint8_t *)buf_jpg, info.fsize, &image_info);
            decoded->header.w = image_info.width;
            decoded->header.h = image_info.height;
            decoded->header.cf = LV_COLOR_FORMAT_RGB888;
            decoded->header.stride = image_info.width * 3;

            decoded->data = buf_raw;
            decoded->data_size = image_info.width * image_info.height * lv_color_format_get_bpp(LV_COLOR_FORMAT_RGB888);

            dsc->decoded = decoded;
        }
        else if ((lv_strcmp(lv_fs_get_ext(fn), "png") == 0))
        {
            f_open(&file, fn, FA_CREATE_ALWAYS | FA_READ);
            f_stat(fn, &info);
            SCB_InvalidateDCache();  
            f_read(&file, buf_jpg, info.fsize, &br);
           
            image_png_decode1((uint32_t)buf_jpg, info.fsize, (uint32_t)buf_raw);
            png_info = hal_png_getparsedinfo();

            decoded->header.w = png_info.ihdr_info.width;
            decoded->header.h = png_info.ihdr_info.height;
            decoded->header.cf = LV_COLOR_FORMAT_ARGB8888;
            decoded->header.stride = png_info.ihdr_info.width* 4;

            decoded->data = buf_raw;
            decoded->data_size = image_info.width * image_info.height * lv_color_format_get_bpp(LV_COLOR_FORMAT_ARGB8888);

            dsc->decoded = decoded;
        }

        if (dsc->args.no_cache)
            return LV_RESULT_OK;

        /*If the image cache is disabled, just return the decoded image*/
        if (!lv_image_cache_is_enabled())
            return LV_RESULT_OK;

        /*Add the decoded image to the cache*/
        lv_image_cache_data_t search_key;
        search_key.src_type = dsc->src_type;
        search_key.src = dsc->src;
        search_key.slot.size = decoded->data_size;

        lv_cache_entry_t *entry = lv_image_decoder_add_to_cache(decoder, &search_key, decoded, NULL);

        if (entry == NULL)
        {
            lv_draw_buf_destroy(decoded);
            return LV_RESULT_INVALID;
        }
        dsc->cache_entry = entry;

        return LV_RESULT_OK; /*If not returned earlier then it failed*/
    }

    return LV_RESULT_INVALID; /*If not returned earlier then it failed*/
}

static void decoder_close(lv_image_decoder_t *decoder, lv_image_decoder_dsc_t *dsc)
{
    LV_UNUSED(decoder); /*Unused*/
    lv_free((void *)dsc->decoded);
}

static int ccore_is_jpg(const uint8_t *raw_data, size_t len)
{
    const uint8_t jpg_signature[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46};
    if (len < sizeof(jpg_signature))
        return false;
    return memcmp(jpg_signature, raw_data, sizeof(jpg_signature)) == 0;
}