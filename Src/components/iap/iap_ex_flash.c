/**
 * @file iap_ex_flash.c
 * @author Product application department
 * @brief flash 操作用例，仅供参考
 * @version V1.0    
 * @date 2025-06-24
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

 /**
 * @defgroup ThirdPart 第三方模块
 * @{
 *
 * @defgroup FLASH FLASH模块
 * @ingroup ThirdPart
 * @{
 */

 //头文件定义
#include "iap_ex_flash.h"
#include <stdint.h>
#include "ssi_hal.h"

//全局变量定义
static uint8_t Flash_Buffer[CCM_SECTOR_SIZE] = {0};

/**
 * @brief flash 任意地址写函数
 * 
 * @param flash_addr flash首地址
 * @param data 数据buffer
 * @param data_len 数据长度
 */
void flash_write(uint32_t flash_addr , uint8_t * data ,uint32_t data_len)
{
   uint32_t NeedSector = 0;
   uint32_t Cnt = 0;
   uint8_t  disp_pos = 30;
   uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
	volatile uint16_t i;
	uint32_t offaddr;
   uint8_t dispbuffer[64] = {0};
	if (flash_addr < CCM_FLASH_BASE || (flash_addr >= (CCM_FLASH_BASE + CCM_SECTOR_SIZE * CCM_FLASH_SIZE)))
   {
       return;
   }


	if((data== NULL)||(data_len == 0)) 
   {
       return ;
   }
	offaddr = flash_addr - CCM_FLASH_BASE;
	secpos = offaddr / CCM_SECTOR_SIZE;      //Section addr
	secoff = (offaddr % CCM_SECTOR_SIZE) ;  //Offset in section
	secremain = CCM_SECTOR_SIZE - secoff;
	if (data_len <= secremain)
		secremain = data_len;
   NeedSector = data_len/4096+ (!!data_len%4096);
	//vaddr = secpos * CCM_SECTOR_SIZE;  // for test 
   
   while (1)
   {
		hal_ssi_flash_read(CCM_FLASH_BASE+secpos * CCM_SECTOR_SIZE , Flash_Buffer , CCM_SECTOR_SIZE);

       hal_ssi_flash_sector_erase(CCM_FLASH_BASE+secpos * CCM_SECTOR_SIZE);
       for (i = 0; i < secremain; i++) // 复制
       {
           Flash_Buffer[i + secoff] = data[i];
       }
		hal_ssi_flash_program(CCM_FLASH_BASE+secpos * CCM_SECTOR_SIZE, Flash_Buffer, CCM_SECTOR_SIZE);

       if(data_len == secremain)
       {
           break;              // 写入结束了
       }
       else                    // 写入未结束
       {
           secpos++;           // 扇区地址增1
           secoff = 0;         // 偏移位置为0
           data += secremain;   // 指针偏移
           data_len -= secremain;
           if(data_len > (CCM_SECTOR_SIZE))
           {
               secremain = CCM_SECTOR_SIZE; // 下一个扇区还是写不完
           }
           else
           {
               secremain = data_len;					//Next section will finish
           }
       }
       Cnt++;    
      

   }


}

/**
 * @brief 根据文件名写flash数据
 * 
 * @param TempFile 文件名
 * @param BaseAddr flash首地址
 * @param ptr 指针
 * @return int8_t 
 */
int8_t flashfile_write(FIL* TempFile ,uint32_t BaseAddr,void *ptr)
{
  
   (void)ptr;
   uint32_t FileLength = 0;
   uint32_t EaserSectorNum = 0;
   uint32_t IntegerSector = 0;
   uint32_t RemainderDataNum = 0;
   uint32_t CurentReadLength = 0;// 当前读取
   uint32_t FlashStartAddr = BaseAddr ;
   uint8_t* WriterPtr = Flash_Buffer;
   uint16_t Temp_len = 0;
   uint8_t  tempbuffer[16] = {0};
   int8_t ret = 0;

   volatile uint32_t cnt = 0; 

   if (BaseAddr < CCM_FLASH_BASE)
   {
       printf(" addr is error  0x%x \r\n",BaseAddr);
       return -1;
   }
      
   FileLength = f_size(TempFile);  // 获取当前文件句柄大小
   IntegerSector = EaserSectorNum = FileLength/CCM_SECTOR_SIZE;
	RemainderDataNum = FileLength%CCM_SECTOR_SIZE;
   if(RemainderDataNum)
   {
       EaserSectorNum++;
   }
   /* 暴力整扇区擦除  */
   printf("Start Erase Sector \r\n");
   

   for(cnt = 0; cnt < EaserSectorNum ;cnt++)
   {
       if(hal_ssi_flash_sector_erase(FlashStartAddr+cnt*CCM_SECTOR_SIZE)!=STATUS_OK)
       {
       printf("Erase Sector Failed %d \r\n",cnt);
       return -1;
       }  

   }

   printf("Erase Sector Success EaserSectorNum is %d \r\n",EaserSectorNum);
   printf("Start Write Flash Data \r\n");

   /* 开始写整扇区数据 */
   WriterPtr = Flash_Buffer;
   for(cnt = 1 ; cnt <= IntegerSector; cnt++)
   {
       for(uint32_t i = 1; i <= (CCM_SECTOR_SIZE/ReadSize) ;i++)
       {
           if(f_read(TempFile ,WriterPtr ,ReadSize ,&CurentReadLength)!= FR_OK)
           {
               printf("Read SD Card Failed Curent Read Num is %d \r\n",cnt*i*ReadSize);
               ret = -2;
               goto ERR ;
           }        
          WriterPtr+=ReadSize ;      
       }
       printf("Start Write Curent Sector is %d \r\n",cnt); 
       if(hal_ssi_flash_program(FlashStartAddr, Flash_Buffer, CCM_SECTOR_SIZE)!=STATUS_OK)
       {
           printf("Flash Erase FAILED Curent Program addr is 0x %x \r\n",FlashStartAddr);
           return -3;
       }
#if 0
       memset((void*)Read_Flash_Buffer,0x00,CCM_SECTOR_SIZE);
       LCD_SSI_FlashRead(FlashStartAddr,Read_Flash_Buffer,CCM_SECTOR_SIZE);
       if(memcmp(Flash_Buffer, Read_Flash_Buffer, CCM_SECTOR_SIZE))
       {
           LOG_E("Write Curent Sector is %d Error Error\r\n",cnt); 
       }
#endif 
      // DumpPrint(Flash_Buffer,4096);
       WriterPtr = Flash_Buffer;
       FlashStartAddr+=CCM_SECTOR_SIZE;

   }
   printf("Write IntegerSector is Done Start Write RemainderData \r\n");
   /* 判断是剩余够512 读取多少*/
   WriterPtr = Flash_Buffer;
   for(cnt = 1; cnt <= (RemainderDataNum / ReadSize);cnt++)
   {
       if(f_read(TempFile ,WriterPtr ,ReadSize ,&CurentReadLength)!= FR_OK)
       {
           return -2;
       }    
       WriterPtr+=ReadSize;
   }

   if(RemainderDataNum % ReadSize)
   {
       if(f_read(TempFile ,WriterPtr ,RemainderDataNum%ReadSize ,&CurentReadLength)!= FR_OK)
       {
           return -2;
       } 
   }

   if(hal_ssi_flash_program(FlashStartAddr, Flash_Buffer, RemainderDataNum)!=STATUS_OK)
   {
       printf("Write Flash  Error \r\n");
       return -3;
   }


ERR:
   printf("Write Done \r\n");

   return ret;
}
