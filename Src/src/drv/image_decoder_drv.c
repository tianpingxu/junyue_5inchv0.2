/**
 * @file image_decoder_drv.c
 * @author Product Application Department
 * @brief  IMGDECODE 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
// 头文件包含
#include "image_decoder_drv.h"

// 函数定义

/**
 * @brief 打开32K SRAM使用权限，以便JPEG加速器使用
 *
 */
void drv_enbale_jpeg_sram(void)
{
    JPEG_SRAM_CONFIG &= ~JPEG_SRAM_EN;
}
/**
 * @brief 关闭32K SRAM使用权限，以PNG解码器使用
 *
 */
void drv_enable_png_sram(void)
{
    JPEG_SRAM_CONFIG |= PNG_SRAM_EN;
}
/**
 * @brief JPEG加速器复位
 *
 */
void drv_jpeg_axi_reset(void)
{
    CPM_JPEG_AXI_RST |= JPEG_AXI_RST;
    CPM_JPEG_AXI_RST &= ~JPEG_AXI_RST;
}
/**
 * @brief 关闭JPEG加速器使能
 *
 */
void drv_png_close_jpeg_axi(void)
{
    JPEG_PIC_CONFIG &= ~JPEG_AXI_EN;
}
/**
 * @brief 打开IMGADECODER门控
 *
 */
void drv_imagedecoder_gate_enable(void)
{
    IMAGE_DECODER->SWREG1_INTR.R = 0;
    IMAGE_DECODER->SWREG2_DEVICE_CONF.B.DEC_CLK_GATE_E = ENABLE;
    IMAGE_DECODER->SWREG2_DEVICE_CONF.B.DEC_MEM_CLK_GATE_E = ENABLE;
}
/**
 * @brief 初始化jpeg解码器
 *
 * @param jfif_info
 * @param jpeg_outset
 */
void drv_jpeg_init(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset)
{
    uint8_t hxvx, ppin;
    uint16_t pp_stride;
    int i;
    // SWREG 3
    /*
    jpeg mode
    */
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.DEC_MODE = DECODE_JPEG;
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.PJPEG_E = BASELINE_MODE;
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.JPEG_12BIT_E = jfif_info->sample_depth;
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.DEC_OUT_DIS = OUTPUT_RAM_DISABLE;
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.FILTERING_DIS = ENABLE;
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.B.BUFFER_EMPTY_INT_E = ENABLE;
    // TODO: bit3

    // SWREG 4
    IMAGE_DECODER->SWREG4_DECODER_CTRL1.R = 0;
    if (jfif_info->width % 8 == 0)
    {
        IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_WIDTH_IN_CBS = (jfif_info->width) / 8;
    }
    else
    {
        IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_WIDTH_IN_CBS = (jfif_info->width) / 8 + 1;
    }

    if (jfif_info->height % 8 == 0)
    {
        IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_HEIGHT_IN_CBS = (jfif_info->height) / 8;
    }
    else
    {
        IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_HEIGHT_IN_CBS = (jfif_info->height) / 8 + 1;
    }

    if (jpeg_outset->crop_enable)
    {
        jfif_info->width = jpeg_outset->crop_width;
        jfif_info->height = jpeg_outset->crop_height;
    }

    // SWREG 5
    /*
    exact bit of start address word具体指图片首地址
    指除去从首地址开始16Byte之外，剩下的数据到第一个DQT（FFDB）剩下的bit数量
    */
    switch ((jfif_info->compinfo[0].hfactor << 4) | jfif_info->compinfo[0].vfactor)
    {
    case 0x11:
        if (jfif_info->compcnt == 1)
            hxvx = PIC_SAMPLE_YUV400;
        else if (jfif_info->compcnt == 3)
            hxvx = PIC_SAMPLE_YUV444;
        break;
    case 0x21:
        hxvx = PIC_SAMPLE_YUV422;
        break;
    case 0x22:
        hxvx = PIC_SAMPLE_YUV420;
        break;
    case 0x41:
        hxvx = PIC_SAMPLE_YUV411;
        break;
    case 0x12:
        hxvx = PIC_SAMPLE_YUV440;
        break;
    default:
        return;
    }

    ppin = PP_INPUT_YUV420_1; // SWREG353

    IMAGE_DECODER->SWREG5_DECODER_CTRL2.B.STRM_START_BIT = jfif_info->start_bit;
    IMAGE_DECODER->SWREG5_DECODER_CTRL2.B.JPEG_QTABLES = jfif_info->compcnt;
    IMAGE_DECODER->SWREG5_DECODER_CTRL2.B.JPEG_MODE = hxvx;
    IMAGE_DECODER->SWREG5_DECODER_CTRL2.B.JPEG_STREAM_ALL = EOI_IN;

    // SWREG 6
    /*
    总长度减去16对齐的倍数
    */
    IMAGE_DECODER->SWREG6_DECODER_CTRL3.B.STREAM_LEN = jfif_info->jpeg_len - jfif_info->start_byte;

    // SWREG 8
    /*RESET PNG STATUS*/
    IMAGE_DECODER->SWREG8_DECODER_CTRL5.R = 0;

    // SWREG 12
    /*
    qtable selection
    */
    IMAGE_DECODER->SWREG12_DECODER_CTRL.B.PJPEG_QTABLE_SEL0 = jfif_info->compinfo[0].qtab_id;
    IMAGE_DECODER->SWREG12_DECODER_CTRL.B.PJPEG_QTABLE_SEL1 = jfif_info->compinfo[1].qtab_id;
    IMAGE_DECODER->SWREG12_DECODER_CTRL.B.PJPEG_QTABLE_SEL2 = jfif_info->compinfo[2].qtab_id;
    IMAGE_DECODER->SWREG12_DECODER_CTRL.B.SYNC_MARKER_E = DISABLE;

    // SWREG 58
    /*
    按照log文件，
    b8-10, decoder master interface width 0-32bit,1-64bit,2-128bit(64)
    b0-7,max burst length(32)
    */
    IMAGE_DECODER->SWREG58_DEVICE_CONF2.R = 0X00000110;

    // SWREG 60
    /*
    AXI WR ID 16-31
    AXI RD ID 0-15
    */
    IMAGE_DECODER->SWREG60_DECODER_AXI_ID_BASE.R = 0X00000000;

    // SWREG 65-67-69
    /*
    decoded address
    65-y
    67-u
    69-v
    不需要配置
    */

    // SWREG 133
    /*
    mvs direct mode
    */
    IMAGE_DECODER->SWREG133_BASE_DIRECT_MVS.R = 0X00000000;

    // SWREG 169
    /*
    stream start address
    原始数据推移16对齐倍数Byte（实际上是通过偏移byte和bit推移到DQT开始的位置）
    */

    IMAGE_DECODER->SWREG169_BASE_STREAM.R = jfif_info->jpeg_addr + jfif_info->start_byte;
    // SWREG 175
    /*
    base addr for AC,DC/Q table
    目前版本hw不使用sw解析的table地址，所以此寄存器不需要关注配置
    */

    // SWREG 258
    /*
    input stream length ==swreg6
    同SWREG6
    */
    IMAGE_DECODER->SWREG258_INPUT_BUFF_LEN.R = jfif_info->jpeg_len - jfif_info->start_byte;

    // SWREG 265
    /*
    AXI MAX THRESHOLD READ  新版本改为0x80 ->0x02004000
    AXI MAX THRESHOLD WIRTE 0X40
    Qos WR 0
    Qos RD 0
    */
    IMAGE_DECODER->SWREG265_AXI4_MISC_CONF.R = 0X02004000;

    // SWREG 318
    /*
    external Timeout enable & value
    */
    IMAGE_DECODER->SWREG318_EXT_TIMEOUT_CTRL.B.EXT_TIMEOUT_OVERRIDE_E = ENABLE;
    IMAGE_DECODER->SWREG318_EXT_TIMEOUT_CTRL.B.EXT_TIMEOUT_CYCLES = 0X05FFFFFF;

    // SWREG 319
    /*
    Timeout enable & value
    */
    IMAGE_DECODER->SWREG319_TIMEOUT_CTRL.B.TIMEOUT_OVERRIDE_E = ENABLE;
    IMAGE_DECODER->SWREG319_TIMEOUT_CTRL.B.TIMEOUT_CYCLES = 0X05FFFFFF;

    // SWREG 353
    /*
    PP input setting
    format YUV420 Linear 不生效，pp输入只和swreg5有关
    enable pp
    */
    IMAGE_DECODER->SWREG353_DEVICE_CONF_POST.B.PP_IN_FORMAT = ppin;
    IMAGE_DECODER->SWREG353_DEVICE_CONF_POST.B.PP_OUT_E = ENABLE;

    // SWREG 354
    /*
    bit 1 无说明
    */
    if (jpeg_outset->output_rgb)
    {
        if ((jpeg_outset->format == PP_OUTPUT_RGB565) || (jpeg_outset->format == PP_OUTPUT_BGR565) || (jpeg_outset->format == PP_OUTPUT_BGRA888) || (jpeg_outset->format == PP_OUTPUT_RGBA888))
            IMAGE_DECODER->SWREG354_RANGE_MAPPING_CTRL.R = 0X20000000;
        else if ((jpeg_outset->format == PP_OUTPUT_RGB888) || (jpeg_outset->format == PP_OUTPUT_BGR888))
            IMAGE_DECODER->SWREG354_RANGE_MAPPING_CTRL.R = 0X00000002;
        else if ((jpeg_outset->format == PP_OUTPUT_ABGR888) || (jpeg_outset->format == PP_OUTPUT_ARGB888))
            IMAGE_DECODER->SWREG354_RANGE_MAPPING_CTRL.R = 0X20000001;
    }
    else
    {
        IMAGE_DECODER->SWREG354_RANGE_MAPPING_CTRL.R = 0X00000000;
    }

    // SWREG 384
    /*
    PP output setting
    RGB/RGB888
    */
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_SWAP = DISABLE;
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_SHAPER_DIS = ENABLE;
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_COMP_E = DISABLE;

    if (jpeg_outset->output_rgb)
    {
        IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_FORMAT = PP_OUTPUT_RGB;
        IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_RGB_FMT = jpeg_outset->format;
    }
    else
    {
        IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_FORMAT = jpeg_outset->format;
    }
    // SWREG 386
    /*
    PP output Y addr / RGB ADDR
    */

    if (jpeg_outset->output_rgb)
    {
        IMAGE_DECODER->SWREG386_PP_OUT_LU_BASE.R = jpeg_outset->rgb_addr;
    }
    else
    {
        IMAGE_DECODER->SWREG386_PP_OUT_LU_BASE.R = jpeg_outset->y_addr;
    }

    // SWREG 388
    /*
    PP output CbCr addr
    */
    IMAGE_DECODER->SWREG388_PP_OUT_CH_BASE.R = jpeg_outset->u_addr;

    // SWREG 390
    /*
    YUV444 Cr输出
    */
    IMAGE_DECODER->SWREG390_PP_OUT_B_BASE.R = jpeg_outset->v_addr;
    // SWREG 391
    /*
    PP output stride，行对齐；
    */

    if (jpeg_outset->output_rgb)
    {
        if ((jpeg_outset->format == PP_OUTPUT_RGB565) || (jpeg_outset->format == PP_OUTPUT_BGR565))
            pp_stride = jfif_info->width * 2;
        else if ((jpeg_outset->format == PP_OUTPUT_RGB888) || (jpeg_outset->format == PP_OUTPUT_BGR888))
            pp_stride = jfif_info->width * 3;
        else if ((jpeg_outset->format == PP_OUTPUT_ABGR888) || (jpeg_outset->format == PP_OUTPUT_ARGB888) || (jpeg_outset->format == PP_OUTPUT_BGRA888) || (jpeg_outset->format == PP_OUTPUT_RGBA888))
            pp_stride = jfif_info->width * 4;
    }
    else
    {
        pp_stride = jfif_info->width;
    }

    IMAGE_DECODER->SWREG391_PP_OUT_STRIDE.B.PPX_OUT_C_STRIDE = pp_stride;
    IMAGE_DECODER->SWREG391_PP_OUT_STRIDE.B.PPX_OUT_Y_STRIDE = pp_stride;
    // SWREG 393
    /*
    PP crop input size
    */
    if (jpeg_outset->crop_enable)
    {
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_HEIGHT = jpeg_outset->crop_height;
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_WIDTH = jpeg_outset->crop_width;
    }
    else
    {
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_HEIGHT = jfif_info->height;
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_WIDTH = jfif_info->width;
    }

    // SWREG 394
    /*
    Dither enable（RGB565）, alpha值写入;
    1)对于原始数据就没有A分量的图片，这里的配置才有效；
    2)dither对于原始数据类似于RGB888转为RGB565向下转换会生效；
    */

    IMAGE_DECODER->SWREG394_PP_OUT_ALPHA.B.PPX_DITHER = ENABLE;
    IMAGE_DECODER->SWREG394_PP_OUT_ALPHA.B.PPX_OUT_ALPHA = jpeg_outset->output_alpha;

    // SWREG395
    /*
    PP output scale size
    */
    if (jpeg_outset->crop_enable)
    {
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_HEIGHT = jpeg_outset->crop_height;
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_WIDTH = jpeg_outset->crop_width;
    }
    else
    {
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_HEIGHT = jfif_info->height;
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_WIDTH = jfif_info->width;
    }
}
/**
 * @brief 初始化png解码器
 *
 * @param m_parsed_info
 * @param m_param_cfg
 * @return png_config_err_t 初始化png解码器的错误码
 */
png_config_err_t drv_png_init(png_parse_info_t m_parsed_info, png_param_cfg_t m_param_cfg)
{
    if (m_param_cfg.out_channel_num == 0)
        return PNG_CONFIG_CHN_NUM_ERR;
    // decoder mdoe:PNG, buffer empty int enable, disable to write external memory
    IMAGE_DECODER->SWREG3_DECODER_CTRL0.R = 0xA800C00C;

    // picture height/width in min coded blocks, size/8; size%8 is set in SWREG9
    IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_HEIGHT_IN_CBS = (m_parsed_info.ihdr_info.height >> 3);
    IMAGE_DECODER->SWREG4_DECODER_CTRL1.B.PIC_WIDTH_IN_CBS = (m_parsed_info.ihdr_info.width >> 3);

    // Exact bit of stream start word
    IMAGE_DECODER->SWREG5_DECODER_CTRL2.B.STRM_START_BIT = m_parsed_info.idat_info.idat_stream_offset;

    // Amount of stream data bytes in input buffer
    IMAGE_DECODER->SWREG6_DECODER_CTRL3.R = ((uint32_t)(m_parsed_info.idat_info.idat_total_len));

    // bit depth and colorType, bit depth fix to 8 if color_type is not INDEXD_COLOR
    if (m_parsed_info.ihdr_info.color_type == IHDR_COLOR_INDEXD_COLOR)
        IMAGE_DECODER->SWREG8_DECODER_CTRL5.B.BIT_DEPTH_INDEX_LOG2 = ((m_parsed_info.ihdr_info.bit_depth >> 3) == 0) ? (m_parsed_info.ihdr_info.bit_depth >> 1) : (3);
    else
        IMAGE_DECODER->SWREG8_DECODER_CTRL5.B.BIT_DEPTH_INDEX_LOG2 = 0;
    IMAGE_DECODER->SWREG8_DECODER_CTRL5.B.DEC_COLOR_TYPE = m_parsed_info.ihdr_info.color_type;

    // if size%8, off pixels is set in SWREG9
    IMAGE_DECODER->SWREG9_DECODER_CTRL6.B.MB_HEIGHT_OFF = (m_parsed_info.ihdr_info.height & 0x7);
    IMAGE_DECODER->SWREG9_DECODER_CTRL6.B.MB_WIDTH_OFF = (m_parsed_info.ihdr_info.width & 0x7);

    // SWREG 12
    /*RESET JPEG STATUS*/
    IMAGE_DECODER->SWREG12_DECODER_CTRL.R = 0;

    // Bus width=1(64bit), max burst length=256
    IMAGE_DECODER->SWREG58_DEVICE_CONF2.R = 0x110;

    // Base Address for decoded luminance picture
    IMAGE_DECODER->SWREG65_BASE_DEC_LUM.R = m_parsed_info.idat_info.idat_start_addr;

    // Base address for reference luminance picture index 0
    IMAGE_DECODER->SWREG67_BASE_REF_LUM.R = m_parsed_info.idat_info.idat_start_addr;

    // PLTE CHUNK config
    if (m_parsed_info.plte_info.is_chunkExist)
    {
        if ((m_param_cfg.plte_copy_addr == 0) || (m_param_cfg.plte_copy_addr & 0x7))
        {
            return PNG_CONFIG_PLTE_ADDR_ERR;
        }

        IMAGE_DECODER->SWREG133_BASE_DIRECT_MVS.R = m_param_cfg.plte_copy_addr;
    }
    else
        IMAGE_DECODER->SWREG133_BASE_DIRECT_MVS.R = 0x0;

    // InputStream addr config
    IMAGE_DECODER->SWREG169_BASE_STREAM.R = m_parsed_info.idat_info.idat_start_addr;

    // InputStream length config
    IMAGE_DECODER->SWREG258_INPUT_BUFF_LEN.R = ((uint32_t)(m_parsed_info.idat_info.idat_total_len));

    // InputStream buffer offset
    IMAGE_DECODER->SWREG259_INPUT_BUFF_OFFSET.R = 0x0;

    // AXI4 miscellaneous configuration, fixed
    IMAGE_DECODER->SWREG265_AXI4_MISC_CONF.R = 0x02004000;

    // Decoder output stride unit, in unit of 8bytes. recon buffer output stride, not used.
    IMAGE_DECODER->SWREG314_DECODER_OUT_STRIDE.R = 0x0;

    // Timeout cycles config
    // IMAGE_DECODER->SWREG318_EXT_TIMEOUT_CTRL.R = 0x85000000;
    // IMAGE_DECODER->SWREG319_TIMEOUT_CTRL.R = 0x85000000;
    IMAGE_DECODER->SWREG318_EXT_TIMEOUT_CTRL.R = 0xffffffff;
    IMAGE_DECODER->SWREG319_TIMEOUT_CTRL.R = 0xffffffff;

    // Input Format config. For PNG, YUV fixed Value 1
    IMAGE_DECODER->SWREG353_DEVICE_CONF_POST.R = 0x08000001;

    // YCbCr range config, only used for JPEG Decoder
    IMAGE_DECODER->SWREG354_RANGE_MAPPING_CTRL.R = 0x00000000;

    // PPx Configuration
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_FORMAT = m_param_cfg.out_format;
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_OUT_RGB_FMT = m_param_cfg.out_rgb_format;
    IMAGE_DECODER->SWREG384_PP_CONF.B.PPX_SHAPER_DIS = 1;

    // output base lu base addr
    IMAGE_DECODER->SWREG386_PP_OUT_LU_BASE.R = ((uint32_t)(m_param_cfg.out_base_addr));

    // output chroma base addr if nv12 / output u if yuv planner
    IMAGE_DECODER->SWREG388_PP_OUT_CH_BASE.R = ((uint32_t)(m_param_cfg.out_chroma_addr));

    // if yuv planar output, v output
    IMAGE_DECODER->SWREG390_PP_OUT_B_BASE.R = ((uint32_t)(m_param_cfg.out_v_addr));

    // ppX output stride
    IMAGE_DECODER->SWREG391_PP_OUT_STRIDE.B.PPX_OUT_C_STRIDE = m_param_cfg.out_width * m_param_cfg.out_channel_num;
    IMAGE_DECODER->SWREG391_PP_OUT_STRIDE.B.PPX_OUT_Y_STRIDE = m_param_cfg.out_width * m_param_cfg.out_channel_num;

    // ppX crop intput width/height
    if (m_param_cfg.crop_enable)
    {
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_HEIGHT = m_param_cfg.crop_height;
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_WIDTH = m_param_cfg.crop_width;
    }
    else
    {
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_HEIGHT = m_parsed_info.ihdr_info.height;
        IMAGE_DECODER->SWREG393_PP_CROP_INPUT.B.PPX_IN_WIDTH = m_parsed_info.ihdr_info.width;
    }

    // Alpha value
    IMAGE_DECODER->SWREG394_PP_OUT_ALPHA.B.PPX_DITHER = m_param_cfg.dither_en;
    IMAGE_DECODER->SWREG394_PP_OUT_ALPHA.B.PPX_OUT_ALPHA = m_param_cfg.out_alpha_val;
    IMAGE_DECODER->SWREG394_PP_OUT_ALPHA.R |= (0x101);

    // ppX output width/height
    if (m_param_cfg.crop_enable)
    {
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_HEIGHT = m_param_cfg.crop_height;
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_WIDTH = m_param_cfg.crop_width;
    }
    else
    {
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_HEIGHT = m_param_cfg.out_height;
        IMAGE_DECODER->SWREG395_PP_OUT_SCALE.B.PPX_OUT_WIDTH = m_param_cfg.out_width;
    }

    return PNG_CONFIG_SUCCESS;
}
/**
 * @brief 启动解码器
 *
 */
void drv_imagedecoder_start(void)
{
    IMAGE_DECODER->SWREG1_INTR.B.DEC_E = ENABLE;
}
/**
 * @brief 获取解码器状态
 *
 * @return imagedecoder_status_t 解码器状态
 */
imagedecoder_status_t drv_get_imagedecoder_status(void)
{
    if (IMAGE_DECODER->SWREG1_INTR.B.DEC_ERROR_INT)
        return IMAGEDECODER_ERROR;

    if ((IMAGE_DECODER->SWREG1_INTR.B.DEC_RDY_INT) & (IMAGE_DECODER->SWREG1_INTR.B.DEC_IRQ))
    {
        return IMAGEDECODER_OK;
    }
    else
    {
        return IMAGEDECODER_BUSY;
    }
}
/**
 * @brief 清除解码器状态
 *
 * @param timeout 超时时间
 * @return status_t 清除状态
 */
status_t drv_imagedecoder_clr_status(uint32_t timeout)
{
    IMAGE_DECODER->SWREG1_INTR.R = 0;
    while (IMAGE_DECODER->SWREG1_INTR.R != 0)
    {
        if (timeout == 0)
            return STATUS_TIMEOUT;
        timeout--;
    }
    return STATUS_OK;
}
/**
 * @brief 配置JPEG加速器
 *
 * @param jfif_info
 * @param jpeg_outset
 */
void drv_jpeg_accelerate_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset)
{
    uint16_t pp_stride;
    uint8_t pp_data_width;
    if ((jpeg_outset->format == PP_OUTPUT_RGB565) || (jpeg_outset->format == PP_OUTPUT_BGR565))
        pp_data_width = 2;
    else if ((jpeg_outset->format == PP_OUTPUT_RGB888) || (jpeg_outset->format == PP_OUTPUT_BGR888))
        pp_data_width = 3;
    else if ((jpeg_outset->format == PP_OUTPUT_ABGR888) || (jpeg_outset->format == PP_OUTPUT_ARGB888) || (jpeg_outset->format == PP_OUTPUT_BGRA888) || (jpeg_outset->format == PP_OUTPUT_RGBA888))
        pp_data_width = 4;

    pp_stride = jfif_info->width * pp_data_width;

    JPEG_PIC_INFO = IMAGE_DECODER->SWREG393_PP_CROP_INPUT.R;
    JPEG_PIC_CONFIG = (JPEG_PIC_CONFIG & 0X00000000) | (pp_stride << 16) | ((pp_data_width * 2) << 12) | JPEG_ACCELERATE_INTR_DONE | JPEG_ACCELERATE_INTR_FIFOSWITCH | JPEG_ACCELERATE_SRAM_EN;
}
