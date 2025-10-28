/**
 * @file audio_adpcm.c
 * @author Product application department
 * @brief  adpcm 压缩解压驱动，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "audio_adpcm.h"

// 全局变量定义
const uint16_t StepSizeTable[89] = {7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
                                    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
                                    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
                                    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
                                    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
                                    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
                                    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
                                    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
                                    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767};

/* Table of gindex changes */
const int8_t IndexTable[16] = {-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};
static int8_t gindex = 0;
static int32_t gpredsample = 0;

// 函数定义

/**
 * @brief AUDIO 解压初始化函数
 *
 */
void audiodecodeinit(void)
{
    gindex = 0;
    gpredsample = 0;
}

/**
 * @brief AUDIO 解码功能函数
 *
 * @param code 源数据
 * @return int16_t 解码后数据
 */
int16_t audiodecodeproc(uint8_t code)
{

    uint16_t step = 0;
    int32_t diffq = 0;

    step = StepSizeTable[gindex];

    /* 2. inverse code into diff */
    diffq = step >> 3;
    if (code & 4)
    {
        diffq += step;
    }

    if (code & 2)
    {
        diffq += step >> 1;
    }

    if (code & 1)
    {
        diffq += step >> 2;
    }

    /* 3. add diff to predicted sample*/
    if (code & 8)
    {
        gpredsample -= diffq;
    }
    else
    {
        gpredsample += diffq;
    }

    /* check for overflow*/
    if (gpredsample > 32767)
    {
        gpredsample = 32767;
    }
    else if (gpredsample < -32768)
    {
        gpredsample = -32768;
    }

    /* 4. find new quantizer step size */
    gindex += IndexTable[code];
    /* check for overflow*/
    if (gindex < 0)
    {
        gindex = 0;
    }
    if (gindex > 88)
    {
        gindex = 88;
    }

    /* 5. save predict sample and gindex for next iteration */
    /* done! static variables */

    /* 6. return new speech sample*/
    return ((int16_t)gpredsample);
}

/**
 * @brief AUDIO 压缩函数
 *
 * @param code 源数据
 * @return int16_t 解压数据
 */
int16_t audioencodeproc(uint32_t code)
{
    uint16_t tmpstep = 0;
    int32_t diff = 0;
    int32_t diffq = 0;
    uint16_t step = 0;

    step = StepSizeTable[gindex];
    /* 2. compute diff and record sign and absolut value */
    diff = code - gpredsample;
    if (diff < 0)
    {
        code = 8;
        diff = -diff;
    }

    /* 3. quantize the diff into ADPCM code */
    /* 4. inverse quantize the code into a predicted diff */
    tmpstep = step;
    diffq = (step >> 3);
    if (diff >= tmpstep)
    {
        code |= 0x04;
        diff -= tmpstep;
        diffq += step;
    }

    tmpstep = tmpstep >> 1;
    if (diff >= tmpstep)
    {
        code |= 0x02;
        diff -= tmpstep;
        diffq += (step >> 1);
    }
    tmpstep = tmpstep >> 1;
    if (diff >= tmpstep)
    {
        code |= 0x01;
        diffq += (step >> 2);
    }
    /* 5. fixed predictor to get new predicted sample*/
    if (code & 8)
    {
        gpredsample -= diffq;
    }
    else
    {
        gpredsample += diffq;
    }

    /* check for overflow*/
    if (gpredsample > 32767)
    {
        gpredsample = 32767;
    }

    else if (gpredsample < -32768)
    {
        gpredsample = -32768;
    }

    /* 6. find new stepsize index */
    gindex += IndexTable[code];
    /* check for overflow*/
    if (gindex < 0)
    {
        gindex = 0;
    }
    else if (gindex > 88)
    {
        gindex = 88;
    }
    /* 8. return new ADPCM code*/
    return (code & 0x0f);
}
