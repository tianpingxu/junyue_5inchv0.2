/**
 * @file iap_test.c
 * @author Product application department
 * @brief  iap ���������������ο�
 * @version V1.0
 * @date 2025-06-24
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

 
/**
 * @defgroup ThirdPart ������ģ��
 * @{
 *
 * @defgroup IAP IAPģ��
 * @ingroup ThirdPart
 * @{
 */

#include "iap_test.h"
#include "pinswap_drv.h"
#include "eport_hal.h"
#include "diskio.h"
#include "ff.h"
#include "dictionary.h"
#include "iniparser.h"
#include "iap_ex_flash.h"
#include "lcd_iap.h"

#define SD_MOUNT    0
#define UDISK_MOUNT 1
ConfigParam SDConfig;
unsigned updateflag =0;
FIL TempFile ;

extern  lcd_handle_t lcd_dev;
uint8_t * PFileBuffer = NULL;
uint8_t fontlength = 0;
uint8_t fsize = 16;
uint8_t ypos = 2;
uint16_t j = 0;
char fontbuffer[128] ={0};

void BootLcdConfig(void)
{
    lcd_dev.lcd_itf_type = LCD_RGB;
    lcd_dev.lcd_ic = RGB_480854;
    lcd_dev.lcd_size.x = LCD_DISP_HOR_RES;
    lcd_dev.lcd_size.y = LCD_DISP_VER_RES;

    lcd_init(&lcd_dev);

    extern int LVGL_DISP_Color_Fill(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *color);
    LVGL_DISP_Color_Fill(0, 0, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, COLOR_BLACK);
}

void ShowBootMsg(void)
{
    lcd_show_string(&lcd_dev,5, ypos+ fsize*j++, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, fsize, "C*Core Bootloadr "BootVersion, COLOR_GREEN);
    lcd_show_string(&lcd_dev,5, ypos+ fsize*j++, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, fsize, "Copyright (C) 2022-2032", COLOR_GREEN);
    lcd_show_string(&lcd_dev,5, ypos + fsize*j++, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, fsize, "CPU:CCM4101 200Mhz", COLOR_GREEN);
    lcd_show_string(&lcd_dev,5, ypos + fsize*j++, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, fsize, "FLASH:2MB SRAM:128KB", COLOR_GREEN);
}

 /**
  * @brief ��תAPP�ӿ�
  * @param addr APP��ַ
  */
void bootjumpapp(uint32_t addr)
{
    printf("Setting jump app addr is 0x%x \r\n",addr);
    uint32_t sp = *((volatile uint32_t *)(addr));
    uint32_t pc = *((volatile uint32_t *)(addr + 4));
    typedef void (*FuncRunApp)(void);
    FuncRunApp ResetHandler = (FuncRunApp)pc;
    /* �ر��ж� */
    printf("Disable IRQ Handler \r\n");
    __disable_irq();
    __DSB();
    __ISB();
     /* �����ж�������λ�� */
    printf("Setting VTOR \r\n");
    SCB->VTOR = (uint32_t)(addr);
    /* ��ת APP  */
    printf("Jump function \r\n");
    ResetHandler();
    
    printf("Never Go There \r\n");
    while(1) __NOP(); // never go there

}

int8_t mount_fatfs()
{
    FATFS fs;
    FRESULT res;
    #if SD_MOUNT
    printf("Start mound sd card \r\n");
	res = f_mount(&fs, "0:", 1);
    if (FR_OK != res)
    {
        printf("f_mount = %d, ERROR\r\n", res);
        return -1;
    }
    printf("SD Card mount success \r\n");
    #elif UDISK_MOUNT
    printf("Start mound u disk \r\n");
	res = f_mount(&fs, "3:", 1);
    if (FR_OK != res)
    {
        printf("f_mount = %d, ERROR\r\n", res);
        return -1;
    }
    printf("u disk mount success \r\n");

    #endif

    return 0;
}
/**
 * @brief ��ȡSD/U��������Ϣ
 * 
 * @param config ������Ϣ
 * @return int8_t 
 */
int8_t readparam(ConfigParam * config)
{
    dictionary  *Config_ini = NULL;
    Config_ini = iniparser_load(SD_PARA_COFIG);
    if(NULL == Config_ini)
    {
        printf("Config.ini load error\n");
		return -1;
	}
    
    printf("Read SD param\r\n");
    
    config->DebugPrint = iniparser_getint(Config_ini,"config:DEBUG",0);
	printf("config:DEBUG is %d \r\n",config->DebugPrint);

    config->UpdateBoot = iniparser_getint(Config_ini,"update:UpdateBoot",0);
	printf("update:UpdateBoot is %d \r\n", config->UpdateBoot);

	config->UpdateApp = iniparser_getint(Config_ini,"update:UpdateApp",0);
	printf("update:UpdateApp is %d \r\n",config->UpdateApp);

	config->UpdateImg = iniparser_getint(Config_ini,"update:UpdateImg",0);
	printf("update:UpdateImg is %d \r\n",config->UpdateImg);

	config->CheckBootCrc = iniparser_getint(Config_ini,"config:CheckBootCrc",0);
	printf("config:CheckBootCrc is %d \r\n",config->CheckBootCrc);

	config->CheckAppCrc = iniparser_getint(Config_ini,"config:CheckAppCrc",0);
	printf("config:CheckAppCrc is %d \r\n",config->CheckAppCrc);

	config->CheckImgCrc = iniparser_getint(Config_ini,"config:CheckImgCrc",0);
    printf("config:CheckImgCrc is %d \r\n",config->CheckImgCrc);

    iniparser_freedict(Config_ini);
    return 0;
}

/**
 * @brief ���¹̼���flash
 * 
 * @param config �����ļ�
 * @param area 
 * @return int8_t 
 */
int8_t updateappfirmware(ConfigParam * config, UpdateArea area)
{
    uint32_t DataAddr = 0;
    FRESULT res;
  
    int8_t ret = 0;
    uint8_t  CheckCrcFlag = 0;
    uint8_t CrcValueLehgth =0;
    char FileName[64]={0};
    uint32_t FileLength = 0;
    uint32_t FileSizeArea = 0; //�ļ���С��Χ
    uint32_t ReadLength=0;
    uint32_t CalCrcVlaue = 0;
  
    printf("Start update Firmware \r\n");
    if(area == AppArea)  // ���� APP����
    {
        DataAddr = CCM_APP_BASE;
        (config->CheckAppCrc == 1)?(CheckCrcFlag = 1,CrcValueLehgth = 4):(CheckCrcFlag = 0);
        strncpy(FileName,APP_FILE,strlen(APP_FILE)); 
        FileName[strlen(APP_FILE)] ='\0';
        FileSizeArea = CCM_APP_MAX_SIZE;
    }else
    {
        printf("unknow area Symbol \r\n");
    }
    res = f_open(&TempFile, FileName,FA_READ);
    if (res !=FR_OK)
    {
        printf("Open %s File Failed ErrorCode is %d \r\n",&FileName[2] ,res);
        return -1;
    }
    printf("Open %s File Success!! \r\n",&FileName[2]);
    FileLength = f_size(&TempFile);
    printf("%s FileSize is %d \r\n",&FileName[2],FileLength);
    if((FileLength - CrcValueLehgth) > FileSizeArea) // �̼������Գ���
    {
        printf("File is To Large \r\n");
        ret = -1;
        goto Err;
    }
    printf("Start Write Flash Please Wait ...\r\n");
    printf("Data Addr is 0x%x \r\n",DataAddr);

    flashfile_write(&TempFile ,DataAddr,NULL);
Err:
    f_close(&TempFile);

    return ret;

}

extern void drv_systick_enable(uint8_t flag);

void iap_demo(void)
{
    if(mount_fatfs() < 0)
    {
        printf("Mount Error\r\n");

        printf("BootJumpApp\r\n");
        SCB_DisableICache();
        SCB_DisableDCache();
        drv_systick_enable(FALSE);
        bootjumpapp(CCM_APP_BASE + 0x1000);
    }
    BootLcdConfig();
    ShowBootMsg();
    fontlength = sprintf(fontbuffer,"Check SD Card Insert ");
    lcd_show_string(&lcd_dev,5,ypos+ fsize*j,lcd_dev.lcd_size.x, lcd_dev.lcd_size.y,fsize,fontbuffer, COLOR_GREEN);

    if(readparam(&SDConfig) < 0)
    {
        printf("Config.ini is not found or broken\r\n");
        
        printf("BootJumpApp\r\n");
        SCB_DisableICache();
        SCB_DisableDCache();
        drv_systick_enable(FALSE);
        bootjumpapp(CCM_APP_BASE + 0x1000);
    }
    printf("Load Config.ini SUCCESS \r\n");
    if(SDConfig.UpdateApp == 1)
    {
        if(updateappfirmware(&SDConfig, AppArea) < 0)
        {
            printf("update error\r\n");

            printf("BootJumpApp\r\n");
            SCB_DisableICache();
            SCB_DisableDCache();
            drv_systick_enable(FALSE);
            bootjumpapp(CCM_APP_BASE + 0x1000);
        }else {
            printf("update success\r\n");
            printf("Please Shutdown Power\r\n");
        }  
    }
}
/** @} */  // ���� IAP ģ�����
/** @} */  // ��������ģ�����