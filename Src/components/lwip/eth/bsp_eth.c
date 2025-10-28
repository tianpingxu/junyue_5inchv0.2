/**
 * @file bsp_eth.c
 * @author Product application department 
 * @brief  ETH 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

 //头文件定义 
#include "stdbool.h"
#include "eth_hal.h" 
#include "bsp_eth.h" 
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "debug.h"
#include "uart_hal.h"
#include "drv_gpio_def.h"

//全局变量定义 
ETH_HandleTypeDef heth;

#define EHT_DMA_MODE            ETH_DMA_DEFAULT_MODE
//#define EHT_DMA_MODE            ETH_DMA_CONTINUOUS_MODE

#if( EHT_DMA_MODE == ETH_DMA_CONTINUOUS_MODE )


#define ETH_RXBUFCNT    (ETH_RXBUFNB<<2)

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFCNT] __ALIGN_END;/* Ethernet Rx MA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFCNT][(ETH_RX_BUF_SIZE>>2)] __ALIGN_END; /* Ethernet Receive Buffer */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __ALIGN_END; /* Ethernet Transmit Buffer */

#else//EHT_DMA_MODE == ETH_DMA_DEFAULT_MODE

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __ALIGN_END;/* Ethernet Rx MA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __attribute__((section("NO_INIT")))  __ALIGN_END; /* Ethernet Receive Buffer */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]  __attribute__((section("NO_INIT")))__ALIGN_END; /* Ethernet Transmit Buffer */

#define ETH_RXBUFCNT    ETH_RXBUFNB

#endif


#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */
                                                                                                            
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))


#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10U)


#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10U)


#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= (IRQn_Type)0x00U)

//函数定义

void Eth_Reset(void);
/**
  * @brief  Sets the priority grouping field (preemption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup The priority grouping bits length. 
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bits for preemption priority
  *                                    4 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bits for preemption priority
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for preemption priority
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for preemption priority
  *                                    1 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_4: 4 bits for preemption priority
  *                                    0 bits for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ preemption is no more possible. 
  *         The pending IRQ priority will be managed only by the subpriority. 
  * @retval None
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
  
  /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
  NVIC_SetPriorityGrouping(PriorityGroup);
}


/**
  * @brief  Sets the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file )
  * @param  PreemptPriority The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority 
  * @param  SubPriority the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority.          
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
  uint32_t prioritygroup = 0x00U;
  
  /* Check the parameters */
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
  
  prioritygroup = NVIC_GetPriorityGrouping();
  
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}


/**
  * @brief  Enables a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before. 
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file )
  * @retval None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  //assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}


/**
  * @brief  Disables a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file )
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}

static void ETH_PrintDMA(const char *title, const ETH_DMADescTypeDef *reg, int nr)
{
    int i;
    
    printf("======[ %s ]======\n", title);
    for (i = 0; i < nr; i++, reg++) {
        printf("%d: Status              = %x\n", i, reg->Status);
        printf("%d: ControlBufferSize   = %x\n", i, reg->ControlBufferSize);
        printf("%d: Buffer1Addr         = %x\n", i, reg->Buffer1Addr);
        printf("%d: Buffer2NextDescAddr = %x\n", i, reg->Buffer2NextDescAddr);
    }
}

//void ETH_Print(void)
//{
//    ETH_TypeDef *eth = (ETH_TypeDef *)ETH_MAC_BASE;

//    // printk_console("MACCR=          %x\n", eth->MACCR);
//    // printk_console("MACFFR=         %x\n", eth->MACFFR);
//    // printk_console("MACHTHR=        %x\n", eth->MACHTHR);
//    // printk_console("MACHTLR=        %x\n", eth->MACHTLR);
//    // printk_console("MACMIIAR=       %x\n", eth->MACMIIAR);
//    // printk_console("MACMIIDR=       %x\n", eth->MACMIIDR);
//    // printk_console("MACFCR=         %x\n", eth->MACFCR);
//    // printk_console("MACVLANTR=      %x\n", eth->MACVLANTR);            
//    // printk_console("MACRWUFFR=      %x\n", eth->MACRWUFFR);            
//    // printk_console("MACPMTCSR=      %x\n", eth->MACPMTCSR);
//    // printk_console("MACDBGR=        %x\n", eth->MACDBGR);
//    // printk_console("MACSR=          %x\n", eth->MACSR);                
//    // printk_console("MACIMR=         %x\n", eth->MACIMR);
//    // printk_console("MACA0HR=        %x\n", eth->MACA0HR);
//    // printk_console("MACA0LR=        %x\n", eth->MACA0LR);
//    // printk_console("MACA1HR=        %x\n", eth->MACA1HR);
//    // printk_console("MACA1LR=        %x\n", eth->MACA1LR);
//    // printk_console("MACA2HR=        %x\n", eth->MACA2HR);
//    // printk_console("MACA2LR=        %x\n", eth->MACA2LR);
//    // printk_console("MACA3HR=        %x\n", eth->MACA3HR);
//    // printk_console("MACA3LR=        %x\n", eth->MACA3LR);              
//    // printk_console("MMCCR=          %x\n", eth->MMCCR);                
//    // printk_console("MMCRIR=         %x\n", eth->MMCRIR);
//    // printk_console("MMCTIR=         %x\n", eth->MMCTIR);
//    // printk_console("MMCRIMR=        %x\n", eth->MMCRIMR);
//    // printk_console("MMCTIMR=        %x\n", eth->MMCTIMR);              
//    // printk_console("MMCTGFSCCR=     %x\n", eth->MMCTGFSCCR);           
//    // printk_console("MMCTGFMSCCR=    %x\n", eth->MMCTGFMSCCR);
//    // printk_console("MMCTGFCR=       %x\n", eth->MMCTGFCR);
//    // printk_console("MMCRFCECR=      %x\n", eth->MMCRFCECR);
//    // printk_console("MMCRFAECR=      %x\n", eth->MMCRFAECR);
//    // printk_console("MMCRGUFCR=      %x\n", eth->MMCRGUFCR);
//    // printk_console("MMCIPCINTMASKRX=%x\n", eth->MMCIPCINTMASKRX);
//    // printk_console("PTPTSCR=        %x\n", eth->PTPTSCR);
//    // printk_console("PTPSSIR=        %x\n", eth->PTPSSIR);
//    // printk_console("PTPTSHR=        %x\n", eth->PTPTSHR);
//    // printk_console("PTPTSLR=        %x\n", eth->PTPTSLR);
//    // printk_console("PTPTSHUR=       %x\n", eth->PTPTSHUR);
//    // printk_console("PTPTSLUR=       %x\n", eth->PTPTSLUR);
//    // printk_console("PTPTSAR=        %x\n", eth->PTPTSAR);
//    // printk_console("PTPTTHR=        %x\n", eth->PTPTTHR);
//    // printk_console("PTPTTLR=        %x\n", eth->PTPTTLR);
//    // printk_console("PTPTSSR=        %x\n", eth->PTPTSSR);
//    // printk_console("DMABMR=         %x\n", eth->DMABMR);
//    // printk_console("DMATPDR=        %x\n", eth->DMATPDR);
//    // printk_console("DMARPDR=        %x\n", eth->DMARPDR);
//    // printk_console("DMARDLAR=       %x\n", eth->DMARDLAR);
//    // printk_console("DMATDLAR=       %x\n", eth->DMATDLAR);
//        printf("DMASR=          %x\n", eth->DMASR);
//    // printk_console("DMAOMR=         %x\n", eth->DMAOMR);
//    // printk_console("DMAIER=         %x\n", eth->DMAIER);
//    // printk_console("DMAMFBOCR=      %x\n", eth->DMAMFBOCR);
//    // printk_console("DMARSWTR=       %x\n", eth->DMARSWTR);
//    // printk_console("DMACHTDR=       %x\n", eth->DMACHTDR);
//    // printk_console("DMACHRDR=       %x\n", eth->DMACHRDR);
//    // printk_console("DMACHTBAR=      %x\n", eth->DMACHTBAR);
//    // printk_console("DMACHRBAR=      %x\n", eth->DMACHRBAR);

//    ETH_PrintDMA("RxDscrTab", DMARxDscrTab, ETH_RXBUFCNT);
//    ETH_PrintDMA("TxDscrTab", DMATxDscrTab, ETH_TXBUFNB);
//}

void ETH_Print(void)
{
    ETH_TypeDef *eth = (ETH_TypeDef *)ETH_MAC_BASE;

     printf("MACCR=          %x\n", eth->MACCR);
     printf("MACFFR=         %x\n", eth->MACFFR);
     printf("MACHTHR=        %x\n", eth->MACHTHR);
     printf("MACHTLR=        %x\n", eth->MACHTLR);
     printf("MACMIIAR=       %x\n", eth->MACMIIAR);
     printf("MACMIIDR=       %x\n", eth->MACMIIDR);
     printf("MACFCR=         %x\n", eth->MACFCR);
     printf("MACVLANTR=      %x\n", eth->MACVLANTR);            
     printf("MACRWUFFR=      %x\n", eth->MACRWUFFR);            
     printf("MACPMTCSR=      %x\n", eth->MACPMTCSR);
     printf("MACDBGR=        %x\n", eth->MACDBGR);
     printf("MACSR=          %x\n", eth->MACSR);                
     printf("MACIMR=         %x\n", eth->MACIMR);
     printf("MACA0HR=        %x\n", eth->MACA0HR);
     printf("MACA0LR=        %x\n", eth->MACA0LR);
     printf("MACA1HR=        %x\n", eth->MACA1HR);
     printf("MACA1LR=        %x\n", eth->MACA1LR);
     printf("MACA2HR=        %x\n", eth->MACA2HR);
     printf("MACA2LR=        %x\n", eth->MACA2LR);
     printf("MACA3HR=        %x\n", eth->MACA3HR);
     printf("MACA3LR=        %x\n", eth->MACA3LR);              
     printf("MMCCR=          %x\n", eth->MMCCR);                
     printf("MMCRIR=         %x\n", eth->MMCRIR);
     printf("MMCTIR=         %x\n", eth->MMCTIR);
     printf("MMCRIMR=        %x\n", eth->MMCRIMR);
     printf("MMCTIMR=        %x\n", eth->MMCTIMR);              
     printf("MMCTGFSCCR=     %x\n", eth->MMCTGFSCCR);           
     printf("MMCTGFMSCCR=    %x\n", eth->MMCTGFMSCCR);
     printf("MMCTGFCR=       %x\n", eth->MMCTGFCR);
     printf("MMCRFCECR=      %x\n", eth->MMCRFCECR);
     printf("MMCRFAECR=      %x\n", eth->MMCRFAECR);
     printf("MMCRGUFCR=      %x\n", eth->MMCRGUFCR);
     printf("MMCIPCINTMASKRX=%x\n", eth->MMCIPCINTMASKRX);
     printf("PTPTSCR=        %x\n", eth->PTPTSCR);
     printf("PTPSSIR=        %x\n", eth->PTPSSIR);
         printf("PTPTSHR=        %x\n", eth->PTPTSHR);
     printf("PTPTSLR=        %x\n", eth->PTPTSLR);
     printf("PTPTSHUR=       %x\n", eth->PTPTSHUR);
     printf("PTPTSLUR=       %x\n", eth->PTPTSLUR);
     printf("PTPTSAR=        %x\n", eth->PTPTSAR);
     printf("PTPTTHR=        %x\n", eth->PTPTTHR);
     printf("PTPTTLR=        %x\n", eth->PTPTTLR);
     printf("PTPTSSR=        %x\n", eth->PTPTSSR);
     printf("DMABMR=         %x\n", eth->DMABMR);
     printf("DMATPDR=        %x\n", eth->DMATPDR);
     printf("DMARPDR=        %x\n", eth->DMARPDR);
     printf("DMARDLAR=       %x\n", eth->DMARDLAR);
     printf("DMATDLAR=       %x\n", eth->DMATDLAR);
        
        
        printf("DMASR=          %x\n", eth->DMASR);
        
        
     printf("DMAOMR=         %x\n", eth->DMAOMR);
     printf("DMAIER=         %x\n", eth->DMAIER);
     printf("DMAMFBOCR=      %x\n", eth->DMAMFBOCR);
     printf("DMARSWTR=       %x\n", eth->DMARSWTR);
         printf("DMACHTDR=       %x\n", eth->DMACHTDR);
     printf("DMACHRDR=       %x\n", eth->DMACHRDR);
     printf("DMACHTBAR=      %x\n", eth->DMACHTBAR);
     printf("DMACHRBAR=      %x\n", eth->DMACHRBAR);

    ETH_PrintDMA("RxDscrTab", DMARxDscrTab, ETH_RXBUFCNT);
    ETH_PrintDMA("TxDscrTab", DMATxDscrTab, ETH_TXBUFNB);
}



void HAL_ETH_MspInit(ETH_HandleTypeDef* ethHandle)
{
    uint32_t prioritygroup;
    
  //gpio_init_t GPIO_InitStruct;
  if(ethHandle->Instance==ETH)
  {
  /* USER CODE BEGIN ETH_MspInit 0 */
    #define SWAPHCR (*(volatile unsigned int*)(0x40000054))      
    //#define SWAPCR5 (*(volatile unsigned int*)(0x4000006c))  
    #define CPM_CSWCFGR (*(volatile unsigned int*)(0x40004024)) 

//clock input from phy:
    SWAPHCR |= 0x1ff00000;//pin mux new
    CPM_CSWCFGR |= 0x00080000;//osc select from pad
    
    Eth_Reset();
  }
}

//static void Eth_Reset(void)
//{ 
//  
//    gpio_init_t uart_gpio_init;
////  gpio_pinstate_t PinState;

//    uart_gpio_init.Pin = UART_PIN_RXD;
//    uart_gpio_init.Dir = GPIO_DIR_OUT;

//    HAL_UART_GPIOInit(UART3, &uart_gpio_init);
//    HAL_UART_GPIOWritePin(UART3, UART_PIN_RXD, RESET);
//  HAL_Delay(500);
//    HAL_UART_GPIOWritePin(UART3, UART_PIN_RXD, SET);
//  HAL_Delay(500);


//}

#if 1
void Eth_Reset(void)
{ 
  
    


}
#else

void Eth_Reset(void)
{ 
        gpio_init_t uart_gpio_init;

//        __disable_irq();
        uart_gpio_init.Pin = UART_PIN_TXD;
        uart_gpio_init.Dir = GPIO_DIR_OUT;

        HAL_UART_GPIOInit(UART3, &uart_gpio_init);
        uart_gpio_init.Pin = UART_PIN_RXD;
        uart_gpio_init.Dir = GPIO_DIR_OUT;

        HAL_UART_GPIOInit(UART3, &uart_gpio_init);
        HAL_UART_GPIOWritePin(UART3, UART_PIN_TXD, RESET);
        HAL_UART_GPIOWritePin(UART3, UART_PIN_RXD, RESET);
        HAL_Delay_ms(500);
        HAL_UART_GPIOWritePin(UART3, UART_PIN_RXD, SET);
        HAL_Delay_ms(500);
//        __enable_irq();
}


#endif

void HAL_ETH_MspDeInit(ETH_HandleTypeDef* ethHandle)
{
  if(ethHandle->Instance==ETH)
  {
  /* USER CODE BEGIN ETH_MspDeInit 0 */

  /* USER CODE END ETH_MspDeInit 0 */
    /* Peripheral clock disable */
//        __HAL_RCC_ETH_CLK_DISABLE();
  
    /**ETH GPIO Configuration    
    PC1     ------> ETH_MDC
    PA1     ------> ETH_REF_CLK
    PA2     ------> ETH_MDIO
    PA7     ------> ETH_CRS_DV
    PC4     ------> ETH_RXD0
    PC5     ------> ETH_RXD1
    PB11     ------> ETH_TX_EN
    PG13     ------> ETH_TXD0
    PG14     ------> ETH_TXD1 
    */
//    HAL_GPIO_DeInit(GPIOC, ETH_MDC_Pin|ETH_RXD0_Pin|ETH_RXD1_Pin);

//    HAL_GPIO_DeInit(GPIOA, ETH_REF_CLK_Pin|ETH_MDIO_Pin|ETH_CRS_DV_Pin);

//    HAL_GPIO_DeInit(ETH_TX_EN_GPIO_Port, ETH_TX_EN_Pin);

//    HAL_GPIO_DeInit(GPIOG, ETH_TXD0_Pin|ETH_TXD1_Pin);

  /* USER CODE BEGIN ETH_MspDeInit 1 */

  /* USER CODE END ETH_MspDeInit 1 */
  }
}

#define LOG_D printf
#define LOG_E printf
#define LOG_I printf

#define PHY_LINK_MASK       (1<<0)

/* The PHY basic control register */
#define PHY_BASIC_CONTROL_REG       0x00U
#define PHY_RESET_MASK              (1<<15)
#define PHY_AUTO_NEGOTIATION_MASK   (1<<12)

/* The PHY basic status register */
#define PHY_BASIC_STATUS_REG        0x01U
#define PHY_LINKED_STATUS_MASK      (1<<2)
#define PHY_AUTONEGO_COMPLETE_MASK  (1<<5)

/* The PHY ID one register */
#define PHY_ID1_REG                 0x02U

/* The PHY ID two register */
#define PHY_ID2_REG                 0x03U

/* The PHY auto-negotiate advertise register */
#define PHY_AUTONEG_ADVERTISE_REG   0x04U

/*  The PHY interrupt source flag register. */
#define PHY_INTERRUPT_FLAG_REG      0x1DU
/*  The PHY interrupt mask register. */
#define PHY_INTERRUPT_MSAK_REG      0x1EU
#define PHY_LINK_DOWN_MASK          (1<<4)
#define PHY_AUTO_NEGO_COMPLETE_MASK (1<<6)

/*  The PHY status register. */
#define PHY_Status_REG              0x1FU
#define PHY_10M_MASK                (1<<2)
#define PHY_100M_MASK               (1<<3)
#define PHY_FULL_DUPLEX_MASK        (1<<4)
/* PHY_USING_LAN8720A */

static uint8_t phy_speed = 1;
uint32_t dev_link_changed = 0;
uint32_t dev_link_status = 0;
extern void* s_xSemaphore;
uint32_t eth_device_linkchange(bool up)
{
    uint32_t level;
        
        taskENTER_CRITICAL();
    dev_link_changed = 0x01;
    if (up == TRUE)
        dev_link_status = 0x01;
    else
        dev_link_status = 0x00;
        taskEXIT_CRITICAL();

    /* post message to ethernet thread */
    return xSemaphoreGive(s_xSemaphore);
}

void phy_monitor_thread_entry(void *parameter)
{
    uint8_t phy_addr = 0xFF;
    uint8_t phy_speed_new = 0;
    uint32_t status = 0;
    uint8_t detected_count = 0;

    while(phy_addr == 0xFF)
    {
        /* phy search */
        uint32_t i, temp;
        for (i = 0; i <= 0x1F; i++)
        {
            HAL_ETH_ReadPHYRegister(&heth, PHY_ID1_REG, (uint32_t *)&temp);

            if (temp != 0xFFFF && temp != 0x00)
            {
                phy_addr = i;
                break;
            }
        }

        detected_count++;
        vTaskDelay(1000);

        if (detected_count > 10)
        {
            LOG_E("No PHY device was detected, please check hardware!");
        }
    }

    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* RESET PHY */
    LOG_D("RESET PHY!");
    HAL_ETH_WritePHYRegister(&heth, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    vTaskDelay(2000);
    HAL_ETH_WritePHYRegister(&heth, PHY_BASIC_CONTROL_REG, PHY_AUTO_NEGOTIATION_MASK);

    while (1)
    {
        HAL_ETH_ReadPHYRegister(&heth, PHY_BASIC_STATUS_REG, (uint32_t *)&status);
//        LOG_D("PHY BASIC STATUS REG:0x%04X", status);

        phy_speed_new = 0;

        if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
        {
            uint32_t SR;

            phy_speed_new = PHY_LINK_MASK;

            SR = HAL_ETH_ReadPHYRegister(&heth, PHY_Status_REG, (uint32_t *)&SR);
//            LOG_D("PHY Control/Status REG:0x%04X ", SR);

            if (SR & PHY_100M_MASK)
            {
                phy_speed_new |= PHY_100M_MASK;
            }
            else if (SR & PHY_10M_MASK)
            {
                phy_speed_new |= PHY_10M_MASK;
            }

            if (SR & PHY_FULL_DUPLEX_MASK)
            {
                phy_speed_new |= PHY_FULL_DUPLEX_MASK;
            }
        }

        /* linkchange */
        if (phy_speed_new != phy_speed)
        {
            if (phy_speed_new & PHY_LINK_MASK)
            {
                LOG_D("link up ");

                if (phy_speed_new & PHY_100M_MASK)
                {
                    LOG_D("100Mbps");
//                    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
                }
                else
                {
//                    stm32_eth_device.ETH_Speed = ETH_SPEED_10M;
                    LOG_D("10Mbps");
                }

                if (phy_speed_new & PHY_FULL_DUPLEX_MASK)
                {
                    LOG_D("full-duplex");
//                    stm32_eth_device.ETH_Mode = ETH_MODE_FULLDUPLEX;
                }
                else
                {
                    LOG_D("half-duplex");
//                    stm32_eth_device.ETH_Mode = ETH_MODE_HALFDUPLEX;
                }

                /* send link up. */
                eth_device_linkchange(TRUE);
            } /* link up. */
            else
            {
                LOG_I("link down");
                /* send link down. */
                eth_device_linkchange(FALSE);
            }
            phy_speed = phy_speed_new;
        }

        vTaskDelay(1000);
    }
}

 uint8_t MACAddr[6] ;


status_t Bsp_Eth_Init(void)
{
  status_t ret;
  
  uint8_t val ;
    
    uint32_t phyregid1,phyregid2;
    
  HAL_ETH_DeInit(&heth);
  
  //Eth_Reset();
  
  ETH->DMABMR |= ETH_DMABMR_SR;
    
  /* Init ETH */
  MACAddr[0] = 0x02;
  MACAddr[1] = 0x03;
  MACAddr[2] = 0x04;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Instance = ETH;
  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_DISABLE;
  heth.Init.PhyAddress = LAN8720_PHY_ADDRESS;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.RxMode = ETH_RXINTERRUPT_MODE;  // rx mode   
  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
  heth.Init.Speed = ETH_SPEED_100M;       //speed
  heth.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
  heth.Init.EthDMAMode = EHT_DMA_MODE;
    printf("eth hardware init start\n");
  
    /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
  ret = HAL_ETH_Init(&heth);
    if (ret == STATUS_OK)
    {
        if( heth.Init.Speed == ETH_SPEED_100M )
        {
            printf("eth hardware init sucess...ETH_SPEED_100M\n");
        }
        else
        {
            printf("eth hardware init sucess...ETH_SPEED_10M\n");
        }
    }
  else
    printf("eth hardware init faild...\n");
    
    if((HAL_ETH_ReadPHYRegister(&heth, PHY_ID1, &phyregid1)) != STATUS_OK)
    {
        printf("eth HAL_ETH_ReadPHYRegister PHY_ID1 faild...\n");
    }
    else
    {
        printf("eth HAL_ETH_ReadPHYRegister PHY_ID1 OK = 0x%02x...\n",phyregid1);
    }
    
    if((HAL_ETH_ReadPHYRegister(&heth, PHY_ID2, &phyregid2)) != STATUS_OK)
    {
        printf("eth HAL_ETH_ReadPHYRegister PHY_ID1 faild...\n");
    }
    else
    {
        printf("eth HAL_ETH_ReadPHYRegister PHY_ID2 OK = 0x%02x...\n",phyregid2);
    }
    
  /* Initialize Tx Descriptors list: Chain Mode */
  HAL_ETH_DMATxDescListInit(&heth, DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
     
  /* Initialize Rx Descriptors list: Chain Mode  */
  HAL_ETH_DMARxDescListInit(&heth, DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFCNT);
    /* Enable MAC and DMA transmission and reception */   

  NVIC_Init(3, 3, GMAC_IRQn, 2);
    
    ETH_Print(); 
  return ret;
}


void GMAC_IRQHandler1(void)
//void ETH_IRQHandler(void)
{
  uint32_t ulReturn;
  /* 进入临界段，临界段可以嵌套 */
  ulReturn = taskENTER_CRITICAL_FROM_ISR();
  
//    printf("isr\n");
  HAL_ETH_IRQHandler(&heth);
  
  /* 退出临界段 */
  taskEXIT_CRITICAL_FROM_ISR( ulReturn );
}

/**
  * @brief  Ethernet Rx Transfer completed callback
  * @param  heth: ETH handle
  * @retval None
  */
//extern xSemaphoreHandle s_xSemaphore;
extern void* s_xSemaphore;
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
//  LED2_TOGGLE;
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR( s_xSemaphore, &xHigherPriorityTaskWoken );
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
  ;
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    printf("============================HAL_ETH_AISCallback\n");
}

void HAL_ETH_RBUCallback(ETH_HandleTypeDef *heth)
{
    printf("============================HAL_ETH_RBUCallback\n");
      portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR( s_xSemaphore, &xHigherPriorityTaskWoken );
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}