/**
 * @file eport_hal.c
 * @author Product application department
 * @brief  EPORT 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 *
 */

// 头文件包含
#include "eport_hal.h"

// 函数定义

/**
 * @brief EPORT 模块初始化函数
 *
 * @param pEportInit 指向 eport初始化结构体的指针
 * @return status_t 是否成功
 */
status_t hal_eport_init(eport_init_t *pEportInit)
{
    status_t ret = STATUS_OK;
    uint8_t i;
    hal_ioctrl_eportinit(&pEportInit->ioctrl_init);
    if (pEportInit->dir == GPIO_DIR_IN)
    {
        drv_eport_setpullup(pEportInit->Instance, pEportInit->pins, pEportInit->pull_up_status);
    }

    else
    {
        drv_eport_setopendrain(pEportInit->Instance, pEportInit->pins, pEportInit->output_mode);
    }
    drv_eport_setdirection(pEportInit->Instance, pEportInit->pins, pEportInit->dir);

    if (ENABLE == pEportInit->it_status)
    {
        if (pEportInit->Instance == EPORT0)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT0_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT1)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT1_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT2)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT2_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT3)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT3_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT4)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT4_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT5)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT5_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT6)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT6_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT7)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT7_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT8)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT8_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }
        else if (pEportInit->Instance == EPORT9)
        {
            for (i = 0; i < 8; i++)
            {
                if (pEportInit->pins & (0x01 << i))
                {
                    NVIC_Init(pEportInit->irq.NVIC_PreemptionPriority,
                              pEportInit->irq.NVIC_SubPriority,
                              (EPORT9_0_IRQn + i),
                              pEportInit->irq.NVIC_Group);
                }
            }
        }

        drv_eport_settriggermode(pEportInit->Instance, pEportInit->pins, pEportInit->it_type);
    }

    drv_eport_setit(pEportInit->Instance, pEportInit->pins, pEportInit->it_status);
    return ret;
}

/**
 * @brief EPORT 模块输出初始化函数
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 */
void hal_eport_output(reg_eport_t *pEport, uint8_t Pinx)
{
    eport_init_t eport_init;
    eport_init.pins = Pinx;
    eport_init.dir = GPIO_DIR_OUT;
    eport_init.output_mode = EPORT_OUTPUT_MODE_CMOS;
    eport_init.it_status = DISABLE;
    eport_init.it_type = EPORT_LOW_LEVEL_TRIGGER;
    eport_init.pull_up_status = DISABLE;
    eport_init.ioctrl_init.ds = DS_2MA;
    eport_init.ioctrl_init.sr = SR_NULL;
    eport_init.ioctrl_init.is = IS_NULL;
    eport_init.ioctrl_init.pins = eport_init.pins;
    eport_init.ioctrl_init.ie = IE_INPUT_DIS;
    eport_init.ioctrl_init.ps = PS_PULL_NULL;
    eport_init.irq.NVIC_SubPriority = 3;
    eport_init.irq.NVIC_PreemptionPriority = 3;
    eport_init.irq.NVIC_Group = 2;
    /* EPORT初始化 */
    eport_init.Instance = pEport;

    if (pEport == EPORT0)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT0;
    }

    if (pEport == EPORT1)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT1;
    }

    if (pEport == EPORT2)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT2;
    }

    if (pEport == EPORT3)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT3;
    }

    if (pEport == EPORT4)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT4;
    }

    if (pEport == EPORT5)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT5;
    }

    if (pEport == EPORT6)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT6;
    }

    if (pEport == EPORT7)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT7;
    }
    if (pEport == EPORT8)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT8;
    }
    if (pEport == EPORT9)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT9;
    }
    hal_eport_init(&eport_init);
}

/**
 * @brief EPORT 模块输出电平函数
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 * @param Level 电平值
 */
void hal_eport_writepinlevel(reg_eport_t *pEport, uint8_t Pinx, gpio_pinstate_t Level)
{
    drv_eport_writepinslevel(pEport, Pinx, Level);
    dcache_invalidate_range(pEport,sizeof(pEport));
}

/**
 * @brief EPORT 模块输入配置
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 * @param ps 上拉/下拉/浮空
 */
void hal_eport_input(reg_eport_t *pEport, uint8_t Pinx, ioctrl_ps_t ps)
{
    eport_init_t eport_init;
    eport_init.pins = Pinx;
    eport_init.dir = GPIO_DIR_IN;
    eport_init.output_mode = EPORT_OUTPUT_MODE_CMOS;
    eport_init.it_status = DISABLE;
    eport_init.it_type = EPORT_FALLING_TRIGGER;
    if (ps == PS_PULL_NULL)
        eport_init.pull_up_status = DISABLE;
    else
        eport_init.pull_up_status = ENABLE;

    eport_init.ioctrl_init.ds = DS_2MA;
    eport_init.ioctrl_init.sr = SR_NULL;
    eport_init.ioctrl_init.is = IS_INPUT_CMOS;
    eport_init.ioctrl_init.pins = eport_init.pins;
    eport_init.ioctrl_init.ie = IE_INPUT_EN;
    eport_init.ioctrl_init.ps = ps;
    eport_init.Instance = pEport;
    eport_init.irq.NVIC_SubPriority = 3;
    eport_init.irq.NVIC_PreemptionPriority = 3;
    eport_init.irq.NVIC_Group = 2;

    if (pEport == EPORT0)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT0;
    }

    if (pEport == EPORT1)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT1;
    }

    if (pEport == EPORT2)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT2;
    }

    if (pEport == EPORT3)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT3;
    }

    if (pEport == EPORT4)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT4;
    }

    if (pEport == EPORT5)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT5;
    }

    if (pEport == EPORT6)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT6;
    }

    if (pEport == EPORT7)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT7;
    }
    if (pEport == EPORT8)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT8;
    }
    if (pEport == EPORT9)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT9;
    }
    eport_init.pins = Pinx;
    hal_eport_init(&eport_init);
}

/**
 * @brief EPORT 模块读取pin脚状态函数
 *
 * @param pEport EPORT实例化
 * @param pins EPORT引脚
 * @return uint8_t 返回pin脚电平
 */
uint8_t hal_eport_readpinslevel(reg_eport_t *pEport, uint8_t pins)
{
    if (_eport_eppdr_pin_data_get(pEport, pins) == 0)
        return BIT_RESET;
    else
        return BIT_SET;
}

/**
 * @brief EPORT 模块中断服务函数
 *
 */
void hal_eport0_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN0);
}
void hal_eport0_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN1);
}
void hal_eport0_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN2);
}
void hal_eport0_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN3);
}
void hal_eport0_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN4);
}
void hal_eport0_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN5);
}
void hal_eport0_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN6);
}
void hal_eport0_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT0, EPORT0_PIN7);
}
void hal_eport1_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN0);
}
void hal_eport1_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN1);
}
void hal_eport1_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN2);
}
void hal_eport1_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN3);
}
void hal_eport1_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN4);
}
void hal_eport1_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN5);
}
void hal_eport1_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN6);
}
void hal_eport1_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT1, EPORT1_PIN7);
}
void hal_eport2_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN0);
}
void hal_eport2_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN1);
}
void hal_eport2_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN2);
}
void hal_eport2_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN3);
}
void hal_eport2_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN4);
}
void hal_eport2_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN5);
}
void hal_eport2_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN6);
}
void hal_eport2_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT2, EPORT2_PIN7);
}
void hal_eport3_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN0);
}
void hal_eport3_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN1);
}
void hal_eport3_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN2);
}
void hal_eport3_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN3);
}
void hal_eport3_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN4);
}
void hal_eport3_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN5);
}
void hal_eport3_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN6);
}
void hal_eport3_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT3, EPORT3_PIN7);
}
void hal_eport4_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN0);
}
void hal_eport4_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN1);
}
void hal_eport4_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN2);
}
void hal_eport4_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN3);
}
void hal_eport4_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN4);
}
void hal_eport4_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN5);
}
void hal_eport4_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN6);
}
void hal_eport4_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT4, EPORT4_PIN7);
}
void hal_eport5_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN0);
}
void hal_eport5_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN1);
}
void hal_eport5_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN2);
}
void hal_eport5_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN3);
}
void hal_eport5_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN4);
}
void hal_eport5_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN5);
}
void hal_eport5_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN6);
}

void hal_eport5_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT5, EPORT5_PIN7);
}
void hal_eport6_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN0);
}
void hal_eport6_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN1);
}
void hal_eport6_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN2);
}
void hal_eport6_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN3);
}
void hal_eport6_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN4);
}
void hal_eport6_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN5);
}
void hal_eport6_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN6);
}
void hal_eport6_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT6, EPORT6_PIN7);
}
void hal_eport7_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN0);
}
void hal_eport7_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN1);
}
void hal_eport7_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN2);
}
void hal_eport7_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN3);
}
void hal_eport7_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN4);
}
void hal_eport7_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN5);
}
void hal_eport7_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN6);
}
void hal_eport7_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT7, EPORT7_PIN7);
}
void hal_eport8_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN0);
}
void hal_eport8_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN1);
}
void hal_eport8_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN2);
}
void hal_eport8_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN3);
}
void hal_eport8_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN4);
}
void hal_eport8_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN5);
}
void hal_eport8_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN6);
}
void hal_eport8_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT8, EPORT8_PIN7);
}
void hal_eport9_0_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN0);
}
void hal_eport9_1_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN1);
}
void hal_eport9_2_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN2);
}
void hal_eport9_3_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN3);
}
void hal_eport9_4_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN4);
}
void hal_eport9_5_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN5);
}
void hal_eport9_6_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN6);
}
void hal_eport9_7_irqhandler(void)
{
    drv_eport_clearitflag(EPORT9, EPORT9_PIN7);
}
/**
 * @brief EPORT 模块中断回调函数注册函数
 * @param
 */
void HAL_EPORT_SetIRQHandlerCallback(void)
{
    EPORT0_0_IRQHandler_Callback = hal_eport0_0_irqhandler;
    EPORT0_1_IRQHandler_Callback = hal_eport0_1_irqhandler;
    EPORT0_2_IRQHandler_Callback = hal_eport0_2_irqhandler;
    EPORT0_3_IRQHandler_Callback = hal_eport0_3_irqhandler;
    EPORT0_4_IRQHandler_Callback = hal_eport0_4_irqhandler;
    EPORT0_5_IRQHandler_Callback = hal_eport0_5_irqhandler;
    EPORT0_6_IRQHandler_Callback = hal_eport0_6_irqhandler;
    EPORT0_7_IRQHandler_Callback = hal_eport0_7_irqhandler;
    EPORT1_0_IRQHandler_Callback = hal_eport1_0_irqhandler;
    EPORT1_1_IRQHandler_Callback = hal_eport1_1_irqhandler;
    EPORT1_2_IRQHandler_Callback = hal_eport1_2_irqhandler;
    EPORT1_3_IRQHandler_Callback = hal_eport1_3_irqhandler;
    EPORT1_4_IRQHandler_Callback = hal_eport1_4_irqhandler;
    EPORT1_5_IRQHandler_Callback = hal_eport1_5_irqhandler;
    EPORT1_6_IRQHandler_Callback = hal_eport1_6_irqhandler;
    EPORT1_7_IRQHandler_Callback = hal_eport1_7_irqhandler;
    EPORT2_0_IRQHandler_Callback = hal_eport2_0_irqhandler;
    EPORT2_1_IRQHandler_Callback = hal_eport2_1_irqhandler;
    EPORT2_2_IRQHandler_Callback = hal_eport2_2_irqhandler;
    EPORT2_3_IRQHandler_Callback = hal_eport2_3_irqhandler;
    EPORT2_4_IRQHandler_Callback = hal_eport2_4_irqhandler;
    EPORT2_5_IRQHandler_Callback = hal_eport2_5_irqhandler;
    EPORT2_6_IRQHandler_Callback = hal_eport2_6_irqhandler;
    EPORT2_7_IRQHandler_Callback = hal_eport2_7_irqhandler;
    EPORT3_0_IRQHandler_Callback = hal_eport3_0_irqhandler;
    EPORT3_1_IRQHandler_Callback = hal_eport3_1_irqhandler;
    EPORT3_2_IRQHandler_Callback = hal_eport3_2_irqhandler;
    EPORT3_3_IRQHandler_Callback = hal_eport3_3_irqhandler;
    EPORT3_4_IRQHandler_Callback = hal_eport3_4_irqhandler;
    EPORT3_5_IRQHandler_Callback = hal_eport3_5_irqhandler;
    EPORT3_6_IRQHandler_Callback = hal_eport3_6_irqhandler;
    EPORT3_7_IRQHandler_Callback = hal_eport3_7_irqhandler;
    EPORT4_0_IRQHandler_Callback = hal_eport4_0_irqhandler;
    EPORT4_1_IRQHandler_Callback = hal_eport4_1_irqhandler;
    EPORT4_2_IRQHandler_Callback = hal_eport4_2_irqhandler;
    EPORT4_3_IRQHandler_Callback = hal_eport4_3_irqhandler;
    EPORT4_4_IRQHandler_Callback = hal_eport4_4_irqhandler;
    EPORT4_5_IRQHandler_Callback = hal_eport4_5_irqhandler;
    EPORT4_6_IRQHandler_Callback = hal_eport4_6_irqhandler;
    EPORT4_7_IRQHandler_Callback = hal_eport4_7_irqhandler;
    EPORT5_0_IRQHandler_Callback = hal_eport5_0_irqhandler;
    EPORT5_1_IRQHandler_Callback = hal_eport5_1_irqhandler;
    EPORT5_2_IRQHandler_Callback = hal_eport5_2_irqhandler;
    EPORT5_3_IRQHandler_Callback = hal_eport5_3_irqhandler;
    EPORT5_4_IRQHandler_Callback = hal_eport5_4_irqhandler;
    EPORT5_5_IRQHandler_Callback = hal_eport5_5_irqhandler;
    EPORT5_6_IRQHandler_Callback = hal_eport5_6_irqhandler;
    EPORT5_7_IRQHandler_Callback = hal_eport5_7_irqhandler;
    EPORT6_0_IRQHandler_Callback = hal_eport6_0_irqhandler;
    EPORT6_1_IRQHandler_Callback = hal_eport6_1_irqhandler;
    EPORT6_2_IRQHandler_Callback = hal_eport6_2_irqhandler;
    EPORT6_3_IRQHandler_Callback = hal_eport6_3_irqhandler;
    EPORT6_4_IRQHandler_Callback = hal_eport6_4_irqhandler;
    EPORT6_5_IRQHandler_Callback = hal_eport6_5_irqhandler;
    EPORT6_6_IRQHandler_Callback = hal_eport6_6_irqhandler;
    EPORT6_7_IRQHandler_Callback = hal_eport6_0_irqhandler;
    EPORT7_0_IRQHandler_Callback = hal_eport7_0_irqhandler;
    EPORT7_1_IRQHandler_Callback = hal_eport7_1_irqhandler;
    EPORT7_2_IRQHandler_Callback = hal_eport7_2_irqhandler;
    EPORT7_3_IRQHandler_Callback = hal_eport7_3_irqhandler;
    EPORT7_4_IRQHandler_Callback = hal_eport7_4_irqhandler;
    EPORT7_5_IRQHandler_Callback = hal_eport7_5_irqhandler;
    EPORT7_6_IRQHandler_Callback = hal_eport7_6_irqhandler;
    EPORT7_7_IRQHandler_Callback = hal_eport7_7_irqhandler;
    EPORT8_0_IRQHandler_Callback = hal_eport8_0_irqhandler;
    EPORT8_1_IRQHandler_Callback = hal_eport8_1_irqhandler;
    EPORT8_2_IRQHandler_Callback = hal_eport8_2_irqhandler;
    EPORT8_3_IRQHandler_Callback = hal_eport8_3_irqhandler;
    EPORT8_4_IRQHandler_Callback = hal_eport8_4_irqhandler;
    EPORT8_5_IRQHandler_Callback = hal_eport8_5_irqhandler;
    EPORT8_6_IRQHandler_Callback = hal_eport8_6_irqhandler;
    EPORT8_7_IRQHandler_Callback = hal_eport8_7_irqhandler;
    EPORT9_0_IRQHandler_Callback = hal_eport9_0_irqhandler;
    EPORT9_1_IRQHandler_Callback = hal_eport9_1_irqhandler;
    EPORT9_2_IRQHandler_Callback = hal_eport9_2_irqhandler;
    EPORT9_3_IRQHandler_Callback = hal_eport9_3_irqhandler;
    EPORT9_4_IRQHandler_Callback = hal_eport9_4_irqhandler;
    EPORT9_5_IRQHandler_Callback = hal_eport9_5_irqhandler;
    EPORT9_6_IRQHandler_Callback = hal_eport9_6_irqhandler;
    EPORT9_7_IRQHandler_Callback = hal_eport9_7_irqhandler;
}

/** @brief         EPORT 模块中断配函数置
 * @param[in] pEport:EPORT实例化
 * @param[in] Pins: EPORT引脚
 * @return      null
 **/
void hal_eport_interrupt(reg_eport_t *pEport, uint8_t Pinx, eport_intmode_t int_type, ioctrl_ps_t ps)
{
    HAL_EPORT_SetIRQHandlerCallback();
    eport_init_t eport_init;
    eport_init.pins = Pinx;
    eport_init.dir = GPIO_DIR_IN;
    eport_init.output_mode = EPORT_OUTPUT_MODE_CMOS;
    eport_init.it_status = ENABLE;
    eport_init.it_type = int_type;
    eport_init.pull_up_status = DISABLE;
    eport_init.ioctrl_init.ds = DS_2MA;
    eport_init.ioctrl_init.sr = SR_NULL;
    eport_init.ioctrl_init.is = IS_INPUT_CMOS;
    eport_init.ioctrl_init.pins = eport_init.pins;
    eport_init.ioctrl_init.ie = IE_INPUT_EN;
    eport_init.ioctrl_init.ps = ps;
    eport_init.Instance = pEport;
    eport_init.irq.NVIC_SubPriority = 3;
    eport_init.irq.NVIC_PreemptionPriority = 3;
    eport_init.irq.NVIC_Group = 2;
    if (pEport == EPORT0)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT0;
    }

    if (pEport == EPORT1)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT1;
    }

    if (pEport == EPORT2)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT2;
    }
    if (pEport == EPORT3)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT3;
    }
    if (pEport == EPORT4)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT4;
    }
    if (pEport == EPORT5)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT5;
    }

    if (pEport == EPORT6)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT6;
    }

    if (pEport == EPORT7)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT7;
    }
    if (pEport == EPORT8)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT8;
    }

    if (pEport == EPORT9)
    {
        eport_init.ioctrl_init.id = IOCTRL_EPORT9;
    }
    hal_eport_init(&eport_init);
}
