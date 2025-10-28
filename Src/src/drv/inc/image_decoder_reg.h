/**
 * @file image_decoder_reg.h
 * @author Product Application Department
 * @brief  IMGDECODE 模块寄存器配置文件
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IMAGE_DECODER_REG_H
#define __IMAGE_DECODER_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define IMAGE_DECODER_BASE_ADDR (0x40090000 + 0x800)
#define IMAGE_DECODER ((reg_decoder_t *)IMAGE_DECODER_BASE_ADDR)

// Register Micro Define
#define SWREG0_ID_R (IMAGE_DECODER_BASE_ADDR + 0x00)
#define SWREG1_INTR_R (IMAGE_DECODER_BASE_ADDR + 0x04)
#define SWREG2_DEVICE_CONF_R (IMAGE_DECODER_BASE_ADDR + 0x08)
#define SWREG3_DECODER_CTRL0_R (IMAGE_DECODER_BASE_ADDR + 0x0c)
#define SWREG4_DECODER_CTRL1_R (IMAGE_DECODER_BASE_ADDR + 0x10)
#define SWREG4_DECODER_CTRL2_R (IMAGE_DECODER_BASE_ADDR + 0x14)
#define SWREG4_DECODER_CTRL3_R (IMAGE_DECODER_BASE_ADDR + 0x18)
#define SWREG7_DECODER_CTRL4_R (IMAGE_DECODER_BASE_ADDR + 0x1c)
#define SWREG7_DECODER_CTRL5_R (IMAGE_DECODER_BASE_ADDR + 0x20)
#define SWREG7_DECODER_CTRL6_R (IMAGE_DECODER_BASE_ADDR + 0x24)
#define SWREG12_DECODER_CTRL_R (IMAGE_DECODER_BASE_ADDR + 0x30)
#define SWREG50_SYNTHESIS_CONFIG0_R (IMAGE_DECODER_BASE_ADDR + 0xc8)
#define SWREG54_SYNTHESIS_CONFIG1_R (IMAGE_DECODER_BASE_ADDR + 0xd8)
#define SWREG57_DECODER_FUSE_R (IMAGE_DECODER_BASE_ADDR + 0xe4)
#define SWREG2_DEVICE_CONF2_R (IMAGE_DECODER_BASE_ADDR + 0xe8)
#define SWREG60_DECODER_AXI_ID_BASE_R (IMAGE_DECODER_BASE_ADDR + 0xf0)
#define SWREG62_HW_PROCEED_R (IMAGE_DECODER_BASE_ADDR + 0xf8)
#define SWREG63_HW_PERFORMANCE_R (IMAGE_DECODER_BASE_ADDR + 0xfc)
#define SWREG65_BASE_DEC_LUM_R (IMAGE_DECODER_BASE_ADDR + 0x104)
#define SWREG67_BASE_REF_LUM_R (IMAGE_DECODER_BASE_ADDR + 0x10c)
#define SWREG133_BASE_DIRECT_MVS_R (IMAGE_DECODER_BASE_ADDR + 0x214)
#define SWREG169_BASE_STREAM_R (IMAGE_DECODER_BASE_ADDR + 0x2a4)
#define SWREG175_BASE_QTABLE_R (IMAGE_DECODER_BASE_ADDR + 0x2bc)
#define SWREG258_INPUT_BUFF_LEN_R (IMAGE_DECODER_BASE_ADDR + 0x408)
#define SWREG259_INPUT_BUFF_OFFSET_R (IMAGE_DECODER_BASE_ADDR + 0x40c)
#define SWREG260_SYNTHESIS_CONFIG3_R (IMAGE_DECODER_BASE_ADDR + 0x410)
#define SWREG265_AXI4_MISC_CONF_R (IMAGE_DECODER_BASE_ADDR + 0x424)
#define SWREG297_ABNORMAL_INTR_MSK_R (IMAGE_DECODER_BASE_ADDR + 0x4a4)
#define SWREG300_AXI_DEBUG0_R (IMAGE_DECODER_BASE_ADDR + 0x4b0)
#define SWREG301_AXI_DEBUG1_R (IMAGE_DECODER_BASE_ADDR + 0x4b4)
#define SWREG302_AXI_DEBUG2_R (IMAGE_DECODER_BASE_ADDR + 0x4b8)
#define SWREG303_AXI_DEBUG3_R (IMAGE_DECODER_BASE_ADDR + 0x4bc)
#define SWREG304_AXI_DEBUG4_R (IMAGE_DECODER_BASE_ADDR + 0x4c0)
#define SWREG305_AXI_DEBUG5_R (IMAGE_DECODER_BASE_ADDR + 0x4c4)
#define SWREG306_AXI_DEBUG6_R (IMAGE_DECODER_BASE_ADDR + 0x4c8)
#define SWREG307_AXI_DEBUG7_R (IMAGE_DECODER_BASE_ADDR + 0x4cc)
#define SWREG308_AXI_DEBUG8_R (IMAGE_DECODER_BASE_ADDR + 0x4d0)
#define SWREG309_DECODER_BUILD_VER_R (IMAGE_DECODER_BASE_ADDR + 0x4d4)
#define SWREG310_SYNTHESIS_CONFIG4_R (IMAGE_DECODER_BASE_ADDR + 0x4d8)
#define SWREG314_DECODER_OUT_STRIDE_R (IMAGE_DECODER_BASE_ADDR + 0x4e8)
#define SWREG318_EXT_TIMEOUT_CTRL_R (IMAGE_DECODER_BASE_ADDR + 0x4f8)
#define SWREG319_TIMEOUT_CTRL_R (IMAGE_DECODER_BASE_ADDR + 0x4fc)
#define SWREG327_UNIQUE_ID_R (IMAGE_DECODER_BASE_ADDR + 0x51c)
#define SWREG353_DEVICE_CONF_POST_R (IMAGE_DECODER_BASE_ADDR + 0x584)
#define SWREG354_RANGE_MAPPING_CTRL_R (IMAGE_DECODER_BASE_ADDR + 0x588)
#define SWREG384_PP_CONF_R (IMAGE_DECODER_BASE_ADDR + 0x600)
#define SWREG386_PP_OUT_LU_BASE_R (IMAGE_DECODER_BASE_ADDR + 0x608)
#define SWREG388_PP_OUT_CH_BASE_R (IMAGE_DECODER_BASE_ADDR + 0x610)
#define SWREG390_PP_OUT_B_BASE_R (IMAGE_DECODER_BASE_ADDR + 0x618)
#define SWREG391_PP_OUT_STRIDE_R (IMAGE_DECODER_BASE_ADDR + 0x61c)
#define SWREG393_PP_CROP_INPUT_R (IMAGE_DECODER_BASE_ADDR + 0x624)
#define SWREG394_PP_OUT_ALPHA_R (IMAGE_DECODER_BASE_ADDR + 0x628)
#define SWREG395_PP_OUT_SCALE_R (IMAGE_DECODER_BASE_ADDR + 0x62c)

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t ASIC_ID;
    } B;
} swreg0_id_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_E : 1;               // 0, decode enable
        uint32_t : 1;                     // 1, rsv
        uint32_t DEC_BUS_INT_DIS : 1;     // 2,
        uint32_t DEC_TIMEOUT_SOURCE : 1;  // 3,
        uint32_t DEC_IRQ_DIS : 1;         // 4,
        uint32_t DEC_ABORT_E : 1;         // 5,
        uint32_t DEC_SELF_RESET_DIS : 1;  // 6,
        uint32_t : 1;                     // 7, rsv
        uint32_t DEC_IRQ : 1;             // 8,
        uint32_t : 2;                     // 9:10, rsv
        uint32_t DEC_ABORT_INT : 1;       // 11,
        uint32_t DEC_RDY_INT : 1;         // 12,
        uint32_t DEC_BUS_INT : 1;         // 13,
        uint32_t DEC_BUFFER_INT : 1;      // 14,
        uint32_t : 1;                     // 15, rsv
        uint32_t DEC_ERROR_INT : 1;       // 16,
        uint32_t : 1;                     // 17, rsv
        uint32_t DEC_TIMEOUT : 1;         // 18,
        uint32_t PNG_CRC_ERROR : 1;       // 19,
        uint32_t PNG_ADLER32_ERROR : 1;   // 20,
        uint32_t DEC_EXT_TIMEOUT_INT : 1; // 21,
        uint32_t : 10;                    // 22:31,
    } B;
} swreg1_intr_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 7;                    // 0:6, rsv
        uint32_t TILED_MODE_LSB : 1;     // 7,
        uint32_t : 2;                    // 8:9, rsv
        uint32_t DEC_CLK_GATE_E : 1;     // 10,
        uint32_t DEC_MEM_CLK_GATE_E : 1; // 11,
        uint32_t DEC_TAB_SWAP : 4;       // 12:15
        uint32_t : 4;                    // 16:19
        uint32_t DEC_DIRMV_SWAP : 4;     // 20:23
        uint32_t DEC_PIC_SWAP : 4;       // 24:27
        uint32_t DEC_STRM_SWAP : 4;      // 28:31
    } B;
} swreg2_device_config_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t LAST_BUFFER_E : 1;              // 0,
        uint32_t BLOCK_BUFFER_MODE_E : 1;        // 1,
        uint32_t BUFFER_EMPTY_INT_E : 1;         // 2,
        uint32_t : 4;                            // 3:6, rsv
        uint32_t STREAM_STATUS_EXT_BUFFER_E : 1; // 7,
        uint32_t : 6;                            // 8:13, rsv
        uint32_t FILTERING_DIS : 1;              // 14,
        uint32_t DEC_OUT_DIS : 1;                // 15,
        uint32_t : 3;                            // 16:18, rsv
        uint32_t JPEG_12BIT_E : 1;               // 19
        uint32_t : 3;                            // 20:22, rsv
        uint32_t PJPEG_LAST_SCAN_E : 1;          // 23,
        uint32_t PJPEG_E : 1;                    // 24,
        uint32_t PJPEG_WIDTH_DIV16 : 1;          // 25,
        uint32_t : 1;                            // 26, rsv
        uint32_t DEC_MODE : 5;                   // 27:31,
    } B;
} swreg3_decoder_ctrl0_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 6;                    // 0:5, rsv
        uint32_t PIC_HEIGHT_IN_CBS : 13; // 6:18
        uint32_t PIC_WIDTH_IN_CBS : 13;  // 19:31
    } B;
} swreg4_decoder_ctrl1_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 6;                 // 0:5, rsv
        uint32_t JPEG_STREAM_ALL : 1; // 6,
        uint32_t : 1;                 // 7, rsv
        uint32_t JPEG_MODE : 3;       // 8:10,
        uint32_t JPEG_QTABLES : 2;    // 11:12,
        uint32_t : 12;                // 13:24, rsv
        uint32_t STRM_START_BIT : 7;  // 25:31,
    } B;
} swreg5_decoder_ctrl2_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t STREAM_LEN;
    } B;
} swreg6_decoder_ctrl3_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PJPEG_SE : 8;        // 0:7,
        uint32_t PJPEG_SS : 8;        // 8:15,
        uint32_t : 4;                 // 16:19, rsv
        uint32_t PJPEG_AH : 4;        // 20:23,
        uint32_t : 2;                 // 24:25, rsv
        uint32_t PJPEG_FILDOWN_E : 1; // 26,
        uint32_t : 5;                 // 27:31, rsv
    } B;
} swreg7_decoder_ctrl4_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_COLOR_TYPE : 3;       // 0:2,
        uint32_t : 1;                      // 3, rsv
        uint32_t BIT_DEPTH_C_MINUS8 : 2;   // 4:5,
        uint32_t BIT_DEPTH_Y_MINUS8 : 2;   // 6:7,
        uint32_t BIT_DEPTH_INDEX_LOG2 : 2; // 8:9,
        uint32_t : 22;                     // 10:31, rsv,
    } B;
} swreg8_decoder_ctrl5_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 26;              // 0:25, rsv
        uint32_t MB_HEIGHT_OFF : 3; // 26:28,
        uint32_t MB_WIDTH_OFF : 3;  // 29:31,
    } B;
} swreg9_decoder_ctrl6_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 25;                  // 0:24, rsv
        uint32_t PJPEG_QTABLE_SEL2 : 2; // 25:26,
        uint32_t PJPEG_QTABLE_SEL1 : 2; // 27:28,
        uint32_t PJPEG_QTABLE_SEL0 : 2; // 29:30,
        uint32_t SYNC_MARKER_E : 1;     // 31,
    } B;
} swreg12_decoder_ctrl_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t REG50;
    } B;
} swreg50_synthesis_config0_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t REG54;
    } B;
} swreg54_synthesis_config1_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t REG57;
    } B;
} swreg57_decoder_fuse_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_MAX_BURST : 8; // 0:7,
        uint32_t DEC_BUS_WIDTH : 3; // 8:10,
        uint32_t : 21;              // 11:31, rsv
    } B;
} swreg58_device_config2_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_RD_ID : 16; // 0:15,
        uint32_t DEC_AXI_WR_ID : 16; // 16:31,
    } B;
} swreg60_decoder_axiid_base_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t MB_LOCATION_Y : 16; // 0:15,
        uint32_t MB_LOCATION_X : 16; // 16:31,
    } B;
} swreg62_hw_proceed_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PERF_CYCLE_COUNT;
    } B;
} swreg63_hw_performance_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_OUT_YBASE_LSB;
    } B;
} swreg65_base_dec_lum_u;
typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t JPG_CH_OUT_BASE_LSB;
    } B;
} swreg67_base_ref_lum_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DIR_MV_BASE_LSB;
    } B;
} swreg133_base_direct_mvs_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t STREAM_BASE_LSB;
    } B;
} swreg169_base_stream_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t QTABLE_BASE_LSB;
    } B;
} swreg175_base_qtable_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t STRM_BUFFER_LEN;
    } B;
} swreg258_input_buff_len_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t STRM_START_OFFSET;
    } B;
} swreg259_input_buff_offset_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t SWREG260;
    } B;
} swreg260_synthesis_config3_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t AXI_ARQOS : 4;              // 0:3,
        uint32_t AXI_AWQOS : 4;              // 4:7,
        uint32_t AXI_WR_OSTD_THRESHOLD : 10; // 8:17,
        uint32_t AXI_RD_OSTD_THRESHOLD : 10; // 18:27,
        uint32_t : 4;                        // 28:31, rsv
    } B;
} swreg265_axi4_misc_config_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 11;                       // 0:10, rsv
        uint32_t DEC_ABNORMAL_INT_MASK : 15; // 11:25,
        uint32_t : 6;
    } B;
} swreg297_abnormal_intr_msk_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_R_LEN_CNT;
    } B;
} swreg300_axi_debug0_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_R_DAT_CNT;
    } B;
} swreg301_axi_debug1_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_R_REQ_CNT;
    } B;
} swreg302_axi_debug2_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_RLAST_CNT;
    } B;
} swreg303_axi_debug3_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_W_LEN_CNT;
    } B;
} swreg304_axi_debug4_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_W_DAT_CNT;
    } B;
} swreg305_axi_debug5_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_W_REQ_CNT;
    } B;
} swreg306_axi_debug6_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_WLAST_CNT;
    } B;
} swreg307_axi_debug7_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_AXI_W_ACK;
    } B;
} swreg308_axi_debug8_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t SWREG309;
    } B;
} swreg309_decoder_build_ver_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t SWREG310;
    } B;
} swreg310_synthesis_config4_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t DEC_OUT_C_STRIDE : 16; // 0:15,
        uint32_t DEC_OUT_Y_STRIDE : 16; // 16:31,
    } B;
} swreg314_decoder_out_stride_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t EXT_TIMEOUT_CYCLES : 31;    // 0:30,
        uint32_t EXT_TIMEOUT_OVERRIDE_E : 1; // 31,
    } B;
} swreg318_ext_timeout_ctrl_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t TIMEOUT_CYCLES : 31;    // 0:30,
        uint32_t TIMEOUT_OVERRIDE_E : 1; // 31,
    } B;
} swreg319_timeout_ctrl_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t UNIQUE_ID : 16; // 0:15
        uint32_t : 16;           // 16:31
    } B;
} swreg327_unique_id_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PP_OUT_E : 1;     // 0,
        uint32_t : 26;             // 1:26,
        uint32_t PP_IN_FORMAT : 5; // 27:31,
    } B;
} swreg353_device_conf_post_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t COLOR_CONVERSION_TYPE : 2; // 0:1,
        uint32_t : 27;                      // 2:28,
        uint32_t YCBCR_RANGE : 1;           // 29,
        uint32_t : 2;                       // 30:31,
    } B;
} swreg354_range_mapping_ctrl_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PPX_RGB_PLANAR : 1;   // 0,
        uint32_t PPX_CR_FIRST : 1;     // 1,
        uint32_t PPX_SHAPER_PAD_E : 1; // 2,
        uint32_t PPX_OUT_TILE_E : 1;   // 3,
        uint32_t PPX_TILE_SIZE : 3;    // 4:6,
        uint32_t PPX_STRIDE_UNIT : 3;  // 7:9,
        uint32_t : 1;                  // 10,
        uint32_t PPX_OUT_P010_FMT : 2; // 11:12,
        uint32_t PPX_OUT_RGB_FMT : 5;  // 13:17,
        uint32_t PPX_OUT_FORMAT : 5;   // 18:22,
        uint32_t : 3;                  // 23:25
        uint32_t PPX_COMP_E : 1;       // 26,
        uint32_t PPX_SHAPER_DIS : 1;   // 27,
        uint32_t PPX_OUT_SWAP : 4;     // 28:31
    } B;
} swreg384_pp_conf_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PP_OUT_LU_BASE_LSB;
    } B;
} swreg386_pp_out_lu_base_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PP_OUT_CH_BASE_LSB;
    } B;
} swreg388_pp_out_ch_base_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PP_OUT_B_BASE_LSB;
    } B;
} swreg390_pp_out_b_base_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PPX_OUT_C_STRIDE : 16; // 0:15,
        uint32_t PPX_OUT_Y_STRIDE : 16; // 16:31,
    } B;
} swreg391_pp_out_stried_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PPX_IN_HEIGHT : 16; // 0:15,
        uint32_t PPX_IN_WIDTH : 16;  // 16:31,
    } B;
} swreg393_pp_crop_input_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t : 16;              // 0:15,
        uint32_t PPX_OUT_ALPHA : 8; // 16:23,
        uint32_t PPX_DITHER : 1;    // 24,
        uint32_t : 7;               // 25:31,
    } B;
} swreg394_pp_out_alpha_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t PPX_OUT_HEIGHT : 16; // 0:15,
        uint32_t PPX_OUT_WIDTH : 16;  // 16:31,
    } B;
} swreg395_pp_out_scale_u;
/**
 * @brief decoder寄存器定义
 *
 */
typedef volatile struct
{
    swreg0_id_u SWREG0_ID;                                     // offset 0x00, RO, ID register
    swreg1_intr_u SWREG1_INTR;                                 // offset 0x04, RW, Interrupt register
    swreg2_device_config_u SWREG2_DEVICE_CONF;                 // offset 0x08, RW, Device configuration register
    swreg3_decoder_ctrl0_u SWREG3_DECODER_CTRL0;               // offset 0x0c, RW, Decoder control register0
    swreg4_decoder_ctrl1_u SWREG4_DECODER_CTRL1;               // offset 0x10, RW, Decoder control register1
    swreg5_decoder_ctrl2_u SWREG5_DECODER_CTRL2;               // offset 0x14, RW, Decoder control register2
    swreg6_decoder_ctrl3_u SWREG6_DECODER_CTRL3;               // offset 0x18, RW, Decoder control register3
    swreg7_decoder_ctrl4_u SWREG7_DECODER_CTRL4;               // offset 0x1c, RW, Decoder control register4
    swreg8_decoder_ctrl5_u SWREG8_DECODER_CTRL5;               // offset 0x20, RW, Decoder control register5
    swreg9_decoder_ctrl6_u SWREG9_DECODER_CTRL6;               // offset 0x24, RW, Decoder control register6
    uint32_t RESERVED1[2];                                     // offset 0x28~0x2c, Reserved
    swreg12_decoder_ctrl_u SWREG12_DECODER_CTRL;               // offset 0x30, RW, Decoder control register6
    uint32_t RESERVED2[37];                                    // offset 0x34~0xc4, Reserved
    swreg50_synthesis_config0_u SWREG50_SYNTHESIS_CONFIG0;     // offset 0xc8, RO, Synthesis configuration register0
    uint32_t RESERVED3[3];                                     // offset 0xcc~0xd4, Reserved
    swreg54_synthesis_config1_u SWREG54_SYNTHESIS_CONFIG1;     // offset 0xd8, RO, Synthesis configuration register1
    uint32_t RESERVED4[2];                                     // offset 0xdc~0xe0, Reserved
    swreg57_decoder_fuse_u SWREG57_DECODER_FUSE;               // offset 0xe4, RO, Decoder fuse register
    swreg58_device_config2_u SWREG58_DEVICE_CONF2;             // offset 0xe8, RW, Device configuration register2 + Multi core control register
    uint32_t RESERVED5;                                        // offset 0xec, Reserved
    swreg60_decoder_axiid_base_u SWREG60_DECODER_AXI_ID_BASE;  // offset 0xf0, RW, Decoder axi id base register
    uint32_t RESERVED6;                                        // offset 0xf4, Reserved
    swreg62_hw_proceed_u SWREG62_HW_PROCEED;                   // offset 0xf8, RO, HW proceed register
    swreg63_hw_performance_u SWREG63_HW_PERFORMANCE;           // offset 0xfc, RO, HW performance register
    uint32_t RESERVED7;                                        // offset 0x100, Reserved
    swreg65_base_dec_lum_u SWREG65_BASE_DEC_LUM;               // offset 0x104, RW, Base address LSB (bits31:0) for decoded luminance picture
    uint32_t RESERVED8;                                        // offset 0x108, Reserved
    swreg67_base_ref_lum_u SWREG67_BASE_REF_LUM;               // offset 0x10c, RW, Base address LSB (bits31:0) for reference luminance picture
    uint32_t RESERVED9[65];                                    // offset 0x110~0x210, Reserved
    swreg133_base_direct_mvs_u SWREG133_BASE_DIRECT_MVS;       // offset 0x214, Base address LSB (bits31:0) for decoded direct mode MVS
    uint32_t RESERVED10[35];                                   // offset 0x218~0x2A0, Reserved
    swreg169_base_stream_u SWREG169_BASE_STREAM;               // offset 0x2a4, RW, Base address LSB (bits31:0) for stream start address/decoded end addr register
    uint32_t RESERVED11[5];                                    // offset 0x2a8~0x2b8, Reserved
    swreg175_base_qtable_u SWREG175_BASE_QTABLE;               // offset 0x2bc, RW, Base address LSB (bits31:0) for standard dependent tables
    uint32_t RESERVED12[82];                                   // offset 0x2c0~0x404, Reserved
    swreg258_input_buff_len_u SWREG258_INPUT_BUFF_LEN;         // offset 0x408, RW, Input stream buffer length
    swreg259_input_buff_offset_u SWREG259_INPUT_BUFF_OFFSET;   // offset 0x40c, RW, Input stream buffer start offset
    swreg260_synthesis_config3_u SWREG260_SYNTHESIS_CONFIG3;   // offset 0x410, RO, Synthesis configuration register3(post-register)
    uint32_t RESERVED13[4];                                    // offset 0x414~0x420, Reserved
    swreg265_axi4_misc_config_u SWREG265_AXI4_MISC_CONF;       // offset 0x424, RW, AXI4 miscellaneous configuration
    uint32_t RESERVED14[31];                                   // offset 0x428~0x4a0, Reserved
    swreg297_abnormal_intr_msk_u SWREG297_ABNORMAL_INTR_MSK;   // offset 0x4a4, RW, NORMAL/ABNORMAL interrupt mask(used in video subsystem with VCMD)
    uint32_t RESERVED15[2];                                    // offset 0x4a8~0x4ac, Reserved
    swreg300_axi_debug0_u SWREG300_AXI_DEBUG0;                 // offset 0x4b0, RO, Decoder AXI debug register0
    swreg301_axi_debug1_u SWREG301_AXI_DEBUG1;                 // offset 0x4b4, RO, Decoder AXI debug register1
    swreg302_axi_debug2_u SWREG302_AXI_DEBUG2;                 // offset 0x4b8, RO, Decoder AXI debug register2
    swreg303_axi_debug3_u SWREG303_AXI_DEBUG3;                 // offset 0x4bc, RO, Decoder AXI debug register3
    swreg304_axi_debug4_u SWREG304_AXI_DEBUG4;                 // offset 0x4c0, RO, Decoder AXI debug register4
    swreg305_axi_debug5_u SWREG305_AXI_DEBUG5;                 // offset 0x4c4, RO, Decoder AXI debug register5
    swreg306_axi_debug6_u SWREG306_AXI_DEBUG6;                 // offset 0x4c8, RO, Decoder AXI debug register6
    swreg307_axi_debug7_u SWREG307_AXI_DEBUG7;                 // offset 0x4cc, RO, Decoder AXI debug register7
    swreg308_axi_debug8_u SWREG308_AXI_DEBUG8;                 // offset 0x4d0, RO, Decoder AXI debug register8
    swreg309_decoder_build_ver_u SWREG309_DECODER_BUILD_VER;   // offset 0x4d4, RO, Decoder Build ID Version Register
    swreg310_synthesis_config4_u SWREG310_SYNTHESIS_CONFIG4;   // offset 0x4d8, RO, Synthesis configuration register4
    uint32_t RESERVED16[3];                                    // offset 0x4dc~0x4e4, Reserved
    swreg314_decoder_out_stride_u SWREG314_DECODER_OUT_STRIDE; // offset 0x4e8, RW, Decoder output stride
    uint32_t RESERVED17[3];                                    // offset 0x4ec~0x4f4, Reserved
    swreg318_ext_timeout_ctrl_u SWREG318_EXT_TIMEOUT_CTRL;     // offset 0x4f8, RW, External timeout control register
    swreg319_timeout_ctrl_u SWREG319_TIMEOUT_CTRL;             // offset 0x4fc, RW, Timeout control register
    uint32_t RESERVED18[7];                                    // offset 0x500~0x518, Reserved
    swreg327_unique_id_u SWREG327_UNIQUE_ID;                   // offset 0x51c, POC diff between ref and current pic
    uint32_t RESERVED19[25];                                   // offset 0x520~0x580, Reserved
    swreg353_device_conf_post_u SWREG353_DEVICE_CONF_POST;     // offset 0x584, RW, Device configuration register post-processor
    swreg354_range_mapping_ctrl_u SWREG354_RANGE_MAPPING_CTRL; // offset 0x588, RW, Range Mapping Control
    uint32_t RESERVED20[29];                                   // offset 0x58c~0x5fc, Reserved
    swreg384_pp_conf_u SWREG384_PP_CONF;                       // offset 0x600, RW, Configuration register for ppX
    uint32_t RESERVED21;                                       // offset 0x604, Reserved
    swreg386_pp_out_lu_base_u SWREG386_PP_OUT_LU_BASE;         // offset 0x608, RW, Base address LSB (bits31:0) for writing post-processed picture luminance/R for ppX
    uint32_t RESERVED22;                                       // offset 0x60c, Reserved
    swreg388_pp_out_ch_base_u SWREG388_PP_OUT_CH_BASE;         // offset 0x610, RW, Base address LSB (bits31:0) for writing post-processed picture Ch/G for ppX
    uint32_t RESERVED23;                                       // offset 0x614, Reserved
    swreg390_pp_out_b_base_u SWREG390_PP_OUT_B_BASE;           // offset 0x618, RW, Base address LSB (bits31:0) for writing post-processed picture B for ppX
    swreg391_pp_out_stried_u SWREG391_PP_OUT_STRIDE;           // offset 0x61c, RW, PP output stride register for ppX
    uint32_t RESERVED24;                                       // offset 0x620, Reserved
    swreg393_pp_crop_input_u SWREG393_PP_CROP_INPUT;           // offset 0x624, RW, Crop input width/height for ppX
    swreg394_pp_out_alpha_u SWREG394_PP_OUT_ALPHA;             // offset 0x628, RW, Alpha value of ARGB and duplicated pixels count in two directions for ppX
    swreg395_pp_out_scale_u SWREG395_PP_OUT_SCALE;             // offset 0x62c, RW, Scale output width/height for ppX
} reg_decoder_t;


#ifdef __cplusplus
}
#endif

#endif
