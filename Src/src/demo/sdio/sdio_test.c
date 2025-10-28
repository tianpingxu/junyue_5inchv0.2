/**
 * @file sdio_test.c
 * @author Product Application Department
 * @brief  SDIO 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup SDIO SDIO模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "sdio_test.h"
#include "diskio.h"
#include "ff.h"


// 全局变量定义
uint8_t g_read_databuf[1024] = {0};
uint8_t g_write_databuf[1024] = {0};

/**
 * @brief 数值赋值函数
 *
 * @param data 数据缓存
 * @param len 数据长度
 */
static void data_gnrt(uint8_t *data, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        data[i] = i;
    }
}

/**
 * @brief SDIO 模块测试示例函数
 *
 */
void sdio_sd_test(void)
{
    sdio_sd_error_t status;
    uint32_t i, lbaaddr = 20480, secCnt = 2;
    uint32_t test_cnt = 2;

    printf("\r\n----------------- SDIO R/W -----------------\r\n");
    status = hal_sd_enumcard();
    if (status != SD_OK)
    {
        printf("hal_sd_enumcard error.\r\n");
    }
    else
    {
        printf("hal_sd_enumcard ok.\r\n");
    }
    status = hal_sd_readblock(lbaaddr, (uint32_t *)g_read_databuf, BLOCK_SIZE, secCnt);
    if (status != SD_OK)
    {
        printf("hal_sd_readblock error.\r\n");
    }
    else
    {
        printf("hal_sd_readblock ok.\r\n");
    }

    data_gnrt(g_write_databuf, sizeof(g_write_databuf));
    status = hal_sd_writeblock(lbaaddr, (uint32_t *)g_write_databuf, BLOCK_SIZE, secCnt);
    if (status != SD_OK)
    {
        printf("hal_sd_writeblock error.\r\n");
    }
    else
    {
        printf("hal_sd_writeblock ok.\r\n");
    }

    memset(g_read_databuf, 0, sizeof(g_read_databuf));
    status = hal_sd_readblock(lbaaddr, (uint32_t *)g_read_databuf, BLOCK_SIZE, secCnt);
    if (status != SD_OK)
    {
        printf("hal_sd_readblock error.\r\n");
    }
    else
    {
        printf("hal_sd_readblock ok.\r\n");
    }

    if (memcmp(g_read_databuf, g_write_databuf, sizeof(g_read_databuf)) == 0)
    {
        printf("test ok.");
    }
    else
    {
        printf("test error.");
    }
}

/**
 * @brief SDIO 模块FATFS测试示例函数
 * 
 */
void sdio_fatfs_test(void)
{
    FATFS fs;
    FIL file;
    DIR dir;
    FILINFO info;
    int nfile, ndir;
    UINT bw = 0;  
    UINT br = 0;  
    
    FRESULT res;
    uint8_t writebuff[15] = {0x32, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x33, 0x32, 0x33};
    uint8_t readBuff[512] = {0};

    printf("\r\n----------------- FATFS -----------------\r\n");
    res = f_mount(&fs, "1:", 1);
    if (FR_OK != res)
    {
        printf("f_mount = %d, ERROR\r\n", res);
        return;
    }
    else
    {
        printf("f_mount OK\r\n");
    }
	
	extern  __ALIGNED(8) uint8_t buf_jpg[];
	const char *fn1 = "1:/fan_logo_on.png";;//"1:/background.jpg";;//"1:/fan.png";//"1:/background.jpg";
	res = f_open(&file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	printf("f_open = %d.\r\n", res);
	res = f_stat(fn1, &info);
	printf("f_stat = %d.\r\n", res);
	res = f_read(&file, buf_jpg, info.fsize, &br);
	printf("f_read = %d.\r\n", res);
	
	printf("br=%x; %x; %x,%x\r\n", br, info.fsize, buf_jpg[0], buf_jpg[1]);
	
//	res = f_open(&file,  "1:/background.jpg", FA_CREATE_ALWAYS | FA_READ);
//    if (res)
//    {
//        printf("f_open = %d, ERROR.\r\n", res);
//    }
//    else
//    {
//        printf("f_open OK.\r\n");
//    }

//	
//	FILINFO info1;
//	
//	res = f_stat("1:/background.jpg", &info1);
//	printf("f_stat = %d.\r\n", res);
//	res = f_read(&file, bk_decode_buffer, 1024*600, &br);
//	printf("f_read = %d. %d/%d\r\n", res, info1.fsize, br);

//    res = f_opendir(&dir, "1:"); 
//    if (res == FR_OK) {
//        nfile = ndir = 0;
//        for (;;) {
//            res = f_readdir(&dir, &info);
//            if (res != FR_OK || info.fname[0] == 0) break;
//            if (info.fattrib & AM_DIR) {
//                printf(">> <DIR> %s\n", info.fname);
//                ndir++;
//            } else {
//                printf(">> len=%u, filename:%s\n", info.fsize, info.fname);
//                nfile++;
//            }
//        }
//        f_closedir(&dir);
//        printf("%d dirs, %d files.\n", ndir, nfile);
//    }

//    res = f_open(&file, "0:test.txt", FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
//    if (res)
//    {
//        printf("f_open = %d, ERROR.\r\n", res);
//    }
//    else
//    {
//        printf("f_open OK.\r\n");
//    }


//    res = f_write(&file, writebuff, sizeof(writebuff), &bw);
//    if (res)
//    {
//        printf("f_write = %d, ERROR.\r\n", res);
//    }
//    else
//    {
//        printf("f_write OK.\r\n");
//    }

//    res = f_sync(&file);
//    if (res)
//    {
//        printf("f_sync = %d, ERROR.\r\n", res);
//    }
//    else
//    {
//        printf("sync OK\r\n");
//    }

//    f_lseek (&file, 0);  
//    res = f_read(&file, readBuff, 512, &br);
//    if (res)
//    {
//        printf("f_read = %d, ERROR.\r\n", res);
//    }else
//    {
//        printf(">> readBuff = %s, readlen = %d\r\n", readBuff, br);
//    }

    res = f_close(&file);
    if (res)
    {
        printf("f_close = %d, ERROR\r\n", res);
    }else
    {
        printf("f_close OK\r\n");
    }
}


/** @} */  // 结束 SDIO 模块分组
/** @} */  // 结束外设模块分组
