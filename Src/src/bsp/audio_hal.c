/**
 * @file audio_hal.c
 * @author Product application department
 * @brief AUDIO 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-17
 *
 * @copyright  Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "audio_hal.h"
#include "dac_hal.h"
#include "pit32_hal.h"
#include "dma_hal.h"
#include "audio_array.h"
#include "audio_adpcm.h"
#include "cpm_hal.h"
#include "interrupt.h"

// 全局变量定义
#define MAX_TUNE_VOLUME 10
#define MAX_LLI_NUM mIVoiceBlockNum
#define _bit(x) ((uint32_t)1 << (x))
#define _bit_set1(value,bit)     (value |= (1 << bit))
#define _bit_clr1(value,bit)     (value &= ~(1 << bit))
#define _chk_bit1(val, bit) ((val) & (1 << bit))

#define FDIN_MASK 0
#define FDOT_MASK 1
#define ADDONE_MASK 2
#define ADDMA_MASK 3
#define READDATA_MASK 4

#define STATUS sVoice.mStatus

#define FDIN_SET() _bit_set1(STATUS, FDIN_MASK) // 淡入完成状态位
#define FDIN_CLR() _bit_clr1(STATUS, FDIN_MASK)
#define FDIN_CHK() _chk_bit1(STATUS, FDIN_MASK)

#define FDOT_SET() _bit_set1(STATUS, FDOT_MASK) // 淡出完成状态位
#define FDOT_CLR() _bit_clr1(STATUS, FDOT_MASK)
#define FDOT_CHK() _chk_bit1(STATUS, FDOT_MASK)

#define STDO_SET() _bit_set1(STATUS, ADDONE_MASK) // 数据完成状态位
#define STDO_CLR() _bit_clr1(STATUS, ADDONE_MASK)
#define STDO_CHK() _chk_bit1(STATUS, ADDONE_MASK)

#define STDM_SET() _bit_set1(STATUS, ADDMA_MASK) // DMA完成状态位
#define STDM_CLR() _bit_clr1(STATUS, ADDMA_MASK)
#define STDM_CHK() _chk_bit1(STATUS, ADDMA_MASK)

#define RDDATA_SET() _bit_set1(STATUS, READDATA_MASK) // 请求数据状态位
#define RDDATA_CLR() _bit_clr1(STATUS, READDATA_MASK)
#define RDDATA_CHK() _chk_bit1(STATUS, READDATA_MASK)

#define AudioTimer_Enable() AUDIOTM->PCSR |= PIT_PCSR_EN
#define AudioTimer_Disable() AUDIOTM->PCSR &= ~PIT_PCSR_EN
#define AudioSize 0
#define AudioAddr 1
#define AUDIOTM ((reg_pit32_t *)PIT2_BASE_ADDR)
uint8_t g_tuneVolume = 10;
volatile uint32_t dma_isr_errflag = 0;
static dmac_lli_t g_dma_lli_voice[MAX_LLI_NUM];
extern uint32_t AudioMem[AUDIO_MAX][2];
extern dmac_controlreg_t *m_dma_control;

// 结构体定义
/**
 * @brief audio 驱动结构体定义
 * 
 */
typedef struct
{
    BOOL bStart;
    BOOL bBusy;
    uint8_t mStatus;
    uint32_t wCurAddr;
    uint32_t wTatolLength;
    uint32_t wOutIndex;
    uint32_t wDataInNumMax;
    uint8_t wDataBufIn[mIVoiceBufSize];
    uint8_t wDataBufOut[mIVoiceBlockSize * 2];
} taudiodrv_t;
taudiodrv_t sVoice;

dmac_channel_t *m_dmacdac_channel[DMAC_CHNUM] = {(dmac_channel_t *)(DMAC2_BASE_ADDR), (dmac_channel_t *)(DMAC2_BASE_ADDR + 0x58),
                                                 (dmac_channel_t *)(DMAC2_BASE_ADDR + 0xB0), (dmac_channel_t *)(DMAC2_BASE_ADDR + 0x108)}; // global struct variable for for Channel registers

// 函数定义

/**
 * @brief  AUDIO 初始化驱动DMA搬运音频数据的定时器函数
 *
 * @param  rate 波特率
 *
 */
static void hal_audiotimerinit(uint32_t rate)
{
    uint8_t DMA_ENABLE = 1;
    AUDIOTM->PCSR &= (~PIT_PCSR_EN);
    AUDIOTM->PCSR = (0 << 8) | PIT_PCSR_OVW | PIT_PCSR_RLD;

    AUDIOTM->PMR = (g_ips_clk / 1000000 * (1000000 / (float)rate));
    AUDIOTM->PCSR = (PIT32_CLK_DIV_1 << 8) | PIT_PCSR_OVW | PIT_PCSR_RLD;

    drv_dac_init(LEFTALIGNED_12BITS, TRIGGER_PIT, DET_ON_RISING, DMA_ENABLE);
}

/**
 * @brief DAC 模块 DMA传输配置函数
 * @param channel DMA通道
 * @param src 传输数据源地址
 * @param length 传输长度
 */
void dma_dac_tran(uint8_t channel, uint32_t src, uint32_t length)
{
    // m_dma_control->DMA_CONFIG = 1;
    m_dmacdac_channel[channel]->SRCADDR = src;
    m_dmacdac_channel[channel]->DSTADDR = DAC->DAC_DR;
    m_dmacdac_channel[channel]->CTRL = SIEC | DNOCHG | M2P_DMA | DWIDTH_HW | SWIDTH_HW | INTEN;
    m_dmacdac_channel[channel]->CTRL_HIGH = length;

    m_dmacdac_channel[channel]->CONFIG = 0;
    m_dmacdac_channel[channel]->CONFIG_HIGH = DST_PER_DAC;

    m_dma_control->DMA_MASKTFR = CHANNEL_UMASK(channel);
    m_dma_control->DMA_CHEN = CHANNEL_WRITE_ENABLE(channel) | CHANNEL_ENABLE(channel);
}

/**
 * @brief DMA 模块初始化DAC DMA LLI寄存器函数.
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @param[in] pdma_lli dma的LLI结构体
 *
 * @return @ref NONE
 */
void dma_dac_lli_reg_init(uint8_t n, dmac_lli_t *dma_lli)
{
    m_dma_control->DMA_CONFIG = 1;

    m_dmacdac_channel[n]->SRCADDR = dma_lli->src_addr;
    m_dmacdac_channel[n]->DSTADDR = dma_lli->dst_addr;
    m_dmacdac_channel[n]->LLI = (uint32_t)dma_lli;
    m_dmacdac_channel[n]->CTRL = dma_lli->control;
    m_dmacdac_channel[n]->CTRL_HIGH = dma_lli->len;

    m_dmacdac_channel[n]->CONFIG = 0;
    m_dmacdac_channel[n]->CONFIG_HIGH = DST_PER_DAC;

    m_dma_control->DMA_MASKTFR = CHANNEL_UMASK(n);
    m_dma_control->DMA_CHEN = CHANNEL_WRITE_ENABLE(n) | CHANNEL_ENABLE(n);
}
/**
 * @brief AUDIO 开始DMA传输配置函数
 *
 * @param data 待发送数据
 * @param length 数据长度
 */
void hal_audiodrvprocessdma(uint8_t *data, uint32_t length)
{
    dcache_invalidate_range((uint32_t *) data, length);
    uint8_t i = 0;
    uint32_t transLen = 0, lli_num;
    uint32_t wDataOutLen = length;
    uint32_t index = 0;
    uint8_t *wBufOut = data;

    if (data == NULL || length == 0)
        return;

    if (wDataOutLen > (0xFF0 << 1))
    {
        transLen = (0xFF0);
        lli_num = wDataOutLen / (0xFF0 << 1);
        if (wDataOutLen % (0xFF0 << 1))
            lli_num++;
        for (i = 0; i < lli_num; i++)
        {
            g_dma_lli_voice[i].src_addr = ((uint32_t)(wBufOut) + index);
            g_dma_lli_voice[i].dst_addr = 0x40021004;

            if (i < (lli_num - 1))
            {
                g_dma_lli_voice[i].next_lli = (uint32_t)&g_dma_lli_voice[i + 1];
            }
            else
            {
                g_dma_lli_voice[i].next_lli = 0;
            }

            g_dma_lli_voice[i].control = SIEC | DNOCHG | M2P_DMA | DWIDTH_HW | SWIDTH_HW | INTEN | LLP_SRC_EN;
            g_dma_lli_voice[i].len = transLen;
            index += (transLen << 1);
            wDataOutLen -= (transLen << 1);

            if (wDataOutLen > (0xFF0 << 1))
            {
                transLen = 0xFF0;
            }
            else
            {
                transLen = (wDataOutLen >> 1);
            }
        }
        dma_dac_lli_reg_init(AUDIO_DMA_CH, &g_dma_lli_voice[0]);
    }
    else
    {

        transLen = (wDataOutLen >> 1);
        dma_dac_tran(AUDIO_DMA_CH, (uint32_t)wBufOut, transLen);

    }

}

/**
 * @brief AUDIO 配置数据发送函数
 *
 */
static void hal_audiodrvsenddata(void)
{
    hal_audiodrvprocessdma(sVoice.wDataBufOut + sVoice.wOutIndex, sVoice.wDataInNumMax);
    // 重置待发送缓冲区索引地址
    if (sVoice.wDataInNumMax <= mIVoiceBlockSize)
    {
        sVoice.wOutIndex = (sVoice.wOutIndex + sVoice.wDataInNumMax) > mIVoiceBlockSize ? 0 : mIVoiceBlockSize;
    }
    // 待发送数据长度设置为0
    sVoice.wDataInNumMax = 0;
}

/**
 * @brief  AUDIO 音频功能的中断处理函数
 *
 */
void hal_audioisrhandler(void)
{
    STDM_SET();

    // 待发送数据若不为空，配置DMA发送
    if (sVoice.wDataInNumMax)
    {
        // 配置发送下一段数据
        STDM_CLR();
        hal_audiodrvsenddata();
    }

    // 设置读取标记，需要读取新数据
    RDDATA_SET();
}

/**
 * @brief AUDIO DMA中断服务函数
 *
 */
void hal_audio_irqhandler(void)
{
    if (m_dma_control[AUDIO_DMA_CH].DMA_STATTFR & (1 << AUDIO_DMA_CH))
    {
        // Only Handle TF IRQ
        hal_audioisrhandler();
    }
    if (m_dma_control->DMA_STATERR & 0x0f) // dma error
    {
        dma_isr_errflag = m_dma_control->DMA_STATERR & 0x0f;
        m_dma_control->DMA_CLRERR = dma_isr_errflag;
    }

    m_dma_control->DMA_CLRTFR = m_dma_control->DMA_STATTFR;
    m_dma_control->DMA_CLRBLOCK = m_dma_control->DMA_STATBLOCK;
    m_dma_control->DMA_CLRSRC = m_dma_control->DMA_STATSRC;
    m_dma_control->DMA_CLRDST = m_dma_control->DMA_STATDST;
    m_dma_control->DMA_CLRERR = m_dma_control->DMA_STATERR;
}

/**
 * @brief  AUDIO 初始化驱动DMA函数
 *
 */
static void hal_audiodmainit(void)
{
    drv_dmac_reg_init(DMAC2_BASE_ADDR);
    NVIC_Init(3, 3, DMA2_IRQn, 2);
    DMA2_IRQHandler_Callback = hal_audio_irqhandler;
}

/**
 * @brief  AUDIO 根据参考点寻找语言平滑过渡的起点/终点函数
 *
 * @param  i 向上平滑/向下平滑移动
 * @param  data 参考点
 *
 */
static uint32_t hal_findpointinfadedata(uint8_t i, uint16_t data)
{
    uint16_t end_addr, base_data, start_addr;
    uint32_t index;

    if (i == 0)
    {
        data = (data / 0x10) * 0x10;
        for (end_addr = 0, base_data = 0, index = 0; data > base_data; end_addr = end_addr + 2)
        {
            base_data = base_data + 0x10;
            index = index + 0x02;
        }
    }
    else
    {
        for (start_addr = 0, base_data = 0xfff0, index = 0x2000; data < base_data; start_addr = start_addr + 2)
        {
            base_data = base_data - 0x10;
            index = index - 0x02;
        }

        index = 0x2000 - index;
    }
    return index;
}

/**
 * @brief  AUDIO 配置用于语言平滑播放的前置/后置数据函数
 *
 * @param  data 参考点
 *
 */
static void hal_audiofadeconfig(uint8_t *data)
{
    uint8_t dir = 0;
    uint16_t sData = 0, tData = 0;
    uint32_t dlen, addr = 0;

    sData = (DAC->DAC_DOR << 4);
    tData = (data[1] << 8) + data[0];

    if (sData < tData)
    {
        dir = 0;
        addr = (uint32_t)fadein_data;
    }
    else
    {
        dir = 1;
        addr = (uint32_t)fadeout_data;
    }

    dlen = hal_findpointinfadedata(dir, sData);
    addr += dlen;
    dlen = hal_findpointinfadedata(dir, tData) - dlen;

#ifdef AUDIO_LOG
    AUDIO_LOG("addr = %p,dlen = %d\n", addr, dlen);
#endif
    if (dlen)
    {
        STDM_CLR();
        hal_audiodrvprocessdma((uint8_t *)addr, dlen);
    }
    else
    {
#ifdef AUDIO_LOG
        AUDIO_LOG("AudioISRHandler call\n");
#endif

        hal_audioisrhandler();
    }
}

/**
 * @brief  AUDIO 解压缩功能函数
 *
 * @param  dst 目的地址
 * @param  src 源地址
 * @param  length 解码前/解码后长度
 *
 */
void hal_audiodecode(uint8_t *dst, uint8_t *src, uint32_t *length)
{
#if AUDIO_COMPRESS
    uint32_t i = 0, mlen = *length;
    int16_t temp;
    for (; i < mlen; i++)
    {
        temp = (audiodecodeproc(src[i] & 0x0F) / MAX_TUNE_VOLUME) * g_tuneVolume;
        temp += 0x8000;

        dst[4 * i] = (uint8_t)(temp & 0xff);
        dst[4 * i + 1] = (uint8_t)((temp >> 8) & 0xff);

        temp = (audiodecodeproc((src[i] >> 4) & 0x0F) / MAX_TUNE_VOLUME) * g_tuneVolume;
        temp += 0x8000;

        dst[4 * i + 2] = (uint8_t)(temp & 0xff);
        dst[4 * i + 3] = (uint8_t)((temp >> 8) & 0xff);
    }
    *length = mlen * 4;
#else
    memcpy(dst, src, *length);
#endif
}

/**
 * @brief AUDIO 将4字节合并为1个32bit变量函数
 *
 * @param value 值
 * @return unsigned long
 */
unsigned long byte_to_int(const uint8_t value[4])
{
    unsigned long nubmer = 0;

    nubmer = (unsigned long)value[3];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[2];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[1];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[0];

    return nubmer;
}

/**
 * @brief AUDIO 根据语言文件编号，索引文件存储地址和长度函数
 *
 * @param playNumber 语言文件编号
 * @param length 文件长度
 * @return uint32_t 文件首地址
 */
uint32_t hal_audioflashaddr(uint16_t playNumber, uint32_t *length)
{
    uint32_t addr = 0;
    audiodecodeinit();
    // 根据PlayNumber，获取文件地址和长度
    // 客户自定义代码实现
    /**********************************/
#ifdef AUDIO_EXAMPLE
    if (TEST_AUDIO_NUMBER == playNumber)
    {
        addr = (uint32_t)mWavSample;
        *length = mWavSampleLength;
    }
#else

    *length = AudioMem[playNumber][AudioSize];
    addr = AudioMem[playNumber][AudioAddr];
#endif
    return addr;
}

/**
 * @brief  AUDIO 读取任意字节数函数
 *
 * @param  dst 语言文件编号
 * @param  length 读取长度
 * @param  addr 地址
 *
 */
void hal_audioreadbytes(uint8_t *dst, uint32_t length, uint32_t addr)
{
#ifdef AUDIO_EXAMPLE
    memcpy(dst, (uint8_t *)addr, length);
#else
    ENTER_CRITICAL();
    SSI_EFlash_QUAD_Read(SSI1, addr, dst, length);
    EXIT_CRITICAL();
#endif
}

/**
 * @brief  AUDIO 初始化语言播放驱动层初始化函数
 *
 */
void hal_audiodrvinit(void)
{
#ifdef AUDIO_LOG
    AUDIO_LOG("Audio Init\n");
#endif
    memset(&sVoice, 0, sizeof(sVoice));

    hal_audiodmainit();
}
/**
 * @brief  AUDIO 初始化语言播放函数
 *
 */
void hal_audioinit(void)
{
    hal_audiodrvinit();
}

/**
 * @brief  AUDIO 设置音量大小函数
 * @param  volume 音量参数处于0~MAX_TUNE_VOLUME之间
 *
 */
void hal_audiosetvolume(uint8_t volume)
{
    g_tuneVolume = volume > MAX_TUNE_VOLUME ? MAX_TUNE_VOLUME : volume;
}

/**
 * @brief  AUDIO 获取当前音量函数
 *
 * @return 当前音量值
 */
uint8_t hal_audiogetcurvolume(void)
{
    return g_tuneVolume;
}

/**
 * @brief  AUDIO 获取最大音量函数
 *
 * @return 最大音量值，MAX_TUNE_VOLUME
 */
uint8_t hal_audiogetmaxvolume(void)
{
    return MAX_TUNE_VOLUME;
}

/**
 * @brief   AUDIO 停止播放函数
 *
 */
void hal_audiodrvstop(void)
{
    // 停止计时器和DMA
    AudioTimer_Disable();
    drv_dmac_dis(AUDIO_DMA_CH);

    if (sVoice.bStart)
    {
        // 播放状态
        hal_audiotimerinit(mVoiceFreq);
        AudioTimer_Enable();
        // 播放一段静音数据，避免噪音/爆音出现
        hal_audiodrvprocessdma(voicemutedata, 16);

        delayms(3);
        AudioTimer_Disable();
        drv_dmac_dis(AUDIO_DMA_CH);

        memset(&sVoice, 0, sizeof(sVoice));
    }
}
/**
 * @brief   AUDIO 设置待播放语音文件函数
 *
 * @param addr 文件首地址
 * @param length 文件长度
 *
 */
void hal_audiodrvconfig(uint32_t addr, uint32_t length)
{
    sVoice.wCurAddr = addr;
    sVoice.wTatolLength = length;

    sVoice.bBusy = TRUE;
    if (sVoice.wTatolLength == 0)
    {
#ifdef AUDIO_LOG
        AUDIO_LOG("invalid voice！\n");
#endif
        hal_audiodrvstop();
    }
#ifdef AUDIO_LOG
    AUDIO_LOG("SET CONFIG,sVoice.wCurAddr = 0x%x,sVoice.wTatolLength = %d\n", sVoice.wCurAddr, sVoice.wTatolLength);
#endif
}

/**
 * @brief   AUDIO 设置待播放语言文件函数
 *
 * @param  playNumber 语言文件编号
 *
 */
void hal_audiosetplaynumber(uint16_t playNumber)
{
    uint32_t length = 0;
    uint32_t addr;

    addr = hal_audioflashaddr(playNumber, &length);

    hal_audiodrvinit();
    hal_audiodrvconfig(addr, length);
}
/**
 * @brief   AUDIO 配置用于语言平滑播放的前置/后置数据函数
 *
 * @param  length 获取数据长度
 *
 */
static void hal_audiodrvgetdataout(uint32_t length)
{
    uint32_t dlen = 0;
    uint16_t data = 0;

    if (sVoice.wTatolLength)
    {
#if AUDIO_COMPRESS
        dlen = length / 4;
#else
        dlen = length;
#endif
        dlen = sVoice.wTatolLength > dlen ? dlen : sVoice.wTatolLength;
        hal_audioreadbytes(sVoice.wDataBufIn, dlen, sVoice.wCurAddr);

        sVoice.wTatolLength -= dlen;
        sVoice.wCurAddr += dlen;

        hal_audiodecode(sVoice.wDataBufOut + sVoice.wOutIndex, sVoice.wDataBufIn, &dlen);
        sVoice.wDataInNumMax = dlen;
    }
    else
    {
        if (!FDOT_CHK() && STDM_CHK())
        {
#ifdef AUDIO_LOG
            AUDIO_LOG("FADE OUT\n");
#endif
            data = (uint16_t)0x8000;
            hal_audiofadeconfig((uint8_t *)&data);
            FDOT_SET();
        }
    }

    RDDATA_CLR();

    if (!FDIN_CHK())
    {
#ifdef AUDIO_LOG
        AUDIO_LOG("FADE IN,Data = %02x,%02x\n", (uint8_t)*(uint8_t *)(sVoice.wDataBufOut + sVoice.wOutIndex), (uint8_t)*(uint8_t *)(sVoice.wDataBufOut + sVoice.wOutIndex + 1));
#endif
        hal_audiofadeconfig((sVoice.wDataBufOut + sVoice.wOutIndex));
        FDIN_SET();
    }
}
/**
 * @brief   AUDIO 语言播放功能函数
 *
 */
void hal_audiodrvhandle(void)
{
    if (!sVoice.bBusy)
        return;

    if (sVoice.bStart == 0)
    {
        sVoice.bStart = TRUE;
        hal_audiotimerinit(mVoiceFreq);
        AudioTimer_Enable();
        RDDATA_SET();
    }

    if (RDDATA_CHK())
    {
        hal_audiodrvgetdataout(mIVoiceBlockSize);
    }
    else if (STDM_CHK())
    {
        if (sVoice.wDataInNumMax)
        {
            hal_audiodrvsenddata();
        }

        if (FDOT_CHK())
        {
#ifdef AUDIO_LOG
            AUDIO_LOG("Audio Stop\n");
#endif
            hal_audiodrvstop();
        }
    }
}

/**
 * @brief   AUDIO 播放语言函数
 *
 */
errorstatus hal_audioplay(void)
{
    hal_audiodrvhandle();
    return hal_audiogetstatus();
}

/**
 * @brief   AUDIO 停止语言播放函数
 *
 */
void hal_audiostop(void)
{
    hal_audiodrvstop();
}

/**
 * @brief   AUDIO 当前播放状态函数
 *
 * @return
 *
 */
BOOL hal_audiobusystatus(void)
{
    return sVoice.bBusy;
}

/**
 * @brief  AUDIO  获取当前播放状态函数
 *
 */
errorstatus hal_audiogetstatus(void)
{
    return hal_audiobusystatus() ? _ERROR : _SUCCESS;
}
