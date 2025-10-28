/**
 * @file image_decoder_hal.c
 * @author Product Application Department
 * @brief  IMGDECODE 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
// 头文件包含
#include "image_decoder_hal.h"

// 全局变量定义
image_decoder_initstructure_t *g_image_decoder_init;

static jfif_info_t jfif_info = {0};
static png_parse_info_t g_parsed_info = {0};
static const uint8_t PNG_FILE_SIGN[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
static png_parse_info_t parsed_info = {0};
static png_param_cfg_t m_param_cfg = {0};
//volatile uint8_t plte_buffer[1000]  __attribute__((aligned(8)));
extern uint32_t jpeg_time_id;
extern uint32_t png_time_id;
// 函数定义

/**
 * @brief 初始化图像解码器配置
 *
 * @param image_decoder_init 图像解码器配置结构体
 * @return status_t 配置结果
 */
status_t hal_imagedecoder_init(image_decoder_initstructure_t *image_decoder_init)
{
    if (((uint32_t)(image_decoder_init->image_addr) & 0x7) != 0)
        return STATUS_ADDR_ERR;
    g_image_decoder_init = image_decoder_init;
    switch (image_decoder_init->image_type)
    {
    case IMAGE_JPEG:
        return hal_jpeg_decode(image_decoder_init);
        break;
    case IMAGE_PNG:
        return hal_png_decode(image_decoder_init);
        break;
    default:
        break;
    }
    return STATUS_ERROR;
}

/**
 * @brief 使用解码器解码PNG图片
 *
 * @param png_decoder_init
 * @return status_t
 */
status_t hal_png_decode(image_decoder_initstructure_t *png_decoder_init)
{
    png_parse_err_t parse_ret = PARSE_SUCCESS;
    uint8_t *png_image_addr;

    png_image_addr = (uint8_t *)png_decoder_init->image_addr;
    parse_ret = hal_png_fileparse(png_image_addr);

    if (parse_ret != PARSE_SUCCESS)
        return STATUS_ERROR;

    parsed_info = hal_png_getparsedinfo();

    if (parsed_info.plte_info.is_chunkExist)
    {
        if (parsed_info.plte_info.plte_payload_addr & 0x7)
        {
            printf("png plte chunk\r\n");
            return STATUS_TYPE_ERR;
            //	m_param_cfg.plte_copy_addr = (uint32_t)plte_buffer;
            //	memcpy((void *)(m_param_cfg.plte_copy_addr), (void *)(parsed_info.plte_info.plte_payload_addr), parsed_info.plte_info.plte_payload_len);
        }
    }

    // OUTPUT config
    m_param_cfg.out_height = parsed_info.ihdr_info.height;
    m_param_cfg.out_width = parsed_info.ihdr_info.width;

    if (png_decoder_init->output_type >= PNG_OUTPUT_RGB888 && png_decoder_init->output_type <= PNG_OUTPUT_ARGB888)
    {
        m_param_cfg.out_format = PNG_OUT_RGB;

        switch (png_decoder_init->output_type)
        {
        case PNG_OUTPUT_RGB888:
            m_param_cfg.out_rgb_format = PNG_OUT_RGB888;
            break;
        case PNG_OUTPUT_BGR888:
            m_param_cfg.out_rgb_format = PNG_OUT_BGR888;
            break;
        case PNG_OUTPUT_ABGR888:
            m_param_cfg.out_rgb_format = PNG_OUT_ABGR888;
            break;
        case PNG_OUTPUT_ARGB888:
            m_param_cfg.out_rgb_format = PNG_OUT_ARGB888;
            break;
        default:
            break;
        }

        m_param_cfg.out_channel_num = 4;
    }
    else
        return STATUS_ERROR;

    // PNG 图片只有输出无A通道此配置才会自动生效
    m_param_cfg.out_alpha_val = png_decoder_init->alpha;
    m_param_cfg.dither_en = ENABLE;

    m_param_cfg.out_base_addr = png_decoder_init->out_addr0;
    m_param_cfg.out_chroma_addr = 0;
    m_param_cfg.out_v_addr = 0;

    m_param_cfg.crop_enable = png_decoder_init->crop_en;
    m_param_cfg.crop_width = png_decoder_init->crop_width;
    m_param_cfg.crop_height = png_decoder_init->crop_height;

    hal_png_init(png_decoder_init->decoder_irq_en);
    if (hal_png_decode_set(parsed_info, m_param_cfg) != PNG_CONFIG_SUCCESS)
        return STATUS_ERROR;
    hal_imagedecoder_start();

    return STATUS_OK;
}

/**
 * @brief 使用解码器解码JPEG图片
 *
 * @param jpeg_decoder_init
 * @return status_t
 */
status_t hal_jpeg_decode(image_decoder_initstructure_t *jpeg_decoder_init)
{
    uint8_t *jpeg_image_sdr;
    jpeg_outset_t jpeg_outset;
    jpeg_parse_err_t parse_ret;

    jpeg_image_sdr = (uint8_t *)jpeg_decoder_init->image_addr;
    parse_ret = hal_jpeg_parse(jpeg_image_sdr, jpeg_decoder_init->image_len, &jfif_info);
    if (parse_ret != JFIF_RES_OK)
    {
        printf("jpeg parse error, ret = %d\r\n", parse_ret);
        // printf("jpeg_image_sdr=0x%x, jpeg_image_len=%d\r\n", jpeg_image_sdr, jpeg_decoder_init->image_len);
        // while(1);
        return STATUS_HANDLE_ERR;
    }
    // printf("jpeg_image_sdr=0x%x, jpeg_image_len=%d\r\n", jpeg_image_sdr, jpeg_decoder_init->image_len);
    // return STATUS_ERROR;

    if (jpeg_decoder_init->output_type >= JPEG_OUTPUT_YUV420_0 && jpeg_decoder_init->output_type <= JPEG_OUTPUT_YUV444_0)
    {
        jpeg_outset.output_rgb = 0;
        jpeg_outset.y_addr = jpeg_decoder_init->out_addr0;
        jpeg_outset.u_addr = jpeg_decoder_init->out_addr1;
        jpeg_outset.v_addr = jpeg_decoder_init->out_addr2;

        switch (jpeg_decoder_init->output_type)
        {
        case JPEG_OUTPUT_YUV420_0:
            jpeg_outset.format = PP_OUTPUT_YUV420_0;
            break;
        case JPEG_OUTPUT_YUV400_0:
            jpeg_outset.format = PP_OUTPUT_YUV400_0;
            break;
        case JPEG_OUTPUT_YUV422_0:
            jpeg_outset.format = PP_OUTPUT_YUV422_0;
            break;
        case JPEG_OUTPUT_YUV444_0:
            jpeg_outset.format = PP_OUTPUT_YUV444_0;
            break;
        default:
            break;
        }
    }
    else if (jpeg_decoder_init->output_type >= JPEG_OUTPUT_BGR888 && jpeg_decoder_init->output_type <= JPEG_OUTPUT_RGB565)
    {
        jpeg_outset.output_rgb = 1;
        jpeg_outset.rgb_addr = jpeg_decoder_init->out_addr0;
        switch (jpeg_decoder_init->output_type)
        {
        case JPEG_OUTPUT_BGR888:
            jpeg_outset.format = PP_OUTPUT_BGR888;
            break;
        case JPEG_OUTPUT_RGB888:
            jpeg_outset.format = PP_OUTPUT_RGB888;
            break;
        case JPEG_OUTPUT_ABGR888:
            jpeg_outset.format = PP_OUTPUT_ABGR888;
            break;
        case JPEG_OUTPUT_ARGB888:
            jpeg_outset.format = PP_OUTPUT_ARGB888;
            break;
        case JPEG_OUTPUT_BGRA888:
            jpeg_outset.format = PP_OUTPUT_BGRA888;
            break;
        case JPEG_OUTPUT_RGBA888:
            jpeg_outset.format = PP_OUTPUT_RGBA888;
            break;
        case JPEG_OUTPUT_BGR565:
            jpeg_outset.format = PP_OUTPUT_BGR565;
            break;
        case JPEG_OUTPUT_RGB565:
            jpeg_outset.format = PP_OUTPUT_RGB565;
            break;
        default:
            break;
        }
    }
    else
        return STATUS_ERROR;

    jpeg_outset.crop_enable = jpeg_decoder_init->crop_en;
    jpeg_outset.crop_width = jpeg_decoder_init->crop_width;
    jpeg_outset.crop_height = jpeg_decoder_init->crop_height;
    jpeg_outset.output_alpha = jpeg_decoder_init->alpha;

    hal_jpeg_init(jpeg_decoder_init->decoder_irq_en);
    hal_jpeg_decode_set(&jfif_info, &jpeg_outset);
    hal_imagedecoder_start();

    return STATUS_OK;
}
/**
 * @brief 对PNG图片进行解析
 *
 * @param inputStream 输入的PNG图片流
 * @return png_parse_err_t 解析结果
 */
png_parse_err_t hal_png_fileparse(uint8_t inputStream[])
{
    uint32_t stream_idx = 0;
    uint32_t chunk_sign = 0x0;
    uint32_t chunk_len = 0x0;

    // 1. compare the file signature
    uint8_t sign_idx = 0;
    for (sign_idx = 0; sign_idx < sizeof(PNG_FILE_SIGN); sign_idx++)
    {
        if (PNG_FILE_SIGN[sign_idx] != inputStream[sign_idx])
        {
            return PARSE_FILE_SING_ERR;
        }
    }

    // clear g_parsed_info
    memset(&g_parsed_info, 0, sizeof(g_parsed_info));

    // 2. stream index offset
    stream_idx += sizeof(PNG_FILE_SIGN);

    // 3. chunk parse
    while (chunk_sign != IEND_CHUNK_SIGN)
    {
        chunk_sign = ((inputStream[stream_idx + 4] << 24) | (inputStream[stream_idx + 5] << 16) | (inputStream[stream_idx + 6] << 8) | (inputStream[stream_idx + 7]));
        chunk_len = ((inputStream[stream_idx] << 24) | (inputStream[stream_idx + 1] << 16) | (inputStream[stream_idx + 2] << 8) | (inputStream[stream_idx + 3]));
        //@TODO CRC check
        switch (chunk_sign)
        {
        case IHDR_CHUNK_SIGN:
        {
            g_parsed_info.ihdr_info.width = ((inputStream[stream_idx + 8] << 24) | (inputStream[stream_idx + 9] << 16) | (inputStream[stream_idx + 10] << 8) | (inputStream[stream_idx + 11]));
            g_parsed_info.ihdr_info.height = ((inputStream[stream_idx + 12] << 24) | (inputStream[stream_idx + 13] << 16) | (inputStream[stream_idx + 14] << 8) | (inputStream[stream_idx + 15]));
            g_parsed_info.ihdr_info.bit_depth = inputStream[stream_idx + 16];
            g_parsed_info.ihdr_info.color_type = (png_color_type_t)inputStream[stream_idx + 17];
            g_parsed_info.ihdr_info.compression_method = inputStream[stream_idx + 18];
            g_parsed_info.ihdr_info.filter_method = inputStream[stream_idx + 19];
            g_parsed_info.ihdr_info.interface_method = inputStream[stream_idx + 20];
//            printf("IHDR Width = %d,Height = %d\r\n", g_parsed_info.ihdr_info.width, g_parsed_info.ihdr_info.height);
            break;
        }

        case PLTE_CHUNK_SIGN:
        {
            g_parsed_info.plte_info.is_chunkExist = 1;
            g_parsed_info.plte_info.plte_payload_addr = (uint32_t)(&inputStream[stream_idx + PNG_CHUNK_LEN_SIZE + PNG_CHUNK_TYPE_SIZE]);
            g_parsed_info.plte_info.plte_payload_len = chunk_len;
            break;
        }

        case IDAT_CHUNK_SIGN:
        {
            if (g_parsed_info.idat_info.idat_start_addr == 0x0)
            {
                // addr align(8)
                uint8_t addr_offset = (uint32_t)(&inputStream[stream_idx]) & 0x7;

                g_parsed_info.idat_info.idat_start_addr = ((uint32_t)(&inputStream[stream_idx]) - addr_offset);
                g_parsed_info.idat_info.idat_total_len += addr_offset;
                g_parsed_info.idat_info.idat_stream_offset = addr_offset * 8;
            }

            g_parsed_info.idat_info.idat_total_len += (PNG_CHUNK_LEN_SIZE + PNG_CHUNK_TYPE_SIZE + PNG_CHUNK_CRC_SIZE + chunk_len);
            break;
        }

        case IEND_CHUNK_SIGN:
        {
            if (g_parsed_info.idat_info.idat_start_addr == 0x0)
                return PARSE_IDAT_LOSS_ERR;

            break;
        }
        default:
        {
            break;
        }
        }

        stream_idx += (PNG_CHUNK_LEN_SIZE + PNG_CHUNK_TYPE_SIZE + PNG_CHUNK_CRC_SIZE + chunk_len);
    }

    return PARSE_SUCCESS;
}
/**
 * @brief 获取解析后的PNG图片信息
 *
 * @return png_parse_info_t PNG图像信息
 */
png_parse_info_t hal_png_getparsedinfo(void)
{
    return g_parsed_info;
}
/**
 * @brief 对JPEG图片进行解析
 *
 * @param buf 输入的JPEG图片流
 * @param len JPEG数据流长度
 * @param jfif_info JPEG图片信息
 * @return jpeg_parse_err_t 解析结果
 */
jpeg_parse_err_t hal_jpeg_parse(uint8_t buf[], uint32_t len, jfif_info_t *jfif_info)
{
    uint32_t index = 0;
    uint16_t marker;
    uint16_t blklen;
    uint32_t i, start_dqt;
    uint8_t end_flg;
    uint32_t exif_flg = 1;

    end_flg = 1;
    start_dqt = 1;
    memset(jfif_info, 0x00, sizeof(jfif_info_t));

    jfif_info->jpeg_len = len;
    jfif_info->jpeg_addr = (uint32_t)&buf[0];

    do
    {
        marker = buf[index++];
        marker = (marker << 8) | buf[index++];

        switch (marker)
        {
        case JFIF_MKR_SOI:
            break;

        case JFIF_MKR_APP0:
        case JFIF_MKR_APP1:
        case JFIF_MKR_APP2:
        case JFIF_MKR_APP3:
        case JFIF_MKR_APP4:
        case JFIF_MKR_APP5:
        case JFIF_MKR_APP6:
        case JFIF_MKR_APP7:
        case JFIF_MKR_APP8:
        case JFIF_MKR_APP9:
        case JFIF_MKR_APPa:
        case JFIF_MKR_APPb:
        case JFIF_MKR_APPc:
        case JFIF_MKR_APPd:
        case JFIF_MKR_APPe:
        case JFIF_MKR_APPf:

            index += (buf[index] << 8) | buf[index + 1];
            break;

        case JFIF_MKR_DQT:
            if (start_dqt)
            {
                start_dqt = 0;
                jfif_info->start_byte = (index - 2) / 16 * 16;
                jfif_info->start_bit = ((index - 2) % 16) * 8;
            }

            blklen = (buf[index] << 8) | buf[index + 1];
            index += 2;
            blklen -= 2;
            while (blklen)
            {
                uint8_t idx = buf[index] & 0x0F;
                uint8_t fmt = buf[index] >> 4;
                jfif_info->sample_depth = fmt;
                if (fmt != 0)
                {
                    printf("DQT precision 16,no support\r\n");
                    return JFIF_NO_SUPPORT;
                }

                if (idx >= JFIF_QTAB_MAX)
                {
                    printf("DQT amount > 3,no support\r\n");
                    return JFIF_NO_SUPPORT;
                }

                jfif_info->qtablecnt++;

                index += 65;
                blklen -= 65;
            }
            break;

        case JFIF_MKR_SOF0:
//            printf("JFIF_MKR_SOF0\r\n");
            //如果是SOF在前面，记录SOF起始位置；并且不再记录DQT位置
            if (start_dqt)
            {
                start_dqt = 0;
                jfif_info->start_byte = (index - 2) / 16 * 16;
                jfif_info->start_bit = ((index - 2) % 16) * 8;
//                printf("JFIF_MKR_DQT start_byte = %d,start_bit = %d\r\n", jfif_info->start_byte, jfif_info->start_bit);
            }

            if (buf[index + 2] != 8)
            {
                printf("SOF0 precision = %X,no support\r\n", buf[index + 2]);
                return JFIF_NO_SUPPORT;
            }

            jfif_info->height = (buf[index + 3] << 8) | buf[index + 4];
            jfif_info->width = (buf[index + 5] << 8) | buf[index + 6];

            jfif_info->compcnt = buf[index + 7];
            //printf("SOF0 Width = %d,Height = %d,ComCnt = %d\r\n", jfif_info->width, jfif_info->height, jfif_info->compcnt);

            index += 8;
            for (i = 0; i < jfif_info->compcnt; i++)
            {
                jfif_info->compinfo[i].id = buf[index];
                jfif_info->compinfo[i].hfactor = buf[index + 1] >> 4;
                jfif_info->compinfo[i].vfactor = buf[index + 1] & 0x0F;
                jfif_info->compinfo[i].qtab_id = buf[index + 2];
                index += 3;
            }
            end_flg = 0;
            break;

        case JFIF_MKR_DHT:
            blklen = (buf[index] << 8) | buf[index + 1];
            index += blklen;
            break;

        case JFIF_MKR_SOS:
            return JFIF_RES_OK;
        case JFIF_MKR_DRI:
        case JFIF_MKR_COM:
            index += (buf[index] << 8) | buf[index + 1];
            break;
        case JFIF_MKR_EOI:
            end_flg = 0;
            break;
        default:
            return JFIF_FORMAT_ERR;
        }
    } while (end_flg);

    if (end_flg)
        return JFIF_FORMAT_ERR;
    else
        return JFIF_RES_OK;
}
/**
 * @brief 初始化JPEG配置
 *
 * @param irq_en 是否使用中断
 */
void hal_jpeg_init(uint8_t irq_en)
{
    drv_png_close_jpeg_axi();
    drv_imagedecoder_gate_enable();
    if (irq_en)
    {
        NVIC_Init(3, 3, IMAGE_DECODER_IRQ, 2);
        IMGAGE_DECODER_IRQHandler_Callback = hal_image_irq_handler;
    }
    else
    {
        NVIC_Clear(IMAGE_DECODER_IRQ);
    }
    return;
}
/**
 * @brief 配置解码器解码JPEG图片
 *
 * @param jfif_info JPEG图片信息
 * @param jpeg_outset 输出JPEG图片配置
 */
void hal_jpeg_decode_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset)
{
    drv_jpeg_init(jfif_info, jpeg_outset);
}
/**
 * @brief 初始化PNG配置
 *
 * @param irq_en 是否使用中断
 */
void hal_png_init(uint8_t irq_en)
{
    drv_png_close_jpeg_axi();
    drv_enable_png_sram();
    drv_imagedecoder_gate_enable();
    if (irq_en)
    {
        NVIC_Init(3, 3, IMAGE_DECODER_IRQ, 2);
        IMGAGE_DECODER_IRQHandler_Callback = hal_image_irq_handler;
    }
    else
    {
        NVIC_Clear(IMAGE_DECODER_IRQ);
    }
}
/**
 * @brief 配置解码器解码PNG图片
 *
 * @param m_parsed_info
 * @param m_param_cfg
 * @return png_config_err_t 配置结果
 */
png_config_err_t hal_png_decode_set(png_parse_info_t m_parsed_info, png_param_cfg_t m_param_cfg)
{
    return drv_png_init(m_parsed_info, m_param_cfg);
}
/**
 * @brief 启动解码器
 *
 */
void hal_imagedecoder_start(void)
{
    drv_imagedecoder_start();
}
/**
 * @brief 获取解码器状态
 *
 * @return status_t 解码器状态
 */
status_t hal_get_imagedecoder_status(void)
{
    switch (drv_get_imagedecoder_status())
    {
    case IMAGEDECODER_OK:
        return STATUS_OK;
        break;
    case IMAGEDECODER_BUSY:
        return STATUS_BUSY;
        break;
    case IMAGEDECODER_ERROR:
        return STATUS_ERROR;
        break;
    default:
        break;
    }

    return STATUS_BUSY;
}
/**
 * @brief 清除解码器状态
 *
 * @return status_t 清除结果
 */
status_t hal_imagedecoder_clr_status()
{
    uint32_t timeout = 0xffff;
    return drv_imagedecoder_clr_status(timeout);
}
/**
 * @brief 解码器中断处理函数
 *
 */
void hal_image_irq_handler(void)
{
    if (hal_get_imagedecoder_status() == STATUS_OK)
        hal_imagedecoder_clr_status();
    if (g_image_decoder_init->image_decoder_irq_cb)
        g_image_decoder_init->image_decoder_irq_cb();
}
/**
 * @brief 配置JPEG加速器
 *
 * @param jfif_info JPEG图片信息
 * @param jpeg_outset 输出JPEG图片配置
 */
void hal_jpeg_accelerate_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset)
{
    drv_enbale_jpeg_sram();
    drv_jpeg_accelerate_set(jfif_info, jpeg_outset);
}
/**
 * @brief 启动JPEG加速器
 *
 */
void hal_jpeg_accelerate_start(void)
{
    // 此处必须进行中断使能，注意使能的是jpeg的加速中断，打开的nvic对应的为jpeg加速中断;
    NVIC_Init(3, 3, JPEG_ACCELERATOR_IRQn, 2);
    hal_imagedecoder_start();
}
/**
 * @brief 复位JPEG加速器
 *
 */
void hal_jpeg_accelerate_reset(void)
{
    drv_jpeg_axi_reset();
}
